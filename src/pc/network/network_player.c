#include "network_player.h"
#include "types.h"
#include "object_fields.h"
#include "game/mario_misc.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "game/area.h"
#include "game/level_info.h"
#include "game/hardcoded.h"
#include "game/object_helpers.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/network/socket/socket.h"
#include "lag_compensation.h"
#ifdef DISCORD_SDK
#include "pc/discord/discord.h"
#endif
#include "game/mario.h"
#include "pc/djui/djui_unicode.h"

struct NetworkPlayer gNetworkPlayers[MAX_PLAYERS] = { 0 };
struct NetworkPlayer *gNetworkPlayerLocal = NULL;
struct NetworkPlayer *gNetworkPlayerServer = NULL;
static char sDefaultPlayerName[] = "Player";
static char sDefaultDiscordId[] = "0";

bool network_player_name_valid(char* buffer) {
    if (buffer[0] == '\0') { return false; }
    u16 numEscapeChars = 0;
    bool isOnlyEscapeChars = true;
    bool isInEscapedChar = false;
    char* c = buffer;
    while (*c != '\0') {
        if (*c == ' ') { return false; }
        if (!djui_unicode_valid_char(c)) { return false; }
        if (*c == '\\') { numEscapeChars++; isInEscapedChar = !isInEscapedChar; }
        else if (!isInEscapedChar) { isOnlyEscapeChars = false; }
        c = djui_unicode_next_char(c);
    }
    if (isOnlyEscapeChars) { return false; }
    if (numEscapeChars % 2 != 0) { return false; }
    return true;
}

void network_player_init(void) {
    gNetworkPlayers[0].modelIndex = (configPlayerModel < CT_MAX) ? configPlayerModel : CT_MARIO;
    gNetworkPlayers[0].palette = configPlayerPalette;
    gNetworkPlayers[0].overrideModelIndex = gNetworkPlayers[0].modelIndex;
    gNetworkPlayers[0].overridePalette = gNetworkPlayers[0].palette;
    lag_compensation_clear();
}

void network_player_update_model(u8 localIndex) {
    struct MarioState* m = &gMarioStates[localIndex];
    if (m == NULL) { return; }
    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];

    u8 index = np->overrideModelIndex;
    if (index >= CT_MAX) { index = 0; }
    m->character = &gCharacters[index];

    if (m->marioObj == NULL || m->marioObj->behavior != smlua_override_behavior(bhvMario)) { return; }
    obj_set_model(m->marioObj, m->character->modelId);
}

bool network_player_any_connected(void) {
    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        if (gNetworkPlayers[i].connected) { return true; }
    }
    return false;
}

u8 network_player_connected_count(void) {
    u8 count = 0;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (gNetworkPlayers[i].connected) { count++; }
    }
    return count;
}

void network_player_set_description(struct NetworkPlayer *np, const char *description, u8 r, u8 g, u8 b, u8 a) {
    if (np == NULL) { return; }

    if (description != NULL) {
        snprintf(np->description, MAX_DESCRIPTION_STRING, "%s", description);
    } else {
        np->description[0] = '\0';
    }

    np->descriptionR = r;
    np->descriptionG = g;
    np->descriptionB = b;
    np->descriptionA = a;
}

void network_player_set_override_location(struct NetworkPlayer *np, const char *location) {
    if (np == NULL) { return; }

    if (location != NULL) {
        snprintf(np->overrideLocation, 256, "%s", location);
    } else {
        np->overrideLocation[0] = '\0';
    }
}

struct NetworkPlayer *network_player_from_global_index(u8 globalIndex) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        if (gNetworkPlayers[i].globalIndex == globalIndex) {
            return &gNetworkPlayers[i];
        }
    }
    return NULL;
}

struct NetworkPlayer *get_network_player_from_level(s16 courseNum, s16 actNum, s16 levelNum) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer *np = &gNetworkPlayers[i];
        if (!np->connected)                 { continue; }
        if (!np->currLevelSyncValid)        { continue; }
        if (np->currCourseNum != courseNum) { continue; }
        if (np->currActNum != actNum)       { continue; }
        if (np->currLevelNum != levelNum)   { continue; }
        return np;
    }
    return NULL;
}

struct NetworkPlayer *get_network_player_from_area(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer *np = &gNetworkPlayers[i];
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

struct NetworkPlayer *get_network_player_smallest_global(void) {
    struct NetworkPlayer* lNp = gNetworkPlayerLocal;
    struct NetworkPlayer* smallest = gNetworkPlayerLocal;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer *np = &gNetworkPlayers[i];
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

u8 network_player_get_palette_color_channel(struct NetworkPlayer *np, enum PlayerPart part, u8 index) {
    if (np == NULL || part < 0 || part >= PLAYER_PART_MAX || index > 2) { return 0; }

    return np->palette.parts[part][index];
}

u8 network_player_get_override_palette_color_channel(struct NetworkPlayer *np, enum PlayerPart part, u8 index) {
    if (np == NULL || part < 0 || part >= PLAYER_PART_MAX || index > 2) { return 0; }

    return np->overridePalette.parts[part][index];
}

void network_player_set_override_palette_color(struct NetworkPlayer *np, enum PlayerPart part, Color color) {
    if (part < 0 || part >= PLAYER_PART_MAX) { return; }

    np->overridePalette.parts[part][0] = color[0];
    np->overridePalette.parts[part][1] = color[1];
    np->overridePalette.parts[part][2] = color[2];
}

void network_player_reset_override_palette(struct NetworkPlayer *np) {
    if (np == NULL) { return; }

    np->overridePalette = np->palette;
}

bool network_player_is_override_palette_same(struct NetworkPlayer *np) {
    if (np == NULL) { return false; }

    return memcmp(&np->palette, &np->overridePalette, sizeof(struct PlayerPalette)) == 0;
}

void network_player_update(void) {
    lag_compensation_store();

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer *np = &gNetworkPlayers[i];
        if (!np->connected && i > 0) { continue; }

        network_player_update_model(i);
    }

    if (!network_player_any_connected()) { return; }


    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer *np = &gNetworkPlayers[i];
        if (!np->connected && i > 0) { continue; }
        float elapsed = (clock_elapsed() - np->lastPingSent);
        if (elapsed > NETWORK_PLAYER_PING_TIMEOUT) {
            network_send_ping(np);
        }
        //LOG_INFO("Ping %s: %u", np->name, np->ping / 2);
    }

    if (gNetworkType == NT_SERVER) {
        for (s32 i = 1; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer *np = &gNetworkPlayers[i];
            if (!np->connected && i > 0) { continue; }

            float elapsed = (clock_elapsed() - np->lastReceived);
#ifdef DEVELOPMENT
            if (elapsed > NETWORK_PLAYER_TIMEOUT && (gNetworkSystem != &gNetworkSystemSocket)) {
#else
            if (elapsed > NETWORK_PLAYER_TIMEOUT) {
#endif
                LOG_INFO("dropping player %d", i);
                network_player_disconnected(i);
                continue;
            }
            elapsed = (clock_elapsed() - np->lastSent);
            if (elapsed > NETWORK_PLAYER_TIMEOUT / 3.0f) {
                network_send_keep_alive(np->localIndex);
            }
        }
    } else if (gNetworkType == NT_CLIENT && gNetworkSentJoin) {
        struct NetworkPlayer *np = gNetworkPlayerServer;
        if (!np->connected) { return; }
        float elapsed = (clock_elapsed() - np->lastReceived);

#ifdef DEVELOPMENT
        if (elapsed > NETWORK_PLAYER_TIMEOUT * 1.5f && (gNetworkSystem != &gNetworkSystemSocket)) {
#else
        if (elapsed > NETWORK_PLAYER_TIMEOUT * 1.5f) {
#endif
            LOG_INFO("dropping due to no server connectivity");
            network_shutdown(false, false, true, false);
        }

        elapsed = (clock_elapsed() - np->lastSent);
        if (elapsed > NETWORK_PLAYER_TIMEOUT / 3.0f) {
            network_send_keep_alive(np->localIndex);
        }
    }
}

extern bool gCurrentlyJoining;
u8 network_player_connected(enum NetworkPlayerType type, u8 globalIndex, u8 modelIndex, const struct PlayerPalette* palette, const char* name, const char* discordId) {
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
    struct NetworkPlayer *np = &gNetworkPlayers[localIndex];

    // ensure that a valid name is given
    if (!network_player_name_valid((char*)name)) {
        name = sDefaultPlayerName;
    }
    if (discordId[0] == '\0') {
        discordId = sDefaultDiscordId;
    }
    if (modelIndex >= CT_MAX) { modelIndex = 0; }

    // if already connected, update a few things
    if (np->connected) {
        np->lastReceived = clock_elapsed();
        np->lastSent = clock_elapsed();
        if ((type != NPT_LOCAL) && (gNetworkType == NT_SERVER || type == NPT_SERVER)) { gNetworkSystem->save_id(localIndex, 0); }

        if (np->modelIndex   == np->overrideModelIndex)   { np->overrideModelIndex   = modelIndex;   }
        if (memcmp(&np->palette, &np->overridePalette, sizeof(struct PlayerPalette)) == 0) { np->overridePalette = *palette; }
        np->modelIndex = modelIndex;
        np->palette = *palette;
        network_player_update_model(localIndex);

        snprintf(np->name, MAX_CONFIG_STRING, "%s", name);
        return localIndex;
    }

    // clear
    memset(np, 0, sizeof(struct NetworkPlayer));

    // update fundamentals
    np->connected = true;
    np->type = type;
    np->localIndex = localIndex;
    np->globalIndex = globalIndex;
    np->ping = 50;
    if ((type != NPT_LOCAL) && (gNetworkType == NT_SERVER || type == NPT_SERVER)) { gNetworkSystem->save_id(localIndex, 0); }
    network_player_set_description(np, NULL, 0, 0, 0, 0);

    // update course/level
    np->currLevelAreaSeqId = 0;
    np->currLevelSyncValid = false;
    np->currAreaSyncValid = false;
    np->currPositionValid = false;
    network_player_update_course_level(np, 0, 0, gLevelValues.entryLevel, 1);

    // update visuals
    np->fadeOpacity = 0;
    np->modelIndex = modelIndex;
    np->palette = *palette;
    np->overrideModelIndex = modelIndex;
    np->overridePalette = *palette;

    snprintf(np->name, MAX_CONFIG_STRING, "%s", name);
    network_player_update_model(localIndex);

    snprintf(np->discordId, 64, "%s", discordId);

    // clear networking fields
    np->lastReceived = clock_elapsed();
    np->lastSent = clock_elapsed();
    np->onRxSeqId = 0;

    if (localIndex != 0) {
        for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
            so->rxEventId[localIndex] = 0;
        }
    }

    for (s32 j = 0; j < MAX_RX_SEQ_IDS; j++) { np->rxSeqIds[j] = 0; np->rxPacketHash[j] = 0; }

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
    if (!gCurrentlyJoining && type != NPT_SERVER && (gNetworkType != NT_SERVER || type != NPT_LOCAL)) {
        construct_player_popup(np, DLANG(NOTIF, CONNECTED), NULL);
    }
    LOG_INFO("player connected, local %d, global %d", localIndex, np->globalIndex);

    smlua_call_event_hooks_mario_param(HOOK_ON_PLAYER_CONNECTED, &gMarioStates[localIndex]);

#ifdef DISCORD_SDK
    if (gDiscordInitialized) {
        discord_activity_update();
    }
#endif

    return localIndex;
}

u8 network_player_disconnected(u8 globalIndex) {
    if (globalIndex == 0) {
        if (gNetworkType == NT_SERVER) {
            LOG_ERROR("player disconnected, but it's local.. this shouldn't happen!");
            return UNKNOWN_GLOBAL_INDEX;
        } else {
            network_shutdown(true, false, true, false);
        }
    }

    if (globalIndex == UNKNOWN_GLOBAL_INDEX) {
        LOG_ERROR("player disconnected, but unknown global index!");
        return UNKNOWN_GLOBAL_INDEX;
    }

    for (s32 i = 1; i < MAX_PLAYERS; i++) {
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

        for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
            so->rxEventId[i] = 0;
        }

        LOG_INFO("player disconnected, local %d, global %d", i, globalIndex);

        // display popup
        construct_player_popup(np, DLANG(NOTIF, DISCONNECTED), NULL);

        packet_ordered_clear(globalIndex);

        smlua_call_event_hooks_mario_param(HOOK_ON_PLAYER_DISCONNECTED, &gMarioStates[i]);

        memset(np, 0, sizeof(struct NetworkPlayer));

#ifdef DISCORD_SDK
        if (gDiscordInitialized) {
            discord_activity_update();
        }
#endif

        // reset mario state
        init_mario_single_from_save_file(&gMarioStates[i], i);

        return i;
    }
    return UNKNOWN_GLOBAL_INDEX;
}

void construct_player_popup(struct NetworkPlayer* np, char* msg, const char* level) {
    char built[256] = { 0 };
    snprintf(built, 256, "\\#dcdcdc\\");

    char player[128] = { 0 };
    snprintf(player, 128, "%s%s\\#dcdcdc\\", network_get_player_text_color_string(np->localIndex), np->name);
    if (level) {
        djui_language_replace2(msg, &built[9], 256 - 9, '@', player, '#', (char*)level);
    } else {
        djui_language_replace(msg, &built[9], 256 - 9, '@', player);
    }
    djui_popup_create(built, 1);
}

void network_player_update_course_level(struct NetworkPlayer* np, s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
    // prevent sync valid packets from corrupting areaIndex
    if (areaIndex == -1) {
        areaIndex = np->currAreaIndex;
    }

    // display popup
    bool inCredits = (np->currActNum == 99);

    if (np->currCourseNum != courseNum && np->localIndex != 0 && !inCredits) {
        bool matchingLocal = (np->currCourseNum == gNetworkPlayerLocal->currCourseNum) && (np->currActNum == gNetworkPlayerLocal->currActNum);

        if (matchingLocal && gNetworkPlayerLocal->currCourseNum != 0) {
            construct_player_popup(np, DLANG(NOTIF, LEFT_THIS_LEVEL), NULL);
        } else if (gNetworkPlayerLocal->currCourseNum == courseNum && gNetworkPlayerLocal->currCourseNum != 0) {
            construct_player_popup(np, DLANG(NOTIF, ENTERED_THIS_LEVEL), NULL);
        } else {
            construct_player_popup(np, DLANG(NOTIF, ENTERED), get_level_name(courseNum, levelNum, areaIndex));
        }
    }

    bool mismatch = (np->currCourseNum != courseNum)
                 || (np->currActNum    != actNum)
                 || (np->currLevelNum  != levelNum)
                 || (np->currAreaIndex != areaIndex);

    np->currCourseNum = courseNum;
    np->currActNum    = actNum;
    np->currLevelNum  = levelNum;
    np->currAreaIndex = areaIndex;

    // Whether the new np location differs from the local location
    bool mismatchLocal = (np->currCourseNum != gCurrCourseNum)
                      || (np->currActNum != gCurrActNum)
                      || (np->currLevelNum != gCurrLevelNum)
                      || (np->currAreaIndex != gCurrAreaIndex);
    if (mismatchLocal) {
        np->currPositionValid = false;
    }

    if (mismatch) {
        if (np == gNetworkPlayerLocal) {
            network_send_level_area_inform();

            for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
                so->txEventId = 0;
            }

            // If this machine's player changed to a different location, then all of the other np locations are no longer valid
            for (u32 i = 1; i < MAX_PLAYERS; i++) {
                struct NetworkPlayer* npi = &gNetworkPlayers[i];
                if ((!npi->connected) || npi == gNetworkPlayerLocal) { continue; }
                npi->currPositionValid = false;
            }

        } else {
            for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
                so->rxEventId[np->localIndex] = 0;
            }
        }
    }
}

void network_player_shutdown(bool popup) {
    gNetworkPlayerLocal = NULL;
    gNetworkPlayerServer = NULL;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer *networkPlayer = &gNetworkPlayers[i];
        memset(networkPlayer, 0, sizeof(struct NetworkPlayer));
        networkPlayer->connected = false;
        gNetworkSystem->clear_id(i);
    }

    if (popup) { djui_popup_create(DLANG(NOTIF, SERVER_CLOSED), 1); }
    LOG_INFO("cleared all network players");
}
