#include "pc/rom_assets.h"
// 0x0500FC9C
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_0500FC9C, 0x001521d0, 57608, 0x0000fc9c, 688);

// 0x0500FF4C
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0500FF4C, 0x001521d0, 57608, 0x0000ff4c, 288);

// 0x0501006C
static const struct Animation ukiki_seg5_anim_0501006C = {
    0,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0500FF4C),
    ukiki_seg5_animvalue_0500FC9C,
    ukiki_seg5_animindex_0500FF4C,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_0500FC9C),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0500FF4C),
};
