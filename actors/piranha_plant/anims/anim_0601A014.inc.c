#include "pc/rom_assets.h"
// 0x0601986C
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_0601986C, 0x001c4230, 80474, 0x0001986c, 1792);

// 0x06019F6C
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_06019F6C, 0x001c4230, 80474, 0x00019f6c, 168);

// 0x0601A014
static const struct Animation piranha_plant_seg6_anim_0601A014 = {
    0,
    0,
    0,
    0,
    0x2A,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_06019F6C),
    piranha_plant_seg6_animvalue_0601986C,
    piranha_plant_seg6_animindex_06019F6C,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_0601986C),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_06019F6C),
};
