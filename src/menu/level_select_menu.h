#ifndef LEVEL_SELECT_MENU_H
#define LEVEL_SELECT_MENU_H

#include <PR/ultratypes.h>

#include "macros.h"

#define LEVEL_INTRO_GOTO_FILE_SELECT            100
#define LEVEL_INTRO_GOTO_DEBUG_LEVEL_SELECT     101
#define LEVEL_INTRO_GOTO_MAIN_SCRIPTS           102

s32 lvl_intro_update(s16 arg1, UNUSED s32 arg2);

#endif // LEVEL_SELECT_MENU_H
