#include <stdio.h>
#include "network_player.h"
#include "game/mario_misc.h"
#include "reservation_area.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "game/area.h"
#include "game/level_info.h"
#include "pc/lua/smlua_hooks.h"

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

    if (gNetworkType == NT_SERVER) {
        for (int i = 1; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected) { continue; }
            float elapsed = (clock_elapsed() - np->lastReceived);
#ifndef DEVELOPMENT
            if (elapsed > NETWORK_PLAYER_TIMEOUT) {
                LOG_INFO("dropping player %d", i);
                network_player_disconnected(i);
                continue;
            }
#endif
            elapsed = (clock_elapsed() - np->lastSent);
            if (elapsed > NETWORK_PLAYER_TIMEOUT / 3.0f) {
                network_send_keep_alive(np->localIndex);
            }
        }
    } else if (gNetworkType == NT_CLIENT && gNetworkSentJoin) {
        struct NetworkPlayer* np = gNetworkPlayerServer;
        if (!np->connected) { return; }
        float elapsed = (clock_elapsed() - np->lastReceived);

#ifndef DEVELOPMENT
        if (elapsed > NETWORK_PLAYER_TIMEOUT * 1.5f) {
            LOG_INFO("dropping due to no server connectivity");
            network_shutdown(false);
        }
#endif

        elapsed = (clock_elapsed() - np->lastSent);
        if (elapsed > NETWORK_PLAYER_TIMEOUT / 3.0f) {
            network_send_keep_alive(np->localIndex);
        }
    }
}

u8 network_player_connected(enum NetworkPlayerType type, u8 globalIndex, u8 modelIndex, u8 paletteIndex, char* name) {
    // translate globalIndex to localIndex
    u8 localIndex = globalIndex;
    if (gNetworkType == NT_SERVER) {
        localIndex = globalIndex;
    } else if (type == NPT_SERVER) {
        localIndex = 1;
    } else if (type == NPT_LOCAL) {
        localIndex = 0;
    } else if (gNetworkPlayerLocal != NULL) {
        localIndex = globalIndex + ((globalIndex < gNetworkPlayerLocal->globalIndex) ? 1 : 0);
    } else {
        assert(false);
    }
    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];

    // ensure that a name is given
    if (name[0] == '\0') {
        name = sDefaultPlayerName;
    }
    if (modelIndex >= CT_MAX) { modelIndex = 0; }

    // if already connected, update a few things
    if (np->connected) {
        np->lastReceived = clock_elapsed();
        np->lastSent = clock_elapsed();
        if ((type != NPT_LOCAL) && (gNetworkType == NT_SERVER || type == NPT_SERVER)) { gNetworkSystem->save_id(localIndex, 0); }

        np->modelIndex = modelIndex;
        np->paletteIndex = paletteIndex;
        network_player_update_model(localIndex);

        snprintf(np->name, MAX_PLAYER_STRING, "%s", name);
        return localIndex;
    }

    // clear
    memset(np, 0, sizeof(struct NetworkPlayer));

    // update fundamentals
    np->connected = true;
    np->type = type;
    np->localIndex = localIndex;
    np->globalIndex = globalIndex;
    if ((type != NPT_LOCAL) && (gNetworkType == NT_SERVER || type == NPT_SERVER)) { gNetworkSystem->save_id(localIndex, 0); }

    // update course/level
    np->currLevelAreaSeqId = 0;
    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
    network_player_update_course_level(np, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex);
    np->currLevelSyncValid = false;
    np->currAreaSyncValid = false;

    // update visuals
    np->fadeOpacity = 0;
    np->modelIndex = modelIndex;
    np->paletteIndex = paletteIndex;
    snprintf(np->name, MAX_PLAYER_STRING, "%s", name);
    network_player_update_model(localIndex);

    // clear networking fields
    np->lastReceived = clock_elapsed();
    np->lastSent = clock_elapsed();
    np->onRxSeqId = 0;

    if (localIndex != 0) {
        for (int j = 0; j < MAX_SYNC_OBJECTS; j++) { gSyncObjects[j].rxEventId[localIndex] = 0; }
    }
    for (int j = 0; j < MAX_RX_SEQ_IDS; j++) { np->rxSeqIds[j] = 0; np->rxPacketHash[j] = 0; }
    packet_ordered_clear(globalIndex);

    // set up network player pointers
    if (type == NPT_LOCAL) {
        gNetworkPlayerLocal = np;
        if (gNetworkType == NT_SERVER) {
            gNetworkPlayerServer = gNetworkPlayerLocal;
        }
    } else if (type == NPT_SERVER) {
        gNetworkPlayerServer = np;
    }

    // display connected popup
    if (type != NPT_SERVER && (gNetworkType != NT_SERVER || type != NPT_LOCAL)) {
        char* playerColorString = network_get_player_text_color_string(np->localIndex);
        char popupMsg[128] = { 0 };
        snprintf(popupMsg, 128, "%s%s\\#dcdcdc\\ connected", playerColorString, np->name);
        djui_popup_create(popupMsg, 1);
    }
    LOG_INFO("player connected, local %d, global %d", localIndex, np->globalIndex);

    smlua_call_event_hooks_mario_param(HOOK_ON_PLAYER_CONNECTED, &gMarioStates[localIndex]);

    return localIndex;
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
        char* playerColorString = network_get_player_text_color_string(np->localIndex);
        char popupMsg[128] = { 0 };
        snprintf(popupMsg, 128, "%s%s\\#dcdcdc\\ disconnected", playerColorString, np->name);
        djui_popup_create(popupMsg, 1);

        packet_ordered_clear(globalIndex);
        reservation_area_change(np);

        smlua_call_event_hooks_mario_param(HOOK_ON_PLAYER_DISCONNECTED, &gMarioStates[i]);

        return i;
    }
    return UNKNOWN_GLOBAL_INDEX;
}

void network_player_update_course_level(struct NetworkPlayer* np, s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
    // display popup
    bool inCredits = (np->currActNum == 99);
    if (np->currCourseNum != courseNum && np->localIndex != 0 && !inCredits) {
        char* playerColorString = network_get_player_text_color_string(np->localIndex);
        char popupMsg[128] = { 0 };
        bool matchingLocal = (np->currCourseNum == gNetworkPlayerLocal->currCourseNum) && (np->currActNum == gNetworkPlayerLocal->currActNum);
        if (matchingLocal && gNetworkPlayerLocal->currCourseNum != 0) {
            snprintf(popupMsg, 128, "%s%s\\#dcdcdc\\ left this level", playerColorString, np->name);
        } else if (matchingLocal && gNetworkPlayerLocal->currCourseNum != 0) {
            snprintf(popupMsg, 128, "%s%s\\#dcdcdc\\ entered this level", playerColorString, np->name);
        } else {
            snprintf(popupMsg, 128, "%s%s\\#dcdcdc\\ entered\n%s", playerColorString, np->name, get_level_name(courseNum, levelNum, areaIndex));
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
