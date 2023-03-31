#include "djui.h"
#include "src/pc/configfile.h"

void djui_panel_controls_extra_create(struct DjuiBase* caller) {
    f32 bindBodyHeight = 28 * 8 + 1 * 7;

    struct DjuiThreePanel* panel = djui_panel_menu_create("CONTROLS");
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiFlowLayout* bindBody = djui_flow_layout_create(body);
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
            djui_bind_create(&bindBody->base, "X",       configKeyX);
            djui_bind_create(&bindBody->base, "Y",       configKeyY);
        }

        djui_button_create(body, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
