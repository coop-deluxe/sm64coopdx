#include "dynos.cpp.h"
extern "C" {
#include "include/level_commands.h"
#include "include/model_ids.h"
#include "include/behavior_data.h"
#include "include/surface_terrains.h"
#include "include/seq_ids.h"
#include "level_commands.h"
#include "src/game/level_update.h"
}

// Free data pointers, but keep nodes and tokens intact
// Delete nodes generated from GfxDynCmds
template <typename T>
static void ClearLvlDataNodes(DataNodes<T> &aDataNodes) {
    for (s32 i = aDataNodes.Count(); i != 0; --i) {
        Delete(aDataNodes[i - 1]->mData);
    }
}

//
// Lvl Functions
//

static const Array<Pair<const char *, void *>> &__LvlFunctions() {
#define define_lvl_function(name) { #name, (void *) name }
static const Array<Pair<const char *, void *>> sLvlFunctions = {
    define_lvl_function(lvl_init_or_update)
};
#undef define_lvl_function
return sLvlFunctions;
}
#define sLvlFunctions __LvlFunctions()

void *DynOS_Lvl_GetFunctionPointerFromName(const String &aName) {
    for (const auto &_GeoFunction : sLvlFunctions) {
        if (aName == _GeoFunction.first) {
            return _GeoFunction.second;
        }
    };
    return NULL;
}

//
// Parse level script file
//

#define LEVEL_SCRIPT_SIZE_PER_TOKEN 4

#define lvl_constant(x) if (_Arg == #x) { return (LevelScript) (x); }
static LevelScript ParseLevelScriptSymbolArg(GfxData* aGfxData, DataNode<LevelScript>* aNode, u64& aTokenIndex) {
    const String& _Arg = aNode->mTokens[aTokenIndex++];

    // Lvl functions
    void *_LvlFunctionPtr = DynOS_Lvl_GetFunctionPointerFromName(_Arg);
    if (_LvlFunctionPtr != NULL) {
        return (LevelScript) _LvlFunctionPtr;
    }

    // Behavior constants
    lvl_constant(bhvMario);
    lvl_constant(bhvAirborneWarp);

    // Level constants
    lvl_constant(LEVEL_BOB);

    // Surface constants
    lvl_constant(TERRAIN_GRASS);

    // Seq ids constants
    lvl_constant(SEQ_LEVEL_GRASS);

    // Model constants
    lvl_constant(ACT_1);
    lvl_constant(ACT_2);
    lvl_constant(ACT_3);
    lvl_constant(ACT_4);
    lvl_constant(ACT_5);
    lvl_constant(ACT_6);
    lvl_constant(ALL_ACTS_MACRO);
    lvl_constant(ALL_ACTS);
    lvl_constant(COIN_FORMATION_FLAG_VERTICAL);
    lvl_constant(COIN_FORMATION_FLAG_RING);
    lvl_constant(COIN_FORMATION_FLAG_ARROW);
    lvl_constant(COIN_FORMATION_FLAG_FLYING);
    lvl_constant(MODEL_NONE);
    lvl_constant(MODEL_MARIO);
    lvl_constant(MODEL_LEVEL_GEOMETRY_03);
    lvl_constant(MODEL_LEVEL_GEOMETRY_04);
    lvl_constant(MODEL_LEVEL_GEOMETRY_05);
    lvl_constant(MODEL_LEVEL_GEOMETRY_06);
    lvl_constant(MODEL_LEVEL_GEOMETRY_07);
    lvl_constant(MODEL_LEVEL_GEOMETRY_08);
    lvl_constant(MODEL_LEVEL_GEOMETRY_09);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0A);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0B);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0C);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0D);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0E);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0F);
    lvl_constant(MODEL_LEVEL_GEOMETRY_10);
    lvl_constant(MODEL_LEVEL_GEOMETRY_11);
    lvl_constant(MODEL_LEVEL_GEOMETRY_12);
    lvl_constant(MODEL_LEVEL_GEOMETRY_13);
    lvl_constant(MODEL_LEVEL_GEOMETRY_14);
    lvl_constant(MODEL_LEVEL_GEOMETRY_15);
    lvl_constant(MODEL_LEVEL_GEOMETRY_16);
    lvl_constant(MODEL_BOB_BUBBLY_TREE);
    lvl_constant(MODEL_WDW_BUBBLY_TREE);
    lvl_constant(MODEL_CASTLE_GROUNDS_BUBBLY_TREE);
    lvl_constant(MODEL_WF_BUBBLY_TREE);
    lvl_constant(MODEL_THI_BUBBLY_TREE);
    lvl_constant(MODEL_COURTYARD_SPIKY_TREE);
    lvl_constant(MODEL_CCM_SNOW_TREE);
    lvl_constant(MODEL_SL_SNOW_TREE);
    lvl_constant(MODEL_UNKNOWN_TREE_1A);
    lvl_constant(MODEL_SSL_PALM_TREE);
    lvl_constant(MODEL_CASTLE_CASTLE_DOOR_UNUSED);
    lvl_constant(MODEL_CASTLE_WOODEN_DOOR_UNUSED);
    lvl_constant(MODEL_BBH_HAUNTED_DOOR);
    lvl_constant(MODEL_HMC_WOODEN_DOOR);
    lvl_constant(MODEL_UNKNOWN_DOOR_1E);
    lvl_constant(MODEL_HMC_METAL_DOOR);
    lvl_constant(MODEL_HMC_HAZY_MAZE_DOOR);
    lvl_constant(MODEL_UNKNOWN_DOOR_21);
    lvl_constant(MODEL_CASTLE_DOOR_0_STARS);
    lvl_constant(MODEL_CASTLE_DOOR_1_STAR);
    lvl_constant(MODEL_CASTLE_DOOR_3_STARS);
    lvl_constant(MODEL_CASTLE_KEY_DOOR);
    lvl_constant(MODEL_CASTLE_CASTLE_DOOR);
    lvl_constant(MODEL_CASTLE_GROUNDS_CASTLE_DOOR);
    lvl_constant(MODEL_CASTLE_WOODEN_DOOR);
    lvl_constant(MODEL_COURTYARD_WOODEN_DOOR);
    lvl_constant(MODEL_CCM_CABIN_DOOR);
    lvl_constant(MODEL_UNKNOWN_DOOR_28);
    lvl_constant(MODEL_CASTLE_METAL_DOOR);
    lvl_constant(MODEL_CASTLE_GROUNDS_METAL_DOOR);
    lvl_constant(MODEL_UNKNOWN_DOOR_2A);
    lvl_constant(MODEL_UNKNOWN_DOOR_2B);
    lvl_constant(MODEL_WF_TOWER_TRAPEZOID_PLATORM);
    lvl_constant(MODEL_WF_TOWER_SQUARE_PLATORM);
    lvl_constant(MODEL_WF_TOWER_SQUARE_PLATORM_UNUSED);
    lvl_constant(MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR);
    lvl_constant(MODEL_BBH_STAIRCASE_STEP);
    lvl_constant(MODEL_BBH_TILTING_FLOOR_PLATFORM);
    lvl_constant(MODEL_BBH_TUMBLING_PLATFORM);
    lvl_constant(MODEL_BBH_TUMBLING_PLATFORM_PART);
    lvl_constant(MODEL_BBH_MOVING_BOOKSHELF);
    lvl_constant(MODEL_BBH_MESH_ELEVATOR);
    lvl_constant(MODEL_BBH_MERRY_GO_ROUND);
    lvl_constant(MODEL_BBH_WOODEN_TOMB);
    lvl_constant(MODEL_CCM_ROPEWAY_LIFT);
    lvl_constant(MODEL_CCM_SNOWMAN_HEAD);
    lvl_constant(MODEL_CASTLE_BOWSER_TRAP);
    lvl_constant(MODEL_CASTLE_WATER_LEVEL_PILLAR);
    lvl_constant(MODEL_CASTLE_CLOCK_MINUTE_HAND);
    lvl_constant(MODEL_CASTLE_CLOCK_HOUR_HAND);
    lvl_constant(MODEL_CASTLE_CLOCK_PENDULUM);
    lvl_constant(MODEL_HMC_METAL_PLATFORM);
    lvl_constant(MODEL_HMC_METAL_ARROW_PLATFORM);
    lvl_constant(MODEL_HMC_ELEVATOR_PLATFORM);
    lvl_constant(MODEL_HMC_ROLLING_ROCK);
    lvl_constant(MODEL_HMC_ROCK_PIECE);
    lvl_constant(MODEL_HMC_ROCK_SMALL_PIECE);
    lvl_constant(MODEL_HMC_RED_GRILLS);
    lvl_constant(MODEL_SSL_PYRAMID_TOP);
    lvl_constant(MODEL_SSL_GRINDEL);
    lvl_constant(MODEL_SSL_SPINDEL);
    lvl_constant(MODEL_SSL_MOVING_PYRAMID_WALL);
    lvl_constant(MODEL_SSL_PYRAMID_ELEVATOR);
    lvl_constant(MODEL_BOB_CHAIN_CHOMP_GATE);
    lvl_constant(MODEL_BOB_SEESAW_PLATFORM);
    lvl_constant(MODEL_BOB_BARS_GRILLS);
    lvl_constant(MODEL_SL_SNOW_TRIANGLE);
    lvl_constant(MODEL_SL_CRACKED_ICE);
    lvl_constant(MODEL_SL_CRACKED_ICE_CHUNK);
    lvl_constant(MODEL_WDW_SQUARE_FLOATING_PLATFORM);
    lvl_constant(MODEL_WDW_ARROW_LIFT);
    lvl_constant(MODEL_WDW_WATER_LEVEL_DIAMOND);
    lvl_constant(MODEL_WDW_HIDDEN_PLATFORM);
    lvl_constant(MODEL_WDW_EXPRESS_ELEVATOR);
    lvl_constant(MODEL_WDW_RECTANGULAR_FLOATING_PLATFORM);
    lvl_constant(MODEL_WDW_ROTATING_PLATFORM);
    lvl_constant(MODEL_JRB_SHIP_LEFT_HALF_PART);
    lvl_constant(MODEL_JRB_SHIP_BACK_LEFT_PART);
    lvl_constant(MODEL_JRB_SHIP_RIGHT_HALF_PART);
    lvl_constant(MODEL_JRB_SHIP_BACK_RIGHT_PART);
    lvl_constant(MODEL_JRB_SUNKEN_SHIP);
    lvl_constant(MODEL_JRB_SUNKEN_SHIP_BACK);
    lvl_constant(MODEL_JRB_ROCK);
    lvl_constant(MODEL_JRB_SLIDING_BOX);
    lvl_constant(MODEL_JRB_FALLING_PILLAR);
    lvl_constant(MODEL_JRB_FALLING_PILLAR_BASE);
    lvl_constant(MODEL_JRB_FLOATING_PLATFORM);
    lvl_constant(MODEL_THI_HUGE_ISLAND_TOP);
    lvl_constant(MODEL_THI_TINY_ISLAND_TOP);
    lvl_constant(MODEL_TTC_ROTATING_CUBE);
    lvl_constant(MODEL_TTC_ROTATING_PRISM);
    lvl_constant(MODEL_TTC_PENDULUM);
    lvl_constant(MODEL_TTC_LARGE_TREADMILL);
    lvl_constant(MODEL_TTC_SMALL_TREADMILL);
    lvl_constant(MODEL_TTC_PUSH_BLOCK);
    lvl_constant(MODEL_TTC_ROTATING_HEXAGON);
    lvl_constant(MODEL_TTC_ROTATING_TRIANGLE);
    lvl_constant(MODEL_TTC_PIT_BLOCK);
    lvl_constant(MODEL_TTC_PIT_BLOCK_UNUSED);
    lvl_constant(MODEL_TTC_ELEVATOR_PLATFORM);
    lvl_constant(MODEL_TTC_CLOCK_HAND);
    lvl_constant(MODEL_TTC_SPINNER);
    lvl_constant(MODEL_TTC_SMALL_GEAR);
    lvl_constant(MODEL_TTC_LARGE_GEAR);
    lvl_constant(MODEL_RR_SLIDING_PLATFORM);
    lvl_constant(MODEL_RR_FLYING_CARPET);
    lvl_constant(MODEL_RR_OCTAGONAL_PLATFORM);
    lvl_constant(MODEL_RR_ROTATING_BRIDGE_PLATFORM);
    lvl_constant(MODEL_RR_TRIANGLE_PLATFORM);
    lvl_constant(MODEL_RR_CRUISER_WING);
    lvl_constant(MODEL_RR_SEESAW_PLATFORM);
    lvl_constant(MODEL_RR_L_SHAPED_PLATFORM);
    lvl_constant(MODEL_RR_SWINGING_PLATFORM);
    lvl_constant(MODEL_RR_DONUT_PLATFORM);
    lvl_constant(MODEL_RR_ELEVATOR_PLATFORM);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME1);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME2);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME3);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME4);
    lvl_constant(MODEL_BITDW_SQUARE_PLATFORM);
    lvl_constant(MODEL_BITDW_SEESAW_PLATFORM);
    lvl_constant(MODEL_BITDW_SLIDING_PLATFORM);
    lvl_constant(MODEL_BITDW_FERRIS_WHEEL_AXLE);
    lvl_constant(MODEL_BITDW_BLUE_PLATFORM);
    lvl_constant(MODEL_BITDW_STAIRCASE_FRAME4);
    lvl_constant(MODEL_BITDW_STAIRCASE_FRAME3);
    lvl_constant(MODEL_BITDW_STAIRCASE_FRAME2);
    lvl_constant(MODEL_BITDW_STAIRCASE_FRAME1);
    lvl_constant(MODEL_BITDW_STAIRCASE);
    lvl_constant(MODEL_VCUTM_SEESAW_PLATFORM);
    lvl_constant(MODEL_VCUTM_CHECKERBOARD_PLATFORM_SPAWNER);
    lvl_constant(MODEL_BITFS_PLATFORM_ON_TRACK);
    lvl_constant(MODEL_BITFS_TILTING_SQUARE_PLATFORM);
    lvl_constant(MODEL_BITFS_SINKING_PLATFORMS);
    lvl_constant(MODEL_BITFS_BLUE_POLE);
    lvl_constant(MODEL_BITFS_SINKING_CAGE_PLATFORM);
    lvl_constant(MODEL_BITFS_ELEVATOR);
    lvl_constant(MODEL_BITFS_STRETCHING_PLATFORMS);
    lvl_constant(MODEL_BITFS_SEESAW_PLATFORM);
    lvl_constant(MODEL_BITFS_MOVING_SQUARE_PLATFORM);
    lvl_constant(MODEL_BITFS_SLIDING_PLATFORM);
    lvl_constant(MODEL_BITFS_TUMBLING_PLATFORM_PART);
    lvl_constant(MODEL_BITFS_TUMBLING_PLATFORM);
    lvl_constant(MODEL_BITS_SLIDING_PLATFORM);
    lvl_constant(MODEL_BITS_TWIN_SLIDING_PLATFORMS);
    lvl_constant(MODEL_BITS_OCTAGONAL_PLATFORM);
    lvl_constant(MODEL_BITS_BLUE_PLATFORM);
    lvl_constant(MODEL_BITS_FERRIS_WHEEL_AXLE);
    lvl_constant(MODEL_BITS_ARROW_PLATFORM);
    lvl_constant(MODEL_BITS_SEESAW_PLATFORM);
    lvl_constant(MODEL_BITS_TILTING_W_PLATFORM);
    lvl_constant(MODEL_BITS_STAIRCASE);
    lvl_constant(MODEL_BITS_STAIRCASE_FRAME1);
    lvl_constant(MODEL_BITS_STAIRCASE_FRAME2);
    lvl_constant(MODEL_BITS_STAIRCASE_FRAME3);
    lvl_constant(MODEL_BITS_STAIRCASE_FRAME4);
    lvl_constant(MODEL_BITS_WARP_PIPE);
    lvl_constant(MODEL_LLL_DRAWBRIDGE_PART);
    lvl_constant(MODEL_LLL_ROTATING_BLOCK_FIRE_BARS);
    lvl_constant(MODEL_LLL_ROTATING_HEXAGONAL_RING);
    lvl_constant(MODEL_LLL_SINKING_RECTANGULAR_PLATFORM);
    lvl_constant(MODEL_LLL_SINKING_SQUARE_PLATFORMS);
    lvl_constant(MODEL_LLL_TILTING_SQUARE_PLATFORM);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_1);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_2);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_3);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_4);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_5);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_6);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_7);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_8);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_9);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_10);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_11);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_12);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_13);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_14);
    lvl_constant(MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM);
    lvl_constant(MODEL_LLL_SINKING_ROCK_BLOCK);
    lvl_constant(MODEL_LLL_ROLLING_LOG);
    lvl_constant(MODEL_LLL_WOOD_BRIDGE);
    lvl_constant(MODEL_LLL_LARGE_WOOD_BRIDGE);
    lvl_constant(MODEL_LLL_FALLING_PLATFORM);
    lvl_constant(MODEL_LLL_LARGE_FALLING_PLATFORM);
    lvl_constant(MODEL_LLL_VOLCANO_FALLING_TRAP);
    lvl_constant(MODEL_DDD_BOWSER_SUB_DOOR);
    lvl_constant(MODEL_DDD_BOWSER_SUB);
    lvl_constant(MODEL_DDD_POLE);
    lvl_constant(MODEL_WF_BREAKABLE_WALL_RIGHT);
    lvl_constant(MODEL_WF_BREAKABLE_WALL_LEFT);
    lvl_constant(MODEL_WF_KICKABLE_BOARD);
    lvl_constant(MODEL_WF_TOWER_DOOR);
    lvl_constant(MODEL_WF_KICKABLE_BOARD_FELLED);
    lvl_constant(MODEL_CASTLE_GROUNDS_VCUTM_GRILL);
    lvl_constant(MODEL_CASTLE_GROUNDS_FLAG);
    lvl_constant(MODEL_CASTLE_GROUNDS_CANNON_GRILL);
    lvl_constant(MODEL_BOWSER_2_TILTING_ARENA);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_1);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_2);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_3);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_4);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_5);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_6);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_7);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_8);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_9);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_10);
    lvl_constant(MODEL_TTM_ROLLING_LOG);
    lvl_constant(MODEL_TTM_STAR_CAGE);
    lvl_constant(MODEL_TTM_BLUE_SMILEY);
    lvl_constant(MODEL_TTM_YELLOW_SMILEY);
    lvl_constant(MODEL_TTM_STAR_SMILEY);
    lvl_constant(MODEL_TTM_MOON_SMILEY);
    lvl_constant(MODEL_BULLET_BILL);
    lvl_constant(MODEL_YELLOW_SPHERE);
    lvl_constant(MODEL_HOOT);
    lvl_constant(MODEL_YOSHI_EGG);
    lvl_constant(MODEL_THWOMP);
    lvl_constant(MODEL_HEAVE_HO);
    lvl_constant(MODEL_BLARGG);
    lvl_constant(MODEL_BULLY);
    lvl_constant(MODEL_BULLY_BOSS);
    lvl_constant(MODEL_WATER_BOMB);
    lvl_constant(MODEL_WATER_BOMB_SHADOW);
    lvl_constant(MODEL_KING_BOBOMB);
    lvl_constant(MODEL_MANTA_RAY);
    lvl_constant(MODEL_UNAGI);
    lvl_constant(MODEL_SUSHI);
    lvl_constant(MODEL_DL_WHIRLPOOL);
    lvl_constant(MODEL_CLAM_SHELL);
    lvl_constant(MODEL_POKEY_HEAD);
    lvl_constant(MODEL_POKEY_BODY_PART);
    lvl_constant(MODEL_TWEESTER);
    lvl_constant(MODEL_KLEPTO);
    lvl_constant(MODEL_EYEROK_LEFT_HAND);
    lvl_constant(MODEL_EYEROK_RIGHT_HAND);
    lvl_constant(MODEL_DL_MONTY_MOLE_HOLE);
    lvl_constant(MODEL_MONTY_MOLE);
    lvl_constant(MODEL_UKIKI);
    lvl_constant(MODEL_FWOOSH);
    lvl_constant(MODEL_SPINDRIFT);
    lvl_constant(MODEL_MR_BLIZZARD_HIDDEN);
    lvl_constant(MODEL_MR_BLIZZARD);
    lvl_constant(MODEL_PENGUIN);
    lvl_constant(MODEL_CAP_SWITCH_EXCLAMATION);
    lvl_constant(MODEL_CAP_SWITCH);
    lvl_constant(MODEL_CAP_SWITCH_BASE);
    lvl_constant(MODEL_BOO);
    lvl_constant(MODEL_BETA_BOO_KEY);
    lvl_constant(MODEL_HAUNTED_CHAIR);
    lvl_constant(MODEL_MAD_PIANO);
    lvl_constant(MODEL_BOOKEND_PART);
    lvl_constant(MODEL_BOOKEND);
    lvl_constant(MODEL_HAUNTED_CAGE);
    lvl_constant(MODEL_BIRDS);
    lvl_constant(MODEL_YOSHI);
    lvl_constant(MODEL_ENEMY_LAKITU);
    lvl_constant(MODEL_SPINY_BALL);
    lvl_constant(MODEL_SPINY);
    lvl_constant(MODEL_WIGGLER_HEAD);
    lvl_constant(MODEL_WIGGLER_BODY);
    lvl_constant(MODEL_BUBBA);
    lvl_constant(MODEL_UNKNOWN_54);
    lvl_constant(MODEL_UNKNOWN_58);
    lvl_constant(MODEL_BOWSER);
    lvl_constant(MODEL_BOWSER_BOMB_CHILD_OBJ);
    lvl_constant(MODEL_BOWSER_SMOKE);
    lvl_constant(MODEL_BOWSER_FLAMES);
    lvl_constant(MODEL_BOWSER_WAVE);
    lvl_constant(MODEL_BOWSER2);
    lvl_constant(MODEL_BUB);
    lvl_constant(MODEL_TREASURE_CHEST_BASE);
    lvl_constant(MODEL_TREASURE_CHEST_LID);
    lvl_constant(MODEL_CYAN_FISH);
    lvl_constant(MODEL_WATER_RING);
    lvl_constant(MODEL_SKEETER);
    lvl_constant(MODEL_PIRANHA_PLANT);
    lvl_constant(MODEL_WHOMP);
    lvl_constant(MODEL_KOOPA_WITH_SHELL);
    lvl_constant(MODEL_METALLIC_BALL);
    lvl_constant(MODEL_CHAIN_CHOMP);
    lvl_constant(MODEL_KOOPA_FLAG);
    lvl_constant(MODEL_WOODEN_POST);
    lvl_constant(MODEL_MIPS);
    lvl_constant(MODEL_BOO_CASTLE);
    lvl_constant(MODEL_LAKITU);
    lvl_constant(MODEL_CHILL_BULLY);
    lvl_constant(MODEL_BIG_CHILL_BULLY);
    lvl_constant(MODEL_MONEYBAG);
    lvl_constant(MODEL_SWOOP);
    lvl_constant(MODEL_SCUTTLEBUG);
    lvl_constant(MODEL_MR_I_IRIS);
    lvl_constant(MODEL_MR_I);
    lvl_constant(MODEL_DORRIE);
    lvl_constant(MODEL_YELLOW_COIN);
    lvl_constant(MODEL_YELLOW_COIN_NO_SHADOW);
    lvl_constant(MODEL_BLUE_COIN);
    lvl_constant(MODEL_BLUE_COIN_NO_SHADOW);
    lvl_constant(MODEL_HEART);
    lvl_constant(MODEL_TRANSPARENT_STAR);
    lvl_constant(MODEL_STAR);
    lvl_constant(MODEL_TTM_SLIDE_EXIT_PODIUM);
    lvl_constant(MODEL_WOODEN_SIGNPOST);
    lvl_constant(MODEL_UNKNOWN_7D);
    lvl_constant(MODEL_CANNON_BARREL);
    lvl_constant(MODEL_CANNON_BASE);
    lvl_constant(MODEL_BREAKABLE_BOX);
    lvl_constant(MODEL_BREAKABLE_BOX_SMALL);
    lvl_constant(MODEL_EXCLAMATION_BOX_OUTLINE);
    lvl_constant(MODEL_EXCLAMATION_POINT);
    lvl_constant(MODEL_MARIOS_WINGED_METAL_CAP);
    lvl_constant(MODEL_MARIOS_METAL_CAP);
    lvl_constant(MODEL_MARIOS_WING_CAP);
    lvl_constant(MODEL_MARIOS_CAP);
    lvl_constant(MODEL_EXCLAMATION_BOX);
    lvl_constant(MODEL_DIRT_ANIMATION);
    lvl_constant(MODEL_CARTOON_STAR);
    lvl_constant(MODEL_BLUE_COIN_SWITCH);
    lvl_constant(MODEL_MIST);
    lvl_constant(MODEL_SPARKLES_ANIMATION);
    lvl_constant(MODEL_RED_FLAME);
    lvl_constant(MODEL_BLUE_FLAME);
    lvl_constant(MODEL_BURN_SMOKE);
    lvl_constant(MODEL_SPARKLES);
    lvl_constant(MODEL_SMOKE);
    lvl_constant(MODEL_BURN_SMOKE_UNUSED);
    lvl_constant(MODEL_WHITE_PARTICLE_DL);
    lvl_constant(MODEL_SAND_DUST);
    lvl_constant(MODEL_WHITE_PARTICLE);
    lvl_constant(MODEL_PEBBLE);
    lvl_constant(MODEL_LEAVES);
    lvl_constant(MODEL_WAVE_TRAIL);
    lvl_constant(MODEL_WHITE_PARTICLE_SMALL);
    lvl_constant(MODEL_SMALL_WATER_SPLASH);
    lvl_constant(MODEL_IDLE_WATER_WAVE);
    lvl_constant(MODEL_WATER_SPLASH);
    lvl_constant(MODEL_BUBBLE);
    lvl_constant(MODEL_PURPLE_MARBLE);
    lvl_constant(MODEL_UNKNOWN_AC);
    lvl_constant(MODEL_WF_SLIDING_PLATFORM);
    lvl_constant(MODEL_WF_SMALL_BOMP);
    lvl_constant(MODEL_WF_ROTATING_WOODEN_PLATFORM);
    lvl_constant(MODEL_WF_TUMBLING_BRIDGE_PART);
    lvl_constant(MODEL_WF_LARGE_BOMP);
    lvl_constant(MODEL_WF_TUMBLING_BRIDGE);
    lvl_constant(MODEL_BOWSER_BOMB);
    lvl_constant(MODEL_WATER_MINE);
    lvl_constant(MODEL_BOWLING_BALL);
    lvl_constant(MODEL_TRAMPOLINE);
    lvl_constant(MODEL_TRAMPOLINE_CENTER);
    lvl_constant(MODEL_TRAMPOLINE_BASE);
    lvl_constant(MODEL_UNKNOWN_B8);
    lvl_constant(MODEL_FISH);
    lvl_constant(MODEL_FISH_SHADOW);
    lvl_constant(MODEL_BUTTERFLY);
    lvl_constant(MODEL_BLACK_BOBOMB);
    lvl_constant(MODEL_KOOPA_SHELL);
    lvl_constant(MODEL_KOOPA_WITHOUT_SHELL);
    lvl_constant(MODEL_GOOMBA);
    lvl_constant(MODEL_SEAWEED);
    lvl_constant(MODEL_AMP);
    lvl_constant(MODEL_BOBOMB_BUDDY);
    lvl_constant(MODEL_SSL_TOX_BOX);
    lvl_constant(MODEL_BOWSER_KEY_CUTSCENE);
    lvl_constant(MODEL_DL_CANNON_LID);
    lvl_constant(MODEL_CHECKERBOARD_PLATFORM);
    lvl_constant(MODEL_RED_FLAME_SHADOW);
    lvl_constant(MODEL_BOWSER_KEY);
    lvl_constant(MODEL_EXPLOSION);
    lvl_constant(MODEL_SNUFIT);
    lvl_constant(MODEL_PURPLE_SWITCH);
    lvl_constant(MODEL_CASTLE_STAR_DOOR_30_STARS);
    lvl_constant(MODEL_CASTLE_STAR_DOOR_50_STARS);
    lvl_constant(MODEL_CCM_SNOWMAN_BASE);
    lvl_constant(MODEL_1UP);
    lvl_constant(MODEL_CASTLE_STAR_DOOR_8_STARS);
    lvl_constant(MODEL_CASTLE_STAR_DOOR_70_STARS);
    lvl_constant(MODEL_RED_COIN);
    lvl_constant(MODEL_RED_COIN_NO_SHADOW);
    lvl_constant(MODEL_METAL_BOX);
    lvl_constant(MODEL_METAL_BOX_DL);
    lvl_constant(MODEL_NUMBER);
    lvl_constant(MODEL_FLYGUY);
    lvl_constant(MODEL_TOAD);
    lvl_constant(MODEL_PEACH);
    lvl_constant(MODEL_CHUCKYA);
    lvl_constant(MODEL_WHITE_PUFF);
    lvl_constant(MODEL_TRAJECTORY_MARKER_BALL);
    lvl_constant(MODEL_MAIN_MENU_MARIO_SAVE_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_RED_ERASE_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_BLUE_COPY_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_YELLOW_FILE_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_GREEN_SCORE_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_MARIO_SAVE_BUTTON_FADE);
    lvl_constant(MODEL_MAIN_MENU_MARIO_NEW_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_MARIO_NEW_BUTTON_FADE);
    lvl_constant(MODEL_MAIN_MENU_PURPLE_SOUND_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_GENERIC_BUTTON);
    lvl_constant(MODEL_LLL_ROTATING_HEXAGONAL_PLATFORM);
    lvl_constant(MODEL_WF_GIANT_POLE);
    lvl_constant(MODEL_WF_ROTATING_PLATFORM);
    lvl_constant(MODEL_BITDW_WARP_PIPE);
    lvl_constant(MODEL_THI_WARP_PIPE);
    lvl_constant(MODEL_VCUTM_WARP_PIPE);
    lvl_constant(MODEL_CASTLE_GROUNDS_WARP_PIPE);
    lvl_constant(MODEL_BUBBLE_PLAYER);
    lvl_constant(MODEL_LUIGI);
    lvl_constant(MODEL_LUIGIS_CAP);
    lvl_constant(MODEL_LUIGIS_METAL_CAP);
    lvl_constant(MODEL_LUIGIS_WING_CAP);
    lvl_constant(MODEL_LUIGIS_WINGED_METAL_CAP);
    lvl_constant(MODEL_TOAD_PLAYER);
    lvl_constant(MODEL_TOADS_CAP);
    lvl_constant(MODEL_TOADS_METAL_CAP);
    lvl_constant(MODEL_TOADS_WING_CAP);
    lvl_constant(MODEL_WALUIGI);
    lvl_constant(MODEL_WALUIGIS_CAP);
    lvl_constant(MODEL_WALUIGIS_METAL_CAP);
    lvl_constant(MODEL_WALUIGIS_WING_CAP);
    lvl_constant(MODEL_WALUIGIS_WINGED_METAL_CAP);
    lvl_constant(MODEL_WARIO);
    lvl_constant(MODEL_WARIOS_CAP);
    lvl_constant(MODEL_WARIOS_METAL_CAP);
    lvl_constant(MODEL_WARIOS_WING_CAP);
    lvl_constant(MODEL_WARIOS_WINGED_METAL_CAP);
    lvl_constant(MODEL_ERROR_MODEL);

    // OP constants
    lvl_constant(OP_AND);
    lvl_constant(OP_NAND);
    lvl_constant(OP_EQ);
    lvl_constant(OP_NEQ);
    lvl_constant(OP_LT);
    lvl_constant(OP_LEQ);
    lvl_constant(OP_GT);
    lvl_constant(OP_GEQ);
    lvl_constant(OP_SET);
    lvl_constant(OP_GET);

    // VAR_CURR constants
    lvl_constant(VAR_CURR_SAVE_FILE_NUM);
    lvl_constant(VAR_CURR_COURSE_NUM);
    lvl_constant(VAR_CURR_ACT_NUM);
    lvl_constant(VAR_CURR_LEVEL_NUM);
    lvl_constant(VAR_CURR_AREA_INDEX);

    // WARP constants
    lvl_constant(WARP_CHECKPOINT);
    lvl_constant(WARP_NO_CHECKPOINT);

    // WHIRLPOOL constants
    lvl_constant(WHIRLPOOL_COND_ALWAYS);
    lvl_constant(WHIRLPOOL_COND_BOWSER2_BEATEN);
    lvl_constant(WHIRLPOOL_COND_AT_LEAST_SECOND_STAR);

    // FACE constants
    lvl_constant(REGULAR_FACE);
    lvl_constant(DIZZY_FACE);

    // Other constants
    lvl_constant(NULL);

    // Integers
    s32 x;
    if ((_Arg[1] == 'x' && sscanf(_Arg.begin(), "%x", &x) == 1) || (sscanf(_Arg.begin(), "%d", &x) == 1)) {
        return (LevelScript) x;
    }

    // Unknown
    PrintError("  ERROR: Unknown lvl arg: %s", _Arg.begin());
    return 0;
}

#define lvl_symbol_0(symb)                       \
    if (_Symbol == #symb) {                      \
        LevelScript _Ls[] = { symb() };          \
        memcpy(aHead, _Ls, sizeof(_Ls));         \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0])); \
        return;                                  \
    }

#define lvl_symbol_1(symb, n)                                                \
    if (_Symbol == #symb) {                                                  \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n != 0) { aGfxData->mPointerList.Add(aHead + n); }               \
        LevelScript _Ls[] = { symb(_Arg0) };                                 \
        memcpy(aHead, _Ls, sizeof(_Ls));                                     \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                             \
        return;                                                              \
    }

#define lvl_symbol_2(symb, n1, n2)                                           \
    if (_Symbol == #symb) {                                                  \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }             \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }             \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1) };                          \
        memcpy(aHead, _Ls, sizeof(_Ls));                                     \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                             \
        return;                                                              \
    }

#define lvl_symbol_3(symb, n1, n2, n3)                                       \
    if (_Symbol == #symb) {                                                  \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }             \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }             \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }             \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2) };                   \
        memcpy(aHead, _Ls, sizeof(_Ls));                                     \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                             \
        return;                                                              \
    }

#define lvl_symbol_4(symb, n1, n2, n3)                                       \
    if (_Symbol == #symb) {                                                  \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }             \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }             \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }             \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3) };            \
        memcpy(aHead, _Ls, sizeof(_Ls));                                     \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                             \
        return;                                                              \
    }

#define lvl_symbol_5(symb, n1, n2, n3)                                       \
    if (_Symbol == #symb) {                                                  \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg4 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }             \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }             \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }             \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4) };     \
        memcpy(aHead, _Ls, sizeof(_Ls));                                     \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                             \
        return;                                                              \
    }

#define lvl_symbol_6(symb, n1, n2, n3)                                          \
    if (_Symbol == #symb) {                                                     \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);    \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);    \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);    \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);    \
        LevelScript _Arg4 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);    \
        LevelScript _Arg5 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);    \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }                \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5) }; \
        memcpy(aHead, _Ls, sizeof(_Ls));                                        \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                \
        return;                                                                 \
    }

#define lvl_symbol_9(symb, n1, n2, n3)                                       \
    if (_Symbol == #symb) {                                                  \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg4 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg5 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg6 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg7 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg8 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }             \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }             \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }             \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5, \
                                   _Arg6, _Arg7, _Arg8) };                   \
        memcpy(aHead, _Ls, sizeof(_Ls));                                     \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                             \
        return;                                                              \
    }

#define lvl_symbol_10(symb, n1, n2, n3)                                      \
    if (_Symbol == #symb) {                                                  \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg4 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg5 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg6 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg7 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg8 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg9 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }             \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }             \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }             \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5, \
                                   _Arg6, _Arg7, _Arg8, _Arg9) };            \
        memcpy(aHead, _Ls, sizeof(_Ls));                                     \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                             \
        return;                                                              \
    }

static void ParseLevelScriptSymbol(GfxData* aGfxData, DataNode<LevelScript>* aNode, LevelScript*& aHead, u64& aTokenIndex, Array<u64>& aSwitchNodes) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    // execution
    lvl_symbol_4(EXECUTE, 1, 2, 3);
    lvl_symbol_4(EXIT_AND_EXECUTE, 1, 2, 3);
    lvl_symbol_0(EXIT);

    // sleep
    lvl_symbol_1(SLEEP, 0);
    lvl_symbol_1(SLEEP_BEFORE_EXIT, 0);

    // jumps
    lvl_symbol_1(JUMP, 1);
    lvl_symbol_1(JUMP_LINK, 1);
    lvl_symbol_0(RETURN);
    lvl_symbol_1(JUMP_LINK_PUSH_ARG, 0);
    lvl_symbol_0(JUMP_N_TIMES);
    lvl_symbol_0(LOOP_BEGIN);
    lvl_symbol_2(LOOP_UNTIL, 0, 0);
    lvl_symbol_3(JUMP_IF, 2, 0, 0);
    lvl_symbol_2(SKIP_IF, 0, 0);
    lvl_symbol_0(SKIP);
    lvl_symbol_0(SKIP_NOP);

    // calls
    lvl_symbol_2(CALL, 1, 0);
    lvl_symbol_2(CALL_LOOP, 1, 0);

    // misc memory
    lvl_symbol_1(SET_REG, 0);
    lvl_symbol_0(PUSH_POOL);
    lvl_symbol_0(POP_POOL);
    lvl_symbol_3(FIXED_LOAD, 1, 2, 3);
    lvl_symbol_3(LOAD_RAW, 1, 2, 0);
    lvl_symbol_3(LOAD_MIO0, 1, 2, 0);
    lvl_symbol_1(LOAD_MARIO_HEAD, 0);
    lvl_symbol_3(LOAD_MIO0_TEXTURE, 1, 2, 0);

    // levels
    lvl_symbol_0(INIT_LEVEL);
    lvl_symbol_0(CLEAR_LEVEL);
    lvl_symbol_0(ALLOC_LEVEL_POOL);
    lvl_symbol_0(FREE_LEVEL_POOL);

    // areas
    lvl_symbol_2(AREA, 1, 0);
    lvl_symbol_0(END_AREA);

    // models
    lvl_symbol_3(LOAD_MODEL_FROM_DL, 1, 0, 0);
    lvl_symbol_2(LOAD_MODEL_FROM_GEO, 1, 0);
    lvl_symbol_3(CMD23, 1, 0, 0);

    // objects
    lvl_symbol_10(OBJECT_WITH_ACTS, 3, 0, 0);
    lvl_symbol_9(OBJECT, 0, 0, 0);
    lvl_symbol_3(MARIO, 2, 0, 0);

    // warps
    lvl_symbol_5(WARP_NODE, 0, 0, 0);
    lvl_symbol_5(PAINTING_WARP_NODE, 0, 0, 0);
    lvl_symbol_5(INSTANT_WARP, 0, 0, 0);

    // misc
    lvl_symbol_1(LOAD_AREA, 0);
    lvl_symbol_1(CMD2A, 0);
    lvl_symbol_5(MARIO_POS, 0, 0, 0);
    lvl_symbol_0(CMD2C);
    lvl_symbol_0(CMD2D);
    lvl_symbol_1(TERRAIN, 1);
    lvl_symbol_1(ROOMS, 1);
    lvl_symbol_2(SHOW_DIALOG, 0, 0);
    lvl_symbol_1(TERRAIN_TYPE, 0);
    lvl_symbol_0(NOP);

    // transitions
    lvl_symbol_5(TRANSITION, 0, 0, 0);
    lvl_symbol_1(BLACKOUT, 0);
    lvl_symbol_1(GAMMA, 0);

    // music
    lvl_symbol_2(SET_BACKGROUND_MUSIC, 0, 0);
    lvl_symbol_1(SET_MENU_MUSIC, 0);
    lvl_symbol_1(STOP_MUSIC, 0);

    // misc
    lvl_symbol_1(MACRO_OBJECTS, 1);
    lvl_symbol_5(CMD3A, 0, 0, 0);
    lvl_symbol_6(WHIRLPOOL, 0, 0, 0);
    lvl_symbol_2(GET_OR_SET, 0, 0);
    lvl_symbol_0(ADV_DEMO);
    lvl_symbol_0(CLEAR_DEMO_PTR);

    // Unknown
    PrintError("  ERROR: Unknown lvl symbol: %s", _Symbol.begin());
}

static DataNode<LevelScript>* ParseLevelScriptData(GfxData* aGfxData, DataNode<LevelScript>* aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // Level script data
    aNode->mData = New<LevelScript>(aNode->mTokens.Count() * LEVEL_SCRIPT_SIZE_PER_TOKEN);
    LevelScript* _Head = aNode->mData;
    Array<u64> _SwitchNodes;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseLevelScriptSymbol(aGfxData, aNode, _Head, _TokenIndex, _SwitchNodes);
        if (aDisplayPercent && aGfxData->mErrorCount == 0) { PrintNoNewLine("%3d%%\b\b\b\b", (s32) (_TokenIndex * 100) / aNode->mTokens.Count()); }
    }
    if (aDisplayPercent && aGfxData->mErrorCount == 0) { Print("100%%"); }
    aNode->mSize = (u32)(_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

static DataNode<LevelScript> *GetLevelScript(GfxData *aGfxData, const String& aGeoRoot) {
    for (DataNode<LevelScript> *_Node : aGfxData->mLevelScripts) {
        if (_Node->mName == aGeoRoot) {
            return _Node;
        }
    }
    return NULL;
}

bool DynOS_Lvl_GeneratePack_Internal(const SysPath &aPackFolder, Array<Pair<u64, String>> _ActorsFolders, GfxData *_GfxData) {
    bool generated = false;
    for (auto &_LvlNode : _GfxData->mLevelScripts) {
        String _LvlRootName = _LvlNode->mName;
        DataNode<LevelScript> *_LvlRoot = GetLevelScript(_GfxData, _LvlRootName);
        if (_LvlRoot == NULL) { continue; }

        // If there is an existing binary file for this level, skip and go to the next level
        SysPath _LvlFilename = fstring("%s/%s.lvl", aPackFolder.c_str(), _LvlRootName.begin());
        if (fs_sys_file_exists(_LvlFilename.c_str())) {
            continue;
        }

        // Init
        _GfxData->mErrorCount = 0;
        _GfxData->mLoadIndex = 0;

        // Parse data
        PrintNoNewLine("%s.lvl: Model identifier: %X - Processing... ", _LvlRootName.begin(), _GfxData->mModelIdentifier);
        ParseLevelScriptData(_GfxData, _LvlRoot, true);

        // Write if no error
        if (_GfxData->mErrorCount == 0) {
            //DynOS_Lvl_WriteBinary(_LvlFilename, _GfxData, _LvlRoot);
        } else {
            Print("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }

        // Clear data pointers
        ClearLvlDataNodes(_GfxData->mLevelScripts);
        generated = true;
    }
    return generated;
}
