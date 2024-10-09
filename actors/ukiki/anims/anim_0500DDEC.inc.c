#include "pc/rom_assets.h"
// 0x0500DC98
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_0500DC98, 0x001521d0, 57608, 0x0000dc98, 52);

// 0x0500DCCC
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0500DCCC, 0x001521d0, 57608, 0x0000dccc, 288);

// 0x0500DDEC
static const struct Animation ukiki_seg5_anim_0500DDEC = {
    0,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0500DCCC),
    ukiki_seg5_animvalue_0500DC98,
    ukiki_seg5_animindex_0500DCCC,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_0500DC98),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0500DCCC),
};
