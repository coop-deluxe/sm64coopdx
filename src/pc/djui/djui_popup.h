#pragma once
#include "djui.h"

struct DjuiPopup {
    struct DjuiBase base;
    struct DjuiText* text;
};

void djui_popup_create(const char* message, int lines);
void djui_popup_update(void);
