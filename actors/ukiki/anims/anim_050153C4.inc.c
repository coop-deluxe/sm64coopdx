#include "pc/rom_assets.h"
// 0x05014BFC
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_05014BFC, 0x001521d0, 57608, 0x00014bfc, 1704);

// 0x050152A4
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_050152A4, 0x001521d0, 57608, 0x000152a4, 288);

// 0x050153C4
static const struct Animation ukiki_seg5_anim_050153C4 = {
    0,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_050152A4),
    ukiki_seg5_animvalue_05014BFC,
    ukiki_seg5_animindex_050152A4,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_05014BFC),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_050152A4),
};
