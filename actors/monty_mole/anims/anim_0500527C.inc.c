#include "pc/rom_assets.h"
// 0x05005004
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animvalue_05005004, 0x001521d0, 57608, 0x00005004, 452);

// 0x050051C8
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animindex_050051C8, 0x001521d0, 57608, 0x000051c8, 180);

// 0x0500527C
static const struct Animation monty_mole_seg5_anim_0500527C = {
    0,
    0,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(monty_mole_seg5_animindex_050051C8),
    monty_mole_seg5_animvalue_05005004,
    monty_mole_seg5_animindex_050051C8,
    0,
    ANIM_FIELD_LENGTH(monty_mole_seg5_animvalue_05005004),
    ANIM_FIELD_LENGTH(monty_mole_seg5_animindex_050051C8),
};
