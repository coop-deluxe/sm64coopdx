#include "pc/rom_assets.h"
static const struct Animation anim_03[] = {
    1,
    189,
    0,
    0,
    0x40,
    ANIMINDEX_NUMPARTS(anim_03_indices),
    anim_03_values,
    anim_03_indices,
    0,
    ANIM_FIELD_LENGTH(anim_03_values),
    ANIM_FIELD_LENGTH(anim_03_indices),
};


ROM_ASSET_LOAD_ANIM(anim_03_indices, 0x004eecc4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_03_values, 0x004eedc0, 4372, 0x00000000, 4372);

