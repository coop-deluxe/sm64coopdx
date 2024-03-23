#include "pc/rom_assets.h"
static const struct Animation anim_CF[] = {
    1,
    189,
    0,
    0,
    0x2A,
    ANIMINDEX_NUMPARTS(anim_CF_indices),
    anim_CF_values,
    anim_CF_indices,
    0,
    ANIM_FIELD_LENGTH(anim_CF_values),
    ANIM_FIELD_LENGTH(anim_CF_indices),
};


ROM_ASSET_LOAD_ANIM(anim_CF_indices, 0x00578c98, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_CF_values, 0x00578d94, 2708, 0x00000000, 2708);

