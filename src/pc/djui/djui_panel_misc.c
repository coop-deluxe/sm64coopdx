#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "game/hardcoded.h"

#ifdef DEVELOPMENT
void djui_panel_options_debug_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("\\#ff0800\\D\\#1be700\\E\\#00b3ff\\B\\#ffef00\\U\\#ff0800\\G");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        djui_checkbox_create(&body->base, "Fixed Collisions", (bool*)&gLevelValues.fixCollisionBugs, NULL);
        djui_checkbox_create(&body->base, "Lua Profiler", &configLuaProfiler, NULL);
        djui_checkbox_create(&body->base, "Debug Print", &configDebugPrint, NULL);
        djui_checkbox_create(&body->base, "Debug Info", &configDebugInfo, NULL);
        djui_checkbox_create(&body->base, "Debug Errors", &configDebugError, NULL);

        djui_button_create(&body->base, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
#endif

void djui_panel_misc_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("\\#ff0800\\M\\#1be700\\I\\#00b3ff\\S\\#ffef00\\C");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        djui_checkbox_create(&body->base, "Pause In Singleplayer", &configSingleplayerPause, NULL);
        djui_checkbox_create(&body->base, "Disable Popups", &configDisablePopups, NULL);

        djui_button_create(&body->base, "Menu Options", DJUI_BUTTON_STYLE_NORMAL, djui_panel_main_menu_create);

#ifdef DEVELOPMENT
        djui_button_create(&body->base, "Debug", DJUI_BUTTON_STYLE_NORMAL, djui_panel_options_debug_create);
#endif

        djui_button_create(&body->base, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
