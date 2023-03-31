#include "djui.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"

void djui_panel_options_back(struct DjuiBase* caller) {
    configfile_save(configfile_name());
    djui_panel_menu_back(caller);
}

void djui_panel_options_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("OPTIONS");
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_button_create(body, "Player", DJUI_BUTTON_STYLE_NORMAL, djui_panel_player_create);
        djui_button_create(body, "Camera", DJUI_BUTTON_STYLE_NORMAL, djui_panel_camera_create);
        djui_button_create(body, "Controls", DJUI_BUTTON_STYLE_NORMAL, djui_panel_controls_create);
        djui_button_create(body, "Display", DJUI_BUTTON_STYLE_NORMAL, djui_panel_display_create);
        djui_button_create(body, "Sound", DJUI_BUTTON_STYLE_NORMAL, djui_panel_sound_create);
        djui_button_create(body, "Misc", DJUI_BUTTON_STYLE_NORMAL, djui_panel_misc_create);
        djui_button_create(body, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_options_back);
    }

    djui_panel_add(caller, panel, NULL);
}
