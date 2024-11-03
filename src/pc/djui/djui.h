#pragma once
#include <PR/gbi.h>
#include <PR/ultratypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game/game_init.h"
#include "game/ingame_menu.h"

#include "djui_types.h"
#include "djui_font.h"
#include "djui_theme.h"
#include "djui_gfx.h"
#include "djui_base.h"
#include "djui_interactable.h"
#include "djui_language.h"

#include "djui_root.h"
#include "djui_cursor.h"
#include "djui_rect.h"
#include "djui_text.h"
#include "djui_image.h"
#include "djui_three_panel.h"

#include "djui_button.h"
#include "djui_inputbox.h"
#include "djui_slider.h"
#include "djui_progress_bar.h"
#include "djui_checkbox.h"
#include "djui_flow_layout.h"
#include "djui_selectionbox.h"
#include "djui_bind.h"
#include "djui_popup.h"
#include "djui_chat_box.h"
#include "djui_chat_message.h"
#include "djui_console.h"
#include "djui_paginated.h"

extern struct DjuiRoot* gDjuiRoot;
extern struct DjuiText* gDjuiPauseOptions;
extern bool gDjuiInMainMenu;
extern bool gDjuiInPlayerMenu;
extern bool gDjuiDisabled;

void djui_init(void);
void djui_init_late(void);
void djui_connect_menu_open(void);
void djui_lua_error(char* text, struct DjuiColor color);
void djui_lua_error_clear(void);
void djui_render(void);
void djui_reset_hud_params(void);

void djui_shutdown(void);
