Vtx arrow_triangle_mesh_layer_1_vtx_0[3] = {
	{{ {-40, 58, 0}, 0, {-16, 1008}, {0, 0, 129, 255} }},
	{{ {40, 58, 0}, 0, {1008, 1008}, {0, 0, 129, 255} }},
	{{ {0, 0, 0}, 0, {-16, -16}, {0, 0, 129, 255} }},
};

Gfx arrow_triangle_mesh_layer_1_tri_0[] = {
	gsSPVertex(arrow_triangle_mesh_layer_1_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};


Gfx mat_arrow_white[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_arrow_white[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx arrow_triangle_mesh_layer_1[] = {
	gsSPDisplayList(mat_arrow_white),
	gsSPDisplayList(arrow_triangle_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_arrow_white),
	gsSPEndDisplayList(),
};

Gfx arrow_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

