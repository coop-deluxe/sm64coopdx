#include "pc/rom_assets.h"
// 0x050153DC
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animvalue_050153DC, 0x001521d0, 57608, 0x000153dc, 624);

// 0x0501564C
ROM_ASSET_LOAD_ANIM(ukiki_seg5_animindex_0501564C, 0x001521d0, 57608, 0x0001564c, 288);

// 0x0501576C
static const struct Animation ukiki_seg5_anim_0501576C = {
    0,
    0,
    0,
    0,
    0x0E,
    ANIMINDEX_NUMPARTS(ukiki_seg5_animindex_0501564C),
    ukiki_seg5_animvalue_050153DC,
    ukiki_seg5_animindex_0501564C,
    0,
    ANIM_FIELD_LENGTH(ukiki_seg5_animvalue_050153DC),
    ANIM_FIELD_LENGTH(ukiki_seg5_animindex_0501564C),
};
