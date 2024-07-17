#ifdef WINSOCK
#include "socket_windows.h"
#include <stdio.h>
#include "pc/debuglog.h"

SOCKET socket_initialize(void) {
    // start up winsock
    WSADATA wsaData;
    int rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc != NO_ERROR) {
        LOG_ERROR("WSAStartup failed with error %d", rc);
        return INVALID_SOCKET;
    }

    // initialize socket
    SOCKET sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        LOG_ERROR("socket failed with error %d", SOCKET_LAST_ERROR);
        return INVALID_SOCKET;
    }

    // set non-blocking mode
    u_long iMode = 1;
    rc = ioctlsocket(sock, FIONBIO, &iMode);
    if (rc != NO_ERROR) {
        LOG_ERROR("ioctlsocket failed with error: %d", rc);
        return INVALID_SOCKET;
    }

    // set dual-stack socket mode
    int v6only = 0;
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&v6only, sizeof(v6only)) < 0) {
        LOG_ERROR("setsockopt(IPV6_V6ONLY) failed.");
        return INVALID_SOCKET;
    };

#if MAX_PLAYERS > 4
    // on windows, the send buffer for the socket needs to be increased
    // for the many players case to avoid WSAEWOULDBLOCK on send
    // not actually sure this is the "proper" way to fix it
    int bufsiz = 128 * 1024; // 128kb, default is apparently 8kb or 16kb
    rc = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const char *)&bufsiz, sizeof(bufsiz));
    if (rc != NO_ERROR) {
        LOG_ERROR("setsockopt(SO_SNDBUF) failed with error: %d", rc);
    }
#endif

    return sock;
}

void socket_shutdown(SOCKET socket) {
    if (socket == INVALID_SOCKET) { return; }
    int rc = closesocket(socket);
    if (rc == SOCKET_ERROR) {
        LOG_ERROR("closesocket failed with error %d", SOCKET_LAST_ERROR);
    }
    WSACleanup();
}

#endif
