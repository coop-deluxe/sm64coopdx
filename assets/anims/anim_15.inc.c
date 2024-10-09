#include "pc/rom_assets.h"
static const struct Animation anim_15[] = {
    0,
    189,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(anim_15_indices),
    anim_15_values,
    anim_15_indices,
    0,
    ANIM_FIELD_LENGTH(anim_15_values),
    ANIM_FIELD_LENGTH(anim_15_indices),
};


ROM_ASSET_LOAD_ANIM(anim_15_indices, 0x004f6ff4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_15_values, 0x004f70f0, 930, 0x00000000, 930);

