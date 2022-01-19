------------------------
-- initialize actions --
------------------------

ACT_SPIN_POUND_LAND =           (0x037 | ACT_FLAG_STATIONARY | ACT_FLAG_ATTACKING)
ACT_ROLL =                      (0x05B | ACT_FLAG_MOVING | ACT_FLAG_BUTT_OR_STOMACH_SLIDE)
ACT_GROUND_POUND_JUMP =         (0x084 | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_SPIN_JUMP =                 (0x08B | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_SPIN_POUND =                (0x08F | ACT_FLAG_AIR | ACT_FLAG_ATTACKING)
ACT_LEDGE_PARKOUR =             (0x09D | ACT_FLAG_AIR)
ACT_ROLL_AIR =                  (0x0BA | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_WALL_SLIDE =                (0x0BF | ACT_FLAG_AIR | ACT_FLAG_MOVING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_WATER_GROUND_POUND =        (0x0C9 | ACT_FLAG_MOVING | ACT_FLAG_SWIMMING | ACT_FLAG_SWIMMING_OR_FLYING | ACT_FLAG_WATER_OR_TEXT | ACT_FLAG_ATTACKING)
ACT_WATER_GROUND_POUND_LAND =   (0x0CA | ACT_FLAG_STATIONARY | ACT_FLAG_SWIMMING | ACT_FLAG_SWIMMING_OR_FLYING | ACT_FLAG_WATER_OR_TEXT)
ACT_WATER_GROUND_POUND_STROKE = (0x0CB | ACT_FLAG_MOVING | ACT_FLAG_SWIMMING | ACT_FLAG_SWIMMING_OR_FLYING | ACT_FLAG_WATER_OR_TEXT)
ACT_WATER_GROUND_POUND_JUMP =   (0x0CC | ACT_FLAG_MOVING | ACT_FLAG_SWIMMING | ACT_FLAG_SWIMMING_OR_FLYING | ACT_FLAG_WATER_OR_TEXT)

-----------------------------
-- initialize extra fields --
-----------------------------

ANGLE_QUEUE_SIZE = 9
SPIN_TIMER_SUCCESSFUL_INPUT = 4

gMarioStateExtras = {}
for i=0,(MAX_PLAYERS-1) do
    gMarioStateExtras[i] = {}
    local e = gMarioStateExtras[i]
    e.angleDeltaQueue = {}
    for j=0,(ANGLE_QUEUE_SIZE-1) do e.angleDeltaQueue[j] = 0 end
    e.rotAngle = 0
    e.boostTimer = 0
    e.stickLastAngle = 0
    e.spinDirection = 0
    e.spinBufferTimer = 0
    e.spinInput = 0
    e.actionLastFrame = gMarioStates[i].action
    e.lastIntendedMag = 0
end

---------------
-- utilities --
---------------

function sins(theta)
    return math.sin(theta * math.pi / (2 * 16384))
end

function coss(theta)
    return math.cos(theta * math.pi / (2 * 16384))
end

----------
-- roll --
----------

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

function act_roll(m)
    local e = gMarioStateExtras[m.playerIndex]

    local MAX_NORMAL_ROLL_SPEED = 50.0
    local ROLL_BOOST_GAIN = 10.0
    local ROLL_CANCEL_LOCKOUT_TIME = 10
    local BOOST_LOCKOUT_TIME = 20

    -- e.rotAngle is used for Mario's rotation angle during the roll (persists when going into ACT_ROLL_AIR and back)
    -- e.boostTimer is used for the boost lockout timer (persists when going into ACT_ROLL_AIR and back)
    -- m.actionTimer is used to lockout walk canceling out of rollout (reset each action switch)

    if m.actionTimer == 0 then
        if m.prevAction ~= ACT_ROLL_AIR then
            e.rotAngle = 0
            e.boostTimer   = 0
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

        if e.boostTimer >= BOOST_LOCKOUT_TIME then
            e.boostTimer = 0;

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

    e.rotAngle = e.rotAngle + (0x80 * m.forwardVel);
    if e.rotAngle > 0x10000 then
        e.rotAngle = e.rotAngle - 0x10000;
    end
    set_anim_to_frame(m, 10 * e.rotAngle / 0x10000);

    e.boostTimer = e.boostTimer + 1;

    m.actionTimer = m.actionTimer + 1;

    return 0;
end

function act_roll_air(m)
    local e = gMarioStateExtras[m.playerIndex]
    local MAX_NORMAL_ROLL_SPEED = 50.0
    local ROLL_AIR_CANCEL_LOCKOUT_TIME = 15

    if m.actionTimer == 0 then
        if m.prevAction ~= ACT_ROLL then
            e.rotAngle = 0
            e.boostTimer   = 0
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

    e.rotAngle = e.rotAngle + 0x80 * m.forwardVel
    if e.rotAngle > 0x10000 then
        e.rotAngle = e.rotAngle - 0x10000
    end

    set_anim_to_frame(m, 10 * e.rotAngle / 0x10000)

    e.boostTimer = e.boostTimer + 1
    m.actionTimer = m.actionTimer + 1

    return false
end

function act_ground_pound_jump(m)
    local e = gMarioStateExtras[m.playerIndex]
    if check_kick_or_dive_in_air(m) ~= 0 then
        -- TODO: m.marioObj.header.gfx.angle.y = m.marioObj.header.gfx.angle.y + e.rotAngle
        return 1
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        -- TODO: m.marioObj.header.gfx.angle.y = m.marioObj.header.gfx.angle.y + e.rotAngle
        return set_mario_action(m, ACT_GROUND_POUND, 0)
    end

    if e.spinInput ~= 0 then
        return set_mario_action(m, ACT_SPIN_JUMP, 1)
    end

    if m.actionTimer == 0 then
        e.rotAngle = 0
    elseif m.actionTimer == 1 then
        local cx, cy, cz = get_camera_position()
        play_sound(SOUND_ACTION_SPIN, cx, cy, cz)
    end

    play_mario_sound(m, SOUND_ACTION_TERRAIN_JUMP, SOUND_MARIO_YAHOO)

    common_air_action_step(m, ACT_JUMP_LAND, MARIO_ANIM_SINGLE_JUMP,
                           AIR_STEP_CHECK_LEDGE_GRAB | AIR_STEP_CHECK_HANG)

    e.rotAngle = e.rotAngle + (0x10000*1.0 - e.rotAngle) / 5.0
    -- TODO: m.marioObj.header.gfx.angle.y = m.marioObj.header.gfx.angle.y - e.rotAngle

    m.actionTimer = m.actionTimer + 1

    return 0
end

function update_roll(m)
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

----------
-- spin --
----------

function mario_update_spin_input(m)
    local e = gMarioStateExtras[m.playerIndex]
    local rawAngle = atan2s(-m.controller.stickY, m.controller.stickX)
    e.spinInput = 0

    -- prevent issues due to the frame going out of the dead zone registering the last angle as 0
    if e.lastIntendedMag > 0.5 and m.intendedMag > 0.5 then
        local angleOverFrames = 0
        local thisFrameDelta = 0
        local i = 0

        local newDirection = e.spinDirection
        local signedOverflow = 0

        if rawAngle < e.stickLastAngle then
            if (e.stickLastAngle - rawAngle) > 0x8000 then
                signedOverflow = 1
            end
            if signedOverflow ~= 0 then
                newDirection = 1
            else
                newDirection = -1
            end
        elseif rawAngle > e.stickLastAngle then
            if (rawAngle - e.stickLastAngle) > 0x8000 then
                signedOverflow = 1
            end
            if signedOverflow ~= 0 then
                newDirection = -1
            else
                newDirection = 1
            end
        end

        if e.spinDirection ~= newDirection then
            for i=0,(ANGLE_QUEUE_SIZE-1) do
                e.angleDeltaQueue[i] = 0
            end
            e.spinDirection = newDirection
        else
            for i=(ANGLE_QUEUE_SIZE-1),1,-1 do
                e.angleDeltaQueue[i] = e.angleDeltaQueue[i-1]
                angleOverFrames = angleOverFrames + e.angleDeltaQueue[i]
            end
        end

        if e.spinDirection < 0 then
            if signedOverflow ~= 0 then
                thisFrameDelta = math.floor((1.0*e.stickLastAngle + 0x10000) - rawAngle)
            else
                thisFrameDelta = e.stickLastAngle - rawAngle
            end
        elseif e.spinDirection > 0 then
            if signedOverflow ~= 0 then
                thisFrameDelta = math.floor(1.0*rawAngle + 0x10000 - e.stickLastAngle)
            else
                thisFrameDelta = rawAngle - e.stickLastAngle
            end
        end

        e.angleDeltaQueue[0] = thisFrameDelta
        angleOverFrames = angleOverFrames + thisFrameDelta

        if angleOverFrames >= 0xA000 then
            e.spinBufferTimer = SPIN_TIMER_SUCCESSFUL_INPUT
        end


        -- allow a buffer after a successful input so that you can switch directions
        if e.spinBufferTimer > 0 then
            e.spinInput = 1
            e.spinBufferTimer = e.spinBufferTimer - 1
        end
    else
        e.spinDirection = 0
        e.spinBufferTimer = 0
    end

    e.stickLastAngle = rawAngle
    e.lastIntendedMag = m.intendedMag
end

function act_spin_jump(m)
    local e = gMarioStateExtras[m.playerIndex]
    if m.actionTimer == 0 then
        -- determine clockwise/counter-clockwise spin
        if e.spinDirection < 0 then
            m.actionState = 1
        end
    elseif m.actionTimer == 1 or m.actionTimer == 4 then
        local cx, cy, cz = get_camera_position()
        play_sound(SOUND_ACTION_TWIRL, cx, cy, cz)
    end

    local spinDirFactor = 1  -- negative for clockwise, positive for counter-clockwise
    if m.actionState == 1 then
        spinDirFactor = -1
    end

    if (m.input & INPUT_B_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_DIVE, 0)
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        local cx, cy, cz = get_camera_position()
        play_sound(SOUND_ACTION_TWIRL, cx, cy, cz)

        m.vel.y = -50.0
        mario_set_forward_vel(m, 0.0)

        -- choose which direction to be facing on land (practically random if no input)
        if (m.input & INPUT_NONZERO_ANALOG) ~= 0 then
            m.faceAngle.y = m.intendedYaw
        else
            m.faceAngle.y = e.rotAngle
        end

        return set_mario_action(m, ACT_SPIN_POUND, m.actionState)
    end

    play_mario_sound(m, SOUND_ACTION_TERRAIN_JUMP, SOUND_MARIO_YAHOO)

    common_air_action_step(m, ACT_DOUBLE_JUMP_LAND, MARIO_ANIM_TWIRL,
                           AIR_STEP_CHECK_HANG)

    e.rotAngle = e.rotAngle + 0x2867
    if (e.rotAngle >  0x10000) then e.rotAngle = e.rotAngle - 0x10000 end
    if (e.rotAngle < -0x10000) then e.rotAngle = e.rotAngle + 0x10000 end
    -- TODO: m.marioObj.header.gfx.angle.y = m.marioObj.header.gfx.angle.y + (s16) (e.rotAngle * spinDirFactor)

    -- gravity
    m.vel.y = m.vel.y + 2
    if (m.flags & MARIO_WING_CAP) ~= 0 and m.vel.y < 0.0 and (m.input & INPUT_A_DOWN) ~= 0 then
        -- TODO: m.marioBodyState.wingFlutter = 1
        m.vel.y = m.vel.y - 0.7
        if m.vel.y < -37.5 then
            m.vel.y = m.vel.y + 1.4
            if m.vel.y > -37.5 then
                m.vel.y = -37.5
            end
        end
    else
        if m.vel.y > 0 then
            m.vel.y = m.vel.y - 4
        else
            m.vel.y = m.vel.y + 1.4
        end

        if m.vel.y < -75.0 then
            m.vel.y = -75.5
        end
    end

    m.actionTimer = m.actionTimer + 1

    return false
end

function act_spin_pound(m)
    local e = gMarioStateExtras[m.playerIndex]
    if m.actionTimer == 0 then
        m.actionState = m.actionArg
    end

    local spinDirFactor = 1  -- negative for clockwise, positive for counter-clockwise
    if m.actionState == 1 then spinDirFactor = -1 end

    set_mario_animation(m, MARIO_ANIM_TWIRL)

    if (m.input & INPUT_B_PRESSED) ~= 0 then
        mario_set_forward_vel(m, 10.0)
        m.vel.y = 35
        set_mario_action(m, ACT_DIVE, 0)
    end

    local stepResult = perform_air_step(m, 0)
    if stepResult == AIR_STEP_LANDED then
        if should_get_stuck_in_ground(m) ~= 0 then
            local cx, cy, cz = get_camera_position()
            play_sound(SOUND_MARIO_OOOF2, cx, cy, cz)
            m.particleFlags = m.particleFlags | PARTICLE_MIST_CIRCLE
            set_mario_action(m, ACT_BUTT_STUCK_IN_GROUND, 0)
        else
            play_mario_heavy_landing_sound(m, SOUND_ACTION_TERRAIN_HEAVY_LANDING)
            if check_fall_damage(m, ACT_HARD_BACKWARD_GROUND_KB) == 0 then
                m.particleFlags = m.particleFlags | PARTICLE_MIST_CIRCLE | PARTICLE_HORIZONTAL_STAR
                set_mario_action(m, ACT_SPIN_POUND_LAND, 0)
            end
        end
        set_camera_shake_from_hit(SHAKE_GROUND_POUND)
    elseif stepResult == AIR_STEP_HIT_WALL then
        mario_set_forward_vel(m, -16.0)
        if m.vel.y > 0.0 then
            m.vel.y = 0.0
        end

        m.particleFlags = m.particleFlags | PARTICLE_VERTICAL_STAR
        set_mario_action(m, ACT_BACKWARD_AIR_KB, 0)
    end

    e.rotAngle = e.rotAngle + 0x3053
    if e.rotAngle >  0x10000 then e.rotAngle = e.rotAngle - 0x10000 end
    if e.rotAngle < -0x10000 then e.rotAngle = e.rotAngle + 0x10000 end
    -- TODO: m.marioObj.header.gfx.angle.y = m.marioObj.header.gfx.angle.y + e.rotAngle * spinDirFactor

    m.actionTimer = m.actionTimer + 1

    return 0
end

function act_spin_pound_land(m)
    m.actionState = 1

    if m.actionTimer <= 8 then
        if (m.input & INPUT_UNKNOWN_10) ~= 0 then
            return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0)
        end

        if (m.input & INPUT_OFF_FLOOR) ~= 0 then
            return set_mario_action(m, ACT_FREEFALL, 0)
        end

        if (m.input & INPUT_ABOVE_SLIDE) ~= 0 then
            return set_mario_action(m, ACT_BUTT_SLIDE, 0)
        end

        if (m.input & INPUT_A_PRESSED) ~= 0 then
            m.vel.y = 65.0
            return set_jumping_action(m, ACT_GROUND_POUND_JUMP, 0)
        end

        if (m.controller.buttonPressed & R_TRIG) ~= 0 then
            mario_set_forward_vel(m, 60)

            local cx, cy, cz = get_camera_position()
            play_sound(SOUND_ACTION_SPIN, cx, cy, cz)
            return set_mario_action(m, ACT_ROLL, 0)
        end

        stationary_ground_step(m)
        set_mario_animation(m, MARIO_ANIM_LAND_FROM_DOUBLE_JUMP)
    else
        if (m.input & INPUT_UNKNOWN_10) ~= 0 then
            return set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0)
        end

        if (m.input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE)) ~= 0 then
            return check_common_action_exits(m)
        end

        stopping_step(m, MARIO_ANIM_LAND_FROM_DOUBLE_JUMP, ACT_IDLE)
    end

    m.actionTimer = m.actionTimer + 1

    return 0
end

---------------------------------------------------------

function mario_action_on_change(m)
    local e = gMarioStateExtras[m.playerIndex]
    if e.spinInput ~= 0 then
        if m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_TRIPLE_JUMP or m.action == ACT_SIDE_FLIP or m.action == ACT_BACKFLIP or m.action == ACT_WALL_KICK_AIR then
            set_mario_action(m, ACT_SPIN_JUMP, 1)
            m.vel.y = 65.0
            m.faceAngle.y = m.intendedYaw
        end
    end

    if m.action == ACT_GROUND_POUND_JUMP then
        m.vel.y = 65.0
    elseif m.action == ACT_WALL_SLIDE then
        m.vel.y = 0.0
    end
end

function mario_update(m)
    local e = gMarioStateExtras[m.playerIndex]

    mario_update_spin_input(m)
    update_roll(m)

    -- dive hop
    if (m.input & INPUT_B_PRESSED) ~= 0 and (m.input & INPUT_ABOVE_SLIDE) == 0 then
        if m.action == ACT_FORWARD_ROLLOUT and m.prevAction == ACT_DIVE_SLIDE then
            m.vel.y = 21.0
            return set_mario_action(m, ACT_DIVE, 1)

        end
    end

    -- dive out of ACT_GROUND_POUND
    if m.action == ACT_GROUND_POUND and (m.input & INPUT_B_PRESSED) ~= 0 then
        mario_set_forward_vel(m, 10.0)
        m.vel.y = 35.0
        set_mario_action(m, ACT_DIVE, 0)
    end

    -- spin
    if e.actionLastFrame == m.action and (m.action == ACT_JUMP or m.action == ACT_WALL_KICK_AIR) and e.spinInput ~= 0 then
        set_mario_action(m, ACT_SPIN_JUMP, 1)
        e.spinInput = 0
    end

    -- twirl pound
    if m.action == ACT_TWIRLING and (m.input & INPUT_Z_PRESSED) ~= 0 then
        set_mario_action(m, ACT_SPIN_POUND, 0)
    end

    -- ground pound jump
    if m.action == ACT_GROUND_POUND_LAND and (m.input & INPUT_A_PRESSED) ~= 0 then
        set_mario_action(m, ACT_GROUND_POUND_JUMP, 0)
    end

    -- action change event
    if e.actionLastFrame ~= m.action then
        mario_action_on_change(m)
    end
    e.actionLastFrame = m.action

end

function update()
end

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_mario_action(ACT_ROLL, act_roll)
hook_mario_action(ACT_ROLL_AIR, act_roll_air)
hook_mario_action(ACT_SPIN_JUMP, act_spin_jump)
hook_mario_action(ACT_SPIN_POUND, act_spin_pound)
hook_mario_action(ACT_SPIN_POUND_LAND, act_spin_pound_land)
hook_mario_action(ACT_GROUND_POUND_JUMP, act_ground_pound_jump)
