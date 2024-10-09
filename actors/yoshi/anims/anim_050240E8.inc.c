#include "pc/rom_assets.h"
// 0x05023E64
ROM_ASSET_LOAD_ANIM(yoshi_seg5_animvalue_05023E64, 0x0016d870, 76997, 0x00023f4c, 344);

// 0x05023FBC
ROM_ASSET_LOAD_ANIM(yoshi_seg5_animindex_5023FBC, 0x0016d870, 76997, 0x000240a4, 300);

// 0x050240E8
static const struct Animation yoshi_seg5_anim_050240E8 = {
    0,
    0,
    0,
    0,
    0x06,
    ANIMINDEX_NUMPARTS(yoshi_seg5_animindex_5023FBC),
    yoshi_seg5_animvalue_05023E64,
    yoshi_seg5_animindex_5023FBC,
    0,
    ANIM_FIELD_LENGTH(yoshi_seg5_animvalue_05023E64),
    ANIM_FIELD_LENGTH(yoshi_seg5_animindex_5023FBC),
};
