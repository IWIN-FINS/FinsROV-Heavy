<p align="right"><strong>English</strong> · <a href="README.zh-CN.md">简体中文</a></p>

# Mechanical fabrication files

Find the part by its BOM ID, then confirm the revision, material and fabrication parameters. This directory preserves 65 source files: 49 STEP, 7 3MF, 5 PDF, and one each of F3D, SLDASM, OBJ and MTL. Original filenames and revision folders are retained.

[Body BOM](../bom/BOM.csv) · [Electronics BOM](../bom/BOM-electronics.csv) · [Complete file index](FILES.md) · [Checksums](manifest.json) · [Project home](../../README.md)

The BOMs and detailed file notes are in Chinese. The tables below use the same part IDs and quantities.

## Select the revision first

Use the [vehicle assembly STEP](../cad/主体装配.step) and [electronics assembly ZIP](../cad/舱内装配.step.zip) as the assembly references. A geometric match below means matching STEP vertex sets and topology entity counts, allowing axis changes and reflection. It does not establish full surface equivalence, manufacturing tolerances or the physical build configuration.

- **The fabrication references use the V2 side plate, top plate and buoyancy block.** Earlier versions in `框架/` remain available as references.
- **The platform author confirmed that the two side plates are identical. Fabricate two copies of `侧板V2.step`.** FR-01 and FR-02 remain as one piece each to trace the assembly positions. Differences between the original assembly definitions `#159702` and `#159704` are retained as historical evidence, not as a requirement for two different fabricated parts.
- **The crossbeam (FR-07) and motor cable clamp bodies (CB-03/04) differ from the assembly.** Confirm the fabrication revision before using these standalone files. The author has confirmed aluminum sheet metal and black anodizing for the crossbeam.
- **The PDFs are older thread-callout references.** The top-plate PDFs are byte-identical across both revision folders, as are the crossbeam PDFs. All drawings are dated 2025-09-13 and omit complete dimensions, material, tolerance and finish specifications. Their location in the V2 folder does not establish compatibility. The side-plate callout `M3 - H6` also needs clarification before machining.

## Vehicle body parts

Quantities come from the body BOM and apply to one vehicle. The six clamp plates are the combined total of CB-01, CB-02, CB-07 and CB-09; do not add six more to those rows.

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

The shaft-clamp spacer file represents a component within FR-05. Keep the purchase quantity at **six complete shaft-clamp kits**. The two mounting-seat models refer to purchased item EN-04; whether that item was modified remains unconfirmed. Additional model files do not add purchase quantities.

## Electronics mounting parts

All seven STEP files below match parts in the electronics assembly, one of each per enclosure. The author has confirmed **FDM 3D printing** for all seven. Filament grade, orientation, layer height, walls and infill remain to be specified.

| BOM | Part / 零件 | Qty / 数量 | STEP | 3MF |
| --- | --- | ---: | --- | --- |
| MTI-01 | 法兰仓内固定环 v3 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E6%B3%95%E5%85%B0%E4%BB%93%E5%86%85%E5%9B%BA%E5%AE%9A%E7%8E%AF%20v3.step) | — |
| MTI-02 | 对插板固定件 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E5%AF%B9%E6%8F%92%E6%9D%BF%E5%9B%BA%E5%AE%9A%E4%BB%B6.step) | — |
| MTI-03 | 主控固定板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E4%B8%BB%E6%8E%A7%E5%9B%BA%E5%AE%9A%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E4%B8%BB%E6%8E%A7%E5%9B%BA%E5%AE%9A%E6%9D%BF.3mf) |
| MTI-04 | 电调固定板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E7%94%B5%E8%B0%83%E5%9B%BA%E5%AE%9A%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E7%94%B5%E8%B0%83%E5%9B%BA%E5%AE%9A%E6%9D%BF.3mf) |
| MTI-05 | 上板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E4%B8%8A%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E4%B8%8A%E6%9D%BF.3mf) |
| MTI-06 | ORIN NX固定板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/ORIN%20NX%E5%9B%BA%E5%AE%9A%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/ORIN%20NX%E5%9B%BA%E5%AE%9A%E6%9D%BF.3mf) |
| MTI-07 | 电源底板 | 1 | [STEP](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/%E7%94%B5%E6%BA%90%E5%BA%95%E6%9D%BF.step) | [3MF](source/%E8%AE%BE%E5%A4%87%E8%88%B1/%E8%88%B1%E5%86%85/3mf%E6%A0%BC%E5%BC%8F/%E7%94%B5%E6%BA%90%E5%BA%95%E6%9D%BF.3mf) |

The 3MF files use millimeters and contain meshes and thumbnails only. They do not provide slicer settings for material, nozzle, layer height, walls, infill, supports or orientation. Slice them again before printing; the meshes have not been checked surface by surface against the corresponding STEP files. Two additional cable-tube meshes, `3pin.3mf` and `4pin.3mf`, share the internal title “线缆对接灌胶管 v5”; their exact pairing and quantities remain unconfirmed.

## Prepare a fabrication order

1. **Choose the part and quantity.** Follow the BOM IDs and resolve revision differences first. Use the same V2 side-plate model for both plates. Manufacturing details are still needed for parts such as the MTI-08 threaded strips. Avoid recounting components included in purchased kits.
2. **CNC end caps.** Order one of each cap. Supply the aluminum grade, finish, sealing-face and hole tolerances, thread specifications and effective thread depths alongside the STEP.
3. **Frame plates.** The two identical side plates, top plate and two crossbeams use aluminum sheet metal with black anodizing. Aluminum profiles also receive black anodizing. Specify the alloy, thickness, bend radius, direction, finished dimensions and tolerances; reconcile older thread callouts with the selected STEP.
4. **FDM mounts.** MT-01 through MT-06, the seven internal mounts and battery supports use FDM. Supply filament grade, orientation, layer height, walls, infill, supports and insert requirements. Processes for other cable clamps and sleeves remain unconfirmed.
5. **Buoyancy blocks.** Request two BU-01 parts using the V2 model in **PVC foam, 0.25 g/cm³ (250 kg/m³), with a material depth rating of 250 m**, as specified by the author. Target net buoyancy per block and encapsulation remain to be specified. The 250 m value describes the buoyancy material, not the complete vehicle depth rating.
6. **Trial assembly.** Check handed parts, mounting holes, fits and connector clearance against the assemblies. A complete assembly tutorial still needs build photographs, fastener specifications, seal installation details and acceptance records.

Supplier and fabrication-platform links remain in the corresponding BOM rows. Send the selected STEP, applicable drawing annotations and manufacturing specifications together.

## Additional parts and older references

| BOM | 附件 / Accessory | Model |
| --- | --- | --- |
| MT-08 | 电池固定环 / Battery support ring | [STEP](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E5%9B%BA%E5%AE%9A%E7%8E%AF.step) |
| MT-09 | 电池定位片 / Battery locator | [STEP](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E5%AE%9A%E4%BD%8D%E7%89%87.step) |
| MT-10 | 电池舱法兰填充 / Battery flange filler | [STEP](source/%E7%94%B5%E6%B1%A0%E8%88%B1/%E7%94%B5%E6%B1%A0%E8%88%B1%E6%B3%95%E5%85%B0%E5%A1%AB%E5%85%85.step) |
| CB-10 | 光轴短套管 / Short shaft sleeve | [STEP](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E5%85%89%E8%BD%B4%E7%9F%AD%E5%A5%97%E7%AE%A1.step) |
| CB-11 | 光轴长套管 / Long shaft sleeve | [STEP](source/%E7%BA%BF%E7%BC%86%E5%A4%B9/%E5%85%89%E8%BD%B4%E9%95%BF%E5%A5%97%E7%AE%A1.step) |
| BU-03 | 铅块垫片 / Ballast bore spacer | [STEP](source/%E9%93%85%E5%9D%97%E5%9E%AB%E7%89%87.step) |
| MTI-09 | IMU 外壳（选装） / Optional IMU cover | [STEP](source/IMU%E5%A4%96%E5%A3%B3%20v5.step) |

- **Battery supports** are 3D-printed to prevent battery movement and rotation and are classified as FDM internal parts. Ring and locator quantities and positions depend on the battery configuration; the flange filler's exact assembly relationship remains to be documented.
- **Shaft sleeves** limit cable-clamp translation along the shafts. Quantities, material and manufacturing process remain unconfirmed.
- **The IMU cover is optional.** It shields exposed circuitry. The model contains two shell pieces, making one optional set, classified with the FDM internal parts. It is not a watertight pressure housing.
- **Ballast bore spacers** reduce the lead-block hole diameter to suit M4 mounting screws. Quantities depend on the holes used and the mounting arrangement; material and process remain unconfirmed.

These accessories have been added to the BOMs. Unconfirmed quantities are blank and optional items are excluded from default installed quantities. The box/lid, potting tubes and older camera mount remain in the [file index](FILES.md), pending confirmation of use.

### Ballast and trim

The vehicle is designed to be positively buoyant before ballast is fitted. Use **200 g lead blocks** (BU-02) as needed. The author's typical setup uses **4–5 blocks**, totaling **0.8–1.0 kg in mass**; this is an experience-based starting quantity, not a fixed purchase requirement.

[Taobao: 200 g ROV ballast blocks](https://item.taobao.com/item.htm?id=561262404205) · [Original share link](https://e.tb.cn/h.jRkXFiwiurdhOld?tk=7QlA6d6JviR)

The item address was resolved from the supplied share link; the specification and typical quantity were provided by the author. Use BU-03 bore spacers and M4 screws, selecting screw length, nuts and washers for the mounting thickness and counting them under HW-01. With the actual battery, payload and cable configuration, add or remove blocks in water and adjust their fore/aft and lateral positions to obtain the intended buoyancy and attitude.

`框架/外壳FINAL v27.step` is an older vehicle assembly exported on 2025-09-17. The [SLDASM + OBJ + MTL archive](reference/外壳FINAL-v27.zip) preserves the three original reference filenames. No SLDPRT files were supplied, and standalone opening of the SLDASM has not been verified.

## Information still needed

| Area | Missing information |
| --- | --- |
| Revisions | Fabrication revisions for FR-07 and CB-03/04; applicability of the older PDFs. Identical side plates are confirmed |
| Metal parts | Alloy, tolerances, thread and bend specifications; CNC end-cap finish. Sheet-metal frame and black anodizing are confirmed |
| Printed and internal parts | FDM filament grades and slicer settings; materials and processes for cable clamps, sleeves and ballast spacers |
| Buoyancy | Target net buoyancy per block and encapsulation; PVC, density and material depth rating are confirmed |
| Extra accessories | Battery-support, sleeve and spacer quantities and positions; use of the box/lid, potting tubes and older camera mount |

## File integrity

[manifest.json](manifest.json) records each source file's relative path, size, SHA-256, published location and BOM associations. Three reference files are stored in ZIP; all other files are preserved byte for byte. Duplicate drawings remain in their original folders and are identified in the index.
