#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

void djui_panel_sound_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("\\#ff0800\\S\\#1be700\\O\\#00b3ff\\U\\#ffef00\\N\\#ff0800\\D");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        djui_slider_create(&body->base, "Master Volume", &configMasterVolume, 0, 127, NULL);
        djui_slider_create(&body->base, "Music Volume", &configMusicVolume, 0, 127, NULL);
        djui_slider_create(&body->base, "Sfx Volume", &configSfxVolume, 0, 127, NULL);
        djui_slider_create(&body->base, "Env Volume", &configEnvVolume, 0, 127, NULL);
        djui_button_create(&body->base, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
