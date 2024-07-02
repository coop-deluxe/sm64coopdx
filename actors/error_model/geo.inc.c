const GeoLayout error_model_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
      	GEO_SCALE(0x00, 16384),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, error_model_error_bone_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, error_model_material_revert_render_settings),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
