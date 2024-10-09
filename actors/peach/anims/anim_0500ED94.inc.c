#include "pc/rom_assets.h"
// 0x0500E6CC
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_0500E6CC, 0x0016d870, 76997, 0x0000e7b4, 1472);

// 0x0500EC8C
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_500EC8C, 0x0016d870, 76997, 0x0000ed74, 264);

// 0x0500ED94
static const struct Animation peach_seg5_anim_0500ED94 = {
    1,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_500EC8C),
    peach_seg5_animvalue_0500E6CC,
    peach_seg5_animindex_500EC8C,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_0500E6CC),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_500EC8C),
};
