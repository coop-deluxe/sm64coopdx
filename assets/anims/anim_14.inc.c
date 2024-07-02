#include "pc/rom_assets.h"
static const struct Animation anim_14[] = {
    1,
    189,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(anim_14_indices),
    anim_14_values,
    anim_14_indices,
    0,
    ANIM_FIELD_LENGTH(anim_14_values),
    ANIM_FIELD_LENGTH(anim_14_indices),
};


ROM_ASSET_LOAD_ANIM(anim_14_indices, 0x004f6a90, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_14_values, 0x004f6b8c, 1102, 0x00000000, 1102);

