#pragma once
#include "djui.h"

struct DjuiSearchbox {
    struct DjuiBase base;
    struct DjuiText* text;
    struct DjuiImage* image;
    struct DjuiInputbox* inputbox;
    void (*on_value_change)(struct DjuiBase*);
};

bool djui_searchbox_has_string(struct DjuiSearchbox* searchbox, const char* string);
bool djui_searchbox_has_any_strings(struct DjuiSearchbox* searchbox, const char** strings, size_t count);
struct DjuiSearchbox* djui_searchbox_create(struct DjuiBase* base, void (*on_value_change)(struct DjuiBase*));