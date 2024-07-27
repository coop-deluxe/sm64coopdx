#include "djui.h"
#include "djui_theme.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_main.h"
#include "djui_panel_options.h"
#include "djui_panel_misc.h"
#include "djui_panel_pause.h"
#include "djui_hud_utils.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "game/level_update.h"

static struct DjuiSelectionbox* sLevelBox = NULL;
static struct DjuiCheckbox* sUseStageMusicCheckbox = NULL;
static struct DjuiCheckbox* sRandomStageCheckbox = NULL;
// static struct DjuiCheckbox* sVanillaDemosCheckbox = NULL;

void djui_panel_main_menu_create(struct DjuiBase* caller);

static void djui_panel_level_menu(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(&sLevelBox->base, !(configMenuRandom || configMenuStaffRoll));
    djui_base_set_enabled(&sUseStageMusicCheckbox->base, !configMenuStaffRoll);
    djui_base_set_enabled(&sRandomStageCheckbox->base, !configMenuStaffRoll);
    // djui_base_set_enabled(&sVanillaDemosCheckbox->base, !configMenuStaffRoll);
    if (configMenuStaffRoll) {
        warp_credits();
        level_trigger_warp(gMarioState, WARP_OP_CREDITS_NEXT);
    }
}

static void djui_panel_menu_options_djui_setting_change(UNUSED struct DjuiBase* caller) {
    if (gDjuiInMainMenu) {
        djui_panel_shutdown();
        gDjuiInMainMenu = true;
        djui_panel_main_create(NULL);
        djui_panel_options_create(NULL);
        djui_panel_misc_create(NULL);
        djui_panel_main_menu_create(NULL);
    } else if (gDjuiPanelPauseCreated) {
        djui_panel_shutdown();
        djui_panel_pause_create(NULL);
        djui_panel_options_create(NULL);
        djui_panel_misc_create(NULL);
        djui_panel_main_menu_create(NULL);

        djui_text_set_font(gDjuiPauseOptions, gDjuiFonts[configDjuiThemeFont == 1 ? FONT_ALIASED : FONT_ALIASED ? configDjuiThemeFont == 0 ? FONT_NORMAL : FONT_NORMAL ? configDjuiThemeFont == 2 : FONT_EXCOOP : FONT_EXCOOP]);
        djui_text_set_text(gDjuiPauseOptions, DLANG(MISC, R_BUTTON));
    }
}

void djui_panel_main_menu_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MENU_OPTIONS, MENU_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    djui_themes_init();

    {
        djui_checkbox_create(body, DLANG(DJUI_THEMES, CENTER), &configDjuiThemeCenter, djui_panel_menu_options_djui_setting_change);
        char* themeChoices[DJUI_THEME_MAX];
        for (int i = 0; i < DJUI_THEME_MAX; i++) {
            themeChoices[i] = (char*)gDjuiThemes[i]->name;
        }
        djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_THEME), themeChoices, DJUI_THEME_MAX, &configDjuiTheme, djui_panel_menu_options_djui_setting_change);
        char* djuiScaleChoices[5] = {DLANG(DJUI_THEMES, AUTO), "x0.5", "x0.85", "x1.0", "x1.5"};
        djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_SCALE), djuiScaleChoices, 5, &configDjuiScale, djui_panel_menu_options_djui_setting_change);
        char* djuiFontChoices[3] = {DLANG(DJUI_THEMES, FONT_NORMAL), DLANG(DJUI_THEMES, FONT_ALIASED), DLANG(DJUI_THEMES, FONT_EXCOOP)};
        djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_FONT), djuiFontChoices, 3, &configDjuiThemeFont, djui_panel_menu_options_djui_setting_change);

        if (gDjuiInMainMenu) {
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

            struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(body, DLANG(MENU_OPTIONS, LEVEL), levelChoices, 18, &configMenuLevel, NULL);
            djui_base_set_enabled(&selectionbox1->base, !(configMenuRandom || configMenuStaffRoll));
            sLevelBox = selectionbox1;

            djui_checkbox_create(body, DLANG(MENU_OPTIONS, STAFF_ROLL), &configMenuStaffRoll, djui_panel_level_menu);
            struct DjuiCheckbox* checkbox1 = djui_checkbox_create(body, DLANG(MENU_OPTIONS, USE_STAGE_MUSIC), &configMenuSound, NULL);
            djui_base_set_enabled(&checkbox1->base, !configMenuStaffRoll);
            sUseStageMusicCheckbox = checkbox1;
            struct DjuiCheckbox* checkbox2 = djui_checkbox_create(body, DLANG(MENU_OPTIONS, RANDOM_STAGE), &configMenuRandom, djui_panel_level_menu);
            djui_base_set_enabled(&checkbox2->base, !configMenuStaffRoll);
            sRandomStageCheckbox = checkbox2;
            // struct DjuiCheckbox* checkbox3 = djui_checkbox_create(body, DLANG(MENU_OPTIONS, PLAY_VANILLA_DEMOS), &configMenuDemos, stop_demo);
            // djui_base_set_enabled(&checkbox3->base, !configMenuStaffRoll);
            // sVanillaDemosCheckbox = checkbox3;
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
