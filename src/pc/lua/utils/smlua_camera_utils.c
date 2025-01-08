#include "smlua_camera_utils.h"
#include "game/bettercamera.h"
#include "game/object_list_processor.h"

static struct CameraOverride sOverrideCameraXSens            = { 0 };
static struct CameraOverride sOverrideCameraYSens            = { 0 };
static struct CameraOverride sOverrideCameraAggr             = { 0 };
static struct CameraOverride sOverrideCameraPan              = { 0 };
static struct CameraOverride sOverrideCameraDegrade          = { 0 };
static struct CameraOverride sOverrideCameraInvertX          = { 0 };
static struct CameraOverride sOverrideCameraInvertY          = { 0 };
static struct CameraOverride sOverrideEnableCamera           = { 0 };
static struct CameraOverride sOverrideCameraAnalog           = { 0 };
static struct CameraOverride sOverrideCameraMouse            = { 0 };
static struct CameraOverride sOverrideCameraFreecamDpad      = { 0 };
static struct CameraOverride sOverrideCameraFreecamCollision = { 0 };
static struct CameraOverride sOverrideCameraRomhackZoomedInDist = { 0 };
static struct CameraOverride sOverrideCameraRomhackZoomedOutDist = { 0 };
static struct CameraOverride sOverrideCameraRomhackZoomedInHeight = { 0 };
static struct CameraOverride sOverrideCameraRomhackZoomedOutHeight = { 0 };

void camera_reset_overrides(void) {
    sOverrideCameraXSens.override = false;
    sOverrideCameraYSens.override = false;
    sOverrideCameraAggr.override = false;
    sOverrideCameraPan.override = false;
    sOverrideCameraDegrade.override = false;
    sOverrideCameraInvertX.override = false;
    sOverrideCameraInvertY.override = false;
    sOverrideEnableCamera.override = false;
    sOverrideCameraAnalog.override = false;
    sOverrideCameraMouse.override = false;
    sOverrideCameraFreecamDpad.override = false;
    sOverrideCameraFreecamCollision.override = false;
    sOverrideCameraRomhackZoomedInDist.override = false;
    sOverrideCameraRomhackZoomedOutDist.override = false;
    sOverrideCameraRomhackZoomedInHeight.override = false;
    sOverrideCameraRomhackZoomedOutHeight.override = false;
}

void camera_freeze(void) {
    gOverrideFreezeCamera = TRUE;
}

void camera_unfreeze(void) {
    gOverrideFreezeCamera = FALSE;
}

bool camera_is_frozen(void) {
    return gOverrideFreezeCamera;
}

void camera_set_romhack_override(enum RomhackCameraOverride rco) {
    gOverrideRomhackCamera = rco;
}

void camera_romhack_allow_centering(u8 allow) {
    gRomhackCameraAllowCentering = allow;
}

void camera_allow_toxic_gas_camera(u8 allow) {
    gOverrideAllowToxicGasCamera = allow;
}

void camera_romhack_allow_dpad_usage(u8 allow) {
    gRomhackCameraAllowDpad = allow;
}

void rom_hack_cam_set_collisions(u8 enable) {
    gRomHackCamSetCollisions = enable;
}

void camera_romhack_set_zoomed_in_dist(u32 val) {
    if (val < 700) { val = 700; }
    else if (val > 1600) { val = 1600; }
    sOverrideCameraRomhackZoomedInDist.value = val;
    sOverrideCameraRomhackZoomedInDist.override = true;
}

void camera_romhack_set_zoomed_out_dist(u32 val) {
    if (val < 400) { val = 400; }
    else if (val > 1000) { val = 1000; }
    sOverrideCameraRomhackZoomedOutDist.value = val;
    sOverrideCameraRomhackZoomedOutDist.override = true;
}

void camera_romhack_set_zoomed_in_height(u32 val) {
    if (val < 200) { val = 200; }
    else if (val > 600) { val = 600; }
    sOverrideCameraRomhackZoomedInHeight.value = val;
    sOverrideCameraRomhackZoomedInHeight.override = true;
}

void camera_romhack_set_zoomed_out_height(u32 val) {
    if (val < 200) { val = 200; }
    else if (val > 600) { val = 600; }
    sOverrideCameraRomhackZoomedOutHeight.value = val;
    sOverrideCameraRomhackZoomedOutHeight.override = true;
}

u32 camera_romhack_get_zoomed_in_dist(void) {
    return sOverrideCameraRomhackZoomedInDist.override ? sOverrideCameraRomhackZoomedInDist.value : configRomhackCameraZoomedInDist;
}

u32 camera_romhack_get_zoomed_out_dist(void) {
    return sOverrideCameraRomhackZoomedOutDist.override ? sOverrideCameraRomhackZoomedOutDist.value : configRomhackCameraZoomedOutDist;
}

u32 camera_romhack_get_zoomed_in_height(void) {
    return sOverrideCameraRomhackZoomedInHeight.override ? sOverrideCameraRomhackZoomedInHeight.value : configRomhackCameraZoomedInHeight;
}

u32 camera_romhack_get_zoomed_out_height(void) {
    return sOverrideCameraRomhackZoomedOutHeight.override ? sOverrideCameraRomhackZoomedOutHeight.value : configRomhackCameraZoomedOutHeight;
}

enum RomhackCameraOverride camera_get_romhack_override(void) {
    return gOverrideRomhackCamera;
}

u8 camera_romhack_get_allow_centering(void) {
    return gRomhackCameraAllowCentering;
}

u8 camera_get_allow_toxic_gas_camera(void) {
    return gOverrideAllowToxicGasCamera;
}

u8 camera_romhack_get_allow_dpad_usage(void) {
    return gRomhackCameraAllowDpad;
}

u8 camera_romhack_get_collisions(void) {
    return gRomHackCamSetCollisions;
}

bool camera_config_is_free_cam_enabled(void) {
    return sOverrideEnableCamera.override ? sOverrideEnableCamera.value : configEnableFreeCamera;
}

bool camera_config_is_analog_cam_enabled(void) {
    return sOverrideCameraAnalog.override ? sOverrideCameraAnalog.value : configFreeCameraAnalog;
}

bool camera_config_is_freecam_dpad_enabled(void) {
    return sOverrideCameraFreecamDpad.override ? sOverrideCameraFreecamDpad.value : configFreeCameraDpadBehavior;
}

bool camera_config_is_free_camera_collision_enabled(void) {
    return sOverrideCameraFreecamCollision.override ? sOverrideCameraFreecamCollision.value : configFreeCameraHasCollision;
}

bool camera_config_is_mouse_look_enabled(void) {
    return sOverrideCameraMouse.override ? sOverrideCameraMouse.value : configCameraMouse;
}

bool camera_config_is_x_inverted(void) {
    return sOverrideCameraInvertX.override ? sOverrideCameraInvertX.value : configCameraInvertX;
}

bool camera_config_is_y_inverted(void) {
    return sOverrideCameraInvertY.override ? sOverrideCameraInvertY.value : configCameraInvertY;
}

u32 camera_config_get_x_sensitivity(void) {
    return sOverrideCameraXSens.override ? sOverrideCameraXSens.value : configCameraXSens;
}

u32 camera_config_get_y_sensitivity(void) {
    return sOverrideCameraYSens.override ? sOverrideCameraYSens.value : configCameraYSens;
}

u32 camera_config_get_aggression(void) {
    return sOverrideCameraAggr.override ? sOverrideCameraAggr.value : configCameraAggr;
}

u32 camera_config_get_pan_level(void) {
    return sOverrideCameraPan.override ? sOverrideCameraPan.value : configCameraPan;
}

u32 camera_config_get_deceleration(void) {
    return sOverrideCameraDegrade.override ? sOverrideCameraDegrade.value : configCameraDegrade;
}

void camera_config_enable_free_cam(bool enable) {
    sOverrideEnableCamera.value = enable;
    sOverrideEnableCamera.override = true;
    newcam_init_settings();
}

void camera_config_enable_analog_cam(bool enable) {
    sOverrideCameraAnalog.value = enable;
    sOverrideCameraAnalog.override = true;
    newcam_init_settings();
}

void camera_config_enable_freecam_dpad(bool enable) {
    sOverrideCameraFreecamDpad.value = enable;
    sOverrideCameraFreecamDpad.override = true;
    newcam_init_settings();
}

void camera_config_enable_camera_collisions(bool enable) {
    sOverrideCameraFreecamCollision.value = enable;
    sOverrideCameraFreecamCollision.override = true;
    newcam_init_settings();
}

void camera_config_enable_mouse_look(bool enable) {
    sOverrideCameraMouse.value = enable;
    sOverrideCameraMouse.override = true;
    newcam_init_settings();
}

void camera_config_invert_x(bool invert) {
    sOverrideCameraInvertX.value = invert;
    sOverrideCameraInvertX.override = true;
    newcam_init_settings();
}

void camera_config_invert_y(bool invert) {
    sOverrideCameraInvertY.value = invert;
    sOverrideCameraInvertY.override = true;
    newcam_init_settings();
}

void camera_config_set_x_sensitivity(u32 value) {
    sOverrideCameraXSens.value = MIN(MAX(value, 1), 100);
    sOverrideCameraXSens.override = true;
    newcam_init_settings();
}

void camera_config_set_y_sensitivity(u32 value) {
    sOverrideCameraYSens.value = MIN(MAX(value, 1), 100);
    sOverrideCameraYSens.override = true;
    newcam_init_settings();
}

void camera_config_set_aggression(u32 value) {
    sOverrideCameraAggr.value = MIN(MAX(value, 0), 100);
    sOverrideCameraAggr.override = true;
    newcam_init_settings();
}

void camera_config_set_pan_level(u32 value) {
    sOverrideCameraPan.value = MIN(MAX(value, 0), 100);
    sOverrideCameraPan.override = true;
    newcam_init_settings();
}

void camera_config_set_deceleration(u32 value) {
    sOverrideCameraDegrade.value = MIN(MAX(value, 0), 100);
    sOverrideCameraDegrade.override = true;
    newcam_init_settings();
}

bool camera_get_checking_surfaces(void) {
    return gCheckingSurfaceCollisionsForCamera;
}

void camera_set_checking_surfaces(bool value) {
    gCheckingSurfaceCollisionsForCamera = value;
}
