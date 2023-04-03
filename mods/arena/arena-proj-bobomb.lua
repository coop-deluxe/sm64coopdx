define_custom_obj_fields({
    oArenaBobombGlobalOwner = 'u32',
})

function bhv_arena_bobomb_init(obj)
    obj.oAction = 0
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj_scale(obj, 0.75)
    cur_obj_play_sound_2(SOUND_AIR_BOBOMB_LIT_FUSE)
    obj.oVelX = sins(obj.oMoveAngleYaw) * obj.oForwardVel
    obj.oVelY = 30
    obj.oVelZ = coss(obj.oMoveAngleYaw) * obj.oForwardVel
    obj.oAnimations = gObjectAnimations.bobomb_seg8_anims_0802396C
    cur_obj_init_animation(1)
    network_init_object(obj, false, nil)
end

function bhv_arena_bobomb_intersects_player(obj, m, pos, radius)
    local ownerNp = network_player_from_global_index(obj.oArenaBobombGlobalOwner)
    local cm = m
    if m.playerIndex == 0 then
        cm = lag_compensation_get_local_state(ownerNp)
    end

    local mPos1 = { x = cm.pos.x, y = cm.pos.y + 50,  z = cm.pos.z }
    local mPos2 = { x = cm.pos.x, y = cm.pos.y + 150, z = cm.pos.z }
    local ret = (vec3f_dist(pos, mPos1) < radius or vec3f_dist(pos, mPos2) < radius)

    return ret
end

function bhv_arena_bobomb_expode(obj)
    obj.oAction = 1
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj_set_billboard(obj)
    obj_scale(obj, 2)
    obj.oAnimState = -1
    cur_obj_play_sound_2(SOUND_GENERAL2_BOBOMB_EXPLOSION)
    set_environmental_camera_shake(SHAKE_ENV_EXPLOSION)
    obj.oOpacity = 255
    obj_set_model_extended(obj, E_MODEL_EXPLOSION)

    local m = gMarioStates[0]
    local np = gNetworkPlayers[0]
    local e = gMarioStateExtras[0]
    local a = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ }
    local validAttack = global_index_hurts_mario_state(obj.oArenaBobombGlobalOwner, m) or np.globalIndex == obj.oArenaBobombGlobalOwner
    local radius = 650
    if np.globalIndex == obj.oArenaBobombGlobalOwner then radius = 200 end
    if validAttack and bhv_arena_bobomb_intersects_player(obj, m, a, radius) and mario_health_float(m) > 0 then
        obj.oDamageOrCoinValue = 3
        interact_damage(m, INTERACT_DAMAGE, obj)
        e.lastDamagedByGlobal = obj.oArenaBobombGlobalOwner
    end
end

function bhv_arena_bobomb_thrown_loop(obj)
    local a   = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ }
    local dir = { x = obj.oVelX, y = obj.oVelY, z = obj.oVelZ }
    obj.oVelY = obj.oVelY - 3
    obj.oFaceAnglePitch = obj.oFaceAnglePitch - 0x100

    for i = 0, MAX_PLAYERS - 1 do
        local m = gMarioStates[i]
        if active_player(m) and global_index_hurts_mario_state(obj.oArenaBobombGlobalOwner, m) and not is_invuln_or_intang(m) then
            if bhv_arena_bobomb_intersects_player(obj, m, a, 200) then
                bhv_arena_bobomb_expode(obj)
                return
            end
        end
    end

    local info = collision_find_surface_on_ray(
            a.x, a.y, a.z,
            dir.x, dir.y, dir.z)

    local floorHeight = find_floor_height(obj.oPosX, obj.oPosY + 100, obj.oPosZ)
            
    if obj.oTimer > 30 * 1 or info.surface ~= nil or obj.oPosY < floorHeight then
        bhv_arena_bobomb_expode(obj)
        return
    else
        obj.oPosX = obj.oPosX + dir.x
        obj.oPosY = obj.oPosY + dir.y
        obj.oPosZ = obj.oPosZ + dir.z
    end
end

function bhv_arena_bobomb_explode_loop(obj)
    if obj.oTimer >= 9 then
        obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end

    obj.oOpacity = obj.oOpacity - 14
    cur_obj_scale((obj.oTimer / 9.0 + 1.0) * 2)
    obj.oAnimState = obj.oAnimState + 1
end

function bhv_arena_bobomb_loop(obj)
    if obj.oAction == 0 then
        bhv_arena_bobomb_thrown_loop(obj)
    else
        bhv_arena_bobomb_explode_loop(obj)
    end
end

id_bhvArenaBobomb = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_arena_bobomb_init, bhv_arena_bobomb_loop)
