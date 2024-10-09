#include "pc/rom_assets.h"
// 0x05010084
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_05010084, 0x001521d0, 57608, 0x00010084, 592);

// 0x050102D4
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_050102D4, 0x001521d0, 57608, 0x000102d4, 288);

// 0x050103F4
static const struct Animation ukiki_seg5_anim_050103F4 = {
    1,
    0,
    0,
    0,
    0x07,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_050102D4),
    ukiki_seg5_animvalue_05010084,
    ukiki_seg5_animindex_050102D4,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_05010084),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_050102D4),
};
