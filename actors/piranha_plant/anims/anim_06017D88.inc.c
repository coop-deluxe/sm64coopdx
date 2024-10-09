#include "pc/rom_assets.h"
// 0x06017C50
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_06017C50, 0x001c4230, 80474, 0x00017c50, 144);

// 0x06017CE0
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_06017CE0, 0x001c4230, 80474, 0x00017ce0, 168);

// 0x06017D88
static const struct Animation piranha_plant_seg6_anim_06017D88 = {
    0,
    0,
    0,
    0,
    0x04,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_06017CE0),
    piranha_plant_seg6_animvalue_06017C50,
    piranha_plant_seg6_animindex_06017CE0,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_06017C50),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_06017CE0),
};
