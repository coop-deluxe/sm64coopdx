-- We use this instead of o->oHiddenStarLastInteractedObject.
oHiddenStarLastInteractedPlayer = nil

function bhv_custom_hidden_star_trigger_init(obj)
    --obj.oFlags = (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    --obj.hitboxRadius = 200
    --obj.hitboxHeight = 200
    --obj.oIntangibleTimer = 0

    network_init_object(obj, true, { 'activeFlags', 'oInteractStatus' })
end

function bhv_custom_hidden_star_trigger_loop(obj)
    if not ((obj.oInteractStatus & INT_STATUS_INTERACTED) == 0) or obj_check_if_collided_with_object(obj, gMarioStates[0].marioObj) == 1 then
        local hiddenStar = obj_get_nearest_object_with_behavior_id(obj, bhvSMSRHiddenStar)
        if not (hiddenStar == nil) then
            local count = (obj_count_objects_with_behavior_id(bhvSMSRHiddenStarTrigger) - 1)
            hiddenStar.oHiddenStarTriggerCounter = 5 - count

            if not (hiddenStar.oHiddenStarTriggerCounter == 5) then
                spawn_orange_number(hiddenStar.oHiddenStarTriggerCounter, 0, 0, 0)
            end

            -- Set the last person who interacted with a secret to the 
            -- parent so only they get the star cutscene.
            player = nearest_mario_state_to_object(obj)
            if not (player == nil) then
                oHiddenStarLastInteractedPlayer = player
            end

            cur_obj_play_sound_2(SOUND_MENU_COLLECT_SECRET + ((hiddenStar.oHiddenStarTriggerCounter - 1) << 16))
        end

        obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end
end

--bhvSMSRHiddenStarTrigger = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_custom_hidden_star_trigger_init, bhv_custom_hidden_star_trigger_loop)

--------------

function bhv_custom_hidden_star_init(obj)
    --obj.oFlags = (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    local count = obj_count_objects_with_behavior_id(bhvSMSRHiddenStarTrigger)
    if count == 0 then
        local star = spawn_object_abs_with_rot(obj, 0, E_MODEL_STAR, id_bhvStar, obj.oPosX, obj.oPosY, obj.oPosZ, 0, 0, 0)
        if not (star == nil) then
            star.oBehParams = obj.oBehParams
        end

        obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end

    obj.oHiddenStarTriggerCounter = 5 - count

    -- We haven't interacted with a player yet.
    -- We also don't sync this as not only is it not required
    -- but it also is only set for an interaction.
    -- Therefore this object must already be loaded for it to be set
    -- and if it wasn't. You couldn't of possibly been the one
    -- who last interacted to begin with.
    oHiddenStarLastInteractedPlayer = nil

    network_init_object(obj, false, { 'oAction', 'oHiddenStarTriggerCounter', 'oPosX', 'oPosY', 'oPosZ', 'oTimer' })
end

function bhv_custom_hidden_star_loop(obj)
    switch(obj.oAction, {
        [0] = function()    -- for case 0
            if obj.oHiddenStarTriggerCounter == 5 then
                obj.oAction = 1
            end
        end,
        [1] = function()    -- for case 1
            if obj.oTimer > 2 then
                star = spawn_red_coin_cutscene_star(obj.oPosX, obj.oPosY, obj.oPosZ)
                if not (star == nil) then
                    if oHiddenStarLastInteractedPlayer == gMarioStates[0] then
                        star.oStarSpawnExtCutsceneFlags = 1
                    else
                        star.oStarSpawnExtCutsceneFlags = 0
                    end
                    spawn_mist_particles()
                end
                obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
            end
        end,
    })
end

--bhvSMSRHiddenStar = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_custom_hidden_star_init, bhv_custom_hidden_star_loop)

--------------

function bhv_breakable_rock_init(obj)
    --obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    --obj.collisionData = smlua_collision_util_get("col_hmc_geo_000530_0x7020308")
    --obj.oCollisionDistance = 500
    --bhv_init_room()

    network_init_object(obj, false, nil)
end

--[[
function bhv_breakable_rock_loop(obj)
    bhv_breakable_box_loop()
    load_object_collision_model()
end

bhvSMSRBreakableRock = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_breakable_rock_init, bhv_breakable_rock_loop)
--]]

--------------

function bhv_breakable_window_init(obj)
    obj.oFlags = (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("wf_seg7_collision_small_bomp")
    obj.oIntangibleTimer = 0
    obj.hitboxRadius = 200
    obj.hitboxHeight = 200
    --obj.oMoveAngleYaw = obj.oMoveAngleYaw - 0x4000
    network_init_object(obj, false, { 'oInteractStatus' });
end

function bhv_breakable_window_loop(obj)
    if not (obj.oInteractStatus & INT_STATUS_INTERACTED) or not (obj.oInteractStatus & INT_STATUS_WAS_ATTACKED) then
        return
    end

    if not (check_local_mario_attacking(obj) == 0) then
        obj_explode_and_spawn_coins(80, 0)
        create_sound_spawner(obj, SOUND_GENERAL_WALL_EXPLOSION)

        obj.oInteractStatus = 0;
    end
end

---bhvSMSRBreakableWindow = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_breakable_window_init, bhv_breakable_window_loop)

--------------

function bhv_star_replica_init(obj)
    --obj.oFlags = (OBJ_FLAG_HOLDABLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    --bhv_init_room()
    --bhv_collect_star_init()
    despawn_if_stars_below_count(obj, 121) -- 121 star check
end

--[[
function bhv_star_replica_loop(obj)
    bhv_collect_star_loop()
end
--]]

--bhvSMSRStarReplica = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_star_replica_init, bhv_star_replica_loop)

--------------

function bhv_red_sinking_platform_init(obj)
    --obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    --obj.collisionData = smlua_collision_util_get("col_rr_geo_0008C0_0x701ae78")
    --obj.oPosY = obj.oPosY - 306
    cur_obj_set_home_once()
    network_init_object(obj, true, { 'oSinkWhenSteppedOnUnk104', 'oGraphYOffset', 'oHomeY' })
end

--[[
function bhv_red_sinking_platform_loop(obj)
    sinking_perform_sink_check(obj)
    sinking_perform_sink_check(obj) -- called twice
    load_object_collision_model()
end

bhvSMSRRedSinkingPlatform = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_red_sinking_platform_init, bhv_red_sinking_platform_loop)
--]]

--------------

--[[
function bhv_star_door_wall_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.collisionData = smlua_collision_util_get("custom_collision_door_30_stars")
    obj.oCollisionDistance = 4000
end
--]]

function bhv_star_door_wall_loop(obj)
    if get_star_count() >= 30 then
        obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end

    --load_object_collision_model()
end

--bhvSMSR30StarDoorWall = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_star_door_wall_init, bhv_star_door_wall_loop)

--------------

function bhv_special_breakable_box_init(obj)
    --obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    --obj.collisionData = smlua_collision_util_get("breakable_box_seg8_collision_08012D70")
    --obj.oCollisionDistance = 500
    --bhv_init_room()
    despawn_if_stars_below_count(obj, 121) -- 121 star check
end

--[[
function bhv_special_breakable_box_loop(obj)
    bhv_breakable_box_loop()
    load_object_collision_model()
end

bhvSMSRSpecialBreakeableBox = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_special_breakable_box_init, bhv_special_breakable_box_loop)
--]]

--------------

--[[
function bhv_piranha_plant_wild_init(obj)
    obj.oFlags = (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.oAnimations = gObjectAnimations.piranha_plant_seg6_anims_0601C31C
    cur_obj_init_animation(0)
    obj.oInteractType = INTERACT_MR_BLIZZARD
    obj.hitboxRadius = 400
    obj.hitboxHeight = 400
end
--]]

function bhv_piranha_plant_wild_loop(obj)
end

--bhvSMSRPiranhaPlantWild = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_piranha_plant_wild_init, bhv_piranha_plant_wild_loop)

--------------

function bhv_big_leaves_init(obj)
    obj.header.gfx.node.flags = obj.header.gfx.node.flags | GRAPH_RENDER_CYLBOARD
end

--------------

function bhv_lily_pad_init(obj)
    network_init_object(obj, true, { 'oSinkWhenSteppedOnUnk104', 'oGraphYOffset', 'oHomeY' })
end

--------------

function bhv_tambourine_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.collisionData = smlua_collision_util_get("col_ddd_geo_0004A0_0x700cbf0")
end

function bhv_tambourine_loop(obj)
    bhv_ttc_spinner_update()
    load_object_collision_model()
end

bhvSMSRTambourine = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_tambourine_init, bhv_tambourine_loop)

--------------

function bhv_small_bee_init(obj)
    obj.oFlags = (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.header.gfx.node.flags = obj.header.gfx.node.flags | GRAPH_RENDER_BILLBOARD
    cur_obj_set_home_once()
    bhv_init_room()
    cur_obj_scale(150 / 100.0)
end

function bhv_small_bee_loop(obj)
    bhv_fly_guy_update()
    bhv_fly_guy_update() -- called twice
    obj.oAnimState = obj.oAnimState + 1
end

bhvSMSRSmallBee = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_small_bee_init, bhv_small_bee_loop)

--------------

function bhv_drum_stick_init(obj)
    obj.oFlags = (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("col_ddd_geo_000478_0x7000540")
    bhv_ssl_moving_pyramid_wall_init()
end

function bhv_drum_stick_loop(obj)
    bhv_ssl_moving_pyramid_wall_loop()
    load_object_collision_model()
end

bhvSMSRDrumStick = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_drum_stick_init, bhv_drum_stick_loop)

--------------

function bhv_star_moving_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    bhv_init_room()
    bhv_collect_star_init()
end

function bhv_star_moving_loop(obj)
    bhv_collect_star_loop()
    bhv_ssl_moving_pyramid_wall_loop()
end

bhvSMSRStarMoving = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_star_moving_init, bhv_star_moving_loop)

--------------

function bhv_falling_domino_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.collisionData = smlua_collision_util_get("col_ttm_geo_000DF4_0x702b870")
    cur_obj_set_home_once()
end

function bhv_falling_domino_loop(obj)
    bhv_volcano_trap_loop()
    load_object_collision_model()
end

bhvSMSRFallingDomino = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_falling_domino_init, bhv_falling_domino_loop)

--------------

function bhv_lava_lift_init(obj)
    obj.oFlags = (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.oPosY = obj.oPosY + -50
    obj.collisionData = smlua_collision_util_get("col_ttm_geo_000920_0x700a710")
end

function bhv_lava_lift_loop(obj)
    bhv_lll_moving_octagonal_mesh_platform_loop()
    load_object_collision_model()
end

bhvSMSRLavaLift = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_lava_lift_init, bhv_lava_lift_loop)

--------------

function bhv_rotating_lava_platform_init(obj)
    obj.oFlags = (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("col_lll_geo_000A78_0x701d68c")
    cur_obj_set_home_once()
end

function bhv_rotating_lava_platform_loop(obj)
    obj.oAngleVelYaw = 256
    obj.oMoveAngleYaw = obj.oMoveAngleYaw + 256
    load_object_collision_model()
end

bhvSMSRRotatingLavaPlatform = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_rotating_lava_platform_init, bhv_rotating_lava_platform_loop)

--------------

function bhv_small_swing_platform_init(obj)
    obj.collisionData = smlua_collision_util_get("rr_seg7_collision_pendulum")
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oCollisionDistance = 2000
    cur_obj_scale(160 / 100.0)
    bhv_swing_platform_init()
end

function bhv_small_swing_platform_loop(obj)
    bhv_swing_platform_update()
    load_object_collision_model()
end

bhvSMSRSmallSwingPlatform = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_small_swing_platform_init, bhv_small_swing_platform_loop)

--------------

function bhv_sinking_donut_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.collisionData = smlua_collision_util_get("col_rr_geo_000920_0x70295ec")
    obj.oPosY = obj.oPosY - 306
    cur_obj_set_home_once()

    network_init_object(obj, true, { 'oSinkWhenSteppedOnUnk104', 'oGraphYOffset', 'oHomeY' })
end

function bhv_sinking_donut_loop(obj)
    sinking_perform_sink_check(obj)
    sinking_perform_sink_check(obj) -- called twice
    load_object_collision_model()
end

bhvSMSRSinkingDonut = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_sinking_donut_init, bhv_sinking_donut_loop)

--------------

function bhv_floating_thwomp_init(obj)
    obj.collisionData = smlua_collision_util_get("thwomp_seg5_collision_0500B7D0")
    obj.oFlags = (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.oGraphYOffset = 5
    bhv_butterfly_init()
end

function bhv_floating_thwomp_loop(obj)
    bhv_butterfly_loop()
    load_object_collision_model()
end

bhvSMSRFloatingThwomp = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_floating_thwomp_init, bhv_floating_thwomp_loop)

--------------

function bhv_tilting_pyramid_init(obj)
    obj.oFlags = (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("col_geo_bbh_0005F8_0x701fba8")
    cur_obj_set_home_once()
    bhv_platform_normals_init()
end

function bhv_tilting_pyramid_loop(obj)
    bhv_tilting_inverted_pyramid_loop()
    load_object_collision_model()
end

bhvSMSRTiltingPyramid = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_tilting_pyramid_init, bhv_tilting_pyramid_loop)

--------------

function bhv_platform_lift_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.collisionData = smlua_collision_util_get("col_geo_bbh_0005C8_0x701f700")
    obj.oArrowLiftUnk100 = 1
end

function bhv_platform_lift_loop(obj)
    bhv_arrow_lift_loop()
    load_object_collision_model()
end

bhvSMSRPlatformLift = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_platform_lift_init, bhv_platform_lift_loop)

--------------

function bhv_rising_lava_init(obj)
    obj.oFlags = (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("col_geo_bbh_0005B0_0x701f2d8")
    bhv_ssl_moving_pyramid_wall_init()
end

function bhv_rising_lava_loop(obj)
    bhv_ssl_moving_pyramid_wall_loop()
    load_object_collision_model()
end

bhvSMSRRisingLava = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_rising_lava_init, bhv_rising_lava_loop)

--------------

function bhv_rising_tall_platform_init(obj)
    obj.oFlags = (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("col_geo_bbh_000628_0x70200f0")
    bhv_ssl_moving_pyramid_wall_init()
end

function bhv_rising_tall_platform_loop(obj)
    bhv_ssl_moving_pyramid_wall_loop()
    load_object_collision_model()
end

bhvSMSRRisingTallPlatform = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_rising_tall_platform_init, bhv_rising_tall_platform_loop)

--------------

function bhv_sinking_platform_init(obj)
    obj.oFlags = (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("col_geo_bbh_000640_0x600d758")
    obj.oPosY = obj.oPosY + 5
    obj.oCollisionDistance = 2000
end

function bhv_sinking_platform_loop(obj)
    bhv_lll_sinking_square_platforms_loop()
    bhv_lll_sinking_square_platforms_loop() -- called twice
    load_object_collision_model()
end

bhvSMSRSinkingPlatform = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_sinking_platform_init, bhv_sinking_platform_loop)

--------------

function bhv_toxic_waste_platform_init(obj)
    obj.oFlags = (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("col_hmc_geo_000548_0x7023478")
    obj.oPosY = obj.oPosY - 50
    cur_obj_set_home_once()

    network_init_object(obj, true, { 'oSinkWhenSteppedOnUnk104', 'oGraphYOffset', 'oHomeY' })
end

function bhv_toxic_waste_platform_loop(obj)
    sinking_perform_sink_check(obj)
    load_object_collision_model()
end

bhvSMSRToxicWastePlatform = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_toxic_waste_platform_init, bhv_toxic_waste_platform_loop)

--------------

function bhv_attracted_space_box_init(obj)
    obj.oFlags = (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("ssl_seg7_collision_tox_box")
    obj.oPosY = obj.oPosY + 256
    cur_obj_set_home_once()
end

function bhv_attracted_space_box_loop(obj)
    bhv_chuckya_loop()
    bhv_spindrift_loop()
    cur_obj_scale(64 / 100.0)
    load_object_collision_model()
end

bhvSMSRAttractedSpaceBox = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_attracted_space_box_init, bhv_attracted_space_box_loop)

--------------

function bhv_space_box_init(obj)
    obj.oFlags = (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("ssl_seg7_collision_tox_box")
    obj.oPosY = obj.oPosY + 256
end

function bhv_space_box_loop(obj)
    bhv_spindrift_loop()
    cur_obj_scale(64 / 100.0)
    load_object_collision_model()
end

bhvSMSRSpaceBox = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_space_box_init, bhv_space_box_loop)

--------------

function bhv_space_octagon_platform_init(obj)
    obj.collisionData = smlua_collision_util_get("ssl_seg7_collision_spindel")
    obj.oFlags = (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    cur_obj_set_home_once()
    bhv_ttc_moving_bar_init()
end

function bhv_space_octagon_platform_loop(obj)
    bhv_ttc_moving_bar_update()
    load_object_collision_model()
end

bhvSMSRSpaceOctagonPlatform = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_space_octagon_platform_init, bhv_space_octagon_platform_loop)

--------------

function bhv_space_red_platform_init(obj)
    obj.collisionData = smlua_collision_util_get("ssl_seg7_collision_grindel")
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    cur_obj_set_home_once()
    cur_obj_scale(91 / 100.0)
    bhv_horizontal_grindel_init()
end

function bhv_space_red_platform_loop(obj)
    bhv_squishable_platform_loop()
    bhv_squishable_platform_loop() -- called twice
    load_object_collision_model()
end

bhvSMSRSpaceRedPlatform = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_space_red_platform_init, bhv_space_red_platform_loop)

--------------

function bhv_bullet_mine_init(obj)
    obj.oFlags = (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    cur_obj_set_home_once()
    obj.hitboxRadius = 50
    obj.hitboxHeight = 50
    obj.hitboxDownOffset = 50
    obj.oInteractType = INTERACT_DAMAGE
    obj.oDamageOrCoinValue = 3
    cur_obj_scale(256 / 100.0)
    obj.oIntangibleTimer = 0
    bhv_bullet_bill_init()
end

function bhv_bullet_mine_loop(obj)
    bhv_bullet_bill_loop()
end

bhvSMSRBulletMine = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_bullet_mine_init, bhv_bullet_mine_loop)

--------------

E_MODEL_VCUTM_LIGHT = smlua_model_util_get_id("vcutm_light_geo")

function bhv_lights_on_switch_init(obj)
    --obj.oFlags = (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    --obj.oCollisionDistance = 8000
    obj.parentObj = cur_obj_nearest_object_with_behavior(get_behavior_from_id(id_bhvFloorSwitchAnimatesObject));
    obj_set_model_extended(obj, E_MODEL_VCUTM_LIGHT)
end

function bhv_lights_on_switch_loop(obj)
    if obj.oFloorSwitchPressAnimationUnk100 ~= 0 then
        if obj.parentObj ~= nil and obj.parentObj.oAction ~= 2 then
            obj.oFloorSwitchPressAnimationUnk100 = 0
        end

        if obj.oFloorSwitchPressAnimationUnkFC ~= 0 then
            if obj.oBehParams2ndByte >= 0 and obj.oBehParams2ndByte <= 2 then
                obj.oFloorSwitchPressAnimationUnkF4 = 200
            end
        else
            obj.oFloorSwitchPressAnimationUnkF4 = 0
        end
    elseif obj.parentObj ~= nil and obj.parentObj.oAction == 2 then
        obj.oFloorSwitchPressAnimationUnkFC = obj.oFloorSwitchPressAnimationUnkFC ~ 1
        obj.oFloorSwitchPressAnimationUnk100 = 1
    end

    if obj.oFloorSwitchPressAnimationUnkF4 ~= 0 then
        if obj.oFloorSwitchPressAnimationUnkF4 < 60 then
            cur_obj_play_sound_1(SOUND_GENERAL2_SWITCH_TICK_SLOW)
        else
            cur_obj_play_sound_1(SOUND_GENERAL2_SWITCH_TICK_FAST)
        end

        obj.oFloorSwitchPressAnimationUnkF4 = obj.oFloorSwitchPressAnimationUnkF4 - 1
        if obj.oFloorSwitchPressAnimationUnkF4 == 0 then
            obj.oFloorSwitchPressAnimationUnkFC = 0
        end

        if obj.oFloorSwitchPressAnimationUnkF8 < 9 then
            obj.oFloorSwitchPressAnimationUnkF8 = obj.oFloorSwitchPressAnimationUnkF8 + 1
        end
    else
        obj.oFloorSwitchPressAnimationUnkF8 = obj.oFloorSwitchPressAnimationUnkF8 - 2
        if obj.oFloorSwitchPressAnimationUnkF8 < 0 then
            obj.oFloorSwitchPressAnimationUnkF8 = 0
            obj.oFloorSwitchPressAnimationUnkFC = 1
        end
    end

    local fType = math.floor(obj.oFloorSwitchPressAnimationUnkF8 / 2)
    if fType == 0 then
        cur_obj_hide()
    else
        cur_obj_unhide()
    end
end

--bhvSMSRLightsOnSwitch = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_lights_on_switch_init, bhv_lights_on_switch_loop)
