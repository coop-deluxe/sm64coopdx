#include "pc/rom_assets.h"
// 0x0500CD58
ROM_ASSET_LOAD_ANIM(snowman_seg5_animvalue_0500CD58, 0x00160670, 20585, 0x0000cd58, 264);

// 0x0500CE60
ROM_ASSET_LOAD_ANIM(snowman_seg5_animindex_0500CE60, 0x00160670, 20585, 0x0000ce60, 120);

// 0x0500CED8
static const struct Animation snowman_seg5_anim_0500CED8 = {
    1,
    0,
    0,
    0,
    0x0E,
    ANIMINDEX_NUMPARTS(snowman_seg5_animindex_0500CE60),
    snowman_seg5_animvalue_0500CD58,
    snowman_seg5_animindex_0500CE60,
    0,
    ANIM_FIELD_LENGTH(snowman_seg5_animvalue_0500CD58),
    ANIM_FIELD_LENGTH(snowman_seg5_animindex_0500CE60),
};
