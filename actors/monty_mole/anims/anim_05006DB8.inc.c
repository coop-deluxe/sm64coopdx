#include "pc/rom_assets.h"
// 0x05006B28
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animvalue_05006B28, 0x001521d0, 57608, 0x00006b28, 476);

// 0x05006D04
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animindex_05006D04, 0x001521d0, 57608, 0x00006d04, 180);

// 0x05006DB8
static const struct Animation monty_mole_seg5_anim_05006DB8 = {
    0,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(monty_mole_seg5_animindex_05006D04),
    monty_mole_seg5_animvalue_05006B28,
    monty_mole_seg5_animindex_05006D04,
    0,
    ANIM_FIELD_LENGTH(monty_mole_seg5_animvalue_05006B28),
    ANIM_FIELD_LENGTH(monty_mole_seg5_animindex_05006D04),
};
