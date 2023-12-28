#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_host.h"
#include "djui_panel_join.h"
#include "djui_panel_options.h"
#include "djui_panel_menu.h"
#include "djui_panel_confirm.h"
#include "src/pc/controller/controller_sdl.h"
#include "src/pc/pc_main.h"

extern ALIGNED8 u8 texture_coopdx_logo[];

struct DjuiText* gVersionText = NULL;

bool gDjuiPanelMainCreated = false;

static void djui_panel_main_quit_yes(UNUSED struct DjuiBase* caller) {
    game_exit();
}

static void djui_panel_main_quit(struct DjuiBase* caller) {
    djui_panel_confirm_create(caller,
                              DLANG(MAIN, QUIT_TITLE),
                              DLANG(MAIN, QUIT_CONFIRM),
                              djui_panel_main_quit_yes);
}

void djui_panel_main_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("");
    {
        struct DjuiBase* body = djui_three_panel_get_body(panel);
        {
            struct DjuiImage* logo = djui_image_create(body, texture_coopdx_logo, 2048, 1024, 32);
            djui_base_set_size(&logo->base, 370.0f, 185.0f);
            djui_base_set_alignment(&logo->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
            djui_base_set_location_type(&logo->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_location(&logo->base, 0, -50.0f);

            struct DjuiButton* button1 = djui_button_create(body, DLANG(MAIN, HOST), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_create);
            djui_base_set_location(&button1->base, 0, -30.0f);
            djui_cursor_input_controlled_center(&button1->base);

            struct DjuiButton* button2 = djui_button_create(body, DLANG(MAIN, JOIN), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_create);
            djui_base_set_location(&button2->base, 0, -30.0f);
            struct DjuiButton* button3 = djui_button_create(body, DLANG(MAIN, OPTIONS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_options_create);
            djui_base_set_location(&button3->base, 0, -30.0f);
            struct DjuiButton* button4 = djui_button_create(body, DLANG(MAIN, QUIT), DJUI_BUTTON_STYLE_BACK, djui_panel_main_quit);
            djui_base_set_location(&button4->base, 0, -30.0f);
        }

        gVersionText = djui_text_create(&panel->base, get_version_local());
        djui_base_set_size_type(&gVersionText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&gVersionText->base, 1.0f, 1.0f);
        djui_base_set_color(&gVersionText->base, 50, 50, 50, 255);
        djui_text_set_alignment(gVersionText, DJUI_HALIGN_RIGHT, DJUI_VALIGN_BOTTOM);
    }

    djui_panel_add(caller, panel, NULL);
    gInteractableOverridePad = true;
    gDjuiPanelMainCreated = true;
}
