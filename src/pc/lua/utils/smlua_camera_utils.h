#ifndef SMLUA_CAMERA_UTILS_H
#define SMLUA_CAMERA_UTILS_H

#include "types.h"
#include "game/camera.h"

struct CameraOverride {
    unsigned int value;
    bool override;
};

/* |description|Resets camera config overrides|descriptionEnd| */
void camera_reset_overrides(void);
/* |description|Freezes the camera by not updating it|descriptionEnd| */
void camera_freeze(void);
/* |description|Unfreezes the camera|descriptionEnd| */
void camera_unfreeze(void);
/* |description|Checks if the camera is frozen|descriptionEnd| */
bool camera_is_frozen(void);
/* |description|Sets the romhack camera override status|descriptionEnd| */
void camera_set_romhack_override(enum RomhackCameraOverride rco);
/* |description|Sets if the romhack camera should allow centering|descriptionEnd| */
void camera_romhack_allow_centering(u8 allow);
/* |description|Sets if the romhack camera should fly above poison gas|descriptionEnd| */
void camera_allow_toxic_gas_camera(u8 allow);
/* |description|Sets if the romhack camera should allow D-Pad movement|descriptionEnd| */
void camera_romhack_allow_dpad_usage(u8 allow);

/* |description|Checks if Free Camera is enabled|descriptionEnd| */
bool camera_config_is_free_cam_enabled(void);
/* |description|Checks if Analog Camera is enabled|descriptionEnd| */
bool camera_config_is_analog_cam_enabled(void);
/* |description|Checks if Mouse Look is enabled|descriptionEnd| */
bool camera_config_is_mouse_look_enabled(void);
/* |description|Checks if camera X is inverted|descriptionEnd| */
bool camera_config_is_x_inverted(void);
/* |description|Checks if camera Y is inverted|descriptionEnd| */
bool camera_config_is_y_inverted(void);
/* |description|Gets camera X sensitivity|descriptionEnd| */
u32  camera_config_get_x_sensitivity(void);
/* |description|Gets camera Y sensitivity|descriptionEnd| */
u32  camera_config_get_y_sensitivity(void);
/* |description|Gets camera aggression|descriptionEnd| */
u32  camera_config_get_aggression(void);
/* |description|Gets camera pan level|descriptionEnd| */
u32  camera_config_get_pan_level(void);
/* |description|Gets camera deceleration|descriptionEnd| */
u32  camera_config_get_deceleration(void);

/* |description|Overrides if Free Camera is enabled|descriptionEnd| */
void camera_config_enable_free_cam(bool enable);
/* |description|Overrides if Analog Camera is enabled|descriptionEnd| */
void camera_config_enable_analog_cam(bool enable);
/* |description|Overrides if camera mouse look is enabled|descriptionEnd| */
void camera_config_enable_mouse_look(bool enable);
/* |description|Overrides if camera X is inverted|descriptionEnd| */
void camera_config_invert_x(bool invert);
/* |description|Overrides if camera Y is inverted|descriptionEnd| */
void camera_config_invert_y(bool invert);
/* |description|Overrides camera X sensitivity|descriptionEnd| */
void camera_config_set_x_sensitivity(u32 value);
/* |description|Overrides camera Y sensitivity|descriptionEnd| */
void camera_config_set_y_sensitivity(u32 value);
/* |description|Overrides camera aggression|descriptionEnd| */
void camera_config_set_aggression(u32 value);
/* |description|Overrides camera pan level|descriptionEnd| */
void camera_config_set_pan_level(u32 value);
/* |description|Overrides camera deceleration|descriptionEnd| */
void camera_config_set_deceleration(u32 value);

/* |description|Checks if the camera should account for surfaces|descriptionEnd| */
bool camera_get_checking_surfaces(void);
/* |description|Sets if the camera should account for surfaces|descriptionEnd| */
void camera_set_checking_surfaces(bool value);

#endif
