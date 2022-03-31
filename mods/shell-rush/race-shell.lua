
function bhv_race_shell_set_hitbox(obj)
    local hitbox = get_temp_object_hitbox()
    hitbox.interactType      = INTERACT_KOOPA_SHELL
    hitbox.downOffset        = 0
    hitbox.damageOrCoinValue = 4
    hitbox.health            = 1
    hitbox.numLootCoins      = 1
    hitbox.radius            = 50
    hitbox.height            = 50
    hitbox.hurtboxRadius     = 50
    hitbox.hurtboxHeight     = 50
    obj_set_hitbox(obj, hitbox)
end

function bhv_race_shell_water_drop(obj)
    spawn_non_sync_object(id_bhvObjectWaveTrail, E_MODEL_WAVE_TRAIL, obj.oPosX, obj.oPosY, obj.oPosZ, nil)
    if gMarioStates[0].forwardVel > 10.0 then
        local drop = spawn_non_sync_object(id_bhvWaterDroplet, E_MODEL_WHITE_PARTICLE_SMALL, obj.oPosX, obj.oPosY, obj.oPosZ, nil)
        if drop ~= nil then
            obj_scale(drop, 1.5)
            drop.oVelY = math.random() * 30.0
            obj_translate_xz_random(drop, 110.0)
        end
    end
end

function bhv_race_shell_flame_spawn(obj)
    for i = 0, 1 do
        spawn_non_sync_object(id_bhvKoopaShellFlame, E_MODEL_RED_FLAME, obj.oPosX, obj.oPosY, obj.oPosZ, nil)
    end
end

function bhv_race_shell_spawn_sparkles(obj, offset)
    spawn_non_sync_object(id_bhvSparkleSpawn, E_MODEL_NONE, obj.oPosX, obj.oPosY + offset, obj.oPosZ, nil)
end

function bhv_race_shell_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE

    -- set_obj_physics
    obj.oWallHitboxRadius = 30
    obj.oGravity = -400 / 100.0
    obj.oBounciness = -50 / 100.0
    obj.oDragStrength = 1000 / 100.0
    obj.oFriction = 1000 / 100.0
    obj.oBuoyancy = 200 / 100.0
end

function bhv_race_shell_loop(obj)
    local np = gNetworkPlayers[obj.heldByPlayerIndex]
    local m = gMarioStates[obj.heldByPlayerIndex]
    local player = m.marioObj

    local riding = is_riding(m)

    if active_player(m) and riding then
        cur_obj_unhide()
    else
        cur_obj_hide()
        return
    end

    --bhv_race_shell_set_hitbox(obj)
    cur_obj_scale(1.0)

    obj_copy_pos(obj, player)
    obj.oFaceAngleYaw = player.oFaceAngleYaw

    local surface = cur_obj_update_floor_height_and_get_floor()
    local waterLevel = find_water_level(obj.oPosX, obj.oPosZ)

    if math.abs(waterLevel - obj.oPosY) < 10.0 then
        bhv_race_shell_water_drop(obj)

    elseif 5.0 > math.abs(obj.oPosY - obj.oFloorHeight) then
        if surface ~= nil and surface.type == 1 then
            bhv_race_shell_flame_spawn(obj)
        elseif m.forwardVel > 70 then
            bhv_race_shell_spawn_sparkles(obj, 10.0)
        end
    elseif m.forwardVel > 70 then
        bhv_race_shell_spawn_sparkles(obj, 10.0)
    end

    obj.oFaceAngleYaw = player.oMoveAngleYaw

end

id_bhvRaceShell = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_race_shell_init, bhv_race_shell_loop)
