#include "pc/rom_assets.h"
static const struct Animation anim_49[] = {
    1,
    189,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(anim_49_indices),
    anim_49_values,
    anim_49_indices,
    0,
    ANIM_FIELD_LENGTH(anim_49_values),
    ANIM_FIELD_LENGTH(anim_49_indices),
};


ROM_ASSET_LOAD_ANIM(anim_49_indices, 0x00527260, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_49_values, 0x0052735c, 1298, 0x00000000, 1298);

