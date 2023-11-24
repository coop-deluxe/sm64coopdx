#include "djui.h"
#include "djui_theme.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_pause.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/game/level_update.h"

static bool sChangedScale = false;

static struct DjuiSelectionbox* sLevelBox = NULL;

static void djui_panel_random_menu(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(&sLevelBox->base, !configMenuRandom);
}

static void djui_panel_misc_djui_setting_change(UNUSED struct DjuiBase* caller) {
    // god this is so hacky and terrible - djoslin0, 2023
    if (gDjuiInMainMenu) {
        djui_panel_shutdown();
        gDjuiInMainMenu = true;
        djui_panel_main_create(NULL);
        djui_panel_options_create(NULL);
        djui_panel_misc_create(NULL);
    } else if (gDjuiPanelPauseCreated) {
        djui_panel_shutdown();
        djui_panel_pause_create(NULL);
        djui_panel_options_create(NULL);
        djui_panel_misc_create(NULL);
    } else {
        djui_panel_shutdown();
    }

}

void djui_panel_main_menu_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MENU_OPTIONS, MAIN_MENU));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        char* levelChoices[18] = {
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
            "WDW"
        };

        char* djuiScaleChoices[3] = {"x0.85", "x1.0", "x1.5"};

        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(body, DLANG(MENU_OPTIONS, LEVEL), levelChoices, 18, &configMenuLevel, NULL);
        djui_base_set_enabled(&selectionbox1->base, !configMenuRandom);
        sLevelBox = selectionbox1;

        djui_checkbox_create(body, DLANG(MENU_OPTIONS, USE_STAGE_MUSIC), &configMenuSound, NULL);
        djui_checkbox_create(body, DLANG(MENU_OPTIONS, RANDOM_STAGE), &configMenuRandom, djui_panel_random_menu);
        djui_checkbox_create(body, DLANG(MENU_OPTIONS, PLAY_VANILLA_DEMOS), &configMenuDemos, stop_demo);

        char* themeChoices[DJUI_THEME_MAX];
        for (int i = 0; i < DJUI_THEME_MAX; i++) {
            themeChoices[i] = (char*)gDjuiThemes[i]->name;
        }
        djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_THEME), themeChoices, DJUI_THEME_MAX, &configDjuiTheme, djui_panel_misc_djui_setting_change);

        djui_checkbox_create(body, DLANG(DJUI_THEMES, CENTER), &configDjuiThemeCenter, djui_panel_misc_djui_setting_change);
        
        djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_SCALE), djuiScaleChoices, 3, &configDjuiScale, djui_panel_misc_djui_setting_change);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
