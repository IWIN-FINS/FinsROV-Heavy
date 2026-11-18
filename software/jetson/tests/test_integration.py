"""Protocol, actual portable MCU state machine, and fixed PC over real UDP."""
import hashlib
import json
import math
import os
from pathlib import Path
import socket
import subprocess
import sys
import time
import unittest

JETSON = Path(__file__).resolve().parents[1]
ROOT = JETSON.parents[1]
sys.path.insert(0, str(JETSON))
from fins_bridge.codec import Codec
from fins_bridge.bridge import Bridge
from fins_bridge.runtime import HostMCU, Runtime


class Endpoint:
    def __init__(self):
        binary = Path(os.environ.get('FINS_ENDPOINT_HOST', ROOT/'build/integration/endpoint_host.exe'))
        if not binary.exists():
            raise RuntimeError('Build firmware/integrated/tests/endpoint_host.cpp and set FINS_ENDPOINT_HOST')
        self.p = subprocess.Popen([str(binary)], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                  text=True, bufsize=1)
        self.codec = Codec(255,190)
        self.now = 1000000
        self.sequence = 0
        self.exchange('FINS_CAPABILITIES',session=7,protocol_version=1,mode_mask=0,features=3,simulated=0)

    def close(self):
        self.p.stdin.close(); self.p.wait(timeout=3); self.p.stdout.close()

    def raw(self, data):
        self.p.stdin.write(f'{self.now} {data}\n'); self.p.stdin.flush()
        messages=[]
        while True:
            line=self.p.stdout.readline().strip()
            if line=='.': break
            if not line: raise RuntimeError('Endpoint exited')
            messages.extend(self.codec.decode(bytes.fromhex(line)))
        self.status=next(m for m in reversed(messages) if m.get_type()=='FINS_STATUS')
        return messages

    def exchange(self, kind, **data):
        return self.raw(self.codec.encode(kind,**data).hex())

    def action(self, action, value, request=1, epoch=1):
        result=self.exchange('FINS_ACTION_REQUEST',session=7,target_session=1234567,
                             request_id=request,epoch=epoch,action=action,value=value)
        return next(m for m in result if m.get_type()=='FINS_ACTION_ACK')

    def manual(self):
        self.action(1,1);self.action(2,1,request=2)

    def control(self, **overrides):
        self.sequence+=1
        args=dict(session=7,target_session=1234567,source_us=self.now,epoch=1,
                  sequence=self.sequence,valid_ms=200,yaw=0.,forward=.5,left=0.,down=0.,up=0.,depth_target=.5,vertical_mode=0)
        args.update(overrides)
        return self.exchange('FINS_CONTROL_SETPOINT',**args)


class MCUIntegration(unittest.TestCase):
    def setUp(self): self.e=Endpoint();self.addCleanup(self.e.close)

    def test_execution_ack_and_rejected_readiness(self):
        self.e.action(1,1);self.e.raw('notready')
        self.assertEqual(1,self.e.action(2,1,2).result)
        self.assertFalse(self.e.status.armed)

    def test_duplicate_arming_is_not_toggle(self):
        self.e.manual(); self.e.action(2,1,2)
        self.assertTrue(self.e.status.armed)

    def test_disarm_during_mode_transition(self):
        self.e.manual();self.e.action(1,2,3,2)
        self.assertEqual(0,self.e.action(2,0,4,1).result)
        self.assertFalse(self.e.status.armed)

    def test_expiry_latches_stop_and_fresh_command_cannot_restart(self):
        self.e.manual();self.e.control();self.e.now+=200001;self.e.raw('tick')
        self.assertEqual(0,self.e.status.mode)
        self.e.control();self.assertEqual(0,self.e.status.mode)
        self.assertFalse(self.e.status.armed)

    def test_delayed_source_keeps_remaining_validity(self):
        self.e.manual();self.e.control(source_us=self.e.now-150000)
        self.e.now+=50001;self.e.raw('tick');self.assertEqual(0,self.e.status.mode)

    def test_future_source_cannot_extend_200ms(self):
        self.e.manual();self.e.control(source_us=self.e.now+40000)
        self.e.now+=200001;self.e.raw('tick');self.assertEqual(0,self.e.status.mode)

    def test_bad_sequence_session_epoch_nan_do_not_refresh(self):
        for overrides in [dict(sequence=0),dict(session=99),dict(epoch=99),dict(forward=float('nan'))]:
            with self.subTest(overrides=overrides):
                e=Endpoint()
                try:
                    e.manual();e.control(sequence=1);e.now+=150000;e.control(**overrides)
                    e.now+=50001;e.raw('tick');self.assertEqual(0,e.status.mode)
                finally:e.close()

    def test_crc_corruption_and_fragmented_stream(self):
        self.e.manual()
        frame=self.e.codec.encode('FINS_ACTION_REQUEST',session=7,target_session=1234567,request_id=3,epoch=1,action=2,value=0)
        corrupt=bytearray(frame);corrupt[-1]^=128
        self.e.raw(corrupt.hex());self.assertTrue(self.e.status.armed)
        self.e.raw(frame[:8].hex());self.assertTrue(self.e.status.armed)
        self.e.raw(frame[8:].hex());self.assertFalse(self.e.status.armed)

    def test_new_client_clears_armed_state(self):
        self.e.manual();self.e.exchange('FINS_CAPABILITIES',session=8,protocol_version=1,mode_mask=0,features=3,simulated=0)
        self.assertEqual(8,self.e.status.client_session);self.assertFalse(self.e.status.armed)


class BridgeTests(unittest.TestCase):
    def setUp(self):
        self.to_pc=[];self.to_mcu=[];self.c=Codec()
        self.b=Bridge(lambda k,**f:self.to_pc.append((k,f)),lambda k,**f:self.to_mcu.append((k,f)))
    def message(self,k,**f):return self.c.decode(self.c.encode(k,**f))[0]

    def test_no_ack_until_mcu_executes(self):
        b=self.b;b.client=7;b.mcu_session=9;b.last_mcu=b.last_sync=10;b.offset_us=0
        b.receive_pc(self.message('FINS_ACTION_REQUEST',session=7,target_session=b.session,request_id=1,epoch=1,action=1,value=1),10)
        self.assertEqual([],self.to_pc);self.assertEqual(9,self.to_mcu[-1][1]['target_session'])

    def test_mcu_reboot_revokes_session(self):
        b=self.b;b.client=7;b.mcu_session=9;old=b.session
        b.receive_mcu(self.message('FINS_CAPABILITIES',session=10,protocol_version=1,mode_mask=7,features=1,simulated=0),10)
        self.assertNotEqual(old,b.session);self.assertIsNone(b.client)

    def test_bad_odometry_and_source_age(self):
        data=dict(source_us=10000000,sample_seq=1,reset_id=0,x=0.,y=0.,yaw=0.,vx=0.,vy=0.,yaw_rate=0.,depth=.5,valid=1,depth_valid=1)
        self.b.receive_odometry(data,10);self.assertTrue(self.b.odom_fresh(10))
        for change in [dict(x=math.nan),dict(source_us=9000000),dict(sample_seq=-1),dict(depth=-1.)]:
            with self.assertRaises(ValueError):self.b.receive_odometry(dict(data,**change),10)
        self.b.client=7;self.b.mode=2;self.b.last_mcu=10.3;self.b.mcu_session=9
        self.b.tick(10.3);self.assertIsNone(self.b.client)

    def test_clock_conservative_translation(self):
        b=self.b;b.sync_request=10000000000
        b.receive_mcu(self.message('TIMESYNC',tc1=2000500000,ts1=b.sync_request),10.01)
        self.assertEqual(2000500-10010000-2000,b.offset_us)

    def test_pinned_vectors(self):
        for vector in json.loads((ROOT/'protocol/test_vectors.json').read_text()):
            codec=Codec(255,190)
            self.assertEqual(vector['hex'],codec.encode(vector['name'],**vector['fields']).hex())

    def test_imported_bytes_match_pinned_manifest(self):
        for record in json.loads((ROOT/'protocol/provenance.json').read_text())['files']:
            self.assertEqual(record['sha256'],hashlib.sha256((ROOT/record['path']).read_bytes()).hexdigest(),record['path'])

    def test_odometry_reset_revokes_execution(self):
        b=self.b
        sample=dict(source_us=10000000,sample_seq=1,reset_id=0,x=0.,y=0.,yaw=0.,vx=0.,vy=0.,yaw_rate=0.,depth=.5,valid=1,depth_valid=1)
        b.receive_odometry(sample,10);b.client=7;b.mode=2;old=b.session
        b.receive_odometry(dict(sample,sample_seq=2,reset_id=1),10)
        self.assertIsNone(b.client);self.assertNotEqual(old,b.session)

    def test_stale_mcu_link_revokes_execution(self):
        b=self.b;b.client=7;b.mcu_session=9;b.mode=1;b.last_mcu=10
        b.tick(10.301);self.assertIsNone(b.client);self.assertEqual(0,b.mode)


class FixedPCIntegration(unittest.TestCase):
    def test_fixed_pc_controller_real_udp_and_cpp_serial_endpoint(self):
        pc_root=os.environ.get('FINS_PC_ROOT')
        if not pc_root: self.skipTest('Set FINS_PC_ROOT to the pinned read-only PC checkout')
        sys.path.insert(0,pc_root)
        from groundstation.controller import Controller
        from groundstation.models import Action,Mode,InputSnapshot,Axes
        from trajectory_tracking import Waypoint,TrackingSettings
        pc_socket=socket.socket(socket.AF_INET,socket.SOCK_DGRAM);pc_socket.bind(('127.0.0.1',0));pc_socket.setblocking(False)
        binary=Path(os.environ.get('FINS_ENDPOINT_HOST',ROOT/'build/integration/endpoint_host.exe'))
        runtime=Runtime(HostMCU(binary),('127.0.0.1',0),pc_socket.getsockname(),simulated=True,replay=True)
        codec=Codec(255,190)
        pc=Controller(lambda k,**f:pc_socket.sendto(codec.encode(k,**f),runtime.socket.getsockname()))
        def advance(duration=.15):
            end=time.monotonic()+duration
            while time.monotonic()<end:
                now=time.monotonic();pc.input=InputSnapshot(now,True,Axes(),source='keyboard');pc.tick(now);runtime.step()
                while True:
                    try:data,_=pc_socket.recvfrom(4096)
                    except BlockingIOError:break
                    for message in codec.decode(data):pc.receive(message,time.monotonic())
                time.sleep(.005)
        try:
            advance(1.1);self.assertTrue(pc.ready(time.monotonic()));self.assertTrue(pc.simulated)
            pc.request(Action.SET_MODE,Mode.MANUAL,time.monotonic());advance()
            pc.request(Action.SET_ARMED,1,time.monotonic());advance();self.assertTrue(pc.armed)
            pc.request(Action.SET_MODE,Mode.TRAJECTORY,time.monotonic(),dict(points=(Waypoint(0,0,0,1),Waypoint(1,0,0,2)),settings=TrackingSettings()))
            advance();self.assertEqual(Mode.TRAJECTORY,pc.mode)
            pc.request(Action.SET_MODE,Mode.IDLE,time.monotonic());advance();self.assertEqual(Mode.IDLE,pc.mode)
            pc.request(Action.SET_MODE,Mode.MANUAL,time.monotonic());advance();self.assertEqual(Mode.MANUAL,pc.mode)
            # Stop PC traffic while MCU and bridge keep running: execution times out.
            end=time.monotonic()+.3
            while time.monotonic()<end:runtime.step();time.sleep(.005)
            self.assertEqual(0,runtime.bridge.mode)
        finally:runtime.close();pc_socket.close()
