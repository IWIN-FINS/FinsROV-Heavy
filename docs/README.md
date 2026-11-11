# Build FinsROV-Heavy

[Project home](../README.md) · [简体中文](README.zh-CN.md)

These guides follow the build from fabricated parts to the first bench checks. The detailed instructions and original build photographs are currently in Chinese. They were reorganized from the team's V5 build notes exported on 2026-11-11.

| Step | Guide | What it covers |
| --- | --- | --- |
| 1 | [Parts and revision selection](build/01-overview.zh-CN.md) | BOMs, machining files, purchased kits and current versus historical configurations |
| 2 | [Frame assembly](build/02-frame.zh-CN.md) | Frame fasteners, battery slide, buoyancy inserts, thrusters and ballast |
| 3 | [Power board assembly](build/03-power-board.zh-CN.md) | Interactive BOM, soldering order and the unresolved R12 revision discrepancy |
| 4 | [Thrusters and ESC wiring](build/04-thrusters.zh-CN.md) | Physical motor numbers, ESC pads, controller channels and direction checks |
| 5 | [Pressure sensor setup](build/05-pressure-sensors.zh-CN.md) | RS-485 addresses, baud rate, units and readback |
| 6 | [Jetson setup](build/06-jetson.zh-CN.md) | Ethernet, UART, SUB control bridge, video and systemd startup |
| 7 | [Bring-up checklist](build/07-bring-up.zh-CN.md) | Stage-by-stage checks and the remaining gaps before a complete build tutorial |

The supplied [Jetson scripts](../software/jetson/README.md) target **SUB normal operation**: 115200 baud and 28-byte commands. The inertial-odometry firmware uses a different protocol and needs its own host software. The Windows controller application is not included in this release.

[Hardware downloads](../README.md#hardware-files) · [Firmware guide](../firmware/README.md) · [Original attachments](reference/README.md) · [Sources and changes](SOURCES.md)

The original notes include early design targets and unfinished steps. Those are identified in the guides, not presented as measured vehicle capabilities. The new scripts have been checked offline; a complete hardware, sealing and underwater validation procedure is still to be supplied.
