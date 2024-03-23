#include "pc/rom_assets.h"
static const struct Animation anim_50[] = {
    1,
    189,
    0,
    0,
    0x06,
    ANIMINDEX_NUMPARTS(anim_50_indices),
    anim_50_values,
    anim_50_indices,
    0,
    ANIM_FIELD_LENGTH(anim_50_values),
    ANIM_FIELD_LENGTH(anim_50_indices),
};


ROM_ASSET_LOAD_ANIM(anim_50_indices, 0x0052983c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_50_values, 0x00529938, 420, 0x00000000, 420);

