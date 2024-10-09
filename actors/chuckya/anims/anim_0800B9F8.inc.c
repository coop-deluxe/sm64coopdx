#include "pc/rom_assets.h"
// 0x0800B4C0
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animvalue_0800B4C0, 0x001f2200, 59076, 0x0000b4c0, 964);

// 0x0800B884
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animindex_0800B884, 0x001f2200, 59076, 0x0000b884, 372);

// 0x0800B9F8
static const struct Animation chuckya_seg8_anim_0800B9F8 = {
    0,
    0,
    0,
    0,
    0x1D,
    ANIMINDEX_NUMPARTS(chuckya_seg8_animindex_0800B884),
    chuckya_seg8_animvalue_0800B4C0,
    chuckya_seg8_animindex_0800B884,
    0,
    ANIM_FIELD_LENGTH(chuckya_seg8_animvalue_0800B4C0),
    ANIM_FIELD_LENGTH(chuckya_seg8_animindex_0800B884),
};
