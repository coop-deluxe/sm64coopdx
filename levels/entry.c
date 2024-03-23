#include <ultra64.h>
#include "sm64.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "levels/menu/header.h"
#include "levels/scripts.h"

// #include "levels/intro/header.h"

#include "make_const_nonconst.h"

extern const LevelScript level_intro_splash_screen[];
const LevelScript level_script_entry[] = {
#if 1
    SET_REG(/*value*/ LEVEL_CASTLE_GROUNDS),
    EXECUTE(/*seg*/ 0x14, /*script*/ _introSegmentRomStart, /*scriptEnd*/ _introSegmentRomEnd, /*entry*/ level_main_scripts_entry),
    JUMP(level_script_entry),
#else
    // old behavior (intro)
    INIT_LEVEL(),
    SLEEP(/*frames*/ 2),
    BLACKOUT(/*active*/ FALSE),
    SET_REG(/*value*/ 0),
    EXECUTE(/*seg*/ 0x14, /*script*/ _introSegmentRomStart, /*scriptEnd*/ _introSegmentRomEnd, /*entry*/ level_intro_splash_screen),
    JUMP(/*target*/ level_script_entry),
#endif
};
