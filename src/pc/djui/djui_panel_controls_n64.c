#include "djui.h"
#include "src/pc/configfile.h"

void djui_panel_controls_n64_create(struct DjuiBase* caller) {
    f32 bindBodyHeight = 28 * 14 + 1 * 13;
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
            djui_bind_create(&bindBody->base, "Up",          configKeyStickUp);
            djui_bind_create(&bindBody->base, "Down",        configKeyStickDown);
            djui_bind_create(&bindBody->base, "Left",        configKeyStickLeft);
            djui_bind_create(&bindBody->base, "Right",       configKeyStickRight);
            djui_bind_create(&bindBody->base, "A",           configKeyA);
            djui_bind_create(&bindBody->base, "B",           configKeyB);
            djui_bind_create(&bindBody->base, "Start",       configKeyStart);
            djui_bind_create(&bindBody->base, "L",           configKeyL);
            djui_bind_create(&bindBody->base, "R",           configKeyR);
            djui_bind_create(&bindBody->base, "Z",           configKeyZ);
            djui_bind_create(&bindBody->base, "C Up",        configKeyCUp);
            djui_bind_create(&bindBody->base, "C Down",      configKeyCDown);
            djui_bind_create(&bindBody->base, "C Left",      configKeyCLeft);
            djui_bind_create(&bindBody->base, "C Right",     configKeyCRight);
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
