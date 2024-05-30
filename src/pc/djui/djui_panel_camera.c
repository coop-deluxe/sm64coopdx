#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "game/bettercamera.h"
#include "game/first_person_cam.h"
#include "pc/lua/utils/smlua_misc_utils.h"

static void djui_panel_camera_value_changed(UNUSED struct DjuiBase* caller) {
    newcam_init_settings();
}

void djui_panel_camera_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CAMERA, CAMERA));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, DLANG(CAMERA, FREE_CAMERA), &configEnableCamera, djui_panel_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, ANALOG_CAMERA), &configCameraAnalog, djui_panel_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, MOUSE_LOOK), &configCameraMouse, djui_panel_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, INVERT_X), &configCameraInvertX, djui_panel_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, INVERT_Y), &configCameraInvertY, djui_panel_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, X_SENSITIVITY), &configCameraXSens, 1, 100, djui_panel_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, Y_SENSITIVITY), &configCameraYSens, 1, 100, djui_panel_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, AGGRESSION), &configCameraAggr, 0, 100, djui_panel_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, PAN_LEVEL), &configCameraPan, 0, 100, djui_panel_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, DECELERATION), &configCameraDegrade, 0, 100, djui_panel_camera_value_changed);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
