#include "pc/rom_assets.h"
// 0x0500D990
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500D990, 0x00134d20, 26785, 0x0000d990, 724);

// 0x0500DC64
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500DC64, 0x00134d20, 26785, 0x0000dc64, 372);

// 0x0500DDD8
static const struct Animation king_bobomb_seg5_anim_0500DDD8 = {
    1,
    0,
    0,
    0,
    0x0E,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500DC64),
    king_bobomb_seg5_animvalue_0500D990,
    king_bobomb_seg5_animindex_0500DC64,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500D990),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500DC64),
};
