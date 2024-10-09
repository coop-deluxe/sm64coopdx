#include "pc/rom_assets.h"
static const struct Animation anim_3C[] = {
    1,
    189,
    0,
    0,
    0x0B,
    ANIMINDEX_NUMPARTS(anim_3C_3D_indices),
    anim_3C_3D_values,
    anim_3C_3D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_3C_3D_values),
    ANIM_FIELD_LENGTH(anim_3C_3D_indices),
};

static const struct Animation anim_3D[] = {
    1,
    189,
    10,
    0,
    0x0B,
    ANIMINDEX_NUMPARTS(anim_3C_3D_indices),
    anim_3C_3D_values,
    anim_3C_3D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_3C_3D_values),
    ANIM_FIELD_LENGTH(anim_3C_3D_indices),
};


ROM_ASSET_LOAD_ANIM(anim_3C_3D_indices, 0x00520190, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_3C_3D_values, 0x0052028c, 774, 0x00000000, 774);

