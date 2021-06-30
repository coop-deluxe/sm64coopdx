#pragma once
#include "djui.h"

#pragma pack(1)
struct DjuiInputbox {
    struct DjuiBase base;
    char* buffer;
    u16 bufferSize;
    u16 selection[2];
    f32 viewX;
};

struct DjuiInputbox* djui_inputbox_create(struct DjuiBase* parent, u16 bufferSize);
