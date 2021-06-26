#include "djui.h"
#include "src/pc/utils/misc.h"

static void djui_panel_options_back(struct DjuiBase* base) {
    djui_panel_back();
}

void djui_panel_options_create(struct DjuiBase* caller) {
    f32 bodyHeight = 64 * 6 + 16 * 5;

    struct DjuiButton* buttonPlayer = NULL;

    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, 340.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&panel->base, 0, 0, 0, 240);
    djui_base_set_border_color(&panel->base, 0, 0, 0, 200);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    {
        struct DjuiText* header = djui_text_create(&panel->base, "\\#ff0800\\O\\#1be700\\P\\#00b3ff\\T\\#ffef00\\I\\#ff0800\\O\\#1be700\\N\\#00b3ff\\S");
        djui_base_set_size_type(&header->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&header->base, 1.0f, 1.0f);
        djui_base_set_color(&header->base, 255, 8, 0, 255);
        djui_text_set_alignment(header, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_font(header, &gDjuiFonts[1]);
        djui_text_set_font_scale(header, gDjuiFonts[1].defaultFontScale);

        struct DjuiFlowLayout* body = djui_flow_layout_create(&panel->base);
        djui_base_set_alignment(&body->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&body->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&body->base, 1.0f, bodyHeight);
        djui_base_set_color(&body->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(body, 16);
        djui_flow_layout_set_flow_direction(body, DJUI_FLOW_DIR_DOWN);
        {
            buttonPlayer = djui_button_create(&body->base, "Player");
            djui_base_set_size_type(&buttonPlayer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&buttonPlayer->base, 1.0f, 64);

            struct DjuiButton* button2 = djui_button_create(&body->base, "Camera");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 1.0f, 64);
            button2->base.interactable->on_click = djui_panel_camera_create;

            struct DjuiButton* button3 = djui_button_create(&body->base, "Controls");
            djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button3->base, 1.0f, 64);

            struct DjuiButton* button4 = djui_button_create(&body->base, "Display");
            djui_base_set_size_type(&button4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button4->base, 1.0f, 64);
            button4->base.interactable->on_click = djui_panel_display_create;

            struct DjuiButton* button5 = djui_button_create(&body->base, "Sound");
            djui_base_set_size_type(&button5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button5->base, 1.0f, 64);
            button5->base.interactable->on_click = djui_panel_sound_create;

            struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
            djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button6->base, 1.0f, 64);
            button6->base.interactable->on_click = djui_panel_options_back;
        }
    }

    djui_panel_add(caller, &panel->base, &buttonPlayer->base);
}
