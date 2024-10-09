#include "pc/rom_assets.h"
static const struct Animation anim_80[] = {
    0,
    189,
    0,
    0,
    0x40,
    ANIMINDEX_NUMPARTS(anim_80_indices),
    anim_80_values,
    anim_80_indices,
    0,
    ANIM_FIELD_LENGTH(anim_80_values),
    ANIM_FIELD_LENGTH(anim_80_indices),
};


ROM_ASSET_LOAD_ANIM(anim_80_indices, 0x0054a9d8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_80_values, 0x0054aad4, 4248, 0x00000000, 4248);

