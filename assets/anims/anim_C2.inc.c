#include "pc/rom_assets.h"
static const struct Animation anim_C2[] = {
    0,
    189,
    0,
    0,
    0x5A,
    ANIMINDEX_NUMPARTS(anim_C2_indices),
    anim_C2_values,
    anim_C2_indices,
    0,
    ANIM_FIELD_LENGTH(anim_C2_values),
    ANIM_FIELD_LENGTH(anim_C2_indices),
};


ROM_ASSET_LOAD_ANIM(anim_C2_indices, 0x00570cc8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_C2_values, 0x00570dc4, 5422, 0x00000000, 5422);

