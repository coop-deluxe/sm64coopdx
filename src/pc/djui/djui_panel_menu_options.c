#include "djui.h"
#include "djui_theme.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_main.h"
#include "djui_panel_options.h"
#include "djui_panel_misc.h"
#include "djui_panel_pause.h"
#include "djui_panel_menu_options.h"
#include "djui_panel_modlist.h"
#include "djui_panel_playerlist.h"
#include "djui_hud_utils.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/lua/smlua_hooks.h"
#include "game/level_update.h"
#include "seq_ids.h"

static struct DjuiSelectionbox* sLevelBox = NULL;
static struct DjuiCheckbox* sRandomStageCheckbox = NULL;
// static struct DjuiCheckbox* sVanillaDemosCheckbox = NULL;

struct MainMenuSounds gMainMenuSounds[] = {
    { "TITLE_SCREEN", SEQ_MENU_TITLE_SCREEN },
    { "FILE_SELECT", SEQ_MENU_FILE_SELECT },
    { "GRASS", SEQ_LEVEL_GRASS },
    { "WATER", SEQ_LEVEL_WATER },
    { "SNOW", SEQ_LEVEL_SNOW },
    { "SLIDE", SEQ_LEVEL_SLIDE },
    { "BOWSER_STAGE", SEQ_LEVEL_KOOPA_ROAD },
    { "BOWSER_FIGHT", SEQ_LEVEL_BOSS_KOOPA },
    { "SPOOKY", SEQ_LEVEL_SPOOKY },
    { "HOT", SEQ_LEVEL_HOT },
    { "UNDERGROUND", SEQ_LEVEL_UNDERGROUND },
    { "BOWSER_FINALE", SEQ_LEVEL_BOSS_KOOPA_FINAL },
    { "STAFF_ROLL", SEQ_EVENT_CUTSCENE_CREDITS },
    { "STAGE_MUSIC", STAGE_MUSIC },
    { "INSIDE_THE_CASTLE", SEQ_LEVEL_INSIDE_CASTLE },
};

void djui_panel_main_menu_create(struct DjuiBase* caller);

static void djui_panel_level_menu(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(&sLevelBox->base, !(configMenuRandom || configMenuStaffRoll));
    djui_base_set_enabled(&sRandomStageCheckbox->base, !configMenuStaffRoll);
    // djui_base_set_enabled(&sVanillaDemosCheckbox->base, !configMenuStaffRoll);
    if (configMenuStaffRoll) {
        warp_credits();
        level_trigger_warp(gMarioState, WARP_OP_CREDITS_NEXT);
    }
}

static void djui_panel_staff_roll(UNUSED struct DjuiBase* caller) {
    // update level
    djui_panel_level_menu(NULL);
    // change menu sound
    if (configMenuStaffRoll && gMainMenuSounds[configMenuSound].sound == STAGE_MUSIC) {
        configMenuSound = 0;
    }
    // restart djui back to this menu
    djui_panel_shutdown();
    gDjuiInMainMenu = true;
    djui_panel_main_create(NULL);
    djui_panel_options_create(NULL);
    djui_panel_misc_create(NULL);
    djui_panel_main_menu_create(NULL);
}

extern bool gDjuiChangingTheme;
static void djui_panel_menu_options_djui_setting_change(UNUSED struct DjuiBase* caller) {
    gDjuiChangingTheme = true;
    if (gDjuiInMainMenu) {
        djui_panel_shutdown();
        gDjuiInMainMenu = true;
        djui_panel_playerlist_create(NULL);
        djui_panel_modlist_create(NULL);
        djui_panel_main_create(NULL);
        djui_panel_options_create(NULL);
        djui_panel_misc_create(NULL);
        djui_panel_main_menu_create(NULL);
    } else if (gDjuiPanelPauseCreated) {
        djui_panel_shutdown();
        djui_panel_playerlist_create(NULL);
        djui_panel_modlist_create(NULL);
        djui_panel_pause_create(NULL);
        djui_panel_options_create(NULL);
        djui_panel_misc_create(NULL);
        djui_panel_main_menu_create(NULL);

        djui_text_set_font(gDjuiPauseOptions, gDjuiFonts[configDjuiThemeFont == 0 ? FONT_NORMAL : FONT_ALIASED]);
        djui_text_set_text(gDjuiPauseOptions, DLANG(MISC, R_BUTTON));

        djui_text_set_font(gDjuiModReload, gDjuiFonts[configDjuiThemeFont == 0 ? FONT_NORMAL : FONT_ALIASED]);
        djui_text_set_text(gDjuiModReload, DLANG(MISC, L_BUTTON));
    }

    if (gDjuiChatBox) {
        struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
        struct DjuiColor* textColor = &theme->interactables.textColor;
        djui_inputbox_set_text_color(gDjuiChatBox->chatInput, textColor->r, textColor->g, textColor->b, textColor->a);
    }
    gDjuiChangingTheme = false;

    smlua_call_event_hooks(HOOK_ON_DJUI_THEME_CHANGED);
}

void djui_panel_main_menu_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MENU_OPTIONS, MENU_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    djui_themes_init();

    {
        djui_checkbox_create(body, DLANG(DJUI_THEMES, CENTER), &configDjuiThemeCenter, djui_panel_menu_options_djui_setting_change);
        djui_checkbox_create(body, DLANG(DJUI_THEMES, GRADIENTS), &configDjuiThemeGradients, djui_panel_menu_options_djui_setting_change);

        djui_checkbox_create(body, DLANG(DJUI_THEMES, SMOOTH_SCROLLING), &configSmoothScrolling, NULL);

        char* themeChoices[DJUI_THEME_MAX];
        for (int i = 0; i < DJUI_THEME_MAX; i++) {
            themeChoices[i] = (char*)gDjuiThemes[i]->name;
        }
        djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_THEME), themeChoices, DJUI_THEME_MAX, &configDjuiTheme, djui_panel_menu_options_djui_setting_change);

        char* djuiScaleChoices[5] = {DLANG(DJUI_THEMES, AUTO), "x0.5", "x0.75", "x1.0", "x1.5"};
        djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_SCALE), djuiScaleChoices, 5, &configDjuiScale, djui_panel_menu_options_djui_setting_change);

        char* djuiFontChoices[2] = {DLANG(DJUI_THEMES, FONT_NORMAL), DLANG(DJUI_THEMES, FONT_ALIASED)};
        djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_FONT), djuiFontChoices, 2, &configDjuiThemeFont, djui_panel_menu_options_djui_setting_change);

        if (gDjuiInMainMenu) {
            // copy sound choices from gMainMenuSounds
            u32 numSounds = sizeof(gMainMenuSounds) / sizeof(gMainMenuSounds[0]);
            // if stage roll is on, we shouldn't be allowed to use Stage Music, so remove the entry
            if (configMenuStaffRoll) {
                numSounds -= 1;
            }
            char *soundChoices[sizeof(gMainMenuSounds)];

            // loop thru all sounds names, and add those to the soundChoices string array
            for (u32 i = 0; i < numSounds; i++) {
                soundChoices[i] = djui_language_get("MUSIC", gMainMenuSounds[i].key);
            }

            char *levelChoices[gMenuLevelsCount];

            // construct level choices
            for (u32 i = 0; i < gMenuLevelsCount; i++) {
                levelChoices[i] = djui_language_get("LEVELS", gMenuLevels[i].key);
            }

            struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(body, DLANG(MENU_OPTIONS, LEVEL), levelChoices, gMenuLevelsCount, &configMenuLevel, NULL);
            djui_base_set_enabled(&selectionbox1->base, !(configMenuRandom || configMenuStaffRoll));
            sLevelBox = selectionbox1;
            djui_selectionbox_create(body, DLANG(MENU_OPTIONS, MUSIC), soundChoices, numSounds, &configMenuSound, NULL);
            djui_checkbox_create(body, DLANG(MENU_OPTIONS, STAFF_ROLL), &configMenuStaffRoll, djui_panel_staff_roll);
            djui_checkbox_create(body, DLANG(MENU_OPTIONS, ENV_SOUNDS), &configMenuEnvSounds, NULL);
            struct DjuiCheckbox* checkbox1 = djui_checkbox_create(body, DLANG(MENU_OPTIONS, RANDOM_STAGE), &configMenuRandom, djui_panel_level_menu);
            djui_base_set_enabled(&checkbox1->base, !configMenuStaffRoll);
            sRandomStageCheckbox = checkbox1;
            // struct DjuiCheckbox* checkbox2 = djui_checkbox_create(body, DLANG(MENU_OPTIONS, PLAY_VANILLA_DEMOS), &configMenuDemos, stop_demo);
            // djui_base_set_enabled(&checkbox2->base, !configMenuStaffRoll);
            // sVanillaDemosCheckbox = checkbox2;
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
