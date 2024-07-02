#include "pc/rom_assets.h"
// 0x06010270
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_06010270, 0x001c4230, 80474, 0x00010270, 772);

// 0x06010574
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_06010574, 0x001c4230, 80474, 0x00010574, 192);

// 0x06010634
static const struct Animation koopa_seg6_anim_06010634 = {
    0,
    0,
    0,
    0,
    0x0E,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_06010574),
    koopa_seg6_animvalue_06010270,
    koopa_seg6_animindex_06010574,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_06010270),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_06010574),
};
