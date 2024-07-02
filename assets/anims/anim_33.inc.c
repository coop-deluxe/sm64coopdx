#include "pc/rom_assets.h"
static const struct Animation anim_33[] = {
    0,
    189,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(anim_33_indices),
    anim_33_values,
    anim_33_indices,
    0,
    ANIM_FIELD_LENGTH(anim_33_values),
    ANIM_FIELD_LENGTH(anim_33_indices),
};


ROM_ASSET_LOAD_ANIM(anim_33_indices, 0x00517604, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_33_values, 0x00517700, 2840, 0x00000000, 2840);

