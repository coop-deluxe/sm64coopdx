#include "pc/rom_assets.h"
static const struct Animation anim_85[] = {
    0,
    189,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(anim_85_indices),
    anim_85_values,
    anim_85_indices,
    0,
    ANIM_FIELD_LENGTH(anim_85_values),
    ANIM_FIELD_LENGTH(anim_85_indices),
};


ROM_ASSET_LOAD_ANIM(anim_85_indices, 0x00550c48, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_85_values, 0x00550d44, 324, 0x00000000, 324);

