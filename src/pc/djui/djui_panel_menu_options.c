#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/game/level_update.h"

static struct DjuiSelectionbox* sLevelBox = NULL;

static void djui_panel_random_menu(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(&sLevelBox->base, !configMenuRandom);
}

void djui_panel_main_menu_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("MAIN MENU");
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
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(body, "Level", levelChoices, 17, &configMenuLevel, NULL);
        djui_base_set_enabled(&selectionbox1->base, !configMenuRandom);
        sLevelBox = selectionbox1;
        
        djui_checkbox_create(body, "Use Stage Music", &configMenuSound, NULL);
        djui_checkbox_create(body, "Random Stage", &configMenuRandom, djui_panel_random_menu);
        djui_checkbox_create(body, "Play Vanilla Demos", &configMenuDemos, stop_demo);

        djui_button_create(body, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
