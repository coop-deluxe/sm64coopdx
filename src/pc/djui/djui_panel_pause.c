#include "djui.h"
#include "pc/cheats.h"
#include "src/pc/pc_main.h"

bool gDjuiPanelPauseCreated = false;

static void djui_panel_pause_resume(UNUSED struct DjuiBase* caller) {
    djui_panel_shutdown();
}

static void djui_panel_pause_quit_yes(UNUSED struct DjuiBase* caller) {
    game_exit();
}

static void djui_panel_pause_quit(struct DjuiBase* caller) {
    djui_panel_confirm_create(caller,
                              "\\#ff0800\\Q\\#1be700\\U\\#00b3ff\\I\\#ffef00\\T",
                              "Are you sure you want to quit?",
                              djui_panel_pause_quit_yes);
}

void djui_panel_pause_create(struct DjuiBase* caller) {
    if (gDjuiChatBoxFocus) { djui_chat_box_toggle(); }

    f32 bodyHeight = 64 * 3 + 16 * 2;
    if (Cheats.EnableCheats) { bodyHeight += 64 + 16; }

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\P\\#1be700\\A\\#00b3ff\\U\\#ffef00\\S\\#ff0800\\E");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        struct DjuiButton* button1 = djui_button_create(&body->base, "Options");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_interactable_hook_click(&button1->base, djui_panel_options_create);
        defaultBase = &button1->base;

        if (Cheats.EnableCheats) {
            struct DjuiButton* button1 = djui_button_create(&body->base, "Cheats");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 1.0f, 64);
            djui_interactable_hook_click(&button1->base, djui_panel_cheats_create);
        }

        struct DjuiButton* button2 = djui_button_create(&body->base, "Resume");
        djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button2->base, 1.0f, 64);
        djui_interactable_hook_click(&button2->base, djui_panel_pause_resume);

        struct DjuiButton* button3 = djui_button_create(&body->base, "Quit");
        djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button3->base, 1.0f, 64);
        djui_interactable_hook_click(&button3->base, djui_panel_pause_quit);
        djui_button_set_style(button3, 1);
    }
    
    djui_panel_add(caller, &panel->base, defaultBase);
    gInteractableOverridePad = true;
    gDjuiPanelPauseCreated = true;
}
