import * as net from 'net';
import { readProperties } from './read_properties';
const Int, port = 777;
const server = net.createServer((socket) => {
    console.log('Client connected.');
    socket.on('data', (data) => {
        console.log('Received:', data.toString());
        socket.write('Echo: ' + data);
    });
    socket.on('end', () => {
        console.log('Client disconnected.');
    });
    socket.on('error', (err) => {
        console.error('Socket error:', err);
    });
});
server.listen(port, async () => {
    console.log(`Server listening on port ${port}`);
    try {
        const properties = await readProperties('data.json');
        console.log('Loaded properties:', properties);
    }
    catch (err) {
        console.error(err);
    }
});
server.on('error', (err) => {
    console.error('Server error:', err);
});
