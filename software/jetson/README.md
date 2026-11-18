# Jetson host scripts

[Project home](../../README.md) · [完整配置教程（中文）](../../docs/build/06-jetson.zh-CN.md)

These V5 scripts are the **default Jetson deployment for joystick control**. Use `firmware/SUB`, `V5StreamerNX.py` and the original SUB joystick PC application together. The bridge receives the original joystick packet and converts it to the SUB UART protocol; it does not provide trajectory control or online inertial-odometry inference.

SUB's existing attitude, depth and light assistance remain in the firmware. The experimental MAVLink bridge has different capabilities and restrictions; those do not describe the default SUB implementation.

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

The **original SUB Windows joystick application** is not included. Its releasable source/package, matching version, dependencies, launch command and device configuration still need to be supplied. A compatible sender must provide the documented 41-byte structure; the new MAVLink-only NXTelemetryMonitor application cannot connect to this bridge directly. The receiver must reassemble and check telemetry frames: the bridge neither preserves frame boundaries nor recovers lost UDP packets. This is the behavior inherited from the supplied scripts.

Use `StreamerStart.sh` for the default bridge and video pair, or configure `streamer.service` with the actual user, checkout path and Python interpreter. The separate `deploy/fins-bridge.service` and `deploy/fins-video.service` templates belong to the optional MAVLink experiment; do not enable them for this default configuration.

## Publication fixes

- Made packet byte order explicit; preserved field order, axis mapping, ports and baud rate.
- Made a serial-open failure exit unsuccessfully; added SIGTERM cleanup and fixed the receive counter.
- Fixed the missing separator in the raw-video pipeline and removed NVMM buffers from the CPU encoder path. `jpegdec` is software decoding; the NX default accelerates H.264 encoding.
- Corrected subprocess timeout handling, scoped process cleanup to spawned processes and made unexpected video exits visible to systemd.
- Replaced the machine-specific Conda path, device-wide `chmod 777` and broad `pkill -f` launcher with a configurable interpreter and tracked child processes.
- Rebuilt the malformed systemd example as a separate unit file. No automatic installation is performed.

Source file hashes and the published file hashes are recorded in [the import manifest](../../docs/source-manifest.json). Offline checks cover command-frame serialization, CRC, all four video pipeline combinations and process cleanup. The revised scripts still require testing on the actual camera, Jetson, controller and Windows application.

Run the default SUB offline checks from this directory with `python -m unittest discover -s tests -p test_offline.py -v`. They do not require the experimental C++ harness, open a serial port, send joystick commands or launch a real GStreamer pipeline.

## Optional integration experiment

The [PC–NX–MCU integration development version](../../docs/software/pc-nx-mcu.zh-CN.md) retains a fixed-PC MAVLink bridge, MCU overlay and C++ execution harness for future development. It is not the default deployment. Its physical depth capability is disabled until calibration; auxiliary actions and real V24 inference remain outstanding. These are restrictions of the experimental integration only. The inertial-odometry firmware snapshot is also optional and requires its own matching host protocol.
