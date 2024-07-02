#include "pc/rom_assets.h"
static const struct Animation anim_7D[] = {
    0,
    189,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(anim_7D_indices),
    anim_7D_values,
    anim_7D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_7D_values),
    ANIM_FIELD_LENGTH(anim_7D_indices),
};


ROM_ASSET_LOAD_ANIM(anim_7D_indices, 0x0054825c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_7D_values, 0x00548358, 1114, 0x00000000, 1114);

