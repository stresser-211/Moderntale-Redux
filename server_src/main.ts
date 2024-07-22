import * as net from 'net';

const port = 781;
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

server.listen(port, () => {
    console.log(`Server listening on port ${port}`);
});

server.on('error', (err) => {
    console.error('Server error:', err);
});
