#include "pc/rom_assets.h"
// 0x050054C8
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animvalue_050054C8, 0x001521d0, 57608, 0x000054c8, 3380);

// 0x050061FC
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animindex_050061FC, 0x001521d0, 57608, 0x000061fc, 180);

// 0x050062B0
static const struct Animation monty_mole_seg5_anim_050062B0 = {
    0,
    0,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(monty_mole_seg5_animindex_050061FC),
    monty_mole_seg5_animvalue_050054C8,
    monty_mole_seg5_animindex_050061FC,
    0,
    ANIM_FIELD_LENGTH(monty_mole_seg5_animvalue_050054C8),
    ANIM_FIELD_LENGTH(monty_mole_seg5_animindex_050061FC),
};
