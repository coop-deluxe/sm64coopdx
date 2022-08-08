#include "djui.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"

void djui_panel_options_back(struct DjuiBase* caller) {
    configfile_save(configfile_name());
    djui_panel_menu_back(caller);
}

void djui_panel_options_create(struct DjuiBase* caller) {
    f32 bodyHeight = 64 * 7 + 16 * 6;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\O\\#1be700\\P\\#00b3ff\\T\\#ffef00\\I\\#ff0800\\O\\#1be700\\N\\#00b3ff\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        struct DjuiButton* button1 = djui_button_create(&body->base, "Player");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_interactable_hook_click(&button1->base, djui_panel_player_create);
        defaultBase = &button1->base;

        struct DjuiButton* button2 = djui_button_create(&body->base, "Camera");
        djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button2->base, 1.0f, 64);
        djui_interactable_hook_click(&button2->base, djui_panel_camera_create);
        if (defaultBase == NULL) {
            defaultBase = &button2->base;
        }

        struct DjuiButton* button3 = djui_button_create(&body->base, "Controls");
        djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button3->base, 1.0f, 64);
        djui_interactable_hook_click(&button3->base, djui_panel_controls_create);

        struct DjuiButton* button4 = djui_button_create(&body->base, "Display");
        djui_base_set_size_type(&button4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button4->base, 1.0f, 64);
        djui_interactable_hook_click(&button4->base, djui_panel_display_create);

        struct DjuiButton* button5 = djui_button_create(&body->base, "Sound");
        djui_base_set_size_type(&button5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button5->base, 1.0f, 64);
        djui_interactable_hook_click(&button5->base, djui_panel_sound_create);

        struct DjuiButton* button6 = djui_button_create(&body->base, "Misc");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_interactable_hook_click(&button6->base, djui_panel_misc_create);

        struct DjuiButton* button7 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button7->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button7->base, 1.0f, 64);
        djui_button_set_style(button7, 1);
        djui_interactable_hook_click(&button7->base, djui_panel_options_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
