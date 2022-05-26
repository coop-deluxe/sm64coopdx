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
#include "levels/jrb/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_jrb_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _jrb_segment_7SegmentRomStart, _jrb_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _bits_skybox_mio0SegmentRomStart, _bits_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, jrb_area_1),
		WARP_NODE(0x0A, LEVEL_WF, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF3, LEVEL_CASTLE, 0x01, 0x20, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x01, 0x26, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE, 0x01, 0x23, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, 1900, -6380, 0, 0, 0, (0x01 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 0, 1900, 6380, 0, -180, 0, (0x02 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 0, 1000, 0, 0, -90, 0, (0x00 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 0, 700, 0, 0, 90, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1300, 0, 0, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 1300, 0, 0, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1500, 4160, 0, -180, 0, (0x05 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1500, -4160, 0, 0, 0, (0x05 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -3190, 1900, 6370, 0, 90, 0, (0x04 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 3190, 1900, 6370, 0, -90, 0, (0x03 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 3190, 1900, -6380, 0, -90, 0, (0x04 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -3190, 1900, -6380, 0, 90, 0, (0x03 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1400, -7400, 0, -180, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1400, 7400, 0, 0, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1800, -4760, 0, 0, 0, (0x01 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1800, 4760, 0, -180, 0, (0x01 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 3700, 800, -8200, 0, 0, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -3700, 800, -8200, 0, 0, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 3700, 800, 8200, 0, -180, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -3700, 800, 8200, 0, -180, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 1700, 1200, -4660, 0, -180, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1700, 1200, -4660, 0, -180, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1700, 1200, 4660, 0, 0, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 1700, 1200, 4660, 0, 0, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 510, 0, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 1700, 6380, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 1700, -6380, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -3200, 1700, -6380, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 510, 0, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 750, -7900, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 750, 7900, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 680, 4880, 0, -180, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 680, -4880, 0, 0, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -1340, 1700, -6380, 0, 90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 1340, 1700, -6380, 0, -90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -1340, 1700, 6380, 0, 90, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 1340, 1700, 6380, 0, -90, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 1020, -5350, 0, 0, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 1020, 5350, 0, -180, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2180, 570, -6300, 0, 90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2180, 570, -6300, 0, -90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2180, 570, 6300, 0, -90, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2180, 570, 6300, 0, 90, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 1100, 750, -7900, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -1100, 750, -7900, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -1100, 750, 7900, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 1100, 750, 7900, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2180, 420, 4770, 0, -90, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2180, 420, 4770, 0, 90, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2180, 420, -4770, 0, 90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2180, 420, -4770, 0, -90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 1279, 0, 0, 0, 0, (10 << 16), bhvAirborneWarp),
		TERRAIN(jrb_area_1_collision),
		MACRO_OBJECTS(jrb_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
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
