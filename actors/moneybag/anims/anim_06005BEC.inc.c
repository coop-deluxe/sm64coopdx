#include "pc/rom_assets.h"
// 0x06005AF0
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animvalue_06005AF0, 0x001e51f0, 11160, 0x00005af0, 156);

// 0x06005B8C
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animindex_06005B8C, 0x001e51f0, 11160, 0x00005b8c, 96);

// 0x06005BEC
static const struct Animation moneybag_seg6_anim_06005BEC = {
    0,
    0,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(moneybag_seg6_animindex_06005B8C),
    moneybag_seg6_animvalue_06005AF0,
    moneybag_seg6_animindex_06005B8C,
    0,
    ANIM_FIELD_LENGTH(moneybag_seg6_animvalue_06005AF0),
    ANIM_FIELD_LENGTH(moneybag_seg6_animindex_06005B8C),
};
