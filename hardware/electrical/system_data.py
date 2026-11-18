"""Evidence-backed electrical register for SYS-01 Rev A.

Run from any directory. Generates JSON/CSV only; PDF and Excel consume the JSON.
MCU pin mappings describe the SUB snapshot, never connector-face pin positions.
"""
from pathlib import Path
import csv
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
SOURCES = {
    "EQ": "hardware/electrical/equipment-wiring.zh-CN.md",
    "BAT": "hardware/electrical/battery-wiring.zh-CN.md",
    "NX": "docs/reference/达妙科技DM-ORIN NX V2.X使用说明书V1.0.pdf",
    "JET": "docs/build/06-jetson.zh-CN.md",
    "TASK": "firmware/SUB/Interface/Examples/TaskSUB.cpp",
    "BOARD": "firmware/SUB/BSP/Robomaster_A/Robomaster_A.h",
    "UART": "firmware/SUB/BSP/Robomaster_A/Core/Src/usart.c",
    "UART_IO": "firmware/inertial-odometry/BSP/Robomaster_A/Core/Src/usart.c",
    "TIM": "firmware/SUB/BSP/Robomaster_A/Core/Src/tim.c",
    "LIGHT": "firmware/SUB/Devices/FillLight/SUBLAB_FillLight.hpp",
    "THR": "docs/build/04-thrusters.zh-CN.md",
    "PWR": "docs/build/03-power-board.zh-CN.md",
}

# Fields: ID, harness, signal, from, to, evidence status, source IDs, remaining work.
CONNECTIONS = []
def add(harness, signal, origin, destination, status, sources, missing):
    CONNECTIONS.append([f"W-SYS-{len(CONNECTIONS)+1:03}", harness, signal,
                        origin, destination, status, sources, missing])

add("H-SYS-PWR", "放电回路", "BAT-01 放电引线", "J-BAT-PWR 四芯母座", "功能确认", "BAT", "两组放电引线分配、四芯针序及每芯电流")
add("H-SYS-PWR", "主供电", "J-BAT-PWR", "P-PWR 设备舱电源穿舱位置", "功能确认", "BAT;EQ", "外缆两端针序、线径、长度及密封件")
add("H-SYS-PWR", "保护板输入", "P-PWR", "EC-07 输入端待核", "待核", "PWR;EQ", "输入/输出端名称、极性和实际连接路径")
for key, label in [("ESC1", "四合一电调 1"), ("ESC2", "四合一电调 2"), ("NX", "NX 载板 XT30"), ("MCU", "RoboMaster A 供电端"), ("PRS", "四只水压计 24V/GND"), ("EXT", "两只云台舵机 24V/GND"), ("LGT", "三只灯 24V/GND"), ("PLC", "舱端 PLC 电源")]:
    add(f"H-SYS-P-{key}", "负载供电", "舱内供电分配待核", label, "待核", "EQ;PWR", "是否经 EC-07/稳压、支路保护、返回线、端子和负载额定值")
add("H-SYS-NX", "MCU TX → NX RX", "MCU USART3 TX / PD8", "NX U1 RX / 手册针 1", "逻辑核对", "UART;JET;NX", "MCU 板端插座针号、载板实装版及视图核对")
add("H-SYS-NX", "NX TX → MCU RX", "NX U1 TX / 手册针 2", "MCU USART3 RX / PD9", "逻辑核对", "UART;JET;NX", "MCU 板端插座针号、载板实装版及视图核对")
add("H-SYS-NX", "串口参考地", "NX U1 GND / 手册针 3", "MCU 串口 GND", "逻辑核对", "JET;NX", "MCU 板端 GND 针号；不扩展为外壳/CAN 接地结论")
add("H-SYS-IMU", "IMU 数据", "H30 TX（设备针号待核）", "MCU UART7 RX / PE7", "源码推导", "TASK;UART", "实装 H30 型号、电平、供电、物理针号和线束")
add("H-SYS-PRS", "压力串口 TX/RX", "MCU UART8 TX PE1 / RX PE0", "RS-485 收发电路（位置待核）", "源码推导", "TASK;UART", "是否板载/外置、型号、电平、方向控制和端子")
for label, address in [("LF", "0x01"), ("LB", "0x02"), ("RB", "0x03"), ("RF", "0x04")]:
    for pin, signal in [(1,"24V"),(2,"GND"),(3,"485A"),(4,"485B")]:
        add(f"H-SYS-PRS-{label}", signal, f"J-PRS-{label}:{pin}", f"水压计 {address} 的 {signal} 引线", "功能确认", "EQ", "传感器端针号/颜色、舱内端子、端面方向、线径/长度")
for label in ["L", "R"]:
    for pin, signal in [(1,"24V"),(2,"GND"),(3,"485A"),(4,"485B")]:
        add(f"H-SYS-EXT-{label}", signal, f"J-EXT-{label}:{pin}", f"云台舵机的 {signal} 引线", "功能确认", "EQ", "两轴对应、舵机型号/地址、RS-485 分组/端子与线束")
for label in ["LF", "GM", "RF"]:
    for pin, signal in [(1,"24V"),(2,"GND"),(3,"PWM")]:
        add(f"H-SYS-LGT-{label}", signal, f"J-LGT-{label}:{pin}", f"补光灯的 {signal} 引线", "功能确认", "EQ", "灯具端定义、PWM 通道对应/电平、线径/长度及供电")
for pin, signal, batpin in [(1,"CAN_H",3),(2,"CAN_L",4)]:
    add("H-SYS-CAN", signal, f"J-BAT-SVC:{batpin}", f"J-CAN:{pin}", "功能确认", "BAT;EQ", "实际外缆/端面视图、终端、参考地与支线长度")
add("H-SYS-CAN-IN", "CAN_H / CAN_L", "J-CAN:1/2", "舱内 CAN 控制器待核", "待核", "EQ", "不能默认接 NX 或 MCU；控制器、波特率与终端待核")
for pin, signal in [(1,"PLC_L1"),(2,"PLC_L2")]:
    add("H-SYS-PLC", signal, f"J-PLC:{pin}", "系缆对应芯线", "功能确认", "EQ", "两端 PLC 端子、芯数、屏蔽、供电方式及线束")
add("H-SYS-LAN", "以太网", "舱端 PLC 网口", "NX 载板以太网口", "逻辑核对", "JET", "载板板端针号、网线规格与实际转接")
add("H-SYS-SHORE", "以太网", "PC 网口", "岸端 PLC 网口", "逻辑核对", "JET", "岸端板型号/供电、网线与系缆连接")
add("H-SYS-CAM", "USB", "外置双目相机经 P-CAM", "NX USB 接口", "逻辑核对", "JET;EQ", "USB 端口、穿舱件及实际相机电缆，不编造逐针延长线")
add("H-SYS-DBG", "烧写", "J-DBG", "MCU 调试接口待核", "待核", "EQ", "烧写器、接口型号、针序及是否引出复位/VREF")

# Physical motor -> ESC/output -> SUB software channel -> STM32 GPIO.
MOTORS = [(1,2,2,3,"PI6"),(2,1,2,7,"PA1"),(3,1,4,5,"PA3"),(4,2,1,4,"PI5"),
          (5,2,3,2,"PI7"),(6,1,3,6,"PA2"),(7,1,1,8,"PA0"),(8,2,4,1,"PI2")]
for motor, esc, output, channel, gpio in MOTORS:
    add(f"H-SYS-DS-M{motor}", f"DShot 通道 {channel}", f"MCU {gpio}", f"ESC{esc} 输出组 {output} 对应控制输入", "源码推导", "TASK;BOARD;THR", "电调输入端名称、转接板 EC-08/09 逐针网络和信号地")
    add(f"H-SYS-M{motor:02}", "三相线（同组）", f"ESC{esc} 电机输出组 {output}", f"J-M{motor:02} → M{motor}", "功能确认", "EQ;THR", "转接板针脚、三根相线不固定相序、端面视图及裁线长度")

MCU = [
    ["NX 接收", "USART3 RX", "PD9", "NX U1 TX / 手册针 2", "SUB 115200；实验版 460800；8N1", "UART;UART_IO;JET;NX", "板端端子与实装载板待核"],
    ["NX 发送", "USART3 TX", "PD8", "NX U1 RX / 手册针 1", "同一固件两端波特率一致", "UART;JET;NX", "板端端子与实装载板待核"],
    ["H30 接收", "UART7 RX", "PE7", "H30 TX", "921600 / 8N1", "TASK;UART", "H30 供电、电平与设备针序待核"],
    ["H30 发送资源", "UART7 TX", "PE8", "未确认需要连接", "仅 MCU 复用配置；非实装连接证据", "UART", "不额外要求增加该导线"],
    ["压力接收", "UART8 RX", "PE0", "RS-485 收发电路", "115200 / 8N1；地址 01–04", "TASK;UART", "收发电路/方向控制/端子待核"],
    ["压力发送", "UART8 TX", "PE1", "RS-485 收发电路", "115200 / 8N1；地址 01–04", "TASK;UART", "PE0/PE1 不是 485A/485B"],
]
for motor, esc, output, channel, gpio in MOTORS:
    MCU.append([f"电机 M{motor}", f"DShot {channel}", gpio, f"ESC{esc} / 输出组{output}", "GPIO 双向 DShot；非 PWM 索引", "TASK;BOARD;THR", "物理控制端子和信号地待核"])
for name, channel, gpio, tim in [("L1",10,"PH11","TIM5_CH2"),("L2",11,"PH12","TIM5_CH3"),("L3",12,"PI0","TIM5_CH4")]:
    MCU.append([f"灯 {name}", f"PWM {channel} / {tim}", gpio, "三只灯的 PWM；位置对应待核", "驱动设 50 Hz、1100–1900 µs；非实测", "TASK;BOARD;TIM;LIGHT", "灯具电平/极性；当前任务三灯同亮度"])

HEADERS = {
    "connections": ["连接编号","线束编号","信号","起点","终点","依据状态","来源编号","尚缺信息"],
    "mcu": ["功能","外设/软件索引","MCU 引脚","逻辑对端","源码配置","来源编号","物理限制"],
    "harness": ["线束编号","范围","线径 mm²","成品长度 mm","测量起止点","线色/端子","记录/验证","来源编号"],
}
def source_record(path):
    raw=(ROOT/path).read_bytes()
    policy="binary" if Path(path).suffix==".pdf" else "text-lf"
    if policy=="text-lf":
        raw=raw.replace(b"\r\n",b"\n").replace(b"\r",b"\n")
    return {"path":path,"hash_policy":policy,"sha256":hashlib.sha256(raw).hexdigest()}

def build():
    harness = []
    for key in dict.fromkeys(row[1] for row in CONNECTIONS):
        rows = [r for r in CONNECTIONS if r[1] == key]
        harness.append([key, "; ".join(dict.fromkeys(r[2] for r in rows)), "待测", "待测", "待定义", "待记录", "未进行导通/上电验证", ";".join(sorted(set(s for r in rows for s in r[6].split(';'))))])
    return {
        "revision":"SYS-01 Rev A", "date":"2026-11-18", "firmware_baseline":"SUB aebf944b803303c2d26dd1476c9a3496fb3a9a91",
        "source_note":"逻辑图与核验台账，不是可直接裁线下单的定版线束图；源码引脚不等于连接器针号。",
        "sources": {k:source_record(v) for k,v in SOURCES.items()},
        "headers": HEADERS, "connections":CONNECTIONS,"mcu":MCU,"harness":harness,"motors":MOTORS,
    }

if __name__ == "__main__":
    data = build()
    (HERE/"system-wiring.json").write_text(json.dumps(data,ensure_ascii=False,indent=2)+"\n",encoding="utf-8",newline="\n")
    for key, name in [("connections","system-connections.csv"),("mcu","mcu-signal-map.csv"),("harness","system-harness.csv")]:
        with (HERE/name).open("w",encoding="utf-8-sig",newline="") as f:
            writer=csv.writer(f,lineterminator="\n"); writer.writerow(HEADERS[key]); writer.writerows(data[key])
    print({k:len(data[k]) for k in HEADERS})
