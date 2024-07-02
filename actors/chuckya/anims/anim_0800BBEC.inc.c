#include "pc/rom_assets.h"
// 0x0800BA10
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animvalue_0800BA10, 0x001f2200, 59076, 0x0000ba10, 104);

// 0x0800BA78
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animindex_0800BA78, 0x001f2200, 59076, 0x0000ba78, 372);

// 0x0800BBEC
static const struct Animation chuckya_seg8_anim_0800BBEC = {
    0,
    0,
    0,
    0,
    0x07,
    ANIMINDEX_NUMPARTS(chuckya_seg8_animindex_0800BA78),
    chuckya_seg8_animvalue_0800BA10,
    chuckya_seg8_animindex_0800BA78,
    0,
    ANIM_FIELD_LENGTH(chuckya_seg8_animvalue_0800BA10),
    ANIM_FIELD_LENGTH(chuckya_seg8_animindex_0800BA78),
};
