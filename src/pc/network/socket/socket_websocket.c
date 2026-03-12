#ifdef TARGET_WEB
#include <emscripten.h>
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

static SOCKET sCurSocket = INVALID_SOCKET;
static struct sockaddr_in6 sAddr[MAX_PLAYERS] = { 0 };

// Host mode: whether we're hosting through PeerJS
static bool sIsHostMode = false;
// Skip PeerJS destruction on next shutdown (for server→client transition)
static bool sPreservePeerConnection = false;

char gGetHostName[MAX_CONFIG_STRING] = "";

// --- Ring buffer helpers ---

static u32 ringbuf_available(void) {
    return (sRecvBufHead >= sRecvBufTail)
        ? (sRecvBufHead - sRecvBufTail)
        : (WS_RECV_BUF_SIZE - sRecvBufTail + sRecvBufHead);
}

static void ringbuf_read(u8* data, u32 len) {
    for (u32 i = 0; i < len; i++) {
        data[i] = sRecvBuf[sRecvBufTail];
        sRecvBufTail = (sRecvBufTail + 1) % WS_RECV_BUF_SIZE;
    }
}

// --- PeerJS EM_JS interface ---

// Initialize PeerJS with a room ID
EM_JS(int, peer_init, (const char* roomId), {
    var id = UTF8ToString(roomId);
    PeerNetwork.init(id);
    return 0;
});

// Send binary data. In host mode, slotId determines recipient (0=broadcast).
// In client mode, slotId is ignored (always sends to host).
EM_JS(int, peer_send, (int slotId, const uint8_t* data, int len), {
    var buf = HEAPU8.subarray(data, data + len);
    // Must copy since the WASM memory view may be invalidated
    var copy = new Uint8Array(buf);
    PeerNetwork.send(slotId, copy.buffer);
    return 0;
});

// Check if connected
EM_JS(int, peer_is_connected, (), {
    return PeerNetwork.isConnected() ? 1 : 0;
});

// Check if we are the host
EM_JS(int, peer_is_host, (), {
    return PeerNetwork.isHost ? 1 : 0;
});

// Drain received packets into C ring buffer
// Returns number of packets drained
EM_JS(int, peer_drain_recv, (uint8_t* ringBuf, int ringBufSize, int* headPtr, int tailVal), {
    var packets = PeerNetwork.drainRecvBuffer();
    if (packets.length === 0) return 0;

    if (!window._peerDrainLogCount) window._peerDrainLogCount = 0;
    if (window._peerDrainLogCount++ < 5) {
        console.log('[PeerJS drain] packets=' + packets.length + ' ringBuf=' + ringBuf + ' size=' + ringBufSize + ' headPtr=' + headPtr + ' tail=' + tailVal);
    }

    var head = HEAP32[headPtr >> 2];
    var drained = 0;

    for (var i = 0; i < packets.length; i++) {
        var pkt = packets[i];
        var slotId = pkt.slotId;
        var data = pkt.data;
        // Need: 2 bytes slot + 2 bytes length + data
        var needed = 4 + data.length;

        // Check free space
        var used = (head >= tailVal) ? (head - tailVal) : (ringBufSize - tailVal + head);
        var freeSpace = ringBufSize - used - 1;
        if (needed > freeSpace) break;

        // Write slot ID (u16 LE)
        HEAPU8[ringBuf + head] = slotId & 0xFF;
        head = (head + 1) % ringBufSize;
        HEAPU8[ringBuf + head] = (slotId >> 8) & 0xFF;
        head = (head + 1) % ringBufSize;

        // Write length (u16 LE)
        var len = data.length;
        HEAPU8[ringBuf + head] = len & 0xFF;
        head = (head + 1) % ringBufSize;
        HEAPU8[ringBuf + head] = (len >> 8) & 0xFF;
        head = (head + 1) % ringBufSize;

        // Write data
        for (var j = 0; j < len; j++) {
            HEAPU8[ringBuf + head] = data[j];
            head = (head + 1) % ringBufSize;
        }

        drained++;
    }

    HEAP32[headPtr >> 2] = head;
    if (window._peerDrainLogCount <= 5) {
        console.log('[PeerJS drain] drained=' + drained + ' newHead=' + head);
    }
    return drained;
});

// Shutdown PeerJS
EM_JS(void, peer_shutdown, (), {
    PeerNetwork.shutdown();
});

// --- Socket interface ---

SOCKET socket_initialize(void) {
    return 1; // Dummy handle
}

void socket_shutdown(SOCKET socket) {
    (void)socket;
    if (sPreservePeerConnection) {
        // Server→client transition: keep PeerJS alive, just reset ring buffer
        sPreservePeerConnection = false;
    } else {
        peer_shutdown();
    }
    sIsHostMode = false;
    sRecvBufHead = 0;
    sRecvBufTail = 0;
}

// DNS resolution is handled by the browser/PeerJS
void resolve_domain(struct sockaddr_in6 *addr) {
    (void)addr;
}

// Track if we've sent the initial mod list request (only for clients)
static bool sSentModListRequest = false;
// Track if PeerJS was connected last frame (to detect new connections)
static bool sWasPeerConnected = false;
// Track if PeerJS role has been resolved
static bool sRoleResolved = false;

static bool ns_socket_initialize(enum NetworkType networkType, UNUSED bool reconnecting) {
    if (networkType == NT_NONE) {
        LOG_INFO("Network type NONE, skipping PeerJS connection");
        return true;
    }

    sCurSocket = socket_initialize();
    if (sCurSocket == INVALID_SOCKET) { return false; }

    // Get room ID from URL params or config
    const char* roomId = emscripten_run_script_string(
        "(new URLSearchParams(window.location.search)).get('room') || 'default'");

    // If configJoinIp has a value, use it as the room ID (set from DJUI or URL ?room= param)
    if (configJoinIp[0] != '\0') {
        roomId = configJoinIp;
    }

    LOG_INFO("PeerJS init: room='%s' networkType=%d", roomId, networkType);

    // Only initialize PeerJS if not already connected (avoids double-init
    // when ?room= flow transitions from NT_SERVER to NT_CLIENT)
    bool alreadyConnected = peer_is_connected();
    if (!alreadyConnected) {
        peer_init(roomId);
        // Reset role detection flags only for fresh connections
        sSentModListRequest = false;
        sWasPeerConnected = false;
        sRoleResolved = false;
        sIsHostMode = (networkType == NT_SERVER);
    } else {
        // Already connected (server→client transition) — keep role flags,
        // just update the mode
        sIsHostMode = (networkType == NT_SERVER);
    }

    return true;
}

static s64 ns_socket_get_id(UNUSED u8 localId) {
    return 0;
}

static char* ns_socket_get_id_str(u8 localId) {
    if (localId == UNKNOWN_LOCAL_INDEX) { localId = 0; }
    static char id_str[64] = { 0 };
    snprintf(id_str, sizeof(id_str), "peer-%d", localId);
    return id_str;
}

static void ns_socket_save_id(u8 localId, UNUSED s64 networkId) {
    SOFT_ASSERT(localId > 0);
    SOFT_ASSERT(localId < MAX_PLAYERS);
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

    // Update isHost flag from PeerJS state
    sIsHostMode = peer_is_host();

    // Detect when PeerJS connects and handle role
    bool isConnected = peer_is_connected();
    if (!sRoleResolved && isConnected) {
        sRoleResolved = true;
        if (!sIsHostMode && !sSentModListRequest) {
            // We're a client but started as NT_SERVER via djui_panel_do_host.
            // Just switch the type and send the handshake — no shutdown needed.
            printf("[PeerJS C] We are a CLIENT — switching to NT_CLIENT\n");
            gNetworkType = NT_CLIENT;
            network_send_mod_list_request();
            sSentModListRequest = true;
        } else if (sIsHostMode) {
            printf("[PeerJS C] We are the HOST\n");
        }
    }

    // Drain PeerJS received packets into ring buffer
    peer_drain_recv(sRecvBuf, WS_RECV_BUF_SIZE, (int*)&sRecvBufHead, sRecvBufTail);

    // Process ring buffer: each entry is [u16 slotId][u16 packetLen][packetData...]
    while (ringbuf_available() >= 4) {
        u8 hdrBuf[4];
        u32 savedTail = sRecvBufTail;

        ringbuf_read(hdrBuf, 4);
        u16 slotId = (u16)(hdrBuf[0] | (hdrBuf[1] << 8));
        u16 pktLen = (u16)(hdrBuf[2] | (hdrBuf[3] << 8));

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

        u8 rawData[PACKET_LENGTH];
        ringbuf_read(rawData, pktLen);

        if (sIsHostMode) {
            // HOST MODE: slotId from PeerJS identifies the client
            u8 localIndex = (slotId > 0 && slotId < MAX_PLAYERS) ? (u8)slotId : UNKNOWN_LOCAL_INDEX;

            // Store the slot ID so we can send back to this client
            if (localIndex != UNKNOWN_LOCAL_INDEX) {
                sAddr[localIndex].sin6_port = slotId;
            }

            network_receive(localIndex, &sAddr[localIndex < MAX_PLAYERS ? localIndex : 0], rawData, pktLen);
        } else {
            // CLIENT MODE: all packets come from host
            u8 localIndex = UNKNOWN_LOCAL_INDEX;
            network_receive(localIndex, &sAddr[0], rawData, pktLen);
        }
    }
}

static int ns_socket_send(u8 localIndex, void* address, u8* data, u16 dataLength) {
    (void)address;

    if (!peer_is_connected()) {
        return SOCKET_ERROR;
    }

    if (sIsHostMode) {
        // HOST MODE: send to specific slot or broadcast (slot 0)
        u16 slotId = 0;
        if (localIndex > 0 && localIndex < MAX_PLAYERS) {
            slotId = sAddr[localIndex].sin6_port;
        }
        static int sSendLogCount = 0;
        if (++sSendLogCount <= 20 && slotId > 0) {
            printf("[PeerJS C] HOST send: localIndex=%d slotId=%d len=%d\n", localIndex, slotId, dataLength);
        }
        peer_send(slotId, data, dataLength);
    } else {
        // CLIENT MODE: send to host
        if (localIndex != 0) {
            if (gNetworkType == NT_CLIENT && gNetworkPlayers[localIndex].type != NPT_SERVER) { return SOCKET_ERROR; }
        }
        peer_send(0, data, dataLength);
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
