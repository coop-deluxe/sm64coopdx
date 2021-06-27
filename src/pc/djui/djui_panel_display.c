#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

static void djui_panel_display_back(struct DjuiBase* base) {
    djui_panel_back();
}

static void djui_panel_display_apply(struct DjuiBase* caller) {
    configWindow.settings_changed = true;
}

void djui_panel_display_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 5 + 64 * 1 + 16 * 4;
    
    struct DjuiCheckbox* checkbox1 = NULL;

    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, 340.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&panel->base, 0, 0, 0, 240);
    djui_base_set_border_color(&panel->base, 0, 0, 0, 200);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    {
        struct DjuiText* header = djui_text_create(&panel->base, "\\#ff0800\\D\\#1be700\\I\\#00b3ff\\S\\#ffef00\\P\\#ff0800\\L\\#1be700\\A\\#00b3ff\\Y");
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
            checkbox1 = djui_checkbox_create(&body->base, "Fullscreen", &configWindow.fullscreen);
            djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox1->base, 1.0f, 32);
            djui_interactable_hook_value_change(&checkbox1->base, djui_panel_display_apply);

            struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "VSync", &configWindow.vsync);
            djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox2->base, 1.0f, 32);
            djui_interactable_hook_value_change(&checkbox2->base, djui_panel_display_apply);

            struct DjuiCheckbox* checkbox4 = djui_checkbox_create(&body->base, "HUD", &configHUD);
            djui_base_set_size_type(&checkbox4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox4->base, 1.0f, 32);

            char* choices[3] = { "Nearest", "Linear", "Tripoint" };
            struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Filtering", choices, 3, &configFiltering);
            djui_base_set_size_type(&selectionbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&selectionbox1->base, 1.0f, 32);

            struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
            djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button6->base, 1.0f, 64);
            djui_interactable_hook_click(&button6->base, djui_panel_display_back);
        }
    }

    djui_panel_add(caller, &panel->base, &checkbox1->base);
}
