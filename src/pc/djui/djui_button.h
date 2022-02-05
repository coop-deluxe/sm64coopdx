#pragma once
#include "djui.h"

struct DjuiButton {
    struct DjuiBase base;
    struct DjuiRect* rect;
    struct DjuiText* text;
    u8 style;
};

void djui_button_set_style(struct DjuiButton* button, u8 style);

struct DjuiButton* djui_button_create(struct DjuiBase* parent, const char* message);
