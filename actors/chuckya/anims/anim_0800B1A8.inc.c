#include "pc/rom_assets.h"
// 0x0800AF80
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animvalue_0800AF80, 0x001f2200, 59076, 0x0000af80, 180);

// 0x0800B034
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animindex_0800B034, 0x001f2200, 59076, 0x0000b034, 372);

// 0x0800B1A8
static const struct Animation chuckya_seg8_anim_0800B1A8 = {
    0,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(chuckya_seg8_animindex_0800B034),
    chuckya_seg8_animvalue_0800AF80,
    chuckya_seg8_animindex_0800B034,
    0,
    ANIM_FIELD_LENGTH(chuckya_seg8_animvalue_0800AF80),
    ANIM_FIELD_LENGTH(chuckya_seg8_animindex_0800B034),
};
