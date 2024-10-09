#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/area.h"
#include "game/level_update.h"
#include "menu/file_select.h"
#include "menu/star_select.h"

#include "levels/scripts.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/menu/header.h"

const LevelScript level_main_menu_entry_1[] = {
    INIT_LEVEL(),
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
    LOAD_MIO0(/*seg*/ 0x07, _menu_segment_7SegmentRomStart, _menu_segment_7SegmentRomEnd),
    LOAD_RAW(/*seg*/ 0x13, _behaviorSegmentRomStart, _behaviorSegmentRomEnd),
    ALLOC_LEVEL_POOL(),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_MARIO_SAVE_BUTTON,      geo_menu_mario_save_button),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_RED_ERASE_BUTTON,       geo_menu_erase_button),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_BLUE_COPY_BUTTON,       geo_menu_copy_button),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_YELLOW_FILE_BUTTON,     geo_menu_file_button),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_GREEN_SCORE_BUTTON,     geo_menu_score_button),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_MARIO_SAVE_BUTTON_FADE, geo_menu_mario_save_button_fade),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_MARIO_NEW_BUTTON,       geo_menu_mario_new_button),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_MARIO_NEW_BUTTON_FADE,  geo_menu_mario_new_button_fade),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_PURPLE_SOUND_BUTTON,    geo_menu_sound_button),
    LOAD_MODEL_FROM_GEO(MODEL_MAIN_MENU_GENERIC_BUTTON,         geo_menu_generic_button),

    AREA(/*index*/ 1, geo_menu_file_select_strings_and_menu_cursor),
        OBJECT(/*model*/ MODEL_NONE,         /*pos*/ 0, 0, -19000, /*angle*/ 0, 0, 0, /*behParam*/ 0x04000000, /*beh*/ bhvMenuButtonManager),
        OBJECT(/*model*/ MODEL_MAIN_MENU_YELLOW_FILE_BUTTON, /*pos*/ 0, 0, -19000, /*angle*/ 0, 0, 0, /*behParam*/ 0x04000000, /*beh*/ bhvYellowBackgroundInMenu),
        TERRAIN(/*terrainData*/ main_menu_seg7_collision),
    END_AREA(),

    FREE_LEVEL_POOL(),
    LOAD_AREA(/*area*/ 1),
    SET_MENU_MUSIC(/*seq*/ 0x0021),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    CALL(/*arg*/ 0, /*func*/ lvl_init_menu_values_and_cursor_pos),
    CALL_LOOP(/*arg*/ 0, /*func*/ lvl_update_obj_and_load_file_selected),
    GET_OR_SET(/*op*/ OP_SET, /*var*/ VAR_CURR_SAVE_FILE_NUM),
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 8), // Was 16 frames
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    SET_REG(/*value*/ LEVEL_CASTLE_GROUNDS),
    EXIT_AND_EXECUTE(/*seg*/ 0x15, _scriptsSegmentRomStart, _scriptsSegmentRomEnd, level_main_scripts_entry),
};

const LevelScript level_main_menu_entry_2[] = {
    CALL(/*arg*/ 0, /*func*/ lvl_set_current_level),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 0, level_main_menu_entry_2 + 42),
    INIT_LEVEL(),
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
    LOAD_MIO0(/*seg*/ 0x07, _menu_segment_7SegmentRomStart, _menu_segment_7SegmentRomEnd),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 2, geo_menu_act_selector_strings),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/ 0, -100, 0, /*angle*/ 0, 0, 0, /*behParam*/ 0x04000000, /*beh*/ bhvActSelector),
        TERRAIN(/*terrainData*/ main_menu_seg7_collision),
    END_AREA(),

    FREE_LEVEL_POOL(),
    LOAD_AREA(/*area*/ 2),

    // sVisibleStars is set to 0 during FIXED_LOAD above on N64, but not on PC-port.
    // lvl_init_act_selector_values_and_stars must be called here otherwise the
    // previous value is retained and causes incorrect drawing during the 10 transition
    // frames.
    CALL(/*arg*/ 0, /*func*/ lvl_init_act_selector_values_and_stars),

    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 8), // Was 16 frames
    SET_MENU_MUSIC(/*seq*/ 0x000D),
    CALL_LOOP(/*arg*/ 0, /*func*/ lvl_update_obj_and_load_act_button_actions),
    GET_OR_SET(/*op*/ OP_SET, /*var*/ VAR_CURR_ACT_NUM),
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 10), // Was 16 frames
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    // L1:
    EXIT(),
};
