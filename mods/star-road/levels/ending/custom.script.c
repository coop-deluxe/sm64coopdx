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
#include "levels/ending/header.h"
extern u8 _ending_segment_ESegmentRomStart[]; 
extern u8 _ending_segment_ESegmentRomEnd[];
#include "levels/castle_grounds/header.h"
const LevelScript level_ending_entry[] = {
INIT_LEVEL(),
LOAD_MIO0(0x07, _castle_grounds_segment_7SegmentRomStart, _castle_grounds_segment_7SegmentRomEnd),
LOAD_MIO0_TEXTURE(/*seg*/ 0x09, _outside_mio0SegmentRomStart, _outside_mio0SegmentRomEnd),
LOAD_RAW(0x1A, _castle_groundsSegmentRomStart, _castle_groundsSegmentRomEnd),
LOAD_RAW(0x0E, _ending_segment_ESegmentRomStart, _ending_segment_ESegmentRomEnd),
LOAD_MIO0(0xA,_SkyboxCustom38895296_skybox_mio0SegmentRomStart,_SkyboxCustom38895296_skybox_mio0SegmentRomEnd),
LOAD_MIO0(8,_common0_mio0SegmentRomStart,_common0_mio0SegmentRomEnd),
LOAD_RAW(15,_common0_geoSegmentRomStart,_common0_geoSegmentRomEnd),
LOAD_MIO0(5,_group10_mio0SegmentRomStart,_group10_mio0SegmentRomEnd),
LOAD_RAW(12,_group10_geoSegmentRomStart,_group10_geoSegmentRomEnd),
LOAD_MIO0(6,_group15_mio0SegmentRomStart,_group15_mio0SegmentRomEnd),
LOAD_RAW(13,_group15_geoSegmentRomStart,_group15_geoSegmentRomEnd),
ALLOC_LEVEL_POOL(),
MARIO(/*model*/ MODEL_MARIO, /*behParam*/ 0x00000001, /*beh*/ bhvMario),
LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03,           castle_grounds_geo_0006F4),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_BUBBLY_TREE,  bubbly_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_WARP_PIPE,    warp_pipe_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CASTLE_DOOR,  castle_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_METAL_DOOR,   metal_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_VCUTM_GRILL,  castle_grounds_geo_00070C),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_FLAG,         castle_grounds_geo_000660),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CANNON_GRILL, castle_grounds_geo_000724),
LOAD_MODEL_FROM_GEO(22, warp_pipe_geo),
LOAD_MODEL_FROM_GEO(23, bubbly_tree_geo),
LOAD_MODEL_FROM_GEO(24, spiky_tree_geo),
LOAD_MODEL_FROM_GEO(25, snow_tree_geo),
LOAD_MODEL_FROM_GEO(31, metal_door_geo),
LOAD_MODEL_FROM_GEO(32, hazy_maze_door_geo),
LOAD_MODEL_FROM_GEO(34, castle_door_0_star_geo),
LOAD_MODEL_FROM_GEO(35, castle_door_1_star_geo),
LOAD_MODEL_FROM_GEO(36, castle_door_3_stars_geo),
LOAD_MODEL_FROM_GEO(37, key_door_geo),
LOAD_MODEL_FROM_GEO(38, castle_door_geo),
LOAD_MODEL_FROM_GEO(41, metal_door_geo),
// LOAD_MODEL_FROM_DL(132,0x08025f08,4),
// LOAD_MODEL_FROM_DL(158,0x0302c8a0,4),
// LOAD_MODEL_FROM_DL(159,0x0302bcd0,4),
// LOAD_MODEL_FROM_DL(161,0x0301cb00,4),
// LOAD_MODEL_FROM_DL(164,0x04032a18,4),
// LOAD_MODEL_FROM_DL(201,0x080048e0,4),
// LOAD_MODEL_FROM_DL(218,0x08024bb8,4),
JUMP_LINK(script_func_global_1),
JUMP_LINK(script_func_global_11),
JUMP_LINK(script_func_global_16),
JUMP_LINK(local_area_ending_1_),
FREE_LEVEL_POOL(),
MARIO_POS(1,135,-7280,2505,2810),
CALL(/*arg*/ 0, /*func*/ lvl_init_or_update),
CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
CLEAR_LEVEL(),
SLEEP_BEFORE_EXIT(/*frames*/ 1),
EXIT(),
};
const LevelScript local_area_ending_1_[] = {
AREA(1,Geo_ending_1_0x2461700),
TERRAIN(col_ending_1_0xe079bc0),
SET_BACKGROUND_MUSIC(0,26),
TERRAIN_TYPE(0),
JUMP_LINK(local_objects_ending_1_),
JUMP_LINK(local_warps_ending_1_),
END_AREA(),
RETURN()
};
const LevelScript local_objects_ending_1_[] = {
OBJECT_WITH_ACTS(0,-7280,2505,2810,0,135,0,0xa0000, bhvAirborneWarp,31),
OBJECT_WITH_ACTS(122,-3905,-8,5196,0,0,0,0x1000000, bhvStar,31),
OBJECT_WITH_ACTS(222,-7211,1724,2328,0,0,0,0x68000000, bhvSMSRPeachMessage,31),
OBJECT_WITH_ACTS(23,-3947,-321,7052,0,107,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,5176,-671,5835,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,-4578,-721,-2854,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,-4450,-721,-3869,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,-2997,-391,2653,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,-7763,-34,-4935,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,-7042,1435,1742,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,-7949,741,-431,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,-4766,-486,1804,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,-2291,-321,5226,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,6013,-661,-5737,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(212,3775,2709,-1399,0,0,0,0x0, bhv1Up,31),
OBJECT_WITH_ACTS(128,7020,940,-1396,0,0,0,0x7f0000, bhvCannon,31),
OBJECT_WITH_ACTS(124,-6856,1724,3050,0,225,0,0x4e0000, bhvMessagePanel,31),
OBJECT_WITH_ACTS(23,-2574,-721,-211,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(23,-1895,-627,-4255,0,0,0,0x0, bhvTree,31),
OBJECT_WITH_ACTS(221,-2201,-721,-1393,0,270,0,0x27000000, bhvToadMessage,31),
OBJECT_WITH_ACTS(221,-7903,382,-2542,0,28,0,0x24000000, bhvToadMessage,31),
OBJECT_WITH_ACTS(221,-3554,-321,3103,0,232,0,0x28000000, bhvToadMessage,31),
OBJECT_WITH_ACTS(221,5001,-671,6235,0,270,0,0x2a000000, bhvToadMessage,31),
OBJECT_WITH_ACTS(124,4828,-672,5913,0,248,0,0x4d0000, bhvMessagePanel,31),
OBJECT_WITH_ACTS(100,-7070,836,5495,0,110,0,0x2b0000, bhvSMSRMipsMessage,31),
OBJECT_WITH_ACTS(0,-7203,1979,2761,0,90,0,0xf10000, bhvDeathWarp,31),
RETURN()
};
const LevelScript local_warps_ending_1_[] = {
WARP_NODE(10,9,1,10,0),
WARP_NODE(11,9,1,12,0),
WARP_NODE(12,9,1,11,0),
WARP_NODE(13,9,1,14,0),
WARP_NODE(14,9,1,13,0),
WARP_NODE(240,16,1,9,0),
WARP_NODE(241,25,1,241,0),
WARP_NODE(0,9,1,10,0),
WARP_NODE(1,9,1,10,0),
WARP_NODE(2,9,1,10,0),
WARP_NODE(3,9,1,10,0),
WARP_NODE(80,9,1,10,0),
WARP_NODE(61,16,1,60,0),
WARP_NODE(242,31,1,10,0),
RETURN()
};
