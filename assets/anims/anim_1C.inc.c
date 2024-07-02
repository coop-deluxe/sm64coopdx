#include "pc/rom_assets.h"
static const struct Animation anim_1C[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_1C_indices),
    anim_1C_values,
    anim_1C_indices,
    0,
    ANIM_FIELD_LENGTH(anim_1C_values),
    ANIM_FIELD_LENGTH(anim_1C_indices),
};


ROM_ASSET_LOAD_ANIM(anim_1C_indices, 0x004fce00, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_1C_values, 0x004fcefc, 780, 0x00000000, 780);

