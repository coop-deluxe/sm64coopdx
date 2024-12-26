## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-3.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | 4 | [5](functions-5.md) | [6](functions-6.md) | [next >](functions-5.md)]


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

## [get_credits_str_width](#get_credits_str_width)

### Lua Example
`local integerValue = get_credits_str_width(str)`

### Parameters
| Field | Type |
| ----- | ---- |
| str | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 get_credits_str_width(char *str);`

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

### Description
Behavior init function for NPC Toad

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

### Description
Behavior loop function for NPC Toad

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

### Description
Behavior init function for Star Door unlock object

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

### Description
Behavior loop function for Star Door unlock object

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

### Description
Always returns zero. May have been originally used for beta trampolines

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

### Description
Reflects Mario off a wall if he is colliding with one and flips forward velocity if `negateSpeed` is TRUE

### Lua Example
`mario_bonk_reflection(m, negateSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| negateSpeed | `integer` |

### Returns
- None

### C Prototype
`void mario_bonk_reflection(struct MarioState *m, u8 negateSpeed);`

[:arrow_up_small:](#)

<br />

## [mario_push_off_steep_floor](#mario_push_off_steep_floor)

### Description
Pushes Mario off a steep floor and sets his action to `action` with `actionArg`

### Lua Example
`local integerValue = mario_push_off_steep_floor(m, action, actionArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| action | `integer` |
| actionArg | `integer` |

### Returns
- `integer`

### C Prototype
`u32 mario_push_off_steep_floor(struct MarioState *m, u32 action, u32 actionArg);`

[:arrow_up_small:](#)

<br />

## [mario_update_moving_sand](#mario_update_moving_sand)

### Description
Pushes Mario in the direction of the quicksand based on the floor surface

### Lua Example
`local integerValue = mario_update_moving_sand(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u32 mario_update_moving_sand(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [mario_update_quicksand](#mario_update_quicksand)

### Description
Updates Mario's state in quicksand, sinks him at `sinkingSpeed` if he's in non instant quicksand

### Lua Example
`local integerValue = mario_update_quicksand(m, sinkingSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| sinkingSpeed | `number` |

### Returns
- `integer`

### C Prototype
`u32 mario_update_quicksand(struct MarioState *m, f32 sinkingSpeed);`

[:arrow_up_small:](#)

<br />

## [mario_update_windy_ground](#mario_update_windy_ground)

### Description
Pushes Mario in the direction of the wind based on the floor surface

### Lua Example
`local integerValue = mario_update_windy_ground(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u32 mario_update_windy_ground(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [perform_air_step](#perform_air_step)

### Description
Performs a full Mario air physics step (4 substeps) and returns an `AIR_STEP_*` result

### Lua Example
`local integerValue = perform_air_step(m, stepArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| stepArg | `integer` |

### Returns
- `integer`

### C Prototype
`s32 perform_air_step(struct MarioState *m, u32 stepArg);`

[:arrow_up_small:](#)

<br />

## [perform_ground_step](#perform_ground_step)

### Description
Performs a full Mario ground physics step (4 substeps) and returns an `GROUND_STEP_*` result

### Lua Example
`local integerValue = perform_ground_step(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 perform_ground_step(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [set_vel_from_pitch_and_yaw](#set_vel_from_pitch_and_yaw)

### Description
Sets Mario's velocity to his forward velocity multiplied by the cosine and sine of his pitch and yaw

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

### Description
Performs a full Mario stationary physics step (4 substeps) and returns an `GROUND_STEP_*` result

### Lua Example
`local integerValue = stationary_ground_step(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 stationary_ground_step(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

## [stop_and_set_height_to_floor](#stop_and_set_height_to_floor)

### Description
Sets all of Mario's velocity variables to 0 and sets his Y position to the floor height

### Lua Example
`stop_and_set_height_to_floor(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void stop_and_set_height_to_floor(struct MarioState *m);`

[:arrow_up_small:](#)

<br />

---
# functions from math_util.h

<br />


## [anim_spline_init](#anim_spline_init)

### Description
Initializes a spline-based animation for the `MarioState` structure `m` using the provided array of 3D signed-integer vectors `keyFrames`. This sets up the animation so that it can be advanced by polling

### Lua Example
`anim_spline_init(m, keyFrames)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| keyFrames | `Pointer` <`Vec4s`> |

### Returns
- None

### C Prototype
`void anim_spline_init(struct MarioState* m, Vec4s *keyFrames);`

[:arrow_up_small:](#)

<br />

## [anim_spline_poll](#anim_spline_poll)

### Description
Advances the spline-based animation associated with `m` and stores the current interpolated position in `result`. It returns the animation's status, allowing the caller to determine if the animation is ongoing or has completed

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

### Description
Similar to `approach_s32`, but operates on floating-point numbers. It moves `current` toward `target` by increasing it by `inc` if below target, or decreasing it by `dec` if above target, creating a smooth interpolation

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

### Description
Gradually moves an integer `current` value toward a `target` value, increasing it by `inc` if it is too low, or decreasing it by `dec` if it is too high. This is often used for smooth transitions or animations

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

## [atan2s](#atan2s)

### Description
Computes the arctangent of y/x and returns the angle as a signed 16-bit integer, typically representing a direction in the SM64 fixed-point angle format. This can be used to find an angle between x and y coordinates

### Lua Example
`local integerValue = atan2s(y, x)`

### Parameters
| Field | Type |
| ----- | ---- |
| y | `number` |
| x | `number` |

### Returns
- `integer`

### C Prototype
`s16 atan2s(f32 y, f32 x);`

[:arrow_up_small:](#)

<br />

## [coss](#coss)

### Description
Calculates the cosine of the given angle, where the angle is specified as a signed 16-bit integer representing a fixed-point "SM64 angle". The function returns a floating-point value corresponding to cos(angle)

### Lua Example
`local numberValue = coss(sm64Angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| sm64Angle | `integer` |

### Returns
- `number`

### C Prototype
`f32 coss(s16 sm64Angle);`

[:arrow_up_small:](#)

<br />

## [find_vector_perpendicular_to_plane](#find_vector_perpendicular_to_plane)

### Description
Determines a vector that is perpendicular (normal) to the plane defined by three given 3D floating-point points `a`, `b`, and `c`. The resulting perpendicular vector is stored in `dest`

### Lua Example
`local voidValue = find_vector_perpendicular_to_plane(dest, a, b, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |
| c | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c);`

[:arrow_up_small:](#)

<br />

## [get_pos_from_transform_mtx](#get_pos_from_transform_mtx)

### Description
Extracts the position (translation component) from the transformation matrix `objMtx` relative to the coordinate system defined by `camMtx` and stores that 3D position in `dest`. This can be used to get the object's coordinates in camera space

### Lua Example
`get_pos_from_transform_mtx(dest, objMtx, camMtx)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| objMtx | `Mat4` |
| camMtx | `Mat4` |

### Returns
- None

### C Prototype
`void get_pos_from_transform_mtx(Vec3f dest, Mat4 objMtx, Mat4 camMtx);`

[:arrow_up_small:](#)

<br />

## [mtxf_align_terrain_normal](#mtxf_align_terrain_normal)

### Description
Aligns `dest` so that it fits the orientation of a terrain surface defined by its normal vector `upDir`. The transformation is positioned at `pos` and oriented with a given `yaw`. This is often used to make objects sit naturally on uneven ground

### Lua Example
`mtxf_align_terrain_normal(dest, upDir, pos, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| upDir | [Vec3f](structs.md#Vec3f) |
| pos | [Vec3f](structs.md#Vec3f) |
| yaw | `integer` |

### Returns
- None

### C Prototype
`void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw);`

[:arrow_up_small:](#)

<br />

## [mtxf_align_terrain_triangle](#mtxf_align_terrain_triangle)

### Description
Aligns `mtx` to fit onto a terrain triangle at `pos`, applying a given `yaw` and scaling by `radius`. This helps position objects so they match the orientation of the terrain's surface

### Lua Example
`mtxf_align_terrain_triangle(mtx, pos, yaw, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| mtx | `Mat4` |
| pos | [Vec3f](structs.md#Vec3f) |
| yaw | `integer` |
| radius | `number` |

### Returns
- None

### C Prototype
`void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, s16 yaw, f32 radius);`

[:arrow_up_small:](#)

<br />

## [mtxf_billboard](#mtxf_billboard)

### Description
Transforms a 4x4 floating-point matrix `mtx` into a "billboard" oriented toward the camera or a given direction. The billboard is placed at `position` and rotated by `angle`. This is useful for objects that should always face the viewer

### Lua Example
`mtxf_billboard(dest, mtx, position, angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| mtx | `Mat4` |
| position | [Vec3f](structs.md#Vec3f) |
| angle | `integer` |

### Returns
- None

### C Prototype
`void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);`

[:arrow_up_small:](#)

<br />

## [mtxf_copy](#mtxf_copy)

### Description
Copies the 4x4 floating-point matrix `src` into `dest`. After this operation, `dest` contains the same matrix values as `src`

### Lua Example
`mtxf_copy(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| src | `Mat4` |

### Returns
- None

### C Prototype
`void mtxf_copy(Mat4 dest, Mat4 src);`

[:arrow_up_small:](#)

<br />

## [mtxf_cylboard](#mtxf_cylboard)

### Description
Creates a "cylindrical billboard" transformation from the 4x4 matrix `mtx` placed at `position` with a given `angle`. Unlike a full billboard, this might allow rotation around one axis while still facing the viewer on others

### Lua Example
`mtxf_cylboard(dest, mtx, position, angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| mtx | `Mat4` |
| position | [Vec3f](structs.md#Vec3f) |
| angle | `integer` |

### Returns
- None

### C Prototype
`void mtxf_cylboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);`

[:arrow_up_small:](#)

<br />

## [mtxf_identity](#mtxf_identity)

### Description
Sets the 4x4 floating-point matrix `mtx` to the identity matrix. The identity matrix leaves points unchanged when they are transformed by it which is useful for matrix math

### Lua Example
`mtxf_identity(mtx)`

### Parameters
| Field | Type |
| ----- | ---- |
| mtx | `Mat4` |

### Returns
- None

### C Prototype
`void mtxf_identity(Mat4 mtx);`

[:arrow_up_small:](#)

<br />

## [mtxf_inverse](#mtxf_inverse)

### Description
Inverts the 4x4 floating-point matrix `src` and stores the inverse in `dest`. Applying the inverse transformation undoes whatever `src` did, returning points back to their original coordinate space

### Lua Example
`mtxf_inverse(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| src | `Mat4` |

### Returns
- None

### C Prototype
`void mtxf_inverse(Mat4 dest, Mat4 src);`

[:arrow_up_small:](#)

<br />

## [mtxf_lookat](#mtxf_lookat)

### Description
Adjusts the 4x4 floating-point matrix `mtx` so that it represents a viewing transformation looking from the point `from` toward the point `to`, with a given roll angle. This creates a view matrix oriented toward `to`

### Lua Example
`mtxf_lookat(mtx, from, to, roll)`

### Parameters
| Field | Type |
| ----- | ---- |
| mtx | `Mat4` |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| roll | `integer` |

### Returns
- None

### C Prototype
`void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, s16 roll);`

[:arrow_up_small:](#)

<br />

## [mtxf_mul](#mtxf_mul)

### Description
Multiplies two 4x4 floating-point matrices `a` and `b` (in that order), storing the product in `dest`. This can be used for combining multiple transformations into one

### Lua Example
`mtxf_mul(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| a | `Mat4` |
| b | `Mat4` |

### Returns
- None

### C Prototype
`void mtxf_mul(Mat4 dest, Mat4 a, Mat4 b);`

[:arrow_up_small:](#)

<br />

## [mtxf_mul_vec3s](#mtxf_mul_vec3s)

### Description
Multiplies the 4x4 floating-point matrix `mtx` by a 3D signed-integer vector `b`, potentially interpreting `b` as angles or translations depending on usage, and modifies `mtx` accordingly

### Lua Example
`mtxf_mul_vec3s(mtx, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| mtx | `Mat4` |
| b | [Vec3s](structs.md#Vec3s) |

### Returns
- None

### C Prototype
`void mtxf_mul_vec3s(Mat4 mtx, Vec3s b);`

[:arrow_up_small:](#)

<br />

## [mtxf_rotate_xyz_and_translate](#mtxf_rotate_xyz_and_translate)

### Description
Rotates `dest` using angles in XYZ order, and then translates it by the 3D floating-point vector `b` and applies the rotations described by `c`. This sets up `dest` with a specific orientation and position in space

### Lua Example
`mtxf_rotate_xyz_and_translate(dest, b, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| b | [Vec3f](structs.md#Vec3f) |
| c | [Vec3s](structs.md#Vec3s) |

### Returns
- None

### C Prototype
`void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f b, Vec3s c);`

[:arrow_up_small:](#)

<br />

## [mtxf_rotate_zxy_and_translate](#mtxf_rotate_zxy_and_translate)

### Description
Rotates `dest` according to the angles in `rotate` using ZXY order, and then translates it by the 3D floating-point vector `translate`. This effectively positions and orients `dest` in 3D space

### Lua Example
`mtxf_rotate_zxy_and_translate(dest, translate, rotate)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| translate | [Vec3f](structs.md#Vec3f) |
| rotate | [Vec3s](structs.md#Vec3s) |

### Returns
- None

### C Prototype
`void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3s rotate);`

[:arrow_up_small:](#)

<br />

## [mtxf_scale_vec3f](#mtxf_scale_vec3f)

### Description
Scales the 4x4 floating-point matrix `mtx` by the scaling factors found in the 3D floating-point vector `s`, and stores the result in `dest`. This enlarges or shrinks objects in 3D space

### Lua Example
`mtxf_scale_vec3f(dest, mtx, s)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| mtx | `Mat4` |
| s | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s);`

[:arrow_up_small:](#)

<br />

## [mtxf_translate](#mtxf_translate)

### Description
Applies a translation to the 4x4 floating-point matrix `dest` by adding the coordinates in the 3D floating-point vector `b`. This shifts any transformed point by `b`

### Lua Example
`mtxf_translate(dest, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void mtxf_translate(Mat4 dest, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [not_zero](#not_zero)

### Description
Checks if `value` is zero. If not, it returns `value`. If it is zero, it returns the `replacement` value. This function ensures that a zero value can be substituted with a fallback value if needed

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

## [sins](#sins)

### Description
Calculates the sine of the given angle, where the angle is specified as a signed 16-bit integer representing a fixed-point "SM64 angle". This function returns a floating-point result corresponding to sin(angle)

### Lua Example
`local numberValue = sins(sm64Angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| sm64Angle | `integer` |

### Returns
- `number`

### C Prototype
`f32 sins(s16 sm64Angle);`

[:arrow_up_small:](#)

<br />

## [spline_get_weights](#spline_get_weights)

### Description
Computes spline interpolation weights for a given parameter `t` and stores these weights in `result`. This is used in spline-based animations to find intermediate positions between keyframes

### Lua Example
`spline_get_weights(m, result, t, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| result | `Vec4f` |
| t | `number` |
| c | `integer` |

### Returns
- None

### C Prototype
`void spline_get_weights(struct MarioState* m, Vec4f result, f32 t, UNUSED s32 c);`

[:arrow_up_small:](#)

<br />

## [vec3f_add](#vec3f_add)

### Description
Adds the components of the 3D floating-point vector `a` to `dest`. After this operation, `dest.x` will be `dest.x + a.x`, and similarly for the y and z components

### Lua Example
`local voidValue = vec3f_add(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_add(Vec3f dest, Vec3f a);`

[:arrow_up_small:](#)

<br />

## [vec3f_combine](#vec3f_combine)

### Description
Takes two 3D floating-point vectors `vecA` and `vecB`, multiplies them by `sclA` and `sclB` respectively, and then adds the scaled vectors together. The final combined vector is stored in `dest`

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

## [vec3f_copy](#vec3f_copy)

### Description
Copies the contents of a 3D floating-point vector (`src`) into another 3D floating-point vector (`dest`). After this operation, `dest` will have the same x, y, and z values as `src`

### Lua Example
`local voidValue = vec3f_copy(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| src | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_copy(Vec3f dest, Vec3f src);`

[:arrow_up_small:](#)

<br />

## [vec3f_cross](#vec3f_cross)

### Description
Computes the cross product of two 3D floating-point vectors `a` and `b`. The cross product is a vector perpendicular to both `a` and `b`. The result is stored in `dest`

### Lua Example
`local voidValue = vec3f_cross(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_cross(Vec3f dest, Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [vec3f_dif](#vec3f_dif)

### Description
Subtracts the components of the 3D floating-point vector `b` from the components of `a` and stores the result in `dest`. For example, `dest.x = a.x - b.x` This results in a vector that represents the difference between `a` and `b`.

### Lua Example
`local voidValue = vec3f_dif(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_dif(Vec3f dest, Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [vec3f_dist](#vec3f_dist)

### Description
Calculates the distance between two 3D floating-point points `v1` and `v2`. The distance is the length of the vector `v2 - v1`, i.e., sqrt((v2.x - v1.x)² + (v2.y - v1.y)² + (v2.z - v1.z)²)

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

### Description
Computes the dot product of the two 3D floating-point vectors `a` and `b`. The dot product is a scalar value defined by (a.x * b.x + a.y * b.y + a.z * b.z), representing how aligned the two vectors are

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

### Description
Calculates the distance between two points in 3D space (`from` and `to`), as well as the pitch and yaw angles that describe the direction from `from` to `to`. The results are stored in `dist`, `pitch`, and `yaw`

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

### Description
Calculates the length (magnitude) of the 3D floating-point vector `a`. The length is defined as sqrt(x² + y² + z²) for the vector components (x, y, z)

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

## [vec3f_mul](#vec3f_mul)

### Description
Multiplies each component of the 3D floating-point vector `dest` by the scalar value `a`. For instance, `dest.x = dest.x * a`, and similarly for y and z. This scales the vector `dest` by `a`

### Lua Example
`local voidValue = vec3f_mul(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | `number` |

### Returns
- `void *`

### C Prototype
`void *vec3f_mul(Vec3f dest, f32 a);`

[:arrow_up_small:](#)

<br />

## [vec3f_normalize](#vec3f_normalize)

### Description
Normalizes the 3D floating-point vector `dest` so that its length (magnitude) becomes 1, while retaining its direction. This effectively scales `dest` so that it lies on the unit sphere

### Lua Example
`local voidValue = vec3f_normalize(dest)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_normalize(Vec3f dest);`

[:arrow_up_small:](#)

<br />

## [vec3f_project](#vec3f_project)

### Description
Projects the 3D floating-point vector `vec` onto another 3D floating-point vector `onto`. The resulting projection, stored in `out`, represents how much of `vec` lies along the direction of `onto`

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

## [vec3f_rotate_zxy](#vec3f_rotate_zxy)

### Description
Rotates the 3D floating-point vector `v` by the angles specified in the 3D signed-integer vector `rotate`, applying the rotations in the order Z, then X, then Y. The rotated vector replaces `v`

### Lua Example
`local voidValue = vec3f_rotate_zxy(v, rotate)`

### Parameters
| Field | Type |
| ----- | ---- |
| v | [Vec3f](structs.md#Vec3f) |
| rotate | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3f_rotate_zxy(Vec3f v, Vec3s rotate);`

[:arrow_up_small:](#)

<br />

## [vec3f_set](#vec3f_set)

### Description
Sets the values of the 3D floating-point vector `dest` to the given x, y, and z values. After this function, `dest` will have values (x, y, z)

### Lua Example
`local voidValue = vec3f_set(dest, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- `void *`

### C Prototype
`void *vec3f_set(Vec3f dest, f32 x, f32 y, f32 z);`

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

## [vec3f_sum](#vec3f_sum)

### Description
Adds the corresponding components of two 3D floating-point vectors `a` and `b`, and stores the result in `dest`. For example, `dest.x = a.x + b.x`, `dest.y = a.y + b.y`, and `dest.z = a.z + b.z`

### Lua Example
`local voidValue = vec3f_sum(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_sum(Vec3f dest, Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [vec3f_to_vec3s](#vec3f_to_vec3s)

### Description
Converts a 3D floating-point vector `a` (Vec3f) into a 3D signed-integer vector and stores it in `dest`. After this operation, `dest` will contain the integer versions of `a`'s floating-point components

### Lua Example
`local voidValue = vec3f_to_vec3s(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_to_vec3s(Vec3s dest, Vec3f a);`

[:arrow_up_small:](#)

<br />

## [vec3s_add](#vec3s_add)

### Description
Adds the components of a 3D signed-integer vector `a` to the corresponding components of `dest`. After this operation, each component of `dest` is increased by the corresponding component in `a`

### Lua Example
`local voidValue = vec3s_add(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3s_add(Vec3s dest, Vec3s a);`

[:arrow_up_small:](#)

<br />

## [vec3s_copy](#vec3s_copy)

### Description
Copies the components of one 3D signed-integer vector (`src`) to another (`dest`). After this function, `dest` will have the same x, y, and z integer values as `src`

### Lua Example
`local voidValue = vec3s_copy(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| src | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3s_copy(Vec3s dest, Vec3s src);`

[:arrow_up_small:](#)

<br />

## [vec3s_set](#vec3s_set)

### Description
Sets the 3D signed-integer vector `dest` to the specified integer values (x, y, z), so that `dest` becomes (x, y, z).

### Lua Example
`local voidValue = vec3s_set(dest, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| x | `integer` |
| y | `integer` |
| z | `integer` |

### Returns
- `void *`

### C Prototype
`void *vec3s_set(Vec3s dest, s16 x, s16 y, s16 z);`

[:arrow_up_small:](#)

<br />

## [vec3s_sum](#vec3s_sum)

### Description
Adds the components of two 3D signed-integer vectors `a` and `b` together and stores the resulting vector in `dest`. For example, `dest.x = a.x + b.x`, and similarly for y and z

### Lua Example
`local voidValue = vec3s_sum(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |
| b | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3s_sum(Vec3s dest, Vec3s a, Vec3s b);`

[:arrow_up_small:](#)

<br />

## [vec3s_to_vec3f](#vec3s_to_vec3f)

### Description
Converts a 3D signed-integer vector `a` (vec3s) into a 3D floating-point vector and stores it in `dest`. After this operation, `dest` will contain the floating-point equivalents of `a`'s integer components

### Lua Example
`local voidValue = vec3s_to_vec3f(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3s_to_vec3f(Vec3f dest, Vec3s a);`

[:arrow_up_small:](#)

<br />

---
# functions from misc.h

<br />


## [update_all_mario_stars](#update_all_mario_stars)

### Description
Updates every Mario state's star count with the save file total star count

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


## [mod_storage_clear](#mod_storage_clear)

### Description
Clears the mod's data from mod storage

### Lua Example
`local booleanValue = mod_storage_clear()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool mod_storage_clear(void);`

[:arrow_up_small:](#)

<br />

## [mod_storage_exists](#mod_storage_exists)

### Description
Checks if a `key` is in mod storage

### Lua Example
`local booleanValue = mod_storage_exists(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_exists(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_load](#mod_storage_load)

### Description
Loads a string `value` from a `key` in mod storage

### Lua Example
`local stringValue = mod_storage_load(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `string`

### C Prototype
`const char *mod_storage_load(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_load_bool](#mod_storage_load_bool)

### Description
Loads a bool `value` from a `key` in mod storage

### Lua Example
`local booleanValue = mod_storage_load_bool(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_load_bool(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_load_number](#mod_storage_load_number)

### Description
Loads a float `value` from a `key` in mod storage

### Lua Example
`local numberValue = mod_storage_load_number(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `number`

### C Prototype
`f32 mod_storage_load_number(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_remove](#mod_storage_remove)

### Description
Removes a `key` from mod storage

### Lua Example
`local booleanValue = mod_storage_remove(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_remove(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_save](#mod_storage_save)

### Description
Saves a `key` corresponding to a string `value` to mod storage

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
`bool mod_storage_save(const char* key, const char* value);`

[:arrow_up_small:](#)

<br />

## [mod_storage_save_bool](#mod_storage_save_bool)

### Description
Saves a `key` corresponding to a bool `value` to mod storage

### Lua Example
`local booleanValue = mod_storage_save_bool(key, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |
| value | `boolean` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_save_bool(const char* key, bool value);`

[:arrow_up_small:](#)

<br />

## [mod_storage_save_number](#mod_storage_save_number)

### Description
Saves a `key` corresponding to a float `value` to mod storage

### Lua Example
`local booleanValue = mod_storage_save_number(key, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |
| value | `number` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_save_number(const char* key, f32 value);`

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

## [network_player_is_override_palette_same](#network_player_is_override_palette_same)

### Lua Example
`local booleanValue = network_player_is_override_palette_same(np)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |

### Returns
- `boolean`

### C Prototype
`bool network_player_is_override_palette_same(struct NetworkPlayer *np);`

[:arrow_up_small:](#)

<br />

## [network_player_reset_override_palette](#network_player_reset_override_palette)

### Lua Example
`network_player_reset_override_palette(np)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |

### Returns
- None

### C Prototype
`void network_player_reset_override_palette(struct NetworkPlayer *np);`

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

## [network_player_set_override_location](#network_player_set_override_location)

### Lua Example
`network_player_set_override_location(np, location)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |
| location | `string` |

### Returns
- None

### C Prototype
`void network_player_set_override_location(struct NetworkPlayer *np, const char *location);`

[:arrow_up_small:](#)

<br />

## [network_player_set_override_palette_color](#network_player_set_override_palette_color)

### Lua Example
`network_player_set_override_palette_color(np, part, color)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |
| part | [enum PlayerPart](constants.md#enum-PlayerPart) |
| color | `Color` |

### Returns
- None

### C Prototype
`void network_player_set_override_palette_color(struct NetworkPlayer *np, enum PlayerPart part, Color color);`

[:arrow_up_small:](#)

<br />

---
# functions from network_utils.h

<br />


## [network_check_singleplayer_pause](#network_check_singleplayer_pause)

### Description
Checks if the game can currently be paused in singleplayer

### Lua Example
`local booleanValue = network_check_singleplayer_pause()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool network_check_singleplayer_pause(void);`

[:arrow_up_small:](#)

<br />

## [network_discord_id_from_local_index](#network_discord_id_from_local_index)

### Description
Gets a Discord ID corresponding to the network player with `localIndex`

### Lua Example
`local stringValue = network_discord_id_from_local_index(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `string`

### C Prototype
`const char* network_discord_id_from_local_index(u8 localIndex);`

[:arrow_up_small:](#)

<br />

## [network_get_player_text_color_string](#network_get_player_text_color_string)

### Description
Gets the DJUI hex color code string for the player corresponding to `localIndex`'s cap color

### Lua Example
`local stringValue = network_get_player_text_color_string(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `string`

### C Prototype
`const char* network_get_player_text_color_string(u8 localIndex);`

[:arrow_up_small:](#)

<br />

## [network_global_index_from_local](#network_global_index_from_local)

### Description
Gets a player's global index from their local index

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

### Description
Checks if you are a moderator in the current lobby

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

### Description
Checks if you are hosting the current lobby, this value doesn't change

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

### Description
Gets a player's local index from their global index

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

## [is_point_within_radius_of_any_player](#is_point_within_radius_of_any_player)

### Lua Example
`local integerValue = is_point_within_radius_of_any_player(x, y, z, dist)`

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
`s8 is_point_within_radius_of_any_player(f32 x, f32 y, f32 z, s32 dist);`

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

## [nearest_possible_mario_state_to_object](#nearest_possible_mario_state_to_object)

### Lua Example
`local MarioStateValue = nearest_possible_mario_state_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[MarioState](structs.md#MarioState)

### C Prototype
`struct MarioState* nearest_possible_mario_state_to_object(struct Object *obj);`

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
# functions from obj_behaviors_2.c

<br />


## [approach_f32_ptr](#approach_f32_ptr)

### Lua Example
`local integerValue = approach_f32_ptr(px, target, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| px | `Pointer` <`number`> |
| target | `number` |
| delta | `number` |

### Returns
- `integer`

### C Prototype
`s32 approach_f32_ptr(f32 *px, f32 target, f32 delta);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_anim_and_check_if_end](#cur_obj_init_anim_and_check_if_end)

### Lua Example
`local integerValue = cur_obj_init_anim_and_check_if_end(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_init_anim_and_check_if_end(s32 arg0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_anim_check_frame](#cur_obj_init_anim_check_frame)

### Lua Example
`local integerValue = cur_obj_init_anim_check_frame(arg0, arg1)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |
| arg1 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_init_anim_check_frame(s32 arg0, s32 arg1);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_anim_extend](#cur_obj_init_anim_extend)

### Lua Example
`cur_obj_init_anim_extend(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_anim_extend(s32 arg0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_play_sound_at_anim_range](#cur_obj_play_sound_at_anim_range)

### Lua Example
`local integerValue = cur_obj_play_sound_at_anim_range(arg0, arg1, sound)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |
| arg1 | `integer` |
| sound | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_play_sound_at_anim_range(s8 arg0, s8 arg1, u32 sound);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_anim_if_at_end](#cur_obj_set_anim_if_at_end)

### Lua Example
`local integerValue = cur_obj_set_anim_if_at_end(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_set_anim_if_at_end(s32 arg0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spin_all_dimensions](#cur_obj_spin_all_dimensions)

### Lua Example
`cur_obj_spin_all_dimensions(arg0, arg1)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `number` |
| arg1 | `number` |

### Returns
- None

### C Prototype
`void cur_obj_spin_all_dimensions(f32 arg0, f32 arg1);`

[:arrow_up_small:](#)

<br />

## [obj_act_knockback](#obj_act_knockback)

### Lua Example
`obj_act_knockback(baseScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| baseScale | `number` |

### Returns
- None

### C Prototype
`void obj_act_knockback(UNUSED f32 baseScale);`

[:arrow_up_small:](#)

<br />

## [obj_act_squished](#obj_act_squished)

### Lua Example
`obj_act_squished(baseScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| baseScale | `number` |

### Returns
- None

### C Prototype
`void obj_act_squished(f32 baseScale);`

[:arrow_up_small:](#)

<br />

## [obj_bounce_off_walls_edges_objects](#obj_bounce_off_walls_edges_objects)

### Lua Example
`local integerValue = obj_bounce_off_walls_edges_objects(targetYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 obj_bounce_off_walls_edges_objects(s32 *targetYaw);`

[:arrow_up_small:](#)

<br />

## [obj_check_attacks](#obj_check_attacks)

### Lua Example
`local integerValue = obj_check_attacks(hitbox, attackedMarioAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| hitbox | [ObjectHitbox](structs.md#ObjectHitbox) |
| attackedMarioAction | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_check_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction);`

[:arrow_up_small:](#)

<br />

## [obj_compute_vel_from_move_pitch](#obj_compute_vel_from_move_pitch)

### Lua Example
`obj_compute_vel_from_move_pitch(speed)`

### Parameters
| Field | Type |
| ----- | ---- |
| speed | `number` |

### Returns
- None

### C Prototype
`void obj_compute_vel_from_move_pitch(f32 speed);`

[:arrow_up_small:](#)

<br />

## [obj_die_if_above_lava_and_health_non_positive](#obj_die_if_above_lava_and_health_non_positive)

### Lua Example
`local integerValue = obj_die_if_above_lava_and_health_non_positive()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 obj_die_if_above_lava_and_health_non_positive(void);`

[:arrow_up_small:](#)

<br />

## [obj_die_if_health_non_positive](#obj_die_if_health_non_positive)

### Lua Example
`obj_die_if_health_non_positive()`

### Parameters
- None

### Returns
- None

### C Prototype
`void obj_die_if_health_non_positive(void);`

[:arrow_up_small:](#)

<br />

## [obj_face_pitch_approach](#obj_face_pitch_approach)

### Lua Example
`local integerValue = obj_face_pitch_approach(targetPitch, deltaPitch)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetPitch | `integer` |
| deltaPitch | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_face_pitch_approach(s16 targetPitch, s16 deltaPitch);`

[:arrow_up_small:](#)

<br />

## [obj_face_roll_approach](#obj_face_roll_approach)

### Lua Example
`local integerValue = obj_face_roll_approach(targetRoll, deltaRoll)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetRoll | `integer` |
| deltaRoll | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_face_roll_approach(s16 targetRoll, s16 deltaRoll);`

[:arrow_up_small:](#)

<br />

## [obj_face_yaw_approach](#obj_face_yaw_approach)

### Lua Example
`local integerValue = obj_face_yaw_approach(targetYaw, deltaYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `integer` |
| deltaYaw | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_face_yaw_approach(s16 targetYaw, s16 deltaYaw);`

[:arrow_up_small:](#)

<br />

## [obj_forward_vel_approach](#obj_forward_vel_approach)

### Lua Example
`local integerValue = obj_forward_vel_approach(target, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `number` |
| delta | `number` |

### Returns
- `integer`

### C Prototype
`s32 obj_forward_vel_approach(f32 target, f32 delta);`

[:arrow_up_small:](#)

<br />

## [obj_get_pitch_from_vel](#obj_get_pitch_from_vel)

### Lua Example
`local integerValue = obj_get_pitch_from_vel()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 obj_get_pitch_from_vel(void);`

[:arrow_up_small:](#)

<br />

## [obj_get_pitch_to_home](#obj_get_pitch_to_home)

### Lua Example
`local integerValue = obj_get_pitch_to_home(latDistToHome)`

### Parameters
| Field | Type |
| ----- | ---- |
| latDistToHome | `number` |

### Returns
- `integer`

### C Prototype
`s16 obj_get_pitch_to_home(f32 latDistToHome);`

[:arrow_up_small:](#)

<br />

## [obj_grow_then_shrink](#obj_grow_then_shrink)

### Lua Example
`local integerValue = obj_grow_then_shrink(scaleVel, shootFireScale, endScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| scaleVel | `Pointer` <`number`> |
| shootFireScale | `number` |
| endScale | `number` |

### Returns
- `integer`

### C Prototype
`s32 obj_grow_then_shrink(f32 *scaleVel, f32 shootFireScale, f32 endScale);`

[:arrow_up_small:](#)

<br />

## [obj_handle_attacks](#obj_handle_attacks)

### Lua Example
`local integerValue = obj_handle_attacks(hitbox, attackedMarioAction, attackHandlers)`

### Parameters
| Field | Type |
| ----- | ---- |
| hitbox | [ObjectHitbox](structs.md#ObjectHitbox) |
| attackedMarioAction | `integer` |
| attackHandlers | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 obj_handle_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction, u8 *attackHandlers);`

[:arrow_up_small:](#)

<br />

## [obj_is_near_to_and_facing_mario](#obj_is_near_to_and_facing_mario)

### Lua Example
`local integerValue = obj_is_near_to_and_facing_mario(m, maxDist, maxAngleDiff)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| maxDist | `number` |
| maxAngleDiff | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_is_near_to_and_facing_mario(struct MarioState* m, f32 maxDist, s16 maxAngleDiff);`

[:arrow_up_small:](#)

<br />

## [obj_is_rendering_enabled](#obj_is_rendering_enabled)

### Lua Example
`local integerValue = obj_is_rendering_enabled()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 obj_is_rendering_enabled(void);`

[:arrow_up_small:](#)

<br />

## [obj_move_for_one_second](#obj_move_for_one_second)

### Lua Example
`local integerValue = obj_move_for_one_second(endAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| endAction | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_move_for_one_second(s32 endAction);`

[:arrow_up_small:](#)

<br />

## [obj_move_pitch_approach](#obj_move_pitch_approach)

### Lua Example
`local integerValue = obj_move_pitch_approach(target, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `integer` |
| delta | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_move_pitch_approach(s16 target, s16 delta);`

[:arrow_up_small:](#)

<br />

## [obj_random_fixed_turn](#obj_random_fixed_turn)

### Lua Example
`local integerValue = obj_random_fixed_turn(delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| delta | `integer` |

### Returns
- `integer`

### C Prototype
`s16 obj_random_fixed_turn(s16 delta);`

[:arrow_up_small:](#)

<br />

## [obj_resolve_collisions_and_turn](#obj_resolve_collisions_and_turn)

### Lua Example
`local integerValue = obj_resolve_collisions_and_turn(targetYaw, turnSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `integer` |
| turnSpeed | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_resolve_collisions_and_turn(s16 targetYaw, s16 turnSpeed);`

[:arrow_up_small:](#)

<br />

## [obj_resolve_object_collisions](#obj_resolve_object_collisions)

### Lua Example
`local integerValue = obj_resolve_object_collisions(targetYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 obj_resolve_object_collisions(s32 *targetYaw);`

[:arrow_up_small:](#)

<br />

## [obj_roll_to_match_yaw_turn](#obj_roll_to_match_yaw_turn)

### Lua Example
`obj_roll_to_match_yaw_turn(targetYaw, maxRoll, rollSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `integer` |
| maxRoll | `integer` |
| rollSpeed | `integer` |

### Returns
- None

### C Prototype
`void obj_roll_to_match_yaw_turn(s16 targetYaw, s16 maxRoll, s16 rollSpeed);`

[:arrow_up_small:](#)

<br />

## [obj_rotate_yaw_and_bounce_off_walls](#obj_rotate_yaw_and_bounce_off_walls)

### Lua Example
`obj_rotate_yaw_and_bounce_off_walls(targetYaw, turnAmount)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `integer` |
| turnAmount | `integer` |

### Returns
- None

### C Prototype
`void obj_rotate_yaw_and_bounce_off_walls(s16 targetYaw, s16 turnAmount);`

[:arrow_up_small:](#)

<br />

## [obj_set_dist_from_home](#obj_set_dist_from_home)

### Lua Example
`obj_set_dist_from_home(distFromHome)`

### Parameters
| Field | Type |
| ----- | ---- |
| distFromHome | `number` |

### Returns
- None

### C Prototype
`void obj_set_dist_from_home(f32 distFromHome);`

[:arrow_up_small:](#)

<br />

## [obj_set_knockback_action](#obj_set_knockback_action)

### Lua Example
`obj_set_knockback_action(attackType)`

### Parameters
| Field | Type |
| ----- | ---- |
| attackType | `integer` |

### Returns
- None

### C Prototype
`void obj_set_knockback_action(s32 attackType);`

[:arrow_up_small:](#)

<br />

## [obj_set_squished_action](#obj_set_squished_action)

### Lua Example
`obj_set_squished_action()`

### Parameters
- None

### Returns
- None

### C Prototype
`void obj_set_squished_action(void);`

[:arrow_up_small:](#)

<br />

## [obj_smooth_turn](#obj_smooth_turn)

### Lua Example
`local integerValue = obj_smooth_turn(angleVel, angle, targetAngle, targetSpeedProportion, accel, minSpeed, maxSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| angleVel | `Pointer` <`integer`> |
| angle | `Pointer` <`integer`> |
| targetAngle | `integer` |
| targetSpeedProportion | `number` |
| accel | `integer` |
| minSpeed | `integer` |
| maxSpeed | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_smooth_turn(s16 *angleVel, s32 *angle, s16 targetAngle, f32 targetSpeedProportion, s16 accel, s16 minSpeed, s16 maxSpeed);`

[:arrow_up_small:](#)

<br />

## [obj_spit_fire](#obj_spit_fire)

### Lua Example
`local ObjectValue = obj_spit_fire(relativePosX, relativePosY, relativePosZ, scale, model, startSpeed, endSpeed, movePitch)`

### Parameters
| Field | Type |
| ----- | ---- |
| relativePosX | `integer` |
| relativePosY | `integer` |
| relativePosZ | `integer` |
| scale | `number` |
| model | `integer` |
| startSpeed | `number` |
| endSpeed | `number` |
| movePitch | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* obj_spit_fire(s16 relativePosX, s16 relativePosY, s16 relativePosZ, f32 scale, s32 model, f32 startSpeed, f32 endSpeed, s16 movePitch);`

[:arrow_up_small:](#)

<br />

## [obj_turn_pitch_toward_mario](#obj_turn_pitch_toward_mario)

### Lua Example
`local integerValue = obj_turn_pitch_toward_mario(m, targetOffsetY, turnAmount)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| targetOffsetY | `number` |
| turnAmount | `integer` |

### Returns
- `integer`

### C Prototype
`s16 obj_turn_pitch_toward_mario(struct MarioState* m, f32 targetOffsetY, s16 turnAmount);`

[:arrow_up_small:](#)

<br />

## [obj_unused_die](#obj_unused_die)

### Lua Example
`obj_unused_die()`

### Parameters
- None

### Returns
- None

### C Prototype
`void obj_unused_die(void);`

[:arrow_up_small:](#)

<br />

## [obj_update_blinking](#obj_update_blinking)

### Lua Example
`obj_update_blinking(blinkTimer, baseCycleLength, cycleLengthRange, blinkLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| blinkTimer | `Pointer` <`integer`> |
| baseCycleLength | `integer` |
| cycleLengthRange | `integer` |
| blinkLength | `integer` |

### Returns
- None

### C Prototype
`void obj_update_blinking(s32 *blinkTimer, s16 baseCycleLength, s16 cycleLengthRange, s16 blinkLength);`

[:arrow_up_small:](#)

<br />

## [obj_update_standard_actions](#obj_update_standard_actions)

### Lua Example
`local integerValue = obj_update_standard_actions(scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| scale | `number` |

### Returns
- `integer`

### C Prototype
`s32 obj_update_standard_actions(f32 scale);`

[:arrow_up_small:](#)

<br />

## [obj_y_vel_approach](#obj_y_vel_approach)

### Lua Example
`local integerValue = obj_y_vel_approach(target, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `number` |
| delta | `number` |

### Returns
- `integer`

### C Prototype
`s32 obj_y_vel_approach(f32 target, f32 delta);`

[:arrow_up_small:](#)

<br />

## [oscillate_toward](#oscillate_toward)

### Lua Example
`local integerValue = oscillate_toward(value, vel, target, velCloseToZero, accel, slowdown)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `Pointer` <`integer`> |
| vel | `Pointer` <`number`> |
| target | `integer` |
| velCloseToZero | `number` |
| accel | `number` |
| slowdown | `number` |

### Returns
- `integer`

### C Prototype
`s32 oscillate_toward(s32 *value, f32 *vel, s32 target, f32 velCloseToZero, f32 accel, f32 slowdown);`

[:arrow_up_small:](#)

<br />

## [platform_on_track_update_pos_or_spawn_ball](#platform_on_track_update_pos_or_spawn_ball)

### Lua Example
`platform_on_track_update_pos_or_spawn_ball(ballIndex, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| ballIndex | `integer` |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- None

### C Prototype
`void platform_on_track_update_pos_or_spawn_ball(s32 ballIndex, f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [random_linear_offset](#random_linear_offset)

### Lua Example
`local integerValue = random_linear_offset(base, range)`

### Parameters
| Field | Type |
| ----- | ---- |
| base | `integer` |
| range | `integer` |

### Returns
- `integer`

### C Prototype
`s16 random_linear_offset(s16 base, s16 range);`

[:arrow_up_small:](#)

<br />

## [random_mod_offset](#random_mod_offset)

### Lua Example
`local integerValue = random_mod_offset(base, step, mod)`

### Parameters
| Field | Type |
| ----- | ---- |
| base | `integer` |
| step | `integer` |
| mod | `integer` |

### Returns
- `integer`

### C Prototype
`s16 random_mod_offset(s16 base, s16 step, s16 mod);`

[:arrow_up_small:](#)

<br />

## [treat_far_home_as_mario](#treat_far_home_as_mario)

### Lua Example
`treat_far_home_as_mario(threshold, distanceToPlayer, angleToPlayer)`

### Parameters
| Field | Type |
| ----- | ---- |
| threshold | `number` |
| distanceToPlayer | `Pointer` <`integer`> |
| angleToPlayer | `Pointer` <`integer`> |

### Returns
- None

### C Prototype
`void treat_far_home_as_mario(f32 threshold, s32* distanceToPlayer, s32* angleToPlayer);`

[:arrow_up_small:](#)

<br />
---

[< prev](functions-3.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | 4 | [5](functions-5.md) | [6](functions-6.md) | [next >](functions-5.md)]

