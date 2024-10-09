#include "pc/rom_assets.h"
// 0x0600CC3C
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600CC3C, 0x001c4230, 80474, 0x0000cc3c, 700);

// 0x0600CEF8
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0600CEF8, 0x001c4230, 80474, 0x0000cef8, 192);

// 0x0600CFB8
static const struct Animation koopa_seg6_anim_0600CFB8 = {
    0,
    0,
    0,
    0,
    0x16,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0600CEF8),
    koopa_seg6_animvalue_0600CC3C,
    koopa_seg6_animindex_0600CEF8,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600CC3C),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0600CEF8),
};
