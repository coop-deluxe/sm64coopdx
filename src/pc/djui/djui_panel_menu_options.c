#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/game/level_update.h"

static struct DjuiSelectionbox* sLevelBox = NULL;

static void djui_panel_random_menu(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(&sLevelBox->base, !configMenuRandom);
}

void djui_panel_main_menu_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MENU_OPTIONS, MAIN_MENU));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        char* levelChoices[17] = {
            "CG",
            "BOB",
            "WF",
            "WMOTR",
            "JRB",
            "SSL",
            "TTM",
            "SL",
            "BBH",
            "LLL",
            "THI",
            "HMC",
            "CCM",
            "RR",
            "BITDW",
            "PSS",
            "TTC",
        };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(body, DLANG(MENU_OPTIONS, LEVEL), levelChoices, 17, &configMenuLevel, NULL);
        djui_base_set_enabled(&selectionbox1->base, !configMenuRandom);
        sLevelBox = selectionbox1;

        djui_checkbox_create(body, DLANG(MENU_OPTIONS, USE_STAGE_MUSIC), &configMenuSound, NULL);
        djui_checkbox_create(body, DLANG(MENU_OPTIONS, RANDOM_STAGE), &configMenuRandom, djui_panel_random_menu);
        djui_checkbox_create(body, DLANG(MENU_OPTIONS, PLAY_VANILLA_DEMOS), &configMenuDemos, stop_demo);


        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
