#include "pc/rom_assets.h"
// 0x0500F548
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_0500F548, 0x001521d0, 57608, 0x0000f548, 1564);

// 0x0500FB64
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0500FB64, 0x001521d0, 57608, 0x0000fb64, 288);

// 0x0500FC84
static const struct Animation ukiki_seg5_anim_0500FC84 = {
    1,
    0,
    0,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0500FB64),
    ukiki_seg5_animvalue_0500F548,
    ukiki_seg5_animindex_0500FB64,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_0500F548),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0500FB64),
};
