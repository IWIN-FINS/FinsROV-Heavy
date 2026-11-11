<p align="right"><strong>English</strong> · <a href="README.zh-CN.md" lang="zh-CN">简体中文</a></p>

![Front-left view of FinsROV-Heavy, with the camera between the yellow buoyancy blocks and thrusters inside the open frame.](media/finsrov-heavy-hero.png)

# FinsROV-Heavy

FinsROV-Heavy is the open-frame remotely operated vehicle (ROV) used in our underwater inertial odometry experiments. Four horizontal and four vertical thrusters provide propulsion. A RoboMaster Type A controller sends time-stamped IMU readings, depth readings from four pressure sensors, and measured thruster speeds to an onboard Jetson Orin NX.

## Build guide

Start with the [illustrated build tutorials](docs/README.md): parts → frame → power board → thrusters and ESCs → pressure sensors → Jetson → bring-up. Detailed instructions are currently in Chinese, with original photographs and downloadable reference files.

[Start building](docs/README.md) · [Jetson scripts](software/jetson/README.md) · [Remaining documentation gaps](docs/build/07-bring-up.zh-CN.md)

## Hardware files

| Assembly | CAD model | Bill of materials |
| --- | --- | --- |
| **Vehicle body** — frame, enclosures, thrusters, buoyancy blocks, camera, lights and external sensors | [Download STEP · 9.7 MiB](hardware/cad/主体装配.step?raw=true) | [Preview CSV](hardware/bom/BOM.csv) · [Download Excel](hardware/bom/BOM.xlsx?raw=true) |
| **Electronics enclosure** — controller, onboard computer, power distribution, speed controllers, connectors and mounting hardware | [Download zipped STEP · 26.2 MiB](hardware/cad/舱内装配.step.zip?raw=true) | [Preview CSV](hardware/bom/BOM-electronics.csv) · [Download Excel](hardware/bom/BOM-electronics.xlsx?raw=true) |

Both bills of materials (BOMs) are in Chinese. The body BOM lists quantities per vehicle, and the electronics BOM lists quantities per enclosure.

### Fabrication drawings and part models

[Mechanical fabrication guide](hardware/mechanical/README.md) · [All 65 source files](hardware/mechanical/FILES.md)

Find CNC end caps, frame plates, buoyancy blocks, FDM mounts and internal mounting parts by BOM ID. The guide identifies matching models, older references and unresolved revision differences. Read it before requesting fabrication.

### Power protection board (EC-07)

The LM5069 board provides soft start and overcurrent protection. Use the EasyEDA project for the editable design and the ZIP for bare PCB fabrication. The ZIP contains Gerber and drill files. An interactive assembly BOM is also available. Resolve the R12 revision discrepancy and export placement files from the matching design before ordering assembly.

[Open the EasyEDA project](https://oshwhub.com/gan_ju/lm5069-dian-yuan-huan-qi-dong-yu-guo-liu-bao-hu-ban) · [Download PCB fabrication files](hardware/pcb/PowerBoard.zip?raw=true) · [Assembly guide and interactive BOM](docs/build/03-power-board.zh-CN.md)

## Embedded firmware

| Version | Use |
| --- | --- |
| [SUB](firmware/SUB/) | Normal vehicle operation |
| [Inertial odometry](firmware/inertial-odometry/) | Inertial odometry experiments and expanded sensor/actuator telemetry |

Each version records its FineSUB source commit and pins its dependencies. See the build instructions and host protocol settings before selecting a version. [Firmware guide](firmware/README.md)

FineSUB firmware uses the MPL-2.0 licenses included in the two source directories. Third-party components carry their own license notices. [Firmware licensing](firmware/README.md#license)

## Jetson software

[Control bridge, video streaming and startup scripts](software/jetson/README.md) are included for the SUB firmware. Follow the [Jetson setup tutorial](docs/build/06-jetson.zh-CN.md) for Ethernet, UART, camera settings and systemd. The Windows joystick application and the host software for the inertial-odometry protocol are not included yet.

## Preparing a build

1. **Inspect the assemblies.** Open the vehicle STEP to locate external parts and their mounting points. Extract `舱内装配.step` from the ZIP to inspect the board stack and connector layout. The CAD names in the BOMs identify the corresponding parts.
2. **Group orders by process.** Select the matching files in the [fabrication guide](hardware/mechanical/README.md) and resolve revision differences. Filter the Excel column `准备方式` (preparation method). The four aluminum end caps are CNC-machined. The two identical side plates, top plate and two crossbeams are black-anodized aluminum sheet metal. Camera and light/pressure mounts, internal mounts and battery supports use FDM. The two buoyancy blocks are custom PVC foam at 0.25 g/cm³. Each row lists the available supplier or fabrication link.
3. **Reconcile quantities before ordering.** Electronics rows `REF-01` through `REF-04` refer to parts already counted in the body BOM. The four flange kits together include four face seals and eight radial seals. Check rows marked `待核` (to be confirmed) for missing dimensions, material choices or supplier part numbers before requesting a quote.
4. **Adjust ballast and trim.** The vehicle is positively buoyant before ballast is fitted. Purchase 200 g blocks as needed; the typical setup uses 4–5 blocks, mounted with bore spacers and M4 screws. Adjust the quantity in water for the actual payload. [Ballast instructions](hardware/mechanical/README.md#ballast-and-trim)
