# 制作 FinsROV-Heavy

[项目首页](../README.zh-CN.md) · [English](README.md)

按下面的顺序准备零件、装配和联调。教程来自团队的 V5 制作记录，保留实装照片，并与当前 CAD、BOM 和固件对应。2026-11-18 补充制造版本清单、舱内试装和密封记录；原章节编号保留，阅读顺序按下表安排。

| 步骤 | 教程 | 本章完成的工作 |
| --- | --- | --- |
| 01 | [备料与版本说明](build/01-overview.zh-CN.md) | 选对 CAD 和 BOM，区分当前配置与早期方案 |
| 02 | [机架、浮力块与推进器安装](build/02-frame.zh-CN.md) | 组框架、装电池滑座与预埋螺母、固定推进器 |
| 03 | [电源管理板焊接](build/03-power-board.zh-CN.md) | 最终工程已删除 R12，区分旧交互式 BOM 与最终装联文件 |
| 04 | [推进器与电调接线](build/04-thrusters.zh-CN.md) | 对照编号接三相线与控制信号，核对转向 |
| 05 | [水压计配置](build/05-pressure-sensors.zh-CN.md) | 逐个配置地址、波特率和压力单位 |
| 08 | [舱内装配与线束固定](build/08-enclosure-assembly.zh-CN.md) | 对照板卡、支撑件与线束路径完成试装，记录缺失尺寸和照片 |
| 06 | [Jetson 配置与视频传输](build/06-jetson.zh-CN.md) | 网络、串口、SUB 转发脚本、视频及开机自启 |
| 07 | [联调检查与待补资料](build/07-bring-up.zh-CN.md) | 逐级确认通信和控制链路，记录尚缺的装配与试验步骤 |
| 09 | [密封、检漏与配平记录](build/09-sealing-trim.zh-CN.md) | 准备组件依据和试验记录；尚非经过实机验证的操作规程 |

默认复刻路线为 **SUB 固件 + 原 Jetson 转发 + 匹配旧协议的 PC 手柄程序**，当前目标是手柄操控。PC 程序及其版本、启动说明仍待提供；MAVLink 集成与惯性里程计资料作为可选实验版本保留。

## 配套资料

- [合并后的开发状态、优先级与待补清单](development/remaining-work.zh-CN.md)
- [可选 PC—NX—MCU 集成开发版及当前限制](software/pc-nx-mcu.zh-CN.md)
- [作者确认记录：供电、20P/18P 端子与默认 SUB](development/author-confirmations.zh-CN.md)
- [电气接线资料：电池舱、设备舱插座定义、接口/线束表和 CAN 协议](../hardware/electrical/README.zh-CN.md)
- [整机 CAD 与两份 BOM](../README.zh-CN.md#硬件资料)
- [加工图纸与打印模型](../hardware/mechanical/README.zh-CN.md)
- [制造版本与放行清单](../hardware/mechanical/manufacturing-release.zh-CN.md) · [制造与装配记录模板](../hardware/mechanical/build-record.zh-CN.md)
- [固件编译及协议](../firmware/README.zh-CN.md)
- [Jetson 脚本与配置](../software/jetson/README.md)
- [原始附件下载](reference/README.md)
- [来源、修订与文件校验](SOURCES.md)

原有 Jetson 控制脚本只对应 **SUB 正常操控版**。惯性里程计实验版的波特率和帧结构不同，不能只改波特率就复用本脚本。[Windows 多模式上位机 `5ebe00e`](https://github.com/ganju2390/NXTelemetryMonitor/tree/5ebe00e2573c8df5b5ad376915fab2da0644c188) 已提供，使用 MAVLink 2，不能直接与旧脚本混用；三端版本与实机验收需另行核对。视频可用教程中的 GStreamer 命令独立接收。
