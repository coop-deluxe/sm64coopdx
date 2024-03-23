#include "pc/rom_assets.h"
// 0x0500C78C
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500C78C, 0x00134d20, 26785, 0x0000c78c, 1740);

// 0x0500CE58
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500CE58, 0x00134d20, 26785, 0x0000ce58, 372);

// 0x0500CFCC
static const struct Animation king_bobomb_seg5_anim_0500CFCC = {
    0,
    0,
    0,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500CE58),
    king_bobomb_seg5_animvalue_0500C78C,
    king_bobomb_seg5_animindex_0500CE58,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500C78C),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500CE58),
};
