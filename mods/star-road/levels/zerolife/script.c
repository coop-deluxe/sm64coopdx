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
#include "levels/zerolife/header.h"
const LevelScript level_zerolife_entry[] = {
INIT_LEVEL(),
LOAD_MIO0(0x07, _zerolife_segment_7SegmentRomStart, _zerolife_segment_7SegmentRomEnd),
LOAD_MIO0(8,_common0_mio0SegmentRomStart,_common0_mio0SegmentRomEnd),
LOAD_RAW(15,_common0_geoSegmentRomStart,_common0_geoSegmentRomEnd),
LOAD_MIO0(5,_group9_mio0SegmentRomStart,_group9_mio0SegmentRomEnd),
LOAD_RAW(12,_group9_geoSegmentRomStart,_group9_geoSegmentRomEnd),
LOAD_MIO0(6,_group17_mio0SegmentRomStart,_group17_mio0SegmentRomEnd),
LOAD_RAW(13,_group17_geoSegmentRomStart,_group17_geoSegmentRomEnd),
ALLOC_LEVEL_POOL(),
MARIO(/*model*/ MODEL_MARIO, /*behParam*/ 0x00000001, /*beh*/ bhvMario),
JUMP_LINK(script_func_global_1),
JUMP_LINK(script_func_global_10),
JUMP_LINK(script_func_global_18),
JUMP_LINK(local_area_zerolife_1_),
FREE_LEVEL_POOL(),
MARIO_POS(1,135,-4728,-3125,5),
CALL(/*arg*/ 0, /*func*/ lvl_init_or_update),
CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
CLEAR_LEVEL(),
SLEEP_BEFORE_EXIT(/*frames*/ 1),
EXIT(),
};
const LevelScript local_area_zerolife_1_[] = {
AREA(1,Geo_zerolife_1_0x2701700),
TERRAIN(col_zerolife_1_0xe061700),
SET_BACKGROUND_MUSIC(0,48),
TERRAIN_TYPE(3),
JUMP_LINK(local_objects_zerolife_1_),
JUMP_LINK(local_warps_zerolife_1_),
END_AREA(),
RETURN()
};
const LevelScript local_objects_zerolife_1_[] = {
OBJECT_WITH_ACTS(0,-4728,-3125,5,0,135,0,0xa0000, bhvAirborneDeathWarp,31),
OBJECT_WITH_ACTS(MODEL_BOO,-2703,-3563,1506,0,209,0,0x10000, bhvBoo,31),
OBJECT_WITH_ACTS(MODEL_BOO,2516,-3333,1167,0,292,0,0x20000, bhvBoo,31),
OBJECT_WITH_ACTS(MODEL_BOO,2700,-3177,-570,0,347,0,0x30000, bhvBoo,31),
OBJECT_WITH_ACTS(MODEL_BOO,2227,-2544,3333,0,223,0,0x40000, bhvBoo,31),
OBJECT_WITH_ACTS(MODEL_BOO,-2455,-3559,1090,0,264,0,0x50000, bhvBoo,31),
OBJECT_WITH_ACTS(0,2818,-4022,-1652,0,0,0,0x60f00000, bhvWarp,31),
RETURN()
};
const LevelScript local_warps_zerolife_1_[] = {
WARP_NODE(10,9,1,10,0),
WARP_NODE(11,9,1,12,0),
WARP_NODE(12,9,1,11,0),
WARP_NODE(13,9,1,14,0),
WARP_NODE(14,9,1,13,0),
WARP_NODE(240,16,1,128,0),
WARP_NODE(241,16,1,128,0),
WARP_NODE(0,9,1,10,0),
WARP_NODE(1,9,1,10,0),
WARP_NODE(2,9,1,10,0),
WARP_NODE(3,9,1,10,0),
WARP_NODE(4,9,1,10,0),
WARP_NODE(5,9,1,10,0),
WARP_NODE(6,9,1,10,0),
RETURN()
};
