#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "game/hardcoded.h"

#ifdef DEVELOPMENT
void djui_panel_options_debug_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("DEBUG");
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        djui_checkbox_create(body, "Fixed Collisions", (bool*)&gLevelValues.fixCollisionBugs, NULL);
        djui_checkbox_create(body, "Lua Profiler", &configLuaProfiler, NULL);
        djui_checkbox_create(body, "Debug Print", &configDebugPrint, NULL);
        djui_checkbox_create(body, "Debug Info", &configDebugInfo, NULL);
        djui_checkbox_create(body, "Debug Errors", &configDebugError, NULL);

        djui_button_create(body, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
#endif

void djui_panel_misc_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("MISC");
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        djui_checkbox_create(body, "Pause In Singleplayer", &configSingleplayerPause, NULL);
        djui_checkbox_create(body, "Disable Popups", &configDisablePopups, NULL);

        djui_button_create(body, "Menu Options", DJUI_BUTTON_STYLE_NORMAL, djui_panel_main_menu_create);

#ifdef DEVELOPMENT
        djui_button_create(body, "Debug", DJUI_BUTTON_STYLE_NORMAL, djui_panel_options_debug_create);
#endif

        djui_button_create(body, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
