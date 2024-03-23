#include "pc/rom_assets.h"
static const struct Animation anim_56[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_56_57_indices),
    anim_56_57_values,
    anim_56_57_indices,
    0,
    ANIM_FIELD_LENGTH(anim_56_57_values),
    ANIM_FIELD_LENGTH(anim_56_57_indices),
};

static const struct Animation anim_57[] = {
    1,
    189,
    9,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(anim_56_57_indices),
    anim_56_57_values,
    anim_56_57_indices,
    0,
    ANIM_FIELD_LENGTH(anim_56_57_values),
    ANIM_FIELD_LENGTH(anim_56_57_indices),
};


ROM_ASSET_LOAD_ANIM(anim_56_57_indices, 0x0052e0a8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_56_57_values, 0x0052e1a4, 1560, 0x00000000, 1560);

