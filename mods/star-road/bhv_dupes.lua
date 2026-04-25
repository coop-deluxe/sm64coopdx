local E_MODEL_VCUTM_LIGHT = smlua_model_util_get_id("vcutm_light_geo")
local COL_WF_SMALL_BOMP = smlua_collision_util_get("wf_seg7_collision_small_bomp")

-- we use this instead of o->oHiddenStarLastInteractedObject
local oHiddenStarLastInteractedPlayer = nil

--- @param o Object
function bhv_custom_hidden_star_trigger_init(o)
    network_init_object(o, true, { "activeFlags", "oInteractStatus" })
end

--- @param o Object
function bhv_custom_hidden_star_trigger_loop(o)
    if (o.oInteractStatus & INT_STATUS_INTERACTED) ~= 0 or obj_check_if_collided_with_object(o, gMarioStates[0].marioObj) ~= 0 then
        local hiddenStar = obj_get_nearest_object_with_behavior_id(o, bhvSMSRHiddenStar)
        if hiddenStar ~= nil then
            local count = obj_count_objects_with_behavior_id(bhvSMSRHiddenStarTrigger) - 1
            hiddenStar.oHiddenStarTriggerCounter = 5 - count

            if hiddenStar.oHiddenStarTriggerCounter ~= 5 then
                spawn_orange_number(hiddenStar.oHiddenStarTriggerCounter, 0, 0, 0)
            end

            -- set the last person who interacted with a secret to the parent so only they get the star cutscene
            player = nearest_mario_state_to_object(o)
            if player ~= nil then
                oHiddenStarLastInteractedPlayer = player
            end

            cur_obj_play_sound_2(SOUND_MENU_COLLECT_SECRET + ((hiddenStar.oHiddenStarTriggerCounter - 1) << 16))
        end

        o.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end
end

--------------

--- @param o Object
function bhv_custom_hidden_star_init(o)
    local count = obj_count_objects_with_behavior_id(bhvSMSRHiddenStarTrigger)
    if count == 0 then
        local star = spawn_object_abs_with_rot(o, 0, E_MODEL_STAR, id_bhvStar, o.oPosX, o.oPosY, o.oPosZ, 0, 0, 0)
        if star ~= nil then
            star.oBehParams = o.oBehParams
        end

        o.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end

    o.oHiddenStarTriggerCounter = 5 - count

    -- we haven't interacted with a player yet.
    -- We also don't sync this as not only is it not required
    -- but it also is only set for an interaction.
    -- Therefore this object must already be loaded for it to be set
    -- and if it wasn't. You couldn't of possibly been the one
    -- who last interacted to begin with
    --
    -- coding™
    oHiddenStarLastInteractedPlayer = nil

    network_init_object(o, false, { "oAction", "oHiddenStarTriggerCounter", "oPosX", "oPosY", "oPosZ", "oTimer" })
end

--- @param o Object
function bhv_custom_hidden_star_loop(o)
    switch(o.oAction, {
        [0] = function() -- for case 0
            if o.oHiddenStarTriggerCounter == 5 then
                o.oAction = 1
            end
        end,
        [1] = function() -- for case 1
            if o.oTimer > 2 then
                star = spawn_red_coin_cutscene_star(o.oPosX, o.oPosY, o.oPosZ)
                if not (star == nil) then
                    if oHiddenStarLastInteractedPlayer == gMarioStates[0] then
                        star.oStarSpawnExtCutsceneFlags = 1
                    else
                        star.oStarSpawnExtCutsceneFlags = 0
                    end
                    spawn_mist_particles()
                end
                o.activeFlags = ACTIVE_FLAG_DEACTIVATED
            end
        end,
    })
end

--------------

--- @param o Object
function bhv_breakable_rock_init(o)
    network_init_object(o, false, nil)
end

--------------

--- @param o Object
function bhv_breakable_window_init(o)
    o.collisionData = COL_WF_SMALL_BOMP
    network_init_object(o, false, { "oFlags", "oInteractStatus" })
end

--- @param o Object
function bhv_breakable_window_loop(o)
    if (o.oInteractStatus & INT_STATUS_INTERACTED) ~= 0 or (o.oInteractStatus & INT_STATUS_WAS_ATTACKED) ~= 0 then
        return
    end

    if check_local_mario_attacking(o) ~= 0 then
        obj_explode_and_spawn_coins(80, 0)
        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION)

        o.oInteractStatus = 0
    end
end

--------------

--- @param o Object
function bhv_star_replica_init(o)
    despawn_if_stars_below_count(o, 121) -- 121 star check
end

--------------

--- @param o Object
function bhv_red_sinking_platform_init(o)
    cur_obj_set_home_once()
    network_init_object(o, true, { "oSinkWhenSteppedOnUnk104", "oGraphYOffset", "oHomeY" })
end

--------------

--- @param o Object
function bhv_star_door_wall_loop(o)
    if get_star_count() >= 30 then
        o.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end
end

--------------

--- @param o Object
function bhv_special_breakable_box_init(o)
    despawn_if_stars_below_count(o, 121) -- 121 star check
    network_init_object(o, false, nil)
end

--------------

-- why even make an init function
function bhv_piranha_plant_wild_loop()
end

--------------

-- why even make an init function
function bhv_big_leaves_init()
end

--------------

--- @param o Object
function bhv_lily_pad_init(o)
    network_init_object(o, true, { "oSinkWhenSteppedOnUnk104", "oGraphYOffset", "oHomeY" })
end

--------------

--- @param o Object
function bhv_tambourine_init(o)
    network_init_object(o, false, nil)
end

--------------

--- @param o Object
function bhv_small_bee_init(o)
    network_init_object(o, false, nil)
end

--------------

--- @param o Object
function bhv_star_moving_init(o)
    network_init_object(o, false, nil)
end

--------------

--- @param o Object
function bhv_falling_domino_init(o)
    network_init_object(o, false, nil)
end

--------------

--- @param o Object
function bhv_lava_lift_init(o)
    network_init_object(o, false, nil)
end

--------------

--- @param o Object
function bhv_rotating_lava_platform_init(o)
    network_init_object(o, false, nil)
end

--------------

--- @param o Object
function bhv_sinking_donut_init(o)
    network_init_object(o, true, { "oSinkWhenSteppedOnUnk104", "oGraphYOffset", "oHomeY" })
end

--- @param o Object
function bhv_sinking_donut_loop(o)
    sinking_perform_sink_check(o)
    sinking_perform_sink_check(o) -- called twice
end
--------------

--- @param o Object
function bhv_floating_thwomp_init(o)
    network_init_object(o, true, { "oHomeX", "oHomeY", "oHomeZ", "oAction", "oPosX", "oPosY", "oPosZ", "oVelX", "oVelY", "oVelZ" })
end

--------------

--- @param o Object
function bhv_toxic_waste_platform_init(o)
    network_init_object(o, true, { "oSinkWhenSteppedOnUnk104", "oGraphYOffset", "oHomeY" })
end

--- @param o Object
function bhv_toxic_waste_platform_loop(o)
    sinking_perform_sink_check(o)
end

--------------

--- @param o Object
function bhv_pushable_tomb_init(o)
    network_init_object(o, true, { "oPosX", "oPosY", "oPosZ" })
end

--------------

--- @param o Object
function bhv_lights_on_switch_init(o)
    o.parentObj = cur_obj_nearest_object_with_behavior(get_behavior_from_id(id_bhvFloorSwitchAnimatesObject))
    obj_set_model_extended(o, E_MODEL_VCUTM_LIGHT)

    network_init_object(o, true, { "oFloorSwitchPressAnimationUnkF4", "oFloorSwitchPressAnimationUnkF8", "oFloorSwitchPressAnimationUnkFC" })
end

--- @param o Object
function bhv_lights_on_switch_loop(o)
    if o.oFloorSwitchPressAnimationUnk100 ~= 0 then
        if o.parentObj ~= nil and o.parentObj.oAction ~= 2 then
            o.oFloorSwitchPressAnimationUnk100 = 0
        end

        if o.oFloorSwitchPressAnimationUnkFC ~= 0 then
            if o.oBehParams2ndByte >= 0 and o.oBehParams2ndByte <= 2 then
                o.oFloorSwitchPressAnimationUnkF4 = 200
            end
        else
            o.oFloorSwitchPressAnimationUnkF4 = 0
        end
    elseif o.parentObj ~= nil and o.parentObj.oAction == 2 then
        o.oFloorSwitchPressAnimationUnkFC = o.oFloorSwitchPressAnimationUnkFC ~ 1
        o.oFloorSwitchPressAnimationUnk100 = 1
    end

    if o.oFloorSwitchPressAnimationUnkF4 ~= 0 then
        if o.oFloorSwitchPressAnimationUnkF4 < 60 then
            cur_obj_play_sound_1(SOUND_GENERAL2_SWITCH_TICK_SLOW)
        else
            cur_obj_play_sound_1(SOUND_GENERAL2_SWITCH_TICK_FAST)
        end

        o.oFloorSwitchPressAnimationUnkF4 = o.oFloorSwitchPressAnimationUnkF4 - 1
        if o.oFloorSwitchPressAnimationUnkF4 == 0 then
            o.oFloorSwitchPressAnimationUnkFC = 0
        end

        if o.oFloorSwitchPressAnimationUnkF8 < 9 then
            o.oFloorSwitchPressAnimationUnkF8 = o.oFloorSwitchPressAnimationUnkF8 + 1
        end
    else
        o.oFloorSwitchPressAnimationUnkF8 = o.oFloorSwitchPressAnimationUnkF8 - 2
        if o.oFloorSwitchPressAnimationUnkF8 < 0 then
            o.oFloorSwitchPressAnimationUnkF8 = 0
            o.oFloorSwitchPressAnimationUnkFC = 1
        end
    end

    local fType = math.floor(o.oFloorSwitchPressAnimationUnkF8 / 2)
    if fType == 0 then
        cur_obj_hide()
    else
        cur_obj_unhide()
    end
end