#include "pc/rom_assets.h"
// 0x06005CB0
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animvalue_06005CB0, 0x001e51f0, 11160, 0x00005cb0, 44);

// 0x06005CDC
ROM_ASSET_LOAD_ANIM(moneybag_seg6_animindex_06005CDC, 0x001e51f0, 11160, 0x00005cdc, 96);

// 0x06005D3C
static const struct Animation moneybag_seg6_anim_06005D3C = {
    0,
    0,
    0,
    0,
    0x03,
    ANIMINDEX_NUMPARTS(moneybag_seg6_animindex_06005CDC),
    moneybag_seg6_animvalue_06005CB0,
    moneybag_seg6_animindex_06005CDC,
    0,
    ANIM_FIELD_LENGTH(moneybag_seg6_animvalue_06005CB0),
    ANIM_FIELD_LENGTH(moneybag_seg6_animindex_06005CDC),
};
