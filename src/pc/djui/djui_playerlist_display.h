#pragma once
#include "djui.h"

void djui_playerlist_display_render(void);
void djui_playerlist_display_create(void);
void djui_playerlist_display_destroy(void);

#ifdef TARGET_WEB
void web_teleport_to_player(int index);
#endif
