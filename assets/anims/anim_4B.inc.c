#include "pc/rom_assets.h"
static const struct Animation anim_4B[] = {
    1,
    189,
    0,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(anim_4B_indices),
    anim_4B_values,
    anim_4B_indices,
    0,
    ANIM_FIELD_LENGTH(anim_4B_values),
    ANIM_FIELD_LENGTH(anim_4B_indices),
};


ROM_ASSET_LOAD_ANIM(anim_4B_indices, 0x00527c04, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_4B_values, 0x00527d00, 1386, 0x00000000, 1386);

