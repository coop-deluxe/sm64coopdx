#include "pc/rom_assets.h"
// 0x050087D8
ROM_ASSET_LOAD_ANIM(penguin_seg5_animvalue_050087D8, 0x00160670, 20585, 0x000087d8, 756);

// 0x05008ACC
ROM_ASSET_LOAD_ANIM(penguin_seg5_animindex_05008ACC, 0x00160670, 20585, 0x00008acc, 144);

// 0x05008B5C
static const struct Animation penguin_seg5_anim_05008B5C = {
    0,
    0,
    5,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(penguin_seg5_animindex_05008ACC),
    penguin_seg5_animvalue_050087D8,
    penguin_seg5_animindex_05008ACC,
    0,
    ANIM_FIELD_LENGTH(penguin_seg5_animvalue_050087D8),
    ANIM_FIELD_LENGTH(penguin_seg5_animindex_05008ACC),
};
