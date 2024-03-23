#include "pc/rom_assets.h"
static const struct Animation anim_43[] = {
    1,
    189,
    0,
    0,
    0x02,
    ANIMINDEX_NUMPARTS(anim_43_indices),
    anim_43_values,
    anim_43_indices,
    0,
    ANIM_FIELD_LENGTH(anim_43_values),
    ANIM_FIELD_LENGTH(anim_43_indices),
};


ROM_ASSET_LOAD_ANIM(anim_43_indices, 0x00524e28, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_43_values, 0x00524f24, 84, 0x00000000, 84);

