#pragma once
#include "djui.h"

struct DjuiSelectionbox {
    struct DjuiBase base;
    struct DjuiText* text;
    struct DjuiRect* rect;
    struct DjuiText* rectText;
    struct DjuiImage* rectImage;
    unsigned int* value;
    char** choices;
    u8 choiceCount;
};

struct DjuiSelectionbox* djui_selectionbox_create(struct DjuiBase* parent, const char* message, char* choices[], u8 choiceCount, unsigned int* value);