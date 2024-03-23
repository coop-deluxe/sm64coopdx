#include "pc/rom_assets.h"
static const struct Animation anim_7E[] = {
    0,
    189,
    0,
    0,
    0x5A,
    ANIMINDEX_NUMPARTS(anim_7E_indices),
    anim_7E_values,
    anim_7E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_7E_values),
    ANIM_FIELD_LENGTH(anim_7E_indices),
};


ROM_ASSET_LOAD_ANIM(anim_7E_indices, 0x005487cc, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_7E_values, 0x005488c8, 4538, 0x00000000, 4538);

