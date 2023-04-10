#pragma once
#include "djui.h"

struct DjuiLobbyEntry {
    struct DjuiBase base;
};

struct DjuiLobbyEntry* djui_lobby_entry_create(struct DjuiBase* parent, char* host, char* mode, char* players, void (*on_click)(struct DjuiBase*));
