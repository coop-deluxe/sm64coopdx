#include "pc/rom_assets.h"
// 0x0500F48C
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_0500F48C, 0x0016d870, 76997, 0x0000f574, 2288);

// 0x0500FD7C
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_500FD7C, 0x0016d870, 76997, 0x0000fe64, 264);

// 0x0500FE84
static const struct Animation peach_seg5_anim_0500FE84 = {
    0,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_500FD7C),
    peach_seg5_animvalue_0500F48C,
    peach_seg5_animindex_500FD7C,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_0500F48C),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_500FD7C),
};
