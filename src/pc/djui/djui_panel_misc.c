#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_menu_options.h"
#include "djui_panel_options.h"
#include "djui_panel_language.h"
#include "djui_panel_info.h"
#include "djui_panel_debug.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#if defined(_WIN32)
#include <windows.h>
#endif

static void djui_panel_options_open_user_folder(UNUSED struct DjuiBase* caller) {
    open_folder(fs_get_write_path(""));
}

void djui_panel_misc_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MISC, MISC_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, DLANG(DISPLAY, SHOW_PING), &configShowPing, NULL);
        djui_checkbox_create(body, DLANG(MISC, DISABLE_POPUPS), &configDisablePopups, NULL);
        djui_checkbox_create(body, DLANG(MISC, LUA_PROFILER), &configLuaProfiler, NULL);

        djui_button_create(body, DLANG(MISC, LANGUAGE), DJUI_BUTTON_STYLE_NORMAL, djui_panel_language_create);
        djui_button_create(body, DLANG(MISC, MENU_OPTIONS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_main_menu_create);
        djui_button_create(body, DLANG(MISC, INFORMATION), DJUI_BUTTON_STYLE_NORMAL, djui_panel_info_create);
        djui_button_create(body, DLANG(MISC, DEBUG), DJUI_BUTTON_STYLE_NORMAL, djui_panel_debug_create);

#ifndef HANDHELD
#if defined(_WIN32)
        djui_button_create(body, DLANG(OPTIONS, APPDATA), DJUI_BUTTON_STYLE_NORMAL, djui_panel_options_open_user_folder);
#elif __linux__ || __APPLE__ || __MACH__
        djui_button_create(body, DLANG(OPTIONS, USER_FOLDER), DJUI_BUTTON_STYLE_NORMAL, djui_panel_options_open_user_folder);
#endif
#endif
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
