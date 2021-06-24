#include "djui.h"

struct DjuiThreePanel* gPanelMainMenu = NULL;

void djui_panel_main_create(void) {
    f32 bodyHeight = 64 * 4 + 16 * 3;

    gPanelMainMenu = djui_three_panel_create(&gDjuiRoot->base, 128, bodyHeight, 32);
    djui_base_set_size_type(&gPanelMainMenu->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&gPanelMainMenu->base, 340.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&gPanelMainMenu->base, 0, 0, 0, 240);
    djui_base_set_border_color(&gPanelMainMenu->base, 0, 0, 0, 200);
    djui_base_set_border_width(&gPanelMainMenu->base, 8);
    djui_base_set_padding(&gPanelMainMenu->base, 16, 16, 16, 16);
    {
        struct DjuiText* header = djui_text_create(&gPanelMainMenu->base, "\\#ff0800\\SM\\#1be700\\64\\#00b3ff\\EX\n\\#ffef00\\COOP");
        djui_base_set_color(&header->base, 255, 8, 0, 255);
        djui_text_set_font(header, &gDjuiFonts[1]);
        djui_text_set_font_scale(header, gDjuiFonts[1].defaultFontScale);
        djui_text_set_alignment(header, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

        struct DjuiFlowLayout* body = djui_flow_layout_create(&gPanelMainMenu->base);
        djui_base_set_size_type(&body->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&body->base, 1.0f, bodyHeight);
        djui_base_set_color(&body->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(body, 16);
        djui_flow_layout_set_flow_direction(body, DJUI_FLOW_DIR_DOWN);
        {
            struct DjuiButton* button1 = djui_button_create(&body->base, "Host");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 1.0f, 64);
            djui_cursor_input_controlled_center(&button1->base);

            struct DjuiButton* button2 = djui_button_create(&body->base, "Join");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 1.0f, 64);

            struct DjuiButton* button3 = djui_button_create(&body->base, "Options");
            djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button3->base, 1.0f, 64);
            button3->base.interactable->on_click = djui_panel_options_open;

            struct DjuiButton* button4 = djui_button_create(&body->base, "Quit");
            djui_base_set_size_type(&button4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button4->base, 1.0f, 64);
            button4->base.interactable->on_click = djui_panel_quit_open;
        }

        struct DjuiText* footer = djui_text_create(&gPanelMainMenu->base, "version - unst 5");
        djui_base_set_alignment(&footer->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
        djui_base_set_size_type(&footer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&footer->base, 1.0f, 1.0f);
        djui_base_set_color(&footer->base, 50, 50, 50, 255);
        djui_text_set_alignment(footer, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    }
}
