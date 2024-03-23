#include "pc/rom_assets.h"
static const struct Animation anim_07[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_07_08_indices),
    anim_07_08_values,
    anim_07_08_indices,
    0,
    ANIM_FIELD_LENGTH(anim_07_08_values),
    ANIM_FIELD_LENGTH(anim_07_08_indices),
};

static const struct Animation anim_08[] = {
    1,
    189,
    1,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_07_08_indices),
    anim_07_08_values,
    anim_07_08_indices,
    0,
    ANIM_FIELD_LENGTH(anim_07_08_values),
    ANIM_FIELD_LENGTH(anim_07_08_indices),
};


ROM_ASSET_LOAD_ANIM(anim_07_08_indices, 0x004f2538, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_07_08_values, 0x004f2634, 1468, 0x00000000, 1468);

