#include <stdlib.h>
#include <string.h>
#include <PR/ultratypes.h>
#include "moderation.h"
#include "pc/djui/djui_panel_moderator_menu.h"
#include "pc/djui/djui_panel_moderation_list.h"
#include "pc/djui/djui_panel_moderator_menu_inspect.h"
#include "pc/debuglog.h"
#include "pc/ini.h"

u8 gQueuedDisconnect = QUEUED_DISCONNECT_NONE;

void djui_reload_moderation_panels() {
    djui_panel_moderator_menu_reload(NULL);
    djui_panel_moderation_list_reload(NULL);
    djui_panel_moderator_inspector_reload(NULL);
}

void network_kick_player(u8 localIndex, char* reason) {
    if (gNetworkPlayerLocal->moderator) {
        network_send_moderation_action(MODERATION_ACTION_KICK, localIndex, reason, false);
        return;
    }
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("Tried to kick player as non-server!");
        return;
    }
    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    if (!np->connected) {
        LOG_ERROR("Tried to perform moderation on disconnected player!");
        return;
    }
    network_send_kick(np->localIndex, EKT_KICKED, reason);
    network_player_disconnected(np->globalIndex);
}

void network_ban_player(u8 localIndex, char* reason, bool permanent) {
    if (gNetworkPlayerLocal->moderator) {
        network_send_moderation_action(MODERATION_ACTION_BAN, localIndex, reason, permanent);
        return;
    }
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("Tried to ban player as non-server!");
        return;
    }
    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    if (!np->connected) {
        LOG_ERROR("Tried to perform moderation on disconnected player!");
        return;
    }
    moderation_list_add(MODERATION_LIST_TYPE_BAN, localIndex, reason, permanent);
    network_send_kick(np->localIndex, EKT_BANNED, reason);
    network_player_disconnected(np->globalIndex);
}

void network_unban_player(char* address) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("Tried to unban player as non-server!");
        return;
    }
    moderation_list_remove(MODERATION_LIST_TYPE_BAN, address);
}

void network_mod_player(u8 localIndex, char* reason, bool permanent) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("Tried to mod player as non-server!");
        return;
    }
    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    if (!np->connected) {
        LOG_ERROR("Tried to perform moderation on disconnected player!");
        return;
    }
    np->moderator = true;
    network_send_moderator(np->localIndex);
    moderation_list_add(MODERATION_LIST_TYPE_MODERATOR, localIndex, reason, permanent);
}

void network_unmod_player(char* address) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("Tried to unmod player as non-server!");
        return;
    }
    if (gNetworkSystem != NT_NONE) {
        // loop thru to see if moderator is in the lobby
        for (u8 i = 0; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected || !np->moderator || !address || strcmp(gNetworkSystem->get_id_str(np->localIndex), address) != 0) continue;
            np->moderator = false;
            network_send_moderator(np->localIndex);
        }
    }
    moderation_list_remove(MODERATION_LIST_TYPE_MODERATOR, address);
}