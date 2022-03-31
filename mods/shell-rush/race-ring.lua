
define_custom_obj_fields({
    oWaypointIndex = 'u32',
})

function bhv_race_ring_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj_scale(obj, 4)
    obj_set_billboard(obj)
    obj.oOpacity = 200
end

function bhv_race_ring_inactive(obj)
    obj_scale(obj, 1)
    obj.oOpacity = 64

    local waypoint = get_waypoint(obj.oWaypointIndex)
    obj_set_vec3f(obj, waypoint)

    local cur = gPlayerSyncTable[0].waypoint
    local nex = get_waypoint_index(cur + 1)

    if cur == obj.oWaypointIndex then
        obj.oAction = 1
        cur_obj_unhide()
    elseif nex == obj.oWaypointIndex then
        cur_obj_unhide()
    else
        cur_obj_hide()
    end
end

function bhv_race_ring_active(obj)
    local player = gMarioStates[0].marioObj
    local distanceToPlayer = dist_between_objects(obj, player)

    cur_obj_unhide()
    obj_scale(obj, 4)
    obj.oOpacity = 200

    local waypoint = get_waypoint(obj.oWaypointIndex)
    obj_set_vec3f(obj, waypoint)

    if distanceToPlayer < 573 then
        obj.oAction = 2

        local s = gPlayerSyncTable[0]
        if s.waypoint == obj.oWaypointIndex then
            if s.waypoint == 1 then
                race_increment_lap()
            end
            s.waypoint = get_waypoint_index(obj.oWaypointIndex + 1)
        end
        cur_obj_play_sound_2(SOUND_GENERAL_COIN)
    end
end

function bhv_race_ring_shrinking(obj)
    local scalar = 1 - (obj.oTimer / (30 * 3))
    scalar = scalar * scalar
    scalar = scalar * scalar
    scalar = scalar * scalar

    cur_obj_unhide()
    obj_scale(obj, 4 * scalar)
    obj.oOpacity = 200 * scalar

    local waypoint = get_waypoint(obj.oWaypointIndex)
    local nextWaypoint = get_waypoint(obj.oWaypointIndex + 1)
    local wpos = vec3f_tween(nextWaypoint, waypoint, scalar)
    obj_set_vec3f(obj, wpos)

    spawn_non_sync_object(id_bhvTriangleParticleSpawner, E_MODEL_NONE,
        obj.oPosX + 300 * (math.random() - 0.5) * scalar,
        obj.oPosY + 300 * (math.random() - 0.5) * scalar,
        obj.oPosZ + 300 * (math.random() - 0.5) * scalar,
        nil)

    if scalar <= 0.05 then
        obj.oAction = 0
    end
end

function bhv_race_ring_loop(obj)
    if obj.oAction == 0 then
        bhv_race_ring_inactive(obj)
    elseif obj.oAction == 1 then
        bhv_race_ring_active(obj)
    elseif obj.oAction == 2 then
        bhv_race_ring_shrinking(obj)
    end
end

id_bhvRaceRing = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_race_ring_init, bhv_race_ring_loop)
