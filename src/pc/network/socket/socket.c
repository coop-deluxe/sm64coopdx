#include <stdio.h>
#include "socket.h"
#include "pc/configfile.h"
#include "pc/debuglog.h"
#include "menu/custom_menu.h"

static SOCKET curSocket = INVALID_SOCKET;
struct sockaddr_in txAddr = { 0 };

static int socket_bind(SOCKET socket, unsigned int port) {
    struct sockaddr_in rxAddr;
    rxAddr.sin_family = AF_INET;
    rxAddr.sin_port = htons(port);
    rxAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int rc = bind(socket, (SOCKADDR*)&rxAddr, sizeof(rxAddr));
    if (rc != 0) {
        LOG_ERROR("bind failed with error %d", SOCKET_LAST_ERROR);
    }

    return rc;
}

static int socket_send(SOCKET socket, struct sockaddr_in* addr, u8* buffer, u16 bufferLength) {
    int addrSize = sizeof(struct sockaddr_in);
    int rc = sendto(socket, (char*)buffer, bufferLength, 0, (struct sockaddr*)addr, addrSize);
    if (rc == SOCKET_ERROR) {
        LOG_ERROR("sendto failed with error: %d", SOCKET_LAST_ERROR);
    }

    return rc;
}

static int socket_receive(SOCKET socket, struct sockaddr_in* rxAddr, u8* buffer, u16 bufferLength, u16* receiveLength) {
    *receiveLength = 0;

    int rxAddrSize = sizeof(struct sockaddr_in);
    int rc = recvfrom(socket, (char*)buffer, bufferLength, 0, (struct sockaddr*)rxAddr, &rxAddrSize);
    if (rc == SOCKET_ERROR) {
        int error = SOCKET_LAST_ERROR;
        if (error != SOCKET_EWOULDBLOCK && error != SOCKET_ECONNRESET) {
            LOG_ERROR("recvfrom failed with error %d", SOCKET_LAST_ERROR);
        }
        return rc;
    }

    *receiveLength = rc;
    return NO_ERROR;
}

static bool ns_socket_initialize(enum NetworkType networkType) {
    // sanity check port
    unsigned int port = (networkType == NT_CLIENT) ? configJoinPort : configHostPort;
    if (port == 0) { port = DEFAULT_PORT; }

    // create a receiver socket to receive datagrams
    curSocket = socket_initialize();
    if (curSocket == INVALID_SOCKET) { return false; }

    // connect
    if (networkType == NT_SERVER) {
        // bind the socket to any address and the specified port.
        int rc = socket_bind(curSocket, port);
        if (rc != NO_ERROR) { return false; }
        LOG_INFO("bound to port %u", port);
    } else {
        // save the port to send to
        txAddr.sin_family = AF_INET;
        txAddr.sin_port = htons(port);
        txAddr.sin_addr.s_addr = inet_addr(configJoinIp);
        LOG_INFO("connecting to %s %u", configJoinIp, port);
    }

    // kick off first packet
    if (networkType == NT_CLIENT) {
        char joinText[128] = { 0 };
        snprintf(joinText, 63, "%s %d", configJoinIp, configJoinPort);
        gOpenConnectMenu = TRUE;

        gNetworkType = NT_CLIENT;
        network_send_join_request();
    }

    LOG_INFO("initialized");

    // success
    return true;
}

static void ns_socket_update(void) {
    if (gNetworkType == NT_NONE) { return; }
    do {
        // receive packet
        u8 data[PACKET_LENGTH];
        u16 dataLength = 0;
        int rc = socket_receive(curSocket, &txAddr, data, PACKET_LENGTH, &dataLength);
        if (rc != NO_ERROR) { break; }
        network_receive(data, dataLength);
    } while (true);
}

static int ns_socket_send(u8* data, u16 dataLength) {
    return socket_send(curSocket, &txAddr, data, dataLength);
}

static void ns_socket_shutdown(void) {
    socket_shutdown(curSocket);
    curSocket = INVALID_SOCKET;
    LOG_INFO("shutdown");
}

struct NetworkSystem gNetworkSystemSocket = {
    .initialize = ns_socket_initialize,
    .update     = ns_socket_update,
    .send       = ns_socket_send,
    .shutdown   = ns_socket_shutdown,
};
