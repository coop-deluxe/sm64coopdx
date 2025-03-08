#include "sm64.h"
#include "types.h"
#include "geo_commands.h"

#include "game/area.h"
#include "engine/graph_node.h"
#include "engine/level_script.h"

// models
#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/custom0.h"
#include "actors/group0.h"
#include "actors/group1.h"
#include "actors/group2.h"
#include "actors/group3.h"
#include "actors/group4.h"
#include "actors/group5.h"
#include "actors/group6.h"
#include "actors/group7.h"
#include "actors/group8.h"
#include "actors/group9.h"
#include "actors/group10.h"
#include "actors/group11.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "actors/group14.h"
#include "actors/group15.h"
#include "actors/group16.h"
#include "actors/group17.h"
#include "actors/zcustom0.h"
#include "levels/wf/header.h"
#include "levels/bbh/header.h"
#include "levels/ccm/header.h"
#include "levels/castle_inside/header.h"
#include "levels/castle_grounds/header.h"
#include "levels/hmc/header.h"
#include "levels/ssl/header.h"
#include "levels/bob/header.h"
#include "levels/sl/header.h"
#include "levels/wdw/header.h"
#include "levels/jrb/header.h"
#include "levels/thi/header.h"
#include "levels/ttc/header.h"
#include "levels/rr/header.h"
#include "levels/bitdw/header.h"
#include "levels/bitfs/header.h"
#include "levels/bits/header.h"
#include "levels/lll/header.h"
#include "levels/ddd/header.h"
#include "levels/bowser_2/header.h"
#include "levels/bowser_3/header.h"
#include "levels/ttm/header.h"

#include "smlua_model_utils.h"
#include "pc/lua/smlua.h"

struct ModelUtilsInfo {
    enum ModelExtendedId extId;
    u8 layer;
    u16 loadedId;
    bool isDisplayList;
    const void* asset;
};

#define UNLOADED_ID 0

#define MODEL_UTIL_GEO(x, y)           [x] = { .extId = x, .asset = y, .layer = LAYER_OPAQUE, .isDisplayList = false, .loadedId = UNLOADED_ID, }
#define MODEL_UTIL_DL(x, y, z)         [x] = { .extId = x, .asset = y, .layer = z,            .isDisplayList = true,  .loadedId = UNLOADED_ID, }
#define MODEL_UTIL_GEO_PERM(x, y, w)   [x] = { .extId = x, .asset = y, .layer = LAYER_OPAQUE, .isDisplayList = false, .loadedId = w,           }
#define MODEL_UTIL_DL_PERM(x, y, z, w) [x] = { .extId = x, .asset = y, .layer = z,            .isDisplayList = true,  .loadedId = w,           }

struct ModelUtilsInfo sModels[E_MODEL_MAX] = {
    MODEL_UTIL_GEO(E_MODEL_NONE, NULL),

    // actors
    MODEL_UTIL_GEO_PERM(E_MODEL_MARIO,                   mario_geo,                            MODEL_MARIO),
    MODEL_UTIL_GEO_PERM(E_MODEL_SMOKE,                   smoke_geo,                            MODEL_SMOKE),
    MODEL_UTIL_GEO_PERM(E_MODEL_SPARKLES,                sparkles_geo,                         MODEL_SPARKLES),
    MODEL_UTIL_GEO_PERM(E_MODEL_BUBBLE,                  bubble_geo,                           MODEL_BUBBLE),
    MODEL_UTIL_GEO_PERM(E_MODEL_SMALL_WATER_SPLASH,      small_water_splash_geo,               MODEL_SMALL_WATER_SPLASH),
    MODEL_UTIL_GEO_PERM(E_MODEL_IDLE_WATER_WAVE,         idle_water_wave_geo,                  MODEL_IDLE_WATER_WAVE),
    MODEL_UTIL_GEO_PERM(E_MODEL_WATER_SPLASH,            water_splash_geo,                     MODEL_WATER_SPLASH),
    MODEL_UTIL_GEO_PERM(E_MODEL_WAVE_TRAIL,              wave_trail_geo,                       MODEL_WAVE_TRAIL),
    MODEL_UTIL_GEO_PERM(E_MODEL_YELLOW_COIN,             yellow_coin_geo,                      MODEL_YELLOW_COIN),
    MODEL_UTIL_GEO_PERM(E_MODEL_STAR,                    star_geo,                             MODEL_STAR),
    MODEL_UTIL_GEO_PERM(E_MODEL_TRANSPARENT_STAR,        transparent_star_geo,                 MODEL_TRANSPARENT_STAR),
    MODEL_UTIL_GEO_PERM(E_MODEL_WOODEN_SIGNPOST,         wooden_signpost_geo,                  MODEL_WOODEN_SIGNPOST),
    MODEL_UTIL_DL_PERM (E_MODEL_WHITE_PARTICLE_SMALL,    white_particle_small_dl, LAYER_ALPHA, MODEL_WHITE_PARTICLE_SMALL),
    MODEL_UTIL_GEO_PERM(E_MODEL_RED_FLAME,               red_flame_geo,                        MODEL_RED_FLAME),
    MODEL_UTIL_GEO_PERM(E_MODEL_BLUE_FLAME,              blue_flame_geo,                       MODEL_BLUE_FLAME),
    MODEL_UTIL_GEO_PERM(E_MODEL_BURN_SMOKE,              burn_smoke_geo,                       MODEL_BURN_SMOKE),
    MODEL_UTIL_GEO_PERM(E_MODEL_LEAVES,                  leaves_geo,                           MODEL_LEAVES),
    MODEL_UTIL_GEO_PERM(E_MODEL_PURPLE_MARBLE,           purple_marble_geo,                    MODEL_PURPLE_MARBLE),
    MODEL_UTIL_GEO_PERM(E_MODEL_FISH,                    fish_geo,                             MODEL_FISH),
    MODEL_UTIL_GEO_PERM(E_MODEL_FISH_SHADOW,             fish_shadow_geo,                      MODEL_FISH_SHADOW),
    MODEL_UTIL_GEO_PERM(E_MODEL_SPARKLES_ANIMATION,      sparkles_animation_geo,               MODEL_SPARKLES_ANIMATION),
    MODEL_UTIL_DL_PERM (E_MODEL_SAND_DUST,               sand_seg3_dl_0302BCD0, LAYER_ALPHA,   MODEL_SAND_DUST),
    MODEL_UTIL_GEO_PERM(E_MODEL_BUTTERFLY,               butterfly_geo,                        MODEL_BUTTERFLY),
    MODEL_UTIL_GEO_PERM(E_MODEL_BURN_SMOKE_UNUSED,       burn_smoke_geo,                       MODEL_BURN_SMOKE_UNUSED),
    MODEL_UTIL_DL_PERM (E_MODEL_PEBBLE,                  pebble_seg3_dl_0301CB00, LAYER_ALPHA, MODEL_PEBBLE),
    MODEL_UTIL_GEO_PERM(E_MODEL_MIST,                    mist_geo,                             MODEL_MIST),
    MODEL_UTIL_GEO_PERM(E_MODEL_WHITE_PUFF,              white_puff_geo,                       MODEL_WHITE_PUFF),
    MODEL_UTIL_DL_PERM (E_MODEL_WHITE_PARTICLE_DL,       white_particle_dl, LAYER_ALPHA,       MODEL_WHITE_PARTICLE_DL),
    MODEL_UTIL_GEO_PERM(E_MODEL_WHITE_PARTICLE,          white_particle_geo,                   MODEL_WHITE_PARTICLE),
    MODEL_UTIL_GEO_PERM(E_MODEL_YELLOW_COIN_NO_SHADOW,   yellow_coin_no_shadow_geo,            MODEL_YELLOW_COIN_NO_SHADOW),
    MODEL_UTIL_GEO_PERM(E_MODEL_BLUE_COIN,               blue_coin_geo,                        MODEL_BLUE_COIN),
    MODEL_UTIL_GEO_PERM(E_MODEL_BLUE_COIN_NO_SHADOW,     blue_coin_no_shadow_geo,              MODEL_BLUE_COIN_NO_SHADOW),
    MODEL_UTIL_GEO_PERM(E_MODEL_MARIOS_WINGED_METAL_CAP, marios_winged_metal_cap_geo,          MODEL_MARIOS_WINGED_METAL_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_MARIOS_METAL_CAP,        marios_metal_cap_geo,                 MODEL_MARIOS_METAL_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_MARIOS_WING_CAP,         marios_wing_cap_geo,                  MODEL_MARIOS_WING_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_MARIOS_CAP,              marios_cap_geo,                       MODEL_MARIOS_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_BOWSER_KEY_CUTSCENE,     bowser_key_cutscene_geo,              MODEL_BOWSER_KEY_CUTSCENE),
    MODEL_UTIL_GEO_PERM(E_MODEL_BOWSER_KEY,              bowser_key_geo,                       MODEL_BOWSER_KEY),
    MODEL_UTIL_GEO_PERM(E_MODEL_RED_FLAME_SHADOW,        red_flame_shadow_geo,                 MODEL_RED_FLAME_SHADOW),
    MODEL_UTIL_GEO_PERM(E_MODEL_1UP,                     mushroom_1up_geo,                     MODEL_1UP),
    MODEL_UTIL_GEO_PERM(E_MODEL_RED_COIN,                red_coin_geo,                         MODEL_RED_COIN),
    MODEL_UTIL_GEO_PERM(E_MODEL_RED_COIN_NO_SHADOW,      red_coin_no_shadow_geo,               MODEL_RED_COIN_NO_SHADOW),
    MODEL_UTIL_GEO_PERM(E_MODEL_NUMBER,                  number_geo,                           MODEL_NUMBER),
    MODEL_UTIL_GEO_PERM(E_MODEL_EXPLOSION,               explosion_geo,                        MODEL_EXPLOSION),
    MODEL_UTIL_GEO_PERM(E_MODEL_DIRT_ANIMATION,          dirt_animation_geo,                   MODEL_DIRT_ANIMATION),
    MODEL_UTIL_GEO_PERM(E_MODEL_CARTOON_STAR,            cartoon_star_geo,                     MODEL_CARTOON_STAR),

    // Non-permanent actors
    MODEL_UTIL_GEO(E_MODEL_TRAMPOLINE,              springboard_top_geo),
    MODEL_UTIL_GEO(E_MODEL_TRAMPOLINE_CENTER,       springboard_spring_geo),
    MODEL_UTIL_GEO(E_MODEL_TRAMPOLINE_BASE,         springboard_bottom_geo),
    MODEL_UTIL_GEO(E_MODEL_BLUE_COIN_SWITCH,        blue_coin_switch_geo),
    MODEL_UTIL_GEO(E_MODEL_AMP,                     amp_geo),
    MODEL_UTIL_GEO(E_MODEL_PURPLE_SWITCH,           purple_switch_geo),
    MODEL_UTIL_GEO(E_MODEL_CHECKERBOARD_PLATFORM,   checkerboard_platform_geo),
    MODEL_UTIL_GEO(E_MODEL_BREAKABLE_BOX,           breakable_box_geo),
    MODEL_UTIL_GEO(E_MODEL_BREAKABLE_BOX_SMALL,     breakable_box_small_geo),
    MODEL_UTIL_GEO(E_MODEL_EXCLAMATION_BOX_OUTLINE, exclamation_box_outline_geo),
    MODEL_UTIL_GEO(E_MODEL_EXCLAMATION_BOX,         exclamation_box_geo),
    MODEL_UTIL_GEO(E_MODEL_GOOMBA,                  goomba_geo),
    MODEL_UTIL_DL (E_MODEL_EXCLAMATION_POINT,       exclamation_box_outline_seg8_dl_08025F08, LAYER_ALPHA),
    MODEL_UTIL_GEO(E_MODEL_KOOPA_SHELL,             koopa_shell_geo),
    MODEL_UTIL_GEO(E_MODEL_METAL_BOX,               metal_box_geo),
    MODEL_UTIL_DL (E_MODEL_METAL_BOX_DL,            metal_box_dl, LAYER_OPAQUE),
    MODEL_UTIL_GEO(E_MODEL_BLACK_BOBOMB,            black_bobomb_geo),
    MODEL_UTIL_GEO(E_MODEL_BOBOMB_BUDDY,            bobomb_buddy_geo),
    MODEL_UTIL_DL (E_MODEL_DL_CANNON_LID,           cannon_lid_seg8_dl_080048E0, LAYER_OPAQUE),
    MODEL_UTIL_GEO(E_MODEL_BOWLING_BALL,            bowling_ball_geo),
    MODEL_UTIL_GEO(E_MODEL_CANNON_BARREL,           cannon_barrel_geo),
    MODEL_UTIL_GEO(E_MODEL_CANNON_BASE,             cannon_base_geo),
    MODEL_UTIL_GEO(E_MODEL_HEART,                   heart_geo),
    MODEL_UTIL_GEO(E_MODEL_FLYGUY,                  flyguy_geo),
    MODEL_UTIL_GEO(E_MODEL_CHUCKYA,                 chuckya_geo),
    MODEL_UTIL_GEO(E_MODEL_TRAJECTORY_MARKER_BALL,  bowling_ball_track_geo),
    MODEL_UTIL_GEO(E_MODEL_BULLET_BILL,             bullet_bill_geo),
    MODEL_UTIL_GEO(E_MODEL_YELLOW_SPHERE,           yellow_sphere_geo),
    MODEL_UTIL_GEO(E_MODEL_HOOT,                    hoot_geo),
    MODEL_UTIL_GEO(E_MODEL_YOSHI_EGG,               yoshi_egg_geo),
    MODEL_UTIL_GEO(E_MODEL_THWOMP,                  thwomp_geo),
    MODEL_UTIL_GEO(E_MODEL_HEAVE_HO,                heave_ho_geo),
    MODEL_UTIL_GEO(E_MODEL_BLARGG,                  blargg_geo),
    MODEL_UTIL_GEO(E_MODEL_BULLY,                   bully_geo),
    MODEL_UTIL_GEO(E_MODEL_BULLY_BOSS,              bully_boss_geo),
    MODEL_UTIL_GEO(E_MODEL_WATER_BOMB,              water_bomb_geo),
    MODEL_UTIL_GEO(E_MODEL_WATER_BOMB_SHADOW,       water_bomb_shadow_geo),
    MODEL_UTIL_GEO(E_MODEL_KING_BOBOMB,             king_bobomb_geo),
    MODEL_UTIL_GEO(E_MODEL_MANTA_RAY,               manta_seg5_geo_05008D14),
    MODEL_UTIL_GEO(E_MODEL_UNAGI,                   unagi_geo),
    MODEL_UTIL_GEO(E_MODEL_SUSHI,                   sushi_geo),
    MODEL_UTIL_DL (E_MODEL_DL_WHIRLPOOL,            whirlpool_seg5_dl_05013CB8, LAYER_TRANSPARENT),
    MODEL_UTIL_GEO(E_MODEL_CLAM_SHELL,              clam_shell_geo),
    MODEL_UTIL_GEO(E_MODEL_POKEY_HEAD,              pokey_head_geo),
    MODEL_UTIL_GEO(E_MODEL_POKEY_BODY_PART,         pokey_body_part_geo),
    MODEL_UTIL_GEO(E_MODEL_TWEESTER,                tweester_geo),
    MODEL_UTIL_GEO(E_MODEL_KLEPTO,                  klepto_geo),
    MODEL_UTIL_GEO(E_MODEL_EYEROK_LEFT_HAND,        eyerok_left_hand_geo),
    MODEL_UTIL_GEO(E_MODEL_EYEROK_RIGHT_HAND,       eyerok_right_hand_geo),
    MODEL_UTIL_DL (E_MODEL_DL_MONTY_MOLE_HOLE,      monty_mole_hole_seg5_dl_05000840, LAYER_TRANSPARENT_DECAL),
    MODEL_UTIL_GEO(E_MODEL_MONTY_MOLE,              monty_mole_geo),
    MODEL_UTIL_GEO(E_MODEL_UKIKI,                   ukiki_geo),
    MODEL_UTIL_GEO(E_MODEL_FWOOSH,                  fwoosh_geo),
    MODEL_UTIL_GEO(E_MODEL_SPINDRIFT,               spindrift_geo),
    MODEL_UTIL_GEO(E_MODEL_MR_BLIZZARD_HIDDEN,      mr_blizzard_hidden_geo),
    MODEL_UTIL_GEO(E_MODEL_MR_BLIZZARD,             mr_blizzard_geo),
    MODEL_UTIL_GEO(E_MODEL_PENGUIN,                 penguin_geo),
    MODEL_UTIL_DL (E_MODEL_CAP_SWITCH_EXCLAMATION,  cap_switch_exclamation_seg5_dl_05002E00, LAYER_ALPHA),
    MODEL_UTIL_GEO(E_MODEL_CAP_SWITCH,              cap_switch_geo),
    MODEL_UTIL_DL (E_MODEL_CAP_SWITCH_BASE,         cap_switch_base_seg5_dl_05003120, LAYER_OPAQUE),
    MODEL_UTIL_GEO(E_MODEL_BOO,                     boo_geo),
    MODEL_UTIL_GEO(E_MODEL_BETA_BOO_KEY,            small_key_geo),
    MODEL_UTIL_GEO(E_MODEL_HAUNTED_CHAIR,           haunted_chair_geo),
    MODEL_UTIL_GEO(E_MODEL_MAD_PIANO,               mad_piano_geo),
    MODEL_UTIL_GEO(E_MODEL_BOOKEND_PART,            bookend_part_geo),
    MODEL_UTIL_GEO(E_MODEL_BOOKEND,                 bookend_geo),
    MODEL_UTIL_GEO(E_MODEL_HAUNTED_CAGE,            haunted_cage_geo),
    MODEL_UTIL_GEO(E_MODEL_BIRDS,                   birds_geo),
    MODEL_UTIL_GEO(E_MODEL_PEACH,                   peach_geo),
    MODEL_UTIL_GEO(E_MODEL_YOSHI,                   yoshi_geo),
    MODEL_UTIL_GEO(E_MODEL_ENEMY_LAKITU,            enemy_lakitu_geo),
    MODEL_UTIL_GEO(E_MODEL_SPINY_BALL,              spiny_ball_geo),
    MODEL_UTIL_GEO(E_MODEL_SPINY,                   spiny_geo),
    MODEL_UTIL_GEO(E_MODEL_WIGGLER_HEAD,            wiggler_head_geo),
    MODEL_UTIL_GEO(E_MODEL_WIGGLER_BODY,            wiggler_body_geo),
    MODEL_UTIL_GEO(E_MODEL_BUBBA,                   bubba_geo),
    MODEL_UTIL_GEO(E_MODEL_BOWSER,                  bowser_geo),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_BOMB_CHILD_OBJ,   bowser_bomb_geo),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_BOMB,             bowser_bomb_geo),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_SMOKE,            bowser_impact_smoke_geo),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_FLAMES,           bowser_flames_geo),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_WAVE,             invisible_bowser_accessory_geo),
    MODEL_UTIL_GEO(E_MODEL_BOWSER2,                 bowser2_geo),
    MODEL_UTIL_GEO(E_MODEL_BUB,                     bub_geo),
    MODEL_UTIL_GEO(E_MODEL_TREASURE_CHEST_BASE,     treasure_chest_base_geo),
    MODEL_UTIL_GEO(E_MODEL_TREASURE_CHEST_LID,      treasure_chest_lid_geo),
    MODEL_UTIL_GEO(E_MODEL_CYAN_FISH,               cyan_fish_geo),
    MODEL_UTIL_GEO(E_MODEL_WATER_RING,              water_ring_geo),
    MODEL_UTIL_GEO(E_MODEL_WATER_MINE,              water_mine_geo),
    MODEL_UTIL_GEO(E_MODEL_SEAWEED,                 seaweed_geo),
    MODEL_UTIL_GEO(E_MODEL_SKEETER,                 skeeter_geo),
    MODEL_UTIL_GEO(E_MODEL_PIRANHA_PLANT,           piranha_plant_geo),
    MODEL_UTIL_GEO(E_MODEL_WHOMP,                   whomp_geo),
    MODEL_UTIL_GEO(E_MODEL_KOOPA_WITH_SHELL,        koopa_with_shell_geo),
    MODEL_UTIL_GEO(E_MODEL_KOOPA_WITHOUT_SHELL,     koopa_without_shell_geo),
    MODEL_UTIL_GEO(E_MODEL_METALLIC_BALL,           metallic_ball_geo),
    MODEL_UTIL_GEO(E_MODEL_CHAIN_CHOMP,             chain_chomp_geo),
    MODEL_UTIL_GEO(E_MODEL_KOOPA_FLAG,              koopa_flag_geo),
    MODEL_UTIL_GEO(E_MODEL_WOODEN_POST,             wooden_post_geo),
    MODEL_UTIL_GEO(E_MODEL_MIPS,                    mips_geo),
    MODEL_UTIL_GEO(E_MODEL_BOO_CASTLE,              boo_castle_geo),
    MODEL_UTIL_GEO(E_MODEL_LAKITU,                  lakitu_geo),
    MODEL_UTIL_GEO(E_MODEL_TOAD,                    toad_geo),
    MODEL_UTIL_GEO(E_MODEL_CHILL_BULLY,             chilly_chief_geo),
    MODEL_UTIL_GEO(E_MODEL_BIG_CHILL_BULLY,         chilly_chief_big_geo),
    MODEL_UTIL_GEO(E_MODEL_MONEYBAG,                moneybag_geo),
    MODEL_UTIL_GEO(E_MODEL_SWOOP,                   swoop_geo),
    MODEL_UTIL_GEO(E_MODEL_SCUTTLEBUG,              scuttlebug_geo),
    MODEL_UTIL_GEO(E_MODEL_MR_I_IRIS,               mr_i_iris_geo),
    MODEL_UTIL_GEO(E_MODEL_MR_I,                    mr_i_geo),
    MODEL_UTIL_GEO(E_MODEL_DORRIE,                  dorrie_geo),
    MODEL_UTIL_GEO(E_MODEL_SNUFIT,                  snufit_geo),
    MODEL_UTIL_GEO(E_MODEL_ERROR_MODEL,             error_model_geo),

    // level
    MODEL_UTIL_GEO(E_MODEL_BUBBLY_TREE,                        bubbly_tree_geo),
    MODEL_UTIL_GEO(E_MODEL_COURTYARD_SPIKY_TREE,               spiky_tree_geo),
    MODEL_UTIL_GEO(E_MODEL_SNOW_TREE,                          snow_tree_geo),
    MODEL_UTIL_GEO(E_MODEL_PALM_TREE,                          palm_tree_geo),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_CASTLE_DOOR,                 castle_door_geo),
    MODEL_UTIL_GEO(E_MODEL_BBH_HAUNTED_DOOR,                   haunted_door_geo),
    MODEL_UTIL_GEO(E_MODEL_HMC_WOODEN_DOOR,                    wooden_door_geo),
    MODEL_UTIL_GEO(E_MODEL_HMC_METAL_DOOR,                     metal_door_geo),
    MODEL_UTIL_GEO(E_MODEL_HMC_HAZY_MAZE_DOOR,                 hazy_maze_door_geo),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_DOOR_0_STARS,                castle_door_0_star_geo),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_DOOR_1_STAR,                 castle_door_1_star_geo),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_DOOR_3_STARS,                castle_door_3_stars_geo),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_STAR_DOOR_8_STARS,           castle_geo_000F00),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_STAR_DOOR_30_STARS,          castle_geo_000F00),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_STAR_DOOR_50_STARS,          castle_geo_000F00),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_STAR_DOOR_70_STARS,          castle_geo_000F00),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_KEY_DOOR,                    key_door_geo),
    MODEL_UTIL_GEO(E_MODEL_CCM_CABIN_DOOR,                     cabin_door_geo),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_METAL_DOOR,                  metal_door_geo),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_GROUNDS_METAL_DOOR,          metal_door_geo),
    MODEL_UTIL_GEO(E_MODEL_WF_TOWER_TRAPEZOID_PLATORM,         wf_geo_000AF8),
    MODEL_UTIL_GEO(E_MODEL_WF_TOWER_SQUARE_PLATORM,            wf_geo_000B10),
    MODEL_UTIL_GEO(E_MODEL_WF_TOWER_SQUARE_PLATORM_UNUSED,     wf_geo_000B38),
    MODEL_UTIL_GEO(E_MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR,   wf_geo_000B60),
    MODEL_UTIL_GEO(E_MODEL_BBH_STAIRCASE_STEP,                 geo_bbh_0005B0),
    MODEL_UTIL_GEO(E_MODEL_BBH_TILTING_FLOOR_PLATFORM,         geo_bbh_0005C8),
    MODEL_UTIL_GEO(E_MODEL_BBH_TUMBLING_PLATFORM,              geo_bbh_0005E0),
    MODEL_UTIL_GEO(E_MODEL_BBH_TUMBLING_PLATFORM_PART,         geo_bbh_0005F8),
    MODEL_UTIL_GEO(E_MODEL_BBH_MOVING_BOOKSHELF,               geo_bbh_000610),
    MODEL_UTIL_GEO(E_MODEL_BBH_MESH_ELEVATOR,                  geo_bbh_000628),
    MODEL_UTIL_GEO(E_MODEL_BBH_MERRY_GO_ROUND,                 geo_bbh_000640),
    MODEL_UTIL_GEO(E_MODEL_BBH_WOODEN_TOMB,                    geo_bbh_000658),
    MODEL_UTIL_GEO(E_MODEL_CCM_ROPEWAY_LIFT,                   ccm_geo_0003D0),
    MODEL_UTIL_GEO(E_MODEL_CCM_SNOWMAN_HEAD,                   ccm_geo_00040C),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_BOWSER_TRAP,                 castle_geo_000F18),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_WATER_LEVEL_PILLAR,          castle_geo_001940),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_CLOCK_MINUTE_HAND,           castle_geo_001530),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_CLOCK_HOUR_HAND,             castle_geo_001548),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_CLOCK_PENDULUM,              castle_geo_001518),
    MODEL_UTIL_GEO(E_MODEL_HMC_METAL_PLATFORM,                 hmc_geo_0005A0),
    MODEL_UTIL_GEO(E_MODEL_HMC_METAL_ARROW_PLATFORM,           hmc_geo_0005B8),
    MODEL_UTIL_GEO(E_MODEL_HMC_ELEVATOR_PLATFORM,              hmc_geo_0005D0),
    MODEL_UTIL_GEO(E_MODEL_HMC_ROLLING_ROCK,                   hmc_geo_000548),
    MODEL_UTIL_GEO(E_MODEL_HMC_ROCK_PIECE,                     hmc_geo_000570),
    MODEL_UTIL_GEO(E_MODEL_HMC_ROCK_SMALL_PIECE,               hmc_geo_000588),
    MODEL_UTIL_GEO(E_MODEL_HMC_RED_GRILLS,                     hmc_geo_000530),
    MODEL_UTIL_GEO(E_MODEL_SSL_PYRAMID_TOP,                    ssl_geo_000618),
    MODEL_UTIL_GEO(E_MODEL_SSL_GRINDEL,                        ssl_geo_000734),
    MODEL_UTIL_GEO(E_MODEL_SSL_SPINDEL,                        ssl_geo_000764),
    MODEL_UTIL_GEO(E_MODEL_SSL_MOVING_PYRAMID_WALL,            ssl_geo_000794),
    MODEL_UTIL_GEO(E_MODEL_SSL_PYRAMID_ELEVATOR,               ssl_geo_0007AC),
    MODEL_UTIL_GEO(E_MODEL_SSL_TOX_BOX,                        ssl_geo_000630),
    MODEL_UTIL_GEO(E_MODEL_BOB_CHAIN_CHOMP_GATE,               bob_geo_000440),
    MODEL_UTIL_GEO(E_MODEL_BOB_SEESAW_PLATFORM,                bob_geo_000458),
    MODEL_UTIL_GEO(E_MODEL_BOB_BARS_GRILLS,                    bob_geo_000470),
    MODEL_UTIL_GEO(E_MODEL_SL_SNOW_TRIANGLE,                   sl_geo_000390),
    MODEL_UTIL_GEO(E_MODEL_SL_CRACKED_ICE,                     sl_geo_000360),
    MODEL_UTIL_GEO(E_MODEL_SL_CRACKED_ICE_CHUNK,               sl_geo_000378),
    MODEL_UTIL_GEO(E_MODEL_WDW_SQUARE_FLOATING_PLATFORM,       wdw_geo_000580),
    MODEL_UTIL_GEO(E_MODEL_WDW_ARROW_LIFT,                     wdw_geo_000598),
    MODEL_UTIL_GEO(E_MODEL_WDW_WATER_LEVEL_DIAMOND,            wdw_geo_0005C0),
    MODEL_UTIL_GEO(E_MODEL_WDW_HIDDEN_PLATFORM,                wdw_geo_0005E8),
    MODEL_UTIL_GEO(E_MODEL_WDW_EXPRESS_ELEVATOR,               wdw_geo_000610),
    MODEL_UTIL_GEO(E_MODEL_WDW_RECTANGULAR_FLOATING_PLATFORM,  wdw_geo_000628),
    MODEL_UTIL_GEO(E_MODEL_WDW_ROTATING_PLATFORM,              wdw_geo_000640),
    MODEL_UTIL_GEO(E_MODEL_JRB_SHIP_LEFT_HALF_PART,            jrb_geo_000978),
    MODEL_UTIL_GEO(E_MODEL_JRB_SHIP_BACK_LEFT_PART,            jrb_geo_0009B0),
    MODEL_UTIL_GEO(E_MODEL_JRB_SHIP_RIGHT_HALF_PART,           jrb_geo_0009E8),
    MODEL_UTIL_GEO(E_MODEL_JRB_SHIP_BACK_RIGHT_PART,           jrb_geo_000A00),
    MODEL_UTIL_GEO(E_MODEL_JRB_SUNKEN_SHIP,                    jrb_geo_000990),
    MODEL_UTIL_GEO(E_MODEL_JRB_SUNKEN_SHIP_BACK,               jrb_geo_0009C8),
    MODEL_UTIL_GEO(E_MODEL_JRB_ROCK,                           jrb_geo_000930),
    MODEL_UTIL_GEO(E_MODEL_JRB_SLIDING_BOX,                    jrb_geo_000960),
    MODEL_UTIL_GEO(E_MODEL_JRB_FALLING_PILLAR,                 jrb_geo_000900),
    MODEL_UTIL_GEO(E_MODEL_JRB_FALLING_PILLAR_BASE,            jrb_geo_000918),
    MODEL_UTIL_GEO(E_MODEL_JRB_FLOATING_PLATFORM,              jrb_geo_000948),
    MODEL_UTIL_GEO(E_MODEL_THI_HUGE_ISLAND_TOP,                thi_geo_0005B0),
    MODEL_UTIL_GEO(E_MODEL_THI_TINY_ISLAND_TOP,                thi_geo_0005C8),
    MODEL_UTIL_GEO(E_MODEL_TTC_ROTATING_CUBE,                  ttc_geo_000240),
    MODEL_UTIL_GEO(E_MODEL_TTC_ROTATING_PRISM,                 ttc_geo_000258),
    MODEL_UTIL_GEO(E_MODEL_TTC_PENDULUM,                       ttc_geo_000270),
    MODEL_UTIL_GEO(E_MODEL_TTC_LARGE_TREADMILL,                ttc_geo_000288),
    MODEL_UTIL_GEO(E_MODEL_TTC_SMALL_TREADMILL,                ttc_geo_0002A8),
    MODEL_UTIL_GEO(E_MODEL_TTC_PUSH_BLOCK,                     ttc_geo_0002C8),
    MODEL_UTIL_GEO(E_MODEL_TTC_ROTATING_HEXAGON,               ttc_geo_0002E0),
    MODEL_UTIL_GEO(E_MODEL_TTC_ROTATING_TRIANGLE,              ttc_geo_0002F8),
    MODEL_UTIL_GEO(E_MODEL_TTC_PIT_BLOCK,                      ttc_geo_000310),
    MODEL_UTIL_GEO(E_MODEL_TTC_PIT_BLOCK_UNUSED,               ttc_geo_000328),
    MODEL_UTIL_GEO(E_MODEL_TTC_ELEVATOR_PLATFORM,              ttc_geo_000340),
    MODEL_UTIL_GEO(E_MODEL_TTC_CLOCK_HAND,                     ttc_geo_000358),
    MODEL_UTIL_GEO(E_MODEL_TTC_SPINNER,                        ttc_geo_000370),
    MODEL_UTIL_GEO(E_MODEL_TTC_SMALL_GEAR,                     ttc_geo_000388),
    MODEL_UTIL_GEO(E_MODEL_TTC_LARGE_GEAR,                     ttc_geo_0003A0),
    MODEL_UTIL_GEO(E_MODEL_RR_SLIDING_PLATFORM,                rr_geo_0008C0),
    MODEL_UTIL_GEO(E_MODEL_RR_FLYING_CARPET,                   rr_geo_000848),
    MODEL_UTIL_GEO(E_MODEL_RR_OCTAGONAL_PLATFORM,              rr_geo_0008A8),
    MODEL_UTIL_GEO(E_MODEL_RR_ROTATING_BRIDGE_PLATFORM,        rr_geo_000878),
    MODEL_UTIL_GEO(E_MODEL_RR_TRIANGLE_PLATFORM,               rr_geo_0008D8),
    MODEL_UTIL_GEO(E_MODEL_RR_CRUISER_WING,                    rr_geo_000890),
    MODEL_UTIL_GEO(E_MODEL_RR_SEESAW_PLATFORM,                 rr_geo_000908),
    MODEL_UTIL_GEO(E_MODEL_RR_L_SHAPED_PLATFORM,               rr_geo_000940),
    MODEL_UTIL_GEO(E_MODEL_RR_SWINGING_PLATFORM,               rr_geo_000860),
    MODEL_UTIL_GEO(E_MODEL_RR_DONUT_PLATFORM,                  rr_geo_000920),
    MODEL_UTIL_GEO(E_MODEL_RR_ELEVATOR_PLATFORM,               rr_geo_0008F0),
    MODEL_UTIL_GEO(E_MODEL_RR_TRICKY_TRIANGLES,                rr_geo_000958),
    MODEL_UTIL_GEO(E_MODEL_RR_TRICKY_TRIANGLES_FRAME1,         rr_geo_000970),
    MODEL_UTIL_GEO(E_MODEL_RR_TRICKY_TRIANGLES_FRAME2,         rr_geo_000988),
    MODEL_UTIL_GEO(E_MODEL_RR_TRICKY_TRIANGLES_FRAME3,         rr_geo_0009A0),
    MODEL_UTIL_GEO(E_MODEL_RR_TRICKY_TRIANGLES_FRAME4,         rr_geo_0009B8),
    MODEL_UTIL_GEO(E_MODEL_BITDW_SQUARE_PLATFORM,              geo_bitdw_000558),
    MODEL_UTIL_GEO(E_MODEL_BITDW_SEESAW_PLATFORM,              geo_bitdw_000540),
    MODEL_UTIL_GEO(E_MODEL_BITDW_SLIDING_PLATFORM,             geo_bitdw_000528),
    MODEL_UTIL_GEO(E_MODEL_BITDW_FERRIS_WHEEL_AXLE,            geo_bitdw_000570),
    MODEL_UTIL_GEO(E_MODEL_BITDW_BLUE_PLATFORM,                geo_bitdw_000588),
    MODEL_UTIL_GEO(E_MODEL_BITDW_STAIRCASE_FRAME4,             geo_bitdw_0005A0),
    MODEL_UTIL_GEO(E_MODEL_BITDW_STAIRCASE_FRAME3,             geo_bitdw_0005B8),
    MODEL_UTIL_GEO(E_MODEL_BITDW_STAIRCASE_FRAME2,             geo_bitdw_0005D0),
    MODEL_UTIL_GEO(E_MODEL_BITDW_STAIRCASE_FRAME1,             geo_bitdw_0005E8),
    MODEL_UTIL_GEO(E_MODEL_BITDW_STAIRCASE,                    geo_bitdw_000600),
    MODEL_UTIL_GEO(E_MODEL_BITFS_PLATFORM_ON_TRACK,            bitfs_geo_000758),
    MODEL_UTIL_GEO(E_MODEL_BITFS_TILTING_SQUARE_PLATFORM,      bitfs_geo_0006C0),
    MODEL_UTIL_GEO(E_MODEL_BITFS_SINKING_PLATFORMS,            bitfs_geo_000770),
    MODEL_UTIL_GEO(E_MODEL_BITFS_BLUE_POLE,                    bitfs_geo_0006A8),
    MODEL_UTIL_GEO(E_MODEL_BITFS_SINKING_CAGE_PLATFORM,        bitfs_geo_000690),
    MODEL_UTIL_GEO(E_MODEL_BITFS_ELEVATOR,                     bitfs_geo_000678),
    MODEL_UTIL_GEO(E_MODEL_BITFS_STRETCHING_PLATFORMS,         bitfs_geo_000708),
    MODEL_UTIL_GEO(E_MODEL_BITFS_SEESAW_PLATFORM,              bitfs_geo_000788),
    MODEL_UTIL_GEO(E_MODEL_BITFS_MOVING_SQUARE_PLATFORM,       bitfs_geo_000728),
    MODEL_UTIL_GEO(E_MODEL_BITFS_SLIDING_PLATFORM,             bitfs_geo_000740),
    MODEL_UTIL_GEO(E_MODEL_BITFS_TUMBLING_PLATFORM_PART,       bitfs_geo_0006D8),
    MODEL_UTIL_GEO(E_MODEL_BITFS_TUMBLING_PLATFORM,            bitfs_geo_0006F0),
    MODEL_UTIL_GEO(E_MODEL_BITS_SLIDING_PLATFORM,              bits_geo_0005E0),
    MODEL_UTIL_GEO(E_MODEL_BITS_TWIN_SLIDING_PLATFORMS,        bits_geo_0005F8),
    MODEL_UTIL_GEO(E_MODEL_BITS_OCTAGONAL_PLATFORM,            bits_geo_000610),
    MODEL_UTIL_GEO(E_MODEL_BITS_BLUE_PLATFORM,                 bits_geo_000628),
    MODEL_UTIL_GEO(E_MODEL_BITS_FERRIS_WHEEL_AXLE,             bits_geo_000640),
    MODEL_UTIL_GEO(E_MODEL_BITS_ARROW_PLATFORM,                bits_geo_000658),
    MODEL_UTIL_GEO(E_MODEL_BITS_SEESAW_PLATFORM,               bits_geo_000670),
    MODEL_UTIL_GEO(E_MODEL_BITS_TILTING_W_PLATFORM,            bits_geo_000688),
    MODEL_UTIL_GEO(E_MODEL_BITS_STAIRCASE,                     bits_geo_0006A0),
    MODEL_UTIL_GEO(E_MODEL_BITS_STAIRCASE_FRAME1,              bits_geo_0006B8),
    MODEL_UTIL_GEO(E_MODEL_BITS_STAIRCASE_FRAME2,              bits_geo_0006D0),
    MODEL_UTIL_GEO(E_MODEL_BITS_STAIRCASE_FRAME3,              bits_geo_0006E8),
    MODEL_UTIL_GEO(E_MODEL_BITS_STAIRCASE_FRAME4,              bits_geo_000700),
    MODEL_UTIL_GEO(E_MODEL_BITS_WARP_PIPE,                     warp_pipe_geo),
    MODEL_UTIL_GEO(E_MODEL_LLL_DRAWBRIDGE_PART,                lll_geo_000B20),
    MODEL_UTIL_GEO(E_MODEL_LLL_ROTATING_BLOCK_FIRE_BARS,       lll_geo_000B38),
    MODEL_UTIL_GEO(E_MODEL_LLL_ROTATING_HEXAGONAL_RING,        lll_geo_000BB0),
    MODEL_UTIL_GEO(E_MODEL_LLL_SINKING_RECTANGULAR_PLATFORM,   lll_geo_000BC8),
    MODEL_UTIL_GEO(E_MODEL_LLL_SINKING_SQUARE_PLATFORMS,       lll_geo_000BE0),
    MODEL_UTIL_GEO(E_MODEL_LLL_TILTING_SQUARE_PLATFORM,        lll_geo_000BF8),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_1,                 lll_geo_000C10),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_2,                 lll_geo_000C30),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_3,                 lll_geo_000C50),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_4,                 lll_geo_000C70),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_5,                 lll_geo_000C90),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_6,                 lll_geo_000CB0),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_7,                 lll_geo_000CD0),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_8,                 lll_geo_000CF0),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_9,                 lll_geo_000D10),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_10,                lll_geo_000D30),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_11,                lll_geo_000D50),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_12,                lll_geo_000D70),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_13,                lll_geo_000D90),
    MODEL_UTIL_GEO(E_MODEL_LLL_BOWSER_PIECE_14,                lll_geo_000DB0),
    MODEL_UTIL_GEO(E_MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM, lll_geo_000B08),
    MODEL_UTIL_GEO(E_MODEL_LLL_SINKING_ROCK_BLOCK,             lll_geo_000DD0),
    MODEL_UTIL_GEO(E_MODEL_LLL_ROLLING_LOG,                    lll_geo_000DE8),
    MODEL_UTIL_GEO(E_MODEL_LLL_WOOD_BRIDGE,                    lll_geo_000B50),
    MODEL_UTIL_GEO(E_MODEL_LLL_LARGE_WOOD_BRIDGE,              lll_geo_000B68),
    MODEL_UTIL_GEO(E_MODEL_LLL_FALLING_PLATFORM,               lll_geo_000B80),
    MODEL_UTIL_GEO(E_MODEL_LLL_LARGE_FALLING_PLATFORM,         lll_geo_000B98),
    MODEL_UTIL_GEO(E_MODEL_LLL_VOLCANO_FALLING_TRAP,           lll_geo_000EA8),
    MODEL_UTIL_GEO(E_MODEL_DDD_BOWSER_SUB_DOOR,                ddd_geo_000478),
    MODEL_UTIL_GEO(E_MODEL_DDD_BOWSER_SUB,                     ddd_geo_0004A0),
    MODEL_UTIL_GEO(E_MODEL_DDD_POLE,                           ddd_geo_000450),
    MODEL_UTIL_GEO(E_MODEL_WF_BREAKABLE_WALL_RIGHT,            wf_geo_000B78),
    MODEL_UTIL_GEO(E_MODEL_WF_BREAKABLE_WALL_LEFT,             wf_geo_000B90),
    MODEL_UTIL_GEO(E_MODEL_WF_KICKABLE_BOARD,                  wf_geo_000BA8),
    MODEL_UTIL_GEO(E_MODEL_WF_TOWER_DOOR,                      wf_geo_000BE0),
    MODEL_UTIL_GEO(E_MODEL_WF_KICKABLE_BOARD_FELLED,           wf_geo_000BC8),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_GROUNDS_VCUTM_GRILL,         castle_grounds_geo_00070C),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_GROUNDS_FLAG,                castle_grounds_geo_000660),
    MODEL_UTIL_GEO(E_MODEL_CASTLE_GROUNDS_CANNON_GRILL,        castle_grounds_geo_000724),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_2_TILTING_ARENA,             bowser_2_geo_000170),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_1,        bowser_3_geo_000290),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_2,        bowser_3_geo_0002A8),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_3,        bowser_3_geo_0002C0),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_4,        bowser_3_geo_0002D8),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_5,        bowser_3_geo_0002F0),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_6,        bowser_3_geo_000308),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_7,        bowser_3_geo_000320),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_8,        bowser_3_geo_000338),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_9,        bowser_3_geo_000350),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_3_FALLING_PLATFORM_10,       bowser_3_geo_000368),
    MODEL_UTIL_GEO(E_MODEL_TTM_ROLLING_LOG,                    ttm_geo_000730),
    MODEL_UTIL_GEO(E_MODEL_TTM_STAR_CAGE,                      ttm_geo_000710),
    MODEL_UTIL_GEO(E_MODEL_TTM_BLUE_SMILEY,                    ttm_geo_000D14),
    MODEL_UTIL_GEO(E_MODEL_TTM_YELLOW_SMILEY,                  ttm_geo_000D4C),
    MODEL_UTIL_GEO(E_MODEL_TTM_STAR_SMILEY,                    ttm_geo_000D84),
    MODEL_UTIL_GEO(E_MODEL_TTM_MOON_SMILEY,                    ttm_geo_000DBC),

    // custom models
    MODEL_UTIL_GEO_PERM(E_MODEL_BUBBLE_PLAYER,             water_bomb_geo,                MODEL_BUBBLE_PLAYER),
    MODEL_UTIL_GEO_PERM(E_MODEL_LUIGI,                     luigi_geo,                     MODEL_LUIGI),
    MODEL_UTIL_GEO_PERM(E_MODEL_LUIGIS_CAP,                luigis_cap_geo,                MODEL_LUIGIS_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_LUIGIS_METAL_CAP,          luigis_metal_cap_geo,          MODEL_LUIGIS_METAL_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_LUIGIS_WING_CAP,           luigis_wing_cap_geo,           MODEL_LUIGIS_WING_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_LUIGIS_WINGED_METAL_CAP,   luigis_winged_metal_cap_geo,   MODEL_LUIGIS_WINGED_METAL_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_TOAD_PLAYER,               toad_player_geo,               MODEL_TOAD_PLAYER),
    MODEL_UTIL_GEO_PERM(E_MODEL_TOADS_CAP,                 toads_cap_geo,                 MODEL_TOADS_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_TOADS_METAL_CAP,           toads_metal_cap_geo,           MODEL_TOADS_METAL_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_TOADS_WING_CAP,            toads_wing_cap_geo,            MODEL_TOADS_WING_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_WALUIGI,                   waluigi_geo,                   MODEL_WALUIGI),
    MODEL_UTIL_GEO_PERM(E_MODEL_WALUIGIS_CAP,              waluigis_cap_geo,              MODEL_WALUIGIS_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_WALUIGIS_METAL_CAP,        waluigis_metal_cap_geo,        MODEL_WALUIGIS_METAL_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_WALUIGIS_WING_CAP,         waluigis_wing_cap_geo,         MODEL_WALUIGIS_WING_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_WALUIGIS_WINGED_METAL_CAP, waluigis_winged_metal_cap_geo, MODEL_WALUIGIS_WINGED_METAL_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_WARIO,                     wario_geo,                     MODEL_WARIO),
    MODEL_UTIL_GEO_PERM(E_MODEL_WARIOS_CAP,                warios_cap_geo,                MODEL_WARIOS_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_WARIOS_METAL_CAP,          warios_metal_cap_geo,          MODEL_WARIOS_METAL_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_WARIOS_WING_CAP,           warios_wing_cap_geo,           MODEL_WARIOS_WING_CAP),
    MODEL_UTIL_GEO_PERM(E_MODEL_WARIOS_WINGED_METAL_CAP,   warios_winged_metal_cap_geo,   MODEL_WARIOS_WINGED_METAL_CAP),
};

#define CUSTOM_MODEL_CHUNK_SIZE 256
static u16 sCustomModelsCount = 0;
static u16 sMaxCustomModelsCount = CUSTOM_MODEL_CHUNK_SIZE;
struct ModelUtilsInfo *sCustomModels = NULL;

void smlua_model_util_initialize(void) {
    // Allocate the custom models array. We start off with a maximum of 256 custom models.
    sCustomModels = (struct ModelUtilsInfo *)calloc(sMaxCustomModelsCount, sizeof(struct ModelUtilsInfo));
}

void smlua_model_util_clear(void) {
    sCustomModelsCount = 0;
    sMaxCustomModelsCount = CUSTOM_MODEL_CHUNK_SIZE;
    if (sCustomModels) { free(sCustomModels); }
    sCustomModels = NULL;
}

void smlua_model_util_store_in_slot(u32 slot, const char* name) {
    u32 extId = smlua_model_util_get_id(name);
    if (extId == E_MODEL_ERROR_MODEL) { return; }
    u32 loadedId = smlua_model_util_load(extId);
    dynos_model_overwrite_slot(slot, loadedId);
}

// Takes an extended model id, loads the model, and returns the regular model id
u16 smlua_model_util_load(enum ModelExtendedId extId) {
    if (extId == E_MODEL_NONE) { return MODEL_NONE; }
    if (!extId || (u32)extId >= (u32)E_MODEL_MAX + (u32)sCustomModelsCount) { extId = E_MODEL_ERROR_MODEL; }

    struct ModelUtilsInfo* info = (extId < E_MODEL_MAX)
        ? &sModels[extId]
        : &sCustomModels[extId - E_MODEL_MAX];

    u32 id = info->loadedId;
    if (info->isDisplayList) {
        dynos_model_load_dl(&id, MODEL_POOL_SESSION, info->layer, (void*)info->asset);
    } else {
        dynos_model_load_geo(&id, MODEL_POOL_SESSION, (void*)info->asset, true);
    }
    return (u16)id;
}

// Links the regular model id created by DynOS to our models list
void smlua_model_util_register_model_id(u32 id, const void *asset) {
    if (id < VANILLA_ID_END) {
        for (u32 i = 0; i < E_MODEL_MAX; i++) {
            struct ModelUtilsInfo* m = &sModels[i];
            if (m->asset == asset) {
                m->loadedId = id;
                return;
            }
        }
    } else {
        for (u32 i = 0; i < sCustomModelsCount; i++) {
            struct ModelUtilsInfo* m = &sCustomModels[i];
            if (m->asset == asset) {
                m->loadedId = id;
                return;
            }
        }
    }
}

// Translates an extended model id to a regular model id
u16 smlua_model_util_ext_id_to_id(enum ModelExtendedId extId) {
    if (extId == E_MODEL_NONE) { return MODEL_NONE; }
    if ((u32)extId >= (u32)E_MODEL_MAX + (u32)sCustomModelsCount) { return MODEL_ERROR_MODEL; }

    struct ModelUtilsInfo* info = (extId < E_MODEL_MAX)
        ? &sModels[extId]
        : &sCustomModels[extId - E_MODEL_MAX];
    return info->loadedId != UNLOADED_ID ? info->loadedId : MODEL_ERROR_MODEL;
}

// Translates a regular model id to an extended model id
enum ModelExtendedId smlua_model_util_id_to_ext_id(u16 id) {
    if (!id) { return E_MODEL_NONE; }

    // Check built-in models
    for (u32 i = 0; i < E_MODEL_MAX; i++) {
        struct ModelUtilsInfo* m = &sModels[i];
        if (m->loadedId == id) {
            return m->extId;
        }
    }

    // Check custom models
    for (u32 i = 0; i < sCustomModelsCount; i++) {
        struct ModelUtilsInfo* m = &sCustomModels[i];
        if (m->loadedId == id) {
            return m->extId;
        }
    }

    return E_MODEL_ERROR_MODEL;
}

enum ModelExtendedId smlua_model_util_get_id(const char* name) {
    // Find geolayout
    const void* asset = dynos_geolayout_get(name);
    if (asset == NULL) {
        LOG_LUA_LINE("Could not find model: '%s'", name);
        return E_MODEL_ERROR_MODEL;
    }

    // Find existing built-in model
    for (u32 i = 0; i < E_MODEL_MAX; i++) {
        struct ModelUtilsInfo* m = &sModels[i];
        if (m->asset == asset) {
            return m->extId;
        }
    }

    // Find existing custom model
    for (u32 i = 0; i < sCustomModelsCount; i++) {
        struct ModelUtilsInfo* m = &sCustomModels[i];
        if (m->asset == asset) {
            return m->extId;
        }
    }

    // If we've extended past our current custom model limit. Reallocate so we have more space.
    if (sCustomModelsCount >= sMaxCustomModelsCount) {
        if (sMaxCustomModelsCount + CUSTOM_MODEL_CHUNK_SIZE >= 0xFFFF) {
            LOG_LUA("Failed to get model: '%s' (too many custom models!)", name);
            return E_MODEL_ERROR_MODEL;
        }
        sMaxCustomModelsCount += CUSTOM_MODEL_CHUNK_SIZE;
        sCustomModels = (struct ModelUtilsInfo *)realloc(sCustomModels, sMaxCustomModelsCount * sizeof(struct ModelUtilsInfo));
    }

    // Allocate custom model
    u16 customIndex = sCustomModelsCount++;
    struct ModelUtilsInfo* info = &sCustomModels[customIndex];
    info->asset = asset;
    info->loadedId = UNLOADED_ID;
    info->extId = E_MODEL_MAX + customIndex;
    info->isDisplayList = false;
    info->layer = LAYER_OPAQUE;

    return info->extId;
}
