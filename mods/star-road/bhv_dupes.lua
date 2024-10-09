-- We use this instead of o->oHiddenStarLastInteractedObject.
oHiddenStarLastInteractedPlayer = nil

function bhv_custom_hidden_star_trigger_init(obj)
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

--------------

function bhv_custom_hidden_star_init(obj)
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

--------------

function bhv_breakable_rock_init(obj)
    network_init_object(obj, false, nil)
end

--------------

function bhv_breakable_window_init(obj)
    obj.collisionData = smlua_collision_util_get("wf_seg7_collision_small_bomp")
    network_init_object(obj, false, { 'oFlags', 'oInteractStatus' });
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

--------------

function bhv_star_replica_init(obj)
    despawn_if_stars_below_count(obj, 121) -- 121 star check
end

--------------

function bhv_red_sinking_platform_init(obj)
    cur_obj_set_home_once()
    network_init_object(obj, true, { 'oSinkWhenSteppedOnUnk104', 'oGraphYOffset', 'oHomeY' })
end

--------------

function bhv_star_door_wall_loop(obj)
    if get_star_count() >= 30 then
        obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end
end

--------------

function bhv_special_breakable_box_init(obj)
    despawn_if_stars_below_count(obj, 121) -- 121 star check
    network_init_object(obj, false, nil);
end

--------------

function bhv_piranha_plant_wild_loop(obj)
end

--------------

function bhv_big_leaves_init(obj)
end

--------------

function bhv_lily_pad_init(obj)
    network_init_object(obj, true, { 'oSinkWhenSteppedOnUnk104', 'oGraphYOffset', 'oHomeY' })
end

--------------

function bhv_tambourine_init(obj)
    network_init_object(obj, false, nil);
end

--------------

function bhv_small_bee_init(obj)
    network_init_object(obj, false, nil);
end

--------------

function bhv_star_moving_init(obj)
    network_init_object(obj, false, nil);
end

--------------

function bhv_falling_domino_init(obj)
    network_init_object(obj, false, nil);
end

--------------

function bhv_lava_lift_init(obj)
    network_init_object(obj, false, nil);
end

--------------

function bhv_rotating_lava_platform_init(obj)
    network_init_object(obj, false, nil);
end

--------------

function bhv_sinking_donut_init(obj)
    network_init_object(obj, true, { 'oSinkWhenSteppedOnUnk104', 'oGraphYOffset', 'oHomeY' })
end

function bhv_sinking_donut_loop(obj)
    sinking_perform_sink_check(obj)
    sinking_perform_sink_check(obj) -- called twice
end
--------------

function bhv_floating_thwomp_init(obj)
    network_init_object(obj, true, { 'oHomeX', 'oHomeY', 'oHomeZ', 'oAction', 'oPosX', 'oPosY', 'oPosZ', 'oVelX', 'oVelY', 'oVelZ' })
end

--------------

function bhv_toxic_waste_platform_init(obj)
    network_init_object(obj, true, { 'oSinkWhenSteppedOnUnk104', 'oGraphYOffset', 'oHomeY' })
end

function bhv_toxic_waste_platform_loop(obj)
    sinking_perform_sink_check(obj)
end

--------------

function bhv_pushable_tomb_init(obj)
    network_init_object(obj, true, { 'oPosX', 'oPosY', 'oPosZ' })
end

--------------

E_MODEL_VCUTM_LIGHT = smlua_model_util_get_id("vcutm_light_geo")

function bhv_lights_on_switch_init(obj)
    obj.parentObj = cur_obj_nearest_object_with_behavior(get_behavior_from_id(id_bhvFloorSwitchAnimatesObject));
    obj_set_model_extended(obj, E_MODEL_VCUTM_LIGHT)
    
    network_init_object(obj, true, { 'oFloorSwitchPressAnimationUnkF4', 'oFloorSwitchPressAnimationUnkF8', 'oFloorSwitchPressAnimationUnkFC' })
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