#ifndef SOCKET_H
#define SOCKET_H

#include "../network.h"

#ifdef WINSOCK
#include "socket_windows.h"
#else
#include "socket_linux.h"
#endif

extern struct NetworkSystem gNetworkSystemSocket;

SOCKET socket_initialize(void);
void socket_shutdown(SOCKET socket);

#endif
