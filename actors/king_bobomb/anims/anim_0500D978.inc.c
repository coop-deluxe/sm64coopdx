#include "pc/rom_assets.h"
// 0x0500D5C8
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500D5C8, 0x00134d20, 26785, 0x0000d5c8, 572);

// 0x0500D804
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500D804, 0x00134d20, 26785, 0x0000d804, 372);

// 0x0500D978
static const struct Animation king_bobomb_seg5_anim_0500D978 = {
    0,
    0,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500D804),
    king_bobomb_seg5_animvalue_0500D5C8,
    king_bobomb_seg5_animindex_0500D804,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500D5C8),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500D804),
};
