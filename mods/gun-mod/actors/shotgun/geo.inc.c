#include "src/game/envfx_snow.h"

const GeoLayout shotgun_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SCALE(LAYER_FORCE, 65536),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_mario_set_player_colors),
			GEO_ASM(8, geo_mario_set_player_colors),
			GEO_SWITCH_CASE(0, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_NODE_START(),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -45, 0, NULL),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 25, 0, 0, shotgun_Arm_mesh_layer_1),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, shotgun_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
