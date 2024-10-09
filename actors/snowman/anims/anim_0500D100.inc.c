#include "pc/rom_assets.h"
// 0x0500CEF0
ROM_ASSET_LOAD_ANIM(snowman_seg5_animvalue_0500CEF0, 0x00160670, 20585, 0x0000cef0, 408);

// 0x0500D088
ROM_ASSET_LOAD_ANIM(snowman_seg5_animindex_0500D088, 0x00160670, 20585, 0x0000d088, 120);

// 0x0500D100
static const struct Animation snowman_seg5_anim_0500D100 = {
    0,
    0,
    0,
    0,
    0x16,
    ANIMINDEX_NUMPARTS(snowman_seg5_animindex_0500D088),
    snowman_seg5_animvalue_0500CEF0,
    snowman_seg5_animindex_0500D088,
    0,
    ANIM_FIELD_LENGTH(snowman_seg5_animvalue_0500CEF0),
    ANIM_FIELD_LENGTH(snowman_seg5_animindex_0500D088),
};
