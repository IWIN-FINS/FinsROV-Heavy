"""Render SYS-01 JSON to two editable SVG sheets and an A3 landscape PDF.

Uses the existing equipment drawings' typography, colours and SVG/ReportLab
coordinate convention. Requires reportlab; FINS_PDF_FONT overrides the CJK font.
Run system_data.py first after changing source records.
"""
from pathlib import Path
import json
import os
from xml.sax.saxutils import escape
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib.colors import HexColor
from reportlab.lib.pagesizes import A3, landscape

OUT = Path(__file__).resolve().parent
DATA = json.loads((OUT.parent/"system-wiring.json").read_text(encoding="utf-8"))
W, H = 1600, 1131
INK, MUTED, BORDER, AMBER, BLUE = "#203047", "#596B80", "#B9C7D4", "#94600C", "#2467AD"
pdfmetrics.registerFont(TTFont("SYSCJK", os.environ.get("FINS_PDF_FONT", "C:/Windows/Fonts/msyh.ttc")))
PDF = canvas.Canvas(str(OUT/"system-wiring.pdf"), pagesize=landscape(A3), invariant=1)
PDF.setTitle("FinsROV-Heavy system wiring - SYS-01 Rev A")
PDF.setAuthor("FinsROV-Heavy project")

class Sheet:
    def __init__(self, title, filename, page):
        self.filename = filename
        PDF.scale(landscape(A3)[0]/W, landscape(A3)[1]/H)
        self.svg=[f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}"><title>{escape(title)}</title>']
        self.rect(0, 0, W, H, fill="#FFFFFF", stroke="#FFFFFF")
        self.text(50,60,"FinsROV-Heavy",32)
        self.text(50,108,title,26)
        self.text(1260,60,DATA["revision"],18)
        self.text(1260,93,DATA["date"],18,MUTED)
        self.line([(50,135),(1550,135)],BORDER,1)
        self.text(50,1092,"来源及连接编号：system-wiring.json / system-connections.csv；未进行实机导通、上电或通信验证。",16,MUTED)
        self.text(1460,1092,f"{page} / 2",17,MUTED)
    def text(self,x,y,s,size=18,color=INK):
        self.svg.append(f'<text x="{x}" y="{y}" fill="{color}" font-family="Microsoft YaHei, Noto Sans CJK SC, sans-serif" font-size="{size}">{escape(s)}</text>')
        PDF.setFillColor(HexColor(color));PDF.setFont("SYSCJK",size);PDF.drawString(x,H-y,s)
    def rect(self,x,y,w,h,fill="#FFFFFF",stroke=BORDER,dash=False):
        self.svg.append(f'<rect x="{x}" y="{y}" width="{w}" height="{h}" rx="8" fill="{fill}" stroke="{stroke}" stroke-width="1.5"'+(' stroke-dasharray="7 5"' if dash else '')+'/>')
        PDF.setFillColor(HexColor(fill));PDF.setStrokeColor(HexColor(stroke));PDF.setLineWidth(1.5);PDF.setDash([7,5] if dash else []);PDF.roundRect(x,H-y-h,w,h,8,fill=1,stroke=1);PDF.setDash([])
    def line(self,pts,color=BLUE,width=2.5,dash=False):
        self.svg.append('<polyline points="'+' '.join(f'{x},{y}' for x,y in pts)+f'" fill="none" stroke="{color}" stroke-width="{width}"'+(' stroke-dasharray="8 6"' if dash else '')+'/>')
        PDF.setStrokeColor(HexColor(color));PDF.setLineWidth(width);PDF.setDash([8,6] if dash else []);p=PDF.beginPath();p.moveTo(pts[0][0],H-pts[0][1])
        for x,y in pts[1:]:p.lineTo(x,H-y)
        PDF.drawPath(p);PDF.setDash([])
    def box(self,x,y,w,h,title,lines,pending=False):
        self.rect(x,y,w,h,fill="#FFF7E6" if pending else "#F2F6FA",dash=pending)
        self.text(x+18,y+32,title,21,AMBER if pending else INK)
        for i,line in enumerate(lines):self.text(x+18,y+64+i*29,line,17,MUTED)
    def end(self):
        self.svg.append("</svg>");(OUT/self.filename).write_text("\n".join(self.svg)+"\n",encoding="utf-8",newline="\n");PDF.showPage()

s=Sheet("系统供电与待核边界 / Power distribution", "system-power.svg", 1)
s.text(50,178,"实线：已有功能关系。虚线：待核路径；不表示已确认共用母线、稳压输出或串联顺序。",19,AMBER)
s.box(50,230,350,170,"BAT-01 电池舱",["6S5P · 标称 21.6 V / 25 Ah", "供应商工作范围 16.8–25.2 V", "额定值不扩展到线束/插座"])
s.box(500,230,400,170,"J-BAT-PWR → P-PWR",["四芯主供电口 → 设备舱电源位置", "功能关系已确认", "针序、芯线分配及外缆规格待核"])
s.line([(400,310),(500,310)])
s.box(1040,230,510,170,"EC-07 LM5069 保护板",["输入/输出端名称与极性待核", "R12：教程不焊与 HTML 装配冲突", "缓启动/过流参数与板版待核"],True)
s.line([(900,310),(1040,310)],AMBER,dash=True)
s.text(50,447,"设备舱负载清点：下面列出需要核实的供电回路，未把所有负载接到同一输出。",20)
loads=[("P-ESC1 / P-ESC2","两块四合一电调","电源端、返回线和支路保护待核"),
       ("P-NX","NX 载板 XT30","手册输入 12–28 V；实接来源待核"),
       ("P-MCU","RoboMaster A","供电端定义和实际输入电压待核"),
       ("P-PRS","4 只水压计","面板 1=24V、2=GND；来源待核"),
       ("P-EXT / P-LGT","云台 2 路 / 灯 3 路","面板 24V/GND；分配与负载待核"),
       ("P-PLC","舱端 PLC","板卡输入端、电压与回路待核")]
for i,(code,name,note) in enumerate(loads):
    x=50+(i%3)*510;y=475+(i//3)*160
    s.box(x,y,480,135,f"{code}   {name}",[note,"见 H-SYS-"+code+"；不据名称补接线"],True)
s.box(50,835,735,175,"电池开关 / 充电",["SW-BAT 两线接电池原开关线；不画成主功率串联开关。", "J-BAT-SVC:1=充电正，2=充电负。", "充电器由作者确认为 25.2 V / 5 A；配线另见电池图。"])
s.box(815,835,735,175,"供电定版必须补齐",["主供电逐针分配 → EC-07 输入/输出 → 每路负载与返回线。", "线径、长度、端子、每芯电流、分支保护及壳体关系。", "载板内部 DC/DC 来自原手册，不代表舱内外加稳压方案。"],True)
s.end()

s=Sheet("通信与执行端对照 / Communications and actuators", "system-signals.svg", 2)
s.text(50,177,"蓝线为逻辑配对；MCU 引脚不等于板端插座针号。虚线项目尚缺物理端子、线束或总线依据。",18,AMBER)
s.box(50,210,390,190,"RoboMaster A / USART3",["PD8  TX", "PD9  RX", "串口 GND；板端针号待核"])
s.box(1110,210,440,190,"NX 载板 U1 / ttyTHS1",["手册针 1  RX（3.3 V 信号）", "手册针 2  TX（3.3 V 信号）", "手册针 3  GND；针 4 为 5V"])
for y,label in [(275,"PD8 TX → RX 1"),(317,"PD9 RX ← TX 2"),(359,"GND - GND 3")]:
    s.line([(440,y),(1110,y)]);s.text(620,y-8,label,18,BLUE)
s.text(50,433,"SUB：115200 / 8N1；实验快照：460800 / 8N1。三线通信不连接载板针 4，端面按原手册核验。",19)
s.box(50,465,475,155,"H30 / 四路压力",["UART7 RX PE7 ← H30 TX；921600", "UART8 TX PE1 / RX PE0；115200", "压力 RS-485 收发电路与端子待核"],True)
s.box(550,465,475,155,"CAN / PLC / 相机",["BAT-SVC 3/4 - J-CAN 1/2：H/L", "J-PLC 1/2：PLC_L1 / PLC_L2", "USB 相机 → NX；控制器/穿舱待核"],True)
s.box(1050,465,500,155,"云台 / 照明 / 烧写",["扩展两口均为 24V/GND/485A/485B", "灯 L1/2/3：PWM10/11/12；同亮度", "轴向、灯口对应和烧写针序待核"],True)
s.text(50,663,"八路执行链：来自现有面板定义、实装记录与 SUB 源码；EC-08/09 中间针脚仍待补。",19)
cols=[70,260,445,650,850,1080,1335]
heads=["推进器", "ESC", "输出组", "DShot 索引", "MCU 引脚", "穿舱插座", "转接板网络"]
s.rect(50,685,1500,42,fill="#203047",stroke="#203047")
for x,h in zip(cols,heads):s.text(x,713,h,18,"#FFFFFF")
for i,(motor,esc,output,ch,gpio) in enumerate(DATA["motors"]):
    y=727+i*35;s.rect(50,y,1500,35,fill="#F2F6FA" if i%2==0 else "#FFFFFF",stroke="#E6ECF1")
    for x,value in zip(cols,[f"M{motor}",str(esc),str(output),str(ch),gpio,f"J-M{motor:02}","EC-08/09 待核"]):s.text(x,y+24,value,17)
s.text(50,1043,"三相线同组、不固定相序；实际旋向在电调中调整后核对。DShot 索引与 PWM 索引不是同一编号体系。",17,MUTED)
s.end()
PDF.save()
print("Generated system-power.svg, system-signals.svg and system-wiring.pdf")
