#include "pc/rom_assets.h"
// 0x03015470
ROM_ASSET_LOAD_ANIM(door_seg3_animvalue_03015470, 0x00201410, 96653, 0x00015470, 484);

// 0x03015654
ROM_ASSET_LOAD_ANIM(door_seg3_animindex_03015654, 0x00201410, 96653, 0x00015404, 60);

// 0x03015690
static const struct Animation door_seg3_anim_03015690 = {
    0,
    0,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(door_seg3_animindex_03015654),
    door_seg3_animvalue_03015470,
    door_seg3_animindex_03015654,
    0,
    ANIM_FIELD_LENGTH(door_seg3_animvalue_03015470),
    ANIM_FIELD_LENGTH(door_seg3_animindex_03015654),
};
