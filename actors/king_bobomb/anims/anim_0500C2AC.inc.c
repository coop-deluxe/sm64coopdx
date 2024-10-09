#include "pc/rom_assets.h"
// 0x0500BE14
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500BE14, 0x00134d20, 26785, 0x0000be14, 804);

// 0x0500C138
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500C138, 0x00134d20, 26785, 0x0000c138, 372);

// 0x0500C2AC
static const struct Animation king_bobomb_seg5_anim_0500C2AC = {
    0,
    0,
    0,
    0,
    0x1D,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500C138),
    king_bobomb_seg5_animvalue_0500BE14,
    king_bobomb_seg5_animindex_0500C138,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500BE14),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500C138),
};
