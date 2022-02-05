#pragma once
#include "djui.h"

struct DjuiInputbox {
    struct DjuiBase base;
    char* buffer;
    u16 bufferSize;
    u16 selection[2];
    f32 viewX;
    struct DjuiColor textColor;
    void (*on_enter_press)(struct DjuiInputbox*);
    void (*on_escape_press)(struct DjuiInputbox*);
};

void djui_inputbox_set_text_color(struct DjuiInputbox* inputbox, u8 r, u8 g, u8 b, u8 a);
void djui_inputbox_set_text(struct DjuiInputbox* inputbox, char* text);
void djui_inputbox_select_all(struct DjuiInputbox* inputbox);
void djui_inputbox_hook_enter_press(struct DjuiInputbox* inputbox, void (*on_enter_press)(struct DjuiInputbox*));
void djui_inputbox_hook_escape_press(struct DjuiInputbox* inputbox, void (*on_escape_press)(struct DjuiInputbox*));
bool djui_inputbox_on_key_down(struct DjuiBase* base, int scancode);
void djui_inputbox_on_key_up(struct DjuiBase* base, int scancode);

struct DjuiInputbox* djui_inputbox_create(struct DjuiBase* parent, u16 bufferSize);
