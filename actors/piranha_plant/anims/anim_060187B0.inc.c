#include "pc/rom_assets.h"
// 0x06017DA0
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_06017DA0, 0x001c4230, 80474, 0x00017da0, 2408);

// 0x06018708
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_06018708, 0x001c4230, 80474, 0x00018708, 168);

// 0x060187B0
static const struct Animation piranha_plant_seg6_anim_060187B0 = {
    1,
    0,
    0,
    0,
    0x46,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_06018708),
    piranha_plant_seg6_animvalue_06017DA0,
    piranha_plant_seg6_animindex_06018708,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_06017DA0),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_06018708),
};
