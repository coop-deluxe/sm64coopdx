#include "pc/rom_assets.h"
static const struct Animation anim_B9[] = {
    1,
    189,
    0,
    0,
    0x19,
    ANIMINDEX_NUMPARTS(anim_B9_indices),
    anim_B9_values,
    anim_B9_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B9_values),
    ANIM_FIELD_LENGTH(anim_B9_indices),
};


ROM_ASSET_LOAD_ANIM(anim_B9_indices, 0x0056c444, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_B9_values, 0x0056c540, 2068, 0x00000000, 2068);

