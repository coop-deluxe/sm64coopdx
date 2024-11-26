#pragma once
#include "djui.h"

struct ModCategory {
    const char* langKey;
    const char* category;
};

void djui_panel_host_mods_create(struct DjuiBase* caller);
