#include "sm64.h"
#include "types.h"

#include "src/game/area.h"
#include "src/engine/graph_node.h"
#include "src/engine/level_script.h"

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

#include "smlua_model_utils.h"
#include "pc/debuglog.h"

struct ModelUtilsInfo {
    enum ModelExtendedId id;
    const void* asset;
    u8 layer;
    u8 cacheId;
};

#define MODEL_UTIL_GEO(x, y) [x] = { .id = x, .asset = y, .layer = LAYER_OPAQUE, .cacheId = 0xFF }
#define MODEL_UTIL_DL(x, y, z) [x] = { .id = x, .asset = y, .layer = z, .cacheId = 0xFF }

struct ModelUtilsInfo sModels[] = {
    MODEL_UTIL_GEO(E_MODEL_MARIO,                   mario_geo),
    MODEL_UTIL_GEO(E_MODEL_SMOKE,                   smoke_geo),
    MODEL_UTIL_GEO(E_MODEL_SPARKLES,                sparkles_geo),
    MODEL_UTIL_GEO(E_MODEL_BUBBLE,                  bubble_geo),
    MODEL_UTIL_GEO(E_MODEL_SMALL_WATER_SPLASH,      small_water_splash_geo),
    MODEL_UTIL_GEO(E_MODEL_IDLE_WATER_WAVE,         idle_water_wave_geo),
    MODEL_UTIL_GEO(E_MODEL_WATER_SPLASH,            water_splash_geo),
    MODEL_UTIL_GEO(E_MODEL_WAVE_TRAIL,              wave_trail_geo),
    MODEL_UTIL_GEO(E_MODEL_YELLOW_COIN,             yellow_coin_geo),
    MODEL_UTIL_GEO(E_MODEL_STAR,                    star_geo),
    MODEL_UTIL_GEO(E_MODEL_TRANSPARENT_STAR,        transparent_star_geo),
    MODEL_UTIL_GEO(E_MODEL_WOODEN_SIGNPOST,         wooden_signpost_geo),
    MODEL_UTIL_DL (E_MODEL_WHITE_PARTICLE_SMALL,    white_particle_small_dl, LAYER_ALPHA),
    MODEL_UTIL_GEO(E_MODEL_RED_FLAME,               red_flame_geo),
    MODEL_UTIL_GEO(E_MODEL_BLUE_FLAME,              blue_flame_geo),
    MODEL_UTIL_GEO(E_MODEL_BURN_SMOKE,              burn_smoke_geo),
    MODEL_UTIL_GEO(E_MODEL_LEAVES,                  leaves_geo),
    MODEL_UTIL_GEO(E_MODEL_PURPLE_MARBLE,           purple_marble_geo),
    MODEL_UTIL_GEO(E_MODEL_FISH,                    fish_geo),
    MODEL_UTIL_GEO(E_MODEL_FISH_SHADOW,             fish_shadow_geo),
    MODEL_UTIL_GEO(E_MODEL_SPARKLES_ANIMATION,      sparkles_animation_geo),
    MODEL_UTIL_DL (E_MODEL_SAND_DUST,               sand_seg3_dl_0302BCD0, LAYER_ALPHA),
    MODEL_UTIL_GEO(E_MODEL_BUTTERFLY,               butterfly_geo),
    MODEL_UTIL_GEO(E_MODEL_BURN_SMOKE_UNUSED,       burn_smoke_geo),
    MODEL_UTIL_DL (E_MODEL_PEBBLE,                  pebble_seg3_dl_0301CB00, LAYER_ALPHA),
    MODEL_UTIL_GEO(E_MODEL_MIST,                    mist_geo),
    MODEL_UTIL_GEO(E_MODEL_WHITE_PUFF,              white_puff_geo),
    MODEL_UTIL_DL (E_MODEL_WHITE_PARTICLE_DL,       white_particle_dl, LAYER_ALPHA),
    MODEL_UTIL_GEO(E_MODEL_WHITE_PARTICLE,          white_particle_geo),
    MODEL_UTIL_GEO(E_MODEL_YELLOW_COIN_NO_SHADOW,   yellow_coin_no_shadow_geo),
    MODEL_UTIL_GEO(E_MODEL_BLUE_COIN,               blue_coin_geo),
    MODEL_UTIL_GEO(E_MODEL_BLUE_COIN_NO_SHADOW,     blue_coin_no_shadow_geo),
    MODEL_UTIL_GEO(E_MODEL_MARIOS_WINGED_METAL_CAP, marios_winged_metal_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_MARIOS_METAL_CAP,        marios_metal_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_MARIOS_WING_CAP,         marios_wing_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_MARIOS_CAP,              marios_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_MARIOS_CAP2,              marios_cap_geo), // repeated
    MODEL_UTIL_GEO(E_MODEL_BOWSER_KEY_CUTSCENE,     bowser_key_cutscene_geo),
    MODEL_UTIL_GEO(E_MODEL_BOWSER_KEY,              bowser_key_geo),
    MODEL_UTIL_GEO(E_MODEL_RED_FLAME_SHADOW,        red_flame_shadow_geo),
    MODEL_UTIL_GEO(E_MODEL_1UP,                     mushroom_1up_geo),
    MODEL_UTIL_GEO(E_MODEL_RED_COIN,                red_coin_geo),
    MODEL_UTIL_GEO(E_MODEL_RED_COIN_NO_SHADOW,      red_coin_no_shadow_geo),
    MODEL_UTIL_GEO(E_MODEL_NUMBER,                  number_geo),
    MODEL_UTIL_GEO(E_MODEL_EXPLOSION,               explosion_geo),
    MODEL_UTIL_GEO(E_MODEL_DIRT_ANIMATION,          dirt_animation_geo),
    MODEL_UTIL_GEO(E_MODEL_CARTOON_STAR,            cartoon_star_geo),
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

    // CUSTOM MODELS BEGIN
    MODEL_UTIL_GEO(E_MODEL_BUBBLE_PLAYER,             water_bomb_geo),
    MODEL_UTIL_GEO(E_MODEL_LUIGI,                     luigi_geo),
    MODEL_UTIL_GEO(E_MODEL_LUIGIS_CAP,                luigis_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_LUIGIS_METAL_CAP,          luigis_metal_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_LUIGIS_WING_CAP,           luigis_wing_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_LUIGIS_WINGED_METAL_CAP,   luigis_winged_metal_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_TOAD_PLAYER,               toad_player_geo),
    MODEL_UTIL_GEO(E_MODEL_TOADS_CAP,                 toads_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_TOADS_METAL_CAP,           toads_metal_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_TOADS_WING_CAP,            toads_wing_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_WALUIGI,                   waluigi_geo),
    MODEL_UTIL_GEO(E_MODEL_WALUIGIS_CAP,              waluigis_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_WALUIGIS_METAL_CAP,        waluigis_metal_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_WALUIGIS_WING_CAP,         waluigis_wing_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_WALUIGIS_WINGED_METAL_CAP, waluigis_winged_metal_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_WARIO,                     wario_geo),
    MODEL_UTIL_GEO(E_MODEL_WARIOS_CAP,                warios_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_WARIOS_METAL_CAP,          warios_metal_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_WARIOS_WING_CAP,           warios_wing_cap_geo),
    MODEL_UTIL_GEO(E_MODEL_WARIOS_WINGED_METAL_CAP,   warios_winged_metal_cap_geo),
    // CUSTOM MODELS END
};

struct ModelUtilsInfo sCachedAssets[256] = { 0 };

void smlua_model_util_remember(u8 modelId, u8 layer, const void* asset) {
    struct ModelUtilsInfo* c = &sCachedAssets[modelId];
    c->id = modelId;
    c->layer = layer;
    c->asset = asset;
}

void smlua_model_util_clear(void) {
    memset(sCachedAssets, 0, sizeof(sCachedAssets));
    for (int i = 0; i < E_MODEL_MAX; i++) {
        if (sModels[i].cacheId != 0xFF) {
            gLoadedGraphNodes[sModels[i].cacheId] = NULL;
        }
        sModels[i].cacheId = 0xFF;
    }
}

u8 smlua_model_util_load(enum ModelExtendedId id) {
    if (id >= E_MODEL_MAX) {
        LOG_ERROR("id invalid");
        return 0xFF;
    }

    struct ModelUtilsInfo* info = &sModels[id];

    // check cache
    if (info->cacheId != 0xFF) {
        //LOG_INFO("Found in info cache");
        return info->cacheId;
    }

    // find cached asset
    bool foundEmptyCacheId = false;
    u8 emptyCacheId = 0;
    for (int i = 0; i < 255; i++) {
        if (sCachedAssets[i].asset == info->asset) {
            //LOG_INFO("Found in cached assets");
            return sCachedAssets[i].id;
        }
        if (sCachedAssets[i].asset == NULL) {
            foundEmptyCacheId = true;
            emptyCacheId = i;
        }
    }
    if (!foundEmptyCacheId) {
        LOG_ERROR("No empty cache");
        return 0xFF;
    }

    // load
    struct AllocOnlyPool* pool = alloc_only_pool_init(main_pool_available() - sizeof(struct AllocOnlyPool), MEMORY_POOL_LEFT);
    gLoadedGraphNodes[emptyCacheId] = process_geo_layout(pool, (void*)info->asset);
    alloc_only_pool_resize(pool, pool->usedSpace);
    //LOG_INFO("Loaded at runtime");

    // remember
    smlua_model_util_remember(emptyCacheId, info->layer, info->asset);
    info->cacheId = emptyCacheId;

    return emptyCacheId;
}
