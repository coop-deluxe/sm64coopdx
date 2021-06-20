#pragma once
#include <PR/gbi.h>
#include <PR/ultratypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "djui_types.h"
#include "djui_gfx.h"
#include "djui_base.h"
#include "djui_interactable.h"

#include "djui_root.h"
#include "djui_rect.h"
#include "djui_text.h"
#include "djui_image.h"

#include "djui_button.h"

#include "game/game_init.h"
#include "game/ingame_menu.h"

extern struct DjuiRoot* gDjuiRoot;

void djui_render_patch(void);
void djui_render(void);
