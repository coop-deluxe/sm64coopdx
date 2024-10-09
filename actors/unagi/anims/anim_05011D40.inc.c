#include "pc/rom_assets.h"
// 0x050118A8
ROM_ASSET_LOAD_ANIM(unagi_seg5_animvalue_050118A8, 0x0013b910, 41727, 0x000118a8, 984);

// 0x05011C80
ROM_ASSET_LOAD_ANIM(unagi_seg5_animindex_05011C80, 0x0013b910, 41727, 0x00011c80, 192);

// 0x05011D40
static const struct Animation unagi_seg5_anim_05011D40 = {
    0,
    0,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(unagi_seg5_animindex_05011C80),
    unagi_seg5_animvalue_050118A8,
    unagi_seg5_animindex_05011C80,
    0,
    ANIM_FIELD_LENGTH(unagi_seg5_animvalue_050118A8),
    ANIM_FIELD_LENGTH(unagi_seg5_animindex_05011C80),
};
