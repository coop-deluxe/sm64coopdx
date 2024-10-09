#include "pc/rom_assets.h"
// 0x06016F80
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_06016F80, 0x001c4230, 80474, 0x00016f80, 3088);

// 0x06017B90
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_06017B90, 0x001c4230, 80474, 0x00017b90, 168);

// 0x06017C38
static const struct Animation piranha_plant_seg6_anim_06017C38 = {
    0,
    0,
    0,
    0,
    0x5A,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_06017B90),
    piranha_plant_seg6_animvalue_06016F80,
    piranha_plant_seg6_animindex_06017B90,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_06016F80),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_06017B90),
};
