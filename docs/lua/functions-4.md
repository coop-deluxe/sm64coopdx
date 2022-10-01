## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-3.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | 4]


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
# functions from object_helpers.c

<br />


## [abs_angle_diff](#abs_angle_diff)

### Lua Example
`local integerValue = abs_angle_diff(x0, x1)`

### Parameters
| Field | Type |
| ----- | ---- |
| x0 | `integer` |
| x1 | `integer` |

### Returns
- `integer`

### C Prototype
`s16 abs_angle_diff(s16 x0, s16 x1);`

[:arrow_up_small:](#)

<br />

## [apply_drag_to_value](#apply_drag_to_value)

### Lua Example
`apply_drag_to_value(value, dragStrength)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `Pointer` <`number`> |
| dragStrength | `number` |

### Returns
- None

### C Prototype
`void apply_drag_to_value(f32 *value, f32 dragStrength);`

[:arrow_up_small:](#)

<br />

## [approach_f32_signed](#approach_f32_signed)

### Lua Example
`local integerValue = approach_f32_signed(value, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `Pointer` <`number`> |
| target | `number` |
| increment | `number` |

### Returns
- `integer`

### C Prototype
`s32 approach_f32_signed(f32 *value, f32 target, f32 increment);`

[:arrow_up_small:](#)

<br />

## [approach_f32_symmetric](#approach_f32_symmetric)

### Lua Example
`local numberValue = approach_f32_symmetric(value, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `number` |
| target | `number` |
| increment | `number` |

### Returns
- `number`

### C Prototype
`f32 approach_f32_symmetric(f32 value, f32 target, f32 increment);`

[:arrow_up_small:](#)

<br />

## [approach_s16_symmetric](#approach_s16_symmetric)

### Lua Example
`local integerValue = approach_s16_symmetric(value, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |
| target | `integer` |
| increment | `integer` |

### Returns
- `integer`

### C Prototype
`s16 approach_s16_symmetric(s16 value, s16 target, s16 increment);`

[:arrow_up_small:](#)

<br />

## [bhv_dust_smoke_loop](#bhv_dust_smoke_loop)

### Lua Example
`bhv_dust_smoke_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_dust_smoke_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_init_room](#bhv_init_room)

### Lua Example
`bhv_init_room()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_init_room(void);`

[:arrow_up_small:](#)

<br />

## [bit_shift_left](#bit_shift_left)

### Lua Example
`local integerValue = bit_shift_left(a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 bit_shift_left(s32 a0);`

[:arrow_up_small:](#)

<br />

## [chain_segment_init](#chain_segment_init)

### Lua Example
`chain_segment_init(segment)`

### Parameters
| Field | Type |
| ----- | ---- |
| segment | [ChainSegment](structs.md#ChainSegment) |

### Returns
- None

### C Prototype
`void chain_segment_init(struct ChainSegment *segment);`

[:arrow_up_small:](#)

<br />

## [clear_move_flag](#clear_move_flag)

### Lua Example
`local integerValue = clear_move_flag(bitSet, flag)`

### Parameters
| Field | Type |
| ----- | ---- |
| bitSet | `Pointer` <`integer`> |
| flag | `integer` |

### Returns
- `integer`

### C Prototype
`s32 clear_move_flag(u32 *bitSet, s32 flag);`

[:arrow_up_small:](#)

<br />

## [clear_time_stop_flags](#clear_time_stop_flags)

### Lua Example
`clear_time_stop_flags(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void clear_time_stop_flags(s32 flags);`

[:arrow_up_small:](#)

<br />

## [count_objects_with_behavior](#count_objects_with_behavior)

### Lua Example
`local integerValue = count_objects_with_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `integer`

### C Prototype
`s32 count_objects_with_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [count_unimportant_objects](#count_unimportant_objects)

### Lua Example
`local integerValue = count_unimportant_objects()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 count_unimportant_objects(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_abs_y_dist_to_home](#cur_obj_abs_y_dist_to_home)

### Lua Example
`local numberValue = cur_obj_abs_y_dist_to_home()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 cur_obj_abs_y_dist_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_advance_looping_anim](#cur_obj_advance_looping_anim)

### Lua Example
`local integerValue = cur_obj_advance_looping_anim()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_advance_looping_anim(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_align_gfx_with_floor](#cur_obj_align_gfx_with_floor)

### Lua Example
`cur_obj_align_gfx_with_floor()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_align_gfx_with_floor(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_angle_to_home](#cur_obj_angle_to_home)

### Lua Example
`local integerValue = cur_obj_angle_to_home()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 cur_obj_angle_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_apply_drag_xz](#cur_obj_apply_drag_xz)

### Lua Example
`cur_obj_apply_drag_xz(dragStrength)`

### Parameters
| Field | Type |
| ----- | ---- |
| dragStrength | `number` |

### Returns
- None

### C Prototype
`void cur_obj_apply_drag_xz(f32 dragStrength);`

[:arrow_up_small:](#)

<br />

## [cur_obj_become_intangible](#cur_obj_become_intangible)

### Lua Example
`cur_obj_become_intangible()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_become_intangible(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_become_tangible](#cur_obj_become_tangible)

### Lua Example
`cur_obj_become_tangible()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_become_tangible(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_can_mario_activate_textbox](#cur_obj_can_mario_activate_textbox)

### Lua Example
`local integerValue = cur_obj_can_mario_activate_textbox(m, radius, height, unused)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| radius | `number` |
| height | `number` |
| unused | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_can_mario_activate_textbox(struct MarioState* m, f32 radius, f32 height, UNUSED s32 unused);`

[:arrow_up_small:](#)

<br />

## [cur_obj_can_mario_activate_textbox_2](#cur_obj_can_mario_activate_textbox_2)

### Lua Example
`local integerValue = cur_obj_can_mario_activate_textbox_2(m, radius, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| radius | `number` |
| height | `number` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_can_mario_activate_textbox_2(struct MarioState* m, f32 radius, f32 height);`

[:arrow_up_small:](#)

<br />

## [cur_obj_change_action](#cur_obj_change_action)

### Lua Example
`cur_obj_change_action(action)`

### Parameters
| Field | Type |
| ----- | ---- |
| action | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_change_action(s32 action);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_anim_frame](#cur_obj_check_anim_frame)

### Lua Example
`local integerValue = cur_obj_check_anim_frame(frame)`

### Parameters
| Field | Type |
| ----- | ---- |
| frame | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_anim_frame(s32 frame);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_anim_frame_in_range](#cur_obj_check_anim_frame_in_range)

### Lua Example
`local integerValue = cur_obj_check_anim_frame_in_range(startFrame, rangeLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| startFrame | `integer` |
| rangeLength | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_anim_frame_in_range(s32 startFrame, s32 rangeLength);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_frame_prior_current_frame](#cur_obj_check_frame_prior_current_frame)

### Lua Example
`local integerValue = cur_obj_check_frame_prior_current_frame(a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_frame_prior_current_frame(s16 *a0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_grabbed_mario](#cur_obj_check_grabbed_mario)

### Lua Example
`local integerValue = cur_obj_check_grabbed_mario()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_grabbed_mario(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_if_at_animation_end](#cur_obj_check_if_at_animation_end)

### Lua Example
`local integerValue = cur_obj_check_if_at_animation_end()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_if_at_animation_end(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_if_near_animation_end](#cur_obj_check_if_near_animation_end)

### Lua Example
`local integerValue = cur_obj_check_if_near_animation_end()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_if_near_animation_end(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_interacted](#cur_obj_check_interacted)

### Lua Example
`local integerValue = cur_obj_check_interacted()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_interacted(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_clear_interact_status_flag](#cur_obj_clear_interact_status_flag)

### Lua Example
`local integerValue = cur_obj_clear_interact_status_flag(flag)`

### Parameters
| Field | Type |
| ----- | ---- |
| flag | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_clear_interact_status_flag(s32 flag);`

[:arrow_up_small:](#)

<br />

## [cur_obj_compute_vel_xz](#cur_obj_compute_vel_xz)

### Lua Example
`cur_obj_compute_vel_xz()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_compute_vel_xz(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_count_objects_with_behavior](#cur_obj_count_objects_with_behavior)

### Lua Example
`local integerValue = cur_obj_count_objects_with_behavior(behavior, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |
| dist | `number` |

### Returns
- `integer`

### C Prototype
`u16 cur_obj_count_objects_with_behavior(const BehaviorScript* behavior, f32 dist);`

[:arrow_up_small:](#)

<br />

## [cur_obj_detect_steep_floor](#cur_obj_detect_steep_floor)

### Lua Example
`local integerValue = cur_obj_detect_steep_floor(steepAngleDegrees)`

### Parameters
| Field | Type |
| ----- | ---- |
| steepAngleDegrees | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_detect_steep_floor(s16 steepAngleDegrees);`

[:arrow_up_small:](#)

<br />

## [cur_obj_disable](#cur_obj_disable)

### Lua Example
`cur_obj_disable()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_disable(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_disable_rendering](#cur_obj_disable_rendering)

### Lua Example
`cur_obj_disable_rendering()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_disable_rendering(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_disable_rendering_and_become_intangible](#cur_obj_disable_rendering_and_become_intangible)

### Lua Example
`cur_obj_disable_rendering_and_become_intangible(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void cur_obj_disable_rendering_and_become_intangible(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [cur_obj_dist_to_nearest_object_with_behavior](#cur_obj_dist_to_nearest_object_with_behavior)

### Lua Example
`local numberValue = cur_obj_dist_to_nearest_object_with_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `number`

### C Prototype
`f32 cur_obj_dist_to_nearest_object_with_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [cur_obj_enable_rendering](#cur_obj_enable_rendering)

### Lua Example
`cur_obj_enable_rendering()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_enable_rendering(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_enable_rendering_2](#cur_obj_enable_rendering_2)

### Lua Example
`cur_obj_enable_rendering_2()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_enable_rendering_2(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_enable_rendering_and_become_tangible](#cur_obj_enable_rendering_and_become_tangible)

### Lua Example
`cur_obj_enable_rendering_and_become_tangible(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void cur_obj_enable_rendering_and_become_tangible(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [cur_obj_enable_rendering_if_mario_in_room](#cur_obj_enable_rendering_if_mario_in_room)

### Lua Example
`cur_obj_enable_rendering_if_mario_in_room()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_enable_rendering_if_mario_in_room(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_end_dialog](#cur_obj_end_dialog)

### Lua Example
`cur_obj_end_dialog(m, dialogFlags, dialogResult)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| dialogFlags | `integer` |
| dialogResult | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_end_dialog(struct MarioState* m, s32 dialogFlags, s32 dialogResult);`

[:arrow_up_small:](#)

<br />

## [cur_obj_extend_animation_if_at_end](#cur_obj_extend_animation_if_at_end)

### Lua Example
`cur_obj_extend_animation_if_at_end()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_extend_animation_if_at_end(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_find_nearby_held_actor](#cur_obj_find_nearby_held_actor)

### Lua Example
`local ObjectValue = cur_obj_find_nearby_held_actor(behavior, maxDist)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |
| maxDist | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *cur_obj_find_nearby_held_actor(const BehaviorScript *behavior, f32 maxDist);`

[:arrow_up_small:](#)

<br />

## [cur_obj_find_nearest_object_with_behavior](#cur_obj_find_nearest_object_with_behavior)

### Lua Example
`local ObjectValue = cur_obj_find_nearest_object_with_behavior(behavior, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |
| dist | `Pointer` <`number`> |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *cur_obj_find_nearest_object_with_behavior(const BehaviorScript *behavior, f32 *dist);`

[:arrow_up_small:](#)

<br />

## [cur_obj_find_nearest_pole](#cur_obj_find_nearest_pole)

### Lua Example
`local ObjectValue = cur_obj_find_nearest_pole()`

### Parameters
- None

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* cur_obj_find_nearest_pole(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_follow_path](#cur_obj_follow_path)

### Lua Example
`local integerValue = cur_obj_follow_path(unusedArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| unusedArg | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_follow_path(UNUSED s32 unusedArg);`

[:arrow_up_small:](#)

<br />

## [cur_obj_forward_vel_approach_upward](#cur_obj_forward_vel_approach_upward)

### Lua Example
`cur_obj_forward_vel_approach_upward(target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `number` |
| increment | `number` |

### Returns
- None

### C Prototype
`void cur_obj_forward_vel_approach_upward(f32 target, f32 increment);`

[:arrow_up_small:](#)

<br />

## [cur_obj_get_dropped](#cur_obj_get_dropped)

### Lua Example
`cur_obj_get_dropped()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_get_dropped(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_get_thrown_or_placed](#cur_obj_get_thrown_or_placed)

### Lua Example
`cur_obj_get_thrown_or_placed(forwardVel, velY, thrownAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| forwardVel | `number` |
| velY | `number` |
| thrownAction | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_get_thrown_or_placed(f32 forwardVel, f32 velY, s32 thrownAction);`

[:arrow_up_small:](#)

<br />

## [cur_obj_has_behavior](#cur_obj_has_behavior)

### Lua Example
`local integerValue = cur_obj_has_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_has_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [cur_obj_has_model](#cur_obj_has_model)

### Lua Example
`local integerValue = cur_obj_has_model(modelID)`

### Parameters
| Field | Type |
| ----- | ---- |
| modelID | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_has_model(u16 modelID);`

[:arrow_up_small:](#)

<br />

## [cur_obj_hide](#cur_obj_hide)

### Lua Example
`cur_obj_hide()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_hide(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_hide_if_mario_far_away_y](#cur_obj_hide_if_mario_far_away_y)

### Lua Example
`local integerValue = cur_obj_hide_if_mario_far_away_y(distY)`

### Parameters
| Field | Type |
| ----- | ---- |
| distY | `number` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_hide_if_mario_far_away_y(f32 distY);`

[:arrow_up_small:](#)

<br />

## [cur_obj_if_hit_wall_bounce_away](#cur_obj_if_hit_wall_bounce_away)

### Lua Example
`cur_obj_if_hit_wall_bounce_away()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_if_hit_wall_bounce_away(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation](#cur_obj_init_animation)

### Lua Example
`cur_obj_init_animation(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_and_anim_frame](#cur_obj_init_animation_and_anim_frame)

### Lua Example
`cur_obj_init_animation_and_anim_frame(animIndex, animFrame)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |
| animFrame | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation_and_anim_frame(s32 animIndex, s32 animFrame);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_and_check_if_near_end](#cur_obj_init_animation_and_check_if_near_end)

### Lua Example
`local integerValue = cur_obj_init_animation_and_check_if_near_end(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_init_animation_and_check_if_near_end(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_and_extend_if_at_end](#cur_obj_init_animation_and_extend_if_at_end)

### Lua Example
`cur_obj_init_animation_and_extend_if_at_end(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation_and_extend_if_at_end(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_with_accel_and_sound](#cur_obj_init_animation_with_accel_and_sound)

### Lua Example
`cur_obj_init_animation_with_accel_and_sound(animIndex, accel)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |
| accel | `number` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation_with_accel_and_sound(s32 animIndex, f32 accel);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_with_sound](#cur_obj_init_animation_with_sound)

### Lua Example
`cur_obj_init_animation_with_sound(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation_with_sound(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_is_any_player_on_platform](#cur_obj_is_any_player_on_platform)

### Lua Example
`local integerValue = cur_obj_is_any_player_on_platform()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_is_any_player_on_platform(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_is_mario_ground_pounding_platform](#cur_obj_is_mario_ground_pounding_platform)

### Lua Example
`local integerValue = cur_obj_is_mario_ground_pounding_platform()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_is_mario_ground_pounding_platform(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_is_mario_on_platform](#cur_obj_is_mario_on_platform)

### Lua Example
`local integerValue = cur_obj_is_mario_on_platform()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_is_mario_on_platform(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_lateral_dist_from_mario_to_home](#cur_obj_lateral_dist_from_mario_to_home)

### Lua Example
`local numberValue = cur_obj_lateral_dist_from_mario_to_home()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 cur_obj_lateral_dist_from_mario_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_lateral_dist_from_obj_to_home](#cur_obj_lateral_dist_from_obj_to_home)

### Lua Example
`local numberValue = cur_obj_lateral_dist_from_obj_to_home(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- `number`

### C Prototype
`f32 cur_obj_lateral_dist_from_obj_to_home(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [cur_obj_lateral_dist_to_home](#cur_obj_lateral_dist_to_home)

### Lua Example
`local numberValue = cur_obj_lateral_dist_to_home()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 cur_obj_lateral_dist_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_mario_far_away](#cur_obj_mario_far_away)

### Lua Example
`local integerValue = cur_obj_mario_far_away()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_mario_far_away(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_after_thrown_or_dropped](#cur_obj_move_after_thrown_or_dropped)

### Lua Example
`cur_obj_move_after_thrown_or_dropped(forwardVel, velY)`

### Parameters
| Field | Type |
| ----- | ---- |
| forwardVel | `number` |
| velY | `number` |

### Returns
- None

### C Prototype
`void cur_obj_move_after_thrown_or_dropped(f32 forwardVel, f32 velY);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_standard](#cur_obj_move_standard)

### Lua Example
`cur_obj_move_standard(steepSlopeAngleDegrees)`

### Parameters
| Field | Type |
| ----- | ---- |
| steepSlopeAngleDegrees | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_move_standard(s16 steepSlopeAngleDegrees);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_up_and_down](#cur_obj_move_up_and_down)

### Lua Example
`local integerValue = cur_obj_move_up_and_down(a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_move_up_and_down(s32 a0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_update_ground_air_flags](#cur_obj_move_update_ground_air_flags)

### Lua Example
`cur_obj_move_update_ground_air_flags(gravity, bounciness)`

### Parameters
| Field | Type |
| ----- | ---- |
| gravity | `number` |
| bounciness | `number` |

### Returns
- None

### C Prototype
`void cur_obj_move_update_ground_air_flags(UNUSED f32 gravity, f32 bounciness);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_update_underwater_flags](#cur_obj_move_update_underwater_flags)

### Lua Example
`cur_obj_move_update_underwater_flags()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_update_underwater_flags(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_using_fvel_and_gravity](#cur_obj_move_using_fvel_and_gravity)

### Lua Example
`cur_obj_move_using_fvel_and_gravity()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_using_fvel_and_gravity(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_using_vel](#cur_obj_move_using_vel)

### Lua Example
`cur_obj_move_using_vel()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_using_vel(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_using_vel_and_gravity](#cur_obj_move_using_vel_and_gravity)

### Lua Example
`cur_obj_move_using_vel_and_gravity()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_using_vel_and_gravity(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_xz](#cur_obj_move_xz)

### Lua Example
`local integerValue = cur_obj_move_xz(steepSlopeNormalY, careAboutEdgesAndSteepSlopes)`

### Parameters
| Field | Type |
| ----- | ---- |
| steepSlopeNormalY | `number` |
| careAboutEdgesAndSteepSlopes | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_move_xz(f32 steepSlopeNormalY, s32 careAboutEdgesAndSteepSlopes);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_xz_using_fvel_and_yaw](#cur_obj_move_xz_using_fvel_and_yaw)

### Lua Example
`cur_obj_move_xz_using_fvel_and_yaw()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_xz_using_fvel_and_yaw(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_y](#cur_obj_move_y)

### Lua Example
`cur_obj_move_y(gravity, bounciness, buoyancy)`

### Parameters
| Field | Type |
| ----- | ---- |
| gravity | `number` |
| bounciness | `number` |
| buoyancy | `number` |

### Returns
- None

### C Prototype
`void cur_obj_move_y(f32 gravity, f32 bounciness, f32 buoyancy);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_y_and_get_water_level](#cur_obj_move_y_and_get_water_level)

### Lua Example
`local numberValue = cur_obj_move_y_and_get_water_level(gravity, buoyancy)`

### Parameters
| Field | Type |
| ----- | ---- |
| gravity | `number` |
| buoyancy | `number` |

### Returns
- `number`

### C Prototype
`f32 cur_obj_move_y_and_get_water_level(f32 gravity, f32 buoyancy);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_y_with_terminal_vel](#cur_obj_move_y_with_terminal_vel)

### Lua Example
`cur_obj_move_y_with_terminal_vel()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_y_with_terminal_vel(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_nearest_object_with_behavior](#cur_obj_nearest_object_with_behavior)

### Lua Example
`local ObjectValue = cur_obj_nearest_object_with_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *cur_obj_nearest_object_with_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [cur_obj_outside_home_rectangle](#cur_obj_outside_home_rectangle)

### Lua Example
`local integerValue = cur_obj_outside_home_rectangle(minX, maxX, minZ, maxZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| minX | `number` |
| maxX | `number` |
| minZ | `number` |
| maxZ | `number` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_outside_home_rectangle(f32 minX, f32 maxX, f32 minZ, f32 maxZ);`

[:arrow_up_small:](#)

<br />

## [cur_obj_outside_home_square](#cur_obj_outside_home_square)

### Lua Example
`local integerValue = cur_obj_outside_home_square(halfLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| halfLength | `number` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_outside_home_square(f32 halfLength);`

[:arrow_up_small:](#)

<br />

## [cur_obj_progress_direction_table](#cur_obj_progress_direction_table)

### Lua Example
`local integerValue = cur_obj_progress_direction_table()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_progress_direction_table(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_push_mario_away](#cur_obj_push_mario_away)

### Lua Example
`cur_obj_push_mario_away(radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| radius | `number` |

### Returns
- None

### C Prototype
`void cur_obj_push_mario_away(f32 radius);`

[:arrow_up_small:](#)

<br />

## [cur_obj_push_mario_away_from_cylinder](#cur_obj_push_mario_away_from_cylinder)

### Lua Example
`cur_obj_push_mario_away_from_cylinder(radius, extentY)`

### Parameters
| Field | Type |
| ----- | ---- |
| radius | `number` |
| extentY | `number` |

### Returns
- None

### C Prototype
`void cur_obj_push_mario_away_from_cylinder(f32 radius, f32 extentY);`

[:arrow_up_small:](#)

<br />

## [cur_obj_reflect_move_angle_off_wall](#cur_obj_reflect_move_angle_off_wall)

### Lua Example
`local integerValue = cur_obj_reflect_move_angle_off_wall()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 cur_obj_reflect_move_angle_off_wall(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_reset_timer_and_subaction](#cur_obj_reset_timer_and_subaction)

### Lua Example
`cur_obj_reset_timer_and_subaction()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_reset_timer_and_subaction(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_resolve_wall_collisions](#cur_obj_resolve_wall_collisions)

### Lua Example
`local integerValue = cur_obj_resolve_wall_collisions()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_resolve_wall_collisions(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_reverse_animation](#cur_obj_reverse_animation)

### Lua Example
`cur_obj_reverse_animation()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_reverse_animation(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_rotate_face_angle_using_vel](#cur_obj_rotate_face_angle_using_vel)

### Lua Example
`cur_obj_rotate_face_angle_using_vel()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_rotate_face_angle_using_vel(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_rotate_move_angle_using_vel](#cur_obj_rotate_move_angle_using_vel)

### Lua Example
`cur_obj_rotate_move_angle_using_vel()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_rotate_move_angle_using_vel(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_rotate_yaw_toward](#cur_obj_rotate_yaw_toward)

### Lua Example
`local integerValue = cur_obj_rotate_yaw_toward(target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `integer` |
| increment | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_rotate_yaw_toward(s16 target, s16 increment);`

[:arrow_up_small:](#)

<br />

## [cur_obj_scale](#cur_obj_scale)

### Lua Example
`cur_obj_scale(scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| scale | `number` |

### Returns
- None

### C Prototype
`void cur_obj_scale(f32 scale);`

[:arrow_up_small:](#)

<br />

## [cur_obj_scale_over_time](#cur_obj_scale_over_time)

### Lua Example
`cur_obj_scale_over_time(a0, a1, sp10, sp14)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `integer` |
| a1 | `integer` |
| sp10 | `number` |
| sp14 | `number` |

### Returns
- None

### C Prototype
`void cur_obj_scale_over_time(s32 a0, s32 a1, f32 sp10, f32 sp14);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_behavior](#cur_obj_set_behavior)

### Lua Example
`cur_obj_set_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- None

### C Prototype
`void cur_obj_set_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_direction_table](#cur_obj_set_direction_table)

### Lua Example
`local integerValue = cur_obj_set_direction_table(a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_set_direction_table(s8 *a0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_face_angle_to_move_angle](#cur_obj_set_face_angle_to_move_angle)

### Lua Example
`cur_obj_set_face_angle_to_move_angle()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_face_angle_to_move_angle(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_hitbox_and_die_if_attacked](#cur_obj_set_hitbox_and_die_if_attacked)

### Lua Example
`local integerValue = cur_obj_set_hitbox_and_die_if_attacked(hitbox, deathSound, noLootCoins)`

### Parameters
| Field | Type |
| ----- | ---- |
| hitbox | [ObjectHitbox](structs.md#ObjectHitbox) |
| deathSound | `integer` |
| noLootCoins | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_set_hitbox_and_die_if_attacked(struct ObjectHitbox *hitbox, s32 deathSound, s32 noLootCoins);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_hitbox_radius_and_height](#cur_obj_set_hitbox_radius_and_height)

### Lua Example
`cur_obj_set_hitbox_radius_and_height(radius, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| radius | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_hitbox_radius_and_height(f32 radius, f32 height);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_home_once](#cur_obj_set_home_once)

### Lua Example
`cur_obj_set_home_once()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_home_once(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_hurtbox_radius_and_height](#cur_obj_set_hurtbox_radius_and_height)

### Lua Example
`cur_obj_set_hurtbox_radius_and_height(radius, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| radius | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_hurtbox_radius_and_height(f32 radius, f32 height);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_relative](#cur_obj_set_pos_relative)

### Lua Example
`cur_obj_set_pos_relative(other, dleft, dy, dforward)`

### Parameters
| Field | Type |
| ----- | ---- |
| other | [Object](structs.md#Object) |
| dleft | `number` |
| dy | `number` |
| dforward | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_pos_relative(struct Object *other, f32 dleft, f32 dy, f32 dforward);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_relative_to_parent](#cur_obj_set_pos_relative_to_parent)

### Lua Example
`cur_obj_set_pos_relative_to_parent(dleft, dy, dforward)`

### Parameters
| Field | Type |
| ----- | ---- |
| dleft | `number` |
| dy | `number` |
| dforward | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_pos_relative_to_parent(f32 dleft, f32 dy, f32 dforward);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_to_home](#cur_obj_set_pos_to_home)

### Lua Example
`cur_obj_set_pos_to_home()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_pos_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_to_home_and_stop](#cur_obj_set_pos_to_home_and_stop)

### Lua Example
`cur_obj_set_pos_to_home_and_stop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_pos_to_home_and_stop(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_to_home_with_debug](#cur_obj_set_pos_to_home_with_debug)

### Lua Example
`cur_obj_set_pos_to_home_with_debug()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_pos_to_home_with_debug(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_via_transform](#cur_obj_set_pos_via_transform)

### Lua Example
`cur_obj_set_pos_via_transform()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_pos_via_transform(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_vel_from_mario_vel](#cur_obj_set_vel_from_mario_vel)

### Lua Example
`cur_obj_set_vel_from_mario_vel(m, f12, f14)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| f12 | `number` |
| f14 | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_vel_from_mario_vel(struct MarioState* m, f32 f12, f32 f14);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_y_vel_and_animation](#cur_obj_set_y_vel_and_animation)

### Lua Example
`cur_obj_set_y_vel_and_animation(sp18, sp1C)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp18 | `number` |
| sp1C | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_set_y_vel_and_animation(f32 sp18, s32 sp1C);`

[:arrow_up_small:](#)

<br />

## [cur_obj_shake_screen](#cur_obj_shake_screen)

### Lua Example
`cur_obj_shake_screen(shake)`

### Parameters
| Field | Type |
| ----- | ---- |
| shake | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_shake_screen(s32 shake);`

[:arrow_up_small:](#)

<br />

## [cur_obj_shake_y](#cur_obj_shake_y)

### Lua Example
`cur_obj_shake_y(amount)`

### Parameters
| Field | Type |
| ----- | ---- |
| amount | `number` |

### Returns
- None

### C Prototype
`void cur_obj_shake_y(f32 amount);`

[:arrow_up_small:](#)

<br />

## [cur_obj_shake_y_until](#cur_obj_shake_y_until)

### Lua Example
`local integerValue = cur_obj_shake_y_until(cycles, amount)`

### Parameters
| Field | Type |
| ----- | ---- |
| cycles | `integer` |
| amount | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_shake_y_until(s32 cycles, s32 amount);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spawn_loot_blue_coin](#cur_obj_spawn_loot_blue_coin)

### Lua Example
`cur_obj_spawn_loot_blue_coin()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_spawn_loot_blue_coin(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spawn_loot_coin_at_mario_pos](#cur_obj_spawn_loot_coin_at_mario_pos)

### Lua Example
`cur_obj_spawn_loot_coin_at_mario_pos(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void cur_obj_spawn_loot_coin_at_mario_pos(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spawn_particles](#cur_obj_spawn_particles)

### Lua Example
`cur_obj_spawn_particles(info)`

### Parameters
| Field | Type |
| ----- | ---- |
| info | [SpawnParticlesInfo](structs.md#SpawnParticlesInfo) |

### Returns
- None

### C Prototype
`void cur_obj_spawn_particles(struct SpawnParticlesInfo *info);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spawn_star_at_y_offset](#cur_obj_spawn_star_at_y_offset)

### Lua Example
`cur_obj_spawn_star_at_y_offset(targetX, targetY, targetZ, offsetY)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetX | `number` |
| targetY | `number` |
| targetZ | `number` |
| offsetY | `number` |

### Returns
- None

### C Prototype
`void cur_obj_spawn_star_at_y_offset(f32 targetX, f32 targetY, f32 targetZ, f32 offsetY);`

[:arrow_up_small:](#)

<br />

## [cur_obj_start_cam_event](#cur_obj_start_cam_event)

### Lua Example
`cur_obj_start_cam_event(obj, cameraEvent)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| cameraEvent | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_start_cam_event(UNUSED struct Object *obj, s32 cameraEvent);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unhide](#cur_obj_unhide)

### Lua Example
`cur_obj_unhide()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_unhide(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unrender_and_reset_state](#cur_obj_unrender_and_reset_state)

### Lua Example
`cur_obj_unrender_and_reset_state(sp18, sp1C)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp18 | `integer` |
| sp1C | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_unrender_and_reset_state(s32 sp18, s32 sp1C);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unused_init_on_floor](#cur_obj_unused_init_on_floor)

### Lua Example
`cur_obj_unused_init_on_floor()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_unused_init_on_floor(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unused_play_footstep_sound](#cur_obj_unused_play_footstep_sound)

### Lua Example
`cur_obj_unused_play_footstep_sound(animFrame1, animFrame2, sound)`

### Parameters
| Field | Type |
| ----- | ---- |
| animFrame1 | `integer` |
| animFrame2 | `integer` |
| sound | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_unused_play_footstep_sound(s32 animFrame1, s32 animFrame2, s32 sound);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unused_resolve_wall_collisions](#cur_obj_unused_resolve_wall_collisions)

### Lua Example
`cur_obj_unused_resolve_wall_collisions(offsetY, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| offsetY | `number` |
| radius | `number` |

### Returns
- None

### C Prototype
`void cur_obj_unused_resolve_wall_collisions(f32 offsetY, f32 radius);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor](#cur_obj_update_floor)

### Lua Example
`cur_obj_update_floor()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_update_floor(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor_and_resolve_wall_collisions](#cur_obj_update_floor_and_resolve_wall_collisions)

### Lua Example
`cur_obj_update_floor_and_resolve_wall_collisions(steepSlopeDegrees)`

### Parameters
| Field | Type |
| ----- | ---- |
| steepSlopeDegrees | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_update_floor_and_resolve_wall_collisions(s16 steepSlopeDegrees);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor_and_walls](#cur_obj_update_floor_and_walls)

### Lua Example
`cur_obj_update_floor_and_walls()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_update_floor_and_walls(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor_height](#cur_obj_update_floor_height)

### Lua Example
`cur_obj_update_floor_height()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_update_floor_height(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor_height_and_get_floor](#cur_obj_update_floor_height_and_get_floor)

### Lua Example
`local SurfaceValue = cur_obj_update_floor_height_and_get_floor()`

### Parameters
- None

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface *cur_obj_update_floor_height_and_get_floor(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_wait_then_blink](#cur_obj_wait_then_blink)

### Lua Example
`local integerValue = cur_obj_wait_then_blink(timeUntilBlinking, numBlinks)`

### Parameters
| Field | Type |
| ----- | ---- |
| timeUntilBlinking | `integer` |
| numBlinks | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_wait_then_blink(s32 timeUntilBlinking, s32 numBlinks);`

[:arrow_up_small:](#)

<br />

## [cur_obj_was_attacked_or_ground_pounded](#cur_obj_was_attacked_or_ground_pounded)

### Lua Example
`local integerValue = cur_obj_was_attacked_or_ground_pounded()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_was_attacked_or_ground_pounded(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_within_12k_bounds](#cur_obj_within_12k_bounds)

### Lua Example
`local integerValue = cur_obj_within_12k_bounds()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_within_12k_bounds(void);`

[:arrow_up_small:](#)

<br />

## [disable_time_stop](#disable_time_stop)

### Lua Example
`disable_time_stop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void disable_time_stop(void);`

[:arrow_up_small:](#)

<br />

## [disable_time_stop_including_mario](#disable_time_stop_including_mario)

### Lua Example
`disable_time_stop_including_mario()`

### Parameters
- None

### Returns
- None

### C Prototype
`void disable_time_stop_including_mario(void);`

[:arrow_up_small:](#)

<br />

## [dist_between_object_and_point](#dist_between_object_and_point)

### Lua Example
`local numberValue = dist_between_object_and_point(obj, pointX, pointY, pointZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| pointX | `number` |
| pointY | `number` |
| pointZ | `number` |

### Returns
- `number`

### C Prototype
`f32 dist_between_object_and_point(struct Object *obj, f32 pointX, f32 pointY, f32 pointZ);`

[:arrow_up_small:](#)

<br />

## [dist_between_objects](#dist_between_objects)

### Lua Example
`local numberValue = dist_between_objects(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- `number`

### C Prototype
`f32 dist_between_objects(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [enable_time_stop](#enable_time_stop)

### Lua Example
`enable_time_stop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void enable_time_stop(void);`

[:arrow_up_small:](#)

<br />

## [enable_time_stop_if_alone](#enable_time_stop_if_alone)

### Lua Example
`enable_time_stop_if_alone()`

### Parameters
- None

### Returns
- None

### C Prototype
`void enable_time_stop_if_alone(void);`

[:arrow_up_small:](#)

<br />

## [enable_time_stop_including_mario](#enable_time_stop_including_mario)

### Lua Example
`enable_time_stop_including_mario()`

### Parameters
- None

### Returns
- None

### C Prototype
`void enable_time_stop_including_mario(void);`

[:arrow_up_small:](#)

<br />

## [find_object_with_behavior](#find_object_with_behavior)

### Lua Example
`local ObjectValue = find_object_with_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *find_object_with_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [find_unimportant_object](#find_unimportant_object)

### Lua Example
`local ObjectValue = find_unimportant_object()`

### Parameters
- None

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *find_unimportant_object(void);`

[:arrow_up_small:](#)

<br />

## [geo_offset_klepto_debug](#geo_offset_klepto_debug)

### Lua Example
`local integerValue = geo_offset_klepto_debug(callContext, a1, sp8)`

### Parameters
| Field | Type |
| ----- | ---- |
| callContext | `integer` |
| a1 | [GraphNode](structs.md#GraphNode) |
| sp8 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 geo_offset_klepto_debug(s32 callContext, struct GraphNode *a1, UNUSED s32 sp8);`

[:arrow_up_small:](#)

<br />

## [get_object_list_from_behavior](#get_object_list_from_behavior)

### Lua Example
`local integerValue = get_object_list_from_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `integer`

### C Prototype
`u32 get_object_list_from_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [increment_velocity_toward_range](#increment_velocity_toward_range)

### Lua Example
`local numberValue = increment_velocity_toward_range(value, center, zeroThreshold, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `number` |
| center | `number` |
| zeroThreshold | `number` |
| increment | `number` |

### Returns
- `number`

### C Prototype
`f32 increment_velocity_toward_range(f32 value, f32 center, f32 zeroThreshold, f32 increment);`

[:arrow_up_small:](#)

<br />

## [is_item_in_array](#is_item_in_array)

### Lua Example
`local integerValue = is_item_in_array(item, array)`

### Parameters
| Field | Type |
| ----- | ---- |
| item | `integer` |
| array | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 is_item_in_array(s8 item, s8 *array);`

[:arrow_up_small:](#)

<br />

## [is_mario_moving_fast_or_in_air](#is_mario_moving_fast_or_in_air)

### Lua Example
`local integerValue = is_mario_moving_fast_or_in_air(speedThreshold)`

### Parameters
| Field | Type |
| ----- | ---- |
| speedThreshold | `integer` |

### Returns
- `integer`

### C Prototype
`s32 is_mario_moving_fast_or_in_air(s32 speedThreshold);`

[:arrow_up_small:](#)

<br />

## [lateral_dist_between_objects](#lateral_dist_between_objects)

### Lua Example
`local numberValue = lateral_dist_between_objects(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- `number`

### C Prototype
`f32 lateral_dist_between_objects(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [mario_is_dive_sliding](#mario_is_dive_sliding)

### Lua Example
`local integerValue = mario_is_dive_sliding(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_is_dive_sliding(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [mario_is_in_air_action](#mario_is_in_air_action)

### Lua Example
`local integerValue = mario_is_in_air_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_is_in_air_action(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [mario_is_within_rectangle](#mario_is_within_rectangle)

### Lua Example
`local integerValue = mario_is_within_rectangle(minX, maxX, minZ, maxZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| minX | `integer` |
| maxX | `integer` |
| minZ | `integer` |
| maxZ | `integer` |

### Returns
- `integer`

### C Prototype
`s32 mario_is_within_rectangle(s16 minX, s16 maxX, s16 minZ, s16 maxZ);`

[:arrow_up_small:](#)

<br />

## [mario_set_flag](#mario_set_flag)

### Lua Example
`mario_set_flag(flag)`

### Parameters
| Field | Type |
| ----- | ---- |
| flag | `integer` |

### Returns
- None

### C Prototype
`void mario_set_flag(s32 flag);`

[:arrow_up_small:](#)

<br />

## [obj_angle_to_object](#obj_angle_to_object)

### Lua Example
`local integerValue = obj_angle_to_object(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s16 obj_angle_to_object(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [obj_angle_to_point](#obj_angle_to_point)

### Lua Example
`local integerValue = obj_angle_to_point(obj, pointX, pointZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| pointX | `number` |
| pointZ | `number` |

### Returns
- `integer`

### C Prototype
`s16 obj_angle_to_point(struct Object *obj, f32 pointX, f32 pointZ);`

[:arrow_up_small:](#)

<br />

## [obj_apply_scale_to_transform](#obj_apply_scale_to_transform)

### Lua Example
`obj_apply_scale_to_transform(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_apply_scale_to_transform(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_attack_collided_from_other_object](#obj_attack_collided_from_other_object)

### Lua Example
`local integerValue = obj_attack_collided_from_other_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s32 obj_attack_collided_from_other_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_become_tangible](#obj_become_tangible)

### Lua Example
`obj_become_tangible(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_become_tangible(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_build_relative_transform](#obj_build_relative_transform)

### Lua Example
`obj_build_relative_transform(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_build_relative_transform(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_build_transform_from_pos_and_angle](#obj_build_transform_from_pos_and_angle)

### Lua Example
`obj_build_transform_from_pos_and_angle(obj, posIndex, angleIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| posIndex | `integer` |
| angleIndex | `integer` |

### Returns
- None

### C Prototype
`void obj_build_transform_from_pos_and_angle(struct Object *obj, s16 posIndex, s16 angleIndex);`

[:arrow_up_small:](#)

<br />

## [obj_build_transform_relative_to_parent](#obj_build_transform_relative_to_parent)

### Lua Example
`obj_build_transform_relative_to_parent(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_build_transform_relative_to_parent(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_build_vel_from_transform](#obj_build_vel_from_transform)

### Lua Example
`obj_build_vel_from_transform(a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_build_vel_from_transform(struct Object *a0);`

[:arrow_up_small:](#)

<br />

## [obj_check_if_collided_with_object](#obj_check_if_collided_with_object)

### Lua Example
`local integerValue = obj_check_if_collided_with_object(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s32 obj_check_if_collided_with_object(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [obj_copy_angle](#obj_copy_angle)

### Lua Example
`obj_copy_angle(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_angle(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_behavior_params](#obj_copy_behavior_params)

### Lua Example
`obj_copy_behavior_params(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_behavior_params(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_graph_y_offset](#obj_copy_graph_y_offset)

### Lua Example
`obj_copy_graph_y_offset(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_graph_y_offset(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_pos](#obj_copy_pos)

### Lua Example
`obj_copy_pos(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_pos(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_pos_and_angle](#obj_copy_pos_and_angle)

### Lua Example
`obj_copy_pos_and_angle(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_pos_and_angle(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_scale](#obj_copy_scale)

### Lua Example
`obj_copy_scale(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_scale(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_create_transform_from_self](#obj_create_transform_from_self)

### Lua Example
`obj_create_transform_from_self(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_create_transform_from_self(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_explode_and_spawn_coins](#obj_explode_and_spawn_coins)

### Lua Example
`obj_explode_and_spawn_coins(sp18, sp1C)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp18 | `number` |
| sp1C | `integer` |

### Returns
- None

### C Prototype
`void obj_explode_and_spawn_coins(f32 sp18, s32 sp1C);`

[:arrow_up_small:](#)

<br />

## [obj_has_behavior](#obj_has_behavior)

### Lua Example
`local integerValue = obj_has_behavior(obj, behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `integer`

### C Prototype
`s32 obj_has_behavior(struct Object *obj, const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [obj_init_animation](#obj_init_animation)

### Lua Example
`obj_init_animation(obj, animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void obj_init_animation(struct Object *obj, s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [obj_is_hidden](#obj_is_hidden)

### Lua Example
`local integerValue = obj_is_hidden(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s32 obj_is_hidden(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_mark_for_deletion](#obj_mark_for_deletion)

### Lua Example
`obj_mark_for_deletion(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_mark_for_deletion(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_pitch_to_object](#obj_pitch_to_object)

### Lua Example
`local integerValue = obj_pitch_to_object(obj, target)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| target | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s16 obj_pitch_to_object(struct Object* obj, struct Object* target);`

[:arrow_up_small:](#)

<br />

## [obj_scale](#obj_scale)

### Lua Example
`obj_scale(obj, scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| scale | `number` |

### Returns
- None

### C Prototype
`void obj_scale(struct Object *obj, f32 scale);`

[:arrow_up_small:](#)

<br />

## [obj_scale_random](#obj_scale_random)

### Lua Example
`obj_scale_random(obj, rangeLength, minScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| rangeLength | `number` |
| minScale | `number` |

### Returns
- None

### C Prototype
`void obj_scale_random(struct Object *obj, f32 rangeLength, f32 minScale);`

[:arrow_up_small:](#)

<br />

## [obj_scale_xyz](#obj_scale_xyz)

### Lua Example
`obj_scale_xyz(obj, xScale, yScale, zScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| xScale | `number` |
| yScale | `number` |
| zScale | `number` |

### Returns
- None

### C Prototype
`void obj_scale_xyz(struct Object *obj, f32 xScale, f32 yScale, f32 zScale);`

[:arrow_up_small:](#)

<br />

## [obj_set_angle](#obj_set_angle)

### Lua Example
`obj_set_angle(obj, pitch, yaw, roll)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| pitch | `integer` |
| yaw | `integer` |
| roll | `integer` |

### Returns
- None

### C Prototype
`void obj_set_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll);`

[:arrow_up_small:](#)

<br />

## [obj_set_behavior](#obj_set_behavior)

### Lua Example
`obj_set_behavior(obj, behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- None

### C Prototype
`void obj_set_behavior(struct Object *obj, const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [obj_set_billboard](#obj_set_billboard)

### Lua Example
`obj_set_billboard(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_billboard(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_set_cylboard](#obj_set_cylboard)

### Lua Example
`obj_set_cylboard(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_cylboard(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_set_face_angle_to_move_angle](#obj_set_face_angle_to_move_angle)

### Lua Example
`obj_set_face_angle_to_move_angle(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_face_angle_to_move_angle(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_set_gfx_pos_at_obj_pos](#obj_set_gfx_pos_at_obj_pos)

### Lua Example
`obj_set_gfx_pos_at_obj_pos(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_gfx_pos_at_obj_pos(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [obj_set_gfx_pos_from_pos](#obj_set_gfx_pos_from_pos)

### Lua Example
`obj_set_gfx_pos_from_pos(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_gfx_pos_from_pos(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_set_held_state](#obj_set_held_state)

### Lua Example
`obj_set_held_state(obj, heldBehavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| heldBehavior | `Pointer` <`BehaviorScript`> |

### Returns
- None

### C Prototype
`void obj_set_held_state(struct Object *obj, const BehaviorScript *heldBehavior);`

[:arrow_up_small:](#)

<br />

## [obj_set_hitbox](#obj_set_hitbox)

### Lua Example
`obj_set_hitbox(obj, hitbox)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| hitbox | [ObjectHitbox](structs.md#ObjectHitbox) |

### Returns
- None

### C Prototype
`void obj_set_hitbox(struct Object *obj, struct ObjectHitbox *hitbox);`

[:arrow_up_small:](#)

<br />

## [obj_set_parent_relative_pos](#obj_set_parent_relative_pos)

### Lua Example
`obj_set_parent_relative_pos(obj, relX, relY, relZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| relX | `integer` |
| relY | `integer` |
| relZ | `integer` |

### Returns
- None

### C Prototype
`void obj_set_parent_relative_pos(struct Object *obj, s16 relX, s16 relY, s16 relZ);`

[:arrow_up_small:](#)

<br />

## [obj_set_pos](#obj_set_pos)

### Lua Example
`obj_set_pos(obj, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| x | `integer` |
| y | `integer` |
| z | `integer` |

### Returns
- None

### C Prototype
`void obj_set_pos(struct Object *obj, s16 x, s16 y, s16 z);`

[:arrow_up_small:](#)

<br />

## [obj_set_pos_relative](#obj_set_pos_relative)

### Lua Example
`obj_set_pos_relative(obj, other, dleft, dy, dforward)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| other | [Object](structs.md#Object) |
| dleft | `number` |
| dy | `number` |
| dforward | `number` |

### Returns
- None

### C Prototype
`void obj_set_pos_relative(struct Object *obj, struct Object *other, f32 dleft, f32 dy, f32 dforward);`

[:arrow_up_small:](#)

<br />

## [obj_set_throw_matrix_from_transform](#obj_set_throw_matrix_from_transform)

### Lua Example
`obj_set_throw_matrix_from_transform(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_throw_matrix_from_transform(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_spawn_loot_blue_coins](#obj_spawn_loot_blue_coins)

### Lua Example
`obj_spawn_loot_blue_coins(obj, numCoins, sp28, posJitter)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| numCoins | `integer` |
| sp28 | `number` |
| posJitter | `integer` |

### Returns
- None

### C Prototype
`void obj_spawn_loot_blue_coins(struct Object *obj, s32 numCoins, f32 sp28, s16 posJitter);`

[:arrow_up_small:](#)

<br />

## [obj_spawn_loot_coins](#obj_spawn_loot_coins)

### Lua Example
`obj_spawn_loot_coins(obj, numCoins, sp30, coinBehavior, posJitter, model)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| numCoins | `integer` |
| sp30 | `number` |
| coinBehavior | `Pointer` <`BehaviorScript`> |
| posJitter | `integer` |
| model | `integer` |

### Returns
- None

### C Prototype
`void obj_spawn_loot_coins(struct Object *obj, s32 numCoins, f32 sp30, const BehaviorScript *coinBehavior, s16 posJitter, s16 model);`

[:arrow_up_small:](#)

<br />

## [obj_spawn_loot_yellow_coins](#obj_spawn_loot_yellow_coins)

### Lua Example
`obj_spawn_loot_yellow_coins(obj, numCoins, sp28)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| numCoins | `integer` |
| sp28 | `number` |

### Returns
- None

### C Prototype
`void obj_spawn_loot_yellow_coins(struct Object *obj, s32 numCoins, f32 sp28);`

[:arrow_up_small:](#)

<br />

## [obj_translate_local](#obj_translate_local)

### Lua Example
`obj_translate_local(obj, posIndex, localTranslateIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| posIndex | `integer` |
| localTranslateIndex | `integer` |

### Returns
- None

### C Prototype
`void obj_translate_local(struct Object *obj, s16 posIndex, s16 localTranslateIndex);`

[:arrow_up_small:](#)

<br />

## [obj_translate_xyz_random](#obj_translate_xyz_random)

### Lua Example
`obj_translate_xyz_random(obj, rangeLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| rangeLength | `number` |

### Returns
- None

### C Prototype
`void obj_translate_xyz_random(struct Object *obj, f32 rangeLength);`

[:arrow_up_small:](#)

<br />

## [obj_translate_xz_random](#obj_translate_xz_random)

### Lua Example
`obj_translate_xz_random(obj, rangeLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| rangeLength | `number` |

### Returns
- None

### C Prototype
`void obj_translate_xz_random(struct Object *obj, f32 rangeLength);`

[:arrow_up_small:](#)

<br />

## [obj_turn_toward_object](#obj_turn_toward_object)

### Lua Example
`local integerValue = obj_turn_toward_object(obj, target, angleIndex, turnAmount)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| target | [Object](structs.md#Object) |
| angleIndex | `integer` |
| turnAmount | `integer` |

### Returns
- `integer`

### C Prototype
`s16 obj_turn_toward_object(struct Object *obj, struct Object *target, s16 angleIndex, s16 turnAmount);`

[:arrow_up_small:](#)

<br />

## [player_performed_grab_escape_action](#player_performed_grab_escape_action)

### Lua Example
`local integerValue = player_performed_grab_escape_action()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 player_performed_grab_escape_action(void);`

[:arrow_up_small:](#)

<br />

## [random_f32_around_zero](#random_f32_around_zero)

### Lua Example
`local numberValue = random_f32_around_zero(diameter)`

### Parameters
| Field | Type |
| ----- | ---- |
| diameter | `number` |

### Returns
- `number`

### C Prototype
`f32 random_f32_around_zero(f32 diameter);`

[:arrow_up_small:](#)

<br />

## [set_mario_interact_hoot_if_in_range](#set_mario_interact_hoot_if_in_range)

### Lua Example
`set_mario_interact_hoot_if_in_range(sp0, sp4, sp8)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp0 | `integer` |
| sp4 | `integer` |
| sp8 | `number` |

### Returns
- None

### C Prototype
`void set_mario_interact_hoot_if_in_range(UNUSED s32 sp0, UNUSED s32 sp4, f32 sp8);`

[:arrow_up_small:](#)

<br />

## [set_time_stop_flags](#set_time_stop_flags)

### Lua Example
`set_time_stop_flags(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void set_time_stop_flags(s32 flags);`

[:arrow_up_small:](#)

<br />

## [set_time_stop_flags_if_alone](#set_time_stop_flags_if_alone)

### Lua Example
`set_time_stop_flags_if_alone(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void set_time_stop_flags_if_alone(s32 flags);`

[:arrow_up_small:](#)

<br />

## [signum_positive](#signum_positive)

### Lua Example
`local integerValue = signum_positive(x)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `integer` |

### Returns
- `integer`

### C Prototype
`s32 signum_positive(s32 x);`

[:arrow_up_small:](#)

<br />

## [spawn_base_star_with_no_lvl_exit](#spawn_base_star_with_no_lvl_exit)

### Lua Example
`spawn_base_star_with_no_lvl_exit()`

### Parameters
- None

### Returns
- None

### C Prototype
`void spawn_base_star_with_no_lvl_exit(void);`

[:arrow_up_small:](#)

<br />

## [spawn_mist_particles](#spawn_mist_particles)

### Lua Example
`spawn_mist_particles()`

### Parameters
- None

### Returns
- None

### C Prototype
`void spawn_mist_particles(void);`

[:arrow_up_small:](#)

<br />

## [spawn_mist_particles_with_sound](#spawn_mist_particles_with_sound)

### Lua Example
`spawn_mist_particles_with_sound(sp18)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp18 | `integer` |

### Returns
- None

### C Prototype
`void spawn_mist_particles_with_sound(u32 sp18);`

[:arrow_up_small:](#)

<br />

## [spawn_star_with_no_lvl_exit](#spawn_star_with_no_lvl_exit)

### Lua Example
`local ObjectValue = spawn_star_with_no_lvl_exit(sp20, sp24)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp20 | `integer` |
| sp24 | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *spawn_star_with_no_lvl_exit(s32 sp20, s32 sp24);`

[:arrow_up_small:](#)

<br />

## [spawn_water_droplet](#spawn_water_droplet)

### Lua Example
`local ObjectValue = spawn_water_droplet(parent, params)`

### Parameters
| Field | Type |
| ----- | ---- |
| parent | [Object](structs.md#Object) |
| params | [WaterDropletParams](structs.md#WaterDropletParams) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *spawn_water_droplet(struct Object *parent, struct WaterDropletParams *params);`

[:arrow_up_small:](#)

<br />

## [stub_obj_helpers_3](#stub_obj_helpers_3)

### Lua Example
`stub_obj_helpers_3(sp0, sp4)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp0 | `integer` |
| sp4 | `integer` |

### Returns
- None

### C Prototype
`void stub_obj_helpers_3(UNUSED s32 sp0, UNUSED s32 sp4);`

[:arrow_up_small:](#)

<br />

## [stub_obj_helpers_4](#stub_obj_helpers_4)

### Lua Example
`stub_obj_helpers_4()`

### Parameters
- None

### Returns
- None

### C Prototype
`void stub_obj_helpers_4(void);`

[:arrow_up_small:](#)

<br />

---
# functions from object_list_processor.h

<br />


## [set_object_respawn_info_bits](#set_object_respawn_info_bits)

### Lua Example
`set_object_respawn_info_bits(obj, bits)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| bits | `integer` |

### Returns
- None

### C Prototype
`void set_object_respawn_info_bits(struct Object *obj, u8 bits);`

[:arrow_up_small:](#)

<br />

---
# functions from rumble_init.c

<br />


## [queue_rumble_data](#queue_rumble_data)

### Lua Example
`queue_rumble_data(a0, a1)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `integer` |
| a1 | `integer` |

### Returns
- None

### C Prototype
`void queue_rumble_data(s16 a0, s16 a1);`

[:arrow_up_small:](#)

<br />

## [queue_rumble_data_mario](#queue_rumble_data_mario)

### Lua Example
`queue_rumble_data_mario(m, a0, a1)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| a0 | `integer` |
| a1 | `integer` |

### Returns
- None

### C Prototype
`void queue_rumble_data_mario(struct MarioState* m, s16 a0, s16 a1);`

[:arrow_up_small:](#)

<br />

## [queue_rumble_data_object](#queue_rumble_data_object)

### Lua Example
`queue_rumble_data_object(object, a0, a1)`

### Parameters
| Field | Type |
| ----- | ---- |
| object | [Object](structs.md#Object) |
| a0 | `integer` |
| a1 | `integer` |

### Returns
- None

### C Prototype
`void queue_rumble_data_object(struct Object* object, s16 a0, s16 a1);`

[:arrow_up_small:](#)

<br />

## [reset_rumble_timers](#reset_rumble_timers)

### Lua Example
`reset_rumble_timers(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void reset_rumble_timers(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [reset_rumble_timers_2](#reset_rumble_timers_2)

### Lua Example
`reset_rumble_timers_2(m, a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| a0 | `integer` |

### Returns
- None

### C Prototype
`void reset_rumble_timers_2(struct MarioState* m, s32 a0);`

[:arrow_up_small:](#)

<br />

---
# functions from save_file.h

<br />


## [save_file_clear_flags](#save_file_clear_flags)

### Lua Example
`save_file_clear_flags(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void save_file_clear_flags(u32 flags);`

[:arrow_up_small:](#)

<br />

## [save_file_erase_current_backup_save](#save_file_erase_current_backup_save)

### Lua Example
`save_file_erase_current_backup_save()`

### Parameters
- None

### Returns
- None

### C Prototype
`void save_file_erase_current_backup_save(void);`

[:arrow_up_small:](#)

<br />

## [save_file_get_cap_pos](#save_file_get_cap_pos)

### Lua Example
`local integerValue = save_file_get_cap_pos(capPos)`

### Parameters
| Field | Type |
| ----- | ---- |
| capPos | [Vec3s](structs.md#Vec3s) |

### Returns
- `integer`

### C Prototype
`s32 save_file_get_cap_pos(Vec3s capPos);`

[:arrow_up_small:](#)

<br />

## [save_file_get_course_coin_score](#save_file_get_course_coin_score)

### Lua Example
`local integerValue = save_file_get_course_coin_score(fileIndex, courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 save_file_get_course_coin_score(s32 fileIndex, s32 courseIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_get_course_star_count](#save_file_get_course_star_count)

### Lua Example
`local integerValue = save_file_get_course_star_count(fileIndex, courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 save_file_get_course_star_count(s32 fileIndex, s32 courseIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_get_flags](#save_file_get_flags)

### Lua Example
`local integerValue = save_file_get_flags()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 save_file_get_flags(void);`

[:arrow_up_small:](#)

<br />

## [save_file_get_max_coin_score](#save_file_get_max_coin_score)

### Lua Example
`local integerValue = save_file_get_max_coin_score(courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u32 save_file_get_max_coin_score(s32 courseIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_get_sound_mode](#save_file_get_sound_mode)

### Lua Example
`local integerValue = save_file_get_sound_mode()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u16 save_file_get_sound_mode(void);`

[:arrow_up_small:](#)

<br />

## [save_file_get_star_flags](#save_file_get_star_flags)

### Lua Example
`local integerValue = save_file_get_star_flags(fileIndex, courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u32 save_file_get_star_flags(s32 fileIndex, s32 courseIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_get_total_star_count](#save_file_get_total_star_count)

### Lua Example
`local integerValue = save_file_get_total_star_count(fileIndex, minCourse, maxCourse)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| minCourse | `integer` |
| maxCourse | `integer` |

### Returns
- `integer`

### C Prototype
`s32 save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);`

[:arrow_up_small:](#)

<br />

## [save_file_reload](#save_file_reload)

### Lua Example
`save_file_reload(load_all)`

### Parameters
| Field | Type |
| ----- | ---- |
| load_all | `integer` |

### Returns
- None

### C Prototype
`void save_file_reload(u8 load_all);`

[:arrow_up_small:](#)

<br />

## [save_file_set_flags](#save_file_set_flags)

### Lua Example
`save_file_set_flags(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void save_file_set_flags(u32 flags);`

[:arrow_up_small:](#)

<br />

## [save_file_set_star_flags](#save_file_set_star_flags)

### Lua Example
`save_file_set_star_flags(fileIndex, courseIndex, starFlags)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |
| starFlags | `integer` |

### Returns
- None

### C Prototype
`void save_file_set_star_flags(s32 fileIndex, s32 courseIndex, u32 starFlags);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_audio_utils.h

<br />


## [audio_sample_destroy](#audio_sample_destroy)

### Lua Example
`audio_sample_destroy(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |

### Returns
- None

### C Prototype
`void audio_sample_destroy(struct BassAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_sample_load](#audio_sample_load)

### Lua Example
`local BassAudioValue = audio_sample_load(filename)`

### Parameters
| Field | Type |
| ----- | ---- |
| filename | `string` |

### Returns
[BassAudio](structs.md#BassAudio)

### C Prototype
`struct BassAudio* audio_sample_load(const char* filename);`

[:arrow_up_small:](#)

<br />

## [audio_sample_play](#audio_sample_play)

### Lua Example
`audio_sample_play(audio, position, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |
| position | [Vec3f](structs.md#Vec3f) |
| volume | `number` |

### Returns
- None

### C Prototype
`void audio_sample_play(struct BassAudio* audio, Vec3f position, f32 volume);`

[:arrow_up_small:](#)

<br />

## [audio_stream_destroy](#audio_stream_destroy)

### Lua Example
`audio_stream_destroy(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |

### Returns
- None

### C Prototype
`void audio_stream_destroy(struct BassAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_frequency](#audio_stream_get_frequency)

### Lua Example
`local numberValue = audio_stream_get_frequency(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_frequency(struct BassAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_looping](#audio_stream_get_looping)

### Lua Example
`local booleanValue = audio_stream_get_looping(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |

### Returns
- `boolean`

### C Prototype
`bool audio_stream_get_looping(struct BassAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_position](#audio_stream_get_position)

### Lua Example
`local numberValue = audio_stream_get_position(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_position(struct BassAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_tempo](#audio_stream_get_tempo)

### Lua Example
`local numberValue = audio_stream_get_tempo(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_tempo(struct BassAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_volume](#audio_stream_get_volume)

### Lua Example
`local numberValue = audio_stream_get_volume(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_volume(struct BassAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_load](#audio_stream_load)

### Lua Example
`local BassAudioValue = audio_stream_load(filename)`

### Parameters
| Field | Type |
| ----- | ---- |
| filename | `string` |

### Returns
[BassAudio](structs.md#BassAudio)

### C Prototype
`struct BassAudio* audio_stream_load(const char* filename);`

[:arrow_up_small:](#)

<br />

## [audio_stream_load_url](#audio_stream_load_url)

### Lua Example
`local BassAudioValue = audio_stream_load_url(url)`

### Parameters
| Field | Type |
| ----- | ---- |
| url | `string` |

### Returns
[BassAudio](structs.md#BassAudio)

### C Prototype
`struct BassAudio* audio_stream_load_url(const char* url);`

[:arrow_up_small:](#)

<br />

## [audio_stream_pause](#audio_stream_pause)

### Lua Example
`audio_stream_pause(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |

### Returns
- None

### C Prototype
`void audio_stream_pause(struct BassAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_play](#audio_stream_play)

### Lua Example
`audio_stream_play(audio, restart, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |
| restart | `boolean` |
| volume | `number` |

### Returns
- None

### C Prototype
`void audio_stream_play(struct BassAudio* audio, bool restart, f32 volume);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_frequency](#audio_stream_set_frequency)

### Lua Example
`audio_stream_set_frequency(audio, freq)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |
| freq | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_frequency(struct BassAudio* audio, f32 freq);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_looping](#audio_stream_set_looping)

### Lua Example
`audio_stream_set_looping(audio, looping)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |
| looping | `boolean` |

### Returns
- None

### C Prototype
`void audio_stream_set_looping(struct BassAudio* audio, bool looping);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_position](#audio_stream_set_position)

### Lua Example
`audio_stream_set_position(audio, pos)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |
| pos | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_position(struct BassAudio* audio, f32 pos);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_speed](#audio_stream_set_speed)

### Lua Example
`audio_stream_set_speed(audio, initial_freq, speed, pitch)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |
| initial_freq | `number` |
| speed | `number` |
| pitch | `boolean` |

### Returns
- None

### C Prototype
`void audio_stream_set_speed(struct BassAudio* audio, f32 initial_freq, f32 speed, bool pitch);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_tempo](#audio_stream_set_tempo)

### Lua Example
`audio_stream_set_tempo(audio, tempo)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |
| tempo | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_tempo(struct BassAudio* audio, f32 tempo);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_volume](#audio_stream_set_volume)

### Lua Example
`audio_stream_set_volume(audio, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |
| volume | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_volume(struct BassAudio* audio, f32 volume);`

[:arrow_up_small:](#)

<br />

## [audio_stream_stop](#audio_stream_stop)

### Lua Example
`audio_stream_stop(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [BassAudio](structs.md#BassAudio) |

### Returns
- None

### C Prototype
`void audio_stream_stop(struct BassAudio* audio);`

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
# functions from smlua_collision_utils.h

<br />


## [collision_find_surface_on_ray](#collision_find_surface_on_ray)

### Lua Example
`local RayIntersectionInfoValue = collision_find_surface_on_ray(startX, startY, startZ, endX, endY, endZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| startX | `number` |
| startY | `number` |
| startZ | `number` |
| endX | `number` |
| endY | `number` |
| endZ | `number` |

### Returns
[RayIntersectionInfo](structs.md#RayIntersectionInfo)

### C Prototype
`struct RayIntersectionInfo* collision_find_surface_on_ray(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ);`

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
# functions from smlua_level_utils.h

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
`struct CustomLevelInfo* smlua_level_util_get_info_from_short_name(char* shortName);`

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
# functions from smlua_misc_utils.h

<br />


## [add_scroll_target](#add_scroll_target)

### Lua Example
`add_scroll_target(index, name, offset, size)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| name | `string` |
| offset | `integer` |
| size | `integer` |

### Returns
- None

### C Prototype
`void add_scroll_target(u32 index, const char* name, u32 offset, u32 size);`

[:arrow_up_small:](#)

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

---
# functions from smlua_model_utils.h

<br />


## [smlua_model_util_get_id](#smlua_model_util_get_id)

### Lua Example
`local integerValue = smlua_model_util_get_id(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
- `integer`

### C Prototype
`u32 smlua_model_util_get_id(const char* name);`

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

## [smlua_text_utils_reset_all](#smlua_text_utils_reset_all)

### Lua Example
`smlua_text_utils_reset_all()`

### Parameters
- None

### Returns
- None

### C Prototype
`void smlua_text_utils_reset_all(void);`

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
`exec_anim_sound_state(soundStates)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundStates | [SoundState](structs.md#SoundState) |

### Returns
- None

### C Prototype
`void exec_anim_sound_state(struct SoundState *soundStates);`

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

---

[< prev](functions-3.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | 4]

