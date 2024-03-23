#include "pc/rom_assets.h"
static const struct Animation anim_13[] = {
    1,
    189,
    0,
    0,
    0x17,
    ANIMINDEX_NUMPARTS(anim_13_indices),
    anim_13_values,
    anim_13_indices,
    0,
    ANIM_FIELD_LENGTH(anim_13_values),
    ANIM_FIELD_LENGTH(anim_13_indices),
};


ROM_ASSET_LOAD_ANIM(anim_13_indices, 0x004f62ec, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_13_values, 0x004f63e8, 1678, 0x00000000, 1678);

