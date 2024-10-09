#include "pc/rom_assets.h"
// 0x050065F0
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animvalue_050065F0, 0x001521d0, 57608, 0x000065f0, 476);

// 0x050067CC
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animindex_050067CC, 0x001521d0, 57608, 0x000067cc, 180);

// 0x05006880
static const struct Animation monty_mole_seg5_anim_05006880 = {
    0,
    0,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(monty_mole_seg5_animindex_050067CC),
    monty_mole_seg5_animvalue_050065F0,
    monty_mole_seg5_animindex_050067CC,
    0,
    ANIM_FIELD_LENGTH(monty_mole_seg5_animvalue_050065F0),
    ANIM_FIELD_LENGTH(monty_mole_seg5_animindex_050067CC),
};
