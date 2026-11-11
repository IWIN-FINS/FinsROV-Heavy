# 制作 FinsROV-Heavy

[项目首页](../README.zh-CN.md) · [English](README.md)

按下面的顺序准备零件、装配和联调。教程来自团队的 V5 制作记录，保留实装照片，并与当前 CAD、BOM 和两套固件对应。整理日期：2026-11-11。

| 步骤 | 教程 | 本章完成的工作 |
| --- | --- | --- |
| 01 | [备料与版本说明](build/01-overview.zh-CN.md) | 选对 CAD 和 BOM，区分当前配置与早期方案 |
| 02 | [机架、浮力块与推进器安装](build/02-frame.zh-CN.md) | 组框架、装电池滑座与预埋螺母、固定推进器 |
| 03 | [电源管理板焊接](build/03-power-board.zh-CN.md) | 使用交互式 BOM 定位元件，核对 R12 的版本冲突 |
| 04 | [推进器与电调接线](build/04-thrusters.zh-CN.md) | 对照编号接三相线与控制信号，核对转向 |
| 05 | [水压计配置](build/05-pressure-sensors.zh-CN.md) | 逐个配置地址、波特率和压力单位 |
| 06 | [Jetson 配置与视频传输](build/06-jetson.zh-CN.md) | 网络、串口、SUB 转发脚本、视频及开机自启 |
| 07 | [联调检查与待补资料](build/07-bring-up.zh-CN.md) | 逐级确认通信和控制链路，记录尚缺的装配与试验步骤 |

## 配套资料

- [整机 CAD 与两份 BOM](../README.zh-CN.md#硬件资料)
- [加工图纸与打印模型](../hardware/mechanical/README.zh-CN.md)
- [固件编译及协议](../firmware/README.zh-CN.md)
- [Jetson 脚本与配置](../software/jetson/README.md)
- [原始附件下载](reference/README.md)
- [来源、修订与文件校验](SOURCES.md)

Jetson 控制脚本目前只对应 **SUB 正常操控版**。惯性里程计实验版的波特率和帧结构不同，不能只改波特率就复用本脚本。Windows 上位机程序尚未提供；视频可先用教程中的 GStreamer 命令独立接收。
