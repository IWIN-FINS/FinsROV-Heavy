# Electrical wiring

[Project home](../../README.md) · [简体中文](README.zh-CN.md)

The wiring package covers the battery enclosure and the equipment enclosure's motor and signal interfaces. The 2026-11-18 system register adds 74 connection records, 17 MCU mappings and 44 harness groups with fields for physical measurements. Detailed instructions and tables are currently in Chinese.

- [System wiring and verification guide](system-wiring.zh-CN.md), [two-page PDF](diagrams/system-wiring.pdf), [power SVG](diagrams/system-power.svg), [signal SVG](diagrams/system-signals.svg)
- [System workbook](system-wiring.xlsx), [connections](system-connections.csv), [MCU map](mcu-signal-map.csv), [harness register](system-harness.csv)
- [EC-07 revision checklist](../pcb/assembly/revision-checklist.zh-CN.md)

System drawings distinguish functional relationships, source-code mappings and unresolved physical wiring. MCU GPIOs are not board-connector pin numbers. The NX UART mapping was cross-checked against the supplied carrier-board manual; its fourth pin is 5 V and is excluded from the documented three-wire serial connection. Internal power distribution and actual cable terminations remain unverified.

- [Equipment enclosure wiring](equipment-wiring.zh-CN.md), [two-page PDF](diagrams/equipment-wiring.pdf), [panel SVG](diagrams/equipment-panel.svg), [circuit SVG](diagrams/equipment-circuits.svg)
- [Equipment interface workbook](equipment-wiring.xlsx), [connector CSV](equipment-connectors.csv), [pinout CSV](equipment-pinout.csv)

- [Battery wiring guide](battery-wiring.zh-CN.md)
- [Editable SVG diagram](diagrams/battery-wiring.svg) and [PDF drawing](diagrams/battery-wiring.pdf)
- [Connector and harness workbook](battery-wiring.xlsx), [pinout CSV](battery-pinout.csv), [harness CSV](battery-harness.csv)
- [Battery CAN protocol notes](battery-can.zh-CN.md) and [original references](references/battery/README.md)

Solid connections identify confirmed signal functions; dashed connections mark unresolved wiring. The drawings are logical interconnections and location sketches, not connector mating-face pin maps or dimensioned machining drawings. The battery CAN connection now maps battery pins 3/4 to equipment J-CAN pins 1/2. Main-power assignments, CAN reference grounding, internal controller connections and the programming-port pinout remain open. No hardware continuity, charging, flashing or communication tests have been performed for this documentation update.
