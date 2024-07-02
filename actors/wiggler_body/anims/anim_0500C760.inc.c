#include "pc/rom_assets.h"
// 0x0500C2F0
ROM_ASSET_LOAD_ANIM(wiggler_seg5_animvalue_0500C2F0, 0x00180bb0, 29674, 0x0000c2f0, 1004);

// 0x0500C6DC
ROM_ASSET_LOAD_ANIM(wiggler_seg5_animindex_0500C6DC, 0x00180bb0, 29674, 0x0000c6dc, 132);

// 0x0500C760
static const struct Animation wiggler_seg5_anim_0500C760 = {
    0,
    0,
    0,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(wiggler_seg5_animindex_0500C6DC),
    wiggler_seg5_animvalue_0500C2F0,
    wiggler_seg5_animindex_0500C6DC,
    0,
    ANIM_FIELD_LENGTH(wiggler_seg5_animvalue_0500C2F0),
    ANIM_FIELD_LENGTH(wiggler_seg5_animindex_0500C6DC),
};
