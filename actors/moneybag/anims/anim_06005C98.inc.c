#include "pc/rom_assets.h"
// 0x06005C04
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animvalue_06005C04, 0x001e51f0, 11160, 0x00005c04, 52);

// 0x06005C38
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animindex_06005C38, 0x001e51f0, 11160, 0x00005c38, 96);

// 0x06005C98
static const struct Animation moneybag_seg6_anim_06005C98 = {
    0,
    0,
    0,
    0,
    0x04,
    ANIMINDEX_NUMPARTS(moneybag_seg6_animindex_06005C38),
    moneybag_seg6_animvalue_06005C04,
    moneybag_seg6_animindex_06005C38,
    0,
    ANIM_FIELD_LENGTH(moneybag_seg6_animvalue_06005C04),
    ANIM_FIELD_LENGTH(moneybag_seg6_animindex_06005C38),
};
