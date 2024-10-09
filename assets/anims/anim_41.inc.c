#include "pc/rom_assets.h"
static const struct Animation anim_41[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_41_indices),
    anim_41_values,
    anim_41_indices,
    0,
    ANIM_FIELD_LENGTH(anim_41_values),
    ANIM_FIELD_LENGTH(anim_41_indices),
};


ROM_ASSET_LOAD_ANIM(anim_41_indices, 0x0052462c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_41_values, 0x00524728, 536, 0x00000000, 536);

