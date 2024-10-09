#include "pc/rom_assets.h"
// 0x05005294
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animvalue_05005294, 0x001521d0, 57608, 0x00005294, 360);

// 0x050053FC
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animindex_050053FC, 0x001521d0, 57608, 0x000053fc, 180);

// 0x050054B0
static const struct Animation monty_mole_seg5_anim_050054B0 = {
    0,
    0,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(monty_mole_seg5_animindex_050053FC),
    monty_mole_seg5_animvalue_05005294,
    monty_mole_seg5_animindex_050053FC,
    0,
    ANIM_FIELD_LENGTH(monty_mole_seg5_animvalue_05005294),
    ANIM_FIELD_LENGTH(monty_mole_seg5_animindex_050053FC),
};
