#include "pc/rom_assets.h"
// 0x05014100
ROM_ASSET_LOAD_ANIM(lakitu_enemy_seg5_animvalue_05014100, 0x00180bb0, 29674, 0x00014100, 372);

// 0x05014274
ROM_ASSET_LOAD_ANIM(lakitu_enemy_seg5_animindex_05014274, 0x00180bb0, 29674, 0x00014274, 108);

// 0x050142E0
static const struct Animation lakitu_enemy_seg5_anim_050142E0 = {
    0,
    0,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(lakitu_enemy_seg5_animindex_05014274),
    lakitu_enemy_seg5_animvalue_05014100,
    lakitu_enemy_seg5_animindex_05014274,
    0,
    ANIM_FIELD_LENGTH(lakitu_enemy_seg5_animvalue_05014100),
    ANIM_FIELD_LENGTH(lakitu_enemy_seg5_animindex_05014274),
};
