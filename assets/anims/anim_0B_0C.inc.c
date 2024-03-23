#include "pc/rom_assets.h"
static const struct Animation anim_0B[] = {
    17,
    189,
    0,
    0,
    0x11,
    ANIMINDEX_NUMPARTS(anim_0B_0C_indices),
    anim_0B_0C_values,
    anim_0B_0C_indices,
    0,
    ANIM_FIELD_LENGTH(anim_0B_0C_values),
    ANIM_FIELD_LENGTH(anim_0B_0C_indices),
};

static const struct Animation anim_0C[] = {
    19,
    189,
    16,
    0,
    0x11,
    ANIMINDEX_NUMPARTS(anim_0B_0C_indices),
    anim_0B_0C_values,
    anim_0B_0C_indices,
    0,
    ANIM_FIELD_LENGTH(anim_0B_0C_values),
    ANIM_FIELD_LENGTH(anim_0B_0C_indices),
};


ROM_ASSET_LOAD_ANIM(anim_0B_0C_indices, 0x004f4424, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_0B_0C_values, 0x004f4520, 1348, 0x00000000, 1348);

