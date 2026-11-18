"""Single-owner bridge. Execution ACKs originate only at the MCU endpoint."""
import math
import secrets
from .codec import fields


class Bridge:
    def __init__(self, pc_send, mcu_send, *, simulated=False):
        self.pc_send, self.mcu_send = pc_send, mcu_send
        self.simulated = simulated
        self.session = secrets.randbits(63) or 1
        self.client = self.mcu_session = None
        self.last_mcu = self.last_sync = -math.inf
        self.offset_us = None
        self.sync_request = None
        self.last_probe = -math.inf
        self.mode = 0
        self.odometry = None
        self.last_odom_seq = None
        self.reset_id = None
        self.features = 0
        self.clock_fault = False

    def invalidate(self):
        """Revoke execution on uncertainty; a new handshake is mandatory."""
        self.session = secrets.randbits(63) or 1
        self.client = None
        self.mode = 0
        self.offset_us = None
        self.mcu_send('FINS_CAPABILITIES', session=secrets.randbits(63) or 1,
                      protocol_version=1, mode_mask=0, features=0, simulated=0)

    def receive_pc(self, m, now):
        kind, data = m.get_type(), fields(m)
        if kind == 'TIMESYNC' and m.tc1 == 0:
            self.pc_send(kind, tc1=int(now * 1e9), ts1=m.ts1)
            return
        if kind == 'FINS_CAPABILITIES' and m.protocol_version == 1 and m.mode_mask == 0:
            if not m.session:
                return
            if m.session != self.client:
                self.client = m.session
                self.mode = 0
            self.mcu_send(kind, **data)
            return
        if (not self.client or getattr(m, 'session', None) != self.client
                or getattr(m, 'target_session', None) != self.session
                or self.mcu_session is None or now - self.last_mcu > .3):
            return
        if kind == 'FINS_ACTION_REQUEST':
            if m.action == 1 and m.value == 2 and not self.odom_fresh(now):
                self.reject(m, 2)
                return
            # Arming/motion requires a recent conservative MCU clock estimate.
            if ((m.action == 1 and m.value != 0) or (m.action == 2 and m.value == 1)) and not self.clock_ready(now):
                self.reject(m, 2)
                return
        elif kind == 'FINS_CONTROL_SETPOINT':
            if not self.clock_ready(now) or (self.mode == 2 and not self.odom_fresh(now)):
                return
            age_us = int(now * 1e6) - m.source_us
            if not 0 < m.valid_ms <= 200 or age_us < -50000 or age_us >= m.valid_ms * 1000:
                return
            # offset is MCU clock - NX clock, with one full RTT + 2ms removed.
            # Source validity is translated, never restarted at serial receive.
            source = m.source_us + self.offset_us
            if source < 0:
                return
            data['source_us'] = source
        else:
            return  # Auxiliary hardware/reset are not silently emulated.
        data['target_session'] = self.mcu_session
        self.mcu_send(kind, **data)

    def reject(self, request, reason):
        self.pc_send('FINS_ACTION_ACK', session=self.session, target_session=request.session,
                     request_id=request.request_id, epoch=request.epoch, action=request.action,
                     result=1, reason=reason)

    def receive_mcu(self, m, now):
        kind, data = m.get_type(), fields(m)
        if kind == 'TIMESYNC' and self.sync_request == m.ts1 and m.tc1 > 0:
            rtt_us = int(now * 1e6) - m.ts1 // 1000
            self.sync_request = None
            if 0 <= rtt_us <= 20000:
                self.offset_us = m.tc1 // 1000 - int(now * 1e6) - 2000
                self.last_sync = now
            return
        if kind == 'FINS_CAPABILITIES':
            if m.protocol_version != 1 or m.mode_mask == 0:
                return
            if self.mcu_session is not None and self.mcu_session != m.session:
                self.mcu_session = m.session
                self.invalidate()
                return
            self.mcu_session = m.session
            self.features = m.features & 1  # No unimplemented light/gimbal capability.
            self.last_mcu = now
            if self.client:
                data.update(session=self.session, simulated=int(self.simulated), features=self.features)
                self.pc_send(kind, **data)
            return
        if getattr(m, 'session', None) != self.mcu_session:
            return
        if kind == 'FINS_STATUS':
            if m.client_session != self.client:
                return
            self.last_mcu = now
            self.mode = m.mode
        elif kind == 'FINS_ACTION_ACK':
            if m.target_session != self.client:
                return
        elif kind == 'FINS_TELEMETRY':
            if not self.clock_ready(now):
                return
            data['source_us'] = max(0, m.source_us - self.offset_us)
        else:
            return
        data['session'] = self.session
        self.pc_send(kind, **data)

    def clock_ready(self, now):
        return self.offset_us is not None and now - self.last_sync < 2

    def odom_fresh(self, now):
        return (self.odometry is not None and self.odometry['valid'] == 1
                and -.005 <= now - self.odometry['source_us'] / 1e6 < .2)

    def receive_odometry(self, data, now):
        required = {'source_us', 'sample_seq', 'reset_id', 'x', 'y', 'yaw', 'vx', 'vy',
                    'yaw_rate', 'depth', 'valid', 'depth_valid'}
        if set(data) != required:
            raise ValueError('Odometry must supply the documented fields exactly')
        for key in ('source_us', 'sample_seq', 'reset_id', 'valid', 'depth_valid'):
            if type(data[key]) is not int or data[key] < 0:
                raise ValueError('Invalid odometry integer: ' + key)
        if data['sample_seq'] > 0xffffffff or data['reset_id'] > 0xffffffff or data['source_us'] > 0xffffffffffffffff:
            raise ValueError('Odometry counter outside wire range')
        if data['valid'] not in (0, 1) or data['depth_valid'] not in (0, 1):
            raise ValueError('Validity must be 0 or 1')
        if any(not math.isfinite(data[k]) for k in required - {'source_us', 'sample_seq', 'reset_id', 'valid', 'depth_valid'}):
            raise ValueError('Nonfinite odometry')
        if data['depth'] < 0 or not -.005 <= now - data['source_us'] / 1e6 < .2:
            raise ValueError('Stale/future odometry or negative depth')
        if self.reset_id is not None and data['reset_id'] != self.reset_id:
            self.invalidate()
            self.last_odom_seq = None
        if self.last_odom_seq is not None and not 0 < ((data['sample_seq'] - self.last_odom_seq) & 0xffffffff) < 0x80000000:
            return
        self.reset_id, self.last_odom_seq = data['reset_id'], data['sample_seq']
        self.odometry = data.copy()
        if self.client:
            self.pc_send('FINS_ODOMETRY', session=self.session, **data)

    def tick(self, now):
        if self.client and ((self.mcu_session is not None and now - self.last_mcu > .3)
                            or (self.mode == 2 and not self.odom_fresh(now))):
            self.invalidate()
        if now - self.last_probe >= .5:
            self.sync_request = int(now * 1e9)
            self.mcu_send('TIMESYNC', tc1=0, ts1=self.sync_request)
            self.last_probe = now
