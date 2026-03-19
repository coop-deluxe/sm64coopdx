ANGLE_QUEUE_SIZE = 9
SPIN_TIMER_SUCCESSFUL_INPUT = 4

gEventTable = {}

gStateExtras = {}
for i = 0, (MAX_PLAYERS - 1) do
    gStateExtras[i] = {}
    local e = gStateExtras[i]
    e.angleDeltaQueue = {}
    for j = 1, ANGLE_QUEUE_SIZE do e.angleDeltaQueue[j] = 0 end
    e.averageForwardVel = 0
    e.lastHurtCounter = 0
    e.stickLastAngle = 0
    e.spinDirection = 0
    e.spinBufferTimer = 0
    e.spinInput = 0
    e.lastIntendedMag = 0
    e.swims = 0
end

-----------
-- toad --
-----------

function toad_before_phys_step(m)
    local hScale = 1.0
    local vScale = 1.0

    -- faster ground movement
    if (m.action & ACT_FLAG_MOVING) ~= 0 then
        hScale = hScale * 1.19
    end

    -- slower holding item
    if m.heldObj then
        m.vel.y = m.vel.y - 2.0
        hScale = hScale * 0.9
        if (m.action & ACT_FLAG_AIR) ~= 0 then
            hScale = hScale * 0.9
        end
    end

    m.vel.x = m.vel.x * hScale
    m.vel.y = m.vel.y * vScale
    m.vel.z = m.vel.z * hScale
end

function toad_on_set_action(m)
    local e = gStateExtras[m.playerIndex]

    -- wall kick height based on how fast toad is going
    if m.action == ACT_WALL_KICK_AIR and m.prevAction ~= ACT_HOLDING_POLE and m.prevAction ~= ACT_CLIMBING_POLE then
        m.vel.y = m.vel.y * 0.5
        m.vel.y = m.vel.y + e.averageForwardVel * 0.7
        return
    end

    -- more distance on dive and long jump
    if m.action == ACT_DIVE or m.action == ACT_LONG_JUMP then
        m.forwardVel = m.forwardVel * 1.35
    end

    -- less height on jumps
    if m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_TRIPLE_JUMP or m.action == ACT_SPECIAL_TRIPLE_JUMP or m.action == ACT_STEEP_JUMP or m.action == ACT_RIDING_SHELL_JUMP or m.action == ACT_BACKFLIP or m.action == ACT_WALL_KICK_AIR  or m.action == ACT_LONG_JUMP then
        m.vel.y = m.vel.y * 0.8

        -- prevent from getting stuck on platform
        if m.marioObj.platform then
            m.pos.y = m.pos.y + 10
        end
    elseif m.action == ACT_SIDE_FLIP then
        m.vel.y = m.vel.y * 0.86

        -- prevent from getting stuck on platform
        if m.marioObj.platform then
            m.pos.y = m.pos.y + 10
        end
    end
end

function toad_update(m)
    local e = gStateExtras[m.playerIndex]

    -- track average forward velocity
    if e.averageForwardVel > m.forwardVel then
        e.averageForwardVel = e.averageForwardVel * 0.93 + m.forwardVel * 0.07
    else
        e.averageForwardVel = m.forwardVel
    end

    -- keep your momentum for a while
    if m.action == ACT_WALKING and m.forwardVel > 30 then
        mario_set_forward_vel(m, m.forwardVel + 0.8)
    end

    -- faster flip during ground pound
    if m.action == ACT_GROUND_POUND then
        if m.actionTimer < 10 then
            m.actionTimer = m.actionTimer + 1
        end
    end

    -- ground pound jump
    if m.action == ACT_GROUND_POUND_LAND and (m.input & INPUT_A_PRESSED) ~= 0 then
        set_mario_action(m, ACT_TRIPLE_JUMP, 0)
        m.vel.y = m.vel.y + 18
        m.forwardVel = m.forwardVel + 10
    end

end

gEventTable[CT_TOAD] = {
    before_phys_step = toad_before_phys_step,
    on_set_action    = toad_on_set_action,
    update           = toad_update,
}

-------------
-- waluigi --
-------------

ACT_WALL_SLIDE       = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_MOVING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_ELEGANT_JUMP     = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_CONTROL_JUMP_HEIGHT)
ACT_WALUIGI_AIR_SWIM = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_MOVING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)

function act_wall_slide(m)
    if (m.input & INPUT_A_PRESSED) ~= 0 then
        local rc = set_mario_action(m, ACT_TRIPLE_JUMP, 0)
        m.vel.y = 72.0

        if m.forwardVel < 20.0 then
            m.forwardVel = 20.0
        end
        m.wallKickTimer = 0
        return rc
    end

    -- attempt to stick to the wall a bit. if it's 0, sometimes you'll get kicked off of slightly sloped walls
    mario_set_forward_vel(m, -1.0)

    m.particleFlags = m.particleFlags | PARTICLE_DUST

    play_sound(SOUND_MOVING_TERRAIN_SLIDE + m.terrainSoundAddend, m.marioObj.header.gfx.cameraToObject)
    set_mario_animation(m, MARIO_ANIM_START_WALLKICK)

    if perform_air_step(m, 0) == AIR_STEP_LANDED then
        mario_set_forward_vel(m, 0.0)
        if check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0 then
            return set_mario_action(m, ACT_FREEFALL_LAND, 0)
        end
    end

    m.actionTimer = m.actionTimer + 1
    if m.wall == nil and m.actionTimer > 2 then
        mario_set_forward_vel(m, 0.0)
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    -- gravity
    m.vel.y = m.vel.y + 2

    return 0
end

function act_elegant_jump(m)
    if m.actionArg == 0 then
        m.particleFlags = m.particleFlags | PARTICLE_MIST_CIRCLE
        play_character_sound(m, CHAR_SOUND_HAHA)
        m.twirlYaw = m.faceAngle.y
        m.actionArg = math.random(2)
    end
    local stepResult = common_air_action_step(m, ACT_DOUBLE_JUMP_LAND, MARIO_ANIM_RUNNING_UNUSED,
                                              AIR_STEP_CHECK_LEDGE_GRAB | AIR_STEP_CHECK_HANG)
    if stepResult == AIR_STEP_NONE then
        smlua_anim_util_set_animation(m.marioObj, "WALUIGI_ANIM_ELEGANT_JUMP_" .. tostring(m.actionArg))
    end
    m.particleFlags = m.particleFlags | PARTICLE_SPARKLES
    m.marioBodyState.eyeState = MARIO_EYES_CLOSED
    m.faceAngle.y = m.intendedYaw

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_GROUND_POUND, 0)
    end

    if (m.input & INPUT_NONZERO_ANALOG) ~= 0 then
        mario_set_forward_vel(m, math.abs(m.forwardVel))
    end

    if stepResult == AIR_STEP_LANDED then
        if should_get_stuck_in_ground(m) ~= 0 then
            queue_rumble_data_mario(m, 5, 80)
            play_sound(SOUND_MARIO_OOOF2, m.marioObj.header.gfx.cameraToObject)
            m.particleFlags = m.particleFlags | PARTICLE_MIST_CIRCLE
            set_mario_action(m, ACT_FEET_STUCK_IN_GROUND, 0)
        else
            play_sound(SOUND_ACTION_TERRAIN_LANDING, m.marioObj.header.gfx.cameraToObject)
            set_mario_action(m, ACT_DOUBLE_JUMP_LAND, 0)
        end
    end

    m.twirlYaw = m.twirlYaw + 0x2000
    m.marioObj.header.gfx.angle.y = m.twirlYaw
    return 0
end

function act_waluigi_air_swim(m)
    local e = gStateExtras[m.playerIndex]

    if m.actionTimer == 0 then
        set_anim_to_frame(m, 0)
        play_sound(SOUND_ACTION_SWIM_FAST, m.marioObj.header.gfx.cameraToObject)
        if m.forwardVel <= 40 then
            mario_set_forward_vel(m, 40)
        else
            mario_set_forward_vel(m, m.forwardVel + 5)
        end
    end

    if m.actionTimer >= 20 then
        set_mario_action(m, ACT_DIVE, 0)
        m.vel.y = 0
        m.faceAngle.x = 0
        mario_set_forward_vel(m, 0)
    end

    if m.actionTimer > 10 and (m.controller.buttonPressed & B_BUTTON) ~= 0 and e.swims > 0 then
        e.swims = e.swims - 1
        return set_mario_action(m, ACT_WALUIGI_AIR_SWIM, 0)
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_GROUND_POUND, 0)
    end

    m.vel.y = 0

    set_mario_animation(m, MARIO_ANIM_SWIM_PART1)

    local stepResult = perform_air_step(m, 0)
    if stepResult == AIR_STEP_LANDED then
        if should_get_stuck_in_ground(m) ~= 0 then
            queue_rumble_data_mario(m, 5, 80)
            play_character_sound(m, CHAR_SOUND_OOOF2)
            set_mario_action(m, ACT_FEET_STUCK_IN_GROUND, 0)
        else
            if check_fall_damage(m, ACT_SQUISHED) == 0 then
                set_mario_action(m, ACT_DIVE_SLIDE, 0)
            end
        end
    elseif stepResult == AIR_STEP_HIT_WALL then
        set_mario_action(m, ACT_SOFT_BONK, 0)
    end

    if m.forwardVel > 4 then mario_set_forward_vel(m, m.forwardVel - 2) end
    m.actionTimer = m.actionTimer + 1
    m.faceAngle.y = m.intendedYaw - approach_s32(convert_s16(m.intendedYaw - m.faceAngle.y), 0, 0x200, 0x200)
    return 0
end

function waluigi_before_phys_step(m)
    local e = gStateExtras[m.playerIndex]

    local hScale = 1.0
    local vScale = 1.0

    -- faster ground movement
    if (m.action & ACT_FLAG_MOVING) ~= 0 then
        hScale = hScale * 1.09
    end

    m.vel.x = m.vel.x * hScale
    m.vel.y = m.vel.y * vScale
    m.vel.z = m.vel.z * hScale

    if m.action == ACT_TRIPLE_JUMP and m.prevAction == ACT_DOUBLE_JUMP and m.actionTimer < 6 then
        m.particleFlags = m.particleFlags | PARTICLE_DUST
        m.actionTimer = m.actionTimer + 1
    end
end

function waluigi_on_set_action(m)
    local e = gStateExtras[m.playerIndex]

    -- wall slide
    if m.action == ACT_SOFT_BONK then
        m.faceAngle.y = m.faceAngle.y + 0x8000
        set_mario_action(m, ACT_WALL_SLIDE, 0)
        m.vel.x = 0
        m.vel.y = 0
        m.vel.z = 0

    -- turn wall kick into flip
    elseif m.action == ACT_WALL_KICK_AIR and m.prevAction ~= ACT_HOLDING_POLE and m.prevAction ~= ACT_CLIMBING_POLE then
        local rc = set_mario_action(m, ACT_TRIPLE_JUMP, 0)
        m.vel.y = 60.0

        if m.forwardVel < 20.0 then
            m.forwardVel = 20.0
        end
        m.wallKickTimer = 0
        return rc

    -- less height on jumps
    elseif m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_TRIPLE_JUMP or m.action == ACT_SPECIAL_TRIPLE_JUMP or m.action == ACT_STEEP_JUMP or m.action == ACT_SIDE_FLIP or m.action == ACT_RIDING_SHELL_JUMP or m.action == ACT_BACKFLIP or m.action == ACT_WALL_KICK_AIR  or m.action == ACT_LONG_JUMP then
        m.vel.y = m.vel.y * 0.9
    end

    -- more height on triple jump
    if m.action == ACT_TRIPLE_JUMP or m.action == ACT_SPECIAL_TRIPLE_JUMP then
        m.vel.y = m.vel.y * 1.25
    end

    if m.action == ACT_ELEGANT_JUMP then
        m.vel.y = 60
    end
end

function waluigi_update(m)
    local e = gStateExtras[m.playerIndex]

    -- increase player damage (go easy on the capless players)
    if m.hurtCounter > e.lastHurtCounter then
        if m.flags & (MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD) == 0 then
            m.hurtCounter = m.hurtCounter + 6
        else
            m.hurtCounter = m.hurtCounter + 8
        end
    end
    e.lastHurtCounter = m.hurtCounter

    -- double jump
    local shouldDoubleJump = (m.action == ACT_DOUBLE_JUMP or m.action == ACT_JUMP or m.action == ACT_SIDE_FLIP or m.action == ACT_BACKFLIP or m.action == ACT_FREEFALL)

    if shouldDoubleJump and m.actionTimer > 0 and (m.controller.buttonPressed & A_BUTTON) ~= 0 then
        return set_mario_action(m, ACT_ELEGANT_JUMP, 0)
    end
    if shouldDoubleJump then
        m.actionTimer = m.actionTimer + 1
    end

    -- swim mid-air
    if m.action == ACT_DIVE and m.actionTimer > 0 and (m.controller.buttonPressed & B_BUTTON) ~= 0 and e.swims > 0 then
        e.swims = e.swims - 1
        return set_mario_action(m, ACT_WALUIGI_AIR_SWIM, 0)
    end
    if (m.action & ACT_GROUP_AIRBORNE) == 0 then
        e.swims = 3
    end

    if m.action == ACT_DIVE then
        m.actionTimer = m.actionTimer + 1
        if m.prevAction == ACT_WALUIGI_AIR_SWIM then
            set_mario_animation(m, MARIO_ANIM_SWIM_PART1)
            set_anim_to_frame(m, 30)
        end
    end
end

gEventTable[CT_WALUIGI] = {
    before_phys_step = waluigi_before_phys_step,
    on_set_action    = waluigi_on_set_action,
    update           = waluigi_update,
}

-----------
-- wario --
-----------

ACT_WARIO_DASH             = allocate_mario_action(ACT_GROUP_MOVING | ACT_FLAG_MOVING | ACT_FLAG_ATTACKING)
ACT_WARIO_AIR_DASH         = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ATTACKING)
ACT_WARIO_DASH_REBOUND     = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR)
ACT_PILEDRIVER             = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ATTACKING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_PILEDRIVER_LAND        = allocate_mario_action(ACT_GROUP_MOVING | ACT_FLAG_MOVING | ACT_FLAG_ATTACKING)
ACT_WARIO_HOLD_JUMP        = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_WARIO_HOLD_FREEFALL    = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_CORKSCREW_CONK         = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ATTACKING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_CONTROL_JUMP_HEIGHT)
ACT_WARIO_SPINNING_OBJ     = allocate_mario_action(ACT_GROUP_OBJECT | ACT_FLAG_STATIONARY)

function act_corkscrew_conk(m)
    -- visuals
    m.particleFlags = m.particleFlags | PARTICLE_DUST

    -- physics
    common_air_action_step(m, ACT_JUMP_LAND, MARIO_ANIM_FORWARD_SPINNING, AIR_STEP_NONE)

    -- fast ground pound out of it
    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        local rc = set_mario_action(m, ACT_GROUND_POUND, 0)
        m.actionTimer = 5
        return rc
    end

    return 0
end

function act_wario_dash(m)
    m.marioBodyState.eyeState = 5

    -- make sound
    if m.actionTimer == 0 then
        m.actionState = m.actionArg
        play_character_sound(m, CHAR_SOUND_WAH2)
    end

    -- walk once dash is up
    if m.actionTimer > 30 then
        return set_mario_action(m, ACT_WALKING, 0)
    end

    -- physics
    local stepResult = perform_ground_step(m)
    if stepResult == GROUND_STEP_HIT_WALL then
        if m.wall.object == nil or m.wall.object.oInteractType & (INTERACT_BREAKABLE) == 0 then
            return wario_rebound(m, -40, 30)
        end
    elseif stepResult == GROUND_STEP_LEFT_GROUND then
        m.action = ACT_WARIO_AIR_DASH
    end

    set_mario_anim_with_accel(m, MARIO_ANIM_RUNNING_UNUSED, m.forwardVel / 5 * 0x10000)
    smlua_anim_util_set_animation(m.marioObj, "WARIO_ANIM_SHOULDER_BASH")
    play_step_sound(m, 15, 35)

    -- set dash speed
    local speed = 50
    if m.actionTimer > 8 then
        speed = speed - (m.actionTimer - 8)
    end
    mario_set_forward_vel(m, speed)

    -- corkscrew conk
    if (m.input & INPUT_A_PRESSED) ~= 0 then
        set_jumping_action(m, ACT_CORKSCREW_CONK, 0)
        play_character_sound(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE)
    end

    -- slide kick
    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_SLIDE_KICK, 0)
    end

    m.faceAngle.y = m.intendedYaw - approach_s32(convert_s16(m.intendedYaw - m.faceAngle.y), 0, 0x400, 0x400)

    m.actionTimer = m.actionTimer + 1
    return 0
end

function act_wario_air_dash(m)
    m.marioBodyState.eyeState = 5

    -- fall once dash is up
    if m.actionTimer > 30 * 5 then
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    -- physics
    local stepResult = perform_air_step(m, 0)
    update_air_without_turn(m)
    set_mario_animation(m, MARIO_ANIM_FIRST_PUNCH)
    smlua_anim_util_set_animation(m.marioObj, "WARIO_ANIM_SHOULDER_BASH_AIR")
    if stepResult == AIR_STEP_HIT_WALL then
        if m.wall.object and m.wall.object.oInteractType & (INTERACT_BREAKABLE) == 0 then
            return wario_rebound(m, -40, 15)
        end
    elseif stepResult == AIR_STEP_LANDED then
        if check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0 then
            if m.actionTimer < 1 then
                m.action = ACT_WARIO_DASH
            else
                set_mario_action(m, ACT_WALKING, 0)
            end
        end
    end

    -- corkscrew conk
    if (m.input & INPUT_A_PRESSED) ~= 0 then
        m.particleFlags = m.particleFlags | PARTICLE_MIST_CIRCLE
        set_jumping_action(m, ACT_CORKSCREW_CONK, 0)
        play_character_sound(m, CHAR_SOUND_YAHOO)
    end

    -- slide kick
    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_SLIDE_KICK, 0)
    end

    m.faceAngle.y = m.intendedYaw - approach_s32(convert_s16(m.intendedYaw - m.faceAngle.y), 0, 0x400, 0x400)

    m.actionTimer = m.actionTimer + 1
    return 0
end

function act_wario_dash_rebound(m)
    m.marioBodyState.eyeState = 5

    -- physics
    local stepResult = perform_air_step(m, 0)
    update_air_without_turn(m)
    set_mario_animation(m, MARIO_ANIM_FIRST_PUNCH)
    smlua_anim_util_set_animation(m.marioObj, "WARIO_ANIM_SHOULDER_BASH_AIR")
    if stepResult == AIR_STEP_LANDED then
        if check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0 then
            return set_mario_action(m, ACT_FREEFALL_LAND, 0)
        end
    end
    return 0
end

function wario_rebound(m, VelF, VelY)
    mario_set_forward_vel(m, VelF)
    set_camera_shake_from_point(SHAKE_POS_SMALL, m.pos.x, m.pos.y, m.pos.z)
    m.vel.y = VelY
    set_mario_action(m, ACT_WARIO_DASH_REBOUND, 0)
    m.particleFlags = m.particleFlags | PARTICLE_VERTICAL_STAR
    play_sound(SOUND_ACTION_BOUNCE_OFF_OBJECT, m.marioObj.header.gfx.cameraToObject)
    return 0
end

function act_wario_spinning_obj(m)
    local spin = 0

    -- throw object
    if m.playerIndex == 0 and (m.input & INPUT_B_PRESSED) ~= 0 then
        play_character_sound_if_no_flag(m, CHAR_SOUND_WAH2, MARIO_MARIO_SOUND_PLAYED)
        play_sound_if_no_flag(m, SOUND_ACTION_THROW, MARIO_ACTION_SOUND_PLAYED)
        return set_mario_action(m, ACT_RELEASING_BOWSER, 0)
    end

    -- set animation
    if m.playerIndex == 0 and m.angleVel.y == 0 then
        m.actionTimer = m.actionTimer + 1
        if m.actionTimer > 120 then
            return set_mario_action(m, ACT_RELEASING_BOWSER, 1)
        end

        set_mario_animation(m, MARIO_ANIM_HOLDING_BOWSER)
    else
        m.actionTimer = 0
        set_mario_animation(m, MARIO_ANIM_SWINGING_BOWSER)
    end

    -- spin
    if m.intendedMag > 20.0 then
        -- spin = acceleration
        spin = (m.intendedYaw - m.twirlYaw) / 0x20

        if spin < -0x80 then
            spin = -0x80
        end
        if spin > 0x80 then
            spin = 0x80
        end

        m.twirlYaw = m.intendedYaw
        m.angleVel.y = m.angleVel.y + spin

        if m.angleVel.y > 0x1000 then
            m.angleVel.y = 0x1000
        end
        if m.angleVel.y < -0x1000 then
            m.angleVel.y = -0x1000
        end
    elseif m.angleVel.y > -0x750 and m.angleVel.y < 0x750 then
        -- go back to walking
        if m.forwardVel ~= 0 then m.faceAngle.y = atan2s(m.vel.z, m.vel.x) end
        return set_mario_action(m, ACT_HOLD_WALKING, 0)
    else
        -- slow down spin
        m.angleVel.y = approach_s32(m.angleVel.y, 0, 128, 128);
    end

    -- apply spin
    spin = m.faceAngle.y
    m.faceAngle.y = m.faceAngle.y + m.angleVel.y

    -- play sound on overflow
    if m.angleVel.y <= -0x100 and spin < m.faceAngle.y then
        queue_rumble_data_mario(m, 4, 20)
        play_sound(SOUND_OBJ_BOWSER_SPINNING, m.marioObj.header.gfx.cameraToObject)
    end
    if m.angleVel.y >= 0x100 and spin > m.faceAngle.y then
        queue_rumble_data_mario(m, 4, 20)
        play_sound(SOUND_OBJ_BOWSER_SPINNING, m.marioObj.header.gfx.cameraToObject)
    end

    perform_ground_step(m)

    apply_slope_decel(m, 0.1)

    if m.angleVel.y >= 0 then
        m.marioObj.header.gfx.angle.x = -m.angleVel.y
    else
        m.marioObj.header.gfx.angle.x = m.angleVel.y
    end

    return false
end

function wario_update_spin_input(m)
    local e = gStateExtras[m.playerIndex]
    local rawAngle = atan2s(-m.controller.stickY, m.controller.stickX)

    -- prevent issues due to the frame going out of the dead zone registering the last angle as 0
    if e.lastIntendedMag > 0.5 and m.intendedMag > 0.5 then
        local angleOverFrames = 0
        local thisFrameDelta = 0

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
            for i = 1, ANGLE_QUEUE_SIZE do
                e.angleDeltaQueue[i] = 0
            end
            e.spinDirection = newDirection
        else
            for i = ANGLE_QUEUE_SIZE, 2, -1 do
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
                thisFrameDelta = math.floor(1.0 * rawAngle + 0x10000 - e.stickLastAngle)
            else
                thisFrameDelta = rawAngle - e.stickLastAngle
            end
        end

        e.angleDeltaQueue[1] = thisFrameDelta
        angleOverFrames = angleOverFrames + thisFrameDelta

        if angleOverFrames >= 0xA000 then
            e.spinBufferTimer = SPIN_TIMER_SUCCESSFUL_INPUT
        end


        -- allow a buffer after a successful input so that you can switch directions
        if e.spinBufferTimer > 0 then
            e.spinInput = e.spinInput + 1
            e.spinBufferTimer = e.spinBufferTimer - 1
        end
    else
        e.spinDirection = 0
        e.spinBufferTimer = 0
        e.spinInput = 0
    end

    e.stickLastAngle = rawAngle
    e.lastIntendedMag = m.intendedMag
end

-- patch wario's hold jump for piledriver
function act_wario_hold_jump(m)
    if (m.marioObj.oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) ~= 0 then
        return drop_and_set_mario_action(m, ACT_FREEFALL, 0)
    end

    if (m.input & INPUT_B_PRESSED) ~= 0 and (m.heldObj and (m.heldObj.oInteractionSubtype & INT_SUBTYPE_HOLDABLE_NPC) ~= 0) then
        return set_mario_action(m, ACT_AIR_THROW, 0)
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_PILEDRIVER, 0)
    end

    play_mario_sound(m, SOUND_ACTION_TERRAIN_JUMP, 0)
    common_air_action_step(m, ACT_HOLD_JUMP_LAND, MARIO_ANIM_JUMP_WITH_LIGHT_OBJ,
                           AIR_STEP_CHECK_LEDGE_GRAB)
    return false
end

function act_wario_hold_freefall(m)
    local animation = (m.actionArg == 0) and CHAR_ANIM_FALL_WITH_LIGHT_OBJ or CHAR_ANIM_FALL_FROM_SLIDING_WITH_LIGHT_OBJ

    if (m.marioObj.oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) ~= 0 then
        return drop_and_set_mario_action(m, ACT_FREEFALL, 0)
    end

    if (m.input & INPUT_B_PRESSED) ~= 0 and (m.heldObj and (m.heldObj.oInteractionSubtype & INT_SUBTYPE_HOLDABLE_NPC) ~= 0) then
        return set_mario_action(m, ACT_AIR_THROW, 0)
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_PILEDRIVER, 0)
    end

    common_air_action_step(m, ACT_HOLD_FREEFALL_LAND, animation, AIR_STEP_CHECK_LEDGE_GRAB)
    return false
end

function act_piledriver(m)
    if m.actionTimer == 0 then
        play_sound(SOUND_ACTION_SPIN, m.marioObj.header.gfx.cameraToObject)
        play_character_sound(m, CHAR_SOUND_SO_LONGA_BOWSER)
    end
    set_mario_animation(m, MARIO_ANIM_GRAB_BOWSER)

    local stepResult = perform_air_step(m, 0)
    update_air_without_turn(m)
    if stepResult == AIR_STEP_LANDED then
        if should_get_stuck_in_ground(m) ~= 0 then
            queue_rumble_data_mario(m, 5, 80)
            play_sound(SOUND_MARIO_OOOF2, m.marioObj.header.gfx.cameraToObject)
            m.particleFlags = m.particleFlags | PARTICLE_MIST_CIRCLE
            set_mario_action(m, ACT_BUTT_STUCK_IN_GROUND, 0)
        else
            play_mario_heavy_landing_sound(m, SOUND_ACTION_TERRAIN_HEAVY_LANDING)
            if check_fall_damage(m, ACT_HARD_BACKWARD_GROUND_KB) == 0 then
                m.particleFlags = m.particleFlags | PARTICLE_MIST_CIRCLE | PARTICLE_HORIZONTAL_STAR
                -- set facing direction
                -- not part of original Extended Moveset
                m.faceAngle.y = m.intendedYaw
                return set_mario_action(m, ACT_PILEDRIVER_LAND, 0)
            end
        end
    end

    if m.vel.y >= 0 then
        m.angleVel.y = 0
        m.marioObj.header.gfx.angle.y = m.faceAngle.y
    else
        m.angleVel.y = m.angleVel.y + math.abs(m.vel.y) * 0x100
        m.marioObj.header.gfx.angle.y = m.marioObj.header.gfx.angle.y + m.angleVel.y
        m.particleFlags = m.particleFlags | PARTICLE_DUST
    end
    m.actionTimer = m.actionTimer + 1
    return 0
end

function act_piledriver_land(m)
    set_mario_animation(m, MARIO_ANIM_SWINGING_BOWSER)

    local stepResult = perform_ground_step(m)

    if stepResult == GROUND_STEP_LEFT_GROUND then
        m.action = ACT_PILEDRIVER
    end

    -- A debuff so that players can't just bounce up slides.
    if (m.input & INPUT_ABOVE_SLIDE) ~= 0 then
        return set_mario_action(m, ACT_BUTT_SLIDE, 0)
    end

    if (m.input & INPUT_UNKNOWN_10) ~= 0 then
        return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0)
    end

    if m.actionTimer > 2 then return set_mario_action(m, ACT_RELEASING_BOWSER, 0) end

	m.actionTimer = m.actionTimer + 1
end

function wario_before_phys_step(m)
    local hScale = 1.0
    local vScale = 1.0

    -- slower on ground
    if (m.action & ACT_FLAG_MOVING) ~= 0 then
        hScale = hScale * 0.9
    end

    -- fixes the momentum bug
    if (m.action == ACT_HOLD_WATER_JUMP) then
        return
    end

    -- faster holding item
    if m.action == ACT_HOLD_WALKING then
        hScale = hScale * 2
    end

    -- make wario sink
    if (m.action & ACT_FLAG_SWIMMING) ~= 0 then
        if m.action ~= ACT_BACKWARD_WATER_KB and
           m.action ~= ACT_FORWARD_WATER_KB and
           m.action ~= ACT_WATER_PLUNGE then
            m.vel.y = m.vel.y - 3
        end
    end

    m.vel.x = m.vel.x * hScale
    m.vel.z = m.vel.z * hScale
end

function wario_on_set_action(m)
    -- air dash
    if m.action == ACT_MOVE_PUNCHING and m.prevAction == ACT_WARIO_DASH then
        local actionTimer = m.actionTimer
        set_mario_action(m, ACT_WARIO_AIR_DASH, 0)
        m.actionTimer = actionTimer
        vec3f_zero(m.vel)
        return
    end

    -- slow down when dash/conk ends
    if (m.prevAction == ACT_WARIO_DASH) or (m.prevAction == ACT_WARIO_AIR_DASH) or (m.prevAction == ACT_CORKSCREW_CONK) then
        if m.action == ACT_CORKSCREW_CONK then
            m.vel.x = 0
            -- nerf the conk when executed in the air
            if (m.prevAction == ACT_WARIO_DASH) then
                set_mario_y_vel_based_on_fspeed(m, 30 , 0.6)
            elseif (m.prevAction == ACT_WARIO_AIR_DASH) then
                m.vel.y = 60.0
            end
        elseif m.action == ACT_SLIDE_KICK then
            mario_set_forward_vel(m, 40)
            m.vel.y = 30.0
        elseif m.forwardVel > 20 then
            mario_set_forward_vel(m, 20)
        end
    end

    if m.action == ACT_PILEDRIVER then
        if m.vel.y < 50 then m.vel.y = 50 end
    end

    -- patch wario's hold jump for piledriver
    if m.action == ACT_HOLD_JUMP then
        m.action = ACT_WARIO_HOLD_JUMP
    end

    if m.action == ACT_HOLD_FREEFALL then
        m.action = ACT_WARIO_HOLD_FREEFALL
    end

    -- less height on other jumps
    if m.action == ACT_JUMP or
       m.action == ACT_DOUBLE_JUMP or
       m.action == ACT_STEEP_JUMP or
       m.action == ACT_RIDING_SHELL_JUMP or
       m.action == ACT_BACKFLIP or
       m.action == ACT_LONG_JUMP or
       m.action == ACT_SIDE_FLIP then

        m.vel.y = m.vel.y * 0.9

        -- prevent from getting stuck on platform
        if m.marioObj.platform then
            m.pos.y = m.pos.y + 10
        end
    end
end

function wario_update(m)
    local hScale = 1.0
    local e = gStateExtras[m.playerIndex]

    wario_update_spin_input(m)

    -- spin around objects
    if m.action == ACT_HOLD_IDLE or m.action == ACT_HOLD_WALKING then
        if e.spinInput > 30 then
            m.twirlYaw = m.intendedYaw
            if e.spinDirection == 1 then
                m.angleVel.y = 3000
            else
                m.angleVel.y = -3000
            end
            m.intendedMag = 21
            return set_mario_action(m, ACT_WARIO_SPINNING_OBJ, 1)
        end
    end

    -- turn heavy objects into light
    if m.action == ACT_HOLD_HEAVY_IDLE then
        return set_mario_action(m, ACT_HOLD_IDLE, 0)
    end

    -- turn dive into dash
    if m.action == ACT_DIVE and m.prevAction == ACT_WALKING then
        if (m.controller.buttonPressed & B_BUTTON) ~= 0 then
            m.actionTimer = 0
            return set_mario_action(m, ACT_WARIO_DASH, 0)
        end
    end

    -- shake camera
    if m.action == ACT_GROUND_POUND_LAND then
        set_camera_shake_from_point(SHAKE_POS_MEDIUM, m.pos.x, m.pos.y, m.pos.z)
        m.squishTimer = 5
    end

    -- faster ground pound
    if m.action == ACT_GROUND_POUND then
        m.vel.y = m.vel.y * 1.3
    end

    -- decrease player damage
    if m.hurtCounter > e.lastHurtCounter and m.action ~= ACT_LAVA_BOOST then
        m.hurtCounter = math.max(3, m.hurtCounter - 4)
    end
    e.lastHurtCounter = m.hurtCounter

    m.vel.x = m.vel.x * hScale
    m.vel.z = m.vel.z * hScale
end

gEventTable[CT_WARIO] = {
    before_phys_step = wario_before_phys_step,
    on_set_action    = wario_on_set_action,
    update           = wario_update,
}

----------
-- main --
----------

function char_before_phys_step(m)
    if m.action ~= ACT_BUBBLED
    and gEventTable[m.character.type]
    and gEventTable[m.character.type].before_phys_step then
        gEventTable[m.character.type].before_phys_step(m)
    end
end

function char_on_set_action(m)
    if m.action ~= ACT_BUBBLED
    and gEventTable[m.character.type]
    and gEventTable[m.character.type].on_set_action then
        gEventTable[m.character.type].on_set_action(m)
    end
end

function char_update(m)

    if m.action ~= ACT_BUBBLED
    and gEventTable[m.character.type]
    and gEventTable[m.character.type].update then
        gEventTable[m.character.type].update(m)
    end
end

-- shoulder bash interactions
function dash_attacks(m, o, intType)
    if obj_has_behavior_id(o, id_bhvKingBobomb) ~= 0 and o.oAction ~= 0 then
        o.oMoveAngleYaw = m.faceAngle.y
        o.oAction = 4
        o.oVelY = 50
        o.oForwardVel = 20
    end

    if obj_has_behavior_id(o, id_bhvBreakableBoxSmall) ~= 0 then
        o.oMoveAngleYaw = m.faceAngle.y
        o.oVelY = 30
        o.oForwardVel = 40
    end

    if obj_has_behavior_id(o, id_bhvChuckya) ~= 0 then
        o.oMoveAngleYaw = m.faceAngle.y
        o.oAction = 2
        o.oVelY = 30
        o.oForwardVel = 40
    end

    if obj_has_behavior_id(o, id_bhvMrBlizzard) ~= 0 then
        o.oFaceAngleRoll = 0x3000
        o.oMrBlizzardHeldObj = nil
        o.prevObj = o.oMrBlizzardHeldObj
        o.oAction = MR_BLIZZARD_ACT_DEATH
    end

    if obj_has_behavior_id(o, id_bhvHeaveHo) ~= 0 then
        obj_mark_for_deletion(o)
        spawn_triangle_break_particles(30, 138, 3.0, 4)
        spawn_non_sync_object(
            id_bhvBlueCoinJumping,
            E_MODEL_BLUE_COIN,
            o.oPosX, o.oPosY, o.oPosZ,
            function (coin)
                coin.oVelY = math.random(20, 40)
                coin.oForwardVel = 0
            end)
    end

    if (intType & INTERACT_BULLY) ~= 0 then
        o.oVelY = 30
        o.oForwardVel = 50
    end
end

function char_on_interact(m, o, intType)
    local damagableTypes = (INTERACT_BOUNCE_TOP | INTERACT_BOUNCE_TOP2 | INTERACT_HIT_FROM_BELOW | 2097152 | INTERACT_KOOPA |
    INTERACT_BREAKABLE | INTERACT_GRABBABLE | INTERACT_BULLY)

    -- rebound from bash and interact

    if m.action == ACT_WARIO_DASH and (intType & damagableTypes) ~= 0 then
        dash_attacks(m, o, intType)
        
        wario_rebound(m, -40, 30)
        return false
    end

    if m.action == ACT_WARIO_AIR_DASH and (intType & damagableTypes) ~= 0 then
        dash_attacks(m, o, intType)
        
        wario_rebound(m, -40, 15)
        return false
    end
end

function char_on_pvp_attack(a, v)
    if a.action == ACT_WARIO_DASH then
        wario_rebound(a, -40, 30)
    end

    if a.action == ACT_WARIO_AIR_DASH then
        wario_rebound(a, -40, 15)
    end
end

function convert_s16(num)
    local min = -32768
    local max = 32767
    while (num < min) do
        num = max + (num - min)
    end
    while (num > max) do
        num = min + (num - max)
    end
    return num
end

-----------
-- hooks --
-----------


hook_mario_action(ACT_WALL_SLIDE,                 act_wall_slide)
hook_mario_action(ACT_ELEGANT_JUMP,               act_elegant_jump)
hook_mario_action(ACT_WALUIGI_AIR_SWIM,           act_waluigi_air_swim)

hook_mario_action(ACT_WARIO_DASH,                 act_wario_dash,      INT_KICK)
hook_mario_action(ACT_WARIO_AIR_DASH,             act_wario_air_dash,  INT_KICK)
hook_mario_action(ACT_WARIO_DASH_REBOUND,         act_wario_dash_rebound)
hook_mario_action(ACT_CORKSCREW_CONK,             act_corkscrew_conk,  INT_FAST_ATTACK_OR_SHELL)
hook_mario_action(ACT_WARIO_SPINNING_OBJ,         act_wario_spinning_obj)
hook_mario_action(ACT_PILEDRIVER,                 act_piledriver)
hook_mario_action(ACT_PILEDRIVER_LAND,            act_piledriver_land,  INT_GROUND_POUND_OR_TWIRL)
hook_mario_action(ACT_WARIO_HOLD_JUMP,            act_wario_hold_jump)
hook_mario_action(ACT_WARIO_HOLD_FREEFALL,        act_wario_hold_freefall)
