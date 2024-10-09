#ifndef SOCKET_WINDOWS_H
#define SOCKET_WINDOWS_H

#include <winsock2.h>
#include <ws2tcpip.h>

#define SOCKET_LAST_ERROR WSAGetLastError()
#define SOCKET_EWOULDBLOCK WSAEWOULDBLOCK
#define SOCKET_ECONNRESET WSAECONNRESET
#define RX_ADDR_SIZE_TYPE int

#endif
