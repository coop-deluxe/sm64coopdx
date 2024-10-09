#include "pc/rom_assets.h"
static const struct Animation anim_88[] = {
    1,
    189,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_88_89_indices),
    anim_88_89_values,
    anim_88_89_indices,
    0,
    ANIM_FIELD_LENGTH(anim_88_89_values),
    ANIM_FIELD_LENGTH(anim_88_89_indices),
};

static const struct Animation anim_89[] = {
    1,
    189,
    20,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_88_89_indices),
    anim_88_89_values,
    anim_88_89_indices,
    0,
    ANIM_FIELD_LENGTH(anim_88_89_values),
    ANIM_FIELD_LENGTH(anim_88_89_indices),
};


ROM_ASSET_LOAD_ANIM(anim_88_89_indices, 0x00552254, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_88_89_values, 0x00552350, 1260, 0x00000000, 1260);

