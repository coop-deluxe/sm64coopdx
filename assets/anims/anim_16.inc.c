#include "pc/rom_assets.h"
static const struct Animation anim_16[] = {
    0,
    189,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(anim_16_indices),
    anim_16_values,
    anim_16_indices,
    0,
    ANIM_FIELD_LENGTH(anim_16_values),
    ANIM_FIELD_LENGTH(anim_16_indices),
};


ROM_ASSET_LOAD_ANIM(anim_16_indices, 0x004f74ac, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_16_values, 0x004f75a8, 4452, 0x00000000, 4452);

