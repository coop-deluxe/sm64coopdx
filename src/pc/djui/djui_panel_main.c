#include "djui.h"
#include "src/pc/controller/controller_sdl.h"
#include "src/pc/pc_main.h"

bool gDjuiPanelMainCreated = false;

static void djui_panel_main_quit_yes(UNUSED struct DjuiBase* caller) {
    game_exit();
}

static void djui_panel_main_quit(struct DjuiBase* caller) {
    djui_panel_confirm_create(caller,
                              "\\#ff0800\\Q\\#1be700\\U\\#00b3ff\\I\\#ffef00\\T",
                              "Are you sure you want to quit?",
                              djui_panel_main_quit_yes);
}

void djui_panel_main_create(struct DjuiBase* caller) {
    f32 bodyHeight = 64 * 4 + 16 * 3;
    
    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\SM\\#1be700\\64\\#00b3ff\\EX\n\\#ffef00\\COOP");
    {
        struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
        {
            struct DjuiButton* button1 = djui_button_create(&body->base, "Host");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 1.0f, 64);
            djui_cursor_input_controlled_center(&button1->base);
            djui_interactable_hook_click(&button1->base, djui_panel_host_create);
            defaultBase = &button1->base;

            struct DjuiButton* button2 = djui_button_create(&body->base, "Join");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 1.0f, 64);
            djui_interactable_hook_click(&button2->base, djui_panel_join_create);

            struct DjuiButton* button3 = djui_button_create(&body->base, "Options");
            djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button3->base, 1.0f, 64);
            djui_interactable_hook_click(&button3->base, djui_panel_options_create);

            struct DjuiButton* button4 = djui_button_create(&body->base, "Quit");
            djui_base_set_size_type(&button4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button4->base, 1.0f, 64);
            djui_button_set_style(button4, 1);
            djui_interactable_hook_click(&button4->base, djui_panel_main_quit);
        }

        char* version = get_version_local();
        struct DjuiText* footer = djui_text_create(&panel->base, version);
        djui_base_set_size_type(&footer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&footer->base, 1.0f, 1.0f);
        djui_base_set_color(&footer->base, 50, 50, 50, 255);
        djui_text_set_alignment(footer, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
    gInteractableOverridePad = true;
    gDjuiPanelMainCreated = true;
}
