#include "pc/rom_assets.h"
// 0x05013EF4
ROM_ASSET_LOAD_ANIM(lakitu_enemy_seg5_animvalue_05013EF4, 0x00180bb0, 29674, 0x00013ef4, 392);

// 0x0501407C
ROM_ASSET_LOAD_ANIM(lakitu_enemy_seg5_animindex_0501407C, 0x00180bb0, 29674, 0x0001407c, 108);

// 0x050140E8
static const struct Animation lakitu_enemy_seg5_anim_050140E8 = {
    0,
    0,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(lakitu_enemy_seg5_animindex_0501407C),
    lakitu_enemy_seg5_animvalue_05013EF4,
    lakitu_enemy_seg5_animindex_0501407C,
    0,
    ANIM_FIELD_LENGTH(lakitu_enemy_seg5_animvalue_05013EF4),
    ANIM_FIELD_LENGTH(lakitu_enemy_seg5_animindex_0501407C),
};
