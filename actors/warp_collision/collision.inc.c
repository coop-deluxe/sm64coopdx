#include "pc/rom_assets.h"
// Warp Collision (seems strange to put these collision in another file. Only instance of this seperation thus far. Not sure what this is doing as a file.)

// 0x0301CE78 - 0x0301CECC
ROM_ASSET_LOAD_COLLISION(door_seg3_collision_0301CE78, 0x00201410, 96653, 0x0001ce78, 84);

// 0x0301CECC - 0x0301CEFC
ROM_ASSET_LOAD_COLLISION(lll_hexagonal_mesh_seg3_collision_0301CECC, 0x00201410, 96653, 0x0001cecc, 48);
