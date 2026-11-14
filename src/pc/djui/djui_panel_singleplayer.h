#pragma once
#include "djui.h"

void djui_panel_singleplayer_create(struct DjuiBase* caller);
bool djui_panel_singleplayer_is_open(void);
void djui_panel_do_singleplayer(bool reconnecting, bool playSound);
