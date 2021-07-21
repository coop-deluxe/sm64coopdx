#pragma once
#include "djui.h"

#pragma pack(1)
struct DjuiPopup {
    struct DjuiBase base;
    struct DjuiText* text;
};

struct DjuiPopup* djui_popup_create(const char* message, int lines);
void djui_popup_update(void);
