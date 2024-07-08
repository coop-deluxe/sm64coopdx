#ifndef WINSOCK
#include "socket_linux.h"
#include "../network.h"
#include "pc/debuglog.h"

SOCKET socket_initialize(void) {
    // initialize socket
    SOCKET sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        LOG_ERROR("socket failed with error %d", SOCKET_LAST_ERROR);
        return INVALID_SOCKET;
    }

    // set non-blocking mode
    int rc = fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);
    if (rc == (int)INVALID_SOCKET) {
        LOG_ERROR("fcntl failed with error: %d", rc);
        return INVALID_SOCKET;
    }
    
    // Make sure our socket is dual-stack. So we can use both IPv4 and IPv6.
    int opt = 0;
    rc = setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&opt, sizeof(opt));
    if (rc != NO_ERROR) {
        LOG_ERROR("setsockopt(IPV6_V6ONLY) failed with error: %d", rc);
        return INVALID_SOCKET;
    }

    return sock;
}

void socket_shutdown(SOCKET socket) {
    if (socket == INVALID_SOCKET) { return; }
    int rc = closesocket(socket);
    if (rc == (int)SOCKET_ERROR) {
        LOG_ERROR("closesocket failed with error %d\n", SOCKET_LAST_ERROR);
    }
}

#endif
