# Integrated MCU overlay

Derived MPL-2.0 integration overlay for the inertial-odometry snapshot `d2fbd78d23361b05f18b15ae8768a1a8b621330c`. It reuses the original BSP, framework and pinned dependencies without modifying either legacy snapshot. The new CMake entry selects RoboMaster A and replaces the legacy task/controller path.

[Build, protocol, deployment and verification](../../docs/software/pc-nx-mcu.zh-CN.md)

The same `Services/Endpoint.hpp` runs on the board and in the host harness. Physical depth capability defaults off pending calibration. Unsupported auxiliary actions are not advertised. No hardware has been flashed or operated in this change.
