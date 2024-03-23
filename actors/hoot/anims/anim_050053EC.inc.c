#include "pc/rom_assets.h"
// 0x05004EC0
ROM_ASSET_LOAD_ANIM(hoot_seg5_animvalue_05004EC0, 0x0012a7e0, 32879, 0x00004ec0, 988);

// 0x0500529C
ROM_ASSET_LOAD_ANIM(hoot_seg5_animindex_0500529C, 0x0012a7e0, 32879, 0x0000529c, 336);

// 0x050053EC
static const struct Animation hoot_seg5_anim_050053EC = {
    0,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(hoot_seg5_animindex_0500529C),
    hoot_seg5_animvalue_05004EC0,
    hoot_seg5_animindex_0500529C,
    0,
    ANIM_FIELD_LENGTH(hoot_seg5_animvalue_05004EC0),
    ANIM_FIELD_LENGTH(hoot_seg5_animindex_0500529C),
};
