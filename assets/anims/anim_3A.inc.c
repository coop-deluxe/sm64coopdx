#include "pc/rom_assets.h"
static const struct Animation anim_3A[] = {
    1,
    189,
    0,
    0,
    0x06,
    ANIMINDEX_NUMPARTS(anim_3A_indices),
    anim_3A_values,
    anim_3A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_3A_values),
    ANIM_FIELD_LENGTH(anim_3A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_3A_indices, 0x0051f924, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_3A_values, 0x0051fa20, 374, 0x00000000, 374);

