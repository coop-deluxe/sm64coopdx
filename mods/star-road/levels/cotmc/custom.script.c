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
#include "levels/cotmc/header.h"
extern u8 _cotmc_segment_ESegmentRomStart[]; 
extern u8 _cotmc_segment_ESegmentRomEnd[];
#include "levels/ssl/header.h"
const LevelScript level_cotmc_entry[] = {
INIT_LEVEL(),
LOAD_MIO0(0x07, _ssl_segment_7SegmentRomStart, _ssl_segment_7SegmentRomEnd),
LOAD_MIO0_TEXTURE(/*seg*/ 0x09, _generic_mio0SegmentRomStart, _generic_mio0SegmentRomEnd),
LOAD_RAW(0x1A, _sslSegmentRomStart, _sslSegmentRomEnd),
LOAD_RAW(0x0E, _cotmc_segment_ESegmentRomStart, _cotmc_segment_ESegmentRomEnd),
LOAD_MIO0(0xA,_bbh_skybox_mio0SegmentRomStart,_bbh_skybox_mio0SegmentRomEnd),
LOAD_MIO0(8,_common0_mio0SegmentRomStart,_common0_mio0SegmentRomEnd),
LOAD_RAW(15,_common0_geoSegmentRomStart,_common0_geoSegmentRomEnd),
LOAD_MIO0(5,_group8_mio0SegmentRomStart,_group8_mio0SegmentRomEnd),
LOAD_RAW(12,_group8_geoSegmentRomStart,_group8_geoSegmentRomEnd),
LOAD_MIO0(6,_group17_mio0SegmentRomStart,_group17_mio0SegmentRomEnd),
LOAD_RAW(13,_group17_geoSegmentRomStart,_group17_geoSegmentRomEnd),
ALLOC_LEVEL_POOL(),
MARIO(/*model*/ MODEL_MARIO, /*behParam*/ 0x00000001, /*beh*/ bhvMario),
LOAD_MODEL_FROM_GEO(MODEL_SSL_PALM_TREE,           palm_tree_geo),
LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03,       ssl_geo_0005C0),
LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_04,       ssl_geo_0005D8),
LOAD_MODEL_FROM_GEO(MODEL_SSL_PYRAMID_TOP,         ssl_geo_000618),
LOAD_MODEL_FROM_GEO(MODEL_SSL_GRINDEL,             ssl_geo_000734),
LOAD_MODEL_FROM_GEO(MODEL_SSL_SPINDEL,             ssl_geo_000764),
LOAD_MODEL_FROM_GEO(MODEL_SSL_MOVING_PYRAMID_WALL, ssl_geo_000794),
LOAD_MODEL_FROM_GEO(MODEL_SSL_PYRAMID_ELEVATOR,    ssl_geo_0007AC),
LOAD_MODEL_FROM_GEO(MODEL_SSL_TOX_BOX,             ssl_geo_000630),
LOAD_MODEL_FROM_GEO(22, warp_pipe_geo),
LOAD_MODEL_FROM_GEO(27, palm_tree_geo),
// LOAD_MODEL_FROM_DL(84,0x05002e00,4),
// LOAD_MODEL_FROM_DL(86,0x05003120,4),
// LOAD_MODEL_FROM_DL(132,0x08025f08,4),
// LOAD_MODEL_FROM_DL(158,0x0302c8a0,4),
// LOAD_MODEL_FROM_DL(159,0x0302bcd0,4),
// LOAD_MODEL_FROM_DL(161,0x0301cb00,4),
// LOAD_MODEL_FROM_DL(164,0x04032a18,4),
// LOAD_MODEL_FROM_DL(201,0x080048e0,4),
// LOAD_MODEL_FROM_DL(218,0x08024bb8,4),
JUMP_LINK(script_func_global_1),
JUMP_LINK(script_func_global_9),
JUMP_LINK(script_func_global_18),
JUMP_LINK(local_area_cotmc_1_),
FREE_LEVEL_POOL(),
MARIO_POS(1,270,2038,11272,4960),
CALL(/*arg*/ 0, /*func*/ lvl_init_or_update),
CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
CLEAR_LEVEL(),
SLEEP_BEFORE_EXIT(/*frames*/ 1),
EXIT(),
};
const LevelScript local_area_cotmc_1_[] = {
AREA(1,Geo_cotmc_1_0x2701700),
TERRAIN(col_cotmc_1_0xe061700),
SET_BACKGROUND_MUSIC(0,44),
TERRAIN_TYPE(3),
JUMP_LINK(local_objects_cotmc_1_),
JUMP_LINK(local_warps_cotmc_1_),
END_AREA(),
RETURN()
};
const LevelScript local_objects_cotmc_1_[] = {
OBJECT_WITH_ACTS(0,2038,11272,4960,0,270,0,0xa0000, bhvFlyingWarp,31),
OBJECT_WITH_ACTS(206,2210,5430,-1046,0,0,0,0x0, bhvSnufit,31),
OBJECT_WITH_ACTS(206,-1011,5113,710,0,-153,0,0x0, bhvSnufit,31),
OBJECT_WITH_ACTS(122,1625,11249,4976,0,270,0,0x4000000, bhvSMSRStarReplica,31),
OBJECT_WITH_ACTS(85,4191,5321,-294,0,270,0,0x10000, bhvCapSwitch,31),
OBJECT_WITH_ACTS(180,-1429,5660,-1906,0,0,0,0x0, bhvFireSpitter,31),
OBJECT_WITH_ACTS(215,-177,6343,-1618,0,0,0,0x0, bhvRedCoin,31),
OBJECT_WITH_ACTS(0,1014,5403,541,0,0,0,0x0, bhvHiddenRedCoinStar,31),
OBJECT_WITH_ACTS(137,2024,4908,-117,0,0,0,0x10000, bhvExclamationBox,31),
OBJECT_WITH_ACTS(215,4938,4675,-322,0,0,0,0x0, bhvRedCoin,31),
OBJECT_WITH_ACTS(0,-1162,9468,4991,0,270,0,0x0, bhvCoinFormation,31),
OBJECT_WITH_ACTS(0,-5771,7049,642,0,340,0,0x0, bhvCoinFormation,31),
OBJECT_WITH_ACTS(215,649,4607,639,0,0,0,0x0, bhvRedCoin,31),
OBJECT_WITH_ACTS(215,4641,5532,145,0,0,0,0x0, bhvRedCoin,95),
OBJECT_WITH_ACTS(215,2172,5094,-2619,0,0,0,0x0, bhvRedCoin,31),
OBJECT_WITH_ACTS(215,4630,5532,-786,0,0,0,0x0, bhvRedCoin,31),
OBJECT_WITH_ACTS(215,-269,5264,-2626,0,0,0,0x0, bhvRedCoin,31),
OBJECT_WITH_ACTS(215,2207,5288,-1539,0,0,0,0x0, bhvRedCoin,31),
OBJECT_WITH_ACTS(0,656,5620,-1202,0,225,0,0x0, bhvCoinFormation,31),
OBJECT_WITH_ACTS(206,-771,5248,-3631,0,0,0,0x0, bhvSnufit,31),
OBJECT_WITH_ACTS(212,-5094,6916,-506,0,0,0,0x0, bhv1Up,31),
RETURN()
};
const LevelScript local_warps_cotmc_1_[] = {
WARP_NODE(10,9,1,10,0),
WARP_NODE(11,9,1,12,0),
WARP_NODE(12,9,1,11,0),
WARP_NODE(13,9,1,14,0),
WARP_NODE(14,9,1,13,0),
WARP_NODE(240,16,1,27,0),
WARP_NODE(241,16,1,28,0),
WARP_NODE(0,9,1,10,0),
WARP_NODE(1,9,1,10,0),
WARP_NODE(2,9,1,10,0),
WARP_NODE(3,9,1,10,0),
WARP_NODE(4,9,1,10,0),
WARP_NODE(5,9,1,10,0),
WARP_NODE(6,9,1,10,0),
RETURN()
};
