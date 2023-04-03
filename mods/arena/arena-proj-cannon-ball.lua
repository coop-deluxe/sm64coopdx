define_custom_obj_fields({
    oArenaCannonBallGlobalOwner = 'u32',
    oArenaCannonBallSize = 'f32',
    oArenaCannonBallDamages = 'u32',
})

function bhv_arena_cannon_ball_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oArenaCannonBallDamages = 1
    obj_scale(obj, 1.5 * obj.oArenaCannonBallSize)
    obj_set_billboard(obj)
    cur_obj_play_sound_2(SOUND_OBJ_POUNDING_CANNON)
    spawn_mist(obj, 1)
    obj.oVelX = sins(obj.oMoveAngleYaw) * obj.oForwardVel
    obj.oVelY = 0
    obj.oVelZ = coss(obj.oMoveAngleYaw) * obj.oForwardVel
    network_init_object(obj, false, nil)
end

function bhv_arena_cannon_ball_intersects_local(obj, pos)
    local ownerNp = network_player_from_global_index(obj.oArenaBobombGlobalOwner)
    local cm = gMarioStates[0]
    if gMarioStates[0].playerIndex == 0 then
        cm = lag_compensation_get_local_state(ownerNp)
    end

    local mPos1 = { x = cm.pos.x, y = cm.pos.y + 50,  z = cm.pos.z }
    local mPos2 = { x = cm.pos.x, y = cm.pos.y + 150, z = cm.pos.z }
    local radius = clamp(obj.oArenaCannonBallSize * 250, 75, 250)
    local ret = (vec3f_dist(pos, mPos1) < radius or vec3f_dist(pos, mPos2) < radius)

    return ret
end

function bhv_arena_cannon_ball_loop(obj)
    local a   = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ }
    local dir = { x = obj.oVelX, y = obj.oVelY, z = obj.oVelZ }

    -- update pallet
    local np = gNetworkPlayers[obj.oArenaCannonBallGlobalOwner]
    if np ~= nil then
        obj.globalPlayerIndex = np.globalIndex
    end

    local m = gMarioStates[0]
    if global_index_hurts_mario_state(obj.oArenaCannonBallGlobalOwner, m) and not is_invuln_or_intang(m) then
        local b = { x = a.x + dir.x / 2, y = a.y + dir.y / 2, z = a.z + dir.z / 2 }
        if bhv_arena_cannon_ball_intersects_local(obj, a) or bhv_arena_cannon_ball_intersects_local(obj, b) then
            if obj.oArenaCannonBallDamages ~= 0 then
                obj.oDamageOrCoinValue = clamp(obj.oArenaCannonBallSize * 8, 1, 5)
                interact_damage(m, INTERACT_DAMAGE, obj)
                obj.oArenaCannonBallDamages = 0
            end
        end

        local e = gMarioStateExtras[0]
        e.lastDamagedByGlobal = obj.oArenaCannonBallGlobalOwner
    end

    info = collision_find_surface_on_ray(
            a.x, a.y, a.z,
            dir.x, dir.y, dir.z)

    if obj.oTimer > 30 * 6 or info.surface ~= nil then
        spawn_mist(obj, 1 + obj.oArenaCannonBallSize * 5)
        spawn_balls(obj, 1 + obj.oArenaCannonBallSize * 5)
        obj_mark_for_deletion(obj)
    else
        obj.oPosX = obj.oPosX + dir.x
        obj.oPosY = obj.oPosY + dir.y
        obj.oPosZ = obj.oPosZ + dir.z
    end

end

id_bhvArenaCannonBall = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_arena_cannon_ball_init, bhv_arena_cannon_ball_loop)
