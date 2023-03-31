#include "djui.h"
#include "src/pc/utils/misc.h"

void djui_panel_confirm_create(struct DjuiBase* caller, char* title, char* message, void (*on_yes_click)(struct DjuiBase*)) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(title);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiText* text = djui_text_create(body, message);
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, 64);
        djui_base_set_color(&text->base, 200, 200, 200, 255);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

        struct DjuiRect* rect1 = djui_rect_container_create(body, 64);
        {
            djui_button_left_create(&rect1->base, "No", DJUI_BUTTON_STYLE_NORMAL, djui_panel_menu_back);
            djui_button_right_create(&rect1->base, "Yes", DJUI_BUTTON_STYLE_NORMAL, on_yes_click);
        }
    }

    djui_panel_add(caller, panel, NULL);
}
