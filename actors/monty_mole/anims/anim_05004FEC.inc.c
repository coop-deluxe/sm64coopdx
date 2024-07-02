#include "pc/rom_assets.h"
// 0x05004DA0
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animvalue_05004DA0, 0x001521d0, 57608, 0x00004da0, 408);

// 0x05004F38
ROM_ASSET_LOAD_ANIM(monty_mole_seg5_animindex_05004F38, 0x001521d0, 57608, 0x00004f38, 180);

// 0x05004FEC
static const struct Animation monty_mole_seg5_anim_05004FEC = {
    0,
    0,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(monty_mole_seg5_animindex_05004F38),
    monty_mole_seg5_animvalue_05004DA0,
    monty_mole_seg5_animindex_05004F38,
    0,
    ANIM_FIELD_LENGTH(monty_mole_seg5_animvalue_05004DA0),
    ANIM_FIELD_LENGTH(monty_mole_seg5_animindex_05004F38),
};
