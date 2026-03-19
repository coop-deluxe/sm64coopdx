-------------------
-- Sonic Moveset --
-------------------

if not charSelect then return end

require "anims/sonic"

-- Sonic variables for the local player only
local sPrevRings = 0
local sRingTimeBetweenDamages = 0
local sRingFlingFactor = 0
local sPrevNonSonicHealth = nil
-- SlowDownBoots decreases values for a more balanced multiplayer experience. Temporary until Balanced Movesets is applied to CS.
-- Sonic actions
_G.ACT_SONIC_SPIN_JUMP        = allocate_mario_action(ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_CONTROL_JUMP_HEIGHT | ACT_FLAG_AIR | ACT_GROUP_AIRBORNE | ACT_FLAG_ATTACKING)
_G.ACT_SONIC_FALL             = allocate_mario_action(ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_AIR | ACT_GROUP_AIRBORNE)
_G.ACT_SONIC_AIR_SPIN         = allocate_mario_action(ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_AIR | ACT_FLAG_ATTACKING | ACT_GROUP_AIRBORNE)
_G.ACT_SONIC_HOMING_ATTACK    = allocate_mario_action(ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_AIR | ACT_FLAG_ATTACKING | ACT_GROUP_AIRBORNE)
_G.ACT_SONIC_SPIN_DASH_CHARGE = allocate_mario_action(ACT_FLAG_STATIONARY | ACT_GROUP_STATIONARY | ACT_FLAG_SHORT_HITBOX)
_G.ACT_SONIC_BOUNCE_LAND      = allocate_mario_action(ACT_FLAG_STATIONARY | ACT_GROUP_STATIONARY | ACT_FLAG_SHORT_HITBOX | ACT_FLAG_ATTACKING)
_G.ACT_SONIC_SPIN_DASH        = allocate_mario_action(ACT_FLAG_MOVING | ACT_GROUP_MOVING | ACT_FLAG_SHORT_HITBOX | ACT_FLAG_ATTACKING)
_G.ACT_SONIC_RUNNING          = allocate_mario_action(ACT_FLAG_MOVING | ACT_GROUP_MOVING)

-- Sonic sounds
local SOUND_SPIN_JUMP           = audio_sample_load("z_sfx_sonic_spinjump.ogg")
local SOUND_SPIN_CHARGE         = audio_sample_load("z_sfx_sonic_spincharge.ogg")
local SOUND_SPIN_RELEASE        = audio_sample_load("z_sfx_sonic_spinrelease.ogg")
local SOUND_ROLL                = audio_sample_load("z_sfx_sonic_spinroll.ogg")
local SOUND_SONIC_BOUNCE        = audio_sample_load("z_sfx_sonic_bounce.ogg")
local SOUND_SONIC_HOMING        = audio_sample_load("z_sfx_sonic_homingselect.ogg")
local SOUND_SONIC_INSTA         = audio_sample_load("z_sfx_sonic_instashield.ogg")
local SOUND_SONIC_ELECTRIC_JUMP = audio_sample_load("z_sfx_sonic_electricjump.ogg")
local SOUND_COUNTDOWN_CD        = audio_sample_load("z_sfx_sonic_countdown.ogg")

-- Sonic textures
local TEX_HOMING_CURSOR = get_texture_info("homing-cursor")
local TEX_SONIC_RING_METER = get_texture_info("char-select-ec-sonic-ring-meter")

-- Sonic animations
local CUSTOM_CHAR_ANIM_SONIC_RUN = 'sonic_running_2'
local CUSTOM_CHAR_ANIM_SONIC_SPRING_RISE = 'sonic_spring'
local CUSTOM_CHAR_ANIM_SONIC_SPRING_FALL = 'sonic_spring_fall'
local CUSTOM_CHAR_ANIM_SONIC_BEFORE_GROUND_POUND = 'sonic_before_ground_pound'

local l = gLakituState

--- @param t number
function ease_out_quad(t)
    return 1 - (1 - t) ^ 2
end

--- @param from Vec3f
--- @param to Vec3f
--- @return integer
function pitch_to_point(from, to)
    local a = to.x - from.x
    local c = to.z - from.z
    a = math.sqrt(a * a + c * c)

    local b = -to.y
    local d = -from.y

    return atan2s(a, b - d)
end

--- @param m MarioState
--- @param accel number
--- @param lossFactor number
local function update_spin_dash_angle(m, accel, lossFactor)
    local newFacingDYaw
    local facingDYaw

    local floor = m.floor
    local slopeAngle = atan2s(floor.normal.z, floor.normal.x)
    local steepness = math.sqrt(floor.normal.x ^ 2 + floor.normal.z ^ 2)

    m.slideVelX = m.slideVelX + accel * steepness * sins(slopeAngle)
    m.slideVelZ = m.slideVelZ + accel * steepness * coss(slopeAngle)

    m.slideVelX = m.slideVelX * lossFactor
    m.slideVelZ = m.slideVelZ * lossFactor

    m.slideYaw = atan2s(m.slideVelZ, m.slideVelX)

    facingDYaw = math.s16(m.faceAngle.y - m.slideYaw)
    newFacingDYaw = facingDYaw

    if (newFacingDYaw > 0 and newFacingDYaw <= 0x4000) then
        newFacingDYaw = newFacingDYaw - 0x200
        if (newFacingDYaw < 0) then newFacingDYaw = 0 end
    elseif (newFacingDYaw >= -0x4000 and newFacingDYaw < 0) then
        newFacingDYaw = newFacingDYaw + 0x200
        if (newFacingDYaw > 0) then newFacingDYaw = 0 end
    elseif (newFacingDYaw > 0x4000 and newFacingDYaw < 0x8000) then
        newFacingDYaw = newFacingDYaw + 0x200
        if (newFacingDYaw > 0x8000) then newFacingDYaw = 0x8000 end
    elseif (newFacingDYaw > -0x8000 and newFacingDYaw < -0x4000) then
        newFacingDYaw = newFacingDYaw - 0x200
        if (newFacingDYaw < -0x8000) then newFacingDYaw = -0x8000 end
    end

    m.faceAngle.y = m.slideYaw + newFacingDYaw

    m.vel.x = m.slideVelX
    m.vel.y = 0.0
    m.vel.z = m.slideVelZ

    mario_update_moving_sand(m)
    mario_update_windy_ground(m)

    m.forwardVel = math.sqrt(m.slideVelX ^ 2 + m.slideVelZ ^ 2)
    if m.forwardVel > 256.0 then -- still dunno what we should be replacin' this with
        m.slideVelX = m.slideVelX * 256.0 / m.forwardVel
        m.slideVelZ = m.slideVelZ * 256.0 / m.forwardVel
    end

    if math.abs(newFacingDYaw) > 0x4000 then
        m.forwardVel = m.forwardVel * -1.0
    end
end

---@param m MarioState
---@param stopSpeed number
---@return integer
--[[
    Updates Sonic's spin dashing state each frame, applying additional friction or acceleration based on the surface's slipperiness.
    Also checks if speed has slowed below a threshold to end the slide.
    Returns `true` if spin dashing has stopped
]]
function update_spin_dashing(m, stopSpeed)
    local lossFactor
    local accel = 4.0
    local oldSpeed
    local newSpeed

    local stopped = 0

    local intendedDYaw = m.intendedYaw - m.slideYaw
    local forward = coss(intendedDYaw)
    local sideward = sins(intendedDYaw)

    if (forward < 0.0 and m.forwardVel >= 0.0) then
        forward = forward * (0.5 + 0.5 * m.forwardVel / 100.0)
    end

    if (m.input & INPUT_ABOVE_SLIDE) ~= 0 then accel = 8.0 end
    lossFactor = math.min(m.intendedMag / 32.0 * forward / 100 + 0.98, 1)

    oldSpeed = math.sqrt(m.slideVelX * m.slideVelX + m.slideVelZ * m.slideVelZ)

    local newSlideVelX = m.slideVelX + m.slideVelZ * (m.intendedMag / 32.0) * sideward * 0.05
    local newSlideVelZ = m.slideVelZ - m.slideVelX * (m.intendedMag / 32.0) * sideward * 0.05
    m.slideVelX = newSlideVelX
    m.slideVelZ = newSlideVelZ

    newSpeed = math.sqrt(m.slideVelX * m.slideVelX + m.slideVelZ * m.slideVelZ)

    if (oldSpeed > 0.0 and newSpeed > 0.0) then
        m.slideVelX = m.slideVelX * oldSpeed / newSpeed
        m.slideVelZ = m.slideVelZ * oldSpeed / newSpeed
    end

    update_spin_dash_angle(m, accel, lossFactor)

    if (m.playerIndex == 0 and mario_floor_is_slope(m) == 0 and math.abs(m.forwardVel) < stopSpeed) then
        mario_set_forward_vel(m, 0.0)
        stopped = 1
    end

    return stopped
end

--- @param m MarioState
local function sonic_update_air(m)
    local dragThreshold = 32
    local speedAngle = atan2s(m.vel.z, m.vel.x)

    local accel = 2
    local targetSpeed = dragThreshold
    local fVel = math.sqrt(m.vel.x ^ 2 + m.vel.z ^ 2)

    local intendedDYaw = m.faceAngle.y - speedAngle
    local intendedMag = m.intendedMag / 32

    if math.abs(intendedDYaw) > 0x4000 then
        fVel = fVel * -1
    end

    m.forwardVel = fVel

    if (check_horizontal_wind(m)) == 0 then

        if m.pos.y < m.waterLevel then
            accel = 0.5
        end

        if (m.input & INPUT_NONZERO_ANALOG) ~= 0 then
            m.faceAngle.y = m.intendedYaw

            -- Wing Cap acting like Speed Shoes.
            if (m.flags & MARIO_WING_CAP) ~= 0 then
                dragThreshold = dragThreshold * 4
                accel = accel * 2
            end

            if fVel > dragThreshold then
                targetSpeed = fVel
            else
                targetSpeed = dragThreshold
            end

            m.vel.x = approach_f32_symmetric(m.vel.x, targetSpeed * sins(m.intendedYaw) * intendedMag, accel)
            m.vel.z = approach_f32_symmetric(m.vel.z, targetSpeed * coss(m.intendedYaw) * intendedMag, accel)
        end

        --djui_chat_message_create(tostring(math.abs(speed) * sins(m.intendedYaw) * intendedMag))
    end

    local airDrag = (math.abs(fVel) / 0.125) / 256

    if m.vel.y > 0 and m.vel.y < 32 then
        m.vel.x = approach_f32_symmetric(m.vel.x, 0, airDrag)
        m.vel.z = approach_f32_symmetric(m.vel.z, 0, airDrag)
    end
end

local function update_sonic_running_speed(m)
    local e = gCharacterStates[m.playerIndex].sonic
    local maxTargetSpeed = 0
    local targetSpeed = 0
    local accel = 1.05

    if (m.floor and m.floor.type == SURFACE_SLOW) then
        maxTargetSpeed = 48
    elseif sSlowDownBoots then
        maxTargetSpeed = 40
    else
        maxTargetSpeed = 64
    end

    if m.intendedMag < 24 then
        targetSpeed = m.intendedMag
    else
        targetSpeed = maxTargetSpeed
    end

    if m.pos.y < m.waterLevel then
        targetSpeed = targetSpeed / 2
        accel = 1.025
    end

    -- Wing Cap acting like Speed Shoes.
    if (m.flags & MARIO_WING_CAP) ~= 0 then
        targetSpeed = targetSpeed * 2
        accel = accel * 2
    end

    if (m.quicksandDepth > 10.0) then
        targetSpeed = targetSpeed * (6.25 / m.quicksandDepth)
    end

    if (m.forwardVel <= 0.0) then
        m.forwardVel = m.forwardVel + accel
    elseif (m.forwardVel <= targetSpeed) then
        m.forwardVel = m.forwardVel + (accel - m.forwardVel / targetSpeed)
        --elseif (m.floor and m.floor.normal.y >= 0.95) then
        --m.forwardVel = m.forwardVel - 1.0
    end

    if m.forwardVel > 250 then
        m.forwardVel = 250
    end

    m.faceAngle.y = m.intendedYaw - approach_s32(math.s16(m.intendedYaw - m.faceAngle.y), 0, 0x800, 0x800)

    apply_slope_accel(m)
end

function set_sonic_jump_vel(m, jumpForce, initialVelY)
    local velY = 0

    if initialVelY then velY = initialVelY end

    m.vel.x = m.vel.x * m.floor.normal.y + jumpForce * m.floor.normal.x
    m.vel.z = m.vel.z * m.floor.normal.y + jumpForce * m.floor.normal.z

    m.vel.y = velY + jumpForce * m.floor.normal.y
end

-- mfw align_with_floor(m) aligns with walls
local function align_with_floor_but_better(m)
    if not m.floor then return end
    m.marioObj.header.gfx.angle.x = find_floor_slope(m, 0x8000)
    m.marioObj.header.gfx.angle.z = find_floor_slope(m, 0x4000)
end

--- @param m MarioState
--- @param walkCap number
--- @param jogCap number
--- @param runCap number
local function sonic_anim_and_audio_for_walk(m, walkCap, jogCap, runCap)
    local val14 = 0
    local val0C = true
    local val04 = 4.0

    if val14 < 4 then
        val14 = 4
    end

    if m.forwardVel > 2 then
        val04 = math.abs(m.forwardVel)
    else
        val04 = 5
    end

    if (m.quicksandDepth > 50.0) then
        val14 = (val04 / 4.0 * 0x10000)
        set_mario_anim_with_accel(m, MARIO_ANIM_MOVE_IN_QUICKSAND, val14)
        play_step_sound(m, 19, 93)
        m.actionTimer = 0
    else
        if val0C then
            if m.actionTimer == 0 then
                if (val04 > 8.0) then
                    m.actionTimer = 2
                else
                    if (val14 < 0x1000) then
                        val14 = 0x1000
                    else
                        val14 = (val04 / 4.0 * 0x10000)
                    end
                    set_mario_animation(m, MARIO_ANIM_START_TIPTOE)
                    play_step_sound(m, 7, 22)
                    if (is_anim_past_frame(m, 23)) then
                        m.actionTimer = 2
                    end

                    val0C = false
                end
            elseif m.actionTimer == 1 then
                if (val04 > 8.0) or m.intendedMag > 8.0 then
                    m.actionTimer = 2
                else
                    if (val14 < 0x1000) then
                        val14 = 0x1000
                    else
                        val14 = (val04 / 4.0 * 0x10000)
                    end
                    set_mario_animation(m, MARIO_ANIM_TIPTOE)
                    play_step_sound(m, 14, 72)

                    val0C = false
                end
            elseif m.actionTimer == 2 then
                if (val04 < 5.0) then
                    m.actionTimer = 1
                elseif (val04 > walkCap) then
                    m.actionTimer = 3
                else
                    set_mario_anim_with_accel(m, MARIO_ANIM_WALKING, 2.0 * 0x10000)
                    play_step_sound(m, 10, 49)

                    val0C = false
                end
            elseif m.actionTimer == 3 then
                if (val04 <= walkCap) then
                    m.actionTimer = 2
                else
                    if m.forwardVel > runCap then
                        play_step_sound(m, 14, 29)
                        play_custom_anim(m, CUSTOM_CHAR_ANIM_SONIC_RUN, m.forwardVel/8 * 0x8000)
                    elseif m.forwardVel > jogCap then
                        play_step_sound(m, 14, 29)
                        play_custom_anim(m, CUSTOM_CHAR_ANIM_SONIC_RUN, m.forwardVel/8 * 0x8000)
                    else
                        play_step_sound(m, 26, 58)
                        set_mario_anim_with_accel(m, MARIO_ANIM_RUNNING, m.forwardVel/2.0 * 0x8000)
                    end
                    if jogCap - val04 <= 30 and math.sign(jogCap - val04) == 1 then
                        m.marioBodyState.allowPartRotation = true
                        m.marioBodyState.torsoAngle.x = degrees_to_sm64(30 - (jogCap - val04))
                    else
                        m.marioBodyState.torsoAngle.x = 0
                        m.marioBodyState.allowPartRotation = false
                    end

                    val0C = false
                end
            end
        end
    end

    --marioObj.oMarioWalkingPitch = math.s16(approach_s32(marioObj.oMarioWalkingPitch, find_floor_slope(m, 0x8000), 0x800, 0x800))
    align_with_floor_but_better(m)
end

function badnik_bounce(m, prevHeightInput, currentGravity)
    local targetVel = math.sqrt(currentGravity * 2 * math.abs(prevHeightInput - m.pos.y))
    local trueTargetVel = 0

    if targetVel ^ 2 > m.vel.y ^ 2 then
        trueTargetVel = targetVel
    else
        trueTargetVel = math.abs(m.vel.y)
    end

    if (m.action & ACT_FLAG_AIR) ~= 0 then
        m.vel.y = trueTargetVel
    end
end

function move_with_current(m)
    if (m.flags & MARIO_METAL_CAP) ~= 0 then
        return
    end
    local step = gVec3fZero()
    vec3f_copy(m.marioObj.header.gfx.pos, m.pos)

    apply_water_current(m, step)

    m.pos.x = m.pos.x + step.x
    m.pos.y = m.pos.y + step.y
    m.pos.z = m.pos.z + step.z
end

--- @param m MarioState
--- @param landAction integer
--- @param animation MarioAnimID
--- @param stepArg integer
--- @param bonking? boolean
--- @return integer
function sonic_air_action_step(m, landAction, animation, stepArg, bonking)
    local stepResult = perform_air_step(m, stepArg)
    local fVel = math.sqrt(m.vel.x ^ 2 + m.vel.z ^ 2)
    local hSpeedAngle = atan2s(m.vel.z, m.vel.x)

    local intendedDYaw = m.faceAngle.y - hSpeedAngle

    if math.abs(intendedDYaw) > 0x4000 then
        fVel = fVel * -1
    end

    local steepness = math.sqrt(m.floor.normal.x ^ 2 + m.floor.normal.z ^ 2)
    local floorDYaw = m.floorAngle - hSpeedAngle

    --djui_chat_message_create(tostring(coss(floorDYaw)))

    if (m.action == ACT_BUBBLED and stepResult == AIR_STEP_HIT_LAVA_WALL) then
        stepResult = AIR_STEP_HIT_WALL
    end

    if stepResult == AIR_STEP_NONE then
        set_mario_animation(m, animation)
    end

    if stepResult == AIR_STEP_LANDED then

        if (check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0) then
            if math.abs(m.forwardVel) > 1 or steepness ~= 0 then
                m.faceAngle.y = atan2s(m.vel.z, m.vel.x)
                mario_set_forward_vel(m, math.sqrt(m.vel.x ^ 2 + m.vel.z ^ 2))
                if steepness ~= 0 then
                    mario_set_forward_vel(m, m.forwardVel + math.abs(m.vel.y) * steepness * coss(floorDYaw))
                end

                return set_mario_action(m, ACT_SONIC_RUNNING, 0)
            else
                m.faceAngle.y = m.faceAngle.y
                set_mario_action(m, landAction, 0)
            end
        end

    elseif stepResult == AIR_STEP_HIT_WALL and bonking then
        set_mario_animation(m, animation)

        if (m.forwardVel > 16.0) then
            queue_rumble_data_mario(m, 5, 40)
            mario_bonk_reflection(m, 0)
            m.faceAngle.y = m.faceAngle.y + 0x8000

            if (m.wall) then
                set_mario_action(m, ACT_AIR_HIT_WALL, 0)
            else
                if (m.vel.y > 0.0) then
                    m.vel.y = 0.0
                end

                mario_stop_riding_and_holding(m)
                if (m.forwardVel >= 38.0) then
                    set_mario_particle_flags(m, PARTICLE_VERTICAL_STAR, 0)
                    set_mario_action(m, ACT_BACKWARD_AIR_KB, 0)
                else
                    if (m.forwardVel > 8.0) then
                        m.forwardVel = -8.0
                    end
                    return set_mario_action(m, ACT_SOFT_BONK, 0)
                end
            end
        else
            m.forwardVel = 0.0
        end
    elseif stepResult == AIR_STEP_GRABBED_LEDGE then
        set_mario_animation(m, MARIO_ANIM_IDLE_ON_LEDGE)
        drop_and_set_mario_action(m, ACT_LEDGE_GRAB, 0)
    elseif stepResult == AIR_STEP_GRABBED_CEILING then
        set_mario_action(m, ACT_START_HANGING, 0)
    elseif stepResult == AIR_STEP_HIT_LAVA_WALL then
        lava_boost_on_wall(m)
    end

    sonic_update_air(m)

    return stepResult
end

--- @param m MarioState
--- @param target Object
--- @return integer
--- Target above the enemy.
function sonic_pitch_to_object(m, target)
    if not (m and target) then return 0 end
    local a, b, c, d
    a = target.oPosX - m.pos.x
    c = target.oPosZ - m.pos.z
    a = math.sqrt(a ^ 2 + c ^ 2)

    b = -m.pos.y
    d = -(target.oPosY + target.hitboxHeight)

    return atan2s(a, d - b)
end

local sonicActionOverride = {
    [ACT_JUMP]         = ACT_SONIC_SPIN_JUMP,
    [ACT_DOUBLE_JUMP]  = ACT_SONIC_SPIN_JUMP,
    [ACT_BACKFLIP]     = ACT_SONIC_SPIN_JUMP,
    [ACT_SIDE_FLIP]    = ACT_SONIC_SPIN_JUMP,
    [ACT_STEEP_JUMP]   = ACT_SONIC_SPIN_JUMP,
    [ACT_LONG_JUMP]    = ACT_SONIC_SPIN_JUMP,
    [ACT_WALKING]      = ACT_SONIC_RUNNING,
    [ACT_CROUCH_SLIDE] = ACT_SONIC_SPIN_DASH,
}

--- @param o Object
--- @return boolean
--- Checks if `o` is a treasure chest
local function obj_is_treasure_chest(o)
    return obj_has_behavior_id(o, id_bhvTreasureChestBottom) == 1 and o.oAction == 0
end

local breakableObjects = {
    id_bhvBreakableBox,
    id_bhvHiddenObject,
}

--- @param o Object
--- @return boolean
--- Checks if `o` is breakable
local function obj_is_breakable(o)
    for _, id_bhv in ipairs(breakableObjects) do
        if obj_has_behavior_id(o, id_bhv) ~= 0 then
            return true
        end
    end
    return false
end

local function sonic_is_obj_targetable(obj)
    return (obj_is_treasure_chest(obj) or obj_is_exclamation_box(obj) or obj_is_bully(obj) or obj_is_breakable(obj) or obj_is_attackable(obj)) and obj_is_valid_for_interaction(obj)
end

local sonicHomingLists = {
    OBJ_LIST_DEFAULT,
    OBJ_LIST_LEVEL,
    OBJ_LIST_SURFACE,
    OBJ_LIST_PUSHABLE,
    OBJ_LIST_GENACTOR,
    OBJ_LIST_DESTRUCTIVE,
}

--- @param m MarioState
--- @param distmax number
--- @return Object
--- Finds the closest target to MarioState `m` within the `distmax` units
function sonic_find_homing_target(m, distmax)
    local target
    local distmin = distmax
    local pos = gVec3fZero()
    vec3f_copy(pos, m.pos)
    for _, objList in pairs(sonicHomingLists) do
        local obj = obj_get_first(objList)
        while obj do
            if sonic_is_obj_targetable(obj) then
                local distToObj = math.sqrt((pos.x - obj.oPosX)^2 + (pos.y - obj.oPosY)^2 + (pos.z - obj.oPosZ)^2) - (m.marioObj.hitboxRadius + obj.hitboxRadius)
                local angleToObj = obj_angle_to_object(m.marioObj, obj)

                if distToObj < distmin and math.abs(m.faceAngle.y - angleToObj) < 0x3800 then
                    distmin = distToObj
                    target = obj
                end
            end
            obj = obj_get_next(obj)
        end
    end
    return target
end

--- @param m MarioState
local function perform_sonic_a_action(m)
    local o = sonic_find_homing_target(m, 700)
    local dist = dist_between_objects(m.marioObj, o)
    local e = gCharacterStates[m.playerIndex].sonic

    local fVel = math.sqrt(m.vel.x ^ 2 + m.vel.z ^ 2)
    local hSpeedAngle = atan2s(m.vel.z, m.vel.x)

    local intendedDYaw = m.faceAngle.y - hSpeedAngle

    if math.abs(intendedDYaw) > 0x4000 then
        fVel = fVel * -1
    end

    if m.pos.y < m.waterLevel then
        m.action = ACT_SONIC_SPIN_JUMP
        m.vel.y = 30
    else
        if not e.actionADone and e.instashieldTimer <= 0 then
            if o and dist < 1000 then
                set_mario_action(m, ACT_SONIC_HOMING_ATTACK, 0)
            else
                if (m.flags & MARIO_WING_CAP) ~= 0 and fVel > 110 then
                    set_mario_particle_flags(m, PARTICLE_VERTICAL_STAR, 0)
                    play_sound(SOUND_OBJ_POUNDING_CANNON, m.marioObj.header.gfx.cameraToObject)
                    play_sound(SOUND_ACTION_FLYING_FAST, m.marioObj.header.gfx.cameraToObject)
                    cur_obj_shake_screen(SHAKE_POS_LARGE)
                    set_mario_action(m, ACT_FLYING, 0)
                else
                    set_mario_action(m, ACT_SONIC_AIR_SPIN, 1)
                end
            end
        end
    end
end

--- @param m MarioState
local function perform_sonic_b_action(m)
    local e = gCharacterStates[m.playerIndex].sonic

    if (m.controller.buttonDown & Z_TRIG) ~= 0 then
        if e.bounceCooldown > 0 then return end
        set_mario_action(m, ACT_GROUND_POUND, 0)
        e.bounceCooldown = 36
    else
        if e.actionBDone then return end

        if (m.flags & MARIO_METAL_CAP) ~= 0 then
            audio_sample_play(SOUND_SONIC_ELECTRIC_JUMP, m.pos, 1)
            set_mario_action(m, ACT_SONIC_AIR_SPIN, 0)
            m.vel.y = 52
        else
            audio_sample_play(SOUND_SONIC_INSTA, m.pos, 1)
            e.instashieldTimer = 7
        end

        e.actionBDone = true
    end
end

---@param m MarioState
local function act_spin_jump(m)
    local e = gCharacterStates[m.playerIndex].sonic

    if m.actionTimer == 0 then
        audio_sample_play(SOUND_SPIN_JUMP, m.pos, 1)
        play_character_sound_if_no_flag(m, CHAR_SOUND_YAH_WAH_HOO, MARIO_ACTION_SOUND_PLAYED)

        e.prevForwardVel = m.forwardVel
    end

    local spinSpeed = math.max(0.5, e.prevForwardVel / 32)

    if e.instashieldTimer > 0 then spinSpeed = 1.5 end

    m.faceAngle.x = m.faceAngle.x + (0x2000 * spinSpeed)

    set_character_animation(m, CHAR_ANIM_A_POSE)
    local stepResult = sonic_air_action_step(m, ACT_DOUBLE_JUMP_LAND, CHAR_ANIM_A_POSE, AIR_STEP_CHECK_HANG)
    m.marioObj.header.gfx.animInfo.animID = -1

    m.marioObj.header.gfx.angle.x = m.faceAngle.x

    if (m.controller.buttonDown & Z_TRIG) ~= 0 then
        if stepResult == AIR_STEP_LANDED then
            audio_sample_play(SOUND_ROLL, m.pos, 1)
            set_mario_action(m, ACT_SONIC_SPIN_DASH, 0)
        end
    end

    if (m.controller.buttonPressed & A_BUTTON) ~= 0 and m.actionTimer > 0 then
        return perform_sonic_a_action(m)
    end

    if (m.controller.buttonPressed & B_BUTTON) ~= 0 then
        perform_sonic_b_action(m)
    end

    m.actionTimer = m.actionTimer + 1
end

-- The air dash and air roll are grouped into this.
local function act_air_spin(m)
    local e = gCharacterStates[m.playerIndex].sonic

    local spinSpeed = math.max(0.5, e.prevForwardVel / 32)

    if e.instashieldTimer > 0 then spinSpeed = 1.5 end

    m.faceAngle.x = m.faceAngle.x + (0x2000 * spinSpeed)

    set_character_animation(m, CHAR_ANIM_A_POSE)
    local stepResult = sonic_air_action_step(m, ACT_DOUBLE_JUMP_LAND, CHAR_ANIM_A_POSE, AIR_STEP_CHECK_HANG)
    m.marioObj.header.gfx.animInfo.animID = -1

    m.marioObj.header.gfx.angle.x = m.faceAngle.x

    if (m.input & INPUT_A_PRESSED) ~= 0 and m.actionTimer > 0 then
        return perform_sonic_a_action(m)
    end

    if (m.controller.buttonPressed & B_BUTTON) ~= 0 then
        return perform_sonic_b_action(m)
    end

    if m.actionArg == 1 then -- Air dash and wall bounce.
        if not e.actionADone then
            e.prevForwardVel = m.forwardVel
            audio_sample_play(SOUND_SPIN_RELEASE, m.pos, 1)
            m.vel.y = 0
            if not sSlowDownBoots then
                if m.forwardVel < 0 then
                    m.vel.x = m.vel.x + 30 * sins(m.faceAngle.y)
                    m.vel.z = m.vel.z + 30 * coss(m.faceAngle.y)
                elseif m.forwardVel < 72 then
                    m.vel.x = m.vel.x + 20 * sins(m.faceAngle.y)
                    m.vel.z = m.vel.z + 20 * coss(m.faceAngle.y)
                end
            else
                if m.forwardVel < 0 then
                    m.vel.x = m.vel.x + 20 * sins(m.faceAngle.y)
                    m.vel.z = m.vel.z + 20 * coss(m.faceAngle.y)
                elseif m.forwardVel < 50 then
                    m.vel.x = m.vel.x + 10 * sins(m.faceAngle.y)
                    m.vel.z = m.vel.z + 10 * coss(m.faceAngle.y)
                end
            end
            m.particleFlags = m.particleFlags + PARTICLE_VERTICAL_STAR
            e.actionADone = true
        end

        if m.actionTimer < 10 then

            local dist = 80
            local speedAngle = atan2s(m.vel.z, m.vel.x)
            local ray = collision_find_surface_on_ray(m.pos.x, m.pos.y + 30, m.pos.z,
            sins(speedAngle) * dist, 0, coss(speedAngle) * dist)

            if ray.surface and ray.surface.normal.y > gLevelValues.ceilNormalMaxY and ray.surface.normal.y < gLevelValues.floorNormalMinY then

                local rawWallAngle = atan2s(ray.surface.normal.z, ray.surface.normal.x)
                local wallAngle = wall_bounce(m, ray.surface.normal)
                audio_sample_play(SOUND_SONIC_BOUNCE, m.pos, 1)

                -- Count how many times you use the same wall angle, and punish accordingly
                if e.prevWallAngle ~= rawWallAngle then
                    e.wallSpam = 0
                    e.prevWallAngle = rawWallAngle
                else
                    e.wallSpam = e.wallSpam + 1
                end

                local realVelFloored = math.max(math.abs(e.realFVel), 20)
                if m.actionTimer < 2 and e.wallSpam == 0 then
                    m.vel.y = 30 * realVelFloored / HEDGEHOG_HEIGHT
                else
                    m.vel.y = 20 * realVelFloored / HEDGEHOG_HEIGHT
                end
                m.vel.y = m.vel.y - e.wallSpam
                m.vel.x = realVelFloored * sins(wallAngle)
                m.vel.z = realVelFloored * coss(wallAngle)

                m.actionArg = 0
                e.actionADone = false
            end
        end
    end

    if (m.controller.buttonDown & Z_TRIG) ~= 0 then
        if stepResult == AIR_STEP_LANDED then
            audio_sample_play(SOUND_ROLL, m.pos, 1)
            set_mario_action(m, ACT_SONIC_SPIN_DASH, 0)
        end
    end

    m.actionTimer = m.actionTimer + 1
end

--- @param m MarioState
local function act_homing_attack(m)
    local e = gCharacterStates[m.playerIndex].sonic
    local spinSpeed = math.max(0.5, e.prevForwardVel / 32)
    local o = sonic_find_homing_target(m, 700)
    local yaw, pitch

    if o == nil or m.actionTimer > 150  then
        set_mario_action(m, ACT_SONIC_FALL, 3)
        e.actionADone = true
        return 1
    end

    yaw = obj_angle_to_object(m.marioObj, o)
    if o.collisionData then
        pitch = sonic_pitch_to_object(m, o) + degrees_to_sm64(5)
    else
        pitch = sonic_pitch_to_object(m, o) - degrees_to_sm64(3)
    end

    m.vel.y = math.abs(m.forwardVel) * sins(-pitch)
    m.vel.x = math.abs(m.forwardVel) * sins(yaw) * coss(pitch)
    m.vel.z = math.abs(m.forwardVel) * coss(yaw) * coss(pitch)

    if m.actionTimer <= 0 then
        audio_sample_play(SOUND_SPIN_RELEASE, m.pos, 1)
        m.particleFlags = m.particleFlags + PARTICLE_VERTICAL_STAR
        local totalVel = math.sqrt(m.forwardVel ^ 2 + m.vel.y ^ 2)

        m.forwardVel = math.clamp(80, totalVel + 20, 172)

        m.faceAngle.y = yaw
    end

    m.faceAngle.x = m.faceAngle.x + (0x2000 * spinSpeed)

    set_character_animation(m, CHAR_ANIM_A_POSE)
    m.particleFlags = m.particleFlags + PARTICLE_DUST
    m.marioObj.header.gfx.animInfo.animID = -1

    local stepResult = perform_air_step(m, 0)
    if stepResult == AIR_STEP_LANDED then
        if m.floor.object == o and o.oInteractType == INTERACT_BREAKABLE then
            m.vel.y = math.abs(m.vel.y)
            set_mario_action(m, ACT_SONIC_FALL, 4 + math.random(4))
            play_character_sound_offset(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE, math.fmod(math.random(3, 5), 5) << 16)
            o.oInteractStatus = ATTACK_GROUND_POUND_OR_TWIRL + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)
        else
            if (m.controller.buttonDown & Z_TRIG) ~= 0 then
                audio_sample_play(SOUND_ROLL, m.pos, 1)
                set_mario_action(m, ACT_SONIC_SPIN_DASH, 0)
            else

                if (check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0) then
                    m.faceAngle.y = atan2s(m.vel.z, m.vel.x)
                    mario_set_forward_vel(m, math.sqrt(m.vel.x ^ 2 + m.vel.z ^ 2))
                    set_mario_action(m, ACT_SONIC_RUNNING, 0)
                end
            end
        end

    elseif stepResult == AIR_STEP_HIT_WALL then
        -- A failsafe in case the homing attack doesn't break boxes for some godforsaken reason.
        if m.wall ~= nil and m.wall.object ~= nil then

            -- Make sure the box is the same box we were homing on.
            if m.wall.object == o and o.oInteractType == INTERACT_BREAKABLE then
                m.vel.x = sins(m.faceAngle.y) * -16
                m.vel.z = coss(m.faceAngle.y) * -16
                if m.playerIndex == 0 then set_camera_shake_from_hit(SHAKE_ATTACK) end
                set_mario_particle_flags(m, PARTICLE_TRIANGLE, 0)
                o.oInteractStatus = ATTACK_GROUND_POUND_OR_TWIRL + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)
                set_mario_action(m, ACT_SONIC_AIR_SPIN, 0)
            end
        end
    end

    m.marioObj.header.gfx.angle.x = m.faceAngle.x

    m.actionTimer = m.actionTimer + 1
end

-- Code nabbed from Shell Rush.
function wall_bounce(m, normal)
    -- figure out direction
    local v = gVec3fZero()
    v.x = m.vel.x
    v.z = m.vel.z

    -- projection
    local parallel = vec3f_project(gVec3fZero(), v, normal)
    local perpendicular = { x = v.x - parallel.x, y = v.y - parallel.y, z = v.z - parallel.z }

    -- reflect velocity along normal
    local reflect = {
        x = perpendicular.x - parallel.x,
        y = perpendicular.y - parallel.y,
        z = perpendicular.z - parallel.z
    }

    return atan2s(reflect.z, reflect.x)
end

---@param m MarioState
local function act_spin_dash_charge(m)
    local e = gCharacterStates[m.playerIndex].sonic
    local MINDASH = 4
    local MAXDASH = HEDGEHOG_SPEED
    local decel = e.spinCharge / 32

    if (m.controller.buttonPressed & B_BUTTON) ~= 0 then
        audio_sample_play(SOUND_SPIN_CHARGE, m.pos, 1)
        e.spinCharge = math.min(e.spinCharge + 32, MAXDASH)
    else
        e.spinCharge = approach_f32_symmetric(e.spinCharge, MINDASH, decel)
    end

    set_mario_animation(m, CHAR_ANIM_A_POSE)
    m.marioObj.header.gfx.animInfo.animID = -1
    stationary_ground_step(m)

    if math.floor(e.spindashState) > 7 then
        e.spindashState = 0
    end

    m.faceAngle.y = m.intendedYaw - approach_s32(math.s16(m.intendedYaw - m.faceAngle.y), 0, 0x2000, 0x2000)
    m.marioObj.header.gfx.pos.y = m.pos.y + 60

    if m.input & INPUT_Z_DOWN == 0 then
        audio_sample_play(SOUND_SPIN_RELEASE, m.pos, 1)
        mario_set_forward_vel(m, e.spinCharge)
        e.spinCharge = 0
        l.posHSpeed = 0
        l.focHSpeed = 0
        return set_mario_action(m, ACT_SONIC_SPIN_DASH, 0)
    end
    e.spindashState = e.spindashState + e.spinCharge / 50
end

---@param m MarioState
local function act_spin_dash(m)
    local e = gCharacterStates[m.playerIndex].sonic

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_JUMP, 0)
    end

    m.faceAngle.x = m.faceAngle.x + 0x2000 * m.forwardVel / 32

    set_mario_animation(m, CHAR_ANIM_A_POSE)
    m.marioObj.header.gfx.animInfo.animID = -1
    local stepResult = perform_ground_step(m)

    if stepResult == GROUND_STEP_LEFT_GROUND then
        m.vel.y = e.groundYVel
        set_mario_action(m, ACT_SONIC_AIR_SPIN, 0)

    elseif stepResult == GROUND_STEP_HIT_WALL then
        if m.forwardVel > 64 then
            set_mario_particle_flags(m, PARTICLE_VERTICAL_STAR, 0)
            return slide_bonk(m, ACT_GROUND_BONK, ACT_GROUND_BONK)
        else
            return set_mario_action(m, ACT_CROUCHING, 0)
        end
    end

    local spinPhys = update_spin_dashing(m, 3)

    if spinPhys ~= 0 then
        return set_mario_action(m, ACT_CROUCHING, 0)
    end

    m.marioObj.header.gfx.angle.x = m.faceAngle.x

    m.marioObj.header.gfx.pos.y = m.pos.y + 60

    m.actionTimer = m.actionTimer + 1
end

--- @param m MarioState
local function act_sonic_running(m)
    local e = gCharacterStates[m.playerIndex].sonic
    mario_drop_held_object(m)

    m.actionState = 0
    update_sonic_running_speed(m)
    local stepResult = perform_ground_step(m)

    if stepResult == GROUND_STEP_LEFT_GROUND then
        m.vel.y = e.groundYVel
        set_mario_action(m, ACT_FREEFALL, 0)
        set_mario_animation(m, MARIO_ANIM_GENERAL_FALL)
    elseif stepResult == GROUND_STEP_NONE then
        sonic_anim_and_audio_for_walk(m, 10, 40, 70)
        if (m.intendedMag - m.forwardVel) > 16 then
            set_mario_particle_flags(m, PARTICLE_DUST, 0)
        end
    elseif stepResult == GROUND_STEP_HIT_WALL then
        push_or_sidle_wall(m, m.pos)
        m.actionTimer = 0
    end

    check_ledge_climb_down(m)

    if should_begin_sliding(m) ~= 0 then
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0)
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        audio_sample_play(SOUND_ROLL, m.pos, 1)
        return set_mario_action(m, ACT_CROUCH_SLIDE, 0)
    end

    if (m.input & INPUT_FIRST_PERSON) ~= 0 then
        return begin_braking_action(m)
    end

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        return set_jump_from_landing(m)
    end

    if (check_ground_dive_or_punch(m)) ~= 0 then
        return 1
    end

    if (m.input & INPUT_ZERO_MOVEMENT) ~= 0 then
        mario_set_forward_vel(m, approach_f32_symmetric(m.forwardVel, 0, 1))
        if m.forwardVel <= 0 then
            set_mario_action(m, ACT_IDLE, 0)
        end
    end

    if analog_stick_held_back(m) ~= 0 then
        return set_mario_action(m, ACT_TURNING_AROUND, 0)
    end

    return 0
end

function act_sonic_fall(m)
    local animation = 0
    local landAction = 0
    local frame = m.marioObj.header.gfx.animInfo.animFrame
    local c = gMarioStates[0].area.camera

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        return perform_sonic_a_action(m)
    end

    if (m.input & INPUT_B_PRESSED) ~= 0 then
        set_mario_action(m, ACT_SONIC_AIR_SPIN, 0)
        return perform_sonic_b_action(m)
    end


    if not m.heldObj then
        if m.actionArg == 0 then
            animation = CHAR_ANIM_GENERAL_FALL
            m.faceAngle.x = 0
        elseif m.actionArg == 1 then
            animation = CHAR_ANIM_FALL_FROM_SLIDE
            m.faceAngle.x = 0
        elseif m.actionArg == 2 then
            animation = CHAR_ANIM_FALL_FROM_SLIDE_KICK
            m.faceAngle.x = 0
        elseif m.actionArg == 3 then
            if m.vel.y > 0 then
                animation = CHAR_ANIM_DOUBLE_JUMP_RISE
            else
                animation = CHAR_ANIM_DOUBLE_JUMP_FALL
            end
            m.faceAngle.x = 0
        elseif m.actionArg == 4 then
            if m.vel.y > 0 then
                animation = CHAR_ANIM_DOUBLE_JUMP_RISE
                smlua_anim_util_set_animation(m.marioObj, CUSTOM_CHAR_ANIM_SONIC_SPRING_RISE)
            else
                animation = CHAR_ANIM_DOUBLE_JUMP_FALL
                smlua_anim_util_set_animation(m.marioObj, CUSTOM_CHAR_ANIM_SONIC_SPRING_FALL)
            end
            m.faceAngle.x = 0
        else
            local animIndex = m.actionArg - 4
            animation = CHAR_ANIM_DOUBLE_JUMP_FALL
            smlua_anim_util_set_animation(m.marioObj, 'sonic_homing_pose_' .. animIndex)

            if animIndex == 2 and in_between(frame, 8, 21, true) then
                m.marioBodyState.eyeState = MARIO_EYES_LOOK_LEFT
            elseif animIndex == 4 and frame <= 22 then
                m.marioBodyState.eyeState = MARIO_EYES_LOOK_RIGHT
            end

            m.faceAngle.x = 0
        end
        landAction = ACT_FREEFALL_LAND
    else
        animation = MARIO_ANIM_FALL_WITH_LIGHT_OBJ
        landAction = ACT_HOLD_FREEFALL_LAND
    end

    local stepResult = sonic_air_action_step(m, landAction, animation, AIR_STEP_CHECK_LEDGE_GRAB, true)

    if m.actionArg == 8 and c then
        local yaw = obj_angle_to_point(m.marioObj, c.pos.x, c.pos.z)
        local pitch = pitch_to_point(m.marioObj.header.gfx.pos, c.pos)
        local t = ease_out_quad(math.clamp((frame - 18) / 15, 0, 1))

        m.marioObj.header.gfx.angle.x = math.lerp(pitch, 0, t)
        m.marioObj.header.gfx.angle.y = math.lerp(yaw, m.faceAngle.y, t)
    end

    if (m.controller.buttonDown & Z_TRIG) ~= 0 then
        if stepResult == AIR_STEP_LANDED then
            audio_sample_play(SOUND_ROLL, m.pos, 1)
            set_mario_action(m, ACT_SONIC_SPIN_DASH, 0)
        end
    end

    m.actionTimer = m.actionTimer + 1

    return 0
end

local function act_bounce_land(m)
    m.actionState = 1
    if (m.input & INPUT_UNKNOWN_10) ~= 0 then
        return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0)
    end

    if (m.input & INPUT_OFF_FLOOR) ~= 0 then
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    stationary_ground_step(m)

    -- Changes Bounce Height
    audio_sample_play(SOUND_SONIC_BOUNCE, m.pos, 1)
    set_sonic_jump_vel(m, sSlowDownBoots and 70 or 85)
    return set_mario_action(m, ACT_SONIC_AIR_SPIN, 0)
end

local waterActions = {
    [ACT_WATER_PLUNGE]          = true,
    [ACT_WATER_IDLE]            = true,
    [ACT_FLUTTER_KICK]          = true,
    [ACT_SWIMMING_END]          = true,
    [ACT_WATER_ACTION_END]      = true,
    [ACT_HOLD_WATER_IDLE]       = true,
    [ACT_HOLD_WATER_JUMP]       = true,
    [ACT_HOLD_WATER_ACTION_END] = true,
    [ACT_BREASTSTROKE]          = true
}

local instashieldActions = {
    [ACT_SONIC_SPIN_JUMP]        = true,
    [ACT_SONIC_AIR_SPIN]         = true,
}

---@param m MarioState
---@param action integer
function before_set_sonic_action(m, action, actionArg)
    local e = gCharacterStates[m.playerIndex].sonic

    if waterActions[action] then -- Prevent swimming in the air.
        return ACT_SONIC_FALL
    end

    if sonicActionOverride[action] then
        set_sonic_jump_vel(m, 64, e.groundYVel)
        return sonicActionOverride[action]
    end

    if action == ACT_PUNCHING and actionArg == 9 then
        return ACT_SONIC_SPIN_DASH_CHARGE
    end

    if action == ACT_GROUND_POUND_LAND then
        return ACT_SONIC_BOUNCE_LAND
    end
end

function on_set_sonic_action(m)

    m.faceAngle.x = 0
    m.marioObj.header.gfx.angle.x = 0
    m.marioObj.header.gfx.prevAngle.x = 0

    if m.action == ACT_FREEFALL then
        set_mario_action(m, ACT_SONIC_FALL, m.actionArg)
    end

    if m.action == ACT_TRIPLE_JUMP then
        set_mario_action(m, ACT_SONIC_FALL, 4)
    end
end

--- @param m MarioState
function sonic_update(m)
    local e = gCharacterStates[m.playerIndex].sonic

    local groundMovingActions = {
        [ACT_SONIC_RUNNING] = 1,
        [ACT_SONIC_SPIN_DASH] = 1,
        [ACT_DECELERATING] = 1,
        [ACT_BUTT_SLIDE] = 1
    }

    if m.playerIndex == 0 and m.action == ACT_BURNING_JUMP and m.actionArg == 1 then
        local p = gPlayerSyncTable[m.playerIndex]
        sPrevRings = p.rings
    end

    if groundMovingActions[m.action] then
        local steepness = sins(find_floor_slope(m, 0x8000)) * math.sign(m.forwardVel)

        e.groundYVel = -math.sqrt(m.vel.x ^ 2 + m.vel.z ^ 2) * steepness
    else
        e.groundYVel = 0
    end

    if (m.action & ACT_FLAG_AIR) ~= 0 and m.action ~= ACT_GROUND_POUND then
        if m.vel.y >= 0 then
            e.prevHeight = m.pos.y
        end
    else
        e.prevWallAngle = -1
    end

    -- Water action sanity check in case before_set_sonic_action fails.
    if waterActions[m.action] then
        set_mario_action(m, ACT_SONIC_FALL, 0)
    end

    -- Bounce attack that's just a modified ground pound.
    if m.action == ACT_GROUND_POUND then
        smlua_anim_util_set_animation(m.marioObj, CUSTOM_CHAR_ANIM_SONIC_BEFORE_GROUND_POUND)
        if m.actionTimer > 15 then
            set_character_animation(m, CHAR_ANIM_A_POSE)
            m.marioObj.header.gfx.animInfo.animID = -1
            m.faceAngle.x = m.faceAngle.x + 0x4000
            m.marioObj.header.gfx.angle.x = m.faceAngle.x
            m.particleFlags = m.particleFlags + PARTICLE_DUST
        end

        if m.pos.y < m.waterLevel then
            m.vel.y = -60
        else
            m.vel.y = -100
        end
        m.actionTimer = m.actionTimer + 1
    end

    if e.bounceCooldown > 0 then
        e.bounceCooldown = e.bounceCooldown - 1
        if e.bounceCooldown == 0 then
            play_sound(SOUND_MENU_YOSHI_GAIN_LIVES, gGlobalSoundSource)
            set_mario_particle_flags(m, PARTICLE_SPARKLES, 0)
        end
    end

    if (m.action & ACT_FLAG_AIR) == 0 and m.action ~= ACT_SONIC_BOUNCE_LAND then
        e.actionADone = false
        e.actionBDone = false
        e.bounceCooldown = 0
        e.instashieldTimer = 0
    end

    -- Splash.
    if m.pos.y <= m.waterLevel and m.pos.y >= m.waterLevel - math.abs(m.vel.y) then
        if math.abs(m.vel.y) > 40 then
            m.particleFlags = m.particleFlags + PARTICLE_WATER_SPLASH
            play_sound(SOUND_ACTION_UNKNOWN430, m.marioObj.header.gfx.cameraToObject)
        elseif math.abs(m.vel.y) > 0 then
            m.particleFlags = m.particleFlags + PARTICLE_SHALLOW_WATER_SPLASH
        end
    end

    -- Fall damage delay.
    if e.peakHeight - m.pos.y < 2000 then m.peakHeight = m.pos.y end
    if m.vel.y >= 0 or m.pos.y == m.floorHeight then e.peakHeight = m.pos.y end

    sonic_instashield_interactions(m, e)

    -- Restore oxygen if Sonic is dead to prevent a death loop after respawning
    if m.health <= 0xFF then
        e.oxygen = 900
    elseif m.action ~= ACT_BUBBLED and (m.action & ACT_GROUP_CUTSCENE) == 0 then
        sonic_drowning(m, e)
    end

    sonic_ring_health(m, e)

    e.instashieldTimer = e.instashieldTimer - 1
end

function sonic_instashield_interactions(m, e)

    -- Insta-shield attack. The best way I can do it for now.
    if e.instashieldTimer > 0 and instashieldActions[m.action] then
        for objList = 0, NUM_OBJ_LISTS - 1 do
            local obj = obj_get_first(objList)
            while obj ~= nil do
                if (obj_is_attackable(obj) or obj_is_bully(obj) or obj_is_breakable_object(obj) or obj_has_behavior_id(obj, id_bhvBobomb) ~= 0) then
                    if (dist_between_objects(m.marioObj, obj) <= 280 and obj_is_valid_for_interaction(obj)) then

                        -- Kicks the object and send it flying
                        obj.oInteractStatus = ATTACK_KICK_OR_TRIP + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)
                        obj.oFaceAngleYaw = obj_angle_to_point(obj, m.pos.x, m.pos.z)
                        obj.oMoveAngleYaw = math.s16(obj.oFaceAngleYaw + 0x8000)
                        obj.oVelX = 60 * sins(obj.oMoveAngleYaw)
                        obj.oVelZ = 60 * coss(obj.oMoveAngleYaw)
                        obj.oForwardVel = 60

                        -- Stops momentum on impact
                        mario_set_forward_vel(m, 0)
                        if m.playerIndex == 0 then set_camera_shake_from_hit(SHAKE_ATTACK) end
                        set_mario_particle_flags(m, PARTICLE_TRIANGLE, 0)
                        play_sound(SOUND_ACTION_HIT_2, m.marioObj.header.gfx.cameraToObject)
                    end
                end

                obj = obj_get_next(obj)
            end
        end

        --[[local m2 = nearest_mario_state_to_object(m.marioObj)

        if m2 ~= nil and m2.playerIndex ~= m.playerIndex then
            if (dist_between_objects(m.marioObj, m2.marioObj) <= 200 and passes_pvp_interaction_checks(m, m2)) then
                local angleToSonic = mario_obj_angle_to_object(m2, m.marioObj)
                local facingDYaw = angleToSonic - m2.faceAngle.y

                local sign = 1
                local kbAct = ACT_HARD_FORWARD_AIR_KB

                if math.abs(facingDYaw) <= 0x4000 then
                    sign = -1
                    kbAct = ACT_HARD_BACKWARD_AIR_KB
                end
                
                local speed = gServerSettings.playerKnockbackStrength * sign * 50
                
                m2.marioObj.oInteractStatus = ATTACK_KICK_OR_TRIP + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)

                m2.faceAngle.y = angleToSonic * -sign
                m2.vel.y = 25
                set_mario_action(m2, kbAct, 0)
                mario_set_forward_vel(m2, speed)
                
                mario_set_forward_vel(m, 0)
                if m.playerIndex == 0 then set_camera_shake_from_hit(SHAKE_ATTACK) end
                set_mario_particle_flags(m, PARTICLE_TRIANGLE, 0)
                play_sound(SOUND_ACTION_HIT_2, m.marioObj.header.gfx.cameraToObject)

                return true
            end
        end]]
        
    end
end

local showHealth = 0
local function sonic_set_alive(m)
    if m.playerIndex == 0 and sPrevNonSonicHealth == nil then
        sPrevNonSonicHealth = m.health
    end
    m.health = showHealth > 0 and 0x700 or 0x880
end

local function sonic_set_dead(m)
    if m.playerIndex == 0 then
        sPrevNonSonicHealth = nil
    end
    m.health = 0xFF
end

function sonic_things_for_non_sonic_chars(m)
    -- Only run for the local player.
    if m.playerIndex ~= 0 then return end
    -- Only run if you're not sonic
    if gCSPlayers[m.playerIndex].movesetToggle or character_get_current_number(m.playerIndex) == CT_SONIC then return end

    -- Clear rings even when you're not Sonic.
    if m.hurtCounter > 0 then
        gPlayerSyncTable[0].rings = 0
    end

    -- Restore previous health if not Sonic
    if sPrevNonSonicHealth ~= nil then
        m.health = sPrevNonSonicHealth
        sPrevNonSonicHealth = nil
    end
end

function sonic_drowning(m, e)
    if m.health <= 0xFF then return end
    local p = gPlayerSyncTable[m.playerIndex]

    local warning = {
        [750] = true, -- 25 seconds
        [600] = true, -- 20 seconds
        [450] = true -- 15 seconds
    }
    local getOutNow = {
        [360] = 5, -- 12 seconds
        [300] = 4, -- 10 seconds
        [240] = 3, -- 8 seconds
        [180] = 2, -- 6 seconds
        [120] = 1, -- 4 seconds
        [60] = 0 -- 2 seconds
    }

    if e.oxygen <= 0 then
        sonic_set_dead(m)

        -- Empty rings and hide rings meter
        if m.playerIndex == 0 then
            p.rings = 0
        end

        if (m.input & INPUT_IN_POISON_GAS) ~= 0 then
            set_mario_action(m, ACT_SUFFOCATION, 0)
        else
            set_mario_action(m, ACT_DROWNING, 0)
        end
        return
    end

    if m.pos.y + m.marioObj.hitboxHeight - 50 < m.waterLevel or (m.input & INPUT_IN_POISON_GAS) ~= 0 then
        sonic_set_alive(m)
        e.oxygen = e.oxygen - 1

        if m.playerIndex == 0 then
            if warning[e.oxygen] then
                play_sound(SOUND_MOVING_ALMOST_DROWNING, m.marioObj.header.gfx.cameraToObject)
            elseif getOutNow[e.oxygen] then
                audio_sample_play(SOUND_COUNTDOWN_CD, m.pos, 2)
                spawn_orange_number(getOutNow[e.oxygen], 0, 100, 0)
            end
        end
        --djui_chat_message_create(tostring(e.oxygen))
    else
        e.oxygen = 900
    end
end

function sonic_ring_health(m, e)
    if m.playerIndex ~= 0 then return end
    local p = gPlayerSyncTable[0]
    local realFlingFactor = math.clamp(math.sqrt(sRingFlingFactor ^ 2 + (m.hurtCounter / 4) ^ 2), 1, 8)

    --djui_chat_message_create(tostring(realFlingFactor))

    --if (m.controller.buttonPressed & X_BUTTON) ~= 0 then p.rings = p.rings + 20 end

    if m.health > 0xFF then
        sonic_set_alive(m)
    else
        sonic_set_dead(m)
    end

    if m.hurtCounter > 0 then
        if p.rings > 32 then p.rings = 32 end
        m.hurtCounter = 0

        if p.rings > 0 then
            for i = 0, p.rings - 1, 1 do

                -- Near ground, send rings upwards only
                local minY, maxY, flingFactorY
                if m.pos.y < m.floorHeight + 100 then
                    minY, maxY, flingFactorY = 20, 30, math.max(1, realFlingFactor / 2)
                else
                    minY, maxY, flingFactorY = -10, 15, realFlingFactor
                end

                spawn_sync_object(
                    id_bhvSonicRing,
                    E_MODEL_YELLOW_COIN,
                    m.pos.x, m.pos.y, m.pos.z,
                    function (o)
                        o.oVelY = math.random(minY, maxY) * flingFactorY
                        o.oForwardVel = math.random(5, 10) * realFlingFactor
                        o.oMoveAngleYaw = random_u16()
                    end
                )
            end
            sonic_set_alive(m)
        else
            sonic_set_dead(m)
        end

        if sRingTimeBetweenDamages > 0 then sRingFlingFactor = sRingFlingFactor + 1 end

        p.rings = 0
        sRingTimeBetweenDamages = 240 -- 8 seconds
    end

    if sRingTimeBetweenDamages <= 0 then sRingFlingFactor = 0 end

    local burnActions = {
        [ACT_BURNING_JUMP] = true,
        [ACT_BURNING_FALL] = true,
        [ACT_BURNING_GROUND] = true
    }

    if burnActions[m.action] then
        if sPrevRings > 0 then
            sonic_set_alive(m)
        end
        if p.rings > 0 then
            showHealth = 90
            spawn_sync_object(
                id_bhvSonicRing,
                E_MODEL_YELLOW_COIN,
                m.pos.x, m.pos.y, m.pos.z,
                function (o)
                    o.oVelY = math.random(20, 40)
                    o.oForwardVel = math.random(15, 30)
                    o.oMoveAngleYaw = m.faceAngle.y + 0x8000 + degrees_to_sm64(math.random(-30, 30))
                    o.oTimer = 100
                end)
            p.rings = p.rings - 1
        end

        if m.action == ACT_BURNING_JUMP and m.actionArg == 1 then
            djui_chat_message_create(tostring(m.actionArg))
            if sPrevRings == 0 then
                sonic_set_dead(m)
            else
                sonic_set_alive(m)
            end
        end
    end

    -- Disable fall damage if no rings.
    if p.rings <= 0 then m.peakHeight = m.pos.y end

    sRingTimeBetweenDamages = sRingTimeBetweenDamages - 1
end

function sonic_value_refresh(m)
    local m = type(m) == "table" and m or gMarioStates[0] -- Fall back to local index
    local e = gCharacterStates[m.playerIndex].sonic
    local p = gPlayerSyncTable[m.playerIndex]
    local level = gNetworkPlayers[m.playerIndex].currLevelNum
    local bowserFight = (obj_get_first_with_behavior_id(id_bhvBowser) ~= nil
    or (level == LEVEL_BOWSER_1 or level == LEVEL_BOWSER_2 or level == LEVEL_BOWSER_3))
    e.oxygen = 900
    p.rings = (GAMEMODE_ACTIVE or bowserFight) and 10 or 0
end

local bounceTypes = {
    [INTERACT_BOUNCE_TOP]  = true,
    [INTERACT_BOUNCE_TOP2] = true,
    [INTERACT_KOOPA]       = true
}

function sonic_allow_interact(m, o, intType)
    local e = gCharacterStates[m.playerIndex].sonic

    if e.instashieldTimer > 0 and instashieldActions[m.action] then
        return false
    end

    if bounceTypes[intType] then
        e.prevVelY = m.vel.y
    end

    if bounceTypes[intType] and (o.oInteractionSubtype & INT_SUBTYPE_TWIRL_BOUNCE) == 0 then
        if m.action == ACT_SONIC_HOMING_ATTACK then
            if m.vel.y < 0 then
                m.vel.y = math.abs(m.vel.y)
            end
            set_mario_action(m, ACT_SONIC_FALL, 4 + math.random(4))
            play_character_sound_offset(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE, math.fmod(math.random(3, 5), 5) << 16)
            o.oInteractStatus = ATTACK_GROUND_POUND_OR_TWIRL + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)
            return false
        end
    end

    if intType == INTERACT_POLE then
        if m.action == ACT_SONIC_HOMING_ATTACK then
            return false
        end
    end
end

local badnikBounceActions = {
    [ACT_SONIC_SPIN_JUMP] = true,
    [ACT_SONIC_FALL] = true,
    [ACT_SONIC_AIR_SPIN] = true,
    [ACT_GROUND_POUND] = true,
}

function sonic_on_interact(m, o, intType)
    local e = gCharacterStates[m.playerIndex].sonic
    if (m.action == ACT_SONIC_RUNNING) and not m.heldObj and m.pos.y + 80 >= m.waterLevel then
        if obj_has_behavior_id(o, id_bhvDoorWarp) ~= 0 then
            set_mario_action(m, ACT_DECELERATING, 0)
            interact_warp_door(m, 0, o)
        elseif obj_has_behavior_id(o, id_bhvDoor) ~= 0 or obj_has_behavior_id(o, id_bhvStarDoor) ~= 0 then
            set_mario_action(m, ACT_DECELERATING, 0)
            interact_door(m, 0, o)
        end
    end

    if bounceTypes[intType] and (o.oInteractionSubtype & INT_SUBTYPE_TWIRL_BOUNCE) == 0 then
        if e.prevVelY < 0 and m.pos.y > o.oPosY then
            if badnikBounceActions[m.action] then
                if m.action == ACT_GROUND_POUND then
                    o.oInteractStatus = ATTACK_GROUND_POUND_OR_TWIRL + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)
                    set_mario_particle_flags(m, PARTICLE_HORIZONTAL_STAR, 0)
                    play_sound(SOUND_ACTION_HIT_2, m.marioObj.header.gfx.cameraToObject)
                    set_mario_action(m, ACT_SONIC_AIR_SPIN, 0)
                else
                    o.oInteractStatus = ATTACK_FROM_ABOVE + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)
                end

                badnik_bounce(m, e.prevHeight, 4)
            end
        end
    end

    if intType == INTERACT_BREAKABLE then
        if m.action == ACT_SONIC_HOMING_ATTACK then
            set_mario_action(m, ACT_SONIC_AIR_SPIN, 0)
        end
    end

    if intType == INTERACT_STAR_OR_KEY then
        e.oxygen = 900
    end
end

-- Around here is unused code for slope flinging that's pretty broken. It's currently disabled, but the code will be here in case the feature is revisited.
local FLOOR_LOWER_LIMIT = gLevelValues.floorLowerLimit - gLevelValues.cellHeightLimit

local function sonic_slope_detach(m, nextPos)
    local e = gCharacterStates[m.playerIndex].sonic
    local floorDYaw = m.floorAngle - m.faceAngle.y

    --m.marioObj.header.gfx.angle.x = find_floor_slope(m, 0x8000)
    --m.marioObj.header.gfx.angle.z = find_floor_slope(m, 0x4000)

    local dist = -30
    local ray = collision_find_surface_on_ray(nextPos.x, m.pos.y + 200, nextPos.z, 0, FLOOR_LOWER_LIMIT, 0)

    local detach = false

    if ray.surface ~= nil then

        -- Downwards slopes are still affected.
        local nextNormal = (math.sqrt(ray.surface.normal.x ^ 2 + ray.surface.normal.z ^ 2)) * 90 * - coss(floorDYaw)
        local curNormal =  (math.sqrt(m.floor.normal.x ^ 2 + m.floor.normal.z ^ 2)) * 90 * - coss(floorDYaw)

        djui_chat_message_create(tostring(nextNormal) .. "," .. tostring(curNormal))

        if curNormal - nextNormal >= 20 and nextNormal >= 0 then
            detach = true
        end
    end

    return detach
end

local function perform_ground_quarter_step(m, nextPos)
    local lowerWcd = collision_get_temp_wall_collision_data()
    local upperWcd = collision_get_temp_wall_collision_data()

    local ceil = collision_find_ceil(nextPos.x, nextPos.y, nextPos.z)
    local floor = collision_find_floor(nextPos.x, nextPos.y, nextPos.z)

    local floorHeight = find_floor_height(nextPos.x, nextPos.y, nextPos.z)
    local ceilHeight = find_ceil_height(nextPos.x, nextPos.y, nextPos.z)

    local waterLevel = find_water_level(nextPos.x, nextPos.z)

    local detach = sonic_slope_detach(m, nextPos)

    lowerWcd = resolve_and_return_wall_collisions_data(nextPos, 30.0, 24.0, lowerWcd)
    upperWcd = resolve_and_return_wall_collisions_data(nextPos, 60.0, 50.0, upperWcd)

    mario_update_wall(m, upperWcd)

    if (floor == nil) then
        if (gServerSettings.bouncyLevelBounds == BOUNCY_LEVEL_BOUNDS_OFF) then
            m.faceAngle.y = m.faceAngle.y + 0x8000
            --mario_set_forward_vel(m, gServerSettings.bouncyLevelBounds == BOUNCY_LEVEL_BOUNDS_ON_CAP ? clamp(1.5f * m.forwardVel, -500, 500) : 1.5f * m.forwardVel)
        end
        return GROUND_STEP_HIT_WALL_STOP_QSTEPS
    end

    if ((m.action & ACT_FLAG_RIDING_SHELL) ~= 0 and floorHeight < waterLevel) then
        local allow = true
        if (allow == true) then
            floorHeight = waterLevel
            floor = gWaterSurfacePseudoFloor
            floor.originOffset = floorHeight --! Wrong origin offset (no effect)
        end
    end

    if (nextPos.y > floorHeight + 100.0) then
        if (nextPos.y + m.marioObj.hitboxHeight >= ceilHeight) then
            return GROUND_STEP_HIT_WALL_STOP_QSTEPS
        end

        vec3f_copy(m.pos, nextPos)
        m.floor = floor
        m.floorHeight = floorHeight
        return GROUND_STEP_LEFT_GROUND
    end

    if detach == true then
        m.floor = floor
        m.floorHeight = floorHeight
        return GROUND_STEP_LEFT_GROUND
    end

    if (floorHeight + m.marioObj.hitboxHeight >= ceilHeight) then
        return GROUND_STEP_HIT_WALL_STOP_QSTEPS
    end

    vec3f_set(m.pos, nextPos.x, floorHeight, nextPos.z)
    m.floor = floor
    m.floorHeight = floorHeight

    if (upperWcd.numWalls > 0) then
        for i = 0, upperWcd.numWalls, 1 do
            if (gLevelValues.fixCollisionBugs ~= true) then
                i = (upperWcd.numWalls - 1)
            end
            local wall = upperWcd.walls[i]
            local wallDYaw = atan2s(wall.normal.z, wall.normal.x) - m.faceAngle.y

            if (wallDYaw >= 0x2AAA and wallDYaw <= 0x5555) then
                -- nothing
            elseif (wallDYaw <= -0x2AAA and wallDYaw >= -0x5555) then
                -- nothing
            else
                return GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS
            end
        end
    end

    return GROUND_STEP_NONE
end

local function sonic_perform_ground_step(m)
    local i = 0
    local stepResult
    local intendedPos = {x = 0, y = 0, z = 0}

    local returnValue = 0
    --if (smlua_call_event_hooks_mario_param_and_int_ret_int(HOOK_BEFORE_PHYS_STEP, m, STEP_TYPE_GROUND, &returnValue)) return returnValue

    for i = 0, 4, 1 do
        local step = {x = 0, y = 0, z = 0}
        if (m.floor ~= nil) then
            local floorNormal = m.floor.normal.y
            step.x = floorNormal * (m.vel.x / 4.0)
            step.z = floorNormal * (m.vel.z / 4.0)
        end

        intendedPos.x = m.pos.x + step.x
        intendedPos.y = m.pos.y
        intendedPos.z = m.pos.z + step.z

        vec3f_normalize(step)

        gFindWallDirectionActive = true
        stepResult = perform_ground_quarter_step(m, intendedPos)
        gFindWallDirectionActive = false

        if (stepResult == GROUND_STEP_LEFT_GROUND or stepResult == GROUND_STEP_HIT_WALL_STOP_QSTEPS) then
            break
        end
    end

    m.terrainSoundAddend = mario_get_terrain_sound_addend(m)
    vec3f_copy(m.marioObj.header.gfx.pos, m.pos)
    vec3s_set(m.marioObj.header.gfx.angle, 0, m.faceAngle.y, 0)

    if (stepResult == GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS) then
        stepResult = GROUND_STEP_HIT_WALL
    end
    return stepResult
end

function sonic_before_phys_step(m, stepType, stepArg)
    local e = gCharacterStates[m.playerIndex].sonic

    if m.pos.y < m.waterLevel then
        move_with_current(m)
        if (m.action & ACT_FLAG_AIR) ~= 0 then
            m.vel.y = m.vel.y + 2
        end
    end

    if e.physTimer > 0 then
        e.realFVel = math.sqrt((m.pos.x - e.lastforwardPos.x) ^ 2 + (m.pos.z - e.lastforwardPos.z) ^ 2)
        local speedAngle = atan2s(m.vel.z, m.vel.x)
        local intendedDYaw = m.faceAngle.y - speedAngle

        if math.abs(intendedDYaw) > 0x4000 then
            e.realFVel = e.realFVel * -1
        end

        vec3f_copy(e.lastforwardPos, m.pos)

        e.physTimer = 0
    end

    --[[if stepType == STEP_TYPE_GROUND then
        return sonic_perform_ground_step(m)
    end]]

    --djui_chat_message_create(tostring(m.floor.normal.x) .. ", " .. tostring(m.floor.normal.y) .. ", " .. tostring(m.floor.normal.z))
    e.physTimer = e.physTimer + 1
end

function sonic_allow_water(m, inWater)
    if not inWater then
        return false
    end
end

---------------
-- Sonic HUD --
---------------

local homingActs = {
    [ACT_SONIC_SPIN_JUMP]     = true,
    [ACT_SONIC_AIR_SPIN]      = true,
    [ACT_SONIC_FALL]    = true,
    [ACT_SONIC_HOMING_ATTACK] = true,
}

local homingCursorScaleTimer = 0
local homingCursorPrevScale = 1
local homingCursorPrevHudPos = gVec3fZero()
local homingCursorPrevTarget

function sonic_homing_hud()
    djui_hud_set_resolution(RESOLUTION_N64)
    local color = network_player_get_palette_color(gNetworkPlayers[0], CAP)
    djui_hud_set_color(color.r, color.g, color.b, 255)
    local m = gMarioStates[0]
    local e = gCharacterStates[m.playerIndex].sonic

    if homingActs[m.action] then
        -- HUD detection range is slightly shorter to guarantee homing accuracy.
        local o = sonic_find_homing_target(m, 695)

        if o and not e.actionADone then
            local pos = gVec3fZero()
            homingCursorScaleTimer = homingCursorScaleTimer + 1

            if homingCursorPrevTarget ~= o then
                homingCursorPrevTarget = o
                audio_sample_play(SOUND_SONIC_HOMING, l.pos, 3)
            end

            object_pos_to_vec3f(pos, o)
            local hudPos = gVec3fZero()
            local onScreen = djui_hud_world_pos_to_screen_pos(pos, hudPos)
            if onScreen then
                local scale = (((math.sin(homingCursorScaleTimer / 5) / 16) + 1)) * (-300 / hudPos.z * djui_hud_get_fov_coeff())
                djui_hud_render_texture_interpolated(TEX_HOMING_CURSOR, homingCursorPrevHudPos.x - 64 * homingCursorPrevScale, homingCursorPrevHudPos.y - 64 * homingCursorPrevScale, 8 * homingCursorPrevScale, 8 * homingCursorPrevScale, hudPos.x - 64 * scale, hudPos.y - 64 * scale, 8 * scale, 8 * scale)
                vec3f_copy(homingCursorPrevHudPos, hudPos)
                homingCursorPrevScale = scale
            end
        else
            homingCursorScaleTimer = 0
            homingCursorPrevScale = 1
            homingCursorPrevTarget = nil
        end
    else
        homingCursorScaleTimer = 0
        homingCursorPrevScale = 1
        homingCursorPrevTarget = nil
    end

    -- If not in a homing state, set the homing cursor previous pos on Sonic
    -- It will make the cursor smoothly move from Sonic instead of out of nowhere
    if homingCursorPrevTarget == nil then
        local hudPos = gVec3fZero()
        local onScreen = djui_hud_world_pos_to_screen_pos(m.pos, hudPos)
        if onScreen then
            vec3f_copy(homingCursorPrevHudPos, hudPos)
        end
    end
end

sonicVanillaMeter = {
    label = {
        left = get_texture_info("char-select-ec-sonic-meter-left"),
        right = get_texture_info("char-select-ec-sonic-meter-right"),
    },
    pie = {
        get_texture_info("char_select_custom_meter_pie1"),
        get_texture_info("char_select_custom_meter_pie2"),
        get_texture_info("char_select_custom_meter_pie3"),
        get_texture_info("char_select_custom_meter_pie4"),
        get_texture_info("char_select_custom_meter_pie5"),
        get_texture_info("char_select_custom_meter_pie6"),
        get_texture_info("char_select_custom_meter_pie7"),
        get_texture_info("char_select_custom_meter_pie8"),
    }
}

function sonic_health_meter(localIndex, health, prevX, prevY, prevScaleW, prevScaleH, x, y, scaleW, scaleH)
    local m = gMarioStates[localIndex]
    local p = gPlayerSyncTable[localIndex]
    local prevScaleW = prevScaleW/64
    local prevScaleH = prevScaleH/64
    local scaleW = scaleW/64
    local scaleH = scaleH/64
    if gCSPlayers[m.playerIndex].movesetToggle then
        local djuiFont = djui_hud_get_font()
        local djuiColor = djui_hud_get_color()
        djui_hud_set_font(FONT_RECOLOR_HUD)

        djui_hud_render_texture_interpolated(TEX_SONIC_RING_METER, prevX, prevY, prevScaleW, prevScaleH, x, y, scaleW, scaleH)

        showHealth = showHealth - 1
        djui_hud_set_color(255 * djuiColor.r/255, 255 * djuiColor.g/255, 0, djuiColor.a)
        if p.rings == 0 then
            if math.floor(get_global_timer()%30 / 15) == 1 then
                djui_hud_set_color(255 * djuiColor.r/255, 0, 0, djuiColor.a)
            end
            showHealth = 150
        end
        local rings = tostring(p.rings)
        djui_hud_print_text_interpolated(rings, prevX + (31 - djui_hud_measure_text(rings)*0.25)*prevScaleW, prevY + 25*prevScaleH, prevScaleH*0.5, x + (31 - djui_hud_measure_text(rings)*0.25)*prevScaleW, y + 25*prevScaleH, scaleH*0.5)

        -- Clean up after we're done
        djui_hud_set_font(djuiFont)
        djui_hud_set_color(djuiColor.r, djuiColor.g, djuiColor.b, djuiColor.a)
    else
        health = health >> 8
        local tex = sonicVanillaMeter.label.left
        djui_hud_render_texture_interpolated(tex, prevX, prevY, prevScaleW, prevScaleH, x, y, scaleW, scaleH)
        tex = sonicVanillaMeter.label.right
        djui_hud_render_texture_interpolated(tex, prevX + 31*prevScaleW, prevY, prevScaleW, prevScaleH, x + 31*scaleW, y, scaleW, scaleH)
        if health > 0 then
            tex = sonicVanillaMeter.pie[health]
            djui_hud_render_texture_interpolated(tex, prevX + 15*prevScaleW, prevY + 16*scaleH, prevScaleW, prevScaleH, x + 15*scaleW, y + 16*scaleH, scaleW, scaleH)
        end
    end
end

-- Removes Sonic's defacto speed on slopes.

--- @param m MarioState
function sonic_defacto_fix(m)
    local floorDYaw = m.floorAngle - m.faceAngle.y
    if (m.floor.normal.y < 0.9 and (math.abs(floorDYaw) <= 0x4500 and math.abs(floorDYaw) >= 0x3500)) then
        return math.max(math.abs(sins(floorDYaw)), m.floor.normal.y)
    end
    return m.floor.normal.y
end

-- Mute health meter sounds
function sonic_on_play_sound(soundBits, pos)
    if soundBits == SOUND_MENU_POWER_METER then
        return NO_SOUND
    end
end

hook_mario_action(ACT_SONIC_SPIN_JUMP, act_spin_jump)
hook_mario_action(ACT_SONIC_SPIN_DASH_CHARGE, act_spin_dash_charge, INT_FAST_ATTACK_OR_SHELL)
hook_mario_action(ACT_SONIC_SPIN_DASH, act_spin_dash, INT_FAST_ATTACK_OR_SHELL)
hook_mario_action(ACT_SONIC_RUNNING, act_sonic_running)
hook_mario_action(ACT_SONIC_FALL, act_sonic_fall)
hook_mario_action(ACT_SONIC_AIR_SPIN, act_air_spin)
hook_mario_action(ACT_SONIC_HOMING_ATTACK, { every_frame = act_homing_attack, gravity = function () end }, (INT_FAST_ATTACK_OR_SHELL | INT_KICK | INT_HIT_FROM_ABOVE))
hook_mario_action(ACT_SONIC_BOUNCE_LAND, act_bounce_land, INT_GROUND_POUND_OR_TWIRL)

hook_event(HOOK_ON_DEATH, sonic_value_refresh)
hook_event(HOOK_ON_LEVEL_INIT, sonic_value_refresh)
hook_event(HOOK_MARIO_UPDATE, sonic_things_for_non_sonic_chars)

-- Ring object.

local function bhv_ring_init(o)
    o.oFlags = (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)

    -- hitbox
    o.oInteractType = INTERACT_COIN
    o.oHealth = 0
    o.oNumLootCoins = 0
    o.hitboxRadius = 100
    o.hitboxHeight = 64
    o.hitboxDownOffset = 0
    o.oGravity = -2
    o.oBounciness = -0.95
    o.oIntangibleTimer = 60

    obj_set_billboard(o)
end

local function bhv_ring_loop(o)
    local sp1C = o.oFloor
    local sp1A
    cur_obj_update_floor_and_walls()
    cur_obj_if_hit_wall_bounce_away()
    cur_obj_move_standard(-62)

    --if o.oIntangibleTimer > 0 then o.oIntangibleTimer = o.oIntangibleTimer - 1 end

    if (o.oMoveFlags & OBJ_MOVE_LANDED) ~= 0 then
        if (o.oMoveFlags & (OBJ_MOVE_ABOVE_DEATH_BARRIER)) ~= 0 then
            obj_mark_for_deletion(o)
        end
    end

    if (o.oMoveFlags & OBJ_MOVE_BOUNCE) ~= 0 then
        --cur_obj_play_sound_2(SOUND_GENERAL_COIN_DROP)
        play_sound_with_freq_scale(SOUND_GENERAL_COIN_DROP, o.header.gfx.cameraToObject, math.random(980, 1030) / 1000)

        if (sp1C ~= nil and sp1C.normal.y < 0.9) then
            sp1A = atan2s(sp1C.normal.z, sp1C.normal.x)
            cur_obj_rotate_yaw_toward(sp1A, 0x400)
        end
    end

    if (o.oInteractStatus & INT_STATUS_INTERACTED) ~= 0 then
        obj_mark_for_deletion(o)
        spawn_non_sync_object(
            id_bhvCoinSparkles,
            E_MODEL_SPARKLES,
            o.oPosX, o.oPosY, o.oPosZ,
            nil)
    end

    if (cur_obj_wait_then_blink(150, 20) ~= 0) then
        obj_mark_for_deletion(o)
    end

    o.oAnimState = o.oAnimState + 1
end

function ringteract(m, o, intType) -- This is the ring interaction for ALL characters.
    local e = gCharacterStates[m.playerIndex].sonic
    local p = gPlayerSyncTable[m.playerIndex]

    if obj_has_behavior_id(o, id_bhvSonicRing) ~= 0 then
        m.healCounter = m.healCounter + 4
        if m.playerIndex == 0 then
            p.rings = p.rings + 1
            if m.action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER) ~= 0 then
                play_sound(SOUND_GENERAL_COIN_WATER, m.marioObj.header.gfx.cameraToObject)
            else
                play_sound(SOUND_GENERAL_COIN, m.marioObj.header.gfx.cameraToObject)
            end
        end
    end

    -- Regular coins increase the rings counter and partially restore oxygen (1 coin = 5 seconds)
    if intType == INTERACT_COIN then
        if m.playerIndex == 0 then
            p.rings = p.rings + o.oDamageOrCoinValue
            showHealth = 150
        end
        e.oxygen = math.min(e.oxygen + o.oDamageOrCoinValue * 150, 900)
    end

    -- Fully restores oxygen if Sonic grabs a bubble/water ring
    if intType == INTERACT_WATER_RING then
        e.oxygen = 900
        if m.playerIndex == 0 then
            play_sound(SOUND_MENU_POWER_METER, gGlobalSoundSource)
        end
    end
end

hook_event(HOOK_ON_INTERACT, ringteract)
id_bhvSonicRing = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_ring_init, bhv_ring_loop, "bhvSonicRing")

-- Various API functions for sonic
_G.extraCharsSonic = {}

---@param index_ integer?
---@return boolean usingRingHealth
extraCharsSonic.using_ring_health = function(index_)
    if (CT_SONIC ~= _G.charSelect.character_get_current_number(index_ or 0)) then return false end
    if (_G.charSelect.get_options_status(6) == 0) then return false end

    return true
end
-- Note: update the above function if the ability to toggle off ring health is added

---@param index_ integer?
---@return integer rings
extraCharsSonic.get_rings = function(index_)
    local index = index_ or 0
    return (gPlayerSyncTable[index].rings or 0)
end

---@param index_ integer?
---@param value integer
extraCharsSonic.set_rings = function(index_, value)
    local index = index_ or 0
    gPlayerSyncTable[index].rings = (value or 0)
end

---@param index_ integer?
---@return integer oxygen
extraCharsSonic.get_oxygen = function(index_)
    local index = index_ or 0
    return (gCharacterStates[index].sonic.oxygen or 900)
end

---@param index_ integer?
---@param value integer
extraCharsSonic.set_oxygen = function(index_, value)
    local index = index_ or 0
    gCharacterStates[index].sonic.oxygen = (value or 900)
end

---@param index_ integer?
extraCharsSonic.reset_oxygen = function(index_)
    local index = index_ or 0
    gCharacterStates[index].sonic.oxygen = 900
end

-- Drops a ring behind Sonic, like when he is in a burning action
---@param index_ integer?
---@return Object o
extraCharsSonic.drop_ring = function(index_)
    local m = gMarioStates[index_ or 0]
    local o = spawn_sync_object(
        id_bhvSonicRing,
        E_MODEL_YELLOW_COIN,
        m.pos.x, m.pos.y, m.pos.z,
        function (o)
            o.oVelY = math.random(20, 40)
            o.oForwardVel = math.random(15, 30)
            o.oMoveAngleYaw = m.faceAngle.y + 0x8000 + degrees_to_sm64(math.random(-30, 30))
            o.oTimer = 100
        end)
    return o
end

extraCharsSonic.sonic_set_alive = sonic_set_alive
extraCharsSonic.sonic_set_dead = sonic_set_dead

-- Handle Slow Down Boots option
local forceSlowBoots = false
gGlobalSyncTable.slowDownBoots = sSlowDownBoots

local OPTION_SLOW_BOOTS = charSelect.add_option("Slow Down Boots", nil, nil, nil, {"Makes Sonic's moveset less", "powerful (Host Only)"}, false)
charSelect.get_option(OPTION_SLOW_BOOTS).lock = function()
    if not network_is_server() then
        return "Host Only"
    elseif forceSlowBoots then
        return "Forced On"
    end
end

-- Toggles forcing Sonic to have slow boots or not. Will only run for the host.
extraCharsSonic.sonic_force_slow_down_boots = function(toggle_)
    if not network_is_server() then return end
    local toggle = toggle_ or false
    forceSlowBoots = toggle
end

extraCharsSonic.sonic_slow_down_boots_active = function()
    return sSlowDownBoots
end

function on_slow_boots_option_change(tag, oldVal, newVal)
    if newVal == nil then return end

    sSlowDownBoots = newVal
    HEDGEHOG_SPEED  = sSlowDownBoots and 64 or 128
    HEDGEHOG_HEIGHT = sSlowDownBoots and 20 or 32
end
hook_on_sync_table_change(gGlobalSyncTable, "slowDownBoots", "slowDownBoots", on_slow_boots_option_change)

function update_slow_boots_option()
    local slowBootsToggle = forceSlowBoots or (charSelect.get_options_status(OPTION_SLOW_BOOTS) ~= 0)
    gGlobalSyncTable.slowDownBoots = slowBootsToggle
end
if network_is_server() then
    hook_event(HOOK_UPDATE, update_slow_boots_option)
end

return {
    { HOOK_BEFORE_SET_MARIO_ACTION, before_set_sonic_action },
    { HOOK_ON_SET_MARIO_ACTION, on_set_sonic_action },
    { HOOK_ALLOW_INTERACT, sonic_allow_interact },
    { HOOK_ON_INTERACT, sonic_on_interact },
    { HOOK_ALLOW_FORCE_WATER_ACTION, sonic_allow_water },
    { HOOK_MARIO_UPDATE, sonic_update },
    { HOOK_BEFORE_PHYS_STEP, sonic_before_phys_step },
    { HOOK_ON_HUD_RENDER_BEHIND, sonic_homing_hud },
    { HOOK_MARIO_OVERRIDE_PHYS_STEP_DEFACTO_SPEED, sonic_defacto_fix },
    { HOOK_ON_PLAY_SOUND, sonic_on_play_sound },
    meter = sonic_health_meter
}