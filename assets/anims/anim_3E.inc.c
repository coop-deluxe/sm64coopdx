#include "pc/rom_assets.h"
static const struct Animation anim_3E[] = {
    1,
    189,
    0,
    0,
    0x9B,
    ANIMINDEX_NUMPARTS(anim_3E_indices),
    anim_3E_values,
    anim_3E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_3E_values),
    ANIM_FIELD_LENGTH(anim_3E_indices),
};


ROM_ASSET_LOAD_ANIM(anim_3E_indices, 0x005205ac, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_3E_values, 0x005206a8, 11490, 0x00000000, 11490);

