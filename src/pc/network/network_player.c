#include <stdio.h>
#include "network_player.h"
#include "game/chat.h"
#include "pc/debuglog.h"

struct NetworkPlayer gNetworkPlayers[MAX_PLAYERS] = { 0 };
struct NetworkPlayer* gNetworkPlayerLocal = NULL;
struct NetworkPlayer* gNetworkPlayerServer = NULL;

bool network_player_any_connected(void) {
    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (gNetworkPlayers[i].connected) { return true; }
    }
    return false;
}

u8 network_player_connected_count(void) {
    u8 count = 0;
    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (gNetworkPlayers[i].connected) { count++; }
    }
    return count;
}

void network_player_update(void) {
    float elapsed = (clock() - gLastNetworkSend) / (float)CLOCKS_PER_SEC;
    if (elapsed > NETWORK_PLAYER_TIMEOUT / 3.0f) {
        network_send_keep_alive();
    }

#ifndef DEVELOPMENT
    if (gNetworkType == NT_SERVER) {
        for (int i = 1; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected) { continue; }
            float elapsed = (clock() - np->lastReceived) / (float)CLOCKS_PER_SEC;
            if (elapsed > NETWORK_PLAYER_TIMEOUT) {
                network_player_disconnected(i);
            }
        }
    } else if (gNetworkType == NT_CLIENT) {
        bool connectionAlive = false;
        for (int i = 1; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected) { continue; }
            float elapsed = (clock() - np->lastReceived) / (float)CLOCKS_PER_SEC;
            if (elapsed <= NETWORK_PLAYER_TIMEOUT * 1.5f) {
                connectionAlive = true;
                break;
            }
        }
        if (!connectionAlive) {
            network_shutdown();
        }
    }
#endif
}

u8 network_player_connected(enum NetworkPlayerType type, u8 globalIndex) {
    if (type == NPT_LOCAL) {
        gNetworkPlayers[0].connected = true;
        gNetworkPlayers[0].type = type;
        gNetworkPlayers[0].localIndex = 0;
        gNetworkPlayers[0].globalIndex = globalIndex;
        gNetworkPlayerLocal = &gNetworkPlayers[0];
        return 0;
    }

    if (globalIndex != UNKNOWN_GLOBAL_INDEX) {
        for (int i = 1; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected) { continue; }
            if (np->globalIndex != globalIndex) { continue; }
            np->localIndex = i;
            np->lastReceived = clock();
            gNetworkSystem->save_id(i);
            LOG_ERROR("player connected, reusing local %d, global %d, duplicate event?", i, globalIndex);
            return i;
        }
    }

    for (int i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (np->connected) { continue; }
        np->connected = true;
        np->localIndex = i;
        np->globalIndex = (gNetworkType == NT_SERVER) ? i : globalIndex;
        np->type = type;
        np->lastReceived = clock();
        gNetworkSystem->save_id(i);
        if (type == NPT_SERVER) { gNetworkPlayerServer = np; }
        chat_add_message("player connected", CMT_SYSTEM);
        LOG_INFO("player connected, local %d, global %d", i, globalIndex);
        extern s16 sCurrPlayMode;
        if (gNetworkType == NT_SERVER && sCurrPlayMode == PLAY_MODE_SYNC_LEVEL) {
            network_send_level_warp_repeat();
        }
        return i;
    }

    LOG_ERROR("player connected, but unable to allocate!");
    return UNKNOWN_GLOBAL_INDEX;
}

u8 network_player_disconnected(u8 globalIndex) {
    if (globalIndex == 0) {
        if (gNetworkType == NT_SERVER) {
            LOG_ERROR("player disconnected, but it's local.. this shouldn't happen!");
            return UNKNOWN_GLOBAL_INDEX;
        } else {
            network_shutdown();
        }
    }

    if (globalIndex == UNKNOWN_GLOBAL_INDEX) {
        LOG_ERROR("player disconnected, but unknown global index!");
        return UNKNOWN_GLOBAL_INDEX;
    }

    for (int i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }
        if (np->globalIndex != globalIndex) { continue; }
        if (gNetworkType == NT_SERVER) { network_send_leaving(np->globalIndex); }
        np->connected = false;
        gNetworkSystem->clear_id(i);
        LOG_INFO("player disconnected, local %d, global %d", i, globalIndex);
        chat_add_message("player disconnected", CMT_SYSTEM);
        return i;
    }
    return UNKNOWN_GLOBAL_INDEX;
}

void network_player_shutdown(void) {
    gNetworkPlayerLocal = NULL;
    gNetworkPlayerServer = NULL;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* networkPlayer = &gNetworkPlayers[i];
        networkPlayer->connected = false;
        gNetworkSystem->clear_id(i);
    }

    chat_add_message("network shutdown", CMT_SYSTEM);
    LOG_INFO("cleared all network players");
}
