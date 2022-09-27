## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-2.md) | [1](functions.md) | [2](functions-2.md) | 3 | [4](functions-4.md) | [next >](functions-4.md)]


---
# functions from camera.h

<br />


## [approach_camera_height](#approach_camera_height)

### Lua Example
`approach_camera_height(c, goal, inc)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |
| goal | `number` |
| inc | `number` |

### Returns
- None

### C Prototype
`void approach_camera_height(struct Camera *c, f32 goal, f32 inc);`

[:arrow_up_small:](#)

<br />

## [approach_f32_asymptotic](#approach_f32_asymptotic)

### Lua Example
`local numberValue = approach_f32_asymptotic(current, target, multiplier)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `number` |
| target | `number` |
| multiplier | `number` |

### Returns
- `number`

### C Prototype
`f32 approach_f32_asymptotic(f32 current, f32 target, f32 multiplier);`

[:arrow_up_small:](#)

<br />

## [approach_f32_asymptotic_bool](#approach_f32_asymptotic_bool)

### Lua Example
`local integerValue = approach_f32_asymptotic_bool(current, target, multiplier)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `Pointer` <`number`> |
| target | `number` |
| multiplier | `number` |

### Returns
- `integer`

### C Prototype
`s32 approach_f32_asymptotic_bool(f32 *current, f32 target, f32 multiplier);`

[:arrow_up_small:](#)

<br />

## [approach_s16_asymptotic](#approach_s16_asymptotic)

### Lua Example
`local integerValue = approach_s16_asymptotic(current, target, divisor)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `integer` |
| target | `integer` |
| divisor | `integer` |

### Returns
- `integer`

### C Prototype
`s32 approach_s16_asymptotic(s16 current, s16 target, s16 divisor);`

[:arrow_up_small:](#)

<br />

## [approach_s16_asymptotic_bool](#approach_s16_asymptotic_bool)

### Lua Example
`local integerValue = approach_s16_asymptotic_bool(current, target, divisor)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `Pointer` <`integer`> |
| target | `integer` |
| divisor | `integer` |

### Returns
- `integer`

### C Prototype
`s32 approach_s16_asymptotic_bool(s16 *current, s16 target, s16 divisor);`

[:arrow_up_small:](#)

<br />

## [approach_vec3f_asymptotic](#approach_vec3f_asymptotic)

### Lua Example
`approach_vec3f_asymptotic(current, target, xMul, yMul, zMul)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | [Vec3f](structs.md#Vec3f) |
| target | [Vec3f](structs.md#Vec3f) |
| xMul | `number` |
| yMul | `number` |
| zMul | `number` |

### Returns
- None

### C Prototype
`void approach_vec3f_asymptotic(Vec3f current, Vec3f target, f32 xMul, f32 yMul, f32 zMul);`

[:arrow_up_small:](#)

<br />

## [calc_abs_dist](#calc_abs_dist)

### Lua Example
`local numberValue = calc_abs_dist(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `number`

### C Prototype
`f32 calc_abs_dist(Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [calc_hor_dist](#calc_hor_dist)

### Lua Example
`local numberValue = calc_hor_dist(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `number`

### C Prototype
`f32 calc_hor_dist(Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [calculate_angles](#calculate_angles)

### Lua Example
`calculate_angles(from, to, pitch, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| pitch | `Pointer` <`integer`> |
| yaw | `Pointer` <`integer`> |

### Returns
- None

### C Prototype
`void calculate_angles(Vec3f from, Vec3f to, s16 *pitch, s16 *yaw);`

[:arrow_up_small:](#)

<br />

## [calculate_pitch](#calculate_pitch)

### Lua Example
`local integerValue = calculate_pitch(from, to)`

### Parameters
| Field | Type |
| ----- | ---- |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |

### Returns
- `integer`

### C Prototype
`s16 calculate_pitch(Vec3f from, Vec3f to);`

[:arrow_up_small:](#)

<br />

## [calculate_yaw](#calculate_yaw)

### Lua Example
`local integerValue = calculate_yaw(from, to)`

### Parameters
| Field | Type |
| ----- | ---- |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |

### Returns
- `integer`

### C Prototype
`s16 calculate_yaw(Vec3f from, Vec3f to);`

[:arrow_up_small:](#)

<br />

## [cam_select_alt_mode](#cam_select_alt_mode)

### Lua Example
`local integerValue = cam_select_alt_mode(angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| angle | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cam_select_alt_mode(s32 angle);`

[:arrow_up_small:](#)

<br />

## [camera_approach_f32_symmetric](#camera_approach_f32_symmetric)

### Lua Example
`local numberValue = camera_approach_f32_symmetric(value, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `number` |
| target | `number` |
| increment | `number` |

### Returns
- `number`

### C Prototype
`f32 camera_approach_f32_symmetric(f32 value, f32 target, f32 increment);`

[:arrow_up_small:](#)

<br />

## [camera_approach_f32_symmetric_bool](#camera_approach_f32_symmetric_bool)

### Lua Example
`local integerValue = camera_approach_f32_symmetric_bool(current, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `Pointer` <`number`> |
| target | `number` |
| increment | `number` |

### Returns
- `integer`

### C Prototype
`s32 camera_approach_f32_symmetric_bool(f32 *current, f32 target, f32 increment);`

[:arrow_up_small:](#)

<br />

## [camera_approach_s16_symmetric_bool](#camera_approach_s16_symmetric_bool)

### Lua Example
`local integerValue = camera_approach_s16_symmetric_bool(current, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `Pointer` <`integer`> |
| target | `integer` |
| increment | `integer` |

### Returns
- `integer`

### C Prototype
`s32 camera_approach_s16_symmetric_bool(s16 *current, s16 target, s16 increment);`

[:arrow_up_small:](#)

<br />

## [camera_course_processing](#camera_course_processing)

### Lua Example
`local integerValue = camera_course_processing(c)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |

### Returns
- `integer`

### C Prototype
`s16 camera_course_processing(struct Camera *c);`

[:arrow_up_small:](#)

<br />

## [camera_set_use_course_specific_settings](#camera_set_use_course_specific_settings)

### Lua Example
`camera_set_use_course_specific_settings(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `integer` |

### Returns
- None

### C Prototype
`void camera_set_use_course_specific_settings(u8 enable);`

[:arrow_up_small:](#)

<br />

## [center_rom_hack_camera](#center_rom_hack_camera)

### Lua Example
`center_rom_hack_camera()`

### Parameters
- None

### Returns
- None

### C Prototype
`void center_rom_hack_camera(void);`

[:arrow_up_small:](#)

<br />

## [clamp_pitch](#clamp_pitch)

### Lua Example
`local integerValue = clamp_pitch(from, to, maxPitch, minPitch)`

### Parameters
| Field | Type |
| ----- | ---- |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| maxPitch | `integer` |
| minPitch | `integer` |

### Returns
- `integer`

### C Prototype
`s32 clamp_pitch(Vec3f from, Vec3f to, s16 maxPitch, s16 minPitch);`

[:arrow_up_small:](#)

<br />

## [clamp_positions_and_find_yaw](#clamp_positions_and_find_yaw)

### Lua Example
`local integerValue = clamp_positions_and_find_yaw(pos, origin, xMax, xMin, zMax, zMin)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| origin | [Vec3f](structs.md#Vec3f) |
| xMax | `number` |
| xMin | `number` |
| zMax | `number` |
| zMin | `number` |

### Returns
- `integer`

### C Prototype
`s32 clamp_positions_and_find_yaw(Vec3f pos, Vec3f origin, f32 xMax, f32 xMin, f32 zMax, f32 zMin);`

[:arrow_up_small:](#)

<br />

## [collide_with_walls](#collide_with_walls)

### Lua Example
`local integerValue = collide_with_walls(pos, offsetY, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| offsetY | `number` |
| radius | `number` |

### Returns
- `integer`

### C Prototype
`s32 collide_with_walls(Vec3f pos, f32 offsetY, f32 radius);`

[:arrow_up_small:](#)

<br />

## [cutscene_object](#cutscene_object)

### Lua Example
`local integerValue = cutscene_object(cutscene, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| cutscene | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s16 cutscene_object(u8 cutscene, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [cutscene_object_with_dialog](#cutscene_object_with_dialog)

### Lua Example
`local integerValue = cutscene_object_with_dialog(cutscene, o, dialogID)`

### Parameters
| Field | Type |
| ----- | ---- |
| cutscene | `integer` |
| o | [Object](structs.md#Object) |
| dialogID | `integer` |

### Returns
- `integer`

### C Prototype
`s16 cutscene_object_with_dialog(u8 cutscene, struct Object *o, s16 dialogID);`

[:arrow_up_small:](#)

<br />

## [cutscene_object_without_dialog](#cutscene_object_without_dialog)

### Lua Example
`local integerValue = cutscene_object_without_dialog(cutscene, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| cutscene | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s16 cutscene_object_without_dialog(u8 cutscene, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [cutscene_set_fov_shake_preset](#cutscene_set_fov_shake_preset)

### Lua Example
`cutscene_set_fov_shake_preset(preset)`

### Parameters
| Field | Type |
| ----- | ---- |
| preset | `integer` |

### Returns
- None

### C Prototype
`void cutscene_set_fov_shake_preset(u8 preset);`

[:arrow_up_small:](#)

<br />

## [cutscene_spawn_obj](#cutscene_spawn_obj)

### Lua Example
`local integerValue = cutscene_spawn_obj(obj, frame)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | `integer` |
| frame | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cutscene_spawn_obj(u32 obj, s16 frame);`

[:arrow_up_small:](#)

<br />

## [find_c_buttons_pressed](#find_c_buttons_pressed)

### Lua Example
`local integerValue = find_c_buttons_pressed(currentState, buttonsPressed, buttonsDown)`

### Parameters
| Field | Type |
| ----- | ---- |
| currentState | `integer` |
| buttonsPressed | `integer` |
| buttonsDown | `integer` |

### Returns
- `integer`

### C Prototype
`s32 find_c_buttons_pressed(u16 currentState, u16 buttonsPressed, u16 buttonsDown);`

[:arrow_up_small:](#)

<br />

## [find_mario_floor_and_ceil](#find_mario_floor_and_ceil)

### Lua Example
`find_mario_floor_and_ceil(pg)`

### Parameters
| Field | Type |
| ----- | ---- |
| pg | [PlayerGeometry](structs.md#PlayerGeometry) |

### Returns
- None

### C Prototype
`void find_mario_floor_and_ceil(struct PlayerGeometry *pg);`

[:arrow_up_small:](#)

<br />

## [get_cutscene_from_mario_status](#get_cutscene_from_mario_status)

### Lua Example
`local integerValue = get_cutscene_from_mario_status(c)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |

### Returns
- `integer`

### C Prototype
`u8 get_cutscene_from_mario_status(struct Camera *c);`

[:arrow_up_small:](#)

<br />

## [handle_c_button_movement](#handle_c_button_movement)

### Lua Example
`handle_c_button_movement(c)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |

### Returns
- None

### C Prototype
`void handle_c_button_movement(struct Camera *c);`

[:arrow_up_small:](#)

<br />

## [is_range_behind_surface](#is_range_behind_surface)

### Lua Example
`local integerValue = is_range_behind_surface(from, to, surf, range, surfType)`

### Parameters
| Field | Type |
| ----- | ---- |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| surf | [Surface](structs.md#Surface) |
| range | `integer` |
| surfType | `integer` |

### Returns
- `integer`

### C Prototype
`s32 is_range_behind_surface(Vec3f from, Vec3f to, struct Surface *surf, s16 range, s16 surfType);`

[:arrow_up_small:](#)

<br />

## [is_within_100_units_of_mario](#is_within_100_units_of_mario)

### Lua Example
`local integerValue = is_within_100_units_of_mario(posX, posY, posZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| posX | `number` |
| posY | `number` |
| posZ | `number` |

### Returns
- `integer`

### C Prototype
`s32 is_within_100_units_of_mario(f32 posX, f32 posY, f32 posZ);`

[:arrow_up_small:](#)

<br />

## [move_mario_head_c_up](#move_mario_head_c_up)

### Lua Example
`move_mario_head_c_up(c)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |

### Returns
- None

### C Prototype
`void move_mario_head_c_up(UNUSED struct Camera *c);`

[:arrow_up_small:](#)

<br />

## [next_lakitu_state](#next_lakitu_state)

### Lua Example
`local integerValue = next_lakitu_state(newPos, newFoc, curPos, curFoc, oldPos, oldFoc, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| newPos | [Vec3f](structs.md#Vec3f) |
| newFoc | [Vec3f](structs.md#Vec3f) |
| curPos | [Vec3f](structs.md#Vec3f) |
| curFoc | [Vec3f](structs.md#Vec3f) |
| oldPos | [Vec3f](structs.md#Vec3f) |
| oldFoc | [Vec3f](structs.md#Vec3f) |
| yaw | `integer` |

### Returns
- `integer`

### C Prototype
`s16 next_lakitu_state(Vec3f newPos, Vec3f newFoc, Vec3f curPos, Vec3f curFoc, Vec3f oldPos, Vec3f oldFoc, s16 yaw);`

[:arrow_up_small:](#)

<br />

## [obj_rotate_towards_point](#obj_rotate_towards_point)

### Lua Example
`obj_rotate_towards_point(o, point, pitchOff, yawOff, pitchDiv, yawDiv)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| point | [Vec3f](structs.md#Vec3f) |
| pitchOff | `integer` |
| yawOff | `integer` |
| pitchDiv | `integer` |
| yawDiv | `integer` |

### Returns
- None

### C Prototype
`void obj_rotate_towards_point(struct Object *o, Vec3f point, s16 pitchOff, s16 yawOff, s16 pitchDiv, s16 yawDiv);`

[:arrow_up_small:](#)

<br />

## [object_pos_to_vec3f](#object_pos_to_vec3f)

### Lua Example
`object_pos_to_vec3f(dst, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Vec3f](structs.md#Vec3f) |
| o | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void object_pos_to_vec3f(Vec3f dst, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [offset_rotated](#offset_rotated)

### Lua Example
`offset_rotated(dst, from, to, rotation)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Vec3f](structs.md#Vec3f) |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| rotation | [Vec3s](structs.md#Vec3s) |

### Returns
- None

### C Prototype
`void offset_rotated(Vec3f dst, Vec3f from, Vec3f to, Vec3s rotation);`

[:arrow_up_small:](#)

<br />

## [offset_yaw_outward_radial](#offset_yaw_outward_radial)

### Lua Example
`local integerValue = offset_yaw_outward_radial(c, areaYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |
| areaYaw | `integer` |

### Returns
- `integer`

### C Prototype
`s32 offset_yaw_outward_radial(struct Camera *c, s16 areaYaw);`

[:arrow_up_small:](#)

<br />

## [play_camera_buzz_if_c_sideways](#play_camera_buzz_if_c_sideways)

### Lua Example
`play_camera_buzz_if_c_sideways()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_camera_buzz_if_c_sideways(void);`

[:arrow_up_small:](#)

<br />

## [play_camera_buzz_if_cbutton](#play_camera_buzz_if_cbutton)

### Lua Example
`play_camera_buzz_if_cbutton()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_camera_buzz_if_cbutton(void);`

[:arrow_up_small:](#)

<br />

## [play_camera_buzz_if_cdown](#play_camera_buzz_if_cdown)

### Lua Example
`play_camera_buzz_if_cdown()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_camera_buzz_if_cdown(void);`

[:arrow_up_small:](#)

<br />

## [play_cutscene](#play_cutscene)

### Lua Example
`play_cutscene(c)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |

### Returns
- None

### C Prototype
`void play_cutscene(struct Camera *c);`

[:arrow_up_small:](#)

<br />

## [play_sound_button_change_blocked](#play_sound_button_change_blocked)

### Lua Example
`play_sound_button_change_blocked()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_sound_button_change_blocked(void);`

[:arrow_up_small:](#)

<br />

## [play_sound_cbutton_down](#play_sound_cbutton_down)

### Lua Example
`play_sound_cbutton_down()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_sound_cbutton_down(void);`

[:arrow_up_small:](#)

<br />

## [play_sound_cbutton_side](#play_sound_cbutton_side)

### Lua Example
`play_sound_cbutton_side()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_sound_cbutton_side(void);`

[:arrow_up_small:](#)

<br />

## [play_sound_cbutton_up](#play_sound_cbutton_up)

### Lua Example
`play_sound_cbutton_up()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_sound_cbutton_up(void);`

[:arrow_up_small:](#)

<br />

## [play_sound_if_cam_switched_to_lakitu_or_mario](#play_sound_if_cam_switched_to_lakitu_or_mario)

### Lua Example
`play_sound_if_cam_switched_to_lakitu_or_mario()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_sound_if_cam_switched_to_lakitu_or_mario(void);`

[:arrow_up_small:](#)

<br />

## [play_sound_rbutton_changed](#play_sound_rbutton_changed)

### Lua Example
`play_sound_rbutton_changed()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_sound_rbutton_changed(void);`

[:arrow_up_small:](#)

<br />

## [radial_camera_input](#radial_camera_input)

### Lua Example
`local integerValue = radial_camera_input(c, unused)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |
| unused | `number` |

### Returns
- `integer`

### C Prototype
`s32 radial_camera_input(struct Camera *c, UNUSED f32 unused);`

[:arrow_up_small:](#)

<br />

## [random_vec3s](#random_vec3s)

### Lua Example
`random_vec3s(dst, xRange, yRange, zRange)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Vec3s](structs.md#Vec3s) |
| xRange | `integer` |
| yRange | `integer` |
| zRange | `integer` |

### Returns
- None

### C Prototype
`void random_vec3s(Vec3s dst, s16 xRange, s16 yRange, s16 zRange);`

[:arrow_up_small:](#)

<br />

## [reset_camera](#reset_camera)

### Lua Example
`reset_camera(c)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |

### Returns
- None

### C Prototype
`void reset_camera(struct Camera *c);`

[:arrow_up_small:](#)

<br />

## [resolve_geometry_collisions](#resolve_geometry_collisions)

### Lua Example
`resolve_geometry_collisions(pos, lastGood)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| lastGood | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void resolve_geometry_collisions(Vec3f pos, UNUSED Vec3f lastGood);`

[:arrow_up_small:](#)

<br />

## [rom_hack_cam_set_collisions](#rom_hack_cam_set_collisions)

### Lua Example
`rom_hack_cam_set_collisions(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `integer` |

### Returns
- None

### C Prototype
`void rom_hack_cam_set_collisions(u8 enable);`

[:arrow_up_small:](#)

<br />

## [rotate_camera_around_walls](#rotate_camera_around_walls)

### Lua Example
`local integerValue = rotate_camera_around_walls(c, cPos, avoidYaw, yawRange)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |
| cPos | [Vec3f](structs.md#Vec3f) |
| avoidYaw | `Pointer` <`integer`> |
| yawRange | `integer` |

### Returns
- `integer`

### C Prototype
`s32 rotate_camera_around_walls(struct Camera *c, Vec3f cPos, s16 *avoidYaw, s16 yawRange);`

[:arrow_up_small:](#)

<br />

## [rotate_in_xz](#rotate_in_xz)

### Lua Example
`rotate_in_xz(dst, src, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Vec3f](structs.md#Vec3f) |
| src | [Vec3f](structs.md#Vec3f) |
| yaw | `integer` |

### Returns
- None

### C Prototype
`void rotate_in_xz(Vec3f dst, Vec3f src, s16 yaw);`

[:arrow_up_small:](#)

<br />

## [rotate_in_yz](#rotate_in_yz)

### Lua Example
`rotate_in_yz(dst, src, pitch)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Vec3f](structs.md#Vec3f) |
| src | [Vec3f](structs.md#Vec3f) |
| pitch | `integer` |

### Returns
- None

### C Prototype
`void rotate_in_yz(Vec3f dst, Vec3f src, s16 pitch);`

[:arrow_up_small:](#)

<br />

## [scale_along_line](#scale_along_line)

### Lua Example
`scale_along_line(dest, from, to, scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| scale | `number` |

### Returns
- None

### C Prototype
`void scale_along_line(Vec3f dest, Vec3f from, Vec3f to, f32 scale);`

[:arrow_up_small:](#)

<br />

## [select_mario_cam_mode](#select_mario_cam_mode)

### Lua Example
`select_mario_cam_mode()`

### Parameters
- None

### Returns
- None

### C Prototype
`void select_mario_cam_mode(void);`

[:arrow_up_small:](#)

<br />

## [set_cam_angle](#set_cam_angle)

### Lua Example
`local integerValue = set_cam_angle(mode)`

### Parameters
| Field | Type |
| ----- | ---- |
| mode | `integer` |

### Returns
- `integer`

### C Prototype
`s32 set_cam_angle(s32 mode);`

[:arrow_up_small:](#)

<br />

## [set_camera_mode](#set_camera_mode)

### Lua Example
`set_camera_mode(c, mode, frames)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |
| mode | `integer` |
| frames | `integer` |

### Returns
- None

### C Prototype
`void set_camera_mode(struct Camera *c, s16 mode, s16 frames);`

[:arrow_up_small:](#)

<br />

## [set_camera_mode_fixed](#set_camera_mode_fixed)

### Lua Example
`local integerValue = set_camera_mode_fixed(c, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |
| x | `integer` |
| y | `integer` |
| z | `integer` |

### Returns
- `integer`

### C Prototype
`s32 set_camera_mode_fixed(struct Camera* c, s16 x, s16 y, s16 z);`

[:arrow_up_small:](#)

<br />

## [set_camera_pitch_shake](#set_camera_pitch_shake)

### Lua Example
`set_camera_pitch_shake(mag, decay, inc)`

### Parameters
| Field | Type |
| ----- | ---- |
| mag | `integer` |
| decay | `integer` |
| inc | `integer` |

### Returns
- None

### C Prototype
`void set_camera_pitch_shake(s16 mag, s16 decay, s16 inc);`

[:arrow_up_small:](#)

<br />

## [set_camera_roll_shake](#set_camera_roll_shake)

### Lua Example
`set_camera_roll_shake(mag, decay, inc)`

### Parameters
| Field | Type |
| ----- | ---- |
| mag | `integer` |
| decay | `integer` |
| inc | `integer` |

### Returns
- None

### C Prototype
`void set_camera_roll_shake(s16 mag, s16 decay, s16 inc);`

[:arrow_up_small:](#)

<br />

## [set_camera_shake_from_hit](#set_camera_shake_from_hit)

### Lua Example
`set_camera_shake_from_hit(shake)`

### Parameters
| Field | Type |
| ----- | ---- |
| shake | `integer` |

### Returns
- None

### C Prototype
`void set_camera_shake_from_hit(s16 shake);`

[:arrow_up_small:](#)

<br />

## [set_camera_shake_from_point](#set_camera_shake_from_point)

### Lua Example
`set_camera_shake_from_point(shake, posX, posY, posZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| shake | `integer` |
| posX | `number` |
| posY | `number` |
| posZ | `number` |

### Returns
- None

### C Prototype
`void set_camera_shake_from_point(s16 shake, f32 posX, f32 posY, f32 posZ);`

[:arrow_up_small:](#)

<br />

## [set_camera_yaw_shake](#set_camera_yaw_shake)

### Lua Example
`set_camera_yaw_shake(mag, decay, inc)`

### Parameters
| Field | Type |
| ----- | ---- |
| mag | `integer` |
| decay | `integer` |
| inc | `integer` |

### Returns
- None

### C Prototype
`void set_camera_yaw_shake(s16 mag, s16 decay, s16 inc);`

[:arrow_up_small:](#)

<br />

## [set_environmental_camera_shake](#set_environmental_camera_shake)

### Lua Example
`set_environmental_camera_shake(shake)`

### Parameters
| Field | Type |
| ----- | ---- |
| shake | `integer` |

### Returns
- None

### C Prototype
`void set_environmental_camera_shake(s16 shake);`

[:arrow_up_small:](#)

<br />

## [set_fixed_cam_axis_sa_lobby](#set_fixed_cam_axis_sa_lobby)

### Lua Example
`set_fixed_cam_axis_sa_lobby(preset)`

### Parameters
| Field | Type |
| ----- | ---- |
| preset | `integer` |

### Returns
- None

### C Prototype
`void set_fixed_cam_axis_sa_lobby(UNUSED s16 preset);`

[:arrow_up_small:](#)

<br />

## [set_fov_function](#set_fov_function)

### Lua Example
`set_fov_function(func)`

### Parameters
| Field | Type |
| ----- | ---- |
| func | `integer` |

### Returns
- None

### C Prototype
`void set_fov_function(u8 func);`

[:arrow_up_small:](#)

<br />

## [set_fov_shake](#set_fov_shake)

### Lua Example
`set_fov_shake(amplitude, decay, shakeSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| amplitude | `integer` |
| decay | `integer` |
| shakeSpeed | `integer` |

### Returns
- None

### C Prototype
`void set_fov_shake(s16 amplitude, s16 decay, s16 shakeSpeed);`

[:arrow_up_small:](#)

<br />

## [set_fov_shake_from_point_preset](#set_fov_shake_from_point_preset)

### Lua Example
`set_fov_shake_from_point_preset(preset, posX, posY, posZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| preset | `integer` |
| posX | `number` |
| posY | `number` |
| posZ | `number` |

### Returns
- None

### C Prototype
`void set_fov_shake_from_point_preset(u8 preset, f32 posX, f32 posY, f32 posZ);`

[:arrow_up_small:](#)

<br />

## [set_handheld_shake](#set_handheld_shake)

### Lua Example
`set_handheld_shake(mode)`

### Parameters
| Field | Type |
| ----- | ---- |
| mode | `integer` |

### Returns
- None

### C Prototype
`void set_handheld_shake(u8 mode);`

[:arrow_up_small:](#)

<br />

## [set_or_approach_f32_asymptotic](#set_or_approach_f32_asymptotic)

### Lua Example
`local integerValue = set_or_approach_f32_asymptotic(dst, goal, scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | `Pointer` <`number`> |
| goal | `number` |
| scale | `number` |

### Returns
- `integer`

### C Prototype
`s32 set_or_approach_f32_asymptotic(f32 *dst, f32 goal, f32 scale);`

[:arrow_up_small:](#)

<br />

## [set_or_approach_s16_symmetric](#set_or_approach_s16_symmetric)

### Lua Example
`local integerValue = set_or_approach_s16_symmetric(current, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `Pointer` <`integer`> |
| target | `integer` |
| increment | `integer` |

### Returns
- `integer`

### C Prototype
`s32 set_or_approach_s16_symmetric(s16 *current, s16 target, s16 increment);`

[:arrow_up_small:](#)

<br />

## [set_or_approach_vec3f_asymptotic](#set_or_approach_vec3f_asymptotic)

### Lua Example
`set_or_approach_vec3f_asymptotic(dst, goal, xMul, yMul, zMul)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Vec3f](structs.md#Vec3f) |
| goal | [Vec3f](structs.md#Vec3f) |
| xMul | `number` |
| yMul | `number` |
| zMul | `number` |

### Returns
- None

### C Prototype
`void set_or_approach_vec3f_asymptotic(Vec3f dst, Vec3f goal, f32 xMul, f32 yMul, f32 zMul);`

[:arrow_up_small:](#)

<br />

## [set_pitch_shake_from_point](#set_pitch_shake_from_point)

### Lua Example
`set_pitch_shake_from_point(mag, decay, inc, maxDist, posX, posY, posZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| mag | `integer` |
| decay | `integer` |
| inc | `integer` |
| maxDist | `number` |
| posX | `number` |
| posY | `number` |
| posZ | `number` |

### Returns
- None

### C Prototype
`void set_pitch_shake_from_point(s16 mag, s16 decay, s16 inc, f32 maxDist, f32 posX, f32 posY, f32 posZ);`

[:arrow_up_small:](#)

<br />

## [shake_camera_handheld](#shake_camera_handheld)

### Lua Example
`shake_camera_handheld(pos, focus)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| focus | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void shake_camera_handheld(Vec3f pos, Vec3f focus);`

[:arrow_up_small:](#)

<br />

## [shake_camera_pitch](#shake_camera_pitch)

### Lua Example
`shake_camera_pitch(pos, focus)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| focus | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void shake_camera_pitch(Vec3f pos, Vec3f focus);`

[:arrow_up_small:](#)

<br />

## [shake_camera_roll](#shake_camera_roll)

### Lua Example
`shake_camera_roll(roll)`

### Parameters
| Field | Type |
| ----- | ---- |
| roll | `Pointer` <`integer`> |

### Returns
- None

### C Prototype
`void shake_camera_roll(s16 *roll);`

[:arrow_up_small:](#)

<br />

## [shake_camera_yaw](#shake_camera_yaw)

### Lua Example
`shake_camera_yaw(pos, focus)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| focus | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void shake_camera_yaw(Vec3f pos, Vec3f focus);`

[:arrow_up_small:](#)

<br />

## [soft_reset_camera](#soft_reset_camera)

### Lua Example
`soft_reset_camera(c)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |

### Returns
- None

### C Prototype
`void soft_reset_camera(struct Camera* c);`

[:arrow_up_small:](#)

<br />

## [start_cutscene](#start_cutscene)

### Lua Example
`start_cutscene(c, cutscene)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |
| cutscene | `integer` |

### Returns
- None

### C Prototype
`void start_cutscene(struct Camera *c, u8 cutscene);`

[:arrow_up_small:](#)

<br />

## [start_object_cutscene_without_focus](#start_object_cutscene_without_focus)

### Lua Example
`local integerValue = start_object_cutscene_without_focus(cutscene)`

### Parameters
| Field | Type |
| ----- | ---- |
| cutscene | `integer` |

### Returns
- `integer`

### C Prototype
`u8 start_object_cutscene_without_focus(u8 cutscene);`

[:arrow_up_small:](#)

<br />

## [transition_next_state](#transition_next_state)

### Lua Example
`transition_next_state(c, frames)`

### Parameters
| Field | Type |
| ----- | ---- |
| c | [Camera](structs.md#Camera) |
| frames | `integer` |

### Returns
- None

### C Prototype
`void transition_next_state(UNUSED struct Camera *c, s16 frames);`

[:arrow_up_small:](#)

<br />

## [trigger_cutscene_dialog](#trigger_cutscene_dialog)

### Lua Example
`local integerValue = trigger_cutscene_dialog(trigger)`

### Parameters
| Field | Type |
| ----- | ---- |
| trigger | `integer` |

### Returns
- `integer`

### C Prototype
`s32 trigger_cutscene_dialog(s32 trigger);`

[:arrow_up_small:](#)

<br />

## [vec3f_sub](#vec3f_sub)

### Lua Example
`vec3f_sub(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Vec3f](structs.md#Vec3f) |
| src | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void vec3f_sub(Vec3f dst, Vec3f src);`

[:arrow_up_small:](#)

<br />

## [vec3f_to_object_pos](#vec3f_to_object_pos)

### Lua Example
`vec3f_to_object_pos(o, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| src | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void vec3f_to_object_pos(struct Object *o, Vec3f src);`

[:arrow_up_small:](#)

<br />

## [warp_camera](#warp_camera)

### Lua Example
`warp_camera(displacementX, displacementY, displacementZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| displacementX | `number` |
| displacementY | `number` |
| displacementZ | `number` |

### Returns
- None

### C Prototype
`void warp_camera(f32 displacementX, f32 displacementY, f32 displacementZ);`

[:arrow_up_small:](#)

<br />

---
# functions from characters.h

<br />


## [get_character](#get_character)

### Lua Example
`local CharacterValue = get_character(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
[Character](structs.md#Character)

### C Prototype
`struct Character* get_character(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [get_character_anim_offset](#get_character_anim_offset)

### Lua Example
`local numberValue = get_character_anim_offset(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `number`

### C Prototype
`f32 get_character_anim_offset(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [play_character_sound](#play_character_sound)

### Lua Example
`play_character_sound(m, characterSound)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| characterSound | [enum CharacterSound](constants.md#enum-CharacterSound) |

### Returns
- None

### C Prototype
`void play_character_sound(struct MarioState* m, enum CharacterSound characterSound);`

[:arrow_up_small:](#)

<br />

## [play_character_sound_if_no_flag](#play_character_sound_if_no_flag)

### Lua Example
`play_character_sound_if_no_flag(m, characterSound, flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| characterSound | [enum CharacterSound](constants.md#enum-CharacterSound) |
| flags | `integer` |

### Returns
- None

### C Prototype
`void play_character_sound_if_no_flag(struct MarioState* m, enum CharacterSound characterSound, u32 flags);`

[:arrow_up_small:](#)

<br />

## [play_character_sound_offset](#play_character_sound_offset)

### Lua Example
`play_character_sound_offset(m, characterSound, offset)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| characterSound | [enum CharacterSound](constants.md#enum-CharacterSound) |
| offset | `integer` |

### Returns
- None

### C Prototype
`void play_character_sound_offset(struct MarioState* m, enum CharacterSound characterSound, u32 offset);`

[:arrow_up_small:](#)

<br />

## [update_character_anim_offset](#update_character_anim_offset)

### Lua Example
`update_character_anim_offset(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_character_anim_offset(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

---
# functions from djui_chat_message.h

<br />


## [djui_chat_message_create](#djui_chat_message_create)

### Lua Example
`djui_chat_message_create(message)`

### Parameters
| Field | Type |
| ----- | ---- |
| message | `string` |

### Returns
- None

### C Prototype
`void djui_chat_message_create(const char* message);`

[:arrow_up_small:](#)

<br />

---
# functions from djui_hud_utils.h

<br />


## [djui_hud_get_mouse_x](#djui_hud_get_mouse_x)

### Lua Example
`local numberValue = djui_hud_get_mouse_x()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 djui_hud_get_mouse_x(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_mouse_y](#djui_hud_get_mouse_y)

### Lua Example
`local numberValue = djui_hud_get_mouse_y()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 djui_hud_get_mouse_y(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_raw_mouse_x](#djui_hud_get_raw_mouse_x)

### Lua Example
`local numberValue = djui_hud_get_raw_mouse_x()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 djui_hud_get_raw_mouse_x(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_raw_mouse_y](#djui_hud_get_raw_mouse_y)

### Lua Example
`local numberValue = djui_hud_get_raw_mouse_y()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 djui_hud_get_raw_mouse_y(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_screen_height](#djui_hud_get_screen_height)

### Lua Example
`local integerValue = djui_hud_get_screen_height()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 djui_hud_get_screen_height(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_screen_width](#djui_hud_get_screen_width)

### Lua Example
`local integerValue = djui_hud_get_screen_width()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 djui_hud_get_screen_width(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_measure_text](#djui_hud_measure_text)

### Lua Example
`local numberValue = djui_hud_measure_text(message)`

### Parameters
| Field | Type |
| ----- | ---- |
| message | `string` |

### Returns
- `number`

### C Prototype
`f32 djui_hud_measure_text(const char* message);`

[:arrow_up_small:](#)

<br />

## [djui_hud_print_text](#djui_hud_print_text)

### Lua Example
`djui_hud_print_text(message, x, y, scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| message | `string` |
| x | `number` |
| y | `number` |
| scale | `number` |

### Returns
- None

### C Prototype
`void djui_hud_print_text(const char* message, float x, float y, float scale);`

[:arrow_up_small:](#)

<br />

## [djui_hud_render_rect](#djui_hud_render_rect)

### Lua Example
`djui_hud_render_rect(x, y, width, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| width | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void djui_hud_render_rect(f32 x, f32 y, f32 width, f32 height);`

[:arrow_up_small:](#)

<br />

## [djui_hud_render_rect_interpolated](#djui_hud_render_rect_interpolated)

### Lua Example
`djui_hud_render_rect_interpolated(prevX, prevY, prevWidth, prevHeight, x, y, width, height)`

### Parameters
| Field | Type |
| ----- | ---- |
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
`void djui_hud_render_rect_interpolated(f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height);`

[:arrow_up_small:](#)

<br />

## [djui_hud_set_color](#djui_hud_set_color)

### Lua Example
`djui_hud_set_color(r, g, b, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| r | `integer` |
| g | `integer` |
| b | `integer` |
| a | `integer` |

### Returns
- None

### C Prototype
`void djui_hud_set_color(u8 r, u8 g, u8 b, u8 a);`

[:arrow_up_small:](#)

<br />

## [djui_hud_set_font](#djui_hud_set_font)

### Lua Example
`djui_hud_set_font(fontType)`

### Parameters
| Field | Type |
| ----- | ---- |
| fontType | [enum DjuiFontType](constants.md#enum-DjuiFontType) |

### Returns
- None

### C Prototype
`void djui_hud_set_font(enum DjuiFontType fontType);`

[:arrow_up_small:](#)

<br />

## [djui_hud_set_mouse_locked](#djui_hud_set_mouse_locked)

### Lua Example
`djui_hud_set_mouse_locked(locked)`

### Parameters
| Field | Type |
| ----- | ---- |
| locked | `boolean` |

### Returns
- None

### C Prototype
`void djui_hud_set_mouse_locked(bool locked);`

[:arrow_up_small:](#)

<br />

## [djui_hud_set_resolution](#djui_hud_set_resolution)

### Lua Example
`djui_hud_set_resolution(resolutionType)`

### Parameters
| Field | Type |
| ----- | ---- |
| resolutionType | [enum HudUtilsResolution](constants.md#enum-HudUtilsResolution) |

### Returns
- None

### C Prototype
`void djui_hud_set_resolution(enum HudUtilsResolution resolutionType);`

[:arrow_up_small:](#)

<br />

## [djui_hud_world_pos_to_screen_pos](#djui_hud_world_pos_to_screen_pos)

### Lua Example
`djui_hud_world_pos_to_screen_pos(pos, out)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| out | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void djui_hud_world_pos_to_screen_pos(Vec3f pos, Vec3f out);`

[:arrow_up_small:](#)

<br />

---
# functions from djui_popup.h

<br />


## [djui_popup_create](#djui_popup_create)

### Lua Example
`djui_popup_create(message, lines)`

### Parameters
| Field | Type |
| ----- | ---- |
| message | `string` |
| lines | `integer` |

### Returns
- None

### C Prototype
`void djui_popup_create(const char* message, int lines);`

[:arrow_up_small:](#)

<br />

---
# functions from external.h

<br />


## [fade_volume_scale](#fade_volume_scale)

### Lua Example
`fade_volume_scale(player, targetScale, fadeDuration)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| targetScale | `integer` |
| fadeDuration | `integer` |

### Returns
- None

### C Prototype
`void fade_volume_scale(u8 player, u8 targetScale, u16 fadeDuration);`

[:arrow_up_small:](#)

<br />

## [fadeout_background_music](#fadeout_background_music)

### Lua Example
`fadeout_background_music(arg0, fadeOut)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |
| fadeOut | `integer` |

### Returns
- None

### C Prototype
`void fadeout_background_music(u16 arg0, u16 fadeOut);`

[:arrow_up_small:](#)

<br />

## [get_current_background_music](#get_current_background_music)

### Lua Example
`local integerValue = get_current_background_music()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u16 get_current_background_music(void);`

[:arrow_up_small:](#)

<br />

## [get_current_background_music_default_volume](#get_current_background_music_default_volume)

### Lua Example
`local integerValue = get_current_background_music_default_volume()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 get_current_background_music_default_volume(void);`

[:arrow_up_small:](#)

<br />

## [get_current_background_music_max_target_volume](#get_current_background_music_max_target_volume)

### Lua Example
`local integerValue = get_current_background_music_max_target_volume()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 get_current_background_music_max_target_volume(void);`

[:arrow_up_small:](#)

<br />

## [get_current_background_music_target_volume](#get_current_background_music_target_volume)

### Lua Example
`local integerValue = get_current_background_music_target_volume()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 get_current_background_music_target_volume(void);`

[:arrow_up_small:](#)

<br />

## [is_current_background_music_volume_lowered](#is_current_background_music_volume_lowered)

### Lua Example
`local integerValue = is_current_background_music_volume_lowered()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 is_current_background_music_volume_lowered(void);`

[:arrow_up_small:](#)

<br />

## [play_course_clear](#play_course_clear)

### Lua Example
`play_course_clear()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_course_clear(void);`

[:arrow_up_small:](#)

<br />

## [play_dialog_sound](#play_dialog_sound)

### Lua Example
`play_dialog_sound(dialogID)`

### Parameters
| Field | Type |
| ----- | ---- |
| dialogID | `integer` |

### Returns
- None

### C Prototype
`void play_dialog_sound(u8 dialogID);`

[:arrow_up_small:](#)

<br />

## [play_music](#play_music)

### Lua Example
`play_music(player, seqArgs, fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| seqArgs | `integer` |
| fadeTimer | `integer` |

### Returns
- None

### C Prototype
`void play_music(u8 player, u16 seqArgs, u16 fadeTimer);`

[:arrow_up_small:](#)

<br />

## [play_peachs_jingle](#play_peachs_jingle)

### Lua Example
`play_peachs_jingle()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_peachs_jingle(void);`

[:arrow_up_small:](#)

<br />

## [play_power_star_jingle](#play_power_star_jingle)

### Lua Example
`play_power_star_jingle(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |

### Returns
- None

### C Prototype
`void play_power_star_jingle(u8 arg0);`

[:arrow_up_small:](#)

<br />

## [play_puzzle_jingle](#play_puzzle_jingle)

### Lua Example
`play_puzzle_jingle()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_puzzle_jingle(void);`

[:arrow_up_small:](#)

<br />

## [play_race_fanfare](#play_race_fanfare)

### Lua Example
`play_race_fanfare()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_race_fanfare(void);`

[:arrow_up_small:](#)

<br />

## [play_secondary_music](#play_secondary_music)

### Lua Example
`play_secondary_music(seqId, bgMusicVolume, volume, fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| seqId | `integer` |
| bgMusicVolume | `integer` |
| volume | `integer` |
| fadeTimer | `integer` |

### Returns
- None

### C Prototype
`void play_secondary_music(u8 seqId, u8 bgMusicVolume, u8 volume, u16 fadeTimer);`

[:arrow_up_small:](#)

<br />

## [play_sound](#play_sound)

### Lua Example
`play_sound(soundBits, pos)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundBits | `integer` |
| pos | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void play_sound(s32 soundBits, f32 *pos);`

[:arrow_up_small:](#)

<br />

## [play_sound_with_freq_scale](#play_sound_with_freq_scale)

### Lua Example
`play_sound_with_freq_scale(soundBits, pos, freqScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundBits | `integer` |
| pos | [Vec3f](structs.md#Vec3f) |
| freqScale | `number` |

### Returns
- None

### C Prototype
`void play_sound_with_freq_scale(s32 soundBits, f32* pos, f32 freqScale);`

[:arrow_up_small:](#)

<br />

## [play_star_fanfare](#play_star_fanfare)

### Lua Example
`play_star_fanfare()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_star_fanfare(void);`

[:arrow_up_small:](#)

<br />

## [play_toads_jingle](#play_toads_jingle)

### Lua Example
`play_toads_jingle()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_toads_jingle(void);`

[:arrow_up_small:](#)

<br />

## [seq_player_fade_out](#seq_player_fade_out)

### Lua Example
`seq_player_fade_out(player, fadeDuration)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| fadeDuration | `integer` |

### Returns
- None

### C Prototype
`void seq_player_fade_out(u8 player, u16 fadeDuration);`

[:arrow_up_small:](#)

<br />

## [seq_player_lower_volume](#seq_player_lower_volume)

### Lua Example
`seq_player_lower_volume(player, fadeDuration, percentage)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| fadeDuration | `integer` |
| percentage | `integer` |

### Returns
- None

### C Prototype
`void seq_player_lower_volume(u8 player, u16 fadeDuration, u8 percentage);`

[:arrow_up_small:](#)

<br />

## [seq_player_unlower_volume](#seq_player_unlower_volume)

### Lua Example
`seq_player_unlower_volume(player, fadeDuration)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| fadeDuration | `integer` |

### Returns
- None

### C Prototype
`void seq_player_unlower_volume(u8 player, u16 fadeDuration);`

[:arrow_up_small:](#)

<br />

## [stop_background_music](#stop_background_music)

### Lua Example
`stop_background_music(seqId)`

### Parameters
| Field | Type |
| ----- | ---- |
| seqId | `integer` |

### Returns
- None

### C Prototype
`void stop_background_music(u16 seqId);`

[:arrow_up_small:](#)

<br />

## [stop_sound](#stop_sound)

### Lua Example
`stop_sound(soundBits, pos)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundBits | `integer` |
| pos | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void stop_sound(u32 soundBits, f32 *pos);`

[:arrow_up_small:](#)

<br />

## [stop_sounds_from_source](#stop_sounds_from_source)

### Lua Example
`stop_sounds_from_source(pos)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void stop_sounds_from_source(f32 *pos);`

[:arrow_up_small:](#)

<br />

## [stop_sounds_in_continuous_banks](#stop_sounds_in_continuous_banks)

### Lua Example
`stop_sounds_in_continuous_banks()`

### Parameters
- None

### Returns
- None

### C Prototype
`void stop_sounds_in_continuous_banks(void);`

[:arrow_up_small:](#)

<br />

---
# functions from interaction.h

<br />


## [does_mario_have_normal_cap_on_head](#does_mario_have_normal_cap_on_head)

### Lua Example
`local integerValue = does_mario_have_normal_cap_on_head(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u32 does_mario_have_normal_cap_on_head(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [get_door_save_file_flag](#get_door_save_file_flag)

### Lua Example
`local integerValue = get_door_save_file_flag(door)`

### Parameters
| Field | Type |
| ----- | ---- |
| door | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 get_door_save_file_flag(struct Object *door);`

[:arrow_up_small:](#)

<br />

## [interact_damage](#interact_damage)

### Lua Example
`local integerValue = interact_damage(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_damage(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [mario_blow_off_cap](#mario_blow_off_cap)

### Lua Example
`mario_blow_off_cap(m, capSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| capSpeed | `number` |

### Returns
- None

### C Prototype
`void mario_blow_off_cap(struct MarioState *m, f32 capSpeed);`

[:arrow_up_small:](#)

<br />

## [mario_check_object_grab](#mario_check_object_grab)

### Lua Example
`local integerValue = mario_check_object_grab(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u32 mario_check_object_grab(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_drop_held_object](#mario_drop_held_object)

### Lua Example
`mario_drop_held_object(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void mario_drop_held_object(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_get_collided_object](#mario_get_collided_object)

### Lua Example
`local ObjectValue = mario_get_collided_object(m, interactType)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *mario_get_collided_object(struct MarioState *m, u32 interactType);`

[:arrow_up_small:](#)

<br />

## [mario_grab_used_object](#mario_grab_used_object)

### Lua Example
`mario_grab_used_object(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void mario_grab_used_object(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_lose_cap_to_enemy](#mario_lose_cap_to_enemy)

### Lua Example
`local integerValue = mario_lose_cap_to_enemy(m, arg)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| arg | `integer` |

### Returns
- `integer`

### C Prototype
`u32 mario_lose_cap_to_enemy(struct MarioState* m, u32 arg);`

[:arrow_up_small:](#)

<br />

## [mario_obj_angle_to_object](#mario_obj_angle_to_object)

### Lua Example
`local integerValue = mario_obj_angle_to_object(m, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s16 mario_obj_angle_to_object(struct MarioState *m, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [mario_retrieve_cap](#mario_retrieve_cap)

### Lua Example
`mario_retrieve_cap(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void mario_retrieve_cap(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [mario_stop_riding_and_holding](#mario_stop_riding_and_holding)

### Lua Example
`mario_stop_riding_and_holding(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void mario_stop_riding_and_holding(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_stop_riding_object](#mario_stop_riding_object)

### Lua Example
`mario_stop_riding_object(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void mario_stop_riding_object(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_throw_held_object](#mario_throw_held_object)

### Lua Example
`mario_throw_held_object(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void mario_throw_held_object(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [passes_pvp_interaction_checks](#passes_pvp_interaction_checks)

### Lua Example
`local integerValue = passes_pvp_interaction_checks(attacker, victim)`

### Parameters
| Field | Type |
| ----- | ---- |
| attacker | [MarioState](structs.md#MarioState) |
| victim | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u8 passes_pvp_interaction_checks(struct MarioState* attacker, struct MarioState* victim);`

[:arrow_up_small:](#)

<br />

## [take_damage_and_knock_back](#take_damage_and_knock_back)

### Lua Example
`local integerValue = take_damage_and_knock_back(m, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 take_damage_and_knock_back(struct MarioState *m, struct Object *o);`

[:arrow_up_small:](#)

<br />

---
# functions from level_info.h

<br />


## [get_level_name](#get_level_name)

### Lua Example
`local stringValue = get_level_name(courseNum, levelNum, areaIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| levelNum | `integer` |
| areaIndex | `integer` |

### Returns
- `string`

### C Prototype
`const char *get_level_name(s16 courseNum, s16 levelNum, s16 areaIndex);`

[:arrow_up_small:](#)

<br />

## [get_level_name_ascii](#get_level_name_ascii)

### Lua Example
`local stringValue = get_level_name_ascii(courseNum, levelNum, areaIndex, charCase)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| levelNum | `integer` |
| areaIndex | `integer` |
| charCase | `integer` |

### Returns
- `string`

### C Prototype
`const char *get_level_name_ascii(s16 courseNum, s16 levelNum, s16 areaIndex, s16 charCase);`

[:arrow_up_small:](#)

<br />

## [get_level_name_sm64](#get_level_name_sm64)

### Lua Example
`local PointerValue = get_level_name_sm64(courseNum, levelNum, areaIndex, charCase)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| levelNum | `integer` |
| areaIndex | `integer` |
| charCase | `integer` |

### Returns
- `Pointer` <`integer`>

### C Prototype
`const u8 *get_level_name_sm64(s16 courseNum, s16 levelNum, s16 areaIndex, s16 charCase);`

[:arrow_up_small:](#)

<br />

## [get_star_name](#get_star_name)

### Lua Example
`local stringValue = get_star_name(courseNum, starNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| starNum | `integer` |

### Returns
- `string`

### C Prototype
`const char *get_star_name(s16 courseNum, s16 starNum);`

[:arrow_up_small:](#)

<br />

## [get_star_name_ascii](#get_star_name_ascii)

### Lua Example
`local stringValue = get_star_name_ascii(courseNum, starNum, charCase)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| starNum | `integer` |
| charCase | `integer` |

### Returns
- `string`

### C Prototype
`const char *get_star_name_ascii(s16 courseNum, s16 starNum, s16 charCase);`

[:arrow_up_small:](#)

<br />

## [get_star_name_sm64](#get_star_name_sm64)

### Lua Example
`local PointerValue = get_star_name_sm64(courseNum, starNum, charCase)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| starNum | `integer` |
| charCase | `integer` |

### Returns
- `Pointer` <`integer`>

### C Prototype
`const u8 *get_star_name_sm64(s16 courseNum, s16 starNum, s16 charCase);`

[:arrow_up_small:](#)

<br />

---
# functions from level_update.h

<br />


## [level_trigger_warp](#level_trigger_warp)

### Lua Example
`local integerValue = level_trigger_warp(m, warpOp)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| warpOp | `integer` |

### Returns
- `integer`

### C Prototype
`s16 level_trigger_warp(struct MarioState *m, s32 warpOp);`

[:arrow_up_small:](#)

<br />

---
# functions from mario.h

<br />


## [adjust_sound_for_speed](#adjust_sound_for_speed)

### Lua Example
`adjust_sound_for_speed(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void adjust_sound_for_speed(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_common_action_exits](#check_common_action_exits)

### Lua Example
`local integerValue = check_common_action_exits(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_common_action_exits(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_common_hold_action_exits](#check_common_hold_action_exits)

### Lua Example
`local integerValue = check_common_hold_action_exits(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_common_hold_action_exits(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [drop_and_set_mario_action](#drop_and_set_mario_action)

### Lua Example
`local integerValue = drop_and_set_mario_action(m, action, actionArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| action | `integer` |
| actionArg | `integer` |

### Returns
- `integer`

### C Prototype
`s32 drop_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg);`

[:arrow_up_small:](#)

<br />

## [execute_mario_action](#execute_mario_action)

### Lua Example
`local integerValue = execute_mario_action(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s32 execute_mario_action(UNUSED struct Object *o);`

[:arrow_up_small:](#)

<br />

## [find_floor_height_relative_polar](#find_floor_height_relative_polar)

### Lua Example
`local numberValue = find_floor_height_relative_polar(m, angleFromMario, distFromMario)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| angleFromMario | `integer` |
| distFromMario | `number` |

### Returns
- `number`

### C Prototype
`f32 find_floor_height_relative_polar(struct MarioState *m, s16 angleFromMario, f32 distFromMario);`

[:arrow_up_small:](#)

<br />

## [find_floor_slope](#find_floor_slope)

### Lua Example
`local integerValue = find_floor_slope(m, yawOffset)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| yawOffset | `integer` |

### Returns
- `integer`

### C Prototype
`s16 find_floor_slope(struct MarioState *m, s16 yawOffset);`

[:arrow_up_small:](#)

<br />

## [find_mario_anim_flags_and_translation](#find_mario_anim_flags_and_translation)

### Lua Example
`local integerValue = find_mario_anim_flags_and_translation(o, yaw, translation)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| yaw | `integer` |
| translation | [Vec3s](structs.md#Vec3s) |

### Returns
- `integer`

### C Prototype
`s16 find_mario_anim_flags_and_translation(struct Object *o, s32 yaw, Vec3s translation);`

[:arrow_up_small:](#)

<br />

## [force_idle_state](#force_idle_state)

### Lua Example
`local integerValue = force_idle_state(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 force_idle_state(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [hurt_and_set_mario_action](#hurt_and_set_mario_action)

### Lua Example
`local integerValue = hurt_and_set_mario_action(m, action, actionArg, hurtCounter)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| action | `integer` |
| actionArg | `integer` |
| hurtCounter | `integer` |

### Returns
- `integer`

### C Prototype
`s32 hurt_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg, s16 hurtCounter);`

[:arrow_up_small:](#)

<br />

## [init_single_mario](#init_single_mario)

### Lua Example
`init_single_mario(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void init_single_mario(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [is_anim_at_end](#is_anim_at_end)

### Lua Example
`local integerValue = is_anim_at_end(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 is_anim_at_end(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [is_anim_past_end](#is_anim_past_end)

### Lua Example
`local integerValue = is_anim_past_end(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 is_anim_past_end(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [is_anim_past_frame](#is_anim_past_frame)

### Lua Example
`local integerValue = is_anim_past_frame(m, animFrame)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animFrame | `integer` |

### Returns
- `integer`

### C Prototype
`s32 is_anim_past_frame(struct MarioState *m, s16 animFrame);`

[:arrow_up_small:](#)

<br />

## [mario_can_bubble](#mario_can_bubble)

### Lua Example
`local booleanValue = mario_can_bubble(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `boolean`

### C Prototype
`bool mario_can_bubble(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [mario_facing_downhill](#mario_facing_downhill)

### Lua Example
`local integerValue = mario_facing_downhill(m, turnYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| turnYaw | `integer` |

### Returns
- `integer`

### C Prototype
`s32 mario_facing_downhill(struct MarioState *m, s32 turnYaw);`

[:arrow_up_small:](#)

<br />

## [mario_floor_is_slippery](#mario_floor_is_slippery)

### Lua Example
`local integerValue = mario_floor_is_slippery(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u32 mario_floor_is_slippery(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_floor_is_slope](#mario_floor_is_slope)

### Lua Example
`local integerValue = mario_floor_is_slope(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_floor_is_slope(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_floor_is_steep](#mario_floor_is_steep)

### Lua Example
`local integerValue = mario_floor_is_steep(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_floor_is_steep(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_get_floor_class](#mario_get_floor_class)

### Lua Example
`local integerValue = mario_get_floor_class(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_get_floor_class(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_get_terrain_sound_addend](#mario_get_terrain_sound_addend)

### Lua Example
`local integerValue = mario_get_terrain_sound_addend(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u32 mario_get_terrain_sound_addend(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_set_bubbled](#mario_set_bubbled)

### Lua Example
`mario_set_bubbled(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void mario_set_bubbled(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [mario_set_forward_vel](#mario_set_forward_vel)

### Lua Example
`mario_set_forward_vel(m, speed)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| speed | `number` |

### Returns
- None

### C Prototype
`void mario_set_forward_vel(struct MarioState *m, f32 speed);`

[:arrow_up_small:](#)

<br />

## [mario_update_wall](#mario_update_wall)

### Lua Example
`mario_update_wall(m, wcd)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| wcd | [WallCollisionData](structs.md#WallCollisionData) |

### Returns
- None

### C Prototype
`void mario_update_wall(struct MarioState* m, struct WallCollisionData* wcd);`

[:arrow_up_small:](#)

<br />

## [play_mario_action_sound](#play_mario_action_sound)

### Lua Example
`play_mario_action_sound(m, soundBits, waveParticleType)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| soundBits | `integer` |
| waveParticleType | `integer` |

### Returns
- None

### C Prototype
`void play_mario_action_sound(struct MarioState *m, u32 soundBits, u32 waveParticleType);`

[:arrow_up_small:](#)

<br />

## [play_mario_heavy_landing_sound](#play_mario_heavy_landing_sound)

### Lua Example
`play_mario_heavy_landing_sound(m, soundBits)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| soundBits | `integer` |

### Returns
- None

### C Prototype
`void play_mario_heavy_landing_sound(struct MarioState *m, u32 soundBits);`

[:arrow_up_small:](#)

<br />

## [play_mario_heavy_landing_sound_once](#play_mario_heavy_landing_sound_once)

### Lua Example
`play_mario_heavy_landing_sound_once(m, soundBits)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| soundBits | `integer` |

### Returns
- None

### C Prototype
`void play_mario_heavy_landing_sound_once(struct MarioState *m, u32 soundBits);`

[:arrow_up_small:](#)

<br />

## [play_mario_jump_sound](#play_mario_jump_sound)

### Lua Example
`play_mario_jump_sound(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void play_mario_jump_sound(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [play_mario_landing_sound](#play_mario_landing_sound)

### Lua Example
`play_mario_landing_sound(m, soundBits)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| soundBits | `integer` |

### Returns
- None

### C Prototype
`void play_mario_landing_sound(struct MarioState *m, u32 soundBits);`

[:arrow_up_small:](#)

<br />

## [play_mario_landing_sound_once](#play_mario_landing_sound_once)

### Lua Example
`play_mario_landing_sound_once(m, soundBits)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| soundBits | `integer` |

### Returns
- None

### C Prototype
`void play_mario_landing_sound_once(struct MarioState *m, u32 soundBits);`

[:arrow_up_small:](#)

<br />

## [play_mario_sound](#play_mario_sound)

### Lua Example
`play_mario_sound(m, primarySoundBits, scondarySoundBits)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| primarySoundBits | `integer` |
| scondarySoundBits | `integer` |

### Returns
- None

### C Prototype
`void play_mario_sound(struct MarioState *m, s32 primarySoundBits, s32 scondarySoundBits);`

[:arrow_up_small:](#)

<br />

## [play_sound_and_spawn_particles](#play_sound_and_spawn_particles)

### Lua Example
`play_sound_and_spawn_particles(m, soundBits, waveParticleType)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| soundBits | `integer` |
| waveParticleType | `integer` |

### Returns
- None

### C Prototype
`void play_sound_and_spawn_particles(struct MarioState *m, u32 soundBits, u32 waveParticleType);`

[:arrow_up_small:](#)

<br />

## [play_sound_if_no_flag](#play_sound_if_no_flag)

### Lua Example
`play_sound_if_no_flag(m, soundBits, flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| soundBits | `integer` |
| flags | `integer` |

### Returns
- None

### C Prototype
`void play_sound_if_no_flag(struct MarioState *m, u32 soundBits, u32 flags);`

[:arrow_up_small:](#)

<br />

## [resolve_and_return_wall_collisions](#resolve_and_return_wall_collisions)

### Lua Example
`local SurfaceValue = resolve_and_return_wall_collisions(pos, offset, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| offset | `number` |
| radius | `number` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface *resolve_and_return_wall_collisions(Vec3f pos, f32 offset, f32 radius);`

[:arrow_up_small:](#)

<br />

## [resolve_and_return_wall_collisions_data](#resolve_and_return_wall_collisions_data)

### Lua Example
`resolve_and_return_wall_collisions_data(pos, offset, radius, collisionData)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| offset | `number` |
| radius | `number` |
| collisionData | [WallCollisionData](structs.md#WallCollisionData) |

### Returns
- None

### C Prototype
`void resolve_and_return_wall_collisions_data(Vec3f pos, f32 offset, f32 radius, struct WallCollisionData* collisionData);`

[:arrow_up_small:](#)

<br />

## [return_mario_anim_y_translation](#return_mario_anim_y_translation)

### Lua Example
`local integerValue = return_mario_anim_y_translation(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s16 return_mario_anim_y_translation(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [set_anim_to_frame](#set_anim_to_frame)

### Lua Example
`set_anim_to_frame(m, animFrame)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animFrame | `integer` |

### Returns
- None

### C Prototype
`void set_anim_to_frame(struct MarioState *m, s16 animFrame);`

[:arrow_up_small:](#)

<br />

## [set_jump_from_landing](#set_jump_from_landing)

### Lua Example
`local integerValue = set_jump_from_landing(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 set_jump_from_landing(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [set_jumping_action](#set_jumping_action)

### Lua Example
`local integerValue = set_jumping_action(m, action, actionArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| action | `integer` |
| actionArg | `integer` |

### Returns
- `integer`

### C Prototype
`s32 set_jumping_action(struct MarioState *m, u32 action, u32 actionArg);`

[:arrow_up_small:](#)

<br />

## [set_mario_action](#set_mario_action)

### Lua Example
`local integerValue = set_mario_action(m, action, actionArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| action | `integer` |
| actionArg | `integer` |

### Returns
- `integer`

### C Prototype
`u32 set_mario_action(struct MarioState *m, u32 action, u32 actionArg);`

[:arrow_up_small:](#)

<br />

## [set_mario_anim_with_accel](#set_mario_anim_with_accel)

### Lua Example
`local integerValue = set_mario_anim_with_accel(m, targetAnimID, accel)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| targetAnimID | `integer` |
| accel | `integer` |

### Returns
- `integer`

### C Prototype
`s16 set_mario_anim_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel);`

[:arrow_up_small:](#)

<br />

## [set_mario_animation](#set_mario_animation)

### Lua Example
`local integerValue = set_mario_animation(m, targetAnimID)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| targetAnimID | `integer` |

### Returns
- `integer`

### C Prototype
`s16 set_mario_animation(struct MarioState *m, s32 targetAnimID);`

[:arrow_up_small:](#)

<br />

## [set_mario_particle_flags](#set_mario_particle_flags)

### Lua Example
`set_mario_particle_flags(m, flags, clear)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| flags | `integer` |
| clear | `integer` |

### Returns
- None

### C Prototype
`void set_mario_particle_flags(struct MarioState* m, u32 flags, u8 clear);`

[:arrow_up_small:](#)

<br />

## [set_mario_y_vel_based_on_fspeed](#set_mario_y_vel_based_on_fspeed)

### Lua Example
`set_mario_y_vel_based_on_fspeed(m, initialVelY, multiplier)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| initialVelY | `number` |
| multiplier | `number` |

### Returns
- None

### C Prototype
`void set_mario_y_vel_based_on_fspeed(struct MarioState *m, f32 initialVelY, f32 multiplier);`

[:arrow_up_small:](#)

<br />

## [set_steep_jump_action](#set_steep_jump_action)

### Lua Example
`set_steep_jump_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void set_steep_jump_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [set_water_plunge_action](#set_water_plunge_action)

### Lua Example
`local integerValue = set_water_plunge_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 set_water_plunge_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [transition_submerged_to_walking](#transition_submerged_to_walking)

### Lua Example
`local integerValue = transition_submerged_to_walking(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 transition_submerged_to_walking(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_mario_pos_for_anim](#update_mario_pos_for_anim)

### Lua Example
`update_mario_pos_for_anim(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_mario_pos_for_anim(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_mario_sound_and_camera](#update_mario_sound_and_camera)

### Lua Example
`update_mario_sound_and_camera(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_mario_sound_and_camera(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

---
# functions from mario_actions_airborne.c

<br />


## [check_common_airborne_cancels](#check_common_airborne_cancels)

### Lua Example
`local integerValue = check_common_airborne_cancels(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_common_airborne_cancels(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_fall_damage](#check_fall_damage)

### Lua Example
`local integerValue = check_fall_damage(m, hardFallAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| hardFallAction | `integer` |

### Returns
- `integer`

### C Prototype
`s32 check_fall_damage(struct MarioState *m, u32 hardFallAction);`

[:arrow_up_small:](#)

<br />

## [check_fall_damage_or_get_stuck](#check_fall_damage_or_get_stuck)

### Lua Example
`local integerValue = check_fall_damage_or_get_stuck(m, hardFallAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| hardFallAction | `integer` |

### Returns
- `integer`

### C Prototype
`s32 check_fall_damage_or_get_stuck(struct MarioState *m, u32 hardFallAction);`

[:arrow_up_small:](#)

<br />

## [check_horizontal_wind](#check_horizontal_wind)

### Lua Example
`local integerValue = check_horizontal_wind(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_horizontal_wind(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_kick_or_dive_in_air](#check_kick_or_dive_in_air)

### Lua Example
`local integerValue = check_kick_or_dive_in_air(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_kick_or_dive_in_air(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_wall_kick](#check_wall_kick)

### Lua Example
`local integerValue = check_wall_kick(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_wall_kick(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [common_air_action_step](#common_air_action_step)

### Lua Example
`local integerValue = common_air_action_step(m, landAction, animation, stepArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| landAction | `integer` |
| animation | `integer` |
| stepArg | `integer` |

### Returns
- `integer`

### C Prototype
`u32 common_air_action_step(struct MarioState *m, u32 landAction, s32 animation, u32 stepArg);`

[:arrow_up_small:](#)

<br />

## [common_air_knockback_step](#common_air_knockback_step)

### Lua Example
`local integerValue = common_air_knockback_step(m, landAction, hardFallAction, animation, speed)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| landAction | `integer` |
| hardFallAction | `integer` |
| animation | `integer` |
| speed | `number` |

### Returns
- `integer`

### C Prototype
`u32 common_air_knockback_step(struct MarioState *m, u32 landAction, u32 hardFallAction, s32 animation, f32 speed);`

[:arrow_up_small:](#)

<br />

## [lava_boost_on_wall](#lava_boost_on_wall)

### Lua Example
`local integerValue = lava_boost_on_wall(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 lava_boost_on_wall(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_execute_airborne_action](#mario_execute_airborne_action)

### Lua Example
`local integerValue = mario_execute_airborne_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_execute_airborne_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [play_far_fall_sound](#play_far_fall_sound)

### Lua Example
`play_far_fall_sound(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void play_far_fall_sound(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [play_flip_sounds](#play_flip_sounds)

### Lua Example
`play_flip_sounds(m, frame1, frame2, frame3)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| frame1 | `integer` |
| frame2 | `integer` |
| frame3 | `integer` |

### Returns
- None

### C Prototype
`void play_flip_sounds(struct MarioState *m, s16 frame1, s16 frame2, s16 frame3);`

[:arrow_up_small:](#)

<br />

## [play_knockback_sound](#play_knockback_sound)

### Lua Example
`play_knockback_sound(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void play_knockback_sound(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [should_get_stuck_in_ground](#should_get_stuck_in_ground)

### Lua Example
`local integerValue = should_get_stuck_in_ground(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 should_get_stuck_in_ground(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_air_with_turn](#update_air_with_turn)

### Lua Example
`update_air_with_turn(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_air_with_turn(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_air_without_turn](#update_air_without_turn)

### Lua Example
`update_air_without_turn(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_air_without_turn(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_flying](#update_flying)

### Lua Example
`update_flying(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_flying(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_flying_pitch](#update_flying_pitch)

### Lua Example
`update_flying_pitch(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_flying_pitch(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_flying_yaw](#update_flying_yaw)

### Lua Example
`update_flying_yaw(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_flying_yaw(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_lava_boost_or_twirling](#update_lava_boost_or_twirling)

### Lua Example
`update_lava_boost_or_twirling(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_lava_boost_or_twirling(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

---
# functions from mario_actions_automatic.c

<br />


## [add_tree_leaf_particles](#add_tree_leaf_particles)

### Lua Example
`add_tree_leaf_particles(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void add_tree_leaf_particles(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_common_automatic_cancels](#check_common_automatic_cancels)

### Lua Example
`local integerValue = check_common_automatic_cancels(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_common_automatic_cancels(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [climb_up_ledge](#climb_up_ledge)

### Lua Example
`climb_up_ledge(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void climb_up_ledge(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [let_go_of_ledge](#let_go_of_ledge)

### Lua Example
`local integerValue = let_go_of_ledge(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 let_go_of_ledge(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_execute_automatic_action](#mario_execute_automatic_action)

### Lua Example
`local integerValue = mario_execute_automatic_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_execute_automatic_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [perform_hanging_step](#perform_hanging_step)

### Lua Example
`local integerValue = perform_hanging_step(m, nextPos)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| nextPos | [Vec3f](structs.md#Vec3f) |

### Returns
- `integer`

### C Prototype
`s32 perform_hanging_step(struct MarioState *m, Vec3f nextPos);`

[:arrow_up_small:](#)

<br />

## [play_climbing_sounds](#play_climbing_sounds)

### Lua Example
`play_climbing_sounds(m, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| b | `integer` |

### Returns
- None

### C Prototype
`void play_climbing_sounds(struct MarioState *m, s32 b);`

[:arrow_up_small:](#)

<br />

## [set_pole_position](#set_pole_position)

### Lua Example
`local integerValue = set_pole_position(m, offsetY)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| offsetY | `number` |

### Returns
- `integer`

### C Prototype
`s32 set_pole_position(struct MarioState *m, f32 offsetY);`

[:arrow_up_small:](#)

<br />

## [update_hang_moving](#update_hang_moving)

### Lua Example
`local integerValue = update_hang_moving(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 update_hang_moving(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_hang_stationary](#update_hang_stationary)

### Lua Example
`update_hang_stationary(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_hang_stationary(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_ledge_climb](#update_ledge_climb)

### Lua Example
`update_ledge_climb(m, animation, endAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animation | `integer` |
| endAction | `integer` |

### Returns
- None

### C Prototype
`void update_ledge_climb(struct MarioState *m, s32 animation, u32 endAction);`

[:arrow_up_small:](#)

<br />

## [update_ledge_climb_camera](#update_ledge_climb_camera)

### Lua Example
`update_ledge_climb_camera(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_ledge_climb_camera(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

---
# functions from mario_actions_cutscene.c

<br />


## [bhv_end_peach_loop](#bhv_end_peach_loop)

### Lua Example
`bhv_end_peach_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_end_peach_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_end_toad_loop](#bhv_end_toad_loop)

### Lua Example
`bhv_end_toad_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_end_toad_loop(void);`

[:arrow_up_small:](#)

<br />

## [common_death_handler](#common_death_handler)

### Lua Example
`local integerValue = common_death_handler(m, animation, frameToDeathWarp)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animation | `integer` |
| frameToDeathWarp | `integer` |

### Returns
- `integer`

### C Prototype
`s32 common_death_handler(struct MarioState *m, s32 animation, s32 frameToDeathWarp);`

[:arrow_up_small:](#)

<br />

## [cutscene_put_cap_on](#cutscene_put_cap_on)

### Lua Example
`cutscene_put_cap_on(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void cutscene_put_cap_on(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [cutscene_take_cap_off](#cutscene_take_cap_off)

### Lua Example
`cutscene_take_cap_off(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void cutscene_take_cap_off(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [general_star_dance_handler](#general_star_dance_handler)

### Lua Example
`general_star_dance_handler(m, isInWater)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| isInWater | `integer` |

### Returns
- None

### C Prototype
`void general_star_dance_handler(struct MarioState *m, s32 isInWater);`

[:arrow_up_small:](#)

<br />

## [generate_yellow_sparkles](#generate_yellow_sparkles)

### Lua Example
`generate_yellow_sparkles(x, y, z, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `integer` |
| y | `integer` |
| z | `integer` |
| radius | `number` |

### Returns
- None

### C Prototype
`void generate_yellow_sparkles(s16 x, s16 y, s16 z, f32 radius);`

[:arrow_up_small:](#)

<br />

## [get_star_collection_dialog](#get_star_collection_dialog)

### Lua Example
`local integerValue = get_star_collection_dialog(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 get_star_collection_dialog(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [handle_save_menu](#handle_save_menu)

### Lua Example
`handle_save_menu(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void handle_save_menu(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [launch_mario_until_land](#launch_mario_until_land)

### Lua Example
`local integerValue = launch_mario_until_land(m, endAction, animation, forwardVel)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| endAction | `integer` |
| animation | `integer` |
| forwardVel | `number` |

### Returns
- `integer`

### C Prototype
`s32 launch_mario_until_land(struct MarioState *m, s32 endAction, s32 animation, f32 forwardVel);`

[:arrow_up_small:](#)

<br />

## [mario_execute_cutscene_action](#mario_execute_cutscene_action)

### Lua Example
`local integerValue = mario_execute_cutscene_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_execute_cutscene_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_ready_to_speak](#mario_ready_to_speak)

### Lua Example
`local integerValue = mario_ready_to_speak(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_ready_to_speak(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [print_displaying_credits_entry](#print_displaying_credits_entry)

### Lua Example
`print_displaying_credits_entry()`

### Parameters
- None

### Returns
- None

### C Prototype
`void print_displaying_credits_entry(void);`

[:arrow_up_small:](#)

<br />

## [should_start_or_continue_dialog](#should_start_or_continue_dialog)

### Lua Example
`local integerValue = should_start_or_continue_dialog(m, object)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| object | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u8 should_start_or_continue_dialog(struct MarioState* m, struct Object* object);`

[:arrow_up_small:](#)

<br />

## [stuck_in_ground_handler](#stuck_in_ground_handler)

### Lua Example
`stuck_in_ground_handler(m, animation, unstuckFrame, target2, target3, endAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animation | `integer` |
| unstuckFrame | `integer` |
| target2 | `integer` |
| target3 | `integer` |
| endAction | `integer` |

### Returns
- None

### C Prototype
`void stuck_in_ground_handler(struct MarioState *m, s32 animation, s32 unstuckFrame, s32 target2, s32 target3, s32 endAction);`

[:arrow_up_small:](#)

<br />

---
# functions from mario_actions_moving.c

<br />


## [align_with_floor](#align_with_floor)

### Lua Example
`align_with_floor(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void align_with_floor(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [analog_stick_held_back](#analog_stick_held_back)

### Lua Example
`local integerValue = analog_stick_held_back(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 analog_stick_held_back(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [anim_and_audio_for_heavy_walk](#anim_and_audio_for_heavy_walk)

### Lua Example
`anim_and_audio_for_heavy_walk(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void anim_and_audio_for_heavy_walk(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [anim_and_audio_for_hold_walk](#anim_and_audio_for_hold_walk)

### Lua Example
`anim_and_audio_for_hold_walk(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void anim_and_audio_for_hold_walk(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [anim_and_audio_for_walk](#anim_and_audio_for_walk)

### Lua Example
`anim_and_audio_for_walk(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void anim_and_audio_for_walk(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [apply_landing_accel](#apply_landing_accel)

### Lua Example
`local integerValue = apply_landing_accel(m, frictionFactor)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| frictionFactor | `number` |

### Returns
- `integer`

### C Prototype
`s32 apply_landing_accel(struct MarioState *m, f32 frictionFactor);`

[:arrow_up_small:](#)

<br />

## [apply_slope_accel](#apply_slope_accel)

### Lua Example
`apply_slope_accel(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void apply_slope_accel(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [apply_slope_decel](#apply_slope_decel)

### Lua Example
`local integerValue = apply_slope_decel(m, decelCoef)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| decelCoef | `number` |

### Returns
- `integer`

### C Prototype
`s32 apply_slope_decel(struct MarioState *m, f32 decelCoef);`

[:arrow_up_small:](#)

<br />

## [begin_braking_action](#begin_braking_action)

### Lua Example
`local integerValue = begin_braking_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 begin_braking_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [begin_walking_action](#begin_walking_action)

### Lua Example
`local integerValue = begin_walking_action(m, forwardVel, action, actionArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| forwardVel | `number` |
| action | `integer` |
| actionArg | `integer` |

### Returns
- `integer`

### C Prototype
`s32 begin_walking_action(struct MarioState *m, f32 forwardVel, u32 action, u32 actionArg);`

[:arrow_up_small:](#)

<br />

## [check_common_moving_cancels](#check_common_moving_cancels)

### Lua Example
`local integerValue = check_common_moving_cancels(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_common_moving_cancels(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_ground_dive_or_punch](#check_ground_dive_or_punch)

### Lua Example
`local integerValue = check_ground_dive_or_punch(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_ground_dive_or_punch(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_ledge_climb_down](#check_ledge_climb_down)

### Lua Example
`check_ledge_climb_down(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void check_ledge_climb_down(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [common_ground_knockback_action](#common_ground_knockback_action)

### Lua Example
`local integerValue = common_ground_knockback_action(m, animation, arg2, arg3, arg4)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animation | `integer` |
| arg2 | `integer` |
| arg3 | `integer` |
| arg4 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 common_ground_knockback_action(struct MarioState *m, s32 animation, s32 arg2, s32 arg3, s32 arg4);`

[:arrow_up_small:](#)

<br />

## [common_landing_action](#common_landing_action)

### Lua Example
`local integerValue = common_landing_action(m, animation, airAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animation | `integer` |
| airAction | `integer` |

### Returns
- `integer`

### C Prototype
`u32 common_landing_action(struct MarioState *m, s16 animation, u32 airAction);`

[:arrow_up_small:](#)

<br />

## [common_slide_action](#common_slide_action)

### Lua Example
`common_slide_action(m, endAction, airAction, animation)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| endAction | `integer` |
| airAction | `integer` |
| animation | `integer` |

### Returns
- None

### C Prototype
`void common_slide_action(struct MarioState *m, u32 endAction, u32 airAction, s32 animation);`

[:arrow_up_small:](#)

<br />

## [common_slide_action_with_jump](#common_slide_action_with_jump)

### Lua Example
`local integerValue = common_slide_action_with_jump(m, stopAction, jumpAction, airAction, animation)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| stopAction | `integer` |
| jumpAction | `integer` |
| airAction | `integer` |
| animation | `integer` |

### Returns
- `integer`

### C Prototype
`s32 common_slide_action_with_jump(struct MarioState *m, u32 stopAction, u32 jumpAction, u32 airAction, s32 animation);`

[:arrow_up_small:](#)

<br />

## [mario_execute_moving_action](#mario_execute_moving_action)

### Lua Example
`local integerValue = mario_execute_moving_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_execute_moving_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [play_step_sound](#play_step_sound)

### Lua Example
`play_step_sound(m, frame1, frame2)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| frame1 | `integer` |
| frame2 | `integer` |

### Returns
- None

### C Prototype
`void play_step_sound(struct MarioState *m, s16 frame1, s16 frame2);`

[:arrow_up_small:](#)

<br />

## [push_or_sidle_wall](#push_or_sidle_wall)

### Lua Example
`push_or_sidle_wall(m, startPos)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| startPos | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void push_or_sidle_wall(struct MarioState *m, Vec3f startPos);`

[:arrow_up_small:](#)

<br />

## [quicksand_jump_land_action](#quicksand_jump_land_action)

### Lua Example
`local integerValue = quicksand_jump_land_action(m, animation1, animation2, endAction, airAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animation1 | `integer` |
| animation2 | `integer` |
| endAction | `integer` |
| airAction | `integer` |

### Returns
- `integer`

### C Prototype
`s32 quicksand_jump_land_action(struct MarioState *m, s32 animation1, s32 animation2, u32 endAction, u32 airAction);`

[:arrow_up_small:](#)

<br />

## [set_triple_jump_action](#set_triple_jump_action)

### Lua Example
`local integerValue = set_triple_jump_action(m, action, actionArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| action | `integer` |
| actionArg | `integer` |

### Returns
- `integer`

### C Prototype
`s32 set_triple_jump_action(struct MarioState *m, UNUSED u32 action, UNUSED u32 actionArg);`

[:arrow_up_small:](#)

<br />

## [should_begin_sliding](#should_begin_sliding)

### Lua Example
`local integerValue = should_begin_sliding(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 should_begin_sliding(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [slide_bonk](#slide_bonk)

### Lua Example
`slide_bonk(m, fastAction, slowAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| fastAction | `integer` |
| slowAction | `integer` |

### Returns
- None

### C Prototype
`void slide_bonk(struct MarioState *m, u32 fastAction, u32 slowAction);`

[:arrow_up_small:](#)

<br />

## [stomach_slide_action](#stomach_slide_action)

### Lua Example
`local integerValue = stomach_slide_action(m, stopAction, airAction, animation)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| stopAction | `integer` |
| airAction | `integer` |
| animation | `integer` |

### Returns
- `integer`

### C Prototype
`s32 stomach_slide_action(struct MarioState *m, u32 stopAction, u32 airAction, s32 animation);`

[:arrow_up_small:](#)

<br />

## [tilt_body_butt_slide](#tilt_body_butt_slide)

### Lua Example
`tilt_body_butt_slide(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void tilt_body_butt_slide(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [tilt_body_ground_shell](#tilt_body_ground_shell)

### Lua Example
`tilt_body_ground_shell(m, startYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| startYaw | `integer` |

### Returns
- None

### C Prototype
`void tilt_body_ground_shell(struct MarioState *m, s16 startYaw);`

[:arrow_up_small:](#)

<br />

## [tilt_body_running](#tilt_body_running)

### Lua Example
`local integerValue = tilt_body_running(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s16 tilt_body_running(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [tilt_body_walking](#tilt_body_walking)

### Lua Example
`tilt_body_walking(m, startYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| startYaw | `integer` |

### Returns
- None

### C Prototype
`void tilt_body_walking(struct MarioState *m, s16 startYaw);`

[:arrow_up_small:](#)

<br />

## [update_decelerating_speed](#update_decelerating_speed)

### Lua Example
`local integerValue = update_decelerating_speed(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 update_decelerating_speed(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_shell_speed](#update_shell_speed)

### Lua Example
`update_shell_speed(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_shell_speed(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [update_sliding](#update_sliding)

### Lua Example
`local integerValue = update_sliding(m, stopSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| stopSpeed | `number` |

### Returns
- `integer`

### C Prototype
`s32 update_sliding(struct MarioState *m, f32 stopSpeed);`

[:arrow_up_small:](#)

<br />

## [update_sliding_angle](#update_sliding_angle)

### Lua Example
`update_sliding_angle(m, accel, lossFactor)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| accel | `number` |
| lossFactor | `number` |

### Returns
- None

### C Prototype
`void update_sliding_angle(struct MarioState *m, f32 accel, f32 lossFactor);`

[:arrow_up_small:](#)

<br />

## [update_walking_speed](#update_walking_speed)

### Lua Example
`update_walking_speed(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void update_walking_speed(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

---
# functions from mario_actions_object.c

<br />


## [animated_stationary_ground_step](#animated_stationary_ground_step)

### Lua Example
`animated_stationary_ground_step(m, animation, endAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animation | `integer` |
| endAction | `integer` |

### Returns
- None

### C Prototype
`void animated_stationary_ground_step(struct MarioState *m, s32 animation, u32 endAction);`

[:arrow_up_small:](#)

<br />

## [check_common_object_cancels](#check_common_object_cancels)

### Lua Example
`local integerValue = check_common_object_cancels(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_common_object_cancels(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_execute_object_action](#mario_execute_object_action)

### Lua Example
`local integerValue = mario_execute_object_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_execute_object_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_update_punch_sequence](#mario_update_punch_sequence)

### Lua Example
`local integerValue = mario_update_punch_sequence(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_update_punch_sequence(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

---
# functions from mario_actions_stationary.c

<br />


## [check_common_hold_idle_cancels](#check_common_hold_idle_cancels)

### Lua Example
`local integerValue = check_common_hold_idle_cancels(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_common_hold_idle_cancels(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_common_idle_cancels](#check_common_idle_cancels)

### Lua Example
`local integerValue = check_common_idle_cancels(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_common_idle_cancels(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [check_common_landing_cancels](#check_common_landing_cancels)

### Lua Example
`local integerValue = check_common_landing_cancels(m, action)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| action | `integer` |

### Returns
- `integer`

### C Prototype
`s32 check_common_landing_cancels(struct MarioState *m, u32 action);`

[:arrow_up_small:](#)

<br />

## [check_common_stationary_cancels](#check_common_stationary_cancels)

### Lua Example
`local integerValue = check_common_stationary_cancels(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 check_common_stationary_cancels(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [landing_step](#landing_step)

### Lua Example
`local integerValue = landing_step(m, arg1, action)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| arg1 | `integer` |
| action | `integer` |

### Returns
- `integer`

### C Prototype
`s32 landing_step(struct MarioState *m, s32 arg1, u32 action);`

[:arrow_up_small:](#)

<br />

## [mario_execute_stationary_action](#mario_execute_stationary_action)

### Lua Example
`local integerValue = mario_execute_stationary_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_execute_stationary_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [play_anim_sound](#play_anim_sound)

### Lua Example
`play_anim_sound(m, actionState, animFrame, sound)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| actionState | `integer` |
| animFrame | `integer` |
| sound | `integer` |

### Returns
- None

### C Prototype
`void play_anim_sound(struct MarioState *m, u32 actionState, s32 animFrame, u32 sound);`

[:arrow_up_small:](#)

<br />

## [stopping_step](#stopping_step)

### Lua Example
`stopping_step(m, animID, action)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animID | `integer` |
| action | `integer` |

### Returns
- None

### C Prototype
`void stopping_step(struct MarioState *m, s32 animID, u32 action);`

[:arrow_up_small:](#)

<br />

---
# functions from mario_actions_submerged.c

<br />


## [apply_water_current](#apply_water_current)

### Lua Example
`apply_water_current(m, step)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| step | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void apply_water_current(struct MarioState *m, Vec3f step);`

[:arrow_up_small:](#)

<br />

## [float_surface_gfx](#float_surface_gfx)

### Lua Example
`float_surface_gfx(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void float_surface_gfx(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_execute_submerged_action](#mario_execute_submerged_action)

### Lua Example
`local integerValue = mario_execute_submerged_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_execute_submerged_action(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [perform_water_full_step](#perform_water_full_step)

### Lua Example
`local integerValue = perform_water_full_step(m, nextPos)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| nextPos | [Vec3f](structs.md#Vec3f) |

### Returns
- `integer`

### C Prototype
`u32 perform_water_full_step(struct MarioState *m, Vec3f nextPos);`

[:arrow_up_small:](#)

<br />

## [perform_water_step](#perform_water_step)

### Lua Example
`local integerValue = perform_water_step(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u32 perform_water_step(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [set_swimming_at_surface_particles](#set_swimming_at_surface_particles)

### Lua Example
`set_swimming_at_surface_particles(m, particleFlag)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| particleFlag | `integer` |

### Returns
- None

### C Prototype
`void set_swimming_at_surface_particles(struct MarioState *m, u32 particleFlag);`

[:arrow_up_small:](#)

<br />

---
# functions from mario_misc.h

<br />


## [bhv_toad_message_init](#bhv_toad_message_init)

### Lua Example
`bhv_toad_message_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_toad_message_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_toad_message_loop](#bhv_toad_message_loop)

### Lua Example
`bhv_toad_message_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_toad_message_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_unlock_door_star_init](#bhv_unlock_door_star_init)

### Lua Example
`bhv_unlock_door_star_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_unlock_door_star_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_unlock_door_star_loop](#bhv_unlock_door_star_loop)

### Lua Example
`bhv_unlock_door_star_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_unlock_door_star_loop(void);`

[:arrow_up_small:](#)

<br />

---
# functions from mario_step.h

<br />


## [get_additive_y_vel_for_jumps](#get_additive_y_vel_for_jumps)

### Lua Example
`local numberValue = get_additive_y_vel_for_jumps()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_additive_y_vel_for_jumps(void);`

[:arrow_up_small:](#)

<br />

## [init_bully_collision_data](#init_bully_collision_data)

### Lua Example
`init_bully_collision_data(data, posX, posZ, forwardVel, yaw, conversionRatio, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| data | [BullyCollisionData](structs.md#BullyCollisionData) |
| posX | `number` |
| posZ | `number` |
| forwardVel | `number` |
| yaw | `integer` |
| conversionRatio | `number` |
| radius | `number` |

### Returns
- None

### C Prototype
`void init_bully_collision_data(struct BullyCollisionData *data, f32 posX, f32 posZ, f32 forwardVel, s16 yaw, f32 conversionRatio, f32 radius);`

[:arrow_up_small:](#)

<br />

## [mario_bonk_reflection](#mario_bonk_reflection)

### Lua Example
`mario_bonk_reflection(arg0, arg1)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |
| arg1 | `integer` |

### Returns
- None

### C Prototype
`void mario_bonk_reflection(struct MarioState *, u32);`

[:arrow_up_small:](#)

<br />

## [mario_push_off_steep_floor](#mario_push_off_steep_floor)

### Lua Example
`local integerValue = mario_push_off_steep_floor(arg0, arg1, arg2)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |
| arg1 | `integer` |
| arg2 | `integer` |

### Returns
- `integer`

### C Prototype
`u32 mario_push_off_steep_floor(struct MarioState *, u32, u32);`

[:arrow_up_small:](#)

<br />

## [mario_update_moving_sand](#mario_update_moving_sand)

### Lua Example
`local integerValue = mario_update_moving_sand(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u32 mario_update_moving_sand(struct MarioState *);`

[:arrow_up_small:](#)

<br />

## [mario_update_quicksand](#mario_update_quicksand)

### Lua Example
`local integerValue = mario_update_quicksand(arg0, arg1)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |
| arg1 | `number` |

### Returns
- `integer`

### C Prototype
`u32 mario_update_quicksand(struct MarioState *, f32);`

[:arrow_up_small:](#)

<br />

## [mario_update_windy_ground](#mario_update_windy_ground)

### Lua Example
`local integerValue = mario_update_windy_ground(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u32 mario_update_windy_ground(struct MarioState *);`

[:arrow_up_small:](#)

<br />

## [perform_air_step](#perform_air_step)

### Lua Example
`local integerValue = perform_air_step(arg0, arg1)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |
| arg1 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 perform_air_step(struct MarioState *, u32);`

[:arrow_up_small:](#)

<br />

## [perform_ground_step](#perform_ground_step)

### Lua Example
`local integerValue = perform_ground_step(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 perform_ground_step(struct MarioState *);`

[:arrow_up_small:](#)

<br />

## [set_vel_from_pitch_and_yaw](#set_vel_from_pitch_and_yaw)

### Lua Example
`set_vel_from_pitch_and_yaw(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void set_vel_from_pitch_and_yaw(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [stationary_ground_step](#stationary_ground_step)

### Lua Example
`local integerValue = stationary_ground_step(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 stationary_ground_step(struct MarioState *);`

[:arrow_up_small:](#)

<br />

## [stop_and_set_height_to_floor](#stop_and_set_height_to_floor)

### Lua Example
`stop_and_set_height_to_floor(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void stop_and_set_height_to_floor(struct MarioState *);`

[:arrow_up_small:](#)

<br />

---
# functions from math_util.h

<br />


## [anim_spline_poll](#anim_spline_poll)

### Lua Example
`local integerValue = anim_spline_poll(m, result)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| result | [Vec3f](structs.md#Vec3f) |

### Returns
- `integer`

### C Prototype
`s32 anim_spline_poll(struct MarioState* m, Vec3f result);`

[:arrow_up_small:](#)

<br />

## [approach_f32](#approach_f32)

### Lua Example
`local numberValue = approach_f32(current, target, inc, dec)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `number` |
| target | `number` |
| inc | `number` |
| dec | `number` |

### Returns
- `number`

### C Prototype
`f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec);`

[:arrow_up_small:](#)

<br />

## [approach_s32](#approach_s32)

### Lua Example
`local integerValue = approach_s32(current, target, inc, dec)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `integer` |
| target | `integer` |
| inc | `integer` |
| dec | `integer` |

### Returns
- `integer`

### C Prototype
`s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec);`

[:arrow_up_small:](#)

<br />

## [not_zero](#not_zero)

### Lua Example
`local numberValue = not_zero(value, replacement)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `number` |
| replacement | `number` |

### Returns
- `number`

### C Prototype
`f32 not_zero(f32 value, f32 replacement);`

[:arrow_up_small:](#)

<br />

## [vec3f_combine](#vec3f_combine)

### Lua Example
`vec3f_combine(dest, vecA, vecB, sclA, sclB)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| vecA | [Vec3f](structs.md#Vec3f) |
| vecB | [Vec3f](structs.md#Vec3f) |
| sclA | `number` |
| sclB | `number` |

### Returns
- None

### C Prototype
`void vec3f_combine(Vec3f dest, Vec3f vecA, Vec3f vecB, f32 sclA, f32 sclB);`

[:arrow_up_small:](#)

<br />

## [vec3f_dist](#vec3f_dist)

### Lua Example
`local numberValue = vec3f_dist(v1, v2)`

### Parameters
| Field | Type |
| ----- | ---- |
| v1 | [Vec3f](structs.md#Vec3f) |
| v2 | [Vec3f](structs.md#Vec3f) |

### Returns
- `number`

### C Prototype
`f32 vec3f_dist(Vec3f v1, Vec3f v2);`

[:arrow_up_small:](#)

<br />

## [vec3f_dot](#vec3f_dot)

### Lua Example
`local numberValue = vec3f_dot(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `number`

### C Prototype
`f32 vec3f_dot(Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [vec3f_get_dist_and_angle](#vec3f_get_dist_and_angle)

### Lua Example
`vec3f_get_dist_and_angle(from, to, dist, pitch, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| dist | `Pointer` <`number`> |
| pitch | `Pointer` <`integer`> |
| yaw | `Pointer` <`integer`> |

### Returns
- None

### C Prototype
`void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, s16 *pitch, s16 *yaw);`

[:arrow_up_small:](#)

<br />

## [vec3f_length](#vec3f_length)

### Lua Example
`local numberValue = vec3f_length(a)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | [Vec3f](structs.md#Vec3f) |

### Returns
- `number`

### C Prototype
`f32 vec3f_length(Vec3f a);`

[:arrow_up_small:](#)

<br />

## [vec3f_project](#vec3f_project)

### Lua Example
`vec3f_project(vec, onto, out)`

### Parameters
| Field | Type |
| ----- | ---- |
| vec | [Vec3f](structs.md#Vec3f) |
| onto | [Vec3f](structs.md#Vec3f) |
| out | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void vec3f_project(Vec3f vec, Vec3f onto, Vec3f out);`

[:arrow_up_small:](#)

<br />

## [vec3f_set_dist_and_angle](#vec3f_set_dist_and_angle)

### Lua Example
`vec3f_set_dist_and_angle(from, to, dist, pitch, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| dist | `number` |
| pitch | `integer` |
| yaw | `integer` |

### Returns
- None

### C Prototype
`void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32 dist, s16 pitch, s16 yaw);`

[:arrow_up_small:](#)

<br />

---
# functions from misc.h

<br />


## [update_all_mario_stars](#update_all_mario_stars)

### Lua Example
`update_all_mario_stars()`

### Parameters
- None

### Returns
- None

### C Prototype
`void update_all_mario_stars(void);`

[:arrow_up_small:](#)

<br />

---
# functions from mod_storage.h

<br />


## [mod_storage_load](#mod_storage_load)

### Lua Example
`local stringValue = mod_storage_load(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `string`

### C Prototype
`const char *mod_storage_load(const char *key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_save](#mod_storage_save)

### Lua Example
`local booleanValue = mod_storage_save(key, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |
| value | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_save(const char *key, const char *value);`

[:arrow_up_small:](#)

<br />

---
# functions from network_player.h

<br />


## [get_network_player_from_area](#get_network_player_from_area)

### Lua Example
`local NetworkPlayerValue = get_network_player_from_area(courseNum, actNum, levelNum, areaIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |
| levelNum | `integer` |
| areaIndex | `integer` |

### Returns
[NetworkPlayer](structs.md#NetworkPlayer)

### C Prototype
`struct NetworkPlayer* get_network_player_from_area(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex);`

[:arrow_up_small:](#)

<br />

## [get_network_player_from_level](#get_network_player_from_level)

### Lua Example
`local NetworkPlayerValue = get_network_player_from_level(courseNum, actNum, levelNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |
| levelNum | `integer` |

### Returns
[NetworkPlayer](structs.md#NetworkPlayer)

### C Prototype
`struct NetworkPlayer* get_network_player_from_level(s16 courseNum, s16 actNum, s16 levelNum);`

[:arrow_up_small:](#)

<br />

## [get_network_player_smallest_global](#get_network_player_smallest_global)

### Lua Example
`local NetworkPlayerValue = get_network_player_smallest_global()`

### Parameters
- None

### Returns
[NetworkPlayer](structs.md#NetworkPlayer)

### C Prototype
`struct NetworkPlayer* get_network_player_smallest_global(void);`

[:arrow_up_small:](#)

<br />

## [network_player_color_to_palette](#network_player_color_to_palette)

### Lua Example
`network_player_color_to_palette(np, part, color)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |
| part | [enum PlayerParts](constants.md#enum-PlayerParts) |
| color | `Color` |

### Returns
- None

### C Prototype
`void network_player_color_to_palette(struct NetworkPlayer *np, enum PlayerParts part, Color color);`

[:arrow_up_small:](#)

<br />

## [network_player_connected_count](#network_player_connected_count)

### Lua Example
`local integerValue = network_player_connected_count()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 network_player_connected_count(void);`

[:arrow_up_small:](#)

<br />

## [network_player_from_global_index](#network_player_from_global_index)

### Lua Example
`local NetworkPlayerValue = network_player_from_global_index(globalIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| globalIndex | `integer` |

### Returns
[NetworkPlayer](structs.md#NetworkPlayer)

### C Prototype
`struct NetworkPlayer* network_player_from_global_index(u8 globalIndex);`

[:arrow_up_small:](#)

<br />

## [network_player_palette_to_color](#network_player_palette_to_color)

### Lua Example
`network_player_palette_to_color(np, part, out)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |
| part | [enum PlayerParts](constants.md#enum-PlayerParts) |
| out | `Color` |

### Returns
- None

### C Prototype
`void network_player_palette_to_color(struct NetworkPlayer *np, enum PlayerParts part, Color out);`

[:arrow_up_small:](#)

<br />

## [network_player_set_description](#network_player_set_description)

### Lua Example
`network_player_set_description(np, description, r, g, b, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |
| description | `string` |
| r | `integer` |
| g | `integer` |
| b | `integer` |
| a | `integer` |

### Returns
- None

### C Prototype
`void network_player_set_description(struct NetworkPlayer* np, const char* description, u8 r, u8 g, u8 b, u8 a);`

[:arrow_up_small:](#)

<br />

---
# functions from network_utils.h

<br />


## [network_discord_id_from_local_index](#network_discord_id_from_local_index)

### Lua Example
`local stringValue = network_discord_id_from_local_index(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `string`

### C Prototype
`char* network_discord_id_from_local_index(u8 localIndex);`

[:arrow_up_small:](#)

<br />

## [network_get_player_text_color_string](#network_get_player_text_color_string)

### Lua Example
`local stringValue = network_get_player_text_color_string(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `string`

### C Prototype
`char* network_get_player_text_color_string(u8 localIndex);`

[:arrow_up_small:](#)

<br />

## [network_global_index_from_local](#network_global_index_from_local)

### Lua Example
`local integerValue = network_global_index_from_local(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u8 network_global_index_from_local(u8 localIndex);`

[:arrow_up_small:](#)

<br />

## [network_is_moderator](#network_is_moderator)

### Lua Example
`local booleanValue = network_is_moderator()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool network_is_moderator(void);`

[:arrow_up_small:](#)

<br />

## [network_is_server](#network_is_server)

### Lua Example
`local booleanValue = network_is_server()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool network_is_server(void);`

[:arrow_up_small:](#)

<br />

## [network_local_index_from_global](#network_local_index_from_global)

### Lua Example
`local integerValue = network_local_index_from_global(globalIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| globalIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u8 network_local_index_from_global(u8 globalIndex);`

[:arrow_up_small:](#)

<br />

---
# functions from obj_behaviors.c

<br />


## [absf_2](#absf_2)

### Lua Example
`local numberValue = absf_2(f)`

### Parameters
| Field | Type |
| ----- | ---- |
| f | `number` |

### Returns
- `number`

### C Prototype
`f32 absf_2(f32 f);`

[:arrow_up_small:](#)

<br />

## [calc_new_obj_vel_and_pos_y](#calc_new_obj_vel_and_pos_y)

### Lua Example
`calc_new_obj_vel_and_pos_y(objFloor, objFloorY, objVelX, objVelZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| objFloor | [Surface](structs.md#Surface) |
| objFloorY | `number` |
| objVelX | `number` |
| objVelZ | `number` |

### Returns
- None

### C Prototype
`void calc_new_obj_vel_and_pos_y(struct Surface *objFloor, f32 objFloorY, f32 objVelX, f32 objVelZ);`

[:arrow_up_small:](#)

<br />

## [calc_new_obj_vel_and_pos_y_underwater](#calc_new_obj_vel_and_pos_y_underwater)

### Lua Example
`calc_new_obj_vel_and_pos_y_underwater(objFloor, floorY, objVelX, objVelZ, waterY)`

### Parameters
| Field | Type |
| ----- | ---- |
| objFloor | [Surface](structs.md#Surface) |
| floorY | `number` |
| objVelX | `number` |
| objVelZ | `number` |
| waterY | `number` |

### Returns
- None

### C Prototype
`void calc_new_obj_vel_and_pos_y_underwater(struct Surface *objFloor, f32 floorY, f32 objVelX, f32 objVelZ, f32 waterY);`

[:arrow_up_small:](#)

<br />

## [calc_obj_friction](#calc_obj_friction)

### Lua Example
`calc_obj_friction(objFriction, floor_nY)`

### Parameters
| Field | Type |
| ----- | ---- |
| objFriction | `Pointer` <`number`> |
| floor_nY | `number` |

### Returns
- None

### C Prototype
`void calc_obj_friction(f32 *objFriction, f32 floor_nY);`

[:arrow_up_small:](#)

<br />

## [current_mario_room_check](#current_mario_room_check)

### Lua Example
`local integerValue = current_mario_room_check(room)`

### Parameters
| Field | Type |
| ----- | ---- |
| room | `integer` |

### Returns
- `integer`

### C Prototype
`s8 current_mario_room_check(s16 room);`

[:arrow_up_small:](#)

<br />

## [is_nearest_mario_state_to_object](#is_nearest_mario_state_to_object)

### Lua Example
`local integerValue = is_nearest_mario_state_to_object(m, obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| obj | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u8 is_nearest_mario_state_to_object(struct MarioState *m, struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [is_nearest_player_to_object](#is_nearest_player_to_object)

### Lua Example
`local integerValue = is_nearest_player_to_object(m, obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [Object](structs.md#Object) |
| obj | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u8 is_nearest_player_to_object(struct Object *m, struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [is_other_player_active](#is_other_player_active)

### Lua Example
`local integerValue = is_other_player_active()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 is_other_player_active(void);`

[:arrow_up_small:](#)

<br />

## [is_player_active](#is_player_active)

### Lua Example
`local integerValue = is_player_active(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u8 is_player_active(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [is_player_in_local_area](#is_player_in_local_area)

### Lua Example
`local integerValue = is_player_in_local_area(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u8 is_player_in_local_area(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [is_point_close_to_object](#is_point_close_to_object)

### Lua Example
`local integerValue = is_point_close_to_object(obj, x, y, z, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| x | `number` |
| y | `number` |
| z | `number` |
| dist | `integer` |

### Returns
- `integer`

### C Prototype
`s8 is_point_close_to_object(struct Object *obj, f32 x, f32 y, f32 z, s32 dist);`

[:arrow_up_small:](#)

<br />

## [is_point_within_radius_of_mario](#is_point_within_radius_of_mario)

### Lua Example
`local integerValue = is_point_within_radius_of_mario(x, y, z, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |
| dist | `integer` |

### Returns
- `integer`

### C Prototype
`s8 is_point_within_radius_of_mario(f32 x, f32 y, f32 z, s32 dist);`

[:arrow_up_small:](#)

<br />

## [nearest_interacting_mario_state_to_object](#nearest_interacting_mario_state_to_object)

### Lua Example
`local MarioStateValue = nearest_interacting_mario_state_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[MarioState](structs.md#MarioState)

### C Prototype
`struct MarioState *nearest_interacting_mario_state_to_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [nearest_interacting_player_to_object](#nearest_interacting_player_to_object)

### Lua Example
`local ObjectValue = nearest_interacting_player_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *nearest_interacting_player_to_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [nearest_mario_state_to_object](#nearest_mario_state_to_object)

### Lua Example
`local MarioStateValue = nearest_mario_state_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[MarioState](structs.md#MarioState)

### C Prototype
`struct MarioState* nearest_mario_state_to_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [nearest_player_to_object](#nearest_player_to_object)

### Lua Example
`local ObjectValue = nearest_player_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* nearest_player_to_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_check_floor_death](#obj_check_floor_death)

### Lua Example
`obj_check_floor_death(collisionFlags, floor)`

### Parameters
| Field | Type |
| ----- | ---- |
| collisionFlags | `integer` |
| floor | [Surface](structs.md#Surface) |

### Returns
- None

### C Prototype
`void obj_check_floor_death(s16 collisionFlags, struct Surface *floor);`

[:arrow_up_small:](#)

<br />

## [obj_check_if_facing_toward_angle](#obj_check_if_facing_toward_angle)

### Lua Example
`local integerValue = obj_check_if_facing_toward_angle(base, goal, range)`

### Parameters
| Field | Type |
| ----- | ---- |
| base | `integer` |
| goal | `integer` |
| range | `integer` |

### Returns
- `integer`

### C Prototype
`s8 obj_check_if_facing_toward_angle(u32 base, u32 goal, s16 range);`

[:arrow_up_small:](#)

<br />

## [obj_find_wall](#obj_find_wall)

### Lua Example
`local integerValue = obj_find_wall(objNewX, objY, objNewZ, objVelX, objVelZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| objNewX | `number` |
| objY | `number` |
| objNewZ | `number` |
| objVelX | `number` |
| objVelZ | `number` |

### Returns
- `integer`

### C Prototype
`s8 obj_find_wall(f32 objNewX, f32 objY, f32 objNewZ, f32 objVelX, f32 objVelZ);`

[:arrow_up_small:](#)

<br />

## [obj_find_wall_displacement](#obj_find_wall_displacement)

### Lua Example
`local integerValue = obj_find_wall_displacement(dist, x, y, z, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| dist | [Vec3f](structs.md#Vec3f) |
| x | `number` |
| y | `number` |
| z | `number` |
| radius | `number` |

### Returns
- `integer`

### C Prototype
`s8 obj_find_wall_displacement(Vec3f dist, f32 x, f32 y, f32 z, f32 radius);`

[:arrow_up_small:](#)

<br />

## [obj_flicker_and_disappear](#obj_flicker_and_disappear)

### Lua Example
`local integerValue = obj_flicker_and_disappear(obj, lifeSpan)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| lifeSpan | `integer` |

### Returns
- `integer`

### C Prototype
`s8 obj_flicker_and_disappear(struct Object *obj, s16 lifeSpan);`

[:arrow_up_small:](#)

<br />

## [obj_lava_death](#obj_lava_death)

### Lua Example
`local integerValue = obj_lava_death()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s8 obj_lava_death(void);`

[:arrow_up_small:](#)

<br />

## [obj_move_xyz_using_fvel_and_yaw](#obj_move_xyz_using_fvel_and_yaw)

### Lua Example
`obj_move_xyz_using_fvel_and_yaw(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_move_xyz_using_fvel_and_yaw(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_orient_graph](#obj_orient_graph)

### Lua Example
`obj_orient_graph(obj, normalX, normalY, normalZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| normalX | `number` |
| normalY | `number` |
| normalZ | `number` |

### Returns
- None

### C Prototype
`void obj_orient_graph(struct Object *obj, f32 normalX, f32 normalY, f32 normalZ);`

[:arrow_up_small:](#)

<br />

## [obj_return_and_displace_home](#obj_return_and_displace_home)

### Lua Example
`obj_return_and_displace_home(obj, homeX, homeY, homeZ, baseDisp)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| homeX | `number` |
| homeY | `number` |
| homeZ | `number` |
| baseDisp | `integer` |

### Returns
- None

### C Prototype
`void obj_return_and_displace_home(struct Object *obj, f32 homeX, UNUSED f32 homeY, f32 homeZ, s32 baseDisp);`

[:arrow_up_small:](#)

<br />

## [obj_return_home_if_safe](#obj_return_home_if_safe)

### Lua Example
`local integerValue = obj_return_home_if_safe(obj, homeX, y, homeZ, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| homeX | `number` |
| y | `number` |
| homeZ | `number` |
| dist | `integer` |

### Returns
- `integer`

### C Prototype
`s8 obj_return_home_if_safe(struct Object *obj, f32 homeX, f32 y, f32 homeZ, s32 dist);`

[:arrow_up_small:](#)

<br />

## [obj_spawn_yellow_coins](#obj_spawn_yellow_coins)

### Lua Example
`obj_spawn_yellow_coins(obj, nCoins)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| nCoins | `integer` |

### Returns
- None

### C Prototype
`void obj_spawn_yellow_coins(struct Object *obj, s8 nCoins);`

[:arrow_up_small:](#)

<br />

## [obj_splash](#obj_splash)

### Lua Example
`obj_splash(waterY, objY)`

### Parameters
| Field | Type |
| ----- | ---- |
| waterY | `integer` |
| objY | `integer` |

### Returns
- None

### C Prototype
`void obj_splash(s32 waterY, s32 objY);`

[:arrow_up_small:](#)

<br />

## [obj_update_pos_vel_xz](#obj_update_pos_vel_xz)

### Lua Example
`obj_update_pos_vel_xz()`

### Parameters
- None

### Returns
- None

### C Prototype
`void obj_update_pos_vel_xz(void);`

[:arrow_up_small:](#)

<br />

## [object_step](#object_step)

### Lua Example
`local integerValue = object_step()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 object_step(void);`

[:arrow_up_small:](#)

<br />

## [object_step_without_floor_orient](#object_step_without_floor_orient)

### Lua Example
`local integerValue = object_step_without_floor_orient()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 object_step_without_floor_orient(void);`

[:arrow_up_small:](#)

<br />

## [set_object_visibility](#set_object_visibility)

### Lua Example
`set_object_visibility(obj, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| dist | `integer` |

### Returns
- None

### C Prototype
`void set_object_visibility(struct Object *obj, s32 dist);`

[:arrow_up_small:](#)

<br />

## [set_yoshi_as_not_dead](#set_yoshi_as_not_dead)

### Lua Example
`set_yoshi_as_not_dead()`

### Parameters
- None

### Returns
- None

### C Prototype
`void set_yoshi_as_not_dead(void);`

[:arrow_up_small:](#)

<br />

## [spawn_orange_number](#spawn_orange_number)

### Lua Example
`spawn_orange_number(behParam, relX, relY, relZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| behParam | `integer` |
| relX | `integer` |
| relY | `integer` |
| relZ | `integer` |

### Returns
- None

### C Prototype
`void spawn_orange_number(s8 behParam, s16 relX, s16 relY, s16 relZ);`

[:arrow_up_small:](#)

<br />

## [turn_obj_away_from_steep_floor](#turn_obj_away_from_steep_floor)

### Lua Example
`local integerValue = turn_obj_away_from_steep_floor(objFloor, floorY, objVelX, objVelZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| objFloor | [Surface](structs.md#Surface) |
| floorY | `number` |
| objVelX | `number` |
| objVelZ | `number` |

### Returns
- `integer`

### C Prototype
`s8 turn_obj_away_from_steep_floor(struct Surface *objFloor, f32 floorY, f32 objVelX, f32 objVelZ);`

[:arrow_up_small:](#)

<br />

## [turn_obj_away_from_surface](#turn_obj_away_from_surface)

### Lua Example
`turn_obj_away_from_surface(velX, velZ, nX, nY, nZ, objYawX, objYawZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| velX | `number` |
| velZ | `number` |
| nX | `number` |
| nY | `number` |
| nZ | `number` |
| objYawX | `Pointer` <`number`> |
| objYawZ | `Pointer` <`number`> |

### Returns
- None

### C Prototype
`void turn_obj_away_from_surface(f32 velX, f32 velZ, f32 nX, UNUSED f32 nY, f32 nZ, f32 *objYawX, f32 *objYawZ);`

[:arrow_up_small:](#)

<br />
---

[< prev](functions-2.md) | [1](functions.md) | [2](functions-2.md) | 3 | [4](functions-4.md) | [next >](functions-4.md)]

