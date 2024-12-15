#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"
#include "game/level_update.h"
#include "levels/scripts.h"
#include "actors/common1.h"
#include "make_const_nonconst.h"

#include "areas/1/custom.model.inc.h"
#include "levels/ssl/header.h"
extern u8 _ssl_segment_ESegmentRomStart[]; 
extern u8 _ssl_segment_ESegmentRomEnd[];
#include "levels/ttm/header.h"

const LevelScript level_ssl_entry[] = {
    INIT_LEVEL(),
    LOAD_MIO0(0x07, _ttm_segment_7SegmentRomStart, _ttm_segment_7SegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x09, _mountain_mio0SegmentRomStart, _mountain_mio0SegmentRomEnd),
    LOAD_RAW(0x1A, _ttmSegmentRomStart, _ttmSegmentRomEnd),
    LOAD_RAW(0x0E, _ssl_segment_ESegmentRomStart, _ssl_segment_ESegmentRomEnd),
    LOAD_MIO0(0xA,_SkyboxCustom23297728_skybox_mio0SegmentRomStart,_SkyboxCustom23297728_skybox_mio0SegmentRomEnd),
    LOAD_MIO0(8,_common0_mio0SegmentRomStart,_common0_mio0SegmentRomEnd),
    LOAD_RAW(15,_common0_geoSegmentRomStart,_common0_geoSegmentRomEnd),
    LOAD_MIO0(5,_group11_mio0SegmentRomStart,_group11_mio0SegmentRomEnd),
    LOAD_RAW(12,_group11_geoSegmentRomStart,_group11_geoSegmentRomEnd),
    LOAD_MIO0(6,_group15_mio0SegmentRomStart,_group15_mio0SegmentRomEnd),
    LOAD_RAW(13,_group15_geoSegmentRomStart,_group15_geoSegmentRomEnd),
    ALLOC_LEVEL_POOL(),
    MARIO(/*model*/ MODEL_MARIO, /*behParam*/ 0x00000001, /*beh*/ bhvMario),
    LOAD_MODEL_FROM_GEO(MODEL_TTM_SLIDE_EXIT_PODIUM, ttm_geo_000DF4),
    LOAD_MODEL_FROM_GEO(MODEL_TTM_ROLLING_LOG,       ttm_geo_000730),
    LOAD_MODEL_FROM_GEO(MODEL_TTM_STAR_CAGE,        ttm_geo_000710),
    LOAD_MODEL_FROM_GEO(MODEL_TTM_BLUE_SMILEY,       ttm_geo_000D14),
    LOAD_MODEL_FROM_GEO(MODEL_TTM_YELLOW_SMILEY,     ttm_geo_000D4C),
    LOAD_MODEL_FROM_GEO(MODEL_TTM_STAR_SMILEY,       ttm_geo_000D84),
    LOAD_MODEL_FROM_GEO(MODEL_TTM_MOON_SMILEY,       ttm_geo_000DBC),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03,     ttm_geo_000748),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_04,     ttm_geo_000778),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_05,     ttm_geo_0007A8),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_06,     ttm_geo_0007D8),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_07,     ttm_geo_000808),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_08,     ttm_geo_000830),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_09,     ttm_geo_000858),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0A,     ttm_geo_000880),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0B,     ttm_geo_0008A8),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0C,     ttm_geo_0008D0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0D,     ttm_geo_0008F8),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0F,     ttm_geo_000920),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_10,     ttm_geo_000948),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_11,     ttm_geo_000970),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_12,     ttm_geo_000990),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_13,     ttm_geo_0009C0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_14,     ttm_geo_0009F0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_15,     ttm_geo_000A18),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_16,     ttm_geo_000A40),
    LOAD_MODEL_FROM_GEO(22, warp_pipe_geo),
    LOAD_MODEL_FROM_GEO(23, bubbly_tree_geo),
    LOAD_MODEL_FROM_GEO(24, spiky_tree_geo),
    LOAD_MODEL_FROM_GEO(25, snow_tree_geo),
    LOAD_MODEL_FROM_GEO(31, metal_door_geo),
    LOAD_MODEL_FROM_GEO(32, hazy_maze_door_geo),
    LOAD_MODEL_FROM_GEO(34, castle_door_0_star_geo),
    LOAD_MODEL_FROM_GEO(35, castle_door_1_star_geo),
    LOAD_MODEL_FROM_GEO(36, castle_door_3_star_geo),
    LOAD_MODEL_FROM_GEO(37, key_door_geo),
    LOAD_MODEL_FROM_GEO(38, castle_door_geo),
    // LOAD_MODEL_FROM_GEO(88,0x0500c778),
    // LOAD_MODEL_FROM_DL(132,0x08025f08,4),
    // LOAD_MODEL_FROM_DL(158,0x0302c8a0,4),
    // LOAD_MODEL_FROM_DL(159,0x0302bcd0,4),
    // LOAD_MODEL_FROM_DL(161,0x0301cb00,4),
    // LOAD_MODEL_FROM_DL(164,0x04032a18,4),
    // LOAD_MODEL_FROM_DL(201,0x080048e0,4),
    // LOAD_MODEL_FROM_DL(218,0x08024bb8,4),
    JUMP_LINK(script_func_global_1),
    JUMP_LINK(script_func_global_12),
    JUMP_LINK(script_func_global_16),
    JUMP_LINK(local_area_ssl_1_),
    FREE_LEVEL_POOL(),
    MARIO_POS(1,32,-2081,1019,-5519),
    CALL(/*arg*/ 0, /*func*/ lvl_init_or_update),
    CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    EXIT(),
};

const LevelScript local_area_ssl_1_[] = {
    AREA(1,Geo_ssl_1_0x1581700),
    TERRAIN(col_ssl_1_0xe0205d0),
    SET_BACKGROUND_MUSIC(0,36),
    TERRAIN_TYPE(0),
    JUMP_LINK(local_objects_ssl_1_),
    JUMP_LINK(local_warps_ssl_1_),
    END_AREA(),
    RETURN()
};

const LevelScript local_objects_ssl_1_[] = {
    OBJECT_WITH_ACTS(0,-2081,1019,-5519,0,32,0,0xa0000, bhvSpinAirborneWarp,63),
    OBJECT_WITH_ACTS(5,-20,-21,2392,0,-154,0,0x0, bhvSMSRMovingMushroom,62),
    OBJECT_WITH_ACTS(58,-3144,-537,-4803,0,-153,0,0x0, bhvTree,62),
    OBJECT_WITH_ACTS(58,6219,159,967,0,107,0,0x0, bhvTree,63),
    OBJECT_WITH_ACTS(58,-3475,-759,3825,0,-95,0,0x0, bhvTree,63),
    OBJECT_WITH_ACTS(87,5052,159,770,0,0,0,0x0, bhvSMSRWigglerHead,1),
    OBJECT_WITH_ACTS(207,-2928,-534,-6325,0,265,0,0x0, bhvFloorSwitchHiddenObjects,63),
    OBJECT_WITH_ACTS(122,-43,3914,1846,0,0,0,0x1000000, bhvStar,63),
    OBJECT_WITH_ACTS(188,-1732,-759,1068,0,88,0,0x8c0000, bhvBobombBuddy,127),
    OBJECT_WITH_ACTS(129,4319,-510,-5946,0,45,0,0x0, bhvHiddenObject,63),
    OBJECT_WITH_ACTS(58,-3442,-721,-1913,0,0,0,0x0, bhvTree,63),
    OBJECT_WITH_ACTS(100,-2258,3,-5017,0,180,0,0x950000, bhvSMSRMipsMessage,1),
    OBJECT_WITH_ACTS(122,4314,107,-5949,0,0,0,0x2000000, bhvStar,63),
    OBJECT_WITH_ACTS(122,1190,2580,3105,0,0,0,0x3000000, bhvStar,62),
    OBJECT_WITH_ACTS(0,-3780,-499,1493,0,0,0,0x4000000, bhvHiddenRedCoinStar,63),
    OBJECT_WITH_ACTS(122,459,-4611,2683,0,0,0,0x5000000, bhvStar,63),
    OBJECT_WITH_ACTS(100,3225,159,-47,0,250,0,0x8a0000, bhvSMSRMipsMessage,62),
    OBJECT_WITH_ACTS(100,-2241,-23,-5024,0,180,0,0x8b0000, bhvSMSRMipsMessage,82),
    OBJECT_WITH_ACTS(56,1147,2290,3130,0,0,0,0x0, bhvSMSRYoshiCoin,1),
    OBJECT_WITH_ACTS(215,-1300,2723,1678,0,0,0,0x0, bhvRedCoin,63),
    OBJECT_WITH_ACTS(137,680,-447,3944,0,0,0,0x60000, bhvExclamationBox,63),
    OBJECT_WITH_ACTS(215,1671,3036,3103,0,0,0,0x0, bhvRedCoin,63),
    OBJECT_WITH_ACTS(58,1831,-759,2758,0,0,0,0x0, bhvTree,62),
    OBJECT_WITH_ACTS(57,1434,2161,2511,0,180,0,0x0, bhvSMSRBigLeaves,62),
    OBJECT_WITH_ACTS(57,1046,2004,2241,0,180,0,0x0, bhvSMSRBigLeaves,62),
    OBJECT_WITH_ACTS(0,3592,-1070,-5253,0,0,0,0x0, bhvFish3,63),
    OBJECT_WITH_ACTS(129,24,2230,1230,0,0,0,0x0, bhvJumpingBox,62),
    OBJECT_WITH_ACTS(58,44,-536,-5331,0,0,0,0x10000, bhvTree,63),
    OBJECT_WITH_ACTS(57,-975,2004,1698,0,213,0,0x0, bhvSMSRBigLeaves,63),
    OBJECT_WITH_ACTS(86,-393,879,2716,0,0,0,0x0, bhvSpiny,62),
    OBJECT_WITH_ACTS(58,530,-537,-2536,0,0,0,0x0, bhvTree,63),
    OBJECT_WITH_ACTS(58,-4723,-759,397,0,0,0,0x0, bhvTree,62),
    OBJECT_WITH_ACTS(86,398,871,2116,0,0,0,0x0, bhvSpiny,62),
    OBJECT_WITH_ACTS(57,-1045,697,3263,0,0,0,0x0, bhvSMSRBigLeaves,62),
    OBJECT_WITH_ACTS(58,-5,-759,2,0,0,0,0x0, bhvTree,62),
    OBJECT_WITH_ACTS(58,3396,159,-312,0,0,0,0x0, bhvTree,63),
    OBJECT_WITH_ACTS(0,-1803,-252,-2490,0,325,0,0x0, bhvCoinFormation,63),
    OBJECT_WITH_ACTS(215,-1699,-755,3379,0,0,0,0x0, bhvRedCoin,63),
    OBJECT_WITH_ACTS(0,3995,-1075,-2856,0,0,0,0x0, bhvFish2,63),
    OBJECT_WITH_ACTS(0,-20,-2163,2389,0,0,0,0x20000, bhvCoinFormation,63),
    OBJECT_WITH_ACTS(215,852,-2223,2921,0,0,0,0x0, bhvRedCoin,63),
    OBJECT_WITH_ACTS(137,-814,2923,1930,0,0,0,0x60000, bhvExclamationBox,63),
    OBJECT_WITH_ACTS(129,2271,-775,-418,0,25,0,0x10000, bhvBreakableBox,63),
    OBJECT_WITH_ACTS(215,-1035,697,3298,0,0,0,0x0, bhvRedCoin,63),
    OBJECT_WITH_ACTS(140,323,822,3497,0,0,0,0x0, bhvBlueCoinSwitch,63),
    OBJECT_WITH_ACTS(84,-190,3602,1835,0,0,0,0x0, bhvEnemyLakitu,50),
    OBJECT_WITH_ACTS(56,6721,68,-4868,0,305,0,0x0, bhvSMSRYoshiCoin,63),
    OBJECT_WITH_ACTS(215,6218,1131,958,0,0,0,0x0, bhvRedCoin,63),
    OBJECT_WITH_ACTS(215,-3401,303,-1921,0,0,0,0x0, bhvRedCoin,63),
    OBJECT_WITH_ACTS(215,1878,-1335,1447,0,0,0,0x0, bhvRedCoin,63),
    OBJECT_WITH_ACTS(57,248,1223,2264,0,0,0,0x0, bhvSMSRBigLeaves,63),
    OBJECT_WITH_ACTS(56,-2169,1988,1163,0,0,0,0x0, bhvSMSRYoshiCoin,63),
    OBJECT_WITH_ACTS(56,-5856,-473,-5765,0,0,0,0x0, bhvSMSRYoshiCoin,63),
    OBJECT_WITH_ACTS(56,2302,-363,5332,0,0,0,0x0, bhvSMSRYoshiCoin,63),
    OBJECT_WITH_ACTS(56,3158,-1315,-3506,0,0,0,0x0, bhvSMSRYoshiCoin,63),
    OBJECT_WITH_ACTS(0,-3430,-759,2474,0,0,0,0x0, bhvGoombaTripletSpawner,63),
    OBJECT_WITH_ACTS(0,4871,159,183,0,0,0,0x0, bhvGoombaTripletSpawner,63),
    OBJECT_WITH_ACTS(84,4293,-809,-6208,0,0,0,0x0, bhvEnemyLakitu,13),
    OBJECT_WITH_ACTS(120,2274,-202,158,0,0,0,0x0, bhvRecoveryHeart,63),
    OBJECT_WITH_ACTS(0,6,1952,2302,0,0,0,0x20000, bhvBirdsSoundLoop,63),
    OBJECT_WITH_ACTS(194,5319,161,-1065,0,0,0,0x0, bhvHomingAmp,63),
    OBJECT_WITH_ACTS(0,5328,224,-1285,90,0,0,0x130000, bhvCoinFormation,63),
    OBJECT_WITH_ACTS(0,4772,159,609,0,0,0,0x0, bhvBirdsSoundLoop,63),
    OBJECT_WITH_ACTS(137,-40,1130,1777,0,90,0,0x60000, bhvExclamationBox,63),
    OBJECT_WITH_ACTS(0,-1020,-537,-4008,0,0,0,0x0, bhvGoombaTripletSpawner,63),
    OBJECT_WITH_ACTS(86,1175,2301,3123,0,0,0,0x0, bhvSpiny,8),
    OBJECT_WITH_ACTS(0,-35,822,3571,0,90,0,0x0, bhvBetaFishSplashSpawner,63),
    OBJECT_WITH_ACTS(57,-1575,956,1486,0,0,0,0x0, bhvSMSRBigLeaves,63),
    OBJECT_WITH_ACTS(57,2078,1145,1189,0,0,0,0x0, bhvSMSRBigLeaves,63),
    OBJECT_WITH_ACTS(118,1995,1779,1277,0,0,0,0x0, bhvHiddenBlueCoin,63),
    OBJECT_WITH_ACTS(194,589,-537,-4386,0,0,0,0x0, bhvHomingAmp,63),
    OBJECT_WITH_ACTS(223,-1466,1689,1554,0,52,0,0x0, bhvChuckya,54),
    OBJECT_WITH_ACTS(0,-1337,-758,385,0,0,0,0x110000, bhvCoinFormation,63),
    OBJECT_WITH_ACTS(194,-1360,-734,379,0,0,0,0x0, bhvHomingAmp,63),
    OBJECT_WITH_ACTS(192,1978,-759,3062,0,0,0,0x0, bhvGoomba,63),
    OBJECT_WITH_ACTS(18,4436,-526,-4429,0,32,0,0x0, bhvSMSRLilyPad,63),
    OBJECT_WITH_ACTS(192,-1309,1320,3101,0,0,0,0x0, bhvGoomba,63),
    OBJECT_WITH_ACTS(118,940,1626,2285,0,0,0,0x0, bhvHiddenBlueCoin,63),
    OBJECT_WITH_ACTS(223,1445,1579,1556,0,302,0,0x0, bhvChuckya,62),
    OBJECT_WITH_ACTS(192,539,3275,2727,0,0,0,0x0, bhvGoomba,62),
    OBJECT_WITH_ACTS(118,761,891,3155,0,0,0,0x0, bhvHiddenBlueCoin,63),
    OBJECT_WITH_ACTS(129,-25,233,2375,0,0,0,0x0, bhvHiddenObject,1),
    OBJECT_WITH_ACTS(0,-1591,1035,1496,0,0,0,0x0, bhvHidden1upInPoleSpawner,63),
    OBJECT_WITH_ACTS(18,3178,-526,-3525,0,150,0,0x0, bhvSMSRLilyPad,63),
    RETURN()
};

const LevelScript local_warps_ssl_1_[] = {
    WARP_NODE(10,9,1,10,0),
    WARP_NODE(11,9,1,12,0),
    WARP_NODE(12,9,1,11,0),
    WARP_NODE(13,9,1,14,0),
    WARP_NODE(14,9,1,13,0),
    WARP_NODE(240,26,1,5,0),
    WARP_NODE(241,26,1,6,0),
    WARP_NODE(0,9,1,10,0),
    WARP_NODE(1,9,1,10,0),
    WARP_NODE(2,9,1,10,0),
    WARP_NODE(3,9,1,10,0),
    WARP_NODE(4,9,1,10,0),
    WARP_NODE(5,9,1,10,0),
    WARP_NODE(6,9,1,10,0),
    RETURN()
};