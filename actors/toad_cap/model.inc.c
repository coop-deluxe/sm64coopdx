static const Lights1 toad_cap_black_lights_group = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x49, 0x49, 0x49
);

#include "actors/mario/mario_externs.h"
#include "actors/toad_player/toad_player_externs.h"
#define toad_cap_texture_metal_shade              mario_texture_metal_shade
#define toad_cap_texture_metal_light              mario_texture_metal_light
#define toad_cap_texture_cap                      toad_player_texture_cap
#define toad_cap_texture_spots                    toad_player_texture_spots
#define toad_cap_texture_wings_half_1             mario_texture_wings_half_1
#define toad_cap_texture_wings_half_2             mario_texture_wings_half_2
#define toad_cap_texture_metal_wings_half_1_shade mario_texture_metal_wings_half_1_shade
#define toad_cap_texture_metal_wings_half_1_light mario_texture_metal_wings_half_1_light
#define toad_cap_texture_metal_wings_half_2_shade mario_texture_metal_wings_half_2_shade
#define toad_cap_texture_metal_wings_half_2_light mario_texture_metal_wings_half_2_light

Vtx toad_cap_mesh_layer_1_vtx_0[94] = {
    {{ {-175, 118, 0}, 0, {-418, 482}, {134, 35, 0, 0} }},
    {{ {-70, 167, 123}, 0, {178, 72}, {212, 90, 78, 0} }},
    {{ {-141, 167, 0}, 0, {-280, 152}, {166, 90, 0, 0} }},
    {{ {43, 0, 75}, 0, {751, 1673}, {9, 130, 17, 0} }},
    {{ {89, 0, 0}, 0, {610, 1852}, {20, 131, 0, 0} }},
    {{ {142, 13, 0}, 0, {624, 1980}, {81, 158, 0, 0} }},
    {{ {71, 13, -123}, 0, {306, 1880}, {40, 158, 186, 0} }},
    {{ {43, 0, -75}, 0, {408, 1776}, {9, 130, 240, 0} }},
    {{ {-70, 13, -123}, 0, {250, 1518}, {216, 158, 186, 0} }},
    {{ {-43, 0, -75}, 0, {375, 1557}, {247, 130, 240, 0} }},
    {{ {-141, 13, 0}, 0, {508, 1254}, {175, 158, 0, 0} }},
    {{ {-89, 0, 0}, 0, {531, 1396}, {236, 131, 0, 0} }},
    {{ {-70, 13, 120}, 0, {826, 1356}, {217, 157, 69, 0} }},
    {{ {-43, 0, 75}, 0, {724, 1458}, {247, 130, 17, 0} }},
    {{ {88, 63, 152}, 0, {-92, 952}, {61, 220, 106, 0} }},
    {{ {176, 63, 0}, 0, {1016, 906}, {122, 222, 0, 0} }},
    {{ {176, 118, 0}, 0, {1010, 594}, {122, 35, 0, 0} }},
    {{ {88, 118, 152}, 0, {-98, 640}, {61, 34, 106, 0} }},
    {{ {142, 167, 0}, 0, {892, 212}, {90, 90, 0, 0} }},
    {{ {71, 167, 123}, 0, {2, 250}, {45, 90, 78, 0} }},
    {{ {79, 201, 0}, 0, {688, -162}, {47, 118, 0, 0} }},
    {{ {39, 201, 69}, 0, {194, -140}, {23, 118, 40, 0} }},
    {{ {176, 63, 0}, 0, {-196, 438}, {122, 222, 0, 0} }},
    {{ {88, 118, -152}, 0, {1220, 36}, {61, 36, 150, 0} }},
    {{ {176, 118, 0}, 0, {-198, -10}, {122, 35, 0, 0} }},
    {{ {88, 63, -153}, 0, {1222, 482}, {61, 222, 150, 0} }},
    {{ {142, 13, 0}, 0, {-54, 916}, {81, 158, 0, 0} }},
    {{ {71, 13, -123}, 0, {1084, 952}, {40, 158, 186, 0} }},
    {{ {-70, 13, 120}, 0, {184, 1066}, {217, 157, 69, 0} }},
    {{ {88, 63, 152}, 0, {1214, 712}, {61, 220, 106, 0} }},
    {{ {-88, 63, 152}, 0, {34, 812}, {195, 220, 106, 0} }},
    {{ {88, 118, 152}, 0, {1186, 352}, {61, 34, 106, 0} }},
    {{ {-88, 118, 152}, 0, {6, 452}, {195, 35, 106, 0} }},
    {{ {71, 167, 123}, 0, {1050, -18}, {45, 90, 78, 0} }},
    {{ {-70, 167, 123}, 0, {104, 62}, {212, 90, 78, 0} }},
    {{ {39, 201, 69}, 0, {780, -272}, {23, 118, 40, 0} }},
    {{ {-38, 201, 69}, 0, {304, -170}, {233, 118, 40, 0} }},
    {{ {71, 167, 123}, 0, {1036, -112}, {45, 90, 78, 0} }},
    {{ {-141, 167, 0}, 0, {456, 1066}, {166, 90, 0, 0} }},
    {{ {-70, 167, 123}, 0, {1404, 676}, {212, 90, 78, 0} }},
    {{ {-38, 201, 69}, 0, {1000, 266}, {233, 118, 40, 0} }},
    {{ {-78, 201, 0}, 0, {474, 484}, {210, 118, 0, 0} }},
    {{ {0, 213, 0}, 0, {490, -104}, {0, 127, 0, 0} }},
    {{ {-38, 201, -66}, 0, {-38, 168}, {234, 119, 216, 0} }},
    {{ {-70, 167, -122}, 0, {-462, 496}, {212, 91, 179, 0} }},
    {{ {-38, 201, 69}, 0, {-16, -16}, {233, 118, 40, 0} }},
    {{ {39, 201, 69}, 0, {-16, -16}, {23, 118, 40, 0} }},
    {{ {0, 213, 0}, 0, {-16, -16}, {0, 127, 0, 0} }},
    {{ {79, 201, 0}, 0, {-16, -16}, {47, 118, 0, 0} }},
    {{ {-141, 13, 0}, 0, {-184, 898}, {175, 158, 0, 0} }},
    {{ {-70, 13, 120}, 0, {1120, 942}, {217, 157, 69, 0} }},
    {{ {-88, 63, 152}, 0, {1264, 448}, {195, 220, 106, 0} }},
    {{ {-175, 63, 0}, 0, {-362, 392}, {134, 222, 0, 0} }},
    {{ {-88, 118, 152}, 0, {1258, -4}, {195, 35, 106, 0} }},
    {{ {-175, 118, 0}, 0, {-370, -58}, {134, 35, 0, 0} }},
    {{ {-70, 167, 123}, 0, {1100, -320}, {212, 90, 78, 0} }},
    {{ {71, 167, -122}, 0, {-26, 196}, {44, 91, 179, 0} }},
    {{ {-70, 167, -122}, 0, {888, 166}, {212, 91, 179, 0} }},
    {{ {-38, 201, -66}, 0, {646, -188}, {234, 119, 216, 0} }},
    {{ {88, 118, -152}, 0, {-106, 592}, {61, 36, 150, 0} }},
    {{ {-88, 118, -152}, 0, {1032, 556}, {195, 36, 151, 0} }},
    {{ {88, 63, -153}, 0, {-88, 942}, {61, 222, 150, 0} }},
    {{ {-88, 63, -153}, 0, {1050, 906}, {195, 222, 150, 0} }},
    {{ {-70, 13, -123}, 0, {-96, 882}, {216, 158, 186, 0} }},
    {{ {-141, 13, 0}, 0, {1122, 1024}, {175, 158, 0, 0} }},
    {{ {-175, 63, 0}, 0, {1320, 596}, {134, 222, 0, 0} }},
    {{ {-88, 63, -153}, 0, {-198, 414}, {195, 222, 150, 0} }},
    {{ {-175, 118, 0}, 0, {1372, 98}, {134, 35, 0, 0} }},
    {{ {-88, 118, -152}, 0, {-146, -82}, {195, 36, 151, 0} }},
    {{ {176, 118, 0}, 0, {-16, -16}, {122, 35, 0, 0} }},
    {{ {71, 167, -122}, 0, {-16, -16}, {44, 91, 179, 0} }},
    {{ {142, 167, 0}, 0, {-16, -16}, {90, 90, 0, 0} }},
    {{ {88, 118, -152}, 0, {-16, -16}, {61, 36, 150, 0} }},
    {{ {71, 13, -123}, 0, {-16, -16}, {40, 158, 186, 0} }},
    {{ {-88, 63, -153}, 0, {-16, -16}, {195, 222, 150, 0} }},
    {{ {88, 63, -153}, 0, {-16, -16}, {61, 222, 150, 0} }},
    {{ {-70, 13, -123}, 0, {-16, -16}, {216, 158, 186, 0} }},
    {{ {-88, 118, -152}, 0, {-16, -16}, {195, 36, 151, 0} }},
    {{ {-141, 167, 0}, 0, {-16, -16}, {166, 90, 0, 0} }},
    {{ {-70, 167, -122}, 0, {-16, -16}, {212, 91, 179, 0} }},
    {{ {-175, 118, 0}, 0, {-16, -16}, {134, 35, 0, 0} }},
    {{ {43, 0, 75}, 0, {-11, 790}, {9, 130, 17, 0} }},
    {{ {142, 13, 0}, 0, {1024, 984}, {81, 158, 0, 0} }},
    {{ {71, 13, 120}, 0, {82, 380}, {40, 157, 69, 0} }},
    {{ {176, 63, 0}, 0, {1466, 550}, {122, 222, 0, 0} }},
    {{ {88, 63, 152}, 0, {290, -208}, {61, 220, 106, 0} }},
    {{ {-70, 13, 120}, 0, {-982, 638}, {217, 157, 69, 0} }},
    {{ {-43, 0, 75}, 0, {-656, 946}, {247, 130, 17, 0} }},
    {{ {71, 167, -122}, 0, {832, 1186}, {44, 91, 179, 0} }},
    {{ {-38, 201, -66}, 0, {1162, -70}, {234, 119, 216, 0} }},
    {{ {39, 201, -66}, 0, {654, 498}, {23, 118, 216, 0} }},
    {{ {0, 213, 0}, 0, {414, -278}, {0, 127, 0, 0} }},
    {{ {79, 201, 0}, 0, {-98, 326}, {47, 118, 0, 0} }},
    {{ {142, 167, 0}, 0, {-524, 874}, {90, 90, 0, 0} }},
};

Gfx toad_cap_mesh_layer_1_tri_0[] = {
    gsSPVertex(toad_cap_mesh_layer_1_vtx_0 + 0, 63, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(4, 6, 5, 0, 4, 7, 6, 0),
    gsSP2Triangles(7, 8, 6, 0, 7, 9, 8, 0),
    gsSP2Triangles(9, 10, 8, 0, 9, 11, 10, 0),
    gsSP2Triangles(11, 12, 10, 0, 11, 13, 12, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
    gsSP2Triangles(17, 16, 18, 0, 17, 18, 19, 0),
    gsSP2Triangles(19, 18, 20, 0, 19, 20, 21, 0),
    gsSP2Triangles(22, 23, 24, 0, 22, 25, 23, 0),
    gsSP2Triangles(26, 25, 22, 0, 26, 27, 25, 0),
    gsSP2Triangles(28, 29, 30, 0, 30, 29, 31, 0),
    gsSP2Triangles(30, 31, 32, 0, 32, 31, 33, 0),
    gsSP2Triangles(32, 33, 34, 0, 1, 35, 36, 0),
    gsSP2Triangles(1, 37, 35, 0, 38, 39, 40, 0),
    gsSP2Triangles(38, 40, 41, 0, 41, 40, 42, 0),
    gsSP2Triangles(43, 41, 42, 0, 44, 41, 43, 0),
    gsSP2Triangles(44, 38, 41, 0, 45, 46, 47, 0),
    gsSP2Triangles(46, 48, 47, 0, 49, 50, 51, 0),
    gsSP2Triangles(49, 51, 52, 0, 52, 51, 53, 0),
    gsSP2Triangles(52, 53, 54, 0, 54, 53, 55, 0),
    gsSP2Triangles(56, 57, 58, 0, 59, 57, 56, 0),
    gsSP2Triangles(59, 60, 57, 0, 61, 60, 59, 0),
    gsSP1Triangle(61, 62, 60, 0),
    gsSPVertex(toad_cap_mesh_layer_1_vtx_0 + 63, 31, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 9, 7, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 13, 11, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 17, 15, 0),
    gsSP2Triangles(18, 19, 20, 0, 20, 19, 21, 0),
    gsSP2Triangles(20, 21, 22, 0, 23, 20, 22, 0),
    gsSP2Triangles(24, 20, 23, 0, 24, 18, 20, 0),
    gsSP2Triangles(25, 26, 27, 0, 27, 26, 28, 0),
    gsSP2Triangles(29, 27, 28, 0, 30, 27, 29, 0),
    gsSP1Triangle(30, 25, 27, 0),
    gsSPEndDisplayList(),
};

Vtx toad_cap_mesh_layer_1_vtx_1[6] = {
    {{ {-43, 0, 75}, 0, {-16, -16}, {247, 130, 17, 0} }},
    {{ {-89, 0, 0}, 0, {-16, -16}, {236, 131, 0, 0} }},
    {{ {43, 0, 75}, 0, {-16, -16}, {9, 130, 17, 0} }},
    {{ {89, 0, 0}, 0, {-16, -16}, {20, 131, 0, 0} }},
    {{ {-43, 0, -75}, 0, {-16, -16}, {247, 130, 240, 0} }},
    {{ {43, 0, -75}, 0, {-16, -16}, {9, 130, 240, 0} }},
};

Gfx toad_cap_mesh_layer_1_tri_1[] = {
    gsSPVertex(toad_cap_mesh_layer_1_vtx_1 + 0, 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 2, 1, 0),
    gsSP2Triangles(4, 3, 1, 0, 5, 3, 4, 0),
    gsSPEndDisplayList(),
};

Vtx toad_cap_mesh_layer_5_vtx_0[100] = {
    {{ {-175, 118, 0}, 0, {-418, 482}, {134, 35, 0, 0} }},
    {{ {-70, 167, 123}, 0, {178, 72}, {212, 90, 78, 0} }},
    {{ {-141, 167, 0}, 0, {-280, 152}, {166, 90, 0, 0} }},
    {{ {176, 118, 0}, 0, {-16, -16}, {122, 35, 0, 0} }},
    {{ {88, 118, -152}, 0, {-16, -16}, {61, 36, 150, 0} }},
    {{ {71, 167, -122}, 0, {-16, -16}, {44, 91, 179, 0} }},
    {{ {142, 167, 0}, 0, {-16, -16}, {90, 90, 0, 0} }},
    {{ {71, 167, -122}, 0, {-26, 196}, {44, 91, 179, 0} }},
    {{ {-70, 167, -122}, 0, {888, 166}, {212, 91, 179, 0} }},
    {{ {-38, 201, -66}, 0, {646, -188}, {234, 119, 216, 0} }},
    {{ {88, 118, -152}, 0, {-106, 592}, {61, 36, 150, 0} }},
    {{ {-88, 118, -152}, 0, {1032, 556}, {195, 36, 151, 0} }},
    {{ {88, 63, -153}, 0, {-88, 942}, {61, 222, 150, 0} }},
    {{ {-88, 63, -153}, 0, {1050, 906}, {195, 222, 150, 0} }},
    {{ {176, 63, 0}, 0, {-196, 438}, {122, 222, 0, 0} }},
    {{ {88, 118, -152}, 0, {1220, 36}, {61, 36, 150, 0} }},
    {{ {176, 118, 0}, 0, {-198, -10}, {122, 35, 0, 0} }},
    {{ {88, 63, -153}, 0, {1222, 482}, {61, 222, 150, 0} }},
    {{ {142, 13, 0}, 0, {-54, 916}, {81, 158, 0, 0} }},
    {{ {71, 13, -123}, 0, {1084, 952}, {40, 158, 186, 0} }},
    {{ {71, 13, -123}, 0, {-16, -16}, {40, 158, 186, 0} }},
    {{ {-70, 13, -123}, 0, {-16, -16}, {216, 158, 186, 0} }},
    {{ {-88, 63, -153}, 0, {-16, -16}, {195, 222, 150, 0} }},
    {{ {88, 63, -153}, 0, {-16, -16}, {61, 222, 150, 0} }},
    {{ {-88, 63, -153}, 0, {-198, 414}, {195, 222, 150, 0} }},
    {{ {-175, 118, 0}, 0, {1372, 98}, {134, 35, 0, 0} }},
    {{ {-88, 118, -152}, 0, {-146, -82}, {195, 36, 151, 0} }},
    {{ {-175, 63, 0}, 0, {1320, 596}, {134, 222, 0, 0} }},
    {{ {-70, 13, -123}, 0, {-96, 882}, {216, 158, 186, 0} }},
    {{ {-141, 13, 0}, 0, {1122, 1024}, {175, 158, 0, 0} }},
    {{ {-88, 118, -152}, 0, {-16, -16}, {195, 36, 151, 0} }},
    {{ {-175, 118, 0}, 0, {-16, -16}, {134, 35, 0, 0} }},
    {{ {-141, 167, 0}, 0, {-16, -16}, {166, 90, 0, 0} }},
    {{ {-70, 167, -122}, 0, {-16, -16}, {212, 91, 179, 0} }},
    {{ {-141, 167, 0}, 0, {456, 1066}, {166, 90, 0, 0} }},
    {{ {-70, 167, 123}, 0, {1404, 676}, {212, 90, 78, 0} }},
    {{ {-38, 201, 69}, 0, {1000, 266}, {233, 118, 40, 0} }},
    {{ {-78, 201, 0}, 0, {474, 484}, {210, 118, 0, 0} }},
    {{ {0, 213, 0}, 0, {490, -104}, {0, 127, 0, 0} }},
    {{ {-38, 201, -66}, 0, {-38, 168}, {234, 119, 216, 0} }},
    {{ {-70, 167, -122}, 0, {-462, 496}, {212, 91, 179, 0} }},
    {{ {-175, 118, 0}, 0, {-370, -58}, {134, 35, 0, 0} }},
    {{ {-88, 118, 152}, 0, {1258, -4}, {195, 35, 106, 0} }},
    {{ {-70, 167, 123}, 0, {1100, -320}, {212, 90, 78, 0} }},
    {{ {-175, 63, 0}, 0, {-362, 392}, {134, 222, 0, 0} }},
    {{ {-88, 63, 152}, 0, {1264, 448}, {195, 220, 106, 0} }},
    {{ {-141, 13, 0}, 0, {-184, 898}, {175, 158, 0, 0} }},
    {{ {-70, 13, 120}, 0, {1120, 942}, {217, 157, 69, 0} }},
    {{ {39, 201, 69}, 0, {-16, -16}, {23, 118, 40, 0} }},
    {{ {79, 201, 0}, 0, {-16, -16}, {47, 118, 0, 0} }},
    {{ {0, 213, 0}, 0, {-16, -16}, {0, 127, 0, 0} }},
    {{ {-38, 201, 69}, 0, {-16, -16}, {233, 118, 40, 0} }},
    {{ {71, 167, 123}, 0, {2, 250}, {45, 90, 78, 0} }},
    {{ {79, 201, 0}, 0, {688, -162}, {47, 118, 0, 0} }},
    {{ {39, 201, 69}, 0, {194, -140}, {23, 118, 40, 0} }},
    {{ {142, 167, 0}, 0, {892, 212}, {90, 90, 0, 0} }},
    {{ {88, 118, 152}, 0, {-98, 640}, {61, 34, 106, 0} }},
    {{ {176, 118, 0}, 0, {1010, 594}, {122, 35, 0, 0} }},
    {{ {88, 63, 152}, 0, {-92, 952}, {61, 220, 106, 0} }},
    {{ {176, 63, 0}, 0, {1016, 906}, {122, 222, 0, 0} }},
    {{ {39, 201, 69}, 0, {780, -272}, {23, 118, 40, 0} }},
    {{ {-38, 201, 69}, 0, {304, -170}, {233, 118, 40, 0} }},
    {{ {71, 167, 123}, 0, {1036, -112}, {45, 90, 78, 0} }},
    {{ {43, 0, 75}, 0, {751, 1673}, {9, 130, 17, 0} }},
    {{ {89, 0, 0}, 0, {610, 1852}, {20, 131, 0, 0} }},
    {{ {142, 13, 0}, 0, {624, 1980}, {81, 158, 0, 0} }},
    {{ {71, 13, -123}, 0, {306, 1880}, {40, 158, 186, 0} }},
    {{ {43, 0, -75}, 0, {408, 1776}, {9, 130, 240, 0} }},
    {{ {-70, 13, -123}, 0, {250, 1518}, {216, 158, 186, 0} }},
    {{ {-43, 0, -75}, 0, {375, 1557}, {247, 130, 240, 0} }},
    {{ {-141, 13, 0}, 0, {508, 1254}, {175, 158, 0, 0} }},
    {{ {-89, 0, 0}, 0, {531, 1396}, {236, 131, 0, 0} }},
    {{ {-70, 13, 120}, 0, {826, 1356}, {217, 157, 69, 0} }},
    {{ {-43, 0, 75}, 0, {724, 1458}, {247, 130, 17, 0} }},
    {{ {43, 0, -75}, 0, {-16, -16}, {9, 130, 240, 0} }},
    {{ {89, 0, 0}, 0, {-16, -16}, {20, 131, 0, 0} }},
    {{ {-43, 0, -75}, 0, {-16, -16}, {247, 130, 240, 0} }},
    {{ {-89, 0, 0}, 0, {-16, -16}, {236, 131, 0, 0} }},
    {{ {43, 0, 75}, 0, {-16, -16}, {9, 130, 17, 0} }},
    {{ {-43, 0, 75}, 0, {-16, -16}, {247, 130, 17, 0} }},
    {{ {-70, 13, 120}, 0, {184, 1066}, {217, 157, 69, 0} }},
    {{ {88, 63, 152}, 0, {1214, 712}, {61, 220, 106, 0} }},
    {{ {-88, 63, 152}, 0, {34, 812}, {195, 220, 106, 0} }},
    {{ {88, 118, 152}, 0, {1186, 352}, {61, 34, 106, 0} }},
    {{ {-88, 118, 152}, 0, {6, 452}, {195, 35, 106, 0} }},
    {{ {71, 167, 123}, 0, {1050, -18}, {45, 90, 78, 0} }},
    {{ {-70, 167, 123}, 0, {104, 62}, {212, 90, 78, 0} }},
    {{ {71, 167, -122}, 0, {832, 1186}, {44, 91, 179, 0} }},
    {{ {-38, 201, -66}, 0, {1162, -70}, {234, 119, 216, 0} }},
    {{ {39, 201, -66}, 0, {654, 498}, {23, 118, 216, 0} }},
    {{ {0, 213, 0}, 0, {414, -278}, {0, 127, 0, 0} }},
    {{ {79, 201, 0}, 0, {-98, 326}, {47, 118, 0, 0} }},
    {{ {142, 167, 0}, 0, {-524, 874}, {90, 90, 0, 0} }},
    {{ {71, 13, 120}, 0, {82, 380}, {40, 157, 69, 0} }},
    {{ {142, 13, 0}, 0, {1024, 984}, {81, 158, 0, 0} }},
    {{ {176, 63, 0}, 0, {1466, 550}, {122, 222, 0, 0} }},
    {{ {43, 0, 75}, 0, {-11, 790}, {9, 130, 17, 0} }},
    {{ {-43, 0, 75}, 0, {-656, 946}, {247, 130, 17, 0} }},
    {{ {-70, 13, 120}, 0, {-982, 638}, {217, 157, 69, 0} }},
    {{ {88, 63, 152}, 0, {290, -208}, {61, 220, 106, 0} }},
};

Gfx toad_cap_mesh_layer_5_tri_0[] = {
    gsSPVertex(toad_cap_mesh_layer_5_vtx_0 + 0, 63, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 7, 8, 9, 0),
    gsSP2Triangles(10, 8, 7, 0, 10, 11, 8, 0),
    gsSP2Triangles(12, 11, 10, 0, 12, 13, 11, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 17, 15, 0),
    gsSP2Triangles(18, 17, 14, 0, 18, 19, 17, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 27, 25, 0),
    gsSP2Triangles(28, 27, 24, 0, 28, 29, 27, 0),
    gsSP2Triangles(30, 31, 32, 0, 30, 32, 33, 0),
    gsSP2Triangles(34, 35, 36, 0, 34, 36, 37, 0),
    gsSP2Triangles(37, 36, 38, 0, 39, 37, 38, 0),
    gsSP2Triangles(40, 37, 39, 0, 40, 34, 37, 0),
    gsSP2Triangles(41, 42, 43, 0, 44, 42, 41, 0),
    gsSP2Triangles(44, 45, 42, 0, 46, 45, 44, 0),
    gsSP2Triangles(46, 47, 45, 0, 48, 49, 50, 0),
    gsSP2Triangles(51, 48, 50, 0, 52, 53, 54, 0),
    gsSP2Triangles(52, 55, 53, 0, 56, 55, 52, 0),
    gsSP2Triangles(56, 57, 55, 0, 58, 57, 56, 0),
    gsSP2Triangles(58, 59, 57, 0, 1, 60, 61, 0),
    gsSP1Triangle(1, 62, 60, 0),
    gsSPVertex(toad_cap_mesh_layer_5_vtx_0 + 63, 37, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(1, 4, 3, 0, 4, 5, 3, 0),
    gsSP2Triangles(4, 6, 5, 0, 6, 7, 5, 0),
    gsSP2Triangles(6, 8, 7, 0, 8, 9, 7, 0),
    gsSP2Triangles(8, 10, 9, 0, 11, 12, 13, 0),
    gsSP2Triangles(13, 12, 14, 0, 12, 15, 14, 0),
    gsSP2Triangles(16, 14, 15, 0, 17, 18, 19, 0),
    gsSP2Triangles(19, 18, 20, 0, 19, 20, 21, 0),
    gsSP2Triangles(21, 20, 22, 0, 21, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 26, 25, 27, 0),
    gsSP2Triangles(28, 26, 27, 0, 29, 26, 28, 0),
    gsSP2Triangles(29, 24, 26, 0, 30, 31, 32, 0),
    gsSP2Triangles(33, 31, 30, 0, 34, 33, 30, 0),
    gsSP2Triangles(34, 30, 35, 0, 35, 30, 36, 0),
    gsSP1Triangle(30, 32, 36, 0),
    gsSPEndDisplayList(),
};

Vtx toad_cap_Wing_Cap_Wings_mesh_layer_4_vtx_0[8] = {
    {{ {-132, 118, -76}, 0, {974, 1996}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {-62, 145, -1}, 0, {-16, 1996}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {-192, 321, -94}, 0, {974, -16}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {-125, 348, -19}, 0, {-16, -16}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {192, 321, -94}, 0, {974, -16}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {62, 145, -1}, 0, {-16, 1996}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {132, 118, -76}, 0, {974, 1996}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {125, 348, -19}, 0, {-16, -16}, {0xff, 0xff, 0xff, 0xff} }},
};

Gfx toad_cap_Wing_Cap_Wings_mesh_layer_4_tri_0[] = {
    gsSPVertex(toad_cap_Wing_Cap_Wings_mesh_layer_4_vtx_0 + 0, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
    gsSPEndDisplayList(),
};

Vtx toad_cap_Wing_Cap_Wings_mesh_layer_4_vtx_1[8] = {
    {{ {-132, 118, -76}, 0, {-16, 1996}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {-192, 321, -94}, 0, {-16, -16}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {-261, 293, -171}, 0, {974, -16}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {-201, 90, -153}, 0, {974, 1996}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {261, 293, -171}, 0, {974, -16}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {192, 321, -94}, 0, {-16, -16}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {132, 118, -76}, 0, {-16, 1996}, {0xff, 0xff, 0xff, 0xff} }},
    {{ {201, 90, -153}, 0, {974, 1996}, {0xff, 0xff, 0xff, 0xff} }},
};

Gfx toad_cap_Wing_Cap_Wings_mesh_layer_4_tri_1[] = {
    gsSPVertex(toad_cap_Wing_Cap_Wings_mesh_layer_4_vtx_1 + 0, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};


Gfx mat_toad_cap_metal[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT),
    gsSPGeometryMode(0, G_TEXTURE_GEN),
    gsSPTexture(4032, 1984, 0, 0, 1),
    gsSPLight(&toad_cap_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_metal_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_metal_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(1, 0, 0, 252, 124),
    gsSPEndDisplayList(),
};

Gfx mat_revert_toad_cap_metal[] = {
    gsDPPipeSync(),
    gsSPGeometryMode(G_TEXTURE_GEN, 0),
    gsSPEndDisplayList(),
};

Gfx mat_toad_cap_base[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPCopyLightsPlayerPart(GLOVES),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_cap),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPEndDisplayList(),
};

Gfx mat_toad_cap_inside[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(SHADE, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, SHADE, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPCopyLightsPlayerPart(GLOVES),
    gsDPSetPrimColor(0, 0, 115, 115, 115, 255),
    gsSPEndDisplayList(),
};

Gfx mat_toad_cap_spots[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPCopyLightsPlayerPart(CAP),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_spots),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPEndDisplayList(),
};

Gfx mat_toad_cap_wing[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_wings_half_1),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsSPEndDisplayList(),
};

Gfx mat_revert_toad_cap_wing[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx mat_toad_cap_wing_tip[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_wings_half_2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsSPEndDisplayList(),
};

Gfx mat_revert_toad_cap_wing_tip[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx mat_toad_cap_metal_wing[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&toad_cap_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_metal_wings_half_1_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_metal_wings_half_1_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPEndDisplayList(),
};

Gfx mat_revert_toad_cap_metal_wing[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx mat_toad_cap_metal_wing_tip[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&toad_cap_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_metal_wings_half_2_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, toad_cap_texture_metal_wings_half_2_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPEndDisplayList(),
};

Gfx mat_revert_toad_cap_metal_wing_tip[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx toad_cap_mesh_layer_1[] = {
    gsSPDisplayList(mat_toad_cap_inside),
    gsSPDisplayList(toad_cap_mesh_layer_1_tri_1),
    gsSPEndDisplayList(),
};

Gfx toad_cap_mesh_layer_5[] = {
    gsSPDisplayList(mat_toad_cap_base),
    gsSPDisplayList(toad_cap_mesh_layer_1_tri_0),
    gsSPDisplayList(mat_toad_cap_spots),
    gsSPDisplayList(toad_cap_mesh_layer_5_tri_0),
    gsSPEndDisplayList(),
};

Gfx toad_cap_Metal_Cap_mesh_layer_1[] = {
    gsSPDisplayList(mat_toad_cap_metal),
    gsSPDisplayList(toad_cap_mesh_layer_1_tri_0),
    gsSPDisplayList(mat_revert_toad_cap_metal),
    gsSPEndDisplayList(),
};

Gfx toad_cap_Wing_Cap_Wings_mesh_layer_4[] = {
    gsSPDisplayList(mat_toad_cap_wing),
    gsSPDisplayList(toad_cap_Wing_Cap_Wings_mesh_layer_4_tri_0),
    gsSPDisplayList(mat_revert_toad_cap_wing),
    gsSPDisplayList(mat_toad_cap_wing_tip),
    gsSPDisplayList(toad_cap_Wing_Cap_Wings_mesh_layer_4_tri_1),
    gsSPDisplayList(mat_revert_toad_cap_wing_tip),
    gsSPEndDisplayList(),
};

Gfx toad_cap_Winged_Metal_Cap_Wings_mesh_layer_4[] = {
    gsSPDisplayList(mat_toad_cap_metal_wing),
    gsSPDisplayList(toad_cap_Wing_Cap_Wings_mesh_layer_4_tri_0),
    gsSPDisplayList(mat_revert_toad_cap_metal_wing),
    gsSPDisplayList(mat_toad_cap_metal_wing_tip),
    gsSPDisplayList(toad_cap_Wing_Cap_Wings_mesh_layer_4_tri_1),
    gsSPDisplayList(mat_revert_toad_cap_metal_wing_tip),
    gsSPEndDisplayList(),
};

Gfx toad_cap_material_revert_render_settings[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
    gsSPTexture(65535, 65535, 0, 0, 0),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetAlphaCompare(G_AC_NONE),

    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),

    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),

    gsSPEndDisplayList(),
};

