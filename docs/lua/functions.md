## [:rewind: Lua Reference](lua.md)

# Supported Functions
- camera.h
   - [set_camera_pitch_shake](#set_camera_pitch_shake)
   - [set_camera_roll_shake](#set_camera_roll_shake)
   - [set_camera_shake_from_hit](#set_camera_shake_from_hit)
   - [set_camera_shake_from_point](#set_camera_shake_from_point)
   - [set_camera_yaw_shake](#set_camera_yaw_shake)
   - [set_environmental_camera_shake](#set_environmental_camera_shake)

<br />

- characters.h
   - [get_character](#get_character)
   - [get_character_anim_offset](#get_character_anim_offset)
   - [play_character_sound](#play_character_sound)
   - [play_character_sound_if_no_flag](#play_character_sound_if_no_flag)
   - [play_character_sound_offset](#play_character_sound_offset)
   - [update_character_anim_offset](#update_character_anim_offset)

<br />

- djui_chat_message.h
   - [djui_chat_message_create](#djui_chat_message_create)

<br />

- djui_popup.h
   - [djui_popup_create](#djui_popup_create)

<br />

- external.h
   - [fade_volume_scale](#fade_volume_scale)
   - [fadeout_background_music](#fadeout_background_music)
   - [play_course_clear](#play_course_clear)
   - [play_dialog_sound](#play_dialog_sound)
   - [play_music](#play_music)
   - [play_peachs_jingle](#play_peachs_jingle)
   - [play_power_star_jingle](#play_power_star_jingle)
   - [play_puzzle_jingle](#play_puzzle_jingle)
   - [play_race_fanfare](#play_race_fanfare)
   - [play_secondary_music](#play_secondary_music)
   - [play_sound](#play_sound)
   - [play_sound_with_freq_scale](#play_sound_with_freq_scale)
   - [play_star_fanfare](#play_star_fanfare)
   - [play_toads_jingle](#play_toads_jingle)
   - [sequence_player_fade_out](#sequence_player_fade_out)
   - [sequence_player_unlower](#sequence_player_unlower)

<br />

- interaction.h
   - [does_mario_have_hat](#does_mario_have_hat)
   - [get_door_save_file_flag](#get_door_save_file_flag)
   - [mario_blow_off_cap](#mario_blow_off_cap)
   - [mario_check_object_grab](#mario_check_object_grab)
   - [mario_drop_held_object](#mario_drop_held_object)
   - [mario_get_collided_object](#mario_get_collided_object)
   - [mario_grab_used_object](#mario_grab_used_object)
   - [mario_lose_cap_to_enemy](#mario_lose_cap_to_enemy)
   - [mario_obj_angle_to_object](#mario_obj_angle_to_object)
   - [mario_retrieve_cap](#mario_retrieve_cap)
   - [mario_stop_riding_and_holding](#mario_stop_riding_and_holding)
   - [mario_stop_riding_object](#mario_stop_riding_object)
   - [mario_throw_held_object](#mario_throw_held_object)

<br />

- level_info.h
   - [get_level_name](#get_level_name)

<br />

- mario.h
   - [adjust_sound_for_speed](#adjust_sound_for_speed)
   - [check_common_action_exits](#check_common_action_exits)
   - [check_common_hold_action_exits](#check_common_hold_action_exits)
   - [drop_and_set_mario_action](#drop_and_set_mario_action)
   - [execute_mario_action](#execute_mario_action)
   - [find_floor_height_relative_polar](#find_floor_height_relative_polar)
   - [find_floor_slope](#find_floor_slope)
   - [find_mario_anim_flags_and_translation](#find_mario_anim_flags_and_translation)
   - [force_idle_state](#force_idle_state)
   - [hurt_and_set_mario_action](#hurt_and_set_mario_action)
   - [is_anim_at_end](#is_anim_at_end)
   - [is_anim_past_end](#is_anim_past_end)
   - [is_anim_past_frame](#is_anim_past_frame)
   - [mario_facing_downhill](#mario_facing_downhill)
   - [mario_floor_is_slippery](#mario_floor_is_slippery)
   - [mario_floor_is_slope](#mario_floor_is_slope)
   - [mario_floor_is_steep](#mario_floor_is_steep)
   - [mario_get_floor_class](#mario_get_floor_class)
   - [mario_get_terrain_sound_addend](#mario_get_terrain_sound_addend)
   - [mario_set_bubbled](#mario_set_bubbled)
   - [mario_set_forward_vel](#mario_set_forward_vel)
   - [play_mario_action_sound](#play_mario_action_sound)
   - [play_mario_heavy_landing_sound](#play_mario_heavy_landing_sound)
   - [play_mario_heavy_landing_sound_once](#play_mario_heavy_landing_sound_once)
   - [play_mario_jump_sound](#play_mario_jump_sound)
   - [play_mario_landing_sound](#play_mario_landing_sound)
   - [play_mario_landing_sound_once](#play_mario_landing_sound_once)
   - [play_mario_sound](#play_mario_sound)
   - [play_sound_and_spawn_particles](#play_sound_and_spawn_particles)
   - [play_sound_if_no_flag](#play_sound_if_no_flag)
   - [resolve_and_return_wall_collisions](#resolve_and_return_wall_collisions)
   - [return_mario_anim_y_translation](#return_mario_anim_y_translation)
   - [set_anim_to_frame](#set_anim_to_frame)
   - [set_jump_from_landing](#set_jump_from_landing)
   - [set_jumping_action](#set_jumping_action)
   - [set_mario_action](#set_mario_action)
   - [set_mario_anim_with_accel](#set_mario_anim_with_accel)
   - [set_mario_animation](#set_mario_animation)
   - [set_steep_jump_action](#set_steep_jump_action)
   - [set_water_plunge_action](#set_water_plunge_action)
   - [transition_submerged_to_walking](#transition_submerged_to_walking)
   - [update_mario_pos_for_anim](#update_mario_pos_for_anim)
   - [update_mario_sound_and_camera](#update_mario_sound_and_camera)

<br />

- mario_actions_airborne.c
   - [check_common_airborne_cancels](#check_common_airborne_cancels)
   - [check_fall_damage](#check_fall_damage)
   - [check_fall_damage_or_get_stuck](#check_fall_damage_or_get_stuck)
   - [check_horizontal_wind](#check_horizontal_wind)
   - [check_kick_or_dive_in_air](#check_kick_or_dive_in_air)
   - [check_wall_kick](#check_wall_kick)
   - [common_air_action_step](#common_air_action_step)
   - [common_air_knockback_step](#common_air_knockback_step)
   - [lava_boost_on_wall](#lava_boost_on_wall)
   - [mario_execute_airborne_action](#mario_execute_airborne_action)
   - [play_far_fall_sound](#play_far_fall_sound)
   - [play_flip_sounds](#play_flip_sounds)
   - [play_knockback_sound](#play_knockback_sound)
   - [should_get_stuck_in_ground](#should_get_stuck_in_ground)
   - [update_air_with_turn](#update_air_with_turn)
   - [update_air_without_turn](#update_air_without_turn)
   - [update_flying](#update_flying)
   - [update_flying_pitch](#update_flying_pitch)
   - [update_flying_yaw](#update_flying_yaw)
   - [update_lava_boost_or_twirling](#update_lava_boost_or_twirling)

<br />

- mario_actions_automatic.c
   - [add_tree_leaf_particles](#add_tree_leaf_particles)
   - [check_common_automatic_cancels](#check_common_automatic_cancels)
   - [climb_up_ledge](#climb_up_ledge)
   - [let_go_of_ledge](#let_go_of_ledge)
   - [mario_execute_automatic_action](#mario_execute_automatic_action)
   - [perform_hanging_step](#perform_hanging_step)
   - [play_climbing_sounds](#play_climbing_sounds)
   - [set_pole_position](#set_pole_position)
   - [update_hang_moving](#update_hang_moving)
   - [update_hang_stationary](#update_hang_stationary)
   - [update_ledge_climb](#update_ledge_climb)
   - [update_ledge_climb_camera](#update_ledge_climb_camera)

<br />

- mario_actions_cutscene.c
   - [bhv_end_peach_loop](#bhv_end_peach_loop)
   - [bhv_end_toad_loop](#bhv_end_toad_loop)
   - [common_death_handler](#common_death_handler)
   - [cutscene_put_cap_on](#cutscene_put_cap_on)
   - [cutscene_take_cap_off](#cutscene_take_cap_off)
   - [general_star_dance_handler](#general_star_dance_handler)
   - [generate_yellow_sparkles](#generate_yellow_sparkles)
   - [get_star_collection_dialog](#get_star_collection_dialog)
   - [handle_save_menu](#handle_save_menu)
   - [launch_mario_until_land](#launch_mario_until_land)
   - [mario_execute_cutscene_action](#mario_execute_cutscene_action)
   - [mario_ready_to_speak](#mario_ready_to_speak)
   - [print_displaying_credits_entry](#print_displaying_credits_entry)
   - [should_start_or_continue_dialog](#should_start_or_continue_dialog)
   - [stuck_in_ground_handler](#stuck_in_ground_handler)

<br />

- mario_actions_moving.c
   - [align_with_floor](#align_with_floor)
   - [analog_stick_held_back](#analog_stick_held_back)
   - [anim_and_audio_for_heavy_walk](#anim_and_audio_for_heavy_walk)
   - [anim_and_audio_for_hold_walk](#anim_and_audio_for_hold_walk)
   - [anim_and_audio_for_walk](#anim_and_audio_for_walk)
   - [apply_landing_accel](#apply_landing_accel)
   - [apply_slope_accel](#apply_slope_accel)
   - [apply_slope_decel](#apply_slope_decel)
   - [begin_braking_action](#begin_braking_action)
   - [begin_walking_action](#begin_walking_action)
   - [check_common_moving_cancels](#check_common_moving_cancels)
   - [check_ground_dive_or_punch](#check_ground_dive_or_punch)
   - [check_ledge_climb_down](#check_ledge_climb_down)
   - [common_ground_knockback_action](#common_ground_knockback_action)
   - [common_landing_action](#common_landing_action)
   - [common_slide_action](#common_slide_action)
   - [common_slide_action_with_jump](#common_slide_action_with_jump)
   - [mario_execute_moving_action](#mario_execute_moving_action)
   - [play_step_sound](#play_step_sound)
   - [push_or_sidle_wall](#push_or_sidle_wall)
   - [quicksand_jump_land_action](#quicksand_jump_land_action)
   - [set_triple_jump_action](#set_triple_jump_action)
   - [should_begin_sliding](#should_begin_sliding)
   - [slide_bonk](#slide_bonk)
   - [stomach_slide_action](#stomach_slide_action)
   - [tilt_body_butt_slide](#tilt_body_butt_slide)
   - [tilt_body_ground_shell](#tilt_body_ground_shell)
   - [tilt_body_running](#tilt_body_running)
   - [tilt_body_walking](#tilt_body_walking)
   - [update_decelerating_speed](#update_decelerating_speed)
   - [update_shell_speed](#update_shell_speed)
   - [update_sliding](#update_sliding)
   - [update_sliding_angle](#update_sliding_angle)
   - [update_walking_speed](#update_walking_speed)

<br />

- mario_actions_object.c
   - [animated_stationary_ground_step](#animated_stationary_ground_step)
   - [check_common_object_cancels](#check_common_object_cancels)
   - [mario_execute_object_action](#mario_execute_object_action)
   - [mario_update_punch_sequence](#mario_update_punch_sequence)

<br />

- mario_actions_stationary.c
   - [check_common_hold_idle_cancels](#check_common_hold_idle_cancels)
   - [check_common_idle_cancels](#check_common_idle_cancels)
   - [check_common_landing_cancels](#check_common_landing_cancels)
   - [check_common_stationary_cancels](#check_common_stationary_cancels)
   - [landing_step](#landing_step)
   - [mario_execute_stationary_action](#mario_execute_stationary_action)
   - [play_anim_sound](#play_anim_sound)
   - [stopping_step](#stopping_step)

<br />

- mario_actions_submerged.c
   - [apply_water_current](#apply_water_current)
   - [float_surface_gfx](#float_surface_gfx)
   - [mario_execute_submerged_action](#mario_execute_submerged_action)
   - [perform_water_full_step](#perform_water_full_step)
   - [perform_water_step](#perform_water_step)
   - [set_swimming_at_surface_particles](#set_swimming_at_surface_particles)

<br />

- mario_step.h
   - [get_additive_y_vel_for_jumps](#get_additive_y_vel_for_jumps)
   - [mario_bonk_reflection](#mario_bonk_reflection)
   - [mario_push_off_steep_floor](#mario_push_off_steep_floor)
   - [mario_update_moving_sand](#mario_update_moving_sand)
   - [mario_update_quicksand](#mario_update_quicksand)
   - [mario_update_windy_ground](#mario_update_windy_ground)
   - [perform_air_step](#perform_air_step)
   - [perform_ground_step](#perform_ground_step)
   - [set_vel_from_pitch_and_yaw](#set_vel_from_pitch_and_yaw)
   - [stationary_ground_step](#stationary_ground_step)
   - [stop_and_set_height_to_floor](#stop_and_set_height_to_floor)

<br />

- network_utils.h
   - [network_get_player_text_color_string](#network_get_player_text_color_string)
   - [network_global_index_from_local](#network_global_index_from_local)
   - [network_is_server](#network_is_server)
   - [network_local_index_from_global](#network_local_index_from_global)

<br />

- save_file.h
   - [save_file_get_cap_pos](#save_file_get_cap_pos)
   - [save_file_get_course_coin_score](#save_file_get_course_coin_score)
   - [save_file_get_course_star_count](#save_file_get_course_star_count)
   - [save_file_get_flags](#save_file_get_flags)
   - [save_file_get_max_coin_score](#save_file_get_max_coin_score)
   - [save_file_get_sound_mode](#save_file_get_sound_mode)
   - [save_file_get_star_flags](#save_file_get_star_flags)
   - [save_file_get_total_star_count](#save_file_get_total_star_count)

<br />

- sound_init.h
   - [disable_background_sound](#disable_background_sound)
   - [enable_background_sound](#enable_background_sound)
   - [fadeout_cap_music](#fadeout_cap_music)
   - [fadeout_level_music](#fadeout_level_music)
   - [fadeout_music](#fadeout_music)
   - [lower_background_noise](#lower_background_noise)
   - [play_cap_music](#play_cap_music)
   - [play_cutscene_music](#play_cutscene_music)
   - [play_infinite_stairs_music](#play_infinite_stairs_music)
   - [play_menu_sounds](#play_menu_sounds)
   - [play_painting_eject_sound](#play_painting_eject_sound)
   - [play_shell_music](#play_shell_music)
   - [raise_background_noise](#raise_background_noise)
   - [reset_volume](#reset_volume)
   - [set_background_music](#set_background_music)
   - [stop_cap_music](#stop_cap_music)
   - [stop_shell_music](#stop_shell_music)

<br />

- surface_collision.h
   - [find_floor_height](#find_floor_height)
   - [find_poison_gas_level](#find_poison_gas_level)
   - [find_wall_collisions](#find_wall_collisions)
   - [find_water_level](#find_water_level)

<br />

- thread6.c
   - [queue_rumble_data](#queue_rumble_data)
   - [queue_rumble_data_mario](#queue_rumble_data_mario)
   - [queue_rumble_data_object](#queue_rumble_data_object)

<br />


---
# functions from camera.h

<br />


## [set_camera_pitch_shake](#set_camera_pitch_shake)

### Lua Example
`set_camera_pitch_shake(mag, decay, inc)`

### Parameters
| Field | Type |
| ----- | ---- |
| mag | integer |
| decay | integer |
| inc | integer |

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
| mag | integer |
| decay | integer |
| inc | integer |

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
| shake | integer |

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
| shake | integer |
| posX | number |
| posY | number |
| posZ | number |

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
| mag | integer |
| decay | integer |
| inc | integer |

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
| shake | integer |

### Returns
- None

### C Prototype
`void set_environmental_camera_shake(s16 shake);`

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
- number

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
| characterSound | integer |

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
| characterSound | integer |
| flags | integer |

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
| characterSound | integer |
| offset | integer |

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
| message | string |

### Returns
- None

### C Prototype
`void djui_chat_message_create(const char* message);`

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
| message | string |
| lines | int |

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
`fade_volume_scale(player, targetScale, fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | integer |
| targetScale | integer |
| fadeTimer | integer |

### Returns
- None

### C Prototype
`void fade_volume_scale(u8 player, u8 targetScale, u16 fadeTimer);`

[:arrow_up_small:](#)

<br />

## [fadeout_background_music](#fadeout_background_music)

### Lua Example
`fadeout_background_music(arg0, fadeOut)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | integer |
| fadeOut | integer |

### Returns
- None

### C Prototype
`void fadeout_background_music(u16 arg0, u16 fadeOut);`

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
| dialogID | integer |

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
| player | integer |
| seqArgs | integer |
| fadeTimer | integer |

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
| arg0 | integer |

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
| seqId | integer |
| bgMusicVolume | integer |
| volume | integer |
| fadeTimer | integer |

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
| soundBits | integer |
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
| soundBits | integer |
| pos | [Vec3f](structs.md#Vec3f) |
| freqScale | number |

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

## [sequence_player_fade_out](#sequence_player_fade_out)

### Lua Example
`sequence_player_fade_out(player, fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | integer |
| fadeTimer | integer |

### Returns
- None

### C Prototype
`void sequence_player_fade_out(u8 player, u16 fadeTimer);`

[:arrow_up_small:](#)

<br />

## [sequence_player_unlower](#sequence_player_unlower)

### Lua Example
`sequence_player_unlower(player, fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | integer |
| fadeTimer | integer |

### Returns
- None

### C Prototype
`void sequence_player_unlower(u8 player, u16 fadeTimer);`

[:arrow_up_small:](#)

<br />

---
# functions from interaction.h

<br />


## [does_mario_have_hat](#does_mario_have_hat)

### Lua Example
`local integerValue = does_mario_have_hat(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- integer

### C Prototype
`u32 does_mario_have_hat(struct MarioState *m);`

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
- integer

### C Prototype
`u32 get_door_save_file_flag(struct Object *door);`

[:arrow_up_small:](#)

<br />

## [mario_blow_off_cap](#mario_blow_off_cap)

### Lua Example
`mario_blow_off_cap(m, capSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| capSpeed | number |

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
- integer

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
| interactType | integer |

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
| arg | integer |

### Returns
- integer

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
- integer

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

---
# functions from level_info.h

<br />


## [get_level_name](#get_level_name)

### Lua Example
`local stringValue = get_level_name(courseNum, levelNum, areaIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | integer |
| levelNum | integer |
| areaIndex | integer |

### Returns
- string

### C Prototype
`const char* get_level_name(s16 courseNum, s16 levelNum, s16 areaIndex);`

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
- integer

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
- integer

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
| action | integer |
| actionArg | integer |

### Returns
- integer

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
- integer

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
| angleFromMario | integer |
| distFromMario | number |

### Returns
- number

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
| yawOffset | integer |

### Returns
- integer

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
| yaw | integer |
| translation | [Vec3s](structs.md#Vec3s) |

### Returns
- integer

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
- integer

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
| action | integer |
| actionArg | integer |
| hurtCounter | integer |

### Returns
- integer

### C Prototype
`s32 hurt_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg, s16 hurtCounter);`

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
- integer

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
- integer

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
| animFrame | integer |

### Returns
- integer

### C Prototype
`s32 is_anim_past_frame(struct MarioState *m, s16 animFrame);`

[:arrow_up_small:](#)

<br />

## [mario_facing_downhill](#mario_facing_downhill)

### Lua Example
`local integerValue = mario_facing_downhill(m, turnYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| turnYaw | integer |

### Returns
- integer

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
- integer

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
- integer

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
- integer

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
- integer

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
- integer

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
| speed | number |

### Returns
- None

### C Prototype
`void mario_set_forward_vel(struct MarioState *m, f32 speed);`

[:arrow_up_small:](#)

<br />

## [play_mario_action_sound](#play_mario_action_sound)

### Lua Example
`play_mario_action_sound(m, soundBits, waveParticleType)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| soundBits | integer |
| waveParticleType | integer |

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
| soundBits | integer |

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
| soundBits | integer |

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
| soundBits | integer |

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
| soundBits | integer |

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
| primarySoundBits | integer |
| scondarySoundBits | integer |

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
| soundBits | integer |
| waveParticleType | integer |

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
| soundBits | integer |
| flags | integer |

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
| offset | number |
| radius | number |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface *resolve_and_return_wall_collisions(Vec3f pos, f32 offset, f32 radius);`

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
- integer

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
| animFrame | integer |

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
- integer

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
| action | integer |
| actionArg | integer |

### Returns
- integer

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
| action | integer |
| actionArg | integer |

### Returns
- integer

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
| targetAnimID | integer |
| accel | integer |

### Returns
- integer

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
| targetAnimID | integer |

### Returns
- integer

### C Prototype
`s16 set_mario_animation(struct MarioState *m, s32 targetAnimID);`

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
- integer

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
- integer

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
- integer

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
| hardFallAction | integer |

### Returns
- integer

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
| hardFallAction | integer |

### Returns
- integer

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
- integer

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
- integer

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
- integer

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
| landAction | integer |
| animation | integer |
| stepArg | integer |

### Returns
- integer

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
| landAction | integer |
| hardFallAction | integer |
| animation | integer |
| speed | number |

### Returns
- integer

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
- integer

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
- integer

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
| frame1 | integer |
| frame2 | integer |
| frame3 | integer |

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
- integer

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
- integer

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
- integer

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
- integer

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
- integer

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
| b | integer |

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
| offsetY | number |

### Returns
- integer

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
- integer

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
| animation | integer |
| endAction | integer |

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
| animation | integer |
| frameToDeathWarp | integer |

### Returns
- integer

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
| isInWater | integer |

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
| x | integer |
| y | integer |
| z | integer |
| radius | number |

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
- integer

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
| endAction | integer |
| animation | integer |
| forwardVel | number |

### Returns
- integer

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
- integer

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
- integer

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
- integer

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
| animation | integer |
| unstuckFrame | integer |
| target2 | integer |
| target3 | integer |
| endAction | integer |

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
- integer

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
| frictionFactor | number |

### Returns
- integer

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
| decelCoef | number |

### Returns
- integer

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
- integer

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
| forwardVel | number |
| action | integer |
| actionArg | integer |

### Returns
- integer

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
- integer

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
- integer

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
| animation | integer |
| arg2 | integer |
| arg3 | integer |
| arg4 | integer |

### Returns
- integer

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
| animation | integer |
| airAction | integer |

### Returns
- integer

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
| endAction | integer |
| airAction | integer |
| animation | integer |

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
| stopAction | integer |
| jumpAction | integer |
| airAction | integer |
| animation | integer |

### Returns
- integer

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
- integer

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
| frame1 | integer |
| frame2 | integer |

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
| animation1 | integer |
| animation2 | integer |
| endAction | integer |
| airAction | integer |

### Returns
- integer

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
| action | integer |
| actionArg | integer |

### Returns
- integer

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
- integer

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
| fastAction | integer |
| slowAction | integer |

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
| stopAction | integer |
| airAction | integer |
| animation | integer |

### Returns
- integer

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
| startYaw | integer |

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
- integer

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
| startYaw | integer |

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
- integer

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
| stopSpeed | number |

### Returns
- integer

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
| accel | number |
| lossFactor | number |

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
| animation | integer |
| endAction | integer |

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
- integer

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
- integer

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
- integer

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
- integer

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
- integer

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
| action | integer |

### Returns
- integer

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
- integer

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
| arg1 | integer |
| action | integer |

### Returns
- integer

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
- integer

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
| actionState | integer |
| animFrame | integer |
| sound | integer |

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
| animID | integer |
| action | integer |

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
- integer

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
- integer

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
- integer

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
| particleFlag | integer |

### Returns
- None

### C Prototype
`void set_swimming_at_surface_particles(struct MarioState *m, u32 particleFlag);`

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
- number

### C Prototype
`f32 get_additive_y_vel_for_jumps(void);`

[:arrow_up_small:](#)

<br />

## [mario_bonk_reflection](#mario_bonk_reflection)

### Lua Example
`mario_bonk_reflection(arg0, arg1)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | [MarioState](structs.md#MarioState) |
| arg1 | integer |

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
| arg1 | integer |
| arg2 | integer |

### Returns
- integer

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
- integer

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
| arg1 | number |

### Returns
- integer

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
- integer

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
| arg1 | integer |

### Returns
- integer

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
- integer

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
- integer

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
# functions from network_utils.h

<br />


## [network_get_player_text_color_string](#network_get_player_text_color_string)

### Lua Example
`local stringValue = network_get_player_text_color_string(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | integer |

### Returns
- string

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
| localIndex | integer |

### Returns
- integer

### C Prototype
`u8 network_global_index_from_local(u8 localIndex);`

[:arrow_up_small:](#)

<br />

## [network_is_server](#network_is_server)

### Lua Example
`local boolValue = network_is_server()`

### Parameters
- None

### Returns
- bool

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
| globalIndex | integer |

### Returns
- integer

### C Prototype
`u8 network_local_index_from_global(u8 globalIndex);`

[:arrow_up_small:](#)

<br />

---
# functions from save_file.h

<br />


## [save_file_get_cap_pos](#save_file_get_cap_pos)

### Lua Example
`local integerValue = save_file_get_cap_pos(capPos)`

### Parameters
| Field | Type |
| ----- | ---- |
| capPos | [Vec3s](structs.md#Vec3s) |

### Returns
- integer

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
| fileIndex | integer |
| courseIndex | integer |

### Returns
- integer

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
| fileIndex | integer |
| courseIndex | integer |

### Returns
- integer

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
- integer

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
| courseIndex | integer |

### Returns
- integer

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
- integer

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
| fileIndex | integer |
| courseIndex | integer |

### Returns
- integer

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
| fileIndex | integer |
| minCourse | integer |
| maxCourse | integer |

### Returns
- integer

### C Prototype
`s32 save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);`

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
| fadeTimer | integer |

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
| fadeOutTime | integer |

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
| a | integer |

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
| seqArgs | integer |

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
| seqArgs | integer |

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
| soundMenuFlags | integer |

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
| a | integer |

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
| a | integer |
| seqArgs | integer |
| fadeTimer | integer |

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
# functions from surface_collision.h

<br />


## [find_floor_height](#find_floor_height)

### Lua Example
`local numberValue = find_floor_height(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | number |
| y | number |
| z | number |

### Returns
- number

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
| x | number |
| z | number |

### Returns
- number

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
- integer

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
| x | number |
| z | number |

### Returns
- number

### C Prototype
`f32 find_water_level(f32 x, f32 z);`

[:arrow_up_small:](#)

<br />

---
# functions from thread6.c

<br />


## [queue_rumble_data](#queue_rumble_data)

### Lua Example
`queue_rumble_data(a0, a1)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | integer |
| a1 | integer |

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
| a0 | integer |
| a1 | integer |

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
| a0 | integer |
| a1 | integer |

### Returns
- None

### C Prototype
`void queue_rumble_data_object(struct Object* object, s16 a0, s16 a1);`

[:arrow_up_small:](#)

<br />
