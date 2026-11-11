"""Offline checks: no serial/network devices or real GStreamer processes."""
import ast
import importlib.util
from pathlib import Path
import signal
import struct
import subprocess
import unittest
from unittest.mock import Mock, patch

ROOT = Path(__file__).resolve().parents[1]


def load_control_functions():
    # The inherited bridge opens hardware at top level. Extract only its pure
    # protocol helpers and serializer; never import/execute the live bridge.
    tree = ast.parse((ROOT / "V5StreamerNX.py").read_text(encoding="utf-8"))
    names = {"JoystickState", "crc16_modbus", "normalize_value", "forward_to_serial"}
    module = ast.Module(body=[n for n in tree.body
                             if isinstance(n, (ast.ClassDef, ast.FunctionDef))
                             and n.name in names], type_ignores=[])
    ns = {"struct": struct, "serial_send_count": 0,
          "ser": Mock(is_open=True)}
    exec(compile(module, "protocol-only", "exec"), ns)
    return ns


spec = importlib.util.spec_from_file_location("video_under_test", ROOT / "GStreamerTest.py")
video = importlib.util.module_from_spec(spec)
spec.loader.exec_module(video)


class ControlProtocolTests(unittest.TestCase):
    def setUp(self):
        self.ns = load_control_functions()

    def test_crc_standard_vector(self):
        self.assertEqual(self.ns["crc16_modbus"](b"123456789"), 0x4B37)

    def test_joystick_to_sub_frame(self):
        buttons = [0] * 15
        buttons[0] = buttons[6] = 1
        wire = struct.pack("<6f15B2b", 0.25, 0, -0.5, 0.75, -1, 1,
                           *buttons, -1, 1)
        self.assertEqual(len(wire), 41)
        state = self.ns["JoystickState"]()
        state.from_bytes(wire)
        ok, payload = self.ns["forward_to_serial"](state)
        self.assertTrue(ok)
        expected = struct.pack("<5f3B2b", -0.25, -0.75, 0.5, 0, 1, 1, 1, 0, -1, 1)
        self.assertEqual(payload, expected)
        frame = self.ns["ser"].write.call_args.args[0]
        self.assertEqual(len(frame), 28)
        self.assertEqual(frame[:26], b"\xaa" + expected)
        # Residue of a complete Modbus frame is zero, including the low-byte-first CRC.
        self.assertEqual(self.ns["crc16_modbus"](frame), 0)
        self.assertEqual(self.ns["serial_send_count"], 1)

    def test_trigger_range_and_closed_serial(self):
        self.assertEqual(self.ns["normalize_value"](-2), 0)
        self.assertEqual(self.ns["normalize_value"](0), 0.5)
        self.assertEqual(self.ns["normalize_value"](2), 1)
        self.ns["ser"].is_open = False
        self.assertEqual(self.ns["forward_to_serial"](self.ns["JoystickState"]()), (False, None))
        self.ns["ser"].write.assert_not_called()


class VideoTests(unittest.TestCase):
    def test_all_capture_encoder_combinations(self):
        for mode in ("raw", "mjpeg"):
            for nvenc in (False, True):
                with self.subTest(mode=mode, nvenc=nvenc), \
                     patch.object(video, "CAMERA_MODE", mode), \
                     patch.object(video, "USE_NVENC", nvenc):
                    cmd = video.build_gst_cmd("192.168.0.1")
                    self.assertEqual(cmd[:2], ["gst-launch-1.0", "-e"])
                    self.assertIn("host=192.168.0.1", cmd)
                    self.assertIn("port=5600", cmd)
                    self.assertIn("pt=96", cmd)
                    self.assertEqual("jpegdec" in cmd, mode == "mjpeg")
                    self.assertEqual("nvv4l2h264enc" in cmd, nvenc)
                    self.assertEqual("x264enc" in cmd, not nvenc)
                    self.assertEqual("NVMM" in " ".join(cmd), nvenc)
                    self.assertEqual("nvvidconv" in cmd, nvenc)
                    encoder = "nvv4l2h264enc" if nvenc else "x264enc"
                    self.assertEqual(cmd[cmd.index(encoder) - 1], "!")
                    self.assertIn("bitrate=4000000" if nvenc else "bitrate=4000", cmd)
                    self.assertNotIn("! !", " ".join(cmd))

    def test_invalid_configuration(self):
        with self.assertRaises(ValueError):
            video.build_gst_cmd("")
        with patch.object(video, "CAMERA_MODE", "unsupported"), self.assertRaises(ValueError):
            video.build_gst_cmd("192.168.0.1")

    def test_timeout_kills_only_owned_process_group(self):
        streamer = video.VideoStreamer("192.168.0.1")
        proc = Mock(pid=43210)
        proc.wait.side_effect = [subprocess.TimeoutExpired("gst", 5), 0]
        streamer.video_proc = proc
        with patch.object(video.os, "getpgid", return_value=43210, create=True), \
             patch.object(video.os, "killpg", create=True) as killpg, \
             patch.object(video.signal, "SIGKILL", 9, create=True):
            streamer.stop()
        self.assertEqual(killpg.call_args_list[0].args, (43210, signal.SIGTERM))
        self.assertEqual(killpg.call_args_list[1].args, (43210, 9))
        self.assertEqual(proc.wait.call_count, 2)
        self.assertIsNone(streamer.video_proc)


if __name__ == "__main__":
    unittest.main()
