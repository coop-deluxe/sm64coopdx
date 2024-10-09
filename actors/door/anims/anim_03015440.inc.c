#include "pc/rom_assets.h"
// 0x03015220
ROM_ASSET_LOAD_ANIM(door_seg3_animvalue_03015220, 0x00201410, 96653, 0x00015220, 484);

// 0x03015404
ROM_ASSET_LOAD_ANIM(door_seg3_animindex_03015404, 0x00201410, 96653, 0x00015404, 60);

// 0x03015440
static const struct Animation door_seg3_anim_03015440 = {
    1,
    0,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(door_seg3_animindex_03015404),
    door_seg3_animvalue_03015220,
    door_seg3_animindex_03015404,
    0,
    ANIM_FIELD_LENGTH(door_seg3_animvalue_03015220),
    ANIM_FIELD_LENGTH(door_seg3_animindex_03015404),
};
