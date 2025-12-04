#pragma once
#include "djui.h"

struct DjuiChatBox {
    struct DjuiBase base;
    struct DjuiRect* chatContainer;
    struct DjuiFlowLayout* chatFlow;
    struct DjuiInputbox* chatInput;
    bool scrolling;
    f32 scrollY;
};

extern struct DjuiChatBox* gDjuiChatBox;
extern bool gDjuiChatBoxFocus;

void djui_chat_box_toggle(void);
void djui_chat_box_open_with_text(const char* text);
char* get_next_tab_completion_preview(const char* input);
struct DjuiChatBox* djui_chat_box_create(void);
