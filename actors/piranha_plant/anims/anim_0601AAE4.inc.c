#include "pc/rom_assets.h"
// 0x0601A02C
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_0601A02C, 0x001c4230, 80474, 0x0001a02c, 2576);

// 0x0601AA3C
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_0601AA3C, 0x001c4230, 80474, 0x0001aa3c, 168);

// 0x0601AAE4
static const struct Animation piranha_plant_seg6_anim_0601AAE4 = {
    0,
    0,
    0,
    0,
    0x4B,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_0601AA3C),
    piranha_plant_seg6_animvalue_0601A02C,
    piranha_plant_seg6_animindex_0601AA3C,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_0601A02C),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_0601AA3C),
};
