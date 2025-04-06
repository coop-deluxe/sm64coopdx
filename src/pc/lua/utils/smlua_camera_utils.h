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

/* |description|Sets if only mods are allowed to modify the camera (Enabling prevents the player from modifying the camera through the settings)|descriptionEnd| */
void camera_romhack_allow_only_mods(u8 allow);
/* |description|Sets the romhack camera override status|descriptionEnd| */
void camera_set_romhack_override(enum RomhackCameraOverride rco);
/* |description|Sets if the romhack camera should allow centering, triggered with the L button|descriptionEnd| */
void camera_romhack_allow_centering(u8 allow);
/* |description|Sets if the romhack camera should fly above poison gas|descriptionEnd| */
void camera_allow_toxic_gas_camera(u8 allow);
/* |description|Sets if the romhack camera should allow D-Pad movement|descriptionEnd| */
void camera_romhack_allow_dpad_usage(u8 allow);
/* |description|
Toggles collision settings for the ROM hack camera.
This enables or disables specific collision behaviors in modded levels
|descriptionEnd| */
void rom_hack_cam_set_collisions(u8 enable);

/* |description|Sets the romhack camera's zoomed in distance (Default: 900)|descriptionEnd| */
void camera_romhack_set_zoomed_in_dist(u32 val);
/* |description|Sets the romhack camera's zoomed out additional distance (Default: 500)|descriptionEnd| */
void camera_romhack_set_zoomed_out_dist(u32 val);
/* |description|Sets the romhack camera's zoomed in height (Default: 300)|descriptionEnd| */
void camera_romhack_set_zoomed_in_height(u32 val);
/* |description|Sets the romhack camera's zoomed out additional height (Default: 150)|descriptionEnd| */
void camera_romhack_set_zoomed_out_height(u32 val);

/* |description|Gets the romhack camera's zoomed in distance|descriptionEnd| */
u32 camera_romhack_get_zoomed_in_dist(void);
/* |description|Gets the romhack camera's additional zoomed out distance|descriptionEnd| */
u32 camera_romhack_get_zoomed_out_dist(void);
/* |description|Gets the romhack camera's zoomed in height|descriptionEnd| */
u32 camera_romhack_get_zoomed_in_height(void);
/* |description|Gets the romhack camera's additional zoomed out height|descriptionEnd| */
u32 camera_romhack_get_zoomed_out_height(void);

/* |description|Gets the current romhack camera override status|descriptionEnd| */
enum RomhackCameraOverride camera_get_romhack_override(void);
/* |description|Gets if the romhack camera should allow centering|descriptionEnd| */
u8 camera_romhack_get_allow_centering(void);
/* |description|Gets if the romhack camera should fly above poison gas|descriptionEnd| */
u8 camera_get_allow_toxic_gas_camera(void);
/* |description|Gets if the romhack camera should allow D-Pad movement|descriptionEnd| */
u8 camera_romhack_get_allow_dpad_usage(void);
/* |description|Gets if the romhack camera has surface collisions|descriptionEnd| */
u8 camera_romhack_get_collisions(void);

/* |description|Checks if Free Camera is enabled|descriptionEnd| */
bool camera_config_is_free_cam_enabled(void);
/* |description|Checks if Analog Camera is enabled|descriptionEnd| */
bool camera_config_is_analog_cam_enabled(void);
/* |description|Checks if Freecam DPad Behavior is enabled|descriptionEnd| */
bool camera_config_is_dpad_enabled(void);
/* |description|Checks if Camera Collision is enabled|descriptionEnd| */
bool camera_config_is_collision_enabled(void);
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
/* |description|Gets if the L button will center the camera|descriptionEnd| */
bool camera_config_get_centering(void);

/* |description|Overrides if Free Camera is enabled|descriptionEnd| */
void camera_config_enable_free_cam(bool enable);
/* |description|Overrides if Analog Camera is enabled|descriptionEnd| */
void camera_config_enable_analog_cam(bool enable);
/* |description|Overrides if the L button will center the camera|descriptionEnd| */
void camera_config_enable_centering(bool enable);
/* |description|Overrides if Freecam DPad Behavior is enabled|descriptionEnd| */
void camera_config_enable_dpad(bool enable);
/* |description|Overrides if Camera Collision is enabled|descriptionEnd| */
void camera_config_enable_collisions(bool enable);
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
