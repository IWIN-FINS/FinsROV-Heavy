# 电气接线资料

[项目首页](../../README.zh-CN.md) · [English](README.md) · [制作教程](../../docs/README.zh-CN.md)

本目录按实际设备、穿舱接口和线束组织接线资料。2026-11-18 系统级资料更新为 Rev B：74 条连接记录、17 条 MCU 对照、44 组线束补录项和 10 组端子功能分配。已加入主供电同极性并线、24V 电池直供、压力链路及三灯独立 PWM；尚未具备按图制作全部线束的条件，未做实机导通或上电验证。

| 资料 | 文件 | 用途 |
| --- | --- | --- |
| 系统接线与核验 | [总说明](system-wiring.zh-CN.md) · [三页 PDF](diagrams/system-wiring.pdf) · [供电 SVG](diagrams/system-power.svg) · [通信 SVG](diagrams/system-signals.svg) · [端子 SVG](diagrams/system-terminal-allocation.svg) | 供电边界、NX 三线串口、传感器、八推进器执行链及 20P/18P 分组 |
| 系统台账 | [Excel](system-wiring.xlsx) · [连接 CSV](system-connections.csv) · [MCU CSV](mcu-signal-map.csv) · [线束 CSV](system-harness.csv) · [端子分组 CSV](system-terminal-allocation.csv) | 四个页签逐条记录来源；功能分组不代表物理针号，未填长度不以零代替 |
| 电源板定版 | [EC-07 版本核对单](../pcb/assembly/revision-checklist.zh-CN.md) | 最终 EDA 已删除 R12；其余板版、端子、装联文件和板级验证记录 |
| 设备舱插座定义 | [两端接口、位置与逐类接线](equipment-wiring.zh-CN.md) | 8 个电机插座、信号端位置及烧写方式 |
| 设备舱图纸 | [位置 SVG](diagrams/equipment-panel.svg) · [接线 SVG](diagrams/equipment-circuits.svg) · [端子 SVG](diagrams/equipment-terminals.svg) · [三页 PDF](diagrams/equipment-wiring.pdf) | 23 个接口/开孔位置及端子功能分组；区分通用扩展与当前云台用途 |
| 设备舱接口表 | [Excel](equipment-wiring.xlsx) · [清单 CSV](equipment-connectors.csv) · [逐针 CSV](equipment-pinout.csv) | 61 个已明确功能的针脚；型号与针序待核项单列 |
| 电池舱接线说明 | [电池、开关、供电和充电/CAN](battery-wiring.zh-CN.md) | 电池规格、三个面板接口、来源差异和集中待核项 |
| 电池舱接线图 | [SVG](diagrams/battery-wiring.svg) · [PDF](diagrams/battery-wiring.pdf) | 逻辑接线及接口编号，不表示孔位比例或插头物理针位 |
| 接口和线束表 | [Excel](battery-wiring.xlsx) · [接口 CSV](battery-pinout.csv) · [线束 CSV](battery-harness.csv) | 与图纸共用编号，未核线号、长度和线径明确留空待补 |
| 电池状态通信 | [BMS CAN 协议摘录](battery-can.zh-CN.md) | 后续读取电压、电流、SOC、单体和故障信息的接口依据 |
| 原始资料 | [电池附件索引](references/battery/README.md) | 参数表、CAN 协议原件、实物照片及文件校验 |

## 编号规则

`BAT-01` 为电池总成，`SW-BAT` 为舱盖开关，`J-BAT-PWR` 为主供电插座，`J-BAT-SVC` 为充电/CAN 插座；`H-BAT-xx` 为线束，`W-BAT-xx` 为线束内导线或尚未拆解的回路。设备舱以 `J-Mxx` 标记电机口，`J-PRS-*` 为水压计，`J-EXT-*` 为扩展，`J-LGT-*` 为照明，另设 `J-PLC`、`J-CAN` 和 `J-DBG`。`P-*` 是暂未完整定义的图中位置。它们是接线资料编号，不替代原有 BOM 编号。

电池内部的放电接口、充电接口和 CAN 引线，与穿舱插座分开描述。没有厂家针位图或实物核验时，不画接插件端面针号，不将负极、CAN 参考地或外壳默认为相连。

## 后续资料范围

| 子系统 | 已有依据 | 尚需整理 |
| --- | --- | --- |
| 电池舱 | 主供电 1/2 正、3/4 负，同极性并至单个 LCB60 匹配插头；CAN 为电池 3/4 到设备舱 1/2 | 端接工艺、每芯电流、CAN 舱内控制器与参考地、插座视图、线径和线长 |
| 设备舱面板 | [位置、针脚和转向说明](equipment-wiring.zh-CN.md) | 烧写/相机/电源线/顶部件的接法，端面针位与舱内端子 |
| 主舱配电 | LM5069 制板文件、旧交互式 BOM；最终 EDA 已删除 R12；24V 标签为电池直供 | EC-07 物理端子、输入及其他负载保护路径、支路保护和负载适配 |
| 主控与 Jetson | [UART 接线照片和逻辑端口](../../docs/build/06-jetson.zh-CN.md) | 实装载板版本、物理针号、供电与编程接口 |
| 电调与推进器 | [M1–M8、ESC 焊盘和 DShot 映射](../../docs/build/04-thrusters.zh-CN.md) | 两块转接板逐针网络、线缆长度、最终旋向 |
| 传感器与附件 | 压力从 EC-07 取电，UART8 经串口转485到20P；三灯 PWM10/11/12 独立连接；20P 顺序自由记录 | 转换器型号/端子、舵机型号和轴向、灯空间映射/电平、其余支路保护路径 |
| 岸端与系缆 | PLC 和网络配置记录 | 岸端/水下板电源、系缆芯数、屏蔽与接地 |

系统台账已补出 MCU GPIO 与载板手册接口的逻辑对应；当前默认固件为 SUB，仅手柄控制。20P 同信号 4P 组各用一个互联短接件，四组独立；PLC 两线、CAN 两线及三灯 PWM 禁止互相短接。物理端子、配电、线束和实物参数仍按表逐项核验，现有图表尚未经过实机导通、上电、充电或 CAN 报文验证。
