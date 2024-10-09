#include "pc/rom_assets.h"
// 0x06000E78
ROM_ASSET_LOAD_ANIM(koopa_flag_seg6_animvalue_06000E78, 0x001c4230, 80474, 0x00000e78, 300);

// 0x06000FA4
ROM_ASSET_LOAD_ANIM(koopa_flag_seg6_animindex_06000FA4, 0x001c4230, 80474, 0x00000fa4, 108);

// 0x06001010
static const struct Animation koopa_flag_seg6_anim_06001010 = {
    0,
    0,
    0,
    0,
    0x1D,
    ANIMINDEX_NUMPARTS(koopa_flag_seg6_animindex_06000FA4),
    koopa_flag_seg6_animvalue_06000E78,
    koopa_flag_seg6_animindex_06000FA4,
    0,
    ANIM_FIELD_LENGTH(koopa_flag_seg6_animvalue_06000E78),
    ANIM_FIELD_LENGTH(koopa_flag_seg6_animindex_06000FA4),
};
