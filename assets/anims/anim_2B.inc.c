#include "pc/rom_assets.h"
static const struct Animation anim_2B[] = {
    0,
    189,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(anim_2B_indices),
    anim_2B_values,
    anim_2B_indices,
    0,
    ANIM_FIELD_LENGTH(anim_2B_values),
    ANIM_FIELD_LENGTH(anim_2B_indices),
};


ROM_ASSET_LOAD_ANIM(anim_2B_indices, 0x0050cbc0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_2B_values, 0x0050ccbc, 1582, 0x00000000, 1582);

