#include "pc/rom_assets.h"
// 0x05007E4C
ROM_ASSET_LOAD_ANIM(klepto_seg5_animvalue_05007E4C, 0x00145e90, 48337, 0x00007e4c, 1840);

// 0x0500857C
ROM_ASSET_LOAD_ANIM(klepto_seg5_animindex_0500857C, 0x00145e90, 48337, 0x0000857c, 324);

// 0x050086C0
static const struct Animation klepto_seg5_anim_050086C0 = {
    0,
    0,
    0,
    0,
    0x24,
    ANIMINDEX_NUMPARTS(klepto_seg5_animindex_0500857C),
    klepto_seg5_animvalue_05007E4C,
    klepto_seg5_animindex_0500857C,
    0,
    ANIM_FIELD_LENGTH(klepto_seg5_animvalue_05007E4C),
    ANIM_FIELD_LENGTH(klepto_seg5_animindex_0500857C),
};
