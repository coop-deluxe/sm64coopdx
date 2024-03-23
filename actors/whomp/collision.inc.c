#include "pc/rom_assets.h"
// Whomp

// 0x06020A0C - 0x06020A90
#ifndef VERSION_JP
ROM_ASSET_LOAD_COLLISION(whomp_seg6_collision_06020A0C, 0x001c4230, 80474, 0x00020a0c, 132);
#endif

#ifdef VERSION_JP
const Collision whomp_seg6_collision_06020A0C[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x8),
    COL_VERTEX(-200, 50, -100),
    COL_VERTEX(150, 50, -100),
    COL_VERTEX(150, 430, -100),
    COL_VERTEX(-200, 430, -100),
    COL_VERTEX(-200, 50, -3),
    COL_VERTEX(150, 430, -3),
    COL_VERTEX(150, 50, -3),
    COL_VERTEX(-200, 430, -3),
    COL_TRI_INIT(SURFACE_NO_CAM_COLLISION, 12),
    COL_TRI(2, 1, 0),
    COL_TRI(3, 2, 0),
    COL_TRI(6, 5, 4),
    COL_TRI(5, 7, 4),
    COL_TRI(7, 5, 3),
    COL_TRI(5, 2, 3),
    COL_TRI(6, 4, 0),
    COL_TRI(1, 6, 0),
    COL_TRI(5, 1, 2),
    COL_TRI(6, 1, 5),
    COL_TRI(0, 7, 3),
    COL_TRI(0, 4, 7),
    COL_TRI_STOP(),
    COL_END(),
};
#endif

UNUSED static const u32 whomp_unused_2 = 0;
