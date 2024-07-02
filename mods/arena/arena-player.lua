------------
-- tables --
------------

gMarioStateExtras = {}
for i = 0, (MAX_PLAYERS - 1) do
    local np = gNetworkPlayers[i]

    gMarioStateExtras[i] = {}
    local e = gMarioStateExtras[i]
    e.rotAngle            = 0
    e.rotFrames           = 0
    e.lastDamagedByGlobal = np.globalIndex
    e.attackCooldown      = 0
    e.prevHurtCounter     = 0
    e.levelTimer          = 0
    e.levelTimerLevel     = 0
    e.springing           = 0

    local s = gPlayerSyncTable[i]
    s.item     = ITEM_NONE
    s.ammo     = 0
    s.kills    = 0
    s.deaths   = 0
    s.score    = 0
    s.team     = 0
    s.charging = 0
    s.metal    = false
    s.rank     = 0
end

local sKnockbackActions = {
    ACT_SOFT_FORWARD_GROUND_KB, ACT_FORWARD_GROUND_KB, ACT_HARD_FORWARD_GROUND_KB,
    ACT_FORWARD_AIR_KB, ACT_FORWARD_AIR_KB, ACT_HARD_FORWARD_AIR_KB,
    ACT_FORWARD_WATER_KB, ACT_FORWARD_WATER_KB, ACT_FORWARD_WATER_KB,
    ACT_SOFT_BACKWARD_GROUND_KB, ACT_BACKWARD_GROUND_KB, ACT_HARD_BACKWARD_GROUND_KB,
    ACT_BACKWARD_AIR_KB, ACT_BACKWARD_AIR_KB, ACT_HARD_BACKWARD_AIR_KB,
    ACT_BACKWARD_WATER_KB, ACT_BACKWARD_WATER_KB, ACT_BACKWARD_WATER_KB,

    ACT_LEDGE_GRAB, ACT_LEDGE_CLIMB_SLOW_1, ACT_LEDGE_CLIMB_SLOW_2, ACT_LEDGE_CLIMB_DOWN, ACT_LEDGE_CLIMB_FAST,
    ACT_GROUND_BONK, ACT_SOFT_BONK,

    ACT_STOP_CROUCHING, ACT_STOMACH_SLIDE_STOP,
}
------------
-- hammer --
------------

function mario_hammer_is_attack(action)
    if action == ACT_PUNCHING      then return true end
    if action == ACT_MOVE_PUNCHING then return true end
    if action == ACT_JUMP_KICK     then return true end
    if action == ACT_DIVE          then return true end
    if action == ACT_GROUND_POUND  then return true end
    return false
end

function mario_hammer_position(m)
    local held = gItemHeld[m.playerIndex]
    if held == nil then
        return { x = m.pos.x, y = m.pos.y, z = m.pos.z }
    end

    local origin = { x = held.oPosX, y = held.oPosY, z = held.oPosZ }
    return set_dist_and_angle(origin, 100, 0x4000 + -held.oFaceAnglePitch, held.oFaceAngleYaw)
end

function mario_hammer_pound(m)
    local v = {
        x = m.pos.x + sins(m.faceAngle.y) * 200,
        y = m.pos.y,
        z = m.pos.z + coss(m.faceAngle.y) * 200,
    }
    spawn_horizontal_stars(v.x, v.y, v.z)
    play_mario_heavy_landing_sound(m, SOUND_ACTION_TERRAIN_HEAVY_LANDING)
    cur_obj_shake_screen(SHAKE_POS_MEDIUM)
end

function mario_hammer_on_set_action(m)
    if m.action == ACT_PUNCHING or m.action == ACT_MOVE_PUNCHING or m.action == ACT_JUMP_KICK then
        play_sound(SOUND_ACTION_TWIRL, m.marioObj.header.gfx.cameraToObject)
    elseif m.action == ACT_DIVE_SLIDE or m.action == ACT_GROUND_POUND_LAND then
        mario_hammer_pound(m)
    end
end

function mario_hammer_update(m)
    local e = gMarioStateExtras[m.playerIndex]
    local s = gPlayerSyncTable[m.playerIndex]

    -- override dive animation
    if m.action == ACT_DIVE then
        set_mario_animation(m, MARIO_ANIM_FORWARD_SPINNING)

        e.rotFrames = e.rotFrames + 1
        if (e.rotFrames) % 7 == 0 then
            play_sound(SOUND_ACTION_TWIRL, m.marioObj.header.gfx.cameraToObject)
        end

        e.rotAngle = e.rotAngle + (0x80 * 60)
        if e.rotAngle > 0x10000 then
            e.rotAngle = e.rotAngle - 0x10000
        end
        set_anim_to_frame(m, 10 * e.rotAngle / 0x10000)
    elseif m.action == ACT_PUNCHING or m.action == ACT_MOVE_PUNCHING then
        local animFrame = m.marioObj.header.gfx.animInfo.animFrame
        if animFrame == -1 and m.actionArg > 1 then
            mario_hammer_pound(m)
        end
        if m.actionArg > 2 then m.actionArg = 0 end
    end
end

function mario_local_hammer_check(m)
    local np = gNetworkPlayers[m.playerIndex]
    local e = gMarioStateExtras[m.playerIndex]
    local savedKb = m.knockbackTimer
    m.knockbackTimer = 0

    -- check for hammer attacks
    for i = 1, (MAX_PLAYERS - 1) do
        local mattacker  = gMarioStates[i]
        local npattacker = gNetworkPlayers[i]
        local sattacker  = gPlayerSyncTable[i]
        local cmvictim = lag_compensation_get_local_state(npattacker)

        if sattacker.item == ITEM_HAMMER and mario_hammer_is_attack(mattacker.action) and passes_pvp_interaction_checks(mattacker, cmvictim) ~= 0 and passes_pvp_interaction_checks(mattacker, m) ~= 0 and global_index_hurts_mario_state(npattacker.globalIndex, m) then
            local pos = mario_hammer_position(mattacker)
            local dist = vec3f_dist(pos, cmvictim.pos)
            if dist <= 200 then
                local yOffset = 0.6
                if mattacker.action == ACT_JUMP_KICK then
                    yOffset = 1.0
                end

                local vel = {
                    x = sins(mattacker.faceAngle.y),
                    y = yOffset,
                    z = coss(mattacker.faceAngle.y),
                }
                vec3f_normalize(vel)
                vec3f_mul(vel, 80 + 10 * (1 - mario_health_float(cmvictim)))

                set_mario_action(m, ACT_BACKWARD_AIR_KB, 0)
                m.invincTimer = 20
                m.knockbackTimer = 10
                m.vel.x = vel.x
                m.vel.y = vel.y
                m.vel.z = vel.z
                m.faceAngle.y = atan2s(vel.z, vel.x) + 0x8000
                m.forwardVel = 0
                sattacker.ammo = sattacker.ammo - 1

                send_arena_hammer_hit(np.globalIndex, npattacker.globalIndex)
                e.lastDamagedByGlobal = npattacker.globalIndex

                if mattacker.action == ACT_JUMP_KICK or mattacker.action == ACT_DIVE then
                    m.hurtCounter = 10
                else
                    m.hurtCounter = 15
                end
            end
        end
    end

    if savedKb > m.knockbackTimer then
        m.knockbackTimer = savedKb
    end
end

-----------------
-- fire flower --
-----------------

function mario_fire_flower_use(m)
    local np = gNetworkPlayers[m.playerIndex]
    local e = gMarioStateExtras[m.playerIndex]
    local s = gPlayerSyncTable[m.playerIndex]

    spawn_sync_object(id_bhvArenaFlame, E_MODEL_RED_FLAME, m.pos.x, m.pos.y, m.pos.z,
        function (obj)
            obj.oArenaFlameGlobalOwner = np.globalIndex
            obj.oVelY = m.vel.y + 25
            obj.oMoveAngleYaw = m.faceAngle.y
            obj.oForwardVel = m.forwardVel + 70
        end)

    if (m.action & ACT_FLAG_INVULNERABLE) ~= 0 or (m.action & ACT_FLAG_INTANGIBLE) ~= 0 then
        -- nothing
    elseif (m.action == ACT_SHOT_FROM_CANNON) then
        -- nothing
    elseif (m.action & ACT_FLAG_SWIMMING) ~= 0 then
        set_mario_action(m, ACT_WATER_PUNCH, 0)
    elseif (m.action & ACT_FLAG_MOVING) ~= 0 then
        set_mario_action(m, ACT_MOVE_PUNCHING, 0)
    elseif (m.action & ACT_FLAG_AIR) ~= 0 then
        set_mario_action(m, ACT_DIVE, 0)
    elseif (m.action & ACT_FLAG_STATIONARY) ~= 0 then
        set_mario_action(m, ACT_PUNCHING, 0)
    end

    e.attackCooldown = 20
    s.ammo = s.ammo - 1
end

------------
-- bobomb --
------------

function mario_bobomb_use(m)
    local np = gNetworkPlayers[m.playerIndex]
    local e = gMarioStateExtras[m.playerIndex]
    local s = gPlayerSyncTable[m.playerIndex]

    spawn_sync_object(id_bhvArenaBobomb, E_MODEL_BLACK_BOBOMB, m.pos.x, m.pos.y + 50, m.pos.z,
        function (obj)
            obj.oArenaBobombGlobalOwner = np.globalIndex
            obj.oMoveAngleYaw = m.faceAngle.y
            obj.oForwardVel = m.forwardVel + 50
        end)

    if (m.action & ACT_FLAG_INVULNERABLE) ~= 0 or (m.action & ACT_FLAG_INTANGIBLE) ~= 0 then
        -- nothing
    elseif (m.action == ACT_SHOT_FROM_CANNON) then
        -- nothing
    elseif (m.action & ACT_FLAG_SWIMMING) ~= 0 then
        set_mario_action(m, ACT_WATER_PUNCH, 0)
    elseif (m.action & ACT_FLAG_MOVING) ~= 0 then
        set_mario_action(m, ACT_MOVE_PUNCHING, 0)
    elseif (m.action & ACT_FLAG_AIR) ~= 0 then
        set_mario_action(m, ACT_DIVE, 0)
    elseif (m.action & ACT_FLAG_STATIONARY) ~= 0 then
        set_mario_action(m, ACT_PUNCHING, 0)
    end

    e.attackCooldown = 20
    s.ammo = s.ammo - 1
end

----------------
-- cannon box --
----------------

function mario_cannon_box_update(m)
    local np = gNetworkPlayers[m.playerIndex]
    local e = gMarioStateExtras[m.playerIndex]
    local s = gPlayerSyncTable[m.playerIndex]

    if m.playerIndex == 0 and (m.controller.buttonPressed & Y_BUTTON) ~= 0 then
        s.charging = get_network_area_timer()
    end

    if (m.controller.buttonDown & Y_BUTTON) ~= 0 and s.charging > 0 then
        local cannonBallSize = clamp((get_network_area_timer() - s.charging) / (30 * 5) + 0.1, 0, 1)
        local held = gItemHeld[m.playerIndex]
        if held ~= nil then
            for i = 0, 2 do
                spawn_non_sync_object(id_bhvArenaSparkle, E_MODEL_SPARKLES_ANIMATION,
                    held.oPosX, held.oPosY, held.oPosZ,
                    function (obj)
                        obj.oArenaSparkleOwner = m.playerIndex
                        obj.oArenaSparkleSize = cannonBallSize
                    end)
            end
        end
    elseif m.playerIndex == 0 and s.charging > 0 then
        local cannonBallSize = clamp((get_network_area_timer() - s.charging) / (30 * 5) + 0.1, 0, 1)
        s.charging = 0
        spawn_sync_object(id_bhvArenaCannonBall, E_MODEL_CANNON_BALL, m.pos.x, m.pos.y + 150, m.pos.z,
            function (obj)
                obj.oArenaCannonBallGlobalOwner = np.globalIndex
                obj.oArenaCannonBallSize = cannonBallSize
                obj.oMoveAngleYaw = m.faceAngle.y
                obj.oForwardVel = m.forwardVel + 150
            end)
        s.ammo = s.ammo - 1
    end
end

-----------
-- hooks --
-----------

function allow_pvp_attack(attacker, victim)
    local npAttacker = gNetworkPlayers[attacker.playerIndex]
    local sAttacker = gPlayerSyncTable[attacker.playerIndex]

    -- hammer attacks are custom
    if sAttacker.item == ITEM_HAMMER and mario_hammer_is_attack(attacker.action) then
        return false
    end

    -- check teams
    return global_index_hurts_mario_state(npAttacker.globalIndex, victim)
end

function on_pvp_attack(attacker, victim)
    if victim.playerIndex == 0 then
        local e = gMarioStateExtras[victim.playerIndex]
        local npAttacker = gNetworkPlayers[attacker.playerIndex]
        e.lastDamagedByGlobal = npAttacker.globalIndex
    end
end

function on_interact(interactor, interactee, interactType, interactValue)
    if interactor.playerIndex ~= 0 then return end
    local bhvId = get_id_from_behavior(interactee.behavior)
    if bhvId ~= id_bhvArenaFlame and bhvId ~= id_bhvArenaChildFlame then return end

    local e = gMarioStateExtras[interactor.playerIndex]
    e.lastDamagedByGlobal = interactee.oArenaFlameGlobalOwner
end

function on_set_mario_action(m)
    local e = gMarioStateExtras[m.playerIndex]
    local s = gPlayerSyncTable[m.playerIndex]
    if m.action == ACT_DIVE then
        e.rotAngle = 0
        e.rotFrames = 0
    end

    if m.playerIndex == 0 and is_player_active(m) ~= 0 then
        if (m.action & ACT_FLAG_AIR) == 0 then
            if e.springing == 1 then
                e.springing = 0
            end
        end
    end

    if s.item == ITEM_HAMMER then
        mario_hammer_on_set_action(m)
    end

end

function mario_local_update(m)
    local np = gNetworkPlayers[m.playerIndex]
    local s = gPlayerSyncTable[m.playerIndex]
    local e = gMarioStateExtras[m.playerIndex]

    -- decrease cooldown
    if e.attackCooldown > 0 then
        e.attackCooldown = e.attackCooldown - 1
    end

    -- use the hammer
    mario_local_hammer_check(m)

    -- use the fire flower
    if e.attackCooldown <= 0 and s.item == ITEM_FIRE_FLOWER and (m.controller.buttonPressed & Y_BUTTON) ~= 0 then
        mario_fire_flower_use(m)
    end

    -- use the bobomb
    if e.attackCooldown <= 0 and s.item == ITEM_BOBOMB and (m.controller.buttonPressed & Y_BUTTON) ~= 0 then
        mario_bobomb_use(m)
    end

    -- break out of shot from cannon
    if (m.action == ACT_SHOT_FROM_CANNON) then
        if (m.input & INPUT_B_PRESSED) ~= 0 then
            return set_mario_action(m, ACT_DIVE, 0)
        elseif (m.input & INPUT_Z_PRESSED) ~= 0 then
            return set_mario_action(m, ACT_GROUND_POUND, 0)
        end
    end

    -- set metal
    s.metal = (m.capTimer > 0)

    -- increase damage when holding flag
    if is_holding_flag(m) then
        if m.hurtCounter > e.prevHurtCounter then
            m.hurtCounter = m.hurtCounter * 2
        end
    end

    -- reduce damage when metal
    if s.metal then
        if m.hurtCounter > e.prevHurtCounter then
            m.hurtCounter = m.hurtCounter / 2
        end
    end

    -- discard current item
    if s.item ~= ITEM_NONE and (s.ammo <= 0 or (m.controller.buttonPressed & L_TRIG) ~= 0) then
        s.item = ITEM_NONE
        if gItemHeld[m.playerIndex] ~= nil then
            spawn_triangles(gItemHeld[m.playerIndex])
        end
        play_sound(SOUND_GENERAL_BREAK_BOX, m.marioObj.header.gfx.cameraToObject)
    end

    -- prevent water heal
    if m.health >= 0x100 then
        if m.healCounter == 0 and m.hurtCounter == 0 then
            if ((m.action & ACT_FLAG_SWIMMING ~= 0) and (m.action & ACT_FLAG_INTANGIBLE == 0)) then
                if ((m.pos.y >= (m.waterLevel - 140)) and not (m.area.terrainType & TERRAIN_SNOW ~= 0)) then
                    m.health = m.health - 0x1A
                end
            end
        end
    end

    e.prevHurtCounter = m.hurtCounter
end

function mario_update(m)
    local e  = gMarioStateExtras[m.playerIndex]
    local s  = gPlayerSyncTable[m.playerIndex]
    local np = gNetworkPlayers[m.playerIndex]
    if not np.connected then return end

    -- increase knockback animations
    local animInfo = nil
    if m.marioObj ~= nil then
        animInfo = m.marioObj.header.gfx.animInfo
    end
    for i, value in ipairs(sKnockbackActions) do
        if m.action == value then
            local frame = animInfo.animFrame
            local loopEnd = frame
            if animInfo.curAnim ~= nil then
                loopEnd = animInfo.curAnim.loopEnd
            end

            if frame < loopEnd - 2 then
                frame = frame + 1
            end

            animInfo.animFrame = frame
        end
    end

    -- clear invincibilities
    m.invincTimer = 0
    if m.knockbackTimer > 5 then
        m.knockbackTimer = 5
    end

    -- update the local player
    if m.playerIndex == 0 then
        mario_local_update(m)
    end

    -- update palette
    if s.team == 1 then
        network_player_set_override_palette_color(np, PANTS, { r = 225, g = 5, b = 49 })
        network_player_set_override_palette_color(np, SHIRT, { r = 40, g = 10, b = 10 })
        network_player_set_override_palette_color(np, GLOVES, network_player_get_palette_color(np, GLOVES))
        network_player_set_override_palette_color(np, SHOES, network_player_get_palette_color(np, SHOES))
        network_player_set_override_palette_color(np, HAIR, network_player_get_palette_color(np, HAIR))
        network_player_set_override_palette_color(np, SKIN, network_player_get_palette_color(np, SKIN))
        network_player_set_override_palette_color(np, CAP, { r = 40, g = 10, b = 10 })
        network_player_set_override_palette_color(np, EMBLEM, network_player_get_palette_color(np, EMBLEM))
    elseif s.team == 2 then
        network_player_set_override_palette_color(np, PANTS, { r = 63, g = 63, b = 255 })
        network_player_set_override_palette_color(np, SHIRT, { r = 10, g = 10, b = 40 })
        network_player_set_override_palette_color(np, GLOVES, network_player_get_palette_color(np, GLOVES))
        network_player_set_override_palette_color(np, SHOES, network_player_get_palette_color(np, SHOES))
        network_player_set_override_palette_color(np, HAIR, network_player_get_palette_color(np, HAIR))
        network_player_set_override_palette_color(np, SKIN, network_player_get_palette_color(np, SKIN))
        network_player_set_override_palette_color(np, CAP, { r = 10, g = 10, b = 40 })
        network_player_set_override_palette_color(np, EMBLEM, network_player_get_palette_color(np, EMBLEM))
    else
        network_player_reset_override_palette(np)
    end

    -- set metal
    if s.metal then
        m.marioBodyState.modelState = MODEL_STATE_METAL
    end

    -- allow yaw change on springing
    if e.springing == 1 then
        m.faceAngle.y = m.intendedYaw - approach_s32(convert_s16(m.intendedYaw - m.faceAngle.y), 0, 0x400, 0x400)
    end

    -- update player items
    if s.item == ITEM_HAMMER then
        mario_hammer_update(m)
    elseif s.item == ITEM_CANNON_BOX then
        mario_cannon_box_update(m)
    end

    -- update level timer
    if e.levelTimerLevel ~= np.currLevelNum then
        e.levelTimer = 0
        e.levelTimerLevel = np.currLevelNum
    else
        e.levelTimer = e.levelTimer + 1
    end
end

function player_reset_sync_table(m)
    local s  = gPlayerSyncTable[m.playerIndex]
    s.item     = ITEM_NONE
    s.ammo     = 0
    s.kills    = 0
    s.deaths   = 0
    s.score    = 0
    s.charging = 0
    s.metal    = false
    s.rank     = 0
    s.team     = pick_team_on_join(m)
end

function player_respawn(m)
    local np = gNetworkPlayers[m.playerIndex]
    local e  = gMarioStateExtras[m.playerIndex]
    local s  = gPlayerSyncTable[m.playerIndex]

    -- reset most variables
    init_single_mario(m)

    -- spawn location/angle
    spawn = find_spawn_point()
    if spawn ~= nil then
        m.pos.x = spawn.pos.x
        m.pos.y = spawn.pos.y
        m.pos.z = spawn.pos.z
        m.faceAngle.y = spawn.yaw
    else
        m.pos.x = 0
        m.pos.y = 0
        m.pos.z = 0
    end

    -- reset the rest of the variables
    m.capTimer = 0
    m.health = 0x880
    soft_reset_camera(m.area.camera)
    s.ammo = 0
    s.item = ITEM_NONE
    e.lastDamagedByGlobal = np.globalIndex
    stop_cap_music()
end

function on_death(m)
    if m.playerIndex ~= 0 then return end
    local np = gNetworkPlayers[m.playerIndex]
    local e = gMarioStateExtras[m.playerIndex]
    local s = gPlayerSyncTable[m.playerIndex]

    -- inform of death
    send_arena_death(np.globalIndex, e.lastDamagedByGlobal)

    -- respawn
    player_respawn(m)
    return false
end

function on_player_connected(m)
    local np = gNetworkPlayers[m.playerIndex]
    local e = gMarioStateExtras[m.playerIndex]
    local s = gPlayerSyncTable[m.playerIndex]
    if network_is_server() then
        player_reset_sync_table(m)
    end
    if m.playerIndex == 0 then
        e.lastDamagedByGlobal = np.globalIndex
    end
end

function on_player_disconnected(m)
    local s = gPlayerSyncTable[m.playerIndex]
    if network_is_server() then
        player_reset_sync_table(m)
    end
end

function before_phys_step(m)
    local hScale = 1.0

    if is_holding_flag(m) and m.action ~= ACT_SHOT_FROM_CANNON then
        hScale = 0.9
    end

    m.vel.x = m.vel.x * hScale
    m.vel.z = m.vel.z * hScale
end

hook_event(HOOK_ALLOW_PVP_ATTACK, allow_pvp_attack)
hook_event(HOOK_ON_PVP_ATTACK, on_pvp_attack)
hook_event(HOOK_ON_INTERACT, on_interact)
hook_event(HOOK_ON_SET_MARIO_ACTION, on_set_mario_action)
hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ON_DEATH, on_death)
hook_event(HOOK_ON_PLAYER_CONNECTED, on_player_connected)
hook_event(HOOK_ON_PLAYER_DISCONNECTED, on_player_disconnected)
hook_event(HOOK_BEFORE_PHYS_STEP, before_phys_step)
