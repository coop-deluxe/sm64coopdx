#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "game/hardcoded.h"

#ifdef DEVELOPMENT
void djui_panel_options_debug_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 3 + 64 * 1 + 16 * 1;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\D\\#1be700\\E\\#00b3ff\\B\\#ffef00\\U\\#ff0800\\G");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Fixed Collisions", (bool*)&gLevelValues.fixCollisionBugs);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);
        defaultBase = &checkbox1->base;

#ifdef LUA_PROFILER
        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "Lua Profiler", &configLuaProfiler);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);
        defaultBase = &checkbox2->base;
#endif

        struct DjuiButton* button1 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_button_set_style(button1, 1);
        djui_interactable_hook_click(&button1->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
#endif

void djui_panel_misc_create(struct DjuiBase* caller) {
#ifdef DEVELOPMENT
    f32 bodyHeight = 64 * 5 + 16 * 4;
#else
    f32 bodyHeight = 64 * 4 + 16 * 3;
#endif

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\M\\#1be700\\I\\#00b3ff\\S\\#ffef00\\C");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Pause In Singleplayer", &configSingleplayerPause);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);
        defaultBase = &checkbox1->base;

        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "Disable Popups", &configDisablePopups);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);

        struct DjuiButton* button1 = djui_button_create(&body->base, "Menu Options");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_interactable_hook_click(&button1->base, djui_panel_main_menu_create);

#ifdef DEVELOPMENT
        struct DjuiButton* button2 = djui_button_create(&body->base, "Debug");
        djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button2->base, 1.0f, 64);
        djui_interactable_hook_click(&button2->base, djui_panel_options_debug_create);
#endif

        struct DjuiButton* button3 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button3->base, 1.0f, 64);
        djui_button_set_style(button3, 1);
        djui_interactable_hook_click(&button3->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
