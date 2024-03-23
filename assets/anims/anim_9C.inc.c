#include "pc/rom_assets.h"
static const struct Animation anim_9C[] = {
    9,
    189,
    0,
    0,
    0x40,
    ANIMINDEX_NUMPARTS(anim_9C_indices),
    anim_9C_values,
    anim_9C_indices,
    0,
    ANIM_FIELD_LENGTH(anim_9C_values),
    ANIM_FIELD_LENGTH(anim_9C_indices),
};


ROM_ASSET_LOAD_ANIM(anim_9C_indices, 0x0055ad34, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_9C_values, 0x0055ae30, 4884, 0x00000000, 4884);

