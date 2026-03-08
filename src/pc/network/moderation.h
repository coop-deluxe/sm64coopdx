#pragma once
#include <stdbool.h>

enum ModerationActions {
    MODERATION_ACTION_KICK,
    MODERATION_ACTION_BAN,
    MODERATION_ACTION_UNBAN,
    MODERATION_ACTION_MOD,
    MODERATION_ACTION_UNMOD,
    MODERATION_ACTION_COUNT,
};

void network_kick_player(u8 localIndex, char* reason);
void network_ban_player(u8 localIndex, char* reason, bool permanent);
void network_unban_player(char* address);
void network_mod_player(u8 localIndex, char* reason, bool permanent);
void network_unmod_player(char* address);

#include "moderation_list.h"