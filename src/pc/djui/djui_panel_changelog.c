#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"

static char sChangelog[2][700];

void djui_panel_changelog_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHANGELOG, CHANGELOG_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 1);
        struct DjuiBase* layoutBase = &paginated->layout->base;

        snprintf(sChangelog[0], 700, "Welcome back! - \\#ffff00\\v0.1.4\\#dcdcdc\\:\n\
\\#ffff00\\Changes:\\#dcdcdc\\\n\
Disabled credits camera control easter egg if on the title screen (Agent X)\n\
Increased Mod Storage key/value length to 256 (Agent X)\n\
Added option to disable gamepads (Agent X)\n\
Made the changelog have pages (Agent X)\n\
\\#ffff00\\Fixes:\\#dcdcdc\\\n\
Fixed compilation error with DISCORD_SDK=0 (Agent X)\n\
Fixed potential Mod Storage crashes (Agent X)\n\
Fixed macOS Arm compilation (Agent X)\n\
Fixed broken unicode characters (Agent X)\n\
Fixed DynOS not allowing the '/' character in the HUD font to be edited (xLuigiGamerx)\n\
Fixed custom level reverb (Agent X)"
        );
        snprintf(sChangelog[1], 700, "\\#ffff00\\Lua API Changes:\\#dcdcdc\\\n\
Fixed Lua not allowing over exposure in marioBodyState light and shade values (Agent X)\n\
Fixed djui_hud_get_color() (Agent X)\n\
Added FONT_ALIASED, which uses Mr. Porkchop's improved smooth font atlas (Agent X, Mr. Porkchop)\n\
Added FONT_CUSTOM_HUD, a version of the HUD font containing all of the unicode characters (xLuigiGamerx)\n\
Added FONT_RECOLOR_HUD, a recolorable version of FONT_CUSTOM_HUD (xLuigiGamerx)\n\
Added HOOK_ON_PLAY_SOUND, a hook that is called whenever a sound is going to play (Agent X)\n\
\\#ffff00\\Mod Changes:\\#dcdcdc\\\n\
Removed Sex in Minecraft (Agent X)"
        );

        for (int i = 0; i < 2; i++) {
            struct DjuiText* text = djui_text_create(layoutBase, sChangelog[i]);
            djui_base_set_location(&text->base, 0, 0);
            djui_base_set_size(&text->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 450);
            djui_base_set_color(&text->base, 220, 220, 220, 255);
            djui_text_set_drop_shadow(text, 64, 64, 64, 100);
            djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
        }

        djui_paginated_calculate_height(paginated);

        djui_button_create(body, "OK", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}