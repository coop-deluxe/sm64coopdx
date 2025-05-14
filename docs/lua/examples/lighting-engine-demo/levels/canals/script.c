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

#include "make_const_nonconst.h"
#include "levels/canals/header.h"

const LevelScript level_canals_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _canals_segment_7SegmentRomStart, _canals_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario),

	AREA(1, canals_area_1),
		WARP_NODE(0x0A, 51, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, 51, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, 51, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF2, LEVEL_CASTLE_GROUNDS, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -2378, 250, -457, 0, 0, 0, (0xEB << 24) | (0x9B << 16) | (0x47 << 8) | (0x00), bhvAmbientLight),
		OBJECT(MODEL_NONE, -8000, 140, -4400, 0, 180, 0, 0x000A0000, bhvInstantActiveWarp),
		MARIO_POS(0x01, 180, -8000, 140, -4400),
		OBJECT(MODEL_NONE, -3800, -50, 5899, 0, 0, 0, (0x00 << 24) | (0xF2 << 16) | (0x00 << 8) | (0x00), bhvWarp),
		TERRAIN(canals_area_1_collision),
		MACRO_OBJECTS(canals_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_SOUND_PLAYER),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 180, -8000, 140, -4400),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
