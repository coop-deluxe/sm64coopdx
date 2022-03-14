#include "pc/network/network.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/djui/djui_chat_message.h"
#include "chat_commands.h"
#include "pc/network/ban_list.h"
#include "pc/debuglog.h"

enum ChatConfirmCommand {
    CCC_NONE,
    CCC_KICK,
    CCC_BAN,
    CCC_PERMBAN,
};

static enum ChatConfirmCommand sConfirming = CCC_NONE;
static u8 sConfirmPlayerIndex = 0;

static struct NetworkPlayer* chat_get_network_player(char* name) {
    // check for id
    for (int i = 0; i < MAX_PLAYERS; i++) {
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
    for (int i = 0; i < MAX_PLAYERS; i++) {
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

bool exec_chat_command(char* command) {
    enum ChatConfirmCommand ccc = sConfirming;
    sConfirming = CCC_NONE;

    if (ccc != CCC_NONE && strcmp("/confirm", command) == 0) {
        if (gNetworkType == NT_SERVER && ccc == CCC_KICK) {
            struct NetworkPlayer* np = &gNetworkPlayers[sConfirmPlayerIndex];
            if (!np->connected) { return true; }
            char message[256] = { 0 };
            snprintf(message, 256, "\\#fff982\\Kicking '%s%s\\#fff982\\'!", network_get_player_text_color_string(np->localIndex), np->name);
            djui_chat_message_create(message);
            network_send_kick(np->localIndex, EKT_KICKED);
            network_player_disconnected(np->localIndex);
            return true;
        }
        if (gNetworkType == NT_SERVER && ccc == CCC_BAN) {
            struct NetworkPlayer* np = &gNetworkPlayers[sConfirmPlayerIndex];
            if (!np->connected) { return true; }
            char message[256] = { 0 };
            snprintf(message, 256, "\\#fff982\\Banning '%s%s\\#fff982\\'!", network_get_player_text_color_string(np->localIndex), np->name);
            djui_chat_message_create(message);
            network_send_kick(np->localIndex, EKT_BANNED);
            ban_list_add(gNetworkSystem->get_id_str(np->localIndex), false);
            network_player_disconnected(np->localIndex);
            return true;
        }
        if (gNetworkType == NT_SERVER && ccc == CCC_PERMBAN) {
            struct NetworkPlayer* np = &gNetworkPlayers[sConfirmPlayerIndex];
            if (!np->connected) { return true; }
            char message[256] = { 0 };
            snprintf(message, 256, "\\#fff982\\Permanently banning '%s%s\\#fff982\\'!", network_get_player_text_color_string(np->localIndex), np->name);
            djui_chat_message_create(message);
            network_send_kick(np->localIndex, EKT_BANNED);
            ban_list_add(gNetworkSystem->get_id_str(np->localIndex), true);
            network_player_disconnected(np->localIndex);
            return true;
        }
    }

    if (strcmp("/players", command) == 0) {
        char message[600] = { 0 };
        char line[128] = { 0 };
        strncat(message, "\\#fff982\\Players:\n", 599);
        for (int i = 0; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected) { continue; }
            snprintf(line, 128, "\\#82f9ff\\%u \\#fff982\\- %s%s\n", np->globalIndex, network_get_player_text_color_string(np->localIndex), np->name);
            strncat(message, line, 599);
        }
        djui_chat_message_create(message);
        return true;
    }

    if (str_starts_with("/kick ", command)) {
        if (gNetworkType != NT_SERVER) {
            djui_chat_message_create("Only the server can use this command.");
            return true;
        }

        struct NetworkPlayer* np = chat_get_network_player(&command[6]);
        if (np == NULL) {
            djui_chat_message_create("Could not find player.");
            return true;
        }

        if (np->localIndex == 0) {
            djui_chat_message_create("Can not kick yourself.");
            return true;
        }

        char message[256] = { 0 };
        snprintf(message, 256, "\\#fff982\\Are you sure you want to kick '%s%s\\#fff982\\'?\nType '\\#a0ffa0\\/confirm\\#fff982\\' to kick.", network_get_player_text_color_string(np->localIndex), np->name);
        djui_chat_message_create(message);

        sConfirming = CCC_KICK;
        sConfirmPlayerIndex = np->localIndex;

        return true;
    }

    if (str_starts_with("/ban ", command)) {
        if (gNetworkType != NT_SERVER) {
            djui_chat_message_create("Only the server can use this command.");
            return true;
        }

        struct NetworkPlayer* np = chat_get_network_player(&command[5]);
        if (np == NULL) {
            djui_chat_message_create("Could not find player.");
            return true;
        }

        if (np->localIndex == 0) {
            djui_chat_message_create("Can not ban yourself.");
            return true;
        }

        char message[256] = { 0 };
        snprintf(message, 256, "\\#fff982\\Are you sure you want to ban '%s%s\\#fff982\\'?\nType '\\#a0ffa0\\/confirm\\#fff982\\' to ban.", network_get_player_text_color_string(np->localIndex), np->name);
        djui_chat_message_create(message);

        sConfirming = CCC_BAN;
        sConfirmPlayerIndex = np->localIndex;

        return true;
    }

    if (str_starts_with("/permban ", command)) {
        if (gNetworkType != NT_SERVER) {
            djui_chat_message_create("Only the server can use this command.");
            return true;
        }

        struct NetworkPlayer* np = chat_get_network_player(&command[9]);
        if (np == NULL) {
            djui_chat_message_create("Could not find player.");
            return true;
        }

        if (np->localIndex == 0) {
            djui_chat_message_create("Can not permanently ban yourself.");
            return true;
        }

        char message[256] = { 0 };
        snprintf(message, 256, "\\#fff982\\Are you sure you want to permanently ban '%s%s\\#fff982\\'?\nType '\\#a0ffa0\\/confirm\\#fff982\\' to permanently ban.", network_get_player_text_color_string(np->localIndex), np->name);
        djui_chat_message_create(message);

        sConfirming = CCC_PERMBAN;
        sConfirmPlayerIndex = np->localIndex;

        return true;
    }

    return smlua_call_chat_command_hook(command);
}

void display_chat_commands(void) {
    djui_chat_message_create("/players - List all players and their IDs");
    if (gNetworkType == NT_SERVER) {
        djui_chat_message_create("/kick [NAME|ID] - Kick this player from the current game");
        djui_chat_message_create("/ban [NAME|ID] - Ban this player from the current game");
        djui_chat_message_create("/permban [NAME|ID] - Ban this player from any game you host");
    }
    if (sConfirming != CCC_NONE) { djui_chat_message_create("/confirm"); }
    smlua_display_chat_commands();
}