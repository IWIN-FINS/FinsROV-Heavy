# PC—NX—MCU 集成开发版（可选实验）

**本页不是当前默认复刻流程。** 默认使用 [SUB 固件](../../firmware/README.zh-CN.md)、[SUB Jetson 转发](../../software/jetson/README.md)和原 SUB 手柄上位机，按 [Jetson 教程](../build/06-jetson.zh-CN.md)部署。默认控制入口仅为手柄，保留 SUB 原有姿态、深度和灯光辅助；原 SUB Windows 程序和可复现启动配置仍待补齐。本页保留新 MAVLink 方案的实现、验证和后续实验资料，不改变固件行为或仓库 Git 默认分支。

固定兼容 NXTelemetryMonitor `5ebe00e2573c8df5b5ad376915fab2da0644c188`。PC 负责输入映射、轨迹规划和水平闭环，NX 管理通信及外部定位输入，MCU 负责实际执行和超时停止。原 SUB 与实验版快照没有修改。

**本实验版本已交付可构建固件、NX 桥接及本地三端闭环；真实机器人验收、V24 推理接入仍待完成。** 仅本集成固件的物理定深能力默认关闭，固定 MAVLink PC 因而阻止其物理轨迹启动；模拟 C++ 端点明确声明为模拟运行。这一限制不描述默认 SUB 固件。

## 入口与本地验证

- [固定 PC 版本](https://github.com/ganju2390/NXTelemetryMonitor/tree/5ebe00e2573c8df5b5ad376915fab2da0644c188)、[协议文件与校验](../../protocol/provenance.json)。消息 ID、字段、单位未改动。
- [NX 程序](../../software/jetson/fins_bridge/)、[集成固件覆盖层](../../firmware/integrated/)、[测试入口](../../software/jetson/tests/test_integration.py)。

桥接自身使用 Python 3.10+。下列固定 PC 集成测试应使用该 PC 仓库的锁定 Python 3.12 虚拟环境（其项目要求 >=3.12,<3.13），并安装 PC 锁定依赖。将该环境 Python 和 C++17 编译器加入 PATH，在平台仓库根目录执行：

```powershell
New-Item -ItemType Directory -Force build/integration
g++ -std=c++17 -O2 -Wno-address-of-packed-member -Iprotocol/generated/c -Ifirmware/integrated/Services firmware/integrated/tests/endpoint_host.cpp -o build/integration/endpoint_host.exe
$env:FINS_ENDPOINT_HOST = (Resolve-Path build/integration/endpoint_host.exe).Path
$env:FINS_PC_ROOT = 'D:\FINS\NXTelemetryMonitor'
python -m unittest discover -s software/jetson/tests -v
cd software/jetson
python -m fins_bridge --mcu-host ../../build/integration/endpoint_host.exe --replay
```

Linux 可省略 `.exe`，并设置 `FINS_ENDPOINT_HOST` 指向实际文件。固定 PC 使用 `python -m groundstation --nx 127.0.0.1`，不要再开 PC 的 `--simulate` 占用同一端口。可运行手动→启用→轨迹→停止→手动。`--replay` 是静态有效位置夹具，不代表水动力或轨迹精度；不能与真实串口同时启用。缺 `FINS_PC_ROOT` 会明确跳过固定 PC 集成测试，不能称为全项通过；缺 C++ 端点则报错。

## 可选集成固件

先初始化原有子模块，将 Arm Compiler 6.24、CMake、Ninja 加入 PATH，在无空格路径执行：

```powershell
git submodule update --init --recursive
cmake -S firmware/integrated -B build/integrated -G Ninja
cmake --build build/integrated --target Robomaster_A --parallel
```

输出 `build/integrated/bin/Robomaster_A.elf`、`.hex`。工程复用实验版 BSP/框架及其固定 ETL/CMSIS-DSP，排除旧 TaskSUB，编入新任务与控制器。`FINS_DEPENDENCY_ROOT` 可指向提交已核验的本地依赖；未修改 `.gitmodules`。UART3 为 **460800、8N1**，旧协议不能接入新固件。

- MCU 硬件 RNG 生成启动会话，失败时不接受控制。RX ISR 只写有界环形缓冲；任务内解析执行，TX 使用固定 DMA 帧缓冲。缓冲溢出停止。
- 启停为绝对状态，请求去重；成功 ACK 来自 MCU 控制层应用结果，不代表机械动作实测通过。停用不受在途模式代次阻挡。过期后 IDLE、撤销定深并停用电机，新设定值不能自动恢复。
- 模式、代次或激活状态变化重新捕获航向，清除 PID 积分；没有当前有效设定值时输出为零。继承前向/横向 `0.35` 缩放，偏航按实际步长积分 `0.4 rad/s`，手动垂向 `0.35`，这些参数仍需池试。
- 启用及保持运动要求 H30 完整有效帧年龄小于 100 ms、四压力计有效 CRC/数值帧年龄小于 500 ms。H30 同帧须有加速度、角速度、四元数；先检查帧边界再调用旧解码器。实机需核对输出配置及压力更新周期。
- **仅集成版定深默认关闭**。本覆盖层深度为四只绝对压力均值减共同零点、除以 `9806.65`，向下为正，在覆盖层内替代旧两传感器及固定偏置计算，原 SUB 和实验快照未改。确认各传感器校准和 NX/MCU 零点、安装高度一致后，才用 `-DFINS_DEPTH_CALIBRATED=ON -DFINS_DEPTH_DATUM_PA=<确认的Pa数值>` 构建。默认 `101325.0f` 来自 V24 文档公式，不是实机校准证明。

## 可选实验的 NX 部署与定位适配

本节仅用于主动选择新 MAVLink 实验的开发者。默认 SUB 用户继续使用 `StreamerStart.sh` / `streamer.service`，不执行本节服务切换。

安装 [串口依赖](../../software/jetson/requirements-integration.txt)，GStreamer 沿用 Jetson 教程。仓库部署到 `/opt/finsrov`，服务用户 `finsrov` 需具有 dialout/video 权限。先前台测试：

```bash
cd /opt/finsrov/software/jetson
python3 -m fins_bridge --serial /dev/ttyTHS1 --baud 460800 --bind 192.168.0.2 --pc 192.168.0.1
```

确认配置后，将 [环境文件样例](../../software/jetson/deploy/bridge.env.example) 保存为 `/etc/finsrov/bridge.env`，将 [控制服务](../../software/jetson/deploy/fins-bridge.service) 和 [视频服务](../../software/jetson/deploy/fins-video.service) 安装到 systemd 单元目录。检查 `GStreamerTest.py` 的相机、PC 地址。停止旧 `streamer.service` 再启用新服务；模板也声明互斥。查看 `journalctl -u fins-bridge -u fins-video`。本次未安装服务、烧录或操作设备。

串口 exclusive 打开，仅桥接占用；串口错误退出，由 systemd 重启，新会话要求显式恢复。视频与控制独立。回退须恢复匹配的旧固件和旧服务。

定位进程向 `127.0.0.1:54323` 发 UTF-8 JSON 数据报，所有字段必需：

```json
{"source_us":10000000,"sample_seq":1,"reset_id":0,"x":0.0,"y":0.0,"yaw":0.0,"vx":0.0,"vy":0.0,"yaw_rate":0.0,"depth":0.5,"valid":1,"depth_valid":1}
```

`source_us` 必须是本 NX monotonic 采样时刻，不能直接使用示例数值或把旧样本盖上新时间。XY/速度为局部世界系，机体前左上，yaw 逆时针；单位 m、m/s、rad、rad/s，深度向下为正。`sample_seq` 和 `reset_id` 是 uint32，前者递增允许回绕，重置坐标只改后者。非法数值、过期、未来超过 5 ms、负深度被拒绝。定位无效发 `valid=0`；停更 200 ms 或重置会撤销轨迹会话。

PC↔NX 沿用原 TIMESYNC；NX↔MCU 每 0.5 s 同步，接受 RTT≤20 ms，映射保守减去传输耗时和额外 2 ms，2 s 后失效。转发保留源有效期，MCU 截止时间再限于接收后最多 200 ms。无法同步不启用运动；需要实机测量时延。

## 此集成实验的未完成事项与验收门槛

1. V24 需要 200 Hz 原始流、1536 健康样本（7.68 s）预热及 50 Hz 输出。本版本只接收外部生成的定位，没有加载模型或声称完成在线推理。
2. 固定 `FINS_TELEMETRY` 没有 V24 所需的 IMU 解算 yaw/quaternion，驱动也没有全部 RPM/电压新鲜度。当前 200 Hz 诊断 `valid_mask=0`，不能作为完整推理输入。需另行确定内部原始流、yaw 来源、源时刻和有效性，不暗改 PC dialect。
3. 本集成端点的定位重置、灯光动作明确返回不支持；云台辅助指令不执行，能力位不声明辅助控制。外部定位重置以 `reset_id` 通知。这些限制专属于新集成端点，不能据此认定 SUB 源码没有灯光、姿态或深度辅助功能。
4. 尚未验证手柄插拔、DMA/串口吞吐、传感器刷新、推进器方向、密封与池试。先全部传感器有效→手动启停→逐路方向→网络/串口/定位故障停止→共享深度校准→定深构建→轨迹池试，记录三端版本和日志。
5. 协议保留原声明和哈希；上位机源仓库未找到根许可证，来源记录不等于新增授权。固件沿用 MPL-2.0；公开发布前确认协议生成物与来源代码的授权范围。
