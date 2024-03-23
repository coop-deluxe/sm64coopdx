#include "pc/rom_assets.h"
static const struct Animation anim_58[] = {
    0,
    189,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_58_indices),
    anim_58_values,
    anim_58_indices,
    0,
    ANIM_FIELD_LENGTH(anim_58_values),
    ANIM_FIELD_LENGTH(anim_58_indices),
};


ROM_ASSET_LOAD_ANIM(anim_58_indices, 0x0052e7d4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_58_values, 0x0052e8d0, 1082, 0x00000000, 1082);

