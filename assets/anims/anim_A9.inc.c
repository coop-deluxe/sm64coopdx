#include "pc/rom_assets.h"
static const struct Animation anim_A9[] = {
    1,
    189,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_A9_indices),
    anim_A9_values,
    anim_A9_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A9_values),
    ANIM_FIELD_LENGTH(anim_A9_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A9_indices, 0x00564570, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A9_values, 0x0056466c, 1728, 0x00000000, 1728);

