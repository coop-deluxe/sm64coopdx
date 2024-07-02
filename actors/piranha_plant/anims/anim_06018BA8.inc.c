#include "pc/rom_assets.h"
// 0x060187C8
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animvalue_060187C8, 0x001c4230, 80474, 0x000187c8, 824);

// 0x06018B00
ROM_ASSET_LOAD_ANIM(piranha_plant_seg6_animindex_06018B00, 0x001c4230, 80474, 0x00018b00, 168);

// 0x06018BA8
static const struct Animation piranha_plant_seg6_anim_06018BA8 = {
    0,
    0,
    0,
    0,
    0x13,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_06018B00),
    piranha_plant_seg6_animvalue_060187C8,
    piranha_plant_seg6_animindex_06018B00,
    0,
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animvalue_060187C8),
    ANIM_FIELD_LENGTH(piranha_plant_seg6_animindex_06018B00),
};
