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


extern bool gIsModerator;
static enum ChatConfirmCommand sConfirming = CCC_NONE;
static u8 sConfirmPlayerIndex = 0;

static struct NetworkPlayer* chat_get_network_player(char* name) {
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

static bool str_starts_with(const char* pre, char* str) {
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
    enum ChatConfirmCommand ccc = sConfirming;
    sConfirming = CCC_NONE;

    if (ccc != CCC_NONE && strcmp("/confirm", command) == 0) {
        if (gNetworkType == NT_SERVER || gIsModerator) {
            if (ccc == CCC_KICK) {
                struct NetworkPlayer* np = &gNetworkPlayers[sConfirmPlayerIndex];
                if (!np->connected) { return true; }
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
        if (gNetworkType == NT_SERVER || gIsModerator) {
            if (ccc == CCC_BAN) {
                struct NetworkPlayer* np = &gNetworkPlayers[sConfirmPlayerIndex];
                if (!np->connected) { return true; }
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
            struct NetworkPlayer* np = &gNetworkPlayers[sConfirmPlayerIndex];
            if (!np->connected) { return true; }
            chat_construct_player_message(np, DLANG(CHAT, PERM_BANNING));
            network_send_kick(np->localIndex, EKT_BANNED);
            ban_list_add(gNetworkSystem->get_id_str(np->localIndex), true);
            network_player_disconnected(np->localIndex);
            return true;
        }
        if (gNetworkType == NT_SERVER && ccc == CCC_MODERATOR) {
            struct NetworkPlayer* np = &gNetworkPlayers[sConfirmPlayerIndex];
            if (!np->connected) { return true; }
            chat_construct_player_message(np, DLANG(CHAT, ADD_MODERATOR));
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

    if (str_starts_with("/kick ", command)) {
        if (gNetworkType != NT_SERVER && !gIsModerator) {
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

    if (str_starts_with("/ban ", command)) {
        if (gNetworkType != NT_SERVER && !gIsModerator) {
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

    if (str_starts_with("/permban ", command)) {
        if (gNetworkType != NT_SERVER && !gIsModerator) {
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
#if defined(DEVELOPMENT)
    if (gNetworkSystem == &gNetworkSystemSocket && str_starts_with("/warp ", command)) {
        static const struct { const char *name; s32 num; } sLevelNumByName[] = {
#undef STUB_LEVEL
#undef DEFINE_LEVEL
#define STUB_LEVEL(...)
#define DEFINE_LEVEL(_0, levelnum, _2, levelname, ...) { #levelname, levelnum },
#include "levels/level_defines.h"
#undef STUB_LEVEL
#undef DEFINE_LEVEL
        };

        // Params
        char *paramLevel = command + 6;
        if (*paramLevel == 0 || *paramLevel == ' ') {
            djui_chat_message_create("Missing parameters: [LEVEL] [AREA] [ACT]");
            return true;
        }
        char *paramArea = strchr(paramLevel, ' ');
        if (paramArea++ == NULL || *paramArea == 0 || *paramArea == ' ') {
            djui_chat_message_create("Missing parameters: [AREA] [ACT]");
            return true;
        }
        char *paramAct = strchr(paramArea, ' ');
        if (paramAct++ == NULL || *paramAct == 0 || *paramAct == ' ') {
            djui_chat_message_create("Missing parameters: [ACT]");
            return true;
        }
        *(paramArea - 1) = 0;
        *(paramAct - 1) = 0;

        // Level
        s32 level = -1;
        if (sscanf(paramLevel, "%d", &level) <= 0) {
            for (s32 i = 0; i != (s32) (sizeof(sLevelNumByName) / sizeof(sLevelNumByName[0])); ++i) {
                if (strstr(paramLevel, sLevelNumByName[i].name) == paramLevel) {
                    level = sLevelNumByName[i].num;
                    break;
                }
            }
            if (level == -1) {
                struct CustomLevelInfo* info = smlua_level_util_get_info_from_short_name(paramLevel);
                if (info != NULL) {
                    level = info->levelNum;
                }
            }
            if (level == -1) {
                char message[256];
                snprintf(message, 256, "Invalid [LEVEL] parameter: %s", paramLevel);
                djui_chat_message_create(message);
                return true;
            }
        }

        // Area
        s32 area = -1;
        if (sscanf(paramArea, "%d", &area) <= 0) {
            char message[256];
            snprintf(message, 256, "Invalid [AREA] parameter: %s", paramArea);
            djui_chat_message_create(message);
            return true;
        }

        // Act
        s32 act = -1;
        if (sscanf(paramAct, "%d", &act) <= 0) {
            char message[256];
            snprintf(message, 256, "Invalid [ACT] parameter: %s", paramAct);
            djui_chat_message_create(message);
            return true;
        }

        // Warp
        if (!dynos_warp_to_level(level, area, act)) {
            char message[256];
            snprintf(message, 256, "Unable to warp to: %s %s %s", paramLevel, paramArea, paramAct);
            djui_chat_message_create(message);
            return true;
        }

        // OK
        char message[256];
        snprintf(message, 256, "Warping to: %s %s %s...", paramLevel, paramArea, paramAct);
        djui_chat_message_create(message);
        return true;
    }

    if (str_starts_with("/lua ", command)) {
        smlua_exec_str(&command[5]);
        return true;
    }

    if (str_starts_with("/luaf ", command)) {
        smlua_exec_file(&command[6]);
        return true;
    }
#endif

    return smlua_call_chat_command_hook(command);
}

void display_chat_commands(void) {
    djui_chat_message_create(DLANG(CHAT, PLAYERS_DESC));
    if (gNetworkType == NT_SERVER || gIsModerator) {
        djui_chat_message_create(DLANG(CHAT, KICK_DESC));
        djui_chat_message_create(DLANG(CHAT, BAN_DESC));
        djui_chat_message_create(DLANG(CHAT, PERM_BAN_DESC));
        djui_chat_message_create(DLANG(CHAT, MOD_DESC));
    }
#if defined(DEVELOPMENT)
    djui_chat_message_create("/warp [LEVEL] [AREA] [ACT] - Level can be either a numeric value or a shorthand name");
    djui_chat_message_create("/lua [LUA] - Execute Lua code from a string");
    djui_chat_message_create("/luaf [FILENAME] - Execute Lua code from a file");
#endif
    if (sConfirming != CCC_NONE) { djui_chat_message_create("/confirm"); }
    smlua_display_chat_commands();
}