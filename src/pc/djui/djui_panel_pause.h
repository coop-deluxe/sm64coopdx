#pragma once
#include "djui.h"

extern bool gDjuiPanelPauseCreated;

void djui_panel_pause_quit_yes(UNUSED struct DjuiBase* caller);

void djui_panel_pause_disconnect_key_update(int scancode);

void djui_panel_pause_create(struct DjuiBase* caller);
