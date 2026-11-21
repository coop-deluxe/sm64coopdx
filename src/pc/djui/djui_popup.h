#pragma once

#include "djui.h"

#define MAX_GLOBAL_POPUP_MESSAGE_LENGTH 512

struct DjuiPopup {
    struct DjuiBase base;
    struct DjuiText* text;
};

/* |description|Creates a popup that says `message` and has `lines`|descriptionEnd| */
void djui_popup_create(const char* message, int lines);
void djui_popup_update(void);
