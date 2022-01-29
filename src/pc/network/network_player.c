#include <stdio.h>
#include "network_player.h"
#include "game/mario_misc.h"
#include "reservation_area.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "game/area.h"
#include "game/level_info.h"

struct NetworkPlayer gNetworkPlayers[MAX_PLAYERS] = { 0 };
struct NetworkPlayer* gNetworkPlayerLocal = NULL;
struct NetworkPlayer* gNetworkPlayerServer = NULL;
static char sDefaultPlayerName[] = "Player";

void network_player_init(void) {
    gNetworkPlayers[0].modelIndex = (configPlayerModel < CT_MAX) ? configPlayerModel : 0;
    gNetworkPlayers[0].paletteIndex = configPlayerPalette;
}

void network_player_update_model(u8 localIndex) {
    struct MarioState* m = &gMarioStates[localIndex];
    if (m == NULL) { return; }
    m->character = &gCharacters[gNetworkPlayers[localIndex].modelIndex];
    if (m->marioObj == NULL) { return; }
    m->marioObj->header.gfx.sharedChild = gLoadedGraphNodes[m->character->modelId];
}

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
    if (!network_player_any_connected()) { return; }

#ifndef DEVELOPMENT
    if (gNetworkType == NT_SERVER) {
        for (int i = 1; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected) { continue; }
            float elapsed = (clock_elapsed() - np->lastReceived);
            if (elapsed > NETWORK_PLAYER_TIMEOUT) {
                LOG_INFO("dropping player %d", i);
                network_player_disconnected(i);
                continue;
            }
            elapsed = (clock_elapsed() - np->lastSent);
            if (elapsed > NETWORK_PLAYER_TIMEOUT / 3.0f) {
                network_send_keep_alive(np->localIndex);
            }
        }
    } else if (gNetworkType == NT_CLIENT) {
        struct NetworkPlayer* np = gNetworkPlayerServer;
        if (!np->connected) { return; }
        float elapsed = (clock_elapsed() - np->lastReceived);

        if (elapsed > NETWORK_PLAYER_TIMEOUT * 1.5f) {
            LOG_INFO("dropping due to no server connectivity");
            network_shutdown(false);
        }

        elapsed = (clock_elapsed() - np->lastSent);
        if (elapsed > NETWORK_PLAYER_TIMEOUT / 3.0f) {
            network_send_keep_alive(np->localIndex);
        }
    }
#endif
}

u8 network_player_connected(enum NetworkPlayerType type, u8 globalIndex, u8 modelIndex, u8 paletteIndex, char* name) {
    // ensure that a name is given
    if (name[0] == '\0') {
        name = sDefaultPlayerName;
    }
    if (modelIndex >= CT_MAX) { modelIndex = 0; }

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
        network_player_update_course_level(np, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex);
        np->currLevelSyncValid = false;
        np->currAreaSyncValid  = false;
        np->modelIndex         = modelIndex;
        np->paletteIndex       = paletteIndex;
        snprintf(np->name, MAX_PLAYER_STRING, "%s", name);
        network_player_update_model(0);

        for (int j = 0; j < MAX_RX_SEQ_IDS; j++) { np->rxSeqIds[j] = 0; np->rxPacketHash[j] = 0; }
        np->onRxSeqId = 0;

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
            np->lastReceived = clock_elapsed();
            np->lastSent = clock_elapsed();
            np->modelIndex = modelIndex;
            np->paletteIndex = paletteIndex;
            np->localLevelMatch = (np->currCourseNum == gCurrCourseNum && np->currActNum == gCurrActStarNum && np->currLevelNum == gCurrLevelNum);
            snprintf(np->name, MAX_PLAYER_STRING, "%s", name);
            network_player_update_model(i);
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
        if (gNetworkType == NT_SERVER && !np->currAreaSyncValid) {
            network_player_update_course_level(np, 0, 0, 16, 1);
            np->currLevelSyncValid = false;
            np->currAreaSyncValid  = false;
        }
        np->fadeOpacity = 0;
        np->localIndex = i;
        np->globalIndex = (gNetworkType == NT_SERVER) ? i : globalIndex;
        np->type = type;
        np->lastReceived = clock_elapsed();
        np->lastSent = clock_elapsed();
        np->modelIndex = modelIndex;
        np->paletteIndex = paletteIndex;
        np->localLevelMatch = (np->currCourseNum == gCurrCourseNum && np->currActNum == gCurrActStarNum && np->currLevelNum == gCurrLevelNum);
        snprintf(np->name, MAX_PLAYER_STRING, "%s", name);
        network_player_update_model(i);
        if (gNetworkType == NT_SERVER || type == NPT_SERVER) { gNetworkSystem->save_id(i, 0); }
        for (int j = 0; j < MAX_SYNC_OBJECTS; j++) { gSyncObjects[j].rxEventId[i] = 0; }
        for (int j = 0; j < MAX_RX_SEQ_IDS; j++) { np->rxSeqIds[j] = 0; np->rxPacketHash[j] = 0; }
        np->onRxSeqId = 0;
        if (type == NPT_SERVER) {
            gNetworkPlayerServer = np;
        } else {
            // display popup
            u8* rgb = get_player_color(np->paletteIndex, 0);
            char popupMsg[128] = { 0 };
            snprintf(popupMsg, 128, "\\#%02x%02x%02x\\%s\\#dcdcdc\\ connected", rgb[0], rgb[1], rgb[2], np->name);
            djui_popup_create(popupMsg, 1);
        }
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
            network_shutdown(true);
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
        network_forget_all_reliable_from(i);
        for (int j = 0; j < MAX_SYNC_OBJECTS; j++) { gSyncObjects[j].rxEventId[i] = 0; }
        LOG_INFO("player disconnected, local %d, global %d", i, globalIndex);

        // display popup
        u8* rgb = get_player_color(np->paletteIndex, 0);
        char popupMsg[128] = { 0 };
        snprintf(popupMsg, 128, "\\#%02x%02x%02x\\%s\\#dcdcdc\\ disconnected", rgb[0], rgb[1], rgb[2], np->name);
        djui_popup_create(popupMsg, 1);

        packet_ordered_clear(globalIndex);
        reservation_area_change(np);
        return i;
    }
    return UNKNOWN_GLOBAL_INDEX;
}

void network_player_update_course_level(struct NetworkPlayer* np, s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
    // display popup
    if (np->currCourseNum != courseNum && np->localIndex != 0) {
        u8* rgb = get_player_color(np->paletteIndex, 0);
        char popupMsg[128] = { 0 };
        bool matchingLocal = (np->currCourseNum == gNetworkPlayerLocal->currCourseNum) && (np->currActNum == gNetworkPlayerLocal->currActNum);
        if (matchingLocal && gNetworkPlayerLocal->currCourseNum != 0) {
            snprintf(popupMsg, 128, "\\#%02x%02x%02x\\%s\\#dcdcdc\\ left this level", rgb[0], rgb[1], rgb[2], np->name);
        } else if (matchingLocal && gNetworkPlayerLocal->currCourseNum != 0) {
            snprintf(popupMsg, 128, "\\#%02x%02x%02x\\%s\\#dcdcdc\\ entered this level", rgb[0], rgb[1], rgb[2], np->name);
        } else {
            snprintf(popupMsg, 128, "\\#%02x%02x%02x\\%s\\#dcdcdc\\ entered\n%s", rgb[0], rgb[1], rgb[2], np->name, get_level_name(courseNum, levelNum, areaIndex));
        }
        djui_popup_create(popupMsg, 1);
    }

    np->currCourseNum = courseNum;
    np->currActNum    = actNum;
    np->currLevelNum  = levelNum;
    np->currAreaIndex = areaIndex;
}

void network_player_shutdown(void) {
    gNetworkPlayerLocal = NULL;
    gNetworkPlayerServer = NULL;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* networkPlayer = &gNetworkPlayers[i];
        networkPlayer->connected = false;
        gNetworkSystem->clear_id(i);
    }

    djui_popup_create("\\#ffa0a0\\Error:\\#dcdcdc\\ network shutdown", 1);
    LOG_INFO("cleared all network players");
}
