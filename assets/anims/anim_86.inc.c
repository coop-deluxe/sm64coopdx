#include "pc/rom_assets.h"
static const struct Animation anim_86[] = {
    1,
    189,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(anim_86_indices),
    anim_86_values,
    anim_86_indices,
    0,
    ANIM_FIELD_LENGTH(anim_86_values),
    ANIM_FIELD_LENGTH(anim_86_indices),
};


ROM_ASSET_LOAD_ANIM(anim_86_indices, 0x00550ea0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_86_values, 0x00550f9c, 2902, 0x00000000, 2902);

