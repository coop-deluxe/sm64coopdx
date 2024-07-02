#include "pc/rom_assets.h"
// 0x05010B6C
ROM_ASSET_LOAD_ANIM(unagi_seg5_animvalue_05010B6C, 0x0013b910, 41727, 0x00010b6c, 2140);

// 0x050113C8
ROM_ASSET_LOAD_ANIM(unagi_seg5_animindex_050113C8, 0x0013b910, 41727, 0x000113c8, 192);

// 0x05011488
static const struct Animation unagi_seg5_anim_05011488 = {
    1,
    0,
    0,
    0,
    0x4C,
    ANIMINDEX_NUMPARTS(unagi_seg5_animindex_050113C8),
    unagi_seg5_animvalue_05010B6C,
    unagi_seg5_animindex_050113C8,
    0,
    ANIM_FIELD_LENGTH(unagi_seg5_animvalue_05010B6C),
    ANIM_FIELD_LENGTH(unagi_seg5_animindex_050113C8),
};
