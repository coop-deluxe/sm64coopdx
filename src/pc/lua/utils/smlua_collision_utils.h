#ifndef SMLUA_COLLISION_UTILS_H
#define SMLUA_COLLISION_UTILS_H

#include "engine/surface_collision.h"

struct RayIntersectionInfo {
    struct Surface* surface;
    Vec3f hitPos;
};

struct GlobalObjectCollisionData {
    Collision* bbh_seg7_collision_coffin;
    Collision* bbh_seg7_collision_haunted_bookshelf;
    Collision* bbh_seg7_collision_merry_go_round;
    Collision* bbh_seg7_collision_mesh_elevator;
    Collision* bbh_seg7_collision_staircase_step;
    Collision* bbh_seg7_collision_tilt_floor_platform;
    Collision* bitdw_seg7_collision_moving_pyramid;
    Collision* bitfs_seg7_collision_inverted_pyramid;
    Collision* bitfs_seg7_collision_sinking_cage_platform;
    Collision* bitfs_seg7_collision_sinking_platform;
    Collision* bitfs_seg7_collision_squishable_platform;
    Collision* blue_coin_switch_seg8_collision_08000E98;
    Collision* bob_seg7_collision_chain_chomp_gate;
    Collision* bowser_2_seg7_collision_tilting_platform;
    Collision* breakable_box_seg8_collision_08012D70;
    Collision* cannon_lid_seg8_collision_08004950;
    Collision* capswitch_collision_050033D0;
    Collision* capswitch_collision_05003448;
    Collision* castle_grounds_seg7_collision_cannon_grill;
    Collision* castle_grounds_seg7_collision_moat_grills;
    Collision* checkerboard_platform_seg8_collision_0800D710;
    Collision* ddd_seg7_collision_bowser_sub_door;
    Collision* ddd_seg7_collision_submarine;
    Collision* door_seg3_collision_0301CE78;
    Collision* dorrie_seg6_collision_0600F644;
    Collision* dorrie_seg6_collision_0600FBB8;
    Collision* exclamation_box_outline_seg8_collision_08025F78;
    Collision* hmc_seg7_collision_controllable_platform;
    Collision* hmc_seg7_collision_controllable_platform_sub;
    Collision* hmc_seg7_collision_elevator;
    Collision* inside_castle_seg7_collision_floor_trap;
    Collision* inside_castle_seg7_collision_star_door;
    Collision* inside_castle_seg7_collision_water_level_pillar;
    Collision* jrb_seg7_collision_floating_box;
    Collision* jrb_seg7_collision_floating_platform;
    Collision* jrb_seg7_collision_in_sunken_ship;
    Collision* jrb_seg7_collision_in_sunken_ship_2;
    Collision* jrb_seg7_collision_in_sunken_ship_3;
    Collision* jrb_seg7_collision_pillar_base;
    Collision* jrb_seg7_collision_rock_solid;
    Collision* lll_hexagonal_mesh_seg3_collision_0301CECC;
    Collision* lll_seg7_collision_drawbridge;
    Collision* lll_seg7_collision_falling_wall;
    Collision* lll_seg7_collision_floating_block;
    Collision* lll_seg7_collision_hexagonal_platform;
    Collision* lll_seg7_collision_inverted_pyramid;
    Collision* lll_seg7_collision_octagonal_moving_platform;
    Collision* lll_seg7_collision_pitoune;
    Collision* lll_seg7_collision_puzzle_piece;
    Collision* lll_seg7_collision_rotating_fire_bars;
    Collision* lll_seg7_collision_rotating_platform;
    Collision* lll_seg7_collision_sinking_pyramids;
    Collision* lll_seg7_collision_slow_tilting_platform;
    Collision* lll_seg7_collision_wood_piece;
    Collision* metal_box_seg8_collision_08024C28;
    Collision* penguin_seg5_collision_05008B88;
    Collision* poundable_pole_collision_06002490;
    Collision* purple_switch_seg8_collision_0800C7A8;
    Collision* rr_seg7_collision_donut_platform;
    Collision* rr_seg7_collision_elevator_platform;
    Collision* rr_seg7_collision_pendulum;
    Collision* rr_seg7_collision_rotating_platform_with_fire;
    Collision* sl_seg7_collision_pound_explodes;
    Collision* sl_seg7_collision_sliding_snow_mound;
    Collision* springboard_collision_05001A28;
    Collision* ssl_seg7_collision_0702808C;
    Collision* ssl_seg7_collision_grindel;
    Collision* ssl_seg7_collision_pyramid_elevator;
    Collision* ssl_seg7_collision_pyramid_top;
    Collision* ssl_seg7_collision_spindel;
    Collision* ssl_seg7_collision_tox_box;
    Collision* thi_seg7_collision_top_trap;
    Collision* thwomp_seg5_collision_0500B7D0;
    Collision* thwomp_seg5_collision_0500B92C;
    Collision* ttc_seg7_collision_clock_main_rotation;
    Collision* ttc_seg7_collision_clock_pendulum;
    Collision* ttc_seg7_collision_clock_platform;
    Collision* ttc_seg7_collision_rotating_clock_platform2;
    Collision* ttc_seg7_collision_sliding_surface;
    Collision* ttm_seg7_collision_pitoune_2;
    Collision* ttm_seg7_collision_podium_warp;
    Collision* ttm_seg7_collision_ukiki_cage;
    Collision* unknown_seg8_collision_080262F8;
    Collision* warp_pipe_seg3_collision_03009AC8;
    Collision* wdw_seg7_collision_arrow_lift;
    Collision* wdw_seg7_collision_express_elevator_platform;
    Collision* wdw_seg7_collision_rect_floating_platform;
    Collision* wdw_seg7_collision_square_floating_platform;
    Collision* wf_seg7_collision_breakable_wall;
    Collision* wf_seg7_collision_breakable_wall_2;
    Collision* wf_seg7_collision_bullet_bill_cannon;
    Collision* wf_seg7_collision_clocklike_rotation;
    Collision* wf_seg7_collision_kickable_board;
    Collision* wf_seg7_collision_large_bomp;
    Collision* wf_seg7_collision_platform;
    Collision* wf_seg7_collision_sliding_brick_platform;
    Collision* wf_seg7_collision_small_bomp;
    Collision* wf_seg7_collision_tower;
    Collision* wf_seg7_collision_tower_door;
    Collision* whomp_seg6_collision_06020A0C;
    Collision* wooden_signpost_seg3_collision_0302DD80;
};

extern struct GlobalObjectCollisionData gGlobalObjectCollisionData;

struct RayIntersectionInfo* collision_find_surface_on_ray(f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32 precision);
/* |description|Finds a potential floor at the given `x`, `y`, and `z` values|descriptionEnd| */
struct Surface* collision_find_floor(f32 x, f32 y, f32 z);

/* |description|Finds a potential ceiling at the given `x`, `y`, and `z` values|descriptionEnd| */
struct Surface* collision_find_ceil(f32 x, f32 y, f32 z);

struct Surface* get_water_surface_pseudo_floor(void);

/* |description|Gets the `Collision` with `name`|descriptionEnd| */
Collision* smlua_collision_util_get(const char* name);

/* |description|Returns a temporary wall collision data pointer|descriptionEnd| */
struct WallCollisionData* collision_get_temp_wall_collision_data(void);

/* |description|Gets the surface corresponding to `index` from `wcd`|descriptionEnd| */
struct Surface* get_surface_from_wcd_index(struct WallCollisionData* wcd, s8 index);

/* |description|Gets the current level terrain collision|descriptionEnd| */
Collision* smlua_collision_util_get_current_terrain_collision(void);

/* |description|Gets the `level` terrain collision from `area`|descriptionEnd| */
Collision *smlua_collision_util_get_level_collision(u32 level, u16 area);

/* |description|Gets a table of the surface types from `data`|descriptionEnd| */
void smlua_collision_util_find_surface_types(Collision* data);

#endif
