#include "pc/rom_assets.h"
// 0x0800AC18
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animvalue_0800AC18, 0x001f2200, 59076, 0x0000ac18, 476);

// 0x0800ADF4
ROM_ASSET_LOAD_ANIM(chuckya_seg8_animindex_0800ADF4, 0x001f2200, 59076, 0x0000adf4, 372);

// 0x0800AF68
static const struct Animation chuckya_seg8_anim_0800AF68 = {
    0,
    0,
    0,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(chuckya_seg8_animindex_0800ADF4),
    chuckya_seg8_animvalue_0800AC18,
    chuckya_seg8_animindex_0800ADF4,
    0,
    ANIM_FIELD_LENGTH(chuckya_seg8_animvalue_0800AC18),
    ANIM_FIELD_LENGTH(chuckya_seg8_animindex_0800ADF4),
};
