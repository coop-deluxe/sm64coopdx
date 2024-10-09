#include "pc/rom_assets.h"
// 0x0600E940
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600E940, 0x001c4230, 80474, 0x0000e940, 2540);

// 0x0600F32C
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0600F32C, 0x001c4230, 80474, 0x0000f32c, 192);

// 0x0600F3EC
static const struct Animation koopa_seg6_anim_0600F3EC = {
    0,
    0,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0600F32C),
    koopa_seg6_animvalue_0600E940,
    koopa_seg6_animindex_0600F32C,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600E940),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0600F32C),
};
