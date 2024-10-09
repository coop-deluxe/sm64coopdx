#include "pc/rom_assets.h"
static const struct Animation anim_29[] = {
    0,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_29_indices),
    anim_29_values,
    anim_29_indices,
    0,
    ANIM_FIELD_LENGTH(anim_29_values),
    ANIM_FIELD_LENGTH(anim_29_indices),
};


ROM_ASSET_LOAD_ANIM(anim_29_indices, 0x0050c26c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_29_values, 0x0050c368, 582, 0x00000000, 582);

