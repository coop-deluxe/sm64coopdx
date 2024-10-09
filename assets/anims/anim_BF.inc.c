#include "pc/rom_assets.h"
static const struct Animation anim_BF[] = {
    1,
    189,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(anim_BF_indices),
    anim_BF_values,
    anim_BF_indices,
    0,
    ANIM_FIELD_LENGTH(anim_BF_values),
    ANIM_FIELD_LENGTH(anim_BF_indices),
};


ROM_ASSET_LOAD_ANIM(anim_BF_indices, 0x0056eec4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_BF_values, 0x0056efc0, 1936, 0x00000000, 1936);

