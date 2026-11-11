<p align="right"><a href="README.md">English</a> · <strong>简体中文</strong></p>

# 机械加工与打印资料

按 BOM 编号寻找单件，再确认材料、图纸版本和加工参数。本目录保留 65 个原文件：49 个 STEP、7 个 3MF、5 个 PDF，以及 F3D、SLDASM、OBJ、MTL 各 1 个。原文件名与版本目录保持不变。

[本体 BOM](../bom/BOM.csv) · [舱内 BOM](../bom/BOM-electronics.csv) · [完整文件索引](FILES.md) · [文件校验清单](manifest.json) · [返回首页](../../README.zh-CN.md)

## 先确认版本

当前装配基准是 [主体装配 STEP](../cad/主体装配.step) 和 [舱内装配 STEP 压缩包](../cad/舱内装配.step.zip)。下表“对应”指单件与总装的顶点集合、拓扑实体计数一致，允许坐标轴变换和镜像；这项检查不替代完整曲面、制造公差或实机配置核验。

- **当前主体对应 V2 侧板 A、V2 顶板和 V2 浮力块。** `框架/` 中的旧版同类件保留作参考。
- **侧板 B（FR-02）没有完全对应的独立文件。** 总装定义为 `#159704`，与 V2 侧板 A 存在差异；不要将 A 直接按 2 件下单或自行镜像替代。
- **横梁（FR-07）、电机线夹夹体（CB-03/04）有版本差异。** 已提供的单件与当前总装不完全一致，需确认以哪个版本加工。
- **PDF 是旧版螺纹标注参考。** 两目录的顶板 PDF 分别相同，横梁 PDF 也分别相同，日期均为 2025-09-13。它们没有完整尺寸、材料、公差和表面处理要求，也不能仅因位于 `框架V2/` 就视为 V2 制造图。侧板图中的 `M3 - H6` 原文须确认牙规后再用于加工。

## 本体单件

数量沿用本体 BOM，按一台机器人计。压片 6 件是 CB-01、CB-02、CB-07、CB-09 的合计，不要在各行数量之外再加 6 件。

| BOM | Part / 零件 | Qty / 数量 | STEP | Process / 制备方式 |
| --- | --- | ---: | --- | --- |
| FR-01 | 侧板 A / Side plate A | 1 | [STEP](source/%E6%A1%86%E6%9E%B6V2/%E4%BE%A7%E6%9D%BFV2.step) | 铝合金钣金 / Aluminum sheet metal |
| FR-03 | 顶板 / Top plate | 1 | [STEP](source/%E6%A1%86%E6%9E%B6V2/%E9%A1%B6%E6%9D%BFV2.step) | 铝合金钣金 / Aluminum sheet metal |
| BU-01 | 浮力块 / Buoyancy block | 2 | [STEP](source/%E6%A1%86%E6%9E%B6V2/%E6%B5%AE%E5%8A%9B%E5%9D%97V2.step) | 浮力材料定制 / Custom buoyancy material |
| EN-05 | 电池舱后盖 / Battery rear cap | 1 | [STEP](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E8%88%B1%E5%90%8E%E7%9B%96.step) | 铝合金 CNC / Aluminum CNC |
| EN-06 | 电池舱前盖 / Battery front cap | 1 | [STEP](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E8%88%B1%E5%89%8D%E7%9B%96.step) | 铝合金 CNC / Aluminum CNC |
| EN-07 | 电机端舱盖 / Motor end cap | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E7%9B%96_%E7%94%B5%E6%9C%BA%E7%AB%AF.step) | 铝合金 CNC / Aluminum CNC |
| EN-08 | 信号端舱盖 / Signal end cap | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E7%9B%96_%E4%BF%A1%E5%8F%B7%E7%AB%AF.step) | 铝合金 CNC / Aluminum CNC |
| MT-01 | 水压计固定块 A / Pressure mount A | 1 | [STEP](source/%E6%A1%86%E6%9E%B6/%E5%9B%BA%E5%AE%9A%E5%9D%97R.step) | FDM |
| MT-02 | 水压计固定块 A 镜像 / Pressure mount A, mirrored | 1 | [STEP](source/%E6%A1%86%E6%9E%B6/%E5%9B%BA%E5%AE%9A%E5%9D%97L.step) | FDM |
| MT-03 | 灯与水压计固定块 B / Light + pressure mount B | 1 | [STEP](source/%E6%A1%86%E6%9E%B6/%E4%BA%8C%E5%90%88%E4%B8%80%E5%9B%BA%E5%AE%9A%E5%9D%97R.step) | FDM |
| MT-04 | 灯与水压计固定块 B 镜像 / Light + pressure mount B, mirrored | 1 | [STEP](source/%E6%A1%86%E6%9E%B6/%E4%BA%8C%E5%90%88%E4%B8%80%E5%9B%BA%E5%AE%9A%E5%9D%97L.step) | FDM |
| MT-05 | 相机主体支架 / Camera bracket | 1 | [STEP](source/%E6%A1%86%E6%9E%B6/%E7%9B%B8%E6%9C%BA%E6%94%AF%E6%9E%B6%20v21.step) | FDM |
| MT-06 | 相机固定座 / Camera base | 1 | [STEP](source/%E5%9B%BA%E5%AE%9A%E7%9B%B8%E6%9C%BA%E5%BA%95%E5%BA%A7.step) | FDM |
| CB-01/02/07/09 | 线夹压片 / Cable clamp plates | 6 | [STEP](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E5%A4%B9%E7%89%87.step) | 工艺待核 / Process unconfirmed |
| CB-05 | 普通线夹 / Cable clip | 6 | [STEP](source/%E6%A1%86%E6%9E%B6/%E7%BA%BF%E5%A4%B9%20v1.step) | 工艺待核 / Process unconfirmed |
| CB-06 | 云台线缆夹 1 / Camera cable clamp 1 | 1 | [STEP](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E4%BA%91%E5%8F%B0%E7%BA%BF%E7%BC%86%E5%A4%B91%E5%8F%B7.step) | 工艺待核 / Process unconfirmed |
| CB-08 | 云台线缆夹 2 / Camera cable clamp 2 | 1 | [STEP](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E4%BA%91%E5%8F%B0%E7%BA%BF%E7%BC%86%E5%A4%B92%E5%8F%B7.step) | 工艺待核 / Process unconfirmed |

光轴夹垫片模型是 FR-05 成品套件内实体的参考，仍按 **6 套光轴夹**采购。两种阿卡插座模型对应 EN-04 成品安装座，是否经过改制仍待核实，不能据模型文件另计一套。

## 舱内安装件

以下七个 STEP 均对应当前舱内装配，每舱各 1 件。实机材料和制法暂未确认；提供 3MF 不代表实机一定采用 FDM。

| BOM | Part / 零件 | Qty / 数量 | STEP | 3MF |
| --- | --- | ---: | --- | --- |
| MTI-01 | 法兰仓内固定环 v3 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E6%B3%95%E5%85%B0%E4%BB%93%E5%86%85%E5%9B%BA%E5%AE%9A%E7%8E%AF%20v3.step) | — |
| MTI-02 | 对插板固定件 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E5%AF%B9%E6%8F%92%E6%9D%BF%E5%9B%BA%E5%AE%9A%E4%BB%B6.step) | — |
| MTI-03 | 主控固定板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E4%B8%BB%E6%8E%A7%E5%9B%BA%E5%AE%9A%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E4%B8%BB%E6%8E%A7%E5%9B%BA%E5%AE%9A%E6%9D%BF.3mf) |
| MTI-04 | 电调固定板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E7%94%B5%E8%B0%83%E5%9B%BA%E5%AE%9A%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E7%94%B5%E8%B0%83%E5%9B%BA%E5%AE%9A%E6%9D%BF.3mf) |
| MTI-05 | 上板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E4%B8%8A%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E4%B8%8A%E6%9D%BF.3mf) |
| MTI-06 | ORIN NX固定板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/ORIN%20NX%E5%9B%BA%E5%AE%9A%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/ORIN%20NX%E5%9B%BA%E5%AE%9A%E6%9D%BF.3mf) |
| MTI-07 | 电源底板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E7%94%B5%E6%BA%90%E5%BA%95%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E7%94%B5%E6%BA%90%E5%BA%95%E6%9D%BF.3mf) |

3MF 单位为 mm，仅包含网格和缩略图，没有喷嘴、耗材、层高、壁数、填充、支撑或摆放方向等切片配置。打印时需重新切片；STEP 与同名 3MF 尚未逐面核验。线缆夹目录另有 3pin、4pin 两个 3MF，其内部标题均为“线缆对接灌胶管 v5”，对应关系和用量见待核项。

## 如何准备加工单

1. **选定单件和数量。** 用本页和 BOM 定位文件；“几何差异”项先确定版本。补出 FR-02 的独立 STEP，以及螺母条 MTI-08 等当前缺失的制造资料。采购套件内的零件不重复计数。
2. **CNC 舱盖。** 每种 1 件。随 STEP 提供铝材牌号、表面处理、密封面与孔位公差、螺纹牙规及有效深度。现有模型不能单独说明这些要求。
3. **机架板件。** FR-01/02/03 分别列项。顶板需确认板厚、折弯内 R、折弯方向和成形尺寸；旧 PDF 的螺纹标注需与最终 STEP 对照。横梁的材料及成形或切削路线仍待核。
4. **FDM 安装件。** 对已确认的 MT-01 至 MT-06 提供耗材牌号、打印方向、层高、壁厚、填充率、支撑及嵌件要求。其余线夹和舱内安装件先确认实际制法，再决定是否打印。
5. **浮力块。** BU-01 共 2 件，以 V2 模型询价；同时给出材料密度、目标净浮力、工作深度和表面封装要求。
6. **收件后试装。** 对照总装检查左右件、安装孔、配合及接插件空间。最终装配教程仍需补充实机照片、紧固件规格、密封安装方法和验收记录。

加工平台入口保留在 BOM 对应行。确认版本后，把 STEP、适配的二维标注和上述参数一起发给加工方。

## 附件与旧版参考

电池舱内部支撑、IMU 外壳、盒子／盖子、套管、灌胶管、铅块垫片和旧云台支架已保留在 [完整文件索引](FILES.md)。尚不能从当前总装确定它们的实机用途和数量，因此没有增加采购量。

`框架/外壳FINAL v27.step` 是 2025-09-17 导出的旧版总装。另有 [SLDASM + OBJ + MTL 参考压缩包](reference/外壳FINAL-v27.zip)，解压保留原始文件名。目录中没有 SLDPRT 文件，SLDASM 是否可独立打开尚未验证。

## 待补资料

| 项目 | 需要确认 |
| --- | --- |
| 版本 | FR-02 独立模型；FR-07、CB-03/04 采用总装版本还是单件版本；旧 PDF 是否仍适用 |
| 金属件 | 铝材牌号、表面处理、公差、螺纹及折弯要求；横梁实机制法 |
| 打印与舱内件 | 实机耗材与打印参数；七种舱内安装件的材料和制法；线夹制法暂缺 |
| 浮力材料 | 密度、目标净浮力、工作深度和封装要求 |
| 额外附件 | 哪些仍装在当前机器人上，各自数量与安装位置 |

## 文件完整性

[manifest.json](manifest.json) 记录每个原文件的相对路径、大小、SHA-256、发布位置及 BOM 对应关系。三个参考文件存入 ZIP，其余文件逐字节保留。重复图纸也保留原目录，并在索引说明重复关系。
