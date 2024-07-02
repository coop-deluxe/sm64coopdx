#include "pc/rom_assets.h"
// 0x0600D81C
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600D81C, 0x001c4230, 80474, 0x0000d81c, 1204);

// 0x0600DCD0
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0600DCD0, 0x001c4230, 80474, 0x0000dcd0, 192);

// 0x0600DD90
static const struct Animation koopa_seg6_anim_0600DD90 = {
    0,
    0,
    0,
    0,
    0x16,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0600DCD0),
    koopa_seg6_animvalue_0600D81C,
    koopa_seg6_animindex_0600DCD0,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600D81C),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0600DCD0),
};
