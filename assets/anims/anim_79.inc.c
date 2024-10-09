#include "pc/rom_assets.h"
static const struct Animation anim_79[] = {
    1,
    189,
    0,
    0,
    0x35,
    ANIMINDEX_NUMPARTS(anim_79_indices),
    anim_79_values,
    anim_79_indices,
    0,
    ANIM_FIELD_LENGTH(anim_79_values),
    ANIM_FIELD_LENGTH(anim_79_indices),
};


ROM_ASSET_LOAD_ANIM(anim_79_indices, 0x00545c10, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_79_values, 0x00545d0c, 3634, 0x00000000, 3634);

