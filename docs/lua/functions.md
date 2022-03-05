## [:rewind: Lua Reference](lua.md)

# Supported Functions

- manually written functions
   - [define_custom_obj_fields](#define_custom_obj_fields)
   - [network_init_object](#network_init_object)
   - [network_send_object](#network_send_object)

<br />

- behavior_table.h
   - [get_behavior_from_id](#get_behavior_from_id)
   - [get_id_from_behavior](#get_id_from_behavior)

<br />

- camera.h
   - [set_camera_mode](#set_camera_mode)
   - [set_camera_mode_fixed](#set_camera_mode_fixed)
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

- djui_hud_utils.h
   - [djui_hud_get_screen_height](#djui_hud_get_screen_height)
   - [djui_hud_get_screen_width](#djui_hud_get_screen_width)
   - [djui_hud_measure_text](#djui_hud_measure_text)
   - [djui_hud_print_text](#djui_hud_print_text)
   - [djui_hud_render_rect](#djui_hud_render_rect)
   - [djui_hud_render_texture](#djui_hud_render_texture)
   - [djui_hud_set_color](#djui_hud_set_color)
   - [djui_hud_set_font](#djui_hud_set_font)
   - [djui_hud_set_resolution](#djui_hud_set_resolution)

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
   - [does_mario_have_normal_cap_on_head](#does_mario_have_normal_cap_on_head)
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
   - [init_bully_collision_data](#init_bully_collision_data)
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

- network_player.h
   - [get_network_player_from_area](#get_network_player_from_area)
   - [get_network_player_from_level](#get_network_player_from_level)
   - [get_network_player_smallest_global](#get_network_player_smallest_global)
   - [network_player_connected_count](#network_player_connected_count)
   - [network_player_from_global_index](#network_player_from_global_index)
   - [network_player_set_description](#network_player_set_description)

<br />

- network_utils.h
   - [network_get_player_text_color_string](#network_get_player_text_color_string)
   - [network_global_index_from_local](#network_global_index_from_local)
   - [network_is_server](#network_is_server)
   - [network_local_index_from_global](#network_local_index_from_global)

<br />

- obj_behaviors.c
   - [absf_2](#absf_2)
   - [calc_new_obj_vel_and_pos_y](#calc_new_obj_vel_and_pos_y)
   - [calc_new_obj_vel_and_pos_y_underwater](#calc_new_obj_vel_and_pos_y_underwater)
   - [calc_obj_friction](#calc_obj_friction)
   - [current_mario_room_check](#current_mario_room_check)
   - [is_player_active](#is_player_active)
   - [is_point_close_to_object](#is_point_close_to_object)
   - [is_point_within_radius_of_mario](#is_point_within_radius_of_mario)
   - [nearest_mario_state_to_object](#nearest_mario_state_to_object)
   - [nearest_player_to_object](#nearest_player_to_object)
   - [obj_check_floor_death](#obj_check_floor_death)
   - [obj_check_if_facing_toward_angle](#obj_check_if_facing_toward_angle)
   - [obj_find_wall](#obj_find_wall)
   - [obj_find_wall_displacement](#obj_find_wall_displacement)
   - [obj_flicker_and_disappear](#obj_flicker_and_disappear)
   - [obj_lava_death](#obj_lava_death)
   - [obj_move_xyz_using_fvel_and_yaw](#obj_move_xyz_using_fvel_and_yaw)
   - [obj_orient_graph](#obj_orient_graph)
   - [obj_return_and_displace_home](#obj_return_and_displace_home)
   - [obj_return_home_if_safe](#obj_return_home_if_safe)
   - [obj_spawn_yellow_coins](#obj_spawn_yellow_coins)
   - [obj_splash](#obj_splash)
   - [obj_update_pos_vel_xz](#obj_update_pos_vel_xz)
   - [object_step](#object_step)
   - [object_step_without_floor_orient](#object_step_without_floor_orient)
   - [set_object_visibility](#set_object_visibility)
   - [set_yoshi_as_not_dead](#set_yoshi_as_not_dead)
   - [spawn_orange_number](#spawn_orange_number)
   - [turn_obj_away_from_steep_floor](#turn_obj_away_from_steep_floor)
   - [turn_obj_away_from_surface](#turn_obj_away_from_surface)

<br />

- obj_behaviors_2.c
   - [approach_f32_ptr](#approach_f32_ptr)
   - [cur_obj_init_anim_and_check_if_end](#cur_obj_init_anim_and_check_if_end)
   - [cur_obj_init_anim_check_frame](#cur_obj_init_anim_check_frame)
   - [cur_obj_init_anim_extend](#cur_obj_init_anim_extend)
   - [cur_obj_play_sound_at_anim_range](#cur_obj_play_sound_at_anim_range)
   - [cur_obj_set_anim_if_at_end](#cur_obj_set_anim_if_at_end)
   - [cur_obj_spin_all_dimensions](#cur_obj_spin_all_dimensions)
   - [obj_act_knockback](#obj_act_knockback)
   - [obj_act_squished](#obj_act_squished)
   - [obj_bounce_off_walls_edges_objects](#obj_bounce_off_walls_edges_objects)
   - [obj_check_attacks](#obj_check_attacks)
   - [obj_compute_vel_from_move_pitch](#obj_compute_vel_from_move_pitch)
   - [obj_die_if_above_lava_and_health_non_positive](#obj_die_if_above_lava_and_health_non_positive)
   - [obj_die_if_health_non_positive](#obj_die_if_health_non_positive)
   - [obj_face_pitch_approach](#obj_face_pitch_approach)
   - [obj_face_roll_approach](#obj_face_roll_approach)
   - [obj_face_yaw_approach](#obj_face_yaw_approach)
   - [obj_forward_vel_approach](#obj_forward_vel_approach)
   - [obj_get_pitch_from_vel](#obj_get_pitch_from_vel)
   - [obj_get_pitch_to_home](#obj_get_pitch_to_home)
   - [obj_grow_then_shrink](#obj_grow_then_shrink)
   - [obj_handle_attacks](#obj_handle_attacks)
   - [obj_is_near_to_and_facing_mario](#obj_is_near_to_and_facing_mario)
   - [obj_is_rendering_enabled](#obj_is_rendering_enabled)
   - [obj_move_for_one_second](#obj_move_for_one_second)
   - [obj_move_pitch_approach](#obj_move_pitch_approach)
   - [obj_random_fixed_turn](#obj_random_fixed_turn)
   - [obj_resolve_collisions_and_turn](#obj_resolve_collisions_and_turn)
   - [obj_resolve_object_collisions](#obj_resolve_object_collisions)
   - [obj_roll_to_match_yaw_turn](#obj_roll_to_match_yaw_turn)
   - [obj_rotate_yaw_and_bounce_off_walls](#obj_rotate_yaw_and_bounce_off_walls)
   - [obj_set_dist_from_home](#obj_set_dist_from_home)
   - [obj_set_knockback_action](#obj_set_knockback_action)
   - [obj_set_squished_action](#obj_set_squished_action)
   - [obj_smooth_turn](#obj_smooth_turn)
   - [obj_spit_fire](#obj_spit_fire)
   - [obj_turn_pitch_toward_mario](#obj_turn_pitch_toward_mario)
   - [obj_unused_die](#obj_unused_die)
   - [obj_update_blinking](#obj_update_blinking)
   - [obj_update_standard_actions](#obj_update_standard_actions)
   - [obj_y_vel_approach](#obj_y_vel_approach)
   - [oscillate_toward](#oscillate_toward)
   - [platform_on_track_update_pos_or_spawn_ball](#platform_on_track_update_pos_or_spawn_ball)
   - [random_linear_offset](#random_linear_offset)
   - [random_mod_offset](#random_mod_offset)

<br />

- object_helpers.c
   - [abs_angle_diff](#abs_angle_diff)
   - [apply_drag_to_value](#apply_drag_to_value)
   - [approach_f32_signed](#approach_f32_signed)
   - [approach_f32_symmetric](#approach_f32_symmetric)
   - [approach_s16_symmetric](#approach_s16_symmetric)
   - [bhv_dust_smoke_loop](#bhv_dust_smoke_loop)
   - [bhv_init_room](#bhv_init_room)
   - [bit_shift_left](#bit_shift_left)
   - [chain_segment_init](#chain_segment_init)
   - [clear_move_flag](#clear_move_flag)
   - [clear_time_stop_flags](#clear_time_stop_flags)
   - [count_objects_with_behavior](#count_objects_with_behavior)
   - [count_unimportant_objects](#count_unimportant_objects)
   - [cur_obj_abs_y_dist_to_home](#cur_obj_abs_y_dist_to_home)
   - [cur_obj_advance_looping_anim](#cur_obj_advance_looping_anim)
   - [cur_obj_align_gfx_with_floor](#cur_obj_align_gfx_with_floor)
   - [cur_obj_angle_to_home](#cur_obj_angle_to_home)
   - [cur_obj_apply_drag_xz](#cur_obj_apply_drag_xz)
   - [cur_obj_become_intangible](#cur_obj_become_intangible)
   - [cur_obj_become_tangible](#cur_obj_become_tangible)
   - [cur_obj_can_mario_activate_textbox](#cur_obj_can_mario_activate_textbox)
   - [cur_obj_can_mario_activate_textbox_2](#cur_obj_can_mario_activate_textbox_2)
   - [cur_obj_change_action](#cur_obj_change_action)
   - [cur_obj_check_anim_frame](#cur_obj_check_anim_frame)
   - [cur_obj_check_anim_frame_in_range](#cur_obj_check_anim_frame_in_range)
   - [cur_obj_check_frame_prior_current_frame](#cur_obj_check_frame_prior_current_frame)
   - [cur_obj_check_grabbed_mario](#cur_obj_check_grabbed_mario)
   - [cur_obj_check_if_at_animation_end](#cur_obj_check_if_at_animation_end)
   - [cur_obj_check_if_near_animation_end](#cur_obj_check_if_near_animation_end)
   - [cur_obj_check_interacted](#cur_obj_check_interacted)
   - [cur_obj_clear_interact_status_flag](#cur_obj_clear_interact_status_flag)
   - [cur_obj_compute_vel_xz](#cur_obj_compute_vel_xz)
   - [cur_obj_count_objects_with_behavior](#cur_obj_count_objects_with_behavior)
   - [cur_obj_detect_steep_floor](#cur_obj_detect_steep_floor)
   - [cur_obj_disable](#cur_obj_disable)
   - [cur_obj_disable_rendering](#cur_obj_disable_rendering)
   - [cur_obj_disable_rendering_and_become_intangible](#cur_obj_disable_rendering_and_become_intangible)
   - [cur_obj_dist_to_nearest_object_with_behavior](#cur_obj_dist_to_nearest_object_with_behavior)
   - [cur_obj_enable_rendering](#cur_obj_enable_rendering)
   - [cur_obj_enable_rendering_2](#cur_obj_enable_rendering_2)
   - [cur_obj_enable_rendering_and_become_tangible](#cur_obj_enable_rendering_and_become_tangible)
   - [cur_obj_enable_rendering_if_mario_in_room](#cur_obj_enable_rendering_if_mario_in_room)
   - [cur_obj_end_dialog](#cur_obj_end_dialog)
   - [cur_obj_extend_animation_if_at_end](#cur_obj_extend_animation_if_at_end)
   - [cur_obj_find_nearby_held_actor](#cur_obj_find_nearby_held_actor)
   - [cur_obj_find_nearest_object_with_behavior](#cur_obj_find_nearest_object_with_behavior)
   - [cur_obj_find_nearest_pole](#cur_obj_find_nearest_pole)
   - [cur_obj_follow_path](#cur_obj_follow_path)
   - [cur_obj_forward_vel_approach_upward](#cur_obj_forward_vel_approach_upward)
   - [cur_obj_get_dropped](#cur_obj_get_dropped)
   - [cur_obj_get_thrown_or_placed](#cur_obj_get_thrown_or_placed)
   - [cur_obj_has_behavior](#cur_obj_has_behavior)
   - [cur_obj_has_model](#cur_obj_has_model)
   - [cur_obj_hide](#cur_obj_hide)
   - [cur_obj_hide_if_mario_far_away_y](#cur_obj_hide_if_mario_far_away_y)
   - [cur_obj_if_hit_wall_bounce_away](#cur_obj_if_hit_wall_bounce_away)
   - [cur_obj_init_animation](#cur_obj_init_animation)
   - [cur_obj_init_animation_and_anim_frame](#cur_obj_init_animation_and_anim_frame)
   - [cur_obj_init_animation_and_check_if_near_end](#cur_obj_init_animation_and_check_if_near_end)
   - [cur_obj_init_animation_and_extend_if_at_end](#cur_obj_init_animation_and_extend_if_at_end)
   - [cur_obj_init_animation_with_accel_and_sound](#cur_obj_init_animation_with_accel_and_sound)
   - [cur_obj_init_animation_with_sound](#cur_obj_init_animation_with_sound)
   - [cur_obj_is_any_player_on_platform](#cur_obj_is_any_player_on_platform)
   - [cur_obj_is_mario_ground_pounding_platform](#cur_obj_is_mario_ground_pounding_platform)
   - [cur_obj_is_mario_on_platform](#cur_obj_is_mario_on_platform)
   - [cur_obj_lateral_dist_from_mario_to_home](#cur_obj_lateral_dist_from_mario_to_home)
   - [cur_obj_lateral_dist_from_obj_to_home](#cur_obj_lateral_dist_from_obj_to_home)
   - [cur_obj_lateral_dist_to_home](#cur_obj_lateral_dist_to_home)
   - [cur_obj_mario_far_away](#cur_obj_mario_far_away)
   - [cur_obj_move_after_thrown_or_dropped](#cur_obj_move_after_thrown_or_dropped)
   - [cur_obj_move_standard](#cur_obj_move_standard)
   - [cur_obj_move_up_and_down](#cur_obj_move_up_and_down)
   - [cur_obj_move_update_ground_air_flags](#cur_obj_move_update_ground_air_flags)
   - [cur_obj_move_update_underwater_flags](#cur_obj_move_update_underwater_flags)
   - [cur_obj_move_using_fvel_and_gravity](#cur_obj_move_using_fvel_and_gravity)
   - [cur_obj_move_using_vel](#cur_obj_move_using_vel)
   - [cur_obj_move_using_vel_and_gravity](#cur_obj_move_using_vel_and_gravity)
   - [cur_obj_move_xz](#cur_obj_move_xz)
   - [cur_obj_move_xz_using_fvel_and_yaw](#cur_obj_move_xz_using_fvel_and_yaw)
   - [cur_obj_move_y](#cur_obj_move_y)
   - [cur_obj_move_y_and_get_water_level](#cur_obj_move_y_and_get_water_level)
   - [cur_obj_move_y_with_terminal_vel](#cur_obj_move_y_with_terminal_vel)
   - [cur_obj_nearest_object_with_behavior](#cur_obj_nearest_object_with_behavior)
   - [cur_obj_outside_home_rectangle](#cur_obj_outside_home_rectangle)
   - [cur_obj_outside_home_square](#cur_obj_outside_home_square)
   - [cur_obj_progress_direction_table](#cur_obj_progress_direction_table)
   - [cur_obj_push_mario_away](#cur_obj_push_mario_away)
   - [cur_obj_push_mario_away_from_cylinder](#cur_obj_push_mario_away_from_cylinder)
   - [cur_obj_reflect_move_angle_off_wall](#cur_obj_reflect_move_angle_off_wall)
   - [cur_obj_reset_timer_and_subaction](#cur_obj_reset_timer_and_subaction)
   - [cur_obj_resolve_wall_collisions](#cur_obj_resolve_wall_collisions)
   - [cur_obj_reverse_animation](#cur_obj_reverse_animation)
   - [cur_obj_rotate_face_angle_using_vel](#cur_obj_rotate_face_angle_using_vel)
   - [cur_obj_rotate_move_angle_using_vel](#cur_obj_rotate_move_angle_using_vel)
   - [cur_obj_rotate_yaw_toward](#cur_obj_rotate_yaw_toward)
   - [cur_obj_scale](#cur_obj_scale)
   - [cur_obj_scale_over_time](#cur_obj_scale_over_time)
   - [cur_obj_set_behavior](#cur_obj_set_behavior)
   - [cur_obj_set_direction_table](#cur_obj_set_direction_table)
   - [cur_obj_set_face_angle_to_move_angle](#cur_obj_set_face_angle_to_move_angle)
   - [cur_obj_set_hitbox_and_die_if_attacked](#cur_obj_set_hitbox_and_die_if_attacked)
   - [cur_obj_set_hitbox_radius_and_height](#cur_obj_set_hitbox_radius_and_height)
   - [cur_obj_set_hurtbox_radius_and_height](#cur_obj_set_hurtbox_radius_and_height)
   - [cur_obj_set_model](#cur_obj_set_model)
   - [cur_obj_set_pos_relative](#cur_obj_set_pos_relative)
   - [cur_obj_set_pos_relative_to_parent](#cur_obj_set_pos_relative_to_parent)
   - [cur_obj_set_pos_to_home](#cur_obj_set_pos_to_home)
   - [cur_obj_set_pos_to_home_and_stop](#cur_obj_set_pos_to_home_and_stop)
   - [cur_obj_set_pos_to_home_with_debug](#cur_obj_set_pos_to_home_with_debug)
   - [cur_obj_set_pos_via_transform](#cur_obj_set_pos_via_transform)
   - [cur_obj_set_vel_from_mario_vel](#cur_obj_set_vel_from_mario_vel)
   - [cur_obj_set_y_vel_and_animation](#cur_obj_set_y_vel_and_animation)
   - [cur_obj_shake_screen](#cur_obj_shake_screen)
   - [cur_obj_shake_y](#cur_obj_shake_y)
   - [cur_obj_shake_y_until](#cur_obj_shake_y_until)
   - [cur_obj_spawn_loot_blue_coin](#cur_obj_spawn_loot_blue_coin)
   - [cur_obj_spawn_loot_coin_at_mario_pos](#cur_obj_spawn_loot_coin_at_mario_pos)
   - [cur_obj_spawn_particles](#cur_obj_spawn_particles)
   - [cur_obj_spawn_star_at_y_offset](#cur_obj_spawn_star_at_y_offset)
   - [cur_obj_start_cam_event](#cur_obj_start_cam_event)
   - [cur_obj_unhide](#cur_obj_unhide)
   - [cur_obj_unrender_and_reset_state](#cur_obj_unrender_and_reset_state)
   - [cur_obj_unused_init_on_floor](#cur_obj_unused_init_on_floor)
   - [cur_obj_unused_play_footstep_sound](#cur_obj_unused_play_footstep_sound)
   - [cur_obj_unused_resolve_wall_collisions](#cur_obj_unused_resolve_wall_collisions)
   - [cur_obj_update_floor](#cur_obj_update_floor)
   - [cur_obj_update_floor_and_resolve_wall_collisions](#cur_obj_update_floor_and_resolve_wall_collisions)
   - [cur_obj_update_floor_and_walls](#cur_obj_update_floor_and_walls)
   - [cur_obj_update_floor_height](#cur_obj_update_floor_height)
   - [cur_obj_update_floor_height_and_get_floor](#cur_obj_update_floor_height_and_get_floor)
   - [cur_obj_wait_then_blink](#cur_obj_wait_then_blink)
   - [cur_obj_was_attacked_or_ground_pounded](#cur_obj_was_attacked_or_ground_pounded)
   - [cur_obj_within_12k_bounds](#cur_obj_within_12k_bounds)
   - [disable_time_stop](#disable_time_stop)
   - [disable_time_stop_including_mario](#disable_time_stop_including_mario)
   - [dist_between_object_and_point](#dist_between_object_and_point)
   - [dist_between_objects](#dist_between_objects)
   - [enable_time_stop](#enable_time_stop)
   - [enable_time_stop_including_mario](#enable_time_stop_including_mario)
   - [find_unimportant_object](#find_unimportant_object)
   - [geo_offset_klepto_debug](#geo_offset_klepto_debug)
   - [get_object_list_from_behavior](#get_object_list_from_behavior)
   - [increment_velocity_toward_range](#increment_velocity_toward_range)
   - [is_item_in_array](#is_item_in_array)
   - [is_mario_moving_fast_or_in_air](#is_mario_moving_fast_or_in_air)
   - [lateral_dist_between_objects](#lateral_dist_between_objects)
   - [mario_is_dive_sliding](#mario_is_dive_sliding)
   - [mario_is_in_air_action](#mario_is_in_air_action)
   - [mario_is_within_rectangle](#mario_is_within_rectangle)
   - [mario_set_flag](#mario_set_flag)
   - [obj_angle_to_object](#obj_angle_to_object)
   - [obj_angle_to_point](#obj_angle_to_point)
   - [obj_apply_scale_to_transform](#obj_apply_scale_to_transform)
   - [obj_attack_collided_from_other_object](#obj_attack_collided_from_other_object)
   - [obj_become_tangible](#obj_become_tangible)
   - [obj_build_relative_transform](#obj_build_relative_transform)
   - [obj_build_transform_from_pos_and_angle](#obj_build_transform_from_pos_and_angle)
   - [obj_build_transform_relative_to_parent](#obj_build_transform_relative_to_parent)
   - [obj_build_vel_from_transform](#obj_build_vel_from_transform)
   - [obj_check_if_collided_with_object](#obj_check_if_collided_with_object)
   - [obj_copy_angle](#obj_copy_angle)
   - [obj_copy_behavior_params](#obj_copy_behavior_params)
   - [obj_copy_graph_y_offset](#obj_copy_graph_y_offset)
   - [obj_copy_pos](#obj_copy_pos)
   - [obj_copy_pos_and_angle](#obj_copy_pos_and_angle)
   - [obj_copy_scale](#obj_copy_scale)
   - [obj_create_transform_from_self](#obj_create_transform_from_self)
   - [obj_explode_and_spawn_coins](#obj_explode_and_spawn_coins)
   - [obj_has_behavior](#obj_has_behavior)
   - [obj_init_animation](#obj_init_animation)
   - [obj_is_hidden](#obj_is_hidden)
   - [obj_mark_for_deletion](#obj_mark_for_deletion)
   - [obj_pitch_to_object](#obj_pitch_to_object)
   - [obj_scale](#obj_scale)
   - [obj_scale_random](#obj_scale_random)
   - [obj_scale_xyz](#obj_scale_xyz)
   - [obj_set_angle](#obj_set_angle)
   - [obj_set_behavior](#obj_set_behavior)
   - [obj_set_billboard](#obj_set_billboard)
   - [obj_set_cylboard](#obj_set_cylboard)
   - [obj_set_face_angle_to_move_angle](#obj_set_face_angle_to_move_angle)
   - [obj_set_gfx_pos_at_obj_pos](#obj_set_gfx_pos_at_obj_pos)
   - [obj_set_gfx_pos_from_pos](#obj_set_gfx_pos_from_pos)
   - [obj_set_held_state](#obj_set_held_state)
   - [obj_set_hitbox](#obj_set_hitbox)
   - [obj_set_parent_relative_pos](#obj_set_parent_relative_pos)
   - [obj_set_pos](#obj_set_pos)
   - [obj_set_pos_relative](#obj_set_pos_relative)
   - [obj_set_throw_matrix_from_transform](#obj_set_throw_matrix_from_transform)
   - [obj_spawn_loot_blue_coins](#obj_spawn_loot_blue_coins)
   - [obj_spawn_loot_coins](#obj_spawn_loot_coins)
   - [obj_spawn_loot_yellow_coins](#obj_spawn_loot_yellow_coins)
   - [obj_translate_local](#obj_translate_local)
   - [obj_translate_xyz_random](#obj_translate_xyz_random)
   - [obj_translate_xz_random](#obj_translate_xz_random)
   - [obj_turn_toward_object](#obj_turn_toward_object)
   - [player_performed_grab_escape_action](#player_performed_grab_escape_action)
   - [random_f32_around_zero](#random_f32_around_zero)
   - [set_mario_interact_hoot_if_in_range](#set_mario_interact_hoot_if_in_range)
   - [set_time_stop_flags](#set_time_stop_flags)
   - [signum_positive](#signum_positive)
   - [spawn_base_star_with_no_lvl_exit](#spawn_base_star_with_no_lvl_exit)
   - [spawn_mist_particles](#spawn_mist_particles)
   - [spawn_mist_particles_with_sound](#spawn_mist_particles_with_sound)
   - [spawn_star_with_no_lvl_exit](#spawn_star_with_no_lvl_exit)
   - [spawn_water_droplet](#spawn_water_droplet)
   - [stub_obj_helpers_3](#stub_obj_helpers_3)
   - [stub_obj_helpers_4](#stub_obj_helpers_4)

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

- smlua_obj_utils.h
   - [obj_get_first](#obj_get_first)
   - [obj_get_first_with_behavior_id](#obj_get_first_with_behavior_id)
   - [obj_get_first_with_behavior_id_and_field_f32](#obj_get_first_with_behavior_id_and_field_f32)
   - [obj_get_first_with_behavior_id_and_field_s32](#obj_get_first_with_behavior_id_and_field_s32)
   - [obj_get_next](#obj_get_next)
   - [obj_get_next_with_same_behavior_id](#obj_get_next_with_same_behavior_id)
   - [obj_get_next_with_same_behavior_id_and_field_f32](#obj_get_next_with_same_behavior_id_and_field_f32)
   - [obj_get_next_with_same_behavior_id_and_field_s32](#obj_get_next_with_same_behavior_id_and_field_s32)
   - [obj_set_model_extended](#obj_set_model_extended)
   - [spawn_sync_object](#spawn_sync_object)

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

- spawn_sound.c
   - [calc_dist_to_volume_range_1](#calc_dist_to_volume_range_1)
   - [calc_dist_to_volume_range_2](#calc_dist_to_volume_range_2)
   - [cur_obj_play_sound_1](#cur_obj_play_sound_1)
   - [cur_obj_play_sound_2](#cur_obj_play_sound_2)
   - [exec_anim_sound_state](#exec_anim_sound_state)

<br />

- surface_collision.h
   - [find_ceil_height](#find_ceil_height)
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
# manually written functions

<br />

## [define_custom_obj_fields](#define_custom_obj_fields)

Defines a custom set of overlapping object fields.

The `fieldTable` table's keys must start with the letter `o` and the values must be either `u32`, `s32`, or `f32`.

### Lua Example
`define_custom_obj_fields({ oCustomField1 = 'u32', oCustomField2 = 's32', oCustomField3 = 'f32' })`

### Parameters
| Field | Type |
| ----- | ---- |
| fieldTable | `Lua Table` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

## [network_init_object](#network_init_object)

Enables synchronization on an object.

- Setting `standardSync` to `true` will automatically synchronize the object at a rate that is determined based on player distance. The commonly used object fields will be automatically synchronized.
- Setting `standardSync` to `false` will not automatically synchronize the object, or add commonly used object fields. The mod must manually call `network_send_object()` when fields have changed.

The `fieldTable` parameter can be `nil`, or a list of object fields.

### Lua Example
`network_init_object(obj, true, { 'oCustomField1', 'oCustomField2', 'oCustomField3' })`

### Parameters
| Field | Type |
| ----- | ---- |
| object | [Object](structs.md#Object) |
| standardSync | `bool` |
| fieldTable | `Lua Table` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />

## [network_send_object](#network_send_object)

Sends a packet that synchronizes an object. This does not need to be called when `standardSync` is enabled.

The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.

### Lua Example
`network_send_object(obj, false)`

### Parameters
| Field | Type |
| ----- | ---- |
| object | [Object](structs.md#Object) |
| reliable | `bool` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />


---
# functions from behavior_table.h

<br />


## [get_behavior_from_id](#get_behavior_from_id)

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

## [get_id_from_behavior](#get_id_from_behavior)

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

---
# functions from camera.h

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
| x | `float` |
| y | `float` |
| scale | `float` |

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

## [djui_hud_render_texture](#djui_hud_render_texture)

### Lua Example
`djui_hud_render_texture(texInfo, x, y, scaleW, scaleH)`

### Parameters
| Field | Type |
| ----- | ---- |
| texInfo | [TextureInfo](structs.md#TextureInfo) |
| x | `number` |
| y | `number` |
| scaleW | `number` |
| scaleH | `number` |

### Returns
- None

### C Prototype
`void djui_hud_render_texture(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH);`

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
| lines | `int` |

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
| player | `integer` |
| targetScale | `integer` |
| fadeTimer | `integer` |

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
| arg0 | `integer` |
| fadeOut | `integer` |

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

## [sequence_player_fade_out](#sequence_player_fade_out)

### Lua Example
`sequence_player_fade_out(player, fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| fadeTimer | `integer` |

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
| player | `integer` |
| fadeTimer | `integer` |

### Returns
- None

### C Prototype
`void sequence_player_unlower(u8 player, u16 fadeTimer);`

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

## [network_is_server](#network_is_server)

### Lua Example
`local boolValue = network_is_server()`

### Parameters
- None

### Returns
- `bool`

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
`s32 is_point_close_to_object(struct Object *obj, f32 x, f32 y, f32 z, s32 dist);`

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
`s32 is_point_within_radius_of_mario(f32 x, f32 y, f32 z, s32 dist);`

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
`s32 obj_check_if_facing_toward_angle(u32 base, u32 goal, s16 range);`

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
`s32 obj_find_wall(f32 objNewX, f32 objY, f32 objNewZ, f32 objVelX, f32 objVelZ);`

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
`s32 obj_find_wall_displacement(Vec3f dist, f32 x, f32 y, f32 z, f32 radius);`

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
`s32 obj_flicker_and_disappear(struct Object *obj, s16 lifeSpan);`

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
`s32 obj_lava_death(void);`

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
`s32 obj_return_home_if_safe(struct Object *obj, f32 homeX, f32 y, f32 homeZ, s32 dist);`

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
`s32 turn_obj_away_from_steep_floor(struct Surface *objFloor, f32 floorY, f32 objVelX, f32 objVelZ);`

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

## [cur_obj_set_model](#cur_obj_set_model)

### Lua Example
`cur_obj_set_model(modelID)`

### Parameters
| Field | Type |
| ----- | ---- |
| modelID | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_set_model(s32 modelID);`

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

---
# functions from smlua_obj_utils.h

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
# functions from thread6.c

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
