#include "pc/rom_assets.h"
// 0x0500CFE4
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500CFE4, 0x00134d20, 26785, 0x0000cfe4, 1112);

// 0x0500D43C
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500D43C, 0x00134d20, 26785, 0x0000d43c, 372);

// 0x0500D5B0
static const struct Animation king_bobomb_seg5_anim_0500D5B0 = {
    0,
    0,
    0,
    0,
    0x20,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500D43C),
    king_bobomb_seg5_animvalue_0500CFE4,
    king_bobomb_seg5_animindex_0500D43C,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500CFE4),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500D43C),
};
