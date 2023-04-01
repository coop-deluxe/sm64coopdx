#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_menu_options.h"
#include "djui_panel_language.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "game/hardcoded.h"

#ifdef DEVELOPMENT
void djui_panel_options_debug_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MISC, DEBUG_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        djui_checkbox_create(body, DLANG(MISC, FIXED_COLLISIONS), (bool*)&gLevelValues.fixCollisionBugs, NULL);
        djui_checkbox_create(body, DLANG(MISC, LUA_PROFILER), &configLuaProfiler, NULL);
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

    {
        djui_checkbox_create(body, DLANG(MISC, PAUSE_IN_SINGLEPLAYER), &configSingleplayerPause, NULL);
        djui_checkbox_create(body, DLANG(MISC, DISABLE_POPUPS), &configDisablePopups, NULL);
        djui_button_create(body, DLANG(MISC, LANGUAGE), DJUI_BUTTON_STYLE_NORMAL, djui_panel_language_create);
        djui_button_create(body, DLANG(MISC, MENU_OPTIONS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_main_menu_create);
#ifdef DEVELOPMENT
        djui_button_create(body, DLANG(MISC, DEBUG), DJUI_BUTTON_STYLE_NORMAL, djui_panel_options_debug_create);
#endif
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
