#include "pc/rom_assets.h"
static const struct Animation anim_42[] = {
    1,
    189,
    2,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(anim_42_indices),
    anim_42_values,
    anim_42_indices,
    0,
    ANIM_FIELD_LENGTH(anim_42_values),
    ANIM_FIELD_LENGTH(anim_42_indices),
};


ROM_ASSET_LOAD_ANIM(anim_42_indices, 0x00524958, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_42_values, 0x00524a54, 956, 0x00000000, 956);

