#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "game/bettercamera.h"
#include "game/first_person_cam.h"
#include "pc/lua/utils/smlua_misc_utils.h"

static void djui_panel_free_camera_value_changed(UNUSED struct DjuiBase* caller) {
    newcam_init_settings();
}

static void djui_panel_romhack_camera_value_changed(UNUSED struct DjuiBase* caller) {
    romhack_camera_init_settings();
}

void djui_panel_free_camera_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CAMERA, FREE_CAMERA_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, DLANG(CAMERA, FREE_CAMERA), &configEnableFreeCamera, djui_panel_free_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, ANALOG_CAMERA), &configFreeCameraAnalog, djui_panel_free_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, ROMHACK_CAMERA_L_CENTERING), &configFreeCameraLCentering, djui_panel_free_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, FREE_CAMERA_USE_DPAD), &configFreeCameraDPadBehavior, djui_panel_free_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, FREE_CAMERA_COLLISION), &configFreeCameraHasCollision, djui_panel_free_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, MOUSE_LOOK), &configFreeCameraMouse, djui_panel_free_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, X_SENSITIVITY), &configFreeCameraXSens, 1, 100, djui_panel_free_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, Y_SENSITIVITY), &configFreeCameraYSens, 1, 100, djui_panel_free_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, AGGRESSION), &configFreeCameraAggr, 0, 100, djui_panel_free_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, PAN_LEVEL), &configFreeCameraPan, 0, 100, djui_panel_free_camera_value_changed);
        djui_slider_create(body, DLANG(CAMERA, DECELERATION), &configFreeCameraDegrade, 0, 100, djui_panel_free_camera_value_changed);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}

void djui_panel_romhack_camera_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CAMERA, ROMHACK_CAMERA_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        char* choices[3] = { DLANG(CAMERA, ROMHACK_CAMERA_AUTOMATIC), DLANG(CAMERA, ROMHACK_CAMERA_ON), DLANG(CAMERA, ROMHACK_CAMERA_OFF) };
        djui_selectionbox_create(body, DLANG(CAMERA, ROMHACK_CAMERA), choices, 3, &configEnableRomhackCamera, djui_panel_romhack_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, ROMHACK_CAMERA_IN_BOWSER), &configRomhackCameraBowserFights, djui_panel_romhack_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, ROMHACK_CAMERA_COLLISION), &configRomhackCameraHasCollision, djui_panel_romhack_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, ROMHACK_CAMERA_L_CENTERING), &configRomhackCameraHasCentering, djui_panel_romhack_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, ROMHACK_CAMERA_USE_DPAD), &configRomhackCameraDPadBehavior, djui_panel_romhack_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, ROMHACK_CAMERA_SLOW_FALL), &configRomhackCameraSlowFall, djui_panel_romhack_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, CAMERA_TOXIC_GAS), &configCameraToxicGas, djui_panel_romhack_camera_value_changed); // this should technically be a common option

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}

void djui_panel_camera_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CAMERA, CAMERA), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_button_create(body, DLANG(CAMERA, FREE_CAMERA), DJUI_BUTTON_STYLE_NORMAL, djui_panel_free_camera_create);
        djui_button_create(body, DLANG(CAMERA, ROMHACK_CAMERA), DJUI_BUTTON_STYLE_NORMAL, djui_panel_romhack_camera_create);
        djui_checkbox_create(body, DLANG(CAMERA, INVERT_X), &configCameraInvertX, djui_panel_free_camera_value_changed);
        djui_checkbox_create(body, DLANG(CAMERA, INVERT_Y), &configCameraInvertY, djui_panel_free_camera_value_changed);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}