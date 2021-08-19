extern const GeoLayout toad_player_geo_cap[];
extern const GeoLayout toad_player_geo_vanish_cap[];
extern const GeoLayout toad_player_geo_cap_wing[];
extern const GeoLayout toad_player_geo_vanish_cap_wing[];
extern const GeoLayout toad_player_geo_metal_cap[];
extern const GeoLayout toad_player_geo_metal_vanish_cap[];
extern const Gfx toad_player_metal_start[];
extern const Gfx toad_player_metal_stop[];

const GeoLayout toads_cap_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_9_VERTS, 0xB4, 75),
   GEO_OPEN_NODE(),
      GEO_SCALE(0x00, 16384),
      GEO_OPEN_NODE(),
        GEO_TRANSLATE_ROTATE(0, 0, 80, 0, 30, 0, 0),
          GEO_OPEN_NODE(),
             GEO_ASM(1, geo_mario_set_player_colors),
             GEO_ASM(10, geo_update_layer_transparency),
             GEO_SWITCH_CASE(2, geo_switch_anim_state),
             GEO_OPEN_NODE(),
                GEO_NODE_START(),
                GEO_OPEN_NODE(),
                   GEO_BRANCH(1, toad_player_geo_cap),
                GEO_CLOSE_NODE(),

                GEO_NODE_START(),
                GEO_OPEN_NODE(),
                   GEO_BRANCH(1, toad_player_geo_vanish_cap),
                GEO_CLOSE_NODE(),
             GEO_CLOSE_NODE(),
          GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

const GeoLayout toads_wing_cap_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_9_VERTS, 0xB4, 75),
   GEO_OPEN_NODE(),
      GEO_SCALE(0x00, 16384),
      GEO_OPEN_NODE(),
        GEO_TRANSLATE_ROTATE(0, 0, 80, 0, 30, 0, 0),
          GEO_OPEN_NODE(),
             GEO_ASM(1, geo_mario_set_player_colors),
             GEO_ASM(10, geo_update_layer_transparency),
             GEO_SWITCH_CASE(2, geo_switch_anim_state),
             GEO_OPEN_NODE(),
                GEO_NODE_START(),
                GEO_OPEN_NODE(),
                   GEO_BRANCH(1, toad_player_geo_cap_wing),
                GEO_CLOSE_NODE(),

                GEO_NODE_START(),
                GEO_OPEN_NODE(),
                   GEO_BRANCH(1, toad_player_geo_vanish_cap_wing),
                GEO_CLOSE_NODE(),
             GEO_CLOSE_NODE(),
          GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

const GeoLayout toads_metal_cap_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_9_VERTS, 0xB4, 75),
   GEO_OPEN_NODE(),
      GEO_SCALE(0x00, 16384),
      GEO_OPEN_NODE(),
        GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_metal_start), // starts sharing solid color with mario_torso (blue)
        GEO_TRANSLATE_ROTATE(0, 0, 80, 0, 30, 0, 0),
          GEO_OPEN_NODE(),
             GEO_SWITCH_CASE(2, geo_switch_anim_state),
             GEO_OPEN_NODE(),
                GEO_NODE_START(),
                GEO_OPEN_NODE(),
                   GEO_BRANCH(1, toad_player_geo_metal_cap),
                GEO_CLOSE_NODE(),

                GEO_NODE_START(),
                GEO_OPEN_NODE(),
                   GEO_BRANCH(1, toad_player_geo_metal_vanish_cap),
                GEO_CLOSE_NODE(),
             GEO_CLOSE_NODE(),
          GEO_CLOSE_NODE(),
        GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_metal_stop),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
