#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

static void djui_panel_controls_back(struct DjuiBase* base) {
    djui_panel_back();
}

void djui_panel_controls_create(struct DjuiBase* caller) {
    f32 bindBodyHeight = 32 * 11 + 1 * 10;
    f32 bodyHeight = bindBodyHeight + 16 * 3 + 32 * 2 + 64;

    struct DjuiBind* bind1 = NULL;

    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, 340.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&panel->base, 0, 0, 0, 240);
    djui_base_set_border_color(&panel->base, 0, 0, 0, 200);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    {
        struct DjuiText* header = djui_text_create(&panel->base, "\\#ff0800\\C\\#1be700\\O\\#00b3ff\\N\\#ffef00\\T\\#ff0800\\R\\#1be700\\O\\#00b3ff\\L\\#ffef00\\S");
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
        {
            struct DjuiFlowLayout* bindBody = djui_flow_layout_create(&body->base);
            djui_base_set_size_type(&bindBody->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&bindBody->base, 1.0f, bindBodyHeight);
            djui_base_set_color(&bindBody->base, 0, 0, 0, 0);
            djui_flow_layout_set_margin(bindBody, 1);
            {
                bind1                   = djui_bind_create(&bindBody->base, "A",       configKeyA);
                struct DjuiBind* bind2  = djui_bind_create(&bindBody->base, "B",       configKeyB);
                struct DjuiBind* bind3  = djui_bind_create(&bindBody->base, "Start",   configKeyStart);
                struct DjuiBind* bind4  = djui_bind_create(&bindBody->base, "L",       configKeyL);
                struct DjuiBind* bind5  = djui_bind_create(&bindBody->base, "R",       configKeyR);
                struct DjuiBind* bind6  = djui_bind_create(&bindBody->base, "Z",       configKeyZ);
                struct DjuiBind* bind7  = djui_bind_create(&bindBody->base, "C Up",    configKeyCUp);
                struct DjuiBind* bind8  = djui_bind_create(&bindBody->base, "C Down",  configKeyCDown);
                struct DjuiBind* bind9  = djui_bind_create(&bindBody->base, "C Left",  configKeyCLeft);
                struct DjuiBind* bind10 = djui_bind_create(&bindBody->base, "C Right", configKeyCRight);
                struct DjuiBind* bind11 = djui_bind_create(&bindBody->base, "Chat",    configKeyChat);
            }

            struct DjuiSlider* slider1 = djui_slider_create(&body->base, "Deadzone", &configStickDeadzone, 0, 100);
            djui_base_set_size_type(&slider1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&slider1->base, 1.0f, 32);

            struct DjuiSlider* slider2 = djui_slider_create(&body->base, "Rumble Strength", &configRumbleStrength, 0, 100);
            djui_base_set_size_type(&slider2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&slider2->base, 1.0f, 32);

            struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
            djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button6->base, 1.0f, 64);
            djui_interactable_hook_click(&button6->base, djui_panel_controls_back);
        }
    }

    djui_panel_add(caller, &panel->base, &bind1->base);
}
