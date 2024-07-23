#include "main.h"
#include "consts.h"

enum error_codes {
	SUCCESS,
	INITIALISATION,
	HOST_RESOLVING,
	TCP_SOCKET
};

int net_init(void) {
	if (SDLNet_Init(void) == -1) {
		return INITIALISATION;
	}
	return SUCCESS;
}
void net_quit(void) {
    SDLNet_Quit();
    SDL_Quit();
}
int TCP_transfer(int port, const char* datagram) {
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, "127.0.0.1", 1234) == -1) {
        return HOST_RESOLVING;
    }
    TCPsocket client = SDLNet_TCP_Open(&ip);
    if (!client) {
        return TCP_SOCKET;
    }
    SDLNet_TCP_Send(client, datagram, strlen(datagram) + 1);
    char response[100];
    if (SDLNet_TCP_Recv(client, response, 100) > 0) {
        const char* aeaeae = response;
    }
    SDLNet_TCP_Close(client);
    return SUCCESS;
}
int TCP_transfer(int port, int datagram) {
	char buffer[80];
	sprintf(buffer, "%s", datagram);
	TCP_transfer(port, buffer)
	return SUCCESS;
}
void TCP_receive(int port) {
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, NULL, 1234) == -1) {
        return HOST_RESOLVING;
    }
	TCPsocket server = SDLNet_TCP_Open(&ip);
    if (!server) {
		return TCP_SOCKET;
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
	case INITIALISATION: break;
	case HOST_RESOLVING: break;
	case TCP_SOCKET: break;
	default: break;
	}
}
