#include "pc/rom_assets.h"
// 0x0600FB34
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600FB34, 0x001c4230, 80474, 0x0000fb34, 1636);

// 0x06010198
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_06010198, 0x001c4230, 80474, 0x00010198, 192);

// 0x06010258
static const struct Animation koopa_seg6_anim_06010258 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_06010198),
    koopa_seg6_animvalue_0600FB34,
    koopa_seg6_animindex_06010198,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600FB34),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_06010198),
};
