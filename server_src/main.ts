import * as net from 'net';

const PORT = 777;
const HOST = '127.0.0.1';

const server = net.createServer((socket) => {
	console.log('Client connected.');

	socket.on('data', (data) => {
	console.log(`Received data: ${data}`);
		socket.write(data);
	});

	socket.on('end', () => {
		console.log('Client disconnected.');
	});

	socket.on('error', (err) => {
		console.error(`Error: ${err}`);
	});
});

server.listen(PORT, HOST, () => {
	console.log(`Server listening on ${HOST}:${PORT}`);
});

