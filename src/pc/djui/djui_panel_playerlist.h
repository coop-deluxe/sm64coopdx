#pragma once
#include "djui.h"

extern struct DjuiThreePanel* gDjuiPlayerList;
extern bool gAttemptingToOpenPlayerlist;

extern const u8 sPlayerListSize;
extern u8 sPageIndex;

void djui_panel_playerlist_create(UNUSED struct DjuiBase* caller);
