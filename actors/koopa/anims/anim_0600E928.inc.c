#include "pc/rom_assets.h"
// 0x0600E344
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600E344, 0x001c4230, 80474, 0x0000e344, 1316);

// 0x0600E868
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0600E868, 0x001c4230, 80474, 0x0000e868, 192);

// 0x0600E928
static const struct Animation koopa_seg6_anim_0600E928 = {
    0,
    0,
    0,
    0,
    0x15,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0600E868),
    koopa_seg6_animvalue_0600E344,
    koopa_seg6_animindex_0600E868,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600E344),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0600E868),
};
