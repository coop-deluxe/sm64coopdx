#include "pc/rom_assets.h"
static const struct Animation anim_A2[] = {
    1,
    189,
    0,
    0,
    0x17,
    ANIMINDEX_NUMPARTS(anim_A2_indices),
    anim_A2_values,
    anim_A2_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A2_values),
    ANIM_FIELD_LENGTH(anim_A2_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A2_indices, 0x0055e628, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A2_values, 0x0055e724, 1448, 0x00000000, 1448);

