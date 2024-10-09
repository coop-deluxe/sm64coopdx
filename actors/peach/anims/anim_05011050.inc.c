#include "pc/rom_assets.h"
// 0x0500FE9C
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_0500FE9C, 0x0016d870, 76997, 0x0000ff84, 4268);

// 0x05010F48
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_5010F48, 0x0016d870, 76997, 0x00011030, 264);

// 0x05011050
static const struct Animation peach_seg5_anim_05011050 = {
    1,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_5010F48),
    peach_seg5_animvalue_0500FE9C,
    peach_seg5_animindex_5010F48,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_0500FE9C),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_5010F48),
};
