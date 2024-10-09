#include "pc/rom_assets.h"
// 0x060110F0
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_060110F0, 0x001c4230, 80474, 0x000110f0, 412);

// 0x0601128C
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0601128C, 0x001c4230, 80474, 0x0001128c, 192);

// 0x0601134C
static const struct Animation koopa_seg6_anim_0601134C = {
    1,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0601128C),
    koopa_seg6_animvalue_060110F0,
    koopa_seg6_animindex_0601128C,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_060110F0),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0601128C),
};
