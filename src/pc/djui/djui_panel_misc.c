#include "djui.h"
#include "djui_theme.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_menu_options.h"
#include "djui_panel_main.h"
#include "djui_panel_options.h"
#include "djui_panel_pause.h"
#include "djui_panel_language.h"
#include "djui_panel_info.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/pc_main.h"
#include "game/hardcoded.h"

static struct DjuiText* sRestartText = NULL;

static void djui_panel_compatibility_checkbox_on_value_change(UNUSED struct DjuiBase* caller) {
    if (gCoopCompatibility != configCoopCompatibility) {
        djui_text_set_text(sRestartText, DLANG(DISPLAY, MUST_RESTART));
    } else {
        djui_text_set_text(sRestartText, "");
    }
}

void djui_panel_misc_create(struct DjuiBase* caller);

static void djui_panel_misc_djui_theme_change(UNUSED struct DjuiBase* caller) {
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

#ifdef DEVELOPMENT
void djui_panel_options_debug_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MISC, DEBUG_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        djui_checkbox_create(body, DLANG(MISC, FIXED_COLLISIONS), (bool*)&gLevelValues.fixCollisionBugs, NULL);
        djui_checkbox_create(body, DLANG(MISC, LUA_PROFILER), &configLuaProfiler, NULL);
        djui_checkbox_create(body, DLANG(MISC, CTX_PROFILER), &configCtxProfiler, NULL);
        djui_checkbox_create(body, DLANG(MISC, DEBUG_PRINT), &configDebugPrint, NULL);
        djui_checkbox_create(body, DLANG(MISC, DEBUG_INFO), &configDebugInfo, NULL);
        djui_checkbox_create(body, DLANG(MISC, DEBUG_ERRORS), &configDebugError, NULL);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
#endif

void djui_panel_misc_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MISC, MISC_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    djui_themes_init();

    {
        djui_checkbox_create(body, DLANG(MISC, PAUSE_IN_SINGLEPLAYER), &configSingleplayerPause, NULL);
        djui_checkbox_create(body, DLANG(MISC, DISABLE_POPUPS), &configDisablePopups, NULL);
        
        char* themeChoices[DJUI_THEME_MAX];
        for (int i = 0; i < DJUI_THEME_MAX; i++) {
            themeChoices[i] = (char*)gDjuiThemes[i]->name;
        }
        djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_THEME), themeChoices, DJUI_THEME_MAX, &configDjuiTheme, djui_panel_misc_djui_theme_change);

        djui_checkbox_create(body, DLANG(MISC, COOP_COMPATIBILITY), &configCoopCompatibility, djui_panel_compatibility_checkbox_on_value_change);
        
        djui_button_create(body, DLANG(MISC, LANGUAGE), DJUI_BUTTON_STYLE_NORMAL, djui_panel_language_create);
        if (gDjuiInMainMenu) {
            djui_button_create(body, DLANG(MISC, MENU_OPTIONS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_main_menu_create);
        }
        djui_button_create(body, DLANG(MISC, INFORMATION), DJUI_BUTTON_STYLE_NORMAL, djui_panel_info_create);
#ifdef DEVELOPMENT
        djui_button_create(body, DLANG(MISC, DEBUG), DJUI_BUTTON_STYLE_NORMAL, djui_panel_options_debug_create);
#endif
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        sRestartText = djui_text_create(body, "");
        djui_text_set_alignment(sRestartText, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_color(&sRestartText->base, 255, 100, 100, 255);
        djui_base_set_size_type(&sRestartText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sRestartText->base, 1.0f, 64);
    }

    // force the restart text to update
    if (gCoopCompatibility != configCoopCompatibility) {
        djui_text_set_text(sRestartText, DLANG(DISPLAY, MUST_RESTART));
    } else {
        djui_text_set_text(sRestartText, "");
    }

    djui_panel_add(caller, panel, NULL);
}
