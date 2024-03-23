#include "pc/rom_assets.h"
static const struct Animation anim_45[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_45_46_indices),
    anim_45_46_values,
    anim_45_46_indices,
    0,
    ANIM_FIELD_LENGTH(anim_45_46_values),
    ANIM_FIELD_LENGTH(anim_45_46_indices),
};

static const struct Animation anim_46[] = {
    1,
    189,
    1,
    0,
    0x0E,
    ANIMINDEX_NUMPARTS(anim_45_46_indices),
    anim_45_46_values,
    anim_45_46_indices,
    0,
    ANIM_FIELD_LENGTH(anim_45_46_values),
    ANIM_FIELD_LENGTH(anim_45_46_indices),
};


ROM_ASSET_LOAD_ANIM(anim_45_46_indices, 0x00525348, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_45_46_values, 0x00525444, 1190, 0x00000000, 1190);

