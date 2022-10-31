-- name: Character Movesets
-- incompatible: moveset
-- description: Gives each character unique abilities and stats.\n\nContributors: djoslin0, TheGag96, Draco, steven.

ANGLE_QUEUE_SIZE = 9
SPIN_TIMER_SUCCESSFUL_INPUT = 4

gEventTable = {}

gStateExtras = {}
for i = 0, (MAX_PLAYERS - 1) do
    gStateExtras[i] = {}
    local m = gMarioStates[i]
    local e = gStateExtras[i]
    e.prevPos = {}
    e.prevPos.x = 0
    e.prevPos.y = 0
    e.prevPos.z = 0
    e.angleDeltaQueue = {}
    for j = 0, (ANGLE_QUEUE_SIZE - 1) do e.angleDeltaQueue[j] = 0 end
    e.lastAction = m.action
    e.animFrame = 0
    e.scuttle = 0
    e.averageForwardVel = 0
    e.boostTimer = 0
    e.rotAngle = 0
    e.lastHurtCounter = 0
    e.stickLastAngle = 0
    e.spinDirection = 0
    e.spinBufferTimer = 0
    e.spinInput = 0
    e.lastIntendedMag = 0
end

-----------
-- luigi --
-----------

ACT_SPIN_POUND_LAND = allocate_mario_action(ACT_GROUP_STATIONARY | ACT_FLAG_STATIONARY | ACT_FLAG_ATTACKING)
ACT_SPIN_POUND      = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ATTACKING)

function act_spin_pound(m)
    local e = gStateExtras[m.playerIndex]
    if m.actionTimer == 0 then
        m.actionState = m.actionArg
    end

    local spinDirFactor = 1  -- negative for clockwise, positive for counter-clockwise
    if m.actionState == 1 then spinDirFactor = -1 end

    set_mario_animation(m, MARIO_ANIM_TWIRL)

    m.particleFlags = m.particleFlags | PARTICLE_DUST

    if (m.controller.buttonDown & Z_TRIG) == 0 then
        set_mario_action(m, ACT_TWIRLING, 5)
    end

    local stepResult = perform_air_step(m, 0)
    if stepResult == AIR_STEP_LANDED then
        if should_get_stuck_in_ground(m) ~= 0 then
            queue_rumble_data_mario(m, 5, 80)
            play_character_sound(m, CHAR_SOUND_OOOF2)
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

    -- set facing direction
    -- not part of original Extended Moveset
    local yawDiff = m.faceAngle.y - m.intendedYaw
    e.rotAngle = e.rotAngle + yawDiff
    m.faceAngle.y = m.intendedYaw

    e.rotAngle = e.rotAngle + 0x3053
    if e.rotAngle >  0x10000 then e.rotAngle = e.rotAngle - 0x10000 end
    if e.rotAngle < -0x10000 then e.rotAngle = e.rotAngle + 0x10000 end
    m.marioObj.header.gfx.angle.y = m.marioObj.header.gfx.angle.y + e.rotAngle * spinDirFactor
    m.marioBodyState.handState = MARIO_HAND_OPEN

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

function luigi_before_phys_step(m)
    local e = gStateExtras[m.playerIndex]

    local floorClass = mario_get_floor_class(m)
    local hScale = 1.0
    local vScale = 1.0

    -- faster swimming
    if (m.action & ACT_FLAG_SWIMMING) ~= 0 then
        if m.action ~= ACT_BACKWARD_WATER_KB and m.action ~= ACT_FORWARD_WATER_KB then
            hScale = hScale * 1.5
            if m.action ~= ACT_WATER_PLUNGE then
                vScale = vScale * 1.5
            end
        end
    end

    -- slower holding item
    if m.heldObj ~= nil then
        m.vel.y = m.vel.y - 1.0
        hScale = hScale * 0.9
        if (m.action & ACT_FLAG_AIR) ~= 0 then
            hScale = hScale * 0.9
        end
    end

    -- acceleration
    if (m.action == ACT_WALKING) then
        if (floorClass == 19 or floorClass == 20) then
            hScale = -(m.forwardVel / 64) + 1.5
        else
            hScale = (m.forwardVel / 64) + 0.5
        end
    end

    -- friction
    if (m.action == ACT_BRAKING or m.action == ACT_TURNING_AROUND) then
        if (floorClass == 19 or floorClass == 20) then
            m.forwardVel = m.forwardVel - 3
        elseif (floorClass == 21) then
            hScale = hScale * 1.5
            m.forwardVel = m.forwardVel + (hScale * 2)
        else
            hScale = hScale * 1.4
            m.forwardVel = m.forwardVel + hScale
        end
        if (m.forwardVel < 0) then
            m.forwardVel = 0
        end
    end

    m.vel.x = m.vel.x * hScale
    m.vel.y = m.vel.y * vScale
    m.vel.z = m.vel.z * hScale
end

function luigi_on_set_action(m)
    local e = gStateExtras[m.playerIndex]

    -- extra height to the backflip
    if m.action == ACT_BACKFLIP then
        m.vel.y = m.vel.y + 18

    -- nerf wall kicks
    elseif m.action == ACT_WALL_KICK_AIR and m.prevAction ~= ACT_HOLDING_POLE and m.prevAction ~= ACT_CLIMBING_POLE then
        if m.vel.y > 56 then m.vel.y = 56 end
        return

    -- turn dive into kick when holding jump
    elseif m.action == ACT_DIVE and (m.controller.buttonDown & A_BUTTON) ~= 0 and e.scuttle > 0 then
        return set_mario_action(m, ACT_JUMP_KICK, 0)

    -- extra height on jumps
    elseif m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_TRIPLE_JUMP or m.action == ACT_SPECIAL_TRIPLE_JUMP or m.action == ACT_STEEP_JUMP or m.action == ACT_SIDE_FLIP or m.action == ACT_RIDING_SHELL_JUMP then
        m.vel.y = m.vel.y + 6

    end

    e.lastAction = action
end

function luigi_update(m)
    local e = gStateExtras[m.playerIndex]

    -- increase player damage
    if (m.hurtCounter > e.lastHurtCounter) then
        m.hurtCounter = m.hurtCounter + 4
    end
    e.lastHurtCounter = m.hurtCounter

    -- air scuttle
    e.scuttle = 0
    local shouldScuttle = (m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_HOLD_JUMP) and ((m.controller.buttonDown & A_BUTTON) ~= 0 and m.vel.y < -5)
    if shouldScuttle then
        -- prevent wing flutter from glitching out while scuttling
        if m.marioBodyState.wingFlutter == 1 then
            m.vel.y = m.vel.y + 1
        else
            m.vel.y = m.vel.y + 3
            if m.action == ACT_HOLD_JUMP then
                set_mario_animation(m, MARIO_ANIM_RUN_WITH_LIGHT_OBJ)
            else
                set_mario_animation(m, MARIO_ANIM_RUNNING_UNUSED)
            end
            set_anim_to_frame(m, e.animFrame)
            e.animFrame = e.animFrame + 13
            if e.animFrame >= m.marioObj.header.gfx.animInfo.curAnim.loopEnd then
                e.animFrame = e.animFrame - m.marioObj.header.gfx.animInfo.curAnim.loopEnd
            end
            e.scuttle = 1
        end
    end

    -- twirl pound
    if m.action == ACT_TWIRLING and (m.controller.buttonDown & Z_TRIG) ~= 0 then
        set_mario_action(m, ACT_SPIN_POUND, 0)
    end

    -- backflip turns into twirl
    if m.action == ACT_BACKFLIP and m.marioObj.header.gfx.animInfo.animFrame > 18 then
        m.angleVel.y = 0x1800
        set_mario_action(m, ACT_TWIRLING, 1)
    end
end

gEventTable[CT_LUIGI] = {
    before_phys_step = luigi_before_phys_step,
    on_set_action    = luigi_on_set_action,
    update           = luigi_update,
}

-----------
-- toad --
-----------

function toad_before_phys_step(m)
    local e = gStateExtras[m.playerIndex]

    local hScale = 1.0
    local vScale = 1.0

    -- faster ground movement
    if (m.action & ACT_FLAG_MOVING) ~= 0 then
        hScale = hScale * 1.19
    end

    -- slower holding item
    if m.heldObj ~= nil then
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
        if m.marioObj.platform ~= nil then
            m.pos.y = m.pos.y + 10
        end
    elseif m.action == ACT_SIDE_FLIP then
        m.vel.y = m.vel.y * 0.86

        -- prevent from getting stuck on platform
        if m.marioObj.platform ~= nil then
            m.pos.y = m.pos.y + 10
        end
    end

    e.lastAction = action
end

function toad_update(m)
    local e = gStateExtras[m.playerIndex]

    -- track average forward velocity
    if e.averageForwardVel > m.forwardVel then
        e.averageForwardVel = e.averageForwardVel * 0.93 + m.forwardVel * 0.07
    else
        e.averageForwardVel = m.forwardVel
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

ACT_WALL_SLIDE = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_MOVING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)

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

function waluigi_before_phys_step(m)
    local e = gStateExtras[m.playerIndex]

    local hScale = 1.0
    local vScale = 1.0

    -- faster ground movement
    if (m.action & ACT_FLAG_MOVING) ~= 0 then
        hScale = hScale * 1.085
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
        m.vel.y = m.vel.y * 0.91
    end

    e.lastAction = action
end

function waluigi_update(m)
    local e = gStateExtras[m.playerIndex]

    -- increase player damage
    if m.hurtCounter > e.lastHurtCounter then
        m.hurtCounter = m.hurtCounter * 2
    end
    e.lastHurtCounter = m.hurtCounter

    -- double jump
    if m.action == ACT_DOUBLE_JUMP and m.actionTimer > 0 and (m.controller.buttonPressed & A_BUTTON) ~= 0 then
        set_mario_action(m, ACT_TRIPLE_JUMP, 0)
        m.vel.y = m.vel.y * 0.8
    end
    if m.action == ACT_DOUBLE_JUMP then
        m.actionTimer = m.actionTimer + 1
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

ACT_WARIO_DASH         = allocate_mario_action(ACT_GROUP_MOVING | ACT_FLAG_MOVING | ACT_FLAG_ATTACKING)
ACT_WARIO_AIR_DASH     = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ATTACKING)
ACT_PILEDRIVER         = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ATTACKING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_WARIO_HOLD_JUMP    = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_CORKSCREW_CONK     = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ATTACKING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_WARIO_SPINNING_OBJ = allocate_mario_action(ACT_GROUP_OBJECT | ACT_FLAG_STATIONARY)

function act_corkscrew_conk(m)
    local e = gStateExtras[m.playerIndex]

    -- visuals
    m.particleFlags = m.particleFlags | PARTICLE_DUST

    -- physics
    common_air_action_step(m, ACT_JUMP_LAND, MARIO_ANIM_FORWARD_SPINNING, AIR_STEP_NONE)

    -- animation
    set_anim_to_frame(m, e.animFrame)
    if e.animFrame >= m.marioObj.header.gfx.animInfo.curAnim.loopEnd then
        e.animFrame = e.animFrame - m.marioObj.header.gfx.animInfo.curAnim.loopEnd
    end

    -- fast ground pound out of it
    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        local rc = set_mario_action(m, ACT_GROUND_POUND, 0)
        m.actionTimer = 5
        return rc
    end

    -- timers
    m.actionTimer = m.actionTimer + 1
    e.animFrame = e.animFrame + 1

    return 0
end

function act_wario_dash(m)
    local e = gStateExtras[m.playerIndex]

    -- when hitting wall, knock Wario backwards and thrust him upwards
    if m.actionArg == 99 then
        m.actionTimer = m.actionTimer + 1
        if m.actionTimer > 2 then
            mario_set_forward_vel(m, -30)
            m.vel.y = 40
            return set_mario_action(m, ACT_FREEFALL, 0)
        end
        return 0
    end

    -- make sound
    if m.actionTimer == 0 then
        m.actionState = m.actionArg
        play_character_sound(m, CHAR_SOUND_YAHOO)
    end

    -- walk once dash is up
    if m.actionTimer > 15 then
        return set_mario_action(m, ACT_WALKING, 0)
    end

    -- slide and set animation
    common_slide_action(m, ACT_DIVE, ACT_MOVE_PUNCHING, MARIO_ANIM_FIRST_PUNCH)
    set_anim_to_frame(m, 25)

    -- set dash speed
    local speed = 60
    if m.actionTimer > 8 then
        speed = speed - (m.actionTimer - 8)
    end
    mario_set_forward_vel(m, speed)

    -- corkscrew conk
    if (m.input & INPUT_A_PRESSED) ~= 0 then
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

function act_wario_air_dash(m)
    local e = gStateExtras[m.playerIndex]

    -- when hitting wall, knock Wario backwards and thrust him upwards
    if m.actionArg == 99 then
        m.actionTimer = m.actionTimer + 1
        if m.actionTimer > 2 then
            m.particleFlags = m.particleFlags | PARTICLE_VERTICAL_STAR
            mario_set_forward_vel(m, -30)
            m.vel.y = 40
            return set_mario_action(m, ACT_FREEFALL, 0)
        end
        return 0
    end

    -- fall once dash is up
    if m.actionTimer > 15 then
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    -- slide and set animation
    common_air_action_step(m, ACT_JUMP_LAND, MARIO_ANIM_FIRST_PUNCH, AIR_STEP_NONE)
    set_anim_to_frame(m, 25)

    -- set dash speed
    local speed = 60
    if m.actionTimer > 8 then
        speed = speed - (m.actionTimer - 8)
    end
    mario_set_forward_vel(m, speed)

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
        return set_mario_action(m, ACT_HOLD_IDLE, 0)
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

    stationary_ground_step(m)

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
            for i = 0, (ANGLE_QUEUE_SIZE - 1) do
                e.angleDeltaQueue[i] = 0
            end
            e.spinDirection = newDirection
        else
            for i = (ANGLE_QUEUE_SIZE - 1), 1, -1 do
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

-- patch wario's hold jump for piledriver
function act_wario_hold_jump(m)
    if (m.marioObj.oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) ~= 0 then
        return drop_and_set_mario_action(m, ACT_FREEFALL, 0)
    end

    if (m.input & INPUT_B_PRESSED) ~= 0 and (m.heldObj ~= nil and (m.heldObj.oInteractionSubtype & INT_SUBTYPE_HOLDABLE_NPC) ~= nil) then
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

function act_piledriver(m)
    local e = gStateExtras[m.playerIndex]
    if m.actionTimer == 0 then
        play_sound(SOUND_ACTION_SPIN, m.marioObj.header.gfx.cameraToObject)
        play_character_sound(m, CHAR_SOUND_SO_LONGA_BOWSER)
    end
    set_mario_animation(m, MARIO_ANIM_HOLDING_BOWSER)
    local stepResult = perform_air_step(m, 0)
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
                local yawDiff = m.faceAngle.y - m.intendedYaw
                e.rotAngle = e.rotAngle + yawDiff
                m.faceAngle.y = m.intendedYaw
                return set_mario_action(m, ACT_RELEASING_BOWSER, 0)
            end
        end
    end
    m.vel.y = -32
    mario_set_forward_vel(m, 0)
    m.faceAngle.y = m.faceAngle.y + 0x3000
    m.actionTimer = m.actionTimer + 1
    return 0
end

function wario_before_phys_step(m)
    local hScale = 1.0

    -- slower on ground
    if m.action == ACT_WALKING then
        hScale = hScale * 0.9
    end

    -- make wario sink
    if (m.action & ACT_FLAG_SWIMMING) ~= 0 then
        if m.action ~= ACT_BACKWARD_WATER_KB and
           m.action ~= ACT_FORWARD_WATER_KB and
           m.action ~= ACT_WATER_PLUNGE then
            m.vel.y = m.vel.y - 3
        end
    end

    -- fixes the momentum bug
    if (m.action & ACT_HOLD_WATER_JUMP) then
        return
    end

    -- faster holding item
    if m.heldObj ~= nil then
        m.vel.y = m.vel.y - 1
        hScale = hScale * 1.3
        if (m.action & ACT_FLAG_AIR) ~= 0 then
            hScale = hScale * 1.3
        end
    end

    m.vel.x = m.vel.x * hScale
    m.vel.z = m.vel.z * hScale
end

function wario_on_set_action(m)
    local e = gStateExtras[m.playerIndex]

    -- air dash
    if m.action == ACT_MOVE_PUNCHING and m.prevAction == ACT_WARIO_DASH then
        local actionTimer = m.actionTimer
        set_mario_action(m, ACT_WARIO_AIR_DASH, 0)
        m.actionTimer = actionTimer
        m.vel.x = 0
        m.vel.y = 0
        m.vel.z = 0
        return
    end

    -- slow down when dash/conk ends
    if (m.prevAction == ACT_WARIO_DASH) or (m.prevAction == ACT_WARIO_AIR_DASH) or (m.prevAction == ACT_CORKSCREW_CONK) then
        if m.action == ACT_CORKSCREW_CONK then
            mario_set_forward_vel(m, 60)
            m.vel.x = 0
            -- nerf the conk when executed in the air
            if (m.prevAction == ACT_WARIO_DASH) then
                m.vel.y = 70.0
            elseif (m.prevAction == ACT_WARIO_AIR_DASH) then
                m.vel.y = 60.0
            end
            m.vel.z = 0
        elseif m.action == ACT_SLIDE_KICK then
            mario_set_forward_vel(m, 70)
            m.vel.x = 0
            m.vel.y = 30.0
            m.vel.z = 0
        elseif m.forwardVel > 20 then
            mario_set_forward_vel(m, 20)
        end
    end

    -- when hitting a wall which dashing, have one more single frame of dash
    if m.action == ACT_GROUND_BONK and m.prevAction == ACT_WARIO_DASH then
        set_mario_action(m, ACT_WARIO_DASH, 99)
        mario_set_forward_vel(m, 1)
        m.vel.x = 0
        m.vel.y = 0
        m.vel.z = 0
    end

    -- when hitting a wall which dashing, have one more single frame of dash
    if m.action == ACT_AIR_HIT_WALL and m.prevAction == ACT_WARIO_AIR_DASH then
        set_mario_action(m, ACT_WARIO_AIR_DASH, 99)
        mario_set_forward_vel(m, 1)
        m.vel.x = 0
        m.vel.y = 0
        m.vel.z = 0
    end

    -- more height on triple jump
    if m.action == ACT_TRIPLE_JUMP or m.action == ACT_SPECIAL_TRIPLE_JUMP then
        m.vel.y = m.vel.y * 1.15
    end
    
    -- patch wario's hold jump for piledriver
    if m.action == ACT_HOLD_JUMP then
        return set_mario_action(m, ACT_WARIO_HOLD_JUMP, 0)
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
        if m.marioObj.platform ~= nil then
            m.pos.y = m.pos.y + 10
        end
    end
    e.lastAction = action
end

function wario_update(m)
    local hScale = 1.0
    local e = gStateExtras[m.playerIndex]

    wario_update_spin_input(m)

    -- spin around objects
    if m.action == ACT_HOLD_IDLE or m.action == ACT_HOLD_WALKING then
        if e.spinInput ~= 0 then
            m.twirlYaw = m.intendedYaw
            if e.spinDirection == 1 then
                m.angleVel.y = 1500
            else
                m.angleVel.y = -1500
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

    e.prevPos.x = m.pos.x
    e.prevPos.y = m.pos.y
    e.prevPos.z = m.pos.z
end

gEventTable[CT_WARIO] = {
    before_phys_step = wario_before_phys_step,
    on_set_action    = wario_on_set_action,
    update           = wario_update,
}

----------
-- main --
----------

function mario_before_phys_step(m)
    if m.action == ACT_BUBBLED then
        return
    end

    if gEventTable[m.character.type] == nil then
        return
    end

    if gEventTable[m.character.type].before_phys_step == nil then
        return
    end

    gEventTable[m.character.type].before_phys_step(m)
end

function mario_on_set_action(m)
    if m.action == ACT_BUBBLED then
        return
    end

    if gEventTable[m.character.type] == nil then
        return
    end

    if gEventTable[m.character.type].on_set_action == nil then
        return
    end

    gEventTable[m.character.type].on_set_action(m)
end

function mario_update(m)
    if m.action == ACT_BUBBLED then
        return
    end

    if gEventTable[m.character.type] == nil then
        return
    end

    if gEventTable[m.character.type].update == nil then
        return
    end

    gEventTable[m.character.type].update(m)
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

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ON_SET_MARIO_ACTION, mario_on_set_action)
hook_event(HOOK_BEFORE_PHYS_STEP, mario_before_phys_step)

hook_mario_action(ACT_WALL_SLIDE,         { every_frame = act_wall_slide })
hook_mario_action(ACT_SPIN_POUND,         { every_frame = act_spin_pound },      INT_GROUND_POUND_OR_TWIRL)
hook_mario_action(ACT_SPIN_POUND_LAND,    { every_frame = act_spin_pound_land }, INT_GROUND_POUND_OR_TWIRL)
hook_mario_action(ACT_WARIO_DASH,         { every_frame = act_wario_dash },      INT_KICK)
hook_mario_action(ACT_WARIO_AIR_DASH,     { every_frame = act_wario_air_dash },  INT_KICK)
hook_mario_action(ACT_CORKSCREW_CONK,     { every_frame = act_corkscrew_conk },  INT_FAST_ATTACK_OR_SHELL)
hook_mario_action(ACT_WARIO_SPINNING_OBJ, { every_frame = act_wario_spinning_obj })
hook_mario_action(ACT_PILEDRIVER,         { every_frame = act_piledriver})
hook_mario_action(ACT_WARIO_HOLD_JUMP,    { every_frame = act_wario_hold_jump})
