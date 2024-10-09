#include "pc/rom_assets.h"
static const struct Animation anim_55[] = {
    1,
    189,
    0,
    0,
    0x98,
    ANIMINDEX_NUMPARTS(anim_55_indices),
    anim_55_values,
    anim_55_indices,
    0,
    ANIM_FIELD_LENGTH(anim_55_values),
    ANIM_FIELD_LENGTH(anim_55_indices),
};


ROM_ASSET_LOAD_ANIM(anim_55_indices, 0x0052b378, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_55_values, 0x0052b474, 11268, 0x00000000, 11268);

