#include "pc/rom_assets.h"
// 0x0600DDA8
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600DDA8, 0x001c4230, 80474, 0x0000dda8, 1220);

// 0x0600E26C
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0600E26C, 0x001c4230, 80474, 0x0000cb64, 192);

// 0x0600E32C
static const struct Animation koopa_seg6_anim_0600E32C = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0600E26C),
    koopa_seg6_animvalue_0600DDA8,
    koopa_seg6_animindex_0600E26C,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600DDA8),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0600E26C),
};
