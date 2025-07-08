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

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_sl_entry[] = {
    INIT_LEVEL(),
    ALLOC_LEVEL_POOL(),
    MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
    /* Fast64 begin persistent block [level commands] */
    /* Fast64 end persistent block [level commands] */

    AREA(1, mirror_room_area_1),
        WARP_NODE(0x0A, LEVEL_SL, 0x01, 0x0A, WARP_NO_CHECKPOINT),
        WARP_NODE(0xF0, LEVEL_CASTLE, 0x02, 0x36, WARP_NO_CHECKPOINT),
        WARP_NODE(0xF1, LEVEL_CASTLE, 0x02, 0x68, WARP_NO_CHECKPOINT),
        MARIO_POS(0x01, 0, 0, 0, 0),
        OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x0A << 16), bhvSpinAirborneWarp),

        // Mirrors
        OBJECT(MODEL_NONE, 813, 920, 1480, 0, 270, 0, ((((7760 / 10) & 0x7FF) << 21) | (((1860 / 10) & 0x7FF) << 10) | (((2700 / 10) & 0x3FF) << 0)), bhvHorizontalMirror),
        OBJECT(MODEL_NONE, 813, 920, 1480, 0, 180, 0, ((((5400 / 10) & 0x7FF) << 21) | (((1860 / 10) & 0x7FF) << 10) | (((3880 / 10) & 0x3FF) << 0)), bhvHorizontalMirror),
        OBJECT(MODEL_NONE, 813, 920, 1480, 0, 0, 0, ((((5400 / 10) & 0x7FF) << 21) | (((7760 / 10) & 0x7FF) << 10) | (((930 / 10) & 0x3FF) << 0)), bhvVerticalMirror),

        TERRAIN(mirror_room_area_1_collision),
        SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_INSIDE_CASTLE),
        TERRAIN_TYPE(TERRAIN_GRASS),
        /* Fast64 begin persistent block [area commands] */
        /* Fast64 end persistent block [area commands] */
    END_AREA(),

    AREA(2, mirror_room_area_2),
        WARP_NODE(0x0A, LEVEL_SL, 0x02, 0x0A, WARP_NO_CHECKPOINT),
        WARP_NODE(0xF0, LEVEL_CASTLE, 0x02, 0x36, WARP_NO_CHECKPOINT),
        WARP_NODE(0xF1, LEVEL_CASTLE, 0x02, 0x68, WARP_NO_CHECKPOINT),
        MARIO_POS(0x01, 0, 0, 0, 0),
        OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x0A << 16), bhvSpinAirborneWarp),

        // Mirrors
        OBJECT(MODEL_NONE, -813, -5, 1480, 0, 90, 0, ((((7760 / 10) & 0x7FF) << 21) | (((1860 / 10) & 0x7FF) << 10) | (((2700 / 10) & 0x3FF) << 0)), bhvHorizontalMirror),
        OBJECT(MODEL_NONE, -813, -5, 1480, 0, 180, 0, ((((5400 / 10) & 0x7FF) << 21) | (((1860 / 10) & 0x7FF) << 10) | (((3880 / 10) & 0x3FF) << 0)), bhvHorizontalMirror),
        OBJECT(MODEL_NONE, -813, -5, 1480, 0, 0, 0, ((((5400 / 10) & 0x7FF) << 21) | (((7760 / 10) & 0x7FF) << 10) | (((930 / 10) & 0x3FF) << 0)), bhvVerticalMirror),

        TERRAIN(mirror_room_area_2_collision),
        SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_INSIDE_CASTLE),
        TERRAIN_TYPE(TERRAIN_GRASS),
        /* Fast64 begin persistent block [area commands] */
        /* Fast64 end persistent block [area commands] */
    END_AREA(),

    FREE_LEVEL_POOL(),
    MARIO_POS(0x01, 0, 0, 0, 0),
    CALL(0, lvl_init_or_update),
    CALL_LOOP(1, lvl_init_or_update),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(1),
    EXIT(),
};