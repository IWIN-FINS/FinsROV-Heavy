# 电气资料开发交接

日期：2026-11-18。本轮在共用 `codex/pc-nx-mcu-integration` 工作树更新 **SYS-01 Rev B**；提交由主任务统一处理。作者补充记录见 [AUTH](author-confirmations.zh-CN.md)。

## 本轮交付

- [系统接线说明](../../hardware/electrical/system-wiring.zh-CN.md)：电源分配边界、NX 三线串口、传感器、云台、照明、CAN、PLC 与烧写接口。
- [三页 A3 图册](../../hardware/electrical/diagrams/system-wiring.pdf)：供电、通信执行链与新增 20P/18P 端子功能分组，三页均有可编辑 SVG。
- [系统工作簿](../../hardware/electrical/system-wiring.xlsx)：保留 74 条功能连接、17 条 MCU 对照、44 组线束编号，增加 10 组端子分配；四张 CSV 与四个工作簿页签共用 JSON。
- 主供电 1/2 正、3/4 负，同极性两线并接一个 LCB60 匹配插头；单个放电口足够，未将此结论转写成连接器厂家额定电流。
- 全部 24V 标签明确为电池直供，供应商范围 16.8–25.2 V。压力计从 EC-07 取电，UART8 经串口转 RS-485 模块与 20P 接到四只压力计。
- 20P 的四个 4P 同信号组分别用互联短接件，PLC/CAN 两线各自独立；20P 无固定顺序，复刻者按布线安排并记录。18P 三路 PWM 独立接线，L1/L2/L3 对应 PWM10/11/12、PH11/PH12/PI0；余 9P 自由分配。
- 最终 EDA 已删除 R12，旧焊装争议关闭；旧 HTML 保留，最终制板/装联文件的替换由[电源板定版清单](../../hardware/pcb/assembly/revision-checklist.zh-CN.md)跟踪。
- 默认固件为 SUB，仅手柄控制；三路灯同一个软件亮度状态不等于物理短接或 UI 分别调亮度。

## 验证与重建

从仓库根目录执行：

```text
python hardware/electrical/system_data.py
python hardware/electrical/diagrams/render_system_wiring.py
node hardware/electrical/build_system_workbook.mjs
python hardware/electrical/verify_system_wiring.py
```

PDF 生成需要 ReportLab 和中文 TrueType 字体，非 Windows 使用 `FINS_PDF_FONT` 指定字体。Excel 生成器需要可导入的 `@oai/artifact-tool`，其第一个可选参数为 JSON 绝对路径，第二个为预览输出目录。`verify_system_wiring.py` 仅用 Python 标准库，且不接触硬件。新生成器不自动运行旧图纸生成器或改写已有工作簿。

本轮已读取其他 agent 定稿的 BAT/EQ/JET/PWR 与 AUTH 来源。后续任何来源文件变化都会使整文件哈希失效；应先审阅是否改变连接含义，再按上述顺序刷新来源和生成物并校验，不要压制来源变化提示。新记录应写回源数据再生成，避免覆盖仅填在 Excel 中的内容。

本轮完成的检查：

- 四张 CSV 与 JSON 全部字段一致；导出 XLSX 重新读取 OOXML，核对每个表格单元格、四张筛选表及冻结窗格；验证 20P/18P 占位总数和独立信号规则。
- 从实际 SUB 宏、GPIO 数组、UART 注释与 TIM 配置重新计算/核对八路 DShot、串口和三路灯引脚；核对实验快照的串口波特率。
- 来源 SHA-256 与生成时记录一致；文本先统一 LF，二进制按原字节核对。
- 三张 SVG 可解析；PDF 为三页 A3 横版，全部页面已渲染检查；工作簿四个页签的首尾区段已渲染检查，未见裁切或乱码。
- 未执行实机导通、上电、充电、烧写、CAN 采集或推进器试验。

## 尚需实物或原工程确认

1. EC-07 输入/输出物理端子、其余负载的保护路径与回流、保护参数、铜排规格和最终匹配的制板/装联发布文件。
2. 主供电焊点与每芯通流验证，EC-08/09 逐针网络、板端插座针号、连接器观察面、线径/长度/端子、CAN 终端与参考地、PLC 板端和系缆。
3. 实装 H30 型号/供电/电平，RS-485 转换模块型号/电平/方向控制/端子及模块供电，云台两轴/型号/地址，LF/GM/RF 与 L1/L2/L3 的灯位映射、电平及电源组端接工艺，烧写口针序。

20P 原机顺序、主电源四芯功能、压力供电来源和 R12 焊装选择已不属于未决问题。4P 互联短接件采购链接来自作者，本次未读取到商品页，未补猜间距、电流或适配型号。软件 agent 可引用源码映射，但不能把它当作实机部署验证。
