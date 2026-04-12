#pragma once
#include "djui.h"

#define MAX_CATEGORY_STRINGS 12

struct ModCategory {
    const char* langKey;
    const char* category[MAX_CATEGORY_STRINGS];
};

void djui_panel_host_mods_create(struct DjuiBase* caller);
