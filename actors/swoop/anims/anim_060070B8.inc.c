#include "pc/rom_assets.h"
// 0x06006EA0
ROM_ASSET_LOAD_ANIM(swoop_seg6_animvalue_06006EA0, 0x001e7ee0, 40011, 0x00006ea0, 428);

// 0x0600704C
ROM_ASSET_LOAD_ANIM(swoop_seg6_animindex_0600704C, 0x001e7ee0, 40011, 0x0000704c, 108);

// 0x060070B8
static const struct Animation swoop_seg6_anim_060070B8 = {
    0,
    0,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(swoop_seg6_animindex_0600704C),
    swoop_seg6_animvalue_06006EA0,
    swoop_seg6_animindex_0600704C,
    0,
    ANIM_FIELD_LENGTH(swoop_seg6_animvalue_06006EA0),
    ANIM_FIELD_LENGTH(swoop_seg6_animindex_0600704C),
};
