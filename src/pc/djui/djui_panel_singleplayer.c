#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_host_mods.h"
#include "djui_panel_host_save.h"
#include "djui_panel_host_settings.h"
#include "djui_panel_loading.h"
#include "djui_panel_singleplayer.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/configfile.h"
#include "pc/pc_main.h"

static bool sSingleplayerPanelOpen = false;

bool djui_panel_singleplayer_is_open(void) {
    return sSingleplayerPanelOpen;
}

static void djui_panel_singleplayer_start(struct DjuiBase* caller) {
    if (!gGameInited) {
        djui_panel_loading_create(caller, djui_panel_singleplayer_start);
        return;
    }

    if (network_is_local_session()) {
        network_rehost_begin();
        return;
    }

    network_reset_reconnect_and_rehost();
    djui_panel_do_singleplayer(false, true);
}

static void djui_panel_singleplayer_destroy(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;
    free(threePanel);
    sSingleplayerPanelOpen = false;
}

void djui_panel_singleplayer_create(struct DjuiBase* caller) {
    struct DjuiBase* defaultBase = NULL;
    bool inSession = network_is_local_session();
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(SINGLEPLAYER, TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        if (!inSession) {
            struct DjuiText* info = djui_text_create(body, DLANG(SINGLEPLAYER, INFO));
            djui_base_set_size_type(&info->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&info->base, 1.0f, 100);
            djui_base_compute_tree(&info->base);
            u16 infoLines = djui_text_count_lines(info, 12);
            djui_base_set_size(&info->base, 1.0f, 32 * 0.8125f * infoLines + 8);
            djui_base_set_color(&info->base, 220, 220, 220, 255);
            djui_text_set_drop_shadow(info, 64, 64, 64, 100);
        }

        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(HOST, SAVE_SLOT));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 220, 220, 220, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

            char starString[64] = { 0 };
            snprintf(starString, 64, "%c x%d - %s", '~' + 1, save_file_get_total_star_count(configHostSaveSlot - 1, 0, 24), configSaveNames[configHostSaveSlot - 1]);
            struct DjuiButton* button1 = djui_button_create(&rect1->base, starString, DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_save_create);
            djui_base_set_size(&button1->base, 0.45f, 32);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
        }

        djui_button_create(body, DLANG(HOST, SETTINGS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_settings_create);
        djui_button_create(body, DLANG(HOST, MODS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_mods_create);

        struct DjuiRect* rect2 = djui_rect_container_create(body, 64);
        {
            struct DjuiButton* button1 = djui_button_create(&rect2->base, inSession ? DLANG(MENU, CANCEL) : DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiButton* button2 = djui_button_create(&rect2->base, inSession ? DLANG(HOST, APPLY) : DLANG(SINGLEPLAYER, START), DJUI_BUTTON_STYLE_NORMAL, djui_panel_singleplayer_start);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            defaultBase = inSession ? &button1->base : &button2->base;
        }
    }

    panel->base.destroy = djui_panel_singleplayer_destroy;
    sSingleplayerPanelOpen = true;

    djui_panel_add(caller, panel, defaultBase);
}
