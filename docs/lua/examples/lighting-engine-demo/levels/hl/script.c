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
#include "levels/hl/header.h"

const LevelScript level_hl_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _hl_segment_7SegmentRomStart, _hl_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario),

	AREA(1, hl_area_1),
		WARP_NODE(0x0A, 50, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, 51, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, 50, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01, 50, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, 50, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x64 << 24) | (0x64 << 16) | (0x78 << 8) | (0x00), bhvAmbientLight),
		OBJECT(MODEL_NONE, 1296, -527, -592, 0, 0, 0, 0x000A0000, bhvInstantActiveWarp),
		MARIO_POS(0x01, 0, 1296, -527, -592),
		OBJECT(MODEL_NONE, -111, -287, -1006, 0, 0, 0, (0x32 << 24) | (0x32 << 16) | (0x46 << 8) | (0x64), bhvPointLight),
		OBJECT(MODEL_NONE, -111, -287, -183, 0, 0, 0, (0x32 << 24) | (0x32 << 16) | (0x46 << 8) | (0x64), bhvPointLight),
		OBJECT(MODEL_NONE, -111, -287, -618, 0, 0, 0, (0x32 << 24) | (0x32 << 16) | (0x46 << 8) | (0x64), bhvPointLight),
		OBJECT(MODEL_NONE, -111, -287, -618, 0, 0, 0, (0x46 << 24) | (0x50 << 16) | (0x64 << 8) | (0x64), bhvPointLight),
		TERRAIN(hl_area_1_collision),
		MACRO_OBJECTS(hl_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_SOUND_PLAYER),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 1296, -527, -592),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
