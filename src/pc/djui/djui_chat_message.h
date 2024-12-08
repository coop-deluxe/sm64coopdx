#pragma once
#include "djui.h"

#define MAX_CHAT_MSG_LENGTH 500

struct DjuiChatMessage {
    struct DjuiBase base;
    struct DjuiText* message;
    f32 messageWidth;
    f32 createTime;
};

void djui_chat_message_create_from(u8 globalIndex, const char* message);
/* |description|Creates a `message` in the game's chat box|descriptionEnd| */
void djui_chat_message_create(const char* message);
