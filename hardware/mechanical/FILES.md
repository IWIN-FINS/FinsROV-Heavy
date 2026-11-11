# File index / 文件索引

[English guide](README.md) · [中文制造说明](README.zh-CN.md) · [SHA-256 manifest](manifest.json)

65 source files are preserved. Counts here describe files, not quantities to manufacture. 原文件共 65 个；文件数不等于加工数量。

“几何对应”仅表示与当前总装的顶点集合及拓扑计数匹配；材料、曲面、制造公差及实机配置仍以相应说明为准。

| Source file / 原文件 | BOM | Status / 状态 | Notes / 说明 |
| --- | --- | --- | --- |
| [IMU外壳 v5.step](source/IMU%E5%A4%96%E5%A3%B3%20v5.step) | MTI-09 | 选装 / optional | 选装，主要遮护电路、防止电路外露。模型含两片壳体，选装 1 套；按舱内件 FDM 归类，适配型号和耗材待补。 |
| [固定相机底座.step](source/%E5%9B%BA%E5%AE%9A%E7%9B%B8%E6%9C%BA%E5%BA%95%E5%BA%A7.step) | MT-06 | 几何对应 / matched | 已确认 FDM；耗材牌号、打印方向、壁厚及填充参数待补。 |
| [外壳FINAL v27.mtl](reference/%E5%A4%96%E5%A3%B3FINAL-v27.zip) | — | 参考压缩包 / archive | 保留原始装配/渲染参考；SLDASM 是否可独立打开尚未验证，目录内未发现 SLDPRT。 |
| [外壳FINAL v27.obj](reference/%E5%A4%96%E5%A3%B3FINAL-v27.zip) | — | 参考压缩包 / archive | 保留原始装配/渲染参考；SLDASM 是否可独立打开尚未验证，目录内未发现 SLDPRT。 |
| [外壳FINAL v27.SLDASM](reference/%E5%A4%96%E5%A3%B3FINAL-v27.zip) | — | 参考压缩包 / archive | 保留原始装配/渲染参考；SLDASM 是否可独立打开尚未验证，目录内未发现 SLDPRT。 |
| [框架/二合一固定块L.step](source/%E6%A1%86%E6%9E%B6/%E4%BA%8C%E5%90%88%E4%B8%80%E5%9B%BA%E5%AE%9A%E5%9D%97L.step) | MT-04 | 几何对应 / matched | 已确认 FDM；耗材牌号、打印方向、壁厚及填充参数待补。 |
| [框架/二合一固定块R.step](source/%E6%A1%86%E6%9E%B6/%E4%BA%8C%E5%90%88%E4%B8%80%E5%9B%BA%E5%AE%9A%E5%9D%97R.step) | MT-03 | 几何对应 / matched | 已确认 FDM；耗材牌号、打印方向、壁厚及填充参数待补。 |
| [框架/云台支架.step](source/%E6%A1%86%E6%9E%B6/%E4%BA%91%E5%8F%B0%E6%94%AF%E6%9E%B6.step) | — | 归属待核 / unassigned | 未与当前相机安装件建立一致对应，可能为其他版本，需确认是否仍使用。 |
| [框架/侧板.step](source/%E6%A1%86%E6%9E%B6/%E4%BE%A7%E6%9D%BF.step) | — | 旧版 / legacy | 与当前总装对应件有几何差异，保留为旧版参考。 |
| [框架/侧板图纸.pdf](source/%E6%A1%86%E6%9E%B6/%E4%BE%A7%E6%9D%BF%E5%9B%BE%E7%BA%B8.pdf) | FR-01、FR-02 | 旧图参考 / drawing reference | 旧版螺纹标注图。作者确认两侧同件、铝合金钣金及黑色阳极氧化；与侧板 V2 适配、完整尺寸和公差待核。 |
| [框架/光轴夹垫片.step](source/%E6%A1%86%E6%9E%B6/%E5%85%89%E8%BD%B4%E5%A4%B9%E5%9E%AB%E7%89%87.step) | FR-05 | 套件内实体 / kit component | 对应光轴夹套件内实体 #159717。套件已按 6 套计数，不自动增加独立加工数量。 |
| [框架/固定块L.step](source/%E6%A1%86%E6%9E%B6/%E5%9B%BA%E5%AE%9A%E5%9D%97L.step) | MT-02 | 几何对应 / matched | 已确认 FDM；耗材牌号、打印方向、壁厚及填充参数待补。 |
| [框架/固定块R.step](source/%E6%A1%86%E6%9E%B6/%E5%9B%BA%E5%AE%9A%E5%9D%97R.step) | MT-01 | 几何对应 / matched | 已确认 FDM；耗材牌号、打印方向、壁厚及填充参数待补。 |
| [框架/外壳FINAL v27.step](source/%E6%A1%86%E6%9E%B6/%E5%A4%96%E5%A3%B3FINAL%20v27.step) | — | 旧总装 / legacy assembly | 2025-09-17 旧版整机参考，不能替代 hardware/cad/主体装配.step。 |
| [框架/横梁.step](source/%E6%A1%86%E6%9E%B6/%E6%A8%AA%E6%A2%81.step) | FR-07 | 几何差异 / differs | 作者确认铝合金钣金、黑色阳极氧化，共 2 件。两目录文件相同；单件与总装的版本差异仍需核清。 |
| [框架/横梁图纸.pdf](source/%E6%A1%86%E6%9E%B6/%E6%A8%AA%E6%A2%81%E5%9B%BE%E7%BA%B8.pdf) | FR-07 | 旧图参考 / drawing reference | 两份 PDF 相同，标注 18 个 M4-6H 通孔螺纹。作者确认铝合金钣金及黑色阳极氧化；尺寸、公差与版本适配待核。 |
| [框架/浮力块 v1.step](source/%E6%A1%86%E6%9E%B6/%E6%B5%AE%E5%8A%9B%E5%9D%97%20v1.step) | — | 旧版 / legacy | 与当前总装对应件有几何差异，保留为旧版参考。 |
| [框架/电机线夹2pin.step](source/%E6%A1%86%E6%9E%B6/%E7%94%B5%E6%9C%BA%E7%BA%BF%E5%A4%B92pin.step) | CB-04 | 几何差异 / differs | 与主体装配夹体顶点坐标存在差异。下单版本及实机工艺待核。 |
| [框架/电机线夹4pin.step](source/%E6%A1%86%E6%9E%B6/%E7%94%B5%E6%9C%BA%E7%BA%BF%E5%A4%B94pin.step) | CB-03 | 几何差异 / differs | 与主体装配夹体顶点坐标存在差异。下单版本及实机工艺待核。 |
| [框架/电机线夹片.step](source/%E6%A1%86%E6%9E%B6/%E7%94%B5%E6%9C%BA%E7%BA%BF%E5%A4%B9%E7%89%87.step) | CB-01、CB-02、CB-07、CB-09 | 几何对应 / matched | 四行压片的顶点几何与拓扑计数均对应。总量 6 件，按 BOM 分配；材料及制法暂缺。 |
| [框架/相机支架 v21.step](source/%E6%A1%86%E6%9E%B6/%E7%9B%B8%E6%9C%BA%E6%94%AF%E6%9E%B6%20v21.step) | MT-05 | 几何对应 / matched | 已确认 FDM；耗材牌号、打印方向、壁厚及填充参数待补。 |
| [框架/线夹 v1.step](source/%E6%A1%86%E6%9E%B6/%E7%BA%BF%E5%A4%B9%20v1.step) | CB-05 | 几何对应 / matched | 数量见 BOM；实机材料及制法暂缺。 |
| [框架/阿卡插座.step](source/%E6%A1%86%E6%9E%B6/%E9%98%BF%E5%8D%A1%E6%8F%92%E5%BA%A7.step) | EN-04 | 成品参考 / purchased part | 对应成品安装座的 CAD 参考。是否改件待核，保持 BOM 成套采购数量。 |
| [框架/顶板.step](source/%E6%A1%86%E6%9E%B6/%E9%A1%B6%E6%9D%BF.step) | — | 旧版 / legacy | 与当前总装对应件有几何差异，保留为旧版参考。 |
| [框架/顶板图纸.pdf](source/%E6%A1%86%E6%9E%B6/%E9%A1%B6%E6%9D%BF%E5%9B%BE%E7%BA%B8.pdf) | FR-03 | 旧图参考 / drawing reference | 两份 PDF 完全相同，日期 2025-09-13；与 V2 STEP 的适配关系待核。 |
| [框架V2/侧板V2.step](source/%E6%A1%86%E6%9E%B6V2/%E4%BE%A7%E6%9D%BFV2.step) | FR-01、FR-02 | 作者确认 / owner confirmed | 作者确认两块侧板相同，共 2 件，统一采用此文件。铝合金钣金、黑色阳极氧化；原总装两个定义的差异仅保留追溯。 |
| [框架V2/横梁.step](source/%E6%A1%86%E6%9E%B6V2/%E6%A8%AA%E6%A2%81.step) | FR-07 | 几何差异 / differs | 作者确认铝合金钣金、黑色阳极氧化，共 2 件。两目录文件相同；单件与总装的版本差异仍需核清。 |
| [框架V2/横梁图纸.pdf](source/%E6%A1%86%E6%9E%B6V2/%E6%A8%AA%E6%A2%81%E5%9B%BE%E7%BA%B8.pdf) | FR-07 | 旧图参考 / drawing reference | 两份 PDF 相同，标注 18 个 M4-6H 通孔螺纹。作者确认铝合金钣金及黑色阳极氧化；尺寸、公差与版本适配待核。 |
| [框架V2/浮力块V2.step](source/%E6%A1%86%E6%9E%B6V2/%E6%B5%AE%E5%8A%9B%E5%9D%97V2.step) | BU-01 | 几何对应 / matched | PVC 发泡，密度 0.25 g/cm³，材料耐压深度 250 m，共 2 件；净浮力及封装要求待补。该深度非整机额定深度。 |
| [框架V2/阿卡插座V2.step](source/%E6%A1%86%E6%9E%B6V2/%E9%98%BF%E5%8D%A1%E6%8F%92%E5%BA%A7V2.step) | EN-04 | 成品参考 / purchased part | 对应成品安装座的 CAD 参考。是否改件待核，保持 BOM 成套采购数量。 |
| [框架V2/顶板V2.step](source/%E6%A1%86%E6%9E%B6V2/%E9%A1%B6%E6%9D%BFV2.step) | FR-03 | 几何对应 / matched | 铝合金钣金、黑色阳极氧化；对应当前顶板。铝材牌号、折弯及旧 PDF 适配待核。 |
| [框架V2/顶板图纸.pdf](source/%E6%A1%86%E6%9E%B6V2/%E9%A1%B6%E6%9D%BF%E5%9B%BE%E7%BA%B8.pdf) | FR-03 | 旧图参考 / drawing reference | 两份 PDF 完全相同，日期 2025-09-13；与 V2 STEP 的适配关系待核。 |
| [电池舱/电池固定环.step](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E5%9B%BA%E5%AE%9A%E7%8E%AF.step) | MT-08 | 用途已确认 / function confirmed | 电池支撑采用 3D 打印，防止电池晃动和旋转；按舱内件 FDM 归类。数量、安装位置及耗材参数待补。 |
| [电池舱/电池定位片.step](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E5%AE%9A%E4%BD%8D%E7%89%87.step) | MT-09 | 用途已确认 / function confirmed | 电池支撑采用 3D 打印，防止电池晃动和旋转；按舱内件 FDM 归类。数量、安装位置及耗材参数待补。 |
| [电池舱/电池舱前盖.step](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E8%88%B1%E5%89%8D%E7%9B%96.step) | EN-06 | 几何对应 / matched | 已确认铝合金 CNC；铝材牌号、密封面及孔公差、表面处理待补。 |
| [电池舱/电池舱后盖.step](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E8%88%B1%E5%90%8E%E7%9B%96.step) | EN-05 | 几何对应 / matched | 已确认铝合金 CNC；铝材牌号、密封面及孔公差、表面处理待补。 |
| [电池舱/电池舱法兰填充.step](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E8%88%B1%E6%B3%95%E5%85%B0%E5%A1%AB%E5%85%85.step) | MT-10 | 用途已确认 / function confirmed | 按作者确认的舱内件 FDM 归类；与电池支撑的装配关系、实装数量及打印参数待核。 |
| [盒子.step](source/%E7%9B%92%E5%AD%90.step) | — | 归属待核 / unassigned | 保留附件原件。是否属于当前实机、安装位置、数量与制法待核，不额外增加 BOM 数量。 |
| [盖子.step](source/%E7%9B%96%E5%AD%90.step) | — | 归属待核 / unassigned | 保留附件原件。是否属于当前实机、安装位置、数量与制法待核，不额外增加 BOM 数量。 |
| [线缆夹/3pin.3mf](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/3pin.3mf) | — | 归属待核 / unassigned | 3MF 单位 mm，无切片参数；用途、对应 STEP、数量与材料待核。内部 Title 均为“线缆对接灌胶管 v5”。 |
| [线缆夹/3pin细线缆管.step](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/3pin%E7%BB%86%E7%BA%BF%E7%BC%86%E7%AE%A1.step) | — | 归属待核 / unassigned | 保留附件原件。是否属于当前实机、安装位置、数量与制法待核，不额外增加 BOM 数量。 |
| [线缆夹/4pin.3mf](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/4pin.3mf) | — | 归属待核 / unassigned | 3MF 单位 mm，无切片参数；用途、对应 STEP、数量与材料待核。内部 Title 均为“线缆对接灌胶管 v5”。 |
| [线缆夹/4pin细线缆管.step](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/4pin%E7%BB%86%E7%BA%BF%E7%BC%86%E7%AE%A1.step) | — | 归属待核 / unassigned | 保留附件原件。是否属于当前实机、安装位置、数量与制法待核，不额外增加 BOM 数量。 |
| [线缆夹/云台线缆夹1号.step](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E4%BA%91%E5%8F%B0%E7%BA%BF%E7%BC%86%E5%A4%B91%E5%8F%B7.step) | CB-06 | 几何对应 / matched | 数量见 BOM；实机材料及制法暂缺。 |
| [线缆夹/云台线缆夹2号.step](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E4%BA%91%E5%8F%B0%E7%BA%BF%E7%BC%86%E5%A4%B92%E5%8F%B7.step) | CB-08 | 几何对应 / matched | 数量见 BOM；实机材料及制法暂缺。 |
| [线缆夹/光轴短套管.step](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E5%85%89%E8%BD%B4%E7%9F%AD%E5%A5%97%E7%AE%A1.step) | CB-10 | 用途已确认 / function confirmed | 用于限制线缆夹沿光轴平移。实装数量、材料、制法和轴向配合待补。 |
| [线缆夹/光轴长套管.step](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E5%85%89%E8%BD%B4%E9%95%BF%E5%A5%97%E7%AE%A1.step) | CB-11 | 用途已确认 / function confirmed | 用于限制线缆夹沿光轴平移。实装数量、材料、制法和轴向配合待补。 |
| [线缆夹/夹片.step](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E5%A4%B9%E7%89%87.step) | CB-01、CB-02、CB-07、CB-09 | 几何对应 / matched | 四行压片的顶点几何与拓扑计数均对应。总量 6 件，按 BOM 分配；材料及制法暂缺。 |
| [线缆夹/线缆对接灌胶管.step](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E7%BA%BF%E7%BC%86%E5%AF%B9%E6%8E%A5%E7%81%8C%E8%83%B6%E7%AE%A1.step) | — | 归属待核 / unassigned | 保留附件原件。是否属于当前实机、安装位置、数量与制法待核，不额外增加 BOM 数量。 |
| [设备舱/舱内/3mf格式/ORIN NX固定板.3mf](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/ORIN%20NX%E5%9B%BA%E5%AE%9A%E6%9D%BF.3mf) | MTI-06 | 网格参考 / mesh | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。3MF 单位 mm，不含切片配置；与 STEP 尚未逐面核验。 |
| [设备舱/舱内/3mf格式/上板.3mf](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E4%B8%8A%E6%9D%BF.3mf) | MTI-05 | 网格参考 / mesh | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。3MF 单位 mm，不含切片配置；与 STEP 尚未逐面核验。 |
| [设备舱/舱内/3mf格式/主控固定板.3mf](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E4%B8%BB%E6%8E%A7%E5%9B%BA%E5%AE%9A%E6%9D%BF.3mf) | MTI-03 | 网格参考 / mesh | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。3MF 单位 mm，不含切片配置；与 STEP 尚未逐面核验。 |
| [设备舱/舱内/3mf格式/电源底板.3mf](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E7%94%B5%E6%BA%90%E5%BA%95%E6%9D%BF.3mf) | MTI-07 | 网格参考 / mesh | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。3MF 单位 mm，不含切片配置；与 STEP 尚未逐面核验。 |
| [设备舱/舱内/3mf格式/电调固定板.3mf](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E7%94%B5%E8%B0%83%E5%9B%BA%E5%AE%9A%E6%9D%BF.3mf) | MTI-04 | 网格参考 / mesh | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。3MF 单位 mm，不含切片配置；与 STEP 尚未逐面核验。 |
| [设备舱/舱内/ORIN NX固定板.step](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/ORIN%20NX%E5%9B%BA%E5%AE%9A%E6%9D%BF.step) | MTI-06 | 几何对应 / matched | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。单件与当前舱内装配几何对应。 |
| [设备舱/舱内/上板.step](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E4%B8%8A%E6%9D%BF.step) | MTI-05 | 几何对应 / matched | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。单件与当前舱内装配几何对应。 |
| [设备舱/舱内/主控固定板.step](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E4%B8%BB%E6%8E%A7%E5%9B%BA%E5%AE%9A%E6%9D%BF.step) | MTI-03 | 几何对应 / matched | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。单件与当前舱内装配几何对应。 |
| [设备舱/舱内/对插板固定件.step](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E5%AF%B9%E6%8F%92%E6%9D%BF%E5%9B%BA%E5%AE%9A%E4%BB%B6.step) | MTI-02 | 几何对应 / matched | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。单件与当前舱内装配几何对应。 |
| [设备舱/舱内/法兰仓内固定环 v3.step](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E6%B3%95%E5%85%B0%E4%BB%93%E5%86%85%E5%9B%BA%E5%AE%9A%E7%8E%AF%20v3.step) | MTI-01 | 几何对应 / matched | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。单件与当前舱内装配几何对应。 |
| [设备舱/舱内/电源底板.step](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E7%94%B5%E6%BA%90%E5%BA%95%E6%9D%BF.step) | MTI-07 | 几何对应 / matched | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。单件与当前舱内装配几何对应。 |
| [设备舱/舱内/电调固定板.step](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E7%94%B5%E8%B0%83%E5%9B%BA%E5%AE%9A%E6%9D%BF.step) | MTI-04 | 几何对应 / matched | 作者确认舱内安装件为 FDM，每舱 1 件。耗材及打印参数待补。单件与当前舱内装配几何对应。 |
| [设备舱/舱盖_信号端.step](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E7%9B%96_%E4%BF%A1%E5%8F%B7%E7%AB%AF.step) | EN-08 | 几何对应 / matched | 已确认铝合金 CNC；铝材牌号、密封面及孔公差、表面处理待补。 |
| [设备舱/舱盖_电机端.step](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E7%9B%96_%E7%94%B5%E6%9C%BA%E7%AB%AF.step) | EN-07 | 几何对应 / matched | 已确认铝合金 CNC；铝材牌号、密封面及孔公差、表面处理待补。 |
| [铅块垫片.f3d](source/%E9%93%85%E5%9D%97%E5%9E%AB%E7%89%87.f3d) | BU-03 | 用途已确认 / function confirmed | 缩减铅块孔径，以便用 M4 螺钉安装到框架上配平。数量随铅块孔数及装配方案确定；材质、制法与配合待核。 |
| [铅块垫片.step](source/%E9%93%85%E5%9D%97%E5%9E%AB%E7%89%87.step) | BU-03 | 用途已确认 / function confirmed | 缩减铅块孔径，以便用 M4 螺钉安装到框架上配平。数量随铅块孔数及装配方案确定；材质、制法与配合待核。 |
