const GeoLayout toad_player_geo_cap[] = {
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_dl_cap),
      GEO_ASM(2, geo_mirror_mario_backface_culling),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_cap_decal),
      GEO_ASM(3, geo_mirror_mario_backface_culling),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_cap_wing[] = {
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_dl_cap),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_cap_decal),
      GEO_TRANSLATE_ROTATE(0, 180, 50, 0, -10, 0, -20),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_cap_wings), // left
      GEO_CLOSE_NODE(),
      GEO_TRANSLATE_ROTATE(0, -180, 50, 0, 10, 180, -20),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_cap_wings), // right
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_face_and_wings[] = {
   GEO_ASM(0, geo_mario_head_rotation),
   GEO_ROTATION_NODE(0x00, 0, 0, 0),
   GEO_OPEN_NODE(),
      GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 100, -20, 0, -90, -90, 0),

      GEO_OPEN_NODE(),
         GEO_SWITCH_CASE(0, geo_switch_mario_eyes),
         GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_dl_face),
            GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_dl_eyes_half_closed),
            GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_dl_eyes_closed),
            GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL), // unused
            GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL), // unused
            GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL), // unused
            GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL), // unused
            GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_dl_eyes_dead),
         GEO_CLOSE_NODE(),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_hair),
         GEO_ASM(0, geo_mirror_mario_backface_culling),
      GEO_CLOSE_NODE(),

      GEO_OPEN_NODE(),
         GEO_SWITCH_CASE(0, geo_switch_mario_cap_on_off),
         GEO_OPEN_NODE(),
            // cap
            GEO_NODE_START(),
            GEO_OPEN_NODE(),
               GEO_BRANCH(1, toad_player_geo_cap),
            GEO_CLOSE_NODE(),

            // no cap
            GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
         GEO_CLOSE_NODE(),

         GEO_TRANSLATE_ROTATE(0, 180, 50, 0, -10, 0, -20),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_mario_rotate_wing_cap_wings),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_cap_wings), // left
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_TRANSLATE_ROTATE(0, -180, 50, 0, 10, 180, -20),
         GEO_OPEN_NODE(),
            GEO_ASM(1, geo_mario_rotate_wing_cap_wings),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_cap_wings), // right
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),

   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_right_hand[] = {
   GEO_TRANSLATE(LAYER_OPAQUE, 100, 0, 0),
   GEO_OPEN_NODE(),
      GEO_HELD_OBJECT(0x00, 0, 0, 0, geo_switch_mario_hand_grab_pos),
   GEO_CLOSE_NODE(),

   GEO_SWITCH_CASE(0, geo_switch_mario_hand),
   GEO_OPEN_NODE(),
      // FISTS
      GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
      // OPEN
      GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
      // PEACE SIGN
      GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
      // HOLDING CAP
      GEO_NODE_START(),
      GEO_OPEN_NODE(),
         GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 120, 0, -120, 0, 90, -90),
         GEO_BRANCH(1, toad_player_geo_cap),
      GEO_CLOSE_NODE(),
      // HOLDING WING CAP
      GEO_NODE_START(),
      GEO_OPEN_NODE(),
         GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 120, 0, -120, 0, 90, -90),
         GEO_BRANCH(1, toad_player_geo_cap_wing),
      GEO_CLOSE_NODE(),
      // HAND RIGHT OPEN
      GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
   GEO_CLOSE_NODE(),

   GEO_RETURN(),
};

const GeoLayout toad_player_geo_body[] = {
   GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
   GEO_OPEN_NODE(),
      GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -70, 0, /*mario_butt*/ NULL), // starts sharing solid color with mario_torso (blue)
      GEO_OPEN_NODE(),
         GEO_ASM(0, geo_move_mario_part_from_parent),
         GEO_ASM(0, geo_mario_tilt_torso),
         GEO_ROTATION_NODE(0x00, 0, 0, 0),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, /*mario_torso*/ NULL),

            GEO_OPEN_NODE(),
               GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, -90, -90, 0, toad_player_dl_body), // torso
               GEO_ASM(0, geo_mirror_mario_backface_culling),
               GEO_ASM(2, geo_mario_set_player_colors),
            GEO_CLOSE_NODE(),

            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 87, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_BRANCH(1, toad_player_geo_face_and_wings), // stops sharing because faces has its own dl
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 67, -10, 79, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -15, -5, /*mario_left_arm*/ NULL), // starts sharing solid color with mario_left_forearm (red)

                  GEO_OPEN_NODE(),
                     GEO_ASM(1, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, -20, 120, -45, toad_player_dl_arm_left), // left arm
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),

                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 65, 0, 0, /*mario_left_forearm_shared_dl*/ NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 60, 0, 0, /*mario_left_hand_closed*/ NULL),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 68, -10, -79, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -15, 5, /*mario_right_arm*/ NULL), // starts sharing solid color of his dl with mario_right_forearm (red)

                  GEO_OPEN_NODE(),
                     GEO_ASM(0, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 20, -120, -45, toad_player_dl_arm_right), // right arm
                     GEO_CLOSE_NODE(),
                     GEO_OPEN_NODE(),
                        GEO_BRANCH(1, toad_player_geo_right_hand), // stops sharing because hand has its solid color (white)
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),

                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 65, 0, 0, /*mario_right_forearm_shared_dl*/ NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 60, 0, 0, /*mario_right_hand_closed*/ NULL),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_ANIMATED_PART(LAYER_OPAQUE, 60, -8, 50, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, /*mario_left_thigh*/ NULL), // starts sharing solid color of his dl with mario_left_leg (blue)
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 89, 0, 0, /*mario_left_leg_shared_dl*/ NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 67, 0, 0, /*mario_left_foot*/ NULL), // stops sharing because foot has its solid color (brown)

                  GEO_OPEN_NODE(),
                     GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 160, -90, 0, toad_player_dl_foot_left), // left foot
                  GEO_CLOSE_NODE(),

               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_ANIMATED_PART(LAYER_OPAQUE, 60, -8, -50, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, /*mario_right_thigh*/ NULL), // starts sharing solid color of his dl with mario_left_leg (blue)
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 89, 0, 0, /*mario_right_leg_shared_dl*/ NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 67, 0, 0, NULL),
                  GEO_OPEN_NODE(),
                     GEO_ASM(2, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 200, 90, 0, /*mario_right_foot*/ toad_player_dl_foot_right), // stops sharing because foot has its solid color (brown)
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

  ////////////
 // vanish //
////////////

const GeoLayout toad_player_geo_vanish_cap[] = {
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_cap),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_cap_decal),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_vanish_cap_wing[] = {
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_cap),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_cap_decal),
      GEO_TRANSLATE_ROTATE(0, 180, 50, 0, -10, 0, -20),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_cap_wings), // left
      GEO_CLOSE_NODE(),
      GEO_TRANSLATE_ROTATE(0, -180, 50, 0, 10, 180, -20),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_cap_wings), // right
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_vanish_face_and_wings[] = {
   GEO_ASM(0, geo_mario_head_rotation),
   GEO_ROTATION_NODE(0x00, 0, 0, 0),
   GEO_OPEN_NODE(),
      GEO_TRANSLATE_ROTATE(LAYER_TRANSPARENT, 100, -20, 0, -90, -90, 0),

      GEO_OPEN_NODE(),
         GEO_SWITCH_CASE(0, geo_switch_mario_eyes),
         GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_face),
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_eyes_half_closed),
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_eyes_closed),
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL), // unused
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL), // unused
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL), // unused
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL), // unused
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_eyes_dead),
         GEO_CLOSE_NODE(),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_hair),
      GEO_CLOSE_NODE(),

      GEO_OPEN_NODE(),
         GEO_SWITCH_CASE(0, geo_switch_mario_cap_on_off),
         GEO_OPEN_NODE(),
            // cap
            GEO_NODE_START(),
            GEO_OPEN_NODE(),
               GEO_BRANCH(1, toad_player_geo_vanish_cap),
            GEO_CLOSE_NODE(),

            // no cap
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
         GEO_CLOSE_NODE(),

         GEO_TRANSLATE_ROTATE(0, 180, 50, 0, -10, 0, -20),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_mario_rotate_wing_cap_wings),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_cap_wings), // left
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_TRANSLATE_ROTATE(0, -180, 50, 0, 10, 180, -20),
         GEO_OPEN_NODE(),
            GEO_ASM(1, geo_mario_rotate_wing_cap_wings),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_cap_wings), // right
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),

   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_vanish_right_hand[] = {
   GEO_TRANSLATE(LAYER_TRANSPARENT, 100, 0, 0),
   GEO_OPEN_NODE(),
      GEO_HELD_OBJECT(0x00, 0, 0, 0, geo_switch_mario_hand_grab_pos),
   GEO_CLOSE_NODE(),

   GEO_SWITCH_CASE(0, geo_switch_mario_hand),
   GEO_OPEN_NODE(),
      // FISTS
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
      // OPEN
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
      // PEACE SIGN
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
      // HOLDING CAP
      GEO_NODE_START(),
      GEO_OPEN_NODE(),
         GEO_TRANSLATE_ROTATE(LAYER_TRANSPARENT, 120, 0, -120, 0, 90, -90),
         GEO_BRANCH(1, toad_player_geo_vanish_cap),
      GEO_CLOSE_NODE(),
      // HOLDING WING CAP
      GEO_NODE_START(),
      GEO_OPEN_NODE(),
         GEO_TRANSLATE_ROTATE(LAYER_TRANSPARENT, 120, 0, -120, 0, 90, -90),
         GEO_BRANCH(1, toad_player_geo_vanish_cap_wing),
      GEO_CLOSE_NODE(),
      // HAND RIGHT OPEN
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
   GEO_CLOSE_NODE(),

   GEO_RETURN(),
};

const GeoLayout toad_player_geo_vanish_body[] = {
   GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, NULL),
   GEO_OPEN_NODE(),
      GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, -70, 0, /*mario_butt*/ NULL), // starts sharing solid color with mario_torso (blue)
      GEO_OPEN_NODE(),
         GEO_ASM(0, geo_move_mario_part_from_parent),
         GEO_ASM(0, geo_mario_tilt_torso),
         GEO_ROTATION_NODE(0x00, 0, 0, 0),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, /*mario_torso*/ NULL),

            GEO_OPEN_NODE(),
               GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, -90, -90, 0, toad_player_dl_body), // torso
            GEO_CLOSE_NODE(),

            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 87, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_BRANCH(1, toad_player_geo_vanish_face_and_wings), // stops sharing because faces has its own dl
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 67, -10, 79, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, -15, -5, /*mario_left_arm*/ NULL), // starts sharing solid color with mario_left_forearm (red)

                  GEO_OPEN_NODE(),
                     GEO_ASM(1, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, -20, 120, -45, toad_player_dl_arm_left), // left arm
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),

                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_TRANSPARENT, 65, 0, 0, /*mario_left_forearm_shared_dl*/ NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_TRANSPARENT, 60, 0, 0, /*mario_left_hand_closed*/ NULL),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 68, -10, -79, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, -15, 5, /*mario_right_arm*/ NULL), // starts sharing solid color of his dl with mario_right_forearm (red)

                  GEO_OPEN_NODE(),
                     GEO_ASM(0, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, 20, -120, -45, toad_player_dl_arm_right), // right arm
                     GEO_CLOSE_NODE(),
                     GEO_OPEN_NODE(),
                        GEO_BRANCH(1, toad_player_geo_vanish_right_hand), // stops sharing because hand has its solid color (white)
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),

                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_TRANSPARENT, 65, 0, 0, /*mario_right_forearm_shared_dl*/ NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_TRANSPARENT, 60, 0, 0, /*mario_right_hand_closed*/ NULL),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_ANIMATED_PART(LAYER_TRANSPARENT, 60, -8, 50, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, /*mario_left_thigh*/ NULL), // starts sharing solid color of his dl with mario_left_leg (blue)
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 89, 0, 0, /*mario_left_leg_shared_dl*/ NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_TRANSPARENT, 67, 0, 0, /*mario_left_foot*/ NULL), // stops sharing because foot has its solid color (brown)

                  GEO_OPEN_NODE(),
                     GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, 160, -90, 0, toad_player_dl_foot_left), // left foot
                  GEO_CLOSE_NODE(),

               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_ANIMATED_PART(LAYER_TRANSPARENT, 60, -8, -50, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, /*mario_right_thigh*/ NULL), // starts sharing solid color of his dl with mario_left_leg (blue)
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 89, 0, 0, /*mario_right_leg_shared_dl*/ NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_TRANSPARENT, 67, 0, 0, NULL),
                  GEO_OPEN_NODE(),
                     GEO_ASM(2, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, 200, 90, 0, /*mario_right_foot*/ toad_player_dl_foot_right), // stops sharing because foot has its solid color (brown)
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

  ///////////
 // metal //
///////////

const GeoLayout toad_player_geo_metal_cap[] = {
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_dl_cap_inner),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_metal_cap_wing[] = {
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_dl_cap_inner),
      GEO_TRANSLATE_ROTATE(0, 180, 50, 0, -10, 0, -20),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_metal_cap_wings), // left
      GEO_CLOSE_NODE(),
      GEO_TRANSLATE_ROTATE(0, -180, 50, 0, 10, 180, -20),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_metal_cap_wings), // right
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_metal_face_and_wings[] = {
   GEO_ASM(0, geo_mario_head_rotation),
   GEO_ROTATION_NODE(0x00, 0, 0, 0),
   GEO_OPEN_NODE(),
      GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 100, -20, 0, -90, -90, 0),

      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_dl_face_inner),
      GEO_CLOSE_NODE(),

      GEO_OPEN_NODE(),
         GEO_SWITCH_CASE(0, geo_switch_mario_cap_on_off),
         GEO_OPEN_NODE(),
            // cap
            GEO_NODE_START(),
            GEO_OPEN_NODE(),
               GEO_BRANCH(1, toad_player_geo_metal_cap),
            GEO_CLOSE_NODE(),

            // no cap
            GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
         GEO_CLOSE_NODE(),

         GEO_TRANSLATE_ROTATE(0, 180, 50, 0, -10, 0, -20),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_mario_rotate_wing_cap_wings),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_metal_cap_wings), // left
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_TRANSLATE_ROTATE(0, -180, 50, 0, 10, 180, -20),
         GEO_OPEN_NODE(),
            GEO_ASM(1, geo_mario_rotate_wing_cap_wings),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_metal_cap_wings), // right
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),

   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_metal_right_hand[] = {
   GEO_TRANSLATE(LAYER_OPAQUE, 100, 0, 0),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_metal_stop),
   GEO_CLOSE_NODE(),

   GEO_OPEN_NODE(),
      GEO_HELD_OBJECT(0x00, 0, 0, 0, geo_switch_mario_hand_grab_pos),
   GEO_CLOSE_NODE(),

   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_player_metal_start),
   GEO_CLOSE_NODE(),

   GEO_SWITCH_CASE(0, geo_switch_mario_hand),
   GEO_OPEN_NODE(),
      // FISTS
      GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
      // OPEN
      GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
      // PEACE SIGN
      GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
      // HOLDING CAP
      GEO_NODE_START(),
      GEO_OPEN_NODE(),
         GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 120, 0, -120, 0, 90, -90),
         GEO_BRANCH(1, toad_player_geo_metal_cap),
      GEO_CLOSE_NODE(),
      // HOLDING WING CAP
      GEO_NODE_START(),
      GEO_OPEN_NODE(),
         GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 120, 0, -120, 0, 90, -90),
         GEO_BRANCH(1, toad_player_geo_metal_cap_wing),
      GEO_CLOSE_NODE(),
      // HAND RIGHT OPEN
      GEO_DISPLAY_LIST(LAYER_OPAQUE, NULL),
   GEO_CLOSE_NODE(),

   GEO_RETURN(),
};

const GeoLayout toad_player_geo_metal_body[] = {
   GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
   GEO_OPEN_NODE(),
      GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -70, 0, /*mario_butt*/ toad_player_metal_start), // starts sharing solid color with mario_torso (blue)
      GEO_OPEN_NODE(),
         GEO_ASM(0, geo_move_mario_part_from_parent),
         GEO_ASM(0, geo_mario_tilt_torso),
         GEO_ROTATION_NODE(0x00, 0, 0, 0),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, /*mario_torso*/ NULL),

            GEO_OPEN_NODE(),
               GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, -90, -90, 0, toad_player_metal_dl_body), // torso
            GEO_CLOSE_NODE(),

            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 87, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_BRANCH(1, toad_player_geo_metal_face_and_wings), // stops sharing because faces has its own dl
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 67, -10, 79, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -15, -5, /*mario_left_arm*/ NULL), // starts sharing solid color with mario_left_forearm (red)

                  GEO_OPEN_NODE(),
                     GEO_ASM(1, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, -20, 120, -45, toad_player_dl_arm_left_inner), // left arm
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),

                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 65, 0, 0, /*mario_left_forearm_shared_dl*/ NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 60, 0, 0, /*mario_left_hand_closed*/ NULL),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 68, -10, -79, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -15, 5, /*mario_right_arm*/ NULL), // starts sharing solid color of his dl with mario_right_forearm (red)

                  GEO_OPEN_NODE(),
                     GEO_ASM(0, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 20, -120, -45, toad_player_dl_arm_right_inner), // right arm
                     GEO_CLOSE_NODE(),
                     GEO_OPEN_NODE(),
                        GEO_BRANCH(1, toad_player_geo_metal_right_hand), // stops sharing because hand has its solid color (white)
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),

                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 65, 0, 0, /*mario_right_forearm_shared_dl*/ NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 60, 0, 0, /*mario_right_hand_closed*/ NULL),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_ANIMATED_PART(LAYER_OPAQUE, 60, -8, 50, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, /*mario_left_thigh*/ NULL), // starts sharing solid color of his dl with mario_left_leg (blue)
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 89, 0, 0, /*mario_left_leg_shared_dl*/ NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 67, 0, 0, /*mario_left_foot*/ NULL), // stops sharing because foot has its solid color (brown)

                  GEO_OPEN_NODE(),
                     GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 160, -90, 0, toad_player_dl_foot_left_inner), // left foot
                  GEO_CLOSE_NODE(),

               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_ANIMATED_PART(LAYER_OPAQUE, 60, -8, -50, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, /*mario_right_thigh*/ NULL), // starts sharing solid color of his dl with mario_left_leg (blue)
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 89, 0, 0, /*mario_right_leg_shared_dl*/ NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 67, 0, 0, NULL),
                  GEO_OPEN_NODE(),
                     GEO_ASM(2, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 200, 90, 0, /*mario_right_foot*/ toad_player_dl_foot_right_metal), // stops sharing because foot has its solid color (brown)
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

  //////////////////
 // metal-vanish //
//////////////////

const GeoLayout toad_player_geo_metal_vanish_cap[] = {
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_cap_inner),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_metal_vanish_cap_wing[] = {
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_cap_inner),
      GEO_TRANSLATE_ROTATE(0, 180, 50, 0, -10, 0, -20),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_metal_cap_wings), // left
      GEO_CLOSE_NODE(),
      GEO_TRANSLATE_ROTATE(0, -180, 50, 0, 10, 180, -20),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_metal_cap_wings), // right
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_metal_vanish_face_and_wings[] = {
   GEO_ASM(0, geo_mario_head_rotation),
   GEO_ROTATION_NODE(0x00, 0, 0, 0),
   GEO_OPEN_NODE(),
      GEO_TRANSLATE_ROTATE(LAYER_TRANSPARENT, 100, -20, 0, -90, -90, 0),

      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_dl_face_inner),
      GEO_CLOSE_NODE(),

      GEO_OPEN_NODE(),
         GEO_SWITCH_CASE(0, geo_switch_mario_cap_on_off),
         GEO_OPEN_NODE(),
            // cap
            GEO_NODE_START(),
            GEO_OPEN_NODE(),
               GEO_BRANCH(1, toad_player_geo_metal_vanish_cap),
            GEO_CLOSE_NODE(),

            // no cap
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
         GEO_CLOSE_NODE(),

         GEO_TRANSLATE_ROTATE(0, 180, 50, 0, -10, 0, -20),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_mario_rotate_wing_cap_wings),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_metal_cap_wings), // left
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_TRANSLATE_ROTATE(0, -180, 50, 0, 10, 180, -20),
         GEO_OPEN_NODE(),
            GEO_ASM(1, geo_mario_rotate_wing_cap_wings),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_ALPHA, toad_player_metal_cap_wings), // right
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),

   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

const GeoLayout toad_player_geo_metal_vanish_right_hand[] = {
   GEO_TRANSLATE(LAYER_TRANSPARENT, 100, 0, 0),

   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_metal_stop),
   GEO_CLOSE_NODE(),

   GEO_OPEN_NODE(),
      GEO_HELD_OBJECT(0x00, 0, 0, 0, geo_switch_mario_hand_grab_pos),
   GEO_CLOSE_NODE(),

   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_player_metal_start),
   GEO_CLOSE_NODE(),

   GEO_SWITCH_CASE(0, geo_switch_mario_hand),
   GEO_OPEN_NODE(),
      // FISTS
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
      // OPEN
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
      // PEACE SIGN
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
      // HOLDING CAP
      GEO_NODE_START(),
      GEO_OPEN_NODE(),
         GEO_TRANSLATE_ROTATE(LAYER_TRANSPARENT, 120, 0, -120, 0, 90, -90),
         GEO_BRANCH(1, toad_player_geo_metal_vanish_cap),
      GEO_CLOSE_NODE(),
      // HOLDING WING CAP
      GEO_NODE_START(),
      GEO_OPEN_NODE(),
         GEO_TRANSLATE_ROTATE(LAYER_TRANSPARENT, 120, 0, -120, 0, 90, -90),
         GEO_BRANCH(1, toad_player_geo_metal_vanish_cap_wing),
      GEO_CLOSE_NODE(),
      // HAND RIGHT OPEN
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, NULL),
   GEO_CLOSE_NODE(),

   GEO_RETURN(),
};

const GeoLayout toad_player_geo_metal_vanish_body[] = {
   GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, NULL),
   GEO_OPEN_NODE(),
      GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, -70, 0, /*mario_butt*/ toad_player_metal_start), // starts sharing solid color with mario_torso (blue)
      GEO_OPEN_NODE(),
         GEO_ASM(0, geo_move_mario_part_from_parent),
         GEO_ASM(0, geo_mario_tilt_torso),
         GEO_ROTATION_NODE(0x00, 0, 0, 0),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, /*mario_torso*/ NULL),

            GEO_OPEN_NODE(),
               GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, -90, -90, 0, toad_player_metal_dl_body), // torso
            GEO_CLOSE_NODE(),

            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 87, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_BRANCH(1, toad_player_geo_metal_vanish_face_and_wings), // stops sharing because faces has its own dl
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 67, -10, 79, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, -15, -5, /*mario_left_arm*/ NULL), // starts sharing solid color with mario_left_forearm (red)

                  GEO_OPEN_NODE(),
                     GEO_ASM(1, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, -20, 120, -45, toad_player_dl_arm_left_inner), // left arm
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),

                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_TRANSPARENT, 65, 0, 0, /*mario_left_forearm_shared_dl*/ NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_TRANSPARENT, 60, 0, 0, /*mario_left_hand_closed*/ NULL),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 68, -10, -79, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, -15, 5, /*mario_right_arm*/ NULL), // starts sharing solid color of his dl with mario_right_forearm (red)

                  GEO_OPEN_NODE(),
                     GEO_ASM(0, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, 20, -120, -45, toad_player_dl_arm_right_inner), // right arm
                     GEO_CLOSE_NODE(),
                     GEO_OPEN_NODE(),
                        GEO_BRANCH(1, toad_player_geo_metal_vanish_right_hand), // stops sharing because hand has its solid color (white)
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),

                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_TRANSPARENT, 65, 0, 0, /*mario_right_forearm_shared_dl*/ NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_TRANSPARENT, 60, 0, 0, /*mario_right_hand_closed*/ NULL),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_ANIMATED_PART(LAYER_TRANSPARENT, 60, -8, 50, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, /*mario_left_thigh*/ NULL), // starts sharing solid color of his dl with mario_left_leg (blue)
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 89, 0, 0, /*mario_left_leg_shared_dl*/ NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_TRANSPARENT, 67, 0, 0, /*mario_left_foot*/ NULL), // stops sharing because foot has its solid color (brown)

                  GEO_OPEN_NODE(),
                     GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, 160, -90, 0, toad_player_dl_foot_left_inner), // left foot
                  GEO_CLOSE_NODE(),

               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_ANIMATED_PART(LAYER_TRANSPARENT, 60, -8, -50, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, /*mario_right_thigh*/ NULL), // starts sharing solid color of his dl with mario_left_leg (blue)
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_TRANSPARENT, 89, 0, 0, /*mario_right_leg_shared_dl*/ NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_TRANSPARENT, 67, 0, 0, NULL),
                  GEO_OPEN_NODE(),
                     GEO_ASM(2, geo_mario_hand_foot_scaler),
                     GEO_SCALE(0x00, 65536),
                     GEO_OPEN_NODE(),
                        GEO_ROTATION_NODE_WITH_DL(LAYER_TRANSPARENT, 200, 90, 0, /*mario_right_foot*/ toad_player_dl_foot_right_metal), // stops sharing because foot has its solid color (brown)
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

  //////////
 // main //
//////////

const GeoLayout toad_player_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_PLAYER, 0x96, 100),
   GEO_OPEN_NODE(),
      GEO_SCALE(0x00, 16384),
      GEO_OPEN_NODE(),
         GEO_ASM(0, geo_mario_set_player_colors),
         GEO_ASM(0, geo_mirror_mario_backface_culling),
         GEO_ASM(0, geo_mirror_mario_set_alpha),

         GEO_SWITCH_CASE(0, geo_switch_mario_cap_effect),
         GEO_OPEN_NODE(),
            GEO_BRANCH(1, toad_player_geo_body),
            GEO_BRANCH(1, toad_player_geo_vanish_body),
            GEO_BRANCH(1, toad_player_geo_metal_body),
            GEO_BRANCH(1, toad_player_geo_metal_vanish_body),
         GEO_CLOSE_NODE(),

         GEO_ASM(1, geo_mirror_mario_backface_culling),

      GEO_CLOSE_NODE(),

   GEO_DISPLAY_LIST(LAYER_OPAQUE, toad_material_revert_render_settings),
   GEO_DISPLAY_LIST(LAYER_ALPHA, toad_material_revert_render_settings),
   GEO_DISPLAY_LIST(LAYER_TRANSPARENT, toad_material_revert_render_settings),

   GEO_CLOSE_NODE(),
   GEO_END(),
};
