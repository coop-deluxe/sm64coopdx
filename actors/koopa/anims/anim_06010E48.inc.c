#include "pc/rom_assets.h"
// 0x0601064C
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0601064C, 0x001c4230, 80474, 0x0001064c, 1852);

// 0x06010D88
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_06010D88, 0x001c4230, 80474, 0x00010d88, 192);

// 0x06010E48
static const struct Animation koopa_seg6_anim_06010E48 = {
    0,
    0,
    0,
    0,
    0x22,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_06010D88),
    koopa_seg6_animvalue_0601064C,
    koopa_seg6_animindex_06010D88,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0601064C),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_06010D88),
};
