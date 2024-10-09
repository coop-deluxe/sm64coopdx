#include "pc/rom_assets.h"
// 0x050062C8
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animvalue_050062C8, 0x001521d0, 57608, 0x000062c8, 580);

// 0x0500650C
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animindex_0500650C, 0x001521d0, 57608, 0x0000650c, 180);

// 0x050065C0
static const struct Animation monty_mole_seg5_anim_050065C0 = {
    0,
    0,
    1,
    1,
    0x0E,
    ANIMINDEX_NUMPARTS(monty_mole_seg5_animindex_0500650C),
    monty_mole_seg5_animvalue_050062C8,
    monty_mole_seg5_animindex_0500650C,
    0,
    ANIM_FIELD_LENGTH(monty_mole_seg5_animvalue_050062C8),
    ANIM_FIELD_LENGTH(monty_mole_seg5_animindex_0500650C),
};
