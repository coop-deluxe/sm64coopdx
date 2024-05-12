#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "game/bettercamera.h"

#define FREE_CAMERA_OPTIONS 9

static struct DjuiBase* sFreeCameraOptions[FREE_CAMERA_OPTIONS] = { 0 };
static u8 sIndex = 0;

static struct DjuiCheckbox* djui_linked_checkbox_create(struct DjuiBase* parent, const char* message, bool* value, void (*on_value_change)(struct DjuiBase*)) {
    struct DjuiCheckbox* checkbox = djui_checkbox_create(parent, message, value, on_value_change);
    djui_base_set_enabled(&checkbox->base, configEnableCamera);
    sFreeCameraOptions[sIndex] = &checkbox->base;
    sIndex++;
    return checkbox;
}

static struct DjuiSlider* djui_linked_slider_create(struct DjuiBase* parent, const char* message, unsigned int* value, unsigned int min, unsigned int max, void (*on_value_change)(struct DjuiBase*)) {
    struct DjuiSlider* slider = djui_slider_create(parent, message, value, min, max, on_value_change);
    djui_base_set_enabled(&slider->base, configEnableCamera);
    sFreeCameraOptions[sIndex] = &slider->base;
    sIndex++;
    return slider;
}

static void djui_panel_camera_value_changed(UNUSED struct DjuiBase* caller) {
    newcam_init_settings();
    for (s32 i = 0; i < FREE_CAMERA_OPTIONS; i++) {
        djui_base_set_enabled(sFreeCameraOptions[i], configEnableCamera);
    }
}

void djui_panel_camera_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CAMERA, CAMERA));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, DLANG(CAMERA, FREE_CAMERA), &configEnableCamera, djui_panel_camera_value_changed);
        djui_linked_checkbox_create(body, DLANG(CAMERA, ANALOG_CAMERA), &configCameraAnalog, djui_panel_camera_value_changed);
        djui_linked_checkbox_create(body, DLANG(CAMERA, MOUSE_LOOK), &configCameraMouse, djui_panel_camera_value_changed);
        djui_linked_checkbox_create(body, DLANG(CAMERA, INVERT_X), &configCameraInvertX, djui_panel_camera_value_changed);
        djui_linked_checkbox_create(body, DLANG(CAMERA, INVERT_Y), &configCameraInvertY, djui_panel_camera_value_changed);
        djui_linked_slider_create(body, DLANG(CAMERA, X_SENSITIVITY), &configCameraXSens, 1, 100, djui_panel_camera_value_changed);
        djui_linked_slider_create(body, DLANG(CAMERA, Y_SENSITIVITY), &configCameraYSens, 1, 100, djui_panel_camera_value_changed);
        djui_linked_slider_create(body, DLANG(CAMERA, AGGRESSION), &configCameraAggr, 0, 100, djui_panel_camera_value_changed);
        djui_linked_slider_create(body, DLANG(CAMERA, PAN_LEVEL), &configCameraPan, 0, 100, djui_panel_camera_value_changed);
        djui_linked_slider_create(body, DLANG(CAMERA, DECELERATION), &configCameraDegrade, 0, 100, djui_panel_camera_value_changed);
        sIndex = 0;

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
