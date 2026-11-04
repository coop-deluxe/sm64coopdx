#pragma once
#include "djui.h"

/* |description|
Pushes a new panel to the mod menu using `panelId`. You can change the `headerTitle`
or adjust `hideBackButton`
|descriptionEnd| */
void mod_menu_push_panel(const char *panelId, OPTIONAL const char *headerTitle, OPTIONAL bool hideBackButton);

/* |description|Pops the last panel|descriptionEnd| */
void mod_menu_pop_panel(void);

void djui_panel_mod_menu_mod_button(struct DjuiBase* caller);
void djui_panel_mod_menu_mod_create(struct DjuiBase* caller);
void djui_panel_mod_menu_create(struct DjuiBase* caller);
