#pragma once
#include "djui.h"

struct DjuiSearchbox {
    struct DjuiBase base;
    struct DjuiText* text;
    struct DjuiImage* image;
    struct DjuiInputbox* inputbox;
    void (*on_value_change)(struct DjuiBase*);
};

struct DjuiSearchbox* djui_searchbox_create(struct DjuiBase* base, void (*on_value_change)(struct DjuiBase*));