#include "pc/rom_assets.h"
// 0x0800BC04
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animvalue_0800BC04, 0x001f2200, 59076, 0x0000bc04, 736);

// 0x0800BEE4
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animindex_0800BEE4, 0x001f2200, 59076, 0x0000bee4, 372);

// 0x0800C058
static const struct Animation chuckya_seg8_anim_0800C058 = {
    0,
    0,
    0,
    0,
    0x1D,
    ANIMINDEX_NUMPARTS(chuckya_seg8_animindex_0800BEE4),
    chuckya_seg8_animvalue_0800BC04,
    chuckya_seg8_animindex_0800BEE4,
    0,
    ANIM_FIELD_LENGTH(chuckya_seg8_animvalue_0800BC04),
    ANIM_FIELD_LENGTH(chuckya_seg8_animindex_0800BEE4),
};
