#include "pc/rom_assets.h"
static const struct Animation anim_23[] = {
    1,
    189,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(anim_23_indices),
    anim_23_values,
    anim_23_indices,
    0,
    ANIM_FIELD_LENGTH(anim_23_values),
    ANIM_FIELD_LENGTH(anim_23_indices),
};


ROM_ASSET_LOAD_ANIM(anim_23_indices, 0x00501428, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_23_values, 0x00501524, 8216, 0x00000000, 8216);

