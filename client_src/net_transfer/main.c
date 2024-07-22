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
	return 0;
}
const char* TCP_receive(int port) {
	return "";
}
void NT_exc_handler(int exc) {
	switch (exc) {
	case INIT: break;
	default: break;
	}
}
