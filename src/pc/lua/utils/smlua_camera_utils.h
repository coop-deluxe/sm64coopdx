#ifndef SMLUA_CAMERA_UTILS_H
#define SMLUA_CAMERA_UTILS_H

#include "types.h"
#include "game/camera.h"

struct CameraOverride {
    unsigned int value;
    bool override;
};

void camera_reset_overrides(void);
void camera_freeze(void);
void camera_unfreeze(void);
bool camera_is_frozen(void);
void camera_set_romhack_override(enum RomhackCameraOverride rco);
void camera_romhack_allow_centering(u8 allow);
void camera_allow_toxic_gas_camera(u8 allow);
void camera_romhack_allow_dpad_usage(u8 allow);

bool camera_config_is_free_cam_enabled(void);
bool camera_config_is_analog_cam_enabled(void);
bool camera_config_is_mouse_look_enabled(void);
bool camera_config_is_x_inverted(void);
bool camera_config_is_y_inverted(void);
u32  camera_config_get_x_sensitivity(void);
u32  camera_config_get_y_sensitivity(void);
u32  camera_config_get_aggression(void);
u32  camera_config_get_pan_level(void);
u32  camera_config_get_deceleration(void);

void camera_config_enable_free_cam(bool enable);
void camera_config_enable_analog_cam(bool enable);
void camera_config_enable_mouse_look(bool enable);
void camera_config_invert_x(bool invert);
void camera_config_invert_y(bool invert);
void camera_config_set_x_sensitivity(u32 value);
void camera_config_set_y_sensitivity(u32 value);
void camera_config_set_aggression(u32 value);
void camera_config_set_pan_level(u32 value);
void camera_config_set_deceleration(u32 value);

bool camera_get_checking_surfaces(void);
void camera_set_checking_surfaces(bool value);

#endif
