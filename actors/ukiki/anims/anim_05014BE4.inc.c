#include "pc/rom_assets.h"
// 0x05012AD4
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_05012AD4, 0x001521d0, 57608, 0x00012ad4, 8176);

// 0x05014AC4
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_05014AC4, 0x001521d0, 57608, 0x00014ac4, 288);

// 0x05014BE4
static const struct Animation ukiki_seg5_anim_05014BE4 = {
    0,
    0,
    0,
    0,
    0x55,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_05014AC4),
    ukiki_seg5_animvalue_05012AD4,
    ukiki_seg5_animindex_05014AC4,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_05012AD4),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_05014AC4),
};
