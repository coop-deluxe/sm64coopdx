#ifndef STAR_SELECT_H
#define STAR_SELECT_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "types.h"

enum StarSelectorTypes
{
    STAR_SELECTOR_NOT_SELECTED,
    STAR_SELECTOR_SELECTED,
    STAR_SELECTOR_100_COINS
};

struct OverrideHideActSelectHud {
    /*0x00*/ u8 all;
    /*0x02*/ u8 score;
    /*0x04*/ u8 levelName;
    /*0x06*/ u8 courseNum;
    /*0x08*/ u8 actName;
    /*0x0A*/ u8 starNum;
    /*0x0C*/ u8 playersInLevel;
};

extern struct OverrideHideActSelectHud gOverrideHideActSelectHud;


#ifdef AVOID_UB
Gfx *geo_act_selector_strings(s16 callContext, UNUSED struct GraphNode *node, UNUSED void *context);
#else
Gfx *geo_act_selector_strings(s16 callContext, UNUSED struct GraphNode *node);
#endif
s32 lvl_init_act_selector_values_and_stars(UNUSED s32 arg, UNUSED s32 unused);
s32 lvl_update_obj_and_load_act_button_actions(UNUSED s32 arg, UNUSED s32 unused);

#endif // STAR_SELECT_H
