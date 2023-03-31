#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

void djui_panel_sound_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("SOUND");
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        djui_slider_create(body, "Master Volume", &configMasterVolume, 0, 127, NULL);
        djui_slider_create(body, "Music Volume", &configMusicVolume, 0, 127, NULL);
        djui_slider_create(body, "Sfx Volume", &configSfxVolume, 0, 127, NULL);
        djui_slider_create(body, "Env Volume", &configEnvVolume, 0, 127, NULL);
        djui_button_create(body, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
