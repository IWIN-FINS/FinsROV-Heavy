<p align="right"><a href="README.md">English</a> · <strong>简体中文</strong></p>

# 机械加工与打印资料

按 BOM 编号寻找单件，再确认材料、图纸版本和加工参数。本目录保留 65 个原文件：49 个 STEP、7 个 3MF、5 个 PDF，以及 F3D、SLDASM、OBJ、MTL 各 1 个。原文件名与版本目录保持不变。

[本体 BOM](../bom/BOM.csv) · [舱内 BOM](../bom/BOM-electronics.csv) · [完整文件索引](FILES.md) · [文件校验清单](manifest.json) · [返回首页](../../README.zh-CN.md)

## 先确认版本

当前装配基准是 [主体装配 STEP](../cad/主体装配.step) 和 [舱内装配 STEP 压缩包](../cad/舱内装配.step.zip)。下表“对应”指单件与总装的顶点集合、拓扑实体计数一致，允许坐标轴变换和镜像；这项检查不替代完整曲面、制造公差或实机配置核验。

- **当前制造资料采用 V2 侧板、V2 顶板和 V2 浮力块。** `框架/` 中的旧版同类件保留作参考。
- **作者确认两块侧板相同，统一用 `侧板V2.step` 加工 2 件。** BOM 保留 FR-01、FR-02 各 1 件以追溯原装配位置。原总装 `#159702`、`#159704` 的几何差异保留为历史记录，不再据此要求两个不同加工件。
- **横梁（FR-07）、电机线夹夹体（CB-03/04）有版本差异。** 已提供的单件与当前总装不完全一致，需确认具体加工版本。横梁的铝合金钣金工艺及黑色阳极氧化表面处理已由作者确认。
- **PDF 是旧版螺纹标注参考。** 两目录的顶板 PDF 分别相同，横梁 PDF 也分别相同，日期均为 2025-09-13。原图没有完整尺寸、材料、公差和表面处理要求；框架材料及黑色阳极氧化现已由作者补充确认，也不能仅因位于 `框架V2/` 就视为 V2 制造图。侧板图中的 `M3 - H6` 原文须确认牙规后再用于加工。

## 本体单件

数量沿用本体 BOM，按一台机器人计。压片 6 件是 CB-01、CB-02、CB-07、CB-09 的合计，不要在各行数量之外再加 6 件。

| BOM | Part / 零件 | Qty / 数量 | STEP | Process / 制备方式 |
| --- | --- | ---: | --- | --- |
| FR-01 + FR-02 | 相同侧板 / Identical side plates | 2 | [STEP](source/%E6%A1%86%E6%9E%B6V2/%E4%BE%A7%E6%9D%BFV2.step) | 铝合金钣金 + 黑色阳极氧化 / Black-anodized aluminum sheet metal |
| FR-03 | 顶板 / Top plate | 1 | [STEP](source/%E6%A1%86%E6%9E%B6V2/%E9%A1%B6%E6%9D%BFV2.step) | 铝合金钣金 + 黑色阳极氧化 / Black-anodized aluminum sheet metal |
| FR-07 | 横梁 / Crossbeam | 2 | [STEP](source/%E6%A1%86%E6%9E%B6V2/%E6%A8%AA%E6%A2%81.step) | 钣金 + 黑色阳极氧化；版本待核 / Black-anodized sheet metal; revision to confirm |
| BU-01 | 浮力块 / Buoyancy block | 2 | [STEP](source/%E6%A1%86%E6%9E%B6V2/%E6%B5%AE%E5%8A%9B%E5%9D%97V2.step) | PVC 发泡定制 / Custom PVC foam |
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

以下七个 STEP 均对应当前舱内装配，每舱各 1 件，作者已确认全部采用 **FDM 3D 打印**。耗材牌号、打印方向、层高、壁厚和填充率仍需补充。

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

1. **选定单件和数量。** 用本页和 BOM 定位文件；“几何差异”项先确定版本。两块侧板共用 V2 单件，加工 2 件；螺母条 MTI-08 等零件仍需补充制造资料。采购套件内的零件不重复计数。
2. **CNC 舱盖。** 每种 1 件。随 STEP 提供铝材牌号、表面处理、密封面与孔位公差、螺纹牙规及有效深度。现有模型不能单独说明这些要求。
3. **机架板件。** 两块相同侧板、一块顶板和两根横梁均采用铝合金钣金及黑色阳极氧化。铝型材表面同样采用黑色阳极氧化。制作笔记标注框架板厚 6 mm；顶板及横梁仍需核对最终孔位、铝材牌号、折弯内 R、方向、成形尺寸与公差；旧 PDF 的螺纹标注需与最终 STEP 对照。
4. **FDM 安装件。** MT-01 至 MT-06、七种舱内安装件和电池支撑按 FDM 准备。提供耗材牌号、打印方向、层高、壁厚、填充率、支撑及嵌件要求。其余线夹与套管的实机制法暂缺。
5. **浮力块。** BU-01 共 2 件，按 V2 模型定制 PVC 发泡材料，密度 **0.25 g/cm³（250 kg/m³）**，材料耐压深度 **250 m**。每块目标净浮力及封装要求待补；250 m 是浮力材料参数，不代表整机额定深度。
6. **收件后试装。** 对照总装检查左右件、安装孔、配合及接插件空间。最终装配教程仍需补充实机照片、紧固件规格、密封安装方法和验收记录。

加工平台入口保留在 BOM 对应行。确认版本后，把 STEP、适配的二维标注和上述参数一起发给加工方。

## 附件与旧版参考

| BOM | 附件 / Accessory | Model |
| --- | --- | --- |
| MT-08 | 电池固定环 / Battery support ring | [STEP](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E5%9B%BA%E5%AE%9A%E7%8E%AF.step) |
| MT-09 | 电池定位片 / Battery locator | [STEP](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E5%AE%9A%E4%BD%8D%E7%89%87.step) |
| MT-10 | 电池舱法兰填充 / Battery flange filler | [STEP](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E8%88%B1%E6%B3%95%E5%85%B0%E5%A1%AB%E5%85%85.step) |
| CB-10 | 光轴短套管 / Short shaft sleeve | [STEP](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E5%85%89%E8%BD%B4%E7%9F%AD%E5%A5%97%E7%AE%A1.step) |
| CB-11 | 光轴长套管 / Long shaft sleeve | [STEP](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E5%85%89%E8%BD%B4%E9%95%BF%E5%A5%97%E7%AE%A1.step) |
| BU-03 | 铅块垫片 / Ballast bore spacer | [STEP](source/%E9%93%85%E5%9D%97%E5%9E%AB%E7%89%87.step) |
| MTI-09 | IMU 外壳（选装） / Optional IMU cover | [STEP](source/IMU%E5%A4%96%E5%A3%B3%20v5.step) |

- **电池支撑**采用 3D 打印，防止电池晃动和旋转，按舱内件 FDM 归类。固定环、定位片的数量和位置随电池配置确定；法兰填充件与支撑的具体装配关系待补。
- **光轴套管**限制线缆夹沿光轴平移。长、短套管的数量、材质和制法仍待补充。
- **IMU 外壳为选装件**，主要遮护电路，防止电路外露。模型含两片壳体，选装时 1 套；按舱内件 FDM 归类。它不是水密耐压外壳。
- **铅块垫片**缩减配重铅块孔径，便于使用 M4 螺钉将铅块固定在框架上。用量按实际孔数及安装方案确定，材质和制法待补。

以上附件已列入 BOM；未确认的数量留空，选装项不计入默认装机数量。盒子／盖子、灌胶管和旧云台支架仍保留在 [文件索引](FILES.md)，其用途或实机使用情况待核。

### 配平浮力

平台未加配重时，设计浮力大于重力。BU-02 使用 **200 g 铅块**按需调整，作者经验用量为 **4–5 块**，总质量约 **0.8–1.0 kg**，不是固定采购数量。

[淘宝商品：水下机器人配重 200 g 铅块](https://item.taobao.com/item.htm?id=561262404205) · [作者提供的分享链接](https://e.tb.cn/h.jRkXFiwiurdhOld?tk=7QlA6d6JviR)

商品地址由分享链接解析得到，规格和经验用量由作者提供。安装时配合 BU-03 垫片和 M4 螺钉，螺钉长度、螺母及垫圈按装配厚度选配并计入 HW-01。使用实际电池、载荷和线缆配置，在水中逐块增减并调整前后、左右位置，直到达到所需浮态与姿态。

`框架/外壳FINAL v27.step` 是 2025-09-17 导出的旧版总装。另有 [SLDASM + OBJ + MTL 参考压缩包](reference/外壳FINAL-v27.zip)，解压保留原始文件名。目录中没有 SLDPRT 文件，SLDASM 是否可独立打开尚未验证。

## 待补资料

| 项目 | 需要确认 |
| --- | --- |
| 版本 | FR-07、CB-03/04 的加工版本；旧 PDF 是否仍适用。两侧板同件已确认 |
| 金属件 | 铝材牌号、公差、螺纹及折弯要求；CNC 舱盖表面处理。框架钣金及黑色阳极氧化已确认 |
| 打印与舱内件 | FDM 耗材与打印参数；线夹、套管和铅块垫片的材料及制法 |
| 浮力材料 | 每块目标净浮力和封装要求；PVC、密度与材料耐压深度已确认 |
| 额外附件 | 电池支撑、套管、垫片的数量及安装位置；盒盖、灌胶管和旧云台支架的使用情况 |

## 文件完整性

[manifest.json](manifest.json) 记录每个原文件的相对路径、大小、SHA-256、发布位置及 BOM 对应关系。三个参考文件存入 ZIP，其余文件逐字节保留。重复图纸也保留原目录，并在索引说明重复关系。

## 制作教程补充

已补充 [机架、浮力块与推进器安装](../../docs/build/02-frame.zh-CN.md)，包含四类紧固件用量及预埋螺母安装照片。原教程的电机线夹为 3D 打印、每电机一夹共 8 个，与当前 STEP 夹体数量及单件版本尚待对应；其余线夹和套管的具体制法仍待核。
