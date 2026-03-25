#include "pc/network/network.h"
#include "pc/network/socket/socket.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_chat_message.h"
#include "pc/djui/djui_console.h"
#include "commands.h"
#include "pc/network/ban_list.h"
#include "pc/network/moderator_list.h"
#include "pc/debuglog.h"
#include "pc/lua/utils/smlua_level_utils.h"
#include "pc/mods/mods_utils.h"
#include "pc/pc_main.h"
#include "level_table.h"
#ifdef DEVELOPMENT
#include "pc/dev/chat.h"
#endif

static bool command_help(UNUSED const char* message);
static bool command_players(UNUSED const char* message);
static bool command_kick(const char* message);
static bool command_ban(const char* message);
static bool command_permaban(const char* message);
static bool command_mod(const char* message);
static bool command_confirm(UNUSED const char* message);
static bool command_nametags(const char* message);
static bool command_clear(UNUSED const char* message);
static bool command_quit(UNUSED const char* message);
static bool command_host(UNUSED const char* message);
static bool command_rehost(UNUSED const char* message);
static bool command_stop_hosting(UNUSED const char* message);
static bool command_disconnect(UNUSED const char* message);

static struct Command sCommands[] = {
    {
        .command = "players",
        .description = "PLAYERS_DESC",
        .action = command_players,
        .active = true,
        .isChatCommand = true
    },
    {
        .command = "kick",
        .description = "KICK_DESC",
        .action = command_kick,
        .active = true,
        .isChatCommand = true
    },
    {
        .command = "ban",
        .description = "BAN_DESC",
        .action = command_ban,
        .active = true,
        .isChatCommand = true
    },
    {
        .command = "permaban",
        .description = "PERM_BAN_DESC",
        .action = command_permaban,
        .active = true,
        .isChatCommand = true
    },
    {
        .command = "moderator",
        .description = "MOD_DESC",
        .action = command_mod,
        .active = true,
        .isChatCommand = true
    },
    {
        .command = "confirm",
        .description = "",
        .action = command_confirm,
        .active = false,
        .isChatCommand = true
    },
    {
        .command = "nametags",
        .description = "NAMETAGS_DESC",
        .action = command_nametags,
        .active = false,
        .isChatCommand = true
    },
    {
        .command = "clear",
        .description = "/clear - Clears the current console's text",
        .action = command_clear,
        .active = true,
        .isChatCommand = false
    },
    {
        .command = "quit",
        .description = "/quit - Quits the game",
        .action = command_quit,
        .active = true,
        .isChatCommand = false
    },
    {
        .command = "host",
        .description = "/host - Hosts a new game using your saved server settings and mod list",
        .action = command_host,
        .active = true,
        .isChatCommand = false
    },
    {
        .command = "rehost",
        .description = "/rehost - Rehosts a currently active game",
        .action = command_rehost,
        .active = false,
        .isChatCommand = false
    },
    {
        .command = "stop-hosting",
        .description = "/stop-hosting - Stop hosting a currently active game",
        .action = command_stop_hosting,
        .active = false,
        .isChatCommand = false
    },
    {
        .command = "disconnect",
        .description = "/disconnect - Disconnects from a currently active game",
        .action = command_disconnect,
        .active = false,
        .isChatCommand = false
    },
};
static unsigned int sCommandCount = sizeof(sCommands) / sizeof(struct Command);
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

static void chat_construct_player_message(struct NetworkPlayer* np, char* msg) {
    char built[256] = { 0 };
    snprintf(built, 256, "\\#fff982\\");

    char player[128] = { 0 };
    snprintf(player, 128, "%s%s\\#fff982\\", network_get_player_text_color_string(np->localIndex), np->name);
    djui_language_replace(msg, &built[9], 256 - 9, '@', player);
    command_message_create(built, CONSOLE_MESSAGE_INFO);
}

static bool command_help(UNUSED const char* message) {
    for (unsigned int i = 0; i < sCommandCount; i++) {
        if (!sCommands[i].active) continue;
        if (!sCommands[i].isChatCommand && gDjuiChatBoxFocus) continue;
        command_message_create(djui_language_get("CHAT", sCommands[i].description), CONSOLE_MESSAGE_INFO);
    }
#ifdef DEVELOPMENT
    dev_display_chat_commands();
#endif
    smlua_display_chat_commands(gDjuiConsoleFocus);
    return true;
}

static bool command_players(UNUSED const char* message) {
    char line[128] = { 0 };
    snprintf(line, 127, "\\#fff982\\%s:\n", DLANG(CHAT, PLAYERS));
    command_message_create(line, CONSOLE_MESSAGE_INFO);
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }
        if (gNetworkSystem == &gNetworkSystemSocket) {
            snprintf(line, 127, "\\#82f9ff\\%u\\#fff982\\ - %s%s\n", np->globalIndex, network_get_player_text_color_string(np->localIndex), np->name);
        } else {
            snprintf(line, 127, "\\#82f9ff\\%u\\#fff982\\ - \\#82f9ff\\%s\\#fff982\\ - %s%s\n", np->globalIndex, gNetworkSystem->get_id_str(np->localIndex), network_get_player_text_color_string(np->localIndex), np->name);
        }
        command_message_create(line, CONSOLE_MESSAGE_INFO);
    }
    return true;
}

static bool command_kick(const char* message) {
    struct NetworkPlayer* npl = &gNetworkPlayers[0];
    if (gNetworkType != NT_SERVER && !npl->moderator) {
        command_message_create(DLANG(CHAT, NO_PERMS), CONSOLE_MESSAGE_ERROR);
        return true;
    }

    struct NetworkPlayer* np = chat_get_network_player(message);
    if (np == NULL) {
        command_message_create(DLANG(CHAT, PLAYER_NOT_FOUND), CONSOLE_MESSAGE_ERROR);
        return true;
    }

    if (np->localIndex == 0) {
        command_message_create(DLANG(CHAT, SELF_KICK), CONSOLE_MESSAGE_ERROR);
        return true;
    }
    chat_construct_player_message(np, DLANG(CHAT, KICK_CONFIRM));
    sConfirming = CCC_KICK;
    sConfirmPlayerIndex = np->localIndex;
    struct Command* confirmCommand = get_command("confirm");
    if (confirmCommand) confirmCommand->active = true;
    return true;
}

static bool command_ban(const char* message) {
    struct NetworkPlayer* npl = &gNetworkPlayers[0];
    if (gNetworkType != NT_SERVER && !npl->moderator) {
        command_message_create(DLANG(CHAT, NO_PERMS), CONSOLE_MESSAGE_ERROR);
        return true;
    }

    struct NetworkPlayer* np = chat_get_network_player(message);
    if (np == NULL) {
        command_message_create(DLANG(CHAT, PLAYER_NOT_FOUND), CONSOLE_MESSAGE_ERROR);
        return true;
    }

    if (np->localIndex == 0) {
        command_message_create(DLANG(CHAT, SELF_BAN), CONSOLE_MESSAGE_ERROR);
        return true;
    }
    chat_construct_player_message(np, DLANG(CHAT, BAN_CONFIRM));
    sConfirming = CCC_BAN;
    sConfirmPlayerIndex = np->localIndex;
    struct Command* confirmCommand = get_command("confirm");
    if (confirmCommand) confirmCommand->active = true;
    return true;
}

static bool command_permaban(const char* message) {
    struct NetworkPlayer* npl = &gNetworkPlayers[0];
    if (gNetworkType != NT_SERVER && !npl->moderator) {
        command_message_create(DLANG(CHAT, NO_PERMS), CONSOLE_MESSAGE_ERROR);
        return true;
    }

    struct NetworkPlayer* np = chat_get_network_player(message);
    if (np == NULL) {
        command_message_create(DLANG(CHAT, PLAYER_NOT_FOUND), CONSOLE_MESSAGE_ERROR);
        return true;
    }

    if (np->localIndex == 0) {
        command_message_create(DLANG(CHAT, SELF_BAN), CONSOLE_MESSAGE_ERROR);
        return true;
    }
    chat_construct_player_message(np, DLANG(CHAT, PERM_BAN_CONFIRM));
    sConfirming = CCC_PERMBAN;
    sConfirmPlayerIndex = np->localIndex;
    struct Command* confirmCommand = get_command("confirm");
    if (confirmCommand) confirmCommand->active = true;
    return true;
}

static bool command_mod(const char* message) {
    if (gNetworkType != NT_SERVER) {
        command_message_create(DLANG(CHAT, SERVER_ONLY), CONSOLE_MESSAGE_ERROR);
        return true;
    }

    struct NetworkPlayer* np = chat_get_network_player(message);
    if (np == NULL) {
        command_message_create(DLANG(CHAT, PLAYER_NOT_FOUND), CONSOLE_MESSAGE_ERROR);
        return true;
    }

    if (np->localIndex == 0) {
        command_message_create(DLANG(CHAT, SELF_MOD), CONSOLE_MESSAGE_ERROR);
        return true;
    }
    chat_construct_player_message(np, DLANG(CHAT, MOD_CONFIRM));
    sConfirming = CCC_MODERATOR;
    sConfirmPlayerIndex = np->localIndex;
    struct Command* confirmCommand = get_command("confirm");
    if (confirmCommand) confirmCommand->active = true;
    return true;
}

static bool command_confirm(UNUSED const char* message) {
    // deactivate command
    struct Command* confirmCommand = get_command("confirm");
    if (confirmCommand) confirmCommand->active = false;

    enum ChatConfirmCommand ccc = sConfirming;
    sConfirming = CCC_NONE;

    struct NetworkPlayer* npl = &gNetworkPlayers[0];
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
    return false;
}

static bool command_nametags(const char* message) {
    if (strcmp("show-tag", message) == 0) {
        gNametagsSettings.showSelfTag = !gNametagsSettings.showSelfTag;
    } else if (strcmp("show-health", message) == 0) {
        gNametagsSettings.showHealth = !gNametagsSettings.showHealth;
    }
    command_message_create(DLANG(CHAT, NAMETAGS_MISSING_PARAMETERS), CONSOLE_MESSAGE_ERROR);
    return true;
}

static bool command_clear(UNUSED const char* message) {
    djui_console_clear();
    terminal_clear();
    return true;
}

static bool command_quit(UNUSED const char* message) {
    game_exit();
    return true;
}

extern void djui_panel_do_host(bool reconnecting, bool playSound);
static bool command_host(UNUSED const char* message) {
    djui_panel_do_host(false, true);
    return true;
}

static bool command_rehost(UNUSED const char* message) {
    network_rehost_begin();
    return true;
}

static bool command_stop_hosting(UNUSED const char* message) {
    network_reset_reconnect_and_rehost();
    network_shutdown(true, false, false, false);
    return true;
}

static bool command_disconnect(UNUSED const char* message) {
    network_reset_reconnect_and_rehost();
    network_shutdown(true, false, false, false);
    return true;
}

static void set_command_active(const char* name, bool active) {
    struct Command* command = get_command(name);
    if (command) command->active = active;
}

struct Command* get_command(const char* name) {
    for (unsigned int i = 0; i < sCommandCount; i++) {
        if (strcmp(sCommands[i].command, name) == 0) {
            return &sCommands[i];
        }
    }
    return NULL;
}


void command_message_create(const char* message, OPTIONAL enum ConsoleMessageLevel level) {
    if (gDjuiChatBoxFocus) {
        size_t newMsgLength = strlen(message) + 12;
        char newMsg[newMsgLength];
        switch (level) {
            case CONSOLE_MESSAGE_INFO:
                snprintf(newMsg, newMsgLength, "\\#dcdcdc\\%s", message);
                break;
            case CONSOLE_MESSAGE_WARNING:
                snprintf(newMsg, newMsgLength, "\\#ffffa0\\%s", message);
                break;
            case CONSOLE_MESSAGE_ERROR:
                snprintf(newMsg, newMsgLength, "\\#ffa0a0\\%s", message);
                break;
            default:
                snprintf(newMsg, newMsgLength, "\\#dcdcdc\\%s", message);
                break;
        }
        djui_chat_message_create(newMsg);
    } else {
        djui_console_message_create(message, level);
        char* colorCode;
        switch (level) {
            case CONSOLE_MESSAGE_WARNING: colorCode = "\x1b[33m"; break;
            case CONSOLE_MESSAGE_ERROR:   colorCode = "\x1b[31m"; break;
            default:                      colorCode = "\x1b[0m"; break;
        }
        log_to_terminal("%s%s\x1b[0m\n", colorCode, message);
    }
}

void run_command(char* command) {
    // directly set active state of certain commands
    set_command_active("nametags", gServerSettings.nametags);
    set_command_active("host", gDjuiInMainMenu);
    set_command_active("rehost", gNetworkType == NT_SERVER && !gDjuiInMainMenu);
    set_command_active("stop-hosting", gNetworkType == NT_SERVER && !gDjuiInMainMenu);
    set_command_active("disconnect", gNetworkType == NT_CLIENT && !gDjuiInMainMenu);

    // directly check help command
    if (strcmp(command, "help") == 0 || strcmp(command, "?") == 0 || strcmp(command, "") == 0) {
        command_help(NULL);
        return;
    }

    // loop through builtin commands first
    for (unsigned int i = 0; i < sCommandCount; i++) {
        // sanity checks
        if (sCommands[i].command[0] == '\0') continue;
        if (!sCommands[i].action) continue;
        if (!sCommands[i].active) continue;
        if (!sCommands[i].isChatCommand && gDjuiChatBoxFocus) continue;

        // compare strings
        size_t commandLength = strlen(sCommands[i].command);
        if (!str_starts_with(command, sCommands[i].command)) continue;
        if (command[commandLength] != '\0' && command[commandLength] != ' ') continue;

        // get args
        char* arguments = command + commandLength;
        if (*arguments != '\0') arguments++;

        // run action
        if (sCommands[i].action(arguments)) return;
    }

#ifdef DEVELOPMENT
    // check development commands
    if (exec_dev_chat_command(command)) return;
#endif

    // check lua commands
    if (smlua_call_chat_command_hook(command)) return;

    // no command exists, alert the user
    char extendedUnknownCommandMessage[MAX_CONSOLE_INPUT_LENGTH];
    snprintf(extendedUnknownCommandMessage, sizeof(extendedUnknownCommandMessage), "%s (/help)", DLANG(CHAT, UNRECOGNIZED));
    command_message_create(extendedUnknownCommandMessage, CONSOLE_MESSAGE_INFO);
}
