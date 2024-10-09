#include "pc/rom_assets.h"
static const struct Animation anim_87[] = {
    0,
    189,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(anim_87_indices),
    anim_87_values,
    anim_87_indices,
    0,
    ANIM_FIELD_LENGTH(anim_87_values),
    ANIM_FIELD_LENGTH(anim_87_indices),
};


ROM_ASSET_LOAD_ANIM(anim_87_indices, 0x00551b0c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_87_values, 0x00551c08, 1564, 0x00000000, 1564);

