#include "pc/rom_assets.h"
// 0x050079FC
ROM_ASSET_LOAD_ANIM(penguin_seg5_animvalue_050079FC, 0x00160670, 20585, 0x000079fc, 832);

// 0x05007D3C
ROM_ASSET_LOAD_ANIM(penguin_seg5_animindex_05007D3C, 0x00160670, 20585, 0x00007d3c, 144);

// 0x05007DCC
static const struct Animation penguin_seg5_anim_05007DCC = {
    1,
    0,
    0,
    0,
    0x19,
    ANIMINDEX_NUMPARTS(penguin_seg5_animindex_05007D3C),
    penguin_seg5_animvalue_050079FC,
    penguin_seg5_animindex_05007D3C,
    0,
    ANIM_FIELD_LENGTH(penguin_seg5_animvalue_050079FC),
    ANIM_FIELD_LENGTH(penguin_seg5_animindex_05007D3C),
};
