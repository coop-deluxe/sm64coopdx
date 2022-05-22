#include "src/game/envfx_snow.h"

const GeoLayout fire_flower[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fire_flower_Cube_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, fire_flower_Cube_002_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fire_flower_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, fire_flower_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
