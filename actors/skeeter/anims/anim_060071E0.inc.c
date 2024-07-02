#include "pc/rom_assets.h"
// 0x06006B88
ROM_ASSET_LOAD_ANIM(skeeter_seg6_animvalue_06006B88, 0x001b9cc0, 41188, 0x00006b88, 1276);

// 0x06007084
ROM_ASSET_LOAD_ANIM(skeeter_seg6_animindex_06007084, 0x001b9cc0, 41188, 0x00007084, 348);

// 0x060071E0
static const struct Animation skeeter_seg6_anim_060071E0 = {
    0,
    0,
    0,
    0,
    0x13,
    ANIMINDEX_NUMPARTS(skeeter_seg6_animindex_06007084),
    skeeter_seg6_animvalue_06006B88,
    skeeter_seg6_animindex_06007084,
    0,
    ANIM_FIELD_LENGTH(skeeter_seg6_animvalue_06006B88),
    ANIM_FIELD_LENGTH(skeeter_seg6_animindex_06007084),
};
