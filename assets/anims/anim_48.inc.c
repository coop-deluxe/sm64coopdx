#include "pc/rom_assets.h"
static const struct Animation anim_48[] = {
    0,
    189,
    0,
    0,
    0x4D,
    ANIMINDEX_NUMPARTS(anim_48_indices),
    anim_48_values,
    anim_48_indices,
    0,
    ANIM_FIELD_LENGTH(anim_48_values),
    ANIM_FIELD_LENGTH(anim_48_indices),
};


ROM_ASSET_LOAD_ANIM(anim_48_indices, 0x00525d60, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_48_values, 0x00525e5c, 5098, 0x00000000, 5098);

