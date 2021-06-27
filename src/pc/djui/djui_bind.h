#pragma once
#include "djui.h"
#include "src/pc/configfile.h"

#pragma pack(1)
struct DjuiBind {
    struct DjuiBase base;
    struct DjuiText* text;
    struct DjuiRect* rect;
    struct DjuiButton* buttons[MAX_BINDS];
    unsigned int* configKey;
};

struct DjuiBind* djui_bind_create(struct DjuiBase* parent, const char* message, unsigned int configKey[]);
