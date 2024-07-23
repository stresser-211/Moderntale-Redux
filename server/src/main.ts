import * as net from 'net';
import { readProperties } from './read_properties';

const port: number = 777;

const server = net.createServer((socket: net.Socket) => {
    console.log('Client connected.');

    socket.on('data', (data: Buffer) => {
        console.log('Received:', data.toString());
        socket.write('Echo: ' + data.toString());
    });

    socket.on('end', () => {
        console.log('Client disconnected.');
    });

    socket.on('error', (err: Error) => {
        console.error('Socket error:', err);
    });
});

server.listen(port, async () => {
    console.log(`Server listening on port ${port}`);

    try {
        const properties = await readProperties('data.json');
        console.log('Loaded properties:', properties);
    } catch (err) {
        console.error('Error reading properties:', err);
    }
});

server.on('error', (err: Error) => {
    console.error('Server error:', err);
});
