#include "pc/rom_assets.h"
// 0x0500F6E0
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500F6E0, 0x00134d20, 26785, 0x0000f6e0, 1476);

// 0x0500FCA4
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500FCA4, 0x00134d20, 26785, 0x0000fca4, 372);

// 0x0500FE18
static const struct Animation king_bobomb_seg5_anim_0500FE18 = {
    0,
    0,
    0,
    0,
    0x1D,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500FCA4),
    king_bobomb_seg5_animvalue_0500F6E0,
    king_bobomb_seg5_animindex_0500FCA4,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500F6E0),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500FCA4),
};
