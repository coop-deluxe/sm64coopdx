#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/area.h"
#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/ending/header.h"

const LevelScript level_ending_entry[] = {
    CALL(/*arg*/ LEVEL_ENDING, /*func*/ lvl_set_current_level),
    INIT_LEVEL(),
    LOAD_MIO0(/*seg*/ 0x07, _ending_segment_7SegmentRomStart, _ending_segment_7SegmentRomEnd),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, ending_geo_000050),
    END_AREA(),

    FREE_LEVEL_POOL(),
    SLEEP(/*frames*/ 60),
    BLACKOUT(/*active*/ FALSE),
    LOAD_AREA(/*area*/ 1),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_COLOR, /*time*/ 75, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 120),
    CALL(/*arg*/ 0, /*func*/ lvl_play_the_end_screen_sound),
    // L1:
    // SLEEP(/*frames*/ 1),
    // JUMP(level_ending_entry + 17),
    SLEEP_BEFORE_EXIT(/*frames*/ 30 * 10),
    CALL(/*arg*/ 0, /*func*/ lvl_exiting_credits),
    CLEAR_LEVEL(),
    EXIT(),
};
