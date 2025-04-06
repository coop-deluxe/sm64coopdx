if not _G.charSelectExists then return end

ANGLE_QUEUE_SIZE = 9
SPIN_TIMER_SUCCESSFUL_INPUT = 4

gEventTable = {}
gCharSelectEventTable = {}

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
    e.animArg = 0
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
    e.swims = 0
    -- birdo
    e.spitTimer = 0
    e.framesSinceShoot = 255
    e.flameCharge = 0
end

local princessFloatActs = {
    [ACT_JUMP] = true,
    [ACT_DOUBLE_JUMP] = true,
    [ACT_TRIPLE_JUMP] = true,
    [ACT_LONG_JUMP] = true,
    [ACT_BACKFLIP] = true,
    [ACT_SIDE_FLIP] = true,
    [ACT_WALL_KICK_AIR] = true,
}

local function play_custom_anim(m, name, accel)
    if accel == nil then
        accel = 0x10000
    end

    m.marioObj.header.gfx.animInfo.animAccel = accel

    if (smlua_anim_util_get_current_animation_name(m.marioObj) ~= name or m.marioObj.header.gfx.animInfo.animID ~= -1) then
        m.marioObj.header.gfx.animInfo.animFrame = 1
        set_anim_to_frame(m, 0)
    end

    -- jank may occur without this line
    m.marioObj.header.gfx.animInfo.animID = -1

    smlua_anim_util_set_animation(m.marioObj, name)
end

local SOUND_SPIT = audio_sample_load("spit.ogg") -- Load audio sample

-----------------------
-- Toadette Movement --
-----------------------

function toadette_before_phys_step(m)
    local e = gStateExtras[m.playerIndex]

    local hScale = 1.0
    local vScale = 1.0

    -- faster ground movement
    if (m.action & ACT_FLAG_MOVING) ~= 0 then
        hScale = hScale * 1.05
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

function toadette_on_set_action(m)
    local e = gStateExtras[m.playerIndex]

    -- wall kick height based on how fast toadette is going
    if m.action == ACT_WALL_KICK_AIR and m.prevAction ~= ACT_HOLDING_POLE and m.prevAction ~= ACT_CLIMBING_POLE then
        m.vel.y = m.vel.y * 0.8
        m.vel.y = m.vel.y + e.averageForwardVel * 0.8
        return
    end

    -- more distance on dive and long jump
    if m.action == ACT_DIVE or m.action == ACT_LONG_JUMP then
        m.forwardVel = m.forwardVel * 1
    end

    -- less height on jumps
    if m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_TRIPLE_JUMP or m.action == ACT_SPECIAL_TRIPLE_JUMP or m.action == ACT_STEEP_JUMP or m.action == ACT_RIDING_SHELL_JUMP or m.action == ACT_BACKFLIP or m.action == ACT_WALL_KICK_AIR or m.action == ACT_LONG_JUMP then
        m.vel.y = m.vel.y * 1

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

function toadette_update(m)
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
        m.marioObj.header.gfx.animInfo.animAccel = 32768 * 4
        if m.actionTimer < 10 then
            m.actionTimer = m.actionTimer + 1
        end
    end

    -- Floaty
    if m.vel.y < 0 and (m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_TRIPLE_JUMP or m.action == ACT_HOLD_JUMP) then
        m.vel.y = m.vel.y + 0.9
    end
end

-----------------
-- Peach Float --
-----------------

ACT_PEACH_FLOAT = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_MOVING)

--- @param m MarioState
local function act_peach_float(m)
    -- apply movement when using action
    common_air_action_step(m, ACT_JUMP_LAND, CHAR_ANIM_BEND_KNESS_RIDING_SHELL, AIR_STEP_NONE)

    -- setup when action starts (horizontal speed and voiceline)
    if m.actionTimer == 0 then
        play_character_sound(m, CHAR_SOUND_HELLO)
    end


    if m.forwardVel > 20 then
        m.forwardVel = m.forwardVel - 0.5
    end

    -- Slowly decend
    m.vel.y = -1
    set_mario_particle_flags(m, PARTICLE_SPARKLES, 0)

    -- avoid issue with flying and then make the hover end after 2 secs or when stopping holding the button
    if m.prevAction ~= ACT_TRIPLE_JUMP and (m.flags & MARIO_WING_CAP) ~= 0 then
        if m.actionTimer >= 50 or (m.controller.buttonDown & A_BUTTON) == 0 then
            set_mario_action(m, ACT_FREEFALL, 0)
        end
    else
        if m.actionTimer >= 50 or (m.controller.buttonDown & A_BUTTON) == 0 then
            set_mario_action(m, ACT_FREEFALL, 0)
        end
    end

    -- increment the action timer to make the hover stop
    m.actionTimer = m.actionTimer + 1
end

--- @param m MarioState
function peach_update(m)
    if (m.input & INPUT_A_DOWN) ~= 0 and m.vel.y < -10 and m.prevAction ~= ACT_PEACH_FLOAT and princessFloatActs[m.action] then
        set_mario_action(m, ACT_PEACH_FLOAT, 0)
    end
end

hook_mario_action(ACT_PEACH_FLOAT, act_peach_float)

-----------------------
-- Daisy Double Jump --
-----------------------

ACT_DAISY_JUMP = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_MOVING)

--- @param m MarioState
local function act_daisy_jump(m)
    -- apply movement when using action
    common_air_action_step(m, ACT_JUMP_LAND, CHAR_ANIM_BEND_KNESS_RIDING_SHELL, AIR_STEP_NONE)

    -- setup when action starts (vertical speed and voiceline)
    if m.actionTimer == 0 then
        m.vel.y = m.forwardVel*0.3 + 40
        m.forwardVel = m.forwardVel*0.7
        play_character_sound(m, CHAR_SOUND_HELLO)
    end

    set_mario_particle_flags(m, PARTICLE_LEAF, 0)

    -- avoid issue with flying and then make the hover end after 2 secs or when stopping holding the button
    if m.prevAction ~= ACT_TRIPLE_JUMP and (m.flags & MARIO_WING_CAP) ~= 0 then
        if m.actionTimer >= 10 or (m.controller.buttonDown & A_BUTTON) == 0 then
            set_mario_action(m, ACT_FREEFALL, 0)
        end
    else
        if m.actionTimer >= 10 or (m.controller.buttonDown & A_BUTTON) == 0 then
            set_mario_action(m, ACT_FREEFALL, 0)
        end
    end

    -- increment the action timer to make the hover stop
    m.actionTimer = m.actionTimer + 1
end

--- @param m MarioState
function daisy_update(m)
    if (m.input & INPUT_A_PRESSED) ~= 0 and m.vel.y < 10 and m.prevAction ~= ACT_DAISY_JUMP and princessFloatActs[m.action] then
        set_mario_action(m, ACT_DAISY_JUMP, 0)
    end
end

hook_mario_action(ACT_DAISY_JUMP, act_daisy_jump)

-------------------
-- Yoshi Flutter --
-------------------

-- Flutterable actions, these don't match the DS flutterable actions
local flutterWhiteList = {
    [ACT_JUMP] = true,
    [ACT_DOUBLE_JUMP] = true,
    [ACT_TRIPLE_JUMP] = true,
    [ACT_LONG_JUMP] = true,
    [ACT_FREEFALL] = true
}

ACT_FLUTTER = allocate_mario_action(ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_GROUP_AIRBORNE)
YOSHI_ANIM_FLUTTER = 'yoshi_flutter_jump'
local YOSHI_SOUND_FLUTTER = audio_sample_load("yoshi_flutter.ogg") -- Load audio sample

---@param m MarioState
function act_flutter(m)

    -- End flutter after 1 second
    if m.actionTimer >= 30 or (m.input & INPUT_A_DOWN) == 0 then
        if m.actionTimer < 30 then
            audio_sample_stop(YOSHI_SOUND_FLUTTER) -- Stop sample after letting go of A
        end
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    local ended = common_air_action_step(m, ACT_JUMP_LAND, CHAR_ANIM_RUNNING_UNUSED, 0) ~= 0 -- Checks if the action ended earlier due to forced actions like bonking or landing

    if ended then
        audio_sample_stop(YOSHI_SOUND_FLUTTER) -- Stop sample after landing
    end

    if m.actionTimer == 0 and not ended then
        audio_sample_play(YOSHI_SOUND_FLUTTER, m.pos, 1) -- Play audio sample
    end

    smlua_anim_util_set_animation(m.marioObj, YOSHI_ANIM_FLUTTER) -- Sets the animation

    m.marioBodyState.eyeState = MARIO_EYES_CLOSED ---@type MarioEyesGSCId Eye State
    m.vel.y = approach_f32(m.vel.y, m.actionTimer / 1.25, 8, 8) -- Height increases faster as the 1 second passes
    m.marioObj.header.gfx.animInfo.animAccel = 32768 * 4 -- Animation Speed

    m.actionTimer = m.actionTimer + 1
    return false
end

---@param m MarioState
function yoshi_update(m)
    if m.prevAction & ACT_FLAG_AIR == 0 and m.action & ACT_FLAG_AIR ~= 0 and flutterWhiteList[m.action] and m.controller.buttonDown & A_BUTTON ~= 0 and m.vel.y < 0 then
        set_mario_action(m, ACT_FLUTTER, 0)
    end
end

hook_mario_action(ACT_FLUTTER, { every_frame = act_flutter })

---------------
-- Birdo Egg --
---------------

ACT_BIRDO_HOLD_WALKING = allocate_mario_action(ACT_FLAG_MOVING | ACT_GROUP_OBJECT)
ACT_BIRDO_SPIT_EGG = allocate_mario_action(ACT_FLAG_STATIONARY | ACT_FLAG_IDLE | ACT_FLAG_ALLOW_FIRST_PERSON | ACT_FLAG_PAUSE_EXIT)
ACT_BIRDO_SPIT_EGG_WALK = allocate_mario_action(ACT_FLAG_MOVING | ACT_FLAG_ALLOW_FIRST_PERSON)
ACT_BIRDO_SPIT_EGG_AIR = allocate_mario_action(ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_CONTROL_JUMP_HEIGHT)

-- this version works more like regular walking
---@param m MarioState
local function act_birdo_hold_walking(m)
    if not m then return false end

    local startYaw = m.faceAngle.y

    if m.heldObj and m.heldObj.behavior == get_behavior_from_id(id_bhvJumpingBox) then
        return set_mario_action(m, ACT_CRAZY_BOX_BOUNCE, 0);
    end

    if (m.marioObj.oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) ~= 0 then
        return drop_and_set_mario_action(m, ACT_WALKING, 0);
    end

    if (should_begin_sliding(m)) ~= 0 then
        return set_mario_action(m, ACT_HOLD_BEGIN_SLIDING, 0);
    end

    if (m.input & INPUT_B_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_THROWING, 0);
    end

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        return set_jumping_action(m, ACT_HOLD_JUMP, 0);
    end

    if (m.input & INPUT_ZERO_MOVEMENT) ~= 0 then
        return set_mario_action(m, ACT_HOLD_DECELERATING, 0);
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return drop_and_set_mario_action(m, ACT_CROUCH_SLIDE, 0);
    end

    update_walking_speed(m); -- normal walking speed

    local result = perform_ground_step(m)
    if result == GROUND_STEP_LEFT_GROUND then
        set_mario_action(m, ACT_HOLD_FREEFALL, 0);
    elseif result == GROUND_STEP_HIT_WALL then
        if (m.forwardVel > 16) then
            mario_set_forward_vel(m, 16)
        end
    end

    -- for the animation, temporarily read birdo's speed as lower so it looks less goofy
    local prevForwardVel = m.forwardVel
    local prevMag = m.intendedMag
    m.forwardVel = m.forwardVel * 0.6
    m.intendedMag = m.intendedMag * 0.6
    anim_and_audio_for_hold_walk(m)
    m.forwardVel = prevForwardVel
    m.intendedMag = prevMag


    -- tilt body
    local dYaw = m.faceAngle.y - startYaw;
    local val02 = -(dYaw * m.forwardVel / 12);
    local val00 = (m.forwardVel * 170);

    if (val02 > 0x1555) then
        val02 = 0x1555;
    elseif (val02 < -0x1555) then
        val02 = -0x1555;
    end

    if (val00 > 0x1555) then
        val00 = 0x1555;
    elseif (val00 < 0) then
        val00 = 0;
    end

    m.marioBodyState.allowPartRotation = 1
    m.marioBodyState.torsoAngle.z = approach_s32(m.marioBodyState.torsoAngle.z, val02, 0x400, 0x400);
    m.marioBodyState.torsoAngle.x = approach_s32(m.marioBodyState.torsoAngle.x, val00, 0x400, 0x400);

    if (0.4 * m.intendedMag - m.forwardVel > 10) then
        set_mario_particle_flags(m, PARTICLE_DUST, 0);
    end

    return 0
end

-- spit egg actions
local function act_birdo_spit_egg(m)
    if not m then return 0 end
    local e = gStateExtras[m.playerIndex]
    if (m.quicksandDepth > 30) then
        return set_mario_action(m, ACT_IN_QUICKSAND, 0)
    end

    if m.actionState == 0 then
        play_custom_anim(m, "BIRDO_ANIM_IDLE_TO_AIM_IDLE")
        if is_anim_past_end(m) ~= 0 then
            m.actionState = 1
        end
    elseif e.flameCharge == 0 and e.framesSinceShoot > 10 then
        play_custom_anim(m, "BIRDO_ANIM_AIM_IDLE_TO_IDLE")
        if is_anim_past_end(m) ~= 0 then
            return set_mario_action(m, ACT_IDLE, 0)
        end
    else
        play_custom_anim(m, "BIRDO_ANIM_AIM_IDLE")
    end
    mario_drop_held_object(m);

    m.actionTimer = m.actionTimer + 1

    local oldActTimer = m.actionTimer
    if (m.input & INPUT_NONZERO_ANALOG) ~= 0 then
        mario_set_forward_vel(m, 0)
        local result = set_mario_action(m, ACT_BIRDO_SPIT_EGG_WALK, 0)
        m.actionTimer = oldActTimer
        return result
    elseif (check_common_idle_cancels(m) ~= 0) then
        if m.action & ACT_FLAG_AIR ~= 0 then
            mario_set_forward_vel(m, 0)
            set_mario_action(m, ACT_BIRDO_SPIT_EGG_AIR, 1)
            if m.vel.y <= 0 then
                m.actionArg = 0
            end
            m.actionTimer = oldActTimer
        end
        return 1
    end

    mario_set_forward_vel(m, 0)
    perform_ground_step(m);
    return 0
end

local function act_birdo_spit_egg_walk(m)
    if not m then return 0 end
    local e = gStateExtras[m.playerIndex]
    local mBody = m.marioBodyState

    mario_drop_held_object(m);

    m.actionTimer = m.actionTimer + 1
    if e.flameCharge == 0 and e.framesSinceShoot > 10 then
        if m.forwardVel < 0 then
            m.forwardVel = m.intendedMag
            m.faceAngle.y = m.intendedYaw
            return set_mario_action(m, ACT_FINISH_TURNING_AROUND, 0);
        end
        m.forwardVel = m.intendedMag
        m.faceAngle.y = m.intendedYaw
        return set_mario_action(m, ACT_WALKING, 0);
    end

    if mario_floor_is_slippery(m) ~= 0 then
        return set_mario_action(m, ACT_WALKING, 0)
    end

    if (should_begin_sliding(m)) ~= 0 then
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    end

    if (m.input & INPUT_FIRST_PERSON) ~= 0 then
        m.intendedMag = 0
        if m.slideVelX == 0 and m.slideVelZ == 0 then
            return begin_braking_action(m);
        end
    end

    if (m.input & INPUT_ZERO_MOVEMENT) ~= 0 and m.slideVelX == 0 and m.slideVelZ == 0 then
        local oldActTimer = m.actionTimer
        local result = set_mario_action(m, ACT_BIRDO_SPIT_EGG, 0)
        m.actionTimer = oldActTimer
        return result
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_CROUCH_SLIDE, 0);
    end

    -- strafe movement
    local newVelX = sins(m.intendedYaw) * m.intendedMag
    local newVelZ = coss(m.intendedYaw) * m.intendedMag
    m.slideVelX = approach_f32(m.slideVelX, newVelX, 4, 4)
    m.slideVelZ = approach_f32(m.slideVelZ, newVelZ, 4, 4)
    m.vel.x, m.vel.z = m.slideVelX, m.slideVelZ
    m.forwardVel = math.sqrt(m.vel.x ^ 2 + m.vel.z ^ 2)

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        set_mario_y_vel_based_on_fspeed(m, 42, 0.25)
        m.slideVelX = m.slideVelX * 0.8
        m.slideVelZ = m.slideVelZ * 0.8
        m.vel.x, m.vel.z = m.slideVelX, m.slideVelZ
        m.forwardVel = m.forwardVel * 0.8
        local oldActTimer = m.actionTimer
        local result = set_mario_action(m, ACT_BIRDO_SPIT_EGG_AIR, 1)
        m.actionTimer = oldActTimer
        return result
    end

    local result = (perform_ground_step(m))
    if result == GROUND_STEP_LEFT_GROUND then
        m.vel.y = 0
        local oldActTimer = m.actionTimer
        set_mario_action(m, ACT_BIRDO_SPIT_EGG_AIR, 0)
        m.actionTimer = oldActTimer
        --set_character_animation(m, CHAR_ANIM_GENERAL_FALL);
    elseif result == GROUND_STEP_NONE then
        --anim_and_audio_for_walk(m);
        play_step_sound(m, 10, 49)

        local dYaw = convert_s16(m.faceAngle.y - m.intendedYaw)
        play_custom_anim(m, "BIRDO_ANIM_AIM_WALK", m.forwardVel / 4 * 0x10000)

        mBody.allowPartRotation = 1
        m.marioObj.header.gfx.angle.y = m.intendedYaw
        m.marioObj.header.gfx.animInfo.curAnim.flags = m.marioObj.header.gfx.animInfo.curAnim.flags & ~ANIM_FLAG_FORWARD
        if dYaw > 0x4000 or dYaw < -0x4000 then
            m.marioObj.header.gfx.angle.y = m.intendedYaw - 0x8000
            m.marioObj.header.gfx.animInfo.curAnim.flags = ANIM_FLAG_FORWARD
        end

        mBody.torsoAngle.y = convert_s16(m.faceAngle.y - m.marioObj.header.gfx.angle.y) * 0.4
        mBody.headAngle.y =  m.faceAngle.y - m.marioObj.header.gfx.angle.y - mBody.torsoAngle.y

        if m.intendedMag - m.forwardVel > 16 then
            set_mario_particle_flags(m, PARTICLE_DUST, false)
        end
    end

    check_ledge_climb_down(m);
    --tilt_body_walking(m, startYaw);
    return 0
end

---@param m MarioState
local function act_birdo_spit_egg_air(m)
    if not m then return 0 end
    local e = gStateExtras[m.playerIndex]

    play_custom_anim(m, "BIRDO_ANIM_AIM_JUMP")
    if m.actionArg ~= 1 then
        set_anim_to_frame(m, m.marioObj.header.gfx.animInfo.curAnim.loopEnd)
    else
        play_mario_sound(m, SOUND_ACTION_TERRAIN_JUMP, 0);
    end

    m.actionTimer = m.actionTimer + 1

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_GROUND_POUND, 0)
    end

    -- air strafe
    local newVelX = sins(m.intendedYaw) * m.intendedMag
    local newVelZ = coss(m.intendedYaw) * m.intendedMag
    m.slideVelX = approach_f32(m.slideVelX, newVelX, 1, 1)
    m.slideVelZ = approach_f32(m.slideVelZ, newVelZ, 1, 1)
    m.vel.x, m.vel.z = m.slideVelX, m.slideVelZ
    m.forwardVel = m.slideVelX * sins(m.faceAngle.y) + m.slideVelZ * coss(m.faceAngle.y)
    --local absSpeed = math.max(math.abs(m.slideVelX), math.abs(m.slideVelZ))

    local result = (perform_air_step(m, 0))
    if result == AIR_STEP_LANDED then
        if check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) ~= 0 then
            return 1
        elseif e.flameCharge == 0 and e.framesSinceShoot > 10 then
            set_mario_action(m, ACT_FREEFALL_LAND, 0)
        else
            local oldActTimer = m.actionTimer
            set_mario_action(m, ACT_BIRDO_SPIT_EGG_WALK, 0)
            m.actionTimer = oldActTimer
        end
        return 1
    elseif result == AIR_STEP_HIT_WALL then
        mario_set_forward_vel(m, 0)
    elseif result == AIR_STEP_HIT_LAVA_WALL then
        lava_boost_on_wall(m);
    end

    return 0
end

-- egg object
E_MODEL_EGG = smlua_model_util_get_id("egg_geo")
---@param o Object
function bhv_birdo_egg_init(o)
    o.oFlags = (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)
    o.oFaceAngleRoll = 0
    o.oMoveAngleRoll = 0
    o.oGravity = 0
    o.oBounciness = 0
    o.oFriction = 1
    o.oDragStrength = 0
    o.oBuoyancy = 0
    o.oWallHitboxRadius = 60
    o.oVelY = 0

    o.collisionData = smlua_collision_util_get("egg_collision")

    local hitbox = get_temp_object_hitbox()
    hitbox.interactType = INTERACT_DAMAGE
    hitbox.hurtboxRadius = 60
    hitbox.hurtboxHeight = 80
    hitbox.downOffset = 80
    hitbox.radius = 60
    hitbox.height = 80
    hitbox.damageOrCoinValue = 1
    if o.oBehParams ~= 0 then
        hitbox.interactType = INTERACT_FLAME
        hitbox.hurtboxRadius = 30
        hitbox.downOffset = 0
        obj_set_billboard(o)
        o.header.gfx.scale.x = 3
        o.header.gfx.scale.y = 3
        o.header.gfx.scale.z = 3
    end
    obj_set_hitbox(o, hitbox)
    o.oIntangibleTimer = 10

    -- do manual shadow, otherwise the shadow renders on top of itself
    o.header.gfx.disableAutomaticShadowPos = true
    o.header.gfx.shadowPos.x = o.oPosX
    o.header.gfx.shadowPos.y = o.oPosY - 50
    o.header.gfx.shadowPos.z = o.oPosZ

    network_init_object(o, true, { 'globalPlayerIndex' })
end

---@param o Object
function bhv_birdo_egg_loop(o)
    if o.oBehParams ~= 0 then
        o.oAnimState = o.oAnimState + 1
    end

    if o.oHeldState == HELD_FREE then
        cur_obj_enable_rendering()
        if o.oAction == 0 then
            o.oGravity = 0
        else
            o.oMoveAnglePitch = 0
            o.oFaceAnglePitch = 0
            o.oGravity = -2
        end

        cur_obj_update_floor_and_walls()
        local oldForwardVel = o.oForwardVel
        if o.oAction == 0 then
            obj_compute_vel_from_move_pitch(o.oForwardVel)
        end
        cur_obj_move_standard(60)
        o.oForwardVel = oldForwardVel

        local defaultVel = 20
        if o.oBehParams ~= 0 then
            defaultVel = 40
        end
        if o.oAction == 0 and o.oForwardVel > defaultVel then
            o.oForwardVel = approach_f32(o.oForwardVel, defaultVel, 3, 3)
        end

        -- manual object collision
        local dieFromCollision = false
        o.numCollidedObjs = obj_attack_collided_from_other_object(o)
        if o.numCollidedObjs ~= 0 and o.oBehParams == 0 then
            dieFromCollision = true
        end
        if o.oDistanceToMario < 2000 then
            local obj_lists_check = {
                OBJ_LIST_GENACTOR,
                OBJ_LIST_PUSHABLE,
                OBJ_LIST_SURFACE,
            }
            for i, list in ipairs(obj_lists_check) do
                local o2 = obj_get_first(list)
                while o2 and o.numCollidedObjs < 4 do
                    if o ~= o2 and detect_object_hitbox_overlap(o, o2) ~= 0 then
                        if obj_has_behavior_id(o2, id_bhvBowser) == 0 then
                            o2.oInteractStatus = o2.oInteractStatus | ATTACK_PUNCH | INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED | INT_STATUS_TOUCHED_BOB_OMB
                        end
                        o2.numCollidedObjs = o2.numCollidedObjs - 1 -- prevent game crash
                        if o.oBehParams == 0 or birdo_fireball_interaction(o2, o) then
                            dieFromCollision = true
                        end
                    end
                    o2 = obj_get_next(o2)
                end
                if o.numCollidedObjs >= 4 then break end
            end
        end

        -- surface collision
        if o.oAction == 0 and o.oBehParams == 0 and o.oMoveFlags & OBJ_MOVE_MASK_IN_WATER == 0 then
            local m0 = gMarioStates[0]
            load_object_collision_model()
            if cur_obj_is_mario_on_platform() ~= 0 then
                if (m0.action == ACT_PUNCHING or m0.action == ACT_MOVE_PUNCHING) then
                    -- pick up egg
                    m0.heldObj = o
                    m0.marioBodyState.grabPos = GRAB_POS_LIGHT_OBJ
                    o.heldByPlayerIndex = 0
                    o.oHeldState = HELD_HELD
                    set_mario_action(m0, ACT_HOLD_FREEFALL, 0)
                    if (o.oSyncID ~= 0) then network_send_object(o, false) end
                elseif (m0.prevAction & ACT_FLAG_AIR) ~= 0 then -- prevent falling off of egg easily
                    m0.pos.x = o.oPosX
                    m0.pos.z = o.oPosZ
                end
            end
        end

        if dieFromCollision or o.oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_UNDERWATER_ON_GROUND | OBJ_MOVE_MASK_ON_GROUND) ~= 0 or o.oTimer > 120 then
            o.numCollidedObjs = 0
            spawn_mist_particles()
            obj_mark_for_deletion(o)
            o.header.gfx.disableAutomaticShadowPos = false
        end
        o.oInteractStatus = 0
        o.numCollidedObjs = 0
    elseif o.oHeldState == HELD_HELD then
        o.oFaceAnglePitch = 0
        o.oMoveAnglePitch = 0
        o.oInteractType = INTERACT_GRABBABLE
        cur_obj_disable_rendering_and_become_intangible(o)
    elseif o.oHeldState == HELD_THROWN then
        o.oFaceAnglePitch = 0
        o.oMoveAnglePitch = 0
        o.oInteractType = INTERACT_DAMAGE
        cur_obj_enable_rendering_and_become_tangible(o)
        cur_obj_change_action(1)
        local m = gMarioStates[o.heldByPlayerIndex]
        o.oForwardVel = math.max(m.forwardVel + 15, 40)
        o.oVelY = 10
        o.oTimer = 0
        o.oHeldState = HELD_FREE
        o.oIntangibleTimer = 10
    elseif o.oHeldState == HELD_DROPPED then
        spawn_mist_particles()
        obj_mark_for_deletion(o)
        o.header.gfx.disableAutomaticShadowPos = false
    end

    -- do manual shadow, otherwise the shadow renders on top of itself
    if o.activeFlags & ACTIVE_FLAG_DEACTIVATED == 0 then
        o.header.gfx.disableAutomaticShadowPos = true
        o.header.gfx.shadowPos.x = o.oPosX
        o.header.gfx.shadowPos.y = o.oPosY - 50
        o.header.gfx.shadowPos.z = o.oPosZ
    end
end

-- lua recreation
---@param a Object
---@param b Object
function detect_object_hitbox_overlap(a, b)
    if not (a and b) then return 0 end
    local sp3C = a.oPosY - a.hitboxDownOffset;
    local sp38 = b.oPosY - b.hitboxDownOffset;
    local dx = a.oPosX - b.oPosX;
    local dz = a.oPosZ - b.oPosZ;
    local collisionRadius = a.hitboxRadius + b.hitboxRadius;
    local distance = math.floor(math.sqrt(dx * dx + dz * dz))

    -- do not check for player interactions here
    if ((a.oInteractType & INTERACT_PLAYER) ~= 0 and (b.oInteractType & INTERACT_PLAYER) ~= 0) then
        return 0;
    end

    if (collisionRadius > distance) then
        local sp20 = a.hitboxHeight + sp3C;
        local sp1C = b.hitboxHeight + sp38;

        if (sp3C > sp1C) then
            return 0;
        end
        if (sp20 < sp38) then
            return 0;
        end
        if (a.numCollidedObjs >= 4) then
            return 0;
        end
        if (b.numCollidedObjs >= 4) then
            return 0;
        end
        -- can't reference these fields in lua
        --a.collidedObjs[a.numCollidedObjs] = b;
        --b.collidedObjs[b.numCollidedObjs] = a;
        a.collidedObjInteractTypes = a.collidedObjInteractTypes | b.oInteractType;
        b.collidedObjInteractTypes = b.collidedObjInteractTypes | a.oInteractType;
        a.numCollidedObjs = a.numCollidedObjs + 1
        b.numCollidedObjs = b.numCollidedObjs + 1
        return 1;
    end

    return 0;
end

id_bhvBirdoEgg = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_birdo_egg_init, bhv_birdo_egg_loop, "bhvBirdoEgg")

---@param m MarioState
function birdo_update(m)
    -- spit egg
    local e = gStateExtras[m.playerIndex]
    local inSpitAction = (m.action == ACT_BIRDO_SPIT_EGG or m.action == ACT_BIRDO_SPIT_EGG_WALK or m.action == ACT_BIRDO_SPIT_EGG_AIR or m.action == ACT_FIRST_PERSON or m.action == ACT_WATER_PUNCH or m.action == ACT_FLYING)
    local headRot = m.marioBodyState.headAngle

    if m.controller.buttonPressed & B_BUTTON ~= 0 and inSpitAction then
        -- when mashing B, stay in spit action
        e.framesSinceShoot = 0
        if e.spitTimer == 0 then
            e.flameCharge = 0
        end
    else
        -- handle shooting repeatedly/charging
        if e.framesSinceShoot ~= 255 then
            e.framesSinceShoot = e.framesSinceShoot + 1
        end
        if m.controller.buttonDown & B_BUTTON ~= 0 then
            if inSpitAction then
                e.flameCharge = e.flameCharge + 1
            end
        elseif e.spitTimer < 25 then
            if e.flameCharge >= 30 then
                e.framesSinceShoot = 0 -- shoot fireball
            else
                e.flameCharge = 0
            end
        end
    end

    if (e.framesSinceShoot <= 10 or e.flameCharge ~= 0) and m.heldObj == nil and inSpitAction then
        local canShoot = true
        local eggCount = 0
        local gIndex = network_global_index_from_local(m.playerIndex)
        local egg = obj_get_first_with_behavior_id(id_bhvBirdoEgg)
        while egg do
            if egg.oAction == 0 and egg.oHeldState == HELD_FREE and egg.globalPlayerIndex == gIndex then
                eggCount = eggCount + 1
                if eggCount >= 3 then -- max of 3 eggs/fireballs per player
                    canShoot = false
                    break
                end
            end
            egg = obj_get_next_with_same_behavior_id(egg)
        end

        if e.spitTimer ~= 0 then
            e.spitTimer = e.spitTimer - 1
            m.marioBodyState.allowPartRotation = 1
            if e.spitTimer > 24 then
                headRot.x = approach_f32(headRot.x, degrees_to_sm64(-30), degrees_to_sm64(10), degrees_to_sm64(10))
            else
                headRot.x = approach_f32(headRot.x, degrees_to_sm64(0), degrees_to_sm64(3.5), degrees_to_sm64(3.5))
            end
        end
        if e.spitTimer == 0 and canShoot and e.framesSinceShoot <= 10 then
            m.actionTimer = 0
            m.actionArg = 0
        end

        local mouthPos = {x = 0, y = 0, z = 0}
        local yaw = m.faceAngle.y
        local pitch = 0
        if canShoot then
            -- when swimming, flying, or in first person, allow shooting in any direction (UNUSED)
            if m.action == ACT_FIRST_PERSON then
                yaw = m.statusForCamera.headRotation.y + yaw
                pitch = m.statusForCamera.headRotation.x
                mouthPos.x = m.pos.x + sins(yaw) * 60 * coss(pitch)
                mouthPos.y = m.pos.y + 120 - sins(pitch) * 120
                mouthPos.z = m.pos.z + coss(yaw) * 60 * coss(pitch)
            elseif m.action & ACT_FLAG_SWIMMING_OR_FLYING ~= 0 then
                pitch = -m.faceAngle.x
                if pitch < 0 then
                    mouthPos.x = m.pos.x + sins(yaw) * 80 * coss(pitch)
                    mouthPos.y = m.pos.y + 120
                    mouthPos.z = m.pos.z + coss(yaw) * 80 * coss(pitch)
                else
                    mouthPos.x = m.pos.x + sins(yaw) * 80
                    mouthPos.y = m.pos.y + 120 - sins(pitch) * 150
                    mouthPos.z = m.pos.z + coss(yaw) * 80
                end
            else
                mouthPos.x = m.marioBodyState.headPos.x + sins(yaw+m.marioBodyState.headAngle.y) * 60
                mouthPos.y = m.marioBodyState.headPos.y + 20
                mouthPos.z = m.marioBodyState.headPos.z + coss(yaw+m.marioBodyState.headAngle.y) * 60
            end
        end

        if canShoot and e.spitTimer == 0 and e.flameCharge >= 30 and m.action & ACT_FLAG_SWIMMING == 0 then
            spawn_non_sync_object(id_bhvKoopaShellFlame, E_MODEL_RED_FLAME,
            mouthPos.x,
            mouthPos.y,
            mouthPos.z,
            function(o)
                o.oKoopaShellFlameUnkF8 = 2
                o.oMoveAngleYaw = math.random(0, 0xFFFF)
                o.oVelY = math.random(1, 10)
                o.oAnimState = math.random(1, 10)
                o.oGravity = -4.0
                o.oTimer = 1
                o.oForwardVel = math.random(1, 10)
            end)
            play_sound(SOUND_AIR_BLOW_FIRE, m.marioObj.header.gfx.cameraToObject)
        end

        if canShoot and e.spitTimer == 0 and e.framesSinceShoot <= 10 then
            e.spitTimer = 30
        elseif e.spitTimer == 25 then
            local model = E_MODEL_EGG
            local isFireball = (e.flameCharge >= 30)
            if isFireball then
                model = E_MODEL_RED_FLAME
                e.flameCharge = 0
            end

            if not isFireball then
                audio_sample_play(SOUND_SPIT, m.pos, 1) -- Play audio sample
            else
                play_sound(SOUND_AIR_BOWSER_SPIT_FIRE, m.marioObj.header.gfx.cameraToObject)
            end

            if m.playerIndex == 0 then
                local eggVel = m.forwardVel * 2 + 25
                -- add double floor velocity to prevent being able to platform on eggs forever
                if m.floor and m.floor.object and m.floor.object.oForwardVel ~= 0 then
                    eggVel = eggVel + m.floor.object.oForwardVel * 2
                end
                spawn_sync_object(id_bhvBirdoEgg, model, mouthPos.x + sins(yaw) * 40 * coss(pitch), mouthPos.y, mouthPos.z + coss(yaw) * 40 * coss(pitch), function(o)
                        o.oForwardVel = math.max(eggVel, 40)
                        o.oMoveAngleYaw = yaw
                        o.oFaceAnglePitch = pitch
                        o.oMoveAnglePitch = pitch
                        o.oIntangibleTimer = 100
                        o.globalPlayerIndex = gIndex
                        o.oBehParams = (isFireball and 1) or 0
                        spawn_mist_particles_variable(20, 120, 5)
                    end)
            end
        end
    elseif e.spitTimer ~= 0 then
        e.spitTimer = e.spitTimer - 1
        m.marioBodyState.allowPartRotation = 1
        if e.spitTimer > 24 then
            headRot.x = approach_f32(headRot.x, degrees_to_sm64(-30), degrees_to_sm64(10), degrees_to_sm64(10))
        else
            headRot.x = approach_f32(headRot.x, degrees_to_sm64(0), degrees_to_sm64(3.5), degrees_to_sm64(3.5))
        end
    end

    -- throw objects instantly
    if m.action == ACT_THROWING then
        if m.actionTimer < 6 then
            m.actionTimer = 6
            set_anim_to_frame(m, 6)
        end
    elseif m.action == ACT_AIR_THROW or m.action == ACT_AIR_THROW_LAND then
        if m.actionTimer < 3 then
            m.actionTimer = 3
            set_anim_to_frame(m, 3)
        end
    end
end
hook_mario_action(ACT_BIRDO_HOLD_WALKING, { every_frame = act_birdo_hold_walking })
hook_mario_action(ACT_BIRDO_SPIT_EGG, { every_frame = act_birdo_spit_egg })
hook_mario_action(ACT_BIRDO_SPIT_EGG_AIR, { every_frame = act_birdo_spit_egg_air })
hook_mario_action(ACT_BIRDO_SPIT_EGG_WALK, { every_frame = act_birdo_spit_egg_walk })

function birdo_on_set_action(m)
    m.marioBodyState.allowPartRotation = 0
    m.marioBodyState.torsoAngle.x = 0
    m.marioBodyState.torsoAngle.y = 0
    m.marioBodyState.torsoAngle.z = 0
    m.marioBodyState.headAngle.y = 0
    if m.action == ACT_HOLD_WALKING then -- switch to custom hold action
        m.marioBodyState.allowPartRotation = 1
        set_mario_action(m, ACT_BIRDO_HOLD_WALKING, 0)
    end
end

function birdo_before_action(m, action)
    if ((action == ACT_PUNCHING and m.action ~= ACT_CROUCHING) or action == ACT_MOVE_PUNCHING) then
        local e = gStateExtras[m.playerIndex]
        e.framesSinceShoot = 0
        if e.spitTimer == 0 then
            e.flameCharge = 0
        end

        local canShoot = true
        local eggCount = 0
        local gIndex = network_global_index_from_local(m.playerIndex)
        local egg = obj_get_first_with_behavior_id(id_bhvBirdoEgg)
        while egg do
            if egg.oAction == 0 and egg.oHeldState == HELD_FREE and egg.globalPlayerIndex == gIndex then
                eggCount = eggCount + 1
                if eggCount >= 3 then -- max of 3 eggs/fireballs per player
                    canShoot = false
                    break
                end
            end
            egg = obj_get_next_with_same_behavior_id(egg)
        end

        if m.action == ACT_BIRDO_SPIT_EGG or e.spitTimer ~= 0 or not canShoot then
            return 1
        elseif action == ACT_MOVE_PUNCHING then
            m.marioObj.header.gfx.animInfo.animFrame = 1
            return ACT_BIRDO_SPIT_EGG_WALK
        else
            m.marioObj.header.gfx.animInfo.animFrame = 1
            return ACT_BIRDO_SPIT_EGG
        end
    end
end

function birdo_on_interact(m, o, intType)
    local e = gStateExtras[m.playerIndex]
    if intType == INTERACT_GRABBABLE and e.framesSinceShoot == 0 and e.flameCharge == 0 and (m.action == ACT_BIRDO_SPIT_EGG or m.action == ACT_BIRDO_SPIT_EGG_WALK) and o.oInteractionSubtype & INT_SUBTYPE_NOT_GRABBABLE == 0 then
        m.action = ACT_MOVE_PUNCHING
        m.actionArg = 1
        return
    end
end

function birdo_before_phys_step(m)
    local hScale = 1.0
    local vScale = 1.0

    -- faster ground movement and slower, floaty air movement
    if (m.action & ACT_FLAG_MOVING) ~= 0 and m.action ~= ACT_BUBBLED then
        hScale = hScale * 1.12 -- not as fast as toad
    elseif m.action & ACT_FLAG_AIR ~= 0 then
        hScale = hScale * 0.94
        if m.vel.y < 0 then
            vScale = vScale * 0.98
        end
    end

    m.vel.x = m.vel.x * hScale
    m.vel.y = m.vel.y * vScale
    m.vel.z = m.vel.z * hScale
end

-- allow shooting in first person
function birdo_before_update(m)
    if m.action == ACT_FIRST_PERSON and m.controller.buttonPressed & B_BUTTON ~= 0 then
        local e = gStateExtras[m.playerIndex]
        e.framesSinceShoot = 0
        if e.spitTimer == 0 then
            e.flameCharge = 0
        end
        m.controller.buttonPressed = m.controller.buttonPressed & ~B_BUTTON
    end
end

-- interactions for birdo's fireball
function birdo_fireball_interaction(o, egg)
    if obj_has_behavior_id(o, id_bhvMrBlizzard) ~= 0 then
        o.oFaceAngleRoll = 0x3000
        o.oMrBlizzardHeldObj = nil
        o.prevObj = o.oMrBlizzardHeldObj
        o.oAction = MR_BLIZZARD_ACT_DEATH
        o.oMrBlizzardDizziness = 0
        o.oMrBlizzardChangeInDizziness = 0
        o.oTimer = 30
        return true
    end

    if obj_has_behavior_id(o, id_bhvBowser) ~= 0 then
        if o.oAction ~= 4 and o.oAction ~= 5 and o.oAction ~= 6 and o.oAction ~= 12 and o.oAction ~= 19 and o.oAction ~= 20 and math.abs(o.oVelY) <= 2 then
            o.oAction = 1
        end
        return true
    end

    if (o.oInteractType & INTERACT_BULLY) ~= 0 then
        o.oForwardVel = 50
        o.oMoveAngleYaw = obj_angle_to_object(o, egg) + 0x8000
        return true
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

-------------------
-- Rosalina Spin --
-------------------

ACT_SPINJUMP = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ATTACKING)
E_MODEL_SPIN_ATTACK = smlua_model_util_get_id("spin_attack_geo")

---@param o Object
local function bhv_spin_attack_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE -- Allows you to change the position and angle
end

---@param o Object
local function bhv_spin_attack_loop(o)
    cur_obj_set_pos_relative_to_parent(0, 20, 0) -- Makes it move to its parent's position

    o.oFaceAngleYaw = o.oFaceAngleYaw + 0x2000 -- Rotates it

    pM = gMarioStates[network_local_index_from_global(o.globalPlayerIndex)] -- Parent MarioState

    if pM.action ~= ACT_SPINJUMP then -- Deletes itself once the action changes
        obj_mark_for_deletion(o)
    end
end

local id_bhvSpinAttack = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_spin_attack_init, bhv_spin_attack_loop)

gPlayerSyncTable[0].canSpin = true -- Determines if you can spin
gPlayerSyncTable[0].canGrab = false -- Determines if you're near a grabbable

-- Spinable actions, these are actions you can spin out of
local spinWhiteList = {
    [ACT_LONG_JUMP] = true,
    [ACT_BACKFLIP] = true
}

-- Spin overridable actions, these are overriden instantly
local spinOverridableActs = {
    [ACT_PUNCHING] = true,
    [ACT_MOVE_PUNCHING] = true,
    [ACT_JUMP_KICK] = true,
    [ACT_DIVE] = true
}

local ROSALINA_SOUND_SPIN = audio_sample_load("spin_attack.ogg") -- Load audio sample

---@param m MarioState
function act_spinjump(m)

    if m.actionTimer >= 15 then
        return set_mario_action(m, ACT_FREEFALL, 0) -- End the action
    end

    if m.actionTimer == 0 then
        play_character_sound(m, CHAR_SOUND_HELLO) -- Plays the character sound
        audio_sample_play(ROSALINA_SOUND_SPIN, m.pos, 1) -- Plays the spin sound sample
        m.particleFlags = m.particleFlags | ACTIVE_PARTICLE_SPARKLES -- Spawns sparkle particles

        m.vel.y = 30 -- Initial upward velocity
        m.marioObj.hitboxRadius = 100 -- Damage hitbox

        -- Spawn the spin effect
        spawn_non_sync_object(id_bhvSpinAttack, E_MODEL_SPIN_ATTACK, m.pos.x, m.pos.y, m.pos.z,
        function (o)
            o.parentObj = m.marioObj
            o.globalPlayerIndex = m.marioObj.globalPlayerIndex
        end)

    else
        m.marioObj.hitboxRadius = 37 -- Reset the hitbox after initial hit
    end

    common_air_action_step(m, ACT_FREEFALL_LAND, CHAR_ANIM_BEND_KNESS_RIDING_SHELL, AIR_STEP_NONE)

    m.marioBodyState.handState = 2 -- Hand State

    -- Increments the action timer
    m.actionTimer = m.actionTimer + 1
end

---@param m MarioState
---@param o Object
---@param intType InteractionType
local function rosalina_on_interact(m, o, intType)
    local p = gPlayerSyncTable[m.playerIndex]
    if intType == INTERACT_GRABBABLE and o.oInteractionSubtype & INT_SUBTYPE_NOT_GRABBABLE == 0 then
        p.canGrab = true
    end
end

---@param m MarioState
local function rosalina_update(m)
    local p = gPlayerSyncTable[m.playerIndex]

    if p.canSpin and spinWhiteList[m.action] and m.controller.buttonPressed & B_BUTTON ~= 0 then
        p.canSpin = false
        return set_mario_action(m, ACT_SPINJUMP, 0)
    end

    if m.action & ACT_FLAG_AIR == 0 and m.playerIndex == 0 then
        p.canSpin = true
    end

    if m.action ~= ACT_SPINJUMP and m.marioObj.hitboxRadius ~= 37 then
        m.marioObj.hitboxRadius = 37
    end
end

---@param m MarioState
local function rosalina_before_action(m, nextAct)
    local p = gPlayerSyncTable[m.playerIndex]

    if p.canSpin and (not p.canGrab) and spinOverridableActs[nextAct] and m.input & (INPUT_Z_DOWN | INPUT_A_DOWN) == 0 then
        p.canSpin = false
        return ACT_SPINJUMP
    end

    if not nextAct then return end -- So bitwise operations don't fail

    if nextAct & ACT_FLAG_AIR == 0 then
        if not p.canSpin then
            play_sound_with_freq_scale(SOUND_GENERAL_COIN_SPURT_EU, m.marioObj.header.gfx.cameraToObject, 1.6)
            spawn_non_sync_object(id_bhvSparkle, E_MODEL_SPARKLES_ANIMATION, m.pos.x, m.pos.y + 200, m.pos.z, function (o)
                obj_scale(o, 0.75)
            end)
        end
        p.canGrab = false
        p.canSpin = true
    end
end

hook_mario_action(ACT_SPINJUMP, { every_frame = act_spinjump }, INT_KICK)

----------------
---  Pauline  --
----------------

local function pauline_update(m)
    if m.action == ACT_GROUND_POUND and m.input & INPUT_B_PRESSED ~= 0 then
        m.forwardVel = 30
        m.faceAngle.y = m.intendedYaw
        m.vel.y = 30
        set_mario_action(m, ACT_DIVE, 0)
        m.particleFlags = m.particleFlags | PARTICLE_DUST
    end
end

-------------
---  Main  --
-------------

local function on_character_select_load()
    local CT_TOADETTE  = extraCharacters[1].tablePos
    local CT_PEACH     = extraCharacters[2].tablePos
    local CT_DAISY     = extraCharacters[3].tablePos
    local CT_YOSHI     = extraCharacters[4].tablePos
    local CT_BIRDO     = extraCharacters[5].tablePos
    local CT_PAULINE   = extraCharacters[7].tablePos
    local CT_ROSALINA  = extraCharacters[8].tablePos

    -- Toadette
    _G.charSelect.character_hook_moveset(CT_TOADETTE, HOOK_MARIO_UPDATE, toadette_update)
    _G.charSelect.character_hook_moveset(CT_TOADETTE, HOOK_ON_SET_MARIO_ACTION, toadette_on_set_action)
    _G.charSelect.character_hook_moveset(CT_TOADETTE, HOOK_BEFORE_PHYS_STEP, toadette_before_phys_step)
    -- Peach
    _G.charSelect.character_hook_moveset(CT_PEACH, HOOK_MARIO_UPDATE, peach_update)
    -- Daisy
    _G.charSelect.character_hook_moveset(CT_DAISY, HOOK_MARIO_UPDATE, daisy_update)
    -- Yoshi
    _G.charSelect.character_hook_moveset(CT_YOSHI, HOOK_MARIO_UPDATE, yoshi_update)
    -- Birdo
    _G.charSelect.character_hook_moveset(CT_BIRDO, HOOK_MARIO_UPDATE, birdo_update)
    _G.charSelect.character_hook_moveset(CT_BIRDO, HOOK_ON_SET_MARIO_ACTION, birdo_on_set_action)
    _G.charSelect.character_hook_moveset(CT_BIRDO, HOOK_BEFORE_SET_MARIO_ACTION, birdo_before_action)
    _G.charSelect.character_hook_moveset(CT_BIRDO, HOOK_ON_INTERACT, birdo_on_interact)
    _G.charSelect.character_hook_moveset(CT_BIRDO, HOOK_BEFORE_PHYS_STEP, birdo_before_phys_step)
    _G.charSelect.character_hook_moveset(CT_BIRDO, HOOK_BEFORE_MARIO_UPDATE, birdo_before_update)
    -- Pauline
    _G.charSelect.character_hook_moveset(CT_PAULINE, HOOK_MARIO_UPDATE, pauline_update)
    -- Rosalina
    _G.charSelect.character_hook_moveset(CT_ROSALINA, HOOK_MARIO_UPDATE, rosalina_update)
    _G.charSelect.character_hook_moveset(CT_ROSALINA, HOOK_ON_PVP_ATTACK, rosalina_on_pvp_attack)
    _G.charSelect.character_hook_moveset(CT_ROSALINA, HOOK_ON_INTERACT, rosalina_on_interact)
    _G.charSelect.character_hook_moveset(CT_ROSALINA, HOOK_BEFORE_SET_MARIO_ACTION, rosalina_before_action)
end

hook_event(HOOK_ON_MODS_LOADED, on_character_select_load)