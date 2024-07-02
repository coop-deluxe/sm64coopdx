#include "pc/rom_assets.h"
// 0x06005D5C
ROM_ASSET_LOAD_ANIM(skeeter_seg6_animvalue_06005D5C, 0x001b9cc0, 41188, 0x00005d5c, 3256);

// 0x06006A14
ROM_ASSET_LOAD_ANIM(skeeter_seg6_animindex_06006A14, 0x001b9cc0, 41188, 0x00006a14, 348);

// 0x06006B70
static const struct Animation skeeter_seg6_anim_06006B70 = {
    0,
    0,
    0,
    0,
    0x31,
    ANIMINDEX_NUMPARTS(skeeter_seg6_animindex_06006A14),
    skeeter_seg6_animvalue_06005D5C,
    skeeter_seg6_animindex_06006A14,
    0,
    ANIM_FIELD_LENGTH(skeeter_seg6_animvalue_06005D5C),
    ANIM_FIELD_LENGTH(skeeter_seg6_animindex_06006A14),
};
