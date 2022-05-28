const GeoLayout arena_ball_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 280),
   GEO_OPEN_NODE(),
      GEO_SCALE(0x00, 170393),
      GEO_OPEN_NODE(),
         GEO_ASM(LAYER_TRANSPARENT + 3, geo_mario_set_player_colors),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, arena_ball_gfx),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
