"""Executable bridge with explicit physical serial and host-harness transports."""
import argparse
import json
import logging
import math
from pathlib import Path
import secrets
import socket
import subprocess
import time
import queue
import threading
from .bridge import Bridge
from .codec import Codec


class HostMCU:
    """Runs the real C++ endpoint against nonphysical actuators."""
    def __init__(self, executable):
        self.process = subprocess.Popen([str(executable)], stdin=subprocess.PIPE,
                                        stdout=subprocess.PIPE, text=True, bufsize=1)
        self.started = time.monotonic() - 1
        self.pending = bytearray()
        self.lines = queue.Queue(maxsize=512)
        self.reader = threading.Thread(target=self._read_lines, daemon=True)
        self.reader.start()

    def _read_lines(self):
        for line in self.process.stdout:
            try:
                self.lines.put(line.strip(), timeout=.2)
            except queue.Full:
                return

    def exchange(self, value):
        now = int((time.monotonic() - self.started) * 1e6)
        self.process.stdin.write(f'{now} {value}\n')
        self.process.stdin.flush()
        while True:
            try:
                line = self.lines.get(timeout=.2)
            except queue.Empty as error:
                self.process.kill()
                raise ConnectionError('MCU host response timed out') from error
            if not line:
                raise ConnectionError('MCU host stopped')
            if line == '.':
                break
            self.pending.extend(bytes.fromhex(line))

    def write(self, data):
        self.exchange(data.hex())
        return len(data)

    def read(self, size=4096):
        self.exchange('tick')
        result = bytes(self.pending[:size])
        del self.pending[:size]
        return result

    def close(self):
        self.process.stdin.close()
        try:
            self.process.wait(timeout=2)
        except subprocess.TimeoutExpired:
            self.process.kill()
            self.process.wait()
        self.process.stdout.close()
        self.reader.join(timeout=.5)


class Runtime:
    def __init__(self, transport, bind, peer, *, simulated=False, odom_bind=None, replay=False):
        self.transport = transport
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind(bind)
        self.socket.setblocking(False)
        self.peer = (socket.gethostbyname(peer[0]), peer[1])
        self.pc_codec, self.serial_codec = Codec(), Codec()
        self.bridge = Bridge(self.send_pc, self.send_mcu, simulated=simulated or replay)
        self.odom_socket = None
        if odom_bind:
            self.odom_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.odom_socket.bind(odom_bind)
            self.odom_socket.setblocking(False)
        self.replay = replay
        self.seq = 0
        self.last_odom = self.last_heartbeat = -math.inf
        self.bridge.invalidate()  # Revoke any previous process's execution session.

    def send_pc(self, kind, **data):
        self.socket.sendto(self.pc_codec.encode(kind, **data), self.peer)

    def send_mcu(self, kind, **data):
        packet = self.serial_codec.encode(kind, **data)
        if self.transport.write(packet) != len(packet):
            raise ConnectionError('Short UART write')

    def step(self):
        now = time.monotonic()
        for m in self.serial_codec.decode(self.transport.read(4096)):
            self.bridge.receive_mcu(m, now)
        for _ in range(64):
            try:
                packet, address = self.socket.recvfrom(4096)
            except BlockingIOError:
                break
            if address == self.peer:
                for m in self.pc_codec.decode(packet):
                    self.bridge.receive_pc(m, now)
        if self.odom_socket:
            for _ in range(64):
                try:
                    packet, _ = self.odom_socket.recvfrom(4096)
                except BlockingIOError:
                    break
                try:
                    self.bridge.receive_odometry(json.loads(packet), now)
                except (ValueError, TypeError, KeyError, UnicodeError):
                    logging.warning('Rejected odometry sample', exc_info=True)
        if self.replay and now - self.last_odom >= .02:
            self.seq = (self.seq + 1) & 0xffffffff
            # Static fixture, deliberately not an inferred physical position.
            self.bridge.receive_odometry(dict(source_us=int(now*1e6), sample_seq=self.seq,
                reset_id=0, x=0., y=0., yaw=0., vx=0., vy=0., yaw_rate=0.,
                depth=.5, valid=1, depth_valid=1), now)
            self.last_odom = now
        self.bridge.tick(now)
        if now - self.last_heartbeat >= 1:
            self.send_pc('HEARTBEAT', type=12, autopilot=8, base_mode=0,
                         custom_mode=self.bridge.mode, system_status=4, mavlink_version=3)
            self.last_heartbeat = now

    def close(self):
        try:
            self.bridge.invalidate()
        finally:
            self.socket.close()
            if self.odom_socket:
                self.odom_socket.close()
            self.transport.close()


def main():
    parser = argparse.ArgumentParser(description='FinsROV fixed-protocol NX bridge')
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument('--serial', help='Physical UART, e.g. /dev/ttyTHS1')
    mode.add_argument('--mcu-host', type=Path, help='SIMULATED actuator C++ harness executable')
    parser.add_argument('--baud', type=int, default=460800)
    parser.add_argument('--bind', default='127.0.0.1')
    parser.add_argument('--pc', default='127.0.0.1')
    parser.add_argument('--port', type=int, default=54322)
    parser.add_argument('--pc-port', type=int, default=54321)
    parser.add_argument('--odom-port', type=int, default=54323)
    parser.add_argument('--replay', action='store_true', help='SIMULATED static odometry fixture')
    args = parser.parse_args()
    if args.serial and args.replay:
        parser.error('Replay is restricted to nonphysical --mcu-host operation')
    if args.mcu_host:
        transport = HostMCU(args.mcu_host)
    else:
        import serial
        # Exclusive access on Linux; errors fail closed and systemd restarts fresh.
        transport = serial.Serial(args.serial, args.baud, timeout=0, write_timeout=.02, exclusive=True)
    runner = None
    try:
        runner = Runtime(transport, (args.bind,args.port), (args.pc,args.pc_port),
            simulated=bool(args.mcu_host), replay=args.replay, odom_bind=('127.0.0.1',args.odom_port))
        logging.warning('%s running', 'SIMULATED NX/MCU' if args.mcu_host else 'Physical NX bridge')
        while True:
            runner.step()
            time.sleep(.002)
    except KeyboardInterrupt:
        pass
    finally:
        if runner:
            runner.close()
        else:
            transport.close()


if __name__ == '__main__':
    main()
