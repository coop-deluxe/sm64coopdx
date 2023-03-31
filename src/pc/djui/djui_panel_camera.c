#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/game/bettercamera.h"

void djui_panel_camera_value_changed(UNUSED struct DjuiBase* caller) {
    newcam_init_settings();
}

void djui_panel_camera_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("CAMERA");
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, "Free Camera", &configEnableCamera, djui_panel_camera_value_changed);
        djui_checkbox_create(body, "Analog Camera", &configCameraAnalog, djui_panel_camera_value_changed);
#ifdef BETTERCAMERA
        djui_checkbox_create(body, "Mouse Look", &configCameraMouse, djui_panel_camera_value_changed);
#endif
        djui_checkbox_create(body, "Invert X", &configCameraInvertX, djui_panel_camera_value_changed);
        djui_checkbox_create(body, "Invert Y", &configCameraInvertY, djui_panel_camera_value_changed);
        djui_slider_create(body, "X Sensitivity", &configCameraXSens, 1, 100, djui_panel_camera_value_changed);
        djui_slider_create(body, "Y Sensitivity", &configCameraYSens, 1, 100, djui_panel_camera_value_changed);
        djui_slider_create(body, "Aggression", &configCameraAggr, 0, 100, djui_panel_camera_value_changed);
        djui_slider_create(body, "Pan Level", &configCameraPan, 0, 100, djui_panel_camera_value_changed);
        djui_slider_create(body, "Deceleration", &configCameraDegrade, 0, 100, djui_panel_camera_value_changed);

        djui_button_create(body, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
