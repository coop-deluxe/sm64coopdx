#include "pc/rom_assets.h"
// 0x0600C6A0
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600C6A0, 0x001c4230, 80474, 0x0000c6a0, 1220);

// 0x0600CB64
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0600CB64, 0x001c4230, 80474, 0x0000cb64, 192);

// 0x0600CC24
static const struct Animation koopa_seg6_anim_0600CC24 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0600CB64),
    koopa_seg6_animvalue_0600C6A0,
    koopa_seg6_animindex_0600CB64,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600C6A0),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0600CB64),
};
