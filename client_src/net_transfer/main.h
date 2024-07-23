#include "../api"
#include <SDL_net.h>
#include <stdio.h>

/* api here */

API int net_init(void);
API void net_quit(void);
API int TCP_transfer(int port, char* datagram);
API int TCP_transfer(int port, int datagram);
API void TCP_receive(int port);
API void NT_exc_handler(int exc);

