#include "pc/rom_assets.h"
// 0x050099B8
ROM_ASSET_LOAD_ANIM(mad_piano_seg5_animvalue_050099B8, 0x00166c60, 26968, 0x000099b8, 16);

// 0x050099C8
ROM_ASSET_LOAD_ANIM(mad_piano_seg5_animindex_050099C8, 0x00166c60, 26968, 0x000099c8, 60);

// 0x05009A04
static const struct Animation mad_piano_seg5_anim_05009A04 = {
    0,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(mad_piano_seg5_animindex_050099C8),
    mad_piano_seg5_animvalue_050099B8,
    mad_piano_seg5_animindex_050099C8,
    0,
    ANIM_FIELD_LENGTH(mad_piano_seg5_animvalue_050099B8),
    ANIM_FIELD_LENGTH(mad_piano_seg5_animindex_050099C8),
};
