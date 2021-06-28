#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

void djui_panel_host_create(struct DjuiBase* caller) {
#ifdef DISCORD_SDK
    f32 bodyHeight = 32 * 4 + 64 * 2 + 16 * 6;
#else
    f32 bodyHeight = 32 * 3 + 64 * 2 + 16 * 5;
#endif

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\H\\#1be700\\O\\#00b3ff\\S\\#ffef00\\T");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
#ifdef DISCORD_SDK
        char* nChoices[2] = { "Discord", "Direct Connection" };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Network system", nChoices, 2, &configNetworkSystem);
        djui_base_set_size_type(&selectionbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox1->base, 1.0f, 32);
#endif
        char* iChoices[3] = { "Non-solid", "Solid", "Friendly Fire" };
        struct DjuiSelectionbox* selectionbox2 = djui_selectionbox_create(&body->base, "Player interaction", iChoices, 3, &configFiltering);
        djui_base_set_size_type(&selectionbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox2->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Stay in level after star", &configStayInLevelAfterStar);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "Play intro cutscene", &configSkipIntro);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox3 = djui_checkbox_create(&body->base, "Share lives", &configShareLives);
        djui_base_set_size_type(&checkbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox3->base, 1.0f, 32);

        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 64);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);
        {
            struct DjuiButton* button1 = djui_button_create(&rect1->base, "Back");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_interactable_hook_click(&button1->base, djui_panel_menu_back);

            struct DjuiButton* button2 = djui_button_create(&rect1->base, "Host");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_interactable_hook_click(&button2->base, djui_panel_host_message_create);
            defaultBase = &button2->base;
        }
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
