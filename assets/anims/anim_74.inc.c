#include "pc/rom_assets.h"
static const struct Animation anim_74[] = {
    1,
    189,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(anim_74_indices),
    anim_74_values,
    anim_74_indices,
    0,
    ANIM_FIELD_LENGTH(anim_74_values),
    ANIM_FIELD_LENGTH(anim_74_indices),
};


ROM_ASSET_LOAD_ANIM(anim_74_indices, 0x00540374, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_74_values, 0x00540470, 1844, 0x00000000, 1844);

