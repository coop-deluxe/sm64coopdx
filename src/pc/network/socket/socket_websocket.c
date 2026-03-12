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
#define WS_RECV_BUF_SIZE (128 * 1024)
static u8 sRecvBuf[WS_RECV_BUF_SIZE];
static u32 sRecvBufHead = 0;
static u32 sRecvBufTail = 0;

static EMSCRIPTEN_WEBSOCKET_T sWebSocket = 0;
static bool sWebSocketConnected = false;
static SOCKET sCurSocket = INVALID_SOCKET;
static struct sockaddr_in6 sAddr[MAX_PLAYERS] = { 0 };

// Host mode: whether we're hosting through the proxy
static bool sIsHostMode = false;

// Proxy port (proxy runs on same host as the page was loaded from)
#define DEFAULT_PROXY_PORT 8765

// Get the hostname the page was loaded from (e.g. "10.0.0.76" or "localhost")
static const char* get_page_hostname(void) {
    static char hostname[256] = {0};
    if (hostname[0] == '\0') {
        const char* h = emscripten_run_script_string("window.location.hostname");
        if (h && h[0]) {
            snprintf(hostname, sizeof(hostname), "%s", h);
        } else {
            snprintf(hostname, sizeof(hostname), "localhost");
        }
    }
    return hostname;
}

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
    LOG_INFO("WebSocket connected (host mode: %s)", sIsHostMode ? "yes" : "no");
    sWebSocketConnected = true;
    return EM_TRUE;
}

static EM_BOOL on_ws_message(int eventType, const EmscriptenWebSocketMessageEvent* event, void* userData) {
    (void)eventType; (void)userData;

    if (!event->isText && event->numBytes > 0) {
        u16 pktLen = (u16)event->numBytes;
        u32 needed = (u32)pktLen + 2; // 2-byte length prefix in ring buffer
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
    return 1; // Dummy handle
}

void socket_shutdown(SOCKET socket) {
    (void)socket;
    printf("[Web] socket_shutdown called, sWebSocket=%d", sWebSocket);
    if (sWebSocket) {
        printf("[Web] closing WebSocket...");
        emscripten_websocket_close(sWebSocket, 1000, "shutdown");
        emscripten_websocket_delete(sWebSocket);
        sWebSocket = 0;
    }
    sWebSocketConnected = false;
    sIsHostMode = false;
    sRecvBufHead = 0;
    sRecvBufTail = 0;
}

// DNS resolution is handled by the browser
void resolve_domain(struct sockaddr_in6 *addr) {
    (void)addr;
}

// --- Helper: create WebSocket connection to proxy ---

static bool ws_connect(const char* wsUrl) {
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

    emscripten_websocket_set_onopen_callback(sWebSocket, NULL, on_ws_open);
    emscripten_websocket_set_onmessage_callback(sWebSocket, NULL, on_ws_message);
    emscripten_websocket_set_onclose_callback(sWebSocket, NULL, on_ws_close);
    emscripten_websocket_set_onerror_callback(sWebSocket, NULL, on_ws_error);

    return true;
}

static bool ns_socket_initialize(enum NetworkType networkType, UNUSED bool reconnecting) {
    if (networkType == NT_NONE) {
        LOG_INFO("Network type NONE, skipping WebSocket connection");
        return true;
    }

    sCurSocket = socket_initialize();
    if (sCurSocket == INVALID_SOCKET) { return false; }

    char wsUrl[512];

    if (networkType == NT_SERVER) {
        // HOST MODE: Connect to proxy with ?host=PORT
        // The proxy will open a UDP listener for native clients
        sIsHostMode = true;
        unsigned int hostPort = configHostPort;
        if (hostPort == 0) { hostPort = DEFAULT_PORT; }

        // Use proxy address — configJoinIp may be empty, use default proxy
        const char* proxyHost = get_page_hostname();
        unsigned int proxyPort = DEFAULT_PROXY_PORT;

        // If configJoinIp has a value like "proxyhost:proxyport", parse it
        // Otherwise use defaults
        if (configJoinIp[0] != '\0') {
            proxyHost = configJoinIp;
        }

        snprintf(wsUrl, sizeof(wsUrl), "ws://%s:%u/?host=%u", proxyHost, proxyPort, hostPort);
        LOG_INFO("HOST MODE: Connecting to proxy at %s (UDP port %u)", wsUrl, hostPort);

        if (!ws_connect(wsUrl)) { return false; }

        LOG_INFO("Host mode initialized via proxy");
        return true;

    } else {
        // CLIENT MODE: Connect to proxy with ?target=HOST:PORT
        sIsHostMode = false;
        unsigned int port = configJoinPort;
        if (port == 0) { port = DEFAULT_PORT; }

        // Check if configJoinIp looks like it's already a WebSocket URL
        if (strncmp(configJoinIp, "ws://", 5) == 0 || strncmp(configJoinIp, "wss://", 6) == 0) {
            // Direct WebSocket URL to proxy
            snprintf(wsUrl, sizeof(wsUrl), "%s", configJoinIp);
        } else {
            // Connect to proxy, which forwards to the target UDP server
            snprintf(wsUrl, sizeof(wsUrl), "ws://%s:%u/?target=%s:%u",
                get_page_hostname(), DEFAULT_PROXY_PORT, configJoinIp, port);
        }

        printf("[Web] CLIENT MODE: Connecting via %s", wsUrl);
        printf("[Web] CLIENT MODE: configJoinIp='%s' configJoinPort=%d", configJoinIp, configJoinPort);
        snprintf(gGetHostName, MAX_CONFIG_STRING, "%s", configJoinIp);

        if (!ws_connect(wsUrl)) { printf("[Web] ws_connect failed!"); return false; }

        djui_connect_menu_open();
        gNetworkType = NT_CLIENT;

        printf("[Web] Client mode initialized, sending mod list request");
        network_send_mod_list_request();
        return true;
    }
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
    // In host mode, the proxy assigns slot IDs that map to localIndex.
    // Store the slot ID in the sin6_port field for tracking.
    sAddr[localId].sin6_port = localId;
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

    while (ringbuf_available() >= 2) {
        u8 lenBuf[2];
        u32 savedTail = sRecvBufTail;

        ringbuf_read(lenBuf, 2);
        u16 pktLen = (u16)(lenBuf[0] | (lenBuf[1] << 8));

        if (pktLen == 0 || pktLen > PACKET_LENGTH) {
            LOG_ERROR("Invalid packet length %u, resetting ring buffer", pktLen);
            sRecvBufHead = 0;
            sRecvBufTail = 0;
            break;
        }

        if (ringbuf_available() < pktLen) {
            sRecvBufTail = savedTail;
            break;
        }

        u8 rawData[PACKET_LENGTH + 4];
        ringbuf_read(rawData, pktLen);

        if (sIsHostMode && pktLen >= 3) {
            // HOST MODE: first 2 bytes are the proxy's slot ID
            u16 slotId = (u16)(rawData[0] | (rawData[1] << 8));
            u8* packetData = rawData + 2;
            u16 packetLen = pktLen - 2;

            // Map slot ID to localIndex
            // The proxy assigns slot IDs starting from 1, which maps nicely to localIndex
            u8 localIndex = (slotId > 0 && slotId < MAX_PLAYERS) ? (u8)slotId : UNKNOWN_LOCAL_INDEX;

            // Store the slot ID so we can send back to this client
            if (localIndex != UNKNOWN_LOCAL_INDEX) {
                sAddr[localIndex].sin6_port = slotId;
            }

            network_receive(localIndex, &sAddr[localIndex < MAX_PLAYERS ? localIndex : 0], packetData, packetLen);
        } else {
            // CLIENT MODE: raw packet from server
            u8 localIndex = UNKNOWN_LOCAL_INDEX;
            network_receive(localIndex, &sAddr[0], rawData, pktLen);
        }
    }
}

static int ns_socket_send(u8 localIndex, void* address, u8* data, u16 dataLength) {
    (void)address;

    if (!sWebSocketConnected || !sWebSocket) {
        return SOCKET_ERROR;
    }

    if (sIsHostMode) {
        // HOST MODE: prepend 2-byte slot ID
        // localIndex 0 or UNKNOWN = broadcast (slot 0)
        u16 slotId = 0;
        if (localIndex > 0 && localIndex < MAX_PLAYERS) {
            slotId = sAddr[localIndex].sin6_port;
        }

        u8 buf[PACKET_LENGTH + 2];
        buf[0] = (u8)(slotId & 0xFF);
        buf[1] = (u8)((slotId >> 8) & 0xFF);
        memcpy(buf + 2, data, dataLength);

        EMSCRIPTEN_RESULT res = emscripten_websocket_send_binary(sWebSocket, buf, dataLength + 2);
        if (res != EMSCRIPTEN_RESULT_SUCCESS) {
            LOG_ERROR("WebSocket send failed (host mode, slot %u): result %d", slotId, res);
            return SOCKET_ERROR;
        }
    } else {
        // CLIENT MODE: send raw packet
        if (localIndex != 0) {
            if (gNetworkType == NT_CLIENT && gNetworkPlayers[localIndex].type != NPT_SERVER) { return SOCKET_ERROR; }
        }

        EMSCRIPTEN_RESULT res = emscripten_websocket_send_binary(sWebSocket, data, dataLength);
        if (res != EMSCRIPTEN_RESULT_SUCCESS) {
            LOG_ERROR("WebSocket send failed (client mode): result %d", res);
            return SOCKET_ERROR;
        }
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
    sIsHostMode = false;
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
