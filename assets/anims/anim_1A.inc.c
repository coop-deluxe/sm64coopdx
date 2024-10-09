#include "pc/rom_assets.h"
static const struct Animation anim_1A[] = {
    1,
    189,
    0,
    0,
    0x11,
    ANIMINDEX_NUMPARTS(anim_1A_indices),
    anim_1A_values,
    anim_1A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_1A_values),
    ANIM_FIELD_LENGTH(anim_1A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_1A_indices, 0x004fbc30, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_1A_values, 0x004fbd2c, 1146, 0x00000000, 1146);

