# Electrical wiring

[Project home](../../README.md) · [简体中文](README.zh-CN.md)

The wiring package covers the battery enclosure and the equipment enclosure's motor and signal interfaces. The 2026-11-18 Rev B system register retains 74 connection records, 17 MCU mappings and 44 harness groups, and adds 10 terminal allocation groups. Detailed instructions and tables are currently in Chinese.

- [System wiring and verification guide](system-wiring.zh-CN.md), [three-page PDF](diagrams/system-wiring.pdf), [power SVG](diagrams/system-power.svg), [signal SVG](diagrams/system-signals.svg), [terminal SVG](diagrams/system-terminal-allocation.svg)
- [System workbook](system-wiring.xlsx), [connections](system-connections.csv), [MCU map](mcu-signal-map.csv), [harness register](system-harness.csv), [terminal allocation](system-terminal-allocation.csv)
- [EC-07 revision checklist](../pcb/assembly/revision-checklist.zh-CN.md)

System drawings distinguish functional relationships, source-code mappings and unresolved physical wiring. MCU GPIOs are not board-connector pin numbers. The NX UART mapping was cross-checked against the supplied carrier-board manual; its fourth pin is 5 V and is excluded from the documented three-wire serial connection. Internal power distribution and actual cable terminations remain unverified.

- [Equipment enclosure wiring](equipment-wiring.zh-CN.md), [three-page PDF](diagrams/equipment-wiring.pdf), [panel SVG](diagrams/equipment-panel.svg), [circuit SVG](diagrams/equipment-circuits.svg), [terminal SVG](diagrams/equipment-terminals.svg)
- [Equipment interface workbook](equipment-wiring.xlsx), [connector CSV](equipment-connectors.csv), [pinout CSV](equipment-pinout.csv)

- [Battery wiring guide](battery-wiring.zh-CN.md)
- [Editable SVG diagram](diagrams/battery-wiring.svg) and [PDF drawing](diagrams/battery-wiring.pdf)
- [Connector and harness workbook](battery-wiring.xlsx), [pinout CSV](battery-pinout.csv), [harness CSV](battery-harness.csv)
- [Battery CAN protocol notes](battery-can.zh-CN.md) and [original references](references/battery/README.md)

Main power pins 1/2 are battery positive and 3/4 negative. Each same-polarity pair is stripped, twisted and soldered to its respective pole on one LCB60 mating plug; the author confirms that one discharge socket is sufficient. All labels reading 24V mean direct battery supply varying with charge (supplier range 16.8–25.2 V), not a regulated 24 V rail. Pressure sensors take power from EC-07 and communicate through UART8, a serial-to-RS-485 module and the 20P block. The final EDA design has removed R12; the old HTML remains historical evidence.

The 20P block allocates four positions each to supply, ground, 485A and 485B. Each four-position group uses its own 4P link, isolated from the other groups. Two separate PLC positions and two separate CAN positions complete the block; their signal pairs must not be shorted. Position order is freely chosen and recorded by the builder. The 18P block allocates three positions each to supply, ground and independent PWM outputs, leaving nine free. PWM10/11/12 correspond to PH11/PH12/PI0; lamp-location mapping remains open. The default SUB firmware supports joystick control and switches all three lamps through one shared brightness state.

The drawings describe logical interconnections and locations; they do not establish connector mating-face orientation. CAN reference grounding, internal controllers, EC-07 physical terminals, remaining protection paths and the programming-port pinout remain open. No hardware continuity, charging, flashing or communication tests have been performed for this documentation update.
