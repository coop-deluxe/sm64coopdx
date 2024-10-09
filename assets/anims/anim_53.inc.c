#include "pc/rom_assets.h"
static const struct Animation anim_53[] = {
    1,
    189,
    0,
    0,
    0x19,
    ANIMINDEX_NUMPARTS(anim_53_indices),
    anim_53_values,
    anim_53_indices,
    0,
    ANIM_FIELD_LENGTH(anim_53_values),
    ANIM_FIELD_LENGTH(anim_53_indices),
};


ROM_ASSET_LOAD_ANIM(anim_53_indices, 0x0052a478, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_53_values, 0x0052a574, 1970, 0x00000000, 1970);

