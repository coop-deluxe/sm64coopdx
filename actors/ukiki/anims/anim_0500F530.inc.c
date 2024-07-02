#include "pc/rom_assets.h"
// 0x0500EEC0
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_0500EEC0, 0x001521d0, 57608, 0x0000eec0, 1360);

// 0x0500F410
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0500F410, 0x001521d0, 57608, 0x0000f410, 288);

// 0x0500F530
static const struct Animation ukiki_seg5_anim_0500F530 = {
    0,
    0,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0500F410),
    ukiki_seg5_animvalue_0500EEC0,
    ukiki_seg5_animindex_0500F410,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_0500EEC0),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0500F410),
};
