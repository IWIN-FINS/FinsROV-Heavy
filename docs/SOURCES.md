# Documentation sources and changes

[Build guide](README.md) · [制作教程](README.zh-CN.md)

The project author supplied a local export named **V5开源文档**, dated 2026-11-11. This release reorganizes its five substantive documents into seven build chapters. The export's administrative README and internal NAS export command are not part of the public tutorial.

| Original document / 原文 | Published coverage / 对应章节 |
| --- | --- |
| 主体框架搭建 | [Frame assembly](build/02-frame.zh-CN.md) |
| 电源管理板焊接 | [Power board](build/03-power-board.zh-CN.md) |
| 电机电调文档 | [Thrusters and ESCs](build/04-thrusters.zh-CN.md) |
| V5潜器设计与设备选型 | [Parts and revisions](build/01-overview.zh-CN.md), thrusters, [pressure sensors](build/05-pressure-sensors.zh-CN.md) |
| ORIN NX配置（ORIN NANO同样适用 | [Jetson setup](build/06-jetson.zh-CN.md), [bring-up](build/07-bring-up.zh-CN.md) |

## Preserved and adapted files

- All **28 original images** are under `assets/`, grouped by source document. They are preserved byte-for-byte. Historical screenshots and partially assembled photographs are labelled as references.
- The **interactive PCB BOM**, **two vendor software archives**, **one vendor PDF** and **one demonstration video** are preserved byte-for-byte. Download entries are in [the reference index](reference/README.md) and [PCB assembly](../hardware/pcb/assembly/README.md).
- The **three Jetson script attachments** are published with specific fixes documented in [software/jetson](../software/jetson/README.md). The systemd unit and offline tests are new.
- [source-manifest.json](source-manifest.json) records original relative filenames and SHA-256 hashes, along with published paths, sizes, hashes and change flags. The five source articles and the export README are recorded by hash; their prose is reorganized rather than republished as duplicate tutorials.

## Evidence and corrections

Current configuration is checked against the released CAD/BOM, the author's fabrication confirmations and the pinned SUB firmware source. The original document's planned 200 m working depth, 300 m cable, 4K camera and arm are not asserted as validated specifications. The foam's 250 m rating remains a material parameter.

The frame tutorial supplies four additional fastener quantities, now recorded as `HW-06`–`HW-09`. Their counts are installation quantities for those steps, subject to reconciling kit contents. Other unresolved counts remain blank. The tutorial's eight motor cable clamps are explicitly distinguished from the existing four clamp-body STEP instances.

The power-board tutorial and interactive BOM disagree about R12. Both pieces of evidence are recorded; the source HTML and Gerber were not altered. Frame hole corrections, cable-cut lengths, host application files and complete sealing instructions remain on the [open-items list](build/07-bring-up.zh-CN.md#待补资料).

Jetson instructions correct a malformed systemd block, distinguish Orin NX from Nano encoding, explain UART device permissions and state the actual SUB light-control behavior. Upstream references are linked at the relevant steps. The offline tests do not establish hardware operation or underwater performance.

## Third-party material

Vendor tools/manuals and notices embedded in the interactive BOM retain their original ownership and terms; the repository's root license does not override them. The generic thruster diagram in `assets/design/image_04.png` was marked as an internet reference in the source notes. Its watermark is retained, its original article URL was not supplied, and its numbering is not used for this vehicle. No third-party executable was run during this documentation import.
