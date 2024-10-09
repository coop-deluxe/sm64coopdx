#include "pc/rom_assets.h"
// 0x0500D670
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_0500D670, 0x001521d0, 57608, 0x0000d670, 1264);

// 0x0500DB60
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0500DB60, 0x001521d0, 57608, 0x0000db60, 288);

// 0x0500DC80
static const struct Animation ukiki_seg5_anim_0500DC80 = {
    0,
    0,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0500DB60),
    ukiki_seg5_animvalue_0500D670,
    ukiki_seg5_animindex_0500DB60,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_0500D670),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0500DB60),
};
