#pragma once
#include "djui.h"

extern struct DjuiThreePanel* gDjuiPlayerList;
extern bool gAttemptingToOpenPlayerlist;

extern const u8 sPlayerListSize;
extern u8 sPageIndex;

void djui_panel_playerlist_create(UNUSED struct DjuiBase* caller);

#define BK_LEFT  lr & 1
#define BK_RIGHT lr & 2

#define NONE        0
#define KICK        (1 << 0)
#define BAN         (1 << 1)
#define PERM_BAN    (1 << 2)