#include "pc/rom_assets.h"
static const struct Animation anim_0A[] = {
    1,
    189,
    0,
    0,
    0x24,
    ANIMINDEX_NUMPARTS(anim_0A_indices),
    anim_0A_values,
    anim_0A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_0A_values),
    ANIM_FIELD_LENGTH(anim_0A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_0A_indices, 0x004f3908, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_0A_values, 0x004f3a04, 2544, 0x00000000, 2544);

