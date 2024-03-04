#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "data/dynos.c.h"
#include "pc/network/network.h"
#include "djui_panel_main.h"
#include "djui_panel_options.h"
#include "djui_panel_player.h"

void djui_panel_dynos_create(struct DjuiBase* caller);

static void djui_panel_dynos_apply(struct DjuiBase* caller) {
    dynos_pack_set_enabled(caller->tag, caller->bTag);
}

static void djui_panel_dynos_global_player_models(UNUSED struct DjuiBase* caller) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        network_player_update_model(i);
    }
}

static void djui_panel_dynos_refresh(UNUSED struct DjuiBase* base) {
    dynos_gfx_init();
    dynos_packs_init();

    djui_panel_shutdown();
    gDjuiInMainMenu = true;
    djui_panel_main_create(NULL);
    djui_panel_options_create(NULL);
    djui_panel_dynos_create(NULL);
}

void djui_panel_dynos_create(struct DjuiBase* caller) {
    int packCount = dynos_pack_get_count();
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(DYNOS, DYNOS));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        struct DjuiBase* layoutBase = &paginated->layout->base;
        for (int i = 0; i < packCount; i++) {
            if (dynos_pack_get_exists(i)) {
                bool tmp = dynos_pack_get_enabled(i);
                const char* pack = dynos_pack_get_name(i);

                struct DjuiCheckbox* checkbox1 = djui_checkbox_create(layoutBase, pack, &tmp, djui_panel_dynos_apply);
                checkbox1->base.tag = i;
                checkbox1->base.bTag = tmp;
                checkbox1->value = &checkbox1->base.bTag;
            }
        }
        djui_paginated_calculate_height(paginated);

        struct DjuiRect* space = djui_rect_create(body);
        djui_base_set_size_type(&space->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&space->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 32, 1);
        djui_base_set_color(&space->base, 220, 220, 220, 255);

        djui_checkbox_create(body, DLANG(DYNOS, GLOBAL_PLAYER_MODELS), &configGlobalPlayerModels, djui_panel_dynos_global_player_models);
        if (gNetworkType == NT_NONE) {
            struct DjuiRect* rect1 = djui_rect_container_create(body, 64);
            {
                djui_button_left_create(&rect1->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
                djui_button_right_create(&rect1->base, DLANG(LOBBIES, REFRESH), DJUI_BUTTON_STYLE_NORMAL, djui_panel_dynos_refresh);
            }
        } else {
            djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
        }

        panel->bodySize.value = paginated->base.height.value + 16 + 64 + 64;
    }

    djui_panel_add(caller, panel, NULL);
    gDjuiPanelPlayerCreated = true;
}
