#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_player.h"
#include "djui_panel_camera.h"
#include "djui_panel_controls.h"
#include "djui_panel_display.h"
#include "djui_panel_sound.h"
#include "djui_panel_misc.h"
#include "djui_panel_menu.h"
#include "djui_panel_dynos.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/pc_main.h"

static void djui_panel_options_back(struct DjuiBase* caller) {
    configfile_save(configfile_name());
    djui_panel_menu_back(caller);
}

void djui_panel_options_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(OPTIONS, OPTIONS), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        if (gDjuiInMainMenu) {
            struct DjuiRect* rect1 = djui_rect_container_create(body, 64);
            {
                djui_button_left_create(&rect1->base, DLANG(PAUSE, PLAYER), DJUI_BUTTON_STYLE_NORMAL, djui_panel_player_create);
                djui_button_right_create(&rect1->base, DLANG(PAUSE, DYNOS_PACKS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_dynos_create);
            }
        }
        djui_button_create(body, DLANG(OPTIONS, CAMERA), DJUI_BUTTON_STYLE_NORMAL, djui_panel_camera_create);
        djui_button_create(body, DLANG(OPTIONS, CONTROLS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_controls_create);
        djui_button_create(body, DLANG(OPTIONS, DISPLAY), DJUI_BUTTON_STYLE_NORMAL, djui_panel_display_create);
        djui_button_create(body, DLANG(OPTIONS, SOUND), DJUI_BUTTON_STYLE_NORMAL, djui_panel_sound_create);
        djui_button_create(body, DLANG(OPTIONS, MISC), DJUI_BUTTON_STYLE_NORMAL, djui_panel_misc_create);
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_options_back);
    }

    djui_panel_add(caller, panel, NULL);
}
