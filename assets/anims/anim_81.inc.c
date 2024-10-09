#include "pc/rom_assets.h"
static const struct Animation anim_81[] = {
    1,
    189,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(anim_81_indices),
    anim_81_values,
    anim_81_indices,
    0,
    ANIM_FIELD_LENGTH(anim_81_values),
    ANIM_FIELD_LENGTH(anim_81_indices),
};


ROM_ASSET_LOAD_ANIM(anim_81_indices, 0x0054bb84, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_81_values, 0x0054bc80, 4308, 0x00000000, 4308);

