#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/pc/controller/controller_api.h"

void djui_panel_controls_value_change(UNUSED struct DjuiBase* caller) {
    controller_reconfigure();
}

void djui_panel_controls_create(struct DjuiBase* caller) {
    f32 bindBodyHeight = 32 * 11 + 1 * 10;
    f32 bodyHeight = bindBodyHeight + 16 * 3 + 32 * 2 + 64;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\C\\#1be700\\O\\#00b3ff\\N\\#ffef00\\T\\#ff0800\\R\\#1be700\\O\\#00b3ff\\L\\#ffef00\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        struct DjuiFlowLayout* bindBody = djui_flow_layout_create(&body->base);
        djui_base_set_size_type(&bindBody->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&bindBody->base, 1.0f, bindBodyHeight);
        djui_base_set_color(&bindBody->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(bindBody, 1);
        {
            struct DjuiBind* bind1  = djui_bind_create(&bindBody->base, "A", configKeyA);
            djui_bind_create(&bindBody->base, "B",       configKeyB);
            djui_bind_create(&bindBody->base, "Start",   configKeyStart);
            djui_bind_create(&bindBody->base, "L",       configKeyL);
            djui_bind_create(&bindBody->base, "R",       configKeyR);
            djui_bind_create(&bindBody->base, "Z",       configKeyZ);
            djui_bind_create(&bindBody->base, "C Up",    configKeyCUp);
            djui_bind_create(&bindBody->base, "C Down",  configKeyCDown);
            djui_bind_create(&bindBody->base, "C Left",  configKeyCLeft);
            djui_bind_create(&bindBody->base, "C Right", configKeyCRight);
            djui_bind_create(&bindBody->base, "Chat",    configKeyChat);
            defaultBase = &bind1->buttons[0]->base;
        }

        struct DjuiSlider* slider1 = djui_slider_create(&body->base, "Deadzone", &configStickDeadzone, 0, 100);
        djui_base_set_size_type(&slider1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&slider1->base, 1.0f, 32);
        djui_interactable_hook_value_change(&slider1->base, djui_panel_controls_value_change);

        struct DjuiSlider* slider2 = djui_slider_create(&body->base, "Rumble Strength", &configRumbleStrength, 0, 100);
        djui_base_set_size_type(&slider2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&slider2->base, 1.0f, 32);
        djui_interactable_hook_value_change(&slider2->base, djui_panel_controls_value_change);

        struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_button_set_style(button6, 1);
        djui_interactable_hook_click(&button6->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
