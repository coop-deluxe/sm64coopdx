#include "djui.h"
#include "src/pc/utils/misc.h"

static void djui_panel_quit_yes(struct DjuiBase* base) {
    exit(0);
}

static void djui_panel_quit_no(struct DjuiBase* base) {
    djui_panel_back();
}

void djui_panel_quit_create(struct DjuiBase* caller) {
    f32 bodyHeight = 64 * 3 + 16 * 2;

    struct DjuiButton* buttonNo = NULL;

    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, 340.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&panel->base, 0, 0, 0, 230);
    djui_base_set_border_color(&panel->base, 0, 0, 0, 200);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    djui_base_set_enabled(&panel->base, false);
    {
        struct DjuiText* header = djui_text_create(&panel->base, "\\#ff0800\\Q\\#1be700\\U\\#00b3ff\\I\\#ffef00\\T");
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
            struct DjuiText* text = djui_text_create(&body->base, "Are you sure you want to quit?");
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&text->base, 1.0f, 64);
            djui_base_set_color(&text->base, 200, 200, 200, 255);
            djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

            struct DjuiButton* button1 = djui_button_create(&body->base, "Yes");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 1.0f, 64);
            button1->base.interactable->on_click = djui_panel_quit_yes;

            buttonNo = djui_button_create(&body->base, "No");
            djui_base_set_size_type(&buttonNo->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&buttonNo->base, 1.0f, 64);
            buttonNo->base.interactable->on_click = djui_panel_quit_no;
        }
    }

    djui_panel_add(caller, &panel->base, &buttonNo->base);
}
