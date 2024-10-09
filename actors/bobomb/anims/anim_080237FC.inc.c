#include "pc/rom_assets.h"
// 0x08023528
ROM_ASSET_LOAD_ANIM(bobomb_seg8_animvalue_08023528, 0x001f2200, 59076, 0x00023528, 556);

// 0x08023754
ROM_ASSET_LOAD_ANIM(bobomb_seg8_animindex_08023754, 0x001f2200, 59076, 0x00023754, 168);

// 0x080237FC
static const struct Animation bobomb_seg8_anim_080237FC = {
    0,
    0,
    0,
    0,
    0x19,
    ANIMINDEX_NUMPARTS(bobomb_seg8_animindex_08023754),
    bobomb_seg8_animvalue_08023528,
    bobomb_seg8_animindex_08023754,
    0,
    ANIM_FIELD_LENGTH(bobomb_seg8_animvalue_08023528),
    ANIM_FIELD_LENGTH(bobomb_seg8_animindex_08023754),
};
