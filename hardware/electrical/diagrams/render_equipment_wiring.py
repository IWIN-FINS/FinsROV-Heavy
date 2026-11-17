"""Generate two editable SVG sheets and a two-page A3 PDF from interface definitions.

Requires reportlab. Set FINS_PDF_FONT to a Chinese TrueType font on non-Windows.
The panel is a location sketch, not a mechanical or connector mating-face drawing.
"""
from pathlib import Path
import json, os
from xml.sax.saxutils import escape
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib.colors import HexColor
from reportlab.lib.pagesizes import A3, landscape

OUT=Path(__file__).resolve().parent
data=json.loads((OUT.parent/'equipment-connectors.json').read_text(encoding='utf-8'))
W,H=1600,1131
INK='#203047';MUTED='#596B80';BORDER='#B9C7D4';AMBER='#94600C'
RED='#AE3941';GREEN='#187450';BLUE='#2467AD';GRAY='#5F6E7C'
pdfmetrics.registerFont(TTFont('EQCJK',os.environ.get('FINS_PDF_FONT','C:/Windows/Fonts/msyh.ttc')))
pdf=canvas.Canvas(str(OUT/'equipment-wiring.pdf'),pagesize=landscape(A3))
pdf.setTitle('FinsROV-Heavy equipment enclosure interfaces - EQ-01 Rev A')
pdf.setAuthor('FinsROV-Heavy project')

class Sheet:
    def __init__(self,title,filename,page):
        self.filename=filename
        pdf.scale(landscape(A3)[0]/W,landscape(A3)[1]/H)
        self.svg=[f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}">',f'<title>{escape(title)}</title>']
        self.rect(0,0,W,H,fill='#FFFFFF',stroke='#FFFFFF')
        self.text(50,60,'FinsROV-Heavy',32)
        self.text(50,108,title,26)
        self.text(1210,60,'EQ-01 / Rev A',20)
        self.text(1210,93,'2026-11-17',18,MUTED)
        self.line([(50,135),(1550,135)],BORDER,1)
        self.text(50,1092,'来源：作者确认及设备舱标注图；未进行实机导通、通信、转向或烧写验证。',17,MUTED)
        self.text(1450,1092,f'{page} / 2',17,MUTED)
    def text(self,x,y,s,size=18,color=INK):
        self.svg.append(f'<text x="{x}" y="{y}" fill="{color}" font-family="Microsoft YaHei, Noto Sans CJK SC, sans-serif" font-size="{size}">{escape(s)}</text>')
        pdf.setFillColor(HexColor(color));pdf.setFont('EQCJK',size);pdf.drawString(x,H-y,s)
    def rect(self,x,y,w,h,fill='#FFFFFF',stroke=BORDER,dash=False):
        self.svg.append(f'<rect x="{x}" y="{y}" width="{w}" height="{h}" rx="8" fill="{fill}" stroke="{stroke}" stroke-width="1.5"'+(' stroke-dasharray="7 5"' if dash else '')+'/>')
        pdf.setFillColor(HexColor(fill));pdf.setStrokeColor(HexColor(stroke));pdf.setLineWidth(1.5);pdf.setDash([7,5] if dash else []);pdf.roundRect(x,H-y-h,w,h,8,fill=1,stroke=1);pdf.setDash([])
    def circle(self,x,y,r,fill='#FFFFFF',stroke=BORDER,dash=False):
        self.svg.append(f'<circle cx="{x}" cy="{y}" r="{r}" fill="{fill}" stroke="{stroke}" stroke-width="2"'+(' stroke-dasharray="7 5"' if dash else '')+'/>')
        pdf.setFillColor(HexColor(fill));pdf.setStrokeColor(HexColor(stroke));pdf.setLineWidth(2);pdf.setDash([7,5] if dash else []);pdf.circle(x,H-y,r,fill=1,stroke=1);pdf.setDash([])
    def line(self,pts,color=GRAY,width=2.5,dash=False):
        self.svg.append('<polyline points="'+' '.join(f'{x},{y}' for x,y in pts)+f'" fill="none" stroke="{color}" stroke-width="{width}"'+(' stroke-dasharray="8 6"' if dash else '')+'/>')
        pdf.setStrokeColor(HexColor(color));pdf.setLineWidth(width);pdf.setDash([8,6] if dash else []);p=pdf.beginPath();p.moveTo(pts[0][0],H-pts[0][1])
        for x,y in pts[1:]:p.lineTo(x,H-y)
        pdf.drawPath(p);pdf.setDash([])
    def end(self):
        self.svg.append('</svg>');(OUT/self.filename).write_text('\n'.join(self.svg)+'\n',encoding='utf-8');pdf.showPage()

s=Sheet('设备舱信号端位置 / Signal-end connector locations','equipment-panel.svg',1)
s.text(50,181,'沿用作者图片方向；不是插头针位图，也不表示加工尺寸。',19,MUTED)
s.circle(407,532,310,fill='#F0F4F7')
s.circle(407,532,285,fill='#FFFFFF')
colors={}
for p in [p for p in data['ports'] if p['side']=='信号端']:
    x,y=p['xy'];x+=50;y+=200
    pending=not p['pins']
    fill='#FFF4DC' if pending else '#E6F2EF' if ('PRS' in p['id'] or 'EXT' in p['id']) else '#ECF2FB'
    r=53 if p['id']=='P-PWR' else 42 if p['id'] in ('P-CAM','J-EXT-L','J-EXT-R') else 31
    s.circle(x,y,r,fill,AMBER if pending else '#667C92',pending)
    tag=p['position'].split(' / ')[0]
    s.text(x-21,y+7,tag,20,AMBER if pending else INK)
s.rect(50,875,700,135,fill='#F4F7FA')
s.text(72,905,'S08 / S09 是通用扩展口，当前各接一只云台舵机。',19)
s.text(72,937,'S02 顶部红色件、S05 相机、S14 电源线：接法待核。',18)
s.text(72,969,'S03 烧写口用途已确认，型号与逐针定义待补。',18)
s.text(72,998,'圈内 Sxx 是位置编号，不是连接器针号。',18,AMBER)

x=[800,870,1040,1280];y=220
s.rect(780,190,770,45,fill='#23374D',stroke='#23374D')
for xx,txt in zip(x,['位置','接口编号','用途','规格']):s.text(xx,y,txt,18,'#FFFFFF')
for idx,p in enumerate(p for p in data['ports'] if p['side']=='信号端'):
    top=235+idx*46
    s.rect(780,top,770,46,fill='#F2F6F9' if idx%2==0 else '#FFFFFF',stroke='#E2E8EE')
    short=p['name'].replace('扩展口；当前接云台舵机','扩展 / 当前云台').replace('顶部红色件','顶部红色件（待核）')
    typ='待核' if not p['pins'] else p['type']
    for xx,txt in zip(x,[p['position'].split(' / ')[0],p['id'],short,typ]):s.text(xx,top+29,txt,17,AMBER if not p['pins'] else INK)
s.text(800,966,'电机端另有 8 个 1W3PIN，见第 2 页。',20)
s.text(800,999,'本图中的左右位置不直接代表机体坐标方向。',18,MUTED)
s.end()

s=Sheet('设备舱逻辑针脚 / Functional pin assignments','equipment-circuits.svg',2)
s.text(50,177,'针号按作者定义；圆形插头的实际针位、定位键及舱内板端子仍待核对。',18,MUTED)

s.rect(50,200,720,340)
s.text(72,233,'01  四个水压计口 + 当前两个云台扩展口',21)
s.text(72,264,'水压计：00W4PIN；扩展口：1W4PIN（用途可更改）',18)
s.rect(80,295,220,190,fill='#F3F6F9',dash=True)
s.text(95,328,'各接口的舱内回路',19)
s.text(95,368,'24V 电源来源待核',17,AMBER)
s.text(95,405,'RS-485 分组待核',17,AMBER)
s.text(95,451,'未将六口并为一总线',16,MUTED)
s.rect(510,295,230,190)
for y,pin,signal,color in [(320,1,'24V',RED),(365,2,'GND',GRAY),(410,3,'485A',GREEN),(455,4,'485B',BLUE)]:
    s.line([(300,y),(510,y)],color,dash=True);s.text(325,y-9,signal,16,color);s.text(530,y+7,f'{pin}    {signal}',20,color)
s.text(72,519,'云台左右口尚未指定水平 / 俯仰轴；舵机地址待补。',17,MUTED)

s.rect(830,200,720,340)
s.text(852,233,'02  三个补光灯口（各一只 00W3PIN）',21)
s.text(852,264,'J-LGT-LF 左前 / J-LGT-GM 云台 / J-LGT-RF 右前',17)
s.rect(860,295,220,190,fill='#F3F6F9',dash=True)
s.text(875,329,'各灯的舱内回路',19)
s.text(875,368,'24V 电源来源待核',17,AMBER)
s.text(875,409,'PWM 通道 / 电平',17,AMBER)
s.text(875,451,'频率 / 极性待核',17,AMBER)
s.rect(1290,295,230,190)
for y,pin,signal,color in [(325,1,'24V',RED),(385,2,'GND',GRAY),(445,3,'PWM',BLUE)]:
    s.line([(1080,y),(1290,y)],color,dash=True);s.text(1105,y-9,signal,16,color);s.text(1310,y+7,f'{pin}    {signal}',20,color)
s.text(852,519,'24V 为接口信号名称，本图不声明存在 24V 稳压器。',17,MUTED)

s.rect(50,570,720,455)
s.text(72,606,'03  电机端：8 个 1W3PIN，每台独立一组',21)
s.rect(80,630,200,103,fill='#F3F6F9')
s.text(95,666,'同一电调输出组',19)
s.text(95,705,'三根电机相线',18)
s.rect(525,630,215,103)
s.text(541,659,'J-M01 ... J-M08',19)
s.text(541,691,'三针不固定相序',18)
s.text(541,719,'反转在电调软件调整',16)
for y in (650,680,710):s.line([(280,y),(525,y)],GRAY)
s.text(305,625,'每个接口连接一台电机',15,MUTED)
for xx,txt in [(82,'插座 / 电机'),(292,'电调'),(423,'输出组'),(565,'DShot 通道')]:s.text(xx,766,txt,17)
for i,(m,esc,pad,dshot) in enumerate(data['motor_map']):
    yy=795+i*26
    if i%2==0:s.rect(75,yy-19,668,25,fill='#F2F6F9',stroke='#F2F6F9')
    for xx,txt in [(82,f'J-M{m:02d} / M{m}'),(292,str(esc)),(423,str(pad)),(565,str(dshot))]:s.text(xx,yy,txt,17)

s.rect(830,570,720,455)
s.text(852,606,'04  电池 CAN / 电力载波',21)
s.text(852,640,'电池舱 J-BAT-SVC',19)
s.text(1260,640,'设备舱 J-CAN / 00W2PIN',18)
for y,left,right,color in [(681,'3  CAN_H','1  CAN_H',GREEN),(731,'4  CAN_L','2  CAN_L',BLUE)]:
    s.text(865,y,left,20,color);s.line([(1040,y-7),(1250,y-7)],color);s.text(1270,y,right,20,color)
s.text(852,771,'两端功能对应已确认；外缆实物、参考地及终端待核。',17,MUTED)
s.line([(850,797),(1530,797)],BORDER,1)
s.text(852,832,'J-PLC / 00W2PIN',20)
for y,pin,signal in [(878,1,'PLC_L1'),(925,2,'PLC_L2')]:
    s.text(867,y,f'{pin}    {signal}',20);s.line([(1050,y-7),(1250,y-7)],GRAY,dash=True)
s.text(1270,883,'载波板 / 系缆',19)
s.text(1270,925,'具体端子待核',17,AMBER)
s.text(852,977,'PLC_L1 / L2 不自动定义为正负极或市电 L / N。',18,MUTED)
s.text(50,1058,'实线：本次信号功能或既有电机映射；虚线：舱内接点尚未确认。各图按信号分组，不指定实际导线颜色。',17,MUTED)
s.end();pdf.save()
print('Created equipment-panel.svg, equipment-circuits.svg and equipment-wiring.pdf')
