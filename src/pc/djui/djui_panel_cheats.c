#include "djui.h"
#include "pc/cheats.h"

void djui_panel_cheats_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("\\#ff0800\\C\\#1be700\\H\\#00b3ff\\E\\#ffef00\\A\\#ff0800\\T\\#1be700\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(&body->base, "Moon Jump", &gCheats.moonJump, NULL);
        djui_checkbox_create(&body->base, "God Mode", &gCheats.godMode, NULL);
        djui_checkbox_create(&body->base, "Infinite Lives", &gCheats.infiniteLives, NULL);
        djui_checkbox_create(&body->base, "Super Speed", &gCheats.superSpeed, NULL);
        djui_checkbox_create(&body->base, "Responsive Controls", &gCheats.responsiveControls, NULL);
        djui_checkbox_create(&body->base, "Rapid Fire (A)", &gCheats.rapidFireA, NULL);
        djui_checkbox_create(&body->base, "BLJ Anywhere", &gCheats.bljAnywhere, NULL);
        djui_checkbox_create(&body->base, "Always Triple Jump", &gCheats.alwaysTripleJump, NULL);

        djui_button_create(&body->base, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
