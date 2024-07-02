#include "pc/rom_assets.h"
static const struct Animation anim_09[] = {
    16,
    189,
    0,
    0,
    0x34,
    ANIMINDEX_NUMPARTS(anim_09_indices),
    anim_09_values,
    anim_09_indices,
    0,
    ANIM_FIELD_LENGTH(anim_09_values),
    ANIM_FIELD_LENGTH(anim_09_indices),
};


ROM_ASSET_LOAD_ANIM(anim_09_indices, 0x004f2c08, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_09_values, 0x004f2d04, 3052, 0x00000000, 3052);

