#include "pc/rom_assets.h"
// 0x0601AAFC
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_0601AAFC, 0x001c4230, 80474, 0x0001aafc, 912);

// 0x0601AE8C
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_0601AE8C, 0x001c4230, 80474, 0x0001ae8c, 168);

// 0x0601AF34
static const struct Animation piranha_plant_seg6_anim_0601AF34 = {
    0,
    0,
    0,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_0601AE8C),
    piranha_plant_seg6_animvalue_0601AAFC,
    piranha_plant_seg6_animindex_0601AE8C,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_0601AAFC),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_0601AE8C),
};
