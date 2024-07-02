#include "pc/rom_assets.h"
static const struct Animation anim_06[] = {
    1,
    189,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(anim_06_indices),
    anim_06_values,
    anim_06_indices,
    0,
    ANIM_FIELD_LENGTH(anim_06_values),
    ANIM_FIELD_LENGTH(anim_06_indices),
};


ROM_ASSET_LOAD_ANIM(anim_06_indices, 0x004f2090, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_06_values, 0x004f218c, 892, 0x00000000, 892);

