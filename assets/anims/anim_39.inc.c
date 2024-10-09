#include "pc/rom_assets.h"
static const struct Animation anim_39[] = {
    1,
    189,
    0,
    0,
    0x9B,
    ANIMINDEX_NUMPARTS(anim_39_indices),
    anim_39_values,
    anim_39_indices,
    0,
    ANIM_FIELD_LENGTH(anim_39_values),
    ANIM_FIELD_LENGTH(anim_39_indices),
};


ROM_ASSET_LOAD_ANIM(anim_39_indices, 0x0051c78c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_39_values, 0x0051c888, 12418, 0x00000000, 12418);

