#include "pc/rom_assets.h"
static const struct Animation anim_C7[] = {
    0,
    189,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(anim_C7_indices),
    anim_C7_values,
    anim_C7_indices,
    0,
    ANIM_FIELD_LENGTH(anim_C7_values),
    ANIM_FIELD_LENGTH(anim_C7_indices),
};


ROM_ASSET_LOAD_ANIM(anim_C7_indices, 0x005744a8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_C7_values, 0x005745a4, 2844, 0x00000000, 2844);

