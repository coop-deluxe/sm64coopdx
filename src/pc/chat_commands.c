#include "pc/network/network.h"
#include "pc/network/socket/socket.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_chat_message.h"
#include "chat_commands.h"
#include "pc/network/ban_list.h"
#include "pc/network/moderator_list.h"
#include "pc/debuglog.h"
#include "pc/lua/utils/smlua_level_utils.h"
#include "level_table.h"
#ifdef DEVELOPMENT
#include "pc/dev/chat.h"
#endif

static enum ChatConfirmCommand sConfirming = CCC_NONE;
static u8 sConfirmPlayerIndex = 0;

static struct NetworkPlayer* chat_get_network_player(const char* name) {
    // check for id
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        char id[16] = { 0 };
        if (snprintf(id, 16, "%d", i) < 0) {
            // do nothing
        }
        if (strcmp(id, name) == 0) {
            return &gNetworkPlayers[i];
        }
    }

    // check for name
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        if (strcmp(gNetworkPlayers[i].name, name) == 0) {
            return &gNetworkPlayers[i];
        }
    }
    return NULL;
}

static bool str_starts_with(const char* pre, const char* str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

static void chat_construct_player_message(struct NetworkPlayer* np, char* msg) {
    char built[256] = { 0 };
    snprintf(built, 256, "\\#fff982\\");

    char player[128] = { 0 };
    snprintf(player, 128, "%s%s\\#fff982\\", network_get_player_text_color_string(np->localIndex), np->name);
    djui_language_replace(msg, &built[9], 256 - 9, '@', player);
    djui_chat_message_create(built);
}

bool exec_chat_command(char* command) {
    struct NetworkPlayer* npl = &gNetworkPlayers[0];
    enum ChatConfirmCommand ccc = sConfirming;
    sConfirming = CCC_NONE;

    if (ccc != CCC_NONE && strcmp("/confirm", command) == 0) {
        struct NetworkPlayer* np = &gNetworkPlayers[sConfirmPlayerIndex];
        if (!np->connected) return true;
        if (gNetworkType == NT_SERVER || npl->moderator) {
            if (ccc == CCC_KICK) {
                chat_construct_player_message(np, DLANG(CHAT, KICKING));
                if (gNetworkType == NT_SERVER) {
                    network_send_kick(np->localIndex, EKT_KICKED);
                    network_player_disconnected(np->localIndex);
                } else {
                    network_send_chat_command(np->globalIndex, CCC_KICK);
                }
                return true;
            }
        }
        if (gNetworkType == NT_SERVER || npl->moderator) {
            if (ccc == CCC_BAN) {
                chat_construct_player_message(np, DLANG(CHAT, BANNING));
                if (gNetworkType == NT_SERVER) {
                    network_send_kick(np->localIndex, EKT_BANNED);
                    ban_list_add(gNetworkSystem->get_id_str(np->localIndex), false);
                    network_player_disconnected(np->localIndex);
                } else {
                    network_send_chat_command(np->globalIndex, CCC_BAN);
                }
                return true;
            }
        }
        if (gNetworkType == NT_SERVER && ccc == CCC_PERMBAN) {
            chat_construct_player_message(np, DLANG(CHAT, PERM_BANNING));
            network_send_kick(np->localIndex, EKT_BANNED);
            ban_list_add(gNetworkSystem->get_id_str(np->localIndex), true);
            network_player_disconnected(np->localIndex);
            return true;
        }
        if (gNetworkType == NT_SERVER && ccc == CCC_MODERATOR) {
            chat_construct_player_message(np, DLANG(CHAT, ADD_MODERATOR));
            np->moderator = true;
            network_send_moderator(np->localIndex);
            moderator_list_add(gNetworkSystem->get_id_str(np->localIndex), true);
            return true;
        }
    }

    if (strcmp("/players", command) == 0) {
        char line[128] = { 0 };
        snprintf(line, 127, "\\#fff982\\%s:\n", DLANG(CHAT, PLAYERS));
        djui_chat_message_create(line);
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected) { continue; }
            if (gNetworkSystem == &gNetworkSystemSocket) {
                snprintf(line, 127, "\\#82f9ff\\%u\\#fff982\\ - %s%s\n", np->globalIndex, network_get_player_text_color_string(np->localIndex), np->name);
            } else {
                snprintf(line, 127, "\\#82f9ff\\%u\\#fff982\\ - \\#82f9ff\\%s\\#fff982\\ - %s%s\n", np->globalIndex, gNetworkSystem->get_id_str(np->localIndex), network_get_player_text_color_string(np->localIndex), np->name);
            }
            djui_chat_message_create(line);
        }
        return true;
    }

    if (strcmp("/kick", command) == 0) {
        djui_chat_message_create(DLANG(CHAT, PLAYER_NOT_FOUND));
        return true;
    }
  
    if (str_starts_with("/kick ", command)) {
        if (gNetworkType != NT_SERVER && !npl->moderator) {
            djui_chat_message_create(DLANG(CHAT, NO_PERMS));
            return true;
        }

        struct NetworkPlayer* np = chat_get_network_player(&command[6]);
        if (np == NULL) {
            djui_chat_message_create(DLANG(CHAT, PLAYER_NOT_FOUND));
            return true;
        }

        if (np->localIndex == 0) {
            djui_chat_message_create(DLANG(CHAT, SELF_KICK));
            return true;
        }
        chat_construct_player_message(np, DLANG(CHAT, KICK_CONFIRM));
        sConfirming = CCC_KICK;
        sConfirmPlayerIndex = np->localIndex;

        return true;
    }

    if (strcmp("/ban", command) == 0) {
        djui_chat_message_create(DLANG(CHAT, PLAYER_NOT_FOUND));
        return true;
    }

    if (str_starts_with("/ban ", command)) {
        if (gNetworkType != NT_SERVER && !npl->moderator) {
            djui_chat_message_create(DLANG(CHAT, NO_PERMS));
            return true;
        }

        struct NetworkPlayer* np = chat_get_network_player(&command[5]);
        if (np == NULL) {
            djui_chat_message_create(DLANG(CHAT, PLAYER_NOT_FOUND));
            return true;
        }

        if (np->localIndex == 0) {
            djui_chat_message_create(DLANG(CHAT, SELF_BAN));
            return true;
        }
        chat_construct_player_message(np, DLANG(CHAT, BAN_CONFIRM));
        sConfirming = CCC_BAN;
        sConfirmPlayerIndex = np->localIndex;

        return true;
    }

    if (strcmp("/permban", command) == 0) {
        djui_chat_message_create(DLANG(CHAT, PLAYER_NOT_FOUND));
        return true;
    }

    if (str_starts_with("/permban ", command)) {
        if (gNetworkType != NT_SERVER && !npl->moderator) {
            djui_chat_message_create(DLANG(CHAT, NO_PERMS));
            return true;
        }

        struct NetworkPlayer* np = chat_get_network_player(&command[9]);
        if (np == NULL) {
            djui_chat_message_create(DLANG(CHAT, PLAYER_NOT_FOUND));
            return true;
        }

        if (np->localIndex == 0) {
            djui_chat_message_create(DLANG(CHAT, SELF_BAN));
            return true;
        }
        chat_construct_player_message(np, DLANG(CHAT, PERM_BAN_CONFIRM));
        sConfirming = CCC_PERMBAN;
        sConfirmPlayerIndex = np->localIndex;

        return true;
    }

    if (strcmp("/moderator", command) == 0) {
        djui_chat_message_create(DLANG(CHAT, PLAYER_NOT_FOUND));
        return true;
    }

    if (str_starts_with("/moderator ", command)) {     
        if (gNetworkType != NT_SERVER) {
            djui_chat_message_create(DLANG(CHAT, SERVER_ONLY));
            return true;
        }

        struct NetworkPlayer* np = chat_get_network_player(&command[11]);
        if (np == NULL) {
            djui_chat_message_create(DLANG(CHAT, PLAYER_NOT_FOUND));
            return true;
        }

        if (np->localIndex == 0) {
            djui_chat_message_create(DLANG(CHAT, SELF_MOD));
            return true;
        }
        chat_construct_player_message(np, DLANG(CHAT, MOD_CONFIRM));
        sConfirming = CCC_MODERATOR;
        sConfirmPlayerIndex = np->localIndex;

        return true;
    }

    if (gServerSettings.nametags) {
        if (strcmp("/nametags", command) == 0) {
            djui_chat_message_create(DLANG(CHAT, NAMETAGS_MISSING_PARAMETERS));
            return true;
        }

        if (str_starts_with("/nametags ", command)) {
            char *option = &command[10];
            if (strcmp("show-tag", option) == 0) {
                gNametagsSettings.showSelfTag = !gNametagsSettings.showSelfTag;
            } else if (strcmp("show-health", option) == 0) {
                gNametagsSettings.showHealth = !gNametagsSettings.showHealth;
            }
            return true;
        }
    }

#ifdef DEVELOPMENT
    if (exec_dev_chat_command(command)) {
        return true;
    }
#endif

    return smlua_call_chat_command_hook(command);
}

void display_chat_commands(void) {
    djui_chat_message_create(DLANG(CHAT, PLAYERS_DESC));
    if (gNetworkType == NT_SERVER || gNetworkPlayers[0].moderator) {
        djui_chat_message_create(DLANG(CHAT, KICK_DESC));
        djui_chat_message_create(DLANG(CHAT, BAN_DESC));

        if (gNetworkType == NT_SERVER) {
            djui_chat_message_create(DLANG(CHAT, PERM_BAN_DESC));
            djui_chat_message_create(DLANG(CHAT, MOD_DESC));
        }
    }
    if (gServerSettings.nametags) {
        djui_chat_message_create(DLANG(CHAT, NAMETAGS_DESC));
    }
#ifdef DEVELOPMENT
    dev_display_chat_commands();
#endif
    if (sConfirming != CCC_NONE) { djui_chat_message_create("/confirm"); }
    smlua_display_chat_commands();
}
