// Edit the existing interface workbooks from CSV, preserving their established sheets.
// Requires @oai/artifact-tool. Usage: node sync_interface_workbooks.mjs <electrical-dir> <preview-dir> [inspect]
import fs from 'node:fs/promises';
import path from 'node:path';
import {FileBlob, SpreadsheetFile} from '@oai/artifact-tool';
const [dir, preview, mode] = process.argv.slice(2);
if (!dir || !preview) throw new Error('Supply electrical and preview directories.');
await fs.mkdir(preview,{recursive:true});
function csv(text) {
  const rows=[]; let row=[],value='',quoted=false;
  text=text.replace(/^\uFEFF/,'');
  for(let i=0;i<text.length;i++) {
    const char=text[i];
    if(char==='"') {if(quoted&&text[i+1]==='"'){value+='"';i++;}else quoted=!quoted;}
    else if(char===','&&!quoted){row.push(value);value='';}
    else if(char==='\n'&&!quoted){row.push(value.replace(/\r$/,''));rows.push(row);row=[];value='';}
    else value+=char;
  }
  if(value||row.length){row.push(value);rows.push(row);}
  return rows;
}
const specs=[
  ['battery','接口针脚','battery-pinout.csv','A1:H12'],
  ['battery','线束明细','battery-harness.csv','A1:L14'],
  ['equipment','接口清单','equipment-connectors.csv','A10:J24'],
  ['equipment','逐针定义','equipment-pinout.csv','A30:I45'],
];
for(const stem of ['battery','equipment']) {
  const workbook=await SpreadsheetFile.importXlsx(await FileBlob.load(path.join(dir,`${stem}-wiring.xlsx`)));
  const renderSpecs=[];
  for(const [book,name,file,range] of specs.filter(row=>row[0]===stem)) {
    const sheet=workbook.worksheets.getItem(name);
    if(mode!=='inspect') {
      const values=csv(await fs.readFile(path.join(dir,file),'utf8'));
      // Preserve the original numeric cell types on equipment identifiers/counts.
      if(stem==='equipment') for(const row of values.slice(1)) {const col=name==='接口清单'?5:4;if(/^\d+$/.test(row[col]))row[col]=Number(row[col]);}
      const before=sheet.getRangeByIndexes(0,0,values.length,values[0].length).values;
      values.forEach((row,index)=>{
        if(JSON.stringify(row)!==JSON.stringify(before[index])) {
          sheet.getRangeByIndexes(index,0,1,row.length).values=[row];
          if(index>0) sheet.getRangeByIndexes(index,0,1,row.length).format.rowHeight=105;
        }
      });
      const received=sheet.getRangeByIndexes(0,0,values.length,values[0].length).values;
      if(JSON.stringify(received)!==JSON.stringify(values))throw new Error(`${file} workbook mismatch`);
    }
    renderSpecs.push([name,range,`${stem}-${name}-${mode==='inspect'?'before':'after'}.png`]);
    if(stem==='equipment'&&name==='逐针定义')renderSpecs.push([name,'A50:I66',`equipment-lights-${mode==='inspect'?'before':'after'}.png`]);
  }
  if(stem==='battery'&&mode!=='inspect') {
    const pins=workbook.worksheets.getItem('接口针脚');
    for(let r=4;r<=7;r++) {pins.getRange(`C${r}`).format.fill=r%2===0?'#F2F6F9':'#FFFFFF';pins.getRange(`C${r}`).format.font.color='#203047';pins.getRange(`C${r}`).format.font.bold=false;}
    const harness=workbook.worksheets.getItem('线束明细');
    harness.getRange('F4').format.fill='#F2F6F9';harness.getRange('F4').format.font.color='#203047';harness.getRange('F4').format.font.bold=false;
  }
  if(stem==='equipment'&&mode!=='inspect') {
    const values=csv(await fs.readFile(path.join(dir,'equipment-terminals.csv'),'utf8'));
    for(const row of values.slice(1))row[2]=Number(row[2]);
    let sheet;
    try {sheet=workbook.worksheets.getItem('端子分组');}catch{sheet=workbook.worksheets.add('端子分组');}
    const end=values.length;
    sheet.getRange(`A1:G${end}`).values=values;
    sheet.showGridLines=false;
    sheet.getRange(`A1:G${end}`).format={font:{name:'Microsoft YaHei',size:11,color:'#203047'},wrapText:true,verticalAlignment:'center',rowHeight:78};
    sheet.getRange('A1:G1').format={fill:'#203047',font:{name:'Microsoft YaHei',size:11,bold:true,color:'#FFFFFF'},rowHeight:32};
    sheet.getRange(`C2:C${end}`).format.horizontalAlignment='center';
    [130,180,80,360,390,250,390].forEach((width,i)=>sheet.getRangeByIndexes(0,i,end,1).format.columnWidthPx=width);
    sheet.freezePanes.freezeRows(1);sheet.freezePanes.freezeColumns(1);
    for(let r=3;r<=end;r+=2)sheet.getRange(`A${r}:G${r}`).format.fill='#F2F6F9';
    renderSpecs.push(['端子分组',`A1:G${end}`,'equipment-terminals-after.png']);
  }
  if(mode!=='inspect')workbook.recalculate();
  for(const [name,range,filename] of renderSpecs) {
    const blob=await workbook.render({sheetName:name,range,scale:1,format:'png'});
    await fs.writeFile(path.join(preview,filename),new Uint8Array(await blob.arrayBuffer()));
  }
  if(mode!=='inspect') {
    console.log((await workbook.inspect({kind:'match',searchTerm:'#REF!|#DIV/0!|#VALUE!|#NAME\\?|#N/A|#NUM!|#NULL!',options:{useRegex:true,maxResults:20},summary:`${stem} errors`})).ndjson);
    await (await SpreadsheetFile.exportXlsx(workbook)).save(path.join(dir,`${stem}-wiring.xlsx`));
    // Keep SDK inspection sidecars with the requested previews, outside source assets.
    try {
      await fs.rename(path.join(dir,`${stem}-wiring.xlsx.inspect.ndjson`),path.join(preview,`${stem}.inspect.ndjson`));
    } catch(error) {if(error.code!=='ENOENT')throw error;}
  }
}
