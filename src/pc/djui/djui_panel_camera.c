#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/game/bettercamera.h"

void djui_panel_camera_value_changed(UNUSED struct DjuiBase* caller) {
    newcam_init_settings();
}

void djui_panel_camera_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 10 + 64 * 1 + 16 * 10;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\C\\#1be700\\A\\#00b3ff\\M\\#ffef00\\E\\#ff0800\\R\\#1be700\\A");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Free Camera", &configEnableCamera);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);
        djui_interactable_hook_value_change(&checkbox1->base, djui_panel_camera_value_changed);
        defaultBase = &checkbox1->base;

        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "Analog Camera", &configCameraAnalog);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&checkbox2->base, djui_panel_camera_value_changed);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);

#ifdef BETTERCAMERA
        struct DjuiCheckbox* checkbox3 = djui_checkbox_create(&body->base, "Mouse Look", &configCameraMouse);
        djui_base_set_size_type(&checkbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&checkbox3->base, djui_panel_camera_value_changed);
        djui_base_set_size(&checkbox3->base, 1.0f, 32);
#endif

        struct DjuiCheckbox* checkbox4 = djui_checkbox_create(&body->base, "Invert X", &configCameraInvertX);
        djui_base_set_size_type(&checkbox4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&checkbox4->base, djui_panel_camera_value_changed);
        djui_base_set_size(&checkbox4->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox5 = djui_checkbox_create(&body->base, "Invert Y", &configCameraInvertY);
        djui_base_set_size_type(&checkbox5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&checkbox5->base, djui_panel_camera_value_changed);
        djui_base_set_size(&checkbox5->base, 1.0f, 32);

        struct DjuiSlider* slider1 = djui_slider_create(&body->base, "X Sensitivity", &configCameraXSens, 1, 100);
        djui_base_set_size_type(&slider1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&slider1->base, djui_panel_camera_value_changed);
        djui_base_set_size(&slider1->base, 1.0f, 32);

        struct DjuiSlider* slider2 = djui_slider_create(&body->base, "Y Sensitivity", &configCameraYSens, 1, 100);
        djui_base_set_size_type(&slider2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&slider2->base, djui_panel_camera_value_changed);
        djui_base_set_size(&slider2->base, 1.0f, 32);

        struct DjuiSlider* slider3 = djui_slider_create(&body->base, "Aggression", &configCameraAggr, 0, 100);
        djui_base_set_size_type(&slider3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&slider3->base, djui_panel_camera_value_changed);
        djui_base_set_size(&slider3->base, 1.0f, 32);

        struct DjuiSlider* slider4 = djui_slider_create(&body->base, "Pan Level", &configCameraPan, 0, 100);
        djui_base_set_size_type(&slider4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&slider4->base, djui_panel_camera_value_changed);
        djui_base_set_size(&slider4->base, 1.0f, 32);

        struct DjuiSlider* slider5 = djui_slider_create(&body->base, "Deceleration", &configCameraDegrade, 0, 100);
        djui_base_set_size_type(&slider5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&slider5->base, djui_panel_camera_value_changed);
        djui_base_set_size(&slider5->base, 1.0f, 32);

        struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_button_set_style(button6, 1);
        djui_interactable_hook_click(&button6->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
