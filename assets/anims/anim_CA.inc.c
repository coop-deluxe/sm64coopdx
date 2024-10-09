#include "pc/rom_assets.h"
static const struct Animation anim_CA[] = {
    0,
    189,
    25,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_CA_indices),
    anim_CA_values,
    anim_CA_indices,
    0,
    ANIM_FIELD_LENGTH(anim_CA_values),
    ANIM_FIELD_LENGTH(anim_CA_indices),
};


ROM_ASSET_LOAD_ANIM(anim_CA_indices, 0x00576104, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_CA_values, 0x00576200, 1998, 0x00000000, 1998);

