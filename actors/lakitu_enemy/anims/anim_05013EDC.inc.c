#include "pc/rom_assets.h"
// 0x050138C0
ROM_ASSET_LOAD_ANIM(lakitu_enemy_seg5_animvalue_050138C0, 0x00180bb0, 29674, 0x000138c0, 1456);

// 0x05013E70
ROM_ASSET_LOAD_ANIM(lakitu_enemy_seg5_animindex_05013E70, 0x00180bb0, 29674, 0x00013e70, 108);

// 0x05013EDC
static const struct Animation lakitu_enemy_seg5_anim_05013EDC = {
    0,
    0,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(lakitu_enemy_seg5_animindex_05013E70),
    lakitu_enemy_seg5_animvalue_050138C0,
    lakitu_enemy_seg5_animindex_05013E70,
    0,
    ANIM_FIELD_LENGTH(lakitu_enemy_seg5_animvalue_050138C0),
    ANIM_FIELD_LENGTH(lakitu_enemy_seg5_animindex_05013E70),
};
