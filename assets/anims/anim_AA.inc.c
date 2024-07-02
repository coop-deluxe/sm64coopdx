#include "pc/rom_assets.h"
static const struct Animation anim_AA[] = {
    1,
    189,
    0,
    0,
    0x0D,
    ANIMINDEX_NUMPARTS(anim_AA_indices),
    anim_AA_values,
    anim_AA_indices,
    0,
    ANIM_FIELD_LENGTH(anim_AA_values),
    ANIM_FIELD_LENGTH(anim_AA_indices),
};


ROM_ASSET_LOAD_ANIM(anim_AA_indices, 0x00564d44, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_AA_values, 0x00564e40, 972, 0x00000000, 972);

