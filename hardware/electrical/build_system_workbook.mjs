// Build only the SYS-01 workbook from the same JSON used by the diagrams/CSVs.
// Dependency: @oai/artifact-tool. Optional arguments: JSON, preview directory,
// comma-separated table keys to render (default: every table).
import fs from 'node:fs/promises';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { Workbook, SpreadsheetFile } from '@oai/artifact-tool';
const here = path.dirname(fileURLToPath(import.meta.url));
const input = process.argv[2] || path.join(here, 'system-wiring.json');
const previewDir = process.argv[3];
const previewKeys = process.argv[4]?.split(',');
const data = JSON.parse(await fs.readFile(input, 'utf8'));
const workbook = Workbook.create();
const specs = [
  ['connections','系统连接',[145,185,200,290,310,120,150,410]],
  ['mcu','MCU 对照',[135,220,130,310,350,180,380]],
  ['harness','线束实测',[190,290,130,140,250,250,290,180]],
  ['terminals','端子功能分组',[160,155,165,100,395,290,115,365]],
];
for (const [key,name,widths] of specs) {
  const sheet = workbook.worksheets.add(name);
  sheet.showGridLines = false;
  sheet.tabColor = key === 'connections' ? '#203047' : '#60758C';
  const rows=data[key], columns=data.headers[key].length;
  const last=String.fromCharCode(64+columns), end=5+rows.length;
  sheet.getRange(`A1:${last}${end}`).format.font={name:'Microsoft YaHei',size:11,color:'#203047'};
  sheet.getRange('A2').values=[[`FinsROV-Heavy ${name} | ${data.revision}`]];
  sheet.getRange('A2').format.font={name:'Microsoft YaHei',size:16,bold:true,color:'#203047'};
  sheet.getRange('A3').values=[[key==='harness' ? '黄色字段用于实物补录；长度必须同时记录测量起止点。当前均未实测。' : key==='terminals' ? '功能分组不是针号：20P 顺序按布线自行安排并记录；PWM / CAN / PLC 不互相短接。未做导通验证。' : '功能关系、源码配置与实物验证分开记录；MCU 引脚不等于板端插座针号。']];
  sheet.getRange('A3').format.font={name:'Microsoft YaHei',size:11,color:'#94600C'};
  sheet.getRange(`A5:${last}${end}`).values=[data.headers[key],...rows];
  sheet.tables.add(`A5:${last}${end}`,true,`SYS_${key}`).showFilterButton=true;
  sheet.getRange(`A5:${last}5`).format={fill:'#203047',font:{name:'Microsoft YaHei',size:11,bold:true,color:'#FFFFFF'},rowHeight:31,horizontalAlignment:'center',verticalAlignment:'center'};
  sheet.getRange(`A6:${last}${end}`).format.wrapText=true;
  sheet.getRange(`A6:${last}${end}`).format.verticalAlignment='center';
  sheet.getRange(`A6:${last}${end}`).format.rowHeight=key==='connections'?70:key==='terminals'?64:58;
  widths.forEach((width,index)=>sheet.getRangeByIndexes(0,index,end,1).format.columnWidthPx=width);
  sheet.freezePanes.freezeRows(5);
  sheet.freezePanes.freezeColumns(key==='connections'?2:1);
  if(key==='connections')sheet.getRange(`F6:F${end}`).conditionalFormats.add('containsText',{text:'待核',format:{fill:'#FFF0CD',font:{color:'#94600C'}}});
  if(key==='harness') {
    sheet.getRange(`C6:F${end}`).format.fill='#FFF0CD';
    sheet.getRange(`C6:F${end}`).format.font.color='#7C510B';
  }
  if(key==='terminals')sheet.getRange(`D6:D${end}`).format.horizontalAlignment='center';
  const sourceStart=end+3;
  sheet.getRange(`A${sourceStart}`).values=[['来源编号对应仓库文件']];
  sheet.getRange(`A${sourceStart}`).format.font={name:'Microsoft YaHei',size:13,bold:true,color:'#203047'};
  Object.entries(data.sources).forEach(([id,source],index)=>{
    const row=sourceStart+index+1;
    sheet.getRange(`A${row}:B${row}`).values=[[id,source.path]];
    sheet.getRange(`A${row}:B${row}`).format.font={name:'Microsoft YaHei',size:10,color:'#596B80'};
    sheet.getRange(`A${row}:B${row}`).format.rowHeight=21;
    sheet.getRange(`B${row}`).format.wrapText=false;
  });
}
workbook.recalculate();
for(const [key,name] of specs) {
  const sheet=workbook.worksheets.getItem(name);
  const rows=sheet.getRangeByIndexes(5,0,data[key].length,data.headers[key].length).values;
  if(JSON.stringify(rows)!==JSON.stringify(data[key]))throw new Error(`${key}: workbook data mismatch`);
  if(previewDir && (!previewKeys || previewKeys.includes(key))) {
    await fs.mkdir(previewDir,{recursive:true});
    for(const [suffix,range] of [['top',`A1:${String.fromCharCode(64+data.headers[key].length)}12`],['bottom',`A${Math.max(6,data[key].length-3)}:${String.fromCharCode(64+data.headers[key].length)}${data[key].length+5}`]]) {
      const preview=await workbook.render({sheetName:name,range,scale:1,format:'png'});
      await fs.writeFile(path.join(previewDir,`${key}-${suffix}.png`),new Uint8Array(await preview.arrayBuffer()));
    }
  }
}
const scan=await workbook.inspect({kind:'match',searchTerm:'#REF!|#DIV/0!|#VALUE!|#NAME\\?|#N/A|#NUM!|#NULL!',options:{useRegex:true,maxResults:20},summary:'Final error scan'});
console.log(scan.ndjson);
const output=await SpreadsheetFile.exportXlsx(workbook);
await output.save(path.join(path.dirname(input),'system-wiring.xlsx'));
console.log('Exported system-wiring.xlsx; all four tables match JSON exactly.');
