#include "pc/rom_assets.h"
static const struct Animation anim_92[] = {
    0,
    189,
    27,
    0,
    0x74,
    ANIMINDEX_NUMPARTS(anim_92_indices),
    anim_92_values,
    anim_92_indices,
    0,
    ANIM_FIELD_LENGTH(anim_92_values),
    ANIM_FIELD_LENGTH(anim_92_indices),
};


ROM_ASSET_LOAD_ANIM(anim_92_indices, 0x00555954, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_92_values, 0x00555a50, 5600, 0x00000000, 5600);

