# 电气资料开发交接

日期：2026-11-18。分支 `codex/electrical-docs`，基线 `1ce03a0`。

## 本轮交付

- [系统接线说明](../../hardware/electrical/system-wiring.zh-CN.md)：电源分配边界、NX 三线串口、传感器、云台、照明、CAN、PLC 与烧写接口。
- [两页 A3 图册](../../hardware/electrical/diagrams/system-wiring.pdf)：另提供同版可编辑 SVG。
- [系统工作簿](../../hardware/electrical/system-wiring.xlsx)：74 条功能连接、17 条 MCU 对照、44 组待实测线束；三张 CSV 与工作簿数据相同。
- [EC-07 版本核对单](../../hardware/pcb/assembly/revision-checklist.zh-CN.md)：固定 R12、板版、输入输出、铜排、保护参数和装联资料的核对项目。
- 三章相关教程增加与系统资料的交叉链接；现有面板 JSON/CSV、已有接口工作簿、原 Gerber 和 BOM 均未修改。

## 验证与重建

从仓库根目录执行：

```text
python hardware/electrical/system_data.py
python hardware/electrical/diagrams/render_system_wiring.py
node hardware/electrical/build_system_workbook.mjs
python hardware/electrical/verify_system_wiring.py
```

PDF 生成需要 ReportLab 和中文 TrueType 字体，非 Windows 使用 `FINS_PDF_FONT` 指定字体。Excel 生成器需要可导入的 `@oai/artifact-tool`，其第一个可选参数为 JSON 绝对路径，第二个为预览输出目录。`verify_system_wiring.py` 仅用 Python 标准库，且不接触硬件。新生成器不自动运行旧图纸生成器或改写已有工作簿。

本轮完成的检查：

- 三张 CSV 与 JSON 全部字段一致；导出 XLSX 重新读取 OOXML，核对每个表格单元格、三张筛选表及冻结窗格。
- 从实际 SUB 宏、GPIO 数组、UART 注释与 TIM 配置重新计算/核对八路 DShot、串口和三路灯引脚；核对实验快照的串口波特率。
- 来源 SHA-256 与生成时记录一致；文本先统一 LF，二进制按原字节核对。
- 两张 SVG 可解析；PDF 为两页 A3 横版，已渲染检查。工作簿三个页签的首尾区段已渲染检查，未见裁切或乱码。
- 未执行实机导通、上电、充电、烧写、CAN 采集或推进器试验。

## 尚需实物或原工程确认

1. 主供电四芯分配、EC-07 的输入输出及支路回流、R12 与板版关系、保护参数和铜排规格。
2. EC-08/09 逐针网络、板端插座针号、连接器观察面、线径/长度/端子、CAN 终端与参考地、PLC 板端和系缆。
3. 实装 H30 型号/供电/电平，压力收发电路，云台两轴/型号/地址，灯具实际电平与位置通道，烧写口针序。

没有新资料支持修改 BOM 型号或数量，本轮已将该结论告知制造 agent。软件 agent 可引用源码映射，但必须按其集成固件重新核对，不能把当前 SUB 配置当作新协议的部署验证。
