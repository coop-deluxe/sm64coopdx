#ifndef OBJ_BEHAVIORS_2_H
#define OBJ_BEHAVIORS_2_H

#include <PR/ultratypes.h>

#include "types.h"

#define ATTACK_HANDLER_NOP 0
#define ATTACK_HANDLER_DIE_IF_HEALTH_NON_POSITIVE 1
#define ATTACK_HANDLER_KNOCKBACK 2
#define ATTACK_HANDLER_SQUISHED 3
#define ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL 4
#define ATTACK_HANDLER_SET_SPEED_TO_ZERO 5
#define ATTACK_HANDLER_SPECIAL_WIGGLER_JUMPED_ON 6
#define ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED 7
#define ATTACK_HANDLER_SQUISHED_WITH_BLUE_COIN 8

void shelled_koopa_attack_handler(s32 attackType);
struct Object* obj_spit_fire(s16 relativePosX, s16 relativePosY, s16 relativePosZ, f32 scale, s32 model,
                             f32 startSpeed, f32 endSpeed, s16 movePitch);
void obj_set_speed_to_zero(void);

void bhv_koopa_init(void);
void bhv_koopa_update(void);
void bhv_koopa_race_endpoint_update(void);
void bhv_pokey_body_part_update(void);
void bhv_pokey_update(void);
void bhv_swoop_update(void);
void bhv_fly_guy_update(void);
void bhv_goomba_triplet_spawner_update(void);
void bhv_goomba_init(void);
void bhv_goomba_update(void);
void bhv_chain_chomp_chain_part_update(void);
void bhv_chain_chomp_update(void);
void bhv_wooden_post_update(void);
void bhv_chain_chomp_gate_init(void);
void bhv_chain_chomp_gate_update(void);
void bhv_wiggler_body_part_update(void);
void bhv_wiggler_update(void);
void bhv_spiny_update(void);
void bhv_enemy_lakitu_update(void);
void bhv_cloud_update(void);
void bhv_cloud_part_update(void);
void bhv_camera_lakitu_init(void);
void bhv_camera_lakitu_update(void);
void bhv_monty_mole_hole_update(void);
void bhv_monty_mole_init(void);
void bhv_monty_mole_update(void);
void bhv_monty_mole_rock_update(void);
void bhv_platform_on_track_init(void);
void bhv_platform_on_track_update(void);
void bhv_track_ball_update(void);
void bhv_seesaw_platform_init(void);
void bhv_seesaw_platform_update(void);
void bhv_ferris_wheel_axle_init(void);
void bhv_ferris_wheel_platform_init(void);
void bhv_ferris_wheel_platform_update(void);
void bhv_water_bomb_spawner_update(void);
void bhv_water_bomb_update(void);
void bhv_water_bomb_shadow_update(void);
void bhv_ttc_rotating_solid_init(void);
void bhv_ttc_rotating_solid_update(void);
void bhv_ttc_pendulum_init(void);
void bhv_ttc_pendulum_update(void);
void bhv_ttc_treadmill_init(void);
void bhv_ttc_treadmill_update(void);
void bhv_ttc_moving_bar_init(void);
void bhv_ttc_moving_bar_update(void);
void bhv_ttc_cog_init(void);
void bhv_ttc_cog_update(void);
void bhv_ttc_pit_block_init(void);
void bhv_ttc_pit_block_update(void);
void bhv_ttc_elevator_init(void);
void bhv_ttc_elevator_update(void);
void bhv_ttc_2d_rotator_init(void);
void bhv_ttc_2d_rotator_update(void);
void bhv_ttc_spinner_update(void);
void bhv_mr_blizzard_init(void);
void bhv_mr_blizzard_update(void);
void bhv_mr_blizzard_snowball(void);
void bhv_sliding_plat_2_init(void);
void bhv_sliding_plat_2_loop(void);
void bhv_rotating_octagonal_plat_init(void);
void bhv_rotating_octagonal_plat_loop(void);
void bhv_animates_on_floor_switch_press_init(void);
void bhv_animates_on_floor_switch_press_loop(void);
void bhv_activated_back_and_forth_platform_init(void);
void bhv_activated_back_and_forth_platform_update(void);
void bhv_recovery_heart_loop(void);
void bhv_bubble_cannon_barrel_loop(void);
void bhv_water_bomb_cannon_loop(void);
void bhv_unagi_init(void);
void bhv_unagi_loop(void);
void bhv_unagi_subobject_loop(void);
void bhv_dorrie_update(void);
void bhv_haunted_chair_init(void);
void bhv_haunted_chair_loop(void);
void bhv_mad_piano_update(void);
void bhv_flying_bookend_loop(void);
void bhv_bookend_spawn_loop(void);
void bhv_haunted_bookshelf_manager_loop(void);
void bhv_book_switch_loop(void);
void bhv_fire_piranha_plant_init(void);
void bhv_fire_piranha_plant_update(void);
void bhv_fire_spitter_update(void);
void bhv_small_piranha_flame_loop(void);
void bhv_fly_guy_flame_loop(void);
void bhv_snufit_loop(void);
void bhv_snufit_balls_loop(void);
void bhv_horizontal_grindel_init(void);
void bhv_horizontal_grindel_update(void);
void bhv_eyerok_boss_init(void);
void bhv_eyerok_boss_loop(void);
void bhv_eyerok_hand_loop(void);
void bhv_klepto_init(void);
void bhv_klepto_update(void);
void bhv_bird_update(void);
void bhv_racing_penguin_init(void);
void bhv_racing_penguin_update(void);
void bhv_coffin_spawner_loop(void);
void bhv_coffin_loop(void);
void bhv_clam_loop(void);
void bhv_skeeter_update(void);
void bhv_skeeter_wave_update(void);
void bhv_swing_platform_init(void);
void bhv_swing_platform_update(void);
void bhv_donut_platform_spawner_update(void);
void bhv_donut_platform_update(void);
void bhv_ddd_pole_init(void);
void bhv_ddd_pole_update(void);
void bhv_red_coin_star_marker_init(void);
void bhv_triplet_butterfly_update(void);
void bhv_bubba_loop(void);

#endif // OBJ_BEHAVIORS_2_H
