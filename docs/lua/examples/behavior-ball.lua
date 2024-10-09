-- name: Ball
-- description: Press DPAD down to spawn a ball

function bhv_ball_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oGraphYOffset = 35
    cur_obj_scale(1.0)

    -- physics
    obj.oWallHitboxRadius = 40.00
    obj.oGravity          =  2.50
    obj.oBounciness       = -0.75
    obj.oDragStrength     =  0.00
    obj.oFriction         =  0.99
    obj.oBuoyancy         =  -2.00

    -- hitbox
    obj.hitboxRadius = 100
    obj.hitboxHeight = 100

    network_init_object(obj, true, nil)
end

function bhv_ball_loop(obj)
    local m = nearest_mario_state_to_object(obj)
    local player = m.marioObj
    local distanceToPlayer = dist_between_objects(obj, player)
    local angleToPlayer = obj_angle_to_object(obj, player)
    local localPlayerTouch = false

    -- figure out player-to-ball radius
    local radius = 100
    if (m.action & ACT_FLAG_ATTACKING) ~= 0 then
        radius = 150
    end

    -- check if player should affect ball
    if distanceToPlayer < radius then
        local xdiff = player.oPosX - obj.oPosX
        local zdiff = player.oPosZ - obj.oPosZ

        obj.oPosX = obj.oPosX - (radius - distanceToPlayer) / radius * xdiff;
        obj.oPosZ = obj.oPosZ - (radius - distanceToPlayer) / radius * zdiff;

        obj.oMoveAngleYaw = angleToPlayer + 0x8000
        obj.oForwardVel = obj.oForwardVel + 10

        if (m.action & ACT_FLAG_ATTACKING) ~= 0 then
            obj.oVelY = obj.oVelY + 20.0
        end
        if m.playerIndex == 0 then
            localPlayerTouch = true
        end
    end

    -- do physics
    local stepRc = object_step_without_floor_orient()

    -- play sounds
    if stepRc == 1 then
        cur_obj_play_sound_2(SOUND_GENERAL_BOX_LANDING_2)
    elseif (stepRc & 1) ~= 0 then
        if obj.oForwardVel > 20.0 then
            cur_obj_play_sound_2(SOUND_ENV_SLIDING)
        end
    end

    -- check for floor death
    local floor = cur_obj_update_floor_height_and_get_floor()
    if floor ~= nil then
        obj_check_floor_death(stepRc, floor)
    end

    -- update visual rotation
    obj.oFaceAngleYaw = obj.oMoveAngleYaw
    obj.oFaceAnglePitch = obj.oFaceAnglePitch + obj.oForwardVel * 100

    -- if we touched it, send an immediate update instead of waiting
    if localPlayerTouch then
        network_send_object(obj, false)
    end
end

id_bhvBall = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_ball_init, bhv_ball_loop)

function mario_update_local(m)
    if (m.controller.buttonPressed & D_JPAD) ~= 0 then
        -- spawn ball
        spawn_sync_object(
            id_bhvBall,
            E_MODEL_SPINY_BALL,
            m.pos.x + 150, m.pos.y, m.pos.z,
            nil)
    end
end

function mario_update(m)
    if m.playerIndex == 0 then
        mario_update_local(m)
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)