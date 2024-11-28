#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_join_lobbies.h"
#include "djui_panel_join_private.h"
#include "djui_panel_join_direct.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/update_checker.h"

#ifdef COOPNET
static void djui_panel_join_public_lobbies(struct DjuiBase* caller) {
    djui_panel_join_lobbies_create(caller, "");
}
#endif

void djui_panel_join_create(struct DjuiBase* caller) {
#ifndef COOPNET
    djui_panel_join_direct_create(caller);
#else
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(JOIN, JOIN_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_button_create(body, DLANG(JOIN, PUBLIC_LOBBIES), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_public_lobbies);
        djui_button_create(body, DLANG(JOIN, PRIVATE_LOBBIES), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_private_create);
        djui_button_create(body, DLANG(JOIN, DIRECT), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_direct_create);
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    if (gUpdateMessage) {
        struct DjuiText* message = djui_text_create(&panel->base, DLANG(NOTIF, UPDATE_AVAILABLE));
        djui_base_set_size_type(&message->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&message->base, 1.0f, 1.0f);
        djui_base_set_color(&message->base, 255, 255, 160, 255);
        djui_text_set_alignment(message, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
    }

    djui_panel_add(caller, panel, NULL);
#endif
}
