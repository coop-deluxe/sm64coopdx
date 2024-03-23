#include "pc/rom_assets.h"
// 0x06018BC0
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_06018BC0, 0x001c4230, 80474, 0x00018bc0, 3052);

// 0x060197AC
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_060197AC, 0x001c4230, 80474, 0x000197ac, 168);

// 0x06019854
static const struct Animation piranha_plant_seg6_anim_06019854 = {
    0,
    0,
    0,
    0,
    0x48,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_060197AC),
    piranha_plant_seg6_animvalue_06018BC0,
    piranha_plant_seg6_animindex_060197AC,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_06018BC0),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_060197AC),
};
