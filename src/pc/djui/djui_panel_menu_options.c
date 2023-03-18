#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/game/level_update.h"

static struct DjuiSelectionbox* sLevelBox = NULL;

static void djui_panel_random_menu(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(&sLevelBox->base, !configMenuRandom);
}

void djui_panel_main_menu_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 4 + 64 * 1 + 16 * 4;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\M\\#1be700\\A\\#00b3ff\\I\\#ffef00\\N \\#ff0800\\M\\#ff0800\\E\\#1be700\\N\\#ffef00\\U\\#ff0800\\");
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
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Level", levelChoices, 17, &configMenuLevel);
        djui_base_set_size_type(&selectionbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox1->base, 1.0f, 32);
        djui_base_set_enabled(&selectionbox1->base, !configMenuRandom);
        sLevelBox = selectionbox1;
        defaultBase = &selectionbox1->base;
        
        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Use Stage Music", &configMenuSound);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);
        
        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "Random Stage", &configMenuRandom);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);
        djui_interactable_hook_value_change(&checkbox2->base, djui_panel_random_menu);

        struct DjuiCheckbox* checkbox3 = djui_checkbox_create(&body->base, "Play Vanilla Demos", &configMenuDemos);
        djui_base_set_size_type(&checkbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox3->base, 1.0f, 32);
        djui_interactable_hook_value_change(&checkbox3->base, stop_demo);

        struct DjuiButton* button1 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_button_set_style(button1, 1);
        djui_interactable_hook_click(&button1->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
