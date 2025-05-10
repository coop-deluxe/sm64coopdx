#ifndef BEHAVIOR_ACTIONS_H
#define BEHAVIOR_ACTIONS_H

#define BHV_ARR_CHECK(_arr, _idx, _arritem) (((size_t)_idx) < (sizeof(_arr) / sizeof(_arritem)))
#define BHV_ARR(_arr, _idx, _arritem) (BHV_ARR_CHECK(_arr, _idx, _arritem) ? _arr[_idx] : 0)

/* |description|Spawns mist particles around the current object|descriptionEnd| */
void spawn_mist_particles_variable(s32 count, s32 offsetY, f32 size);
/* |description|Spawns a Star parented to `object` that won't make Mario exit the level with an ID corresponding to `params`' first byte|descriptionEnd| */
void bhv_spawn_star_no_level_exit(struct Object* object, u32 params, u8 networkSendEvent);
/* |description|Spawns triangle break particles around the current object|descriptionEnd| */
void spawn_triangle_break_particles(s16 numTris, s16 triModel, f32 triSize, s16 triAnimState);

/* |description|Spawns mist particles around the current object|descriptionEnd| */
void spawn_mist_from_global(void);
/* |description|Clears the particle flags of the current object|descriptionEnd| */
void clear_particle_flags(u32 flags);
/* |description|Spawns wind particles around the current object|descriptionEnd| */
void spawn_wind_particles(s16 pitch, s16 yaw);
/* |description|Checks if the current object is moving `a1` units over a floor and within a threshold of `a0`|descriptionEnd| */
s32 check_if_moving_over_floor(f32 a0, f32 a1);
/* |description|Calculates the time it takes for the current object to follow an arc from `pos` to `goal`|descriptionEnd| */
s32 arc_to_goal_pos(Vec3f goal, Vec3f pos, f32 yVel, f32 gravity);
/* |description|Duplicate of vec3f_copy except without bad return|descriptionEnd| */
void vec3f_copy_2(Vec3f dest, Vec3f src);
/* |description|Moves Tox Box|descriptionEnd| */
void tox_box_move(f32 forwardVel, f32 a1, s16 deltaPitch, s16 deltaRoll);
/* |description|Plays the penguin walking sound|descriptionEnd| */
void play_penguin_walking_sound(s32 walk);
/* |description|Updates the current object's angle from its move flags|descriptionEnd| */
s32 update_angle_from_move_flags(s32 *angle);
/* |description|Spawns strong wind particles relative to the current object|descriptionEnd| */
void cur_obj_spawn_strong_wind_particles(s32 windSpread, f32 scale, f32 relPosX, f32 relPosY, f32 relPosZ);

/* |description|Behavior loop function for Star Door|descriptionEnd| */
void bhv_star_door_loop_2(void);
/* |description|Behavior loop function for Cap Switch|descriptionEnd| */
void bhv_cap_switch_loop(void);
/* |description|Behavior init function for tiny Star particles|descriptionEnd| */
void bhv_tiny_star_particles_init(void);
/* |description|Behavior loop function for Grindel and Thwomp|descriptionEnd| */
void bhv_grindel_thwomp_loop(void);
/* |description|Behavior loop function for Koopa Shell underwater|descriptionEnd| */
void bhv_koopa_shell_underwater_loop(void);
/* |description|Behavior init function for door|descriptionEnd| */
void bhv_door_init(void);
/* |description|Behavior loop function for door|descriptionEnd| */
void bhv_door_loop(void);
/* |description|Behavior loop function for Star Door|descriptionEnd| */
void bhv_star_door_loop(void);
/* |description|Behavior loop function for Mr. I|descriptionEnd| */
void bhv_mr_i_loop(void);
/* |description|Behavior loop function for Mr. I body|descriptionEnd| */
void bhv_mr_i_body_loop(void);
/* |description|Behavior loop function for Mr. I particle|descriptionEnd| */
void bhv_mr_i_particle_loop(void);
/* |description|Behavior loop function for Piranha particle|descriptionEnd| */
void bhv_piranha_particle_loop(void);
/* |description|Behavior loop function for giant pole|descriptionEnd| */
void bhv_giant_pole_loop(void);
/* |description|Behavior init function for pole|descriptionEnd| */
void bhv_pole_init(void);
/* |description|Behavior loop function for pole base|descriptionEnd| */
void bhv_pole_base_loop(void);
/* |description|Behavior loop function for Tiny Huge Island huge island top|descriptionEnd| */
void bhv_thi_huge_island_top_loop(void);
/* |description|Behavior loop function for Tiny Huge Island tiny island top|descriptionEnd| */
void bhv_thi_tiny_island_top_loop(void);
/* |description|Behavior loop function for King Bob-omb|descriptionEnd| */
void bhv_king_bobomb_loop(void);
/* |description|Behavior loop function for Bob-omb anchor mario|descriptionEnd| */
void bhv_bobomb_anchor_mario_loop(void);
/* |description|Behavior init function for beta chest bottom|descriptionEnd| */
void bhv_beta_chest_bottom_init(void);
/* |description|Behavior loop function for beta chest bottom|descriptionEnd| */
void bhv_beta_chest_bottom_loop(void);
/* |description|Behavior loop function for beta chest lid|descriptionEnd| */
void bhv_beta_chest_lid_loop(void);
/* |description|Behavior init function for bubble wave|descriptionEnd| */
void bhv_bubble_wave_init(void);
/* |description|Behavior loop function for bubble maybe|descriptionEnd| */
void bhv_bubble_maybe_loop(void);
/* |description|Behavior loop function for bubble player|descriptionEnd| */
void bhv_bubble_player_loop(void);
/* |description|Behavior init function for water air bubble|descriptionEnd| */
void bhv_water_air_bubble_init(void);
/* |description|Behavior loop function for water air bubble|descriptionEnd| */
void bhv_water_air_bubble_loop(void);
/* |description|Behavior init function for particle|descriptionEnd| */
void bhv_particle_init(void);
/* |description|Behavior loop function for particle|descriptionEnd| */
void bhv_particle_loop(void);
/* |description|Behavior init function for water waves|descriptionEnd| */
void bhv_water_waves_init(void);
/* |description|Behavior loop function for small bubbles|descriptionEnd| */
void bhv_small_bubbles_loop(void);
/* |description|Behavior loop function for fish group|descriptionEnd| */
void bhv_fish_group_loop(void);
/* |description|Behavior loop function for cannon base|descriptionEnd| */
void bhv_cannon_base_loop(void);
/* |description|Behavior loop function for cannon barrel|descriptionEnd| */
void bhv_cannon_barrel_loop(void);
/* |description|Behavior loop function for cannon base unused|descriptionEnd| */
void bhv_cannon_base_unused_loop(void);
/* |description|Common behavior for when Mario's anchoring when grabbed|descriptionEnd| */
void common_anchor_mario_behavior(f32 sp28, f32 sp2C, s32 sp30);
/* |description|Behavior loop function for Chuckya|descriptionEnd| */
void bhv_chuckya_loop(void);
/* |description|Behavior loop function for Chuckya mario anchor|descriptionEnd| */
void bhv_chuckya_anchor_mario_loop(void);
/* |description|Behavior loop function for rotating platform|descriptionEnd| */
void bhv_rotating_platform_loop(void);
/* |description|Behavior loop function for Whomp's Fortress breakable wall|descriptionEnd| */
void bhv_wf_breakable_wall_loop(void);
/* |description|Behavior loop function for Whomp's Fortress kickable board|descriptionEnd| */
void bhv_kickable_board_loop(void);
/* |description|Behavior loop function for Whomp's Fortress tower door|descriptionEnd| */
void bhv_tower_door_loop(void);
/* |description|Behavior init function for Whomp's Fortress rotating wooden platform|descriptionEnd| */
void bhv_wf_rotating_wooden_platform_init(void);
/* |description|Behavior loop function for Whomp's Fortress rotating wooden platform|descriptionEnd| */
void bhv_wf_rotating_wooden_platform_loop(void);
/* |description|Behavior loop function for fading warp|descriptionEnd| */
void bhv_fading_warp_loop(void);
/* |description|Behavior loop function for warp|descriptionEnd| */
void bhv_warp_loop(void);
/* |description|Behavior loop function for white puff exploding|descriptionEnd| */
void bhv_white_puff_exploding_loop(void);
/* |description|Behavior init function for spawned star|descriptionEnd| */
void bhv_spawned_star_init(void);
/* |description|Behavior loop function for Spawned star|descriptionEnd| */
void bhv_spawned_star_loop(void);
/* |description|Behavior init function for Coin|descriptionEnd| */
void bhv_coin_init(void);
/* |description|Behavior loop function for Coin|descriptionEnd| */
void bhv_coin_loop(void);
/* |description|Behavior loop function for Coin inside Boo|descriptionEnd| */
void bhv_coin_inside_boo_loop(void);
/* |description|Behavior init function for Coin formation|descriptionEnd| */
void bhv_coin_formation_init(void);
/* |description|Behavior loop function for Coin formation spawn|descriptionEnd| */
void bhv_coin_formation_spawn_loop(void);
/* |description|Behavior loop function for Coin formation|descriptionEnd| */
void bhv_coin_formation_loop(void);
/* |description|Behavior loop function for despawning Coin|descriptionEnd| */
void bhv_temp_coin_loop(void);
/* |description|Behavior loop function for Coin sparkles|descriptionEnd| */
void bhv_coin_sparkles_loop(void);
/* |description|Behavior loop function for golden Coin sparkles|descriptionEnd| */
void bhv_golden_coin_sparkles_loop(void);
/* |description|Behavior loop function for tiny wall star particle|descriptionEnd| */
void bhv_wall_tiny_star_particle_loop(void);
/* |description|Behavior loop function for tiny pound star particle|descriptionEnd| */
void bhv_pound_tiny_star_particle_loop(void);
/* |description|Behavior init function for tiny pound star particle|descriptionEnd| */
void bhv_pound_tiny_star_particle_init(void);
/* |description|Behavior loop function for tiny punch triangle|descriptionEnd| */
void bhv_punch_tiny_triangle_loop(void);
/* |description|Behavior init function for tiny punch triangle|descriptionEnd| */
void bhv_punch_tiny_triangle_init(void);
/* |description|Behavior loop function for tumbling bridge platform|descriptionEnd| */
void bhv_tumbling_bridge_platform_loop(void);
/* |description|Behavior loop function for tumbling bridge|descriptionEnd| */
void bhv_tumbling_bridge_loop(void);
/* |description|Behavior init function for elevator|descriptionEnd| */
void bhv_elevator_init(void);
/* |description|Behavior loop function for elevator|descriptionEnd| */
void bhv_elevator_loop(void);
/* |description|Behavior loop function for water mist|descriptionEnd| */
void bhv_water_mist_loop(void);
/* |description|Behavior loop function for water mist spawn|descriptionEnd| */
void bhv_water_mist_spawn_loop(void);
/* |description|Behavior loop function for water mist 2|descriptionEnd| */
void bhv_water_mist_2_loop(void);
/* |description|Behavior init function for pound white puffs|descriptionEnd| */
void bhv_pound_white_puffs_init(void);
/* |description|Behavior init function for ground sand|descriptionEnd| */
void bhv_ground_sand_init(void);
/* |description|Behavior init function for ground snow|descriptionEnd| */
void bhv_ground_snow_init(void);
/* |description|Behavior loop function for wind|descriptionEnd| */
void bhv_wind_loop(void);
/* |description|Behavior loop function for unused particle spawn|descriptionEnd| */
void bhv_unused_particle_spawn_loop(void);
/* |description|Behavior loop function for Ukiki cage Star|descriptionEnd| */
void bhv_ukiki_cage_star_loop(void);
/* |description|Behavior loop function for Ukiki cage|descriptionEnd| */
void bhv_ukiki_cage_loop(void);
/* |description|Behavior loop function for Bowser in the Fire Sea sinking platform|descriptionEnd| */
void bhv_bitfs_sinking_platform_loop(void);
/* |description|Behavior loop function for Bowser in the Fire Sea sinking cage platform|descriptionEnd| */
void bhv_bitfs_sinking_cage_platform_loop(void);
/* |description|Behavior loop function for Dire Dire Docks moving pole|descriptionEnd| */
void bhv_ddd_moving_pole_loop(void);
/* |description|Behavior init function for Bowser in the Dark World, Lethal Lava Land, and Bowser in the Fire Sea platform normals|descriptionEnd| */
void bhv_platform_normals_init(void);
/* |description|Behavior loop function for Lethal Lava Land and Bowser in the Fire Sea tilting inverted pyramid|descriptionEnd| */
void bhv_tilting_inverted_pyramid_loop(void);
/* |description|Behavior loop function for squishable platform|descriptionEnd| */
void bhv_squishable_platform_loop(void);
/* |description|Behavior loop function for beta moving flames spawn|descriptionEnd| */
void bhv_beta_moving_flames_spawn_loop(void);
/* |description|Behavior loop function for beta moving flames|descriptionEnd| */
void bhv_beta_moving_flames_loop(void);
/* |description|Behavior loop function for Rainbow Ride rotating bridge platform|descriptionEnd| */
void bhv_rr_rotating_bridge_platform_loop(void);
/* |description|Behavior loop function for flamethrower|descriptionEnd| */
void bhv_flamethrower_loop(void);
/* |description|Behavior loop function for flamethrower flame|descriptionEnd| */
void bhv_flamethrower_flame_loop(void);
/* |description|Behavior loop function for bouncing fireball|descriptionEnd| */
void bhv_bouncing_fireball_loop(void);
/* |description|Behavior loop function for bouncing fireball flame|descriptionEnd| */
void bhv_bouncing_fireball_flame_loop(void);
/* |description|Behavior loop function for Bowser shock wave|descriptionEnd| */
void bhv_bowser_shock_wave_loop(void);
/* |description|Behavior loop function for flame Mario|descriptionEnd| */
void bhv_flame_mario_loop(void);
/* |description|Behavior loop function for black smoke Mario|descriptionEnd| */
void bhv_black_smoke_mario_loop(void);
/* |description|Behavior loop function for black smoke Bowser|descriptionEnd| */
void bhv_black_smoke_bowser_loop(void);
/* |description|Behavior loop function for black smoke upward|descriptionEnd| */
void bhv_black_smoke_upward_loop(void);
/* |description|Behavior loop function for beta fish splash spawner|descriptionEnd| */
void bhv_beta_fish_splash_spawner_loop(void);
/* |description|Behavior loop function for Spindrift|descriptionEnd| */
void bhv_spindrift_loop(void);
/* |description|Behavior init function for Whomp's Fortress tower platform group|descriptionEnd| */
void bhv_tower_platform_group_init(void);
/* |description|Behavior loop function for Whomp's Fortress tower platform group|descriptionEnd| */
void bhv_tower_platform_group_loop(void);
/* |description|Behavior loop function for Whomp's Fortress sliding tower platform|descriptionEnd| */
void bhv_wf_sliding_tower_platform_loop(void);
/* |description|Behavior loop function for Whomp's Fortress elevator tower platform|descriptionEnd| */
void bhv_wf_elevator_tower_platform_loop(void);
/* |description|Behavior loop function for Whomp's Fortress solid tower platform|descriptionEnd| */
void bhv_wf_solid_tower_platform_loop(void);
/* |description|Behavior init function for snow leaf particle spawn|descriptionEnd| */
void bhv_snow_leaf_particle_spawn_init(void);
/* |description|Behavior loop function for tree snow or leaf particle|descriptionEnd| */
void bhv_tree_snow_or_leaf_loop(void);
/* |description|Behavior loop function for Piranha Plant bubble|descriptionEnd| */
void bhv_piranha_plant_bubble_loop(void);
/* |description|Behavior loop function for Piranha Plant waking bubbles|descriptionEnd| */
void bhv_piranha_plant_waking_bubbles_loop(void);
/* |description|Behavior loop function for Purple Switch|descriptionEnd| */
void bhv_purple_switch_loop(void);
/* |description|Behavior loop function for Wet Dry World hidden breakable box|descriptionEnd| */
void bhv_hidden_object_loop(void);
/* |description|Behavior loop function for breakable box|descriptionEnd| */
void bhv_breakable_box_loop(void);
/* |description|Behavior loop function for pushable metal box|descriptionEnd| */
void bhv_pushable_loop(void);
/* |description|Behavior init function for marking what room an object is in|descriptionEnd| */
void bhv_init_room(void);
/* |description|Behavior loop function for small water wave|descriptionEnd| */
void bhv_small_water_wave_loop(void);
/* |description|Behavior init function for Yellow Coin|descriptionEnd| */
void bhv_yellow_coin_init(void);
/* |description|Behavior loop function for Yellow Coin|descriptionEnd| */
void bhv_yellow_coin_loop(void);
/* |description|Behavior loop function for Bowser in the Dark World squarish path moving|descriptionEnd| */
void bhv_squarish_path_moving_loop(void);
/* |description|Behavior init function for Bowser in the Dark World squarish path parent|descriptionEnd| */
void bhv_squarish_path_parent_init(void);
/* |description|Behavior loop function for Bowser in the Dark World Ssuarish path parent|descriptionEnd| */
void bhv_squarish_path_parent_loop(void);
/* |description|Behavior loop function for Heave ho|descriptionEnd| */
void bhv_heave_ho_loop(void);
/* |description|Behavior loop function for Heave ho throwing Mario|descriptionEnd| */
void bhv_heave_ho_throw_mario_loop(void);
/* |description|Behavior loop function for Cool, Cool Mountain touched Star spawn|descriptionEnd| */
void bhv_ccm_touched_star_spawn_loop(void);
/* |description|Behavior loop function for unused poundable platform|descriptionEnd| */
void bhv_unused_poundable_platform(void);
/* |description|Behavior loop function for beta trampoline top|descriptionEnd| */
void bhv_beta_trampoline_top_loop(void);
/* |description|Behavior loop function for beta trampoline spring|descriptionEnd| */
void bhv_beta_trampoline_spring_loop(void);
/* |description|Behavior loop function for jumping box|descriptionEnd| */
void bhv_jumping_box_loop(void);
/* |description|Behavior init function for Boo cage|descriptionEnd| */
void bhv_boo_cage_init(void);
/* |description|Behavior loop function for Boo cage|descriptionEnd| */
void bhv_boo_cage_loop(void);
/* |description|Behavior init function for Bowser key|descriptionEnd| */
void bhv_bowser_key_init(void);
/* |description|Behavior loop function for Bowser key|descriptionEnd| */
void bhv_bowser_key_loop(void);
/* |description|Behavior init function for Grand Star|descriptionEnd| */
void bhv_grand_star_init(void);
/* |description|Behavior loop function for Grand Star|descriptionEnd| */
void bhv_grand_star_loop(void);
/* |description|Behavior loop function for beta boo key|descriptionEnd| */
void bhv_beta_boo_key_loop(void);
/* |description|Behavior loop function for alpha boo key|descriptionEnd| */
void bhv_alpha_boo_key_loop(void);
/* |description|Behavior init function for Bullet Bill|descriptionEnd| */
void bhv_bullet_bill_init(void);
/* |description|Behavior loop function for Bullet Bill|descriptionEnd| */
void bhv_bullet_bill_loop(void);
/* |description|Behavior init function for White puff smoke|descriptionEnd| */
void bhv_white_puff_smoke_init(void);
/* |description|Behavior init function for Bowser tail anchor|descriptionEnd| */
void bhv_bowser_tail_anchor_init(void);
/* |description|Behavior loop function for Bowser tail anchor|descriptionEnd| */
void bhv_bowser_tail_anchor_loop(void);
/* |description|Behavior init function for Bowser|descriptionEnd| */
void bhv_bowser_init(void);
/* |description|Behavior loop function for Bowser|descriptionEnd| */
void bhv_bowser_loop(void);
/* |description|Behavior init function for Bowser body anchor|descriptionEnd| */
void bhv_bowser_body_anchor_init(void);
/* |description|Behavior loop function for Bowser body anchor|descriptionEnd| */
void bhv_bowser_body_anchor_loop(void);
/* |description|Behavior loop function for Bowser flame spawn|descriptionEnd| */
void bhv_bowser_flame_spawn_loop(void);
/* |description|Behavior init function for tilting Bowser in the Fire Sea arena platform|descriptionEnd| */
void bhv_tilting_bowser_lava_platform_init(void);
/* |description|Behavior loop function for falling Bowser in the Sky arena platform|descriptionEnd| */
void bhv_falling_bowser_platform_loop(void);
/* |description|Behavior init function for Blue Bowser flame|descriptionEnd| */
void bhv_blue_bowser_flame_init(void);
/* |description|Behavior loop function for Blue Bowser flame|descriptionEnd| */
void bhv_blue_bowser_flame_loop(void);
/* |description|Behavior init function for flame floating landing|descriptionEnd| */
void bhv_flame_floating_landing_init(void);
/* |description|Behavior loop function for flame floating landing|descriptionEnd| */
void bhv_flame_floating_landing_loop(void);
/* |description|Behavior loop function for blue flames group|descriptionEnd| */
void bhv_blue_flames_group_loop(void);
/* |description|Behavior init function for flame bouncing|descriptionEnd| */
void bhv_flame_bouncing_init(void);
/* |description|Behavior loop function for flame bouncing|descriptionEnd| */
void bhv_flame_bouncing_loop(void);
/* |description|Behavior init function for flame moving forward growing|descriptionEnd| */
void bhv_flame_moving_forward_growing_init(void);
/* |description|Behavior loop function for flame moving forward growing|descriptionEnd| */
void bhv_flame_moving_forward_growing_loop(void);
/* |description|Behavior init function for Bowser flame|descriptionEnd| */
void bhv_flame_bowser_init(void);
/* |description|Behavior loop function for Bowser flame|descriptionEnd| */
void bhv_flame_bowser_loop(void);
/* |description|Behavior init function for large flame burning out|descriptionEnd| */
void bhv_flame_large_burning_out_init(void);
/* |description|Behavior loop function for blue fish movement|descriptionEnd| */
void bhv_blue_fish_movement_loop(void);
/* |description|Behavior loop function for tank fish group|descriptionEnd| */
void bhv_tank_fish_group_loop(void);
/* |description|Behavior init function for checkerboard elevator group|descriptionEnd| */
void bhv_checkerboard_elevator_group_init(void);
/* |description|Behavior loop function for checkerboard elevator group|descriptionEnd| */
void bhv_checkerboard_elevator_group_loop(void);
/* |description|Behavior init function for checkerboard platform|descriptionEnd| */
void bhv_checkerboard_platform_init(void);
/* |description|Behavior loop function for checkerboard platform|descriptionEnd| */
void bhv_checkerboard_platform_loop(void);
/* |description|Behavior loop function for Bowser key unlock door|descriptionEnd| */
void bhv_bowser_key_unlock_door_loop(void);
/* |description|Behavior loop function for Bowser key course exit|descriptionEnd| */
void bhv_bowser_key_course_exit_loop(void);
/* |description|Behavior init function for invisible objects under the Castle bridge|descriptionEnd| */
void bhv_invisible_objects_under_bridge_init(void);
/* |description|Behavior loop function for Invisible objects under the Castle bridge|descriptionEnd| */
void bhv_invisible_objects_under_bridge_loop(void);
/* |description|Behavior init function for Castle Basement water level pillar|descriptionEnd| */
void bhv_water_level_pillar_init(void);
/* |description|Behavior loop function for Castle Basement water level pillar|descriptionEnd| */
void bhv_water_level_pillar_loop(void);
/* |description|Behavior loop function for Castle Basement Dire Dire Docks warp collision|descriptionEnd| */
void bhv_ddd_warp_loop(void);
/* |description|Behavior loop function for moat grills|descriptionEnd| */
void bhv_moat_grills_loop(void);
/* |description|Behavior loop function for rotating clock arm|descriptionEnd| */
void bhv_rotating_clock_arm_loop(void);
/* |description|Behavior init function for Ukiki|descriptionEnd| */
void bhv_ukiki_init(void);
/* |description|Behavior loop function for Ukiki|descriptionEnd| */
void bhv_ukiki_loop(void);
/* |description|Behavior loop function for Lethal Lava Land sinking rock block|descriptionEnd| */
void bhv_lll_sinking_rock_block_loop(void);
/* |description|Behavior loop function for Lethal Lava Land moving octagonal mesh platform|descriptionEnd| */
void bhv_lll_moving_octagonal_mesh_platform_loop(void);
/* |description|Behavior loop function for Lethal Lava Land rotating block fire bars|descriptionEnd| */
void bhv_lll_rotating_block_fire_bars_loop(void);
/* |description|Behavior loop function for Lethal Lava Land rotating hex flame|descriptionEnd| */
void bhv_lll_rotating_hex_flame_loop(void);
/* |description|Behavior loop function for Lethal Lava Land wood piece|descriptionEnd| */
void bhv_lll_wood_piece_loop(void);
/* |description|Behavior loop function for Lethal Lava Land floating wood bridge|descriptionEnd| */
void bhv_lll_floating_wood_bridge_loop(void);
/* |description|Behavior loop function for Volcano flames|descriptionEnd| */
void bhv_volcano_flames_loop(void);
/* |description|Behavior loop function for Lethal Lava Land rotating hexagonal ring|descriptionEnd| */
void bhv_lll_rotating_hexagonal_ring_loop(void);
/* |description|Behavior loop function for Lethal Lava Land sinking rectangular platform|descriptionEnd| */
void bhv_lll_sinking_rectangular_platform_loop(void);
/* |description|Behavior loop function for Lethal Lava Land sinking square platforms|descriptionEnd| */
void bhv_lll_sinking_square_platforms_loop(void);
/* |description|Behavior loop function for Koopa Shell|descriptionEnd| */
void bhv_koopa_shell_loop(void);
/* |description|Behavior loop function for Koopa Shell flame|descriptionEnd| */
void bhv_koopa_shell_flame_loop(void);
/* |description|Behavior loop function for Tox Box|descriptionEnd| */
void bhv_tox_box_loop(void);
/* |description|
Checks if Mario is moving fast enough to make Piranha Plant bite.
This one is a mouthful
|descriptionEnd| */
s32 mario_moving_fast_enough_to_make_piranha_plant_bite(void);
/* |description|Behavior loop function for Piranha Plant|descriptionEnd| */
void bhv_piranha_plant_loop(void);
/* |description|Behavior loop function for Lethal Lava Land bowser puzzle piece|descriptionEnd| */
void bhv_lll_bowser_puzzle_piece_loop(void);
/* |description|Behavior loop function for Lethal Lava Land bowser puzzle|descriptionEnd| */
void bhv_lll_bowser_puzzle_loop(void);
/* |description|Behavior loop function for Tuxie's mother|descriptionEnd| */
void bhv_tuxies_mother_loop(void);
/* |description|Behavior loop function for small penguin|descriptionEnd| */
void bhv_small_penguin_loop(void);
/* |description|Behavior loop function for fish spawner|descriptionEnd| */
void bhv_fish_spawner_loop(void);
/* |description|Behavior loop function for fish|descriptionEnd| */
void bhv_fish_loop(void);
/* |description|Behavior loop function for Wet Dry World express elevator|descriptionEnd| */
void bhv_wdw_express_elevator_loop(void);
/* |description|Behavior loop function for Bub spawner|descriptionEnd| */
void bhv_bub_spawner_loop(void);
/* |description|Behavior loop function for Bub|descriptionEnd| */
void bhv_bub_loop(void);
/* |description|Behavior init function for Exclamation Box|descriptionEnd| */
void bhv_exclamation_box_init(void);
/* |description|Behavior loop function for Exclamation Box|descriptionEnd| */
void bhv_exclamation_box_loop(void);
/* |description|Behavior loop function for rotating exclamation mark|descriptionEnd| */
void bhv_rotating_exclamation_box_loop(void);
/* |description|Behavior init function for sound spawner|descriptionEnd| */
void bhv_sound_spawner_init(void);
/* |description|Behavior loop function for Bowser's submarine|descriptionEnd| */
void bhv_bowsers_sub_loop(void);
/* |description|Behavior loop function for Sushi Shark|descriptionEnd| */
void bhv_sushi_shark_loop(void);
/* |description|Behavior loop function for Sushi Shark collision|descriptionEnd| */
void bhv_sushi_shark_collision_loop(void);
/* |description|Behavior loop function for Jolly Roger Bay sliding box|descriptionEnd| */
void bhv_jrb_sliding_box_loop(void);
/* |description|Behavior loop function for Jolly Roger Bay ship part 3|descriptionEnd| */
void bhv_ship_part_3_loop(void);
/* |description|Behavior loop function for Jolly Roger Bay sunken ship part|descriptionEnd| */
void bhv_sunken_ship_part_loop(void);
/* |description|Behavior loop function for white puff 1|descriptionEnd| */
void bhv_white_puff_1_loop(void);
/* |description|Behavior loop function for white puff 2|descriptionEnd| */
void bhv_white_puff_2_loop(void);
/* |description|Behavior loop function for Blue Coin number|descriptionEnd| */
void bhv_blue_coin_number_loop(void);
/* |description|Behavior init function for Blue Coin switch|descriptionEnd| */
void bhv_blue_coin_switch_init(void);
/* |description|Behavior loop function for Blue Coin switch|descriptionEnd| */
void bhv_blue_coin_switch_loop(void);
/* |description|Behavior loop function for hidden Blue Coin|descriptionEnd| */
void bhv_hidden_blue_coin_loop(void);
/* |description|Behavior loop function for openable cage door|descriptionEnd| */
void bhv_openable_cage_door_loop(void);
/* |description|Behavior loop function for openable grill|descriptionEnd| */
void bhv_openable_grill_loop(void);
/* |description|Behavior loop function for Wet Dry World water level diamond|descriptionEnd| */
void bhv_water_level_diamond_loop(void);
/* |description|Behavior init function for changing water level, called when Wet Dry World is loaded|descriptionEnd| */
void bhv_init_changing_water_level_loop(void);
/* |description|Behavior loop function for Tweester sand particle|descriptionEnd| */
void bhv_tweester_sand_particle_loop(void);
/* |description|Behavior loop function for Tweester|descriptionEnd| */
void bhv_tweester_loop(void);
/* |description|Behavior loop function for Merry Go Round Boo manager|descriptionEnd| */
void bhv_merry_go_round_boo_manager_loop(void);
/* |description|Behavior loop function for animated texture|descriptionEnd| */
void bhv_animated_texture_loop(void);
/* |description|Behavior loop function for the Boo inside the Castle|descriptionEnd| */
void bhv_boo_in_castle_loop(void);
/* |description|Behavior init function for Boo with cage|descriptionEnd| */
void bhv_boo_with_cage_init(void);
/* |description|Behavior loop function for Boo with cage|descriptionEnd| */
void bhv_boo_with_cage_loop(void);
/* |description|Behavior init function for Boo|descriptionEnd| */
void bhv_boo_init(void);
/* |description|Behavior loop function for Big Boo|descriptionEnd| */
void bhv_big_boo_loop(void);
/* |description|Behavior init function for Courtyard Boo triplet|descriptionEnd| */
void bhv_courtyard_boo_triplet_init(void);
/* |description|Sets the secondary camera focus|descriptionEnd| */
void obj_set_secondary_camera_focus(void);
/* |description|Behavior loop function for Boo|descriptionEnd| */
void bhv_boo_loop(void);
/* |description|Behavior loop function for Boo boss spawned bridge|descriptionEnd| */
void bhv_boo_boss_spawned_bridge_loop(void);
/* |description|Behavior loop function for Big Boo's Haunt tilting trap platform|descriptionEnd| */
void bhv_bbh_tilting_trap_platform_loop(void);
/* |description|Behavior loop function for Big Boo's Haunt haunted bookshelf|descriptionEnd| */
void bhv_haunted_bookshelf_loop(void);
/* |description|Behavior loop function for Big Boo's Haunt Merry Go Round|descriptionEnd| */
void bhv_merry_go_round_loop(void);
/* |description|Behavior loop function for playing a jingle when in a 200 unit radius|descriptionEnd| */
void bhv_play_music_track_when_touched_loop(void);
/* |description|Behavior loop function for beta Bowser anchor|descriptionEnd| */
void bhv_beta_bowser_anchor_loop(void);
/* |description|Behavior loop function for static checkered platform|descriptionEnd| */
void bhv_static_checkered_platform_loop(void);
/* |description|Behavior init function for Bowser in the Dark World floor trap manager|descriptionEnd| */
void bhv_castle_floor_trap_init(void);
/* |description|Behavior loop function for Bowser in the Dark World floor trap manager|descriptionEnd| */
void bhv_castle_floor_trap_loop(void);
/* |description|Behavior loop function for Bowser in the Dark World floor trap|descriptionEnd| */
void bhv_floor_trap_in_castle_loop(void);
/* |description|Behavior loop function for sparkle spawner|descriptionEnd| */
void bhv_sparkle_spawn_loop(void);
/* |description|Behavior loop function for Scuttlebug|descriptionEnd| */
void bhv_scuttlebug_loop(void);
/* |description|Behavior loop function for Scuttlebug spawner|descriptionEnd| */
void bhv_scuttlebug_spawn_loop(void);
/* |description|Behavior loop function for Whomp|descriptionEnd| */
void bhv_whomp_loop(void);
/* |description|Behavior init function for spawning water splash droplets|descriptionEnd| */
void bhv_water_splash_spawn_droplets(void);
/* |description|Behavior loop function for water droplet|descriptionEnd| */
void bhv_water_droplet_loop(void);
/* |description|Behavior init function for water droplet splash|descriptionEnd| */
void bhv_water_droplet_splash_init(void);
/* |description|Behavior init function for bubble splash|descriptionEnd| */
void bhv_bubble_splash_init(void);
/* |description|Behavior loop function for idle water wave|descriptionEnd| */
void bhv_idle_water_wave_loop(void);
/* |description|Behavior init function for shallow water splash|descriptionEnd| */
void bhv_shallow_water_splash_init(void);
/* |description|Behavior loop function for shrinking water trail|descriptionEnd| */
void bhv_wave_trail_shrink(void);
/* |description|Behavior loop function for strong wind particle|descriptionEnd| */
void bhv_strong_wind_particle_loop(void);
/* |description|Behavior loop function for Snowman's Land snowman wind|descriptionEnd| */
void bhv_sl_snowman_wind_loop(void);
/* |description|Behavior loop function for Snowman's Land walking penguin|descriptionEnd| */
void bhv_sl_walking_penguin_loop(void);
/* |description|Behavior init function for File Select button|descriptionEnd| */
void bhv_menu_button_init(void);
/* |description|Behavior loop function for File Select button|descriptionEnd| */
void bhv_menu_button_loop(void);
/* |description|Behavior init function for File Select button manager|descriptionEnd| */
void bhv_menu_button_manager_init(void);
/* |description|Behavior loop function for File Select button manager|descriptionEnd| */
void bhv_menu_button_manager_loop(void);
/* |description|Behavior loop function for Act Selector star type|descriptionEnd| */
void bhv_act_selector_star_type_loop(void);
/* |description|Behavior init function for Act Selector|descriptionEnd| */
void bhv_act_selector_init(void);
/* |description|Behavior loop function for Act Selector|descriptionEnd| */
void bhv_act_selector_loop(void);
/* |description|Behavior init function for moving Yellow Coin|descriptionEnd| */
void bhv_moving_yellow_coin_init(void);
/* |description|Behavior loop function for moving Yellow Coin|descriptionEnd| */
void bhv_moving_yellow_coin_loop(void);
/* |description|Behavior init function for moving Blue Coin|descriptionEnd| */
void bhv_moving_blue_coin_init(void);
/* |description|Behavior loop function for moving Blue Coin|descriptionEnd| */
void bhv_moving_blue_coin_loop(void);
/* |description|Behavior init function for Blue Coin sliding jumping|descriptionEnd| */
void bhv_blue_coin_sliding_jumping_init(void);
/* |description|Behavior loop function for Blue Coin sliding|descriptionEnd| */
void bhv_blue_coin_sliding_loop(void);
/* |description|Behavior loop function for Blue Coin jumping|descriptionEnd| */
void bhv_blue_coin_jumping_loop(void);
/* |description|Behavior init function for seaweed|descriptionEnd| */
void bhv_seaweed_init(void);
/* |description|Behavior init function for seaweed bundle|descriptionEnd| */
void bhv_seaweed_bundle_init(void);
/* |description|Behavior init function for Bob-omb|descriptionEnd| */
void bhv_bobomb_init(void);
/* |description|Behavior loop function for Bob-omb|descriptionEnd| */
void bhv_bobomb_loop(void);
/* |description|Behavior init function for Bob-omb fuse smoke|descriptionEnd| */
void bhv_bobomb_fuse_smoke_init(void);
/* |description|Behavior init function for Bob-omb buddy|descriptionEnd| */
void bhv_bobomb_buddy_init(void);
/* |description|Behavior loop function for Bob-omb buddy|descriptionEnd| */
void bhv_bobomb_buddy_loop(void);
/* |description|Behavior init function for cannon closed|descriptionEnd| */
void bhv_cannon_closed_init(void);
/* |description|Behavior loop function for cannon closed|descriptionEnd| */
void bhv_cannon_closed_loop(void);
/* |description|Behavior init function for whirlpool|descriptionEnd| */
void bhv_whirlpool_init(void);
/* |description|Behavior loop function for whirlpool|descriptionEnd| */
void bhv_whirlpool_loop(void);
/* |description|Behavior loop function for jet stream|descriptionEnd| */
void bhv_jet_stream_loop(void);
/* |description|Behavior init function for Homing Amp|descriptionEnd| */
void bhv_homing_amp_init(void);
/* |description|Behavior loop function for Homing Amp|descriptionEnd| */
void bhv_homing_amp_loop(void);
/* |description|Behavior init function for Circling Amp|descriptionEnd| */
void bhv_circling_amp_init(void);
/* |description|Behavior loop function for Circling Amp|descriptionEnd| */
void bhv_circling_amp_loop(void);
/* |description|Behavior init function for Butterfly|descriptionEnd| */
void bhv_butterfly_init(void);
/* |description|Behavior loop function for Butterfly|descriptionEnd| */
void bhv_butterfly_loop(void);
/* |description|Behavior init function for Hoot|descriptionEnd| */
void bhv_hoot_init(void);
/* |description|Behavior loop function for Hoot|descriptionEnd| */
void bhv_hoot_loop(void);
/* |description|Behavior init function for beta holdable object|descriptionEnd| */
void bhv_beta_holdable_object_init(void);
/* |description|Behavior loop function for beta holdable object|descriptionEnd| */
void bhv_beta_holdable_object_loop(void);
/* |description|Behavior init function for bubble object|descriptionEnd| */
void bhv_object_bubble_init(void);
/* |description|Behavior loop function for bubble object|descriptionEnd| */
void bhv_object_bubble_loop(void);
/* |description|Behavior init function for water wave object|descriptionEnd| */
void bhv_object_water_wave_init(void);
/* |description|Behavior loop function for water wave object|descriptionEnd| */
void bhv_object_water_wave_loop(void);
/* |description|Behavior init function for explosion|descriptionEnd| */
void bhv_explosion_init(void);
/* |description|Behavior loop function for explosion|descriptionEnd| */
void bhv_explosion_loop(void);
/* |description|Behavior init function for Bob-omb and Bully death smoke|descriptionEnd| */
void bhv_bobomb_bully_death_smoke_init(void);
/* |description|Behavior init function for Bob-omb explosion bubble|descriptionEnd| */
void bhv_bobomb_explosion_bubble_init(void);
/* |description|Behavior loop function for Bob-omb explosion bubble|descriptionEnd| */
void bhv_bobomb_explosion_bubble_loop(void);
/* |description|Behavior loop function for respawner|descriptionEnd| */
void bhv_respawner_loop(void);
/* |description|Behavior init function for Small Bully|descriptionEnd| */
void bhv_small_bully_init(void);
/* |description|Behavior loop function for Bully|descriptionEnd| */
void bhv_bully_loop(void);
/* |description|Behavior init function for Big Bully|descriptionEnd| */
void bhv_big_bully_init(void);
/* |description|Behavior init function for Big Bully with minions|descriptionEnd| */
void bhv_big_bully_with_minions_init(void);
/* |description|Behavior loop function for Big Bully with minions|descriptionEnd| */
void bhv_big_bully_with_minions_loop(void);
/* |description|Behavior loop function for jet stream ring spawner|descriptionEnd| */
void bhv_jet_stream_ring_spawner_loop(void);
/* |description|Behavior init function for jet stream water ring|descriptionEnd| */
void bhv_jet_stream_water_ring_init(void);
/* |description|Behavior loop function for jet stream water ring|descriptionEnd| */
void bhv_jet_stream_water_ring_loop(void);
/* |description|Behavior init function for Manta Ray water ring|descriptionEnd| */
void bhv_manta_ray_water_ring_init(void);
/* |description|Behavior loop function for Manta Ray water ring|descriptionEnd| */
void bhv_manta_ray_water_ring_loop(void);
/* |description|Behavior loop function for Bowser bomb|descriptionEnd| */
void bhv_bowser_bomb_loop(void);
/* |description|Behavior loop function for Bowser bomb explosion|descriptionEnd| */
void bhv_bowser_bomb_explosion_loop(void);
/* |description|Behavior loop function for Bowser bomb smoke|descriptionEnd| */
void bhv_bowser_bomb_smoke_loop(void);
/* |description|Behavior init function for Celebration Star|descriptionEnd| */
void bhv_celebration_star_init(void);
/* |description|Behavior loop function for Celebration Star|descriptionEnd| */
void bhv_celebration_star_loop(void);
/* |description|Behavior loop function for Celebration Star sparkle|descriptionEnd| */
void bhv_celebration_star_sparkle_loop(void);
/* |description|Behavior loop function for Star and key collection puff spawner|descriptionEnd| */
void bhv_star_key_collection_puff_spawner_loop(void);
/* |description|Behavior init function for Lethal Lava Land drawbridge spawner|descriptionEnd| */
void bhv_lll_drawbridge_spawner_init(void);
/* |description|Behavior loop function for Lethal Lava Land drawbridge spawner|descriptionEnd| */
void bhv_lll_drawbridge_spawner_loop(void);
/* |description|Behavior loop function for Lethal Lava Land drawbridge|descriptionEnd| */
void bhv_lll_drawbridge_loop(void);
/* |description|Behavior init function for Small Bomp (Whomp's Fortress moving wall with eyes)|descriptionEnd| */
void bhv_small_bomp_init(void);
/* |description|Behavior loop function for Small Bomp (Whomp's Fortress moving wall with eyes)|descriptionEnd| */
void bhv_small_bomp_loop(void);
/* |description|Behavior init function for Large Bomp (Whomp's Fortress moving wall with eyes)|descriptionEnd| */
void bhv_large_bomp_init(void);
/* |description|Behavior loop function for Large Bomp (Whomp's Fortress moving wall with eyes)|descriptionEnd| */
void bhv_large_bomp_loop(void);
/* |description|Behavior init function for Whomp's Fortress sliding platform|descriptionEnd| */
void bhv_wf_sliding_platform_init(void);
/* |description|Behavior loop function for Whomp's Fortress sliding platform|descriptionEnd| */
void bhv_wf_sliding_platform_loop(void);
/* |description|Behavior init function for Moneybag|descriptionEnd| */
void bhv_moneybag_init(void);
/* |description|Behavior loop function for Moneybag|descriptionEnd| */
void bhv_moneybag_loop(void);
/* |description|Behavior loop function for Moneybag hidden|descriptionEnd| */
void bhv_moneybag_hidden_loop(void);
/* |description|Behavior init function for Bob-omb Battlefield pit bowling ball|descriptionEnd| */
void bhv_bob_pit_bowling_ball_init(void);
/* |description|Behavior loop function for Bob-omb Battlefield pit bowling ball|descriptionEnd| */
void bhv_bob_pit_bowling_ball_loop(void);
/* |description|Behavior init function for free bowling ball|descriptionEnd| */
void bhv_free_bowling_ball_init(void);
/* |description|Behavior loop function for free bowling ball|descriptionEnd| */
void bhv_free_bowling_ball_loop(void);
/* |description|Behavior init function for bowling ball|descriptionEnd| */
void bhv_bowling_ball_init(void);
/* |description|Behavior loop function for bowling ball|descriptionEnd| */
void bhv_bowling_ball_loop(void);
/* |description|Behavior init function for generic bowling ball spawner|descriptionEnd| */
void bhv_generic_bowling_ball_spawner_init(void);
/* |description|Behavior loop function for generic bowling ball spawner|descriptionEnd| */
void bhv_generic_bowling_ball_spawner_loop(void);
/* |description|Behavior loop function for Tiny Huge Island bowling ball spawner|descriptionEnd| */
void bhv_thi_bowling_ball_spawner_loop(void);
/* |description|Behavior init function for Rainbow Ride cruiser wing|descriptionEnd| */
void bhv_rr_cruiser_wing_init(void);
/* |description|Behavior loop function for Rainbow Ride cruiser wing|descriptionEnd| */
void bhv_rr_cruiser_wing_loop(void);
/* |description|Behavior init function for Spindel|descriptionEnd| */
void bhv_spindel_init(void);
/* |description|Behavior loop function for Spindel|descriptionEnd| */
void bhv_spindel_loop(void);
/* |description|Behavior init function for Ssl moving pyramid wall|descriptionEnd| */
void bhv_ssl_moving_pyramid_wall_init(void);
/* |description|Behavior loop function for Ssl moving pyramid wall|descriptionEnd| */
void bhv_ssl_moving_pyramid_wall_loop(void);
/* |description|Behavior init function for Pyramid elevator|descriptionEnd| */
void bhv_pyramid_elevator_init(void);
/* |description|Behavior loop function for Pyramid elevator|descriptionEnd| */
void bhv_pyramid_elevator_loop(void);
/* |description|Behavior loop function for Pyramid elevator trajectory marker ball|descriptionEnd| */
void bhv_pyramid_elevator_trajectory_marker_ball_loop(void);
/* |description|Behavior init function for Pyramid top|descriptionEnd| */
void bhv_pyramid_top_init(void);
/* |description|Behavior loop function for Pyramid top|descriptionEnd| */
void bhv_pyramid_top_loop(void);
/* |description|Behavior init function for Pyramid top fragment|descriptionEnd| */
void bhv_pyramid_top_fragment_init(void);
/* |description|Behavior loop function for Pyramid top fragment|descriptionEnd| */
void bhv_pyramid_top_fragment_loop(void);
/* |description|Behavior loop function for Pyramid pillar touch detector|descriptionEnd| */
void bhv_pyramid_pillar_touch_detector_loop(void);
/* |description|Behavior loop function for waterfall sound|descriptionEnd| */
void bhv_waterfall_sound_loop(void);
/* |description|Behavior loop function for volcano sound|descriptionEnd| */
void bhv_volcano_sound_loop(void);
/* |description|Behavior init function for castle flag|descriptionEnd| */
void bhv_castle_flag_init(void);
/* |description|Behavior loop function for birds sound|descriptionEnd| */
void bhv_birds_sound_loop(void);
/* |description|Behavior init function for ambient sounds|descriptionEnd| */
void bhv_ambient_sounds_init(void);
/* |description|Behavior loop function for sand sound|descriptionEnd| */
void bhv_sand_sound_loop(void);
/* |description|Behavior init function for Castle cannon grate|descriptionEnd| */
void bhv_castle_cannon_grate_init(void);
/* |description|Behavior init function for Snowman's bottom|descriptionEnd| */
void bhv_snowmans_bottom_init(void);
/* |description|Behavior loop function for Snowman's bottom|descriptionEnd| */
void bhv_snowmans_bottom_loop(void);
/* |description|Behavior init function for Snowman's head|descriptionEnd| */
void bhv_snowmans_head_init(void);
/* |description|Behavior loop function for Snowman's head|descriptionEnd| */
void bhv_snowmans_head_loop(void);
/* |description|Behavior loop function for Snowman's body checkpoint|descriptionEnd| */
void bhv_snowmans_body_checkpoint_loop(void);
/* |description|Behavior init function for big boulder|descriptionEnd| */
void bhv_big_boulder_init(void);
/* |description|Behavior loop function for big boulder|descriptionEnd| */
void bhv_big_boulder_loop(void);
/* |description|Behavior loop function for big boulder generator|descriptionEnd| */
void bhv_big_boulder_generator_loop(void);
/* |description|Behavior init function for Wing Cap|descriptionEnd| */
void bhv_wing_cap_init(void);
/* |description|Behavior loop function for Wing and Vanish caps|descriptionEnd| */
void bhv_wing_vanish_cap_loop(void);
/* |description|Behavior init function for Metal Cap|descriptionEnd| */
void bhv_metal_cap_init(void);
/* |description|Behavior loop function for Metal Cap|descriptionEnd| */
void bhv_metal_cap_loop(void);
/* |description|Behavior init function for Normal Cap|descriptionEnd| */
void bhv_normal_cap_init(void);
/* |description|Behavior loop function for Normal Cap|descriptionEnd| */
void bhv_normal_cap_loop(void);
/* |description|Behavior init function for Vanish Cap|descriptionEnd| */
void bhv_vanish_cap_init(void);
/* |description|Behavior loop function for Star number|descriptionEnd| */
void bhv_star_number_loop(void);
/* |description|Spawns a star number|descriptionEnd| */
void spawn_star_number(void);
/* |description|Behavior init function for collectable Star|descriptionEnd| */
void bhv_collect_star_init(void);
/* |description|Behavior loop function for collectable Star|descriptionEnd| */
void bhv_collect_star_loop(void);
/* |description|Behavior init function for Star spawn|descriptionEnd| */
void bhv_star_spawn_init(void);
/* |description|Behavior loop function for Star spawn|descriptionEnd| */
void bhv_star_spawn_loop(void);
/* |description|Behavior init function for Hidden Red Coin Star|descriptionEnd| */
void bhv_hidden_red_coin_star_init(void);
/* |description|Behavior loop function for Hidden Red Coin Star|descriptionEnd| */
void bhv_hidden_red_coin_star_loop(void);
/* |description|Behavior init function for Red Coin|descriptionEnd| */
void bhv_red_coin_init(void);
/* |description|Behavior loop function for Red Coin|descriptionEnd| */
void bhv_red_coin_loop(void);
/* |description|Behavior loop function for Bowser course Red Coin Star|descriptionEnd| */
void bhv_bowser_course_red_coin_star_loop(void);
/* |description|Behavior init function for Secret Star|descriptionEnd| */
void bhv_hidden_star_init(void);
/* |description|Behavior loop function for Secret Star|descriptionEnd| */
void bhv_hidden_star_loop(void);
/* |description|Behavior loop function for Secrets|descriptionEnd| */
void bhv_hidden_star_trigger_loop(void);
/* |description|Behavior init function for Tall, Tall Mountain rolling log|descriptionEnd| */
void bhv_ttm_rolling_log_init(void);
/* |description|Behavior loop function for rolling log|descriptionEnd| */
void bhv_rolling_log_loop(void);
/* |description|Behavior init function for Lethal Lava Land rolling log|descriptionEnd| */
void bhv_lll_rolling_log_init(void);
/* |description|Behavior init function for 1-Up trigger|descriptionEnd| */
void bhv_1up_trigger_init(void);
/* |description|Behavior init function for common 1-Up|descriptionEnd| */
void bhv_1up_common_init(void);
/* |description|Behavior loop function for walking 1-Up|descriptionEnd| */
void bhv_1up_walking_loop(void);
/* |description|Behavior loop function for running away 1-Up|descriptionEnd| */
void bhv_1up_running_away_loop(void);
/* |description|Behavior loop function for sliding 1-Up|descriptionEnd| */
void bhv_1up_sliding_loop(void);
/* |description|Behavior init function for 1-Up|descriptionEnd| */
void bhv_1up_init(void);
/* |description|Behavior loop function for 1-Up|descriptionEnd| */
void bhv_1up_loop(void);
/* |description|Behavior loop function for jump on approach 1-Up|descriptionEnd| */
void bhv_1up_jump_on_approach_loop(void);
/* |description|Behavior loop function for hidden 1-Up|descriptionEnd| */
void bhv_1up_hidden_loop(void);
/* |description|Behavior loop function for hidden 1-Up trigger|descriptionEnd| */
void bhv_1up_hidden_trigger_loop(void);
/* |description|Behavior loop function for hidden 1-Up in pole (Green Demon)|descriptionEnd| */
void bhv_1up_hidden_in_pole_loop(void);
/* |description|Behavior loop function for 1-Up hidden in pole trigger|descriptionEnd| */
void bhv_1up_hidden_in_pole_trigger_loop(void);
/* |description|Behavior loop function for 1-Up hidden in pole spawner|descriptionEnd| */
void bhv_1up_hidden_in_pole_spawner_loop(void);
/* |description|Behavior init function for controllable platform|descriptionEnd| */
void bhv_controllable_platform_init(void);
/* |description|Behavior loop function for controllable platform|descriptionEnd| */
void bhv_controllable_platform_loop(void);
/* |description|Behavior loop function for controllable sub platform|descriptionEnd| */
void bhv_controllable_platform_sub_loop(void);
/* |description|Behavior init function for small breakable box|descriptionEnd| */
void bhv_breakable_box_small_init(void);
/* |description|Behavior loop function for small breakable box|descriptionEnd| */
void bhv_breakable_box_small_loop(void);
/* |description|Behavior loop function for sliding snow mound|descriptionEnd| */
void bhv_sliding_snow_mound_loop(void);
/* |description|Behavior loop function for snow mound spawn|descriptionEnd| */
void bhv_snow_mound_spawn_loop(void);
/* |description|Behavior loop function for floating platform|descriptionEnd| */
void bhv_floating_platform_loop(void);
/* |description|Behavior loop function for Wet Dry World arrow lift|descriptionEnd| */
void bhv_arrow_lift_loop(void);
/* |description|Behavior init function for orange number|descriptionEnd| */
void bhv_orange_number_init(void);
/* |description|Behavior loop function for orange number|descriptionEnd| */
void bhv_orange_number_loop(void);
/* |description|Behavior init function for Manta Ray|descriptionEnd| */
void bhv_manta_ray_init(void);
/* |description|Behavior loop function for Manta Ray|descriptionEnd| */
void bhv_manta_ray_loop(void);
/* |description|Behavior init function for Jolly Roger Bay falling pillar|descriptionEnd| */
void bhv_falling_pillar_init(void);
/* |description|Behavior loop function for Jolly Roger Bay falling pillar|descriptionEnd| */
void bhv_falling_pillar_loop(void);
/* |description|Behavior loop function for Jolly Roger Bay falling pillar hitbox|descriptionEnd| */
void bhv_falling_pillar_hitbox_loop(void);
/* |description|Behavior loop function for Jolly Roger Bay floating box|descriptionEnd| */
void bhv_jrb_floating_box_loop(void);
/* |description|Behavior init function for decorative pendulum|descriptionEnd| */
void bhv_decorative_pendulum_init(void);
/* |description|Behavior loop function for decorative pendulum|descriptionEnd| */
void bhv_decorative_pendulum_loop(void);
/* |description|Behavior init function for treasure chest ship|descriptionEnd| */
void bhv_treasure_chest_ship_init(void);
/* |description|Behavior loop function for treasure chest ship|descriptionEnd| */
void bhv_treasure_chest_ship_loop(void);
/* |description|Behavior init function for treasure chest jrb|descriptionEnd| */
void bhv_treasure_chest_jrb_init(void);
/* |description|Behavior loop function for treasure chest jrb|descriptionEnd| */
void bhv_treasure_chest_jrb_loop(void);
/* |description|Behavior init function for treasure chest|descriptionEnd| */
void bhv_treasure_chest_init(void);
/* |description|Behavior loop function for treasure chest|descriptionEnd| */
void bhv_treasure_chest_loop(void);
/* |description|Behavior init function for treasure chest bottom|descriptionEnd| */
void bhv_treasure_chest_bottom_init(void);
/* |description|Behavior loop function for treasure chest bottom|descriptionEnd| */
void bhv_treasure_chest_bottom_loop(void);
/* |description|Behavior loop function for treasure chest top|descriptionEnd| */
void bhv_treasure_chest_top_loop(void);
/* |description|Behavior init function for Mips|descriptionEnd| */
void bhv_mips_init(void);
/* |description|Behavior loop function for Mips|descriptionEnd| */
void bhv_mips_loop(void);
/* |description|Behavior init function for Yoshi|descriptionEnd| */
void bhv_yoshi_init(void);
/* |description|Behavior init function for Koopa|descriptionEnd| */
void bhv_koopa_init(void);
/* |description|Behavior loop function for Koopa|descriptionEnd| */
void bhv_koopa_update(void);
/* |description|Behavior loop function for Koopa race endpoint|descriptionEnd| */
void bhv_koopa_race_endpoint_update(void);
/* |description|Behavior loop function for Pokey|descriptionEnd| */
void bhv_pokey_update(void);
/* |description|Behavior loop function for Pokey body part|descriptionEnd| */
void bhv_pokey_body_part_update(void);
/* |description|Behavior loop function for Swoop|descriptionEnd| */
void bhv_swoop_update(void);
/* |description|Behavior loop function for Fly Guy|descriptionEnd| */
void bhv_fly_guy_update(void);
/* |description|Behavior init function for Goomba|descriptionEnd| */
void bhv_goomba_init(void);
/* |description|Behavior loop function for Goomba|descriptionEnd| */
void bhv_goomba_update(void);
/* |description|Behavior loop function for Goomba triplet spawner|descriptionEnd| */
void bhv_goomba_triplet_spawner_update(void);
/* |description|Behavior loop function for Chain Chomp|descriptionEnd| */
void bhv_chain_chomp_update(void);
/* |description|Behavior loop function for Chain Chomp chain part|descriptionEnd| */
void bhv_chain_chomp_chain_part_update(void);
/* |description|Behavior loop function for ground poundable wooden post|descriptionEnd| */
void bhv_wooden_post_update(void);
/* |description|Behavior init function for Chain Chomp gate|descriptionEnd| */
void bhv_chain_chomp_gate_init(void);
/* |description|Behavior loop function for Chain Chomp gate|descriptionEnd| */
void bhv_chain_chomp_gate_update(void);
/* |description|Behavior loop function for Wiggler|descriptionEnd| */
void bhv_wiggler_update(void);
/* |description|Behavior loop function for Wiggler body part|descriptionEnd| */
void bhv_wiggler_body_part_update(void);
/* |description|Behavior loop function for Enemy Lakitu|descriptionEnd| */
void bhv_enemy_lakitu_update(void);
/* |description|Behavior init function for Camera Lakitu|descriptionEnd| */
void bhv_camera_lakitu_init(void);
/* |description|Behavior loop function for Camera Lakitu|descriptionEnd| */
void bhv_camera_lakitu_update(void);
/* |description|Behavior loop function for cloud|descriptionEnd| */
void bhv_cloud_update(void);
/* |description|Behavior loop function for cloud part|descriptionEnd| */
void bhv_cloud_part_update(void);
/* |description|Behavior loop function for Spiny|descriptionEnd| */
void bhv_spiny_update(void);
/* |description|Behavior init function for Monty Mole|descriptionEnd| */
void bhv_monty_mole_init(void);
/* |description|Behavior loop function for Monty Mole|descriptionEnd| */
void bhv_monty_mole_update(void);
/* |description|Behavior loop function for Monty Mole hole|descriptionEnd| */
void bhv_monty_mole_hole_update(void);
/* |description|Behavior loop function for Monty Mole rock|descriptionEnd| */
void bhv_monty_mole_rock_update(void);
/* |description|Behavior init function for platform on track|descriptionEnd| */
void bhv_platform_on_track_init(void);
/* |description|Behavior loop function for platform on track|descriptionEnd| */
void bhv_platform_on_track_update(void);
/* |description|Behavior loop function for track ball|descriptionEnd| */
void bhv_track_ball_update(void);
/* |description|Behavior init function for seesaw platform|descriptionEnd| */
void bhv_seesaw_platform_init(void);
/* |description|Behavior loop function for seesaw platform|descriptionEnd| */
void bhv_seesaw_platform_update(void);
/* |description|Behavior init function for ferris wheel axle|descriptionEnd| */
void bhv_ferris_wheel_axle_init(void);
/* |description|Behavior init function for ferris wheel platform|descriptionEnd| */
void bhv_ferris_wheel_platform_init(void);
/* |description|Behavior loop function for ferris wheel platform|descriptionEnd| */
void bhv_ferris_wheel_platform_update(void);
/* |description|Behavior loop function for water bomb spawner|descriptionEnd| */
void bhv_water_bomb_spawner_update(void);
/* |description|Behavior loop function for water bomb|descriptionEnd| */
void bhv_water_bomb_update(void);
/* |description|Behavior loop function for water bomb shadow|descriptionEnd| */
void bhv_water_bomb_shadow_update(void);
/* |description|Behavior init function for Tick Tock Clock rotating solid|descriptionEnd| */
void bhv_ttc_rotating_solid_init(void);
/* |description|Behavior loop function for Tick Tock Clock rotating solid|descriptionEnd| */
void bhv_ttc_rotating_solid_update(void);
/* |description|Behavior init function for Tick Tock Clock pendulum|descriptionEnd| */
void bhv_ttc_pendulum_init(void);
/* |description|Behavior loop function for Tick Tock Clock pendulum|descriptionEnd| */
void bhv_ttc_pendulum_update(void);
/* |description|Behavior init function for Tick Tock Clock treadmill|descriptionEnd| */
void bhv_ttc_treadmill_init(void);
/* |description|Behavior loop function for Tick Tock Clock treadmill|descriptionEnd| */
void bhv_ttc_treadmill_update(void);
/* |description|Behavior init function for Tick Tock Clock moving bar|descriptionEnd| */
void bhv_ttc_moving_bar_init(void);
/* |description|Behavior loop function for Tick Tock Clock moving bar|descriptionEnd| */
void bhv_ttc_moving_bar_update(void);
/* |description|Behavior init function for Tick Tock Clock cog|descriptionEnd| */
void bhv_ttc_cog_init(void);
/* |description|Behavior loop function for Tick Tock Clock cog|descriptionEnd| */
void bhv_ttc_cog_update(void);
/* |description|Behavior init function for Tick Tock Clock pit block|descriptionEnd| */
void bhv_ttc_pit_block_init(void);
/* |description|Behavior loop function for Tick Tock Clock pit block|descriptionEnd| */
void bhv_ttc_pit_block_update(void);
/* |description|Behavior init function for Tick Tock Clock elevator|descriptionEnd| */
void bhv_ttc_elevator_init(void);
/* |description|Behavior loop function for Tick Tock Clock elevator|descriptionEnd| */
void bhv_ttc_elevator_update(void);
/* |description|Behavior init function for Tick Tock Clock 2D rotator|descriptionEnd| */
void bhv_ttc_2d_rotator_init(void);
/* |description|Behavior loop function for Tick Tock Clock 2D rotator|descriptionEnd| */
void bhv_ttc_2d_rotator_update(void);
/* |description|Behavior loop function for Tick Tock Clock spinner|descriptionEnd| */
void bhv_ttc_spinner_update(void);
/* |description|Behavior init function for Mr. Blizzard|descriptionEnd| */
void bhv_mr_blizzard_init(void);
/* |description|Behavior loop function for Mr. Blizzard|descriptionEnd| */
void bhv_mr_blizzard_update(void);
/* |description|Behavior loop function for Mr. Blizzard's snowball|descriptionEnd| */
void bhv_mr_blizzard_snowball(void);
/* |description|Behavior init function for sliding platform 2 in Rainbow Ride and Bowser courses|descriptionEnd| */
void bhv_sliding_plat_2_init(void);
/* |description|Behavior loop function for sliding platform 2 in Rainbow Ride and Bowser courses|descriptionEnd| */
void bhv_sliding_plat_2_loop(void);
/* |description|Behavior init function for Rotating octagonal platform in Rainbow Ride and Bowser in the Sky|descriptionEnd| */
void bhv_rotating_octagonal_plat_init(void);
/* |description|Behavior loop function for Rotating octagonal platform in Rainbow Ride and Bowser in the Sky|descriptionEnd| */
void bhv_rotating_octagonal_plat_loop(void);
/* |description|Behavior init function for animates on floor switch press in Rainbow Ride and Bowser courses|descriptionEnd| */
void bhv_animates_on_floor_switch_press_init(void);
/* |description|Behavior loop function for animates on floor switch press in Rainbow Ride and Bowser courses|descriptionEnd| */
void bhv_animates_on_floor_switch_press_loop(void);
/* |description|Behavior init function for activated back and forth platform in Bowser courses|descriptionEnd| */
void bhv_activated_back_and_forth_platform_init(void);
/* |description|Behavior loop function for activated back and forth platform in Bowser courses|descriptionEnd| */
void bhv_activated_back_and_forth_platform_update(void);
/* |description|Behavior loop function for Recovery Heart|descriptionEnd| */
void bhv_recovery_heart_loop(void);
/* |description|Behavior loop function for water bomb cannon|descriptionEnd| */
void bhv_water_bomb_cannon_loop(void);
/* |description|Behavior loop function for bubble cannon barrel|descriptionEnd| */
void bhv_bubble_cannon_barrel_loop(void);
/* |description|Behavior init function for Unagi|descriptionEnd| */
void bhv_unagi_init(void);
/* |description|Behavior loop function for Unagi|descriptionEnd| */
void bhv_unagi_loop(void);
/* |description|Behavior loop function for Unagi subobject|descriptionEnd| */
void bhv_unagi_subobject_loop(void);
/* |description|Behavior loop function for Dorrie|descriptionEnd| */
void bhv_dorrie_update(void);
/* |description|Behavior init function for Haunted Chair|descriptionEnd| */
void bhv_haunted_chair_init(void);
/* |description|Behavior loop function for Haunted Chair|descriptionEnd| */
void bhv_haunted_chair_loop(void);
/* |description|Behavior loop function for Mad Piano|descriptionEnd| */
void bhv_mad_piano_update(void);
/* |description|Behavior loop function for flying bookend|descriptionEnd| */
void bhv_flying_bookend_loop(void);
/* |description|Behavior loop function for Bookend spawn|descriptionEnd| */
void bhv_bookend_spawn_loop(void);
/* |description|Behavior loop function for haunted bookshelf manager|descriptionEnd| */
void bhv_haunted_bookshelf_manager_loop(void);
/* |description|Behavior loop function for Book switch|descriptionEnd| */
void bhv_book_switch_loop(void);
/* |description|Behavior init function for Fire Piranha Plant|descriptionEnd| */
void bhv_fire_piranha_plant_init(void);
/* |description|Behavior loop function for Fire Piranha Plant|descriptionEnd| */
void bhv_fire_piranha_plant_update(void);
/* |description|Behavior loop function for Small Piranha flame|descriptionEnd| */
void bhv_small_piranha_flame_loop(void);
/* |description|Behavior loop function for Fire spitter|descriptionEnd| */
void bhv_fire_spitter_update(void);
/* |description|Behavior loop function for Fly Guy flame|descriptionEnd| */
void bhv_fly_guy_flame_loop(void);
/* |description|Behavior loop function for Snufit|descriptionEnd| */
void bhv_snufit_loop(void);
/* |description|Behavior loop function for Snufit balls|descriptionEnd| */
void bhv_snufit_balls_loop(void);
/* |description|Behavior init function for horizontal Grindel|descriptionEnd| */
void bhv_horizontal_grindel_init(void);
/* |description|Behavior loop function for horizontal Grindel|descriptionEnd| */
void bhv_horizontal_grindel_update(void);
/* |description|Behavior init function for Eyerok boss|descriptionEnd| */
void bhv_eyerok_boss_init(void);
/* |description|Behavior loop function for Eyerok boss|descriptionEnd| */
void bhv_eyerok_boss_loop(void);
/* |description|Behavior loop function for Eyerok hand|descriptionEnd| */
void bhv_eyerok_hand_loop(void);
/* |description|Behavior init function for Klepto|descriptionEnd| */
void bhv_klepto_init(void);
/* |description|Behavior loop function for Klepto|descriptionEnd| */
void bhv_klepto_update(void);
/* |description|Behavior loop function for bird|descriptionEnd| */
void bhv_bird_update(void);
/* |description|Behavior init function for Racing Penguin|descriptionEnd| */
void bhv_racing_penguin_init(void);
/* |description|Behavior loop function for Racing Penguin|descriptionEnd| */
void bhv_racing_penguin_update(void);
/* |description|Behavior loop function for Penguin race finish line|descriptionEnd| */
void bhv_penguin_race_finish_line_update(void);
/* |description|Behavior loop function for Penguin race shortcut check|descriptionEnd| */
void bhv_penguin_race_shortcut_check_update(void);
/* |description|Behavior loop function for coffin spawner|descriptionEnd| */
void bhv_coffin_spawner_loop(void);
/* |description|Behavior loop function for coffin|descriptionEnd| */
void bhv_coffin_loop(void);
/* |description|Behavior loop function for Clam|descriptionEnd| */
void bhv_clam_loop(void);
/* |description|Behavior loop function for Skeeter|descriptionEnd| */
void bhv_skeeter_update(void);
/* |description|Behavior loop function for Skeeter wave|descriptionEnd| */
void bhv_skeeter_wave_update(void);
/* |description|Behavior init function for swing platform|descriptionEnd| */
void bhv_swing_platform_init(void);
/* |description|Behavior loop function for swing platform|descriptionEnd| */
void bhv_swing_platform_update(void);
/* |description|Behavior loop function for donut platform spawner|descriptionEnd| */
void bhv_donut_platform_spawner_update(void);
/* |description|Behavior loop function for donut platform|descriptionEnd| */
void bhv_donut_platform_update(void);
/* |description|Behavior init function for Dire Dire Docks pole|descriptionEnd| */
void bhv_ddd_pole_init(void);
/* |description|Behavior loop function for Dire Dire Docks pole|descriptionEnd| */
void bhv_ddd_pole_update(void);
/* |description|Behavior init function for Red Coin Star marker|descriptionEnd| */
void bhv_red_coin_star_marker_init(void);
/* |description|Behavior loop function for a triplet of butterflies|descriptionEnd| */
void bhv_triplet_butterfly_update(void);
/* |description|Behavior loop function for Bubba|descriptionEnd| */
void bhv_bubba_loop(void);
/* |description|Behavior loop function for intro Lakitu|descriptionEnd| */
void bhv_intro_lakitu_loop(void);
/* |description|Behavior loop function for intro Peach|descriptionEnd| */
void bhv_intro_peach_loop(void);
/* |description|Behavior loop function for first end birds|descriptionEnd| */
void bhv_end_birds_1_loop(void);
/* |description|Behavior loop function for second end birds|descriptionEnd| */
void bhv_end_birds_2_loop(void);
/* |description|Behavior loop function for intro scene|descriptionEnd| */
void bhv_intro_scene_loop(void);
/* |description|Behavior loop function for Dust smoke|descriptionEnd| */
void bhv_dust_smoke_loop(void);
/* |description|Behavior loop function for Yoshi|descriptionEnd| */
void bhv_yoshi_loop(void);
/* |description|Behavior loop function for volcano trap|descriptionEnd| */
void bhv_volcano_trap_loop(void);
/* |description|Behavior loop function for UV texture scrolling|descriptionEnd| */
void uv_update_scroll(void);
/* |description|Spawns a lighting engine point light|descriptionEnd| */
struct Object* spawn_ambient_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b);
/* |description|Spawns a lighting engine ambient light|descriptionEnd| */
struct Object* spawn_point_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius);
/* |description|Behavior loop function for the lighting engine ambient light. Takes the first 3 behavior parameter bytes for RGB color|descriptionEnd| */
void bhv_ambient_light_update(void);
/* |description|Behavior init function for the lighting engine point light. Takes the first 3 behavior parameter bytes for RGB color and the last for radius|descriptionEnd| */
void bhv_point_light_init(void);
/* |description|Behavior loop function for the lighting engine point light|descriptionEnd| */
void bhv_point_light_loop(void);

Gfx *geo_move_mario_part_from_parent(s32 run, UNUSED struct GraphNode *node, Mat4 mtx);

// Bowser
Gfx *geo_bits_bowser_coloring(s32 run, struct GraphNode *node, UNUSED s32 a2);
Gfx *geo_update_body_rot_from_parent(s32 run, UNUSED struct GraphNode *node, Mat4 mtx);
Gfx *geo_switch_bowser_eyes(s32 run, struct GraphNode *node, UNUSED Mat4 *mtx);

// Tuxie
Gfx *geo_switch_tuxie_mother_eyes(s32 run, struct GraphNode *node, UNUSED Mat4 *mtx);

// Cap switch
Gfx *geo_update_held_mario_pos(s32 run, UNUSED struct GraphNode *node, Mat4 mtx);

// Snufit
Gfx *geo_snufit_move_mask(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_snufit_scale_body(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);

// Bowser key cutscene
Gfx *geo_scale_bowser_key(s32 run, struct GraphNode *node, UNUSED f32 mtx[4][4]);

// Water splash
extern struct WaterDropletParams gShallowWaterSplashDropletParams;
extern struct WaterDropletParams gShallowWaterWaveDropletParams;

/* |description|Spawns a Star with an ID corresponding to the current object's first behavior parameter byte|descriptionEnd| */
struct Object* spawn_default_star(f32 x, f32 y, f32 z);
/* |description|Spawns a Red Coin cutscene star with an ID corresponding to the current object's first behavior parameter byte|descriptionEnd| */
struct Object* spawn_red_coin_cutscene_star(f32 x, f32 y, f32 z);
/* |description|Spawns a Star that won't make Mario exit the level with an ID corresponding to the current object's first behavior parameter byte|descriptionEnd| */
struct Object* spawn_no_exit_star(f32 x, f32 y, f32 z);

#endif // BEHAVIOR_ACTIONS_H
