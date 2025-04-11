const GeoLayout shape_geo[] = {
    GEO_NODE_START(),
    GEO_OPEN_NODE(),
        GEO_ASM(0, geo_update_shape),
        GEO_DISPLAY_LIST(LAYER_OPAQUE, shape_template_dl),
    GEO_CLOSE_NODE(),
    GEO_END(),
};
