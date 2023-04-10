#include "libcoopnet.h"
#include "coopnet.h"
#include "pc/network/network.h"
#include "pc/debuglog.h"

#define HOST "localhost"
#define PORT 34197

static uint64_t sLocalUserId = 0;
static uint64_t sLocalLobbyId = 0;
static uint64_t sLocalLobbyOwnerId = 0;
static uint64_t sNetworkUserIds[MAX_PLAYERS] = { 0 };
static enum NetworkType sNetworkType;

static u8 coopnet_user_id_to_local_index(uint64_t userId) {
    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (gNetworkPlayers[i].connected && sNetworkUserIds[i] == userId) {
            return i;
        }
    }
    return UNKNOWN_LOCAL_INDEX;
}

static void coopnet_on_connected(uint64_t userId) {
    sLocalUserId = userId;
    if (sNetworkType == NT_SERVER) {
        coopnet_lobby_create("sm64ex-coop", "beta 999", "n/a", 16);
    } else {
        coopnet_lobby_join(1);
    }
}

static void coopnet_on_peer_connected(UNUSED uint64_t peerId) {
}

static void coopnet_on_peer_disconnected(uint64_t peerId) {
    u8 localIndex = coopnet_user_id_to_local_index(peerId);
    if (localIndex != UNKNOWN_LOCAL_INDEX && gNetworkPlayers[localIndex].connected) {
        network_player_disconnected(gNetworkPlayers[localIndex].globalIndex);
    }
}

static void coopnet_on_receive(uint64_t userId, const uint8_t* data, uint64_t dataLength) {
    sNetworkUserIds[0] = userId;
    u8 localIndex = coopnet_user_id_to_local_index(userId);
    network_receive(localIndex, &userId, (u8*)data, dataLength);
}

static void coopnet_on_lobby_joined(uint64_t lobbyId, uint64_t userId, uint64_t ownerId) {
    LOG_INFO("coopnet_on_lobby_joined!");
    sNetworkUserIds[0] = ownerId;
    sLocalLobbyId = lobbyId;
    sLocalLobbyOwnerId = ownerId;
    if (userId == sLocalUserId && sNetworkType == NT_CLIENT) {
        network_send_mod_list_request();
    }
}


static void coopnet_on_lobby_left(uint64_t lobbyId, uint64_t userId) {
    LOG_INFO("coopnet_on_lobby_left!");
    if (lobbyId == sLocalLobbyId && userId == sLocalUserId) {
        network_shutdown(false, false, true);
    }
}

static bool ns_coopnet_initialize(enum NetworkType networkType) {
    if (coopnet_is_connected()) {
        coopnet_shutdown();
    }

    gCoopNetCallbacks.OnConnected = coopnet_on_connected;
    gCoopNetCallbacks.OnReceive = coopnet_on_receive;
    gCoopNetCallbacks.OnLobbyJoined = coopnet_on_lobby_joined;
    gCoopNetCallbacks.OnLobbyLeft = coopnet_on_lobby_left;
    gCoopNetCallbacks.OnPeerConnected = coopnet_on_peer_connected;
    gCoopNetCallbacks.OnPeerDisconnected = coopnet_on_peer_disconnected;
    sNetworkType = networkType;

    return (coopnet_begin(HOST, PORT) == COOPNET_OK);
}

static s64 ns_coopnet_get_id(u8 localIndex) {
    if (localIndex == 0) { return (s64)sLocalUserId; }
    return (s64)sNetworkUserIds[localIndex];
}

static char* ns_coopnet_get_id_str(u8 localIndex) {
    static char id_str[22] = { 0 };
    if (localIndex == UNKNOWN_LOCAL_INDEX) {
        snprintf(id_str, 22, "???");
    } else {
        snprintf(id_str, 22, "%lld", (long long int)ns_coopnet_get_id(localIndex));
    }
    return id_str;
}

static void ns_coopnet_save_id(u8 localIndex, s64 networkId) {
    SOFT_ASSERT(localIndex > 0);
    SOFT_ASSERT(localIndex < MAX_PLAYERS);
    sNetworkUserIds[localIndex] = (networkId == 0) ? sNetworkUserIds[0] : (u64)networkId;
}

static void ns_coopnet_clear_id(u8 localIndex) {
    if (localIndex == 0) { return; }
    SOFT_ASSERT(localIndex < MAX_PLAYERS);
    sNetworkUserIds[localIndex] = 0;
}

static void* ns_coopnet_dup_addr(u8 localIndex) {
    void* address = malloc(sizeof(u64));
    memcpy(address, &sNetworkUserIds[localIndex], sizeof(u64));
    return address;
}

static bool ns_coopnet_match_addr(void* addr1, void* addr2) {
    return !memcmp(addr1, addr2, sizeof(u64));
}

static void ns_coopnet_update(void) {
    coopnet_update();
}

static int ns_coopnet_network_send(u8 localIndex, void* address, u8* data, u16 dataLength) {
    if (!coopnet_is_connected()) { return 1; }
    //if (gCurLobbyId == 0) { return 2; }

    u64 userId = sNetworkUserIds[localIndex];
    if (localIndex == 0 && address != NULL) { userId = *(u64*)address; }
    coopnet_send_to(userId, data, dataLength);

    return 0;
}

static void ns_coopnet_shutdown(void) {
    coopnet_shutdown();
}

struct NetworkSystem gNetworkSystemCoopNet = {
    .initialize = ns_coopnet_initialize,
    .get_id     = ns_coopnet_get_id,
    .get_id_str = ns_coopnet_get_id_str,
    .save_id    = ns_coopnet_save_id,
    .clear_id   = ns_coopnet_clear_id,
    .dup_addr   = ns_coopnet_dup_addr,
    .match_addr = ns_coopnet_match_addr,
    .update     = ns_coopnet_update,
    .send       = ns_coopnet_network_send,
    .shutdown   = ns_coopnet_shutdown,
    .requireServerBroadcast = false,
    .name       = "CoopNet",
};
