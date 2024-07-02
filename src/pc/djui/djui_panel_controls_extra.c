#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/configfile.h"

void djui_panel_controls_extra_create(struct DjuiBase* caller) {
    f32 bindBodyHeight = 28 * 12 + 1 * 10;

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CONTROLS, CONTROLS), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiFlowLayout* bindBody = djui_flow_layout_create(body);
        djui_base_set_size_type(&bindBody->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&bindBody->base, 1.0f, bindBodyHeight);
        djui_base_set_color(&bindBody->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(bindBody, 1);
        {
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, CHAT),       configKeyChat);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, PLAYERS),    configKeyPlayerList);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, D_UP),       configKeyDUp);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, D_DOWN),     configKeyDDown);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, D_LEFT),     configKeyDLeft);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, D_RIGHT),    configKeyDRight);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, X),          configKeyX);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, Y),          configKeyY);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, CONSOLE),    configKeyConsole);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, PREV),       configKeyPrevPage);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, NEXT),       configKeyNextPage);
            djui_bind_create(&bindBody->base, DLANG(CONTROLS, DISCONNECT), configKeyDisconnect);
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
