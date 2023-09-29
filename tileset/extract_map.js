const fs = require('fs');
const xml2js = require('xml2js');

const resultFn = 'tilemap.map';

fs.closeSync(fs.openSync(resultFn, 'w'));
const tmx = fs.readFileSync('demo_map.tmx', { encoding: 'utf8' });

const parser = new xml2js.Parser({
  charkey: 'text',
  normalize: true,
  mergeAttrs: true,
  explicitArray: false,
  preserveChildrenOrder: true
});

// const plus3dosHeader = Buffer.from(
//   '50 4C 55 53 33 44 4F 53 1A 01 00 80 05 00 00 03 00 05 28 00 00 05 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00'
//   .split(' ').map((v) => parseInt(v, 16))
// );

parser.parseString(tmx, (e, result) => {
  if (e) {
    console.error(e);
  }
  else {
    const level = ((result.map && result.map.layer) || [])[0];
    const levelData = new Buffer(1280);

    let crc = 0;
    const data = level.data;
    if (data && data.encoding === 'base64' && data.text) {
      const values = Buffer.from(data.text, 'base64');

      for (let offset = 0, i = 0; offset < values.length; i++, offset += 4) {
        const value = (values.readUInt8(offset) - 1) & 0xff;
        crc ^= value;
        levelData.writeUInt8(value, i);
      }

      // plus3dosHeader.writeUInt8(crc, 127);
      // fs.writeFileSync(resultFn, Buffer.concat([plus3dosHeader, levelData]));
      fs.writeFileSync(resultFn, levelData);
    }
  }
});
