-- name: Visible Lakitu
-- description: You can now see everyone's Lakitu camera like in the Mirror room.\n\nYou may use this code for your own mods.\n\nBy Isaac

-- localized versions of globally defined functions exposed to C (that are used often), for performance
local math_random, is_player_active, network_player_from_global_index, cur_obj_unhide, cur_obj_hide, cur_obj_angle_to_home, atan2s, cur_obj_lateral_dist_to_home, network_send_object =
      math.random, is_player_active, network_player_from_global_index, cur_obj_unhide, cur_obj_hide, cur_obj_angle_to_home, atan2s, cur_obj_lateral_dist_to_home, network_send_object

local l = gLakituState
local npl = gNetworkPlayers[0]

-- define our variables to hold the global id of each Lakitu's owner, and its blink timer
define_custom_obj_fields({ oLakituOwner = 'u32', oLakituBlinkTimer = 's32' })

-- for some reason Lua doesn't treat booleans as 1/0 numbers
local boolToNumber = { [true] = 1, [false] = 0 }

local function obj_update_blinking(o, timer, base, range, length)
    -- update our timer
    if timer > 0 then timer = timer - 1
    else timer = base + (range * math_random()) end

    -- set Lakitu's blink state depending on what our timer is at
    o.oAnimState = boolToNumber[(timer <= length)]
    return timer
end

local function is_current_area_sync_valid()
    -- check all connected players to see if their area sync is valid
    for i = 0, (MAX_PLAYERS - 1) do
        local np = gNetworkPlayers[i]
        if np ~= nil and np.connected and (not np.currLevelSyncValid or not np.currAreaSyncValid) then
            return false
        end
    end
    return true
end

local function active_player(m, np)
    -- check if this player is connected and in the same level
    if not np.connected or np.currCourseNum ~= gNetworkPlayers[0].currCourseNum or np.currActNum ~= gNetworkPlayers[0].currActNum or np.currLevelNum ~= gNetworkPlayers[0].currLevelNum or
        np.currAreaIndex ~= gNetworkPlayers[0].currAreaIndex then
        return false
    end
    return is_player_active(m)
end

local function obj_mark_for_deletion_on_sync(o)
    -- delete this Lakitu if the area's sync status is valid
    if gNetworkPlayers[0].currAreaSyncValid then obj_mark_for_deletion(o) end
end

local function bhv_custom_lakitu_init(o)
    -- set up Lakitu's flags
    o.oFlags = (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    -- use the default Lakitu animations
    o.oAnimations = gObjectAnimations.lakitu_seg6_anims_060058F8
    cur_obj_init_animation(0)

    -- spawn Lakitu's cloud if this isn't the local player's Lakitu
    if network_local_index_from_global(o.oLakituOwner) ~= 0 then
        spawn_non_sync_object(id_bhvCloud, E_MODEL_MIST, o.oPosX, o.oPosY, o.oPosZ,
            function(obj)
                -- make the cloud a child of Lakitu
                obj.parentObj = o
                -- sm64 knows this is a Lakitu cloud if oBehParams2ndByte is set to 1
                -- if oBehParams2ndByte is 0, the cloud will behave as a Fwoosh
                obj.oBehParams2ndByte = 1
                -- make the cloud twice the size size of a normal cloud (all Lakitu clouds do this)
                obj_scale(obj, 2)
            end)
    end

    -- init the networked Lakitu
    network_init_object(o, true, { "oLakituOwner", "oFaceAngleYaw", "oFaceAnglePitch" })
end

local function bhv_custom_lakitu(o)
    -- get the gNetworkPlayers table for the player that owns this Lakitu
    local np = network_player_from_global_index(o.oLakituOwner)
    -- this isn't a valid network player, delete this Lakitu
    if np == nil then
        obj_mark_for_deletion_on_sync(o)
        return
    end

    -- get the mario state of the player that owns this Lakitu
    local m = gMarioStates[np.localIndex]

    -- don't update this Lakitu if it isn't our Lakitu
    if m.playerIndex ~= 0 then
        -- delete this Lakitu if it's owner isn't active
        if not active_player(m, np) then
            obj_mark_for_deletion_on_sync(o)
            return
        end
        -- show the Lakitu for other players
        cur_obj_unhide()

        -- determine whether Lakitu should blink
        o.oLakituBlinkTimer = obj_update_blinking(o, o.oLakituBlinkTimer, 20, 40, 4)
        return
    else
        -- the local player cannot see it's own Lakitu
        cur_obj_hide()
    end

    -- set the Lakitu position to the camera position of that player
    o.oPosX = l.curPos.x
    o.oPosY = l.curPos.y
    o.oPosZ = l.curPos.z

    -- look at Mario
    o.oHomeX = l.curFocus.x
    o.oHomeZ = l.curFocus.z

    o.oFaceAngleYaw = cur_obj_angle_to_home()
    o.oFaceAnglePitch = atan2s(cur_obj_lateral_dist_to_home(), o.oPosY - l.curFocus.y)

    -- send the current state of our Lakitu to other players if the area sync is valild
    if is_current_area_sync_valid() then
        network_send_object(o, false)
    end
end

local bhvPlayerLakitu = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_custom_lakitu_init, bhv_custom_lakitu)

-- search for a Lakitu with our global index
local function search_for_lakitu(index)
    local o = obj_get_first_with_behavior_id(bhvPlayerLakitu)
    while o ~= nil do
        if o.oLakituOwner == index then
            return o
        end
        o = obj_get_next_with_same_behavior_id(o)
    end
    return nil
end

-- spawn the local player's Lakitu when the area's sync state is valid (every time the player warps areas)
local function update_lakitu()
    -- if a Lakitu that we own already exists, don't spawn a new one
    if search_for_lakitu(npl.globalIndex) then return end
    -- spawn Lakitu with our custom Lakitu behavior and the default Lakitu model; and mark it as a sync object
    spawn_sync_object(bhvPlayerLakitu, E_MODEL_LAKITU, 0, 0, 0, function(o)
        -- save the global id of the player that owns this Lakitu
        o.oLakituOwner = npl.globalIndex
    end)
end

hook_event(HOOK_ON_SYNC_VALID, update_lakitu)
