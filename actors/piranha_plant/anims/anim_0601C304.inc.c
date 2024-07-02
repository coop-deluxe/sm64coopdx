#include "pc/rom_assets.h"
// 0x0601B64C
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_0601B64C, 0x001c4230, 80474, 0x0001b64c, 3088);

// 0x0601C25C
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_0601C25C, 0x001c4230, 80474, 0x00017b90, 168);

// 0x0601C304
static const struct Animation piranha_plant_seg6_anim_0601C304 = {
    0,
    0,
    0,
    0,
    0x5A,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_0601C25C),
    piranha_plant_seg6_animvalue_0601B64C,
    piranha_plant_seg6_animindex_0601C25C,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_0601B64C),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_0601C25C),
};
