#include "pc/rom_assets.h"
static const struct Animation anim_61[] = {
    9,
    189,
    0,
    0,
    0x93,
    ANIMINDEX_NUMPARTS(anim_61_indices),
    anim_61_values,
    anim_61_indices,
    0,
    ANIM_FIELD_LENGTH(anim_61_values),
    ANIM_FIELD_LENGTH(anim_61_indices),
};


ROM_ASSET_LOAD_ANIM(anim_61_indices, 0x00536d7c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_61_values, 0x00536e78, 12660, 0x00000000, 12660);

