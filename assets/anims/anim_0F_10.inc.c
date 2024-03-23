#include "pc/rom_assets.h"
static const struct Animation anim_0F[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_0F_10_indices),
    anim_0F_10_values,
    anim_0F_10_indices,
    0,
    ANIM_FIELD_LENGTH(anim_0F_10_values),
    ANIM_FIELD_LENGTH(anim_0F_10_indices),
};

static const struct Animation anim_10[] = {
    1,
    189,
    1,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(anim_0F_10_indices),
    anim_0F_10_values,
    anim_0F_10_indices,
    0,
    ANIM_FIELD_LENGTH(anim_0F_10_values),
    ANIM_FIELD_LENGTH(anim_0F_10_indices),
};


ROM_ASSET_LOAD_ANIM(anim_0F_10_indices, 0x004f5010, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_0F_10_values, 0x004f510c, 1502, 0x00000000, 1502);

