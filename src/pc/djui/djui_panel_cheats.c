#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/cheats.h"

void djui_panel_cheats_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHEATS, CHEATS));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, DLANG(CHEATS, MOON_JUMP), &gCheats.moonJump, NULL);
        djui_checkbox_create(body, DLANG(CHEATS, GOD_MODE), &gCheats.godMode, NULL);
        djui_checkbox_create(body, DLANG(CHEATS, INFINITE_LIVES), &gCheats.infiniteLives, NULL);
        djui_checkbox_create(body, DLANG(CHEATS, SUPER_SPEED), &gCheats.superSpeed, NULL);
        djui_checkbox_create(body, DLANG(CHEATS, RESPONSIVE_CONTROLS), &gCheats.responsiveControls, NULL);
        djui_checkbox_create(body, DLANG(CHEATS, RAPID_FIRE), &gCheats.rapidFireA, NULL);
        djui_checkbox_create(body, DLANG(CHEATS, BLJ_ANYWHERE), &gCheats.bljAnywhere, NULL);
        djui_checkbox_create(body, DLANG(CHEATS, ALWAYS_TRIPLE_JUMP), &gCheats.alwaysTripleJump, NULL);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
