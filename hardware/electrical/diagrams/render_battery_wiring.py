"""Render the editable SVG and A3 landscape PDF. Requires reportlab.

Run: python render_battery_wiring.py
For non-Windows hosts, set FINS_PDF_FONT to a TrueType font with Chinese glyphs.
The source uses logical signal ports, never physical connector pin positions.
"""
from pathlib import Path
import os
from xml.sax.saxutils import escape
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib.colors import HexColor
from reportlab.lib.pagesizes import A3, landscape

OUT = Path(__file__).resolve().parent
W,H = 1600,1131
INK='#162235'; MUTED='#556579'; LINE='#B8C4CF'; AMBER='#966000'
RED='#B6373F'; GREEN='#18734A'; BLUE='#2467AC'; GRAY='#5E6B7B'
font_path = os.environ.get('FINS_PDF_FONT', 'C:/Windows/Fonts/msyh.ttc')
pdfmetrics.registerFont(TTFont('FinsCJK', font_path))
c=canvas.Canvas(str(OUT/'battery-wiring.pdf'),pagesize=landscape(A3))
c.setTitle('FinsROV-Heavy battery wiring - BATT-01 Rev C')
c.setAuthor('FinsROV-Heavy project')
c.scale(landscape(A3)[0]/W,landscape(A3)[1]/H)
svg=[f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}">', '<title>FinsROV-Heavy 电池舱逻辑接线 BATT-01 Rev C</title>', '<desc>主供电1/2正、3/4负，同极性两线并到一个LCB60；不并联电池两口。图中顺序不表示物理针位。</desc>']

def rect(x,y,w,h,fill='#FFFFFF',stroke=LINE,r=8,dash=False):
    svg.append(f'<rect x="{x}" y="{y}" width="{w}" height="{h}" rx="{r}" fill="{fill}" stroke="{stroke}" stroke-width="1.5"'+(' stroke-dasharray="8 6"' if dash else '')+'/>')
    c.setFillColor(HexColor(fill));c.setStrokeColor(HexColor(stroke));c.setLineWidth(1.5);c.setDash([8,6] if dash else [])
    c.roundRect(x,H-y-h,w,h,r,stroke=1,fill=1);c.setDash([])

def text(x,y,s,size=18,color=INK,bold=False):
    svg.append(f'<text x="{x}" y="{y}" fill="{color}" font-family="Microsoft YaHei, Noto Sans CJK SC, sans-serif" font-size="{size}" font-weight="{700 if bold else 400}">{escape(s)}</text>')
    c.setFillColor(HexColor(color));c.setFont('FinsCJK',size);c.drawString(x,H-y,s)

def line(points,color=GRAY,dash=False,width=2.6):
    svg.append('<polyline points="'+' '.join(f'{x},{y}' for x,y in points)+f'" fill="none" stroke="{color}" stroke-width="{width}"'+(' stroke-dasharray="9 7"' if dash else '')+'/>')
    c.setStrokeColor(HexColor(color));c.setLineWidth(width);c.setDash([9,7] if dash else []);p=c.beginPath();p.moveTo(points[0][0],H-points[0][1])
    for x,y in points[1:]:p.lineTo(x,H-y)
    c.drawPath(p);c.setDash([])

def port(x,y,color=GRAY):
    svg.append(f'<circle cx="{x}" cy="{y}" r="4" fill="white" stroke="{color}" stroke-width="2"/>')
    c.setFillColor(HexColor('#FFFFFF'));c.setStrokeColor(HexColor(color));c.setLineWidth(2);c.circle(x,H-y,4,stroke=1,fill=1)

rect(0,0,W,H,stroke='#FFFFFF',r=0)
text(50,64,'FinsROV-Heavy',32,bold=True)
text(50,104,'电池舱逻辑接线 / Battery enclosure wiring',26)
text(1190,60,'BATT-01  /  Rev C',20,bold=True)
text(1190,91,'2026-11-18  ·  电池舱部分',18,MUTED)
line([(50,130),(1550,130)],LINE,width=1)
text(50,165,'电池舱内 / BAT-01',19,bold=True)
text(700,165,'舱盖三孔 / 功能分组',19,bold=True)
text(1220,165,'舱外连接',19,bold=True)
rect(50,185,370,655,fill='#F4F7FA')
rect(670,185,400,655,fill='#F4F7FA')
text(75,222,'三星 21700-50S · 6S5P',21,bold=True)
text(75,253,'21.6 V / 25 Ah · 满充 25.2 V',18)

text(75,301,'原开关线 A（资料标识）',18)
text(75,336,'原开关线 B（资料标识）',18)
for y in (300,335):
    line([(420,y),(700,y)]);port(420,y);port(700,y)
text(445,284,'H-BAT-01 · 两线对应',16,MUTED)
rect(700,266,340,88)
text(718,290,'SW-BAT  电池开关',19,bold=True)
text(718,316,'约 Ø10 mm 光孔（非攻丝孔）',17)
text(718,340,'焊接或经 2P 接头，动作待核',17,MUTED)

text(75,405,'单个匹配 LCB60 放电口',19,bold=True)
text(75,450,'正端：两根正极线拧合焊接',18,RED)
text(75,490,'负端：两根负极线拧合焊接',18,GRAY)
text(75,527,'照片两口不并联；一个口够用',17,MUTED)
rect(700,390,340,145)
text(718,420,'J-BAT-PWR  主供电',19,bold=True)
text(718,453,'1 / 2   BAT+  电池正极',18,RED)
text(718,493,'3 / 4   BAT-  电池负极',18,GRAY)
text(718,522,'4 芯母座公缆 · Ø12.6 mm',16,MUTED)
for y,color in [(450,RED),(490,GRAY)]:
    line([(420,y),(700,y)],color);port(420,y,color);port(700,y,color)
text(445,430,'H-BAT-02 · 同极性并线',16,MUTED)
rect(1220,390,330,145,dash=True)
text(1240,420,'主舱供电入口',20,bold=True)
text(1240,450,'电池直供 16.8-25.2 V',18)
text(1240,482,'具体接点 / 保护路径待核',17,AMBER)
text(1240,516,'不是稳压 24 V',17,MUTED)
for y,color in [(450,RED),(490,GRAY)]:line([(1040,y),(1220,y)],color,True)
text(1085,430,'H-BAT-07',15,AMBER)

text(75,566,'充电口',19,bold=True)
text(75,596,'正极 CHG+',18,RED)
text(75,641,'负极 CHG-',18,GRAY)
text(75,683,'CAN 通信引线',19,bold=True)
text(75,716,'CAN_H（照片标签：绿 H）',17,GREEN)
text(75,761,'CAN_L（照片标签：蓝 L）',17,BLUE)
text(75,811,'CAN 参考地：去向未确认',17,AMBER)

rect(700,550,340,260)
text(718,578,'J-BAT-SVC  1W4PIN',21,bold=True)
for y,pin,signal,color in [(610,1,'CHG+',RED),(655,2,'CHG-',GRAY),(725,3,'CAN_H',GREEN),(770,4,'CAN_L',BLUE)]:
    line([(420,y),(700,y)],color);port(420,y,color);port(700,y,color)
    line([(700,y),(745,y)],color);text(762,y+6,f'{pin}   {signal}',20,color)
    line([(962,y),(1040,y)],color);port(1040,y,color)
text(445,590,'H-BAT-03 · 充电',16,MUTED)
text(445,705,'H-BAT-04 · CAN',16,MUTED)
line([(718,685),(1022,685)],LINE,width=1)
text(718,798,'仅为脚号列表，非端面针位排列',16,AMBER)

rect(1220,570,330,100)
text(1275,600,'充电器',20,bold=True)
text(1275,630,'25.2 V / 5 A DC',20)
text(1275,654,'型号、配插线待补',16,MUTED)
for y,signal,color in [(610,'+',RED),(655,'-',GRAY)]:
    line([(1040,y),(1220,y)],color);port(1220,y,color);text(1236,y+6,signal,20,color)
text(1085,590,'H-BAT-05',15,MUTED)
rect(1220,700,330,110)
text(1275,729,'设备舱 J-CAN',20,bold=True)
text(1275,759,'00W2PIN · 1=H / 2=L',17)
text(1275,790,'舱内控制器 / 参考地待核',17,AMBER)
for y,signal,color in [(725,'1 H',GREEN),(770,'2 L',BLUE)]:
    line([(1040,y),(1220,y)],color);port(1220,y,color);text(1233,y+6,signal,17,color)
text(1085,705,'H-BAT-06',15,MUTED)

text(50,880,'读图说明',20,bold=True)
rect(50,900,480,130,fill='#FBF7EE',stroke='#DACBA9')
text(70,928,'01  物理针位尚未绘制',19,bold=True)
text(70,958,'插座端面 / 焊线面、定位键仍待核实。',18)
text(70,986,'图中的排列顺序不能用于确定插针位置。',18)
text(70,1014,'三孔的相对位置与尺寸以机械图为准。',18)
rect(560,900,480,130,fill='#F4F7FA')
text(580,928,'02  电池接口与面板接口分开编号',19,bold=True)
text(580,958,'开关只接原开关线，不画入主功率回路。',18)
text(580,986,'只使用一个放电口，不并联两口。',18)
text(580,1014,'不补连 CHG-、CAN 地和壳体。',18)
rect(1070,900,480,130,fill='#F4F7FA')
text(1090,928,'03  导线和证据',19,bold=True)
line([(1090,952),(1140,952)],GRAY);text(1155,958,'实线：信号连接已确认',17)
line([(1090,980),(1140,980)],AMBER,True);text(1155,986,'虚线：连接细节待核',17)
text(1090,1014,'线色仅作分组；实装配色见线束表。',17)
text(50,1068,'来源：作者确认、供应商电池参数表及接口照片。完整依据、协议和待核项见 battery-wiring.zh-CN.md。',17,MUTED)
text(50,1100,'实物接线、导通、充电和 CAN 通信尚未验证。',17,AMBER)
text(1435,1100,'1 / 1',17,MUTED)
svg.append('</svg>')
(OUT/'battery-wiring.svg').write_text('\n'.join(svg)+'\n',encoding='utf-8',newline='\n')
c.showPage();c.save()
print('Created battery-wiring.svg and battery-wiring.pdf')
