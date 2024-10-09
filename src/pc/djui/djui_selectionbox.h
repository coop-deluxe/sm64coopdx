#pragma once
#include "djui.h"

struct DjuiSelectionbox {
    struct DjuiBase base;
    struct DjuiText* text;
    struct DjuiRect* rect;
    struct DjuiText* rectText;
    struct DjuiImage* rectImage;
    struct DjuiImage* rectImage2;
    unsigned int* value;
    char** choices;
    u8 choiceCount;
};

struct DjuiSelectionbox* djui_selectionbox_create(struct DjuiBase* parent, const char* message, char* choices[], u8 choiceCount, unsigned int* value, void (*on_value_change)(struct DjuiBase*));
void djui_selectionbox_update_value(struct DjuiBase* base);