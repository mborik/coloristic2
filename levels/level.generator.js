const fs = require('fs');
const xml2js = require('xml2js');

const resultFn = 'levels.bin';

fs.closeSync(fs.openSync(resultFn, 'w'));
const tmx = fs.readFileSync('levels.tmx', { encoding: 'utf8' });

const parser = new xml2js.Parser({
	charkey: 'text',
	normalize: true,
	mergeAttrs: true,
	explicitArray: false,
	preserveChildrenOrder: true
});

parser.parseString(tmx, (e, result) => {
	if (e) {
		console.error(e);
	}
	else {
		const levels = (result.map?.group || []).flatMap(group => group?.layer || []);
		levels.forEach(level => {
			const props = (level.properties && level.properties.property) || [];
			const levelData = new Buffer(68);

			const data = level.data;
			if (data && data.encoding === 'csv' && data.text) {
				const values = data.text.replace(/\s+/g, '').split(',');

				let i = 0;
				for (; i < values.length; i++) {
					let value = parseInt(values[i]) || 0;
					if (value === 16) { // cross
						value = 64;
					}
					else if (value === 17) { // rotation
						value--;
					}
					else if (value === 18) { // teleport
						value = 32;
					}

					levelData.writeUInt8(value, i);
				}

				const offset = ((level.offsetx || 0) >> 3) +
						(((level.offsety || 0) >> 3) * 40);
				levelData.writeUInt8(offset, i);

				i = levelData.length - props.length;
				for (const prop of props) {
					levelData.writeUInt8(parseInt(prop.value) || 0, i++);
				}

				fs.appendFileSync(resultFn, levelData);
			}
		});
	}
});
