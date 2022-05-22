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
#include "levels/ccm/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_ccm_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _ccm_segment_7SegmentRomStart, _ccm_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _clouds_skybox_mio0SegmentRomStart, _clouds_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario),

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, ccm_area_1),
		WARP_NODE(0x0A, LEVEL_CCM, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF3, LEVEL_CASTLE, 0x01, 0x20, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x01, 0x26, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE, 0x01, 0x23, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 2000, 1800, -5500, 0, 0, 0, (0x01 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 2500, 2500, 0, 0, 90, 0, (0x01 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 5000, 1800, -1500, 0, -180, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 5000, 1800, 1500, 0, 0, 0, (0x02 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 2000, 1800, 5500, 0, -180, 0, (0x02 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, 500, 2100, 0, 0, 0, 0, (0x00 << 24), id_bhvArenaFlag),
		OBJECT(MODEL_NONE, -2400, 1300, -1900, 0, -180, 0, (0x05 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -2400, 1300, 1900, 0, 0, 0, (0x05 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -4200, 700, 4500, 0, 0, 0, (0x04 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -4200, 700, -4500, 0, -180, 0, (0x04 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -5300, 700, -100, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1400, 1400, -1100, 0, -180, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1400, 1400, 1100, 0, 0, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 2400, 800, 2500, 0, 0, 0, (0x03 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 2400, 800, -2500, 0, -180, 0, (0x03 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -100, 1700, -5500, 0, 0, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -100, 1700, 5500, 0, -180, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 2000, 1700, 3400, 0, -180, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1800, 1700, 5500, 0, -180, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -1800, 1700, -5500, 0, 0, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 2000, 1700, -3400, 0, 0, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, -100, 500, 0, 0, 90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 1300, 500, 0, 0, -90, 0, (0x06 << 24), id_bhvArenaItem),
		OBJECT(MODEL_NONE, 2000, 1550, -5500, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 2000, 1550, 5500, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 500, 1900, 0, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 3700, 2100, 0, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -2400, 1500, 0, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -5100, 300, 3700, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -5100, 300, -3700, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -700, 300, -3600, 0, 0, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, -700, 300, 3600, 0, -180, 0, 0x00000000, id_bhvArenaKoth),
		OBJECT(MODEL_NONE, 1400, 1500, 1200, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 1400, 1500, -1200, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 6100, 900, -300, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 6100, 900, 300, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -3000, 900, 1300, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -3000, 900, -1300, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -800, 900, -1300, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -800, 900, 1300, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -5700, 300, -800, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, -5700, 300, 800, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2000, 300, 6200, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2000, 300, -6200, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 3800, 300, 3100, 0, -90, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 3800, 300, -3100, 0, -90, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2000, 300, -4800, 0, 0, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 2000, 300, 4800, 0, -180, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 3100, 300, -1900, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 3100, 300, 1900, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 5100, 1700, 800, 0, 0, 0, (0x02 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 5100, 1700, -800, 0, -180, 0, (0x01 << 24), id_bhvArenaSpawn),
		OBJECT(MODEL_NONE, 0, 2486, 0, 0, 0, 0, (10 << 16), bhvAirborneWarp),
		TERRAIN(ccm_area_1_collision),
		MACRO_OBJECTS(ccm_area_1_macro_objs),
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
