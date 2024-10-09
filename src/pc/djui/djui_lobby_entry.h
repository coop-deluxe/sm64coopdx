#pragma once
#include "djui.h"

struct DjuiLobbyEntry {
    struct DjuiBase base;
    const char* description;
};

struct DjuiLobbyEntry* djui_lobby_entry_create(struct DjuiBase* parent, char* host, char* mode, char* players, char* description, bool disabled, void (*on_click)(struct DjuiBase*), void (*on_hover)(struct DjuiBase*), void (*on_hover_end)(struct DjuiBase*));
