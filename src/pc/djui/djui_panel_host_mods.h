#pragma once
#include "djui.h"
#include "pc/mods/mod_presets.h"

void djui_panel_host_mods_create(struct DjuiBase* caller);
void djui_panel_host_mods_rebuild_list(void);
void djui_panel_host_mods_preview_preset(struct ModPreset* preset);
void djui_panel_host_mods_describe_mod(s64 index);
