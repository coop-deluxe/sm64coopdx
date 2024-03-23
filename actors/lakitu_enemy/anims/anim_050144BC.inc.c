#include "pc/rom_assets.h"
// 0x050142F8
ROM_ASSET_LOAD_ANIM(lakitu_enemy_seg5_animvalue_050142F8, 0x00180bb0, 29674, 0x000142f8, 344);

// 0x05014450
ROM_ASSET_LOAD_ANIM(lakitu_enemy_seg5_animindex_05014450, 0x00180bb0, 29674, 0x00014450, 108);

// 0x050144BC
static const struct Animation lakitu_enemy_seg5_anim_050144BC = {
    0,
    0,
    0,
    0,
    0x0B,
    ANIMINDEX_NUMPARTS(lakitu_enemy_seg5_animindex_05014450),
    lakitu_enemy_seg5_animvalue_050142F8,
    lakitu_enemy_seg5_animindex_05014450,
    0,
    ANIM_FIELD_LENGTH(lakitu_enemy_seg5_animvalue_050142F8),
    ANIM_FIELD_LENGTH(lakitu_enemy_seg5_animindex_05014450),
};
