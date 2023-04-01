#pragma once
#include "djui.h"

#define DJUI_DEFAULT_PANEL_WIDTH (500.0f + (16 * 2.0f))
#define DJUI_PANEL_HEADER_OFFSET (-16)

struct DjuiPanel {
    struct DjuiBase* base;
    struct DjuiPanel* parent;
    struct DjuiBase* defaultElementBase;
    void (*on_panel_destroy)(struct DjuiBase*);
};

bool djui_panel_is_active(void);
struct DjuiPanel* djui_panel_add(struct DjuiBase* caller, struct DjuiThreePanel* threePanel, struct DjuiBase* defaultElementBase);
void djui_panel_back(void);
void djui_panel_update(void);
void djui_panel_shutdown(void);
