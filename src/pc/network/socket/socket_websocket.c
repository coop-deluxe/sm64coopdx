#ifdef TARGET_WEB
#include <emscripten/websocket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "socket.h"
#include "pc/configfile.h"
#include "pc/debuglog.h"
#include "pc/djui/djui.h"

// Ring buffer for received packets
#define WS_RECV_BUF_SIZE (64 * 1024)
static u8 sRecvBuf[WS_RECV_BUF_SIZE];
static u32 sRecvBufHead = 0;
static u32 sRecvBufTail = 0;

static EMSCRIPTEN_WEBSOCKET_T sWebSocket = 0;
static bool sWebSocketConnected = false;
static SOCKET sCurSocket = INVALID_SOCKET;
static struct sockaddr_in6 sAddr[MAX_PLAYERS] = { 0 };

char gGetHostName[MAX_CONFIG_STRING] = "";

// --- Ring buffer helpers ---

static u32 ringbuf_available(void) {
    return (sRecvBufHead >= sRecvBufTail)
        ? (sRecvBufHead - sRecvBufTail)
        : (WS_RECV_BUF_SIZE - sRecvBufTail + sRecvBufHead);
}

static void ringbuf_write(const u8* data, u32 len) {
    for (u32 i = 0; i < len; i++) {
        sRecvBuf[sRecvBufHead] = data[i];
        sRecvBufHead = (sRecvBufHead + 1) % WS_RECV_BUF_SIZE;
    }
}

static void ringbuf_read(u8* data, u32 len) {
    for (u32 i = 0; i < len; i++) {
        data[i] = sRecvBuf[sRecvBufTail];
        sRecvBufTail = (sRecvBufTail + 1) % WS_RECV_BUF_SIZE;
    }
}

// --- WebSocket callbacks ---

static EM_BOOL on_ws_open(int eventType, const EmscriptenWebSocketOpenEvent* event, void* userData) {
    (void)eventType; (void)event; (void)userData;
    LOG_INFO("WebSocket connected");
    sWebSocketConnected = true;
    return EM_TRUE;
}

static EM_BOOL on_ws_message(int eventType, const EmscriptenWebSocketMessageEvent* event, void* userData) {
    (void)eventType; (void)userData;

    if (!event->isText && event->numBytes > 0) {
        u16 pktLen = (u16)event->numBytes;
        // Check if there is enough space: 2 bytes for length prefix + data
        u32 needed = (u32)pktLen + 2;
        u32 freeSpace = WS_RECV_BUF_SIZE - ringbuf_available() - 1;
        if (needed > freeSpace) {
            LOG_ERROR("WebSocket receive buffer full, dropping packet (%u bytes)", pktLen);
            return EM_TRUE;
        }

        // Write length prefix (little-endian u16)
        u8 lenBuf[2];
        lenBuf[0] = (u8)(pktLen & 0xFF);
        lenBuf[1] = (u8)((pktLen >> 8) & 0xFF);
        ringbuf_write(lenBuf, 2);
        ringbuf_write(event->data, pktLen);
    }

    return EM_TRUE;
}

static EM_BOOL on_ws_close(int eventType, const EmscriptenWebSocketCloseEvent* event, void* userData) {
    (void)eventType; (void)event; (void)userData;
    LOG_INFO("WebSocket closed");
    sWebSocketConnected = false;
    sWebSocket = 0;
    return EM_TRUE;
}

static EM_BOOL on_ws_error(int eventType, const EmscriptenWebSocketErrorEvent* event, void* userData) {
    (void)eventType; (void)event; (void)userData;
    LOG_ERROR("WebSocket error");
    return EM_TRUE;
}

// --- Socket interface ---

SOCKET socket_initialize(void) {
    // No real socket needed for WebSocket; return a dummy handle
    return 1;
}

void socket_shutdown(SOCKET socket) {
    (void)socket;
    if (sWebSocket) {
        emscripten_websocket_close(sWebSocket, 1000, "shutdown");
        emscripten_websocket_delete(sWebSocket);
        sWebSocket = 0;
    }
    sWebSocketConnected = false;
    sRecvBufHead = 0;
    sRecvBufTail = 0;
}

// DNS resolution is handled by the browser for WebSocket connections
void resolve_domain(struct sockaddr_in6 *addr) {
    (void)addr;
}

static bool ns_socket_initialize(enum NetworkType networkType, UNUSED bool reconnecting) {
    if (networkType == NT_SERVER) {
        LOG_ERROR("Hosting a server is not supported on the web build");
        return false;
    }

    if (networkType == NT_NONE) {
        // No networking requested — just initialize quietly
        LOG_INFO("Network type NONE, skipping WebSocket connection");
        return true;
    }

    // Client mode
    unsigned int port = configJoinPort;
    if (port == 0) { port = DEFAULT_PORT; }

    sCurSocket = socket_initialize();
    if (sCurSocket == INVALID_SOCKET) { return false; }

    // Construct WebSocket URL
    char wsUrl[256];
    snprintf(wsUrl, sizeof(wsUrl), "ws://%s:%u", configJoinIp, port);
    LOG_INFO("Connecting via WebSocket to %s", wsUrl);

    // Copy hostname for config
    snprintf(gGetHostName, MAX_CONFIG_STRING, "%s", configJoinIp);

    // Create WebSocket
    EmscriptenWebSocketCreateAttributes attr;
    emscripten_websocket_init_create_attributes(&attr);
    attr.url = wsUrl;
    attr.protocols = NULL;
    attr.createOnMainThread = EM_TRUE;

    sWebSocket = emscripten_websocket_new(&attr);
    if (sWebSocket <= 0) {
        LOG_ERROR("Failed to create WebSocket (error %d)", sWebSocket);
        return false;
    }

    // Set up callbacks
    emscripten_websocket_set_onopen_callback(sWebSocket, NULL, on_ws_open);
    emscripten_websocket_set_onmessage_callback(sWebSocket, NULL, on_ws_message);
    emscripten_websocket_set_onclose_callback(sWebSocket, NULL, on_ws_close);
    emscripten_websocket_set_onerror_callback(sWebSocket, NULL, on_ws_error);

    // Open connect menu
    char joinText[128] = { 0 };
    snprintf(joinText, 63, "%s %d", configJoinIp, configJoinPort);
    djui_connect_menu_open();

    gNetworkType = NT_CLIENT;

    LOG_INFO("initialized");

    network_send_mod_list_request();

    return true;
}

static s64 ns_socket_get_id(UNUSED u8 localId) {
    return 0;
}

static char* ns_socket_get_id_str(u8 localId) {
    if (localId == UNKNOWN_LOCAL_INDEX) { localId = 0; }
    static char id_str[64] = { 0 };
    snprintf(id_str, sizeof(id_str), "ws-%d", localId);
    return id_str;
}

static void ns_socket_save_id(u8 localId, UNUSED s64 networkId) {
    SOFT_ASSERT(localId > 0);
    SOFT_ASSERT(localId < MAX_PLAYERS);
    sAddr[localId] = sAddr[0];
    LOG_INFO("saved addr for id %d", localId);
}

static void ns_socket_clear_id(u8 localId) {
    if (localId == 0) { return; }
    SOFT_ASSERT(localId < MAX_PLAYERS);
    memset(&sAddr[localId], 0, sizeof(struct sockaddr_in6));
    LOG_INFO("cleared addr for id %d", localId);
}

static void* ns_socket_dup_addr(u8 localIndex) {
    void* address = malloc(sizeof(struct sockaddr_in6));
    memcpy(address, &sAddr[localIndex], sizeof(struct sockaddr_in6));
    return address;
}

static bool ns_socket_match_addr(void* addr1, void* addr2) {
    return !memcmp(addr1, addr2, sizeof(struct sockaddr_in6));
}

static void ns_socket_update(void) {
    if (gNetworkType == NT_NONE) { return; }

    // Drain the receive ring buffer
    while (ringbuf_available() >= 2) {
        // Peek at the length prefix
        u8 lenBuf[2];
        u32 savedTail = sRecvBufTail;

        ringbuf_read(lenBuf, 2);
        u16 pktLen = (u16)(lenBuf[0] | (lenBuf[1] << 8));

        if (pktLen == 0 || pktLen > PACKET_LENGTH) {
            LOG_ERROR("Invalid packet length %u in ring buffer, resetting", pktLen);
            sRecvBufHead = 0;
            sRecvBufTail = 0;
            break;
        }

        // Check if the full packet is available
        if (ringbuf_available() < pktLen) {
            // Restore tail; packet not fully received yet
            sRecvBufTail = savedTail;
            break;
        }

        u8 data[PACKET_LENGTH + 1];
        ringbuf_read(data, pktLen);

        // All WebSocket packets come from the server (localIndex 0)
        u8 localIndex = UNKNOWN_LOCAL_INDEX;
        network_receive(localIndex, &sAddr[0], data, pktLen);
    }
}

static int ns_socket_send(u8 localIndex, void* address, u8* data, u16 dataLength) {
    (void)address;

    if (localIndex != 0) {
        if (gNetworkType == NT_SERVER && gNetworkPlayers[localIndex].type != NPT_CLIENT) { return SOCKET_ERROR; }
        if (gNetworkType == NT_CLIENT && gNetworkPlayers[localIndex].type != NPT_SERVER) { return SOCKET_ERROR; }
    }

    if (!sWebSocketConnected || !sWebSocket) {
        return SOCKET_ERROR;
    }

    EMSCRIPTEN_RESULT res = emscripten_websocket_send_binary(sWebSocket, data, dataLength);
    if (res != EMSCRIPTEN_RESULT_SUCCESS) {
        LOG_ERROR("WebSocket send failed with result %d, localIndex: %d, packetType: %d, dataLength: %d",
                  res, localIndex, data[0], dataLength);
        return SOCKET_ERROR;
    }

    return NO_ERROR;
}

static void ns_socket_get_lobby_id(char* destination, u32 destLength) {
    snprintf(destination, destLength, "%s", "");
}

static void ns_socket_get_lobby_secret(char* destination, u32 destLength) {
    snprintf(destination, destLength, "%s", "");
}

static void ns_socket_shutdown(UNUSED bool reconnecting) {
    socket_shutdown(sCurSocket);
    sCurSocket = INVALID_SOCKET;
    for (u16 i = 0; i < MAX_PLAYERS; i++) {
        memset(&sAddr[i], 0, sizeof(struct sockaddr_in6));
    }
    LOG_INFO("shutdown");
}

struct NetworkSystem gNetworkSystemSocket = {
    .initialize       = ns_socket_initialize,
    .get_id           = ns_socket_get_id,
    .get_id_str       = ns_socket_get_id_str,
    .save_id          = ns_socket_save_id,
    .clear_id         = ns_socket_clear_id,
    .dup_addr         = ns_socket_dup_addr,
    .match_addr       = ns_socket_match_addr,
    .update           = ns_socket_update,
    .send             = ns_socket_send,
    .get_lobby_id     = ns_socket_get_lobby_id,
    .get_lobby_secret = ns_socket_get_lobby_secret,
    .shutdown         = ns_socket_shutdown,
    .requireServerBroadcast = true,
    .name             = "Socket",
};

#endif
