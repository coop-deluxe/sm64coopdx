#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_join_lobbies.h"
#include "djui_panel_join_private.h"
#include "djui_panel_join_direct.h"
#include "djui_panel_main.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/discord/discord.h"

#ifdef COOPNET
static void djui_panel_compatibility_checkbox_on_value_change(UNUSED struct DjuiBase* caller) {
    gDiscordInitialized = false;
    if (gVersionText != NULL) {
        djui_text_set_text(gVersionText, get_version_local());
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
        if (gDjuiInMainMenu) {
            djui_checkbox_create(body, DLANG(MISC, COOP_COMPATIBILITY), &configCoopCompatibility, djui_panel_compatibility_checkbox_on_value_change);
        }
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
#endif
}
