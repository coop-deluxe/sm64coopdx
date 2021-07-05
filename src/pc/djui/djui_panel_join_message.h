#pragma once
#include "djui.h"

extern bool gDjuiPanelJoinMessageVisible;

void djui_panel_join_message_error(char* message);
void djui_panel_join_message_create(struct DjuiBase* caller);
