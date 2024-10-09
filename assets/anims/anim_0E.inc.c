#include "pc/rom_assets.h"
static const struct Animation anim_0E[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_0E_indices),
    anim_0E_values,
    anim_0E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_0E_values),
    ANIM_FIELD_LENGTH(anim_0E_indices),
};


ROM_ASSET_LOAD_ANIM(anim_0E_indices, 0x004f4e94, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_0E_values, 0x004f4f90, 80, 0x00000000, 80);

