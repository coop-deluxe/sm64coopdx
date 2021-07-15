#pragma once
#include "djui.h"

void djui_panel_confirm_create(struct DjuiBase* caller, char* title, char* message, void (*on_yes_click)(struct DjuiBase*));

