#include "pc/rom_assets.h"
// 0x0500B730
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500B730, 0x00134d20, 26785, 0x0000b730, 1368);

// 0x0500BC88
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500BC88, 0x00134d20, 26785, 0x0000bc88, 372);

// 0x0500BDFC
static const struct Animation king_bobomb_seg5_anim_0500BDFC = {
    0,
    0,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500BC88),
    king_bobomb_seg5_animvalue_0500B730,
    king_bobomb_seg5_animindex_0500BC88,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500B730),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500BC88),
};
