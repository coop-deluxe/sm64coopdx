#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

void djui_panel_menu_back(UNUSED struct DjuiBase* base) {
    djui_panel_back();
}

struct DjuiThreePanel* djui_panel_menu_create(char* headerText) {
    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, 0, 0);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, DJUI_DEFAULT_PANEL_WIDTH, 1.0f);
    djui_base_set_color(&panel->base, 0, 0, 0, 240);
    djui_base_set_border_color(&panel->base, 0, 0, 0, 200);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    {
        struct DjuiText* header = djui_text_create(&panel->base, headerText);
        djui_base_set_size_type(&header->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&header->base, 1.0f, 1.0f);
        djui_base_set_color(&header->base, 255, 8, 0, 255);
        djui_base_set_location(&header->base, 0, DJUI_PANEL_HEADER_OFFSET);
        djui_text_set_alignment(header, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
        djui_text_set_font(header, gDjuiFonts[1]);
        djui_text_set_font_scale(header, gDjuiFonts[1]->defaultFontScale);

        struct DjuiFlowLayout* body = djui_flow_layout_create(&panel->base);
        djui_base_set_alignment(&body->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&body->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&body->base, 1.0f, 0);
        djui_base_set_color(&body->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(body, 16);
        djui_flow_layout_set_flow_direction(body, DJUI_FLOW_DIR_DOWN);
    }
    return panel;
}
