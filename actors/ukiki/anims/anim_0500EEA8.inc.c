#include "pc/rom_assets.h"
// 0x0500EAE4
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_0500EAE4, 0x001521d0, 57608, 0x0000eae4, 676);

// 0x0500ED88
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0500ED88, 0x001521d0, 57608, 0x0000ed88, 288);

// 0x0500EEA8
static const struct Animation ukiki_seg5_anim_0500EEA8 = {
    0,
    0,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0500ED88),
    ukiki_seg5_animvalue_0500EAE4,
    ukiki_seg5_animindex_0500ED88,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_0500EAE4),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0500ED88),
};
