#include "pc/rom_assets.h"
static const struct Animation anim_17[] = {
    0,
    189,
    0,
    0,
    0x4C,
    ANIMINDEX_NUMPARTS(anim_17_indices),
    anim_17_values,
    anim_17_indices,
    0,
    ANIM_FIELD_LENGTH(anim_17_values),
    ANIM_FIELD_LENGTH(anim_17_indices),
};


ROM_ASSET_LOAD_ANIM(anim_17_indices, 0x004f8724, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_17_values, 0x004f8820, 2942, 0x00000000, 2942);

