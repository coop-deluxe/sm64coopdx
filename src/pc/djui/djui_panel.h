#pragma once
#include "djui.h"

#define DJUI_DEFAULT_PANEL_WIDTH (410.0f + (16 * 2.0f))
#define DJUI_PANEL_HEADER_OFFSET (-8)

bool djui_panel_is_active(void);
void djui_panel_add(struct DjuiBase* caller, struct DjuiBase* panelBase, struct DjuiBase* defaultElementBase);
void djui_panel_back(void);
void djui_panel_update(void);
void djui_panel_shutdown(void);
