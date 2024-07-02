#include "pc/rom_assets.h"
// 0x08011798
ROM_ASSET_LOAD_ANIM(flyguy_seg8_animvalue_08011798, 0x001f2200, 59076, 0x00011798, 572);

// 0x080119D4
ROM_ASSET_LOAD_ANIM(flyguy_seg8_animindex_080119D4, 0x001f2200, 59076, 0x000119d4, 120);

// 0x08011A4C
static const struct Animation flyguy_seg8_anim_08011A4C = {
    0,
    0,
    0,
    0,
    0x2E,
    ANIMINDEX_NUMPARTS(flyguy_seg8_animindex_080119D4),
    flyguy_seg8_animvalue_08011798,
    flyguy_seg8_animindex_080119D4,
    0,
    ANIM_FIELD_LENGTH(flyguy_seg8_animvalue_08011798),
    ANIM_FIELD_LENGTH(flyguy_seg8_animindex_080119D4),
};
