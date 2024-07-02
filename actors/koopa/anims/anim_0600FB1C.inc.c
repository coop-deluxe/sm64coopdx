#include "pc/rom_assets.h"
// 0x0600F404
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600F404, 0x001c4230, 80474, 0x0000f404, 1624);

// 0x0600FA5C
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0600FA5C, 0x001c4230, 80474, 0x0000fa5c, 192);

// 0x0600FB1C
static const struct Animation koopa_seg6_anim_0600FB1C = {
    0,
    0,
    0,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0600FA5C),
    koopa_seg6_animvalue_0600F404,
    koopa_seg6_animindex_0600FA5C,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600F404),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0600FA5C),
};
