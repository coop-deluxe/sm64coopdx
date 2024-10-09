#include "pc/rom_assets.h"
// 0x05008A30
ROM_ASSET_LOAD_ANIM(klepto_seg5_animvalue_05008A30, 0x00145e90, 48337, 0x00008a30, 368);

// 0x05008BA0
ROM_ASSET_LOAD_ANIM(klepto_seg5_animindex_05008BA0, 0x00145e90, 48337, 0x00008ba0, 324);

// 0x05008CE4
static const struct Animation klepto_seg5_anim_05008CE4 = {
    1,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(klepto_seg5_animindex_05008BA0),
    klepto_seg5_animvalue_05008A30,
    klepto_seg5_animindex_05008BA0,
    0,
    ANIM_FIELD_LENGTH(klepto_seg5_animvalue_05008A30),
    ANIM_FIELD_LENGTH(klepto_seg5_animindex_05008BA0),
};
