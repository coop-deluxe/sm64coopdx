#pragma once
#include "djui.h"

void djui_panel_moderation_confirm_create(struct DjuiBase* caller, u8 action, u8 localIndex, bool permanent, void (*on_yes_click)(struct DjuiBase*));
void djui_panel_moderation_confirm_create_using_list(struct DjuiBase* caller, u8 action, u8 listType, u16 listIndex, void (*on_yes_click)(struct DjuiBase*));