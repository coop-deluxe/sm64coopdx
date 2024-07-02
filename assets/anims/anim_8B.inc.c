#include "pc/rom_assets.h"
static const struct Animation anim_8B[] = {
    1,
    189,
    0,
    0,
    0x25,
    ANIMINDEX_NUMPARTS(anim_8B_indices),
    anim_8B_values,
    anim_8B_indices,
    0,
    ANIM_FIELD_LENGTH(anim_8B_values),
    ANIM_FIELD_LENGTH(anim_8B_indices),
};


ROM_ASSET_LOAD_ANIM(anim_8B_indices, 0x0055350c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_8B_values, 0x00553608, 2970, 0x00000000, 2970);

