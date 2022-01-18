-- initialize actions
ACT_ROLL = (0x05B | ACT_FLAG_MOVING | ACT_FLAG_BUTT_OR_STOMACH_SLIDE)
ACT_ROLL_AIR = (0x0BA | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)

-- initialize extra fields
gMarioStateExtras = {}
for i=0,(MAX_PLAYERS-1) do
    gMarioStateExtras[i] = {}
    gMarioStateExtras[i].spareFloat = 0
    gMarioStateExtras[i].spareInt = 0
end

---------------------------------------------------------

function sins(theta)
    return math.sin(theta * math.pi / (2 * 16384))
end

function coss(theta)
    return math.cos(theta * math.pi / (2 * 16384))
end

---------------------------------------------------------

function increase_roll_yaw(m)
    local newFacingDYaw = m.faceAngle.y - m.slideYaw

    if newFacingDYaw > 0 and newFacingDYaw <= 0x4000 then
        newFacingDYaw = newFacingDYaw - 0x200
        if newFacingDYaw < 0 then
            newFacingDYaw = 0
        end
    elseif newFacingDYaw > -0x4000 and newFacingDYaw < 0 then
        newFacingDYaw = newFacingDYaw + 0x200
        if newFacingDYaw > 0 then
            newFacingDYaw = 0
        end
    elseif newFacingDYaw > 0x4000 and newFacingDYaw < 0x8000 then
        newFacingDYaw = newFacingDYaw + 0x200
        if newFacingDYaw > 0x8000 then
            newFacingDYaw = 0x8000
        end
    elseif newFacingDYaw > -0x8000 and newFacingDYaw < -0x4000 then
        newFacingDYaw = newFacingDYaw - 0x200
        if newFacingDYaw < -0x8000 then
            newFacingDYaw = -0x8000
        end
    end

    if newFacingDYaw < -0x4000 or newFacingDYaw > 0x4000 then
        m.faceAngle.y = m.faceAngle.y + 0x4000
    end
end

function update_roll_sliding(m, stopSpeed)
    local stopped = 0

    local intendedDYaw = m.intendedYaw - m.slideYaw
    local forward = coss(intendedDYaw)
    local sideward = sins(intendedDYaw)

    --! 10k glitch
    if forward < 0.0 and m.forwardVel >= 0.0 then
        forward = forward * (0.5 + 0.5 * m.forwardVel / 100.0)
    end

    local accel = 4.0
    local lossFactor = 0.994

    local oldSpeed = math.sqrt(m.slideVelX * m.slideVelX + m.slideVelZ * m.slideVelZ)

    --! This is uses trig derivatives to rotate Mario's speed.
    -- In vanilla, it was slightly off/asymmetric since it uses the new X speed, but the old
    -- Z speed. I've gone and fixed it here.
    local angleChange  = (m.intendedMag / 32.0) --* 0.6
    local modSlideVelX = m.slideVelZ * angleChange * sideward * 0.05
    local modSlideVelZ = m.slideVelX * angleChange * sideward * 0.05

    m.slideVelX = m.slideVelX + modSlideVelX
    m.slideVelZ = m.slideVelZ - modSlideVelZ

    local newSpeed = math.sqrt(m.slideVelX * m.slideVelX + m.slideVelZ * m.slideVelZ)

    if oldSpeed > 0.0 and newSpeed > 0.0 then
        m.slideVelX = m.slideVelX * oldSpeed / newSpeed
        m.slideVelZ = m.slideVelZ * oldSpeed / newSpeed
    end

    update_sliding_angle(m, accel, lossFactor)
    increase_roll_yaw(m)

    if m.playerIndex == 0 and mario_floor_is_slope(m) == 0 and m.forwardVel * m.forwardVel < stopSpeed * stopSpeed then
        mario_set_forward_vel(m, 0.0)
        stopped = 1
    end

    return stopped
end

---------------------------------------------------------

function act_roll(m)
    local e = gMarioStateExtras[m.playerIndex]

    local MAX_NORMAL_ROLL_SPEED = 50.0
    local ROLL_BOOST_GAIN = 10.0
    local ROLL_CANCEL_LOCKOUT_TIME = 10
    local BOOST_LOCKOUT_TIME = 20

    -- e.spareFloat  is used for Mario's rotation angle during the roll (persists when going into ACT_ROLL_AIR and back)
    -- e.spareInt    is used for the boost lockout timer (persists when going into ACT_ROLL_AIR and back)
    -- m.actionTimer is used to lockout walk canceling out of rollout (reset each action switch)

    if m.actionTimer == 0 then
        if m.prevAction ~= ACT_ROLL_AIR then
            e.spareFloat = 0
            e.spareInt   = 0
        end
    elseif m.actionTimer >= ROLL_CANCEL_LOCKOUT_TIME or m.actionArg == 1 then
        if (m.input & INPUT_Z_DOWN) == 0 then
            return set_mario_action(m, ACT_WALKING, 0);
        end
    end

    if (m.input & INPUT_B_PRESSED) ~= 0 then
        return set_jumping_action(m, ACT_FORWARD_ROLLOUT, 0);
    end

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        return set_jumping_action(m, ACT_LONG_JUMP, 0);
    end

    if (m.controller.buttonPressed & R_TRIG) ~= 0 and m.actionTimer > 0 then
        m.vel.y = 19.0;
        play_mario_sound(m, SOUND_ACTION_TERRAIN_JUMP, 0);

        if e.spareInt >= BOOST_LOCKOUT_TIME then
            e.spareInt = 0;

            if m.forwardVel < MAX_NORMAL_ROLL_SPEED then
                mario_set_forward_vel(m, math.min(m.forwardVel + ROLL_BOOST_GAIN, MAX_NORMAL_ROLL_SPEED));
            end

            m.particleFlags = m.particleFlags | PARTICLE_HORIZONTAL_STAR;

            -- ! playing this after the call to play_mario_sound seems to matter in making this sound play
            local cx, cy, cz = get_camera_position()
            play_sound(SOUND_ACTION_SPIN, cx, cy, cz)
        end

        return set_mario_action(m, ACT_ROLL_AIR, m.actionArg);
    end

    set_mario_animation(m, MARIO_ANIM_FORWARD_SPINNING);

    if update_roll_sliding(m, 10.0) ~= 0 then
        return set_mario_action(m, ACT_CROUCH_SLIDE, 0);
    end

    common_slide_action(m, ACT_CROUCH_SLIDE, ACT_ROLL_AIR, MARIO_ANIM_FORWARD_SPINNING);

    e.spareFloat = e.spareFloat + (0x80 * m.forwardVel);
    if e.spareFloat > 0x10000 then
        e.spareFloat = e.spareFloat - 0x10000;
    end
    set_anim_to_frame(m, 10 * e.spareFloat / 0x10000);

    e.spareInt = e.spareInt + 1;

    m.actionTimer = m.actionTimer + 1;

    return 0;
end

function act_roll_air(m)
    local e = gMarioStateExtras[m.playerIndex]
    local MAX_NORMAL_ROLL_SPEED = 50.0
    local ROLL_AIR_CANCEL_LOCKOUT_TIME = 15

    if m.actionTimer == 0 then
        if m.prevAction ~= ACT_ROLL then
            e.spareFloat = 0
            e.spareInt   = 0
        end
    end

    if (m.input & INPUT_Z_DOWN) == 0 and m.actionTimer >= ROLL_AIR_CANCEL_LOCKOUT_TIME then
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    set_mario_animation(m, MARIO_ANIM_FORWARD_SPINNING)

    local air_step = perform_air_step(m, 0)
    if air_step == AIR_STEP_LANDED then
        if check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0 then
            play_sound_and_spawn_particles(m, SOUND_ACTION_TERRAIN_STEP, 0)
            return set_mario_action(m, ACT_ROLL, m.actionArg)
        end
    elseif air_step == AIR_STEP_HIT_WALL then
        mario_bonk_reflection(m, false)
        m.faceAngle.y = m.faceAngle.y + 0x8000

        if m.vel.y > 0.0 then
            m.vel.y = 0.0
        end

        m.particleFlags = m.particleFlags | PARTICLE_VERTICAL_STAR
        return set_mario_action(m, ACT_BACKWARD_AIR_KB, 0)
    end

    e.spareFloat = e.spareFloat + 0x80 * m.forwardVel
    if e.spareFloat > 0x10000 then
        e.spareFloat = e.spareFloat - 0x10000
    end

    set_anim_to_frame(m, 10 * e.spareFloat / 0x10000)

    e.spareInt = e.spareInt + 1
    m.actionTimer = m.actionTimer + 1

    return false
end


---------------------------------------------------------

function update()
end

function mario_update(m)
    -- if m.vel.y > 0 then
        -- m.vel.y = m.vel.y + 2
    -- end

    if m.action == ACT_DIVE_SLIDE then
        if (m.input & INPUT_ABOVE_SLIDE) == 0 then
            if (m.input & INPUT_Z_DOWN) ~= 0 and m.actionTimer < 2 then
                return set_mario_action(m, ACT_ROLL, 1)
            elseif (m.input & INPUT_B_PRESSED) ~= 0 then
                -- dive hop
                -- m.vel.y = 21.0
                -- return set_mario_action(m, ACT_DIVE, 1)
            end
        end
        m.actionTimer = m.actionTimer + 1
    end

    if m.action == ACT_LONG_JUMP_LAND then
        if (m.input & INPUT_Z_DOWN) ~= 0 and m.forwardVel > 15.0 and m.actionTimer < 1 then
            play_mario_landing_sound_once(m, SOUND_ACTION_TERRAIN_LANDING);
            return set_mario_action(m, ACT_ROLL, 1);
        end
    end

    if m.action == ACT_CROUCHING then
        if (m.controller.buttonPressed & R_TRIG) ~= 0 then
            m.vel.y = 19.0
            mario_set_forward_vel(m, 32.0)
            play_mario_sound(m, SOUND_ACTION_TERRAIN_JUMP, 0)

            local cx, cy, cz = get_camera_position()
            play_sound(SOUND_ACTION_SPIN, cx, cy, cz)

            return set_mario_action(m, ACT_ROLL_AIR, 0)
        end
    end

    if m.action == ACT_CROUCH_SLIDE then
        if (m.controller.buttonPressed & R_TRIG) ~= 0 then
            m.vel.y = 19.0
            mario_set_forward_vel(m, math.max(32, m.forwardVel))
            play_mario_sound(m, SOUND_ACTION_TERRAIN_JUMP, 0)

            local cx, cy, cz = get_camera_position()
            play_sound(SOUND_ACTION_SPIN, cx, cy, cz)

            return set_mario_action(m, ACT_ROLL_AIR, 0)
        end
    end

    if m.action == ACT_GROUND_POUND_LAND then
        if (m.controller.buttonPressed & R_TRIG) ~= 0 then
            mario_set_forward_vel(m, 60)

            local cx, cy, cz = get_camera_position()
            play_sound(SOUND_ACTION_SPIN, cx, cy, cz)

            return set_mario_action(m, ACT_ROLL, 0)
        end
    end
end

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_mario_action(ACT_ROLL, act_roll)
hook_mario_action(ACT_ROLL_AIR, act_roll_air)
