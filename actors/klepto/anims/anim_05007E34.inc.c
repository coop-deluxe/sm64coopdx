#include "pc/rom_assets.h"
// 0x050079C8
ROM_ASSET_LOAD_ANIM(klepto_seg5_animvalue_050079C8, 0x00145e90, 48337, 0x000079c8, 808);

// 0x05007CF0
ROM_ASSET_LOAD_ANIM(klepto_seg5_animindex_05007CF0, 0x00145e90, 48337, 0x00007cf0, 324);

// 0x05007E34
static const struct Animation klepto_seg5_anim_05007E34 = {
    0,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(klepto_seg5_animindex_05007CF0),
    klepto_seg5_animvalue_050079C8,
    klepto_seg5_animindex_05007CF0,
    0,
    ANIM_FIELD_LENGTH(klepto_seg5_animvalue_050079C8),
    ANIM_FIELD_LENGTH(klepto_seg5_animindex_05007CF0),
};
