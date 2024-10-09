#include "pc/rom_assets.h"
// 0x050233BC
ROM_ASSET_LOAD_ANIM(yoshi_seg5_animvalue_050233BC, 0x0016d870, 76997, 0x000234a4, 2404);

// 0x05023D20
ROM_ASSET_LOAD_ANIM(yoshi_seg5_animindex_5023D20, 0x0016d870, 76997, 0x00023e08, 300);

// 0x05023E4C
static const struct Animation yoshi_seg5_anim_05023E4C = {
    0,
    0,
    0,
    0,
    0x1D,
    ANIMINDEX_NUMPARTS(yoshi_seg5_animindex_5023D20),
    yoshi_seg5_animvalue_050233BC,
    yoshi_seg5_animindex_5023D20,
    0,
    ANIM_FIELD_LENGTH(yoshi_seg5_animvalue_050233BC),
    ANIM_FIELD_LENGTH(yoshi_seg5_animindex_5023D20),
};
