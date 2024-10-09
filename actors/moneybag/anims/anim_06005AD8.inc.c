#include "pc/rom_assets.h"
// 0x06005A60
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animvalue_06005A60, 0x001e51f0, 11160, 0x00005a60, 24);

// 0x06005A78
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animindex_06005A78, 0x001e51f0, 11160, 0x00005a78, 96);

// 0x06005AD8
static const struct Animation moneybag_seg6_anim_06005AD8 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(moneybag_seg6_animindex_06005A78),
    moneybag_seg6_animvalue_06005A60,
    moneybag_seg6_animindex_06005A78,
    0,
    ANIM_FIELD_LENGTH(moneybag_seg6_animvalue_06005A60),
    ANIM_FIELD_LENGTH(moneybag_seg6_animindex_06005A78),
};
