#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/game/level_update.h"

static struct DjuiSelectionbox* sLevelBox = NULL;

static void djui_panel_random_menu(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(&sLevelBox->base, !configMenuRandom);
}

void djui_panel_main_menu_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("\\#ff0800\\M\\#1be700\\A\\#00b3ff\\I\\#ffef00\\N \\#ff0800\\M\\#ff0800\\E\\#1be700\\N\\#ffef00\\U\\#ff0800\\");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

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
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Level", levelChoices, 17, &configMenuLevel, NULL);
        djui_base_set_enabled(&selectionbox1->base, !configMenuRandom);
        sLevelBox = selectionbox1;
        
        djui_checkbox_create(&body->base, "Use Stage Music", &configMenuSound, NULL);
        djui_checkbox_create(&body->base, "Random Stage", &configMenuRandom, djui_panel_random_menu);
        djui_checkbox_create(&body->base, "Play Vanilla Demos", &configMenuDemos, stop_demo);

        djui_button_create(&body->base, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
