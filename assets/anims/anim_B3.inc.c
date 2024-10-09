#include "pc/rom_assets.h"
static const struct Animation anim_B3[] = {
    1,
    189,
    0,
    0,
    0x53,
    ANIMINDEX_NUMPARTS(anim_B3_indices),
    anim_B3_values,
    anim_B3_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B3_values),
    ANIM_FIELD_LENGTH(anim_B3_indices),
};


ROM_ASSET_LOAD_ANIM(anim_B3_indices, 0x00568a1c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_B3_values, 0x00568b18, 6494, 0x00000000, 6494);

