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
#include "djui_gfx.h"
#include "djui_base.h"
#include "djui_interactable.h"

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

#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_debug.h"
#include "djui_panel_main.h"
#include "djui_panel_host.h"
#include "djui_panel_host_settings.h"
#include "djui_panel_host_mods.h"
#include "djui_panel_host_save.h"
#include "djui_panel_host_message.h"
#include "djui_panel_join.h"
#include "djui_panel_join_message.h"
#include "djui_panel_pause.h"
#include "djui_panel_options.h"
#include "djui_panel_player.h"
#include "djui_panel_playerlist.h"
#include "djui_panel_modlist.h"
#include "djui_panel_camera.h"
#include "djui_panel_controls.h"
#include "djui_panel_controls_n64.h"
#include "djui_panel_controls_extra.h"
#include "djui_panel_display.h"
#include "djui_panel_sound.h"
#include "djui_panel_confirm.h"
#include "djui_panel_cheats.h"

extern struct DjuiRoot* gDjuiRoot;
extern bool gDjuiInMainMenu;

void djui_init(void);
void djui_connect_menu_open(void);
void djui_render_patch(void);
void djui_render(void);
