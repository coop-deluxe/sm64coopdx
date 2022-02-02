#include "djui.h"
#include "src/pc/configfile.h"

void djui_panel_controls_extra_create(struct DjuiBase* caller) {
    f32 bindBodyHeight = 28 * 6 + 1 * 5;
    f32 bodyHeight = bindBodyHeight + 16 + 64;

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
            djui_bind_create(&bindBody->base, "Chat",    configKeyChat);
            djui_bind_create(&bindBody->base, "Players", configKeyPlayerList);
            djui_bind_create(&bindBody->base, "D Up",    configKeyDUp);
            djui_bind_create(&bindBody->base, "D Down",  configKeyDDown);
            djui_bind_create(&bindBody->base, "D Left",  configKeyDLeft);
            djui_bind_create(&bindBody->base, "D Right", configKeyDRight);
        }

        struct DjuiButton* buttonBack = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&buttonBack->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&buttonBack->base, 1.0f, 64);
        djui_button_set_style(buttonBack, 1);
        djui_interactable_hook_click(&buttonBack->base, djui_panel_menu_back);
        defaultBase = &buttonBack->base;
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
