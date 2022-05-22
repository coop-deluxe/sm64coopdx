#include "src/game/envfx_snow.h"

const GeoLayout arena_flag_white_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, arena_flag_white_flag_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, arena_flag_white_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
