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

function act_roll(mario_index)
    print("rolling!")
    local m = gMarioStates[mario_index]
    local e = gMarioStateExtras[mario_index]

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
            print("rolling -> walking")
            return set_mario_action(mario_index, ACT_WALKING, 0);
        end
    end

    if (m.input & INPUT_B_PRESSED) ~= 0 then
            print("rolling -> rollout")
        return set_jumping_action(mario_index, ACT_FORWARD_ROLLOUT, 0);
    end

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        print("rolling -> long jump")
        return set_jumping_action(mario_index, ACT_LONG_JUMP, 0);
    end

    if (m.controller.buttonPressed & R_TRIG) ~= 0 and m.actionTimer > 0 then
        m.vel.y = 19.0;
        play_mario_sound(mario_index, SOUND_ACTION_TERRAIN_JUMP, 0);

        if e.spareInt >= BOOST_LOCKOUT_TIME then
            e.spareInt = 0;

            if m.forwardVel < MAX_NORMAL_ROLL_SPEED then
                mario_set_forward_vel(mario_index, math.min(m.forwardVel + ROLL_BOOST_GAIN, MAX_NORMAL_ROLL_SPEED));
            end

            m.particleFlags = m.particleFlags | PARTICLE_HORIZONTAL_STAR;

            -- ! playing this after the call to play_mario_sound seems to matter in making this sound play
            ------ TODO: play_sound(SOUND_ACTION_SPIN, m.marioObj->header.gfx.cameraToObject);
        end

        print("rolling -> rolling air")
        return set_mario_action(mario_index, ACT_ROLL_AIR, m.actionArg);
    end

    set_mario_animation(mario_index, MARIO_ANIM_FORWARD_SPINNING);

    if update_sliding(mario_index, 10.0) ~= 0 then
        print("rolling -> crouch slide")
        return set_mario_action(mario_index, ACT_CROUCH_SLIDE, 0);
    end

    common_slide_action(mario_index, ACT_CROUCH_SLIDE, ACT_ROLL_AIR, MARIO_ANIM_FORWARD_SPINNING);

    e.spareFloat = e.spareFloat + (0x80 * m.forwardVel);
    if e.spareFloat > 0x10000 then
        e.spareFloat = e.spareFloat - 0x10000;
    end
    set_anim_to_frame(mario_index, 10 * e.spareFloat / 0x10000);

    e.spareInt = e.spareInt + 1;

    m.actionTimer = m.actionTimer + 1;

    return 0;
end

function act_roll_air(mario_index)
    print("rolling air!")
    return set_mario_action(mario_index, ACT_DIVE, 0);
end

function update()
    --print("----------")
    --print(gMarioStates)
    --print(gMarioStates[0])
    --print(gMarioStates[0].pos)
    --print(gMarioStates[0].pos.x)
    --print(gMarioStates[0].pos.y)
    --print(gMarioStates[0].pos.z)
end

function mario_update(mario_index)
    local m = gMarioStates[mario_index]
    -- if m.vel.y > 0 then
        -- m.vel.y = m.vel.y + 2
    -- end

    if m.action == ACT_DIVE_SLIDE then
        set_mario_action(mario_index, ACT_ROLL, 0);
    end
end

function override_mario_action(mario_index, action)
    return (action == ACT_ROLL) or (action == ACT_ROLL_AIR)
end

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_mario_action(ACT_ROLL, act_roll)
hook_mario_action(ACT_ROLL_AIR, act_roll_air)
