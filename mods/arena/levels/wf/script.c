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
#include "levels/wf/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_wf_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _wf_segment_7SegmentRomStart, _wf_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _wdw_skybox_mio0SegmentRomStart, _wdw_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, wf_area_1),
		WARP_NODE(0x0A, LEVEL_WF, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF3, LEVEL_CASTLE, 0x01, 0x20, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x01, 0x26, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE, 0x01, 0x23, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, 1400, -7000, 0, 0, 0, (0x01 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 0, 1400, 7000, 0, -180, 0, (0x02 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 0, 500, 0, 0, -90, 0, (0x00 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 5100, 1400, 0, 0, 90, 0, (0x01 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -5100, 1400, 0, 0, -90, 0, (0x01 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -5100, 1700, -3000, 0, -90, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -5100, 1700, -7055, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 5100, 1700, -7100, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 5100, 1700, -3000, 0, -90, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 5100, 1700, 7046, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 5100, 1700, 3000, 0, -90, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -5100, 1700, 7046, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -3500, 900, 3000, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1000, 9300, 0, 0, 0, (0x05 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1000, -9300, 0, -180, 0, (0x05 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1900, 200, -9300, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 1900, 200, -9300, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 1900, 200, 9300, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1900, 200, 9300, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1800, 7500, 0, -180, 0, (0x03 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1800, -7500, 0, 0, 0, (0x03 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1400, -5100, 0, 0, 0, (0x04 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 1400, 5100, 0, -180, 0, (0x04 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -5100, 1700, 3000, 0, -90, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -3500, 900, -3000, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 3500, 900, 3000, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 3500, 900, -3000, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 2700, 500, 0, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -2700, 500, 0, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 200, 0, 0, -180, 0, (0x05 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 0, 733, 9300, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 733, -9300, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 5100, 1183, 0, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -5100, 1183, 0, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 1183, 5100, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 1183, -5100, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -3500, 733, -3000, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 3500, 733, -3000, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -3500, 733, 3000, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 3500, 733, 3000, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, -17, 0, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 1595, -7500, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 0, 1633, 7500, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -700, 583, 8000, 0, -45, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 700, 583, 8000, 0, 45, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 800, 133, 9300, 0, 90, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -900, 133, 9300, 0, -90, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 1400, 133, 5500, 0, 135, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -1400, 133, 5500, 0, -135, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2200, -17, 2200, 0, -135, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2200, -17, 2200, 0, 135, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -4800, 1183, 2700, 0, 135, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 4800, 1183, 2700, 0, -135, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 583, 5900, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 583, 4300, 0, -180, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 583, -4300, 0, 0, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 583, -5900, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -4800, 1183, -2700, 0, 45, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 4800, 1183, -2700, 0, -45, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2200, -17, -2200, 0, -45, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -2200, -17, -2200, 0, 45, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 1400, 133, -5500, 0, 45, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -1400, 133, -5500, 0, -45, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 800, 133, -9300, 0, 90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -800, 133, -9300, 0, -90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -700, 583, -8000, 0, -135, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 700, 583, -8000, 0, 135, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 600, 0, 0, 0, 0, (10 << 16), bhvAirborneWarp),
		TERRAIN(wf_area_1_collision),
		MACRO_OBJECTS(wf_area_1_macro_objs),
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
