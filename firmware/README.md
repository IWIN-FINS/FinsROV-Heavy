# Embedded firmware

[简体中文](README.zh-CN.md) · [Project home](../README.md)

Both variants use FineSUB and target the RoboMaster Type A board with an STM32F427.

| Directory | FineSUB branch | Use | Source commit |
| --- | --- | --- | --- |
| [SUB](SUB/) | SUB | Normal vehicle operation, attitude/depth control and light control | aebf944b803303c2d26dd1476c9a3496fb3a9a91 |
| [inertial-odometry](inertial-odometry/) | 惯性里程计实验 | Inertial odometry experiments with IMU, depth, eight thruster RPM/throttle channels, battery voltage and timestamp telemetry | d2fbd78d23361b05f18b15ae8768a1a8b621330c |

These snapshots were exported on 2026-11-11 from the local FineSUB branch heads, which matched their local remote-tracking refs. They include each branch's source tree, board support packages and framework documentation. IDE-specific `.idea/` files were omitted, and dependency declarations were relocated to the repository's root `.gitmodules`. Git handles text line endings through the inherited attributes. Source history is available upstream. [FineSUB upstream](https://gitee.com/gan-ju/FineSUB)

## Get the source and dependencies

~~~powershell
git clone --recurse-submodules https://github.com/IWIN-FINS/FinsROV-Heavy.git
cd FinsROV-Heavy
~~~

For an existing Git checkout, run this command at the repository root.

~~~powershell
git submodule update --init --recursive
~~~

Use the recursive Git checkout to obtain the dependency sources. Each variant pins the same two upstream commits.

| Dependency | Commit |
| --- | --- |
| CMSIS-DSP | 4ee6da97c239071283d869de7c636d7621280e7c |
| ETL | a12dbbd91174e895bdd5492826b0226b9668fc5f |

## Build on Windows

Install CMake 3.21 or later, Ninja and Arm Compiler 6 through Keil MDK. Add the directories containing `cmake.exe`, `ninja.exe`, `armclang.exe`, `armlink.exe` and `fromelf.exe` to `PATH`. Use an ASCII checkout and build path without spaces, for example `C:/src/FinsROV-Heavy`. The original linker configuration failed on the Chinese/space-containing source path used during validation.

Run the commands for your selected variant from the repository root.

~~~powershell
# Normal vehicle operation
cmake -S firmware/SUB -B build/SUB -G Ninja
cmake --build build/SUB --target Robomaster_A --parallel

# Inertial odometry experiments
cmake -S firmware/inertial-odometry -B build/inertial-odometry -G Ninja
cmake --build build/inertial-odometry --target Robomaster_A --parallel
~~~

Each build produces `bin/Robomaster_A.elf` and `bin/Robomaster_A.hex` in its build directory. On 2026-11-11, both variants compiled and linked with Arm Compiler 6.24, CMake and Ninja, using ASCII source/build paths. Hardware flashing and on-water validation remain to be performed for the exported snapshots.

The inherited MDK project is at `BSP/Robomaster_A/MDK-ARM/Robomaster_A.uvprojx` within each variant. The verified build entry point is CMake with target `Robomaster_A`.

## Match the host protocol

| Setting | SUB | Inertial odometry |
| --- | --- | --- |
| Host connection | USART3, 115200 baud | USART3, 460800 baud |
| Host-to-board frame | 28 bytes | 52 bytes |
| Board-to-host telemetry | 64 bytes | 100 bytes |
| IMU connection | UART7, 921600 baud | UART7, 921600 baud, DMA receive |
| Pressure sensors | UART8, 115200 baud, addresses 0x01–0x04 | UART8, 115200 baud, addresses 0x01–0x04 |

The host frame begins with `0xAA` and ends with a two-byte CRC, low byte first. Use `Services/V5Streamer/Streamer.hpp` and `Algorithms/Verification/CRC.cpp` in the selected variant for the payload and CRC implementation. Telemetry fields and packing are defined by `UploadData` in `Components/SUB/V5_SUB.hpp`.

In the experiment snapshot, `TaskTest()` forwards normalized host commands to the vehicle controller. Keep `enablePathTracking` at zero as documented in that source. The trajectory classes are present but are not invoked by the current task entry point. The experimental depth target is initialized to `-0.1f`, and the depth-target update body is commented out. Review the recorded pressure offsets and control parameters in `V5_SUB.hpp` for your vehicle.

The [Jetson SUB control and video scripts](../software/jetson/README.md) are now included, with a [setup tutorial](../docs/build/06-jetson.zh-CN.md). They do not implement the inertial-odometry host protocol.

## Source entry points

Paths below are relative to either variant.

| Path | Purpose |
| --- | --- |
| `Interface/Examples/TaskSUB.cpp` | Device instances, thruster channels, PID parameters and control task |
| `Components/SUB/V5_SUB.hpp` | Vehicle controller, pressure offsets and telemetry layout |
| `Services/V5Streamer/Streamer.hpp` | Host command decoding |
| `Devices/IMU/H30_IMU.hpp` | H30 IMU decoding |
| `BSP/Robomaster_A/` | Peripheral configuration, board mappings and project files |
| `OpenOCD/` | ST-Link and DAP-Link configurations |
| `Docs/` | Inherited FineSUB framework documentation |

## License

The FineSUB source in each variant is distributed under its included MPL-2.0 license. Bundled and submodule dependencies carry their own license notices. [SUB license](SUB/LICENSE) · [Experiment license](inertial-odometry/LICENSE)
