local shellTimeout = 30 * 30 --- 30 seconds

define_custom_obj_fields({
    oWeaponShellType = 'u32',
    oWeaponShellGlobalOwner = 'u32',
    oWeaponShellDeactivate = 'u32',
})

function bhv_weapon_shell_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oOpacity = 255
    obj.oVelY = 0
    obj.oTimer = 0
    if UNST22 then
        obj.oFlyGuyUnusedJitter = 0
    else
        obj.oWeaponShellDeactivate = 0
    end
    obj_scale(obj, 0.9)

    local hitbox = get_temp_object_hitbox()
    hitbox.interactType      = INTERACT_DAMAGE
    hitbox.downOffset        = 0
    hitbox.damageOrCoinValue = 4
    hitbox.health            = 1
    hitbox.numLootCoins      = 1
    hitbox.radius            = 100
    hitbox.height            = 70
    hitbox.hurtboxRadius     = 100
    hitbox.hurtboxHeight     = 70
    obj_set_hitbox(obj, hitbox)

    cur_obj_play_sound_2(SOUND_GENERAL_BIG_POUND)

    if UNST22 then
        network_init_object(obj, false, { 'oFlyGuyUnusedJitter' })
    else
        network_init_object(obj, false, { 'oWeaponShellDeactivate' })
    end
end

function bhv_weapon_shell_destroy(obj)
    obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    spawn_triangles(obj)
    cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX)

    if UNST22 then
        if obj.oFlyGuyUnusedJitter == 0 then
            obj.oFlyGuyUnusedJitter = 1
            network_send_object(obj, true)
        end
        obj.oFlyGuyUnusedJitter = 1
    else
        if obj.oWeaponShellDeactivate == 0 then
            obj.oWeaponShellDeactivate = 1
            network_send_object(obj, true)
        end
        obj.oWeaponShellDeactivate = 1
    end
end

function bhv_weapon_shell_move(obj)
    local hit = false
    local stepHeight = 100
    local savedX = obj.oPosX
    local savedY = obj.oPosY
    local savedZ = obj.oPosZ

    -- figure out direction
    local v = {
        x = sins(obj.oMoveAngleYaw) * obj.oForwardVel,
        y = 0,
        z = coss(obj.oMoveAngleYaw) * obj.oForwardVel,
    }

    -- cast ray
    local info = collision_find_surface_on_ray(
        obj.oPosX, obj.oPosY + stepHeight, obj.oPosZ,
        v.x, v.y, v.z)

    -- move the shell
    obj.oPosX = info.hitPos.x
    obj.oPosY = info.hitPos.y
    obj.oPosZ = info.hitPos.z

    -- figure out how far from floor
    local floorHeight = find_floor_height(obj.oPosX, obj.oPosY, obj.oPosZ)

    if floorHeight <= -10000.0 then
        -- we're OOB
        obj.oPosX = savedX
        obj.oPosY = savedY
        obj.oPosZ = savedZ
        obj.oMoveAngleYaw = obj.oMoveAngleYaw + 0x4000
        obj.oFaceAngleYaw = obj.oMoveAngleYaw
        return true
    elseif math.abs(floorHeight - obj.oPosY) > stepHeight * 1.25 then
        -- we're in the air
        obj.oPosY = obj.oPosY - stepHeight
        obj.oVelY = obj.oVelY - 5
        obj.oPosY = obj.oPosY + obj.oVelY
        if obj.oPosY < floorHeight then
            obj.oPosY = floorHeight
        end
    else
        -- we're on the ground
        obj.oPosY = floorHeight
        obj.oVelY = 0
    end

    -- figure out if we hit wall
    if info.surface ~= nil and math.abs(info.surface.normal.y) < 0.2 then
        -- projection
        local parallel = vec3f_project(v, info.surface.normal)
        local perpendicular = { x = v.x - parallel.x, y = v.y - parallel.y, z = v.z - parallel.z }

        -- reflect velocity along normal
        local reflect = {
            x = perpendicular.x - parallel.x,
            y = perpendicular.y - parallel.y,
            z = perpendicular.z - parallel.z
        }

        obj.oPosX = savedX
        obj.oPosY = savedY
        obj.oPosZ = savedZ
        obj.oMoveAngleYaw = atan2s(reflect.z, reflect.x)
        obj.oFaceAngleYaw = obj.oMoveAngleYaw
        hit = true
        spawn_mist(obj)
        cur_obj_play_sound_2(SOUND_GENERAL_BOX_LANDING)
    end

    -- orient to floor
    info = collision_find_surface_on_ray(
        obj.oPosX, obj.oPosY + stepHeight, obj.oPosZ,
        0, stepHeight * -1.5, 0)
    if info.surface ~= nil then
        obj_orient_graph(obj, info.surface.normal.x, info.surface.normal.y, info.surface.normal.z)
    end

    -- attach to water
    local waterLevel = find_water_level(obj.oPosX, obj.oPosZ)
    if obj.oPosY < waterLevel then obj.oPosY = waterLevel end

    return hit
end

function bhv_weapon_shell_red_loop(obj, hit)
    if hit then
        bhv_weapon_shell_destroy(obj)
        return
    end

    -- find target
    local target = nil
    local targetDist = 1000
    local v = {
        x = sins(obj.oMoveAngleYaw) * obj.oForwardVel,
        y = 0,
        z = coss(obj.oMoveAngleYaw) * obj.oForwardVel,
    }
    for i = 0, (MAX_PLAYERS - 1) do
        local m = gMarioStates[i]
        local np = gNetworkPlayers[i]
        local isntGlobalOwner = (np.globalIndex ~= obj.oWeaponShellGlobalOwner)
        if UNST22 then isntGlobalOwner = (np.globalIndex ~= obj.oFlyGuyOscTimer) end

        if active_player(m) and isntGlobalOwner then
            local dist = dist_between_objects(m.marioObj, obj)
            local diff = { x = m.marioObj.oPosX - obj.oPosX, y = 0, z = m.marioObj.oPosZ - obj.oPosZ }
            local angleBetween = vec3f_angle_between(diff, v)
            if dist < targetDist and angleBetween < 100 then
                target = m
                targetDist = dist
            end
        end
    end

    -- no target found :(
    if target == nil then
        return
    end

    -- turn toward target
    local turnSpeed = 0x300
    local targetYaw = atan2s(target.pos.z - obj.oPosZ, target.pos.x - obj.oPosX)
    obj.oMoveAngleYaw = targetYaw - approach_s32(convert_s16(targetYaw - obj.oMoveAngleYaw), 0, turnSpeed, turnSpeed)
    obj.oFaceAngleYaw = obj.oMoveAngleYaw
end

function bhv_weapon_shell_loop(obj)
    local hit = bhv_weapon_shell_move(obj)
    if UNST22 then
        if obj.oFlyGuyIdleTimer == 1 then
            bhv_weapon_shell_red_loop(obj, hit)
        end
        if obj.oFlyGuyUnusedJitter ~= 0 then
            bhv_weapon_shell_destroy(obj)
            return
        end
    else
        if obj.oWeaponShellType == 1 then
            bhv_weapon_shell_red_loop(obj, hit)
        end
        if obj.oWeaponShellDeactivate ~= 0 then
            bhv_weapon_shell_destroy(obj)
            return
        end
    end

    -- prevent interactions for the first 5 frames
    if obj.oTimer < 5 then
        obj.oInteractStatus = 0
    end

    if cur_obj_check_interacted() ~= 0 then
        bhv_weapon_shell_destroy(obj)
        return
    end

    if obj.oTimer > shellTimeout then
        bhv_weapon_shell_destroy(obj)
        return
    end
end

id_bhvWeaponShell = hook_behavior(nil, OBJ_LIST_PUSHABLE, true, bhv_weapon_shell_init, bhv_weapon_shell_loop)
E_MODEL_RED_SHELL = smlua_model_util_get_id("red_shell_geo")
