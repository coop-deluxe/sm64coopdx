#include "pc/rom_assets.h"
// 0x0800B1C0
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animvalue_0800B1C0, 0x001f2200, 59076, 0x0000b1c0, 372);

// 0x0800B334
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animindex_0800B334, 0x001f2200, 59076, 0x0000b334, 372);

// 0x0800B4A8
static const struct Animation chuckya_seg8_anim_0800B4A8 = {
    0,
    0,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(chuckya_seg8_animindex_0800B334),
    chuckya_seg8_animvalue_0800B1C0,
    chuckya_seg8_animindex_0800B334,
    0,
    ANIM_FIELD_LENGTH(chuckya_seg8_animvalue_0800B1C0),
    ANIM_FIELD_LENGTH(chuckya_seg8_animindex_0800B334),
};
