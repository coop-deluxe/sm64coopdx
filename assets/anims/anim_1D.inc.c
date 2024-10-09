#include "pc/rom_assets.h"
static const struct Animation anim_1D[] = {
    0,
    189,
    0,
    0,
    0x23,
    ANIMINDEX_NUMPARTS(anim_1D_indices),
    anim_1D_values,
    anim_1D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_1D_values),
    ANIM_FIELD_LENGTH(anim_1D_indices),
};


ROM_ASSET_LOAD_ANIM(anim_1D_indices, 0x004fd220, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_1D_values, 0x004fd31c, 1380, 0x00000000, 1380);

