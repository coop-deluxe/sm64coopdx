require "anims/luigi"

ACT_SPIN_POUND_LAND = allocate_mario_action(ACT_GROUP_STATIONARY | ACT_FLAG_STATIONARY | ACT_FLAG_ATTACKING)
ACT_SPIN_POUND      = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ATTACKING)

function act_spin_pound(m)
    if m.actionTimer == 0 then
        m.actionState = m.actionArg
    end

    local spinDirFactor = m.actionState == 1 and -1 or 1  -- negative for clockwise, positive for counter-clockwise

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
    m.angleVel.y = m.angleVel.y + yawDiff
    m.faceAngle.y = m.intendedYaw

    m.angleVel.y = m.angleVel.y + 0x3053
    if m.angleVel.y >  0x10000 then m.angleVel.y = m.angleVel.y - 0x10000 end
    if m.angleVel.y < -0x10000 then m.angleVel.y = m.angleVel.y + 0x10000 end
    m.marioObj.header.gfx.angle.y = m.marioObj.header.gfx.angle.y + m.angleVel.y * spinDirFactor
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
    if m.heldObj then
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
    local e = gCharacterStates[m.playerIndex].luigi

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
end

function luigi_update(m)
    local e = gCharacterStates[m.playerIndex].luigi

    -- increase player damage
    if (m.hurtCounter > e.lastHurtCounter) then
        m.hurtCounter = m.hurtCounter + 4
    end
    e.lastHurtCounter = m.hurtCounter

    -- air scuttle
    local shouldScuttle = (m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_HOLD_JUMP) and ((m.controller.buttonDown & A_BUTTON) ~= 0 and m.vel.y < -5)
    if shouldScuttle then
        -- prevent wing flutter from glitching out while scuttling
        if m.marioBodyState.wingFlutter == 1 then
            m.vel.y = m.vel.y + 1
        else
            m.vel.y = m.vel.y + 3
            if m.action == ACT_HOLD_JUMP then
                play_custom_anim(m, "LUIGI_ANIM_FLUTTER_HOLD")
            else
                play_custom_anim(m, "LUIGI_ANIM_FLUTTER")
            end
            set_anim_to_frame(m, e.scuttle - 1)
            e.scuttle = e.scuttle + 3
            if e.scuttle >= m.marioObj.header.gfx.animInfo.curAnim.loopEnd + 1 then
                e.scuttle = e.scuttle - m.marioObj.header.gfx.animInfo.curAnim.loopEnd
            end
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

hook_mario_action(ACT_SPIN_POUND,      act_spin_pound,      INT_GROUND_POUND_OR_TWIRL)
hook_mario_action(ACT_SPIN_POUND_LAND, act_spin_pound_land, INT_GROUND_POUND_OR_TWIRL)

return {
    { HOOK_MARIO_UPDATE, luigi_update },
    { HOOK_BEFORE_PHYS_STEP, luigi_before_phys_step },
    { HOOK_ON_SET_MARIO_ACTION, luigi_on_set_action }
}