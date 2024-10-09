#include "pc/rom_assets.h"
// 0x0500DE04
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_0500DE04, 0x001521d0, 57608, 0x0000de04, 2984);

// 0x0500E9AC
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0500E9AC, 0x001521d0, 57608, 0x0000e9ac, 288);

// 0x0500EACC
static const struct Animation ukiki_seg5_anim_0500EACC = {
    0,
    0,
    0,
    0,
    0x26,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0500E9AC),
    ukiki_seg5_animvalue_0500DE04,
    ukiki_seg5_animindex_0500E9AC,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_0500DE04),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0500E9AC),
};
