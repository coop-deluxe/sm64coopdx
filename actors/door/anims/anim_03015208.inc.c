#include "pc/rom_assets.h"
// 0x030151C8
ROM_ASSET_LOAD_ANIM(door_seg3_animvalue_030151C8, 0x001c4230, 80474, 0x000071fe, 4);

// 0x030151CC
ROM_ASSET_LOAD_ANIM(door_seg3_animindex_030151CC, 0x00201410, 96653, 0x000151cc, 60);

// 0x03015208
static const struct Animation door_seg3_anim_03015208 = {
    0,
    0,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(door_seg3_animindex_030151CC),
    door_seg3_animvalue_030151C8,
    door_seg3_animindex_030151CC,
    0,
    ANIM_FIELD_LENGTH(door_seg3_animvalue_030151C8),
    ANIM_FIELD_LENGTH(door_seg3_animindex_030151CC),
};
