#include <stdio.h>
#include "network_player.h"
#include "game/chat.h"
#include "game/mario_misc.h"
#include "reservation_area.h"
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
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (gNetworkPlayers[i].connected) { count++; }
    }
    return count;
}

struct NetworkPlayer* network_player_from_global_index(u8 globalIndex) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        if (gNetworkPlayers[i].globalIndex == globalIndex) {
            return &gNetworkPlayers[i];
        }
    }
    return NULL;
}

struct NetworkPlayer* get_network_player_from_level(s16 courseNum, s16 actNum, s16 levelNum) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected)                 { continue; }
        if (!np->currLevelSyncValid)        { continue; }
        if (np->currCourseNum != courseNum) { continue; }
        if (np->currActNum != actNum)       { continue; }
        if (np->currLevelNum != levelNum)   { continue; }
        return np;
    }
    return NULL;
}

struct NetworkPlayer* get_network_player_from_area(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected)                 { continue; }
        if (!np->currLevelSyncValid)        { continue; }
        if (!np->currAreaSyncValid)         { continue; }
        if (np->currCourseNum != courseNum) { continue; }
        if (np->currActNum    != actNum)    { continue; }
        if (np->currLevelNum  != levelNum)  { continue; }
        if (np->currAreaIndex != areaIndex) { continue; }
        return np;
    }
    return NULL;
}

struct NetworkPlayer* get_network_player_smallest_global(void) {
    struct NetworkPlayer* lNp = gNetworkPlayerLocal;
    struct NetworkPlayer* smallest = gNetworkPlayerLocal;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected)                          { continue; }
        if (!np->currLevelSyncValid)                 { continue; }
        if (!np->currAreaSyncValid)                  { continue; }
        if (np->currCourseNum != lNp->currCourseNum) { continue; }
        if (np->currActNum    != lNp->currActNum)    { continue; }
        if (np->currLevelNum  != lNp->currLevelNum)  { continue; }
        if (np->currAreaIndex != lNp->currAreaIndex) { continue; }
        if (np->globalIndex < smallest->globalIndex) { smallest = np; }
    }
    return smallest;
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
        struct NetworkPlayer* np = &gNetworkPlayers[0];
        if (np->connected) {
            np->globalIndex = globalIndex;
            return 0;
        }
        memset(np, 0, sizeof(struct NetworkPlayer));
        np->connected = true;
        np->type = type;
        np->localIndex = 0;
        np->globalIndex = globalIndex;
        np->currLevelAreaSeqId = 0;

        extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
        np->currCourseNum      = gCurrCourseNum;
        np->currActNum         = gCurrActStarNum;
        np->currLevelNum       = gCurrLevelNum;
        np->currAreaIndex      = gCurrAreaIndex;
        np->currLevelSyncValid = false;
        np->currAreaSyncValid  = false;

        gNetworkPlayerLocal = np;

        if (gNetworkType == NT_SERVER) {
            gNetworkPlayerServer = gNetworkPlayerLocal;
        }
        packet_ordered_clear(globalIndex);
        return 0;
    }

    if (globalIndex != UNKNOWN_GLOBAL_INDEX) {
        for (int i = 1; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected) { continue; }
            if (np->globalIndex != globalIndex) { continue; }
            np->localIndex = i;
            np->lastReceived = clock();
            if (gNetworkType == NT_SERVER || type == NPT_SERVER) { gNetworkSystem->save_id(i, 0); }
            LOG_ERROR("player connected, reusing local %d, global %d, duplicate event?", i, globalIndex);
            return i;
        }
    }

    for (int i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (np->connected) { continue; }
        memset(np, 0, sizeof(struct NetworkPlayer));
        np->connected = true;
        np->currLevelAreaSeqId = 0;
        if (!np->currAreaSyncValid) {
            np->currCourseNum      = -1;
            np->currActNum         = -1;
            np->currLevelNum       = -1;
            np->currAreaIndex      = -1;
            np->currLevelSyncValid = false;
            np->currAreaSyncValid  = false;
        }
        np->fadeOpacity = 0;
        np->localIndex = i;
        np->globalIndex = (gNetworkType == NT_SERVER) ? i : globalIndex;
        np->type = type;
        np->lastReceived = clock();
        if (gNetworkType == NT_SERVER || type == NPT_SERVER) { gNetworkSystem->save_id(i, 0); }
        for (int j = 0; j < MAX_SYNC_OBJECTS; j++) { gSyncObjects[j].rxEventId[i] = 0; }
        if (type == NPT_SERVER) { gNetworkPlayerServer = np; }
        else { chat_add_message_ext("player connected", CMT_SYSTEM, get_player_color(np->globalIndex, 0)); }
        LOG_INFO("player connected, local %d, global %d", i, np->globalIndex);
        packet_ordered_clear(np->globalIndex);
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
        np->currCourseNum      = -1;
        np->currActNum         = -1;
        np->currLevelNum       = -1;
        np->currAreaIndex      = -1;
        np->currLevelSyncValid = false;
        np->currAreaSyncValid  = false;
        gNetworkSystem->clear_id(i);
        for (int j = 0; j < MAX_SYNC_OBJECTS; j++) { gSyncObjects[j].rxEventId[i] = 0; }
        LOG_INFO("player disconnected, local %d, global %d", i, globalIndex);
        chat_add_message_ext("player disconnected", CMT_SYSTEM, get_player_color(globalIndex, 0));
        packet_ordered_clear(globalIndex);
        reservation_area_change(np);
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
