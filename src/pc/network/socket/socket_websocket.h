#ifdef TARGET_WEB
#ifndef SOCKET_WEBSOCKET_H
#define SOCKET_WEBSOCKET_H

#define SOCKET int
#define INVALID_SOCKET (-1)
#define SOCKET_LAST_ERROR 0
#define NO_ERROR 0
#define SOCKADDR struct sockaddr
#define SOCKET_ERROR (-1)
#define closesocket(fd) (void)(fd)
#define SOCKET_EWOULDBLOCK 11
#define SOCKET_ECONNRESET 104
#define RX_ADDR_SIZE_TYPE unsigned int

// Stub sockaddr_in6 for WebSocket builds
struct sockaddr_in6 {
    int sin6_family;
    unsigned short sin6_port;
    struct {
        unsigned char s6_addr[16];
    } sin6_addr;
};

#endif
#endif
