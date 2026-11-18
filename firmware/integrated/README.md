# Optional experimental MCU integration overlay

This is **not the default reproduction firmware**. Use [SUB](../SUB/) with the [default Jetson joystick bridge](../../software/jetson/README.md) and the original SUB joystick PC application. The default selection does not change the Git branch or any firmware source behavior.

Derived MPL-2.0 integration overlay for the inertial-odometry snapshot `d2fbd78d23361b05f18b15ae8768a1a8b621330c`. It reuses the original BSP, framework and pinned dependencies without modifying either legacy snapshot. The new CMake entry selects RoboMaster A and replaces the legacy task/controller path.

[Build, protocol, deployment and verification](../../docs/software/pc-nx-mcu.zh-CN.md)

The same `Services/Endpoint.hpp` runs on the board and in the host harness. In **this experimental overlay**, physical depth capability defaults off pending calibration and unsupported auxiliary actions are not advertised. These restrictions do not apply to the existing SUB attitude/depth/light assistance. No hardware has been flashed or operated in this change; previous host-loop and build results remain available in the guide.
