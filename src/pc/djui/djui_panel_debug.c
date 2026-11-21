#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "game/hardcoded.h"

void djui_panel_debug_create(struct DjuiBase *caller) {
    struct DjuiThreePanel *panel = djui_panel_menu_create(DLANG(MISC, DEBUG_TITLE), false);
    struct DjuiBase *body = djui_three_panel_get_body(panel);
    {
#ifdef DEVELOPMENT
        djui_checkbox_create(body, DLANG(MISC, FIXED_COLLISIONS), (bool *)&gLevelValues.fixCollisionBugs, NULL);
#endif
        djui_checkbox_create(body, DLANG(MISC, LUA_PROFILER), &configLuaProfiler, NULL);
        djui_checkbox_create(body, DLANG(MISC, CTX_PROFILER), &configCtxProfiler, NULL);

        djui_checkbox_create(body, DLANG(MISC, DEBUG_PRINT), &configDebugPrint, NULL);
        djui_checkbox_create(body, DLANG(MISC, DEBUG_INFO), &configDebugInfo, NULL);
        djui_checkbox_create(body, DLANG(MISC, DEBUG_WARNING), &configDebugWarning, NULL);
        djui_checkbox_create(body, DLANG(MISC, DEBUG_ERRORS), &configDebugError, NULL);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
