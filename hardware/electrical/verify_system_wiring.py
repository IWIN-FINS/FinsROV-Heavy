"""Read-only verification of generated tables and the SUB-source pin mappings.

Run after system_data.py, render_system_wiring.py and build_system_workbook.mjs.
Uses only Python's standard library. It does not contact or energize hardware.
"""
from pathlib import Path
from xml.etree import ElementTree as ET
from zipfile import ZipFile
import csv
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[1]
data=json.loads((HERE/"system-wiring.json").read_text(encoding="utf-8"))
for code,source in data["sources"].items():
    raw=(ROOT/source["path"]).read_bytes()
    if source["hash_policy"]=="text-lf":
        raw=raw.replace(b"\r\n",b"\n").replace(b"\r",b"\n")
    actual=hashlib.sha256(raw).hexdigest()
    assert actual==source["sha256"],f"Source changed: {code}; review and regenerate"
for key,name in [("connections","system-connections.csv"),("mcu","mcu-signal-map.csv"),("harness","system-harness.csv"),("terminals","system-terminal-allocation.csv")]:
    with (HERE/name).open(encoding="utf-8-sig",newline="") as file: rows=list(csv.reader(file))
    assert rows==[[str(cell) for cell in row] for row in [data["headers"][key]]+data[key]],f"CSV mismatch: {name}"
ids=[row[0] for row in data["connections"]]
assert len(ids)==len(set(ids)),"Duplicate connection ID"
harness={row[0] for row in data["harness"]}
for row in data["connections"]:
    assert row[1] in harness
    assert row[5] in {"功能确认","逻辑核对","源码推导","待核"}
    assert row[7],f"Missing verification scope: {row[0]}"
    assert all(source in data["sources"] for source in row[6].split(";"))

# Allocation counts describe functions, not physical position numbers.
terminal_rows=data["terminals"]
assert len({row[0] for row in terminal_rows})==len(terminal_rows)==10
for block,total in [("20P 压力转接",20),("18P 灯转接",18)]:
    assert sum(row[3] for row in terminal_rows if row[1]==block)==total,block
for row in terminal_rows:
    assert isinstance(row[3],int) and row[3]>0
    assert "不是针号" in row[5] and "未导通验证" in row[7]
    assert all(source in data["sources"] for source in row[6].split(";"))
    if row[0] in {"T-20-PLC","T-20-CAN","T-18-PWM"}:
        assert "禁止" in row[4] and "短接" in row[4],row[0]
    elif row[1]=="20P 压力转接":
        assert row[3]==4 and "一件 4P" in row[4] and "相互独立" in row[4]

# Confirm MCU mappings against actual firmware arrays, not a second copied map.
task=(ROOT/data["sources"]["TASK"]["path"]).read_text(encoding="utf-8")
board=(ROOT/data["sources"]["BOARD"]["path"]).read_text(encoding="utf-8")
portbody=re.search(r"BSP_DHOSTPortList[^=]*=\s*\{(.*?)\};",board,re.S).group(1)
pinbody=re.search(r"BSP_DHOSTPinList[^=]*=\s*\{(.*?)\};",board,re.S).group(1)
ports=re.findall(r"GPIO([A-K])",portbody)
pins=[int(n) for n in re.findall(r"GPIO_PIN_(\d+)",pinbody)]
for motor,esc,output,index,gpio in data["motors"]:
    assert int(re.search(rf"#define M{motor}\s+(\d+)",task).group(1))==index
    assert f"P{ports[index-1]}{pins[index-1]}"==gpio
    existing=(HERE/"equipment-wiring.zh-CN.md").read_text(encoding="utf-8")
    assert re.search(rf"\| J-M{motor:02} \| M{motor} \| {esc} \| {output} \| {index} \|",existing)
uart=(ROOT/data["sources"]["UART"]["path"]).read_text(encoding="utf-8")
uart_io=(ROOT/data["sources"]["UART_IO"]["path"]).read_text(encoding="utf-8")
assert re.search(r"huart3.Init.BaudRate\s*=\s*115200",uart)
assert re.search(r"huart3.Init.BaudRate\s*=\s*460800",uart_io)
for row in data["mcu"][:6]:
    peripheral=row[1].replace(" ","_")
    assert re.search(rf"{row[2]}\s+------>\s+{peripheral}",uart),row
tim=(ROOT/data["sources"]["TIM"]["path"]).read_text(encoding="utf-8")
pwmbody=re.search(r"BSP_PWMList[^=]*=\s*\{(.*?)\};",board,re.S).group(1)
pwm_entries=re.findall(r"\{([^{}]+)\}",pwmbody)
for row in data["mcu"][-3:]:
    lamp=row[0].split()[-1]
    index=int(re.search(r"PWM (\d+)",row[1]).group(1))
    timer,channel=re.search(r"(TIM\d+)_CH(\d+)",row[1]).groups()
    assert int(re.search(rf"#define {lamp}\s+(\d+)",task).group(1))==index
    assert f"TIM_CHANNEL_{channel}" in pwm_entries[index] and f"&h{timer.lower()}" in pwm_entries[index]
    assert re.search(rf"{row[2]}\s+------>\s+{timer}_CH{channel}",tim)

# Read exported XLSX values, filters and panes using OOXML; no rewriting.
NS={"s":"http://schemas.openxmlformats.org/spreadsheetml/2006/main"}
with ZipFile(HERE/"system-wiring.xlsx") as z:
    strings=[]
    if "xl/sharedStrings.xml" in z.namelist():
        strings=["".join(n.itertext()) for n in ET.fromstring(z.read("xl/sharedStrings.xml"))]
    for num,key in enumerate(["connections","mcu","harness","terminals"],1):
        sheet=ET.fromstring(z.read(f"xl/worksheets/sheet{num}.xml"))
        values={}
        for cell in sheet.findall(".//s:sheetData/s:row/s:c",NS):
            value=cell.find("s:v",NS)
            if cell.get("t")=="s":text=strings[int(value.text)]
            elif cell.get("t")=="inlineStr":text="".join(cell.find("s:is",NS).itertext())
            else:text=value.text if value is not None else ""
            values[cell.get("r")]=text
        for i,row in enumerate([data["headers"][key]]+data[key],5):
            for j,expected in enumerate(row):
                assert values.get(f"{chr(65+j)}{i}","")==str(expected),f"XLSX {key} {i}/{j}"
        assert sheet.find(".//s:pane",NS) is not None, f"Missing frozen panes: {key}"
    assert len([n for n in z.namelist() if re.fullmatch(r"xl/tables/table\d+\.xml",n)])==4
for svg in ["system-power.svg","system-signals.svg","system-terminal-allocation.svg"]:
    ET.parse(HERE/"diagrams"/svg)
print(f"PASS: {len(ids)} connections, {len(data['mcu'])} MCU mappings, {len(harness)} harness groups, {len(terminal_rows)} terminal groups; CSV/XLSX parity, provenance, source GPIOs and SVG XML.")
