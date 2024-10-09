#include "pc/rom_assets.h"
// 0x06010E60
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_06010E60, 0x001c4230, 80474, 0x00010e60, 440);

// 0x06011018
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_06011018, 0x001c4230, 80474, 0x00011018, 192);

// 0x060110D8
static const struct Animation koopa_seg6_anim_060110D8 = {
    0,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_06011018),
    koopa_seg6_animvalue_06010E60,
    koopa_seg6_animindex_06011018,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_06010E60),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_06011018),
};
