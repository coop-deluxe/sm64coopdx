#include "pc/rom_assets.h"
// 0x05006DD0
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animvalue_05006DD0, 0x001521d0, 57608, 0x00006dd0, 940);

// 0x0500717C
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animindex_0500717C, 0x001521d0, 57608, 0x0000717c, 180);

// 0x05007230
static const struct Animation monty_mole_seg5_anim_05007230 = {
    0,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(monty_mole_seg5_animindex_0500717C),
    monty_mole_seg5_animvalue_05006DD0,
    monty_mole_seg5_animindex_0500717C,
    0,
    ANIM_FIELD_LENGTH(monty_mole_seg5_animvalue_05006DD0),
    ANIM_FIELD_LENGTH(monty_mole_seg5_animindex_0500717C),
};
