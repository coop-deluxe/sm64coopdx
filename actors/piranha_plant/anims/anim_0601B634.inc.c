#include "pc/rom_assets.h"
// 0x0601AF4C
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_0601AF4C, 0x001c4230, 80474, 0x0001af4c, 1600);

// 0x0601B58C
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_0601B58C, 0x001c4230, 80474, 0x0001b58c, 168);

// 0x0601B634
static const struct Animation piranha_plant_seg6_anim_0601B634 = {
    0,
    0,
    0,
    0,
    0x38,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_0601B58C),
    piranha_plant_seg6_animvalue_0601AF4C,
    piranha_plant_seg6_animindex_0601B58C,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_0601AF4C),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_0601B58C),
};
