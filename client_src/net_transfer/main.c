#include "main.hpp"

enum err_code {
	INIT = 1
};

int net_init() {
	if (SDLNet_Init(void) == -1) {
		return INIT;
	}
}
int TCP_transfer(int port, char* datagram) {
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, "127.0.0.1", 1234) == -1) {
        return 3;
    }
    TCPsocket client = SDLNet_TCP_Open(&ip);
    if (!client) {
        return 4;
    }
    const char* message = "Hello, server!";
    SDLNet_TCP_Send(client, message, strlen(message) + 1);
    char response[100];
    if (SDLNet_TCP_Recv(client, response, 100) > 0) {
        const char* aeaeae = response;
    }
    SDLNet_TCP_Close(client);
    return 0;
}
void TCP_receive(int port) {
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, NULL, 1234) == -1) {
        return 3;
    }
	TCPsocket server = SDLNet_TCP_Open(&ip);
    if (!server) {
		return 4;
    }
    TCPsocket client;
    while (true) {
        client = SDLNet_TCP_Accept(server);
        if (client) {
            char text[100];
            if (SDLNet_TCP_Recv(client, text, 100) > 0) {
                const char* reply = "Hello, client!";
                SDLNet_TCP_Send(client, reply, strlen(reply) + 1);
            }
            SDLNet_TCP_Close(client);
        }
        SDL_Delay(10);
    }
    SDLNet_TCP_Close(server);
}
void NT_exc_handler(int exc) {
	switch (exc) {
	case INIT: break;
	default: break;
	}
}

void net_quit() {
    SDLNet_Quit();
    SDL_Quit();
}