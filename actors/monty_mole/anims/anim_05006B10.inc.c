#include "pc/rom_assets.h"
// 0x05006898
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animvalue_05006898, 0x001521d0, 57608, 0x00006898, 452);

// 0x05006A5C
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animindex_05006A5C, 0x001521d0, 57608, 0x00006a5c, 180);

// 0x05006B10
static const struct Animation monty_mole_seg5_anim_05006B10 = {
    0,
    0,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(monty_mole_seg5_animindex_05006A5C),
    monty_mole_seg5_animvalue_05006898,
    monty_mole_seg5_animindex_05006A5C,
    0,
    ANIM_FIELD_LENGTH(monty_mole_seg5_animvalue_05006898),
    ANIM_FIELD_LENGTH(monty_mole_seg5_animindex_05006A5C),
};
