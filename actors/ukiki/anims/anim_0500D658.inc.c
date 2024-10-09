#include "pc/rom_assets.h"
// 0x0500D198
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_0500D198, 0x001521d0, 57608, 0x0000d198, 928);

// 0x0500D538
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0500D538, 0x001521d0, 57608, 0x0000d538, 288);

// 0x0500D658
static const struct Animation ukiki_seg5_anim_0500D658 = {
    0,
    0,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0500D538),
    ukiki_seg5_animvalue_0500D198,
    ukiki_seg5_animindex_0500D538,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_0500D198),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0500D538),
};
