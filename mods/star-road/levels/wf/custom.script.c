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
#include "levels/wf/header.h"
extern u8 _wf_segment_ESegmentRomStart[]; 
extern u8 _wf_segment_ESegmentRomEnd[];
#include "levels/bob/header.h"
const LevelScript level_wf_entry[] = {
INIT_LEVEL(),
LOAD_MIO0(0x07, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd),
LOAD_MIO0_TEXTURE(/*seg*/ 0x09, _generic_mio0SegmentRomStart, _generic_mio0SegmentRomEnd),
LOAD_RAW(0x1A, _bobSegmentRomStart, _bobSegmentRomEnd),
LOAD_RAW(0x0E, _wf_segment_ESegmentRomStart, _wf_segment_ESegmentRomEnd),
LOAD_MIO0(0xA,_cloud_floor_skybox_mio0SegmentRomStart,_cloud_floor_skybox_mio0SegmentRomEnd),
LOAD_MIO0(8,_common0_mio0SegmentRomStart,_common0_mio0SegmentRomEnd),
LOAD_RAW(15,_common0_geoSegmentRomStart,_common0_geoSegmentRomEnd),
LOAD_MIO0(5,_group11_mio0SegmentRomStart,_group11_mio0SegmentRomEnd),
LOAD_RAW(12,_group11_geoSegmentRomStart,_group11_geoSegmentRomEnd),
LOAD_MIO0(6,_group14_mio0SegmentRomStart,_group14_mio0SegmentRomEnd),
LOAD_RAW(13,_group14_geoSegmentRomStart,_group14_geoSegmentRomEnd),
ALLOC_LEVEL_POOL(),
MARIO(/*model*/ MODEL_MARIO, /*behParam*/ 0x00000001, /*beh*/ bhvMario),
LOAD_MODEL_FROM_GEO(MODEL_BOB_BUBBLY_TREE,      bubbly_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOB_CHAIN_CHOMP_GATE, bob_geo_000440),
    LOAD_MODEL_FROM_GEO(MODEL_BOB_SEESAW_PLATFORM,  bob_geo_000458),
    LOAD_MODEL_FROM_GEO(MODEL_BOB_BARS_GRILLS,      bob_geo_000470),
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
JUMP_LINK(script_func_global_15),
JUMP_LINK(local_area_wf_1_),
FREE_LEVEL_POOL(),
MARIO_POS(1,90,367,-930,-710),
CALL(/*arg*/ 0, /*func*/ lvl_init_or_update),
CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
CLEAR_LEVEL(),
SLEEP_BEFORE_EXIT(/*frames*/ 1),
EXIT(),
};
const LevelScript local_area_wf_1_[] = {
AREA(1,Geo_wf_1_0x2381700),
TERRAIN(col_wf_1_0xe037a58),
SET_BACKGROUND_MUSIC(0,19),
TERRAIN_TYPE(0),
JUMP_LINK(local_objects_wf_1_),
JUMP_LINK(local_warps_wf_1_),
END_AREA(),
RETURN()
};
const LevelScript local_objects_wf_1_[] = {
OBJECT_WITH_ACTS(0,367,-930,-710,0,90,0,0xa0000, bhvSpinAirborneWarp,63),
OBJECT_WITH_ACTS(137,-3530,-697,-2143,0,0,0,0x20000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(116,-4346,-2720,-2872,0,0,0,0x0, bhvOneCoin,63),
OBJECT_WITH_ACTS(103,563,2455,-2192,0,90,0,0x0, bhvWhompKingBoss,1),
OBJECT_WITH_ACTS(0,3032,-1040,2298,0,0,0,0x0, bhvCheckerboardElevatorGroup,63),
OBJECT_WITH_ACTS(0,2174,1565,-2678,0,180,0,0x0, bhvCheckerboardElevatorGroup,63),
OBJECT_WITH_ACTS(0,6924,259,-5231,0,270,0,0x0, bhvOpenableGrill,63),
OBJECT_WITH_ACTS(207,7461,1876,-1755,0,270,0,0x0, bhvFloorSwitchGrills,63),
OBJECT_WITH_ACTS(23,6241,-183,6794,0,0,0,0x0, bhvTree,63),
OBJECT_WITH_ACTS(137,7721,1782,5030,0,0,0,0x20b0000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(122,-3838,-2290,-4926,0,0,0,0x5000000, bhvStar,63),
OBJECT_WITH_ACTS(0,4897,210,4945,0,0,0,0x4000000, bhvHiddenRedCoinStar,63),
OBJECT_WITH_ACTS(122,7440,572,-5228,0,270,0,0x3000000, bhvStar,63),
OBJECT_WITH_ACTS(122,4258,2820,4853,0,0,0,0x1000000, bhvStar,63),
OBJECT_WITH_ACTS(129,5420,1502,5364,0,0,0,0x0, bhvHiddenObject,63),
OBJECT_WITH_ACTS(129,4431,1877,5389,0,0,0,0x0, bhvHiddenObject,63),
OBJECT_WITH_ACTS(207,4804,1670,3759,0,0,0,0x0, bhvFloorSwitchHiddenObjects,63),
OBJECT_WITH_ACTS(215,-1992,-957,-4493,0,0,0,0x0, bhvRedCoin,63),
OBJECT_WITH_ACTS(215,-2649,252,3014,0,0,0,0x0, bhvRedCoin,63),
OBJECT_WITH_ACTS(215,4253,731,5098,0,0,0,0x0, bhvRedCoin,63),
OBJECT_WITH_ACTS(215,7483,2994,-6600,0,0,0,0x0, bhvRedCoin,255),
OBJECT_WITH_ACTS(215,314,-960,-1859,0,0,0,0x0, bhvRedCoin,63),
OBJECT_WITH_ACTS(215,-1067,2346,-2255,0,0,0,0x0, bhvRedCoin,63),
OBJECT_WITH_ACTS(215,-5466,-895,-5635,0,0,0,0x0, bhvRedCoin,63),
OBJECT_WITH_ACTS(215,-1842,89,-7223,0,0,0,0x0, bhvRedCoin,63),
OBJECT_WITH_ACTS(140,6712,259,-5776,0,0,0,0x0, bhvBlueCoinSwitch,63),
OBJECT_WITH_ACTS(118,5195,259,-5664,0,0,0,0x0, bhvHiddenBlueCoin,63),
OBJECT_WITH_ACTS(118,3839,259,-5664,0,0,0,0x0, bhvHiddenBlueCoin,63),
OBJECT_WITH_ACTS(118,3115,575,-5664,0,0,0,0x0, bhvHiddenBlueCoin,63),
OBJECT_WITH_ACTS(118,1217,259,-5664,0,0,0,0x0, bhvHiddenBlueCoin,63),
OBJECT_WITH_ACTS(0,-2782,-2907,-3043,0,145,0,0x0, bhvCoinFormation,63),
OBJECT_WITH_ACTS(194,-3538,-2878,-4377,0,0,0,0x0, bhvHomingAmp,63),
OBJECT_WITH_ACTS(116,-4186,-2851,-2555,0,0,0,0x0, bhvOneCoin,63),
OBJECT_WITH_ACTS(0,-3261,-1665,-3279,0,0,0,0x0, bhvFish2,63),
OBJECT_WITH_ACTS(23,1358,-2159,-1652,0,0,0,0x0, bhvTree,63),
OBJECT_WITH_ACTS(0,-1703,-51,1987,0,120,0,0x0, bhvCoinFormation,63),
OBJECT_WITH_ACTS(0,-5239,-796,-4920,0,0,0,0x0, bhvCoinFormation,63),
OBJECT_WITH_ACTS(84,661,2455,-2224,0,0,0,0x0, bhvEnemyLakitu,62),
OBJECT_WITH_ACTS(116,-271,2768,-2704,0,0,0,0x0, bhvOneCoin,62),
OBJECT_WITH_ACTS(116,1216,2768,-2686,0,0,0,0x0, bhvOneCoin,62),
OBJECT_WITH_ACTS(116,474,2768,-1401,0,0,0,0x0, bhvOneCoin,62),
OBJECT_WITH_ACTS(187,2861,-2159,3424,0,0,0,0x0, bhvButterfly,63),
OBJECT_WITH_ACTS(0,3552,1752,-6480,0,90,0,0x0, bhvCoinFormation,63),
OBJECT_WITH_ACTS(0,4671,1361,5040,0,90,0,0x0, bhvCoinFormation,63),
OBJECT_WITH_ACTS(84,7179,2624,-6157,0,0,0,0x0, bhvEnemyLakitu,63),
OBJECT_WITH_ACTS(192,-2492,-957,1132,0,0,0,0x0, bhvGoomba,63),
OBJECT_WITH_ACTS(100,-4775,-965,-1844,0,90,0,0x0, bhvPiranhaPlant,63),
OBJECT_WITH_ACTS(100,6128,259,-4898,0,180,0,0x0, bhvPiranhaPlant,63),
OBJECT_WITH_ACTS(100,2607,-2159,4071,0,180,0,0x0, bhvPiranhaPlant,63),
OBJECT_WITH_ACTS(192,1448,-2159,2216,0,0,0,0x0, bhvGoomba,63),
OBJECT_WITH_ACTS(220,4339,522,2359,0,0,0,0x0, bhvFlyGuy,63),
OBJECT_WITH_ACTS(220,-1035,-488,2944,0,0,0,0x0, bhvFlyGuy,63),
OBJECT_WITH_ACTS(23,-1113,-957,3700,0,0,0,0x0, bhvTree,63),
OBJECT_WITH_ACTS(0,-1108,-957,3895,270,0,0,0x130000, bhvCoinFormation,63),
OBJECT_WITH_ACTS(192,1170,-2159,-755,0,0,0,0x0, bhvGoomba,63),
OBJECT_WITH_ACTS(23,2929,-1639,1143,0,0,0,0x0, bhvTree,63),
OBJECT_WITH_ACTS(0,-2095,-34,-5174,0,0,0,0x0, bhvCoinFormation,63),
OBJECT_WITH_ACTS(192,-4601,-105,-5696,0,0,0,0x0, bhvGoomba,63),
OBJECT_WITH_ACTS(220,-882,676,-5762,0,0,0,0x0, bhvFlyGuy,45),
OBJECT_WITH_ACTS(192,4031,375,-723,0,0,0,0x0, bhvGoomba,63),
OBJECT_WITH_ACTS(192,-4666,-539,-3784,0,0,0,0x0, bhvGoomba,63),
OBJECT_WITH_ACTS(220,6237,337,6746,0,0,0,0x0, bhvFlyGuy,63),
OBJECT_WITH_ACTS(0,3470,1223,-2613,0,90,0,0x0, bhvCoinFormation,63),
OBJECT_WITH_ACTS(23,-2702,-957,1918,0,0,0,0x0, bhvTree,63),
OBJECT_WITH_ACTS(23,5059,375,-696,0,0,0,0x0, bhvTree,63),
OBJECT_WITH_ACTS(23,-4986,-105,-5549,0,0,0,0x0, bhvTree,63),
OBJECT_WITH_ACTS(116,943,-1799,4359,0,0,0,0x0, bhvOneCoin,63),
OBJECT_WITH_ACTS(187,-4884,-957,-2274,0,0,0,0x0, bhvButterfly,63),
OBJECT_WITH_ACTS(187,-1707,-957,3332,0,0,0,0x0, bhvButterfly,63),
OBJECT_WITH_ACTS(187,1884,259,-5695,0,0,0,0x0, bhvButterfly,63),
OBJECT_WITH_ACTS(187,4231,1223,-2641,0,0,0,0x0, bhvButterfly,63),
OBJECT_WITH_ACTS(0,5067,888,-720,0,0,0,0x0, bhvHidden1upInPoleSpawner,63),
OBJECT_WITH_ACTS(195,656,-2158,-1134,0,0,0,0xa70000, bhvBobombBuddy,1),
OBJECT_WITH_ACTS(103,4202,-155,4226,0,0,0,0x0, bhvSmallWhomp,22),
OBJECT_WITH_ACTS(103,1180,259,-5698,0,90,0,0x0, bhvSmallWhomp,26),
OBJECT_WITH_ACTS(103,496,2455,-2224,0,0,0,0x0, bhvSmallWhomp,30),
OBJECT_WITH_ACTS(195,-2006,-991,2589,0,90,0,0xa60000, bhvBobombBuddy,62),
OBJECT_WITH_ACTS(195,-907,2456,-3062,0,270,0,0xa50000, bhvBobombBuddy,32),
OBJECT_WITH_ACTS(195,-3919,-539,-3811,0,90,0,0xa00000, bhvBobombBuddy,62),
OBJECT_WITH_ACTS(195,656,-2158,-1134,0,0,0,0x9f0000, bhvBobombBuddy,62),
OBJECT_WITH_ACTS(137,3561,688,-640,0,0,0,0x40000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,3561,1104,-640,0,0,0,0x50000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(23,4711,-155,1970,0,0,0,0x0, bhvTree,63),
OBJECT_WITH_ACTS(187,4823,-155,2480,0,0,0,0x0, bhvButterfly,63),
OBJECT_WITH_ACTS(137,7353,471,6379,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7249,471,6275,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7353,471,6275,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7249,471,6379,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7251,731,5858,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7355,731,5963,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7355,731,5858,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7251,731,5963,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7657,992,5859,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7761,992,5963,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7761,992,5859,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(137,7657,992,5963,0,0,0,0x10000, bhvExclamationBox,63),
OBJECT_WITH_ACTS(0,-4347,-2696,-2831,0,0,0,0xd0000, bhvFadingWarp,63),
OBJECT_WITH_ACTS(0,-5342,-99,-1267,0,180,0,0xe0000, bhvFadingWarp,63),
OBJECT_WITH_ACTS(129,4231,2077,5389,0,0,0,0x0, bhvHiddenObject,63),
OBJECT_WITH_ACTS(129,5420,1302,5164,0,0,0,0x0, bhvHiddenObject,63),
RETURN()
};
const LevelScript local_warps_wf_1_[] = {
WARP_NODE(10,9,1,10,0),
WARP_NODE(11,9,1,12,0),
WARP_NODE(12,9,1,11,0),
WARP_NODE(13,24,1,14,0),
WARP_NODE(14,24,1,13,0),
WARP_NODE(240,16,1,36,0),
WARP_NODE(241,16,1,37,0),
WARP_NODE(0,9,1,10,0),
WARP_NODE(1,9,1,10,0),
WARP_NODE(2,9,1,10,0),
WARP_NODE(3,9,1,10,0),
WARP_NODE(4,9,1,10,0),
WARP_NODE(5,9,1,10,0),
WARP_NODE(6,9,1,10,0),
RETURN()
};