#pragma once
#include "djui.h"

#pragma pack(1)
struct DjuiButton {
    struct DjuiBase base;
    struct DjuiRect* rect;
    struct DjuiText* text;
};

struct DjuiButton* djui_button_create(struct DjuiBase* parent, const char* message);
