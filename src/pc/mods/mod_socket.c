#include "pc/cliopts.h"
#include "pc/network/socket/socket.h"
#include "pc/debuglog.h"
#include "pc/cliopts.h"
#include "mod_socket.h"

SOCKET extSock = INVALID_SOCKET;
char recBuffer[4096];
bool connected = false;

bool mod_socket_allowed(void)
{
    return configAllowExternal;
}

bool mod_socket_init(const char* ip, int port, bool TCP)
{
    mod_socket_disconnect(); // If already connected to a socket, reset before new connection

    if (!configAllowExternal)
        return false;
        
    struct sockaddr_in servAddr;
    servAddr.sin_addr.s_addr = inet_addr(ip);
    servAddr.sin_port = htons(port);
    servAddr.sin_family = AF_INET;

    extSock = socket(AF_INET, TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
    if (extSock == INVALID_SOCKET) { return false; }

    if (connect(extSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) return false;

    u_long iMode = 1;
    int rc = ioctlsocket(extSock, FIONBIO, &iMode);
    if (rc != NO_ERROR) {
        LOG_ERROR("ioctlsocket failed with error: %d", rc);
        return INVALID_SOCKET;
    }
    
    return true;
}

void mod_socket_disconnect()
{
    if (extSock != INVALID_SOCKET)
        shutdown(extSock, SD_BOTH);
}

void mod_socket_send(const char* data)
{
    if (extSock == INVALID_SOCKET)
        return;

    sendto(extSock, data, strlen(data), 0, (struct sockaddr*)NULL, 0);
}

bool mod_socket_is_connected()
{
    return connected;
}

void mod_socket_update()
{
    if (extSock == INVALID_SOCKET)
        return;

    if (!configAllowExternal) // Allow external disabled whilst the mod is running
    {
        mod_socket_disconnect();
        return;
    }

    memset(recBuffer, 0, sizeof(recBuffer));
    int rec = recvfrom(extSock, recBuffer, sizeof(recBuffer), 0, (struct sockaddr*)NULL, NULL);

    if (rec < 0)
    {
        int err = WSAGetLastError();
        if (err != WSAEWOULDBLOCK)
            connected = false;
        else
            connected = true;
    }
    else if (rec > 0)
    {
        connected = true;
        smlua_call_event_hooks(HOOK_SOCKET_RECEIVE, recBuffer);
    } else connected = false;
}