#include "game/envfx_snow.h"

const GeoLayout big_paddle_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, big_paddle_paddle_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, big_paddle_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
