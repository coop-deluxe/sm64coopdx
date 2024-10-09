#include "pc/rom_assets.h"
static const struct Animation anim_BB[] = {
    0,
    189,
    0,
    0,
    0x61,
    ANIMINDEX_NUMPARTS(anim_BB_indices),
    anim_BB_values,
    anim_BB_indices,
    0,
    ANIM_FIELD_LENGTH(anim_BB_values),
    ANIM_FIELD_LENGTH(anim_BB_indices),
};


ROM_ASSET_LOAD_ANIM(anim_BB_indices, 0x0056d25c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_BB_values, 0x0056d358, 4132, 0x00000000, 4132);

