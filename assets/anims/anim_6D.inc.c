#include "pc/rom_assets.h"
static const struct Animation anim_6D[] = {
    1,
    189,
    0,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(anim_6D_indices),
    anim_6D_values,
    anim_6D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_6D_values),
    ANIM_FIELD_LENGTH(anim_6D_indices),
};


ROM_ASSET_LOAD_ANIM(anim_6D_indices, 0x0053daec, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_6D_values, 0x0053dbe8, 1286, 0x00000000, 1286);

