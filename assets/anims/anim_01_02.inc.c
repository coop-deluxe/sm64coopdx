#include "pc/rom_assets.h"
static const struct Animation anim_01[] = {
    1,
    189,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(anim_01_02_indices),
    anim_01_02_values,
    anim_01_02_indices,
    0,
    ANIM_FIELD_LENGTH(anim_01_02_values),
    ANIM_FIELD_LENGTH(anim_01_02_indices),
};

static const struct Animation anim_02[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_01_02_indices),
    anim_01_02_values,
    anim_01_02_indices,
    0,
    ANIM_FIELD_LENGTH(anim_01_02_values),
    ANIM_FIELD_LENGTH(anim_01_02_indices),
};


ROM_ASSET_LOAD_ANIM(anim_01_02_indices, 0x004ed200, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_01_02_values, 0x004ed2fc, 6576, 0x00000000, 6576);

