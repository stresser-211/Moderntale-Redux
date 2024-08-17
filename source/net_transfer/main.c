#include "main.h"

volatile char TCP_response[1024] = "No request has been made yet.";

enum error_codes {
	SUCCESS,
	INITIALISATION,
	HOST_RESOLVING,
	TCP_SOCKET
};

void delay(int ms) {
	clock_t start = clock();
	while (clock() < start + ms * CLOCKS_PER_SEC / 1000);
}

int net_init(void) {
	if (SDLNet_Init() == -1) {
		return INITIALISATION;
	}
	return SUCCESS;
}
void net_quit(void) {
	SDLNet_Quit();
}
int TCP_transfer(int port, const char* datagram) {
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, "127.0.0.1", port) == -1) {
		return HOST_RESOLVING;
	}
	TCPsocket client = SDLNet_TCP_Open(&ip);
	if (!client) {
		return TCP_SOCKET;
	}
	SDLNet_TCP_Send(client, datagram, strlen(datagram) + 1);
	if (SDLNet_TCP_Recv(client, TCP_response, 100) > 0) {
	}
	SDLNet_TCP_Close(client);
	return SUCCESS;
}
const char* get_TCP_response() {
	return TCP_response;
}
int TCP_receive(int port, char* buffer) {
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, NULL, port) == -1) {
		return HOST_RESOLVING;
	}
	TCPsocket server = SDLNet_TCP_Open(&ip);
	if (!server) {
		return TCP_SOCKET;
	}
	TCPsocket client;
	while (1) {
		client = SDLNet_TCP_Accept(server);
		if (client) {
			if (SDLNet_TCP_Recv(client, buffer, 100) > 0) {
			}
		SDLNet_TCP_Close(client);
		}
	delay(16);
	}
	SDLNet_TCP_Close(server);
	return SUCCESS;
}
void NT_exc_handler(int exc) {
	switch (exc) {
	case INITIALISATION: net_quit();
	case HOST_RESOLVING: break;
	case TCP_SOCKET: break;
	default: break;
	}
}
