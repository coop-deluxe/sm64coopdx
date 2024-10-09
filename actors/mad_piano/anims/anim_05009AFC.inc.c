#include "pc/rom_assets.h"
// 0x05009A1C
ROM_ASSET_LOAD_ANIM(mad_piano_seg5_animvalue_05009A1C, 0x00166c60, 26968, 0x00009a1c, 164);

// 0x05009AC0
ROM_ASSET_LOAD_ANIM(mad_piano_seg5_animindex_05009AC0, 0x00166c60, 26968, 0x00009ac0, 60);

// 0x05009AFC
static const struct Animation mad_piano_seg5_anim_05009AFC = {
    0,
    0,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(mad_piano_seg5_animindex_05009AC0),
    mad_piano_seg5_animvalue_05009A1C,
    mad_piano_seg5_animindex_05009AC0,
    0,
    ANIM_FIELD_LENGTH(mad_piano_seg5_animvalue_05009A1C),
    ANIM_FIELD_LENGTH(mad_piano_seg5_animindex_05009AC0),
};
