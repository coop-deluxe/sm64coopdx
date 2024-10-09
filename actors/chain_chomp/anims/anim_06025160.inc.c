#include "pc/rom_assets.h"
// 0x06025030
ROM_ASSET_LOAD_ANIM(chain_chomp_seg6_animvalue_06025030, 0x001c4230, 80474, 0x00025030, 208);

// 0x06025100
ROM_ASSET_LOAD_ANIM(chain_chomp_seg6_animindex_06025100, 0x001c4230, 80474, 0x00025100, 96);

// 0x06025160
static const struct Animation chain_chomp_seg6_anim_06025160 = {
    0,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(chain_chomp_seg6_animindex_06025100),
    chain_chomp_seg6_animvalue_06025030,
    chain_chomp_seg6_animindex_06025100,
    0,
    ANIM_FIELD_LENGTH(chain_chomp_seg6_animvalue_06025030),
    ANIM_FIELD_LENGTH(chain_chomp_seg6_animindex_06025100),
};
