#include "djui.h"
#include "pc/cheats.h"

void djui_panel_cheats_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("CHEATS");
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, "Moon Jump", &gCheats.moonJump, NULL);
        djui_checkbox_create(body, "God Mode", &gCheats.godMode, NULL);
        djui_checkbox_create(body, "Infinite Lives", &gCheats.infiniteLives, NULL);
        djui_checkbox_create(body, "Super Speed", &gCheats.superSpeed, NULL);
        djui_checkbox_create(body, "Responsive Controls", &gCheats.responsiveControls, NULL);
        djui_checkbox_create(body, "Rapid Fire (A)", &gCheats.rapidFireA, NULL);
        djui_checkbox_create(body, "BLJ Anywhere", &gCheats.bljAnywhere, NULL);
        djui_checkbox_create(body, "Always Triple Jump", &gCheats.alwaysTripleJump, NULL);

        djui_button_create(body, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
