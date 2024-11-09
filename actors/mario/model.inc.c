#include "pc/rom_assets.h"
// Mario

// 0x04000000 # solid color blue - butt, left thigh, right thigh - all poly types
static const Lights1 mario_blue_lights_group = gdSPDefLights1(
    0x00, 0x00, 0x7f,
    0x00, 0x00, 0xff, 0x28, 0x28, 0x28
);

// 0x04000018 # solid color red - left & right arm, torso (tshirt part), caps - all poly types
static const Lights1 mario_red_lights_group = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x04000030 # solid color white - metal butt & left thigh - normal left & right hand closed & open (with cap too) and all wings - all poly types
static const Lights1 mario_white_lights_group = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x04000048 # solid color brown 1 - foot - all poly types
static const Lights1 mario_brown1_lights_group = gdSPDefLights1(
    0x39, 0x0e, 0x07,
    0x72, 0x1c, 0x0e, 0x28, 0x28, 0x28
);

// 0x04000060 # solid color beige skin - face (cap on and off dls) - all poly types
static const Lights1 mario_beige_lights_group = gdSPDefLights1(
    0x7f, 0x60, 0x3c,
    0xfe, 0xc1, 0x79, 0x28, 0x28, 0x28
);

// 0x04000078  # solid color brown 2 - hair - all poly types
static const Lights1 mario_brown2_lights_group = gdSPDefLights1(
    0x39, 0x03, 0x00,
    0x73, 0x06, 0x00, 0x28, 0x28, 0x28
);

static const Lights1 mario_black_lights_group = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

ALIGNED8 const Texture mario_texture_metal_shade[] = {
#include "actors/mario/custom_mario_metal_shade.rgba16.inc.c"
};

ALIGNED8 const Texture mario_texture_metal_light[] = {
#include "actors/mario/custom_mario_metal_light.rgba16.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(mario_texture_yellow_button, "actors/mario/mario_overalls_button.rgba16.inc.c", 0x00114750, 78432, 0x00001090, 2048);

ALIGNED8 const Texture mario_texture_m_logo[] = {
#include "actors/mario/custom_mario_logo.rgba16.inc.c"
};

ALIGNED8 const Texture mario_texture_m_blend[] = {
#include "actors/mario/custom_mario_logo_blend.rgba16.inc.c"
};

ALIGNED8 const Texture mario_texture_m_cap[] = {
#include "actors/mario/custom_mario_cap.rgba16.inc.c"
};

ALIGNED8 const Texture mario_texture_hair_sideburn[] = {
#include "actors/mario/custom_mario_sideburn.rgba16.inc.c"
};

ALIGNED8 const Texture mario_texture_add_sideburn[] = {
#include "actors/mario/custom_mario_sideburn_add.rgba16.inc.c"
};

ALIGNED8 const Texture mario_texture_skin_sideburn[] = {
#include "actors/mario/custom_mario_skin.rgba16.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(mario_texture_mustache, "actors/mario/mario_mustache.rgba16.inc.c", 0x00114750, 78432, 0x00002890, 2048);

ROM_ASSET_LOAD_TEXTURE(mario_texture_eyes_front, "actors/mario/mario_eyes_center.rgba16.inc.c", 0x00114750, 78432, 0x00003090, 2048);

ROM_ASSET_LOAD_TEXTURE(mario_texture_eyes_half_closed, "actors/mario/mario_eyes_half_closed.rgba16.inc.c", 0x00114750, 78432, 0x00003890, 2048);

ROM_ASSET_LOAD_TEXTURE(mario_texture_eyes_closed, "actors/mario/mario_eyes_closed.rgba16.inc.c", 0x00114750, 78432, 0x00004090, 2048);

ROM_ASSET_LOAD_TEXTURE(mario_texture_eyes_right, "actors/mario/mario_eyes_left_unused.rgba16.inc.c", 0x00114750, 78432, 0x00005890, 2048);

ROM_ASSET_LOAD_TEXTURE(mario_texture_eyes_left, "actors/mario/mario_eyes_right_unused.rgba16.inc.c", 0x00114750, 78432, 0x00006090, 2048);

ROM_ASSET_LOAD_TEXTURE(mario_texture_eyes_up, "actors/mario/mario_eyes_up_unused.rgba16.inc.c", 0x00114750, 78432, 0x00006890, 2048);

ROM_ASSET_LOAD_TEXTURE(mario_texture_eyes_down, "actors/mario/mario_eyes_down_unused.rgba16.inc.c", 0x00114750, 78432, 0x00007090, 2048);

ROM_ASSET_LOAD_TEXTURE(mario_texture_eyes_dead, "actors/mario/mario_eyes_dead.rgba16.inc.c", 0x00114750, 78432, 0x00007890, 2048);

ROM_ASSET_LOAD_TEXTURE(mario_texture_wings_half_1, "actors/mario/mario_wing.rgba16.inc.c", 0x00114750, 78432, 0x00008090, 4096);

ROM_ASSET_LOAD_TEXTURE(mario_texture_wings_half_2, "actors/mario/mario_wing_tip.rgba16.inc.c", 0x00114750, 78432, 0x00009090, 4096);

ALIGNED8 const Texture mario_texture_metal_wings_half_1_shade[] = {
#include "actors/mario/custom_mario_metal_wing_shade.rgba16.inc.c"
};

ALIGNED8 const Texture mario_texture_metal_wings_half_1_light[] = {
#include "actors/mario/custom_mario_metal_wing_light.rgba16.inc.c"
};

ALIGNED8 const Texture mario_texture_metal_wings_half_2_shade[] = {
#include "actors/mario/custom_mario_metal_wing_tip_shade.rgba16.inc.c"
};

ALIGNED8 const Texture mario_texture_metal_wings_half_2_light[] = {
#include "actors/mario/custom_mario_metal_wing_tip_light.rgba16.inc.c"
};

// 0x0400C090
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group1, 0x00114750, 78432, 0x0000c090, 240);

// 0x0400C180
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group2, 0x00114750, 78432, 0x0000c180, 224);

// 0x0400C260
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group3, 0x00114750, 78432, 0x0000c260, 256);

// 0x0400C360
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group4, 0x00114750, 78432, 0x0000c360, 240);

// 0x0400C450
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group5, 0x00114750, 78432, 0x0000c450, 240);

// 0x0400C540
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group6, 0x00114750, 78432, 0x0000c540, 240);

// 0x0400C630
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group7, 0x00114750, 78432, 0x0000c630, 240);

// 0x0400C720
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group8, 0x00114750, 78432, 0x0000c720, 256);

// 0x0400C820
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group9, 0x00114750, 78432, 0x0000c820, 256);

// 0x0400C920
ROM_ASSET_LOAD_VTX(mario_butt_dl_vertex_group10, 0x00114750, 78432, 0x0000c920, 224);

// 0x0400CA00 - 0x0400CC98
const Gfx mario_butt_dl[] = {
    gsSPVertex(mario_butt_dl_vertex_group1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  5, 10, 0x0),
    gsSP2Triangles( 4, 11, 10, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(mario_butt_dl_vertex_group2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  3, 13, 0x0,  6,  8, 12, 0x0),
    gsSPVertex(mario_butt_dl_vertex_group3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  1,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11,  9, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(mario_butt_dl_vertex_group4, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  2, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0, 11, 12,  7, 0x0),
    gsSP1Triangle(13, 11, 14, 0x0),
    gsSPVertex(mario_butt_dl_vertex_group5, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  2,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(mario_butt_dl_vertex_group6, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 0, 13, 12, 0x0),
    gsSPVertex(mario_butt_dl_vertex_group7, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  2,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 13, 14,  1, 0x0),
    gsSPVertex(mario_butt_dl_vertex_group8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles( 4, 11, 12, 0x0,  6, 11, 13, 0x0),
    gsSP2Triangles(13,  3, 14, 0x0, 15,  2,  1, 0x0),
    gsSPVertex(mario_butt_dl_vertex_group9, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  0,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  0, 13, 14, 0x0),
    gsSP1Triangle(15,  0, 14, 0x0),
    gsSPVertex(mario_butt_dl_vertex_group10, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  0, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 9,  1, 11, 0x0, 11, 12, 10, 0x0),
    gsSP1Triangle(10, 13,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400CC98 - 0x0400CCC8
const Gfx mario_butt[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(PANTS), // gsSPLight(&mario_blue_lights_group.a, 2),
    gsSPDisplayList(mario_butt_dl),
    gsSPEndDisplayList(),
};

// 0x0400CCC8 - 0x0400CD40
const Gfx mario_metal_butt[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT),
    gsSPSetGeometryMode(G_TEXTURE_GEN),
    gsSPTexture(4032, 1984, 0, 0, 1),
    gsSPLight(&mario_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(1, 0, 0, 252, 124),
    gsSPDisplayList(mario_butt_dl),
    gsSPEndDisplayList(),
};

// 0x0400CD40
ROM_ASSET_LOAD_VTX(mario_left_arm_shared_dl_vertex_group1, 0x00114750, 78432, 0x0000cd40, 240);

// 0x0400CE30
ROM_ASSET_LOAD_VTX(mario_left_arm_shared_dl_vertex_group2, 0x00114750, 78432, 0x0000ce30, 240);

// 0x0400CF20
ROM_ASSET_LOAD_VTX(mario_left_arm_shared_dl_vertex_group3, 0x00114750, 78432, 0x0000cf20, 224);

// 0x0400D000
ROM_ASSET_LOAD_VTX(mario_left_arm_shared_dl_vertex_group4, 0x00114750, 78432, 0x0000d000, 144);

// 0x0400D090 - 0x0400D1D8
const Gfx mario_left_arm_shared_dl[] = {
    gsSPVertex(mario_left_arm_shared_dl_vertex_group1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 9,  2,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 7, 12, 10, 0x0,  5, 13, 12, 0x0),
    gsSP2Triangles( 3, 14, 13, 0x0,  0, 11, 14, 0x0),
    gsSPVertex(mario_left_arm_shared_dl_vertex_group2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 1,  7,  6, 0x0,  2,  1,  6, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  8,  5,  3, 0x0),
    gsSP2Triangles( 3,  0,  9, 0x0,  9,  0,  2, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(mario_left_arm_shared_dl_vertex_group3, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  2,  4,  7, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  9,  0, 10, 0x0),
    gsSP2Triangles( 6,  9, 11, 0x0,  4,  6, 12, 0x0),
    gsSP1Triangle(13,  5,  3, 0x0),
    gsSPVertex(mario_left_arm_shared_dl_vertex_group4, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP1Triangle( 6,  8,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400D1D8 - 0x0400D1F8
const Gfx mario_left_arm[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(SHIRT), // gsSPLight(&mario_red_lights_group.a, 2),
    gsSPDisplayList(mario_left_arm_shared_dl),
    gsSPEndDisplayList(),
};

// 0x0400D1F8
ROM_ASSET_LOAD_VTX(mario_left_forearm_shared_dl_vertex, 0x00114750, 78432, 0x0000d1f8, 256);

// 0x0400D2F8 - 0x0400D3E8
const Gfx mario_left_forearm_shared_dl[] = {
    gsSPVertex(mario_left_forearm_shared_dl_vertex, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 9,  2,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 7, 12, 10, 0x0,  5, 13, 12, 0x0),
    gsSP2Triangles( 3, 14, 13, 0x0,  0, 11, 14, 0x0),
    gsSP2Triangles( 8, 15,  6, 0x0,  6, 15,  4, 0x0),
    gsSP2Triangles( 4, 15,  1, 0x0,  1, 15,  2, 0x0),
    gsSP2Triangles( 2, 15,  8, 0x0,  0, 14,  3, 0x0),
    gsSP2Triangles( 3, 13,  5, 0x0,  5, 12,  7, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0,  9, 11,  0, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 9,  0,  2, 0x0, 12, 13, 10, 0x0),
    gsSP2Triangles(13, 11, 10, 0x0, 13, 14, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400D3E8
ROM_ASSET_LOAD_VTX(mario_left_hand_closed_shared_dl_vertex_group1, 0x00114750, 78432, 0x0000d3e8, 256);

// 0x0400D4E8
ROM_ASSET_LOAD_VTX(mario_left_hand_closed_shared_dl_vertex_group2, 0x00114750, 78432, 0x0000d4e8, 224);

// 0x0400D5C8
ROM_ASSET_LOAD_VTX(mario_left_hand_closed_shared_dl_vertex_group3, 0x00114750, 78432, 0x0000d5c8, 240);

// 0x0400D6B8
ROM_ASSET_LOAD_VTX(mario_left_hand_closed_shared_dl_vertex_group4, 0x00114750, 78432, 0x0000d6b8, 160);

// 0x0400D758 - 0x0400D8F0
const Gfx mario_left_hand_closed_shared_dl[] = {
    gsSPVertex(mario_left_hand_closed_shared_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  1,  0, 0x0,  2,  1,  7, 0x0),
    gsSP2Triangles( 7,  1,  6, 0x0,  6,  4,  8, 0x0),
    gsSP2Triangles( 8,  4,  3, 0x0,  9,  3,  2, 0x0),
    gsSP2Triangles( 0, 10, 11, 0x0, 12, 10,  0, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(mario_left_hand_closed_shared_dl_vertex_group2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  1,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10,  3, 0x0,  1,  0,  9, 0x0),
    gsSP2Triangles( 9,  3,  1, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  7,  2,  8, 0x0),
    gsSP2Triangles( 8,  2, 11, 0x0, 11,  2,  5, 0x0),
    gsSP2Triangles( 9,  7,  6, 0x0,  6,  8, 12, 0x0),
    gsSP2Triangles(12,  8, 13, 0x0, 13,  5,  4, 0x0),
    gsSPVertex(mario_left_hand_closed_shared_dl_vertex_group3, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 5,  1,  0, 0x0,  6,  7,  2, 0x0),
    gsSP2Triangles( 8,  2,  3, 0x0,  3,  9, 10, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 11,  7,  6, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0,  6, 14, 12, 0x0),
    gsSPVertex(mario_left_hand_closed_shared_dl_vertex_group4, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9,  6, 0x0),
    gsSP1Triangle( 7,  1,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400D8F0 - 0x0400D910
const Gfx mario_left_hand_closed[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(GLOVES), // glove light, set in mario_misc.c
    gsSPDisplayList(mario_left_hand_closed_shared_dl),
    gsSPEndDisplayList(),
};

// 0x0400D910
ROM_ASSET_LOAD_VTX(mario_right_arm_shared_dl_vertex_group1, 0x00114750, 78432, 0x0000d910, 256);

// 0x0400DA10
ROM_ASSET_LOAD_VTX(mario_right_arm_shared_dl_vertex_group2, 0x00114750, 78432, 0x0000da10, 256);

// 0x0400DB10
ROM_ASSET_LOAD_VTX(mario_right_arm_shared_dl_vertex_group3, 0x00114750, 78432, 0x0000db10, 256);

// 0x0400DC10
ROM_ASSET_LOAD_VTX(mario_right_arm_shared_dl_vertex_group4, 0x00114750, 78432, 0x0000dc10, 144);

// 0x0400DCA0 - 0x0400DDE8
const Gfx mario_right_arm_shared_dl[] = {
    gsSPVertex(mario_right_arm_shared_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 9,  2,  8, 0x0,  1, 10,  2, 0x0),
    gsSP2Triangles( 2, 11,  8, 0x0,  8, 12,  6, 0x0),
    gsSP2Triangles( 6, 13,  4, 0x0,  4, 14,  1, 0x0),
    gsSP2Triangles( 9, 15,  0, 0x0,  0, 15,  3, 0x0),
    gsSPVertex(mario_right_arm_shared_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  6,  4, 0x0),
    gsSP2Triangles( 1,  6,  3, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  7,  0, 0x0,  5,  4,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12,  9, 13, 0x0),
    gsSP1Triangle(14, 12, 15, 0x0),
    gsSPVertex(mario_right_arm_shared_dl_vertex_group3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  5,  2, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles( 6, 10, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(mario_right_arm_shared_dl_vertex_group4, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP1Triangle( 5,  8,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400DDE8 - 0x0400DE08
const Gfx mario_right_arm[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(SHIRT), // gsSPLight(&mario_red_lights_group.a, 2),
    gsSPDisplayList(mario_right_arm_shared_dl),
    gsSPEndDisplayList(),
};

// 0x0400DE08
ROM_ASSET_LOAD_VTX(mario_right_forearm_shared_dl_vertex, 0x00114750, 78432, 0x0000de08, 256);

// 0x0400DF08 - 0x0400DFF8
const Gfx mario_right_forearm_shared_dl[] = {
    gsSPVertex(mario_right_forearm_shared_dl_vertex, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 9,  2,  8, 0x0,  1, 10,  2, 0x0),
    gsSP2Triangles( 2, 11,  8, 0x0,  8, 12,  6, 0x0),
    gsSP2Triangles( 6, 13,  4, 0x0,  4, 14,  1, 0x0),
    gsSP2Triangles( 9, 15,  0, 0x0,  0, 15,  3, 0x0),
    gsSP2Triangles( 3, 15,  5, 0x0,  5, 15,  7, 0x0),
    gsSP2Triangles( 7, 15,  9, 0x0, 14, 10,  1, 0x0),
    gsSP2Triangles(13, 14,  4, 0x0, 12, 13,  6, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0, 10, 11,  2, 0x0),
    gsSP2Triangles( 9,  0,  2, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 5,  7,  6, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0, 11, 13, 12, 0x0),
    gsSP2Triangles(11, 10, 13, 0x0, 10, 14, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400DFF8
ROM_ASSET_LOAD_VTX(mario_right_hand_closed_dl_vertex_group1, 0x00114750, 78432, 0x0000dff8, 256);

// 0x0400E0F8
ROM_ASSET_LOAD_VTX(mario_right_hand_closed_dl_vertex_group2, 0x00114750, 78432, 0x0000e0f8, 224);

// 0x0400E1D8
ROM_ASSET_LOAD_VTX(mario_right_hand_closed_dl_vertex_group3, 0x00114750, 78432, 0x0000e1d8, 240);

// 0x0400E2C8 - 0x0400E458
const Gfx mario_right_hand_closed_dl[] = {
    gsSPVertex(mario_right_hand_closed_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9,  5,  2, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0, 14, 12,  8, 0x0),
    gsSP2Triangles( 8, 12,  9, 0x0,  9, 12, 11, 0x0),
    gsSP1Triangle( 3, 15,  0, 0x0),
    gsSPVertex(mario_right_hand_closed_dl_vertex_group2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 8,  7,  1, 0x0,  1,  7,  4, 0x0),
    gsSP2Triangles( 4,  7,  9, 0x0, 10,  7,  6, 0x0),
    gsSP2Triangles( 9, 10,  5, 0x0, 10, 11,  5, 0x0),
    gsSP2Triangles(11, 12,  5, 0x0,  1,  4,  3, 0x0),
    gsSP2Triangles(11, 10,  6, 0x0,  6, 13, 11, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0,  4,  9,  5, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  6,  8,  0, 0x0),
    gsSPVertex(mario_right_hand_closed_dl_vertex_group3, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  0, 0x0,  8,  6,  5, 0x0),
    gsSP2Triangles( 9,  3,  1, 0x0,  0,  6,  8, 0x0),
    gsSP2Triangles(10, 11,  1, 0x0, 11,  9,  1, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0,  1,  0, 10, 0x0),
    gsSP2Triangles(13,  5,  3, 0x0,  3,  9, 14, 0x0),
    gsSP1Triangle(14, 13,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400E458 - 0x0400E478
const Gfx mario_right_hand_closed[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(GLOVES), // glove light, set in mario_misc.c
    gsSPDisplayList(mario_right_hand_closed_dl),
    gsSPEndDisplayList(),
};

// 0x0400E478 - 0x0400E4A8
const Gfx mario_metal_right_hand_closed[] = {
    gsSPDisplayList(mario_right_hand_closed_dl),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0F80, 0x07C0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

// 0x0400E4A8
ROM_ASSET_LOAD_VTX(mario_left_thigh_dl_vertex_group1, 0x00114750, 78432, 0x0000e4a8, 256);

// 0x0400E5A8
ROM_ASSET_LOAD_VTX(mario_left_thigh_dl_vertex_group2, 0x00114750, 78432, 0x0000e5a8, 256);

// 0x0400E6A8 - 0x0400E7B0
const Gfx mario_left_thigh_dl[] = {
    gsSPVertex(mario_left_thigh_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0, 10,  7, 11, 0x0),
    gsSP2Triangles(11,  7,  6, 0x0, 12,  3, 13, 0x0),
    gsSP2Triangles(13,  4, 14, 0x0, 14,  4, 15, 0x0),
    gsSPVertex(mario_left_thigh_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 7,  0,  8, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles( 3,  9, 10, 0x0,  2,  3,  6, 0x0),
    gsSP2Triangles( 3, 11,  6, 0x0, 10, 11,  3, 0x0),
    gsSP2Triangles( 7,  8, 10, 0x0,  0, 12,  8, 0x0),
    gsSP2Triangles( 6, 12,  0, 0x0,  1, 13,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0, 14,  4,  0, 0x0),
    gsSP2Triangles( 9, 15, 14, 0x0,  3, 13, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400E7B0 - 0x0400E7E0
const Gfx mario_left_thigh[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(PANTS), // gsSPLight(&mario_blue_lights_group.a, 2),
    gsSPDisplayList(mario_left_thigh_dl),
    gsSPEndDisplayList(),
};

// 0x0400E7E0 - 0x0400E858
const Gfx mario_metal_left_thigh[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT),
    gsSPSetGeometryMode(G_TEXTURE_GEN),
    gsSPTexture(4032, 1984, 0, 0, 1),
    gsSPLight(&mario_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(1, 0, 0, 252, 124),
    gsSPDisplayList(mario_left_thigh_dl),
    gsSPEndDisplayList(),
};

// 0x0400E858
ROM_ASSET_LOAD_VTX(mario_left_leg_shared_dl_vertex, 0x00114750, 78432, 0x0000e858, 192);

// 0x0400E918 - 0x0400E9C8
const Gfx mario_left_leg_shared_dl[] = {
    gsSPVertex(mario_left_leg_shared_dl_vertex, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 0,  7,  1, 0x0,  0,  8,  7, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  5,  6,  3, 0x0),
    gsSP2Triangles( 3,  9,  2, 0x0,  2,  9,  0, 0x0),
    gsSP2Triangles( 3, 10,  9, 0x0,  5, 11,  7, 0x0),
    gsSP2Triangles( 7, 11,  1, 0x0,  1, 11,  2, 0x0),
    gsSP2Triangles( 2, 11,  4, 0x0,  4, 11,  5, 0x0),
    gsSP2Triangles( 9, 10,  0, 0x0,  0, 10,  8, 0x0),
    gsSP2Triangles( 8, 10,  6, 0x0,  6, 10,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400E9C8
ROM_ASSET_LOAD_VTX(mario_left_foot_shared_dl_vertex_group1, 0x00114750, 78432, 0x0000e9c8, 256);

// 0x0400EAC8
ROM_ASSET_LOAD_VTX(mario_left_foot_shared_dl_vertex_group2, 0x00114750, 78432, 0x0000eac8, 240);

// 0x0400EBB8 - 0x0400ECA0
const Gfx mario_left_foot_shared_dl[] = {
    gsSPVertex(mario_left_foot_shared_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  3,  4, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14,  8, 10, 0x0, 11, 13, 15, 0x0),
    gsSPVertex(mario_left_foot_shared_dl_vertex_group2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 2,  3,  0, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 6,  3,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(12,  9, 10, 0x0,  9, 12,  7, 0x0),
    gsSP2Triangles(14,  0,  3, 0x0, 11,  0, 14, 0x0),
    gsSP2Triangles( 3,  6, 14, 0x0, 14,  6,  7, 0x0),
    gsSP2Triangles(14,  7, 12, 0x0, 12, 11, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400ECA0 - 0x0400ECC0
const Gfx mario_left_foot[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(SHOES),
    gsSPDisplayList(mario_left_foot_shared_dl),
    gsSPEndDisplayList(),
};

// 0x0400ECC0
ROM_ASSET_LOAD_VTX(mario_right_thigh_shared_dl_vertex_group1, 0x00114750, 78432, 0x0000ecc0, 256);

// 0x0400EDC0
ROM_ASSET_LOAD_VTX(mario_right_thigh_shared_dl_vertex_group2, 0x00114750, 78432, 0x0000edc0, 240);

// 0x0400EEB0 - 0x0400EFB8
const Gfx mario_right_thigh_shared_dl[] = {
    gsSPVertex(mario_right_thigh_shared_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 1,  8,  2, 0x0,  2,  8,  7, 0x0),
    gsSP2Triangles( 7, 11,  5, 0x0,  5, 11,  4, 0x0),
    gsSP2Triangles( 4, 12,  1, 0x0, 13, 14,  0, 0x0),
    gsSP2Triangles( 0, 14, 15, 0x0, 15, 14,  3, 0x0),
    gsSP2Triangles( 3, 14,  6, 0x0,  6, 14, 13, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 11,  9, 12, 0x0),
    gsSPVertex(mario_right_thigh_shared_dl_vertex_group2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  0,  6, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  3,  8,  7, 0x0),
    gsSP2Triangles( 4,  2,  3, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11,  9,  7, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles( 4, 14, 12, 0x0, 10, 14,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400EFB8 - 0x0400EFD8
const Gfx mario_right_thigh[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(PANTS), // gsSPLight(&mario_blue_lights_group.a, 2),
    gsSPDisplayList(mario_right_thigh_shared_dl),
    gsSPEndDisplayList(),
};

// 0x0400EFD8
ROM_ASSET_LOAD_VTX(mario_right_leg_shared_dl_vertex_group1, 0x00114750, 78432, 0x0000efd8, 256);

// 0x0400F0D8
ROM_ASSET_LOAD_VTX(mario_right_leg_shared_dl_vertex_group2, 0x00114750, 78432, 0x0000f0d8, 256);

// 0x0400F1D8 - 0x0400F290
const Gfx mario_right_leg_shared_dl[] = {
    gsSPVertex(mario_right_leg_shared_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles(11, 12,  2, 0x0, 13, 14,  2, 0x0),
    gsSP2Triangles( 2, 14, 15, 0x0, 15, 14,  8, 0x0),
    gsSP2Triangles( 8, 14,  5, 0x0,  5, 14, 13, 0x0),
    gsSPVertex(mario_right_leg_shared_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 5,  1,  0, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15, 13,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400F290
ROM_ASSET_LOAD_VTX(mario_right_foot_dl_vertex_group1, 0x00114750, 78432, 0x0000f290, 240);

// 0x0400F380
ROM_ASSET_LOAD_VTX(mario_right_foot_dl_vertex_group2, 0x00114750, 78432, 0x0000f380, 128);

// 0x0400F400 - 0x0400F4E8
const Gfx mario_right_foot_dl[] = {
    gsSPVertex(mario_right_foot_dl_vertex_group1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  5,  6,  0, 0x0),
    gsSP2Triangles( 3,  2,  7, 0x0,  8,  7,  2, 0x0),
    gsSP2Triangles( 1,  9,  8, 0x0,  2,  1,  8, 0x0),
    gsSP2Triangles( 7, 10,  3, 0x0, 11,  5,  4, 0x0),
    gsSP2Triangles( 4, 12, 11, 0x0,  6,  5, 13, 0x0),
    gsSP2Triangles(11, 13,  5, 0x0, 13, 14,  6, 0x0),
    gsSP2Triangles(14,  9,  6, 0x0, 10,  4,  3, 0x0),
    gsSP2Triangles( 9,  1,  6, 0x0, 10, 12,  4, 0x0),
    gsSPVertex(mario_right_foot_dl_vertex_group2, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  5,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400F4E8 - 0x0400F528
const Gfx mario_right_foot[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(SHOES),
    gsSPDisplayList(mario_right_foot_dl),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

// 0x0400F528 - 0x0400F568
const Gfx mario_metal_right_foot[] = {
    gsSPDisplayList(mario_right_foot_dl),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0F80, 0x07C0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

// 0x0400F568
ROM_ASSET_LOAD_VTX(mario_yellow_button_dl_vertex, 0x00114750, 78432, 0x0000f568, 224);

// 0x0400F648
ROM_ASSET_LOAD_VTX(mario_tshirt_shared_dl_vertex_group1, 0x00114750, 78432, 0x0000f648, 256);

// 0x0400F748
ROM_ASSET_LOAD_VTX(mario_tshirt_shared_dl_vertex_group2, 0x00114750, 78432, 0x0000f748, 224);

// 0x0400F828
ROM_ASSET_LOAD_VTX(mario_tshirt_shared_dl_vertex_group3, 0x00114750, 78432, 0x0000f828, 80);

// 0x0400F878
ROM_ASSET_LOAD_VTX(mario_pants_overalls_shared_dl_vertex_group1, 0x00114750, 78432, 0x0000f878, 240);

// 0x0400F968
ROM_ASSET_LOAD_VTX(mario_pants_overalls_shared_dl_vertex_group2, 0x00114750, 78432, 0x0000f968, 256);

// 0x0400FA68
ROM_ASSET_LOAD_VTX(mario_pants_overalls_shared_dl_vertex_group3, 0x00114750, 78432, 0x0000fa68, 256);

// 0x0400FB68
ROM_ASSET_LOAD_VTX(mario_pants_overalls_shared_dl_vertex_group4, 0x00114750, 78432, 0x0000fb68, 256);

// 0x0400FC68
ROM_ASSET_LOAD_VTX(mario_pants_overalls_shared_dl_vertex_group5, 0x00114750, 78432, 0x0000fc68, 224);

// 0x0400FD48
ROM_ASSET_LOAD_VTX(mario_pants_overalls_shared_dl_vertex_group6, 0x00114750, 78432, 0x0000fd48, 240);

// 0x0400FE38
ROM_ASSET_LOAD_VTX(mario_pants_overalls_shared_dl_vertex_group7, 0x00114750, 78432, 0x0000fe38, 240);

// 0x0400FF28 - 0x0400FF88
const Gfx mario_yellow_button_dl[] = {
    gsSPVertex(mario_yellow_button_dl_vertex, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  5,  6,  2, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 13, 10,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0400FF88 - 0x04010260
const Gfx mario_pants_overalls_shared_dl[] = {
    gsSPVertex(mario_pants_overalls_shared_dl_vertex_group1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  1,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 7,  5,  8, 0x0,  9,  6,  7, 0x0),
    gsSP2Triangles( 7,  8, 10, 0x0, 10, 11,  7, 0x0),
    gsSP2Triangles( 9,  7, 11, 0x0, 12,  6, 13, 0x0),
    gsSP2Triangles( 9, 13,  6, 0x0,  6, 12, 14, 0x0),
    gsSPVertex(mario_pants_overalls_shared_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 7, 10, 11, 0x0, 11,  8,  7, 0x0),
    gsSP2Triangles(12,  8, 11, 0x0, 13,  0,  2, 0x0),
    gsSP2Triangles( 2,  1, 14, 0x0,  2, 15, 13, 0x0),
    gsSPVertex(mario_pants_overalls_shared_dl_vertex_group3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  8,  6, 0x0),
    gsSP2Triangles( 5,  9,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0, 11, 10,  8, 0x0),
    gsSP2Triangles( 9, 11,  8, 0x0,  6, 12,  7, 0x0),
    gsSP2Triangles(12,  6, 10, 0x0,  7, 12, 13, 0x0),
    gsSP2Triangles(14,  5, 15, 0x0, 14,  9,  5, 0x0),
    gsSPVertex(mario_pants_overalls_shared_dl_vertex_group4, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  2,  3,  7, 0x0),
    gsSP2Triangles( 7,  3,  5, 0x0,  8,  2,  7, 0x0),
    gsSP2Triangles( 2,  8,  0, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 11,  7, 13, 0x0),
    gsSP1Triangle(14, 15, 11, 0x0),
    gsSPVertex(mario_pants_overalls_shared_dl_vertex_group5, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  0, 0x0,  6,  0,  7, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  9,  7,  4, 0x0),
    gsSP2Triangles( 7, 10, 11, 0x0, 11,  6,  7, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0, 10,  9, 13, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPVertex(mario_pants_overalls_shared_dl_vertex_group6, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(14, 12, 13, 0x0, 11, 10,  9, 0x0),
    gsSPVertex(mario_pants_overalls_shared_dl_vertex_group7, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0,  9,  8,  5, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0, 11,  1,  0, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  6, 14,  4, 0x0),
    gsSP1Triangle(11,  0, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x04010260 - 0x04010348
const Gfx mario_tshirt_shared_dl[] = {
    gsSPVertex(mario_tshirt_shared_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles(12,  8,  7, 0x0,  8, 11, 10, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(mario_tshirt_shared_dl_vertex_group2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 6,  2,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(12,  3,  4, 0x0, 13,  3, 12, 0x0),
    gsSP1Triangle( 6,  3, 13, 0x0),
    gsSPVertex(mario_tshirt_shared_dl_vertex_group3, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP1Triangle( 1,  4,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x04010348 - 0x04010370
const Gfx mario_torso_dl[] = {
    gsSPDisplayList(mario_pants_overalls_shared_dl),
    gsSPCopyLightsPlayerPart(SHIRT), // gsSPLight(&mario_red_lights_group.a, 2),
    gsSPDisplayList(mario_tshirt_shared_dl),
    gsSPEndDisplayList(),
};

// 0x04010370 - 0x040103F0
const Gfx mario_torso[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_yellow_button),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_yellow_button_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_torso_dl),
    gsSPEndDisplayList(),
};

// 0x040103F0 - 0x04010410
const Gfx mario_metal_torso_shared_dl[] = {
    gsSPDisplayList(mario_yellow_button_dl),
    gsSPDisplayList(mario_pants_overalls_shared_dl),
    gsSPDisplayList(mario_tshirt_shared_dl),
    gsSPEndDisplayList(),
};

// 0x04010410
ROM_ASSET_LOAD_VTX(mario_m_logo_dl_vertex, 0x00114750, 78432, 0x00010410, 112);

// 0x04010480
ROM_ASSET_LOAD_VTX(mario_eyes_cap_on_dl_vertex, 0x00114750, 78432, 0x00010480, 192);

// 0x04010540
ROM_ASSET_LOAD_VTX(mario_hair_sideburn_cap_on_dl_vertex, 0x00114750, 78432, 0x00010540, 192);

// 0x04010600
ROM_ASSET_LOAD_VTX(mario_mustache_cap_on_dl_vertex_group1, 0x00114750, 78432, 0x00010600, 256);

// 0x04010700
ROM_ASSET_LOAD_VTX(mario_mustache_cap_on_dl_vertex_group2, 0x00114750, 78432, 0x00010700, 80);

// 0x04010750
ROM_ASSET_LOAD_VTX(mario_face_cap_dl_vertex_group1, 0x00114750, 78432, 0x00010750, 256);

// 0x04010850
ROM_ASSET_LOAD_VTX(mario_face_cap_dl_vertex_group2, 0x00114750, 78432, 0x00010850, 240);

// 0x04010940
ROM_ASSET_LOAD_VTX(mario_face_cap_dl_vertex_group3, 0x00114750, 78432, 0x00010940, 240);

// 0x04010A30
ROM_ASSET_LOAD_VTX(mario_face_part_cap_on_dl_vertex_group1, 0x00114750, 78432, 0x00010a30, 240);

// 0x04010B20
ROM_ASSET_LOAD_VTX(mario_face_part_cap_on_dl_vertex_group2, 0x00114750, 78432, 0x00010b20, 256);

// 0x04010C20
ROM_ASSET_LOAD_VTX(mario_face_part_cap_on_dl_vertex_group3, 0x00114750, 78432, 0x00010c20, 240);

// 0x04010D10
ROM_ASSET_LOAD_VTX(mario_face_part_cap_on_dl_vertex_group4, 0x00114750, 78432, 0x00010d10, 256);

// 0x04010E10
ROM_ASSET_LOAD_VTX(mario_face_part_cap_on_dl_vertex_group5, 0x00114750, 78432, 0x00010e10, 240);

// 0x04010F00
ROM_ASSET_LOAD_VTX(mario_face_part_cap_on_dl_vertex_group6, 0x00114750, 78432, 0x00010f00, 256);

// 0x04011000
ROM_ASSET_LOAD_VTX(mario_face_part_cap_on_dl_vertex_group7, 0x00114750, 78432, 0x00011000, 208);

// 0x040110D0
ROM_ASSET_LOAD_VTX(mario_face_back_hair_cap_on_dl_vertex_group1, 0x00114750, 78432, 0x000110d0, 256);

// 0x040111D0
ROM_ASSET_LOAD_VTX(mario_face_back_hair_cap_on_dl_vertex_group2, 0x00114750, 78432, 0x000111d0, 224);

// 0x040112B0 - 0x040112E8
const Gfx mario_m_logo_dl[] = {
    gsSPVertex(mario_m_logo_dl_vertex, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  3,  0, 0x0,  3,  5,  0, 0x0),
    gsSP1Triangle( 4,  6,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x040112E8 - 0x04011350
const Gfx mario_eyes_cap_on_dl[] = {
    gsSPVertex(mario_eyes_cap_on_dl_vertex, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  6,  3,  5, 0x0),
    gsSP2Triangles( 3,  1,  0, 0x0,  4,  0,  7, 0x0),
    gsSP2Triangles( 5,  4,  8, 0x0,  2,  9, 10, 0x0),
    gsSP2Triangles(10,  7,  2, 0x0, 11,  7, 10, 0x0),
    gsSP1Triangle( 7,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x04011350 - 0x040113A0
const Gfx mario_hair_sideburn_cap_on_dl[] = {
    gsSPVertex(mario_hair_sideburn_cap_on_dl_vertex, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 9, 10,  6, 0x0, 11,  6, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x040113A0 - 0x04011438
const Gfx mario_mustache_cap_on_dl[] = {
    gsSPVertex(mario_mustache_cap_on_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  5,  3,  4, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  3,  7,  1, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 10, 13, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 10,  9, 14, 0x0),
    gsSP1Triangle(15,  9, 11, 0x0),
    gsSPVertex(mario_mustache_cap_on_dl_vertex_group2, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP1Triangle( 2,  4,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x04011438 - 0x040116F8
const Gfx mario_face_part_cap_on_dl[] = {
    gsSPVertex(mario_face_part_cap_on_dl_vertex_group1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  1,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 9,  4,  8, 0x0, 10,  6,  5, 0x0),
    gsSP2Triangles(10,  5, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(mario_face_part_cap_on_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  5,  6,  8, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  9,  3,  7, 0x0),
    gsSP2Triangles( 3,  9,  4, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 10,  0, 11, 0x0),
    gsSP2Triangles(11,  0,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(mario_face_part_cap_on_dl_vertex_group3, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  3,  0,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles(12, 13,  8, 0x0,  8, 13, 11, 0x0),
    gsSP1Triangle( 9, 11, 14, 0x0),
    gsSPVertex(mario_face_part_cap_on_dl_vertex_group4, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  2,  4, 0x0,  2,  6,  3, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  9,  3, 0x0),
    gsSP2Triangles( 9,  4,  3, 0x0,  7, 10,  3, 0x0),
    gsSP2Triangles( 3, 10,  8, 0x0, 11,  4,  9, 0x0),
    gsSP2Triangles(12, 11,  9, 0x0, 13,  9,  8, 0x0),
    gsSP2Triangles( 9, 13, 12, 0x0,  4, 11,  5, 0x0),
    gsSP1Triangle(14, 15, 11, 0x0),
    gsSPVertex(mario_face_part_cap_on_dl_vertex_group5, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  1,  3,  5, 0x0),
    gsSP2Triangles( 2,  1,  6, 0x0,  2,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  6,  5, 11, 0x0),
    gsSP2Triangles(12, 13,  8, 0x0, 10, 12,  8, 0x0),
    gsSP1Triangle(14,  8, 13, 0x0),
    gsSPVertex(mario_face_part_cap_on_dl_vertex_group6, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  6,  5,  8, 0x0),
    gsSP2Triangles( 5,  7,  3, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 6, 12,  7, 0x0, 13, 10,  9, 0x0),
    gsSP2Triangles(14, 13,  9, 0x0, 15, 10, 13, 0x0),
    gsSPVertex(mario_face_part_cap_on_dl_vertex_group7, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 1,  5,  3, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 7,  9,  3, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12,  6, 10, 0x0),
    gsSP1Triangle(12,  8,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x040116F8 - 0x04011870
const Gfx mario_face_cap_dl[] = {
    gsSPVertex(mario_face_cap_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  1,  6, 0x0,  6,  7,  2, 0x0),
    gsSP2Triangles( 5,  2,  7, 0x0,  6,  1,  8, 0x0),
    gsSP2Triangles( 8,  1,  0, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  6, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles(11,  8, 12, 0x0,  0, 12,  8, 0x0),
    gsSP2Triangles(13, 10, 11, 0x0, 11, 12, 14, 0x0),
    gsSP2Triangles(15, 11, 14, 0x0, 13, 11, 15, 0x0),
    gsSPVertex(mario_face_cap_dl_vertex_group2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 7,  1,  8, 0x0,  8,  1,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP2Triangles(12,  9, 13, 0x0, 13,  9, 14, 0x0),
    gsSPVertex(mario_face_cap_dl_vertex_group3, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9,  5, 0x0,  0, 10,  1, 0x0),
    gsSP2Triangles( 1, 10,  3, 0x0, 11, 10,  0, 0x0),
    gsSP2Triangles(12,  3, 10, 0x0, 12, 10, 13, 0x0),
    gsSP2Triangles(13, 10, 11, 0x0,  5,  9,  7, 0x0),
    gsSP1Triangle( 7,  9, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x04011870 - 0x04011960
const Gfx mario_face_back_hair_cap_on_dl[] = {
    gsSPVertex(mario_face_back_hair_cap_on_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 5,  4,  8, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 0,  6,  8, 0x0,  3,  7, 10, 0x0),
    gsSP2Triangles( 1, 11, 12, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(11, 13, 12, 0x0,  1, 12,  2, 0x0),
    gsSP2Triangles(14,  2, 12, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(mario_face_back_hair_cap_on_dl_vertex_group2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  3,  2, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0,  2, 11,  7, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0, 10,  9, 13, 0x0),
    gsSP1Triangle( 8, 12,  9, 0x0),
    gsSPEndDisplayList(),
};

const Gfx mario_hair_sideburn_decal_cap_on[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 11),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_hair_sideburn),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_add_sideburn),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsSPDisplayList(mario_hair_sideburn_cap_on_dl),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPCopyLightsPlayerPart(SKIN),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_skin_sideburn),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPDisplayList(mario_hair_sideburn_cap_on_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

const Gfx mario_m_logo_decal[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, SHADE, TEXEL1, SHADE, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, SHADE, TEXEL1, SHADE, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 17),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_m_logo),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_m_blend),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsSPDisplayList(mario_m_logo_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, TEXEL1, 0, ENVIRONMENT, 0, TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, TEXEL1, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPCopyLightsPlayerPart(CAP),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_m_logo),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_m_cap),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsSPDisplayList(mario_m_logo_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x04011960 - 0x040119A0
const Gfx mario_face_cap_on_dl[] = {
    gsSPDisplayList(mario_face_part_cap_on_dl),
    gsSPCopyLightsPlayerPart(CAP),
    gsSPDisplayList(mario_face_cap_dl),
    gsSPCopyLightsPlayerPart(HAIR),
    gsSPDisplayList(mario_face_back_hair_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x040119A0 - 0x04011A90
const Gfx mario_cap_on_eyes_front[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_front),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_on_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_on_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x04011A90 - 0x04011B80
const Gfx mario_cap_on_eyes_half_closed[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_half_closed),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_on_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_on_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x04011B80 - 0x04011C70
const Gfx mario_cap_on_eyes_closed[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_closed),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_on_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_on_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x04011C70 - 0x04011D60
const Gfx mario_cap_on_eyes_right[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_right),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_on_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_on_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x04011D60 - 0x04011E50
const Gfx mario_cap_on_eyes_left[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_left),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_on_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_on_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x04011E50 - 0x04011F40
const Gfx mario_cap_on_eyes_up[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_up),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_on_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_on_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x04011F40 - 0x04012030
const Gfx mario_cap_on_eyes_down[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_down),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_on_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_on_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x04012030 - 0x04012120
const Gfx mario_cap_on_eyes_dead[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_dead),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_on_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_on_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x04012120 - 0x04012160
const Gfx mario_metal_cap_on_shared_dl[] = {
    gsSPDisplayList(mario_m_logo_dl),
    gsSPDisplayList(mario_eyes_cap_on_dl),
    gsSPDisplayList(mario_hair_sideburn_cap_on_dl),
    gsSPDisplayList(mario_mustache_cap_on_dl),
    gsSPDisplayList(mario_face_part_cap_on_dl),
    gsSPDisplayList(mario_face_cap_dl),
    gsSPDisplayList(mario_face_back_hair_cap_on_dl),
    gsSPEndDisplayList(),
};

// 0x04012190
ROM_ASSET_LOAD_VTX(mario_eyes_cap_off_dl_vertex, 0x00114750, 78432, 0x00012190, 192);

// 0x04012250
ROM_ASSET_LOAD_VTX(mario_hair_sideburn_cap_off_dl_vertex, 0x00114750, 78432, 0x00012250, 192);

// 0x04012310
ROM_ASSET_LOAD_VTX(mario_mustache_cap_off_dl_vertex_group1, 0x00114750, 78432, 0x00012310, 256);

// 0x04012410
ROM_ASSET_LOAD_VTX(mario_mustache_cap_off_dl_vertex_group2, 0x00114750, 78432, 0x00012410, 80);

// 0x04012460
ROM_ASSET_LOAD_VTX(mario_face_part_cap_off_dl_vertex_group1, 0x00114750, 78432, 0x00012460, 240);

// 0x04012550
ROM_ASSET_LOAD_VTX(mario_face_part_cap_off_dl_vertex_group2, 0x00114750, 78432, 0x00012550, 256);

// 0x04012650
ROM_ASSET_LOAD_VTX(mario_face_part_cap_off_dl_vertex_group3, 0x00114750, 78432, 0x00012650, 240);

// 0x04012740
ROM_ASSET_LOAD_VTX(mario_face_part_cap_off_dl_vertex_group4, 0x00114750, 78432, 0x00012740, 240);

// 0x04012830
ROM_ASSET_LOAD_VTX(mario_face_part_cap_off_dl_vertex_group5, 0x00114750, 78432, 0x00012830, 256);

// 0x04012930
ROM_ASSET_LOAD_VTX(mario_face_part_cap_off_dl_vertex_group6, 0x00114750, 78432, 0x00012930, 256);

// 0x04012A30
ROM_ASSET_LOAD_VTX(mario_face_part_cap_off_dl_vertex_group7, 0x00114750, 78432, 0x00012a30, 256);

// 0x04012B30
ROM_ASSET_LOAD_VTX(mario_face_part_cap_off_dl_vertex_group8, 0x00114750, 78432, 0x00012b30, 144);

// 0x04012BC0
ROM_ASSET_LOAD_VTX(mario_face_hair_cap_off_dl_vertex_group1, 0x00114750, 78432, 0x00012bc0, 256);

// 0x04012CC0
ROM_ASSET_LOAD_VTX(mario_face_hair_cap_off_dl_vertex_group2, 0x00114750, 78432, 0x00012cc0, 240);

// 0x04012DB0
ROM_ASSET_LOAD_VTX(mario_face_hair_cap_off_dl_vertex_group3, 0x00114750, 78432, 0x00012db0, 256);

// 0x04012EB0
ROM_ASSET_LOAD_VTX(mario_face_hair_cap_off_dl_vertex_group4, 0x00114750, 78432, 0x00012eb0, 256);

// 0x04012FB0
ROM_ASSET_LOAD_VTX(mario_face_hair_cap_off_dl_vertex_group5, 0x00114750, 78432, 0x00012fb0, 256);

// 0x040130B0
ROM_ASSET_LOAD_VTX(mario_face_hair_cap_off_dl_vertex_group6, 0x00114750, 78432, 0x000130b0, 256);

// 0x040131B0
ROM_ASSET_LOAD_VTX(mario_face_hair_cap_off_dl_vertex_group7, 0x00114750, 78432, 0x000131b0, 208);

// 0x04013280
ROM_ASSET_LOAD_VTX(mario_face_part_cap_off_dl_vertex_group9, 0x00114750, 78432, 0x00013280, 48);

// 0x040132B0 - 0x04013318
const Gfx mario_eyes_cap_off_dl[] = {
    gsSPVertex(mario_eyes_cap_off_dl_vertex, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  8,  6,  4, 0x0),
    gsSP2Triangles( 5,  4,  7, 0x0,  7,  9,  5, 0x0),
    gsSP2Triangles( 2,  8, 10, 0x0,  1,  6,  8, 0x0),
    gsSP2Triangles( 1,  8,  2, 0x0,  6, 11,  7, 0x0),
    gsSP1Triangle( 1, 11,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x04013318 - 0x040133A8
const Gfx mario_mustache_cap_off_dl[] = {
    gsSPVertex(mario_mustache_cap_off_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  8, 11,  6, 0x0),
    gsSP2Triangles(12,  8, 13, 0x0, 13,  8, 10, 0x0),
    gsSP2Triangles(14,  3,  4, 0x0, 13, 10, 15, 0x0),
    gsSPVertex(mario_mustache_cap_off_dl_vertex_group2, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP1Triangle( 2,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x040133A8 - 0x040133F8
const Gfx mario_hair_sideburn_cap_off_dl[] = {
    gsSPVertex(mario_hair_sideburn_cap_off_dl_vertex, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 10,  8, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x040133F8 - 0x040136D0
const Gfx mario_face_part_cap_off_dl[] = {
    gsSPVertex(mario_face_part_cap_off_dl_vertex_group1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  2, 0x0,  8,  4,  9, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  6,  5, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14, 13, 12, 0x0),
    gsSP1Triangle(13, 14,  0, 0x0),
    gsSPVertex(mario_face_part_cap_off_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles(10,  1, 11, 0x0,  1, 12, 11, 0x0),
    gsSP2Triangles(12,  1,  0, 0x0, 13, 11, 14, 0x0),
    gsSP2Triangles(12, 14, 11, 0x0, 11, 13, 15, 0x0),
    gsSPVertex(mario_face_part_cap_off_dl_vertex_group3, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 8,  7,  5, 0x0,  4,  8,  5, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(mario_face_part_cap_off_dl_vertex_group4, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 11, 10, 0x0, 11, 13, 14, 0x0),
    gsSPVertex(mario_face_part_cap_off_dl_vertex_group5, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0,  9, 12, 11, 0x0),
    gsSP2Triangles( 0, 13,  1, 0x0, 13, 14,  1, 0x0),
    gsSP1Triangle( 1, 14, 15, 0x0),
    gsSPVertex(mario_face_part_cap_off_dl_vertex_group6, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  1,  0,  5, 0x0),
    gsSP2Triangles( 1,  6,  7, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  1, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 9,  3, 10, 0x0,  4, 11,  0, 0x0),
    gsSP2Triangles(11,  4, 12, 0x0,  4,  9, 12, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0,  0, 11, 15, 0x0),
    gsSP2Triangles( 5,  0, 15, 0x0, 14,  9, 10, 0x0),
    gsSPVertex(mario_face_part_cap_off_dl_vertex_group7, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 8,  5,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2, 12,  0, 0x0, 13,  4,  6, 0x0),
    gsSP2Triangles( 6, 14, 15, 0x0,  6,  7, 14, 0x0),
    gsSP1Triangle(13,  6, 15, 0x0),
    gsSPVertex(mario_face_part_cap_off_dl_vertex_group8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSP1Triangle( 8,  5,  4, 0x0),
    gsSPVertex(mario_face_part_cap_off_dl_vertex_group9, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x040136D0 - 0x040139C0
const Gfx mario_face_hair_cap_off_dl[] = {
    gsSPVertex(mario_face_hair_cap_off_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  4,  9, 0x0,  7, 10,  4, 0x0),
    gsSP2Triangles( 4, 10,  9, 0x0,  8,  5,  4, 0x0),
    gsSP2Triangles(11,  1, 12, 0x0,  1,  0, 12, 0x0),
    gsSP2Triangles( 1, 13,  2, 0x0,  1, 11, 14, 0x0),
    gsSP2Triangles(13,  1, 14, 0x0, 15,  2, 13, 0x0),
    gsSPVertex(mario_face_hair_cap_off_dl_vertex_group2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  7,  3, 0x0,  5,  8,  3, 0x0),
    gsSP2Triangles( 9, 10,  4, 0x0, 11,  4,  6, 0x0),
    gsSP2Triangles(11,  9,  4, 0x0, 10,  5,  4, 0x0),
    gsSP2Triangles(10, 12,  5, 0x0,  5, 13, 14, 0x0),
    gsSP2Triangles( 8,  5, 14, 0x0,  9,  2, 10, 0x0),
    gsSPVertex(mario_face_hair_cap_off_dl_vertex_group3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  7,  9, 0x0),
    gsSP2Triangles( 8,  7, 11, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 11, 13, 0x0, 14,  8, 11, 0x0),
    gsSP1Triangle(15, 13, 12, 0x0),
    gsSPVertex(mario_face_hair_cap_off_dl_vertex_group4, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  9,  7,  5, 0x0),
    gsSP2Triangles(10,  6,  4, 0x0,  4,  3, 11, 0x0),
    gsSP2Triangles( 3, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(mario_face_hair_cap_off_dl_vertex_group5, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 9,  6,  3, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles(10, 11,  0, 0x0, 12,  0,  2, 0x0),
    gsSP2Triangles(10,  0, 12, 0x0, 10,  5, 11, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0, 13,  3, 10, 0x0),
    gsSPVertex(mario_face_hair_cap_off_dl_vertex_group6, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  5,  4,  0, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  9,  7, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0,  8,  7, 10, 0x0),
    gsSP2Triangles( 3, 11, 12, 0x0, 13, 14,  3, 0x0),
    gsSP2Triangles(12,  6,  3, 0x0,  6, 15, 10, 0x0),
    gsSP1Triangle(12, 15,  6, 0x0),
    gsSPVertex(mario_face_hair_cap_off_dl_vertex_group7, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  9,  8,  5, 0x0),
    gsSP2Triangles( 5,  7,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(11, 10,  3, 0x0, 12,  2, 10, 0x0),
    gsSP2Triangles( 2,  1, 10, 0x0, 10,  1,  3, 0x0),
    gsSPEndDisplayList(),
};

const Gfx mario_hair_sideburn_decal_cap_off[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 11),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_hair_sideburn),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_add_sideburn),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsSPDisplayList(mario_hair_sideburn_cap_off_dl),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPCopyLightsPlayerPart(SKIN),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_skin_sideburn),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPDisplayList(mario_hair_sideburn_cap_off_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x040139C0 - 0x040139E8
const Gfx mario_face_cap_off_dl[] = {
    gsSPDisplayList(mario_face_part_cap_off_dl),
    gsSPCopyLightsPlayerPart(HAIR),
    gsSPDisplayList(mario_face_hair_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x040139E8 - 0x04013AB8
const Gfx mario_cap_off_eyes_front[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_front),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_off_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_off_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x04013AB8 - 0x04013B88
const Gfx mario_cap_off_eyes_half_closed[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_half_closed),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_off_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_off_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x04013B88 - 0x04013C58
const Gfx mario_cap_off_eyes_closed[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_closed),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_off_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_off_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x04013C58 - 0x04013D28
const Gfx mario_cap_off_eyes_right[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_right),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_off_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_off_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x04013D28 - 0x04013DF8
const Gfx mario_cap_off_eyes_left[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_left),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_off_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_off_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x04013DF8 - 0x04013EC8
const Gfx mario_cap_off_eyes_up[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_up),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_off_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_off_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x04013EC8 - 0x04013F98
const Gfx mario_cap_off_eyes_down[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_down),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_off_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_off_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x04013F98 - 0x04014068
const Gfx mario_cap_off_eyes_dead[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_eyes_dead),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPCopyLightsPlayerPart(SKIN),
    gsSPDisplayList(mario_eyes_cap_off_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_mustache),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_mustache_cap_off_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_face_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x04014068 - 0x04014098
const Gfx mario_metal_cap_off_shared_dl[] = {
    gsSPDisplayList(mario_eyes_cap_off_dl),
    gsSPDisplayList(mario_mustache_cap_off_dl),
    gsSPDisplayList(mario_hair_sideburn_cap_off_dl),
    gsSPDisplayList(mario_face_part_cap_off_dl),
    gsSPDisplayList(mario_face_hair_cap_off_dl),
    gsSPEndDisplayList(),
};

// 0x04019538
ROM_ASSET_LOAD_VTX(mario_left_hand_open_shared_dl_vertex_group1, 0x00114750, 78432, 0x00019538, 224);

// 0x04019618
ROM_ASSET_LOAD_VTX(mario_left_hand_open_shared_dl_vertex_group2, 0x00114750, 78432, 0x00019618, 256);

// 0x04019718
ROM_ASSET_LOAD_VTX(mario_left_hand_open_shared_dl_vertex_group3, 0x00114750, 78432, 0x00019718, 256);

// 0x04019818
ROM_ASSET_LOAD_VTX(mario_left_hand_open_shared_dl_vertex_group4, 0x00114750, 78432, 0x00019818, 256);

// 0x04019918
ROM_ASSET_LOAD_VTX(mario_left_hand_open_shared_dl_vertex_group5, 0x00114750, 78432, 0x00019918, 256);

// 0x04019A18
ROM_ASSET_LOAD_VTX(mario_left_hand_open_shared_dl_vertex_group6, 0x00114750, 78432, 0x00019a18, 80);

// 0x04019A68 - 0x04019CA0
const Gfx mario_left_hand_open_shared_dl[] = {
    gsSPVertex(mario_left_hand_open_shared_dl_vertex_group1, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  3,  7, 0x0),
    gsSP2Triangles( 1,  0,  5, 0x0,  5,  4,  1, 0x0),
    gsSP2Triangles( 5,  3,  6, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 12, 13, 11, 0x0),
    gsSPVertex(mario_left_hand_open_shared_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 0, 10,  7, 0x0, 11, 10,  0, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0,  9,  8, 13, 0x0),
    gsSP2Triangles( 7,  5,  8, 0x0, 10, 14,  7, 0x0),
    gsSP2Triangles(11, 14, 10, 0x0, 13,  4, 11, 0x0),
    gsSP2Triangles( 8,  5, 13, 0x0,  3, 15,  1, 0x0),
    gsSPVertex(mario_left_hand_open_shared_dl_vertex_group3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 1,  9, 10, 0x0,  5, 11,  1, 0x0),
    gsSP2Triangles(12, 13,  5, 0x0, 14,  9, 15, 0x0),
    gsSP1Triangle( 4,  7, 12, 0x0),
    gsSPVertex(mario_left_hand_open_shared_dl_vertex_group4, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  7,  0,  2, 0x0),
    gsSP2Triangles( 8,  6,  5, 0x0,  5,  9, 10, 0x0),
    gsSP2Triangles(11,  3,  2, 0x0,  2, 12, 11, 0x0),
    gsSP2Triangles( 3, 13,  9, 0x0,  6,  0,  7, 0x0),
    gsSP2Triangles( 7,  4,  9, 0x0, 10, 14, 15, 0x0),
    gsSP1Triangle(15, 14, 11, 0x0),
    gsSPVertex(mario_left_hand_open_shared_dl_vertex_group5, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  0, 0x0,  2,  8,  9, 0x0),
    gsSP2Triangles( 4, 10,  8, 0x0, 11, 10,  4, 0x0),
    gsSP2Triangles( 7, 12, 11, 0x0,  9, 12,  7, 0x0),
    gsSP2Triangles( 6,  3,  1, 0x0,  6,  5,  3, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14, 10, 11, 0x0),
    gsSP2Triangles( 8, 10, 15, 0x0, 10, 14, 15, 0x0),
    gsSPVertex(mario_left_hand_open_shared_dl_vertex_group6, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x04019CA0 - 0x04019CC0
const Gfx mario_left_hand_open[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(GLOVES), // glove light, set in mario_misc.c
    gsSPDisplayList(mario_left_hand_open_shared_dl),
    gsSPEndDisplayList(),
};

// 0x04019CC0
ROM_ASSET_LOAD_VTX(mario_right_hand_open_dl_vertex_group1, 0x00114750, 78432, 0x00019cc0, 224);

// 0x04019DA0
ROM_ASSET_LOAD_VTX(mario_right_hand_open_dl_vertex_group2, 0x00114750, 78432, 0x00019da0, 256);

// 0x04019EA0
ROM_ASSET_LOAD_VTX(mario_right_hand_open_dl_vertex_group3, 0x00114750, 78432, 0x00019ea0, 256);

// 0x04019FA0
ROM_ASSET_LOAD_VTX(mario_right_hand_open_dl_vertex_group4, 0x00114750, 78432, 0x00019fa0, 256);

// 0x0401A0A0
ROM_ASSET_LOAD_VTX(mario_right_hand_open_dl_vertex_group5, 0x00114750, 78432, 0x0001a0a0, 256);

// 0x0401A1A0
ROM_ASSET_LOAD_VTX(mario_right_hand_open_dl_vertex_group6, 0x00114750, 78432, 0x0001a1a0, 80);

// 0x0401A1F0 - 0x0401A428
const Gfx mario_right_hand_open_dl[] = {
    gsSPVertex(mario_right_hand_open_dl_vertex_group1, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  3,  4, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  1,  6,  5, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(mario_right_hand_open_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  2, 0x0,  2, 10, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 12,  8,  7, 0x0),
    gsSP2Triangles( 8,  5,  9, 0x0,  9, 14, 10, 0x0),
    gsSP2Triangles(10, 14, 11, 0x0, 11,  6, 12, 0x0),
    gsSP2Triangles(12,  5,  8, 0x0,  1, 15,  3, 0x0),
    gsSPVertex(mario_right_hand_open_dl_vertex_group3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10,  1, 0x0,  1, 11,  4, 0x0),
    gsSP2Triangles( 4, 12, 13, 0x0, 14, 10, 15, 0x0),
    gsSP1Triangle(13,  7,  5, 0x0),
    gsSPVertex(mario_right_hand_open_dl_vertex_group4, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 0,  4, 11, 0x0, 11, 12,  0, 0x0),
    gsSP2Triangles(10, 13,  4, 0x0,  5,  2,  6, 0x0),
    gsSP2Triangles(10,  3,  5, 0x0, 14, 15,  9, 0x0),
    gsSP1Triangle(11, 15, 14, 0x0),
    gsSPVertex(mario_right_hand_open_dl_vertex_group5, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 2,  7,  6, 0x0,  8,  9,  0, 0x0),
    gsSP2Triangles( 9, 10,  3, 0x0,  3, 10, 11, 0x0),
    gsSP2Triangles(11, 12,  6, 0x0,  6, 12,  8, 0x0),
    gsSP2Triangles( 1,  4,  7, 0x0,  4,  5,  7, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 11, 10, 14, 0x0),
    gsSP2Triangles(15, 10,  9, 0x0, 15, 14, 10, 0x0),
    gsSPVertex(mario_right_hand_open_dl_vertex_group6, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x0401A428 - 0x0401A448
const Gfx mario_right_hand_open[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(GLOVES), // glove light, set in mario_misc.c
    gsSPDisplayList(mario_right_hand_open_dl),
    gsSPEndDisplayList(),
};

// 0x0401A448 - 0x0401A478
const Gfx mario_metal_right_hand_open[] = {
    gsSPDisplayList(mario_right_hand_open_dl),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0F80, 0x07C0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

// 0x0401A478
ROM_ASSET_LOAD_VTX(mario_right_hand_cap_m_logo_dl_vertex, 0x00114750, 78432, 0x0001a478, 80);

// 0x0401A4C8
ROM_ASSET_LOAD_VTX(mario_right_hand_cap_hand_position_dl_vertex_group1, 0x00114750, 78432, 0x0001a4c8, 240);

// 0x0401A5B8
ROM_ASSET_LOAD_VTX(mario_right_hand_cap_hand_position_dl_vertex_group2, 0x00114750, 78432, 0x0001a5b8, 256);

// 0x0401A6B8
ROM_ASSET_LOAD_VTX(mario_right_hand_cap_hand_position_dl_vertex_group3, 0x00114750, 78432, 0x0001a6b8, 224);

// 0x0401A798
ROM_ASSET_LOAD_VTX(mario_right_hand_cap_top_dl_vertex_group1, 0x00114750, 78432, 0x0001a798, 240);

// 0x0401A888
ROM_ASSET_LOAD_VTX(mario_right_hand_cap_top_dl_vertex_group2, 0x00114750, 78432, 0x0001a888, 256);

// 0x0401A988
ROM_ASSET_LOAD_VTX(mario_right_hand_cap_top_dl_vertex_group3, 0x00114750, 78432, 0x0001a988, 256);

// 0x0401AA88
ROM_ASSET_LOAD_VTX(mario_right_hand_cap_top_dl_vertex_group4, 0x00114750, 78432, 0x0001aa88, 128);

// 0x0401AB08
ROM_ASSET_LOAD_VTX(mario_right_hand_cap_bottom_dl_vertex, 0x00114750, 78432, 0x0001ab08, 160);

// 0x0401ABA8 - 0x0401ABD0
const Gfx mario_right_hand_cap_m_logo_dl[] = {
    gsSPVertex(mario_right_hand_cap_m_logo_dl_vertex, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP1Triangle( 1,  4,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0401ABD0 - 0x0401AD40
const Gfx mario_right_hand_cap_top_dl[] = {
    gsSPVertex(mario_right_hand_cap_top_dl_vertex_group1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  6,  2,  1, 0x0),
    gsSP2Triangles( 2,  6,  4, 0x0,  7,  4,  8, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  4,  9,  5, 0x0),
    gsSP2Triangles( 4,  7,  9, 0x0,  5,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 13, 14, 11, 0x0),
    gsSPVertex(mario_right_hand_cap_top_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9,  3, 0x0),
    gsSP2Triangles(10,  9,  0, 0x0, 11, 12,  2, 0x0),
    gsSP2Triangles( 2,  5, 11, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0, 11,  5, 14, 0x0),
    gsSP1Triangle( 7, 14,  5, 0x0),
    gsSPVertex(mario_right_hand_cap_top_dl_vertex_group3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12,  9, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 12, 13, 10, 0x0),
    gsSP1Triangle(13, 12, 15, 0x0),
    gsSPVertex(mario_right_hand_cap_top_dl_vertex_group4, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  6, 0x0),
    gsSP1Triangle( 7,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0401AD40 - 0x0401AED0
const Gfx mario_right_hand_cap_hand_position_dl[] = {
    gsSPVertex(mario_right_hand_cap_hand_position_dl_vertex_group1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 6,  3,  2, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 3,  7,  0, 0x0,  3,  6,  8, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  9,  0,  7, 0x0),
    gsSP2Triangles(10,  0,  9, 0x0,  1,  0, 10, 0x0),
    gsSP2Triangles(11,  1, 10, 0x0, 11,  4,  1, 0x0),
    gsSP2Triangles( 7, 12, 13, 0x0,  8, 12,  7, 0x0),
    gsSP2Triangles(13, 14,  7, 0x0,  7, 14,  9, 0x0),
    gsSPVertex(mario_right_hand_cap_hand_position_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  6,  2,  4, 0x0),
    gsSP2Triangles( 7,  5,  4, 0x0,  8,  9,  3, 0x0),
    gsSP2Triangles( 3,  9, 10, 0x0, 10,  6,  3, 0x0),
    gsSP2Triangles( 5, 11,  3, 0x0,  3, 11,  8, 0x0),
    gsSP2Triangles(10,  0,  6, 0x0,  6,  0,  2, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0,  5, 13, 11, 0x0),
    gsSP2Triangles( 1, 14, 12, 0x0, 14, 15, 12, 0x0),
    gsSPVertex(mario_right_hand_cap_hand_position_dl_vertex_group3, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 7,  5,  8, 0x0,  8,  5,  9, 0x0),
    gsSP2Triangles( 3, 10,  1, 0x0, 11, 10,  3, 0x0),
    gsSP2Triangles( 1, 10,  2, 0x0,  2, 10, 12, 0x0),
    gsSP2Triangles(12, 10, 13, 0x0, 10, 11, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0401AED0 - 0x0401AF20
const Gfx mario_right_hand_cap_bottom_dl[] = {
    gsSPVertex(mario_right_hand_cap_bottom_dl_vertex, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  5,  4,  2, 0x0),
    gsSP2Triangles( 6,  5,  2, 0x0,  6,  2,  7, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0,  6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

const Gfx mario_right_hand_cap_decal[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, SHADE, TEXEL1, SHADE, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, SHADE, TEXEL1, SHADE, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 17),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_m_logo),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_m_blend),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsSPDisplayList(mario_right_hand_cap_m_logo_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, TEXEL1, 0, ENVIRONMENT, 0, TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, TEXEL1, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPCopyLightsPlayerPart(CAP),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_m_logo),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_m_cap),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsSPDisplayList(mario_right_hand_cap_m_logo_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0401AF20 - 0x0401AF60
const Gfx mario_right_hand_cap_dl[] = {
    gsSPCopyLightsPlayerPart(CAP),
    gsSPDisplayList(mario_right_hand_cap_top_dl),
    gsSPCopyLightsPlayerPart(GLOVES), // glove light, set in mario_misc.c
    gsSPDisplayList(mario_right_hand_cap_hand_position_dl),
    gsDPSetCombineLERP(SHADE, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, SHADE, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPSetPrimColor(0, 0, 115, 115, 115, 255),
    gsSPCopyLightsPlayerPart(CAP),
    gsSPDisplayList(mario_right_hand_cap_bottom_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0401AF60
static const Vtx mario_right_hand_cap_wings_half_1_dl_vertex[] = {
    {{{   368,    146,      7}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   166,     37,     68}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   212,     96,    143}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   368,    146,      7}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   322,     87,    -67}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   166,     37,     68}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   178,   -177,    128}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   149,   -100,     60}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   319,   -248,    -14}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   290,   -171,    -81}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0401B000
static const Vtx mario_right_hand_cap_wings_half_2_dl_vertex[] = {
    {{{   414,    206,     82}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   212,     96,    143}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   258,    156,    218}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   368,    146,      7}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   178,   -177,    128}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   319,   -248,    -14}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   349,   -325,     53}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   207,   -253,    195}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0401B080 - 0x0401B0B0
const Gfx mario_right_hand_cap_wings_half_1_dl[] = {
    gsSPVertex(mario_right_hand_cap_wings_half_1_dl_vertex, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0401B0B0 - 0x0401B0E0
const Gfx mario_right_hand_cap_wings_half_2_dl[] = {
    gsSPVertex(mario_right_hand_cap_wings_half_2_dl_vertex, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0401B0E0 - 0x0401B138
const Gfx mario_right_hand_cap_wings_intial_dl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLight(&mario_white_lights_group.l, 1),
    gsSPLight(&mario_white_lights_group.a, 2),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

const Gfx mario_right_hand_cap_wings_transparent_intial_dl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLight(&mario_white_lights_group.l, 1),
    gsSPLight(&mario_white_lights_group.a, 2),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

const Gfx mario_right_hand_cap_metal_wings_intial_dl[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_CULL_BACK),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsSPEndDisplayList(),
};

// 0x0401B138 - 0x0401B158
const Gfx mario_right_hand_cap_wings_end_dl[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0401B158 - 0x0401B1D8
const Gfx mario_right_hand_cap[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(mario_right_hand_cap_dl),
    gsSPEndDisplayList(),
};

// 0x0401B1D8 - 0x0401B230
const Gfx mario_right_hand_cap_wings[] = {
    gsSPDisplayList(mario_right_hand_cap_wings_intial_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_wings_half_1),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_right_hand_cap_wings_half_1_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_wings_half_2),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_right_hand_cap_wings_half_2_dl),
    gsSPDisplayList(mario_right_hand_cap_wings_end_dl),
    gsSPEndDisplayList(),
};

const Gfx mario_right_hand_cap_wings_transparent[] = {
    gsSPDisplayList(mario_right_hand_cap_wings_transparent_intial_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_wings_half_1),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_right_hand_cap_wings_half_1_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_wings_half_2),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_right_hand_cap_wings_half_2_dl),
    gsSPDisplayList(mario_right_hand_cap_wings_end_dl),
    gsSPEndDisplayList(),
};

// 0x0401B230 - 0x0401B278
const Gfx mario_metal_right_hand_cap_shared_dl[] = {
    gsSPDisplayList(mario_right_hand_cap_m_logo_dl),
    gsSPDisplayList(mario_right_hand_cap_top_dl),
    gsSPDisplayList(mario_right_hand_cap_hand_position_dl),
    gsSPDisplayList(mario_right_hand_cap_bottom_dl),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0F80, 0x07C0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

// 0x0401B278 - 0x0401B2D0
const Gfx mario_metal_right_hand_cap_shared_dl_wings[] = {
    gsSPDisplayList(mario_right_hand_cap_metal_wings_intial_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_1_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_1_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_right_hand_cap_wings_half_1_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_2_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_2_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_right_hand_cap_wings_half_2_dl),
    gsSPDisplayList(mario_right_hand_cap_wings_end_dl),
    gsSPEndDisplayList(),
};

const Gfx mario_metal_right_hand_cap_shared_dl_wings_transparent[] = {
    gsSPDisplayList(mario_right_hand_cap_metal_wings_intial_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_1_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_1_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_right_hand_cap_wings_half_1_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_2_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_2_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_right_hand_cap_wings_half_2_dl),
    gsSPDisplayList(mario_right_hand_cap_wings_end_dl),
    gsSPEndDisplayList(),
};

// 0x0401B2D0
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group1, 0x00114750, 78432, 0x0001b2d0, 256);

// 0x0401B3D0
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group2, 0x00114750, 78432, 0x0001b3d0, 224);

// 0x0401B4B0
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group3, 0x00114750, 78432, 0x0001b4b0, 240);

// 0x0401B5A0
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group4, 0x00114750, 78432, 0x0001b5a0, 256);

// 0x0401B6A0
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group5, 0x00114750, 78432, 0x0001b6a0, 256);

// 0x0401B7A0
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group6, 0x00114750, 78432, 0x0001b7a0, 240);

// 0x0401B890
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group7, 0x00114750, 78432, 0x0001b890, 240);

// 0x0401B980
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group8, 0x00114750, 78432, 0x0001b980, 240);

// 0x0401BA70
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group9, 0x00114750, 78432, 0x0001ba70, 256);

// 0x0401BB70
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group10, 0x00114750, 78432, 0x0001bb70, 224);

// 0x0401BC50
ROM_ASSET_LOAD_VTX(mario_right_hand_peace_shared_dl_vertex_group11, 0x00114750, 78432, 0x0001bc50, 48);

// 0x0401BC80 - 0x0401BF30
const Gfx mario_right_hand_peace_shared_dl[] = {
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0,  7,  6, 10, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0, 11,  8,  9, 0x0),
    gsSP2Triangles( 7, 12,  5, 0x0, 10, 13, 14, 0x0),
    gsSP2Triangles( 6, 15, 10, 0x0, 10, 14,  9, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  0,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group3, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group4, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2, 12, 13, 0x0,  3,  5, 12, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group5, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group6, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group7, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  3,  2,  7, 0x0),
    gsSP2Triangles( 8,  3,  7, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group9, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group10, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 12,  9,  8, 0x0),
    gsSPVertex(mario_right_hand_peace_shared_dl_vertex_group11, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0401BF30 - 0x0401BF50
const Gfx mario_right_hand_peace[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(GLOVES), // glove light, set in mario_misc.c
    gsSPDisplayList(mario_right_hand_peace_shared_dl),
    gsSPEndDisplayList(),
};

// 0x0401C940
static const Vtx mario_wings_half_1_dl_vertex[] = {
    {{{  -105,    212,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -105,      0,      0}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      0,      0}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    212,      0}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0401C980
static const Vtx mario_wings_half_2_dl_vertex[] = {
    {{{     0,      0,      0}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   106,    212,      0}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    212,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   106,      0,      0}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0401C9C0 - 0x0401C9E0
const Gfx mario_wings_half_1_dl[] = {
    gsSPVertex(mario_wings_half_1_dl_vertex, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0401C9E0 - 0x0401CA00
const Gfx mario_wings_half_2_dl[] = {
    gsSPVertex(mario_wings_half_2_dl_vertex, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0401CA00 - 0x0401CAB8
const Gfx mario_cap_wings[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&mario_white_lights_group.l, 1),
    gsSPLight(&mario_white_lights_group.a, 2),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_wings_half_1),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_wings_half_1_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_wings_half_2),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_wings_half_2_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0401CAB8 - 0x0401CB70
const Gfx mario_cap_wings_transparent[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&mario_white_lights_group.l, 1),
    gsSPLight(&mario_white_lights_group.a, 2),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_wings_half_1),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_wings_half_1_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_texture_wings_half_2),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_wings_half_2_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0401CB70 - 0x0401CC28
const Gfx mario_metal_cap_wings[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_CULL_BACK),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_1_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_1_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_wings_half_1_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_2_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_2_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_wings_half_2_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0401CC28 - 0x0401CD20
const Gfx mario_metal_cap_wings_transparent[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_CULL_BACK),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_1_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_1_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_wings_half_1_dl),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_2_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_texture_metal_wings_half_2_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_wings_half_2_dl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx mario_material_revert_render_settings[] = {
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
