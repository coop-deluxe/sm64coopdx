#include "pc/rom_assets.h"
// 0x06044604
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06044604, 0x00188440, 199722, 0x00044754, 2984);

// 0x060451AC
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_060451AC, 0x00188440, 199722, 0x000452fc, 540);

// 0x060453C8
static const struct Animation bowser_seg6_anim_060453C8 = {
    0,
    0,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_060451AC),
    bowser_seg6_animvalue_06044604,
    bowser_seg6_animindex_060451AC,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06044604),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_060451AC),
};
