#include "pc/rom_assets.h"
static const struct Animation anim_83[] = {
    1,
    189,
    0,
    0,
    0x3B,
    ANIMINDEX_NUMPARTS(anim_83_indices),
    anim_83_values,
    anim_83_indices,
    0,
    ANIM_FIELD_LENGTH(anim_83_values),
    ANIM_FIELD_LENGTH(anim_83_indices),
};


ROM_ASSET_LOAD_ANIM(anim_83_indices, 0x0054e50c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_83_values, 0x0054e608, 4734, 0x00000000, 4734);

