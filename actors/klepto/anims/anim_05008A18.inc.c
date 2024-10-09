#include "pc/rom_assets.h"
// 0x050086D8
ROM_ASSET_LOAD_ANIM(klepto_seg5_animvalue_050086D8, 0x00145e90, 48337, 0x000086d8, 508);

// 0x050088D4
ROM_ASSET_LOAD_ANIM(klepto_seg5_animindex_050088D4, 0x00145e90, 48337, 0x000088d4, 324);

// 0x05008A18
static const struct Animation klepto_seg5_anim_05008A18 = {
    0,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(klepto_seg5_animindex_050088D4),
    klepto_seg5_animvalue_050086D8,
    klepto_seg5_animindex_050088D4,
    0,
    ANIM_FIELD_LENGTH(klepto_seg5_animvalue_050086D8),
    ANIM_FIELD_LENGTH(klepto_seg5_animindex_050088D4),
};
