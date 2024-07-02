#include "pc/rom_assets.h"
static const struct Animation anim_C0[] = {
    1,
    189,
    0,
    0,
    0x20,
    ANIMINDEX_NUMPARTS(anim_C0_indices),
    anim_C0_values,
    anim_C0_indices,
    0,
    ANIM_FIELD_LENGTH(anim_C0_values),
    ANIM_FIELD_LENGTH(anim_C0_indices),
};


ROM_ASSET_LOAD_ANIM(anim_C0_indices, 0x0056f768, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_C0_values, 0x0056f864, 2452, 0x00000000, 2452);

