#include "pc/rom_assets.h"
static const struct Animation anim_C9[] = {
    1,
    189,
    0,
    0,
    0x15,
    ANIMINDEX_NUMPARTS(anim_C9_indices),
    anim_C9_values,
    anim_C9_indices,
    0,
    ANIM_FIELD_LENGTH(anim_C9_values),
    ANIM_FIELD_LENGTH(anim_C9_indices),
};


ROM_ASSET_LOAD_ANIM(anim_C9_indices, 0x0057585c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_C9_values, 0x00575958, 1940, 0x00000000, 1940);

