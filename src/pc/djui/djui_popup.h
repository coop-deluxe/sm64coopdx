#pragma once
#include "djui.h"

struct DjuiPopup {
    struct DjuiBase base;
    struct DjuiText* text;
};

/* |description|
Creates a popup that says `message`. The line count may be decided automatically or be set manually
|descriptionEnd| */
void djui_popup_create(const char* message, OPTIONAL int lines);

void djui_popup_update(void);
