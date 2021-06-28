#include "djui.h"
#include "src/pc/utils/misc.h"

static void djui_panel_quit_yes(struct DjuiBase* base) {
    exit(0);
}

static void djui_panel_quit_no(struct DjuiBase* base) {
    djui_panel_back();
}

void djui_panel_quit_create(struct DjuiBase* caller) {
    f32 bodyHeight = 64 * 2 + 16 * 1;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\Q\\#1be700\\U\\#00b3ff\\I\\#ffef00\\T");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        struct DjuiText* text = djui_text_create(&body->base, "Are you sure you want to quit?");
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, 64);
        djui_base_set_color(&text->base, 200, 200, 200, 255);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 64);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);
        {
            struct DjuiButton* button1 = djui_button_create(&rect1->base, "No");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_interactable_hook_click(&button1->base, djui_panel_quit_no);
            defaultBase = &button1->base;

            struct DjuiButton* button2 = djui_button_create(&rect1->base, "Yes");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_interactable_hook_click(&button2->base, djui_panel_quit_yes);
        }
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
