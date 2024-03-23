#include "pc/rom_assets.h"
static const struct Animation anim_38[] = {
    1,
    189,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(anim_38_indices),
    anim_38_values,
    anim_38_indices,
    0,
    ANIM_FIELD_LENGTH(anim_38_values),
    ANIM_FIELD_LENGTH(anim_38_indices),
};


ROM_ASSET_LOAD_ANIM(anim_38_indices, 0x0051c32c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_38_values, 0x0051c428, 844, 0x00000000, 844);

