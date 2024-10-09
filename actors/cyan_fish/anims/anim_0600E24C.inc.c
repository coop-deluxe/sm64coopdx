#include "pc/rom_assets.h"
// 0x0600E098
ROM_ASSET_LOAD_ANIM(cyan_fish_seg6_animvalue_0600E098, 0x001b9cc0, 41188, 0x0000e098, 364);

// 0x0600E204
ROM_ASSET_LOAD_ANIM(cyan_fish_seg6_animindex_0600E204, 0x001b9cc0, 41188, 0x0000e204, 72);

// 0x0600E24C
static const struct Animation cyan_fish_seg6_anim_0600E24C = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(cyan_fish_seg6_animindex_0600E204),
    cyan_fish_seg6_animvalue_0600E098,
    cyan_fish_seg6_animindex_0600E204,
    0,
    ANIM_FIELD_LENGTH(cyan_fish_seg6_animvalue_0600E098),
    ANIM_FIELD_LENGTH(cyan_fish_seg6_animindex_0600E204),
};
