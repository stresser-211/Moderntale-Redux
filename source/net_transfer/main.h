#ifndef NET_TRANSFER_H
#define NET_TRANSFER_H

#include "../api"
#include "consts.h"
#include <time.h>
#include <SDL_net.h>

#ifdef __cplusplus
extern "C" {
#endif

API int net_init(void);
API void net_quit(void);
API int TCP_transfer(int port, char* datagram);
API const char* get_TCP_response();
API int TCP_receive(int port, char* buffer);
API void NT_exc_handler(int exc);

#ifdef __cplusplus
}
#endif

#endif // NET_TRANSFER_H
