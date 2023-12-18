#include "src/game/envfx_snow.h"

const GeoLayout bullet_hole_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bullet_hole_bullet_hole_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bullet_hole_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
