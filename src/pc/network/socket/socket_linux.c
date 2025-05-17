#ifndef WINSOCK
#include "socket_linux.h"
#include "../network.h"
#include "pc/log.h"

SOCKET socket_initialize(void) {
    // initialize socket
    SOCKET sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        LOG_ERROR_VERBOSE("socket failed with error %d", SOCKET_LAST_ERROR);
        return INVALID_SOCKET;
    }

    // set non-blocking mode
    int rc = fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);
    if (rc == (int)INVALID_SOCKET) {
        LOG_ERROR_VERBOSE("fcntl failed with error: %d", rc);
        return INVALID_SOCKET;
    }

    // Set socket to dual-stack
    int v6only = 0;
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&v6only, sizeof(v6only)) < 0) {
        LOG_ERROR_VERBOSE("setsockopt(IPV6_V6ONLY) failed.");
        return INVALID_SOCKET;
    };

    LOG_INFO_VERBOSE("socket initialized.");

    return sock;
}

void socket_shutdown(SOCKET socket) {
    if (socket == INVALID_SOCKET) { return; }
    int rc = closesocket(socket);
    if (rc == (int)SOCKET_ERROR) {
        LOG_ERROR_VERBOSE("closesocket failed with error %d\n", SOCKET_LAST_ERROR);
    }
}

#endif
