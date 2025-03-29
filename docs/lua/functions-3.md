## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-2.md) | [1](functions.md) | [2](functions-2.md) | 3 | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | [next >](functions-4.md)]


---
# functions from behavior_script.h

<br />


## [draw_distance_scalar](#draw_distance_scalar)

### Description
Gets the draw distance scalar

### Lua Example
`local numberValue = draw_distance_scalar()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 draw_distance_scalar(void);`

[:arrow_up_small:](#)

<br />

## [obj_update_gfx_pos_and_angle](#obj_update_gfx_pos_and_angle)

### Description
Updates an object's graphical position and angle

### Lua Example
`obj_update_gfx_pos_and_angle(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_update_gfx_pos_and_angle(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [position_based_random_float_position](#position_based_random_float_position)

### Description
Sets the current object's position to random floats between 0.0 and 1.0

### Lua Example
`local numberValue = position_based_random_float_position()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 position_based_random_float_position(void);`

[:arrow_up_small:](#)

<br />

## [position_based_random_u16](#position_based_random_u16)

### Description
Sets the current object's position to random integers between 0 and 65536

### Lua Example
`local integerValue = position_based_random_u16()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u16 position_based_random_u16(void);`

[:arrow_up_small:](#)

<br />

## [random_float](#random_float)

### Description
Generates a pseudo random float between 0.0 and 1.0

### Lua Example
`local numberValue = random_float()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`float random_float(void);`

[:arrow_up_small:](#)

<br />

## [random_sign](#random_sign)

### Description
Returns either 1 or -1 with a pseudo 50:50 chance

### Lua Example
`local integerValue = random_sign()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 random_sign(void);`

[:arrow_up_small:](#)

<br />

## [random_u16](#random_u16)

### Description
Generates a pseudo random integer between 0 and 65535

### Lua Example
`local integerValue = random_u16()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u16 random_u16(void);`

[:arrow_up_small:](#)

<br />

---
# functions from behavior_table.h

<br />


## [get_behavior_from_id](#get_behavior_from_id)

### Description
Gets a behavior script from a behavior ID

### Lua Example
`local PointerValue = get_behavior_from_id(id)`

### Parameters
| Field | Type |
| ----- | ---- |
| id | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
- `Pointer` <`BehaviorScript`>

### C Prototype
`const BehaviorScript* get_behavior_from_id(enum BehaviorId id);`

[:arrow_up_small:](#)

<br />

## [get_behavior_name_from_id](#get_behavior_name_from_id)

### Description
Gets a behavior name from a behavior ID (bhvMyGreatMODCustom004)

### Lua Example
`local stringValue = get_behavior_name_from_id(id)`

### Parameters
| Field | Type |
| ----- | ---- |
| id | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
- `string`

### C Prototype
`const char* get_behavior_name_from_id(enum BehaviorId id);`

[:arrow_up_small:](#)

<br />

## [get_id_from_behavior](#get_id_from_behavior)

### Description
Gets a behavior ID from a behavior script

### Lua Example
`local enumValue = get_id_from_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
[enum BehaviorId](constants.md#enum-BehaviorId)

### C Prototype
`enum BehaviorId get_id_from_behavior(const BehaviorScript* behavior);`

[:arrow_up_small:](#)

<br />

## [get_id_from_behavior_name](#get_id_from_behavior_name)

### Description
gets a behavior ID from a behavior name

### Lua Example
`local enumValue = get_id_from_behavior_name(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
[enum BehaviorId](constants.md#enum-BehaviorId)

### C Prototype
`enum BehaviorId get_id_from_behavior_name(const char* name);`

[:arrow_up_small:](#)

<br />

## [get_id_from_vanilla_behavior](#get_id_from_vanilla_behavior)

### Description
Gets a behavior ID from only vanilla behavior scripts

### Lua Example
`local enumValue = get_id_from_vanilla_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
[enum BehaviorId](constants.md#enum-BehaviorId)

### C Prototype
`enum BehaviorId get_id_from_vanilla_behavior(const BehaviorScript* behavior);`

[:arrow_up_small:](#)

<br />

---
# functions from camera.h

<br />


## [approach_camera_height](#approach_camera_height)

### Description
Adjusts the camera's height toward a target value (`goalHeight`) while respecting terrain and obstructions. This is really wonky and probably shouldn't be used, prefer `gLakituStates`

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

### Description
Gradually approaches a floating-point value (`target`) using asymptotic smoothing. The rate of approach is controlled by the `multiplier`. Useful for smoothly adjusting camera parameters like field-of-view or position

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

### Description
Gradually adjusts a floating-point value (`current`) towards a target (`target`) using asymptotic smoothing. Returns true if `current` reaches the `target` and false otherwise

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

### Description
Gradually approaches a signed 16-bit integer (`target`) using asymptotic smoothing. The divisor controls the rate of the adjustment. Useful for adjusting angles or positions smoothly

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

### Description
Gradually adjusts a signed 16-bit integer (`current`) towards a target (`target`) using asymptotic smoothing. Returns true if `current` reaches `target` and false otherwise

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

### Description
Smoothly transitions a 3D vector (`current`) towards a target vector (`target`) using asymptotic scaling. Scaling values (the `Mul` variables) for x, y, and z axes determine the speed of adjustment for each component

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

### Description
Calculates the absolute distance between two 3D points (`a` and `b`). Returns the distance as a floating-point value. Useful for determining proximity between objects in 3D space

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

### Description
Calculates the horizontal (XZ-plane) distance between two 3D points (`a` and `b`). Returns the distance as a floating-point value. Useful for terrain navigation or collision detection

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

### Description
Calculates the pitch and yaw angles from one 3D position (`from`) to another (`to`). Updates the provided pointers with the computed pitch and yaw values

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

### Description
Calculates the pitch angle (rotation around the X-axis) from one 3D point (`from`) to another (`to`). Returns the pitch as a signed 16-bit integer

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

### Description
Determines the yaw angle (rotation around the Y-axis) from one 3D position (`from`) to another (`to`). Returns the yaw as a signed 16-bit integer

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

### Description
Selects an alternate camera mode based on the given angle. Used to toggle between predefined camera modes dynamically

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

### Description
Symmetrically approaches a floating-point value (`target`) with a fixed increment (`increment`) per frame. Limits the rate of change to ensure gradual transitions

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

### Description
Adjusts a floating-point value (`current`) towards a target (`target`) symmetrically with a fixed increment (`increment`). Returns true if the value reaches the target and false otherwise

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

### Description
Adjusts a signed 16-bit integer (`current`) towards a target (`target`) symmetrically with a fixed increment (`increment`). Returns true if the value reaches the target and false otherwise

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

### Description
Processes course-specific camera settings, such as predefined positions or modes. Adjusts the camera to match the design and gameplay requirements of the current course

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

### Description
Toggles whether the camera uses course-specific settings. This is useful for enabling or disabling custom behaviors in specific courses or areas

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

### Description
Centers the ROM hack camera. This function is designed for non-standard level layouts and modded game environments

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

### Description
Clamps the camera's pitch angle between a maximum and minimum value. Prevents over-rotation and maintains a consistent viewing angle

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

### Description
Clamps a position within specified X and Z bounds and calculates the yaw angle from the origin. Prevents the camera from moving outside of the designated area

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

### Description
Checks for collisions between the camera and level geometry. Adjusts the camera's position to avoid clipping into walls or obstacles

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

### Description
Initiates a cutscene focusing on a specific object in the game world. The camera transitions smoothly to the object, adapting its position as needed

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

### Description
Starts a cutscene involving an object and displays dialog during the sequence. The camera focuses on the object while synchronizing dialog with the scene

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

### Description
Starts a cutscene involving an object without dialog. The camera transitions smoothly to focus on the object

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

### Description
Applies a preset field-of-view shake effect during a cutscene. This creates dynamic visual effects, such as zoom or focus disruptions

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

### Description
Spawns an object as part of a cutscene, such as props or interactive elements. Returns the spawned object's reference for further manipulation

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

### Description
Determines which C-buttons are currently pressed by the player. Returns a bitmask indicating the active buttons for camera control

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

### Description
Finds the floor and ceiling directly above and below Mario's position. Updates Mario's geometry information for camera calculations

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

### Description
Gets the appropriate cutscene to play based on Mario's current gameplay state. This function helps determine transitions for cinematic or scripted sequences

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

### Description
Handles camera movement based on input from the C-buttons. Updates the camera's position or angle to match directional player input

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

### Description
Determines if a range is obstructed by a surface relative to the camera. Returns true if the range is behind the specified surface

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

### Description
Checks if a position is within 100 units of Mario's current position. Returns true if the position is within the specified radius and false otherwise

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

### Description
Moves Mario's head slightly upward when the C-Up button is pressed. This function aligns the camera to match the head movement for consistency

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

### Description
Transitions the camera to the next Lakitu state, updating position and focus. This function handles smooth transitions between different gameplay scenarios

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

### Description
Rotates an object toward a specific point in 3D space. Gradually updates the object's pitch and yaw angles to face the target

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

### Description
Converts an object's position to a `Vec3f` format. Useful for aligning object behaviors or interactions with the camera system

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

### Description
Offsets a vector by rotating it in 3D space relative to a reference position. This is useful for creating radial effects or dynamic transformations

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

### Description
Calculates an outward radial offset based on the camera's yaw angle. Returns the offset yaw, used for positioning or alignment

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

### Description
Plays a buzzing sound effect when the camera's position is misaligned with the player's perspective. Used as audio feedback for incorrect camera behavior

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

### Description
Plays a buzzing sound effect when a blocked C-button action is attempted. Used to signal invalid input or restricted camera movement

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

### Description
Plays a buzzing sound effect when the camera attempts to move downward but is restricted. Provides feedback for invalid C-Down input actions

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

### Description
Starts the execution of a predefined cutscene. The camera transitions dynamically to follow the scripted sequence

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

### Description
Plays a sound effect when a blocked action changes the camera mode. This provides feedback for invalid attempts to switch the camera state

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

### Description
Plays a sound effect when the C-Down button is pressed for camera movement. Provides auditory feedback for valid camera input

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

### Description
Plays a sound effect when the C-Side button (left or right) is pressed for camera movement. Used as audio feedback for horizontal adjustments to the camera

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

### Description
Plays a sound effect when the C-Up button is pressed for camera movement. Provides feedback for vertical camera adjustments

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

### Description
Plays a sound effect when the camera switches between Lakitu and Mario perspectives. Signals a successful change in camera mode

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

### Description
Plays a sound effect when the R-Button camera mode is changed. Provides feedback for toggling camera behaviors

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

### Description
Handles radial camera movement based on player input. Updates the camera's position or orientation accordingly

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

### Description
Generates a random 3D vector with short integer components. Useful for randomized offsets or environmental effects

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

### Description
Fully resets the camera to its default state and reinitializes all settings. This is typically used when restarting gameplay or loading a new area

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

### Description
Resolves collisions between the camera and level geometry. Adjusts the camera's position to prevent clipping or intersecting with objects

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

## [rotate_camera_around_walls](#rotate_camera_around_walls)

### Description
Rotates the camera to avoid walls or other obstructions. Ensures clear visibility of the player or target objects

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

### Description
Rotates a vector around the XZ-plane by a specified yaw angle. The result is stored in the destination vector (`dst`). Useful for rotating camera positions or object coordinates horizontally

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

### Description
Rotates a vector around the YZ-plane by a specified pitch angle. The result is stored in the destination vector (`dst`). Useful for vertical camera rotations or object transformations

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

### Description
Scales a point along a line between two 3D points (`from` and `to`). The scaling factor determines how far along the line the resulting point will be. The result is stored in the destination vector (`dest`)

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

### Description
Selects the appropriate camera mode for Mario based on the current gameplay context. Adapts camera behavior dynamically to match Mario's environment or state

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

### Description
Sets the camera's angle based on the specified mode. Handles rotation and focus adjustments for predefined camera behaviors

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

### Description
Changes the camera to a new mode, optionally interpolating over a specified number of frames. Useful for transitioning between different camera behaviors dynamically

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

### Description
Activates a fixed camera mode and aligns the camera to specific X, Y, Z coordinates. This is useful for predefined static views in specific areas

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

### Description
Applies a pitch-based shake effect to the camera. The shake's magnitude, decay, and increment are configurable. Simulates vertical disturbances like impacts or explosions

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

### Description
Applies a roll-based shake effect to the camera. Simulates rotational disturbances for dynamic camera effects

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

### Description
Applies a shake effect to the camera based on a hit type. Different shake types simulate various impacts, such as attacks, falls, or shocks

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

### Description
Applies a shake effect to the camera, scaled by its proximity to a specified point. The intensity decreases with distance from the point

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

### Description
Applies a yaw-based shake effect to the camera. Simulates horizontal vibrations or rotational impacts

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

### Description
Applies an environmental shake effect to the camera. Handles predefined shake types triggered by environmental events like explosions or platform movements

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

### Description
Assigns a custom function for dynamic field-of-view adjustments. This allows precise control over the camera's zoom behavior during gameplay

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

### Description
Applies a field-of-view shake effect to simulate zoom or focus disruptions. Shake parameters, such as amplitude and decay, control the intensity

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

### Description
Applies a preset field-of-view shake effect relative to a specific point. The intensity diminishes as the distance from the point increases

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

### Description
Applies a handheld camera shake effect with configurable parameters. Can be used to simulate dynamic, realistic camera movement

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

### Description
Smoothly transitions or directly sets a floating-point value (`dst`) to approach a target (`goal`). Uses asymptotic scaling for gradual adjustments or direct assignment

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

### Description
Smoothly transitions or directly sets a signed 16-bit value (`current`) to approach a target (`target`). Uses symmetric scaling for gradual or immediate adjustments

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

### Description
Smoothly transitions a 3D vector (`current`) toward a target vector (`goal`) using asymptotic scaling. Allows gradual or instantaneous alignment of 3D positions. Scaling values (the `Mul` variables) for x, y, and z axes determine the speed of adjustment for each component

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

### Description
Applies a pitch shake effect to the camera, scaled by proximity to a specified point. Simulates vibrations with intensity decreasing further from the point

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

### Description
Activates a handheld camera shake effect. Calculates positional and focus adjustments to simulate manual movement

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

### Description
Activates a pitch-based shake effect. Adds vertical vibrational movement to the camera's behavior

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

### Description
Applies a roll-based shake effect to the camera. Simulates rotational disturbances caused by impacts or other events

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

### Description
Activates a yaw-based shake effect. Adds horizontal vibrational movement to the camera's behavior

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

## [skip_camera_interpolation](#skip_camera_interpolation)

### Description
Skips camera interpolation for a frame, locking the camera instantly to the target position. Useful for immediate changes in camera state or position without smooth transitions

### Lua Example
`skip_camera_interpolation()`

### Parameters
- None

### Returns
- None

### C Prototype
`void skip_camera_interpolation(void);`

[:arrow_up_small:](#)

<br />

## [snap_to_45_degrees](#snap_to_45_degrees)

### Description
Takes in an SM64 angle unit and returns the nearest 45 degree angle, also in SM64 angle units. Useful when needing to align angles (camera, yaw, etc.)

### Lua Example
`local integerValue = snap_to_45_degrees(angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| angle | `integer` |

### Returns
- `integer`

### C Prototype
`s32 snap_to_45_degrees(s16 angle);`

[:arrow_up_small:](#)

<br />

## [soft_reset_camera](#soft_reset_camera)

### Description
Resets the camera's state while retaining some settings, such as position or mode. This is often used when soft-resetting gameplay without reinitialization

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

### Description
Starts a cutscene based on the provided ID. The camera transitions to predefined behaviors for the duration of the cutscene

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

### Description
Starts a cutscene focused on an object without requiring focus to remain locked. This is useful for dynamic events where the camera adjusts freely

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

### Description
Transitions the camera to the next state over a specified number of frames. This is typically used for cutscenes or scripted sequences

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

### Description
Triggers a dialog sequence during a cutscene. The dialog is synchronized with the camera's position and movement

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

### Description
Subtracts one 3D vector (`src`) from another (`dst`). Stores the result in the destination vector

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

### Description
Converts a `Vec3f` position to an object's internal format. Useful for syncing 3D positions between objects and the game world

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

### Description
Moves the camera to a specified warp destination. This function handles transitions between levels or areas seamlessly

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

## [get_character_anim](#get_character_anim)

### Description
Gets the animation ID to use for a specific character and animation combination. The ID is based on `characterAnim` and the character currently controlled by Mario (`m`). Useful for determining which animation to play for actions like walking, jumping, or idle states

### Lua Example
`local integerValue = get_character_anim(m, characterAnim)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| characterAnim | [enum CharacterAnimID](constants.md#enum-CharacterAnimID) |

### Returns
- `integer`

### C Prototype
`s32 get_character_anim(struct MarioState* m, enum CharacterAnimID characterAnim);`

[:arrow_up_small:](#)

<br />

## [get_character_anim_offset](#get_character_anim_offset)

### Description
Calculates the animation offset for Mario's current animation. The offset is determined by the type of animation being played (e.g., hand, feet, or torso movement). Useful for smoothly syncing Mario's model height or positional adjustments during animations

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

### Description
Plays a character-specific sound based on the given `characterSound` value. The sound is tied to Mario's current state (`m`). Useful for triggering sound effects for actions like jumping or interacting with the environment

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

### Description
Plays a character-specific sound only if certain flags are not set. This ensures that sounds are not repeated unnecessarily. The sound is based on `characterSound`, and the flags are checked using `flags`. Useful for avoiding duplicate sound effects in rapid succession or conditional actions

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

### Description
Plays a character-specific sound with an additional `offset`, allowing variations or delays in the sound effect. Uses Mario's current state (`m`). Useful for adding dynamic sound effects or syncing sounds to specific animations or events

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

### Description
Updates Mario's current animation offset. This adjusts Mario's position based on the calculated offset to ensure animations appear smooth and natural. Useful for keeping Mario's animations visually aligned, particularly when transitioning between animations

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

### Description
Creates a `message` in the game's chat box

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
# functions from djui_console.h

<br />


## [djui_console_toggle](#djui_console_toggle)

### Description
Toggles the visibility of the DJUI console

### Lua Example
`djui_console_toggle()`

### Parameters
- None

### Returns
- None

### C Prototype
`void djui_console_toggle(void);`

[:arrow_up_small:](#)

<br />

---
# functions from djui_hud_utils.h

<br />


## [djui_hud_get_color](#djui_hud_get_color)

### Description
Gets the current DJUI HUD color

### Lua Example
`local DjuiColorValue = djui_hud_get_color()`

### Parameters
- None

### Returns
[DjuiColor](structs.md#DjuiColor)

### C Prototype
`struct DjuiColor* djui_hud_get_color(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_filter](#djui_hud_get_filter)

### Description
Gets the current DJUI HUD texture filter

### Lua Example
`local integerValue = djui_hud_get_filter()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 djui_hud_get_filter(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_font](#djui_hud_get_font)

### Description
Gets the current DJUI HUD font

### Lua Example
`local integerValue = djui_hud_get_font()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 djui_hud_get_font(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_fov_coeff](#djui_hud_get_fov_coeff)

### Description
Gets the camera FOV coefficient

### Lua Example
`local numberValue = djui_hud_get_fov_coeff()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 djui_hud_get_fov_coeff();`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_mouse_x](#djui_hud_get_mouse_x)

### Description
Returns the x coordinate of the mouse relative to the window

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

### Description
Returns the y coordinate of the mouse relative to the window

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

### Description
Returns the x coordinate of the mouse relative to the screen

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

### Description
Returns the y coordinate of the mouse relative to the screen

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

## [djui_hud_get_resolution](#djui_hud_get_resolution)

### Description
Gets the current DJUI HUD resolution

### Lua Example
`local integerValue = djui_hud_get_resolution()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 djui_hud_get_resolution(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_rotation](#djui_hud_get_rotation)

### Description
Gets the current DJUI HUD rotation

### Lua Example
`local HudUtilsRotationValue = djui_hud_get_rotation()`

### Parameters
- None

### Returns
[HudUtilsRotation](structs.md#HudUtilsRotation)

### C Prototype
`struct HudUtilsRotation* djui_hud_get_rotation(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_get_screen_height](#djui_hud_get_screen_height)

### Description
Gets the screen height in the current DJUI HUD resolution

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

### Description
Gets the screen width in the current DJUI HUD resolution

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

## [djui_hud_is_pause_menu_created](#djui_hud_is_pause_menu_created)

### Description
Checks if the DJUI pause menu is created

### Lua Example
`local booleanValue = djui_hud_is_pause_menu_created()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool djui_hud_is_pause_menu_created(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_measure_text](#djui_hud_measure_text)

### Description
Measures the length of `message` in the current font

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

### Description
Prints DJUI HUD text onto the screen

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
`void djui_hud_print_text(const char* message, f32 x, f32 y, f32 scale);`

[:arrow_up_small:](#)

<br />

## [djui_hud_print_text_interpolated](#djui_hud_print_text_interpolated)

### Description
Prints interpolated DJUI HUD text onto the screen

### Lua Example
`djui_hud_print_text_interpolated(message, prevX, prevY, prevScale, x, y, scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| message | `string` |
| prevX | `number` |
| prevY | `number` |
| prevScale | `number` |
| x | `number` |
| y | `number` |
| scale | `number` |

### Returns
- None

### C Prototype
`void djui_hud_print_text_interpolated(const char* message, f32 prevX, f32 prevY, f32 prevScale, f32 x, f32 y, f32 scale);`

[:arrow_up_small:](#)

<br />

## [djui_hud_render_rect](#djui_hud_render_rect)

### Description
Renders a DJUI HUD rect onto the screen

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

### Description
Renders an interpolated DJUI HUD rect onto the screen

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

## [djui_hud_reset_color](#djui_hud_reset_color)

### Description
Resets the current DJUI HUD color

### Lua Example
`djui_hud_reset_color()`

### Parameters
- None

### Returns
- None

### C Prototype
`void djui_hud_reset_color(void);`

[:arrow_up_small:](#)

<br />

## [djui_hud_set_color](#djui_hud_set_color)

### Description
Sets the current DJUI HUD color

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

## [djui_hud_set_filter](#djui_hud_set_filter)

### Description
Sets the current DJUI HUD texture filter

### Lua Example
`djui_hud_set_filter(filterType)`

### Parameters
| Field | Type |
| ----- | ---- |
| filterType | [enum HudUtilsFilter](constants.md#enum-HudUtilsFilter) |

### Returns
- None

### C Prototype
`void djui_hud_set_filter(enum HudUtilsFilter filterType);`

[:arrow_up_small:](#)

<br />

## [djui_hud_set_font](#djui_hud_set_font)

### Description
Sets the current DJUI HUD font

### Lua Example
`djui_hud_set_font(fontType)`

### Parameters
| Field | Type |
| ----- | ---- |
| fontType | `integer` |

### Returns
- None

### C Prototype
`void djui_hud_set_font(s8 fontType);`

[:arrow_up_small:](#)

<br />

## [djui_hud_set_mouse_locked](#djui_hud_set_mouse_locked)

### Description
Sets if the cursor is hidden and constrainted to the window

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

### Description
Sets the current DJUI HUD resolution

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

## [djui_hud_set_rotation](#djui_hud_set_rotation)

### Description
Sets the current DJUI HUD rotation

### Lua Example
`djui_hud_set_rotation(rotation, pivotX, pivotY)`

### Parameters
| Field | Type |
| ----- | ---- |
| rotation | `integer` |
| pivotX | `number` |
| pivotY | `number` |

### Returns
- None

### C Prototype
`void djui_hud_set_rotation(s16 rotation, f32 pivotX, f32 pivotY);`

[:arrow_up_small:](#)

<br />

## [djui_hud_set_rotation_interpolated](#djui_hud_set_rotation_interpolated)

### Description
Sets the current DJUI HUD rotation interpolated

### Lua Example
`djui_hud_set_rotation_interpolated(prevRotation, prevPivotX, prevPivotY, rotation, pivotX, pivotY)`

### Parameters
| Field | Type |
| ----- | ---- |
| prevRotation | `integer` |
| prevPivotX | `number` |
| prevPivotY | `number` |
| rotation | `integer` |
| pivotX | `number` |
| pivotY | `number` |

### Returns
- None

### C Prototype
`void djui_hud_set_rotation_interpolated(s32 prevRotation, f32 prevPivotX, f32 prevPivotY, s32 rotation, f32 pivotX, f32 pivotY);`

[:arrow_up_small:](#)

<br />

## [djui_hud_world_pos_to_screen_pos](#djui_hud_world_pos_to_screen_pos)

### Description
Converts a world position to screen position

### Lua Example
`local booleanValue = djui_hud_world_pos_to_screen_pos(pos, out)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| out | [Vec3f](structs.md#Vec3f) |

### Returns
- `boolean`

### C Prototype
`bool djui_hud_world_pos_to_screen_pos(Vec3f pos, Vec3f out);`

[:arrow_up_small:](#)

<br />

## [djui_open_pause_menu](#djui_open_pause_menu)

### Description
Opens the DJUI pause menu

### Lua Example
`djui_open_pause_menu()`

### Parameters
- None

### Returns
- None

### C Prototype
`void djui_open_pause_menu(void);`

[:arrow_up_small:](#)

<br />

## [get_current_fov](#get_current_fov)

### Description
Gets the current camera FOV

### Lua Example
`local numberValue = get_current_fov()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_current_fov();`

[:arrow_up_small:](#)

<br />

---
# functions from djui_language.h

<br />


## [djui_language_get](#djui_language_get)

### Description
Gets a language `key` from a `section`

### Lua Example
`local stringValue = djui_language_get(section, key)`

### Parameters
| Field | Type |
| ----- | ---- |
| section | `string` |
| key | `string` |

### Returns
- `string`

### C Prototype
`char* djui_language_get(const char *section, const char *key);`

[:arrow_up_small:](#)

<br />

---
# functions from djui_panel_menu.h

<br />


## [djui_menu_get_rainbow_string_color](#djui_menu_get_rainbow_string_color)

### Description
Gets the header hex color code from a `DJUI_RAINBOW_COLOR_*` constant

### Lua Example
`local stringValue = djui_menu_get_rainbow_string_color(color)`

### Parameters
| Field | Type |
| ----- | ---- |
| color | [enum DjuiRainbowColor](constants.md#enum-DjuiRainbowColor) |

### Returns
- `string`

### C Prototype
`char* djui_menu_get_rainbow_string_color(enum DjuiRainbowColor color);`

[:arrow_up_small:](#)

<br />

---
# functions from djui_popup.h

<br />


## [djui_popup_create](#djui_popup_create)

### Description
Creates a popup that says `message` and has `lines`

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


## [drop_queued_background_music](#drop_queued_background_music)

### Description
Drops any queued background music

### Lua Example
`drop_queued_background_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void drop_queued_background_music(void);`

[:arrow_up_small:](#)

<br />

## [fade_volume_scale](#fade_volume_scale)

### Description
Fades the volume of `player` to `targetScale` (0-127) over `fadeDuration`

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

### Description
Fades out background music `seqId` over `fadeOut`

### Lua Example
`fadeout_background_music(seqId, fadeOut)`

### Parameters
| Field | Type |
| ----- | ---- |
| seqId | `integer` |
| fadeOut | `integer` |

### Returns
- None

### C Prototype
`void fadeout_background_music(u16 seqId, u16 fadeOut);`

[:arrow_up_small:](#)

<br />

## [get_current_background_music](#get_current_background_music)

### Description
Gets the current background music

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

### Description
Gets the current background music's default volume

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

### Description
Gets the current max target volume

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

### Description
Gets the current target volume

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

## [get_sound_pan](#get_sound_pan)

### Lua Example
`local numberValue = get_sound_pan(x, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| z | `number` |

### Returns
- `number`

### C Prototype
`f32 get_sound_pan(f32 x, f32 z);`

[:arrow_up_small:](#)

<br />

## [is_current_background_music_volume_lowered](#is_current_background_music_volume_lowered)

### Description
Checks if the current background music is lowered

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

### Description
Plays the star collect fanfare (this function's name was mixed up with the other)

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

### Description
Plays a dialog sound corresponding to `dialogID`

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

### Description
Plays fading in music (`seqArgs`) on `player` over `fadeTimer`

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

### Description
Plays Peach's letter jingle

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

### Description
Plays the power star jingle, set `keepBackgroundMusic` to 0 to mute background music

### Lua Example
`play_power_star_jingle(keepBackgroundMusic)`

### Parameters
| Field | Type |
| ----- | ---- |
| keepBackgroundMusic | `integer` |

### Returns
- None

### C Prototype
`void play_power_star_jingle(u8 keepBackgroundMusic);`

[:arrow_up_small:](#)

<br />

## [play_puzzle_jingle](#play_puzzle_jingle)

### Description
Plays the puzzle jingle

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

### Description
Plays the race fanfare when a race is started

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

### Description
Plays fading in secondary music `seqId` at `volume` over `fadeTimer` and sets the current background music's volume to `bgMusicVolume`

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

### Description
Plays a sound (`soundBits`) at `pos` (usually `gGlobalSoundSource` or `m.header.gfx.cameraToObject`)

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

### Description
Plays a sound (`soundBits`) with `freqScale` at `pos` (usually `gGlobalSoundSource` or `m.header.gfx.cameraToObject`)

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

### Description
Plays the course clear fanfare (this function's name was mixed up with the other)

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

### Description
Plays Toad's jingle

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

### Description
Fades out `player` with `fadeDuration`

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

### Description
Fades the volume of `player` to `percentage` over `fadeDuration`

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

### Description
Unfades the volume of `player` over `fadeDuration`

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

## [set_audio_fadeout](#set_audio_fadeout)

### Description
Sets the `fadeOutTime` of audio

### Lua Example
`set_audio_fadeout(fadeOutTime)`

### Parameters
| Field | Type |
| ----- | ---- |
| fadeOutTime | `integer` |

### Returns
- None

### C Prototype
`void set_audio_fadeout(u16 fadeOutTime);`

[:arrow_up_small:](#)

<br />

## [set_audio_muted](#set_audio_muted)

### Description
Sets the muted status of all sequence players

### Lua Example
`set_audio_muted(muted)`

### Parameters
| Field | Type |
| ----- | ---- |
| muted | `integer` |

### Returns
- None

### C Prototype
`void set_audio_muted(u8 muted);`

[:arrow_up_small:](#)

<br />

## [set_sound_moving_speed](#set_sound_moving_speed)

### Description
Sets the `speed` of moving `bank`

### Lua Example
`set_sound_moving_speed(bank, speed)`

### Parameters
| Field | Type |
| ----- | ---- |
| bank | `integer` |
| speed | `integer` |

### Returns
- None

### C Prototype
`void set_sound_moving_speed(u8 bank, u8 speed);`

[:arrow_up_small:](#)

<br />

## [sound_banks_disable](#sound_banks_disable)

### Description
Enables `bankMask` soundbanks in `player`

### Lua Example
`sound_banks_disable(player, bankMask)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| bankMask | `integer` |

### Returns
- None

### C Prototype
`void sound_banks_disable(u8 player, u16 bankMask);`

[:arrow_up_small:](#)

<br />

## [sound_banks_enable](#sound_banks_enable)

### Description
Disables `bankMask` soundbanks in `player`

### Lua Example
`sound_banks_enable(player, bankMask)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| bankMask | `integer` |

### Returns
- None

### C Prototype
`void sound_banks_enable(u8 player, u16 bankMask);`

[:arrow_up_small:](#)

<br />

## [sound_get_level_intensity](#sound_get_level_intensity)

### Lua Example
`local numberValue = sound_get_level_intensity(distance)`

### Parameters
| Field | Type |
| ----- | ---- |
| distance | `number` |

### Returns
- `number`

### C Prototype
`f32 sound_get_level_intensity(f32 distance);`

[:arrow_up_small:](#)

<br />

## [sound_reset_background_music_default_volume](#sound_reset_background_music_default_volume)

### Lua Example
`sound_reset_background_music_default_volume(seqId)`

### Parameters
| Field | Type |
| ----- | ---- |
| seqId | `integer` |

### Returns
- None

### C Prototype
`void sound_reset_background_music_default_volume(u8 seqId);`

[:arrow_up_small:](#)

<br />

## [sound_set_background_music_default_volume](#sound_set_background_music_default_volume)

### Lua Example
`sound_set_background_music_default_volume(seqId, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| seqId | `integer` |
| volume | `integer` |

### Returns
- None

### C Prototype
`void sound_set_background_music_default_volume(u8 seqId, u8 volume);`

[:arrow_up_small:](#)

<br />

## [stop_background_music](#stop_background_music)

### Description
Stops background music `seqId`

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

## [stop_secondary_music](#stop_secondary_music)

### Description
Fades out secondary music over `fadeTimer`

### Lua Example
`stop_secondary_music(fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| fadeTimer | `integer` |

### Returns
- None

### C Prototype
`void stop_secondary_music(u16 fadeTimer);`

[:arrow_up_small:](#)

<br />

## [stop_sound](#stop_sound)

### Description
Stops a sound (`soundBits`) at `pos` (usually `gGlobalSoundSource` or `m.header.gfx.cameraToObject`)

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

### Description
Stops sounds from `pos` (usually `gGlobalSoundSource` or `m.header.gfx.cameraToObject`)

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

### Description
Stops sounds in sound banks moving, env, and air

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
# functions from first_person_cam.h

<br />


## [first_person_check_cancels](#first_person_check_cancels)

### Description
Checks common cancels for first person

### Lua Example
`local booleanValue = first_person_check_cancels(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `boolean`

### C Prototype
`bool first_person_check_cancels(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [first_person_reset](#first_person_reset)

### Description
Resets first person

### Lua Example
`first_person_reset()`

### Parameters
- None

### Returns
- None

### C Prototype
`void first_person_reset(void);`

[:arrow_up_small:](#)

<br />

## [get_first_person_enabled](#get_first_person_enabled)

### Description
Checks if first person is enabled

### Lua Example
`local booleanValue = get_first_person_enabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool get_first_person_enabled(void);`

[:arrow_up_small:](#)

<br />

## [set_first_person_enabled](#set_first_person_enabled)

### Description
Sets if first person is enabled

### Lua Example
`set_first_person_enabled(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void set_first_person_enabled(bool enable);`

[:arrow_up_small:](#)

<br />

---
# functions from ingame_menu.h

<br />


## [create_dialog_box](#create_dialog_box)

### Lua Example
`create_dialog_box(dialog)`

### Parameters
| Field | Type |
| ----- | ---- |
| dialog | `integer` |

### Returns
- None

### C Prototype
`void create_dialog_box(s16 dialog);`

[:arrow_up_small:](#)

<br />

## [create_dialog_box_with_response](#create_dialog_box_with_response)

### Lua Example
`create_dialog_box_with_response(dialog)`

### Parameters
| Field | Type |
| ----- | ---- |
| dialog | `integer` |

### Returns
- None

### C Prototype
`void create_dialog_box_with_response(s16 dialog);`

[:arrow_up_small:](#)

<br />

## [create_dialog_box_with_var](#create_dialog_box_with_var)

### Lua Example
`create_dialog_box_with_var(dialog, dialogVar)`

### Parameters
| Field | Type |
| ----- | ---- |
| dialog | `integer` |
| dialogVar | `integer` |

### Returns
- None

### C Prototype
`void create_dialog_box_with_var(s16 dialog, s32 dialogVar);`

[:arrow_up_small:](#)

<br />

## [create_dialog_inverted_box](#create_dialog_inverted_box)

### Lua Example
`create_dialog_inverted_box(dialog)`

### Parameters
| Field | Type |
| ----- | ---- |
| dialog | `integer` |

### Returns
- None

### C Prototype
`void create_dialog_inverted_box(s16 dialog);`

[:arrow_up_small:](#)

<br />

## [reset_dialog_override_color](#reset_dialog_override_color)

### Lua Example
`reset_dialog_override_color()`

### Parameters
- None

### Returns
- None

### C Prototype
`void reset_dialog_override_color();`

[:arrow_up_small:](#)

<br />

## [reset_dialog_override_pos](#reset_dialog_override_pos)

### Lua Example
`reset_dialog_override_pos()`

### Parameters
- None

### Returns
- None

### C Prototype
`void reset_dialog_override_pos();`

[:arrow_up_small:](#)

<br />

## [reset_dialog_render_state](#reset_dialog_render_state)

### Lua Example
`reset_dialog_render_state()`

### Parameters
- None

### Returns
- None

### C Prototype
`void reset_dialog_render_state(void);`

[:arrow_up_small:](#)

<br />

## [set_dialog_box_state](#set_dialog_box_state)

### Lua Example
`set_dialog_box_state(state)`

### Parameters
| Field | Type |
| ----- | ---- |
| state | `integer` |

### Returns
- None

### C Prototype
`void set_dialog_box_state(u8 state);`

[:arrow_up_small:](#)

<br />

## [set_dialog_override_color](#set_dialog_override_color)

### Lua Example
`set_dialog_override_color(bgR, bgG, bgB, bgA, textR, textG, textB, textA)`

### Parameters
| Field | Type |
| ----- | ---- |
| bgR | `integer` |
| bgG | `integer` |
| bgB | `integer` |
| bgA | `integer` |
| textR | `integer` |
| textG | `integer` |
| textB | `integer` |
| textA | `integer` |

### Returns
- None

### C Prototype
`void set_dialog_override_color(u8 bgR, u8 bgG, u8 bgB, u8 bgA, u8 textR, u8 textG, u8 textB, u8 textA);`

[:arrow_up_small:](#)

<br />

## [set_dialog_override_pos](#set_dialog_override_pos)

### Lua Example
`set_dialog_override_pos(x, y)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `integer` |
| y | `integer` |

### Returns
- None

### C Prototype
`void set_dialog_override_pos(s16 x, s16 y);`

[:arrow_up_small:](#)

<br />

## [set_menu_mode](#set_menu_mode)

### Lua Example
`set_menu_mode(mode)`

### Parameters
| Field | Type |
| ----- | ---- |
| mode | `integer` |

### Returns
- None

### C Prototype
`void set_menu_mode(s16 mode);`

[:arrow_up_small:](#)

<br />

## [set_min_dialog_width](#set_min_dialog_width)

### Lua Example
`set_min_dialog_width(width)`

### Parameters
| Field | Type |
| ----- | ---- |
| width | `integer` |

### Returns
- None

### C Prototype
`void set_min_dialog_width(s16 width);`

[:arrow_up_small:](#)

<br />

---
# functions from interaction.h

<br />


## [determine_interaction](#determine_interaction)

### Description
Determines how Mario interacts with a given object based on his current action, position, and other state variables. Calculates the appropriate interaction type (e.g., punch, kick, ground pound) that should result from Mario's contact with the specified object (`o`). Useful for handling different types of player-object collisions, attacks, and object behaviors

### Lua Example
`local integerValue = determine_interaction(m, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 determine_interaction(struct MarioState *m, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [does_mario_have_normal_cap_on_head](#does_mario_have_normal_cap_on_head)

### Description
Checks if Mario is currently wearing his normal cap on his head. Returns true if Mario's flag state matches that of having the normal cap equipped on his head, otherwise false. Useful for determining Mario's cap status

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

### Description
Retrieves the save file flag associated with a door, based on the number of stars required to open it. Used to check if the player has unlocked certain star doors or progressed far enough to access new areas

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

## [get_mario_cap_flag](#get_mario_cap_flag)

### Description
Determines the type of cap an object represents. Depending on the object's behavior, it returns a cap type (normal, metal, wing, vanish). Useful for handling the logic of picking up, wearing, or losing different kinds of caps

### Lua Example
`local integerValue = get_mario_cap_flag(capObject)`

### Parameters
| Field | Type |
| ----- | ---- |
| capObject | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 get_mario_cap_flag(struct Object *capObject);`

[:arrow_up_small:](#)

<br />

## [interact_bbh_entrance](#interact_bbh_entrance)

### Description
Handles Mario's interaction with the Boo's Big Haunt (BBH) entrance object. When Mario tries to enter the BBH area, this function determines the resulting action (e.g., a jump or spin entrance)

### Lua Example
`local integerValue = interact_bbh_entrance(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_bbh_entrance(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_bounce_top](#interact_bounce_top)

### Description
Handles interactions where Mario bounces off the top of an object (e.g., Goombas, Koopas). Checks if Mario attacks the object from above and applies the appropriate knockback, sound effects, and object state changes. Useful for enemy defeat mechanics and platform bouncing

### Lua Example
`local integerValue = interact_bounce_top(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_bounce_top(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_breakable](#interact_breakable)

### Description
Handles interactions with breakable objects (e.g., breakable boxes or bob-ombs). If Mario hits the object with a valid attack (like a punch or kick), the object is destroyed or changes state. Useful for managing collectible items hidden in breakable objects and level progression through destructible blocks or walls

### Lua Example
`local integerValue = interact_breakable(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_breakable(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_bully](#interact_bully)

### Description
Handles interaction with Bully enemies. Determines if Mario attacks the Bully or gets knocked back. Updates Mario's velocity and state accordingly, and can defeat the Bully if attacked successfully. Useful for enemy encounters that involve pushing and shoving mechanics rather than just stomping like the bullies

### Lua Example
`local integerValue = interact_bully(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_bully(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_cannon_base](#interact_cannon_base)

### Description
Handles interaction when Mario touches a cannon base. If the cannon is ready, Mario enters the cannon, triggering a special action and camera behavior. Useful for transitioning to cannon-aiming mode and enabling cannon travel within levels

### Lua Example
`local integerValue = interact_cannon_base(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_cannon_base(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_cap](#interact_cap)

### Description
Handles interaction when Mario picks up a cap object. This includes normal caps, wing caps, vanish caps, and metal caps. Updates Mario's state (e.g., cap timers, sound effects) and may initiate putting on the cap animation. Useful for managing cap statuses

### Lua Example
`local integerValue = interact_cap(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_cap(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_clam_or_bubba](#interact_clam_or_bubba)

### Description
Handles interactions with objects like Clams or Bubbas, which can damage Mario or, in Bubba's case, eat Mario. If Bubba eats Mario, it triggers a unique "caught" action. Otherwise, it deals damage and knockback if hit by a Clam

### Lua Example
`local integerValue = interact_clam_or_bubba(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_clam_or_bubba(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_coin](#interact_coin)

### Description
Handles Mario's interaction with coins. Collecting a coin increases Mario's coin count and heals him slightly. Useful for score, and coin management

### Lua Example
`local integerValue = interact_coin(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_coin(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_damage](#interact_damage)

### Description
Handles damaging interactions from various objects (e.g., enemies, hazards). If Mario takes damage, it applies knockback and reduces health. Useful for enemy attacks, environmental hazards, and managing damage related behaviors

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

## [interact_door](#interact_door)

### Description
Handles interaction when Mario touches a door. If Mario meets the star requirement or has the key, he can unlock/open the door. Otherwise, it may display dialog indicating the requirement. Useful for controlling access to locked areas and providing progression gating in the game

### Lua Example
`local integerValue = interact_door(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_door(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_flame](#interact_flame)

### Description
Handles interaction with flame objects. If Mario touches a flame and is not invulnerable or protected by certain caps, he takes damage and may be set on fire, causing a burning jump. Useful for simulating fire damage and hazards in levels

### Lua Example
`local integerValue = interact_flame(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_flame(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_grabbable](#interact_grabbable)

### Description
Handles interaction with grabbable objects (e.g., crates, small enemies, or Bowser). Checks if Mario can pick up the object and initiates the grab action if possible. Useful for course mechanics, throwing items, and Bowser

### Lua Example
`local integerValue = interact_grabbable(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_grabbable(struct MarioState *m, u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_hit_from_below](#interact_hit_from_below)

### Description
Handles interactions where Mario hits an object from below (e.g., hitting a block from underneath). Determines if Mario damages/destroys the object, or if it damages Mario. Useful for handling upward attacks, hitting coin blocks, or interacting with certain NPCs from below

### Lua Example
`local integerValue = interact_hit_from_below(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_hit_from_below(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_hoot](#interact_hoot)

### Description
Handles interaction with Hoot, the owl. If Mario can grab onto Hoot, this sets Mario onto a riding action, allowing him to fly around the level. Useful for special traversal mechanics and shortcuts within a course

### Lua Example
`local integerValue = interact_hoot(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_hoot(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_igloo_barrier](#interact_igloo_barrier)

### Description
Handles interaction with the igloo barrier found in Snowman's Land. If Mario runs into the barrier, this function pushes him away and prevents passage without the vanish cap. Useful for enforcing require-caps to access certain areas

### Lua Example
`local integerValue = interact_igloo_barrier(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_igloo_barrier(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_koopa_shell](#interact_koopa_shell)

### Description
Handles interaction when Mario touches a Koopa Shell. If conditions are met, Mario can hop onto the shell and start riding it, changing his movement mechanics. Useful for implementing Koopa Shell behavior

### Lua Example
`local integerValue = interact_koopa_shell(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_koopa_shell(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_mr_blizzard](#interact_mr_blizzard)

### Description
Handles interaction with Mr. Blizzard (the snowman enemy) or similar objects. If Mario is attacked or collides with Mr. Blizzard, it applies damage and knockback if not protected or attacking

### Lua Example
`local integerValue = interact_mr_blizzard(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_mr_blizzard(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_player](#interact_player)

### Description
Handles interaction with another player (in multiplayer scenarios). Checks if Mario and another player collide and resolves any special behavior like bouncing on top. Useful for multiplayer interactions, such as PvP or cooperative gameplay mechanics

### Lua Example
`local integerValue = interact_player(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_player(struct MarioState* m, UNUSED u32 interactType, struct Object* o);`

[:arrow_up_small:](#)

<br />

## [interact_pole](#interact_pole)

### Description
Handles interaction with poles (e.g., climbing poles). If Mario runs into a vertical pole, he can grab it and start climbing. Useful for platforming mechanics

### Lua Example
`local integerValue = interact_pole(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_pole(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_shock](#interact_shock)

### Description
Handles interaction with shocking objects. If Mario touches an electrified enemy or hazard, he takes damage and may be stunned or shocked. Useful for electric-themed enemies and obstacles

### Lua Example
`local integerValue = interact_shock(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_shock(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_snufit_bullet](#interact_snufit_bullet)

### Description
Handles interaction with Snufit bullets (projectiles fired by certain enemies). If Mario is not protected, he takes damage. Otherwise, the bullet can be destroyed

### Lua Example
`local integerValue = interact_snufit_bullet(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_snufit_bullet(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_spiny_walking](#interact_spiny_walking)

### Description
Handles interaction with Spiny-walking enemies. If Mario attacks it (e.g., by punching), the enemy is hurt. If he fails to attack properly (say bouncing on top), Mario takes damage and knockback. Useful for enemies that cannot be stomped from above and require direct attacks

### Lua Example
`local integerValue = interact_spiny_walking(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_spiny_walking(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_star_or_key](#interact_star_or_key)

### Description
Handles interaction with Stars or Keys. If Mario collects a star or key, it triggers a specific star grab cutscene and progression is updated. Also handles no-exit variants (like the wing cap stage star). Useful for the main progression system of collecting Stars and unlocking new areas

### Lua Example
`local integerValue = interact_star_or_key(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_star_or_key(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_strong_wind](#interact_strong_wind)

### Description
Handles interaction with strong wind gusts. These gusts push Mario back, often knocking him off platforms or sending him flying backwards. Useful for environmental wind hazards

### Lua Example
`local integerValue = interact_strong_wind(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_strong_wind(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_text](#interact_text)

### Description
Handles interaction with signs, NPCs, and other text-bearing objects. If Mario presses the interact button facing them, he enters a dialog reading state. Useful for managing hints, story elements, or gameplay instructions through in-game dialogue

### Lua Example
`local integerValue = interact_text(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_text(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_tornado](#interact_tornado)

### Description
Handles interaction with tornados. If Mario touches a tornado, he enters a spinning twirl action, losing control temporarily. Useful for desert levels or areas where environmental hazards lift Mario into the air

### Lua Example
`local integerValue = interact_tornado(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_tornado(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_warp](#interact_warp)

### Description
Handles interaction with warps, including warp pipes and hole warps. If Mario steps onto a warp, he either transitions into another area or level. Useful for connecting different parts of the game world and controlling transitions between levels as well as custom warp areas

### Lua Example
`local integerValue = interact_warp(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_warp(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_warp_door](#interact_warp_door)

### Description
Handles interaction with warp doors that lead to other areas or require keys. If Mario can open the door (has enough stars or a key), he proceeds. Otherwise, it may show a dialog. Useful for restricting access to certain areas based on progression

### Lua Example
`local integerValue = interact_warp_door(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_warp_door(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_water_ring](#interact_water_ring)

### Description
Handles interactions with water rings that heal Mario. Passing through water rings increases his health counter. Useful for underwater stages

### Lua Example
`local integerValue = interact_water_ring(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_water_ring(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [interact_whirlpool](#interact_whirlpool)

### Description
Handles interaction with whirlpools. If Mario gets caught in a whirlpool, he's pulled toward it, resulting in a unique "caught" action. Useful for hazards that trap Mario like whirlpools

### Lua Example
`local integerValue = interact_whirlpool(m, interactType, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| interactType | `integer` |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 interact_whirlpool(struct MarioState *m, UNUSED u32 interactType, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [mario_blow_off_cap](#mario_blow_off_cap)

### Description
Makes Mario blow off his normal cap at a given speed. Removes the normal cap from Mario's head and spawns it as a collectible object in the game world. Useful for simulating events where Mario loses his cap due to enemy attacks or environmental forces

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

### Description
Checks if Mario can grab the currently encountered object (usually triggered when Mario punches or dives). If conditions are met, initiates the grabbing process. Useful for picking up objects, throwing enemies, or grabbing special items

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

### Description
Causes Mario to drop the object he is currently holding. Sets the held object's state accordingly and places it in front of Mario. Useful for releasing carried objects, such as throwing Bob-ombs or setting down crates

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

### Description
Returns a collided object that matches a given interaction type from Mario's current collision data. Useful for determining which object Mario has come into contact with

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

### Description
Grabs the object currently referenced by Mario's `usedObj` if it's not already being held. Changes the object's state to indicate it is now held by Mario. Useful for handling the moment Mario successfully picks up an object

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

### Description
Makes Mario lose his normal cap to an enemy, such as Klepto or Ukiki. Updates flags so that the cap is no longer on Mario's head. Returns true if Mario was wearing his normal cap, otherwise false. Useful for scenarios where enemies steal Mario's cap

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

### Description
Calculates the angle between Mario and a specified object. Used for determining Mario's orientation relative to the object. Useful for deciding directions between Mario and NPCs

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

### Description
Retrieves Mario's normal cap if it was previously lost. Removes the cap from Mario's hand state and places it on his head. Useful when Mario recovers his normal cap from enemies, finds it in a level, or if it were to disappear

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

### Description
Causes Mario to stop riding any object (like a shell or Hoot) and also drop any held object. Resets related states to ensure Mario is no longer attached to or holding anything. Useful when changing Mario's state after certain actions, transitions, or to prevent exploits

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

### Description
Stops Mario from riding any currently ridden object (e.g., a Koopa shell or Hoot), updating the object's interaction status and Mario's state. Useful for cleanly dismounting ridden objects

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

### Description
Throws the object Mario is currently holding. The object is placed in front of Mario and given a forward velocity. Useful for attacking enemies with thrown objects, solving puzzles by throwing crates, or interacting with environment items

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

### Description
Checks if the necessary conditions are met for one player to successfully attack another player in a PvP scenario. Considers factors like invincibility, action states, and whether the attack is valid. Useful for multiplayer where players can harm each other

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

## [should_push_or_pull_door](#should_push_or_pull_door)

### Description
Determines whether Mario should push or pull a door when he interacts with it, based on his orientation and position. Useful for animating door interactions realistically, depending on which side Mario approaches from

### Lua Example
`local integerValue = should_push_or_pull_door(m, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 should_push_or_pull_door(struct MarioState *m, struct Object *o);`

[:arrow_up_small:](#)

<br />

## [take_damage_and_knock_back](#take_damage_and_knock_back)

### Description
Handles the logic of Mario taking damage and being knocked back by a damaging object. Decreases Mario's health, sets his knockback state, and triggers appropriate sound and camera effects. Useful for implementing enemy attacks, hazards, and ensuring Mario receives proper feedback upon taking damage

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
# functions from lag_compensation.h

<br />


## [lag_compensation_get_local_state](#lag_compensation_get_local_state)

### Description
Gets the local Mario's state stored in lag compensation history

### Lua Example
`local MarioStateValue = lag_compensation_get_local_state(otherNp)`

### Parameters
| Field | Type |
| ----- | ---- |
| otherNp | [NetworkPlayer](structs.md#NetworkPlayer) |

### Returns
[MarioState](structs.md#MarioState)

### C Prototype
`struct MarioState* lag_compensation_get_local_state(struct NetworkPlayer* otherNp);`

[:arrow_up_small:](#)

<br />

## [lag_compensation_get_local_state_index](#lag_compensation_get_local_state_index)

### Description
Gets the local Mario's state index

### Lua Example
`local integerValue = lag_compensation_get_local_state_index()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 lag_compensation_get_local_state_index(void);`

[:arrow_up_small:](#)

<br />

## [lag_compensation_get_local_state_ready](#lag_compensation_get_local_state_ready)

### Description
Checks if lag compensation history is ready

### Lua Example
`local booleanValue = lag_compensation_get_local_state_ready()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool lag_compensation_get_local_state_ready(void);`

[:arrow_up_small:](#)

<br />

## [lag_compensation_store](#lag_compensation_store)

### Description
Stores the local Mario's current state in lag compensation history

### Lua Example
`lag_compensation_store()`

### Parameters
- None

### Returns
- None

### C Prototype
`void lag_compensation_store(void);`

[:arrow_up_small:](#)

<br />

---
# functions from level_info.h

<br />


## [get_level_name](#get_level_name)

### Description
Returns the name of the level corresponding to `courseNum`, `levelNum` and `areaIndex` as a decapitalized ASCII (human readable) string

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

### Description
Returns the name of the level corresponding to `courseNum`, `levelNum` and `areaIndex` as an ASCII (human readable) string. Set `charCase` to 1 to capitalize or -1 to decapitalize the returned string

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

### Description
Returns the name of the star corresponding to `courseNum` and `starNum` as a decapitalized ASCII (human readable) string

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

### Description
Returns the name of the star corresponding to `courseNum` and `starNum` as an ASCII (human readable) string. Set `charCase` to 1 to capitalize or -1 to decapitalize the returned string

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
# functions from level_script.h

<br />


## [area_create_warp_node](#area_create_warp_node)

### Description
Creates a warp node in the current level and area with id `id` that goes to the warp node `destNode` in level `destLevel` and area `destArea`, and attach it to the object `o`. To work properly, object `o` must be able to trigger a warp (for example, with interact type set to `INTERACT_WARP`.) `checkpoint` should be set only to WARP_NO_CHECKPOINT (0x00) or WARP_CHECKPOINT (0x80.) If `checkpoint` is set to `0x80`, Mario will warp directly to this node if he enters the level again (after a death for example)

### Lua Example
`local ObjectWarpNodeValue = area_create_warp_node(id, destLevel, destArea, destNode, checkpoint, o)`

### Parameters
| Field | Type |
| ----- | ---- |
| id | `integer` |
| destLevel | `integer` |
| destArea | `integer` |
| destNode | `integer` |
| checkpoint | `integer` |
| o | [Object](structs.md#Object) |

### Returns
[ObjectWarpNode](structs.md#ObjectWarpNode)

### C Prototype
`struct ObjectWarpNode *area_create_warp_node(u8 id, u8 destLevel, u8 destArea, u8 destNode, u8 checkpoint, struct Object *o);`

[:arrow_up_small:](#)

<br />

---
# functions from level_update.h

<br />


## [fade_into_special_warp](#fade_into_special_warp)

### Description
Fades into a special warp with `arg` and using `color`

### Lua Example
`fade_into_special_warp(arg, color)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg | `integer` |
| color | `integer` |

### Returns
- None

### C Prototype
`void fade_into_special_warp(u32 arg, u32 color);`

[:arrow_up_small:](#)

<br />

## [get_instant_warp](#get_instant_warp)

### Description
Gets an instant warp from the current area's instant warp array (0-3)

### Lua Example
`local InstantWarpValue = get_instant_warp(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
[InstantWarp](structs.md#InstantWarp)

### C Prototype
`struct InstantWarp *get_instant_warp(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_painting_warp_node](#get_painting_warp_node)

### Description
Gets a painting warp node from the local mario's floor type

### Lua Example
`local WarpNodeValue = get_painting_warp_node()`

### Parameters
- None

### Returns
[WarpNode](structs.md#WarpNode)

### C Prototype
`struct WarpNode *get_painting_warp_node(void);`

[:arrow_up_small:](#)

<br />

## [initiate_painting_warp](#initiate_painting_warp)

### Description
Initiates a painting warp of `paintingIndex`

### Lua Example
`initiate_painting_warp(paintingIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| paintingIndex | `integer` |

### Returns
- None

### C Prototype
`void initiate_painting_warp(s16 paintingIndex);`

[:arrow_up_small:](#)

<br />

## [level_control_timer_running](#level_control_timer_running)

### Description
Returns if the level timer is running

### Lua Example
`local integerValue = level_control_timer_running()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 level_control_timer_running(void);`

[:arrow_up_small:](#)

<br />

## [level_trigger_warp](#level_trigger_warp)

### Description
Triggers a warp (WARP_OP_*) for the level. Pass in `gMarioStates[0]` for `m`

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

## [lvl_set_current_level](#lvl_set_current_level)

### Description
Sets the level number and handles the act select screen

### Lua Example
`local integerValue = lvl_set_current_level(arg0, levelNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |
| levelNum | `integer` |

### Returns
- `integer`

### C Prototype
`s32 lvl_set_current_level(s16 arg0, s16 levelNum);`

[:arrow_up_small:](#)

<br />

## [warp_special](#warp_special)

### Description
Special warps to arg (`SPECIAL_WARP_*`)

### Lua Example
`warp_special(arg)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg | `integer` |

### Returns
- None

### C Prototype
`void warp_special(s32 arg);`

[:arrow_up_small:](#)

<br />

---
# functions from lighting_engine.h

<br />


## [le_add_light](#le_add_light)

### Description
Adds a lighting engine point light at `x`, `y`, `z` with color `r`, `g`, `b` and `radius` with `intensity`

### Lua Example
`local integerValue = le_add_light(x, y, z, r, g, b, radius, intensity)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |
| r | `integer` |
| g | `integer` |
| b | `integer` |
| radius | `number` |
| intensity | `number` |

### Returns
- `integer`

### C Prototype
`s32 le_add_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius, f32 intensity);`

[:arrow_up_small:](#)

<br />

## [le_calculate_lighting_color](#le_calculate_lighting_color)

### Description
Calculates the lighting with `lightIntensityScalar` at a position and outputs the color in `out`

### Lua Example
`le_calculate_lighting_color(pos, out, lightIntensityScalar)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| out | `Color` |
| lightIntensityScalar | `number` |

### Returns
- None

### C Prototype
`void le_calculate_lighting_color(Vec3f pos, Color out, f32 lightIntensityScalar);`

[:arrow_up_small:](#)

<br />

## [le_calculate_lighting_dir](#le_calculate_lighting_dir)

### Description
Calculates the lighting direction from a position and outputs the result in `out`

### Lua Example
`le_calculate_lighting_dir(pos, out)`

### Parameters
| Field | Type |
| ----- | ---- |
| pos | [Vec3f](structs.md#Vec3f) |
| out | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void le_calculate_lighting_dir(Vec3f pos, Vec3f out);`

[:arrow_up_small:](#)

<br />

## [le_get_light_count](#le_get_light_count)

### Description
Gets the total number of lights currently loaded in the lighting engine

### Lua Example
`local integerValue = le_get_light_count()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 le_get_light_count(void);`

[:arrow_up_small:](#)

<br />

## [le_remove_light](#le_remove_light)

### Description
Removes a lighting engine point light corresponding to `id`

### Lua Example
`le_remove_light(id)`

### Parameters
| Field | Type |
| ----- | ---- |
| id | `integer` |

### Returns
- None

### C Prototype
`void le_remove_light(s32 id);`

[:arrow_up_small:](#)

<br />

## [le_set_ambient_color](#le_set_ambient_color)

### Description
Sets the lighting engine ambient color

### Lua Example
`le_set_ambient_color(r, g, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| r | `integer` |
| g | `integer` |
| b | `integer` |

### Returns
- None

### C Prototype
`void le_set_ambient_color(u8 r, u8 g, u8 b);`

[:arrow_up_small:](#)

<br />

## [le_set_light_color](#le_set_light_color)

### Description
Sets a lighting engine point light's color to `r`, `g`, `b`

### Lua Example
`le_set_light_color(id, r, g, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| id | `integer` |
| r | `integer` |
| g | `integer` |
| b | `integer` |

### Returns
- None

### C Prototype
`void le_set_light_color(s32 id, u8 r, u8 g, u8 b);`

[:arrow_up_small:](#)

<br />

## [le_set_light_intensity](#le_set_light_intensity)

### Description
Sets a lighting engine point light's `intensity`

### Lua Example
`le_set_light_intensity(id, intensity)`

### Parameters
| Field | Type |
| ----- | ---- |
| id | `integer` |
| intensity | `number` |

### Returns
- None

### C Prototype
`void le_set_light_intensity(s32 id, f32 intensity);`

[:arrow_up_small:](#)

<br />

## [le_set_light_pos](#le_set_light_pos)

### Description
Sets a lighting engine point light's position to `x`, `y`, `z`

### Lua Example
`le_set_light_pos(id, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| id | `integer` |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- None

### C Prototype
`void le_set_light_pos(s32 id, f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [le_set_light_radius](#le_set_light_radius)

### Description
Sets a lighting engine point light's `radius`

### Lua Example
`le_set_light_radius(id, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| id | `integer` |
| radius | `number` |

### Returns
- None

### C Prototype
`void le_set_light_radius(s32 id, f32 radius);`

[:arrow_up_small:](#)

<br />
---

[< prev](functions-2.md) | [1](functions.md) | [2](functions-2.md) | 3 | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | [next >](functions-4.md)]

