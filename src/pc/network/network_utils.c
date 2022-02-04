#include <stdio.h>
#include "network_utils.h"
#include "game/mario_misc.h"

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

u8* network_get_player_text_color(u8 localIndex) {
    if (localIndex >= MAX_PLAYERS) { localIndex = 0; }

    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    u8* rgb = get_player_color(np->paletteIndex, 0);
    static u8 sTextRgb[3] = { 0 };
    for (int i = 0; i < 3; i++) {
        sTextRgb[i] = 127 + rgb[i] / 2;
    }

    return sTextRgb;
}

char* network_get_player_text_color_string(u8 localIndex) {
    if (localIndex >= MAX_PLAYERS) { localIndex = 0; }
    u8* rgb = network_get_player_text_color(localIndex);
    static char sColorString[10] = { 0 };
    snprintf(sColorString, 10, "\\#%02x%02x%02x\\", rgb[0], rgb[1], rgb[2]);
    return sColorString;
}
