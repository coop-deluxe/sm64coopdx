#include "pc/rom_assets.h"
static const struct Animation anim_21[] = {
    1,
    189,
    0,
    0,
    0x23,
    ANIMINDEX_NUMPARTS(anim_21_indices),
    anim_21_values,
    anim_21_indices,
    0,
    ANIM_FIELD_LENGTH(anim_21_values),
    ANIM_FIELD_LENGTH(anim_21_indices),
};


ROM_ASSET_LOAD_ANIM(anim_21_indices, 0x005000f4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_21_values, 0x005001f0, 2610, 0x00000000, 2610);

