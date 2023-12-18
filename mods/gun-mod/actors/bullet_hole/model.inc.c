Lights1 bullet_hole_bullet_hole_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFF, 0xFF, 0xFF, 0x28, 0x28, 0x28);

Gfx bullet_hole_bullet_hole_ia8_aligner[] = {gsSPEndDisplayList()};
u8 bullet_hole_bullet_hole_ia8[] = {
	#include "actors/bullet_hole/bullet_hole.ia8.inc.c"
};

Vtx bullet_hole_bullet_hole_mesh_layer_4_vtx_0[4] = {
	{{ {-22, 1, 22}, 0, {-16, 2032}, {0, 127, 0, 255} }},
	{{ {22, 1, 22}, 0, {2032, 2032}, {0, 127, 0, 255} }},
	{{ {22, 1, -22}, 0, {2032, -16}, {0, 127, 0, 255} }},
	{{ {-22, 1, -22}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx bullet_hole_bullet_hole_mesh_layer_4_tri_0[] = {
	gsSPVertex(bullet_hole_bullet_hole_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_bullet_hole_bullet_hole[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(bullet_hole_bullet_hole_lights),
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b_LOAD_BLOCK, 1, bullet_hole_bullet_hole_ia8),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 2047, 256),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 252),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bullet_hole_bullet_hole[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx bullet_hole_bullet_hole_mesh_layer_4[] = {
	gsSPDisplayList(mat_bullet_hole_bullet_hole),
	gsSPDisplayList(bullet_hole_bullet_hole_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_bullet_hole_bullet_hole),
	gsSPEndDisplayList(),
};

Gfx bullet_hole_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

