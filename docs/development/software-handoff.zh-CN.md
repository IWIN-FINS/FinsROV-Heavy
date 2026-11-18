# 软件贯通分支交接

日期：2026-11-18。分支：`codex/pc-nx-mcu-integration`。平台基线：`1ce03a02f90b8dcb9881c5d26c4dfd7594ad3f99`；固定 PC：`5ebe00e2573c8df5b5ad376915fab2da0644c188`。

## 当前默认复刻选择

用户现已明确以 **SUB 手柄操控**为默认：`firmware/SUB` + `V5StreamerNX.py` + 原 SUB 手柄上位机，启动用 `StreamerStart.sh` / `streamer.service`。SUB 源码已有的姿态、深度、灯光辅助控制保留；默认流程不包含轨迹或在线推理。原 SUB Windows 程序的可发布版本、依赖、启动命令及手柄配置仍需补齐。

以下 MAVLink 实现与惯性里程计快照作为可选实验保留，历史测试和构建事实不变；其定深禁用及辅助能力缺项不描述 SUB。此默认选择仅调整复刻文档，不切换 Git 默认分支，不改固件源行为。

## 已交付的可选实验实现

- 固定 PC 协议及 Python/C 生成物、共同向量和逐文件 SHA-256；未改 PC 工作副本。
- NX 可执行桥接：独占 UART、会话转换、保守时钟映射、MCU 执行 ACK/STATUS、定位输入验证及独立服务模板。
- MCU 集成覆盖层：共享原实验版 BSP 和驱动框架，新增可在目标板及宿主机执行的同一 C++ 状态机、绝对启停、去重、代次和指令有效期。
- 安全停止路径实际调用控制层、清空输出与定深；模式切换重新捕获航向并清除 PID 积分；IMU/四压力计有效帧新鲜度门槛。
- 显式 C++ 模拟执行端与静态定位夹具，不接物理执行器。

该可选实验的操作、构建、部署、接口和已知限制见[集成说明](../software/pc-nx-mcu.zh-CN.md)。实验代码入口为 `software/jetson/fins_bridge/runtime.py` 与 `firmware/integrated/Interface/TaskIntegrated.cpp`；这个 MAVLink 执行端保持绝对目标状态，不混入旧 TaskSUB 按钮翻转语义。默认 SUB 继续使用自己的原有控制入口和匹配转发。

## 验证证据

2026-11-18 使用固定 PC 虚拟环境 Python 3.12、MinGW GCC/G++ 13.1.0，执行 24 项 unittest，全部通过、无跳过。包含 6 项既有 Jetson 回归。固定 PC 的真实 Controller 通过回环 UDP 连接 NX，再经过字节流连接实际 C++ Endpoint，完成手动→轨迹→停止→手动与失联停止。

C++ 宿主程序启动时另有传感器完整帧、每种截断长度、错误校验、计时回绕/超时及 PID 清零断言；这些断言使用与板端相同的辅助实现。它们不等于实际传感器或 DMA 验证。

Arm Compiler 6.24、CMake/Ninja 成功生成 A 板 ELF/HEX。复用依赖提交：CMSIS-DSP `4ee6da97c239071283d869de7c636d7621280e7c`，ETL `a12dbbd91174e895bdd5492826b0226b9668fc5f`。构建有 5 条继承 Battery 驱动缺少 override 的警告，无错误。ROM 82732 bytes，RW+ZI 50672 bytes。

二进制校验及测试结果见[验证记录](../software/integration-validation.json)。构建日志与二进制保留在本 worktree 的忽略目录 `build/integrated`；没有将二进制当作正式发行固件。

## 此集成实验明确未完成

- 未烧录、未连接 NX、未进行推进器或水下试验；仅集成固件的实机定深能力默认关闭。固定 MAVLink PC 会阻止此未校准固件的轨迹启动，不能将模拟模式的能力报告移植到实机。
- V24 推理原始流接口仍缺解算 yaw/quaternion、采样新鲜度及端到端数据契约；定位 JSON 接口不意味着模型已经接通。
- 集成端点诊断 `valid_mask=0`，不可送入正式模型；其 reset/light/gimbal 不支持，不虚报辅助能力。SUB 中已有的灯光及姿态/深度辅助不受此实验限制影响。
- 需确认 H30 的同帧输出配置、四压力计实际刷新周期、共享深度基准、方向与缩放，再开放定深并池试。
- 协议生成物和源代码的对外再分发许可仍需归属核对，原有声明全部保留。

当前先补齐默认 SUB 手柄上位机及启动配置，核验匹配的 SUB 三端组合。若后续继续本 MAVLink 实验，再从真实 NX/MCU 部署文件与模型版本清点开始，台架验证命令生存期、传感器失效、DMA 队列压力与实际停止时延。所有实物缺项集中反馈主协调，不在代码中补猜硬件参数。
