#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_join_lobbies.h"
#include "djui_panel_join_private.h"
#include "djui_panel_join_direct.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/pc_main.h"

#ifdef COOPNET
static struct DjuiText* sRestartText = NULL;

static void djui_panel_compatibility_checkbox_on_value_change(UNUSED struct DjuiBase* caller) {
    if (gCoopCompatibility != configCoopCompatibility) {
        djui_text_set_text(sRestartText, DLANG(DISPLAY, MUST_RESTART));
    } else {
        djui_text_set_text(sRestartText, "");
    }
}

static void djui_panel_join_public_lobbies(struct DjuiBase* caller) {
    djui_panel_join_lobbies_create(caller, "");
}
#endif

void djui_panel_join_create(struct DjuiBase* caller) {
#ifndef COOPNET
    djui_panel_join_direct_create(caller);
#else
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(JOIN, JOIN_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_button_create(body, DLANG(JOIN, PUBLIC_LOBBIES), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_public_lobbies);
        djui_button_create(body, DLANG(JOIN, PRIVATE_LOBBIES), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_private_create);
        djui_button_create(body, DLANG(JOIN, DIRECT), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_direct_create);
        djui_checkbox_create(body, DLANG(MISC, COOP_COMPATIBILITY), &configCoopCompatibility, djui_panel_compatibility_checkbox_on_value_change);
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        sRestartText = djui_text_create(body, "");
        djui_text_set_alignment(sRestartText, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_color(&sRestartText->base, 255, 100, 100, 255);
        djui_base_set_size_type(&sRestartText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sRestartText->base, 1.0f, 64);
    }

    djui_panel_add(caller, panel, NULL);
#endif
}
