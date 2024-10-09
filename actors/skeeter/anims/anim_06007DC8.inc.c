#include "pc/rom_assets.h"
// 0x060071F8
ROM_ASSET_LOAD_ANIM(skeeter_seg6_animvalue_060071F8, 0x001b9cc0, 41188, 0x000071f8, 2676);

// 0x06007C6C
ROM_ASSET_LOAD_ANIM(skeeter_seg6_animindex_06007C6C, 0x001b9cc0, 41188, 0x00007c6c, 348);

// 0x06007DC8
static const struct Animation skeeter_seg6_anim_06007DC8 = {
    0,
    0,
    0,
    0,
    0x27,
    ANIMINDEX_NUMPARTS(skeeter_seg6_animindex_06007C6C),
    skeeter_seg6_animvalue_060071F8,
    skeeter_seg6_animindex_06007C6C,
    0,
    ANIM_FIELD_LENGTH(skeeter_seg6_animvalue_060071F8),
    ANIM_FIELD_LENGTH(skeeter_seg6_animindex_06007C6C),
};
