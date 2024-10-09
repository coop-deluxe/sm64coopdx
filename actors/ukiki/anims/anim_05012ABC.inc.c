#include "pc/rom_assets.h"
// 0x0501040C
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_0501040C, 0x001521d0, 57608, 0x0001040c, 9616);

// 0x0501299C
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0501299C, 0x001521d0, 57608, 0x0001299c, 288);

// 0x05012ABC
static const struct Animation ukiki_seg5_anim_05012ABC = {
    0,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0501299C),
    ukiki_seg5_animvalue_0501040C,
    ukiki_seg5_animindex_0501299C,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_0501040C),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0501299C),
};
