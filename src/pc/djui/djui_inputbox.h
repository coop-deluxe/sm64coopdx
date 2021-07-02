#pragma once
#include "djui.h"

#pragma pack(1)
struct DjuiInputbox {
    struct DjuiBase base;
    char* buffer;
    u16 bufferSize;
    u16 selection[2];
    f32 viewX;
    void (*on_enter_press)(void);
};

void djui_inputbox_hook_enter_press(struct DjuiInputbox* inputbox, void (*on_enter_press)(void));

struct DjuiInputbox* djui_inputbox_create(struct DjuiBase* parent, u16 bufferSize);
