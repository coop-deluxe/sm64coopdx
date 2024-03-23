#include "pc/rom_assets.h"
// 0x0500C2C4
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500C2C4, 0x00134d20, 26785, 0x0000c2c4, 232);

// 0x0500C3AC
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500C3AC, 0x00134d20, 26785, 0x0000c3ac, 372);

// 0x0500C520
static const struct Animation king_bobomb_seg5_anim_0500C520 = {
    0,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500C3AC),
    king_bobomb_seg5_animvalue_0500C2C4,
    king_bobomb_seg5_animindex_0500C3AC,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500C2C4),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500C3AC),
};
