#include <stdio.h>
#include "network_utils.h"
#include "game/camera.h"
#include "game/level_update.h"
#include "game/mario_misc.h"
#include "pc/mods/mods.h"

u8 network_global_index_from_local(u8 localIndex) {
    if (gNetworkType == NT_SERVER) { return localIndex; }

    if (gNetworkPlayerLocal == NULL) { return UNKNOWN_GLOBAL_INDEX; }
    if (localIndex == 0) { return gNetworkPlayerLocal->globalIndex; } // me
    if (localIndex == 1) { return 0; } // server

    return localIndex - ((localIndex <= gNetworkPlayerLocal->globalIndex) ? 1 : 0);
}

u8 network_local_index_from_global(u8 globalIndex) {
    if (gNetworkType == NT_SERVER) { return globalIndex; }

    if (gNetworkPlayerLocal == NULL) { return UNKNOWN_LOCAL_INDEX; }
    if (gNetworkPlayerLocal->globalIndex == globalIndex) { return 0; } // me
    if (globalIndex == 0) { return 1; } // server

    return globalIndex + ((globalIndex < gNetworkPlayerLocal->globalIndex) ? 1 : 0);
}

bool network_is_server(void) {
    return gNetworkType == NT_SERVER;
}

bool network_is_moderator(void) {
    return gNetworkPlayers[0].moderator;
}

u8* network_get_player_text_color(u8 localIndex) {
    if (localIndex >= MAX_PLAYERS) { localIndex = 0; }

    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    static u8 sTextRgb[3] = { 0 };
    for (int i = 0; i < 3; i++) {
        sTextRgb[i] = 127 + np->overridePalette.parts[CAP][i] / 2;
    }

    return sTextRgb;
}

const char* network_get_player_text_color_string(u8 localIndex) {
    if (localIndex >= MAX_PLAYERS) { localIndex = 0; }
    u8* rgb = network_get_player_text_color(localIndex);
    static char sColorString[10] = { 0 };
    snprintf(sColorString, 10, "\\#%02x%02x%02x\\", rgb[0], rgb[1], rgb[2]);
    return sColorString;
}

extern s16 gMenuMode;
bool network_check_singleplayer_pause(void) {
    return ((gMenuMode != -1) || (gCameraMovementFlags & CAM_MOVE_PAUSE_SCREEN)) &&
        !gDjuiInPlayerMenu && network_player_connected_count() == 1 && mods_get_all_pausable();
}

const char* network_discord_id_from_local_index(u8 localIndex) {
    if (localIndex >= MAX_PLAYERS) { return "0"; }
    return gNetworkPlayers[localIndex].discordId;
}
