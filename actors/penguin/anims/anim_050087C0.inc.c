#include "pc/rom_assets.h"
// 0x05007DE4
ROM_ASSET_LOAD_ANIM(penguin_seg5_animvalue_05007DE4, 0x00160670, 20585, 0x00007de4, 2380);

// 0x05008730
ROM_ASSET_LOAD_ANIM(penguin_seg5_animindex_05008730, 0x00160670, 20585, 0x00008730, 144);

// 0x050087C0
static const struct Animation penguin_seg5_anim_050087C0 = {
    0,
    0,
    0,
    0,
    0x5A,
    ANIMINDEX_NUMPARTS(penguin_seg5_animindex_05008730),
    penguin_seg5_animvalue_05007DE4,
    penguin_seg5_animindex_05008730,
    0,
    ANIM_FIELD_LENGTH(penguin_seg5_animvalue_05007DE4),
    ANIM_FIELD_LENGTH(penguin_seg5_animindex_05008730),
};
