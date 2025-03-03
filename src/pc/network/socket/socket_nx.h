#ifndef SOCKET_NX_H
#define SOCKET_NX_H

#include <errno.h>
#include "netinet/in.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <switch.h>
#include "../network.h"

#define SOCKET unsigned int
#define INVALID_SOCKET (unsigned int)(-1)
#define SOCKET_LAST_ERROR errno
#define NO_ERROR (0)
#define SOCKADDR struct sockaddr
#define SOCKET_ERROR (-1)
#define closesocket(fd) close(fd)
#define SOCKET_EWOULDBLOCK EWOULDBLOCK
#define SOCKET_ECONNRESET ECONNRESET
#define RX_ADDR_SIZE_TYPE unsigned int

extern struct NetworkSystem gNetworkSystemSocket;

extern char gGetHostName[];

#endif // SOCKET_NX_H