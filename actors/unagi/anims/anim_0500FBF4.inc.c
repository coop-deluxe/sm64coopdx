#include "pc/rom_assets.h"
// 0x0500E310
ROM_ASSET_LOAD_ANIM(unagi_seg5_animvalue_0500E310, 0x0013b910, 41727, 0x0000e310, 6180);

// 0x0500FB34
ROM_ASSET_LOAD_ANIM(unagi_seg5_animindex_0500FB34, 0x0013b910, 41727, 0x0000fb34, 192);

// 0x0500FBF4
static const struct Animation unagi_seg5_anim_0500FBF4 = {
    0,
    0,
    0,
    0,
    0x8C,
    ANIMINDEX_NUMPARTS(unagi_seg5_animindex_0500FB34),
    unagi_seg5_animvalue_0500E310,
    unagi_seg5_animindex_0500FB34,
    0,
    ANIM_FIELD_LENGTH(unagi_seg5_animvalue_0500E310),
    ANIM_FIELD_LENGTH(unagi_seg5_animindex_0500FB34),
};
