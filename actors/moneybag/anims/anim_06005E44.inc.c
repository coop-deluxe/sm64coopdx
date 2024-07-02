#include "pc/rom_assets.h"
// 0x06005D54
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animvalue_06005D54, 0x001e51f0, 11160, 0x00005d54, 144);

// 0x06005DE4
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animindex_06005DE4, 0x001e51f0, 11160, 0x00005de4, 96);

// 0x06005E44
static const struct Animation moneybag_seg6_anim_06005E44 = {
    0,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(moneybag_seg6_animindex_06005DE4),
    moneybag_seg6_animvalue_06005D54,
    moneybag_seg6_animindex_06005DE4,
    0,
    ANIM_FIELD_LENGTH(moneybag_seg6_animvalue_06005D54),
    ANIM_FIELD_LENGTH(moneybag_seg6_animindex_06005DE4),
};
