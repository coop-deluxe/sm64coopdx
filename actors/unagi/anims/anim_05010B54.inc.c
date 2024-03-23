#include "pc/rom_assets.h"
// 0x050104A0
ROM_ASSET_LOAD_ANIM(unagi_seg5_animvalue_050104A0, 0x0013b910, 41727, 0x000104a0, 1524);

// 0x05010A94
ROM_ASSET_LOAD_ANIM(unagi_seg5_animindex_05010A94, 0x0013b910, 41727, 0x00010a94, 192);

// 0x05010B54
static const struct Animation unagi_seg5_anim_05010B54 = {
    0,
    0,
    0,
    0,
    0x36,
    ANIMINDEX_NUMPARTS(unagi_seg5_animindex_05010A94),
    unagi_seg5_animvalue_050104A0,
    unagi_seg5_animindex_05010A94,
    0,
    ANIM_FIELD_LENGTH(unagi_seg5_animvalue_050104A0),
    ANIM_FIELD_LENGTH(unagi_seg5_animindex_05010A94),
};
