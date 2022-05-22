#include "src/game/envfx_snow.h"

const GeoLayout cannon_box_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(1, geo_mario_set_player_colors),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cannon_box_join_mesh_layer_1),
		GEO_ASM(2, geo_mario_set_player_colors),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, cannon_box_join_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, cannon_box_join_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cannon_box_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, cannon_box_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, cannon_box_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
