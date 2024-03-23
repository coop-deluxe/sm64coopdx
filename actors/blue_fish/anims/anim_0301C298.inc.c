#include "pc/rom_assets.h"
// 0x0301C1B0
ROM_ASSET_LOAD_ANIM(blue_fish_seg3_animvalue_0301C1B0, 0x00201410, 96653, 0x0001c1b0, 184);

// 0x0301C268
ROM_ASSET_LOAD_ANIM(blue_fish_seg3_animindex_0301C268, 0x00201410, 96653, 0x0001c268, 48);

// 0x0301C298
static const struct Animation blue_fish_seg3_anim_0301C298 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(blue_fish_seg3_animindex_0301C268),
    blue_fish_seg3_animvalue_0301C1B0,
    blue_fish_seg3_animindex_0301C268,
    0,
    ANIM_FIELD_LENGTH(blue_fish_seg3_animvalue_0301C1B0),
    ANIM_FIELD_LENGTH(blue_fish_seg3_animindex_0301C268),
};
