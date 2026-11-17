# Electrical wiring

[Project home](../../README.md) · [简体中文](README.zh-CN.md)

The wiring package covers the battery enclosure and the equipment enclosure's motor and signal interfaces, based on the author's confirmations and supplied files dated 2026-11-17. Detailed instructions and tables are currently in Chinese.

- [Equipment enclosure wiring](equipment-wiring.zh-CN.md), [two-page PDF](diagrams/equipment-wiring.pdf), [panel SVG](diagrams/equipment-panel.svg), [circuit SVG](diagrams/equipment-circuits.svg)
- [Equipment interface workbook](equipment-wiring.xlsx), [connector CSV](equipment-connectors.csv), [pinout CSV](equipment-pinout.csv)

- [Battery wiring guide](battery-wiring.zh-CN.md)
- [Editable SVG diagram](diagrams/battery-wiring.svg) and [PDF drawing](diagrams/battery-wiring.pdf)
- [Connector and harness workbook](battery-wiring.xlsx), [pinout CSV](battery-pinout.csv), [harness CSV](battery-harness.csv)
- [Battery CAN protocol notes](battery-can.zh-CN.md) and [original references](references/battery/README.md)

Solid connections identify confirmed signal functions; dashed connections mark unresolved wiring. The drawings are logical interconnections and location sketches, not connector mating-face pin maps or dimensioned machining drawings. The battery CAN connection now maps battery pins 3/4 to equipment J-CAN pins 1/2. Main-power assignments, CAN reference grounding, internal controller connections and the programming-port pinout remain open. No hardware continuity, charging, flashing or communication tests have been performed for this documentation update.
