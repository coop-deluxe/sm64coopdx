#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/configfile.h"

void djui_panel_controls_n64_create(struct DjuiBase* caller) {
    f32 bindBodyHeight = 28 * 14 + 1 * 13;

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CONTROLS, CONTROLS), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiFlowLayout* bindBody = djui_flow_layout_create(body);
        djui_base_set_size_type(&bindBody->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&bindBody->base, 1.0f, bindBodyHeight);
        djui_base_set_color(&bindBody->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(bindBody, 1);
        {
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, UP),      configKeyStickUp);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, DOWN),    configKeyStickDown);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, LEFT),    configKeyStickLeft);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, RIGHT),   configKeyStickRight);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, A),       configKeyA);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, B),       configKeyB);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, START),   configKeyStart);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, L),       configKeyL);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, R),       configKeyR);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, Z),       configKeyZ);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, C_UP),    configKeyCUp);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, C_DOWN),  configKeyCDown);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, C_LEFT),  configKeyCLeft);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, C_RIGHT), configKeyCRight);
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
