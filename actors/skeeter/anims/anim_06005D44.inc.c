#include "pc/rom_assets.h"
// 0x06005720
ROM_ASSET_LOAD_ANIM(skeeter_seg6_animvalue_06005720, 0x001b9cc0, 41188, 0x00005720, 1224);

// 0x06005BE8
ROM_ASSET_LOAD_ANIM(skeeter_seg6_animindex_06005BE8, 0x001b9cc0, 41188, 0x00005be8, 348);

// 0x06005D44
static const struct Animation skeeter_seg6_anim_06005D44 = {
    1,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(skeeter_seg6_animindex_06005BE8),
    skeeter_seg6_animvalue_06005720,
    skeeter_seg6_animindex_06005BE8,
    0,
    ANIM_FIELD_LENGTH(skeeter_seg6_animvalue_06005720),
    ANIM_FIELD_LENGTH(skeeter_seg6_animindex_06005BE8),
};
