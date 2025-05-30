## [:rewind: Lua Reference](lua.md)

---

1 | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | [next >](functions-2.md)]

---

# Supported Functions

- manually written functions
   - [define_custom_obj_fields](#define_custom_obj_fields)
   - [network_init_object](#network_init_object)
   - [network_send_object](#network_send_object)
   - [network_send_to](#network_send_to)
   - [network_send](#network_send)
   - [get_texture_info](#get_texture_info)
   - [djui_hud_render_texture](#djui_hud_render_texture)
   - [djui_hud_render_texture_tile](#djui_hud_render_texture_tile)
   - [djui_hud_render_texture_interpolated](#djui_hud_render_texture_interpolated)
   - [djui_hud_render_texture_tile_interpolated](#djui_hud_render_texture_tile_interpolated)
   - [texture_override_set](#texture_override_set)
   - [texture_override_reset](#texture_override_reset)
   - [smlua_anim_util_register_animation](#smlua_anim_util_register_animation)
   - [level_script_parse](#level_script_parse)
   - [log_to_console](#log_to_console)
   - [add_scroll_target](#add_scroll_target)
   - [collision_find_surface_on_ray](#collision_find_surface_on_ray)
   - [cast_graph_node](#cast_graph_node)
   - [get_uncolored_string](#get_uncolored_string)
   - [gfx_set_command](#gfx_set_command)

<br />

- area.h
   - [get_mario_spawn_type](functions.md#get_mario_spawn_type)
   - [area_get_warp_node](functions.md#area_get_warp_node)
   - [area_get_any_warp_node](functions.md#area_get_any_warp_node)
   - [area_get_warp_node_from_params](functions.md#area_get_warp_node_from_params)
   - [play_transition](functions.md#play_transition)
   - [play_transition_after_delay](functions.md#play_transition_after_delay)

<br />

- behavior_actions.h
   - [spawn_mist_particles_variable](functions-2.md#spawn_mist_particles_variable)
   - [bhv_spawn_star_no_level_exit](functions-2.md#bhv_spawn_star_no_level_exit)
   - [spawn_triangle_break_particles](functions-2.md#spawn_triangle_break_particles)
   - [spawn_mist_from_global](functions-2.md#spawn_mist_from_global)
   - [clear_particle_flags](functions-2.md#clear_particle_flags)
   - [spawn_wind_particles](functions-2.md#spawn_wind_particles)
   - [check_if_moving_over_floor](functions-2.md#check_if_moving_over_floor)
   - [arc_to_goal_pos](functions-2.md#arc_to_goal_pos)
   - [vec3f_copy_2](functions-2.md#vec3f_copy_2)
   - [tox_box_move](functions-2.md#tox_box_move)
   - [play_penguin_walking_sound](functions-2.md#play_penguin_walking_sound)
   - [update_angle_from_move_flags](functions-2.md#update_angle_from_move_flags)
   - [cur_obj_spawn_strong_wind_particles](functions-2.md#cur_obj_spawn_strong_wind_particles)
   - [bhv_star_door_loop_2](functions-2.md#bhv_star_door_loop_2)
   - [bhv_cap_switch_loop](functions-2.md#bhv_cap_switch_loop)
   - [bhv_tiny_star_particles_init](functions-2.md#bhv_tiny_star_particles_init)
   - [bhv_grindel_thwomp_loop](functions-2.md#bhv_grindel_thwomp_loop)
   - [bhv_koopa_shell_underwater_loop](functions-2.md#bhv_koopa_shell_underwater_loop)
   - [bhv_door_init](functions-2.md#bhv_door_init)
   - [bhv_door_loop](functions-2.md#bhv_door_loop)
   - [bhv_star_door_loop](functions-2.md#bhv_star_door_loop)
   - [bhv_mr_i_loop](functions-2.md#bhv_mr_i_loop)
   - [bhv_mr_i_body_loop](functions-2.md#bhv_mr_i_body_loop)
   - [bhv_mr_i_particle_loop](functions-2.md#bhv_mr_i_particle_loop)
   - [bhv_piranha_particle_loop](functions-2.md#bhv_piranha_particle_loop)
   - [bhv_giant_pole_loop](functions-2.md#bhv_giant_pole_loop)
   - [bhv_pole_init](functions-2.md#bhv_pole_init)
   - [bhv_pole_base_loop](functions-2.md#bhv_pole_base_loop)
   - [bhv_thi_huge_island_top_loop](functions-2.md#bhv_thi_huge_island_top_loop)
   - [bhv_thi_tiny_island_top_loop](functions-2.md#bhv_thi_tiny_island_top_loop)
   - [bhv_king_bobomb_loop](functions-2.md#bhv_king_bobomb_loop)
   - [bhv_bobomb_anchor_mario_loop](functions-2.md#bhv_bobomb_anchor_mario_loop)
   - [bhv_beta_chest_bottom_init](functions-2.md#bhv_beta_chest_bottom_init)
   - [bhv_beta_chest_bottom_loop](functions-2.md#bhv_beta_chest_bottom_loop)
   - [bhv_beta_chest_lid_loop](functions-2.md#bhv_beta_chest_lid_loop)
   - [bhv_bubble_wave_init](functions-2.md#bhv_bubble_wave_init)
   - [bhv_bubble_maybe_loop](functions-2.md#bhv_bubble_maybe_loop)
   - [bhv_bubble_player_loop](functions-2.md#bhv_bubble_player_loop)
   - [bhv_water_air_bubble_init](functions-2.md#bhv_water_air_bubble_init)
   - [bhv_water_air_bubble_loop](functions-2.md#bhv_water_air_bubble_loop)
   - [bhv_particle_init](functions-2.md#bhv_particle_init)
   - [bhv_particle_loop](functions-2.md#bhv_particle_loop)
   - [bhv_water_waves_init](functions-2.md#bhv_water_waves_init)
   - [bhv_small_bubbles_loop](functions-2.md#bhv_small_bubbles_loop)
   - [bhv_fish_group_loop](functions-2.md#bhv_fish_group_loop)
   - [bhv_cannon_base_loop](functions-2.md#bhv_cannon_base_loop)
   - [bhv_cannon_barrel_loop](functions-2.md#bhv_cannon_barrel_loop)
   - [bhv_cannon_base_unused_loop](functions-2.md#bhv_cannon_base_unused_loop)
   - [common_anchor_mario_behavior](functions-2.md#common_anchor_mario_behavior)
   - [bhv_chuckya_loop](functions-2.md#bhv_chuckya_loop)
   - [bhv_chuckya_anchor_mario_loop](functions-2.md#bhv_chuckya_anchor_mario_loop)
   - [bhv_rotating_platform_loop](functions-2.md#bhv_rotating_platform_loop)
   - [bhv_wf_breakable_wall_loop](functions-2.md#bhv_wf_breakable_wall_loop)
   - [bhv_kickable_board_loop](functions-2.md#bhv_kickable_board_loop)
   - [bhv_tower_door_loop](functions-2.md#bhv_tower_door_loop)
   - [bhv_wf_rotating_wooden_platform_init](functions-2.md#bhv_wf_rotating_wooden_platform_init)
   - [bhv_wf_rotating_wooden_platform_loop](functions-2.md#bhv_wf_rotating_wooden_platform_loop)
   - [bhv_fading_warp_loop](functions-2.md#bhv_fading_warp_loop)
   - [bhv_warp_loop](functions-2.md#bhv_warp_loop)
   - [bhv_white_puff_exploding_loop](functions-2.md#bhv_white_puff_exploding_loop)
   - [bhv_spawned_star_init](functions-2.md#bhv_spawned_star_init)
   - [bhv_spawned_star_loop](functions-2.md#bhv_spawned_star_loop)
   - [bhv_coin_init](functions-2.md#bhv_coin_init)
   - [bhv_coin_loop](functions-2.md#bhv_coin_loop)
   - [bhv_coin_inside_boo_loop](functions-2.md#bhv_coin_inside_boo_loop)
   - [bhv_coin_formation_init](functions-2.md#bhv_coin_formation_init)
   - [bhv_coin_formation_spawn_loop](functions-2.md#bhv_coin_formation_spawn_loop)
   - [bhv_coin_formation_loop](functions-2.md#bhv_coin_formation_loop)
   - [bhv_temp_coin_loop](functions-2.md#bhv_temp_coin_loop)
   - [bhv_coin_sparkles_loop](functions-2.md#bhv_coin_sparkles_loop)
   - [bhv_golden_coin_sparkles_loop](functions-2.md#bhv_golden_coin_sparkles_loop)
   - [bhv_wall_tiny_star_particle_loop](functions-2.md#bhv_wall_tiny_star_particle_loop)
   - [bhv_pound_tiny_star_particle_loop](functions-2.md#bhv_pound_tiny_star_particle_loop)
   - [bhv_pound_tiny_star_particle_init](functions-2.md#bhv_pound_tiny_star_particle_init)
   - [bhv_punch_tiny_triangle_loop](functions-2.md#bhv_punch_tiny_triangle_loop)
   - [bhv_punch_tiny_triangle_init](functions-2.md#bhv_punch_tiny_triangle_init)
   - [bhv_tumbling_bridge_platform_loop](functions-2.md#bhv_tumbling_bridge_platform_loop)
   - [bhv_tumbling_bridge_loop](functions-2.md#bhv_tumbling_bridge_loop)
   - [bhv_elevator_init](functions-2.md#bhv_elevator_init)
   - [bhv_elevator_loop](functions-2.md#bhv_elevator_loop)
   - [bhv_water_mist_loop](functions-2.md#bhv_water_mist_loop)
   - [bhv_water_mist_spawn_loop](functions-2.md#bhv_water_mist_spawn_loop)
   - [bhv_water_mist_2_loop](functions-2.md#bhv_water_mist_2_loop)
   - [bhv_pound_white_puffs_init](functions-2.md#bhv_pound_white_puffs_init)
   - [bhv_ground_sand_init](functions-2.md#bhv_ground_sand_init)
   - [bhv_ground_snow_init](functions-2.md#bhv_ground_snow_init)
   - [bhv_wind_loop](functions-2.md#bhv_wind_loop)
   - [bhv_unused_particle_spawn_loop](functions-2.md#bhv_unused_particle_spawn_loop)
   - [bhv_ukiki_cage_star_loop](functions-2.md#bhv_ukiki_cage_star_loop)
   - [bhv_ukiki_cage_loop](functions-2.md#bhv_ukiki_cage_loop)
   - [bhv_bitfs_sinking_platform_loop](functions-2.md#bhv_bitfs_sinking_platform_loop)
   - [bhv_bitfs_sinking_cage_platform_loop](functions-2.md#bhv_bitfs_sinking_cage_platform_loop)
   - [bhv_ddd_moving_pole_loop](functions-2.md#bhv_ddd_moving_pole_loop)
   - [bhv_platform_normals_init](functions-2.md#bhv_platform_normals_init)
   - [bhv_tilting_inverted_pyramid_loop](functions-2.md#bhv_tilting_inverted_pyramid_loop)
   - [bhv_squishable_platform_loop](functions-2.md#bhv_squishable_platform_loop)
   - [bhv_beta_moving_flames_spawn_loop](functions-2.md#bhv_beta_moving_flames_spawn_loop)
   - [bhv_beta_moving_flames_loop](functions-2.md#bhv_beta_moving_flames_loop)
   - [bhv_rr_rotating_bridge_platform_loop](functions-2.md#bhv_rr_rotating_bridge_platform_loop)
   - [bhv_flamethrower_loop](functions-2.md#bhv_flamethrower_loop)
   - [bhv_flamethrower_flame_loop](functions-2.md#bhv_flamethrower_flame_loop)
   - [bhv_bouncing_fireball_loop](functions-2.md#bhv_bouncing_fireball_loop)
   - [bhv_bouncing_fireball_flame_loop](functions-2.md#bhv_bouncing_fireball_flame_loop)
   - [bhv_bowser_shock_wave_loop](functions-2.md#bhv_bowser_shock_wave_loop)
   - [bhv_flame_mario_loop](functions-2.md#bhv_flame_mario_loop)
   - [bhv_black_smoke_mario_loop](functions-2.md#bhv_black_smoke_mario_loop)
   - [bhv_black_smoke_bowser_loop](functions-2.md#bhv_black_smoke_bowser_loop)
   - [bhv_black_smoke_upward_loop](functions-2.md#bhv_black_smoke_upward_loop)
   - [bhv_beta_fish_splash_spawner_loop](functions-2.md#bhv_beta_fish_splash_spawner_loop)
   - [bhv_spindrift_loop](functions-2.md#bhv_spindrift_loop)
   - [bhv_tower_platform_group_init](functions-2.md#bhv_tower_platform_group_init)
   - [bhv_tower_platform_group_loop](functions-2.md#bhv_tower_platform_group_loop)
   - [bhv_wf_sliding_tower_platform_loop](functions-2.md#bhv_wf_sliding_tower_platform_loop)
   - [bhv_wf_elevator_tower_platform_loop](functions-2.md#bhv_wf_elevator_tower_platform_loop)
   - [bhv_wf_solid_tower_platform_loop](functions-2.md#bhv_wf_solid_tower_platform_loop)
   - [bhv_snow_leaf_particle_spawn_init](functions-2.md#bhv_snow_leaf_particle_spawn_init)
   - [bhv_tree_snow_or_leaf_loop](functions-2.md#bhv_tree_snow_or_leaf_loop)
   - [bhv_piranha_plant_bubble_loop](functions-2.md#bhv_piranha_plant_bubble_loop)
   - [bhv_piranha_plant_waking_bubbles_loop](functions-2.md#bhv_piranha_plant_waking_bubbles_loop)
   - [bhv_purple_switch_loop](functions-2.md#bhv_purple_switch_loop)
   - [bhv_hidden_object_loop](functions-2.md#bhv_hidden_object_loop)
   - [bhv_breakable_box_loop](functions-2.md#bhv_breakable_box_loop)
   - [bhv_pushable_loop](functions-2.md#bhv_pushable_loop)
   - [bhv_small_water_wave_loop](functions-2.md#bhv_small_water_wave_loop)
   - [bhv_yellow_coin_init](functions-2.md#bhv_yellow_coin_init)
   - [bhv_yellow_coin_loop](functions-2.md#bhv_yellow_coin_loop)
   - [bhv_squarish_path_moving_loop](functions-2.md#bhv_squarish_path_moving_loop)
   - [bhv_squarish_path_parent_init](functions-2.md#bhv_squarish_path_parent_init)
   - [bhv_squarish_path_parent_loop](functions-2.md#bhv_squarish_path_parent_loop)
   - [bhv_heave_ho_loop](functions-2.md#bhv_heave_ho_loop)
   - [bhv_heave_ho_throw_mario_loop](functions-2.md#bhv_heave_ho_throw_mario_loop)
   - [bhv_ccm_touched_star_spawn_loop](functions-2.md#bhv_ccm_touched_star_spawn_loop)
   - [bhv_unused_poundable_platform](functions-2.md#bhv_unused_poundable_platform)
   - [bhv_beta_trampoline_top_loop](functions-2.md#bhv_beta_trampoline_top_loop)
   - [bhv_beta_trampoline_spring_loop](functions-2.md#bhv_beta_trampoline_spring_loop)
   - [bhv_jumping_box_loop](functions-2.md#bhv_jumping_box_loop)
   - [bhv_boo_cage_init](functions-2.md#bhv_boo_cage_init)
   - [bhv_boo_cage_loop](functions-2.md#bhv_boo_cage_loop)
   - [bhv_bowser_key_init](functions-2.md#bhv_bowser_key_init)
   - [bhv_bowser_key_loop](functions-2.md#bhv_bowser_key_loop)
   - [bhv_grand_star_init](functions-2.md#bhv_grand_star_init)
   - [bhv_grand_star_loop](functions-2.md#bhv_grand_star_loop)
   - [bhv_beta_boo_key_loop](functions-2.md#bhv_beta_boo_key_loop)
   - [bhv_alpha_boo_key_loop](functions-2.md#bhv_alpha_boo_key_loop)
   - [bhv_bullet_bill_init](functions-2.md#bhv_bullet_bill_init)
   - [bhv_bullet_bill_loop](functions-2.md#bhv_bullet_bill_loop)
   - [bhv_white_puff_smoke_init](functions-2.md#bhv_white_puff_smoke_init)
   - [bhv_bowser_tail_anchor_init](functions-2.md#bhv_bowser_tail_anchor_init)
   - [bhv_bowser_tail_anchor_loop](functions-2.md#bhv_bowser_tail_anchor_loop)
   - [bhv_bowser_init](functions-2.md#bhv_bowser_init)
   - [bhv_bowser_loop](functions-2.md#bhv_bowser_loop)
   - [bhv_bowser_body_anchor_init](functions-2.md#bhv_bowser_body_anchor_init)
   - [bhv_bowser_body_anchor_loop](functions-2.md#bhv_bowser_body_anchor_loop)
   - [bhv_bowser_flame_spawn_loop](functions-2.md#bhv_bowser_flame_spawn_loop)
   - [bhv_tilting_bowser_lava_platform_init](functions-2.md#bhv_tilting_bowser_lava_platform_init)
   - [bhv_falling_bowser_platform_loop](functions-2.md#bhv_falling_bowser_platform_loop)
   - [bhv_blue_bowser_flame_init](functions-2.md#bhv_blue_bowser_flame_init)
   - [bhv_blue_bowser_flame_loop](functions-2.md#bhv_blue_bowser_flame_loop)
   - [bhv_flame_floating_landing_init](functions-2.md#bhv_flame_floating_landing_init)
   - [bhv_flame_floating_landing_loop](functions-2.md#bhv_flame_floating_landing_loop)
   - [bhv_blue_flames_group_loop](functions-2.md#bhv_blue_flames_group_loop)
   - [bhv_flame_bouncing_init](functions-2.md#bhv_flame_bouncing_init)
   - [bhv_flame_bouncing_loop](functions-2.md#bhv_flame_bouncing_loop)
   - [bhv_flame_moving_forward_growing_init](functions-2.md#bhv_flame_moving_forward_growing_init)
   - [bhv_flame_moving_forward_growing_loop](functions-2.md#bhv_flame_moving_forward_growing_loop)
   - [bhv_flame_bowser_init](functions-2.md#bhv_flame_bowser_init)
   - [bhv_flame_bowser_loop](functions-2.md#bhv_flame_bowser_loop)
   - [bhv_flame_large_burning_out_init](functions-2.md#bhv_flame_large_burning_out_init)
   - [bhv_blue_fish_movement_loop](functions-2.md#bhv_blue_fish_movement_loop)
   - [bhv_tank_fish_group_loop](functions-2.md#bhv_tank_fish_group_loop)
   - [bhv_checkerboard_elevator_group_init](functions-2.md#bhv_checkerboard_elevator_group_init)
   - [bhv_checkerboard_elevator_group_loop](functions-2.md#bhv_checkerboard_elevator_group_loop)
   - [bhv_checkerboard_platform_init](functions-2.md#bhv_checkerboard_platform_init)
   - [bhv_checkerboard_platform_loop](functions-2.md#bhv_checkerboard_platform_loop)
   - [bhv_bowser_key_unlock_door_loop](functions-2.md#bhv_bowser_key_unlock_door_loop)
   - [bhv_bowser_key_course_exit_loop](functions-2.md#bhv_bowser_key_course_exit_loop)
   - [bhv_invisible_objects_under_bridge_init](functions-2.md#bhv_invisible_objects_under_bridge_init)
   - [bhv_invisible_objects_under_bridge_loop](functions-2.md#bhv_invisible_objects_under_bridge_loop)
   - [bhv_water_level_pillar_init](functions-2.md#bhv_water_level_pillar_init)
   - [bhv_water_level_pillar_loop](functions-2.md#bhv_water_level_pillar_loop)
   - [bhv_ddd_warp_loop](functions-2.md#bhv_ddd_warp_loop)
   - [bhv_moat_grills_loop](functions-2.md#bhv_moat_grills_loop)
   - [bhv_rotating_clock_arm_loop](functions-2.md#bhv_rotating_clock_arm_loop)
   - [bhv_ukiki_init](functions-2.md#bhv_ukiki_init)
   - [bhv_ukiki_loop](functions-2.md#bhv_ukiki_loop)
   - [bhv_lll_sinking_rock_block_loop](functions-2.md#bhv_lll_sinking_rock_block_loop)
   - [bhv_lll_moving_octagonal_mesh_platform_loop](functions-2.md#bhv_lll_moving_octagonal_mesh_platform_loop)
   - [bhv_lll_rotating_block_fire_bars_loop](functions-2.md#bhv_lll_rotating_block_fire_bars_loop)
   - [bhv_lll_rotating_hex_flame_loop](functions-2.md#bhv_lll_rotating_hex_flame_loop)
   - [bhv_lll_wood_piece_loop](functions-2.md#bhv_lll_wood_piece_loop)
   - [bhv_lll_floating_wood_bridge_loop](functions-2.md#bhv_lll_floating_wood_bridge_loop)
   - [bhv_volcano_flames_loop](functions-2.md#bhv_volcano_flames_loop)
   - [bhv_lll_rotating_hexagonal_ring_loop](functions-2.md#bhv_lll_rotating_hexagonal_ring_loop)
   - [bhv_lll_sinking_rectangular_platform_loop](functions-2.md#bhv_lll_sinking_rectangular_platform_loop)
   - [bhv_lll_sinking_square_platforms_loop](functions-2.md#bhv_lll_sinking_square_platforms_loop)
   - [bhv_koopa_shell_loop](functions-2.md#bhv_koopa_shell_loop)
   - [bhv_koopa_shell_flame_loop](functions-2.md#bhv_koopa_shell_flame_loop)
   - [bhv_tox_box_loop](functions-2.md#bhv_tox_box_loop)
   - [mario_moving_fast_enough_to_make_piranha_plant_bite](functions-2.md#mario_moving_fast_enough_to_make_piranha_plant_bite)
   - [bhv_piranha_plant_loop](functions-2.md#bhv_piranha_plant_loop)
   - [bhv_lll_bowser_puzzle_piece_loop](functions-2.md#bhv_lll_bowser_puzzle_piece_loop)
   - [bhv_lll_bowser_puzzle_loop](functions-2.md#bhv_lll_bowser_puzzle_loop)
   - [bhv_tuxies_mother_loop](functions-2.md#bhv_tuxies_mother_loop)
   - [bhv_small_penguin_loop](functions-2.md#bhv_small_penguin_loop)
   - [bhv_fish_spawner_loop](functions-2.md#bhv_fish_spawner_loop)
   - [bhv_fish_loop](functions-2.md#bhv_fish_loop)
   - [bhv_wdw_express_elevator_loop](functions-2.md#bhv_wdw_express_elevator_loop)
   - [bhv_bub_spawner_loop](functions-2.md#bhv_bub_spawner_loop)
   - [bhv_bub_loop](functions-2.md#bhv_bub_loop)
   - [bhv_exclamation_box_init](functions-2.md#bhv_exclamation_box_init)
   - [bhv_exclamation_box_loop](functions-2.md#bhv_exclamation_box_loop)
   - [bhv_rotating_exclamation_box_loop](functions-2.md#bhv_rotating_exclamation_box_loop)
   - [bhv_sound_spawner_init](functions-2.md#bhv_sound_spawner_init)
   - [bhv_bowsers_sub_loop](functions-2.md#bhv_bowsers_sub_loop)
   - [bhv_sushi_shark_loop](functions-2.md#bhv_sushi_shark_loop)
   - [bhv_sushi_shark_collision_loop](functions-2.md#bhv_sushi_shark_collision_loop)
   - [bhv_jrb_sliding_box_loop](functions-2.md#bhv_jrb_sliding_box_loop)
   - [bhv_ship_part_3_loop](functions-2.md#bhv_ship_part_3_loop)
   - [bhv_sunken_ship_part_loop](functions-2.md#bhv_sunken_ship_part_loop)
   - [bhv_white_puff_1_loop](functions-2.md#bhv_white_puff_1_loop)
   - [bhv_white_puff_2_loop](functions-2.md#bhv_white_puff_2_loop)
   - [bhv_blue_coin_number_loop](functions-2.md#bhv_blue_coin_number_loop)
   - [bhv_blue_coin_switch_init](functions-2.md#bhv_blue_coin_switch_init)
   - [bhv_blue_coin_switch_loop](functions-2.md#bhv_blue_coin_switch_loop)
   - [bhv_hidden_blue_coin_loop](functions-2.md#bhv_hidden_blue_coin_loop)
   - [bhv_openable_cage_door_loop](functions-2.md#bhv_openable_cage_door_loop)
   - [bhv_openable_grill_loop](functions-2.md#bhv_openable_grill_loop)
   - [bhv_water_level_diamond_loop](functions-2.md#bhv_water_level_diamond_loop)
   - [bhv_init_changing_water_level_loop](functions-2.md#bhv_init_changing_water_level_loop)
   - [bhv_tweester_sand_particle_loop](functions-2.md#bhv_tweester_sand_particle_loop)
   - [bhv_tweester_loop](functions-2.md#bhv_tweester_loop)
   - [bhv_merry_go_round_boo_manager_loop](functions-2.md#bhv_merry_go_round_boo_manager_loop)
   - [bhv_animated_texture_loop](functions-2.md#bhv_animated_texture_loop)
   - [bhv_boo_in_castle_loop](functions-2.md#bhv_boo_in_castle_loop)
   - [bhv_boo_with_cage_init](functions-2.md#bhv_boo_with_cage_init)
   - [bhv_boo_with_cage_loop](functions-2.md#bhv_boo_with_cage_loop)
   - [bhv_boo_init](functions-2.md#bhv_boo_init)
   - [bhv_big_boo_loop](functions-2.md#bhv_big_boo_loop)
   - [bhv_courtyard_boo_triplet_init](functions-2.md#bhv_courtyard_boo_triplet_init)
   - [obj_set_secondary_camera_focus](functions-2.md#obj_set_secondary_camera_focus)
   - [bhv_boo_loop](functions-2.md#bhv_boo_loop)
   - [bhv_boo_boss_spawned_bridge_loop](functions-2.md#bhv_boo_boss_spawned_bridge_loop)
   - [bhv_bbh_tilting_trap_platform_loop](functions-2.md#bhv_bbh_tilting_trap_platform_loop)
   - [bhv_haunted_bookshelf_loop](functions-2.md#bhv_haunted_bookshelf_loop)
   - [bhv_merry_go_round_loop](functions-2.md#bhv_merry_go_round_loop)
   - [bhv_play_music_track_when_touched_loop](functions-2.md#bhv_play_music_track_when_touched_loop)
   - [bhv_beta_bowser_anchor_loop](functions-2.md#bhv_beta_bowser_anchor_loop)
   - [bhv_static_checkered_platform_loop](functions-2.md#bhv_static_checkered_platform_loop)
   - [bhv_castle_floor_trap_init](functions-2.md#bhv_castle_floor_trap_init)
   - [bhv_castle_floor_trap_loop](functions-2.md#bhv_castle_floor_trap_loop)
   - [bhv_floor_trap_in_castle_loop](functions-2.md#bhv_floor_trap_in_castle_loop)
   - [bhv_sparkle_spawn_loop](functions-2.md#bhv_sparkle_spawn_loop)
   - [bhv_scuttlebug_loop](functions-2.md#bhv_scuttlebug_loop)
   - [bhv_scuttlebug_spawn_loop](functions-2.md#bhv_scuttlebug_spawn_loop)
   - [bhv_whomp_loop](functions-2.md#bhv_whomp_loop)
   - [bhv_water_splash_spawn_droplets](functions-2.md#bhv_water_splash_spawn_droplets)
   - [bhv_water_droplet_loop](functions-2.md#bhv_water_droplet_loop)
   - [bhv_water_droplet_splash_init](functions-2.md#bhv_water_droplet_splash_init)
   - [bhv_bubble_splash_init](functions-2.md#bhv_bubble_splash_init)
   - [bhv_idle_water_wave_loop](functions-2.md#bhv_idle_water_wave_loop)
   - [bhv_shallow_water_splash_init](functions-2.md#bhv_shallow_water_splash_init)
   - [bhv_wave_trail_shrink](functions-2.md#bhv_wave_trail_shrink)
   - [bhv_strong_wind_particle_loop](functions-2.md#bhv_strong_wind_particle_loop)
   - [bhv_sl_snowman_wind_loop](functions-2.md#bhv_sl_snowman_wind_loop)
   - [bhv_sl_walking_penguin_loop](functions-2.md#bhv_sl_walking_penguin_loop)
   - [bhv_menu_button_init](functions-2.md#bhv_menu_button_init)
   - [bhv_menu_button_loop](functions-2.md#bhv_menu_button_loop)
   - [bhv_menu_button_manager_init](functions-2.md#bhv_menu_button_manager_init)
   - [bhv_menu_button_manager_loop](functions-2.md#bhv_menu_button_manager_loop)
   - [bhv_act_selector_star_type_loop](functions-2.md#bhv_act_selector_star_type_loop)
   - [bhv_act_selector_init](functions-2.md#bhv_act_selector_init)
   - [bhv_act_selector_loop](functions-2.md#bhv_act_selector_loop)
   - [bhv_moving_yellow_coin_init](functions-2.md#bhv_moving_yellow_coin_init)
   - [bhv_moving_yellow_coin_loop](functions-2.md#bhv_moving_yellow_coin_loop)
   - [bhv_moving_blue_coin_init](functions-2.md#bhv_moving_blue_coin_init)
   - [bhv_moving_blue_coin_loop](functions-2.md#bhv_moving_blue_coin_loop)
   - [bhv_blue_coin_sliding_jumping_init](functions-2.md#bhv_blue_coin_sliding_jumping_init)
   - [bhv_blue_coin_sliding_loop](functions-2.md#bhv_blue_coin_sliding_loop)
   - [bhv_blue_coin_jumping_loop](functions-2.md#bhv_blue_coin_jumping_loop)
   - [bhv_seaweed_init](functions-2.md#bhv_seaweed_init)
   - [bhv_seaweed_bundle_init](functions-2.md#bhv_seaweed_bundle_init)
   - [bhv_bobomb_init](functions-2.md#bhv_bobomb_init)
   - [bhv_bobomb_loop](functions-2.md#bhv_bobomb_loop)
   - [bhv_bobomb_fuse_smoke_init](functions-2.md#bhv_bobomb_fuse_smoke_init)
   - [bhv_bobomb_buddy_init](functions-2.md#bhv_bobomb_buddy_init)
   - [bhv_bobomb_buddy_loop](functions-2.md#bhv_bobomb_buddy_loop)
   - [bhv_cannon_closed_init](functions-2.md#bhv_cannon_closed_init)
   - [bhv_cannon_closed_loop](functions-2.md#bhv_cannon_closed_loop)
   - [bhv_whirlpool_init](functions-2.md#bhv_whirlpool_init)
   - [bhv_whirlpool_loop](functions-2.md#bhv_whirlpool_loop)
   - [bhv_jet_stream_loop](functions-2.md#bhv_jet_stream_loop)
   - [bhv_homing_amp_init](functions-2.md#bhv_homing_amp_init)
   - [bhv_homing_amp_loop](functions-2.md#bhv_homing_amp_loop)
   - [bhv_circling_amp_init](functions-2.md#bhv_circling_amp_init)
   - [bhv_circling_amp_loop](functions-2.md#bhv_circling_amp_loop)
   - [bhv_butterfly_init](functions-2.md#bhv_butterfly_init)
   - [bhv_butterfly_loop](functions-2.md#bhv_butterfly_loop)
   - [bhv_hoot_init](functions-2.md#bhv_hoot_init)
   - [bhv_hoot_loop](functions-2.md#bhv_hoot_loop)
   - [bhv_beta_holdable_object_init](functions-2.md#bhv_beta_holdable_object_init)
   - [bhv_beta_holdable_object_loop](functions-2.md#bhv_beta_holdable_object_loop)
   - [bhv_object_bubble_init](functions-2.md#bhv_object_bubble_init)
   - [bhv_object_bubble_loop](functions-2.md#bhv_object_bubble_loop)
   - [bhv_object_water_wave_init](functions-2.md#bhv_object_water_wave_init)
   - [bhv_object_water_wave_loop](functions-2.md#bhv_object_water_wave_loop)
   - [bhv_explosion_init](functions-2.md#bhv_explosion_init)
   - [bhv_explosion_loop](functions-2.md#bhv_explosion_loop)
   - [bhv_bobomb_bully_death_smoke_init](functions-2.md#bhv_bobomb_bully_death_smoke_init)
   - [bhv_bobomb_explosion_bubble_init](functions-2.md#bhv_bobomb_explosion_bubble_init)
   - [bhv_bobomb_explosion_bubble_loop](functions-2.md#bhv_bobomb_explosion_bubble_loop)
   - [bhv_respawner_loop](functions-2.md#bhv_respawner_loop)
   - [bhv_small_bully_init](functions-2.md#bhv_small_bully_init)
   - [bhv_bully_loop](functions-2.md#bhv_bully_loop)
   - [bhv_big_bully_init](functions-2.md#bhv_big_bully_init)
   - [bhv_big_bully_with_minions_init](functions-2.md#bhv_big_bully_with_minions_init)
   - [bhv_big_bully_with_minions_loop](functions-2.md#bhv_big_bully_with_minions_loop)
   - [bhv_jet_stream_ring_spawner_loop](functions-2.md#bhv_jet_stream_ring_spawner_loop)
   - [bhv_jet_stream_water_ring_init](functions-2.md#bhv_jet_stream_water_ring_init)
   - [bhv_jet_stream_water_ring_loop](functions-2.md#bhv_jet_stream_water_ring_loop)
   - [bhv_manta_ray_water_ring_init](functions-2.md#bhv_manta_ray_water_ring_init)
   - [bhv_manta_ray_water_ring_loop](functions-2.md#bhv_manta_ray_water_ring_loop)
   - [bhv_bowser_bomb_loop](functions-2.md#bhv_bowser_bomb_loop)
   - [bhv_bowser_bomb_explosion_loop](functions-2.md#bhv_bowser_bomb_explosion_loop)
   - [bhv_bowser_bomb_smoke_loop](functions-2.md#bhv_bowser_bomb_smoke_loop)
   - [bhv_celebration_star_init](functions-2.md#bhv_celebration_star_init)
   - [bhv_celebration_star_loop](functions-2.md#bhv_celebration_star_loop)
   - [bhv_celebration_star_sparkle_loop](functions-2.md#bhv_celebration_star_sparkle_loop)
   - [bhv_star_key_collection_puff_spawner_loop](functions-2.md#bhv_star_key_collection_puff_spawner_loop)
   - [bhv_lll_drawbridge_spawner_init](functions-2.md#bhv_lll_drawbridge_spawner_init)
   - [bhv_lll_drawbridge_spawner_loop](functions-2.md#bhv_lll_drawbridge_spawner_loop)
   - [bhv_lll_drawbridge_loop](functions-2.md#bhv_lll_drawbridge_loop)
   - [bhv_small_bomp_init](functions-2.md#bhv_small_bomp_init)
   - [bhv_small_bomp_loop](functions-2.md#bhv_small_bomp_loop)
   - [bhv_large_bomp_init](functions-2.md#bhv_large_bomp_init)
   - [bhv_large_bomp_loop](functions-2.md#bhv_large_bomp_loop)
   - [bhv_wf_sliding_platform_init](functions-2.md#bhv_wf_sliding_platform_init)
   - [bhv_wf_sliding_platform_loop](functions-2.md#bhv_wf_sliding_platform_loop)
   - [bhv_moneybag_init](functions-2.md#bhv_moneybag_init)
   - [bhv_moneybag_loop](functions-2.md#bhv_moneybag_loop)
   - [bhv_moneybag_hidden_loop](functions-2.md#bhv_moneybag_hidden_loop)
   - [bhv_bob_pit_bowling_ball_init](functions-2.md#bhv_bob_pit_bowling_ball_init)
   - [bhv_bob_pit_bowling_ball_loop](functions-2.md#bhv_bob_pit_bowling_ball_loop)
   - [bhv_free_bowling_ball_init](functions-2.md#bhv_free_bowling_ball_init)
   - [bhv_free_bowling_ball_loop](functions-2.md#bhv_free_bowling_ball_loop)
   - [bhv_bowling_ball_init](functions-2.md#bhv_bowling_ball_init)
   - [bhv_bowling_ball_loop](functions-2.md#bhv_bowling_ball_loop)
   - [bhv_generic_bowling_ball_spawner_init](functions-2.md#bhv_generic_bowling_ball_spawner_init)
   - [bhv_generic_bowling_ball_spawner_loop](functions-2.md#bhv_generic_bowling_ball_spawner_loop)
   - [bhv_thi_bowling_ball_spawner_loop](functions-2.md#bhv_thi_bowling_ball_spawner_loop)
   - [bhv_rr_cruiser_wing_init](functions-2.md#bhv_rr_cruiser_wing_init)
   - [bhv_rr_cruiser_wing_loop](functions-2.md#bhv_rr_cruiser_wing_loop)
   - [bhv_spindel_init](functions-2.md#bhv_spindel_init)
   - [bhv_spindel_loop](functions-2.md#bhv_spindel_loop)
   - [bhv_ssl_moving_pyramid_wall_init](functions-2.md#bhv_ssl_moving_pyramid_wall_init)
   - [bhv_ssl_moving_pyramid_wall_loop](functions-2.md#bhv_ssl_moving_pyramid_wall_loop)
   - [bhv_pyramid_elevator_init](functions-2.md#bhv_pyramid_elevator_init)
   - [bhv_pyramid_elevator_loop](functions-2.md#bhv_pyramid_elevator_loop)
   - [bhv_pyramid_elevator_trajectory_marker_ball_loop](functions-2.md#bhv_pyramid_elevator_trajectory_marker_ball_loop)
   - [bhv_pyramid_top_init](functions-2.md#bhv_pyramid_top_init)
   - [bhv_pyramid_top_loop](functions-2.md#bhv_pyramid_top_loop)
   - [bhv_pyramid_top_fragment_init](functions-2.md#bhv_pyramid_top_fragment_init)
   - [bhv_pyramid_top_fragment_loop](functions-2.md#bhv_pyramid_top_fragment_loop)
   - [bhv_pyramid_pillar_touch_detector_loop](functions-2.md#bhv_pyramid_pillar_touch_detector_loop)
   - [bhv_waterfall_sound_loop](functions-2.md#bhv_waterfall_sound_loop)
   - [bhv_volcano_sound_loop](functions-2.md#bhv_volcano_sound_loop)
   - [bhv_castle_flag_init](functions-2.md#bhv_castle_flag_init)
   - [bhv_birds_sound_loop](functions-2.md#bhv_birds_sound_loop)
   - [bhv_ambient_sounds_init](functions-2.md#bhv_ambient_sounds_init)
   - [bhv_sand_sound_loop](functions-2.md#bhv_sand_sound_loop)
   - [bhv_castle_cannon_grate_init](functions-2.md#bhv_castle_cannon_grate_init)
   - [bhv_snowmans_bottom_init](functions-2.md#bhv_snowmans_bottom_init)
   - [bhv_snowmans_bottom_loop](functions-2.md#bhv_snowmans_bottom_loop)
   - [bhv_snowmans_head_init](functions-2.md#bhv_snowmans_head_init)
   - [bhv_snowmans_head_loop](functions-2.md#bhv_snowmans_head_loop)
   - [bhv_snowmans_body_checkpoint_loop](functions-2.md#bhv_snowmans_body_checkpoint_loop)
   - [bhv_big_boulder_init](functions-2.md#bhv_big_boulder_init)
   - [bhv_big_boulder_loop](functions-2.md#bhv_big_boulder_loop)
   - [bhv_big_boulder_generator_loop](functions-2.md#bhv_big_boulder_generator_loop)
   - [bhv_wing_cap_init](functions-2.md#bhv_wing_cap_init)
   - [bhv_wing_vanish_cap_loop](functions-2.md#bhv_wing_vanish_cap_loop)
   - [bhv_metal_cap_init](functions-2.md#bhv_metal_cap_init)
   - [bhv_metal_cap_loop](functions-2.md#bhv_metal_cap_loop)
   - [bhv_normal_cap_init](functions-2.md#bhv_normal_cap_init)
   - [bhv_normal_cap_loop](functions-2.md#bhv_normal_cap_loop)
   - [bhv_vanish_cap_init](functions-2.md#bhv_vanish_cap_init)
   - [bhv_star_number_loop](functions-2.md#bhv_star_number_loop)
   - [spawn_star_number](functions-2.md#spawn_star_number)
   - [bhv_collect_star_init](functions-2.md#bhv_collect_star_init)
   - [bhv_collect_star_loop](functions-2.md#bhv_collect_star_loop)
   - [bhv_star_spawn_init](functions-2.md#bhv_star_spawn_init)
   - [bhv_star_spawn_loop](functions-2.md#bhv_star_spawn_loop)
   - [bhv_hidden_red_coin_star_init](functions-2.md#bhv_hidden_red_coin_star_init)
   - [bhv_hidden_red_coin_star_loop](functions-2.md#bhv_hidden_red_coin_star_loop)
   - [bhv_red_coin_init](functions-2.md#bhv_red_coin_init)
   - [bhv_red_coin_loop](functions-2.md#bhv_red_coin_loop)
   - [bhv_bowser_course_red_coin_star_loop](functions-2.md#bhv_bowser_course_red_coin_star_loop)
   - [bhv_hidden_star_init](functions-2.md#bhv_hidden_star_init)
   - [bhv_hidden_star_loop](functions-2.md#bhv_hidden_star_loop)
   - [bhv_hidden_star_trigger_loop](functions-2.md#bhv_hidden_star_trigger_loop)
   - [bhv_ttm_rolling_log_init](functions-2.md#bhv_ttm_rolling_log_init)
   - [bhv_rolling_log_loop](functions-2.md#bhv_rolling_log_loop)
   - [bhv_lll_rolling_log_init](functions-2.md#bhv_lll_rolling_log_init)
   - [bhv_1up_trigger_init](functions-2.md#bhv_1up_trigger_init)
   - [bhv_1up_common_init](functions-2.md#bhv_1up_common_init)
   - [bhv_1up_walking_loop](functions-2.md#bhv_1up_walking_loop)
   - [bhv_1up_running_away_loop](functions-2.md#bhv_1up_running_away_loop)
   - [bhv_1up_sliding_loop](functions-2.md#bhv_1up_sliding_loop)
   - [bhv_1up_init](functions-2.md#bhv_1up_init)
   - [bhv_1up_loop](functions-2.md#bhv_1up_loop)
   - [bhv_1up_jump_on_approach_loop](functions-2.md#bhv_1up_jump_on_approach_loop)
   - [bhv_1up_hidden_loop](functions-2.md#bhv_1up_hidden_loop)
   - [bhv_1up_hidden_trigger_loop](functions-2.md#bhv_1up_hidden_trigger_loop)
   - [bhv_1up_hidden_in_pole_loop](functions-2.md#bhv_1up_hidden_in_pole_loop)
   - [bhv_1up_hidden_in_pole_trigger_loop](functions-2.md#bhv_1up_hidden_in_pole_trigger_loop)
   - [bhv_1up_hidden_in_pole_spawner_loop](functions-2.md#bhv_1up_hidden_in_pole_spawner_loop)
   - [bhv_controllable_platform_init](functions-2.md#bhv_controllable_platform_init)
   - [bhv_controllable_platform_loop](functions-2.md#bhv_controllable_platform_loop)
   - [bhv_controllable_platform_sub_loop](functions-2.md#bhv_controllable_platform_sub_loop)
   - [bhv_breakable_box_small_init](functions-2.md#bhv_breakable_box_small_init)
   - [bhv_breakable_box_small_loop](functions-2.md#bhv_breakable_box_small_loop)
   - [bhv_sliding_snow_mound_loop](functions-2.md#bhv_sliding_snow_mound_loop)
   - [bhv_snow_mound_spawn_loop](functions-2.md#bhv_snow_mound_spawn_loop)
   - [bhv_floating_platform_loop](functions-2.md#bhv_floating_platform_loop)
   - [bhv_arrow_lift_loop](functions-2.md#bhv_arrow_lift_loop)
   - [bhv_orange_number_init](functions-2.md#bhv_orange_number_init)
   - [bhv_orange_number_loop](functions-2.md#bhv_orange_number_loop)
   - [bhv_manta_ray_init](functions-2.md#bhv_manta_ray_init)
   - [bhv_manta_ray_loop](functions-2.md#bhv_manta_ray_loop)
   - [bhv_falling_pillar_init](functions-2.md#bhv_falling_pillar_init)
   - [bhv_falling_pillar_loop](functions-2.md#bhv_falling_pillar_loop)
   - [bhv_falling_pillar_hitbox_loop](functions-2.md#bhv_falling_pillar_hitbox_loop)
   - [bhv_jrb_floating_box_loop](functions-2.md#bhv_jrb_floating_box_loop)
   - [bhv_decorative_pendulum_init](functions-2.md#bhv_decorative_pendulum_init)
   - [bhv_decorative_pendulum_loop](functions-2.md#bhv_decorative_pendulum_loop)
   - [bhv_treasure_chest_ship_init](functions-2.md#bhv_treasure_chest_ship_init)
   - [bhv_treasure_chest_ship_loop](functions-2.md#bhv_treasure_chest_ship_loop)
   - [bhv_treasure_chest_jrb_init](functions-2.md#bhv_treasure_chest_jrb_init)
   - [bhv_treasure_chest_jrb_loop](functions-2.md#bhv_treasure_chest_jrb_loop)
   - [bhv_treasure_chest_init](functions-2.md#bhv_treasure_chest_init)
   - [bhv_treasure_chest_loop](functions-2.md#bhv_treasure_chest_loop)
   - [bhv_treasure_chest_bottom_init](functions-2.md#bhv_treasure_chest_bottom_init)
   - [bhv_treasure_chest_bottom_loop](functions-2.md#bhv_treasure_chest_bottom_loop)
   - [bhv_treasure_chest_top_loop](functions-2.md#bhv_treasure_chest_top_loop)
   - [bhv_mips_init](functions-2.md#bhv_mips_init)
   - [bhv_mips_loop](functions-2.md#bhv_mips_loop)
   - [bhv_yoshi_init](functions-2.md#bhv_yoshi_init)
   - [bhv_koopa_init](functions-2.md#bhv_koopa_init)
   - [bhv_koopa_update](functions-2.md#bhv_koopa_update)
   - [bhv_koopa_race_endpoint_update](functions-2.md#bhv_koopa_race_endpoint_update)
   - [bhv_pokey_update](functions-2.md#bhv_pokey_update)
   - [bhv_pokey_body_part_update](functions-2.md#bhv_pokey_body_part_update)
   - [bhv_swoop_update](functions-2.md#bhv_swoop_update)
   - [bhv_fly_guy_update](functions-2.md#bhv_fly_guy_update)
   - [bhv_goomba_init](functions-2.md#bhv_goomba_init)
   - [bhv_goomba_update](functions-2.md#bhv_goomba_update)
   - [bhv_goomba_triplet_spawner_update](functions-2.md#bhv_goomba_triplet_spawner_update)
   - [bhv_chain_chomp_update](functions-2.md#bhv_chain_chomp_update)
   - [bhv_chain_chomp_chain_part_update](functions-2.md#bhv_chain_chomp_chain_part_update)
   - [bhv_wooden_post_update](functions-2.md#bhv_wooden_post_update)
   - [bhv_chain_chomp_gate_init](functions-2.md#bhv_chain_chomp_gate_init)
   - [bhv_chain_chomp_gate_update](functions-2.md#bhv_chain_chomp_gate_update)
   - [bhv_wiggler_update](functions-2.md#bhv_wiggler_update)
   - [bhv_wiggler_body_part_update](functions-2.md#bhv_wiggler_body_part_update)
   - [bhv_enemy_lakitu_update](functions-2.md#bhv_enemy_lakitu_update)
   - [bhv_camera_lakitu_init](functions-2.md#bhv_camera_lakitu_init)
   - [bhv_camera_lakitu_update](functions-2.md#bhv_camera_lakitu_update)
   - [bhv_cloud_update](functions-2.md#bhv_cloud_update)
   - [bhv_cloud_part_update](functions-2.md#bhv_cloud_part_update)
   - [bhv_spiny_update](functions-2.md#bhv_spiny_update)
   - [bhv_monty_mole_init](functions-2.md#bhv_monty_mole_init)
   - [bhv_monty_mole_update](functions-2.md#bhv_monty_mole_update)
   - [bhv_monty_mole_hole_update](functions-2.md#bhv_monty_mole_hole_update)
   - [bhv_monty_mole_rock_update](functions-2.md#bhv_monty_mole_rock_update)
   - [bhv_platform_on_track_init](functions-2.md#bhv_platform_on_track_init)
   - [bhv_platform_on_track_update](functions-2.md#bhv_platform_on_track_update)
   - [bhv_track_ball_update](functions-2.md#bhv_track_ball_update)
   - [bhv_seesaw_platform_init](functions-2.md#bhv_seesaw_platform_init)
   - [bhv_seesaw_platform_update](functions-2.md#bhv_seesaw_platform_update)
   - [bhv_ferris_wheel_axle_init](functions-2.md#bhv_ferris_wheel_axle_init)
   - [bhv_ferris_wheel_platform_init](functions-2.md#bhv_ferris_wheel_platform_init)
   - [bhv_ferris_wheel_platform_update](functions-2.md#bhv_ferris_wheel_platform_update)
   - [bhv_water_bomb_spawner_update](functions-2.md#bhv_water_bomb_spawner_update)
   - [bhv_water_bomb_update](functions-2.md#bhv_water_bomb_update)
   - [bhv_water_bomb_shadow_update](functions-2.md#bhv_water_bomb_shadow_update)
   - [bhv_ttc_rotating_solid_init](functions-2.md#bhv_ttc_rotating_solid_init)
   - [bhv_ttc_rotating_solid_update](functions-2.md#bhv_ttc_rotating_solid_update)
   - [bhv_ttc_pendulum_init](functions-2.md#bhv_ttc_pendulum_init)
   - [bhv_ttc_pendulum_update](functions-2.md#bhv_ttc_pendulum_update)
   - [bhv_ttc_treadmill_init](functions-2.md#bhv_ttc_treadmill_init)
   - [bhv_ttc_treadmill_update](functions-2.md#bhv_ttc_treadmill_update)
   - [bhv_ttc_moving_bar_init](functions-2.md#bhv_ttc_moving_bar_init)
   - [bhv_ttc_moving_bar_update](functions-2.md#bhv_ttc_moving_bar_update)
   - [bhv_ttc_cog_init](functions-2.md#bhv_ttc_cog_init)
   - [bhv_ttc_cog_update](functions-2.md#bhv_ttc_cog_update)
   - [bhv_ttc_pit_block_init](functions-2.md#bhv_ttc_pit_block_init)
   - [bhv_ttc_pit_block_update](functions-2.md#bhv_ttc_pit_block_update)
   - [bhv_ttc_elevator_init](functions-2.md#bhv_ttc_elevator_init)
   - [bhv_ttc_elevator_update](functions-2.md#bhv_ttc_elevator_update)
   - [bhv_ttc_2d_rotator_init](functions-2.md#bhv_ttc_2d_rotator_init)
   - [bhv_ttc_2d_rotator_update](functions-2.md#bhv_ttc_2d_rotator_update)
   - [bhv_ttc_spinner_update](functions-2.md#bhv_ttc_spinner_update)
   - [bhv_mr_blizzard_init](functions-2.md#bhv_mr_blizzard_init)
   - [bhv_mr_blizzard_update](functions-2.md#bhv_mr_blizzard_update)
   - [bhv_mr_blizzard_snowball](functions-2.md#bhv_mr_blizzard_snowball)
   - [bhv_sliding_plat_2_init](functions-2.md#bhv_sliding_plat_2_init)
   - [bhv_sliding_plat_2_loop](functions-2.md#bhv_sliding_plat_2_loop)
   - [bhv_rotating_octagonal_plat_init](functions-2.md#bhv_rotating_octagonal_plat_init)
   - [bhv_rotating_octagonal_plat_loop](functions-2.md#bhv_rotating_octagonal_plat_loop)
   - [bhv_animates_on_floor_switch_press_init](functions-2.md#bhv_animates_on_floor_switch_press_init)
   - [bhv_animates_on_floor_switch_press_loop](functions-2.md#bhv_animates_on_floor_switch_press_loop)
   - [bhv_activated_back_and_forth_platform_init](functions-2.md#bhv_activated_back_and_forth_platform_init)
   - [bhv_activated_back_and_forth_platform_update](functions-2.md#bhv_activated_back_and_forth_platform_update)
   - [bhv_recovery_heart_loop](functions-2.md#bhv_recovery_heart_loop)
   - [bhv_water_bomb_cannon_loop](functions-2.md#bhv_water_bomb_cannon_loop)
   - [bhv_bubble_cannon_barrel_loop](functions-2.md#bhv_bubble_cannon_barrel_loop)
   - [bhv_unagi_init](functions-2.md#bhv_unagi_init)
   - [bhv_unagi_loop](functions-2.md#bhv_unagi_loop)
   - [bhv_unagi_subobject_loop](functions-2.md#bhv_unagi_subobject_loop)
   - [bhv_dorrie_update](functions-2.md#bhv_dorrie_update)
   - [bhv_haunted_chair_init](functions-2.md#bhv_haunted_chair_init)
   - [bhv_haunted_chair_loop](functions-2.md#bhv_haunted_chair_loop)
   - [bhv_mad_piano_update](functions-2.md#bhv_mad_piano_update)
   - [bhv_flying_bookend_loop](functions-2.md#bhv_flying_bookend_loop)
   - [bhv_bookend_spawn_loop](functions-2.md#bhv_bookend_spawn_loop)
   - [bhv_haunted_bookshelf_manager_loop](functions-2.md#bhv_haunted_bookshelf_manager_loop)
   - [bhv_book_switch_loop](functions-2.md#bhv_book_switch_loop)
   - [bhv_fire_piranha_plant_init](functions-2.md#bhv_fire_piranha_plant_init)
   - [bhv_fire_piranha_plant_update](functions-2.md#bhv_fire_piranha_plant_update)
   - [bhv_small_piranha_flame_loop](functions-2.md#bhv_small_piranha_flame_loop)
   - [bhv_fire_spitter_update](functions-2.md#bhv_fire_spitter_update)
   - [bhv_fly_guy_flame_loop](functions-2.md#bhv_fly_guy_flame_loop)
   - [bhv_snufit_loop](functions-2.md#bhv_snufit_loop)
   - [bhv_snufit_balls_loop](functions-2.md#bhv_snufit_balls_loop)
   - [bhv_horizontal_grindel_init](functions-2.md#bhv_horizontal_grindel_init)
   - [bhv_horizontal_grindel_update](functions-2.md#bhv_horizontal_grindel_update)
   - [bhv_eyerok_boss_init](functions-2.md#bhv_eyerok_boss_init)
   - [bhv_eyerok_boss_loop](functions-2.md#bhv_eyerok_boss_loop)
   - [bhv_eyerok_hand_loop](functions-2.md#bhv_eyerok_hand_loop)
   - [bhv_klepto_init](functions-2.md#bhv_klepto_init)
   - [bhv_klepto_update](functions-2.md#bhv_klepto_update)
   - [bhv_bird_update](functions-2.md#bhv_bird_update)
   - [bhv_racing_penguin_init](functions-2.md#bhv_racing_penguin_init)
   - [bhv_racing_penguin_update](functions-2.md#bhv_racing_penguin_update)
   - [bhv_penguin_race_finish_line_update](functions-2.md#bhv_penguin_race_finish_line_update)
   - [bhv_penguin_race_shortcut_check_update](functions-2.md#bhv_penguin_race_shortcut_check_update)
   - [bhv_coffin_spawner_loop](functions-2.md#bhv_coffin_spawner_loop)
   - [bhv_coffin_loop](functions-2.md#bhv_coffin_loop)
   - [bhv_clam_loop](functions-2.md#bhv_clam_loop)
   - [bhv_skeeter_update](functions-2.md#bhv_skeeter_update)
   - [bhv_skeeter_wave_update](functions-2.md#bhv_skeeter_wave_update)
   - [bhv_swing_platform_init](functions-2.md#bhv_swing_platform_init)
   - [bhv_swing_platform_update](functions-2.md#bhv_swing_platform_update)
   - [bhv_donut_platform_spawner_update](functions-2.md#bhv_donut_platform_spawner_update)
   - [bhv_donut_platform_update](functions-2.md#bhv_donut_platform_update)
   - [bhv_ddd_pole_init](functions-2.md#bhv_ddd_pole_init)
   - [bhv_ddd_pole_update](functions-2.md#bhv_ddd_pole_update)
   - [bhv_red_coin_star_marker_init](functions-2.md#bhv_red_coin_star_marker_init)
   - [bhv_triplet_butterfly_update](functions-2.md#bhv_triplet_butterfly_update)
   - [bhv_bubba_loop](functions-2.md#bhv_bubba_loop)
   - [bhv_intro_lakitu_loop](functions-2.md#bhv_intro_lakitu_loop)
   - [bhv_intro_peach_loop](functions-2.md#bhv_intro_peach_loop)
   - [bhv_end_birds_1_loop](functions-2.md#bhv_end_birds_1_loop)
   - [bhv_end_birds_2_loop](functions-2.md#bhv_end_birds_2_loop)
   - [bhv_intro_scene_loop](functions-2.md#bhv_intro_scene_loop)
   - [bhv_yoshi_loop](functions-2.md#bhv_yoshi_loop)
   - [bhv_volcano_trap_loop](functions-2.md#bhv_volcano_trap_loop)
   - [uv_update_scroll](functions-2.md#uv_update_scroll)
   - [spawn_ambient_light](functions-2.md#spawn_ambient_light)
   - [spawn_point_light](functions-2.md#spawn_point_light)
   - [bhv_ambient_light_update](functions-2.md#bhv_ambient_light_update)
   - [bhv_point_light_init](functions-2.md#bhv_point_light_init)
   - [bhv_point_light_loop](functions-2.md#bhv_point_light_loop)
   - [spawn_default_star](functions-2.md#spawn_default_star)
   - [spawn_red_coin_cutscene_star](functions-2.md#spawn_red_coin_cutscene_star)
   - [spawn_no_exit_star](functions-2.md#spawn_no_exit_star)

<br />

- behavior_script.h
   - [random_u16](functions-3.md#random_u16)
   - [random_float](functions-3.md#random_float)
   - [random_sign](functions-3.md#random_sign)
   - [obj_update_gfx_pos_and_angle](functions-3.md#obj_update_gfx_pos_and_angle)
   - [position_based_random_u16](functions-3.md#position_based_random_u16)
   - [position_based_random_float_position](functions-3.md#position_based_random_float_position)
   - [draw_distance_scalar](functions-3.md#draw_distance_scalar)

<br />

- behavior_table.h
   - [get_id_from_behavior](functions-3.md#get_id_from_behavior)
   - [get_id_from_vanilla_behavior](functions-3.md#get_id_from_vanilla_behavior)
   - [get_behavior_from_id](functions-3.md#get_behavior_from_id)
   - [get_behavior_name_from_id](functions-3.md#get_behavior_name_from_id)
   - [get_id_from_behavior_name](functions-3.md#get_id_from_behavior_name)

<br />

- camera.h
   - [skip_camera_interpolation](functions-3.md#skip_camera_interpolation)
   - [set_camera_shake_from_hit](functions-3.md#set_camera_shake_from_hit)
   - [set_environmental_camera_shake](functions-3.md#set_environmental_camera_shake)
   - [set_camera_shake_from_point](functions-3.md#set_camera_shake_from_point)
   - [move_mario_head_c_up](functions-3.md#move_mario_head_c_up)
   - [transition_next_state](functions-3.md#transition_next_state)
   - [set_camera_mode](functions-3.md#set_camera_mode)
   - [soft_reset_camera](functions-3.md#soft_reset_camera)
   - [reset_camera](functions-3.md#reset_camera)
   - [select_mario_cam_mode](functions-3.md#select_mario_cam_mode)
   - [object_pos_to_vec3f](functions-3.md#object_pos_to_vec3f)
   - [vec3f_to_object_pos](functions-3.md#vec3f_to_object_pos)
   - [cam_select_alt_mode](functions-3.md#cam_select_alt_mode)
   - [set_cam_angle](functions-3.md#set_cam_angle)
   - [set_handheld_shake](functions-3.md#set_handheld_shake)
   - [shake_camera_handheld](functions-3.md#shake_camera_handheld)
   - [find_c_buttons_pressed](functions-3.md#find_c_buttons_pressed)
   - [collide_with_walls](functions-3.md#collide_with_walls)
   - [clamp_pitch](functions-3.md#clamp_pitch)
   - [is_within_100_units_of_mario](functions-3.md#is_within_100_units_of_mario)
   - [set_or_approach_f32_asymptotic](functions-3.md#set_or_approach_f32_asymptotic)
   - [approach_f32_asymptotic_bool](functions-3.md#approach_f32_asymptotic_bool)
   - [approach_f32_asymptotic](functions-3.md#approach_f32_asymptotic)
   - [approach_s16_asymptotic_bool](functions-3.md#approach_s16_asymptotic_bool)
   - [approach_s16_asymptotic](functions-3.md#approach_s16_asymptotic)
   - [approach_vec3f_asymptotic](functions-3.md#approach_vec3f_asymptotic)
   - [set_or_approach_vec3f_asymptotic](functions-3.md#set_or_approach_vec3f_asymptotic)
   - [camera_approach_s16_symmetric_bool](functions-3.md#camera_approach_s16_symmetric_bool)
   - [set_or_approach_s16_symmetric](functions-3.md#set_or_approach_s16_symmetric)
   - [camera_approach_f32_symmetric_bool](functions-3.md#camera_approach_f32_symmetric_bool)
   - [camera_approach_f32_symmetric](functions-3.md#camera_approach_f32_symmetric)
   - [random_vec3s](functions-3.md#random_vec3s)
   - [clamp_positions_and_find_yaw](functions-3.md#clamp_positions_and_find_yaw)
   - [is_range_behind_surface](functions-3.md#is_range_behind_surface)
   - [scale_along_line](functions-3.md#scale_along_line)
   - [calculate_pitch](functions-3.md#calculate_pitch)
   - [calculate_yaw](functions-3.md#calculate_yaw)
   - [calculate_angles](functions-3.md#calculate_angles)
   - [calc_abs_dist](functions-3.md#calc_abs_dist)
   - [calc_hor_dist](functions-3.md#calc_hor_dist)
   - [rotate_in_xz](functions-3.md#rotate_in_xz)
   - [rotate_in_yz](functions-3.md#rotate_in_yz)
   - [set_camera_pitch_shake](functions-3.md#set_camera_pitch_shake)
   - [set_camera_yaw_shake](functions-3.md#set_camera_yaw_shake)
   - [set_camera_roll_shake](functions-3.md#set_camera_roll_shake)
   - [set_pitch_shake_from_point](functions-3.md#set_pitch_shake_from_point)
   - [shake_camera_pitch](functions-3.md#shake_camera_pitch)
   - [shake_camera_yaw](functions-3.md#shake_camera_yaw)
   - [shake_camera_roll](functions-3.md#shake_camera_roll)
   - [offset_yaw_outward_radial](functions-3.md#offset_yaw_outward_radial)
   - [play_camera_buzz_if_cdown](functions-3.md#play_camera_buzz_if_cdown)
   - [play_camera_buzz_if_cbutton](functions-3.md#play_camera_buzz_if_cbutton)
   - [play_camera_buzz_if_c_sideways](functions-3.md#play_camera_buzz_if_c_sideways)
   - [play_sound_cbutton_up](functions-3.md#play_sound_cbutton_up)
   - [play_sound_cbutton_down](functions-3.md#play_sound_cbutton_down)
   - [play_sound_cbutton_side](functions-3.md#play_sound_cbutton_side)
   - [play_sound_button_change_blocked](functions-3.md#play_sound_button_change_blocked)
   - [play_sound_rbutton_changed](functions-3.md#play_sound_rbutton_changed)
   - [play_sound_if_cam_switched_to_lakitu_or_mario](functions-3.md#play_sound_if_cam_switched_to_lakitu_or_mario)
   - [radial_camera_input](functions-3.md#radial_camera_input)
   - [trigger_cutscene_dialog](functions-3.md#trigger_cutscene_dialog)
   - [handle_c_button_movement](functions-3.md#handle_c_button_movement)
   - [start_cutscene](functions-3.md#start_cutscene)
   - [get_cutscene_from_mario_status](functions-3.md#get_cutscene_from_mario_status)
   - [warp_camera](functions-3.md#warp_camera)
   - [approach_camera_height](functions-3.md#approach_camera_height)
   - [offset_rotated](functions-3.md#offset_rotated)
   - [next_lakitu_state](functions-3.md#next_lakitu_state)
   - [set_fixed_cam_axis_sa_lobby](functions-3.md#set_fixed_cam_axis_sa_lobby)
   - [camera_course_processing](functions-3.md#camera_course_processing)
   - [resolve_geometry_collisions](functions-3.md#resolve_geometry_collisions)
   - [rotate_camera_around_walls](functions-3.md#rotate_camera_around_walls)
   - [find_mario_floor_and_ceil](functions-3.md#find_mario_floor_and_ceil)
   - [start_object_cutscene_without_focus](functions-3.md#start_object_cutscene_without_focus)
   - [cutscene_object_with_dialog](functions-3.md#cutscene_object_with_dialog)
   - [cutscene_object_without_dialog](functions-3.md#cutscene_object_without_dialog)
   - [cutscene_object](functions-3.md#cutscene_object)
   - [play_cutscene](functions-3.md#play_cutscene)
   - [cutscene_spawn_obj](functions-3.md#cutscene_spawn_obj)
   - [set_fov_shake](functions-3.md#set_fov_shake)
   - [set_fov_function](functions-3.md#set_fov_function)
   - [cutscene_set_fov_shake_preset](functions-3.md#cutscene_set_fov_shake_preset)
   - [set_fov_shake_from_point_preset](functions-3.md#set_fov_shake_from_point_preset)
   - [obj_rotate_towards_point](functions-3.md#obj_rotate_towards_point)
   - [set_camera_mode_fixed](functions-3.md#set_camera_mode_fixed)
   - [snap_to_45_degrees](functions-3.md#snap_to_45_degrees)
   - [camera_set_use_course_specific_settings](functions-3.md#camera_set_use_course_specific_settings)
   - [center_rom_hack_camera](functions-3.md#center_rom_hack_camera)

<br />

- characters.h
   - [get_character](functions-3.md#get_character)
   - [play_character_sound](functions-3.md#play_character_sound)
   - [play_character_sound_offset](functions-3.md#play_character_sound_offset)
   - [play_character_sound_if_no_flag](functions-3.md#play_character_sound_if_no_flag)
   - [get_character_anim_offset](functions-3.md#get_character_anim_offset)
   - [get_character_anim](functions-3.md#get_character_anim)
   - [update_character_anim_offset](functions-3.md#update_character_anim_offset)

<br />

- djui_chat_message.h
   - [djui_chat_message_create](functions-3.md#djui_chat_message_create)

<br />

- djui_console.h
   - [djui_console_toggle](functions-3.md#djui_console_toggle)

<br />

- djui_hud_utils.h
   - [djui_hud_get_resolution](functions-3.md#djui_hud_get_resolution)
   - [djui_hud_set_resolution](functions-3.md#djui_hud_set_resolution)
   - [djui_hud_get_filter](functions-3.md#djui_hud_get_filter)
   - [djui_hud_set_filter](functions-3.md#djui_hud_set_filter)
   - [djui_hud_get_font](functions-3.md#djui_hud_get_font)
   - [djui_hud_set_font](functions-3.md#djui_hud_set_font)
   - [djui_hud_get_color](functions-3.md#djui_hud_get_color)
   - [djui_hud_set_color](functions-3.md#djui_hud_set_color)
   - [djui_hud_reset_color](functions-3.md#djui_hud_reset_color)
   - [djui_hud_get_rotation](functions-3.md#djui_hud_get_rotation)
   - [djui_hud_set_rotation](functions-3.md#djui_hud_set_rotation)
   - [djui_hud_set_rotation_interpolated](functions-3.md#djui_hud_set_rotation_interpolated)
   - [djui_hud_get_screen_width](functions-3.md#djui_hud_get_screen_width)
   - [djui_hud_get_screen_height](functions-3.md#djui_hud_get_screen_height)
   - [djui_hud_get_mouse_x](functions-3.md#djui_hud_get_mouse_x)
   - [djui_hud_get_mouse_y](functions-3.md#djui_hud_get_mouse_y)
   - [djui_hud_get_raw_mouse_x](functions-3.md#djui_hud_get_raw_mouse_x)
   - [djui_hud_get_raw_mouse_y](functions-3.md#djui_hud_get_raw_mouse_y)
   - [djui_hud_set_mouse_locked](functions-3.md#djui_hud_set_mouse_locked)
   - [djui_hud_get_mouse_buttons_down](functions-3.md#djui_hud_get_mouse_buttons_down)
   - [djui_hud_get_mouse_buttons_pressed](functions-3.md#djui_hud_get_mouse_buttons_pressed)
   - [djui_hud_get_mouse_buttons_released](functions-3.md#djui_hud_get_mouse_buttons_released)
   - [djui_hud_get_mouse_scroll_x](functions-3.md#djui_hud_get_mouse_scroll_x)
   - [djui_hud_get_mouse_scroll_y](functions-3.md#djui_hud_get_mouse_scroll_y)
   - [djui_hud_measure_text](functions-3.md#djui_hud_measure_text)
   - [djui_hud_print_text](functions-3.md#djui_hud_print_text)
   - [djui_hud_print_text_interpolated](functions-3.md#djui_hud_print_text_interpolated)
   - [djui_hud_render_rect](functions-3.md#djui_hud_render_rect)
   - [djui_hud_render_rect_interpolated](functions-3.md#djui_hud_render_rect_interpolated)
   - [get_current_fov](functions-3.md#get_current_fov)
   - [djui_hud_get_fov_coeff](functions-3.md#djui_hud_get_fov_coeff)
   - [djui_hud_world_pos_to_screen_pos](functions-3.md#djui_hud_world_pos_to_screen_pos)
   - [djui_hud_is_pause_menu_created](functions-3.md#djui_hud_is_pause_menu_created)
   - [djui_open_pause_menu](functions-3.md#djui_open_pause_menu)

<br />

- djui_language.h
   - [djui_language_get](functions-3.md#djui_language_get)

<br />

- djui_panel_menu.h
   - [djui_menu_get_rainbow_string_color](functions-3.md#djui_menu_get_rainbow_string_color)

<br />

- djui_popup.h
   - [djui_popup_create](functions-3.md#djui_popup_create)

<br />

- external.h
   - [play_sound](functions-3.md#play_sound)
   - [play_sound_with_freq_scale](functions-3.md#play_sound_with_freq_scale)
   - [seq_player_fade_out](functions-3.md#seq_player_fade_out)
   - [fade_volume_scale](functions-3.md#fade_volume_scale)
   - [seq_player_lower_volume](functions-3.md#seq_player_lower_volume)
   - [seq_player_unlower_volume](functions-3.md#seq_player_unlower_volume)
   - [set_audio_muted](functions-3.md#set_audio_muted)
   - [stop_sound](functions-3.md#stop_sound)
   - [stop_sounds_from_source](functions-3.md#stop_sounds_from_source)
   - [stop_sounds_in_continuous_banks](functions-3.md#stop_sounds_in_continuous_banks)
   - [sound_banks_disable](functions-3.md#sound_banks_disable)
   - [sound_banks_enable](functions-3.md#sound_banks_enable)
   - [set_sound_moving_speed](functions-3.md#set_sound_moving_speed)
   - [play_dialog_sound](functions-3.md#play_dialog_sound)
   - [play_music](functions-3.md#play_music)
   - [stop_background_music](functions-3.md#stop_background_music)
   - [fadeout_background_music](functions-3.md#fadeout_background_music)
   - [drop_queued_background_music](functions-3.md#drop_queued_background_music)
   - [get_current_background_music](functions-3.md#get_current_background_music)
   - [get_current_background_music_default_volume](functions-3.md#get_current_background_music_default_volume)
   - [get_current_background_music_target_volume](functions-3.md#get_current_background_music_target_volume)
   - [get_current_background_music_max_target_volume](functions-3.md#get_current_background_music_max_target_volume)
   - [is_current_background_music_volume_lowered](functions-3.md#is_current_background_music_volume_lowered)
   - [play_secondary_music](functions-3.md#play_secondary_music)
   - [stop_secondary_music](functions-3.md#stop_secondary_music)
   - [set_audio_fadeout](functions-3.md#set_audio_fadeout)
   - [play_course_clear](functions-3.md#play_course_clear)
   - [play_peachs_jingle](functions-3.md#play_peachs_jingle)
   - [play_puzzle_jingle](functions-3.md#play_puzzle_jingle)
   - [play_star_fanfare](functions-3.md#play_star_fanfare)
   - [play_power_star_jingle](functions-3.md#play_power_star_jingle)
   - [play_race_fanfare](functions-3.md#play_race_fanfare)
   - [play_toads_jingle](functions-3.md#play_toads_jingle)
   - [sound_reset_background_music_default_volume](functions-3.md#sound_reset_background_music_default_volume)
   - [sound_set_background_music_default_volume](functions-3.md#sound_set_background_music_default_volume)
   - [get_sound_pan](functions-3.md#get_sound_pan)
   - [sound_get_level_intensity](functions-3.md#sound_get_level_intensity)

<br />

- first_person_cam.h
   - [first_person_check_cancels](functions-3.md#first_person_check_cancels)
   - [get_first_person_enabled](functions-3.md#get_first_person_enabled)
   - [set_first_person_enabled](functions-3.md#set_first_person_enabled)
   - [first_person_reset](functions-3.md#first_person_reset)

<br />

- ingame_menu.h
   - [create_dialog_box](functions-3.md#create_dialog_box)
   - [create_dialog_box_with_var](functions-3.md#create_dialog_box_with_var)
   - [create_dialog_inverted_box](functions-3.md#create_dialog_inverted_box)
   - [create_dialog_box_with_response](functions-3.md#create_dialog_box_with_response)
   - [reset_dialog_render_state](functions-3.md#reset_dialog_render_state)
   - [set_menu_mode](functions-3.md#set_menu_mode)
   - [set_min_dialog_width](functions-3.md#set_min_dialog_width)
   - [set_dialog_override_pos](functions-3.md#set_dialog_override_pos)
   - [reset_dialog_override_pos](functions-3.md#reset_dialog_override_pos)
   - [set_dialog_override_color](functions-3.md#set_dialog_override_color)
   - [reset_dialog_override_color](functions-3.md#reset_dialog_override_color)
   - [set_dialog_box_state](functions-3.md#set_dialog_box_state)

<br />

- interaction.h
   - [interact_coin](functions-3.md#interact_coin)
   - [interact_water_ring](functions-3.md#interact_water_ring)
   - [interact_star_or_key](functions-3.md#interact_star_or_key)
   - [interact_bbh_entrance](functions-3.md#interact_bbh_entrance)
   - [interact_warp](functions-3.md#interact_warp)
   - [interact_warp_door](functions-3.md#interact_warp_door)
   - [interact_door](functions-3.md#interact_door)
   - [interact_cannon_base](functions-3.md#interact_cannon_base)
   - [interact_player](functions-3.md#interact_player)
   - [interact_igloo_barrier](functions-3.md#interact_igloo_barrier)
   - [interact_tornado](functions-3.md#interact_tornado)
   - [interact_whirlpool](functions-3.md#interact_whirlpool)
   - [interact_strong_wind](functions-3.md#interact_strong_wind)
   - [interact_flame](functions-3.md#interact_flame)
   - [interact_snufit_bullet](functions-3.md#interact_snufit_bullet)
   - [interact_clam_or_bubba](functions-3.md#interact_clam_or_bubba)
   - [interact_bully](functions-3.md#interact_bully)
   - [interact_shock](functions-3.md#interact_shock)
   - [interact_mr_blizzard](functions-3.md#interact_mr_blizzard)
   - [interact_hit_from_below](functions-3.md#interact_hit_from_below)
   - [interact_bounce_top](functions-3.md#interact_bounce_top)
   - [interact_spiny_walking](functions-3.md#interact_spiny_walking)
   - [interact_damage](functions-3.md#interact_damage)
   - [interact_breakable](functions-3.md#interact_breakable)
   - [interact_koopa_shell](functions-3.md#interact_koopa_shell)
   - [interact_pole](functions-3.md#interact_pole)
   - [interact_hoot](functions-3.md#interact_hoot)
   - [interact_cap](functions-3.md#interact_cap)
   - [interact_grabbable](functions-3.md#interact_grabbable)
   - [interact_text](functions-3.md#interact_text)
   - [mario_obj_angle_to_object](functions-3.md#mario_obj_angle_to_object)
   - [mario_stop_riding_object](functions-3.md#mario_stop_riding_object)
   - [mario_grab_used_object](functions-3.md#mario_grab_used_object)
   - [mario_drop_held_object](functions-3.md#mario_drop_held_object)
   - [mario_throw_held_object](functions-3.md#mario_throw_held_object)
   - [mario_stop_riding_and_holding](functions-3.md#mario_stop_riding_and_holding)
   - [does_mario_have_normal_cap_on_head](functions-3.md#does_mario_have_normal_cap_on_head)
   - [does_mario_have_blown_cap](functions-3.md#does_mario_have_blown_cap)
   - [mario_blow_off_cap](functions-3.md#mario_blow_off_cap)
   - [mario_lose_cap_to_enemy](functions-3.md#mario_lose_cap_to_enemy)
   - [mario_retrieve_cap](functions-3.md#mario_retrieve_cap)
   - [mario_get_collided_object](functions-3.md#mario_get_collided_object)
   - [mario_check_object_grab](functions-3.md#mario_check_object_grab)
   - [get_door_save_file_flag](functions-3.md#get_door_save_file_flag)
   - [passes_pvp_interaction_checks](functions-3.md#passes_pvp_interaction_checks)
   - [should_push_or_pull_door](functions-3.md#should_push_or_pull_door)
   - [take_damage_and_knock_back](functions-3.md#take_damage_and_knock_back)
   - [get_mario_cap_flag](functions-3.md#get_mario_cap_flag)
   - [determine_interaction](functions-3.md#determine_interaction)

<br />

- lag_compensation.h
   - [lag_compensation_store](functions-3.md#lag_compensation_store)
   - [lag_compensation_get_local_state](functions-3.md#lag_compensation_get_local_state)
   - [lag_compensation_get_local_state_ready](functions-3.md#lag_compensation_get_local_state_ready)
   - [lag_compensation_get_local_state_index](functions-3.md#lag_compensation_get_local_state_index)

<br />

- level_info.h
   - [get_level_name_ascii](functions-3.md#get_level_name_ascii)
   - [get_level_name_sm64](functions-3.md#get_level_name_sm64)
   - [get_level_name](functions-3.md#get_level_name)
   - [get_star_name_ascii](functions-3.md#get_star_name_ascii)
   - [get_star_name_sm64](functions-3.md#get_star_name_sm64)
   - [get_star_name](functions-3.md#get_star_name)

<br />

- level_script.h
   - [area_create_warp_node](functions-3.md#area_create_warp_node)

<br />

- level_update.h
   - [level_control_timer_running](functions-3.md#level_control_timer_running)
   - [fade_into_special_warp](functions-3.md#fade_into_special_warp)
   - [get_instant_warp](functions-3.md#get_instant_warp)
   - [get_painting_warp_node](functions-3.md#get_painting_warp_node)
   - [initiate_painting_warp](functions-3.md#initiate_painting_warp)
   - [level_trigger_warp](functions-3.md#level_trigger_warp)
   - [warp_special](functions-3.md#warp_special)
   - [lvl_set_current_level](functions-3.md#lvl_set_current_level)

<br />

- lighting_engine.h
   - [le_calculate_lighting_color](functions-3.md#le_calculate_lighting_color)
   - [le_calculate_lighting_dir](functions-3.md#le_calculate_lighting_dir)
   - [le_add_light](functions-3.md#le_add_light)
   - [le_remove_light](functions-3.md#le_remove_light)
   - [le_get_light_count](functions-3.md#le_get_light_count)
   - [le_set_ambient_color](functions-3.md#le_set_ambient_color)
   - [le_set_light_pos](functions-3.md#le_set_light_pos)
   - [le_set_light_color](functions-3.md#le_set_light_color)
   - [le_set_light_radius](functions-3.md#le_set_light_radius)
   - [le_set_light_intensity](functions-3.md#le_set_light_intensity)

<br />

- mario.h
   - [is_anim_at_end](functions-4.md#is_anim_at_end)
   - [is_anim_past_end](functions-4.md#is_anim_past_end)
   - [set_mario_animation](functions-4.md#set_mario_animation)
   - [set_mario_anim_with_accel](functions-4.md#set_mario_anim_with_accel)
   - [set_character_animation](functions-4.md#set_character_animation)
   - [set_character_anim_with_accel](functions-4.md#set_character_anim_with_accel)
   - [set_anim_to_frame](functions-4.md#set_anim_to_frame)
   - [is_anim_past_frame](functions-4.md#is_anim_past_frame)
   - [find_mario_anim_flags_and_translation](functions-4.md#find_mario_anim_flags_and_translation)
   - [update_mario_pos_for_anim](functions-4.md#update_mario_pos_for_anim)
   - [return_mario_anim_y_translation](functions-4.md#return_mario_anim_y_translation)
   - [play_sound_if_no_flag](functions-4.md#play_sound_if_no_flag)
   - [play_mario_jump_sound](functions-4.md#play_mario_jump_sound)
   - [adjust_sound_for_speed](functions-4.md#adjust_sound_for_speed)
   - [play_sound_and_spawn_particles](functions-4.md#play_sound_and_spawn_particles)
   - [play_mario_action_sound](functions-4.md#play_mario_action_sound)
   - [play_mario_landing_sound](functions-4.md#play_mario_landing_sound)
   - [play_mario_landing_sound_once](functions-4.md#play_mario_landing_sound_once)
   - [play_mario_heavy_landing_sound](functions-4.md#play_mario_heavy_landing_sound)
   - [play_mario_heavy_landing_sound_once](functions-4.md#play_mario_heavy_landing_sound_once)
   - [play_mario_sound](functions-4.md#play_mario_sound)
   - [mario_is_crouching](functions-4.md#mario_is_crouching)
   - [mario_is_ground_pound_landing](functions-4.md#mario_is_ground_pound_landing)
   - [mario_can_bubble](functions-4.md#mario_can_bubble)
   - [mario_set_bubbled](functions-4.md#mario_set_bubbled)
   - [mario_set_forward_vel](functions-4.md#mario_set_forward_vel)
   - [mario_get_floor_class](functions-4.md#mario_get_floor_class)
   - [mario_get_terrain_sound_addend](functions-4.md#mario_get_terrain_sound_addend)
   - [resolve_and_return_wall_collisions](functions-4.md#resolve_and_return_wall_collisions)
   - [resolve_and_return_wall_collisions_data](functions-4.md#resolve_and_return_wall_collisions_data)
   - [mario_facing_downhill](functions-4.md#mario_facing_downhill)
   - [mario_floor_is_slippery](functions-4.md#mario_floor_is_slippery)
   - [mario_floor_is_slope](functions-4.md#mario_floor_is_slope)
   - [mario_floor_is_steep](functions-4.md#mario_floor_is_steep)
   - [find_floor_height_relative_polar](functions-4.md#find_floor_height_relative_polar)
   - [find_floor_slope](functions-4.md#find_floor_slope)
   - [update_mario_sound_and_camera](functions-4.md#update_mario_sound_and_camera)
   - [set_steep_jump_action](functions-4.md#set_steep_jump_action)
   - [set_mario_y_vel_based_on_fspeed](functions-4.md#set_mario_y_vel_based_on_fspeed)
   - [set_mario_action](functions-4.md#set_mario_action)
   - [set_jump_from_landing](functions-4.md#set_jump_from_landing)
   - [set_jumping_action](functions-4.md#set_jumping_action)
   - [drop_and_set_mario_action](functions-4.md#drop_and_set_mario_action)
   - [hurt_and_set_mario_action](functions-4.md#hurt_and_set_mario_action)
   - [check_common_action_exits](functions-4.md#check_common_action_exits)
   - [check_common_hold_action_exits](functions-4.md#check_common_hold_action_exits)
   - [transition_submerged_to_walking](functions-4.md#transition_submerged_to_walking)
   - [set_water_plunge_action](functions-4.md#set_water_plunge_action)
   - [execute_mario_action](functions-4.md#execute_mario_action)
   - [force_idle_state](functions-4.md#force_idle_state)
   - [init_single_mario](functions-4.md#init_single_mario)
   - [set_mario_particle_flags](functions-4.md#set_mario_particle_flags)
   - [mario_update_wall](functions-4.md#mario_update_wall)
   - [get_mario_state_from_object](functions-4.md#get_mario_state_from_object)

<br />

- mario_actions_airborne.c
   - [play_flip_sounds](functions-4.md#play_flip_sounds)
   - [play_far_fall_sound](functions-4.md#play_far_fall_sound)
   - [play_knockback_sound](functions-4.md#play_knockback_sound)
   - [lava_boost_on_wall](functions-4.md#lava_boost_on_wall)
   - [check_fall_damage](functions-4.md#check_fall_damage)
   - [check_kick_or_dive_in_air](functions-4.md#check_kick_or_dive_in_air)
   - [should_get_stuck_in_ground](functions-4.md#should_get_stuck_in_ground)
   - [check_fall_damage_or_get_stuck](functions-4.md#check_fall_damage_or_get_stuck)
   - [check_horizontal_wind](functions-4.md#check_horizontal_wind)
   - [update_air_with_turn](functions-4.md#update_air_with_turn)
   - [update_air_without_turn](functions-4.md#update_air_without_turn)
   - [update_lava_boost_or_twirling](functions-4.md#update_lava_boost_or_twirling)
   - [update_flying_yaw](functions-4.md#update_flying_yaw)
   - [update_flying_pitch](functions-4.md#update_flying_pitch)
   - [update_flying](functions-4.md#update_flying)
   - [common_air_action_step](functions-4.md#common_air_action_step)
   - [common_air_knockback_step](functions-4.md#common_air_knockback_step)
   - [check_wall_kick](functions-4.md#check_wall_kick)
   - [check_common_airborne_cancels](functions-4.md#check_common_airborne_cancels)
   - [mario_execute_airborne_action](functions-4.md#mario_execute_airborne_action)

<br />

- mario_actions_automatic.c
   - [add_tree_leaf_particles](functions-4.md#add_tree_leaf_particles)
   - [play_climbing_sounds](functions-4.md#play_climbing_sounds)
   - [set_pole_position](functions-4.md#set_pole_position)
   - [perform_hanging_step](functions-4.md#perform_hanging_step)
   - [update_hang_moving](functions-4.md#update_hang_moving)
   - [update_hang_stationary](functions-4.md#update_hang_stationary)
   - [let_go_of_ledge](functions-4.md#let_go_of_ledge)
   - [climb_up_ledge](functions-4.md#climb_up_ledge)
   - [update_ledge_climb_camera](functions-4.md#update_ledge_climb_camera)
   - [update_ledge_climb](functions-4.md#update_ledge_climb)
   - [mario_pop_bubble](functions-4.md#mario_pop_bubble)
   - [check_common_automatic_cancels](functions-4.md#check_common_automatic_cancels)
   - [mario_execute_automatic_action](functions-4.md#mario_execute_automatic_action)

<br />

- mario_actions_cutscene.c
   - [get_credits_str_width](functions-4.md#get_credits_str_width)
   - [bhv_end_peach_loop](functions-4.md#bhv_end_peach_loop)
   - [bhv_end_toad_loop](functions-4.md#bhv_end_toad_loop)
   - [get_star_collection_dialog](functions-4.md#get_star_collection_dialog)
   - [handle_save_menu](functions-4.md#handle_save_menu)
   - [cutscene_take_cap_off](functions-4.md#cutscene_take_cap_off)
   - [cutscene_put_cap_on](functions-4.md#cutscene_put_cap_on)
   - [mario_ready_to_speak](functions-4.md#mario_ready_to_speak)
   - [should_start_or_continue_dialog](functions-4.md#should_start_or_continue_dialog)
   - [general_star_dance_handler](functions-4.md#general_star_dance_handler)
   - [common_death_handler](functions-4.md#common_death_handler)
   - [launch_mario_until_land](functions-4.md#launch_mario_until_land)
   - [stuck_in_ground_handler](functions-4.md#stuck_in_ground_handler)
   - [generate_yellow_sparkles](functions-4.md#generate_yellow_sparkles)
   - [mario_execute_cutscene_action](functions-4.md#mario_execute_cutscene_action)

<br />

- mario_actions_moving.c
   - [tilt_body_running](functions-4.md#tilt_body_running)
   - [play_step_sound](functions-4.md#play_step_sound)
   - [align_with_floor](functions-4.md#align_with_floor)
   - [begin_walking_action](functions-4.md#begin_walking_action)
   - [check_ledge_climb_down](functions-4.md#check_ledge_climb_down)
   - [slide_bonk](functions-4.md#slide_bonk)
   - [set_triple_jump_action](functions-4.md#set_triple_jump_action)
   - [update_sliding_angle](functions-4.md#update_sliding_angle)
   - [update_sliding](functions-4.md#update_sliding)
   - [apply_slope_accel](functions-4.md#apply_slope_accel)
   - [apply_landing_accel](functions-4.md#apply_landing_accel)
   - [update_shell_speed](functions-4.md#update_shell_speed)
   - [apply_slope_decel](functions-4.md#apply_slope_decel)
   - [update_decelerating_speed](functions-4.md#update_decelerating_speed)
   - [update_walking_speed](functions-4.md#update_walking_speed)
   - [should_begin_sliding](functions-4.md#should_begin_sliding)
   - [analog_stick_held_back](functions-4.md#analog_stick_held_back)
   - [check_ground_dive_or_punch](functions-4.md#check_ground_dive_or_punch)
   - [begin_braking_action](functions-4.md#begin_braking_action)
   - [anim_and_audio_for_walk](functions-4.md#anim_and_audio_for_walk)
   - [anim_and_audio_for_hold_walk](functions-4.md#anim_and_audio_for_hold_walk)
   - [anim_and_audio_for_heavy_walk](functions-4.md#anim_and_audio_for_heavy_walk)
   - [push_or_sidle_wall](functions-4.md#push_or_sidle_wall)
   - [tilt_body_walking](functions-4.md#tilt_body_walking)
   - [tilt_body_ground_shell](functions-4.md#tilt_body_ground_shell)
   - [tilt_body_butt_slide](functions-4.md#tilt_body_butt_slide)
   - [common_slide_action](functions-4.md#common_slide_action)
   - [common_slide_action_with_jump](functions-4.md#common_slide_action_with_jump)
   - [stomach_slide_action](functions-4.md#stomach_slide_action)
   - [common_ground_knockback_action](functions-4.md#common_ground_knockback_action)
   - [common_landing_action](functions-4.md#common_landing_action)
   - [quicksand_jump_land_action](functions-4.md#quicksand_jump_land_action)
   - [check_common_moving_cancels](functions-4.md#check_common_moving_cancels)
   - [mario_execute_moving_action](functions-4.md#mario_execute_moving_action)

<br />

- mario_actions_object.c
   - [animated_stationary_ground_step](functions-4.md#animated_stationary_ground_step)
   - [mario_update_punch_sequence](functions-4.md#mario_update_punch_sequence)
   - [check_common_object_cancels](functions-4.md#check_common_object_cancels)
   - [mario_execute_object_action](functions-4.md#mario_execute_object_action)

<br />

- mario_actions_stationary.c
   - [check_common_idle_cancels](functions-4.md#check_common_idle_cancels)
   - [check_common_hold_idle_cancels](functions-4.md#check_common_hold_idle_cancels)
   - [play_anim_sound](functions-4.md#play_anim_sound)
   - [stopping_step](functions-4.md#stopping_step)
   - [landing_step](functions-4.md#landing_step)
   - [check_common_landing_cancels](functions-4.md#check_common_landing_cancels)
   - [check_common_stationary_cancels](functions-4.md#check_common_stationary_cancels)
   - [mario_execute_stationary_action](functions-4.md#mario_execute_stationary_action)

<br />

- mario_actions_submerged.c
   - [set_swimming_at_surface_particles](functions-4.md#set_swimming_at_surface_particles)
   - [perform_water_full_step](functions-4.md#perform_water_full_step)
   - [apply_water_current](functions-4.md#apply_water_current)
   - [perform_water_step](functions-4.md#perform_water_step)
   - [float_surface_gfx](functions-4.md#float_surface_gfx)
   - [mario_execute_submerged_action](functions-4.md#mario_execute_submerged_action)

<br />

- mario_misc.h
   - [bhv_toad_message_init](functions-4.md#bhv_toad_message_init)
   - [bhv_toad_message_loop](functions-4.md#bhv_toad_message_loop)
   - [bhv_unlock_door_star_init](functions-4.md#bhv_unlock_door_star_init)
   - [bhv_unlock_door_star_loop](functions-4.md#bhv_unlock_door_star_loop)
   - [geo_get_mario_state](functions-4.md#geo_get_mario_state)
   - [geo_get_body_state](functions-4.md#geo_get_body_state)

<br />

- mario_step.h
   - [get_additive_y_vel_for_jumps](functions-4.md#get_additive_y_vel_for_jumps)
   - [mario_bonk_reflection](functions-4.md#mario_bonk_reflection)
   - [init_bully_collision_data](functions-4.md#init_bully_collision_data)
   - [mario_update_quicksand](functions-4.md#mario_update_quicksand)
   - [mario_push_off_steep_floor](functions-4.md#mario_push_off_steep_floor)
   - [mario_update_moving_sand](functions-4.md#mario_update_moving_sand)
   - [mario_update_windy_ground](functions-4.md#mario_update_windy_ground)
   - [stop_and_set_height_to_floor](functions-4.md#stop_and_set_height_to_floor)
   - [stationary_ground_step](functions-4.md#stationary_ground_step)
   - [perform_ground_step](functions-4.md#perform_ground_step)
   - [perform_air_step](functions-4.md#perform_air_step)
   - [set_vel_from_pitch_and_yaw](functions-4.md#set_vel_from_pitch_and_yaw)

<br />

- math_util.h
   - [sins](functions-4.md#sins)
   - [coss](functions-4.md#coss)
   - [atan2s](functions-4.md#atan2s)
   - [atan2f](functions-4.md#atan2f)
   - [approach_s32](functions-4.md#approach_s32)
   - [approach_f32](functions-4.md#approach_f32)
   - [spline_get_weights](functions-4.md#spline_get_weights)
   - [anim_spline_init](functions-4.md#anim_spline_init)
   - [anim_spline_poll](functions-4.md#anim_spline_poll)
   - [vec3f_rotate_zxy](functions-4.md#vec3f_rotate_zxy)
   - [vec3f_rotate_around_n](functions-4.md#vec3f_rotate_around_n)
   - [vec3f_project](functions-4.md#vec3f_project)
   - [vec3f_transform](functions-4.md#vec3f_transform)
   - [vec3f_get_dist_and_angle](functions-4.md#vec3f_get_dist_and_angle)
   - [vec3f_set_dist_and_angle](functions-4.md#vec3f_set_dist_and_angle)
   - [find_vector_perpendicular_to_plane](functions-4.md#find_vector_perpendicular_to_plane)
   - [mtxf_lookat](functions-4.md#mtxf_lookat)
   - [mtxf_rotate_zxy_and_translate](functions-4.md#mtxf_rotate_zxy_and_translate)
   - [mtxf_rotate_xyz_and_translate](functions-4.md#mtxf_rotate_xyz_and_translate)
   - [mtxf_billboard](functions-4.md#mtxf_billboard)
   - [mtxf_cylboard](functions-4.md#mtxf_cylboard)
   - [mtxf_align_terrain_normal](functions-4.md#mtxf_align_terrain_normal)
   - [mtxf_align_terrain_triangle](functions-4.md#mtxf_align_terrain_triangle)
   - [mtxf_mul](functions-4.md#mtxf_mul)
   - [mtxf_mul_vec3s](functions-4.md#mtxf_mul_vec3s)
   - [mtxf_rotate_xy](functions-4.md#mtxf_rotate_xy)
   - [mtxf_inverse](functions-4.md#mtxf_inverse)
   - [get_pos_from_transform_mtx](functions-4.md#get_pos_from_transform_mtx)

<br />

- math_util.inl
   - [replace_value_if_not_zero](functions-4.md#replace_value_if_not_zero)
   - [sm64_to_radians](functions-4.md#sm64_to_radians)
   - [radians_to_sm64](functions-4.md#radians_to_sm64)
   - [sm64_to_degrees](functions-4.md#sm64_to_degrees)
   - [degrees_to_sm64](functions-4.md#degrees_to_sm64)

<br />

- math_util_mat4.inl
   - [mtxf_zero](functions-4.md#mtxf_zero)
   - [mtxf_copy](functions-4.md#mtxf_copy)
   - [mtxf_identity](functions-4.md#mtxf_identity)
   - [mtxf_translate](functions-4.md#mtxf_translate)
   - [mtxf_scale_vec3f](functions-4.md#mtxf_scale_vec3f)

<br />

- math_util_vec3f.inl
   - [vec3f_zero](functions-4.md#vec3f_zero)
   - [vec3f_copy](functions-4.md#vec3f_copy)
   - [vec3f_set](functions-4.md#vec3f_set)
   - [vec3f_add](functions-4.md#vec3f_add)
   - [vec3f_sum](functions-4.md#vec3f_sum)
   - [vec3f_sub](functions-4.md#vec3f_sub)
   - [vec3f_dif](functions-4.md#vec3f_dif)
   - [vec3f_mul](functions-4.md#vec3f_mul)
   - [vec3f_mult](functions-4.md#vec3f_mult)
   - [vec3f_prod](functions-4.md#vec3f_prod)
   - [vec3f_div](functions-4.md#vec3f_div)
   - [vec3f_length](functions-4.md#vec3f_length)
   - [vec3f_normalize](functions-4.md#vec3f_normalize)
   - [vec3f_set_magnitude](functions-4.md#vec3f_set_magnitude)
   - [vec3f_dot](functions-4.md#vec3f_dot)
   - [vec3f_cross](functions-4.md#vec3f_cross)
   - [vec3f_combine](functions-4.md#vec3f_combine)
   - [vec3f_dist](functions-4.md#vec3f_dist)
   - [vec3f_hdist](functions-4.md#vec3f_hdist)
   - [vec3f_is_zero](functions-4.md#vec3f_is_zero)
   - [vec3f_to_vec3i](functions-4.md#vec3f_to_vec3i)
   - [vec3f_to_vec3s](functions-4.md#vec3f_to_vec3s)

<br />

- math_util_vec3i.inl
   - [vec3i_zero](functions-4.md#vec3i_zero)
   - [vec3i_copy](functions-4.md#vec3i_copy)
   - [vec3i_set](functions-4.md#vec3i_set)
   - [vec3i_add](functions-4.md#vec3i_add)
   - [vec3i_sum](functions-4.md#vec3i_sum)
   - [vec3i_sub](functions-4.md#vec3i_sub)
   - [vec3i_dif](functions-4.md#vec3i_dif)
   - [vec3i_mul](functions-4.md#vec3i_mul)
   - [vec3i_mult](functions-4.md#vec3i_mult)
   - [vec3i_prod](functions-4.md#vec3i_prod)
   - [vec3i_div](functions-4.md#vec3i_div)
   - [vec3i_length](functions-4.md#vec3i_length)
   - [vec3i_normalize](functions-4.md#vec3i_normalize)
   - [vec3i_set_magnitude](functions-4.md#vec3i_set_magnitude)
   - [vec3i_dot](functions-4.md#vec3i_dot)
   - [vec3i_cross](functions-4.md#vec3i_cross)
   - [vec3i_combine](functions-4.md#vec3i_combine)
   - [vec3i_dist](functions-4.md#vec3i_dist)
   - [vec3i_hdist](functions-4.md#vec3i_hdist)
   - [vec3i_is_zero](functions-4.md#vec3i_is_zero)
   - [vec3i_to_vec3f](functions-4.md#vec3i_to_vec3f)
   - [vec3i_to_vec3s](functions-4.md#vec3i_to_vec3s)

<br />

- math_util_vec3s.inl
   - [vec3s_zero](functions-4.md#vec3s_zero)
   - [vec3s_copy](functions-4.md#vec3s_copy)
   - [vec3s_set](functions-4.md#vec3s_set)
   - [vec3s_add](functions-4.md#vec3s_add)
   - [vec3s_sum](functions-4.md#vec3s_sum)
   - [vec3s_sub](functions-4.md#vec3s_sub)
   - [vec3s_dif](functions-4.md#vec3s_dif)
   - [vec3s_mul](functions-4.md#vec3s_mul)
   - [vec3s_mult](functions-4.md#vec3s_mult)
   - [vec3s_prod](functions-4.md#vec3s_prod)
   - [vec3s_div](functions-4.md#vec3s_div)
   - [vec3s_length](functions-4.md#vec3s_length)
   - [vec3s_normalize](functions-4.md#vec3s_normalize)
   - [vec3s_set_magnitude](functions-4.md#vec3s_set_magnitude)
   - [vec3s_dot](functions-4.md#vec3s_dot)
   - [vec3s_cross](functions-4.md#vec3s_cross)
   - [vec3s_combine](functions-4.md#vec3s_combine)
   - [vec3s_dist](functions-4.md#vec3s_dist)
   - [vec3s_hdist](functions-4.md#vec3s_hdist)
   - [vec3s_is_zero](functions-4.md#vec3s_is_zero)
   - [vec3s_to_vec3f](functions-4.md#vec3s_to_vec3f)
   - [vec3s_to_vec3i](functions-4.md#vec3s_to_vec3i)

<br />

- misc.h
   - [smooth_step](functions-5.md#smooth_step)
   - [update_all_mario_stars](functions-5.md#update_all_mario_stars)
   - [clock_elapsed](functions-5.md#clock_elapsed)
   - [clock_elapsed_f64](functions-5.md#clock_elapsed_f64)
   - [clock_elapsed_ticks](functions-5.md#clock_elapsed_ticks)
   - [clock_is_date](functions-5.md#clock_is_date)
   - [delta_interpolate_f32](functions-5.md#delta_interpolate_f32)
   - [delta_interpolate_s32](functions-5.md#delta_interpolate_s32)
   - [delta_interpolate_vec3f](functions-5.md#delta_interpolate_vec3f)
   - [delta_interpolate_vec3s](functions-5.md#delta_interpolate_vec3s)

<br />

- mod_storage.h
   - [mod_storage_save](functions-5.md#mod_storage_save)
   - [mod_storage_save_number](functions-5.md#mod_storage_save_number)
   - [mod_storage_save_bool](functions-5.md#mod_storage_save_bool)
   - [mod_storage_load](functions-5.md#mod_storage_load)
   - [mod_storage_load_number](functions-5.md#mod_storage_load_number)
   - [mod_storage_load_bool](functions-5.md#mod_storage_load_bool)
   - [mod_storage_exists](functions-5.md#mod_storage_exists)
   - [mod_storage_remove](functions-5.md#mod_storage_remove)
   - [mod_storage_clear](functions-5.md#mod_storage_clear)

<br />

- network_player.h
   - [network_player_connected_count](functions-5.md#network_player_connected_count)
   - [network_player_set_description](functions-5.md#network_player_set_description)
   - [network_player_set_override_location](functions-5.md#network_player_set_override_location)
   - [network_player_from_global_index](functions-5.md#network_player_from_global_index)
   - [get_network_player_from_level](functions-5.md#get_network_player_from_level)
   - [get_network_player_from_area](functions-5.md#get_network_player_from_area)
   - [get_network_player_smallest_global](functions-5.md#get_network_player_smallest_global)
   - [network_player_set_override_palette_color](functions-5.md#network_player_set_override_palette_color)
   - [network_player_reset_override_palette](functions-5.md#network_player_reset_override_palette)
   - [network_player_is_override_palette_same](functions-5.md#network_player_is_override_palette_same)

<br />

- network_utils.h
   - [network_global_index_from_local](functions-5.md#network_global_index_from_local)
   - [network_local_index_from_global](functions-5.md#network_local_index_from_global)
   - [network_is_server](functions-5.md#network_is_server)
   - [network_is_moderator](functions-5.md#network_is_moderator)
   - [network_get_player_text_color_string](functions-5.md#network_get_player_text_color_string)
   - [network_check_singleplayer_pause](functions-5.md#network_check_singleplayer_pause)
   - [network_discord_id_from_local_index](functions-5.md#network_discord_id_from_local_index)

<br />

- obj_behaviors.c
   - [set_yoshi_as_not_dead](functions-5.md#set_yoshi_as_not_dead)
   - [absf_2](functions-5.md#absf_2)
   - [obj_find_wall](functions-5.md#obj_find_wall)
   - [turn_obj_away_from_steep_floor](functions-5.md#turn_obj_away_from_steep_floor)
   - [obj_orient_graph](functions-5.md#obj_orient_graph)
   - [calc_obj_friction](functions-5.md#calc_obj_friction)
   - [calc_new_obj_vel_and_pos_y](functions-5.md#calc_new_obj_vel_and_pos_y)
   - [calc_new_obj_vel_and_pos_y_underwater](functions-5.md#calc_new_obj_vel_and_pos_y_underwater)
   - [obj_update_pos_vel_xz](functions-5.md#obj_update_pos_vel_xz)
   - [obj_splash](functions-5.md#obj_splash)
   - [object_step](functions-5.md#object_step)
   - [object_step_without_floor_orient](functions-5.md#object_step_without_floor_orient)
   - [obj_move_xyz_using_fvel_and_yaw](functions-5.md#obj_move_xyz_using_fvel_and_yaw)
   - [is_point_within_radius_of_mario](functions-5.md#is_point_within_radius_of_mario)
   - [is_point_within_radius_of_any_player](functions-5.md#is_point_within_radius_of_any_player)
   - [is_player_active](functions-5.md#is_player_active)
   - [is_other_player_active](functions-5.md#is_other_player_active)
   - [is_player_in_local_area](functions-5.md#is_player_in_local_area)
   - [nearest_mario_state_to_object](functions-5.md#nearest_mario_state_to_object)
   - [nearest_possible_mario_state_to_object](functions-5.md#nearest_possible_mario_state_to_object)
   - [nearest_player_to_object](functions-5.md#nearest_player_to_object)
   - [nearest_interacting_mario_state_to_object](functions-5.md#nearest_interacting_mario_state_to_object)
   - [nearest_interacting_player_to_object](functions-5.md#nearest_interacting_player_to_object)
   - [is_nearest_mario_state_to_object](functions-5.md#is_nearest_mario_state_to_object)
   - [is_nearest_player_to_object](functions-5.md#is_nearest_player_to_object)
   - [is_point_close_to_object](functions-5.md#is_point_close_to_object)
   - [set_object_visibility](functions-5.md#set_object_visibility)
   - [obj_return_home_if_safe](functions-5.md#obj_return_home_if_safe)
   - [obj_return_and_displace_home](functions-5.md#obj_return_and_displace_home)
   - [obj_check_if_facing_toward_angle](functions-5.md#obj_check_if_facing_toward_angle)
   - [obj_find_wall_displacement](functions-5.md#obj_find_wall_displacement)
   - [obj_spawn_yellow_coins](functions-5.md#obj_spawn_yellow_coins)
   - [obj_flicker_and_disappear](functions-5.md#obj_flicker_and_disappear)
   - [current_mario_room_check](functions-5.md#current_mario_room_check)
   - [obj_check_floor_death](functions-5.md#obj_check_floor_death)
   - [obj_lava_death](functions-5.md#obj_lava_death)
   - [spawn_orange_number](functions-5.md#spawn_orange_number)

<br />

- obj_behaviors_2.c
   - [obj_is_rendering_enabled](functions-5.md#obj_is_rendering_enabled)
   - [obj_get_pitch_from_vel](functions-5.md#obj_get_pitch_from_vel)
   - [obj_set_dist_from_home](functions-5.md#obj_set_dist_from_home)
   - [obj_is_near_to_and_facing_mario](functions-5.md#obj_is_near_to_and_facing_mario)
   - [platform_on_track_update_pos_or_spawn_ball](functions-5.md#platform_on_track_update_pos_or_spawn_ball)
   - [cur_obj_spin_all_dimensions](functions-5.md#cur_obj_spin_all_dimensions)
   - [obj_rotate_yaw_and_bounce_off_walls](functions-5.md#obj_rotate_yaw_and_bounce_off_walls)
   - [obj_get_pitch_to_home](functions-5.md#obj_get_pitch_to_home)
   - [obj_compute_vel_from_move_pitch](functions-5.md#obj_compute_vel_from_move_pitch)
   - [cur_obj_init_anim_extend](functions-5.md#cur_obj_init_anim_extend)
   - [cur_obj_init_anim_and_check_if_end](functions-5.md#cur_obj_init_anim_and_check_if_end)
   - [cur_obj_init_anim_check_frame](functions-5.md#cur_obj_init_anim_check_frame)
   - [cur_obj_set_anim_if_at_end](functions-5.md#cur_obj_set_anim_if_at_end)
   - [cur_obj_play_sound_at_anim_range](functions-5.md#cur_obj_play_sound_at_anim_range)
   - [obj_turn_pitch_toward_mario](functions-5.md#obj_turn_pitch_toward_mario)
   - [approach_f32_ptr](functions-5.md#approach_f32_ptr)
   - [obj_forward_vel_approach](functions-5.md#obj_forward_vel_approach)
   - [obj_y_vel_approach](functions-5.md#obj_y_vel_approach)
   - [obj_move_pitch_approach](functions-5.md#obj_move_pitch_approach)
   - [obj_face_pitch_approach](functions-5.md#obj_face_pitch_approach)
   - [obj_face_yaw_approach](functions-5.md#obj_face_yaw_approach)
   - [obj_face_roll_approach](functions-5.md#obj_face_roll_approach)
   - [obj_smooth_turn](functions-5.md#obj_smooth_turn)
   - [obj_roll_to_match_yaw_turn](functions-5.md#obj_roll_to_match_yaw_turn)
   - [random_linear_offset](functions-5.md#random_linear_offset)
   - [random_mod_offset](functions-5.md#random_mod_offset)
   - [obj_random_fixed_turn](functions-5.md#obj_random_fixed_turn)
   - [obj_grow_then_shrink](functions-5.md#obj_grow_then_shrink)
   - [oscillate_toward](functions-5.md#oscillate_toward)
   - [obj_update_blinking](functions-5.md#obj_update_blinking)
   - [obj_resolve_object_collisions](functions-5.md#obj_resolve_object_collisions)
   - [obj_bounce_off_walls_edges_objects](functions-5.md#obj_bounce_off_walls_edges_objects)
   - [obj_resolve_collisions_and_turn](functions-5.md#obj_resolve_collisions_and_turn)
   - [obj_die_if_health_non_positive](functions-5.md#obj_die_if_health_non_positive)
   - [obj_unused_die](functions-5.md#obj_unused_die)
   - [obj_set_knockback_action](functions-5.md#obj_set_knockback_action)
   - [obj_set_squished_action](functions-5.md#obj_set_squished_action)
   - [obj_die_if_above_lava_and_health_non_positive](functions-5.md#obj_die_if_above_lava_and_health_non_positive)
   - [obj_handle_attacks](functions-5.md#obj_handle_attacks)
   - [obj_act_knockback](functions-5.md#obj_act_knockback)
   - [obj_act_squished](functions-5.md#obj_act_squished)
   - [obj_update_standard_actions](functions-5.md#obj_update_standard_actions)
   - [obj_check_attacks](functions-5.md#obj_check_attacks)
   - [obj_move_for_one_second](functions-5.md#obj_move_for_one_second)
   - [treat_far_home_as_mario](functions-5.md#treat_far_home_as_mario)
   - [obj_spit_fire](functions-5.md#obj_spit_fire)

<br />

- object_helpers.c
   - [clear_move_flag](functions-5.md#clear_move_flag)
   - [set_room_override](functions-5.md#set_room_override)
   - [obj_update_pos_from_parent_transformation](functions-5.md#obj_update_pos_from_parent_transformation)
   - [obj_apply_scale_to_matrix](functions-5.md#obj_apply_scale_to_matrix)
   - [create_transformation_from_matrices](functions-5.md#create_transformation_from_matrices)
   - [obj_set_held_state](functions-5.md#obj_set_held_state)
   - [lateral_dist_between_objects](functions-5.md#lateral_dist_between_objects)
   - [dist_between_objects](functions-5.md#dist_between_objects)
   - [dist_between_object_and_point](functions-5.md#dist_between_object_and_point)
   - [cur_obj_forward_vel_approach_upward](functions-5.md#cur_obj_forward_vel_approach_upward)
   - [approach_f32_signed](functions-5.md#approach_f32_signed)
   - [approach_f32_symmetric](functions-5.md#approach_f32_symmetric)
   - [approach_s16_symmetric](functions-5.md#approach_s16_symmetric)
   - [cur_obj_rotate_yaw_toward](functions-5.md#cur_obj_rotate_yaw_toward)
   - [obj_angle_to_object](functions-5.md#obj_angle_to_object)
   - [obj_pitch_to_object](functions-5.md#obj_pitch_to_object)
   - [obj_angle_to_point](functions-5.md#obj_angle_to_point)
   - [obj_turn_toward_object](functions-5.md#obj_turn_toward_object)
   - [obj_set_parent_relative_pos](functions-5.md#obj_set_parent_relative_pos)
   - [obj_set_pos](functions-5.md#obj_set_pos)
   - [obj_set_angle](functions-5.md#obj_set_angle)
   - [obj_set_move_angle](functions-5.md#obj_set_move_angle)
   - [obj_set_face_angle](functions-5.md#obj_set_face_angle)
   - [obj_set_gfx_angle](functions-5.md#obj_set_gfx_angle)
   - [obj_set_gfx_pos](functions-5.md#obj_set_gfx_pos)
   - [obj_set_gfx_scale](functions-5.md#obj_set_gfx_scale)
   - [spawn_water_droplet](functions-5.md#spawn_water_droplet)
   - [obj_build_relative_transform](functions-5.md#obj_build_relative_transform)
   - [cur_obj_move_using_vel](functions-5.md#cur_obj_move_using_vel)
   - [obj_copy_graph_y_offset](functions-5.md#obj_copy_graph_y_offset)
   - [obj_copy_pos_and_angle](functions-5.md#obj_copy_pos_and_angle)
   - [obj_copy_pos](functions-5.md#obj_copy_pos)
   - [obj_copy_angle](functions-5.md#obj_copy_angle)
   - [obj_set_gfx_pos_from_pos](functions-5.md#obj_set_gfx_pos_from_pos)
   - [obj_init_animation](functions-5.md#obj_init_animation)
   - [linear_mtxf_mul_vec3f](functions-5.md#linear_mtxf_mul_vec3f)
   - [linear_mtxf_transpose_mul_vec3f](functions-5.md#linear_mtxf_transpose_mul_vec3f)
   - [obj_apply_scale_to_transform](functions-5.md#obj_apply_scale_to_transform)
   - [obj_copy_scale](functions-5.md#obj_copy_scale)
   - [obj_scale_xyz](functions-5.md#obj_scale_xyz)
   - [obj_scale](functions-5.md#obj_scale)
   - [cur_obj_scale](functions-5.md#cur_obj_scale)
   - [cur_obj_init_animation](functions-5.md#cur_obj_init_animation)
   - [cur_obj_init_animation_with_sound](functions-5.md#cur_obj_init_animation_with_sound)
   - [obj_init_animation_with_accel_and_sound](functions-5.md#obj_init_animation_with_accel_and_sound)
   - [cur_obj_init_animation_with_accel_and_sound](functions-5.md#cur_obj_init_animation_with_accel_and_sound)
   - [obj_init_animation_with_sound](functions-5.md#obj_init_animation_with_sound)
   - [cur_obj_enable_rendering_and_become_tangible](functions-5.md#cur_obj_enable_rendering_and_become_tangible)
   - [cur_obj_enable_rendering](functions-5.md#cur_obj_enable_rendering)
   - [cur_obj_disable_rendering_and_become_intangible](functions-5.md#cur_obj_disable_rendering_and_become_intangible)
   - [cur_obj_disable_rendering](functions-5.md#cur_obj_disable_rendering)
   - [cur_obj_unhide](functions-5.md#cur_obj_unhide)
   - [cur_obj_hide](functions-5.md#cur_obj_hide)
   - [cur_obj_set_pos_relative](functions-5.md#cur_obj_set_pos_relative)
   - [cur_obj_set_pos_relative_to_parent](functions-5.md#cur_obj_set_pos_relative_to_parent)
   - [cur_obj_enable_rendering_2](functions-5.md#cur_obj_enable_rendering_2)
   - [cur_obj_unused_init_on_floor](functions-5.md#cur_obj_unused_init_on_floor)
   - [obj_set_face_angle_to_move_angle](functions-5.md#obj_set_face_angle_to_move_angle)
   - [get_object_list_from_behavior](functions-5.md#get_object_list_from_behavior)
   - [cur_obj_nearest_object_with_behavior](functions-5.md#cur_obj_nearest_object_with_behavior)
   - [cur_obj_dist_to_nearest_object_with_behavior](functions-5.md#cur_obj_dist_to_nearest_object_with_behavior)
   - [cur_obj_find_nearest_pole](functions-5.md#cur_obj_find_nearest_pole)
   - [cur_obj_find_nearest_object_with_behavior](functions-5.md#cur_obj_find_nearest_object_with_behavior)
   - [cur_obj_count_objects_with_behavior](functions-5.md#cur_obj_count_objects_with_behavior)
   - [find_unimportant_object](functions-5.md#find_unimportant_object)
   - [count_unimportant_objects](functions-5.md#count_unimportant_objects)
   - [count_objects_with_behavior](functions-5.md#count_objects_with_behavior)
   - [find_object_with_behavior](functions-5.md#find_object_with_behavior)
   - [cur_obj_find_nearby_held_actor](functions-5.md#cur_obj_find_nearby_held_actor)
   - [cur_obj_reset_timer_and_subaction](functions-5.md#cur_obj_reset_timer_and_subaction)
   - [cur_obj_change_action](functions-5.md#cur_obj_change_action)
   - [cur_obj_set_vel_from_mario_vel](functions-5.md#cur_obj_set_vel_from_mario_vel)
   - [cur_obj_reverse_animation](functions-5.md#cur_obj_reverse_animation)
   - [cur_obj_extend_animation_if_at_end](functions-5.md#cur_obj_extend_animation_if_at_end)
   - [cur_obj_check_if_near_animation_end](functions-5.md#cur_obj_check_if_near_animation_end)
   - [cur_obj_check_if_at_animation_end](functions-5.md#cur_obj_check_if_at_animation_end)
   - [cur_obj_check_anim_frame](functions-5.md#cur_obj_check_anim_frame)
   - [cur_obj_check_anim_frame_in_range](functions-5.md#cur_obj_check_anim_frame_in_range)
   - [cur_obj_check_frame_prior_current_frame](functions-5.md#cur_obj_check_frame_prior_current_frame)
   - [mario_is_in_air_action](functions-5.md#mario_is_in_air_action)
   - [mario_is_dive_sliding](functions-5.md#mario_is_dive_sliding)
   - [cur_obj_set_y_vel_and_animation](functions-5.md#cur_obj_set_y_vel_and_animation)
   - [cur_obj_unrender_and_reset_state](functions-5.md#cur_obj_unrender_and_reset_state)
   - [cur_obj_move_after_thrown_or_dropped](functions-5.md#cur_obj_move_after_thrown_or_dropped)
   - [cur_obj_get_thrown_or_placed](functions-5.md#cur_obj_get_thrown_or_placed)
   - [cur_obj_get_dropped](functions-5.md#cur_obj_get_dropped)
   - [mario_set_flag](functions-5.md#mario_set_flag)
   - [cur_obj_clear_interact_status_flag](functions-5.md#cur_obj_clear_interact_status_flag)
   - [obj_mark_for_deletion](functions-5.md#obj_mark_for_deletion)
   - [cur_obj_disable](functions-5.md#cur_obj_disable)
   - [cur_obj_become_intangible](functions-5.md#cur_obj_become_intangible)
   - [cur_obj_become_tangible](functions-5.md#cur_obj_become_tangible)
   - [obj_become_tangible](functions-5.md#obj_become_tangible)
   - [cur_obj_update_floor_height](functions-5.md#cur_obj_update_floor_height)
   - [cur_obj_update_floor_height_and_get_floor](functions-5.md#cur_obj_update_floor_height_and_get_floor)
   - [apply_drag_to_value](functions-5.md#apply_drag_to_value)
   - [cur_obj_apply_drag_xz](functions-5.md#cur_obj_apply_drag_xz)
   - [cur_obj_move_xz](functions-5.md#cur_obj_move_xz)
   - [cur_obj_move_update_underwater_flags](functions-5.md#cur_obj_move_update_underwater_flags)
   - [cur_obj_move_update_ground_air_flags](functions-5.md#cur_obj_move_update_ground_air_flags)
   - [cur_obj_move_y_and_get_water_level](functions-5.md#cur_obj_move_y_and_get_water_level)
   - [cur_obj_move_y](functions-5.md#cur_obj_move_y)
   - [cur_obj_unused_resolve_wall_collisions](functions-5.md#cur_obj_unused_resolve_wall_collisions)
   - [abs_angle_diff](functions-5.md#abs_angle_diff)
   - [cur_obj_move_xz_using_fvel_and_yaw](functions-5.md#cur_obj_move_xz_using_fvel_and_yaw)
   - [cur_obj_move_y_with_terminal_vel](functions-5.md#cur_obj_move_y_with_terminal_vel)
   - [cur_obj_compute_vel_xz](functions-5.md#cur_obj_compute_vel_xz)
   - [increment_velocity_toward_range](functions-5.md#increment_velocity_toward_range)
   - [obj_check_if_collided_with_object](functions-5.md#obj_check_if_collided_with_object)
   - [cur_obj_set_behavior](functions-5.md#cur_obj_set_behavior)
   - [obj_set_behavior](functions-5.md#obj_set_behavior)
   - [cur_obj_has_behavior](functions-5.md#cur_obj_has_behavior)
   - [obj_has_behavior](functions-5.md#obj_has_behavior)
   - [cur_obj_lateral_dist_from_obj_to_home](functions-5.md#cur_obj_lateral_dist_from_obj_to_home)
   - [cur_obj_lateral_dist_from_mario_to_home](functions-5.md#cur_obj_lateral_dist_from_mario_to_home)
   - [cur_obj_lateral_dist_to_home](functions-5.md#cur_obj_lateral_dist_to_home)
   - [cur_obj_outside_home_square](functions-5.md#cur_obj_outside_home_square)
   - [cur_obj_outside_home_rectangle](functions-5.md#cur_obj_outside_home_rectangle)
   - [cur_obj_set_pos_to_home](functions-5.md#cur_obj_set_pos_to_home)
   - [cur_obj_set_pos_to_home_and_stop](functions-5.md#cur_obj_set_pos_to_home_and_stop)
   - [cur_obj_shake_y](functions-5.md#cur_obj_shake_y)
   - [cur_obj_start_cam_event](functions-5.md#cur_obj_start_cam_event)
   - [set_mario_interact_hoot_if_in_range](functions-5.md#set_mario_interact_hoot_if_in_range)
   - [obj_set_billboard](functions-5.md#obj_set_billboard)
   - [obj_set_cylboard](functions-5.md#obj_set_cylboard)
   - [cur_obj_set_billboard_if_vanilla_cam](functions-5.md#cur_obj_set_billboard_if_vanilla_cam)
   - [obj_set_hitbox_radius_and_height](functions-5.md#obj_set_hitbox_radius_and_height)
   - [obj_set_hurtbox_radius_and_height](functions-5.md#obj_set_hurtbox_radius_and_height)
   - [cur_obj_set_hitbox_radius_and_height](functions-5.md#cur_obj_set_hitbox_radius_and_height)
   - [cur_obj_set_hurtbox_radius_and_height](functions-5.md#cur_obj_set_hurtbox_radius_and_height)
   - [obj_spawn_loot_coins](functions-5.md#obj_spawn_loot_coins)
   - [obj_spawn_loot_blue_coins](functions-5.md#obj_spawn_loot_blue_coins)
   - [obj_spawn_loot_yellow_coins](functions-5.md#obj_spawn_loot_yellow_coins)
   - [cur_obj_spawn_loot_coin_at_mario_pos](functions-5.md#cur_obj_spawn_loot_coin_at_mario_pos)
   - [cur_obj_abs_y_dist_to_home](functions-5.md#cur_obj_abs_y_dist_to_home)
   - [cur_obj_advance_looping_anim](functions-5.md#cur_obj_advance_looping_anim)
   - [cur_obj_detect_steep_floor](functions-5.md#cur_obj_detect_steep_floor)
   - [cur_obj_resolve_wall_collisions](functions-5.md#cur_obj_resolve_wall_collisions)
   - [cur_obj_update_floor](functions-5.md#cur_obj_update_floor)
   - [cur_obj_update_floor_and_resolve_wall_collisions](functions-5.md#cur_obj_update_floor_and_resolve_wall_collisions)
   - [cur_obj_update_floor_and_walls](functions-5.md#cur_obj_update_floor_and_walls)
   - [cur_obj_move_standard](functions-5.md#cur_obj_move_standard)
   - [cur_obj_within_12k_bounds](functions-5.md#cur_obj_within_12k_bounds)
   - [cur_obj_move_using_vel_and_gravity](functions-5.md#cur_obj_move_using_vel_and_gravity)
   - [cur_obj_move_using_fvel_and_gravity](functions-5.md#cur_obj_move_using_fvel_and_gravity)
   - [obj_set_pos_relative](functions-5.md#obj_set_pos_relative)
   - [cur_obj_angle_to_home](functions-5.md#cur_obj_angle_to_home)
   - [obj_set_gfx_pos_at_obj_pos](functions-5.md#obj_set_gfx_pos_at_obj_pos)
   - [obj_translate_local](functions-5.md#obj_translate_local)
   - [obj_build_transform_from_pos_and_angle](functions-5.md#obj_build_transform_from_pos_and_angle)
   - [obj_set_throw_matrix_from_transform](functions-5.md#obj_set_throw_matrix_from_transform)
   - [obj_build_transform_relative_to_parent](functions-5.md#obj_build_transform_relative_to_parent)
   - [obj_create_transform_from_self](functions-5.md#obj_create_transform_from_self)
   - [cur_obj_rotate_move_angle_using_vel](functions-5.md#cur_obj_rotate_move_angle_using_vel)
   - [cur_obj_rotate_face_angle_using_vel](functions-5.md#cur_obj_rotate_face_angle_using_vel)
   - [cur_obj_set_face_angle_to_move_angle](functions-5.md#cur_obj_set_face_angle_to_move_angle)
   - [cur_obj_follow_path](functions-5.md#cur_obj_follow_path)
   - [chain_segment_init](functions-5.md#chain_segment_init)
   - [random_f32_around_zero](functions-5.md#random_f32_around_zero)
   - [obj_scale_random](functions-5.md#obj_scale_random)
   - [obj_translate_xyz_random](functions-5.md#obj_translate_xyz_random)
   - [obj_translate_xz_random](functions-5.md#obj_translate_xz_random)
   - [obj_build_vel_from_transform](functions-5.md#obj_build_vel_from_transform)
   - [cur_obj_set_pos_via_transform](functions-5.md#cur_obj_set_pos_via_transform)
   - [cur_obj_reflect_move_angle_off_wall](functions-5.md#cur_obj_reflect_move_angle_off_wall)
   - [cur_obj_spawn_particles](functions-5.md#cur_obj_spawn_particles)
   - [obj_set_hitbox](functions-5.md#obj_set_hitbox)
   - [signum_positive](functions-5.md#signum_positive)
   - [cur_obj_wait_then_blink](functions-5.md#cur_obj_wait_then_blink)
   - [cur_obj_is_mario_ground_pounding_platform](functions-5.md#cur_obj_is_mario_ground_pounding_platform)
   - [obj_is_mario_ground_pounding_platform](functions-5.md#obj_is_mario_ground_pounding_platform)
   - [spawn_mist_particles](functions-5.md#spawn_mist_particles)
   - [spawn_mist_particles_with_sound](functions-5.md#spawn_mist_particles_with_sound)
   - [cur_obj_push_mario_away](functions-5.md#cur_obj_push_mario_away)
   - [cur_obj_push_mario_away_from_cylinder](functions-5.md#cur_obj_push_mario_away_from_cylinder)
   - [bhv_dust_smoke_loop](functions-5.md#bhv_dust_smoke_loop)
   - [stub_obj_helpers_3](functions-5.md#stub_obj_helpers_3)
   - [cur_obj_scale_over_time](functions-5.md#cur_obj_scale_over_time)
   - [cur_obj_set_pos_to_home_with_debug](functions-5.md#cur_obj_set_pos_to_home_with_debug)
   - [stub_obj_helpers_4](functions-5.md#stub_obj_helpers_4)
   - [cur_obj_is_mario_on_platform](functions-5.md#cur_obj_is_mario_on_platform)
   - [cur_obj_is_any_player_on_platform](functions-5.md#cur_obj_is_any_player_on_platform)
   - [cur_obj_shake_y_until](functions-5.md#cur_obj_shake_y_until)
   - [cur_obj_move_up_and_down](functions-5.md#cur_obj_move_up_and_down)
   - [spawn_star_with_no_lvl_exit](functions-5.md#spawn_star_with_no_lvl_exit)
   - [spawn_base_star_with_no_lvl_exit](functions-5.md#spawn_base_star_with_no_lvl_exit)
   - [bit_shift_left](functions-5.md#bit_shift_left)
   - [cur_obj_mario_far_away](functions-5.md#cur_obj_mario_far_away)
   - [is_mario_moving_fast_or_in_air](functions-5.md#is_mario_moving_fast_or_in_air)
   - [is_item_in_array](functions-5.md#is_item_in_array)
   - [bhv_init_room](functions-5.md#bhv_init_room)
   - [cur_obj_enable_rendering_if_mario_in_room](functions-5.md#cur_obj_enable_rendering_if_mario_in_room)
   - [cur_obj_set_hitbox_and_die_if_attacked](functions-5.md#cur_obj_set_hitbox_and_die_if_attacked)
   - [obj_explode_and_spawn_coins](functions-5.md#obj_explode_and_spawn_coins)
   - [cur_obj_if_hit_wall_bounce_away](functions-5.md#cur_obj_if_hit_wall_bounce_away)
   - [cur_obj_hide_if_mario_far_away_y](functions-5.md#cur_obj_hide_if_mario_far_away_y)
   - [obj_is_hidden](functions-5.md#obj_is_hidden)
   - [enable_time_stop](functions-5.md#enable_time_stop)
   - [enable_time_stop_if_alone](functions-5.md#enable_time_stop_if_alone)
   - [disable_time_stop](functions-5.md#disable_time_stop)
   - [set_time_stop_flags](functions-5.md#set_time_stop_flags)
   - [set_time_stop_flags_if_alone](functions-5.md#set_time_stop_flags_if_alone)
   - [clear_time_stop_flags](functions-5.md#clear_time_stop_flags)
   - [cur_obj_can_mario_activate_textbox](functions-5.md#cur_obj_can_mario_activate_textbox)
   - [cur_obj_can_mario_activate_textbox_2](functions-5.md#cur_obj_can_mario_activate_textbox_2)
   - [cur_obj_end_dialog](functions-5.md#cur_obj_end_dialog)
   - [cur_obj_has_model](functions-5.md#cur_obj_has_model)
   - [cur_obj_align_gfx_with_floor](functions-5.md#cur_obj_align_gfx_with_floor)
   - [mario_is_within_rectangle](functions-5.md#mario_is_within_rectangle)
   - [cur_obj_shake_screen](functions-5.md#cur_obj_shake_screen)
   - [obj_attack_collided_from_other_object](functions-5.md#obj_attack_collided_from_other_object)
   - [cur_obj_was_attacked_or_ground_pounded](functions-5.md#cur_obj_was_attacked_or_ground_pounded)
   - [obj_copy_behavior_params](functions-5.md#obj_copy_behavior_params)
   - [cur_obj_init_animation_and_anim_frame](functions-5.md#cur_obj_init_animation_and_anim_frame)
   - [cur_obj_init_animation_and_check_if_near_end](functions-5.md#cur_obj_init_animation_and_check_if_near_end)
   - [cur_obj_init_animation_and_extend_if_at_end](functions-5.md#cur_obj_init_animation_and_extend_if_at_end)
   - [cur_obj_check_grabbed_mario](functions-5.md#cur_obj_check_grabbed_mario)
   - [player_performed_grab_escape_action](functions-5.md#player_performed_grab_escape_action)
   - [cur_obj_unused_play_footstep_sound](functions-5.md#cur_obj_unused_play_footstep_sound)
   - [enable_time_stop_including_mario](functions-5.md#enable_time_stop_including_mario)
   - [disable_time_stop_including_mario](functions-5.md#disable_time_stop_including_mario)
   - [cur_obj_check_interacted](functions-5.md#cur_obj_check_interacted)
   - [cur_obj_spawn_loot_blue_coin](functions-5.md#cur_obj_spawn_loot_blue_coin)
   - [cur_obj_spawn_star_at_y_offset](functions-5.md#cur_obj_spawn_star_at_y_offset)
   - [cur_obj_set_home_once](functions-5.md#cur_obj_set_home_once)
   - [get_trajectory_length](functions-5.md#get_trajectory_length)

<br />

- object_list_processor.h
   - [set_object_respawn_info_bits](functions-5.md#set_object_respawn_info_bits)

<br />

- platform_displacement.h
   - [apply_platform_displacement](functions-5.md#apply_platform_displacement)

<br />

- rumble_init.h
   - [queue_rumble_data](functions-5.md#queue_rumble_data)
   - [queue_rumble_data_object](functions-5.md#queue_rumble_data_object)
   - [queue_rumble_data_mario](functions-5.md#queue_rumble_data_mario)
   - [reset_rumble_timers](functions-5.md#reset_rumble_timers)
   - [reset_rumble_timers_2](functions-5.md#reset_rumble_timers_2)

<br />

- save_file.h
   - [get_level_num_from_course_num](functions-5.md#get_level_num_from_course_num)
   - [get_level_course_num](functions-5.md#get_level_course_num)
   - [touch_coin_score_age](functions-5.md#touch_coin_score_age)
   - [save_file_do_save](functions-5.md#save_file_do_save)
   - [save_file_erase](functions-5.md#save_file_erase)
   - [save_file_erase_current_backup_save](functions-5.md#save_file_erase_current_backup_save)
   - [save_file_reload](functions-5.md#save_file_reload)
   - [save_file_get_max_coin_score](functions-5.md#save_file_get_max_coin_score)
   - [save_file_get_course_star_count](functions-5.md#save_file_get_course_star_count)
   - [save_file_get_total_star_count](functions-5.md#save_file_get_total_star_count)
   - [save_file_set_flags](functions-5.md#save_file_set_flags)
   - [save_file_clear_flags](functions-5.md#save_file_clear_flags)
   - [save_file_get_flags](functions-5.md#save_file_get_flags)
   - [save_file_get_star_flags](functions-5.md#save_file_get_star_flags)
   - [save_file_set_star_flags](functions-5.md#save_file_set_star_flags)
   - [save_file_remove_star_flags](functions-5.md#save_file_remove_star_flags)
   - [save_file_get_course_coin_score](functions-5.md#save_file_get_course_coin_score)
   - [save_file_set_course_coin_score](functions-5.md#save_file_set_course_coin_score)
   - [save_file_is_cannon_unlocked](functions-5.md#save_file_is_cannon_unlocked)
   - [save_file_get_cap_pos](functions-5.md#save_file_get_cap_pos)
   - [save_file_get_sound_mode](functions-5.md#save_file_get_sound_mode)

<br />

- seqplayer.h
   - [sequence_player_get_tempo](functions-6.md#sequence_player_get_tempo)
   - [sequence_player_set_tempo](functions-6.md#sequence_player_set_tempo)
   - [sequence_player_get_tempo_acc](functions-6.md#sequence_player_get_tempo_acc)
   - [sequence_player_set_tempo_acc](functions-6.md#sequence_player_set_tempo_acc)
   - [sequence_player_get_transposition](functions-6.md#sequence_player_get_transposition)
   - [sequence_player_set_transposition](functions-6.md#sequence_player_set_transposition)
   - [sequence_player_get_volume](functions-6.md#sequence_player_get_volume)
   - [sequence_player_get_fade_volume](functions-6.md#sequence_player_get_fade_volume)
   - [sequence_player_get_mute_volume_scale](functions-6.md#sequence_player_get_mute_volume_scale)

<br />

- smlua_anim_utils.h
   - [get_mario_vanilla_animation](functions-6.md#get_mario_vanilla_animation)
   - [smlua_anim_util_set_animation](functions-6.md#smlua_anim_util_set_animation)
   - [smlua_anim_util_get_current_animation_name](functions-6.md#smlua_anim_util_get_current_animation_name)

<br />

- smlua_audio_utils.h
   - [smlua_audio_utils_reset_all](functions-6.md#smlua_audio_utils_reset_all)
   - [smlua_audio_utils_replace_sequence](functions-6.md#smlua_audio_utils_replace_sequence)
   - [audio_stream_load](functions-6.md#audio_stream_load)
   - [audio_stream_destroy](functions-6.md#audio_stream_destroy)
   - [audio_stream_play](functions-6.md#audio_stream_play)
   - [audio_stream_pause](functions-6.md#audio_stream_pause)
   - [audio_stream_stop](functions-6.md#audio_stream_stop)
   - [audio_stream_get_position](functions-6.md#audio_stream_get_position)
   - [audio_stream_set_position](functions-6.md#audio_stream_set_position)
   - [audio_stream_get_looping](functions-6.md#audio_stream_get_looping)
   - [audio_stream_set_looping](functions-6.md#audio_stream_set_looping)
   - [audio_stream_set_loop_points](functions-6.md#audio_stream_set_loop_points)
   - [audio_stream_get_frequency](functions-6.md#audio_stream_get_frequency)
   - [audio_stream_set_frequency](functions-6.md#audio_stream_set_frequency)
   - [audio_stream_get_volume](functions-6.md#audio_stream_get_volume)
   - [audio_stream_set_volume](functions-6.md#audio_stream_set_volume)
   - [audio_sample_load](functions-6.md#audio_sample_load)
   - [audio_sample_destroy](functions-6.md#audio_sample_destroy)
   - [audio_sample_stop](functions-6.md#audio_sample_stop)
   - [audio_sample_play](functions-6.md#audio_sample_play)

<br />

- smlua_camera_utils.h
   - [camera_reset_overrides](functions-6.md#camera_reset_overrides)
   - [camera_freeze](functions-6.md#camera_freeze)
   - [camera_unfreeze](functions-6.md#camera_unfreeze)
   - [camera_is_frozen](functions-6.md#camera_is_frozen)
   - [camera_romhack_allow_only_mods](functions-6.md#camera_romhack_allow_only_mods)
   - [camera_set_romhack_override](functions-6.md#camera_set_romhack_override)
   - [camera_romhack_allow_centering](functions-6.md#camera_romhack_allow_centering)
   - [camera_allow_toxic_gas_camera](functions-6.md#camera_allow_toxic_gas_camera)
   - [camera_romhack_allow_dpad_usage](functions-6.md#camera_romhack_allow_dpad_usage)
   - [rom_hack_cam_set_collisions](functions-6.md#rom_hack_cam_set_collisions)
   - [camera_romhack_set_zoomed_in_dist](functions-6.md#camera_romhack_set_zoomed_in_dist)
   - [camera_romhack_set_zoomed_out_dist](functions-6.md#camera_romhack_set_zoomed_out_dist)
   - [camera_romhack_set_zoomed_in_height](functions-6.md#camera_romhack_set_zoomed_in_height)
   - [camera_romhack_set_zoomed_out_height](functions-6.md#camera_romhack_set_zoomed_out_height)
   - [camera_romhack_get_zoomed_in_dist](functions-6.md#camera_romhack_get_zoomed_in_dist)
   - [camera_romhack_get_zoomed_out_dist](functions-6.md#camera_romhack_get_zoomed_out_dist)
   - [camera_romhack_get_zoomed_in_height](functions-6.md#camera_romhack_get_zoomed_in_height)
   - [camera_romhack_get_zoomed_out_height](functions-6.md#camera_romhack_get_zoomed_out_height)
   - [camera_get_romhack_override](functions-6.md#camera_get_romhack_override)
   - [camera_romhack_get_allow_centering](functions-6.md#camera_romhack_get_allow_centering)
   - [camera_get_allow_toxic_gas_camera](functions-6.md#camera_get_allow_toxic_gas_camera)
   - [camera_romhack_get_allow_dpad_usage](functions-6.md#camera_romhack_get_allow_dpad_usage)
   - [camera_romhack_get_collisions](functions-6.md#camera_romhack_get_collisions)
   - [camera_config_is_free_cam_enabled](functions-6.md#camera_config_is_free_cam_enabled)
   - [camera_config_is_analog_cam_enabled](functions-6.md#camera_config_is_analog_cam_enabled)
   - [camera_config_is_dpad_enabled](functions-6.md#camera_config_is_dpad_enabled)
   - [camera_config_is_collision_enabled](functions-6.md#camera_config_is_collision_enabled)
   - [camera_config_is_mouse_look_enabled](functions-6.md#camera_config_is_mouse_look_enabled)
   - [camera_config_is_x_inverted](functions-6.md#camera_config_is_x_inverted)
   - [camera_config_is_y_inverted](functions-6.md#camera_config_is_y_inverted)
   - [camera_config_get_x_sensitivity](functions-6.md#camera_config_get_x_sensitivity)
   - [camera_config_get_y_sensitivity](functions-6.md#camera_config_get_y_sensitivity)
   - [camera_config_get_aggression](functions-6.md#camera_config_get_aggression)
   - [camera_config_get_pan_level](functions-6.md#camera_config_get_pan_level)
   - [camera_config_get_deceleration](functions-6.md#camera_config_get_deceleration)
   - [camera_config_get_centering](functions-6.md#camera_config_get_centering)
   - [camera_config_enable_free_cam](functions-6.md#camera_config_enable_free_cam)
   - [camera_config_enable_analog_cam](functions-6.md#camera_config_enable_analog_cam)
   - [camera_config_enable_centering](functions-6.md#camera_config_enable_centering)
   - [camera_config_enable_dpad](functions-6.md#camera_config_enable_dpad)
   - [camera_config_enable_collisions](functions-6.md#camera_config_enable_collisions)
   - [camera_config_enable_mouse_look](functions-6.md#camera_config_enable_mouse_look)
   - [camera_config_invert_x](functions-6.md#camera_config_invert_x)
   - [camera_config_invert_y](functions-6.md#camera_config_invert_y)
   - [camera_config_set_x_sensitivity](functions-6.md#camera_config_set_x_sensitivity)
   - [camera_config_set_y_sensitivity](functions-6.md#camera_config_set_y_sensitivity)
   - [camera_config_set_aggression](functions-6.md#camera_config_set_aggression)
   - [camera_config_set_pan_level](functions-6.md#camera_config_set_pan_level)
   - [camera_config_set_deceleration](functions-6.md#camera_config_set_deceleration)
   - [camera_get_checking_surfaces](functions-6.md#camera_get_checking_surfaces)
   - [camera_set_checking_surfaces](functions-6.md#camera_set_checking_surfaces)

<br />

- smlua_collision_utils.h
   - [collision_find_floor](functions-6.md#collision_find_floor)
   - [collision_find_ceil](functions-6.md#collision_find_ceil)
   - [get_water_surface_pseudo_floor](functions-6.md#get_water_surface_pseudo_floor)
   - [smlua_collision_util_get](functions-6.md#smlua_collision_util_get)
   - [collision_get_temp_wall_collision_data](functions-6.md#collision_get_temp_wall_collision_data)
   - [get_surface_from_wcd_index](functions-6.md#get_surface_from_wcd_index)
   - [smlua_collision_util_get_current_terrain_collision](functions-6.md#smlua_collision_util_get_current_terrain_collision)
   - [smlua_collision_util_get_level_collision](functions-6.md#smlua_collision_util_get_level_collision)
   - [smlua_collision_util_find_surface_types](functions-6.md#smlua_collision_util_find_surface_types)

<br />

- smlua_deprecated.h

<br />

- smlua_gfx_utils.h
   - [set_override_fov](functions-6.md#set_override_fov)
   - [set_override_near](functions-6.md#set_override_near)
   - [set_override_far](functions-6.md#set_override_far)
   - [get_lighting_dir](functions-6.md#get_lighting_dir)
   - [set_lighting_dir](functions-6.md#set_lighting_dir)
   - [get_lighting_color](functions-6.md#get_lighting_color)
   - [get_lighting_color_ambient](functions-6.md#get_lighting_color_ambient)
   - [set_lighting_color](functions-6.md#set_lighting_color)
   - [set_lighting_color_ambient](functions-6.md#set_lighting_color_ambient)
   - [get_vertex_color](functions-6.md#get_vertex_color)
   - [set_vertex_color](functions-6.md#set_vertex_color)
   - [get_fog_color](functions-6.md#get_fog_color)
   - [set_fog_color](functions-6.md#set_fog_color)
   - [get_fog_intensity](functions-6.md#get_fog_intensity)
   - [set_fog_intensity](functions-6.md#set_fog_intensity)
   - [get_skybox](functions-6.md#get_skybox)
   - [set_override_skybox](functions-6.md#set_override_skybox)
   - [get_skybox_color](functions-6.md#get_skybox_color)
   - [set_skybox_color](functions-6.md#set_skybox_color)
   - [gfx_parse](functions-6.md#gfx_parse)
   - [gfx_get_op](functions-6.md#gfx_get_op)
   - [gfx_get_display_list](functions-6.md#gfx_get_display_list)
   - [gfx_get_vertex_buffer](functions-6.md#gfx_get_vertex_buffer)
   - [gfx_get_vertex_count](functions-6.md#gfx_get_vertex_count)
   - [gfx_get_length](functions-6.md#gfx_get_length)
   - [gfx_get_command](functions-6.md#gfx_get_command)
   - [gfx_get_next_command](functions-6.md#gfx_get_next_command)
   - [gfx_copy](functions-6.md#gfx_copy)
   - [gfx_create](functions-6.md#gfx_create)
   - [gfx_resize](functions-6.md#gfx_resize)
   - [gfx_delete](functions-6.md#gfx_delete)
   - [gfx_delete_all](functions-6.md#gfx_delete_all)
   - [vtx_get_count](functions-6.md#vtx_get_count)
   - [vtx_get_vertex](functions-6.md#vtx_get_vertex)
   - [vtx_get_next_vertex](functions-6.md#vtx_get_next_vertex)
   - [vtx_copy](functions-6.md#vtx_copy)
   - [vtx_create](functions-6.md#vtx_create)
   - [vtx_resize](functions-6.md#vtx_resize)
   - [vtx_delete](functions-6.md#vtx_delete)
   - [vtx_delete_all](functions-6.md#vtx_delete_all)

<br />

- smlua_level_utils.h
   - [smlua_level_util_change_area](functions-6.md#smlua_level_util_change_area)
   - [smlua_level_util_get_info](functions-6.md#smlua_level_util_get_info)
   - [smlua_level_util_get_info_from_short_name](functions-6.md#smlua_level_util_get_info_from_short_name)
   - [smlua_level_util_get_info_from_course_num](functions-6.md#smlua_level_util_get_info_from_course_num)
   - [level_register](functions-6.md#level_register)
   - [level_is_vanilla_level](functions-6.md#level_is_vanilla_level)
   - [warp_to_warpnode](functions-6.md#warp_to_warpnode)
   - [warp_to_level](functions-6.md#warp_to_level)
   - [warp_restart_level](functions-6.md#warp_restart_level)
   - [warp_to_start_level](functions-6.md#warp_to_start_level)
   - [warp_exit_level](functions-6.md#warp_exit_level)
   - [warp_to_castle](functions-6.md#warp_to_castle)

<br />

- smlua_misc_utils.h
   - [get_network_area_timer](functions-6.md#get_network_area_timer)
   - [get_area_update_counter](functions-6.md#get_area_update_counter)
   - [get_temp_s32_pointer](functions-6.md#get_temp_s32_pointer)
   - [deref_s32_pointer](functions-6.md#deref_s32_pointer)
   - [djui_popup_create_global](functions-6.md#djui_popup_create_global)
   - [djui_is_popup_disabled](functions-6.md#djui_is_popup_disabled)
   - [djui_set_popup_disabled_override](functions-6.md#djui_set_popup_disabled_override)
   - [djui_reset_popup_disabled_override](functions-6.md#djui_reset_popup_disabled_override)
   - [djui_is_playerlist_open](functions-6.md#djui_is_playerlist_open)
   - [djui_attempting_to_open_playerlist](functions-6.md#djui_attempting_to_open_playerlist)
   - [djui_get_playerlist_page_index](functions-6.md#djui_get_playerlist_page_index)
   - [djui_menu_get_font](functions-6.md#djui_menu_get_font)
   - [djui_menu_get_theme](functions-6.md#djui_menu_get_theme)
   - [get_dialog_box_state](functions-6.md#get_dialog_box_state)
   - [get_dialog_id](functions-6.md#get_dialog_id)
   - [get_last_star_or_key](functions-6.md#get_last_star_or_key)
   - [set_last_star_or_key](functions-6.md#set_last_star_or_key)
   - [get_last_completed_course_num](functions-6.md#get_last_completed_course_num)
   - [set_last_completed_course_num](functions-6.md#set_last_completed_course_num)
   - [get_last_completed_star_num](functions-6.md#get_last_completed_star_num)
   - [set_last_completed_star_num](functions-6.md#set_last_completed_star_num)
   - [get_got_file_coin_hi_score](functions-6.md#get_got_file_coin_hi_score)
   - [set_got_file_coin_hi_score](functions-6.md#set_got_file_coin_hi_score)
   - [get_save_file_modified](functions-6.md#get_save_file_modified)
   - [set_save_file_modified](functions-6.md#set_save_file_modified)
   - [hud_hide](functions-6.md#hud_hide)
   - [hud_show](functions-6.md#hud_show)
   - [hud_is_hidden](functions-6.md#hud_is_hidden)
   - [hud_get_value](functions-6.md#hud_get_value)
   - [hud_set_value](functions-6.md#hud_set_value)
   - [hud_render_power_meter](functions-6.md#hud_render_power_meter)
   - [hud_render_power_meter_interpolated](functions-6.md#hud_render_power_meter_interpolated)
   - [hud_get_flash](functions-6.md#hud_get_flash)
   - [hud_set_flash](functions-6.md#hud_set_flash)
   - [is_game_paused](functions-6.md#is_game_paused)
   - [is_transition_playing](functions-6.md#is_transition_playing)
   - [allocate_mario_action](functions-6.md#allocate_mario_action)
   - [get_hand_foot_pos_x](functions-6.md#get_hand_foot_pos_x)
   - [get_hand_foot_pos_y](functions-6.md#get_hand_foot_pos_y)
   - [get_hand_foot_pos_z](functions-6.md#get_hand_foot_pos_z)
   - [get_mario_anim_part_pos](functions-6.md#get_mario_anim_part_pos)
   - [get_current_save_file_num](functions-6.md#get_current_save_file_num)
   - [save_file_get_using_backup_slot](functions-6.md#save_file_get_using_backup_slot)
   - [save_file_set_using_backup_slot](functions-6.md#save_file_set_using_backup_slot)
   - [movtexqc_register](functions-6.md#movtexqc_register)
   - [get_water_level](functions-6.md#get_water_level)
   - [set_water_level](functions-6.md#set_water_level)
   - [course_is_main_course](functions-6.md#course_is_main_course)
   - [get_ttc_speed_setting](functions-6.md#get_ttc_speed_setting)
   - [set_ttc_speed_setting](functions-6.md#set_ttc_speed_setting)
   - [get_time](functions-6.md#get_time)
   - [get_date_and_time](functions-6.md#get_date_and_time)
   - [get_envfx](functions-6.md#get_envfx)
   - [set_override_envfx](functions-6.md#set_override_envfx)
   - [get_global_timer](functions-6.md#get_global_timer)
   - [get_dialog_response](functions-6.md#get_dialog_response)
   - [get_local_discord_id](functions-6.md#get_local_discord_id)
   - [get_coopnet_id](functions-6.md#get_coopnet_id)
   - [get_volume_master](functions-6.md#get_volume_master)
   - [get_volume_level](functions-6.md#get_volume_level)
   - [get_volume_sfx](functions-6.md#get_volume_sfx)
   - [get_volume_env](functions-6.md#get_volume_env)
   - [set_volume_master](functions-6.md#set_volume_master)
   - [set_volume_level](functions-6.md#set_volume_level)
   - [set_volume_sfx](functions-6.md#set_volume_sfx)
   - [set_volume_env](functions-6.md#set_volume_env)
   - [get_environment_region](functions-6.md#get_environment_region)
   - [set_environment_region](functions-6.md#set_environment_region)
   - [mod_file_exists](functions-6.md#mod_file_exists)
   - [get_active_mod](functions-6.md#get_active_mod)
   - [set_window_title](functions-6.md#set_window_title)
   - [reset_window_title](functions-6.md#reset_window_title)
   - [get_os_name](functions-6.md#get_os_name)
   - [geo_get_current_root](functions-6.md#geo_get_current_root)
   - [geo_get_current_master_list](functions-6.md#geo_get_current_master_list)
   - [geo_get_current_perspective](functions-6.md#geo_get_current_perspective)
   - [geo_get_current_camera](functions-6.md#geo_get_current_camera)
   - [geo_get_current_held_object](functions-6.md#geo_get_current_held_object)

<br />

- smlua_model_utils.h
   - [smlua_model_util_get_id](functions-6.md#smlua_model_util_get_id)

<br />

- smlua_obj_utils.h
   - [spawn_sync_object](functions-6.md#spawn_sync_object)
   - [spawn_non_sync_object](functions-6.md#spawn_non_sync_object)
   - [obj_has_behavior_id](functions-6.md#obj_has_behavior_id)
   - [obj_has_model_extended](functions-6.md#obj_has_model_extended)
   - [obj_get_model_id_extended](functions-6.md#obj_get_model_id_extended)
   - [obj_set_model_extended](functions-6.md#obj_set_model_extended)
   - [get_trajectory](functions-6.md#get_trajectory)
   - [geo_get_current_object](functions-6.md#geo_get_current_object)
   - [get_current_object](functions-6.md#get_current_object)
   - [get_dialog_object](functions-6.md#get_dialog_object)
   - [get_cutscene_focus](functions-6.md#get_cutscene_focus)
   - [get_secondary_camera_focus](functions-6.md#get_secondary_camera_focus)
   - [set_cutscene_focus](functions-6.md#set_cutscene_focus)
   - [set_secondary_camera_focus](functions-6.md#set_secondary_camera_focus)
   - [obj_get_first](functions-6.md#obj_get_first)
   - [obj_get_first_with_behavior_id](functions-6.md#obj_get_first_with_behavior_id)
   - [obj_get_first_with_behavior_id_and_field_s32](functions-6.md#obj_get_first_with_behavior_id_and_field_s32)
   - [obj_get_first_with_behavior_id_and_field_f32](functions-6.md#obj_get_first_with_behavior_id_and_field_f32)
   - [obj_get_next](functions-6.md#obj_get_next)
   - [obj_get_next_with_same_behavior_id](functions-6.md#obj_get_next_with_same_behavior_id)
   - [obj_get_next_with_same_behavior_id_and_field_s32](functions-6.md#obj_get_next_with_same_behavior_id_and_field_s32)
   - [obj_get_next_with_same_behavior_id_and_field_f32](functions-6.md#obj_get_next_with_same_behavior_id_and_field_f32)
   - [obj_get_nearest_object_with_behavior_id](functions-6.md#obj_get_nearest_object_with_behavior_id)
   - [obj_count_objects_with_behavior_id](functions-6.md#obj_count_objects_with_behavior_id)
   - [obj_get_collided_object](functions-6.md#obj_get_collided_object)
   - [obj_get_field_u32](functions-6.md#obj_get_field_u32)
   - [obj_get_field_s32](functions-6.md#obj_get_field_s32)
   - [obj_get_field_f32](functions-6.md#obj_get_field_f32)
   - [obj_get_field_s16](functions-6.md#obj_get_field_s16)
   - [obj_set_field_u32](functions-6.md#obj_set_field_u32)
   - [obj_set_field_s32](functions-6.md#obj_set_field_s32)
   - [obj_set_field_f32](functions-6.md#obj_set_field_f32)
   - [obj_set_field_s16](functions-6.md#obj_set_field_s16)
   - [obj_get_temp_spawn_particles_info](functions-6.md#obj_get_temp_spawn_particles_info)
   - [get_temp_object_hitbox](functions-6.md#get_temp_object_hitbox)
   - [obj_is_attackable](functions-6.md#obj_is_attackable)
   - [obj_is_breakable_object](functions-6.md#obj_is_breakable_object)
   - [obj_is_bully](functions-6.md#obj_is_bully)
   - [obj_is_coin](functions-6.md#obj_is_coin)
   - [obj_is_exclamation_box](functions-6.md#obj_is_exclamation_box)
   - [obj_is_grabbable](functions-6.md#obj_is_grabbable)
   - [obj_is_mushroom_1up](functions-6.md#obj_is_mushroom_1up)
   - [obj_is_secret](functions-6.md#obj_is_secret)
   - [obj_is_valid_for_interaction](functions-6.md#obj_is_valid_for_interaction)
   - [obj_check_hitbox_overlap](functions-6.md#obj_check_hitbox_overlap)
   - [obj_check_overlap_with_hitbox_params](functions-6.md#obj_check_overlap_with_hitbox_params)
   - [obj_set_vel](functions-6.md#obj_set_vel)
   - [obj_move_xyz](functions-6.md#obj_move_xyz)
   - [set_whirlpools](functions-6.md#set_whirlpools)

<br />

- smlua_text_utils.h
   - [smlua_text_utils_reset_all](functions-6.md#smlua_text_utils_reset_all)
   - [smlua_text_utils_dialog_replace](functions-6.md#smlua_text_utils_dialog_replace)
   - [smlua_text_utils_course_acts_replace](functions-6.md#smlua_text_utils_course_acts_replace)
   - [smlua_text_utils_secret_star_replace](functions-6.md#smlua_text_utils_secret_star_replace)
   - [smlua_text_utils_course_name_replace](functions-6.md#smlua_text_utils_course_name_replace)
   - [smlua_text_utils_course_name_get](functions-6.md#smlua_text_utils_course_name_get)
   - [smlua_text_utils_course_name_mod_index](functions-6.md#smlua_text_utils_course_name_mod_index)
   - [smlua_text_utils_course_name_reset](functions-6.md#smlua_text_utils_course_name_reset)
   - [smlua_text_utils_act_name_replace](functions-6.md#smlua_text_utils_act_name_replace)
   - [smlua_text_utils_act_name_get](functions-6.md#smlua_text_utils_act_name_get)
   - [smlua_text_utils_act_name_mod_index](functions-6.md#smlua_text_utils_act_name_mod_index)
   - [smlua_text_utils_act_name_reset](functions-6.md#smlua_text_utils_act_name_reset)
   - [smlua_text_utils_castle_secret_stars_replace](functions-6.md#smlua_text_utils_castle_secret_stars_replace)
   - [smlua_text_utils_extra_text_replace](functions-6.md#smlua_text_utils_extra_text_replace)
   - [smlua_text_utils_get_language](functions-6.md#smlua_text_utils_get_language)

<br />

- sound_init.h
   - [reset_volume](functions-6.md#reset_volume)
   - [raise_background_noise](functions-6.md#raise_background_noise)
   - [lower_background_noise](functions-6.md#lower_background_noise)
   - [disable_background_sound](functions-6.md#disable_background_sound)
   - [enable_background_sound](functions-6.md#enable_background_sound)
   - [play_menu_sounds](functions-6.md#play_menu_sounds)
   - [play_painting_eject_sound](functions-6.md#play_painting_eject_sound)
   - [play_infinite_stairs_music](functions-6.md#play_infinite_stairs_music)
   - [set_background_music](functions-6.md#set_background_music)
   - [fadeout_music](functions-6.md#fadeout_music)
   - [fadeout_level_music](functions-6.md#fadeout_level_music)
   - [play_cutscene_music](functions-6.md#play_cutscene_music)
   - [play_shell_music](functions-6.md#play_shell_music)
   - [stop_shell_music](functions-6.md#stop_shell_music)
   - [play_cap_music](functions-6.md#play_cap_music)
   - [fadeout_cap_music](functions-6.md#fadeout_cap_music)
   - [stop_cap_music](functions-6.md#stop_cap_music)

<br />

- spawn_sound.h
   - [cur_obj_play_sound_1](functions-6.md#cur_obj_play_sound_1)
   - [cur_obj_play_sound_2](functions-6.md#cur_obj_play_sound_2)
   - [create_sound_spawner](functions-6.md#create_sound_spawner)
   - [calc_dist_to_volume_range_1](functions-6.md#calc_dist_to_volume_range_1)
   - [calc_dist_to_volume_range_2](functions-6.md#calc_dist_to_volume_range_2)

<br />

- surface_collision.h
   - [find_wall_collisions](functions-6.md#find_wall_collisions)
   - [find_ceil_height](functions-6.md#find_ceil_height)
   - [find_floor_height](functions-6.md#find_floor_height)
   - [find_water_level](functions-6.md#find_water_level)
   - [find_poison_gas_level](functions-6.md#find_poison_gas_level)
   - [set_find_wall_direction](functions-6.md#set_find_wall_direction)
   - [closest_point_to_triangle](functions-6.md#closest_point_to_triangle)

<br />

- surface_load.h
   - [load_object_collision_model](functions-6.md#load_object_collision_model)
   - [obj_get_surface_from_index](functions-6.md#obj_get_surface_from_index)
   - [surface_has_force](functions-6.md#surface_has_force)

<br />

- sync_object.h
   - [sync_object_get_object](functions-6.md#sync_object_get_object)
   - [sync_object_is_initialized](functions-6.md#sync_object_is_initialized)
   - [sync_object_is_owned_locally](functions-6.md#sync_object_is_owned_locally)

<br />


---
# manually written functions

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

## [network_send_to](#network_send_to)

Sends a packet to a particular player (using their local index) containing whatever data you want.

`dataTable` can only contain strings, integers, numbers, booleans, and nil

The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.

### Lua Example
`network_send_to(localPlayerIndex, reliable, { data1 = 'hello', data2 = 10})`

### Parameters
| Field | Type |
| ----- | ---- |
| localPlayerIndex | `integer` |
| reliable | `bool` |
| dataTable | `table` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />

## [network_send](#network_send)

Sends a packet to all players containing whatever data you want.

`dataTable` can only contain strings, integers, numbers, booleans, and nil

The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.

### Lua Example
`network_send(reliable, { data1 = 'hello', data2 = 10})`

### Parameters
| Field | Type |
| ----- | ---- |
| reliable | `bool` |
| dataTable | `table` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />

## [get_texture_info](#get_texture_info)

Retrieves a texture by name.

### Lua Example
`get_texture_info(textureName)`

### Parameters
| Field | Type |
| ----- | ---- |
| textureName | `string` |

### Returns
- [TextureInfo](structs.md#TextureInfo)

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />

## [djui_hud_render_texture](#djui_hud_render_texture)

Renders a texture to the screen.

### Lua Example
`djui_hud_render_texture(texInfo, 0, 0, 1, 1)`

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

## [djui_hud_render_texture_tile](#djui_hud_render_texture_tile)

Renders a tile of a texture to the screen.

### Lua Example
`djui_hud_render_texture_tile(texInfo, 0, 0, 1, 1, 0, 0, 16, 16)`

### Parameters
| Field | Type |
| ----- | ---- |
| texInfo | [TextureInfo](structs.md#TextureInfo) |
| x | `number` |
| y | `number` |
| scaleW | `number` |
| scaleH | `number` |
| tileX | `number` |
| tileY | `number` |
| tileW | `number` |
| tileH | `number` |

### Returns
- None

### C Prototype
`void djui_hud_render_texture_tile(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);`

[:arrow_up_small:](#)

<br />

## [djui_hud_render_texture_tile_interpolated](#djui_hud_render_texture_tile_interpolated)

Renders an interpolated tile of a texture to the screen.

### Lua Example
`djui_hud_render_texture_tile_interpolated(texInfo, prevX, prevY, prevScaleW, prevScaleH, 0, 0, 1, 1, 0, 0, 16, 16)`

### Parameters
| Field | Type |
| ----- | ---- |
| texInfo | [TextureInfo](structs.md#TextureInfo) |
| prevX | `number` |
| prevY | `number` |
| prevScaleW | `number` |
| prevScaleH | `number` |
| x | `number` |
| y | `number` |
| scaleW | `number` |
| scaleH | `number` |
| tileX | `number` |
| tileY | `number` |
| tileW | `number` |
| tileH | `number` |

### Returns
- None

### C Prototype
`void djui_hud_render_texture_tile_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);`

[:arrow_up_small:](#)

<br />

## [texture_override_reset](#texture_override_reset)

Resets an overridden texture.

### Lua Example
`texture_override_reset("outside_09004000")`

### Parameters
| Field | Type |
| ----- | ---- |
| textureName | `string` |

### Returns
- None

### C Prototype
`void dynos_texture_override_reset(const char* textureName);`

[:arrow_up_small:](#)

<br />

## [texture_override_set](#texture_override_set)

Overrides a texture with a custom `TextureInfo`.

### Lua Example
`texture_override_set("outside_09004000", overrideTexInfo)`

### Parameters
| Field | Type |
| ----- | ---- |
| textureName | `string` |
| overrideTexInfo | [TextureInfo](structs.md#TextureInfo) |

### Returns
- None

### C Prototype
`void dynos_texture_override_set(const char* textureName, struct TextureInfo* overrideTexInfo);`

[:arrow_up_small:](#)

<br />

## [smlua_anim_util_register_animation](#smlua_anim_util_register_animation)

Register a new Lua animation.

### Lua Example
`smlua_anim_util_register_animation("apparition_idle", 0, 189, 0, 0, 0x5A, values, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |
| flags | `integer` |
| animYTransDivisor | `integer` |
| startFrame | `integer` |
| loopStart | `integer` |
| loopEnd | `integer` |
| values | `table` |
| index | `table` |

### Returns
- None

### C Prototype
`void smlua_anim_util_register_animation(const char *name, s16 flags, s16 animYTransDivisor, s16 startFrame, s16 loopStart, s16 loopEnd, s16 *values, u32 valuesLength, u16 *index, u32 indexLength);`

[:arrow_up_small:](#)

<br />

## [level_script_parse](#level_script_parse)

### Lua Example
`level_script_parse(LEVEL_BOB, func)`

Parses a level script and passes area index, behavior data, macro behavior IDs and macro behavior arguments to a function.

### Parameters
| Field | Type |
| ----- | ---- |
| levelNum | `LevelNum` |
| func | `function` |

### Returns
- None

### C Prototype
`void smlua_func_level_script_parse(lua_State* L);`

[:arrow_up_small:](#)

<br />

## [log_to_console](#log_to_console)

Logs a message to the in-game console.

### Lua Example
`log_to_console("sm64coopdx FTW", CONSOLE_MESSAGE_INFO)`

### Parameters
| Field | Type |
| ----- | ---- |
| message | `string` |
| level (optional) | `ConsoleMessageLevel` |

### Returns
- None

### C Prototype
`void log_to_console(const char* message, enum ConsoleMessageLevel level);`

[:arrow_up_small:](#)

<br />

## [add_scroll_target](#add_scroll_target)

Registers a vertex buffer to be used for a scrolling texture. Should be used with `RM_Scroll_Texture` or `editor_Scroll_Texture`

### Lua Example
`add_scroll_target(0, "arena_rainbow_dl_StarRoad_mesh_layer_5_vtx_0")`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| name | `string` |

### Returns
- None

### C Prototype
`void dynos_add_scroll_target(u32 index, const char *name, u32 offset, u32 size);`

[:arrow_up_small:](#)

<br />

## [collision_find_surface_on_ray](#collision_find_surface_on_ray)

Shoots a raycast from `startX`, `startY`, and `startZ` in the direction of `dirX`, `dirY`, and `dirZ`.

### Lua Example
`collision_find_surface_on_ray(0, 0, 0, 50, 100, 50)`

### Parameters
| Field | Type |
| ----- | ---- |
| startX | `number` |
| startY | `number` |
| startZ | `number` |
| dirX | `number` |
| dirY | `number` |
| dirZ | `number` |
| precision (optional) | `number` |

### Returns
- [RayIntersectionInfo](structs.md#RayIntersectionInfo)

### C Prototype
`struct RayIntersectionInfo* collision_find_surface_on_ray(f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32 precision);`

[:arrow_up_small:](#)

<br />

## [set_exclamation_box_contents](#set_exclamation_box_contents)

Sets the contents that the exclamation box spawns. A single content has 5 keys: `id`, `unused`, `firstByte`, `model`, and `behavior`.
* `id`: Required; what value the box's oBehParams2ndByte needs to be to spawn this object.
* `unused`: Optional; unused by vanilla.
* `firstByte`: Optional; Overrides the 1st byte given to the spawned object.
* `model`: Required; The model that the object will spawn with. Uses `ModelExtendedId`.
* `behavior`: Required; The behavior ID that the object will spawn with. Uses `BehaviorId`.

### Lua Example
```lua
set_exclamation_box_contents({
   {id = 0, unused = 0, firstByte = 0, model = E_MODEL_GOOMBA, behavior = id_bhvGoomba}, -- Uses both optional fields
   {id = 1, unused = 0, model = E_MODEL_KOOPA_WITH_SHELL, behavior = id_bhvKoopa}, -- Only uses `unused` optional field
   {id = 2, firsteByte = model = E_MODEL_BLACK_BOBOMB, behavior = id_bhvBobomb}, -- Only uses `firstByte` optional field
   {id = 3, model = E_MODEL_BOO, behavior = id_bhvBoo}, -- Uses no optional fields
})
```

### Parameters
There exists only 1 parameter to this function which is the main table. However, each subtable has 5 different keys that could be accessed.
| Field | Type |
| ----- | ---- |
| id | `integer` |
| unused (Optional) | `integer` |
| firstByte (Optional) | `integer` |
| model | [ModelExtendedId](#ModelExtendedId) |
| behavior | [BehaviorId](#BehaviorId) |

### Returns
- None

### C Prototype
N/A

[:arrow_up_small:](#)

<br />

## [get_exclamation_box_contents](#get_exclamation_box_contents)

Gets the contents that the exclamation box spawns. A single content has 5 keys: `id`, `unused`, `firstByte`, `model`, and `behavior`.
* `id`: Required; what value the box's oBehParams2ndByte needs to be to spawn this object.
* `unused`: Optional; unused by vanilla.
* `firstByte`: Optional; Overrides the 1st byte given to the spawned object.
* `model`: Required; The model that the object will spawn with. Uses `ModelExtendedId`.
* `behavior`: Required; The behavior ID that the object will spawn with. Uses `BehaviorId`.

### Lua Example
```lua
local contents = get_exclamation_box_contents()
for index, content in pairs(contents) do -- Enter the main table
   djui_chat_message_create("Table index " .. index) -- Print the current table index
      for key, value in pairs(content) do
         djui_chat_message_create(key .. ": " .. value) -- Print a key-value pair within this subtable
      end
   djui_chat_message_create("---------------------------------") -- Separator
end
```

### Parameters
- N/A

### Returns
The function itself does not return every key/value pair. Instead it returns the main table which holds all the subtables that hold each key/value pair.
| Field | Type |
| ----- | ---- |
| id | `integer` |
| unused (Optional) | `integer` |
| firstByte (Optional) | `integer` |
| model | [ModelExtendedId](#ModelExtendedId) |
| behavior | [BehaviorId](#BehaviorId) |

### C Prototype
N/A

[:arrow_up_small:](#)

<br />

## [cast_graph_node](#cast_graph_node)

Returns the specific GraphNode(...) the node is part of. Basically the reverse of `.node` or `.fnNode`.

### Lua Example
```lua
local marioGfx = gMarioStates[0].marioObj.header.gfx -- GraphNodeObject
local node = marioGfx.node -- GraphNode

print(marioGfx == cast_graph_node(node)) -- true
```

### Parameters
| Field | Type |
| ----- | ---- |
| node  | [GraphNode](structs.md#GraphNode) |

### Returns
- GraphNode(...)

### C Prototype
N/A

[:arrow_up_small:](#)

<br />

## [get_uncolored_string](#get_uncolored_string)

Removes color codes from a string.

### Lua Example
```lua
print(get_uncolored_string("\#210059\Colored \#FF086F\String")) -- "Colored String"
```

### Parameters
| Field | Type |
| ----- | ---- |
| str   | 'string' |

### Returns
- `string`

### C Prototype
N/A

[:arrow_up_small:](#)

<br />

## [gfx_set_command](#gfx_set_command)

Sets a display list command on the display list given.

If `command` includes parameter specifiers (subsequences beginning with `%`), the additional arguments following `command` are converted and inserted in `command` replacing their respective specifiers.

The number of provided parameters must be equal to the number of specifiers in `command`, and the order of parameters must be the same as the specifiers.

The following specifiers are allowed:
- `%i` for an `integer` parameter
- `%s` for a `string` parameter
- `%v` for a `Vtx` parameter
- `%t` for a `Texture` parameter
- `%g` for a `Gfx` parameter

### Lua Examples

Plain string:
```lua
gfx_set_command(gfx, "gsDPSetEnvColor(0x00, 0xFF, 0x00, 0xFF)")
```

With parameter specifiers:
```lua
r, g, b, a = 0x00, 0xFF, 0x00, 0xFF
gfx_set_command(gfx, "gsDPSetEnvColor(%i, %i, %i, %i)", r, g, b, a)
```

### Parameters
| Field | Type |
| ----- | ---- |
| gfx   | [Gfx](structs.md#Gfx) |
| command | `string` |
| parameters... | any of `integer`, `string`, `Gfx`, `Texture`, `Vtx` |

### Returns
- None

### C Prototype
N/A

[:arrow_up_small:](#)

<br />


---
# functions from area.h

<br />


## [get_mario_spawn_type](#get_mario_spawn_type)

### Description
Derives a `MARIO_SPAWN_*` constant from `o`

### Lua Example
`local integerValue = get_mario_spawn_type(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u32 get_mario_spawn_type(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [area_get_warp_node](#area_get_warp_node)

### Description
Finds a warp node in the current area by its ID. The warp node must exist in the list of warp nodes for the current area. Useful for locating a specific warp point in the level, such as teleportation zones or connections to other areas

### Lua Example
`local ObjectWarpNodeValue = area_get_warp_node(id)`

### Parameters
| Field | Type |
| ----- | ---- |
| id | `integer` |

### Returns
[ObjectWarpNode](structs.md#ObjectWarpNode)

### C Prototype
`struct ObjectWarpNode *area_get_warp_node(u8 id);`

[:arrow_up_small:](#)

<br />

## [area_get_any_warp_node](#area_get_any_warp_node)

### Description
Gets the first warp node found in the area, otherwise returns nil

### Lua Example
`local ObjectWarpNodeValue = area_get_any_warp_node()`

### Parameters
- None

### Returns
[ObjectWarpNode](structs.md#ObjectWarpNode)

### C Prototype
`struct ObjectWarpNode *area_get_any_warp_node(void);`

[:arrow_up_small:](#)

<br />

## [area_get_warp_node_from_params](#area_get_warp_node_from_params)

### Description
Finds a warp node in the current area using parameters from the provided object. The object's behavior parameters are used to determine the warp node ID. Useful for associating an object (like a door or warp pipe) with its corresponding warp node in the area

### Lua Example
`local ObjectWarpNodeValue = area_get_warp_node_from_params(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
[ObjectWarpNode](structs.md#ObjectWarpNode)

### C Prototype
`struct ObjectWarpNode *area_get_warp_node_from_params(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [play_transition](#play_transition)

### Description
Plays a screen transition

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

## [play_transition_after_delay](#play_transition_after_delay)

### Description
Plays a screen transition after a `delay` in frames

### Lua Example
`play_transition_after_delay(transType, time, red, green, blue, delay)`

### Parameters
| Field | Type |
| ----- | ---- |
| transType | `integer` |
| time | `integer` |
| red | `integer` |
| green | `integer` |
| blue | `integer` |
| delay | `integer` |

### Returns
- None

### C Prototype
`void play_transition_after_delay(s16 transType, s16 time, u8 red, u8 green, u8 blue, s16 delay);`

[:arrow_up_small:](#)

<br />
---

1 | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | [next >](functions-2.md)]

