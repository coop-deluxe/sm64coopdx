#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"

static char sChangelog[1024];

void djui_panel_changelog_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHANGELOG, CHANGELOG_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        snprintf(sChangelog, 1024, "Welcome back!\n\
v0.1.2:\n\
Changes:\n\
Disable sm64ex-coop Compatibility by default\n\
Restored Luigi's original color palette\n\
Made mario step code use his hitbox height instead of a constant number for his height\n\
Hid Mario's shadow in First Person\n\
Cancelled First Person if Mario is flying\n\
\n\
Fixes:\n\
Reverted dialog cutscene changes to prevent softlocks\n\
Fixed DynOS related crashes\n\
Fixed Mario's shadow not resetting\n\
\n\
Mods:\n\
Updated Gun Mod DX and Character Select\n\
Updated SiM description\n\
Removed Flood and Cheats due to future plans with them"
        );

        struct DjuiText* text = djui_text_create(body, sChangelog);
        djui_base_set_location(&text->base, 0, 0);
        djui_base_set_size(&text->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 497);
        djui_base_set_color(&text->base, 220, 220, 220, 255);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

        djui_button_create(body, "OK", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}