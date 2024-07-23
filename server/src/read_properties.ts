import * as fs from 'fs';

export const readProperties = (filePath: string): Promise<any> => {
    return new Promise((resolve, reject) => {
        fs.readFile(filePath, 'utf8', (err, data) => {
            if (err) {
                reject('Error reading the file: ' + err);
                return;
            }
            try {
                const jsonData = JSON.parse(data);
                resolve(jsonData);
            } catch (err) {
                reject('Error parsing JSON: ' + err);
            }
        });
    });
};
