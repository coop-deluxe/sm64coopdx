#include "pc/rom_assets.h"
// 0x0500F090
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500F090, 0x00134d20, 26785, 0x0000f090, 1220);

// 0x0500F554
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500F554, 0x00134d20, 26785, 0x0000f554, 372);

// 0x0500F6C8
static const struct Animation king_bobomb_seg5_anim_0500F6C8 = {
    0,
    0,
    0,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500F554),
    king_bobomb_seg5_animvalue_0500F090,
    king_bobomb_seg5_animindex_0500F554,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500F090),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500F554),
};
