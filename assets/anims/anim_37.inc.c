#include "pc/rom_assets.h"
static const struct Animation anim_37[] = {
    1,
    189,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(anim_37_indices),
    anim_37_values,
    anim_37_indices,
    0,
    ANIM_FIELD_LENGTH(anim_37_values),
    ANIM_FIELD_LENGTH(anim_37_indices),
};


ROM_ASSET_LOAD_ANIM(anim_37_indices, 0x0051a76c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_37_values, 0x0051a868, 6828, 0x00000000, 6828);

