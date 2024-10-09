#include "pc/rom_assets.h"
// 0x0500A128
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_0500A128, 0x0016d870, 76997, 0x0000a210, 9224);

// 0x0500C530
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_500C530, 0x0016d870, 76997, 0x0000c618, 264);

// 0x0500C638
static const struct Animation peach_seg5_anim_0500C638 = {
    1,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_500C530),
    peach_seg5_animvalue_0500A128,
    peach_seg5_animindex_500C530,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_0500A128),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_500C530),
};
