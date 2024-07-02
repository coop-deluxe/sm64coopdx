#include "pc/rom_assets.h"
// 0x0600D530
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600D530, 0x001c4230, 80474, 0x0000d530, 532);

// 0x0600D744
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0600D744, 0x001c4230, 80474, 0x0000d744, 192);

// 0x0600D804
static const struct Animation koopa_seg6_anim_0600D804 = {
    0,
    0,
    0,
    0,
    0x0D,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0600D744),
    koopa_seg6_animvalue_0600D530,
    koopa_seg6_animindex_0600D744,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600D530),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0600D744),
};
