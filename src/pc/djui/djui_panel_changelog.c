#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"

static char sChangelog[5][1024];

void djui_panel_changelog_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHANGELOG, CHANGELOG_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 1);
        struct DjuiBase* layoutBase = &paginated->layout->base;

        snprintf(sChangelog[0], 1024, "Welcome back! - \\#ffff00\\v0.2\\#dcdcdc\\:\n\
\n\
\\#ffff00\\Changes:\\#dcdcdc\\\n\
Added an update checker to notify people of new updates\n\
Made the version on the main menu always the sm64coopdx version\n\
Added over 40 missing gfx symbols to the DynOS parser\n\
Increased object pool capacity from 960 to 1200\n\
Made Mario & Luigi cap emblems use the shirt color\n\
Moved changelog to the info panel\n\
Added a properly implemented vanilla singleplayer pause\n\
Restored the vanilla pause menu red coin display if there are 8\n\
Restored vanilla camera zoom out with singleplayer\n\
Forced DynOS and player panels to be uncentered");
        snprintf(sChangelog[1], 1024, "Made the light & dark theme panel backgrounds slightly less opaque\n\
Disabled any vertex rounding when generating DynOS actors\n\
Added option to only apply DynOS playermodels onto the local player\n\
Made dirt particle vertex colorable\n\
Allowed players to bounce on mid air players' heads\n\
Made recovery hearts only heal the last person who touched it\n\
Partially rewrote launch parameter code\n\
Added --hide-loading-screen param\n\
Increased vertical tilt range and disabled tilt centering while sliding for free cam");
        snprintf(sChangelog[2], 1024, "\\#ffff00\\Fixes:\\#dcdcdc\\\n\
\n\
Fixed console not being openable from the main menu\n\
Fixed interpolated rectangles using the wrong resolution\n\
Fixed SDL2 linux compositor with X11\n\
Fixed memory leak with custom animations that caused strange glitches\n\
Fixed sm64coopdx exclusive features still working when hosting sm64ex-coop servers\n\
Fixed a bizzare bug with perfect frame pausing causing you to go to seemingly random warp nodes\n\
Fixed 1 player lobbies saying 'Waiting for players...'\n\
Fixed the --help launch parameter not outputting anything\n\
Fixed --server jank by basically rewriting how it works");
        snprintf(sChangelog[3], 1024, "Fixed the mouse disappearing forever on the window after closing the chat\n\
Fixed the bugs with transitions such as delays, not being able to pause, flashing, playing repeatedly\n\
Fixed inconsistent capitalization on the loading screen\n\
Fixed the cake screen cutting off and returning to the entry level too early\n\
Fixed hoot having invisible wings\n\
\n\
\\#ffff00\\Lua API Changes:\\#dcdcdc\\\n\
Added the ability to have global star IDs\n\
Added the ability to not show star collection dialogs\n\
Allowed FONT_HUD to have texture filtering\n\
Added the ability to change window title\n\
Added the ability to get the global timer\n\
Added get and set functions for the HUD star flash");
        snprintf(sChangelog[4], 1024, "Added HUD_DISPLAY_CAMERA_STATUS for hud_get_value()\n\
Exposed level_control_timer_running() to check if the timer is running\n\
Raised max BASS audio files from 128 to 256\n\
Added '-- pausable' field so mods can mark themselves as being able to function when the game is paused in singleplayer\n\
Added OBJ_LIST_EXT for Lua mods to use just in case\n\
\n\
\\#ffff00\\Mod Changes:\\#dcdcdc\\\n\
Updated Character Select to v1.7\n\
Updated Toadette's model in [CS] Extra Characters\n\
Updated Arena and added Blimp City, new music for levels and fixed KOTH, Rainbow Road collision and level lighting direction");

        for (int i = 0; i < 5; i++) {
            struct DjuiText* text = djui_text_create(layoutBase, sChangelog[i]);
            djui_base_set_location(&text->base, 0, 0);
            djui_base_set_size(&text->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 450);
            djui_base_set_color(&text->base, 220, 220, 220, 255);
            djui_text_set_drop_shadow(text, 64, 64, 64, 100);
            djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
        }

        djui_paginated_calculate_height(paginated);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}