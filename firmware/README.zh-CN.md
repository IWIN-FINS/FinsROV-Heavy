# 嵌入式固件

[English](README.md) · [项目首页](../README.zh-CN.md)

两套工程均基于 FineSUB，目标为搭载 STM32F427 的 RoboMaster A 型开发板。

| 目录 | FineSUB 分支 | 用途 | 源提交 |
| --- | --- | --- | --- |
| [SUB](SUB/) | SUB | 正常机器人操控、姿态与深度控制、灯光控制 | aebf944b803303c2d26dd1476c9a3496fb3a9a91 |
| [inertial-odometry](inertial-odometry/) | 惯性里程计实验 | 惯性里程计实验，输出 IMU、深度、8 路推进器转速与油门、电池电压及时间戳 | d2fbd78d23361b05f18b15ae8768a1a8b621330c |

两份快照于 2026-11-11 从本地 FineSUB 对应分支头导出，与当时本地远端跟踪引用一致。快照包含各分支的源码树、板级支持和框架文档。整理时省略了 `.idea/` 编辑器配置，依赖声明移到仓库根目录的 `.gitmodules`，文本换行由原有 Git 属性处理。完整提交历史可在上游仓库查看。[FineSUB 上游](https://gitee.com/gan-ju/FineSUB)

## 获取源码与依赖

~~~powershell
git clone --recurse-submodules https://github.com/IWIN-FINS/FinsROV-Heavy.git
cd FinsROV-Heavy
~~~

已有 Git 工作副本时，在仓库根目录执行以下命令。

~~~powershell
git submodule update --init --recursive
~~~

使用带子模块的 Git 克隆获取依赖源码。两套固件分别固定以下相同版本。

| 依赖 | 提交 |
| --- | --- |
| CMSIS-DSP | 4ee6da97c239071283d869de7c636d7621280e7c |
| ETL | a12dbbd91174e895bdd5492826b0226b9668fc5f |

## Windows 编译

安装 CMake 3.21 或更高版本、Ninja，以及 Keil MDK 中的 Arm Compiler 6。将 `cmake.exe`、`ninja.exe`、`armclang.exe`、`armlink.exe` 和 `fromelf.exe` 所在目录加入 `PATH`。源码和构建目录采用无空格的纯英文路径，例如 `C:/src/FinsROV-Heavy`。此次验证中，原工程链接配置在含中文和空格的源码路径下报错。

在仓库根目录执行所选版本的命令。

~~~powershell
# 正常机器人操控
cmake -S firmware/SUB -B build/SUB -G Ninja
cmake --build build/SUB --target Robomaster_A --parallel

# 惯性里程计实验
cmake -S firmware/inertial-odometry -B build/inertial-odometry -G Ninja
cmake --build build/inertial-odometry --target Robomaster_A --parallel
~~~

输出位于对应构建目录的 `bin/Robomaster_A.elf` 和 `bin/Robomaster_A.hex`。2026-11-11 已在纯英文源码与构建路径下，用 Arm Compiler 6.24、CMake 和 Ninja 完成两套固件的编译及链接验证。导出快照的烧录和实机下水验证尚待执行。

原有 MDK 工程位于各版本的 `BSP/Robomaster_A/MDK-ARM/Robomaster_A.uvprojx`。此次已验证的构建入口为 CMake 的 `Robomaster_A` 目标。

## 上位机协议匹配

| 配置 | SUB | 惯性里程计实验 |
| --- | --- | --- |
| 上位机串口 | USART3，115200 波特率 | USART3，460800 波特率 |
| 上位机下发帧 | 28 字节 | 52 字节 |
| 单片机遥测帧 | 64 字节 | 100 字节 |
| IMU 接口 | UART7，921600 波特率 | UART7，921600 波特率，DMA 接收 |
| 水压计接口 | UART8，115200 波特率，地址 0x01–0x04 | UART8，115200 波特率，地址 0x01–0x04 |

下发帧以 `0xAA` 开头，末尾为低字节在前的两字节 CRC。载荷和 CRC 实现见所选版本的 `Services/V5Streamer/Streamer.hpp` 与 `Algorithms/Verification/CRC.cpp`。遥测字段和打包方式见 `Components/SUB/V5_SUB.hpp` 中的 `UploadData`。

实验快照的 `TaskTest()` 将归一化上位机指令传给机器人控制器。按源码说明将 `enablePathTracking` 设为零，当前任务入口未调用文件中保留的轨迹跟踪类。实验版目标深度初值为 `-0.1f`，更新目标深度的函数体已注释。复现时需对照实机核对 `V5_SUB.hpp` 中记录的压力零偏和控制参数。

配套 SUB 的 [Jetson 控制转发与视频脚本](../software/jetson/README.md) 已提供，[配置教程](../docs/build/06-jetson.zh-CN.md) 包含网络、串口和开机自启。该脚本不适用于惯性里程计实验协议。

## 源码入口

下表路径相对于所选固件目录。

| 路径 | 用途 |
| --- | --- |
| `Interface/Examples/TaskSUB.cpp` | 设备实例、电机通道、PID 参数与操控任务 |
| `Components/SUB/V5_SUB.hpp` | 机器人控制器、压力零偏与遥测定义 |
| `Services/V5Streamer/Streamer.hpp` | 上位机指令解码 |
| `Devices/IMU/H30_IMU.hpp` | H30 IMU 解码 |
| `BSP/Robomaster_A/` | 外设配置、板级映射与工程文件 |
| `OpenOCD/` | ST-Link 和 DAP-Link 配置 |
| `Docs/` | 原有 FineSUB 框架文档 |

## 许可证

两套 FineSUB 源码按各自目录内的 MPL-2.0 许可证发布，随附依赖和子模块适用其各自许可证。[SUB 许可证](SUB/LICENSE) · [实验版许可证](inertial-odometry/LICENSE)
