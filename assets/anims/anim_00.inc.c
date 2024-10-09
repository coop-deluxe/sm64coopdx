#include "pc/rom_assets.h"
static const struct Animation anim_00[] = {
    1,
    189,
    0,
    0,
    0x22,
    ANIMINDEX_NUMPARTS(anim_00_indices),
    anim_00_values,
    anim_00_indices,
    0,
    ANIM_FIELD_LENGTH(anim_00_values),
    ANIM_FIELD_LENGTH(anim_00_indices),
};


ROM_ASSET_LOAD_ANIM(anim_00_indices, 0x004ec6a8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_00_values, 0x004ec7a4, 2604, 0x00000000, 2604);

