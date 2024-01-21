#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/lua/utils/smlua_misc_utils.h"

static char sInfo[1024];

void djui_panel_info_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(INFORMATION, INFORMATION_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        snprintf(sInfo, 1024, "sm64coopdx is a project started by the Coop Deluxe team \
to actively maintain, improve on and provide a better \
community for sm64ex-coop. We are adding more features, \
customizability, and power to the Lua API without having to \
jump through the many hoops of issues sm64ex-coop \
development has, or deal with cool new features being \
turned down by overly cautious developers.\n\
\n\
Coop Deluxe Team:\n\
Agent X: Creator\n\
AngelicMiracles: Co-Creator\n\
eros71: Tester & Developer\n\
FluffaMario: Model Designer\n\
\n\
Contributors:\n\
mike_dobukai: Logo\n\
Pup64HCP: Website\n\
ArcticJaguar725: Fixing a sound engine bug\n\
Mr. Porkchop: New aliased font"
        );

        struct DjuiText* text = djui_text_create(body, sInfo);
        djui_base_set_location(&text->base, 0, 0);
        djui_base_set_size(&text->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 497);
        djui_base_set_color(&text->base, 220, 220, 220, 255);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
