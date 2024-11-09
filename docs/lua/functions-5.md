## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-4.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | 5]


---
# functions from smlua_audio_utils.h

<br />


## [audio_sample_destroy](#audio_sample_destroy)

### Lua Example
`audio_sample_destroy(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_sample_destroy(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_sample_load](#audio_sample_load)

### Lua Example
`local ModAudioValue = audio_sample_load(filename)`

### Parameters
| Field | Type |
| ----- | ---- |
| filename | `string` |

### Returns
[ModAudio](structs.md#ModAudio)

### C Prototype
`struct ModAudio* audio_sample_load(const char* filename);`

[:arrow_up_small:](#)

<br />

## [audio_sample_play](#audio_sample_play)

### Lua Example
`audio_sample_play(audio, position, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| position | [Vec3f](structs.md#Vec3f) |
| volume | `number` |

### Returns
- None

### C Prototype
`void audio_sample_play(struct ModAudio* audio, Vec3f position, f32 volume);`

[:arrow_up_small:](#)

<br />

## [audio_sample_stop](#audio_sample_stop)

### Lua Example
`audio_sample_stop(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_sample_stop(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_destroy](#audio_stream_destroy)

### Lua Example
`audio_stream_destroy(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_stream_destroy(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_frequency](#audio_stream_get_frequency)

### Lua Example
`local numberValue = audio_stream_get_frequency(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_frequency(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_looping](#audio_stream_get_looping)

### Lua Example
`local booleanValue = audio_stream_get_looping(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- `boolean`

### C Prototype
`bool audio_stream_get_looping(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_position](#audio_stream_get_position)

### Lua Example
`local numberValue = audio_stream_get_position(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_position(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_volume](#audio_stream_get_volume)

### Lua Example
`local numberValue = audio_stream_get_volume(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_volume(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_load](#audio_stream_load)

### Lua Example
`local ModAudioValue = audio_stream_load(filename)`

### Parameters
| Field | Type |
| ----- | ---- |
| filename | `string` |

### Returns
[ModAudio](structs.md#ModAudio)

### C Prototype
`struct ModAudio* audio_stream_load(const char* filename);`

[:arrow_up_small:](#)

<br />

## [audio_stream_pause](#audio_stream_pause)

### Lua Example
`audio_stream_pause(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_stream_pause(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_play](#audio_stream_play)

### Lua Example
`audio_stream_play(audio, restart, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| restart | `boolean` |
| volume | `number` |

### Returns
- None

### C Prototype
`void audio_stream_play(struct ModAudio* audio, bool restart, f32 volume);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_frequency](#audio_stream_set_frequency)

### Lua Example
`audio_stream_set_frequency(audio, freq)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| freq | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_frequency(struct ModAudio* audio, f32 freq);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_looping](#audio_stream_set_looping)

### Lua Example
`audio_stream_set_looping(audio, looping)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| looping | `boolean` |

### Returns
- None

### C Prototype
`void audio_stream_set_looping(struct ModAudio* audio, bool looping);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_position](#audio_stream_set_position)

### Lua Example
`audio_stream_set_position(audio, pos)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| pos | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_position(struct ModAudio* audio, f32 pos);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_volume](#audio_stream_set_volume)

### Lua Example
`audio_stream_set_volume(audio, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| volume | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_volume(struct ModAudio* audio, f32 volume);`

[:arrow_up_small:](#)

<br />

## [audio_stream_stop](#audio_stream_stop)

### Lua Example
`audio_stream_stop(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_stream_stop(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [smlua_audio_utils_replace_sequence](#smlua_audio_utils_replace_sequence)

### Lua Example
`smlua_audio_utils_replace_sequence(sequenceId, bankId, defaultVolume, m64Name)`

### Parameters
| Field | Type |
| ----- | ---- |
| sequenceId | `integer` |
| bankId | `integer` |
| defaultVolume | `integer` |
| m64Name | `string` |

### Returns
- None

### C Prototype
`void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, u8 defaultVolume, const char* m64Name);`

[:arrow_up_small:](#)

<br />

## [smlua_audio_utils_reset_all](#smlua_audio_utils_reset_all)

### Lua Example
`smlua_audio_utils_reset_all()`

### Parameters
- None

### Returns
- None

### C Prototype
`void smlua_audio_utils_reset_all(void);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_camera_utils.h

<br />


## [camera_allow_toxic_gas_camera](#camera_allow_toxic_gas_camera)

### Lua Example
`camera_allow_toxic_gas_camera(allow)`

### Parameters
| Field | Type |
| ----- | ---- |
| allow | `integer` |

### Returns
- None

### C Prototype
`void camera_allow_toxic_gas_camera(u8 allow);`

[:arrow_up_small:](#)

<br />

## [camera_config_enable_analog_cam](#camera_config_enable_analog_cam)

### Lua Example
`camera_config_enable_analog_cam(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_enable_analog_cam(bool enable);`

[:arrow_up_small:](#)

<br />

## [camera_config_enable_free_cam](#camera_config_enable_free_cam)

### Lua Example
`camera_config_enable_free_cam(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_enable_free_cam(bool enable);`

[:arrow_up_small:](#)

<br />

## [camera_config_enable_mouse_look](#camera_config_enable_mouse_look)

### Lua Example
`camera_config_enable_mouse_look(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_enable_mouse_look(bool enable);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_aggression](#camera_config_get_aggression)

### Lua Example
`local integerValue = camera_config_get_aggression()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_aggression(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_deceleration](#camera_config_get_deceleration)

### Lua Example
`local integerValue = camera_config_get_deceleration()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_deceleration(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_pan_level](#camera_config_get_pan_level)

### Lua Example
`local integerValue = camera_config_get_pan_level()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_pan_level(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_x_sensitivity](#camera_config_get_x_sensitivity)

### Lua Example
`local integerValue = camera_config_get_x_sensitivity()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_x_sensitivity(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_y_sensitivity](#camera_config_get_y_sensitivity)

### Lua Example
`local integerValue = camera_config_get_y_sensitivity()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_y_sensitivity(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_invert_x](#camera_config_invert_x)

### Lua Example
`camera_config_invert_x(invert)`

### Parameters
| Field | Type |
| ----- | ---- |
| invert | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_invert_x(bool invert);`

[:arrow_up_small:](#)

<br />

## [camera_config_invert_y](#camera_config_invert_y)

### Lua Example
`camera_config_invert_y(invert)`

### Parameters
| Field | Type |
| ----- | ---- |
| invert | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_invert_y(bool invert);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_analog_cam_enabled](#camera_config_is_analog_cam_enabled)

### Lua Example
`local booleanValue = camera_config_is_analog_cam_enabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_analog_cam_enabled(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_free_cam_enabled](#camera_config_is_free_cam_enabled)

### Lua Example
`local booleanValue = camera_config_is_free_cam_enabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_free_cam_enabled(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_mouse_look_enabled](#camera_config_is_mouse_look_enabled)

### Lua Example
`local booleanValue = camera_config_is_mouse_look_enabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_mouse_look_enabled(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_x_inverted](#camera_config_is_x_inverted)

### Lua Example
`local booleanValue = camera_config_is_x_inverted()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_x_inverted(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_y_inverted](#camera_config_is_y_inverted)

### Lua Example
`local booleanValue = camera_config_is_y_inverted()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_y_inverted(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_aggression](#camera_config_set_aggression)

### Lua Example
`camera_config_set_aggression(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_aggression(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_deceleration](#camera_config_set_deceleration)

### Lua Example
`camera_config_set_deceleration(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_deceleration(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_pan_level](#camera_config_set_pan_level)

### Lua Example
`camera_config_set_pan_level(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_pan_level(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_x_sensitivity](#camera_config_set_x_sensitivity)

### Lua Example
`camera_config_set_x_sensitivity(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_x_sensitivity(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_y_sensitivity](#camera_config_set_y_sensitivity)

### Lua Example
`camera_config_set_y_sensitivity(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_y_sensitivity(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_freeze](#camera_freeze)

### Lua Example
`camera_freeze()`

### Parameters
- None

### Returns
- None

### C Prototype
`void camera_freeze(void);`

[:arrow_up_small:](#)

<br />

## [camera_get_checking_surfaces](#camera_get_checking_surfaces)

### Lua Example
`local booleanValue = camera_get_checking_surfaces()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_get_checking_surfaces(void);`

[:arrow_up_small:](#)

<br />

## [camera_is_frozen](#camera_is_frozen)

### Lua Example
`local booleanValue = camera_is_frozen()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_is_frozen(void);`

[:arrow_up_small:](#)

<br />

## [camera_reset_overrides](#camera_reset_overrides)

### Lua Example
`camera_reset_overrides()`

### Parameters
- None

### Returns
- None

### C Prototype
`void camera_reset_overrides(void);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_allow_centering](#camera_romhack_allow_centering)

### Lua Example
`camera_romhack_allow_centering(allow)`

### Parameters
| Field | Type |
| ----- | ---- |
| allow | `integer` |

### Returns
- None

### C Prototype
`void camera_romhack_allow_centering(u8 allow);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_allow_dpad_usage](#camera_romhack_allow_dpad_usage)

### Lua Example
`camera_romhack_allow_dpad_usage(allow)`

### Parameters
| Field | Type |
| ----- | ---- |
| allow | `integer` |

### Returns
- None

### C Prototype
`void camera_romhack_allow_dpad_usage(u8 allow);`

[:arrow_up_small:](#)

<br />

## [camera_set_checking_surfaces](#camera_set_checking_surfaces)

### Lua Example
`camera_set_checking_surfaces(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `boolean` |

### Returns
- None

### C Prototype
`void camera_set_checking_surfaces(bool value);`

[:arrow_up_small:](#)

<br />

## [camera_set_romhack_override](#camera_set_romhack_override)

### Lua Example
`camera_set_romhack_override(rco)`

### Parameters
| Field | Type |
| ----- | ---- |
| rco | [enum RomhackCameraOverride](constants.md#enum-RomhackCameraOverride) |

### Returns
- None

### C Prototype
`void camera_set_romhack_override(enum RomhackCameraOverride rco);`

[:arrow_up_small:](#)

<br />

## [camera_unfreeze](#camera_unfreeze)

### Lua Example
`camera_unfreeze()`

### Parameters
- None

### Returns
- None

### C Prototype
`void camera_unfreeze(void);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_collision_utils.h

<br />


## [collision_find_ceil](#collision_find_ceil)

### Lua Example
`local SurfaceValue = collision_find_ceil(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface* collision_find_ceil(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [collision_find_floor](#collision_find_floor)

### Lua Example
`local SurfaceValue = collision_find_floor(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface* collision_find_floor(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [collision_get_temp_wall_collision_data](#collision_get_temp_wall_collision_data)

### Lua Example
`local WallCollisionDataValue = collision_get_temp_wall_collision_data()`

### Parameters
- None

### Returns
[WallCollisionData](structs.md#WallCollisionData)

### C Prototype
`struct WallCollisionData* collision_get_temp_wall_collision_data(void);`

[:arrow_up_small:](#)

<br />

## [get_surface_from_wcd_index](#get_surface_from_wcd_index)

### Lua Example
`local SurfaceValue = get_surface_from_wcd_index(wcd, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| wcd | [WallCollisionData](structs.md#WallCollisionData) |
| index | `integer` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface* get_surface_from_wcd_index(struct WallCollisionData* wcd, s8 index);`

[:arrow_up_small:](#)

<br />

## [get_water_surface_pseudo_floor](#get_water_surface_pseudo_floor)

### Lua Example
`local SurfaceValue = get_water_surface_pseudo_floor()`

### Parameters
- None

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface* get_water_surface_pseudo_floor(void);`

[:arrow_up_small:](#)

<br />

## [smlua_collision_util_get](#smlua_collision_util_get)

### Lua Example
`local PointerValue = smlua_collision_util_get(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
- `Pointer` <`Collision`>

### C Prototype
`Collision* smlua_collision_util_get(const char* name);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_deprecated.h

<br />


---
# functions from smlua_gfx_utils.h

<br />


## [get_fog_color](#get_fog_color)

### Lua Example
`local integerValue = get_fog_color(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_fog_color(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_fog_intensity](#get_fog_intensity)

### Lua Example
`local numberValue = get_fog_intensity()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_fog_intensity(void);`

[:arrow_up_small:](#)

<br />

## [get_lighting_color](#get_lighting_color)

### Lua Example
`local integerValue = get_lighting_color(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_lighting_color(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_lighting_color_ambient](#get_lighting_color_ambient)

### Lua Example
`local integerValue = get_lighting_color_ambient(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_lighting_color_ambient(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_lighting_dir](#get_lighting_dir)

### Lua Example
`local numberValue = get_lighting_dir(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_lighting_dir(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_skybox](#get_skybox)

### Lua Example
`local integerValue = get_skybox()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s8 get_skybox(void);`

[:arrow_up_small:](#)

<br />

## [get_skybox_color](#get_skybox_color)

### Lua Example
`local integerValue = get_skybox_color(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_skybox_color(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_vertex_color](#get_vertex_color)

### Lua Example
`local integerValue = get_vertex_color(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_vertex_color(u8 index);`

[:arrow_up_small:](#)

<br />

## [set_fog_color](#set_fog_color)

### Lua Example
`set_fog_color(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_fog_color(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

## [set_fog_intensity](#set_fog_intensity)

### Lua Example
`set_fog_intensity(intensity)`

### Parameters
| Field | Type |
| ----- | ---- |
| intensity | `number` |

### Returns
- None

### C Prototype
`void set_fog_intensity(f32 intensity);`

[:arrow_up_small:](#)

<br />

## [set_lighting_color](#set_lighting_color)

### Lua Example
`set_lighting_color(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_lighting_color(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

## [set_lighting_color_ambient](#set_lighting_color_ambient)

### Lua Example
`set_lighting_color_ambient(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_lighting_color_ambient(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

## [set_lighting_dir](#set_lighting_dir)

### Lua Example
`set_lighting_dir(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `number` |

### Returns
- None

### C Prototype
`void set_lighting_dir(u8 index, f32 value);`

[:arrow_up_small:](#)

<br />

## [set_override_far](#set_override_far)

### Lua Example
`set_override_far(far)`

### Parameters
| Field | Type |
| ----- | ---- |
| far | `number` |

### Returns
- None

### C Prototype
`void set_override_far(f32 far);`

[:arrow_up_small:](#)

<br />

## [set_override_fov](#set_override_fov)

### Lua Example
`set_override_fov(fov)`

### Parameters
| Field | Type |
| ----- | ---- |
| fov | `number` |

### Returns
- None

### C Prototype
`void set_override_fov(f32 fov);`

[:arrow_up_small:](#)

<br />

## [set_override_near](#set_override_near)

### Lua Example
`set_override_near(near)`

### Parameters
| Field | Type |
| ----- | ---- |
| near | `number` |

### Returns
- None

### C Prototype
`void set_override_near(f32 near);`

[:arrow_up_small:](#)

<br />

## [set_override_skybox](#set_override_skybox)

### Lua Example
`set_override_skybox(background)`

### Parameters
| Field | Type |
| ----- | ---- |
| background | `integer` |

### Returns
- None

### C Prototype
`void set_override_skybox(s8 background);`

[:arrow_up_small:](#)

<br />

## [set_skybox_color](#set_skybox_color)

### Lua Example
`set_skybox_color(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_skybox_color(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

## [set_vertex_color](#set_vertex_color)

### Lua Example
`set_vertex_color(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_vertex_color(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_level_utils.h

<br />


## [level_is_vanilla_level](#level_is_vanilla_level)

### Lua Example
`local booleanValue = level_is_vanilla_level(levelNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| levelNum | `integer` |

### Returns
- `boolean`

### C Prototype
`bool level_is_vanilla_level(s16 levelNum);`

[:arrow_up_small:](#)

<br />

## [level_register](#level_register)

### Lua Example
`local integerValue = level_register(scriptEntryName, courseNum, fullName, shortName, acousticReach, echoLevel1, echoLevel2, echoLevel3)`

### Parameters
| Field | Type |
| ----- | ---- |
| scriptEntryName | `string` |
| courseNum | `integer` |
| fullName | `string` |
| shortName | `string` |
| acousticReach | `integer` |
| echoLevel1 | `integer` |
| echoLevel2 | `integer` |
| echoLevel3 | `integer` |

### Returns
- `integer`

### C Prototype
`s16 level_register(const char* scriptEntryName, s16 courseNum, const char* fullName, const char* shortName, u32 acousticReach, u32 echoLevel1, u32 echoLevel2, u32 echoLevel3);`

[:arrow_up_small:](#)

<br />

## [smlua_level_util_change_area](#smlua_level_util_change_area)

### Lua Example
`smlua_level_util_change_area(areaIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| areaIndex | `integer` |

### Returns
- None

### C Prototype
`void smlua_level_util_change_area(s32 areaIndex);`

[:arrow_up_small:](#)

<br />

## [smlua_level_util_get_info](#smlua_level_util_get_info)

### Lua Example
`local CustomLevelInfoValue = smlua_level_util_get_info(levelNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| levelNum | `integer` |

### Returns
[CustomLevelInfo](structs.md#CustomLevelInfo)

### C Prototype
`struct CustomLevelInfo* smlua_level_util_get_info(s16 levelNum);`

[:arrow_up_small:](#)

<br />

## [smlua_level_util_get_info_from_course_num](#smlua_level_util_get_info_from_course_num)

### Lua Example
`local CustomLevelInfoValue = smlua_level_util_get_info_from_course_num(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
[CustomLevelInfo](structs.md#CustomLevelInfo)

### C Prototype
`struct CustomLevelInfo* smlua_level_util_get_info_from_course_num(u8 courseNum);`

[:arrow_up_small:](#)

<br />

## [smlua_level_util_get_info_from_short_name](#smlua_level_util_get_info_from_short_name)

### Lua Example
`local CustomLevelInfoValue = smlua_level_util_get_info_from_short_name(shortName)`

### Parameters
| Field | Type |
| ----- | ---- |
| shortName | `string` |

### Returns
[CustomLevelInfo](structs.md#CustomLevelInfo)

### C Prototype
`struct CustomLevelInfo* smlua_level_util_get_info_from_short_name(const char* shortName);`

[:arrow_up_small:](#)

<br />

## [warp_exit_level](#warp_exit_level)

### Lua Example
`local booleanValue = warp_exit_level(aDelay)`

### Parameters
| Field | Type |
| ----- | ---- |
| aDelay | `integer` |

### Returns
- `boolean`

### C Prototype
`bool warp_exit_level(s32 aDelay);`

[:arrow_up_small:](#)

<br />

## [warp_restart_level](#warp_restart_level)

### Lua Example
`local booleanValue = warp_restart_level()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool warp_restart_level(void);`

[:arrow_up_small:](#)

<br />

## [warp_to_castle](#warp_to_castle)

### Lua Example
`local booleanValue = warp_to_castle(aLevel)`

### Parameters
| Field | Type |
| ----- | ---- |
| aLevel | `integer` |

### Returns
- `boolean`

### C Prototype
`bool warp_to_castle(s32 aLevel);`

[:arrow_up_small:](#)

<br />

## [warp_to_level](#warp_to_level)

### Lua Example
`local booleanValue = warp_to_level(aLevel, aArea, aAct)`

### Parameters
| Field | Type |
| ----- | ---- |
| aLevel | `integer` |
| aArea | `integer` |
| aAct | `integer` |

### Returns
- `boolean`

### C Prototype
`bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct);`

[:arrow_up_small:](#)

<br />

## [warp_to_start_level](#warp_to_start_level)

### Lua Example
`local booleanValue = warp_to_start_level()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool warp_to_start_level(void);`

[:arrow_up_small:](#)

<br />

## [warp_to_warpnode](#warp_to_warpnode)

### Lua Example
`local booleanValue = warp_to_warpnode(aLevel, aArea, aAct, aWarpId)`

### Parameters
| Field | Type |
| ----- | ---- |
| aLevel | `integer` |
| aArea | `integer` |
| aAct | `integer` |
| aWarpId | `integer` |

### Returns
- `boolean`

### C Prototype
`bool warp_to_warpnode(s32 aLevel, s32 aArea, s32 aAct, s32 aWarpId);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_math_utils.h

<br />


## [clamp](#clamp)

### Lua Example
`local integerValue = clamp(a, b, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |
| b | `integer` |
| c | `integer` |

### Returns
- `integer`

### C Prototype
`s32 clamp(s32 a, s32 b, s32 c);`

[:arrow_up_small:](#)

<br />

## [clampf](#clampf)

### Lua Example
`local numberValue = clampf(a, b, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `number` |
| b | `number` |
| c | `number` |

### Returns
- `number`

### C Prototype
`f32 clampf(f32 a, f32 b, f32 c);`

[:arrow_up_small:](#)

<br />

## [degrees_to_sm64](#degrees_to_sm64)

### Lua Example
`local integerValue = degrees_to_sm64(degreesAngle)`

### Parameters
| Field | Type |
| ----- | ---- |
| degreesAngle | `number` |

### Returns
- `integer`

### C Prototype
`s16 degrees_to_sm64(f32 degreesAngle);`

[:arrow_up_small:](#)

<br />

## [hypotf](#hypotf)

### Lua Example
`local numberValue = hypotf(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `number` |
| b | `number` |

### Returns
- `number`

### C Prototype
`f32 hypotf(f32 a, f32 b);`

[:arrow_up_small:](#)

<br />

## [radians_to_sm64](#radians_to_sm64)

### Lua Example
`local integerValue = radians_to_sm64(radiansAngle)`

### Parameters
| Field | Type |
| ----- | ---- |
| radiansAngle | `number` |

### Returns
- `integer`

### C Prototype
`s16 radians_to_sm64(f32 radiansAngle);`

[:arrow_up_small:](#)

<br />

## [sm64_to_degrees](#sm64_to_degrees)

### Lua Example
`local numberValue = sm64_to_degrees(sm64Angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| sm64Angle | `integer` |

### Returns
- `number`

### C Prototype
`f32 sm64_to_degrees(s16 sm64Angle);`

[:arrow_up_small:](#)

<br />

## [sm64_to_radians](#sm64_to_radians)

### Lua Example
`local numberValue = sm64_to_radians(sm64Angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| sm64Angle | `integer` |

### Returns
- `number`

### C Prototype
`f32 sm64_to_radians(s16 sm64Angle);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_misc_utils.h

<br />


## [allocate_mario_action](#allocate_mario_action)

### Lua Example
`local integerValue = allocate_mario_action(actFlags)`

### Parameters
| Field | Type |
| ----- | ---- |
| actFlags | `integer` |

### Returns
- `integer`

### C Prototype
`u32 allocate_mario_action(u32 actFlags);`

[:arrow_up_small:](#)

<br />

## [course_is_main_course](#course_is_main_course)

### Lua Example
`local booleanValue = course_is_main_course(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- `boolean`

### C Prototype
`bool course_is_main_course(u16 courseNum);`

[:arrow_up_small:](#)

<br />

## [deref_s32_pointer](#deref_s32_pointer)

### Lua Example
`local integerValue = deref_s32_pointer(pointer)`

### Parameters
| Field | Type |
| ----- | ---- |
| pointer | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 deref_s32_pointer(s32* pointer);`

[:arrow_up_small:](#)

<br />

## [djui_attempting_to_open_playerlist](#djui_attempting_to_open_playerlist)

### Lua Example
`local booleanValue = djui_attempting_to_open_playerlist()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool djui_attempting_to_open_playerlist(void);`

[:arrow_up_small:](#)

<br />

## [djui_is_playerlist_open](#djui_is_playerlist_open)

### Lua Example
`local booleanValue = djui_is_playerlist_open()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool djui_is_playerlist_open(void);`

[:arrow_up_small:](#)

<br />

## [djui_is_popup_disabled](#djui_is_popup_disabled)

### Lua Example
`local booleanValue = djui_is_popup_disabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool djui_is_popup_disabled(void);`

[:arrow_up_small:](#)

<br />

## [djui_menu_get_font](#djui_menu_get_font)

### Lua Example
`local enumValue = djui_menu_get_font()`

### Parameters
- None

### Returns
[enum DjuiFontType](constants.md#enum-DjuiFontType)

### C Prototype
`enum DjuiFontType djui_menu_get_font(void);`

[:arrow_up_small:](#)

<br />

## [djui_popup_create_global](#djui_popup_create_global)

### Lua Example
`djui_popup_create_global(message, lines)`

### Parameters
| Field | Type |
| ----- | ---- |
| message | `string` |
| lines | `integer` |

### Returns
- None

### C Prototype
`void djui_popup_create_global(const char* message, int lines);`

[:arrow_up_small:](#)

<br />

## [djui_reset_popup_disabled_override](#djui_reset_popup_disabled_override)

### Lua Example
`djui_reset_popup_disabled_override()`

### Parameters
- None

### Returns
- None

### C Prototype
`void djui_reset_popup_disabled_override(void);`

[:arrow_up_small:](#)

<br />

## [djui_set_popup_disabled_override](#djui_set_popup_disabled_override)

### Lua Example
`djui_set_popup_disabled_override(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `boolean` |

### Returns
- None

### C Prototype
`void djui_set_popup_disabled_override(bool value);`

[:arrow_up_small:](#)

<br />

## [get_coopnet_id](#get_coopnet_id)

### Lua Example
`local stringValue = get_coopnet_id(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `string`

### C Prototype
`const char* get_coopnet_id(s8 localIndex);`

[:arrow_up_small:](#)

<br />

## [get_current_save_file_num](#get_current_save_file_num)

### Lua Example
`local integerValue = get_current_save_file_num()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 get_current_save_file_num(void);`

[:arrow_up_small:](#)

<br />

## [get_date_and_time](#get_date_and_time)

### Lua Example
`local DateTimeValue = get_date_and_time()`

### Parameters
- None

### Returns
[DateTime](structs.md#DateTime)

### C Prototype
`struct DateTime* get_date_and_time(void);`

[:arrow_up_small:](#)

<br />

## [get_dialog_box_state](#get_dialog_box_state)

### Lua Example
`local integerValue = get_dialog_box_state()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s8 get_dialog_box_state(void);`

[:arrow_up_small:](#)

<br />

## [get_dialog_id](#get_dialog_id)

### Lua Example
`local integerValue = get_dialog_id()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 get_dialog_id(void);`

[:arrow_up_small:](#)

<br />

## [get_dialog_response](#get_dialog_response)

### Lua Example
`local integerValue = get_dialog_response()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 get_dialog_response(void);`

[:arrow_up_small:](#)

<br />

## [get_envfx](#get_envfx)

### Lua Example
`local integerValue = get_envfx()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u16 get_envfx(void);`

[:arrow_up_small:](#)

<br />

## [get_environment_region](#get_environment_region)

### Lua Example
`local numberValue = get_environment_region(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_environment_region(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_global_timer](#get_global_timer)

### Lua Example
`local integerValue = get_global_timer()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 get_global_timer(void);`

[:arrow_up_small:](#)

<br />

## [get_got_file_coin_hi_score](#get_got_file_coin_hi_score)

### Lua Example
`local booleanValue = get_got_file_coin_hi_score()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool get_got_file_coin_hi_score(void);`

[:arrow_up_small:](#)

<br />

## [get_hand_foot_pos_x](#get_hand_foot_pos_x)

### Lua Example
`local numberValue = get_hand_foot_pos_x(m, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_hand_foot_pos_x(struct MarioState* m, u8 index);`

[:arrow_up_small:](#)

<br />

## [get_hand_foot_pos_y](#get_hand_foot_pos_y)

### Lua Example
`local numberValue = get_hand_foot_pos_y(m, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_hand_foot_pos_y(struct MarioState* m, u8 index);`

[:arrow_up_small:](#)

<br />

## [get_hand_foot_pos_z](#get_hand_foot_pos_z)

### Lua Example
`local numberValue = get_hand_foot_pos_z(m, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_hand_foot_pos_z(struct MarioState* m, u8 index);`

[:arrow_up_small:](#)

<br />

## [get_last_completed_course_num](#get_last_completed_course_num)

### Lua Example
`local integerValue = get_last_completed_course_num()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 get_last_completed_course_num(void);`

[:arrow_up_small:](#)

<br />

## [get_last_completed_star_num](#get_last_completed_star_num)

### Lua Example
`local integerValue = get_last_completed_star_num()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 get_last_completed_star_num(void);`

[:arrow_up_small:](#)

<br />

## [get_last_star_or_key](#get_last_star_or_key)

### Lua Example
`local integerValue = get_last_star_or_key()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 get_last_star_or_key(void);`

[:arrow_up_small:](#)

<br />

## [get_local_discord_id](#get_local_discord_id)

### Lua Example
`local stringValue = get_local_discord_id()`

### Parameters
- None

### Returns
- `string`

### C Prototype
`const char* get_local_discord_id(void);`

[:arrow_up_small:](#)

<br />

## [get_network_area_timer](#get_network_area_timer)

### Lua Example
`local integerValue = get_network_area_timer()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 get_network_area_timer(void);`

[:arrow_up_small:](#)

<br />

## [get_os_name](#get_os_name)

### Lua Example
`local stringValue = get_os_name()`

### Parameters
- None

### Returns
- `string`

### C Prototype
`const char* get_os_name(void);`

[:arrow_up_small:](#)

<br />

## [get_save_file_modified](#get_save_file_modified)

### Lua Example
`local booleanValue = get_save_file_modified()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool get_save_file_modified(void);`

[:arrow_up_small:](#)

<br />

## [get_temp_s32_pointer](#get_temp_s32_pointer)

### Lua Example
`local PointerValue = get_temp_s32_pointer(initialValue)`

### Parameters
| Field | Type |
| ----- | ---- |
| initialValue | `integer` |

### Returns
- `Pointer` <`integer`>

### C Prototype
`s32* get_temp_s32_pointer(s32 initialValue);`

[:arrow_up_small:](#)

<br />

## [get_time](#get_time)

### Lua Example
`local integerValue = get_time()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s64 get_time(void);`

[:arrow_up_small:](#)

<br />

## [get_ttc_speed_setting](#get_ttc_speed_setting)

### Lua Example
`local integerValue = get_ttc_speed_setting()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 get_ttc_speed_setting(void);`

[:arrow_up_small:](#)

<br />

## [get_volume_env](#get_volume_env)

### Lua Example
`local numberValue = get_volume_env()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_volume_env(void);`

[:arrow_up_small:](#)

<br />

## [get_volume_level](#get_volume_level)

### Lua Example
`local numberValue = get_volume_level()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_volume_level(void);`

[:arrow_up_small:](#)

<br />

## [get_volume_master](#get_volume_master)

### Lua Example
`local numberValue = get_volume_master()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_volume_master(void);`

[:arrow_up_small:](#)

<br />

## [get_volume_sfx](#get_volume_sfx)

### Lua Example
`local numberValue = get_volume_sfx()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_volume_sfx(void);`

[:arrow_up_small:](#)

<br />

## [get_water_level](#get_water_level)

### Lua Example
`local integerValue = get_water_level(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`s16 get_water_level(u8 index);`

[:arrow_up_small:](#)

<br />

## [hud_get_flash](#hud_get_flash)

### Lua Example
`local integerValue = hud_get_flash()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s8 hud_get_flash(void);`

[:arrow_up_small:](#)

<br />

## [hud_get_value](#hud_get_value)

### Lua Example
`local integerValue = hud_get_value(type)`

### Parameters
| Field | Type |
| ----- | ---- |
| type | [enum HudDisplayValue](constants.md#enum-HudDisplayValue) |

### Returns
- `integer`

### C Prototype
`s32 hud_get_value(enum HudDisplayValue type);`

[:arrow_up_small:](#)

<br />

## [hud_hide](#hud_hide)

### Lua Example
`hud_hide()`

### Parameters
- None

### Returns
- None

### C Prototype
`void hud_hide(void);`

[:arrow_up_small:](#)

<br />

## [hud_is_hidden](#hud_is_hidden)

### Lua Example
`local booleanValue = hud_is_hidden()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool hud_is_hidden(void);`

[:arrow_up_small:](#)

<br />

## [hud_render_power_meter](#hud_render_power_meter)

### Lua Example
`hud_render_power_meter(health, x, y, width, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| health | `integer` |
| x | `number` |
| y | `number` |
| width | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void hud_render_power_meter(s32 health, f32 x, f32 y, f32 width, f32 height);`

[:arrow_up_small:](#)

<br />

## [hud_render_power_meter_interpolated](#hud_render_power_meter_interpolated)

### Lua Example
`hud_render_power_meter_interpolated(health, prevX, prevY, prevWidth, prevHeight, x, y, width, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| health | `integer` |
| prevX | `number` |
| prevY | `number` |
| prevWidth | `number` |
| prevHeight | `number` |
| x | `number` |
| y | `number` |
| width | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void hud_render_power_meter_interpolated(s32 health, f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height);`

[:arrow_up_small:](#)

<br />

## [hud_set_flash](#hud_set_flash)

### Lua Example
`hud_set_flash(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void hud_set_flash(s8 value);`

[:arrow_up_small:](#)

<br />

## [hud_set_value](#hud_set_value)

### Lua Example
`hud_set_value(type, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| type | [enum HudDisplayValue](constants.md#enum-HudDisplayValue) |
| value | `integer` |

### Returns
- None

### C Prototype
`void hud_set_value(enum HudDisplayValue type, s32 value);`

[:arrow_up_small:](#)

<br />

## [hud_show](#hud_show)

### Lua Example
`hud_show()`

### Parameters
- None

### Returns
- None

### C Prototype
`void hud_show(void);`

[:arrow_up_small:](#)

<br />

## [is_game_paused](#is_game_paused)

### Lua Example
`local booleanValue = is_game_paused()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool is_game_paused(void);`

[:arrow_up_small:](#)

<br />

## [is_transition_playing](#is_transition_playing)

### Lua Example
`local booleanValue = is_transition_playing()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool is_transition_playing(void);`

[:arrow_up_small:](#)

<br />

## [movtexqc_register](#movtexqc_register)

### Lua Example
`movtexqc_register(name, level, area, type)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |
| level | `integer` |
| area | `integer` |
| type | `integer` |

### Returns
- None

### C Prototype
`void movtexqc_register(const char* name, s16 level, s16 area, s16 type);`

[:arrow_up_small:](#)

<br />

## [play_transition](#play_transition)

### Lua Example
`play_transition(transType, time, red, green, blue)`

### Parameters
| Field | Type |
| ----- | ---- |
| transType | `integer` |
| time | `integer` |
| red | `integer` |
| green | `integer` |
| blue | `integer` |

### Returns
- None

### C Prototype
`void play_transition(s16 transType, s16 time, u8 red, u8 green, u8 blue);`

[:arrow_up_small:](#)

<br />

## [reset_window_title](#reset_window_title)

### Lua Example
`reset_window_title()`

### Parameters
- None

### Returns
- None

### C Prototype
`void reset_window_title(void);`

[:arrow_up_small:](#)

<br />

## [save_file_get_using_backup_slot](#save_file_get_using_backup_slot)

### Lua Example
`local booleanValue = save_file_get_using_backup_slot()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool save_file_get_using_backup_slot(void);`

[:arrow_up_small:](#)

<br />

## [save_file_set_using_backup_slot](#save_file_set_using_backup_slot)

### Lua Example
`save_file_set_using_backup_slot(usingBackupSlot)`

### Parameters
| Field | Type |
| ----- | ---- |
| usingBackupSlot | `boolean` |

### Returns
- None

### C Prototype
`void save_file_set_using_backup_slot(bool usingBackupSlot);`

[:arrow_up_small:](#)

<br />

## [set_environment_region](#set_environment_region)

### Lua Example
`set_environment_region(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_environment_region(u8 index, s32 value);`

[:arrow_up_small:](#)

<br />

## [set_got_file_coin_hi_score](#set_got_file_coin_hi_score)

### Lua Example
`set_got_file_coin_hi_score(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `boolean` |

### Returns
- None

### C Prototype
`void set_got_file_coin_hi_score(bool value);`

[:arrow_up_small:](#)

<br />

## [set_last_completed_course_num](#set_last_completed_course_num)

### Lua Example
`set_last_completed_course_num(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- None

### C Prototype
`void set_last_completed_course_num(u8 courseNum);`

[:arrow_up_small:](#)

<br />

## [set_last_completed_star_num](#set_last_completed_star_num)

### Lua Example
`set_last_completed_star_num(starNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| starNum | `integer` |

### Returns
- None

### C Prototype
`void set_last_completed_star_num(u8 starNum);`

[:arrow_up_small:](#)

<br />

## [set_last_star_or_key](#set_last_star_or_key)

### Lua Example
`set_last_star_or_key(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_last_star_or_key(u8 value);`

[:arrow_up_small:](#)

<br />

## [set_override_envfx](#set_override_envfx)

### Lua Example
`set_override_envfx(envfx)`

### Parameters
| Field | Type |
| ----- | ---- |
| envfx | `integer` |

### Returns
- None

### C Prototype
`void set_override_envfx(s32 envfx);`

[:arrow_up_small:](#)

<br />

## [set_save_file_modified](#set_save_file_modified)

### Lua Example
`set_save_file_modified(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `boolean` |

### Returns
- None

### C Prototype
`void set_save_file_modified(bool value);`

[:arrow_up_small:](#)

<br />

## [set_ttc_speed_setting](#set_ttc_speed_setting)

### Lua Example
`set_ttc_speed_setting(speed)`

### Parameters
| Field | Type |
| ----- | ---- |
| speed | `integer` |

### Returns
- None

### C Prototype
`void set_ttc_speed_setting(s16 speed);`

[:arrow_up_small:](#)

<br />

## [set_volume_env](#set_volume_env)

### Lua Example
`set_volume_env(volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| volume | `number` |

### Returns
- None

### C Prototype
`void set_volume_env(f32 volume);`

[:arrow_up_small:](#)

<br />

## [set_volume_level](#set_volume_level)

### Lua Example
`set_volume_level(volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| volume | `number` |

### Returns
- None

### C Prototype
`void set_volume_level(f32 volume);`

[:arrow_up_small:](#)

<br />

## [set_volume_master](#set_volume_master)

### Lua Example
`set_volume_master(volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| volume | `number` |

### Returns
- None

### C Prototype
`void set_volume_master(f32 volume);`

[:arrow_up_small:](#)

<br />

## [set_volume_sfx](#set_volume_sfx)

### Lua Example
`set_volume_sfx(volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| volume | `number` |

### Returns
- None

### C Prototype
`void set_volume_sfx(f32 volume);`

[:arrow_up_small:](#)

<br />

## [set_water_level](#set_water_level)

### Lua Example
`set_water_level(index, height, sync)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| height | `integer` |
| sync | `boolean` |

### Returns
- None

### C Prototype
`void set_water_level(u8 index, s16 height, bool sync);`

[:arrow_up_small:](#)

<br />

## [set_window_title](#set_window_title)

### Lua Example
`set_window_title(title)`

### Parameters
| Field | Type |
| ----- | ---- |
| title | `string` |

### Returns
- None

### C Prototype
`void set_window_title(const char* title);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_model_utils.h

<br />


## [smlua_model_util_get_id](#smlua_model_util_get_id)

### Lua Example
`local enumValue = smlua_model_util_get_id(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
[enum ModelExtendedId](constants.md#enum-ModelExtendedId)

### C Prototype
`enum ModelExtendedId smlua_model_util_get_id(const char* name);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_obj_utils.h

<br />


## [get_temp_object_hitbox](#get_temp_object_hitbox)

### Lua Example
`local ObjectHitboxValue = get_temp_object_hitbox()`

### Parameters
- None

### Returns
[ObjectHitbox](structs.md#ObjectHitbox)

### C Prototype
`struct ObjectHitbox* get_temp_object_hitbox(void);`

[:arrow_up_small:](#)

<br />

## [get_trajectory](#get_trajectory)

### Lua Example
`local PointerValue = get_trajectory(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
- `Pointer` <`Trajectory`>

### C Prototype
`Trajectory* get_trajectory(const char* name);`

[:arrow_up_small:](#)

<br />

## [obj_check_hitbox_overlap](#obj_check_hitbox_overlap)

### Lua Example
`local booleanValue = obj_check_hitbox_overlap(o1, o2)`

### Parameters
| Field | Type |
| ----- | ---- |
| o1 | [Object](structs.md#Object) |
| o2 | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_check_hitbox_overlap(struct Object *o1, struct Object *o2);`

[:arrow_up_small:](#)

<br />

## [obj_check_overlap_with_hitbox_params](#obj_check_overlap_with_hitbox_params)

### Lua Example
`local booleanValue = obj_check_overlap_with_hitbox_params(o, x, y, z, h, r, d)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| x | `number` |
| y | `number` |
| z | `number` |
| h | `number` |
| r | `number` |
| d | `number` |

### Returns
- `boolean`

### C Prototype
`bool obj_check_overlap_with_hitbox_params(struct Object *o, f32 x, f32 y, f32 z, f32 h, f32 r, f32 d);`

[:arrow_up_small:](#)

<br />

## [obj_count_objects_with_behavior_id](#obj_count_objects_with_behavior_id)

### Lua Example
`local integerValue = obj_count_objects_with_behavior_id(behaviorId)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
- `integer`

### C Prototype
`s32 obj_count_objects_with_behavior_id(enum BehaviorId behaviorId);`

[:arrow_up_small:](#)

<br />

## [obj_get_collided_object](#obj_get_collided_object)

### Lua Example
`local ObjectValue = obj_get_collided_object(o, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| index | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_collided_object(struct Object *o, s16 index);`

[:arrow_up_small:](#)

<br />

## [obj_get_field_f32](#obj_get_field_f32)

### Lua Example
`local numberValue = obj_get_field_f32(o, fieldIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |

### Returns
- `number`

### C Prototype
`f32 obj_get_field_f32(struct Object *o, s32 fieldIndex);`

[:arrow_up_small:](#)

<br />

## [obj_get_field_s16](#obj_get_field_s16)

### Lua Example
`local integerValue = obj_get_field_s16(o, fieldIndex, fieldSubIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| fieldSubIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s16 obj_get_field_s16(struct Object *o, s32 fieldIndex, s32 fieldSubIndex);`

[:arrow_up_small:](#)

<br />

## [obj_get_field_s32](#obj_get_field_s32)

### Lua Example
`local integerValue = obj_get_field_s32(o, fieldIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_get_field_s32(struct Object *o, s32 fieldIndex);`

[:arrow_up_small:](#)

<br />

## [obj_get_field_u32](#obj_get_field_u32)

### Lua Example
`local integerValue = obj_get_field_u32(o, fieldIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u32 obj_get_field_u32(struct Object *o, s32 fieldIndex);`

[:arrow_up_small:](#)

<br />

## [obj_get_first](#obj_get_first)

### Lua Example
`local ObjectValue = obj_get_first(objList)`

### Parameters
| Field | Type |
| ----- | ---- |
| objList | [enum ObjectList](constants.md#enum-ObjectList) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_first(enum ObjectList objList);`

[:arrow_up_small:](#)

<br />

## [obj_get_first_with_behavior_id](#obj_get_first_with_behavior_id)

### Lua Example
`local ObjectValue = obj_get_first_with_behavior_id(behaviorId)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_first_with_behavior_id(enum BehaviorId behaviorId);`

[:arrow_up_small:](#)

<br />

## [obj_get_first_with_behavior_id_and_field_f32](#obj_get_first_with_behavior_id_and_field_f32)

### Lua Example
`local ObjectValue = obj_get_first_with_behavior_id_and_field_f32(behaviorId, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |
| fieldIndex | `integer` |
| value | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_first_with_behavior_id_and_field_f32(enum BehaviorId behaviorId, s32 fieldIndex, f32 value);`

[:arrow_up_small:](#)

<br />

## [obj_get_first_with_behavior_id_and_field_s32](#obj_get_first_with_behavior_id_and_field_s32)

### Lua Example
`local ObjectValue = obj_get_first_with_behavior_id_and_field_s32(behaviorId, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |
| fieldIndex | `integer` |
| value | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_first_with_behavior_id_and_field_s32(enum BehaviorId behaviorId, s32 fieldIndex, s32 value);`

[:arrow_up_small:](#)

<br />

## [obj_get_nearest_object_with_behavior_id](#obj_get_nearest_object_with_behavior_id)

### Lua Example
`local ObjectValue = obj_get_nearest_object_with_behavior_id(o, behaviorId)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_nearest_object_with_behavior_id(struct Object *o, enum BehaviorId behaviorId);`

[:arrow_up_small:](#)

<br />

## [obj_get_next](#obj_get_next)

### Lua Example
`local ObjectValue = obj_get_next(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_next(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_get_next_with_same_behavior_id](#obj_get_next_with_same_behavior_id)

### Lua Example
`local ObjectValue = obj_get_next_with_same_behavior_id(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_next_with_same_behavior_id(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_get_next_with_same_behavior_id_and_field_f32](#obj_get_next_with_same_behavior_id_and_field_f32)

### Lua Example
`local ObjectValue = obj_get_next_with_same_behavior_id_and_field_f32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_next_with_same_behavior_id_and_field_f32(struct Object *o, s32 fieldIndex, f32 value);`

[:arrow_up_small:](#)

<br />

## [obj_get_next_with_same_behavior_id_and_field_s32](#obj_get_next_with_same_behavior_id_and_field_s32)

### Lua Example
`local ObjectValue = obj_get_next_with_same_behavior_id_and_field_s32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_next_with_same_behavior_id_and_field_s32(struct Object *o, s32 fieldIndex, s32 value);`

[:arrow_up_small:](#)

<br />

## [obj_get_temp_spawn_particles_info](#obj_get_temp_spawn_particles_info)

### Lua Example
`local SpawnParticlesInfoValue = obj_get_temp_spawn_particles_info(modelId)`

### Parameters
| Field | Type |
| ----- | ---- |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |

### Returns
[SpawnParticlesInfo](structs.md#SpawnParticlesInfo)

### C Prototype
`struct SpawnParticlesInfo* obj_get_temp_spawn_particles_info(enum ModelExtendedId modelId);`

[:arrow_up_small:](#)

<br />

## [obj_has_behavior_id](#obj_has_behavior_id)

### Lua Example
`local integerValue = obj_has_behavior_id(o, behaviorId)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
- `integer`

### C Prototype
`s32 obj_has_behavior_id(struct Object *o, enum BehaviorId behaviorId);`

[:arrow_up_small:](#)

<br />

## [obj_has_model_extended](#obj_has_model_extended)

### Lua Example
`local integerValue = obj_has_model_extended(o, modelId)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |

### Returns
- `integer`

### C Prototype
`s32 obj_has_model_extended(struct Object *o, enum ModelExtendedId modelId);`

[:arrow_up_small:](#)

<br />

## [obj_is_attackable](#obj_is_attackable)

### Lua Example
`local booleanValue = obj_is_attackable(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_attackable(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_breakable_object](#obj_is_breakable_object)

### Lua Example
`local booleanValue = obj_is_breakable_object(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_breakable_object(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_bully](#obj_is_bully)

### Lua Example
`local booleanValue = obj_is_bully(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_bully(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_coin](#obj_is_coin)

### Lua Example
`local booleanValue = obj_is_coin(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_coin(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_exclamation_box](#obj_is_exclamation_box)

### Lua Example
`local booleanValue = obj_is_exclamation_box(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_exclamation_box(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_grabbable](#obj_is_grabbable)

### Lua Example
`local booleanValue = obj_is_grabbable(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_grabbable(struct Object *o) ;`

[:arrow_up_small:](#)

<br />

## [obj_is_mushroom_1up](#obj_is_mushroom_1up)

### Lua Example
`local booleanValue = obj_is_mushroom_1up(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_mushroom_1up(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_secret](#obj_is_secret)

### Lua Example
`local booleanValue = obj_is_secret(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_secret(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_valid_for_interaction](#obj_is_valid_for_interaction)

### Lua Example
`local booleanValue = obj_is_valid_for_interaction(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_valid_for_interaction(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_move_xyz](#obj_move_xyz)

### Lua Example
`obj_move_xyz(o, dx, dy, dz)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| dx | `number` |
| dy | `number` |
| dz | `number` |

### Returns
- None

### C Prototype
`void obj_move_xyz(struct Object *o, f32 dx, f32 dy, f32 dz);`

[:arrow_up_small:](#)

<br />

## [obj_set_field_f32](#obj_set_field_f32)

### Lua Example
`obj_set_field_f32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `number` |

### Returns
- None

### C Prototype
`void obj_set_field_f32(struct Object *o, s32 fieldIndex, f32 value);`

[:arrow_up_small:](#)

<br />

## [obj_set_field_s16](#obj_set_field_s16)

### Lua Example
`obj_set_field_s16(o, fieldIndex, fieldSubIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| fieldSubIndex | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void obj_set_field_s16(struct Object *o, s32 fieldIndex, s32 fieldSubIndex, s16 value);`

[:arrow_up_small:](#)

<br />

## [obj_set_field_s32](#obj_set_field_s32)

### Lua Example
`obj_set_field_s32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void obj_set_field_s32(struct Object *o, s32 fieldIndex, s32 value);`

[:arrow_up_small:](#)

<br />

## [obj_set_field_u32](#obj_set_field_u32)

### Lua Example
`obj_set_field_u32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void obj_set_field_u32(struct Object *o, s32 fieldIndex, u32 value);`

[:arrow_up_small:](#)

<br />

## [obj_set_model_extended](#obj_set_model_extended)

### Lua Example
`obj_set_model_extended(o, modelId)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |

### Returns
- None

### C Prototype
`void obj_set_model_extended(struct Object *o, enum ModelExtendedId modelId);`

[:arrow_up_small:](#)

<br />

## [obj_set_vel](#obj_set_vel)

### Lua Example
`obj_set_vel(o, vx, vy, vz)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| vx | `number` |
| vy | `number` |
| vz | `number` |

### Returns
- None

### C Prototype
`void obj_set_vel(struct Object *o, f32 vx, f32 vy, f32 vz);`

[:arrow_up_small:](#)

<br />

## [set_whirlpools](#set_whirlpools)

### Lua Example
`set_whirlpools(x, y, z, strength, area, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |
| strength | `integer` |
| area | `integer` |
| index | `integer` |

### Returns
- None

### C Prototype
`void set_whirlpools(f32 x, f32 y, f32 z, s16 strength, s16 area, s32 index);`

[:arrow_up_small:](#)

<br />

## [spawn_non_sync_object](#spawn_non_sync_object)

### Lua Example
`local ObjectValue = spawn_non_sync_object(behaviorId, modelId, x, y, z, objSetupFunction)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |
| x | `number` |
| y | `number` |
| z | `number` |
| objSetupFunction | `Lua Function` () |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* spawn_non_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);`

[:arrow_up_small:](#)

<br />

## [spawn_sync_object](#spawn_sync_object)

### Lua Example
`local ObjectValue = spawn_sync_object(behaviorId, modelId, x, y, z, objSetupFunction)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |
| x | `number` |
| y | `number` |
| z | `number` |
| objSetupFunction | `Lua Function` () |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* spawn_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_text_utils.h

<br />


## [smlua_text_utils_act_name_get](#smlua_text_utils_act_name_get)

### Lua Example
`local stringValue = smlua_text_utils_act_name_get(courseNum, actNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |

### Returns
- `string`

### C Prototype
`const char* smlua_text_utils_act_name_get(s16 courseNum, u8 actNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_act_name_mod_index](#smlua_text_utils_act_name_mod_index)

### Lua Example
`local integerValue = smlua_text_utils_act_name_mod_index(courseNum, actNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |

### Returns
- `integer`

### C Prototype
`s32 smlua_text_utils_act_name_mod_index(s16 courseNum, u8 actNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_act_name_replace](#smlua_text_utils_act_name_replace)

### Lua Example
`smlua_text_utils_act_name_replace(courseNum, actNum, name)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |
| name | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_act_name_replace(s16 courseNum, u8 actNum, const char* name);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_act_name_reset](#smlua_text_utils_act_name_reset)

### Lua Example
`smlua_text_utils_act_name_reset(courseNum, actNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |

### Returns
- None

### C Prototype
`void smlua_text_utils_act_name_reset(s16 courseNum, u8 actNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_castle_secret_stars_replace](#smlua_text_utils_castle_secret_stars_replace)

### Lua Example
`smlua_text_utils_castle_secret_stars_replace(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_castle_secret_stars_replace(const char* name);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_acts_replace](#smlua_text_utils_course_acts_replace)

### Lua Example
`smlua_text_utils_course_acts_replace(courseNum, courseName, act1, act2, act3, act4, act5, act6)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| courseName | `string` |
| act1 | `string` |
| act2 | `string` |
| act3 | `string` |
| act4 | `string` |
| act5 | `string` |
| act6 | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_course_acts_replace(s16 courseNum, const char* courseName, const char* act1, const char* act2, const char* act3, const char* act4, const char* act5, const char* act6);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_name_get](#smlua_text_utils_course_name_get)

### Lua Example
`local stringValue = smlua_text_utils_course_name_get(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- `string`

### C Prototype
`const char* smlua_text_utils_course_name_get(s16 courseNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_name_mod_index](#smlua_text_utils_course_name_mod_index)

### Lua Example
`local integerValue = smlua_text_utils_course_name_mod_index(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- `integer`

### C Prototype
`s32 smlua_text_utils_course_name_mod_index(s16 courseNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_name_replace](#smlua_text_utils_course_name_replace)

### Lua Example
`smlua_text_utils_course_name_replace(courseNum, name)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| name | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_course_name_replace(s16 courseNum, const char* name);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_name_reset](#smlua_text_utils_course_name_reset)

### Lua Example
`smlua_text_utils_course_name_reset(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- None

### C Prototype
`void smlua_text_utils_course_name_reset(s16 courseNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_dialog_replace](#smlua_text_utils_dialog_replace)

### Lua Example
`smlua_text_utils_dialog_replace(dialogId, unused, linesPerBox, leftOffset, width, str)`

### Parameters
| Field | Type |
| ----- | ---- |
| dialogId | [enum DialogId](constants.md#enum-DialogId) |
| unused | `integer` |
| linesPerBox | `integer` |
| leftOffset | `integer` |
| width | `integer` |
| str | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_dialog_replace(enum DialogId dialogId, u32 unused, s8 linesPerBox, s16 leftOffset, s16 width, const char* str);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_extra_text_replace](#smlua_text_utils_extra_text_replace)

### Lua Example
`smlua_text_utils_extra_text_replace(index, text)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| text | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_extra_text_replace(s16 index, const char* text);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_get_language](#smlua_text_utils_get_language)

### Lua Example
`local stringValue = smlua_text_utils_get_language()`

### Parameters
- None

### Returns
- `string`

### C Prototype
`const char* smlua_text_utils_get_language(void);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_secret_star_replace](#smlua_text_utils_secret_star_replace)

### Lua Example
`smlua_text_utils_secret_star_replace(courseNum, courseName)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| courseName | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_secret_star_replace(s16 courseNum, const char* courseName);`

[:arrow_up_small:](#)

<br />

---
# functions from sound_init.h

<br />


## [disable_background_sound](#disable_background_sound)

### Lua Example
`disable_background_sound()`

### Parameters
- None

### Returns
- None

### C Prototype
`void disable_background_sound(void);`

[:arrow_up_small:](#)

<br />

## [enable_background_sound](#enable_background_sound)

### Lua Example
`enable_background_sound()`

### Parameters
- None

### Returns
- None

### C Prototype
`void enable_background_sound(void);`

[:arrow_up_small:](#)

<br />

## [fadeout_cap_music](#fadeout_cap_music)

### Lua Example
`fadeout_cap_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void fadeout_cap_music(void);`

[:arrow_up_small:](#)

<br />

## [fadeout_level_music](#fadeout_level_music)

### Lua Example
`fadeout_level_music(fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| fadeTimer | `integer` |

### Returns
- None

### C Prototype
`void fadeout_level_music(s16 fadeTimer);`

[:arrow_up_small:](#)

<br />

## [fadeout_music](#fadeout_music)

### Lua Example
`fadeout_music(fadeOutTime)`

### Parameters
| Field | Type |
| ----- | ---- |
| fadeOutTime | `integer` |

### Returns
- None

### C Prototype
`void fadeout_music(s16 fadeOutTime);`

[:arrow_up_small:](#)

<br />

## [lower_background_noise](#lower_background_noise)

### Lua Example
`lower_background_noise(a)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |

### Returns
- None

### C Prototype
`void lower_background_noise(s32 a);`

[:arrow_up_small:](#)

<br />

## [play_cap_music](#play_cap_music)

### Lua Example
`play_cap_music(seqArgs)`

### Parameters
| Field | Type |
| ----- | ---- |
| seqArgs | `integer` |

### Returns
- None

### C Prototype
`void play_cap_music(u16 seqArgs);`

[:arrow_up_small:](#)

<br />

## [play_cutscene_music](#play_cutscene_music)

### Lua Example
`play_cutscene_music(seqArgs)`

### Parameters
| Field | Type |
| ----- | ---- |
| seqArgs | `integer` |

### Returns
- None

### C Prototype
`void play_cutscene_music(u16 seqArgs);`

[:arrow_up_small:](#)

<br />

## [play_infinite_stairs_music](#play_infinite_stairs_music)

### Lua Example
`play_infinite_stairs_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_infinite_stairs_music(void);`

[:arrow_up_small:](#)

<br />

## [play_menu_sounds](#play_menu_sounds)

### Lua Example
`play_menu_sounds(soundMenuFlags)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundMenuFlags | `integer` |

### Returns
- None

### C Prototype
`void play_menu_sounds(s16 soundMenuFlags);`

[:arrow_up_small:](#)

<br />

## [play_painting_eject_sound](#play_painting_eject_sound)

### Lua Example
`play_painting_eject_sound()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_painting_eject_sound(void);`

[:arrow_up_small:](#)

<br />

## [play_shell_music](#play_shell_music)

### Lua Example
`play_shell_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_shell_music(void);`

[:arrow_up_small:](#)

<br />

## [raise_background_noise](#raise_background_noise)

### Lua Example
`raise_background_noise(a)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |

### Returns
- None

### C Prototype
`void raise_background_noise(s32 a);`

[:arrow_up_small:](#)

<br />

## [reset_volume](#reset_volume)

### Lua Example
`reset_volume()`

### Parameters
- None

### Returns
- None

### C Prototype
`void reset_volume(void);`

[:arrow_up_small:](#)

<br />

## [set_background_music](#set_background_music)

### Lua Example
`set_background_music(a, seqArgs, fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |
| seqArgs | `integer` |
| fadeTimer | `integer` |

### Returns
- None

### C Prototype
`void set_background_music(u16 a, u16 seqArgs, s16 fadeTimer);`

[:arrow_up_small:](#)

<br />

## [stop_cap_music](#stop_cap_music)

### Lua Example
`stop_cap_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void stop_cap_music(void);`

[:arrow_up_small:](#)

<br />

## [stop_shell_music](#stop_shell_music)

### Lua Example
`stop_shell_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void stop_shell_music(void);`

[:arrow_up_small:](#)

<br />

---
# functions from spawn_sound.c

<br />


## [calc_dist_to_volume_range_1](#calc_dist_to_volume_range_1)

### Lua Example
`local integerValue = calc_dist_to_volume_range_1(distance)`

### Parameters
| Field | Type |
| ----- | ---- |
| distance | `number` |

### Returns
- `integer`

### C Prototype
`s32 calc_dist_to_volume_range_1(f32 distance);`

[:arrow_up_small:](#)

<br />

## [calc_dist_to_volume_range_2](#calc_dist_to_volume_range_2)

### Lua Example
`local integerValue = calc_dist_to_volume_range_2(distance)`

### Parameters
| Field | Type |
| ----- | ---- |
| distance | `number` |

### Returns
- `integer`

### C Prototype
`s32 calc_dist_to_volume_range_2(f32 distance);`

[:arrow_up_small:](#)

<br />

## [cur_obj_play_sound_1](#cur_obj_play_sound_1)

### Lua Example
`cur_obj_play_sound_1(soundMagic)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundMagic | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_play_sound_1(s32 soundMagic);`

[:arrow_up_small:](#)

<br />

## [cur_obj_play_sound_2](#cur_obj_play_sound_2)

### Lua Example
`cur_obj_play_sound_2(soundMagic)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundMagic | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_play_sound_2(s32 soundMagic);`

[:arrow_up_small:](#)

<br />

## [exec_anim_sound_state](#exec_anim_sound_state)

### Lua Example
`exec_anim_sound_state(soundStates, maxSoundStates)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundStates | [SoundState](structs.md#SoundState) |
| maxSoundStates | `integer` |

### Returns
- None

### C Prototype
`void exec_anim_sound_state(struct SoundState *soundStates, u16 maxSoundStates);`

[:arrow_up_small:](#)

<br />

---
# functions from surface_collision.h

<br />


## [find_ceil_height](#find_ceil_height)

### Lua Example
`local numberValue = find_ceil_height(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- `number`

### C Prototype
`f32 find_ceil_height(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [find_floor_height](#find_floor_height)

### Lua Example
`local numberValue = find_floor_height(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- `number`

### C Prototype
`f32 find_floor_height(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [find_poison_gas_level](#find_poison_gas_level)

### Lua Example
`local numberValue = find_poison_gas_level(x, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| z | `number` |

### Returns
- `number`

### C Prototype
`f32 find_poison_gas_level(f32 x, f32 z);`

[:arrow_up_small:](#)

<br />

## [find_wall_collisions](#find_wall_collisions)

### Lua Example
`local integerValue = find_wall_collisions(colData)`

### Parameters
| Field | Type |
| ----- | ---- |
| colData | [WallCollisionData](structs.md#WallCollisionData) |

### Returns
- `integer`

### C Prototype
`s32 find_wall_collisions(struct WallCollisionData *colData);`

[:arrow_up_small:](#)

<br />

## [find_water_level](#find_water_level)

### Lua Example
`local numberValue = find_water_level(x, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| z | `number` |

### Returns
- `number`

### C Prototype
`f32 find_water_level(f32 x, f32 z);`

[:arrow_up_small:](#)

<br />

---
# functions from surface_load.h

<br />


## [alloc_surface_pools](#alloc_surface_pools)

### Lua Example
`alloc_surface_pools()`

### Parameters
- None

### Returns
- None

### C Prototype
`void alloc_surface_pools(void);`

[:arrow_up_small:](#)

<br />

## [clear_dynamic_surfaces](#clear_dynamic_surfaces)

### Lua Example
`clear_dynamic_surfaces()`

### Parameters
- None

### Returns
- None

### C Prototype
`void clear_dynamic_surfaces(void);`

[:arrow_up_small:](#)

<br />

## [get_area_terrain_size](#get_area_terrain_size)

### Lua Example
`local integerValue = get_area_terrain_size(data)`

### Parameters
| Field | Type |
| ----- | ---- |
| data | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`u32 get_area_terrain_size(s16 *data);`

[:arrow_up_small:](#)

<br />

## [load_area_terrain](#load_area_terrain)

### Lua Example
`load_area_terrain(index, data, surfaceRooms, macroObjects)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| data | `Pointer` <`integer`> |
| surfaceRooms | `Pointer` <`integer`> |
| macroObjects | `Pointer` <`integer`> |

### Returns
- None

### C Prototype
`void load_area_terrain(s16 index, s16 *data, s8 *surfaceRooms, s16 *macroObjects);`

[:arrow_up_small:](#)

<br />

## [load_object_collision_model](#load_object_collision_model)

### Lua Example
`load_object_collision_model()`

### Parameters
- None

### Returns
- None

### C Prototype
`void load_object_collision_model(void);`

[:arrow_up_small:](#)

<br />

## [obj_get_surface_from_index](#obj_get_surface_from_index)

### Lua Example
`local SurfaceValue = obj_get_surface_from_index(o, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| index | `integer` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface *obj_get_surface_from_index(struct Object *o, u32 index);`

[:arrow_up_small:](#)

<br />

---

[< prev](functions-4.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | 5]

