# Build FinsROV-Heavy

[Project home](../README.md) · [简体中文](README.zh-CN.md)

These guides follow the build from fabricated parts to the first bench checks. The detailed instructions and original build photographs are currently in Chinese. They were reorganized from the team's V5 build notes exported on 2026-11-11. Manufacturing, enclosure assembly and sealing records were added on 2026-11-18. Original chapter numbers are retained; follow the reading order below.

| Step | Guide | What it covers |
| --- | --- | --- |
| 1 | [Parts and revision selection](build/01-overview.zh-CN.md) | BOMs, machining files, purchased kits and current versus historical configurations |
| 2 | [Frame assembly](build/02-frame.zh-CN.md) | Frame fasteners, battery slide, buoyancy inserts, thrusters and ballast |
| 3 | [Power board assembly](build/03-power-board.zh-CN.md) | Final-design R12 removal, historical BOM reference and soldering order |
| 4 | [Thrusters and ESC wiring](build/04-thrusters.zh-CN.md) | Physical motor numbers, ESC pads, controller channels and direction checks |
| 5 | [Pressure sensor setup](build/05-pressure-sensors.zh-CN.md) | RS-485 addresses, baud rate, units and readback |
| 8 | [Enclosure assembly and cable routing](build/08-enclosure-assembly.zh-CN.md) | Match boards and supports, trial-fit the stack and document cable routes |
| 6 | [Jetson setup](build/06-jetson.zh-CN.md) | Ethernet, UART, SUB control bridge, video and systemd startup |
| 7 | [Bring-up checklist](build/07-bring-up.zh-CN.md) | Stage-by-stage checks and the remaining gaps before a complete build tutorial |
| 9 | [Sealing, leak checks and trim records](build/09-sealing-trim.zh-CN.md) | Required component evidence and test records; not a hardware-validated procedure |

The default is **SUB with joystick control**, using the original [Jetson scripts](../software/jetson/README.md): 115200 baud and 28-byte MCU commands. The matching legacy PC sender still needs to be supplied. The inertial-odometry firmware uses a different protocol. The [Windows multimode ground station, pinned at `5ebe00e`](https://github.com/ganju2390/NXTelemetryMonitor/tree/5ebe00e2573c8df5b5ad376915fab2da0644c188), belongs to the optional MAVLink integration configuration and cannot connect directly to the default bridge.

[Manufacturing revision checklist](../hardware/mechanical/manufacturing-release.zh-CN.md) · [Build record template](../hardware/mechanical/build-record.zh-CN.md)

[Remaining work and acceptance criteria](development/remaining-work.zh-CN.md) · [PC–NX–MCU integration and limitations](software/pc-nx-mcu.zh-CN.md)

[Hardware downloads](../README.md#hardware-files) · [Firmware guide](../firmware/README.md) · [Original attachments](reference/README.md) · [Sources and changes](SOURCES.md)

The [electrical wiring package](../hardware/electrical/README.md) includes battery wiring, equipment enclosure connector locations and pin definitions, connector/harness tables and the supplied CAN protocol. It distinguishes confirmed signals from unresolved internal connections and physical connector pin views.

The original notes include early design targets and unfinished steps. Those are identified in the guides, not presented as measured vehicle capabilities. The new scripts have been checked offline; a complete hardware, sealing and underwater validation procedure is still to be supplied.
