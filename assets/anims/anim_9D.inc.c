#include "pc/rom_assets.h"
static const struct Animation anim_9D[] = {
    9,
    189,
    0,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(anim_9D_indices),
    anim_9D_values,
    anim_9D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_9D_values),
    ANIM_FIELD_LENGTH(anim_9D_indices),
};


ROM_ASSET_LOAD_ANIM(anim_9D_indices, 0x0055c15c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_9D_values, 0x0055c258, 1944, 0x00000000, 1944);

