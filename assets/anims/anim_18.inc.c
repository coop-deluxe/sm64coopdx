#include "pc/rom_assets.h"
static const struct Animation anim_18[] = {
    0,
    189,
    42,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(anim_18_indices),
    anim_18_values,
    anim_18_indices,
    0,
    ANIM_FIELD_LENGTH(anim_18_values),
    ANIM_FIELD_LENGTH(anim_18_indices),
};


ROM_ASSET_LOAD_ANIM(anim_18_indices, 0x004f74ac, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_18_values, 0x004f94b4, 4452, 0x00000000, 4452);

