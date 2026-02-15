require "anims/mario"

ACT_HANDSTAND_MOVING           = allocate_mario_action(ACT_GROUP_MOVING | ACT_FLAG_MOVING)
ACT_HANDSTAND_IDLE             = allocate_mario_action(ACT_GROUP_STATIONARY | ACT_FLAG_STATIONARY | ACT_FLAG_IDLE)
ACT_HANDSTAND_JUMP             = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
ACT_HANDSTAND_JUMP_LAND        = allocate_mario_action(ACT_GROUP_STATIONARY | ACT_FLAG_STATIONARY)
ACT_HANDSTAND_SECOND_JUMP_LAND = allocate_mario_action(ACT_GROUP_STATIONARY | ACT_FLAG_STATIONARY)

function act_handstand_idle(m)
    if (m.quicksandDepth > 30.0) then
        return drop_and_set_mario_action(m, ACT_IN_QUICKSAND, 0)
    end

    if (m.input & INPUT_NONZERO_ANALOG) ~= 0 then
        return set_mario_action(m, ACT_HANDSTAND_MOVING, 0)
    end

	if (m.input & INPUT_A_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_HANDSTAND_JUMP, 1)
    end

    if (m.input & INPUT_Z_DOWN) == 0 then
        return set_mario_action(m, ACT_STOP_CROUCHING, 0)
    end

    if (m.input & INPUT_ABOVE_SLIDE) ~= 0 then
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0)
    end

    stationary_ground_step(m)
    play_custom_anim(m, "MARIO_ANIM_HANDSTAND_IDLE")
    return false
end

function act_handstand_jump(m)
	local animation = MARIO_ANIM_DOUBLE_JUMP_RISE
	local landAction = ACT_HANDSTAND_JUMP_LAND
	local voiceline = CHAR_SOUND_YAH_WAH_HOO

	if m.actionArg == 0 then
        smlua_anim_util_set_animation(m.marioObj, "MARIO_ANIM_HANDSTAND_JUMP_1")
	elseif m.actionArg == 1 then
	    landAction = ACT_HANDSTAND_SECOND_JUMP_LAND
	    voiceline = CHAR_SOUND_HOOHOO
        smlua_anim_util_set_animation(m.marioObj, "MARIO_ANIM_HANDSTAND_JUMP_2")
	elseif m.actionArg == 2 then
	    animation = MARIO_ANIM_FORWARD_SPINNING
	    landAction = ACT_TRIPLE_JUMP_LAND
	    voiceline = CHAR_SOUND_YAHOO_WAHA_YIPPEE
		play_flip_sounds(m, 4, 4, 4)
    end

    if m.actionTimer == 0 then
        play_character_sound(m, voiceline)
        m.faceAngle.y = m.intendedYaw
    end

    local stepResult = common_air_action_step(m, ACT_HANDSTAND_JUMP_LAND, animation,
                                              AIR_STEP_CHECK_LEDGE_GRAB | AIR_STEP_CHECK_HANG)

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_GROUND_POUND, 0)
    end

    if stepResult == AIR_STEP_LANDED then
        if should_get_stuck_in_ground(m) ~= 0 then
            queue_rumble_data_mario(m, 5, 80)
            play_sound(SOUND_MARIO_OOOF2, m.marioObj.header.gfx.cameraToObject)
            m.particleFlags = m.particleFlags | PARTICLE_MIST_CIRCLE
            set_mario_action(m, ACT_FEET_STUCK_IN_GROUND, 0)
        else
            play_sound(SOUND_ACTION_TERRAIN_LANDING, m.marioObj.header.gfx.cameraToObject)
            set_mario_action(m, landAction, 0)
        end
    end

	if m.forwardVel > 16 then mario_set_forward_vel(m, 16) end

    m.actionTimer = m.actionTimer + 1
    return 0
end

function act_handstand_jump_land(m)
    landing_step(m, CHAR_ANIM_LAND_FROM_DOUBLE_JUMP, ACT_HANDSTAND_IDLE)

    if (m.input & INPUT_ABOVE_SLIDE) ~= 0 then
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0)
    end

    smlua_anim_util_set_animation(m.marioObj, "MARIO_ANIM_HANDSTAND_LAND")
	if (m.input & INPUT_A_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_HANDSTAND_JUMP, 1)
    end

    return false
end

function act_handstand_second_jump_land(m)
    landing_step(m, CHAR_ANIM_LAND_FROM_DOUBLE_JUMP, ACT_IDLE)

    if (m.input & INPUT_ABOVE_SLIDE) ~= 0 then
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0)
    end

	if (m.input & INPUT_A_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_HANDSTAND_JUMP, 2)
    end

    return false
end

function act_handstand_moving(m)
    if (should_begin_sliding(m)) ~= 0 then
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0)
    end

    if (m.input & INPUT_FIRST_PERSON) ~= 0 then
        return set_mario_action(m, ACT_STOP_CROUCHING, 0)
    end

    if (m.input & INPUT_ZERO_MOVEMENT) ~= 0 then
        return set_mario_action(m, ACT_HANDSTAND_IDLE, 0)
    end

    if (m.input & INPUT_Z_DOWN) == 0 then
        return set_mario_action(m, ACT_STOP_CROUCHING, 0)
    end

	if (m.input & INPUT_A_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_HANDSTAND_JUMP, 1)
    end

    m.intendedMag = m.intendedMag * 0.3

    update_walking_speed(m)

    local stepResult = perform_ground_step(m)

    if stepResult == GROUND_STEP_LEFT_GROUND then
        set_mario_action(m, ACT_FREEFALL, 0)

    elseif stepResult ==  GROUND_STEP_HIT_WALL then
        if (m.forwardVel > 10.0) then
            mario_set_forward_vel(m, 10.0)
        end

    elseif stepResult == GROUND_STEP_NONE then
        align_with_floor(m)
    end

    play_custom_anim(m, "MARIO_ANIM_HANDSTAND_WALK", m.intendedMag * 0x5000)
    play_step_sound(m, 20, 40)
    return false
end

function mario_on_set_action(m)
    if m.action == ACT_HANDSTAND_JUMP then
        if m.actionArg == 0 then
            m.vel.y = 50
        elseif m.actionArg == 1 then
            m.vel.y = 70
        elseif m.actionArg == 2 then
            m.vel.y = 90
        end
    end

    --[[
    if m.action == ACT_JUMP and m.prevAction == ACT_CRAWLING then
        set_mario_action(m, ACT_HANDSTAND_JUMP, 0)
    end
    ]]

    if m.action == ACT_JUMP and m.prevAction == ACT_CRAWLING then
        set_mario_action(m, ACT_HANDSTAND_JUMP, 0)
    end
end

hook_mario_action(ACT_HANDSTAND_IDLE,             act_handstand_idle)
hook_mario_action(ACT_HANDSTAND_MOVING,           act_handstand_moving)
hook_mario_action(ACT_HANDSTAND_JUMP,             act_handstand_jump)
hook_mario_action(ACT_HANDSTAND_JUMP_LAND,        act_handstand_jump_land)
hook_mario_action(ACT_HANDSTAND_SECOND_JUMP_LAND, act_handstand_second_jump_land)

return {
    { HOOK_ON_SET_MARIO_ACTION, mario_on_set_action }
}