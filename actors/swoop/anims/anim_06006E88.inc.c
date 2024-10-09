#include "pc/rom_assets.h"
// 0x06006DB8
ROM_ASSET_LOAD_ANIM(swoop_seg6_animvalue_06006DB8, 0x001e7ee0, 40011, 0x00006db8, 100);

// 0x06006E1C
ROM_ASSET_LOAD_ANIM(swoop_seg6_animindex_06006E1C, 0x001e7ee0, 40011, 0x00006e1c, 108);

// 0x06006E88
static const struct Animation swoop_seg6_anim_06006E88 = {
    0,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(swoop_seg6_animindex_06006E1C),
    swoop_seg6_animvalue_06006DB8,
    swoop_seg6_animindex_06006E1C,
    0,
    ANIM_FIELD_LENGTH(swoop_seg6_animvalue_06006DB8),
    ANIM_FIELD_LENGTH(swoop_seg6_animindex_06006E1C),
};
