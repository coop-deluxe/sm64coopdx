#pragma once
#include "djui.h"

struct DjuiPopup {
    struct DjuiBase base;
    struct DjuiText* text;
};

/* |description|Creates a popup that says `message` and has `lines`|descriptionEnd| */
void djui_popup_create(const char* message, int lines);
void djui_popup_update(void);
