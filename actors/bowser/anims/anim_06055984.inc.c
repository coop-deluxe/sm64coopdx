#include "pc/rom_assets.h"
// 0x06055228
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06055228, 0x00188440, 199722, 0x00055378, 1344);

// 0x06055768
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06055768, 0x00188440, 199722, 0x000558b8, 540);

// 0x06055984
static const struct Animation bowser_seg6_anim_06055984 = {
    0,
    0,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06055768),
    bowser_seg6_animvalue_06055228,
    bowser_seg6_animindex_06055768,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06055228),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06055768),
};
