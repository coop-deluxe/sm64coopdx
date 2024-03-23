#include "pc/rom_assets.h"
// 0x0500FC0C
ROM_ASSET_LOAD_ANIM(unagi_seg5_animvalue_0500FC0C, 0x0013b910, 41727, 0x0000fc0c, 1980);

// 0x050103C8
ROM_ASSET_LOAD_ANIM(unagi_seg5_animindex_050103C8, 0x0013b910, 41727, 0x000103c8, 192);

// 0x05010488
static const struct Animation unagi_seg5_anim_05010488 = {
    0,
    0,
    0,
    0,
    0x22,
    ANIMINDEX_NUMPARTS(unagi_seg5_animindex_050103C8),
    unagi_seg5_animvalue_0500FC0C,
    unagi_seg5_animindex_050103C8,
    0,
    ANIM_FIELD_LENGTH(unagi_seg5_animvalue_0500FC0C),
    ANIM_FIELD_LENGTH(unagi_seg5_animindex_050103C8),
};
