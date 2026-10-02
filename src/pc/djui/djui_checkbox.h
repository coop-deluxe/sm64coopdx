#pragma once
#include "djui.h"

struct DjuiCheckbox {
    struct DjuiBase base;
    struct DjuiRect* rect;
    struct DjuiRect* rectValue;
    struct DjuiText* text;
    bool* value;
};

void djui_checkbox_update_style(struct DjuiBase* base);
struct DjuiCheckbox* djui_checkbox_create(struct DjuiBase* parent, const char* message, bool* value, void (*on_value_change)(struct DjuiBase*));
