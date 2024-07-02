#include "pc/rom_assets.h"
static const struct Animation anim_25[] = {
    65,
    189,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(anim_25_indices),
    anim_25_values,
    anim_25_indices,
    0,
    ANIM_FIELD_LENGTH(anim_25_values),
    ANIM_FIELD_LENGTH(anim_25_indices),
};


ROM_ASSET_LOAD_ANIM(anim_25_indices, 0x00505b08, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_25_values, 0x00505c04, 8018, 0x00000000, 8018);

