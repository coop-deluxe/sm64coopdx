#include "djui.h"
#include "pc/cheats.h"

void djui_panel_cheats_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 8 + 64 * 1 + 16 * 9;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\C\\#1be700\\H\\#00b3ff\\E\\#ffef00\\A\\#ff0800\\T\\#1be700\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, "Moon Jump", &gCheats.moonJump);
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
            defaultBase = &checkbox->base;
        }
        {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, "God Mode", &gCheats.godMode);
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
        }
        {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, "Infinite Lives", &gCheats.infiniteLives);
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
        }
        {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, "Super Speed", &gCheats.superSpeed);
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
        }
        {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, "Responsive Controls", &gCheats.responsiveControls);
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
        }
        {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, "Rapid Fire (A)", &gCheats.rapidFireA);
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
        }
        {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, "BLJ Anywhere", &gCheats.bljAnywhere);
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
        }
        {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, "Always Triple Jump", &gCheats.alwaysTripleJump);
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
        }

        struct DjuiButton* button1 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_button_set_style(button1, 1);
        djui_interactable_hook_click(&button1->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
