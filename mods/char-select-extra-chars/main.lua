-- name: [CS] Extra Characters
-- description: [CS] Extra Characters v8.1\nBy: \\#00ff00\\ULTRA BROS TEAM\n\n\\#ffff00\\Ultra Bros Team:\n\\#ffffff\\FunkyLion\nMelzinoff\nFluffaMario\nSharen\nSquishy\n\n\\#f54e59\\Characters:\n\\#ffffff\\Toadette\nPeach\nDaisy\nYoshi\nBirdo\nForeman Spike\nPauline\nRosalina

local TEXT_PACK_NAME = "Extra Characters"

if not _G.charSelectExists then
    djui_popup_create("\\#ffffa0\\Extra Characters requires\nCharacter Select to be enabled.\n\nPlease rehost with it enabled.", 4)
    return
end

-- Characters are stored in a table for ease of addition

extraCharacters = {
    --------------
    -- Toadette --
    --------------
    {
        name = "Toadette",
        description = "A very rare female toad with a bubbly personality who lives in a world of male toads! She seems to enjoy her hobby as a construction boss! Although for some reason, she seems to hate unions. Wonder why?",
        credits = "Coop Team / VA: MelissaMekrose",
        color = { r = 255, g = 70, b = 161 },
        model = smlua_model_util_get_id("toadette_geo"),
        forceChar = CT_TOAD,
        lifeIcon = get_texture_info("icon-toadette"),
        camScale = 0.8,
        offset = 0,
        caps = {
            normal = smlua_model_util_get_id("toadette_cap_geo"),
            wing = smlua_model_util_get_id("toadette_wing_cap_geo"),
            metal = smlua_model_util_get_id("toadette_metal_cap_geo"),
            metalWing = smlua_model_util_get_id("toadette_metal_wing_cap_geo")
        },
        palette = {
            [PANTS]  = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHIRT]  = { r = 0xFF, g = 0x00, b = 0x00 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x68, g = 0x40, b = 0x1B },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xD5, b = 0xA1 },
            [CAP]    = { r = 0xF3, g = 0x00, b = 0x80 },
            [EMBLEM] = { r = 0xF3, g = 0x00, b = 0x80 }
        },
        voices = {
            [CHAR_SOUND_ATTACKED] = "toadette_attacked.ogg",
            [CHAR_SOUND_COUGHING1] = "toadette_coughing1.ogg",
            [CHAR_SOUND_COUGHING2] = "toadette_coughing2.ogg",
            [CHAR_SOUND_COUGHING3] = "toadette_coughing3.ogg",
            [CHAR_SOUND_DOH] = "toadette_doh.ogg",
            [CHAR_SOUND_DROWNING] = "toadette_drowning.ogg",
            [CHAR_SOUND_DYING] = "toadette_dying.ogg",
            [CHAR_SOUND_EEUH] = "toadette_euuh.ogg",
            [CHAR_SOUND_GROUND_POUND_WAH] = "toadette_ground_pound_wah.ogg",
            [CHAR_SOUND_HAHA] = "toadette_haha.ogg",
            [CHAR_SOUND_HAHA_2] = "toadette_haha2.ogg",
            [CHAR_SOUND_HERE_WE_GO] = "toadette_herewego.ogg",
            [CHAR_SOUND_HOOHOO] = "toadette_hoohoo.ogg",
            [CHAR_SOUND_HRMM] = "toadette_hrmm.ogg",
            [CHAR_SOUND_IMA_TIRED] = "toadette_imatired.ogg",
            [CHAR_SOUND_MAMA_MIA] = "toadette_mamamia.ogg",
            [CHAR_SOUND_LETS_A_GO] = "toadette_letsago.ogg",
            [CHAR_SOUND_ON_FIRE] = "toadette_on_fire.ogg",
            [CHAR_SOUND_OOOF] = "toadette_ooof.ogg",
            [CHAR_SOUND_OOOF2] = "toadette_ooof2.ogg",
            [CHAR_SOUND_PANTING] = "toadette_panting.ogg",
            [CHAR_SOUND_PANTING_COLD] = "toadette_panting_cold.ogg",
            [CHAR_SOUND_PUNCH_HOO] = "toadette_punch_hoo.ogg",
            [CHAR_SOUND_PUNCH_WAH] = "toadette_punch_wah.ogg",
            [CHAR_SOUND_PUNCH_YAH] = "toadette_punch_yah.ogg",
            [CHAR_SOUND_SO_LONGA_BOWSER] = "toadette_solonga_bowser.ogg",
            [CHAR_SOUND_SNORING1] = "toadette_snoring1.ogg",
            [CHAR_SOUND_SNORING2] = "toadette_snoring2.ogg",
            [CHAR_SOUND_SNORING3] = {"toadette_snoring2.ogg", "toadette_snoring1.ogg", "toadette_snoring3.ogg"},
            [CHAR_SOUND_TWIRL_BOUNCE] = "toadette_twirl_bounce.ogg",
            [CHAR_SOUND_UH] = "toadette_uh.ogg",
            [CHAR_SOUND_UH2] = "toadette_uh2.ogg",
            [CHAR_SOUND_UH2_2] = "toadette_uh2_2.ogg",
            [CHAR_SOUND_WAAAOOOW] = "toadette_waaaooow.ogg",
            [CHAR_SOUND_WAH2] = "toadette_ground_pound_wah.ogg",
            [CHAR_SOUND_WHOA] = "toadette_whoa.ogg",
            [CHAR_SOUND_YAHOO] = "toadette_yahoo.ogg",
            [CHAR_SOUND_YAWNING] = "toadette_yawning.ogg",
            [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "toadette_yahoo.ogg", "toadette_yahoo1.ogg", "toadette_yahoo2.ogg", "toadette_yahoo3.ogg", "toadette_yahoo4.ogg", "toadette_yahoo5.ogg" },
            [CHAR_SOUND_YAH_WAH_HOO] = { "toadette_yah_wah_hoo1.ogg", "toadette_yah_wah_hoo2.ogg", "toadette_yah_wah_hoo3.ogg"},
            [CHAR_SOUND_HELLO] = "toadette_hello.ogg"
        },
        anims = nil
    },
    --------------------
    -- Princess Peach --
    --------------------
    {
        name = "Peach",
        description = "The ruler of the Mushroom Kingdom, always ready to help Mario in his adventures and save her kingdom from the evil clutches of King Bowser! .........wait. What?! Why is she here?! How did she escape?! And who's the Peach we saw earlier?! This is confusing!",
        credits = "Coop Team / VA: SuperKirbyLover",
        color = {r = 239, g = 128, b = 177},
        model = smlua_model_util_get_id("peach_player_geo"),
        forceChar = CT_MARIO,
        lifeIcon = get_texture_info("icon-peach"),
        camScale = 1,
        offset = 0,
        caps = {
            normal = smlua_model_util_get_id("peach_player_cap_geo"),
            wing = smlua_model_util_get_id("peach_player_wing_cap_geo"),
            metal = smlua_model_util_get_id("peach_player_metal_cap_geo"),
            metalWing = smlua_model_util_get_id("peach_player_metal_wing_cap_geo")
        },
        palette = {
            [PANTS]  = { r = 0xFF, g = 0x50, b = 0x96 },
            [SHIRT]  = { r = 0xF8, g = 0xC8, b = 0xBB },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x00, g = 0x00, b = 0xFF },
            [HAIR]   = { r = 0xFF, g = 0xD3, b = 0x02 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0xFF, g = 0xFF, b = 0x00 },
            [EMBLEM] = { r = 0x00, g = 0x82, b = 0xFF }
        },
        voices = {
            [CHAR_SOUND_ATTACKED] = "peach_attacked.ogg",
            [CHAR_SOUND_COUGHING1] = "peach_coughing1.ogg",
            [CHAR_SOUND_COUGHING2] = "peach_coughing2.ogg",
            [CHAR_SOUND_COUGHING3] = "peach_coughing3.ogg",
            [CHAR_SOUND_DOH] = "peach_doh.ogg",
            [CHAR_SOUND_DROWNING] = "peach_drowning.ogg",
            [CHAR_SOUND_DYING] = "peach_dying.ogg",
            [CHAR_SOUND_EEUH] = "peach_euuh.ogg",
            [CHAR_SOUND_GROUND_POUND_WAH] = "peach_ground_pound_wah.ogg",
            [CHAR_SOUND_HAHA] = "peach_haha.ogg",
            [CHAR_SOUND_HAHA_2] = "peach_haha.ogg",
            [CHAR_SOUND_HERE_WE_GO] = "peach_herewego.ogg",
            [CHAR_SOUND_HOOHOO] = "peach_hoohoo.ogg",
            [CHAR_SOUND_HRMM] = "peach_hrmm.ogg",
            [CHAR_SOUND_IMA_TIRED] = "peach_imatired.ogg",
            [CHAR_SOUND_MAMA_MIA] = "peach_mamamia.ogg",
            [CHAR_SOUND_LETS_A_GO] = "peach_letsago.ogg",
            [CHAR_SOUND_ON_FIRE] = "peach_on_fire.ogg",
            [CHAR_SOUND_OOOF] = "peach_ooof.ogg",
            [CHAR_SOUND_OOOF2] = "peach_ooof2.ogg",
            [CHAR_SOUND_PANTING] = "peach_panting.ogg",
            [CHAR_SOUND_PANTING_COLD] = "peach_panting_cold.ogg",
            [CHAR_SOUND_PUNCH_HOO] = "peach_punch_hoo.ogg",
            [CHAR_SOUND_PUNCH_WAH] = "peach_punch_wah.ogg",
            [CHAR_SOUND_PUNCH_YAH] = "peach_punch_yah.ogg",
            [CHAR_SOUND_SO_LONGA_BOWSER] = "peach_solonga_bowser.ogg",
            [CHAR_SOUND_SNORING1] = "peach_snoring1.ogg",
            [CHAR_SOUND_SNORING2] = "peach_snoring2.ogg",
            [CHAR_SOUND_SNORING3] = {"peach_snoring2.ogg", "peach_snoring1.ogg", "peach_snoring3.ogg"},
            [CHAR_SOUND_TWIRL_BOUNCE] = "peach_twirl_bounce.ogg",
            [CHAR_SOUND_UH] = "peach_uh.ogg",
            [CHAR_SOUND_UH2] = "peach_uh2.ogg",
            [CHAR_SOUND_UH2_2] = "peach_uh2_2.ogg",
            [CHAR_SOUND_WAAAOOOW] = "peach_waaaooow.ogg",
            [CHAR_SOUND_WAH2] = "peach_ground_pound_wah.ogg",
            [CHAR_SOUND_WHOA] = "peach_whoa.ogg",
            [CHAR_SOUND_YAHOO] = "peach_yahoo.ogg",
            [CHAR_SOUND_YAWNING] = "peach_yawning.ogg",
            [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "peach_yahoo.ogg", "peach_yahoo1.ogg", "peach_yahoo2.ogg", "peach_yahoo3.ogg", "peach_yahoo4.ogg", "peach_yahoo5.ogg" },
            [CHAR_SOUND_YAH_WAH_HOO] = { "peach_yah_wah_hoo1.ogg", "peach_yah_wah_hoo2.ogg", "peach_yah_wha_hoo3.ogg"},
            [CHAR_SOUND_HELLO] = "peach_float.ogg"
        },
        anims = {
            [CHAR_ANIM_RUNNING] = 'princess_running',
            [CHAR_ANIM_IDLE_HEAD_CENTER] = 'princess_idle_head_center',
            [CHAR_ANIM_IDLE_HEAD_LEFT] = 'princess_idle_head_left',
            [CHAR_ANIM_IDLE_HEAD_RIGHT] = 'princess_idle_head_right',
            [CHAR_ANIM_BACKWARD_KB] = 'princess_backward_kb',
            [CHAR_ANIM_FIRST_PERSON] = 'princess_first_person',
            [CHAR_ANIM_FLUTTERKICK] = 'princess_flutterkick',
            [CHAR_ANIM_FLUTTERKICK_WITH_OBJ] = 'princess_flutterkick_with_obj',
            [CHAR_ANIM_FORWARD_KB] = 'princess_forward_kb',
            [CHAR_ANIM_GROUND_BONK] = 'princess_ground_bonk',
            [CHAR_ANIM_GROUND_KICK] = 'princess_ground_kick',
            [CHAR_ANIM_GROUND_THROW] = 'princess_ground_throw',
            [CHAR_ANIM_HEAVY_THROW] = 'princess_heavy_throw',
            [CHAR_ANIM_MISSING_CAP] = 'princess_missing_cap',
            [CHAR_ANIM_PULL_DOOR_WALK_IN] = 'princess_pull_door_walk_in',
            [CHAR_ANIM_FIRST_PERSON] = 'princess_first_person',
            [CHAR_ANIM_RELEASE_BOWSER] = 'princess_release_bowser',
            [CHAR_ANIM_RETURN_FROM_STAR_DANCE] = 'princess_return_from_star_dance',
            [CHAR_ANIM_RETURN_STAR_APPROACH_DOOR] = 'princess_return_star_approach_door',
            [CHAR_ANIM_SLIDEFLIP_LAND] = 'princess_sideflip_land',
            [CHAR_ANIM_SLEEP_IDLE] = 'princess_sleep_idle',
            [CHAR_ANIM_START_SLEEP_SITTING] = 'princess_sleep_sitting',
            [CHAR_ANIM_SOFT_BACK_KB] = 'princess_soft_back_kb',
            [CHAR_ANIM_SOFT_FRONT_KB] = 'princess_soft_front_kb',
            [CHAR_ANIM_STAR_DANCE] = 'princess_star_dance',
            [CHAR_ANIM_START_CROUCHING] = 'princess_start_crouch',
            [CHAR_ANIM_STOP_CROUCHING] = 'princess_stop_crouch',
            [CHAR_ANIM_START_SLEEP_IDLE] = 'princess_start_sleep',
            [CHAR_ANIM_STOP_SLIDE] = 'princess_stop_slide',
            [CHAR_ANIM_SUMMON_STAR] = 'princess_summon_star',
            [CHAR_ANIM_SWIM_WITH_OBJ_PART1] = 'princess_swim_with_obj1',
            [CHAR_ANIM_SWIM_WITH_OBJ_PART2] = 'princess_swim_with_obj2',
            [CHAR_ANIM_TRIPLE_JUMP_LAND] = 'princess_triple_jump_land',
            [CHAR_ANIM_TURNING_PART1] = 'princess_turning_part1',
            [CHAR_ANIM_TURNING_PART2] = 'princess_turning_part2',
            [CHAR_ANIM_TWIRL_LAND] = 'princess_twirl_land',
            [CHAR_ANIM_WAKE_FROM_LYING] = 'princess_wake_from_lying',
            [CHAR_ANIM_WAKE_FROM_SLEEP] = 'princess_wake_from_sleep',
            [CHAR_ANIM_CREDITS_RAISE_HAND] = 'princess_credits_raise_hand',
            [CHAR_ANIM_CREDITS_RETURN_FROM_LOOK_UP] = 'princess_credits_return_from_look_up',
            [CHAR_ANIM_CREDITS_START_WALK_LOOK_UP] = 'princess_credits_start_walk_look_up',
            [CHAR_ANIM_CREDITS_TAKE_OFF_CAP] = 'princess_credits_take_off_cap',
            [CHAR_ANIM_DYING_FALL_OVER] = 'princess_dying_fall_over',
            [CHAR_ANIM_FALL_OVER_BACKWARDS] = 'princess_fall_over_backwards',
            [CHAR_ANIM_FAST_LEDGE_GRAB] = 'princess_fast_ledge_grab',
            --[CHAR_ANIM_FINAL_BOWSER_RAISE_HAND_SPIN] = 'princess_final_bowser_raise_hand_spin',
            [CHAR_ANIM_FIRST_PUNCH_FAST] = 'princess_first_punch_fast',
            [CHAR_ANIM_GENERAL_LAND] = 'princess_general_land',
            [CHAR_ANIM_HEAD_STUCK_IN_GROUND] = 'princess_head_stuck_in_ground',
            [CHAR_ANIM_LAND_FROM_DOUBLE_JUMP] = 'princess_land_from_double_jump',
            [CHAR_ANIM_LAND_FROM_SINGLE_JUMP] = 'princess_land_from_single_jump',
            [CHAR_ANIM_LAND_ON_STOMACH] = 'princess_land_on_stomach',
            [CHAR_ANIM_LEGS_STUCK_IN_GROUND] = 'princess_legs_stuck_in_ground',
            [CHAR_ANIM_PLACE_LIGHT_OBJ] = 'princess_place_light_obj',
            [CHAR_ANIM_PUSH_DOOR_WALK_IN] = 'princess_push_door_walk_in',
            [CHAR_ANIM_PUT_CAP_ON] = 'princess_put_cap_on',
            [CHAR_ANIM_RUN_WITH_LIGHT_OBJ] = 'princess_run_with_light_obj',
            [CHAR_ANIM_SECOND_PUNCH_FAST] = 'princess_second_punch_fast',
            [CHAR_ANIM_SHIVERING_RETURN_TO_IDLE] = 'princess_shivering_returning_to_idle',
            [CHAR_ANIM_SKID_ON_GROUND] = 'princess_skid_on_ground',
            [CHAR_ANIM_SLOW_LAND_FROM_DIVE] = 'princess_slow_land_from_dive',
            [CHAR_ANIM_SLOW_LEDGE_GRAB] = 'princess_slow_ledge_grab',
            [CHAR_ANIM_SLOW_WALK_WITH_LIGHT_OBJ] = 'princess_slow_walk_with_light_obj',
            [CHAR_ANIM_STAND_UP_FROM_LAVA_BOOST] = 'princess_stand_up_from_lava_boost',
            [CHAR_ANIM_STOP_SKID] = 'princess_stop_skid',
            [CHAR_ANIM_TAKE_CAP_OFF_THEN_ON] = 'princess_take_cap_off_then_on',
            [CHAR_ANIM_THROW_CATCH_KEY] = 'princess_throw_catch_key',
            [CHAR_ANIM_WALK_WITH_LIGHT_OBJ] = 'princess_walk_with_light_obj',
            [CHAR_ANIM_BOTTOM_STUCK_IN_GROUND] = 'princess_bottom_stuck_in_ground',
            --[CHAR_ANIM_CREDITS_PEACE_SIGN] = 'princess_credits_peace_sign',
            [CHAR_ANIM_FIRE_LAVA_BURN] = 'princess_fire_lava_burn',
            [CHAR_ANIM_GROUND_POUND] = 'princess_ground_pound',
            [CHAR_ANIM_GROUND_POUND_LANDING] = 'princess_ground_pound_landing',
            [CHAR_ANIM_TRIPLE_JUMP_GROUND_POUND] = 'princess_triple_jump_ground_pound_anim',
            [CHAR_ANIM_UNLOCK_DOOR] = 'princess_unlock_door',
            [CHAR_ANIM_SWINGING_BOWSER] = 'princess_swinging_bowser',
            [CHAR_ANIM_HOLDING_BOWSER] = 'princess_holding_bowser',
            [CHAR_ANIM_GRAB_BOWSER] = 'princess_grab_bowser',
            [CHAR_ANIM_BEND_KNESS_RIDING_SHELL] = "peach_dressfloating"
        }
    },
    --------------------
    -- Princess Daisy --
    --------------------
    {
        name = "Daisy",
        description = "Princess of the Sarasaland who was once rescued by Mario against the evil alien, Tatanga! Boasting with energy, she has joined Mario and friends on occasional friendly events, such as golf, tennis, and parties! Try to stay on her good side, if you know what's best for ya!",
        credits = "Coop Team / VA: MorphiGalaxi",
        color = {r = 255, g = 97, b = 0},
        model = smlua_model_util_get_id("daisy_geo"),
        forceChar = CT_MARIO,
        lifeIcon = get_texture_info("icon-daisy"),
        camScale = 1,
        offset = 0,
        caps = {
            normal = smlua_model_util_get_id("daisy_cap_geo"),
            wing = smlua_model_util_get_id("daisy_wing_cap_geo"),
            metal = smlua_model_util_get_id("daisy_metal_cap_geo"),
            metalWing = smlua_model_util_get_id("daisy_metal_wing_cap_geo")
        },
        palette = {
            [PANTS]  = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHIRT]  = { r = 0xEF, g = 0xCA, b = 0x11 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x00, g = 0x00, b = 0xFF },
            [HAIR]   = { r = 0xFF, g = 0x61, b = 0x00 },
            [SKIN]   = { r = 0xFD, g = 0xAE, b = 0x82 },
            [CAP]    = { r = 0xFF, g = 0x00, b = 0x00 },
            [EMBLEM] = { r = 0x00, g = 0xFF, b = 0xFF }
        },
        voices = {
            [CHAR_SOUND_ATTACKED] = {'daisy_attacked_1.ogg','daisy_attacked_2.ogg','daisy_attacked_3.ogg'},
            [CHAR_SOUND_COUGHING1] = 'daisy_coughing1.ogg',
            [CHAR_SOUND_COUGHING2] = 'daisy_coughing2.ogg',
            [CHAR_SOUND_COUGHING3] = 'daisy_coughing3.ogg',
            [CHAR_SOUND_DOH] = {'daisy_doh_1.ogg', 'daisy_doh_2.ogg'},
            [CHAR_SOUND_DROWNING] = 'daisy_drowning_1.ogg',
            [CHAR_SOUND_DYING] = 'daisy_dying.ogg',
            [CHAR_SOUND_EEUH] = 'daisy_eeuh.ogg',
            [CHAR_SOUND_GROUND_POUND_WAH] = 'daisy_ground_pound_wah.ogg',
            [CHAR_SOUND_HAHA] = 'daisy_haha.ogg',
            [CHAR_SOUND_HAHA_2] = 'daisy_haha_2.ogg',
            [CHAR_SOUND_HERE_WE_GO] = 'daisy_here_we_go.ogg',
            [CHAR_SOUND_HOOHOO] = 'daisy_hoohoo.ogg',
            [CHAR_SOUND_HRMM] = 'daisy_hrmm.ogg',
            [CHAR_SOUND_IMA_TIRED] = 'daisy_ima_tired.ogg',
            [CHAR_SOUND_MAMA_MIA] = 'daisy_mama_mia.ogg',
            [CHAR_SOUND_LETS_A_GO] = 'daisy_lets_a_go.ogg',
            [CHAR_SOUND_ON_FIRE] = 'daisy_on_fire.ogg',
            [CHAR_SOUND_OOOF] = 'daisy_oof.ogg',
            [CHAR_SOUND_OOOF2] = 'daisy_ooof2.ogg',
            [CHAR_SOUND_PANTING] = 'daisy_panting.ogg',
            [CHAR_SOUND_PANTING_COLD] = 'daisy_panting_cold.ogg',
            [CHAR_SOUND_PUNCH_HOO] = 'daisy_punch_hoo.ogg',
            [CHAR_SOUND_PUNCH_WAH] = 'daisy_punch_wah.ogg',
            [CHAR_SOUND_PUNCH_YAH] = 'daisy_punch_yah.ogg',
            [CHAR_SOUND_SO_LONGA_BOWSER] = 'daisy_so_longa_bowser.ogg',
            [CHAR_SOUND_SNORING1] = 'daisy_snoring1.ogg',
            [CHAR_SOUND_SNORING2] = 'daisy_snoring2.ogg',
            [CHAR_SOUND_SNORING3] = {'daisy_snoring2.ogg', 'daisy_snoring1.ogg', 'daisy_snoring3.ogg'},
            [CHAR_SOUND_TWIRL_BOUNCE] = 'daisy_twirl_bounce.ogg',
            [CHAR_SOUND_UH] = 'daisy_uh.ogg',
            [CHAR_SOUND_UH2] = 'daisy_uh2.ogg',
            [CHAR_SOUND_UH2_2] = 'daisy_uh2_2.ogg',
            [CHAR_SOUND_WAAAOOOW] = 'daisy_waaaooow.ogg',
            [CHAR_SOUND_WAH2] = 'daisy_wah2.ogg',
            [CHAR_SOUND_WHOA] = 'daisy_whoa.ogg',
            [CHAR_SOUND_YAHOO] = 'daisy_yahoo.ogg',
            [CHAR_SOUND_YAWNING] = 'daisy_yawning.ogg',
            [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { 'daisy_yahoo.ogg', 'daisy_yahoo2.ogg', 'daisy_yahoo3.ogg', 'daisy_yahoo4.ogg'},
            [CHAR_SOUND_YAH_WAH_HOO] = { 'daisy_yah1.ogg', 'daisy_yah2.ogg', 'daisy_yah3.ogg'},
            [CHAR_SOUND_HELLO] = 'daisy_double_jump.ogg'
        },
        anims = {
            [CHAR_ANIM_RUNNING] = 'princess_running',
            [CHAR_ANIM_IDLE_HEAD_CENTER] = 'princess_idle_head_center',
            [CHAR_ANIM_IDLE_HEAD_LEFT] = 'princess_idle_head_left',
            [CHAR_ANIM_IDLE_HEAD_RIGHT] = 'princess_idle_head_right',
            [CHAR_ANIM_BACKWARD_KB] = 'princess_backward_kb',
            [CHAR_ANIM_FIRST_PERSON] = 'princess_first_person',
            [CHAR_ANIM_FLUTTERKICK] = 'princess_flutterkick',
            [CHAR_ANIM_FLUTTERKICK_WITH_OBJ] = 'princess_flutterkick_with_obj',
            [CHAR_ANIM_FORWARD_KB] = 'princess_forward_kb',
            [CHAR_ANIM_GROUND_BONK] = 'princess_ground_bonk',
            [CHAR_ANIM_GROUND_KICK] = 'princess_ground_kick',
            [CHAR_ANIM_GROUND_THROW] = 'princess_ground_throw',
            [CHAR_ANIM_HEAVY_THROW] = 'princess_heavy_throw',
            [CHAR_ANIM_MISSING_CAP] = 'princess_missing_cap',
            [CHAR_ANIM_PULL_DOOR_WALK_IN] = 'princess_pull_door_walk_in',
            [CHAR_ANIM_FIRST_PERSON] = 'princess_first_person',
            [CHAR_ANIM_RELEASE_BOWSER] = 'princess_release_bowser',
            [CHAR_ANIM_RETURN_FROM_STAR_DANCE] = 'princess_return_from_star_dance',
            [CHAR_ANIM_RETURN_STAR_APPROACH_DOOR] = 'princess_return_star_approach_door',
            [CHAR_ANIM_SLIDEFLIP_LAND] = 'princess_sideflip_land',
            [CHAR_ANIM_SLEEP_IDLE] = 'princess_sleep_idle',
            [CHAR_ANIM_START_SLEEP_SITTING] = 'princess_sleep_sitting',
            [CHAR_ANIM_SOFT_BACK_KB] = 'princess_soft_back_kb',
            [CHAR_ANIM_SOFT_FRONT_KB] = 'princess_soft_front_kb',
            [CHAR_ANIM_STAR_DANCE] = 'princess_star_dance',
            [CHAR_ANIM_START_CROUCHING] = 'princess_start_crouch',
            [CHAR_ANIM_STOP_CROUCHING] = 'princess_stop_crouch',
            [CHAR_ANIM_START_SLEEP_IDLE] = 'princess_start_sleep',
            [CHAR_ANIM_STOP_SLIDE] = 'princess_stop_slide',
            [CHAR_ANIM_SUMMON_STAR] = 'princess_summon_star',
            [CHAR_ANIM_SWIM_WITH_OBJ_PART1] = 'princess_swim_with_obj1',
            [CHAR_ANIM_SWIM_WITH_OBJ_PART2] = 'princess_swim_with_obj2',
            [CHAR_ANIM_TRIPLE_JUMP_LAND] = 'princess_triple_jump_land',
            [CHAR_ANIM_TURNING_PART1] = 'princess_turning_part1',
            [CHAR_ANIM_TURNING_PART2] = 'princess_turning_part2',
            [CHAR_ANIM_TWIRL_LAND] = 'princess_twirl_land',
            [CHAR_ANIM_WAKE_FROM_LYING] = 'princess_wake_from_lying',
            [CHAR_ANIM_WAKE_FROM_SLEEP] = 'princess_wake_from_sleep',
            [CHAR_ANIM_CREDITS_RAISE_HAND] = 'princess_credits_raise_hand',
            [CHAR_ANIM_CREDITS_RETURN_FROM_LOOK_UP] = 'princess_credits_return_from_look_up',
            [CHAR_ANIM_CREDITS_START_WALK_LOOK_UP] = 'princess_credits_start_walk_look_up',
            [CHAR_ANIM_CREDITS_TAKE_OFF_CAP] = 'princess_credits_take_off_cap',
            [CHAR_ANIM_DYING_FALL_OVER] = 'princess_dying_fall_over',
            [CHAR_ANIM_FALL_OVER_BACKWARDS] = 'princess_fall_over_backwards',
            [CHAR_ANIM_FAST_LEDGE_GRAB] = 'princess_fast_ledge_grab',
            --[CHAR_ANIM_FINAL_BOWSER_RAISE_HAND_SPIN] = 'princess_final_bowser_raise_hand_spin',
            [CHAR_ANIM_FIRST_PUNCH_FAST] = 'princess_first_punch_fast',
            [CHAR_ANIM_GENERAL_LAND] = 'princess_general_land',
            [CHAR_ANIM_HEAD_STUCK_IN_GROUND] = 'princess_head_stuck_in_ground',
            [CHAR_ANIM_LAND_FROM_DOUBLE_JUMP] = 'princess_land_from_double_jump',
            [CHAR_ANIM_LAND_FROM_SINGLE_JUMP] = 'princess_land_from_single_jump',
            [CHAR_ANIM_LAND_ON_STOMACH] = 'princess_land_on_stomach',
            [CHAR_ANIM_LEGS_STUCK_IN_GROUND] = 'princess_legs_stuck_in_ground',
            [CHAR_ANIM_PLACE_LIGHT_OBJ] = 'princess_place_light_obj',
            [CHAR_ANIM_PUSH_DOOR_WALK_IN] = 'princess_push_door_walk_in',
            [CHAR_ANIM_PUT_CAP_ON] = 'princess_put_cap_on',
            [CHAR_ANIM_RUN_WITH_LIGHT_OBJ] = 'princess_run_with_light_obj',
            [CHAR_ANIM_SECOND_PUNCH_FAST] = 'princess_second_punch_fast',
            [CHAR_ANIM_SHIVERING_RETURN_TO_IDLE] = 'princess_shivering_returning_to_idle',
            [CHAR_ANIM_SKID_ON_GROUND] = 'princess_skid_on_ground',
            [CHAR_ANIM_SLOW_LAND_FROM_DIVE] = 'princess_slow_land_from_dive',
            [CHAR_ANIM_SLOW_LEDGE_GRAB] = 'princess_slow_ledge_grab',
            [CHAR_ANIM_SLOW_WALK_WITH_LIGHT_OBJ] = 'princess_slow_walk_with_light_obj',
            [CHAR_ANIM_STAND_UP_FROM_LAVA_BOOST] = 'princess_stand_up_from_lava_boost',
            [CHAR_ANIM_STOP_SKID] = 'princess_stop_skid',
            [CHAR_ANIM_TAKE_CAP_OFF_THEN_ON] = 'princess_take_cap_off_then_on',
            [CHAR_ANIM_THROW_CATCH_KEY] = 'princess_throw_catch_key',
            [CHAR_ANIM_WALK_WITH_LIGHT_OBJ] = 'princess_walk_with_light_obj',
            [CHAR_ANIM_BOTTOM_STUCK_IN_GROUND] = 'princess_bottom_stuck_in_ground',
            --[CHAR_ANIM_CREDITS_PEACE_SIGN] = 'princess_credits_peace_sign',
            [CHAR_ANIM_FIRE_LAVA_BURN] = 'princess_fire_lava_burn',
            [CHAR_ANIM_GROUND_POUND] = 'princess_ground_pound',
            [CHAR_ANIM_GROUND_POUND_LANDING] = 'princess_ground_pound_landing',
            [CHAR_ANIM_TRIPLE_JUMP_GROUND_POUND] = 'princess_triple_jump_ground_pound_anim',
            [CHAR_ANIM_UNLOCK_DOOR] = 'princess_unlock_door',
            [CHAR_ANIM_SWINGING_BOWSER] = 'princess_swinging_bowser',
            [CHAR_ANIM_HOLDING_BOWSER] = 'princess_holding_bowser',
            [CHAR_ANIM_GRAB_BOWSER] = 'princess_grab_bowser',
            [CHAR_ANIM_BEND_KNESS_RIDING_SHELL] = 'daisy_dressjump'
        }
    },
    -----------
    -- Yoshi --
    -----------
    {
        name = "Yoshi",
        description = "A friendly dinosuar originating from Dinosuar Land where he reunited with Mario! These cute little guys come in different colors! Might suggest to stay back when they're in a very hungry mood...",
        credits = "Coop Team / VA: FunkyLion 'Yuyake'",
        color = { r = 0, g = 255, b = 0 },
        model = smlua_model_util_get_id("yoshi_player_geo"),
        forceChar = CT_MARIO,
        lifeIcon = get_texture_info("icon-yoshi"),
        camScale = 1,
        offset = 0,
        caps = {
            normal = smlua_model_util_get_id("yoshi_player_cap_geo"),
            wing = smlua_model_util_get_id("yoshi_player_wing_cap_geo"),
            metal = smlua_model_util_get_id("yoshi_player_metal_cap_geo"),
            metalWing = smlua_model_util_get_id("yoshi_player_metal_wing_cap_geo")
        },
        palette = {
            [PANTS]  = { r = 0xFF, g = 0x00, b = 0x00 },
            [SHIRT]  = { r = 0x00, g = 0xFF, b = 0x00 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0xFF, g = 0x00, b = 0x00 },
            [HAIR]   = { r = 0xFF, g = 0x00, b = 0x00 },
            [SKIN]   = { r = 0xFF, g = 0xDE, b = 0x39 },
            [CAP]    = { r = 0x00, g = 0xFF, b = 0x00 },
            [EMBLEM] = { r = 0xFF, g = 0x00, b = 0x00 }
        },
        voices = {
            [CHAR_SOUND_ATTACKED] = "yoshi_attacked.ogg",
            [CHAR_SOUND_COUGHING1] = "yoshi_coughing1.ogg", -- missing all three
            [CHAR_SOUND_COUGHING2] = "yoshi_coughing2.ogg", -- missing all three
            [CHAR_SOUND_COUGHING3] = "yoshi_coughing3.ogg", -- missing all three
            [CHAR_SOUND_DOH] = "yoshi_doh.ogg",
            [CHAR_SOUND_DROWNING] = "yoshi_drowning.ogg",
            [CHAR_SOUND_DYING] = "yoshi_dying.ogg",
            [CHAR_SOUND_EEUH] = "yoshi_euuh.ogg",
            [CHAR_SOUND_GROUND_POUND_WAH] = "yoshi_ground_pound_wah.ogg",
            [CHAR_SOUND_HAHA] = "yoshi_haha.ogg",
            [CHAR_SOUND_HAHA_2] = "yoshi_haha2.ogg",
            [CHAR_SOUND_HERE_WE_GO] = "yoshi_herewego.ogg",
            [CHAR_SOUND_HOOHOO] = "yoshi_hoohoo.ogg",
            [CHAR_SOUND_HRMM] = "yoshi_hrmm.ogg",
            [CHAR_SOUND_IMA_TIRED] = "yoshi_imatired.ogg",
            [CHAR_SOUND_MAMA_MIA] = "yoshi_mamamia.ogg",
            [CHAR_SOUND_LETS_A_GO] = "yoshi_letsago.ogg",
            [CHAR_SOUND_ON_FIRE] = "yoshi_on_fire.ogg",
            [CHAR_SOUND_OOOF] = "yoshi_ooof.ogg",
            [CHAR_SOUND_OOOF2] = "yoshi_ooof2.ogg",
            [CHAR_SOUND_PANTING] = "yoshi_panting.ogg",
            [CHAR_SOUND_PANTING_COLD] = "yoshi_panting_cold.ogg",
            [CHAR_SOUND_PUNCH_HOO] = "yoshi_punch_hoo.ogg",
            [CHAR_SOUND_PUNCH_WAH] = "yoshi_punch_wah.ogg",
            [CHAR_SOUND_PUNCH_YAH] = "yoshi_punch_yah.ogg",
            [CHAR_SOUND_SO_LONGA_BOWSER] = "yoshi_solonga_bowser.ogg",
            [CHAR_SOUND_SNORING1] = "yoshi_snoring1.ogg",
            [CHAR_SOUND_SNORING2] = "yoshi_snoring2.ogg",
            [CHAR_SOUND_SNORING3] = {"yoshi_snoring2.ogg", "yoshi_snoring1.ogg", "yoshi_snoring3.ogg"},
            [CHAR_SOUND_TWIRL_BOUNCE] = "yoshi_twirl_bounce.ogg",
            [CHAR_SOUND_UH] = "yoshi_uh.ogg",
            [CHAR_SOUND_UH2] = "yoshi_uh2.ogg",
            [CHAR_SOUND_UH2_2] = "yoshi_uh2_2.ogg",
            [CHAR_SOUND_WAAAOOOW] = "yoshi_waaaooow.ogg",
            [CHAR_SOUND_WAH2] = "yoshi_wah.ogg",
            [CHAR_SOUND_WHOA] = "yoshi_whoa.ogg",
            [CHAR_SOUND_YAHOO] = "yoshi_yahoo.ogg",
            [CHAR_SOUND_YAWNING] = "yoshi_yawning.ogg",
            [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "yoshi_yahoo.ogg", "yoshi_yahoo1.ogg", "yoshi_yahoo2.ogg", "yoshi_yahoo3.ogg", "yoshi_yahoo4.ogg", "yoshi_yahoo5.ogg" },
            [CHAR_SOUND_YAH_WAH_HOO] = { "yoshi_yah_wah_hoo1.ogg", "yoshi_yah_wah_hoo2.ogg", "yoshi_yah_wah_hoo3.ogg"},
            [CHAR_SOUND_HELLO] = "yoshi_hello.ogg"
        },
    },
    -----------
    -- Birdo --
    -----------
    {
        name = "Birdo",
        description = "A very feminine dinosuar who has fought against Mario during his dreams! How she came into reality is anyone's guess. It is said she was once a boy before she learned more about herself in life and eventually became a girl!",
        credits = "Coop Team / VA: LuUvvUCY 'Lucy'",
        color = { r = 254, g = 77, b = 127 },
        model = smlua_model_util_get_id("birdo_geo"),
        forceChar = CT_MARIO,
        lifeIcon = get_texture_info("icon-birdo"),
        camScale = 1,
        offset = 0,
        caps = {
            normal = smlua_model_util_get_id("birdo_cap_geo"),
            wing = smlua_model_util_get_id("birdo_wing_cap_geo"),
            metal = smlua_model_util_get_id("birdo_metal_cap_geo"),
            metalWing = smlua_model_util_get_id("birdo_metal_wing_cap_geo")
        },
        palette = {
            [PANTS]  = { r = 0xFF, g = 0x00, b = 0x00 }, --FF0000
            [SHIRT]  = { r = 0xFE, g = 0x4D, b = 0x7F }, --FE4D7F
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF }, --FFFFFF
            [SHOES]  = { r = 0xFE, g = 0x4D, b = 0x7F }, --FE4D7F
            [HAIR]   = { r = 0xFF, g = 0x00, b = 0x00 }, --FF0000
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 }, --FEC179
            [CAP]    = { r = 0xFE, g = 0x4D, b = 0x7F }, --FE4D7F
            [EMBLEM] = { r = 0xFF, g = 0x00, b = 0x00 }  --FF0000
        },
        voices = {
            [CHAR_SOUND_ATTACKED] = "birdo_attacked.ogg",
            [CHAR_SOUND_COUGHING1] = "birdo_coughing1.ogg",
            [CHAR_SOUND_COUGHING2] = "birdo_coughing2.ogg",
            [CHAR_SOUND_COUGHING3] = "birdo_coughing3.ogg",
            [CHAR_SOUND_DOH] = "birdo_doh.ogg",
            [CHAR_SOUND_DROWNING] = "birdo_drowning.ogg", -- missing
            [CHAR_SOUND_DYING] = "birdo_dying.ogg",
            [CHAR_SOUND_EEUH] = "birdo_euuh.ogg",
            [CHAR_SOUND_GROUND_POUND_WAH] = "birdo_ground_pound_wah.ogg",
            [CHAR_SOUND_HAHA] = "birdo_haha.ogg",
            [CHAR_SOUND_HAHA_2] = "birdo_haha2.ogg",
            [CHAR_SOUND_HERE_WE_GO] = "birdo_herewego.ogg",
            [CHAR_SOUND_HOOHOO] = "birdo_hoohoo.ogg",
            [CHAR_SOUND_HRMM] = "birdo_hrmm.ogg",
            [CHAR_SOUND_IMA_TIRED] = "birdo_imatired.ogg",
            [CHAR_SOUND_MAMA_MIA] = "birdo_mamamia.ogg", -- Missing
            [CHAR_SOUND_LETS_A_GO] = "birdo_letsago.ogg",
            [CHAR_SOUND_ON_FIRE] = "birdo_on_fire.ogg",
            [CHAR_SOUND_OOOF] = "birdo_ooof.ogg",
            [CHAR_SOUND_OOOF2] = "birdo_ooof2.ogg",
            [CHAR_SOUND_PANTING] = "birdo_panting.ogg",
            [CHAR_SOUND_PANTING_COLD] = "birdo_panting_cold.ogg",
            [CHAR_SOUND_PUNCH_HOO] = "birdo_punch_hoo.ogg",
            [CHAR_SOUND_PUNCH_WAH] = "birdo_punch_wah.ogg",
            [CHAR_SOUND_PUNCH_YAH] = "birdo_punch_yah.ogg",
            [CHAR_SOUND_SO_LONGA_BOWSER] = "birdo_solonga_bowser.ogg",
            [CHAR_SOUND_SNORING1] = "birdo_snoring1.ogg",
            [CHAR_SOUND_SNORING2] = "birdo_snoring2.ogg",
            [CHAR_SOUND_SNORING3] = {"birdo_snoring2.ogg", "birdo_snoring1.ogg", "birdo_snoring3.ogg"},
            [CHAR_SOUND_TWIRL_BOUNCE] = "birdo_twirl_bounce.ogg",
            [CHAR_SOUND_UH] = "birdo_uh.ogg",
            [CHAR_SOUND_UH2] = "birdo_uh2.ogg",
            [CHAR_SOUND_UH2_2] = "birdo_uh2_2.ogg",
            [CHAR_SOUND_WAAAOOOW] = "birdo_waaaooow.ogg",
            [CHAR_SOUND_WAH2] = "birdo_ground_pound_wah.ogg",
            [CHAR_SOUND_WHOA] = "birdo_whoa.ogg",
            [CHAR_SOUND_YAHOO] = "birdo_yahoo.ogg",
            [CHAR_SOUND_YAWNING] = "birdo_yawning.ogg",
            [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "birdo_yahoo.ogg", "birdo_yahoo1.ogg", "birdo_yahoo2.ogg", "birdo_yahoo3.ogg", "birdo_yahoo4.ogg", "birdo_yahoo5.ogg" },
            [CHAR_SOUND_YAH_WAH_HOO] = { "birdo_yah_wah_hoo1.ogg", "birdo_yah_wah_hoo2.ogg", "birdo_yah_wah_hoo3.ogg"},
            [CHAR_SOUND_HELLO] = "birdo_hello.ogg"
        },
    },

--------------------------------
-- Extra Characters - Wave II --
--------------------------------

    -----------
    -- Spike --
    -----------
    {
        name = "Spike",
        description = "Owner of the Wrecking Crew company and former boss of the Mario Brothers before they moved to the plumbing business! He's had a vendetta against the bros since! Quite versitile with his hammer!",
        credits = "Coop Team / VA: VinnyVinesauce",
        color = {r = 88, g = 142, b = 255},
        model = smlua_model_util_get_id("foreman_spike_geo"),
        forceChar = CT_MARIO,
        lifeIcon = get_texture_info("icon-spike"),
        camScale = 1,
        offset = 0,
        caps = {
            normal = smlua_model_util_get_id("foreman_spike_cap_geo"),
            wing = smlua_model_util_get_id("foreman_spike_wing_cap_geo"),
            metal = smlua_model_util_get_id("foreman_spike_metal_cap_geo"),
            metalWing = smlua_model_util_get_id("foreman_spike_metal_wing_cap_geo")
        },
        palette = {
            [PANTS]  = { r = 0x00, g = 0x00, b = 0xFF }, -- 0000FF
            [SHIRT]  = { r = 0x56, g = 0x8E, b = 0xFF }, -- 568EFF
            [GLOVES] = { r = 0x61, g = 0x3E, b = 0x21 }, -- 613E21
            [SHOES]  = { r = 0x61, g = 0x3E, b = 0x21 }, -- 613E21
            [HAIR]   = { r = 0x00, g = 0x00, b = 0x00 }, -- 000000
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 }, -- FEC179
            [CAP]    = { r = 0x56, g = 0x8E, b = 0xFF }, -- 568EFF
            [EMBLEM] = { r = 0xFF, g = 0xFF, b = 0x00 }  -- FFFF00
        },
        voices = {
            [CHAR_SOUND_ATTACKED] = "foreman_spike_attacked.ogg",
            [CHAR_SOUND_COUGHING1] = "foreman_spike_coughing1.ogg",
            [CHAR_SOUND_COUGHING2] = "foreman_spike_coughing2.ogg",
            [CHAR_SOUND_COUGHING3] = "foreman_spike_coughing3.ogg",
            [CHAR_SOUND_DOH] = "foreman_spike_doh.ogg",
            [CHAR_SOUND_DROWNING] = "foreman_spike_drowning.ogg",
            [CHAR_SOUND_DYING] = "foreman_spike_dying.ogg",
            [CHAR_SOUND_EEUH] = "foreman_spike_eeuh.ogg",
            [CHAR_SOUND_GROUND_POUND_WAH] = "foreman_spike_ground_pound_wah.ogg",
            [CHAR_SOUND_HAHA] = "foreman_spike_haha.ogg",
            [CHAR_SOUND_HAHA_2] = "foreman_spike_haha.ogg",
            [CHAR_SOUND_HERE_WE_GO] = "foreman_spike_herewego.ogg",
            [CHAR_SOUND_HOOHOO] = "foreman_spike_hoohoo.ogg",
            [CHAR_SOUND_HRMM] = "foreman_spike_hrmm.ogg",
            [CHAR_SOUND_IMA_TIRED] = "foreman_spike_imatired.ogg",
            [CHAR_SOUND_MAMA_MIA] = "foreman_spike_mamamia.ogg",
            [CHAR_SOUND_LETS_A_GO] = "foreman_spike_letsago.ogg",
            [CHAR_SOUND_ON_FIRE] = "foreman_spike_on_fire.ogg",
            [CHAR_SOUND_OOOF] = "foreman_spike_ooof.ogg",
            [CHAR_SOUND_OOOF2] = "foreman_spike_ooof2.ogg",
            [CHAR_SOUND_PANTING] = "foreman_spike_panting.ogg",
            [CHAR_SOUND_PANTING_COLD] = "foreman_spike_panting_cold.ogg",
            [CHAR_SOUND_PUNCH_HOO] = "foreman_spike_punch_hoo.ogg",
            [CHAR_SOUND_PUNCH_WAH] = "foreman_spike_punch_wah.ogg",
            [CHAR_SOUND_PUNCH_YAH] = "foreman_spike_punch_yah.ogg",
            [CHAR_SOUND_SO_LONGA_BOWSER] = "foreman_spike_solonga_bowser.ogg",
            [CHAR_SOUND_SNORING1] = "foreman_spike_snoring1.ogg",
            [CHAR_SOUND_SNORING2] = "foreman_spike_snoring2.ogg",
            [CHAR_SOUND_SNORING3] = {"foreman_spike_snoring2.ogg", "foreman_spike_snoring1.ogg", "foreman_spike_snoring3.ogg"},
            [CHAR_SOUND_TWIRL_BOUNCE] = "foreman_spike_twirl_bounce.ogg",
            [CHAR_SOUND_UH] = "foreman_spike_uh.ogg",
            [CHAR_SOUND_UH2] = "foreman_spike_uh2.ogg",
            [CHAR_SOUND_UH2_2] = "foreman_spike_uh2_2.ogg",
            [CHAR_SOUND_WAAAOOOW] = "foreman_spike_waaaooow.ogg",
            [CHAR_SOUND_WAH2] = "foreman_spike_wah2.ogg",
            [CHAR_SOUND_WHOA] = "foreman_spike_whoa.ogg",
            [CHAR_SOUND_YAHOO] = "foreman_spike_yahoo.ogg",
            [CHAR_SOUND_YAWNING] = "foreman_spike_yawning.ogg",
            [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "foreman_spike_yahoo.ogg", "foreman_spike_yahoo1.ogg", "foreman_spike_yahoo2.ogg", "foreman_spike_yahoo3.ogg", "foreman_spike_yahoo4.ogg", "foreman_spike_yahoo5.ogg" },
            [CHAR_SOUND_YAH_WAH_HOO] = { "foreman_spike_yah_wah_hoo1.ogg", "foreman_spike_yah_wah_hoo2.ogg", "foreman_spike_yah_wah_hoo3.ogg"},
            [CHAR_SOUND_HELLO] = "foreman_spike_hello.ogg"
        },
    },
    -------------
    -- Pauline --
    -------------
    {
        name = "Pauline",
        description = "Mayor of New Donk City who was originally saved by Mario in his days as a carpenter against the big ape, Donkey Kong!",
        credits = "Coop Team / VA: BeckyVO",
        color = {r = 207, g = 66, b = 57},
        model = smlua_model_util_get_id("pauline_geo"),
        forceChar = CT_MARIO,
        lifeIcon = get_texture_info("icon-pauline"),
        camScale = 1,
        offset = 0,
        caps = {
            normal = smlua_model_util_get_id("pauline_cap_geo"),
            wing = smlua_model_util_get_id("pauline_wing_cap_geo"),
            metal = smlua_model_util_get_id("pauline_metal_cap_geo"),
            metalWing = smlua_model_util_get_id("pauline_metal_wing_cap_geo")
        },
        palette = {
            [PANTS]  = { r = 0xCF, g = 0x42, b = 0x39 }, -- CF4239
            [SHIRT]  = { r = 0xCF, g = 0x42, b = 0x39 }, -- CF4239
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0x00 }, -- FFFF00
            [SHOES]  = { r = 0xCF, g = 0x42, b = 0x39 }, -- CF4239
            [HAIR]   = { r = 0x79, g = 0x31, b = 0x27 }, -- 793127
            [SKIN]   = { r = 0xF8, g = 0xC1, b = 0xAC }, -- F8C1AC
            [CAP]    = { r = 0xCF, g = 0x42, b = 0x39 }, -- CF4239
            [EMBLEM] = { r = 0xFF, g = 0xFF, b = 0x00 }  -- FFFF00
        },
        voices = {
            [CHAR_SOUND_ATTACKED] = "pauline_attacked.ogg",
            [CHAR_SOUND_COUGHING1] = "pauline_coughing1.ogg",
            [CHAR_SOUND_COUGHING2] = "pauline_coughing2.ogg",
            [CHAR_SOUND_COUGHING3] = "pauline_coughing3.ogg",
            [CHAR_SOUND_DOH] = "pauline_doh.ogg",
            [CHAR_SOUND_DROWNING] = "pauline_drowning.ogg",
            [CHAR_SOUND_DYING] = "pauline_dying.ogg",
            [CHAR_SOUND_EEUH] = "pauline_eeuh.ogg",
            [CHAR_SOUND_GROUND_POUND_WAH] = "pauline_ground_pound_wah.ogg",
            [CHAR_SOUND_HAHA] = "pauline_haha.ogg",
            [CHAR_SOUND_HAHA_2] = "pauline_haha.ogg",
            [CHAR_SOUND_HERE_WE_GO] = "pauline_herewego.ogg",
            [CHAR_SOUND_HOOHOO] = "pauline_hoohoo.ogg",
            [CHAR_SOUND_HRMM] = "pauline_hrmm.ogg",
            [CHAR_SOUND_IMA_TIRED] = "pauline_imatired.ogg",
            [CHAR_SOUND_MAMA_MIA] = "pauline_mamamia.ogg",
            [CHAR_SOUND_LETS_A_GO] = "pauline_letsago.ogg",
            [CHAR_SOUND_ON_FIRE] = "pauline_on_fire.ogg",
            [CHAR_SOUND_OOOF] = "pauline_ooof.ogg",
            [CHAR_SOUND_OOOF2] = "pauline_ooof2.ogg",
            [CHAR_SOUND_PANTING] = "pauline_panting.ogg",
            [CHAR_SOUND_PANTING_COLD] = "pauline_panting_cold.ogg",
            [CHAR_SOUND_PUNCH_HOO] = "pauline_punch_hoo.ogg",
            [CHAR_SOUND_PUNCH_WAH] = "pauline_punch_wah.ogg",
            [CHAR_SOUND_PUNCH_YAH] = "pauline_punch_yah.ogg",
            [CHAR_SOUND_SO_LONGA_BOWSER] = "pauline_solonga_bowser.ogg",
            [CHAR_SOUND_SNORING1] = "pauline_snoring1.ogg",
            [CHAR_SOUND_SNORING2] = "pauline_snoring2.ogg",
            [CHAR_SOUND_SNORING3] = {"pauline_snoring2.ogg", "pauline_snoring1.ogg", "pauline_snoring3.ogg"},
            [CHAR_SOUND_TWIRL_BOUNCE] = "pauline_twirl_bounce.ogg",
            [CHAR_SOUND_UH] = "pauline_uh.ogg",
            [CHAR_SOUND_UH2] = "pauline_uh2.ogg",
            [CHAR_SOUND_UH2_2] = "pauline_uh2_2.ogg",
            [CHAR_SOUND_WAAAOOOW] = "pauline_waaaooow.ogg",
            [CHAR_SOUND_WAH2] = "pauline_ground_pound_wah.ogg",
            [CHAR_SOUND_WHOA] = "pauline_whoa.ogg",
            [CHAR_SOUND_YAHOO] = "pauline_yahoo.ogg",
            [CHAR_SOUND_YAWNING] = "pauline_yawning.ogg",
            [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "pauline_yahoo.ogg", "pauline_yahoo1.ogg", "pauline_yahoo2.ogg", "pauline_yahoo3.ogg", "pauline_yahoo4.ogg", "pauline_yahoo5.ogg" },
            [CHAR_SOUND_YAH_WAH_HOO] = { "pauline_yah_wah_hoo1.ogg", "pauline_yah_wah_hoo2.ogg", "pauline_yah_wah_hoo3.ogg"},
            [CHAR_SOUND_HELLO] = "pauline_hello.ogg"
        },
        anims = {
            [CHAR_ANIM_RUNNING] = 'princess_running',
            [CHAR_ANIM_IDLE_HEAD_CENTER] = 'princess_idle_head_center',
            [CHAR_ANIM_IDLE_HEAD_LEFT] = 'princess_idle_head_left',
            [CHAR_ANIM_IDLE_HEAD_RIGHT] = 'princess_idle_head_right',
            [CHAR_ANIM_BACKWARD_KB] = 'princess_backward_kb',
            [CHAR_ANIM_FIRST_PERSON] = 'princess_first_person',
            [CHAR_ANIM_FLUTTERKICK] = 'princess_flutterkick',
            [CHAR_ANIM_FLUTTERKICK_WITH_OBJ] = 'princess_flutterkick_with_obj',
            [CHAR_ANIM_FORWARD_KB] = 'princess_forward_kb',
            [CHAR_ANIM_GROUND_BONK] = 'princess_ground_bonk',
            [CHAR_ANIM_GROUND_KICK] = 'princess_ground_kick',
            [CHAR_ANIM_GROUND_THROW] = 'princess_ground_throw',
            [CHAR_ANIM_HEAVY_THROW] = 'princess_heavy_throw',
            [CHAR_ANIM_MISSING_CAP] = 'princess_missing_cap',
            [CHAR_ANIM_PULL_DOOR_WALK_IN] = 'princess_pull_door_walk_in',
            [CHAR_ANIM_FIRST_PERSON] = 'princess_first_person',
            [CHAR_ANIM_RELEASE_BOWSER] = 'princess_release_bowser',
            [CHAR_ANIM_RETURN_FROM_STAR_DANCE] = 'princess_return_from_star_dance',
            [CHAR_ANIM_RETURN_STAR_APPROACH_DOOR] = 'princess_return_star_approach_door',
            [CHAR_ANIM_SLIDEFLIP_LAND] = 'princess_sideflip_land',
            [CHAR_ANIM_SLEEP_IDLE] = 'princess_sleep_idle',
            [CHAR_ANIM_START_SLEEP_SITTING] = 'princess_sleep_sitting',
            [CHAR_ANIM_SOFT_BACK_KB] = 'princess_soft_back_kb',
            [CHAR_ANIM_SOFT_FRONT_KB] = 'princess_soft_front_kb',
            [CHAR_ANIM_STAR_DANCE] = 'princess_star_dance',
            [CHAR_ANIM_START_CROUCHING] = 'princess_start_crouch',
            [CHAR_ANIM_STOP_CROUCHING] = 'princess_stop_crouch',
            [CHAR_ANIM_START_SLEEP_IDLE] = 'princess_start_sleep',
            [CHAR_ANIM_STOP_SLIDE] = 'princess_stop_slide',
            [CHAR_ANIM_SUMMON_STAR] = 'princess_summon_star',
            [CHAR_ANIM_SWIM_WITH_OBJ_PART1] = 'princess_swim_with_obj1',
            [CHAR_ANIM_SWIM_WITH_OBJ_PART2] = 'princess_swim_with_obj2',
            [CHAR_ANIM_TRIPLE_JUMP_LAND] = 'princess_triple_jump_land',
            [CHAR_ANIM_TURNING_PART1] = 'princess_turning_part1',
            [CHAR_ANIM_TURNING_PART2] = 'princess_turning_part2',
            [CHAR_ANIM_TWIRL_LAND] = 'princess_twirl_land',
            [CHAR_ANIM_WAKE_FROM_LYING] = 'princess_wake_from_lying',
            [CHAR_ANIM_WAKE_FROM_SLEEP] = 'princess_wake_from_sleep',
            [CHAR_ANIM_CREDITS_RAISE_HAND] = 'princess_credits_raise_hand',
            [CHAR_ANIM_CREDITS_RETURN_FROM_LOOK_UP] = 'princess_credits_return_from_look_up',
            [CHAR_ANIM_CREDITS_START_WALK_LOOK_UP] = 'princess_credits_start_walk_look_up',
            [CHAR_ANIM_CREDITS_TAKE_OFF_CAP] = 'princess_credits_take_off_cap',
            [CHAR_ANIM_DYING_FALL_OVER] = 'princess_dying_fall_over',
            [CHAR_ANIM_FALL_OVER_BACKWARDS] = 'princess_fall_over_backwards',
            [CHAR_ANIM_FAST_LEDGE_GRAB] = 'princess_fast_ledge_grab',
            --[CHAR_ANIM_FINAL_BOWSER_RAISE_HAND_SPIN] = 'princess_final_bowser_raise_hand_spin',
            [CHAR_ANIM_FIRST_PUNCH_FAST] = 'princess_first_punch_fast',
            [CHAR_ANIM_GENERAL_LAND] = 'princess_general_land',
            [CHAR_ANIM_HEAD_STUCK_IN_GROUND] = 'princess_head_stuck_in_ground',
            [CHAR_ANIM_LAND_FROM_DOUBLE_JUMP] = 'princess_land_from_double_jump',
            [CHAR_ANIM_LAND_FROM_SINGLE_JUMP] = 'princess_land_from_single_jump',
            [CHAR_ANIM_LAND_ON_STOMACH] = 'princess_land_on_stomach',
            [CHAR_ANIM_LEGS_STUCK_IN_GROUND] = 'princess_legs_stuck_in_ground',
            [CHAR_ANIM_PLACE_LIGHT_OBJ] = 'princess_place_light_obj',
            [CHAR_ANIM_PUSH_DOOR_WALK_IN] = 'princess_push_door_walk_in',
            [CHAR_ANIM_PUT_CAP_ON] = 'princess_put_cap_on',
            [CHAR_ANIM_RUN_WITH_LIGHT_OBJ] = 'princess_run_with_light_obj',
            [CHAR_ANIM_SECOND_PUNCH_FAST] = 'princess_second_punch_fast',
            [CHAR_ANIM_SHIVERING_RETURN_TO_IDLE] = 'princess_shivering_returning_to_idle',
            [CHAR_ANIM_SKID_ON_GROUND] = 'princess_skid_on_ground',
            [CHAR_ANIM_SLOW_LAND_FROM_DIVE] = 'princess_slow_land_from_dive',
            [CHAR_ANIM_SLOW_LEDGE_GRAB] = 'princess_slow_ledge_grab',
            [CHAR_ANIM_SLOW_WALK_WITH_LIGHT_OBJ] = 'princess_slow_walk_with_light_obj',
            [CHAR_ANIM_STAND_UP_FROM_LAVA_BOOST] = 'princess_stand_up_from_lava_boost',
            [CHAR_ANIM_STOP_SKID] = 'princess_stop_skid',
            [CHAR_ANIM_TAKE_CAP_OFF_THEN_ON] = 'princess_take_cap_off_then_on',
            [CHAR_ANIM_THROW_CATCH_KEY] = 'princess_throw_catch_key',
            [CHAR_ANIM_WALK_WITH_LIGHT_OBJ] = 'princess_walk_with_light_obj',
            [CHAR_ANIM_BOTTOM_STUCK_IN_GROUND] = 'princess_bottom_stuck_in_ground',
            --[CHAR_ANIM_CREDITS_PEACE_SIGN] = 'princess_credits_peace_sign',
            [CHAR_ANIM_FIRE_LAVA_BURN] = 'princess_fire_lava_burn',
            [CHAR_ANIM_GROUND_POUND] = 'princess_ground_pound',
            [CHAR_ANIM_GROUND_POUND_LANDING] = 'princess_ground_pound_landing',
            [CHAR_ANIM_TRIPLE_JUMP_GROUND_POUND] = 'princess_triple_jump_ground_pound_anim',
            [CHAR_ANIM_UNLOCK_DOOR] = 'princess_unlock_door',
            [CHAR_ANIM_SWINGING_BOWSER] = 'princess_swinging_bowser',
            [CHAR_ANIM_HOLDING_BOWSER] = 'princess_holding_bowser',
            [CHAR_ANIM_GRAB_BOWSER] = 'princess_grab_bowser'
        }
    },
    --------------
    -- Rosalina --
    --------------
    {
        name = "Rosalina",
        description = "Protector of the cosmos and mother to billions of Lumas. She was once a little girl who lost her own mother after traveling the cosmos to help a little Luma find their own mother. She has taken her role as their mother since.",
        credits = "Coop Team / VA: GauntletQueen",
        color = {r = 143, g = 239, b = 246},
        model = smlua_model_util_get_id("rosalina_geo"),
        forceChar = CT_MARIO,
        lifeIcon = get_texture_info("icon-rosalina"),
        camScale = 1.1,
        offset = 0,
        caps = {
            normal = smlua_model_util_get_id("rosalina_cap_geo"),
            wing = smlua_model_util_get_id("rosalina_wing_cap_geo"),
            metal = smlua_model_util_get_id("rosalina_metal_cap_geo"),
            metalWing = smlua_model_util_get_id("rosalina_metal_wing_cap_geo")
        },
        palette = {
            [PANTS]  = { r = 0x8F, g = 0xEF, b = 0xF6 }, -- 8FEFF6
            [SHIRT]  = { r = 0x8F, g = 0xEF, b = 0xF6 }, -- 8FEFF6
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF }, -- FFFFFF
            [SHOES]  = { r = 0xFF, g = 0xFF, b = 0x00 }, -- FFFF00
            [HAIR]   = { r = 0xFC, g = 0xC6, b = 0x9A }, -- FCC69A
            [SKIN]   = { r = 0xFC, g = 0xE3, b = 0xCD }, -- FCE3CD
            [CAP]    = { r = 0xB7, g = 0xB7, b = 0xBB }, -- B7B7BB
            [EMBLEM] = { r = 0xFF, g = 0xFF, b = 0x00 }  -- FFFF00
        },
        voices = {
            [CHAR_SOUND_ATTACKED] = "rosalina_attacked.ogg",
            [CHAR_SOUND_COUGHING1] = "rosalina_coughing1.ogg",
            [CHAR_SOUND_COUGHING2] = "rosalina_coughing2.ogg",
            [CHAR_SOUND_COUGHING3] = "rosalina_coughing3.ogg",
            [CHAR_SOUND_DOH] = "rosalina_doh.ogg",
            [CHAR_SOUND_DROWNING] = "rosalina_drowning.ogg",
            [CHAR_SOUND_DYING] = "rosalina_dying.ogg",
            [CHAR_SOUND_EEUH] = "rosalina_eeuh.ogg",
            [CHAR_SOUND_GROUND_POUND_WAH] = "rosalina_ground_pound_wah.ogg",
            [CHAR_SOUND_HAHA] = "rosalina_haha.ogg",
            [CHAR_SOUND_HAHA_2] = "rosalina_haha.ogg",
            [CHAR_SOUND_HERE_WE_GO] = "rosalina_herewego.ogg",
            [CHAR_SOUND_HOOHOO] = "rosalina_hoohoo.ogg",
            [CHAR_SOUND_HRMM] = "rosalina_hrmm.ogg",
            [CHAR_SOUND_IMA_TIRED] = "rosalina_imatired.ogg",
            [CHAR_SOUND_MAMA_MIA] = "rosalina_mamamia.ogg",
            [CHAR_SOUND_LETS_A_GO] = "rosalina_letsago.ogg",
            [CHAR_SOUND_ON_FIRE] = "rosalina_on_fire.ogg",
            [CHAR_SOUND_OOOF] = "rosalina_ooof.ogg",
            [CHAR_SOUND_OOOF2] = "rosalina_ooof2.ogg",
            [CHAR_SOUND_PANTING] = "rosalina_panting.ogg",
            [CHAR_SOUND_PANTING_COLD] = "rosalina_panting_cold.ogg",
            [CHAR_SOUND_PUNCH_HOO] = "rosalina_punch_hoo.ogg",
            [CHAR_SOUND_PUNCH_WAH] = "rosalina_punch_wah.ogg",
            [CHAR_SOUND_PUNCH_YAH] = "rosalina_punch_yah.ogg",
            [CHAR_SOUND_SO_LONGA_BOWSER] = "rosalina_solonga_bowser.ogg",
            [CHAR_SOUND_SNORING1] = "rosalina_snoring1.ogg",
            [CHAR_SOUND_SNORING2] = "rosalina_snoring2.ogg",
            [CHAR_SOUND_SNORING3] = {"rosalina_snoring2.ogg", "rosalina_snoring1.ogg", "rosalina_snoring3.ogg"},
            [CHAR_SOUND_TWIRL_BOUNCE] = "rosalina_twirl_bounce.ogg",
            [CHAR_SOUND_UH] = "rosalina_uh.ogg",
            [CHAR_SOUND_UH2] = "rosalina_uh2.ogg",
            [CHAR_SOUND_UH2_2] = "rosalina_uh2_2.ogg",
            [CHAR_SOUND_WAAAOOOW] = "rosalina_waaaooow.ogg",
            [CHAR_SOUND_WAH2] = "rosalina_ground_pound_wah.ogg",
            [CHAR_SOUND_WHOA] = "rosalina_whoa.ogg",
            [CHAR_SOUND_YAHOO] = "rosalina_yahoo.ogg",
            [CHAR_SOUND_YAWNING] = "rosalina_yawning.ogg",
            [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "rosalina_yahoo.ogg", "rosalina_yahoo1.ogg", "rosalina_yahoo2.ogg", "rosalina_yahoo3.ogg", "rosalina_yahoo4.ogg", "rosalina_yahoo5.ogg" },
            [CHAR_SOUND_YAH_WAH_HOO] = { "rosalina_yah_wah_hoo1.ogg", "rosalina_yah_wah_hoo2.ogg", "rosalina_yah_wah_hoo3.ogg"},
            [CHAR_SOUND_HELLO] = {"rosalina_hello.ogg", "rosalina_hello1.ogg", "rosalina_hello2.ogg", "rosalina_hello3.ogg", "rosalina_hello4.ogg"}
        },
        anims = {
            [CHAR_ANIM_RUNNING] = 'rosalina_running',
            [CHAR_ANIM_IDLE_HEAD_CENTER] = 'princess_idle_head_center',
            [CHAR_ANIM_IDLE_HEAD_LEFT] = 'princess_idle_head_left',
            [CHAR_ANIM_IDLE_HEAD_RIGHT] = 'princess_idle_head_right',
            [CHAR_ANIM_BACKWARD_KB] = 'princess_backward_kb',
            [CHAR_ANIM_FIRST_PERSON] = 'princess_first_person',
            [CHAR_ANIM_FLUTTERKICK] = 'princess_flutterkick',
            [CHAR_ANIM_FLUTTERKICK_WITH_OBJ] = 'princess_flutterkick_with_obj',
            [CHAR_ANIM_FORWARD_KB] = 'princess_forward_kb',
            [CHAR_ANIM_GROUND_BONK] = 'princess_ground_bonk',
            [CHAR_ANIM_GROUND_KICK] = 'princess_ground_kick',
            [CHAR_ANIM_GROUND_THROW] = 'princess_ground_throw',
            [CHAR_ANIM_HEAVY_THROW] = 'princess_heavy_throw',
            [CHAR_ANIM_MISSING_CAP] = 'princess_missing_cap',
            [CHAR_ANIM_PULL_DOOR_WALK_IN] = 'princess_pull_door_walk_in',
            [CHAR_ANIM_FIRST_PERSON] = 'princess_first_person',
            [CHAR_ANIM_RELEASE_BOWSER] = 'princess_release_bowser',
            [CHAR_ANIM_RETURN_FROM_STAR_DANCE] = 'princess_return_from_star_dance',
            [CHAR_ANIM_RETURN_STAR_APPROACH_DOOR] = 'princess_return_star_approach_door',
            [CHAR_ANIM_SLIDEFLIP_LAND] = 'princess_sideflip_land',
            [CHAR_ANIM_SLEEP_IDLE] = 'princess_sleep_idle',
            [CHAR_ANIM_START_SLEEP_SITTING] = 'princess_sleep_sitting',
            [CHAR_ANIM_SOFT_BACK_KB] = 'princess_soft_back_kb',
            [CHAR_ANIM_SOFT_FRONT_KB] = 'princess_soft_front_kb',
            [CHAR_ANIM_STAR_DANCE] = 'princess_star_dance',
            [CHAR_ANIM_START_CROUCHING] = 'princess_start_crouch',
            [CHAR_ANIM_STOP_CROUCHING] = 'princess_stop_crouch',
            [CHAR_ANIM_START_SLEEP_IDLE] = 'princess_start_sleep',
            [CHAR_ANIM_STOP_SLIDE] = 'princess_stop_slide',
            [CHAR_ANIM_SUMMON_STAR] = 'princess_summon_star',
            [CHAR_ANIM_SWIM_WITH_OBJ_PART1] = 'princess_swim_with_obj1',
            [CHAR_ANIM_SWIM_WITH_OBJ_PART2] = 'princess_swim_with_obj2',
            [CHAR_ANIM_TRIPLE_JUMP_LAND] = 'princess_triple_jump_land',
            [CHAR_ANIM_TURNING_PART1] = 'princess_turning_part1',
            [CHAR_ANIM_TURNING_PART2] = 'princess_turning_part2',
            [CHAR_ANIM_TWIRL_LAND] = 'princess_twirl_land',
            [CHAR_ANIM_WAKE_FROM_LYING] = 'princess_wake_from_lying',
            [CHAR_ANIM_WAKE_FROM_SLEEP] = 'princess_wake_from_sleep',
            [CHAR_ANIM_CREDITS_RAISE_HAND] = 'princess_credits_raise_hand',
            [CHAR_ANIM_CREDITS_RETURN_FROM_LOOK_UP] = 'princess_credits_return_from_look_up',
            [CHAR_ANIM_CREDITS_START_WALK_LOOK_UP] = 'princess_credits_start_walk_look_up',
            [CHAR_ANIM_CREDITS_TAKE_OFF_CAP] = 'princess_credits_take_off_cap',
            [CHAR_ANIM_DYING_FALL_OVER] = 'princess_dying_fall_over',
            [CHAR_ANIM_FALL_OVER_BACKWARDS] = 'princess_fall_over_backwards',
            [CHAR_ANIM_FAST_LEDGE_GRAB] = 'princess_fast_ledge_grab',
            --[CHAR_ANIM_FINAL_BOWSER_RAISE_HAND_SPIN] = 'princess_final_bowser_raise_hand_spin',
            [CHAR_ANIM_FIRST_PUNCH_FAST] = 'princess_first_punch_fast',
            [CHAR_ANIM_GENERAL_LAND] = 'princess_general_land',
            [CHAR_ANIM_HEAD_STUCK_IN_GROUND] = 'princess_head_stuck_in_ground',
            [CHAR_ANIM_LAND_FROM_DOUBLE_JUMP] = 'princess_land_from_double_jump',
            [CHAR_ANIM_LAND_FROM_SINGLE_JUMP] = 'princess_land_from_single_jump',
            [CHAR_ANIM_LAND_ON_STOMACH] = 'princess_land_on_stomach',
            [CHAR_ANIM_LEGS_STUCK_IN_GROUND] = 'princess_legs_stuck_in_ground',
            [CHAR_ANIM_PLACE_LIGHT_OBJ] = 'princess_place_light_obj',
            [CHAR_ANIM_PUSH_DOOR_WALK_IN] = 'princess_push_door_walk_in',
            [CHAR_ANIM_PUT_CAP_ON] = 'princess_put_cap_on',
            [CHAR_ANIM_RUN_WITH_LIGHT_OBJ] = 'princess_run_with_light_obj',
            [CHAR_ANIM_SECOND_PUNCH_FAST] = 'princess_second_punch_fast',
            [CHAR_ANIM_SHIVERING_RETURN_TO_IDLE] = 'princess_shivering_returning_to_idle',
            [CHAR_ANIM_SKID_ON_GROUND] = 'princess_skid_on_ground',
            [CHAR_ANIM_SLOW_LAND_FROM_DIVE] = 'princess_slow_land_from_dive',
            [CHAR_ANIM_SLOW_LEDGE_GRAB] = 'princess_slow_ledge_grab',
            [CHAR_ANIM_SLOW_WALK_WITH_LIGHT_OBJ] = 'princess_slow_walk_with_light_obj',
            [CHAR_ANIM_STAND_UP_FROM_LAVA_BOOST] = 'princess_stand_up_from_lava_boost',
            [CHAR_ANIM_STOP_SKID] = 'princess_stop_skid',
            [CHAR_ANIM_TAKE_CAP_OFF_THEN_ON] = 'princess_take_cap_off_then_on',
            [CHAR_ANIM_THROW_CATCH_KEY] = 'princess_throw_catch_key',
            [CHAR_ANIM_WALK_WITH_LIGHT_OBJ] = 'princess_walk_with_light_obj',
            [CHAR_ANIM_BOTTOM_STUCK_IN_GROUND] = 'princess_bottom_stuck_in_ground',
            --[CHAR_ANIM_CREDITS_PEACE_SIGN] = 'princess_credits_peace_sign',
            [CHAR_ANIM_FIRE_LAVA_BURN] = 'princess_fire_lava_burn',
            [CHAR_ANIM_GROUND_POUND] = 'princess_ground_pound',
            [CHAR_ANIM_GROUND_POUND_LANDING] = 'princess_ground_pound_landing',
            [CHAR_ANIM_TRIPLE_JUMP_GROUND_POUND] = 'princess_triple_jump_ground_pound_anim',
            [CHAR_ANIM_UNLOCK_DOOR] = 'princess_unlock_door',
            [CHAR_ANIM_SWINGING_BOWSER] = 'princess_swinging_bowser',
            [CHAR_ANIM_HOLDING_BOWSER] = 'princess_holding_bowser',
            [CHAR_ANIM_GRAB_BOWSER] = 'princess_grab_bowser',
            [CHAR_ANIM_BEND_KNESS_RIDING_SHELL] = 'rosalina_spinjump',
        }
    },
}

local TEXT_VOICE_ACTOR = " (Voice Actors)"
local TEXT_MOVESET     = " (Movesets)"

local CSloaded = false
local function on_character_select_load()
    for i = 1, #extraCharacters do
        local char = extraCharacters[i]
        char.tablePos = _G.charSelect.character_add(char.name, char.description, char.credits, char.color, char.model, char.forceChar, char.lifeIcon, char.camScale, char.offset, char.meter)
        if char.caps then _G.charSelect.character_add_caps(char.model, char.caps) end
        if char.voices then _G.charSelect.character_add_voice(char.model, char.voices) end
        if char.palette then _G.charSelect.character_add_palette_preset(char.model, char.palette) end
        if char.anims then _G.charSelect.character_add_animations(char.model, char.anims) end
        -- if char.meter then _G.charSelect.character_add_health_meter(char.model, char.meter) end
    end

    _G.charSelect.credit_add(TEXT_PACK_NAME, "FunkyLion", "Lead Dev")
    _G.charSelect.credit_add(TEXT_PACK_NAME, "Melzinoff", "Models / Animation")
    _G.charSelect.credit_add(TEXT_PACK_NAME, "Sharen", "Animation")
    _G.charSelect.credit_add(TEXT_PACK_NAME, "FluffaMario", "Models")
    _G.charSelect.credit_add(TEXT_PACK_NAME, 'Strawberii "Oreo"', "Icons")
    _G.charSelect.credit_add(TEXT_PACK_NAME, "Chars_64", "Icons")
    _G.charSelect.credit_add(TEXT_PACK_NAME, "WaterVapor", "Icons")
    _G.charSelect.credit_add(TEXT_PACK_NAME, "Squishy6094", "Code Rewrite")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_VOICE_ACTOR, "MelissaMekrose", "Toadette")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_VOICE_ACTOR, "SuperKirbyLover", "Peach")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_VOICE_ACTOR, "MorphiGalaxi", "Daisy")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_VOICE_ACTOR, "FunkyLion", "Yoshi")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_VOICE_ACTOR, "LuUvvUCY", "Birdo")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_VOICE_ACTOR, "VinnyVinesauce", "Spike")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_VOICE_ACTOR, "BeckyVO", "Pauline")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_VOICE_ACTOR, "GauntletQueen", "Rosalina")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_MOVESET, "xLuigiGamerx", "Toadette")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_MOVESET, "Wibblus", "Peach")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_MOVESET, "Wibblus", "Daisy")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_MOVESET, "xLuigiGamerx", "Yoshi")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_MOVESET, "EmilyEmmi", "Birdo")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_MOVESET, "Squishy6094", "Pauline")
    _G.charSelect.credit_add(TEXT_PACK_NAME..TEXT_MOVESET, "Wibblus", "Rosalina")

    CSloaded = true
end

local function on_character_sound(m, sound)
    if not CSloaded then return end
    for i = 1, #extraCharacters do
        if _G.charSelect.character_get_voice(m) == extraCharacters[i].voices then return _G.charSelect.voice.sound(m, sound) end
    end
end

--Used for the final Extra Character
--[[local function mario_update(m)
    if not CSloaded then return end
    if m.action == ACT_WALKING and _G.charSelect.character_get_current_number(m.playerIndex) == extraCharacters[10].tablePos then
        m.marioBodyState.torsoAngle.x = 0
        m.marioBodyState.torsoAngle.z = 0
        --results in double step sounds when going at the usual 32 speed (sigh)
        m.marioObj.header.gfx.animInfo.animAccel = m.marioObj.header.gfx.animInfo.animAccel * 0.85
    end
    for i = 1, #extraCharacters do
        if _G.charSelect.character_get_voice(m) == extraCharacters[i].voices then return _G.charSelect.voice.snore(m) end
    end
end
]]

hook_event(HOOK_ON_MODS_LOADED, on_character_select_load)
hook_event(HOOK_CHARACTER_SOUND, on_character_sound)
--hook_event(HOOK_MARIO_UPDATE, mario_update)