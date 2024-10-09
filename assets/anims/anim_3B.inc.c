#include "pc/rom_assets.h"
static const struct Animation anim_3B[] = {
    1,
    189,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(anim_3B_indices),
    anim_3B_values,
    anim_3B_indices,
    0,
    ANIM_FIELD_LENGTH(anim_3B_values),
    ANIM_FIELD_LENGTH(anim_3B_indices),
};


ROM_ASSET_LOAD_ANIM(anim_3B_indices, 0x0051fbb0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_3B_values, 0x0051fcac, 1204, 0x00000000, 1204);

