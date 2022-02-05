#pragma once
#include "djui.h"

struct DjuiChatMessage {
    struct DjuiBase base;
    struct DjuiText* message;
    f32 messageWidth;
    f32 createTime;
};

void djui_chat_message_create_from(u8 globalIndex, const char* message);
void djui_chat_message_create(const char* message);
