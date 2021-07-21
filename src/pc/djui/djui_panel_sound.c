#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

void djui_panel_sound_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 4 + 64 * 1 + 16 * 4;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\S\\#1be700\\O\\#00b3ff\\U\\#ffef00\\N\\#ff0800\\D");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        struct DjuiSlider* slider1 = djui_slider_create(&body->base, "Master Volume", &configMasterVolume, 0, 127);
        djui_base_set_size_type(&slider1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&slider1->base, 1.0f, 32);
        defaultBase = &slider1->base;

        struct DjuiSlider* slider2 = djui_slider_create(&body->base, "Music Volume", &configMusicVolume, 0, 127);
        djui_base_set_size_type(&slider2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&slider2->base, 1.0f, 32);

        struct DjuiSlider* slider3 = djui_slider_create(&body->base, "Sfx Volume", &configSfxVolume, 0, 127);
        djui_base_set_size_type(&slider3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&slider3->base, 1.0f, 32);

        struct DjuiSlider* slider4 = djui_slider_create(&body->base, "Env Volume", &configEnvVolume, 0, 127);
        djui_base_set_size_type(&slider4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&slider4->base, 1.0f, 32);

        struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_button_set_style(button6, 1);
        djui_interactable_hook_click(&button6->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
