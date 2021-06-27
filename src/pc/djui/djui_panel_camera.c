#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

static void djui_panel_camera_back(struct DjuiBase* base) {
    djui_panel_back();
}

void djui_panel_camera_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 10 + 64 * 1 + 16 * 10;
    
    struct DjuiCheckbox* checkbox1 = NULL;

    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, 340.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&panel->base, 0, 0, 0, 240);
    djui_base_set_border_color(&panel->base, 0, 0, 0, 200);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    {
        struct DjuiText* header = djui_text_create(&panel->base, "\\#ff0800\\C\\#1be700\\A\\#00b3ff\\M\\#ffef00\\E\\#ff0800\\R\\#1be700\\A");
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
            checkbox1 = djui_checkbox_create(&body->base, "Free Camera", &configEnableCamera);
            djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox1->base, 1.0f, 32);

            struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "Analog Camera", &configCameraAnalog);
            djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox2->base, 1.0f, 32);

            struct DjuiCheckbox* checkbox3 = djui_checkbox_create(&body->base, "Mouse Look", &configCameraMouse);
            djui_base_set_size_type(&checkbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox3->base, 1.0f, 32);

            struct DjuiCheckbox* checkbox4 = djui_checkbox_create(&body->base, "Invert X", &configCameraInvertX);
            djui_base_set_size_type(&checkbox4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox4->base, 1.0f, 32);

            struct DjuiCheckbox* checkbox5 = djui_checkbox_create(&body->base, "Invert Y", &configCameraInvertY);
            djui_base_set_size_type(&checkbox5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox5->base, 1.0f, 32);

            struct DjuiSlider* slider1 = djui_slider_create(&body->base, "X Sensitivity", &configCameraXSens, 1, 100);
            djui_base_set_size_type(&slider1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&slider1->base, 1.0f, 32);

            struct DjuiSlider* slider2 = djui_slider_create(&body->base, "Y Sensitivity", &configCameraYSens, 1, 100);
            djui_base_set_size_type(&slider2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&slider2->base, 1.0f, 32);

            struct DjuiSlider* slider3 = djui_slider_create(&body->base, "Aggression", &configCameraAggr, 0, 100);
            djui_base_set_size_type(&slider3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&slider3->base, 1.0f, 32);

            struct DjuiSlider* slider4 = djui_slider_create(&body->base, "Pan Level", &configCameraPan, 0, 100);
            djui_base_set_size_type(&slider4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&slider4->base, 1.0f, 32);

            struct DjuiSlider* slider5 = djui_slider_create(&body->base, "Deceleration", &configCameraDegrade, 0, 100);
            djui_base_set_size_type(&slider5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&slider5->base, 1.0f, 32);

            struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
            djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button6->base, 1.0f, 64);
            djui_interactable_hook_click(&button6->base, djui_panel_camera_back);
        }
    }

    djui_panel_add(caller, &panel->base, &checkbox1->base);
}
