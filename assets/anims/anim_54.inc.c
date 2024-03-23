#include "pc/rom_assets.h"
static const struct Animation anim_54[] = {
    1,
    189,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_54_indices),
    anim_54_values,
    anim_54_indices,
    0,
    ANIM_FIELD_LENGTH(anim_54_values),
    ANIM_FIELD_LENGTH(anim_54_indices),
};


ROM_ASSET_LOAD_ANIM(anim_54_indices, 0x0052ad40, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_54_values, 0x0052ae3c, 1314, 0x00000000, 1314);

