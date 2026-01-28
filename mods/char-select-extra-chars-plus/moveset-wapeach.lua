-------------------------
-- Wapeach Axe Attacks --
-------------------------

if not charSelect then return end

_G.ACT_AXE_CHOP       = allocate_mario_action(ACT_GROUP_STATIONARY | ACT_FLAG_STATIONARY)
_G.ACT_AXE_SPIN       = allocate_mario_action(ACT_GROUP_MOVING | ACT_FLAG_MOVING | ACT_FLAG_ATTACKING)
_G.ACT_AXE_SPIN_AIR   = allocate_mario_action(ACT_FLAG_ATTACKING | ACT_FLAG_AIR | ACT_GROUP_AIRBORNE)
_G.ACT_AXE_SPIN_DIZZY = allocate_mario_action(ACT_GROUP_MOVING | ACT_FLAG_MOVING)

---@param o Object
local function bhv_axe_attack_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE

    o.oDamageOrCoinValue = 2
    o.oNumLootCoins = 0
    o.oHealth = 0
    o.hitboxRadius = 60
    o.hitboxHeight = 80
    o.hurtboxRadius = 60
    o.hurtboxHeight = 80
    o.hitboxDownOffset = 0
    o.oInteractType = 0

    cur_obj_scale(1)
    cur_obj_become_tangible()

    network_init_object(o, true, {})
end

---@param o Object
local function bhv_axe_attack_loop(o)
    local m = gMarioStates[network_local_index_from_global(o.globalPlayerIndex)]

    local handPos = gVec3fZero()
    if not get_mario_anim_part_pos(m, MARIO_ANIM_PART_RIGHT_HAND, handPos) then
        vec3f_copy(handPos, m.pos)
    end

    local dist = 185.0

    local axeDir = gVec3fZero()
    vec3f_copy(axeDir, handPos)
    vec3f_sub(axeDir, m.pos)
    vec3f_normalize(axeDir)
    vec3f_mul(axeDir, 120)

    o.oPosX = handPos.x + sins(m.faceAngle.y) * coss(m.faceAngle.x) * dist
    o.oPosY = handPos.y - axeDir.y
    o.oPosZ = handPos.z + coss(m.faceAngle.y) * coss(m.faceAngle.x) * dist

    obj_process_attacks(o, bhvWapeachAxeAttacks)

    if o.oTimer == 15 then
        obj_mark_for_deletion(o)
    end
end

local id_bhvAxeAttack = hook_behavior(nil, OBJ_LIST_DESTRUCTIVE, true, bhv_axe_attack_init, bhv_axe_attack_loop, "bhvWapeachAxeAttack")

---@param m MarioState
local function act_axe_chop(m)
    local slope = -find_floor_slope(m, 0)
    m.faceAngle.x = slope
    m.marioObj.header.gfx.angle.x = slope
    if m.actionTimer == 0 then
        set_character_animation(m, CHAR_ANIM_BREAKDANCE)
        smlua_anim_util_set_animation(m.marioObj, 'wapeach_axechop')
        play_character_sound(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE)
        m.forwardVel = 0
    end

    --if m.actionTimer >= 14 and m.actionTimer <= 40 then m.marioBodyState.handState = 2 end

    if m.actionTimer == 17 then
        play_sound(SOUND_OBJ_POUNDING_LOUD, m.marioObj.header.gfx.cameraToObject)
        if m.playerIndex == 0 then
            local handPos = gVec3fZero()
            if not get_mario_anim_part_pos(m, MARIO_ANIM_PART_RIGHT_HAND, handPos) then
                vec3f_copy(handPos, m.pos)
            end
            spawn_sync_object(id_bhvAxeAttack, E_MODEL_NONE, handPos.x, handPos.y + 25, handPos.z, function(o)
                o.globalPlayerIndex = m.marioObj.globalPlayerIndex
            end)
        end
        -- shakey cam if you are close enough to petey (based on local player's camera)
        if vec3f_length(m.marioObj.header.gfx.cameraToObject) < 2000 then
            set_camera_shake_from_hit(SHAKE_SMALL_DAMAGE)
        end
    end

    if is_anim_at_end(m) ~= 0 then
        set_mario_action(m, ACT_IDLE, 0)
    end

    mario_set_forward_vel(m, approach_f32_symmetric(m.forwardVel, 0.0, 5.0))

    local step = perform_ground_step(m)

    if step == GROUND_STEP_LEFT_GROUND then
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    m.actionTimer = m.actionTimer + 1
end

---@param m MarioState
local function act_axe_spin(m)
    if m.actionTimer == 0 then
        play_character_sound(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE)
        m.forwardVel = math.clamp(m.forwardVel + 21, 0, 850)
    end

    if m.controller.buttonPressed & B_BUTTON ~= 0 then
        m.forwardVel = math.clamp(m.forwardVel + 7, 0, 850)
    end

    play_custom_anim(m, 'wapeach_axespin', math.clamp(m.forwardVel * 0x500, 0, 0x1F000))
    set_mario_particle_flags(m, PARTICLE_DUST, 0)
    if is_anim_past_frame(m, 1) ~= 0 then
        play_sound(SOUND_ACTION_SPIN, m.marioObj.header.gfx.cameraToObject)
    end

    apply_slope_accel(m)
    if m.intendedMag > 1 then
        m.faceAngle.y = approach_s16_symmetric(m.faceAngle.y, m.intendedYaw, 0x200)
    end

    m.forwardVel = m.forwardVel - 1.0
    mario_set_forward_vel(m, m.forwardVel)

    local step = perform_ground_step(m)
    if m.forwardVel < 20 and m.actionTimer >= 15 then
        return set_mario_action(m, ACT_AXE_SPIN_DIZZY, 0)
    end
    if m.forwardVel >= 100 and m.actionState == 0 then
        play_character_sound(m, CHAR_SOUND_TWIRL_BOUNCE)
        m.actionState = 1
    end
    if step == GROUND_STEP_HIT_WALL then
        set_mario_particle_flags(m, PARTICLE_TRIANGLE, 0)
        mario_bonk_reflection(m, 0)
        play_sound(SOUND_ACTION_HIT_3, m.marioObj.header.gfx.cameraToObject)

        return set_mario_action(m, ACT_AXE_SPIN_DIZZY, 0)
    end
    if step == GROUND_STEP_LEFT_GROUND then
        return set_mario_action(m, ACT_AXE_SPIN_AIR, 0)
    end

    local gfx = m.marioObj.header.gfx
    local floorAngle = atan2s(m.floor.normal.z, m.floor.normal.x)
    local floorSlope = radians_to_sm64(math.acos(m.floor.normal.y))
    local speedTilt = math.clamp(m.forwardVel * 0x80, -0x500, 0x500)
    gfx.angle.x = floorSlope * coss(floorAngle - m.faceAngle.y) + speedTilt
    gfx.angle.z = floorSlope * -sins(floorAngle - m.faceAngle.y)

    m.actionTimer = m.actionTimer + 1
end

local function act_axe_spin_air(m)
    update_air_with_turn(m)
    m.vel.y = m.vel.y + 2

    play_custom_anim(m, 'wapeach_axespin', math.clamp(m.forwardVel * 0x500, 0, 0x1F000))
    if is_anim_past_frame(m, 1) ~= 0 then
        play_sound(SOUND_ACTION_SPIN, m.marioObj.header.gfx.cameraToObject)
    end

    if m.intendedMag > 1 then
        m.faceAngle.y = approach_s16_symmetric(m.faceAngle.y, m.intendedYaw, 0x200)
    end

    m.forwardVel = math.clamp(m.forwardVel - 0.7, 0, 850)
    mario_set_forward_vel(m, m.forwardVel)

    local step = perform_air_step(m, 0)
    if m.forwardVel < 20 and m.actionTimer >= 10 then
        set_mario_action(m, ACT_THROWN_FORWARD, 0)
        return
    end
    if m.forwardVel >= 100 and m.actionState == 0 then
        play_character_sound(m, CHAR_SOUND_TWIRL_BOUNCE)
        m.actionState = 1
    end
    if step == AIR_STEP_LANDED then
        return set_mario_action(m, ACT_AXE_SPIN, 0)
    end
    if step == AIR_STEP_HIT_WALL then
        mario_bonk_reflection(m, 1)
        return set_mario_action(m, ACT_THROWN_BACKWARD, 0)
    end

    m.actionTimer = m.actionTimer + 1
end

E_MODEL_DIZZYCIRCLE = smlua_model_util_get_id("dizzy_circle_geo")

---@param o Object
local function bhv_dizzycircle_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE -- Allows you to change the position and angle
end

---@param o Object
local function bhv_dizzycircle_loop(o)
    smlua_anim_util_set_animation(o, 'dizzycircle_idle')
    local m = nearest_mario_state_to_object(o)

    o.oPosX = m.marioBodyState.headPos.x
    o.oPosY = m.marioBodyState.headPos.y + 50

    o.oPosZ = m.marioBodyState.headPos.z


    --pM = gMarioStates[network_local_index_from_global(o.globalPlayerIndex)]

    if o.oTimer > 42 then -- Deletes itself once the action changes
        obj_mark_for_deletion(o)
    end
end

local id_bhvDizzyCircle = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_dizzycircle_init, bhv_dizzycircle_loop, "bhvWapeachDizzyCircle")

local function act_axe_spin_dizzy(m)
    if m.actionTimer == 1 then
        play_character_sound(m, CHAR_SOUND_WHOA)
        -- Spawn the spin effect
        spawn_non_sync_object(id_bhvDizzyCircle, E_MODEL_DIZZYCIRCLE, m.marioBodyState.headPos.x,
            m.marioBodyState.headPos.y, m.marioBodyState.headPos.z,
            function(o)
                o.parentObj = m.marioObj
                o.globalPlayerIndex = m.marioObj.globalPlayerIndex
            end)
    end
    if m.actionTimer >= 42 then
        m.marioBodyState.eyeState = MARIO_EYES_DEAD
        set_character_animation(m, CHAR_ANIM_LAND_ON_STOMACH)
        smlua_anim_util_set_animation(m.marioObj, 'wapeach_flop')
        if m.actionTimer == 52 then
            play_sound(SOUND_ACTION_PAT_BACK, m.marioObj.header.gfx.cameraToObject)
            play_character_sound(m, CHAR_SOUND_OOOF2)
        end
        if m.actionTimer > 52 and m.actionTimer < 111 then
            apply_slope_accel(m)
            m.forwardVel = m.forwardVel * 0.95
            if m.forwardVel <= 0 then
                m.forwardVel = 0
            else
                set_mario_particle_flags(m, PARTICLE_DUST, 0)
                play_sound(SOUND_AIR_ROUGH_SLIDE, m.marioObj.header.gfx.cameraToObject)
            end
        elseif m.actionTimer >= 111 then
            m.forwardVel = 0
            if m.controller.buttonPressed & B_BUTTON ~= 0 or m.controller.buttonPressed & A_BUTTON ~= 0 then
                set_mario_action(m, ACT_FORWARD_ROLLOUT, 0)
            end
        end
    else
        apply_slope_accel(m)
        m.forwardVel = math.clamp(m.forwardVel, 0, 21)
        if is_anim_past_frame(m, 1) ~= 0 then
            play_sound(SOUND_ACTION_SPIN, m.marioObj.header.gfx.cameraToObject)
        end
        set_character_animation(m, CHAR_ANIM_BREAKDANCE)
        smlua_anim_util_set_animation(m.marioObj, 'wapeach_dizzy')
    end

    mario_set_forward_vel(m, m.forwardVel)
    local step = perform_ground_step(m)
    if step == GROUND_STEP_LEFT_GROUND then
        set_mario_action(m, ACT_THROWN_FORWARD, 0)
    end

    local gfx        = m.marioObj.header.gfx
    local floorAngle = atan2s(m.floor.normal.z, m.floor.normal.x)
    local floorSlope = radians_to_sm64(math.acos(m.floor.normal.y))
    gfx.angle.x      = floorSlope * coss(floorAngle - m.faceAngle.y)
    gfx.angle.z      = floorSlope * -sins(floorAngle - m.faceAngle.y)

    m.actionTimer    = m.actionTimer + 1
end

local axeOverrides = {
    [ACT_PUNCHING]      = ACT_AXE_CHOP,
    [ACT_MOVE_PUNCHING] = ACT_AXE_CHOP,
    [ACT_SLIDE_KICK]    = ACT_AXE_SPIN,
}

---@param m MarioState
---@param action integer
function wapeach_before_action(m, action, actionArg)
    if axeOverrides[action] then
        if (action == ACT_PUNCHING or action == ACT_MOVE_PUNCHING) and actionArg ~= 9 then return end
        return axeOverrides[action]
    end
end

hook_mario_action(ACT_AXE_CHOP, act_axe_chop)
hook_mario_action(ACT_AXE_SPIN, act_axe_spin)
hook_mario_action(ACT_AXE_SPIN_AIR, act_axe_spin_air)
hook_mario_action(ACT_AXE_SPIN_DIZZY, act_axe_spin_dizzy)
