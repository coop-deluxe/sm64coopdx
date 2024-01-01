#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"

static char sChangelog[1200];

void djui_panel_changelog_back(UNUSED struct DjuiBase* caller) {
    strncpy(configLastVersion, SM64COOPDX_VERSION, MAX_CONFIG_STRING);
    djui_panel_back();
}

void djui_panel_changelog_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHANGELOG, CHANGELOG_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        snprintf(sChangelog, 1200, "Welcome back! - v0.1.3:\n\
Changes:\n\
Made Lua error logging more readable\n\
Made GitHub README clearer\n\
Made capitalization of some menu strings consistent in English.ini\n\
Removed the need to restart to change sm64ex-coop compatibility\n\
Improved Discord rich presence by adding images\n\
Re-added credits camera movement easter egg but with the player 1 controller this time\n\
Made default network player ping 50 again from 600\n\
Made player text color base off of CAP color instead of SHIRT color\n\
Fixes:\n\
Fixed incompatibility tags only registering the first one\n\
Fixed linker errors with macOS\n\
Fixed corrupted mod levels showing up on the main menu\n\
Fixed crash with disconnect key on star select screen\n\
Fixed singleplayer not forcing direct connection\n\
Fixed water camera and TTM star cutscene in first person\n\
Fixed random crashes with built-in mods\n\
Lua API Changes:\n\
Allowed over exposure (>255) in marioBodyState light and shade values\n\
Undefined SM64COOPDX_VERSION if sm64ex-coop compatibility is on\n\
Added get_coop_compatibility_enabled()\n\
Added gControllers\n\
Mod Changes:\n\
Fixed custom music bug and updated rainbow level with Arena\n\
Updated mQuake\n\
Re-added Hide and Seek\n\
Updated Day Night Cycle DX and Gun Mod DX"
        );

        struct DjuiText* text = djui_text_create(body, sChangelog);
        djui_base_set_location(&text->base, 0, 0);
        djui_base_set_size(&text->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 760);
        djui_base_set_color(&text->base, 220, 220, 220, 255);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

        djui_button_create(body, "OK", DJUI_BUTTON_STYLE_BACK, djui_panel_changelog_back);
    }

    djui_panel_add(caller, panel, NULL);
}