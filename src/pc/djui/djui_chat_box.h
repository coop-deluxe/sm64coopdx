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
struct DjuiChatBox* djui_chat_box_create(void);
