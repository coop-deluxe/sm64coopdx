#include "pc/rom_assets.h"
#include <PR/ultratypes.h>

#include "macros.h"
#include "animdata.h"
#include "../gd_types.h"

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lips_2_1, 0x00282f20, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lips_2_2, 0x00284258, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_lips_2[] = {
    { ARRAY_COUNT(animdata_mario_lips_2_1), GD_ANIM_ROT3S, animdata_mario_lips_2_1 },
    { ARRAY_COUNT(animdata_mario_lips_2_2), GD_ANIM_ROT3S, animdata_mario_lips_2_2 },
    END_ANIMDATA_INFO_ARR,
};
