#pragma once
#include "djui.h"
#include <time.h>

#pragma pack(1)
struct DjuiChatMessage {
    struct DjuiBase base;
    struct DjuiText* message;
    f32 messageWidth;
    clock_t createTime;
};

struct DjuiChatMessage* djui_chat_message_create_from(u8 globalIndex, char* message);
struct DjuiChatMessage* djui_chat_message_create(char* message);
