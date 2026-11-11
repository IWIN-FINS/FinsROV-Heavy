# Jetson host scripts

[Project home](../../README.md) · [完整配置教程（中文）](../../docs/build/06-jetson.zh-CN.md)

These scripts come from the V5 build notes. The control bridge supports the **SUB** firmware snapshot in this repository. It does **not** implement the inertial-odometry protocol.

| File | Role |
| --- | --- |
| [V5StreamerNX.py](V5StreamerNX.py) | Joystick UDP → SUB UART commands; raw UART chunks → PC UDP |
| [GStreamerTest.py](GStreamerTest.py) | USB camera → H.264/RTP over UDP |
| [StreamerStart.sh](StreamerStart.sh) | Supervise both Python processes; stop its own children on exit |
| [streamer.service](streamer.service) | Optional systemd template; edit the user, paths and Python interpreter |

## Defaults

| Connection | Default |
| --- | --- |
| Jetson / PC | 192.168.0.2 / 192.168.0.1, subnet mask 255.255.255.0 |
| Joystick input on Jetson | UDP 12345, 41-byte little-endian `<6f15B2b` |
| Controller UART | `/dev/ttyTHS1`, 115200, 8N1, no flow control |
| Command frame | `0xAA` + 25-byte `<5f3B2b` payload + CRC16/MODBUS low byte first; total 28 bytes |
| Telemetry destination | PC UDP 54321; forwarded serial chunks, **not** complete-frame datagrams |
| Video | `/dev/video0`, MJPEG, 1280×480 at 30 fps, H.264 4 Mbit/s, RTP payload 96, PC UDP 5600 |

Install `python3-serial` and the GStreamer plugins described in the tutorial. The Python package is **pyserial**, not a package named `serial`. For Orin NX the video default uses NVENC; for **Orin Nano set `USE_NVENC = False`**, since that module has no NVENC engine. Check the camera's supported format and modes before retaining the defaults. [NVIDIA Orin Nano encoding documentation](https://docs.nvidia.com/jetson/archives/r36.4.3/DeveloperGuide/SD/Multimedia/SoftwareEncodeInOrinNano.html)

The Windows joystick application is not included. A compatible sender must provide the documented 41-byte structure. The receiver must reassemble and check telemetry frames: the bridge neither preserves frame boundaries nor recovers lost UDP packets. This is the behavior inherited from the supplied scripts.

## Publication fixes

- Made packet byte order explicit; preserved field order, axis mapping, ports and baud rate.
- Made a serial-open failure exit unsuccessfully; added SIGTERM cleanup and fixed the receive counter.
- Fixed the missing separator in the raw-video pipeline and removed NVMM buffers from the CPU encoder path. `jpegdec` is software decoding; the NX default accelerates H.264 encoding.
- Corrected subprocess timeout handling, scoped process cleanup to spawned processes and made unexpected video exits visible to systemd.
- Replaced the machine-specific Conda path, device-wide `chmod 777` and broad `pkill -f` launcher with a configurable interpreter and tracked child processes.
- Rebuilt the malformed systemd example as a separate unit file. No automatic installation is performed.

Source file hashes and the published file hashes are recorded in [the import manifest](../../docs/source-manifest.json). Offline checks cover command-frame serialization, CRC, all four video pipeline combinations and process cleanup. The revised scripts still require testing on the actual camera, Jetson, controller and Windows application.

Run offline checks from this directory with `python -m unittest discover -s tests -v`. They do not open a serial port, send joystick commands or launch a real GStreamer pipeline.
