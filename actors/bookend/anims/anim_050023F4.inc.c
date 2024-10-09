#include "pc/rom_assets.h"
// 0x05002350
ROM_ASSET_LOAD_ANIM(bookend_seg5_animvalue_05002350, 0x00166c60, 26968, 0x00002350, 32);

// 0x05002370
ROM_ASSET_LOAD_ANIM(bookend_seg5_animindex_05002370, 0x00166c60, 26968, 0x00002370, 132);

// 0x050023F4
static const struct Animation bookend_seg5_anim_050023F4 = {
    0,
    0,
    0,
    0,
    0x06,
    ANIMINDEX_NUMPARTS(bookend_seg5_animindex_05002370),
    bookend_seg5_animvalue_05002350,
    bookend_seg5_animindex_05002370,
    0,
    ANIM_FIELD_LENGTH(bookend_seg5_animvalue_05002350),
    ANIM_FIELD_LENGTH(bookend_seg5_animindex_05002370),
};
