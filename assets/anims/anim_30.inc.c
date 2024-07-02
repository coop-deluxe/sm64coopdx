#include "pc/rom_assets.h"
static const struct Animation anim_30[] = {
    0,
    189,
    0,
    0,
    0x5A,
    ANIMINDEX_NUMPARTS(anim_30_indices),
    anim_30_values,
    anim_30_indices,
    0,
    ANIM_FIELD_LENGTH(anim_30_values),
    ANIM_FIELD_LENGTH(anim_30_indices),
};


ROM_ASSET_LOAD_ANIM(anim_30_indices, 0x0051151c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_30_values, 0x00511618, 5428, 0x00000000, 5428);

