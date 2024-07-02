#include "pc/rom_assets.h"
static const struct Animation anim_5C[] = {
    1,
    189,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_5C_indices),
    anim_5C_values,
    anim_5C_indices,
    0,
    ANIM_FIELD_LENGTH(anim_5C_values),
    ANIM_FIELD_LENGTH(anim_5C_indices),
};


ROM_ASSET_LOAD_ANIM(anim_5C_indices, 0x00530bec, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_5C_values, 0x00530ce8, 1258, 0x00000000, 1258);

