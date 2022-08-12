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


/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/ddd/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_ddd_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _ddd_segment_7SegmentRomStart, _ddd_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, ddd_area_1),
		WARP_NODE(0x0A, LEVEL_DDD, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF3, LEVEL_CASTLE, 0x01, 0x20, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x01, 0x26, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE, 0x01, 0x23, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, 0, -2700, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 0, 2700, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2700, 0, 0, 0, 90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2700, 0, 0, 0, -90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2000, 0, 2000, 0, -135, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2000, 0, -2000, 0, 45, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2000, 0, 2000, 0, 135, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2000, 0, -2000, 0, -45, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2500, 0, -1100, 0, -67, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2500, 0, 1100, 0, 113, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -1100, 0, -2500, 0, 23, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 1100, 0, 2500, 0, -157, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2500, 0, 1100, 0, -112, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2500, 0, -1100, 0, 68, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -1100, 0, 2500, 0, 158, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 1100, 0, -2500, 0, -22, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -3900, 800, 0, 0, 90, 0, (0x01 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 3900, 800, 0, 0, -90, 0, (0x02 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 3675, 400, -1350, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 3675, 400, 1350, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -3675, 400, -1350, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -3675, 400, 1350, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 400, 0, 0, 90, 0, (0x00 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, -1700, 0, 0, 0, 90, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 1700, 0, 0, 0, -90, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 0, -1700, 0, 0, 0, (0x03 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 0, 1700, 0, -180, 0, (0x03 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 1300, 0, 1300, 0, -135, 0, (0x05 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1300, 0, -1300, 0, 45, 0, (0x05 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 1300, 0, -1300, 0, -45, 0, (0x04 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1300, 0, 1300, 0, 135, 0, (0x04 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 600, 0, 0, 90, 0, (0x01 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 3900, 586, 0, 0, -90, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -3900, 586, 0, 0, 90, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 145, 0, 0, -90, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 1596, 0, 0, 0, 0, (10 << 16), bhvAirborneWarp),
		TERRAIN(ddd_area_1_collision),
		MACRO_OBJECTS(ddd_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_UNDERGROUND),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(1, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
