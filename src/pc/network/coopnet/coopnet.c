#include "libcoopnet.h"
#include "coopnet.h"
#include "coopnet_id.h"
#include "pc/network/network.h"
#include "pc/network/version.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_popup.h"
#include "pc/mods/mods.h"
#include "pc/debuglog.h"

#ifdef COOPNET

#define CN_GAME_STR "sm64ex-coop"

uint64_t gCoopNetDesiredLobby = 0;

static uint64_t sLocalLobbyId = 0;
static uint64_t sLocalLobbyOwnerId = 0;
static enum NetworkType sNetworkType;

static CoopNetRc coopnet_initialize(void);

bool ns_coopnet_query(QueryCallbackPtr callback, QueryFinishCallbackPtr finishCallback, const char* password) {
    gCoopNetCallbacks.OnLobbyListGot = callback;
    gCoopNetCallbacks.OnLobbyListFinish = finishCallback;
    if (coopnet_initialize() != COOPNET_OK) { return false; }
    if (coopnet_lobby_list_get(CN_GAME_STR, password) != COOPNET_OK) { return false; }
    return true;
}

static void coopnet_on_connected(uint64_t userId) {
    coopnet_set_local_user_id(userId);
}

static void coopnet_on_disconnected(void) {
    LOG_INFO("Coopnet shutdown!");
    djui_popup_create(DLANG(NOTIF, COOPNET_DISCONNECTED), 2);
    coopnet_shutdown();
    gCoopNetCallbacks.OnLobbyListGot = NULL;
    gCoopNetCallbacks.OnLobbyListFinish = NULL;
}

static void coopnet_on_peer_disconnected(uint64_t peerId) {
    u8 localIndex = coopnet_user_id_to_local_index(peerId);
    if (localIndex != UNKNOWN_LOCAL_INDEX && gNetworkPlayers[localIndex].connected) {
        network_player_disconnected(gNetworkPlayers[localIndex].globalIndex);
    }
}

static void coopnet_on_receive(uint64_t userId, const uint8_t* data, uint64_t dataLength) {
    coopnet_set_user_id(0, userId);
    u8 localIndex = coopnet_user_id_to_local_index(userId);
    network_receive(localIndex, &userId, (u8*)data, dataLength);
}

static void coopnet_on_lobby_joined(uint64_t lobbyId, uint64_t userId, uint64_t ownerId, uint64_t destId) {
    LOG_INFO("coopnet_on_lobby_joined!");
    coopnet_set_user_id(0, ownerId);
    sLocalLobbyId = lobbyId;
    sLocalLobbyOwnerId = ownerId;

    if (userId == coopnet_get_local_user_id()) {
        coopnet_clear_dest_ids();
    }

    coopnet_save_dest_id(userId, destId);

    if (userId == coopnet_get_local_user_id() && gNetworkType == NT_CLIENT) {
        network_send_mod_list_request();
    }
}

static void coopnet_on_lobby_left(uint64_t lobbyId, uint64_t userId) {
    LOG_INFO("coopnet_on_lobby_left!");
    coopnet_clear_dest_id(userId);
    if (lobbyId == sLocalLobbyId && userId == coopnet_get_local_user_id()) {
        network_shutdown(false, false, true);
    }
}

static bool ns_coopnet_initialize(enum NetworkType networkType) {
    sNetworkType = networkType;
    return coopnet_is_connected() 
        ? true
        : (coopnet_initialize() == COOPNET_OK);
}

static char* ns_coopnet_get_id_str(u8 localIndex) {
    static char id_str[32] = { 0 };
    if (localIndex == UNKNOWN_LOCAL_INDEX) {
        snprintf(id_str, 32, "???");
    } else {
        uint64_t userId = ns_coopnet_get_id(localIndex);
        uint64_t destId = coopnet_get_dest_id(userId);
        snprintf(id_str, 32, "%" PRIu64 "", destId);
    }
    return id_str;
}

static bool ns_coopnet_match_addr(void* addr1, void* addr2) {
    return !memcmp(addr1, addr2, sizeof(u64));
}

bool ns_coopnet_is_connected(void) {
    return coopnet_is_connected();
}

void ns_coopnet_update(void) {
    if (!coopnet_is_connected()) { return; }

    coopnet_update();
    if (gNetworkType != NT_NONE && sNetworkType != NT_NONE) {
        if (sNetworkType == NT_SERVER) {
            LOG_INFO("Create lobby");
            char mode[64] = "";
            mods_get_main_mod_name(mode, 64);
            coopnet_lobby_create(CN_GAME_STR, get_version(), configPlayerName, mode, (uint16_t)configAmountofPlayers, "");
        } else if (sNetworkType == NT_CLIENT) {
            LOG_INFO("Join lobby");
            coopnet_lobby_join(gCoopNetDesiredLobby, "");
        }
        sNetworkType = NT_NONE;
    }
}

static int ns_coopnet_network_send(u8 localIndex, void* address, u8* data, u16 dataLength) {
    if (!coopnet_is_connected()) { return 1; }
    //if (gCurLobbyId == 0) { return 2; }
    u64 userId = coopnet_raw_get_id(localIndex);
    if (localIndex == 0 && address != NULL) { userId = *(u64*)address; }
    coopnet_send_to(userId, data, dataLength);

    return 0;
}

static void ns_coopnet_shutdown(void) {
    LOG_INFO("Coopnet shutdown!");
    coopnet_shutdown();
    gCoopNetCallbacks.OnLobbyListGot = NULL;
    gCoopNetCallbacks.OnLobbyListFinish = NULL;
}

static CoopNetRc coopnet_initialize(void) {

    gCoopNetCallbacks.OnConnected = coopnet_on_connected;
    gCoopNetCallbacks.OnDisconnected = coopnet_on_disconnected;
    gCoopNetCallbacks.OnReceive = coopnet_on_receive;
    gCoopNetCallbacks.OnLobbyJoined = coopnet_on_lobby_joined;
    gCoopNetCallbacks.OnLobbyLeft = coopnet_on_lobby_left;
    gCoopNetCallbacks.OnPeerDisconnected = coopnet_on_peer_disconnected;

    if (coopnet_is_connected()) { return COOPNET_OK; }

    CoopNetRc rc = coopnet_begin(configCoopNetIp, configCoopNetPort);
    if (rc == COOPNET_FAILED) {
        djui_popup_create(DLANG(NOTIF, COOPNET_CONNECTION_FAILED), 2);
    }
    return rc;
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

#endif
