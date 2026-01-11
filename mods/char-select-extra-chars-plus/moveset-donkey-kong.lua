-------------------------
-- Donkey Kong Moveset --
-------------------------

if not charSelect then return end

local DONKEY_KONG_ROLL_SPEED = 60
local DONKEY_KONG_ROLL_DECAY_PERCENT = 0.98
local DONKEY_KONG_ROLL_DECAY_TIME = 10
local DONKEY_KONG_ROLL_STARTUP = 4
local DONKEY_KONG_ROLL_END = 25
local DONKEY_KONG_SLIP_TIME = 20
local DONKEY_KONG_SLIDE_TIME = 40

----------------
-- DK Gravity --
----------------

--- @param m MarioState
--- @param wall Surface
--- @param intendedPos Vec3f
--- @param nextPos Vec3f
--- @return integer
--- Checks ledge grab for donkey kong
local function donkey_kong_check_ledge_grab(m, wall, intendedPos, nextPos)
    if not m then return 0 end
    local ledgeFloor
    local ledgePos = gVec3fZero()
    local displacementX
    local displacementZ

    if m.vel.y > 0 then
        return 0
    end

    displacementX = nextPos.x - intendedPos.x
    displacementZ = nextPos.z - intendedPos.z

    -- Only ledge grab if the wall displaced Mario in the opposite direction of
    -- his velocity.
    if displacementX * m.vel.x + displacementZ * m.vel.z > 0.0 then
        return 0
    end

    --! Since the search for floors starts at y + m.marioObj.hitboxHeight (160.0f), we will sometimes grab
    -- a higher ledge than expected (glitchy ledge grab)
    ledgePos.x = nextPos.x - wall.normal.x * 60.0
    ledgePos.z = nextPos.z - wall.normal.z * 60.0
    ledgePos.y, ledgeFloor = find_floor(ledgePos.x, nextPos.y + m.marioObj.hitboxHeight, ledgePos.z)
    if not ledgeFloor then return 0 end

    if gLevelValues.fixCollisionBugs ~= 0 and gLevelValues.fixCollisionBugsFalseLedgeGrab ~= 0 then
        -- fix false ledge grabs
        if (not ledgeFloor or ledgeFloor.normal.y < 0.90630779) then
            return 0
        end
    end

    if ledgePos.y - nextPos.y <= 100.0 then
        return 0
    end

    vec3f_copy(m.pos, ledgePos)
    m.floor = ledgeFloor
    m.floorHeight = ledgePos.y

    m.floorAngle = atan2s(ledgeFloor.normal.z, ledgeFloor.normal.x)

    m.faceAngle.x = 0
    m.faceAngle.y = atan2s(wall.normal.z, wall.normal.x) + 0x8000
    return 1
end

--- Turns a WallCollisionData object into a table
--- @param wcd WallCollisionData
--- @return table
local function wcd_to_table(wcd)
    return {
        x = wcd.x, -- number
        y = wcd.y, -- number
        z = wcd.z, -- number
        offsetY = wcd.offsetY, -- number
        radius = wcd.radius, -- number
        unused = wcd.unused, -- integer
        numWalls = wcd.numWalls, -- integer
        walls = {
            wcd.walls[1],
            wcd.walls[2],
            wcd.walls[3],
            wcd.walls[4]
        } , -- Surface[]
        normalAddition = {
            x = wcd.normalAddition.x,
            y = wcd.normalAddition.y,
            z = wcd.normalAddition.z,
        }, -- Vec3f
        normalCount = wcd.normalCount, -- integer
    }
end

--- Fills a WallCollisionData object from a table
--- @param wcd WallCollisionData
--- @param t table
local function table_to_wcd(wcd, t)
    wcd.x = t.x
    wcd.y = t.y
    wcd.z = t.z
    wcd.offsetY = t.offsetY
    wcd.radius = t.radius
    wcd.unused = t.unused
    wcd.numWalls = t.numWalls
    wcd.walls[1] = t.walls[1]
    wcd.walls[2] = t.walls[2]
    wcd.walls[3] = t.walls[3]
    wcd.walls[4] = t.walls[4]
    wcd.normalAddition.x = t.normalAddition.x
    wcd.normalAddition.y = t.normalAddition.y
    wcd.normalAddition.z = t.normalAddition.z
    wcd.normalCount = t.normalCount
end

--- @param m MarioState
--- @param intendedPos Vec3f
--- @param stepArg integer
--- @return integer
--- Performs an air quarter step for donkey kong
local function perform_donkey_kong_air_quarter_step(m, intendedPos, stepArg)
    if not m then return 0 end
    local wallDYaw
    local nextPos = gVec3fZero()
    local ceil
    local floor
    local ceilHeight
    local floorHeight
    local waterLevel
    local tempWcd

    vec3f_copy(nextPos, intendedPos)

    -- Important note:
    -- The WallCollisionData pointer is always the same, meaning it cannot be used for both upperWcd and lowerWcd
    -- Fortunately, it's read-write, so we can turn it into a table for the Lua part of the function and
    -- turn it back into a WallCollisionData object for the C function calls

    tempWcd = collision_get_temp_wall_collision_data()
    resolve_and_return_wall_collisions_data(nextPos, 150.0, 50.0, tempWcd)
    local upperWcd = wcd_to_table(tempWcd)

    tempWcd = collision_get_temp_wall_collision_data()
    resolve_and_return_wall_collisions_data(nextPos, 30.0, 50.0, tempWcd)
    local lowerWcd = wcd_to_table(tempWcd)

    floorHeight, floor = find_floor(nextPos.x, nextPos.y, nextPos.z)
    ceilHeight, ceil = vec3f_mario_ceil(nextPos, floorHeight)
    waterLevel = find_water_level(nextPos.x, nextPos.z)

    m.wall = nil

    --! The water pseudo floor is not referenced when your intended qstep is
    -- out of bounds, so it won't detect you as landing.

    if not floor then
        if nextPos.y <= m.floorHeight then
            m.pos.y = m.floorHeight
            return AIR_STEP_LANDED
        end

        m.pos.y = nextPos.y
        if gServerSettings.bouncyLevelBounds ~= BOUNCY_LEVEL_BOUNDS_OFF then
            m.faceAngle.y = m.faceAngle.y + 0x8000
            mario_set_forward_vel(m, gServerSettings.bouncyLevelBounds == BOUNCY_LEVEL_BOUNDS_ON_CAP and math.clamp(1.5 * m.forwardVel, -500, 500) or 1.5 * m.forwardVel)
        end
        return AIR_STEP_HIT_WALL
    end

    if (m.action & ACT_FLAG_RIDING_SHELL) ~= 0 and floorHeight < waterLevel then
        local allowForceAction = TRIPLET_BUTTERFLY_ACT_ACTIVATE
        if allowForceAction then
            floorHeight = waterLevel
            floor = get_water_surface_pseudo_floor()
            floor.originOffset = floorHeight
        end
    end

    --! This check uses f32, but findFloor uses short (overflow jumps)
    if nextPos.y <= floorHeight then
        if ceilHeight - floorHeight > m.marioObj.hitboxHeight then
            m.pos.x = nextPos.x
            m.pos.z = nextPos.z
            m.floor = floor
            m.floorHeight = floorHeight
        end

        --! When ceilHeight - floorHeight <= m->marioObj->hitboxHeight (160.0f), the step result says that
        -- Mario landed, but his movement is cancelled and his referenced floor
        -- isn't updated (pedro spots)
        m.pos.y = floorHeight
        return AIR_STEP_LANDED
    end

    if nextPos.y + m.marioObj.hitboxHeight > ceilHeight then
        if m.vel.y >= 0.0 then
            m.vel.y = 0.0

            --! Uses referenced ceiling instead of ceil (ceiling hang upwarp)
            if (stepArg and (stepArg & AIR_STEP_CHECK_HANG) ~= 0) and m.ceil and m.ceil.type == SURFACE_HANGABLE then
                return AIR_STEP_GRABBED_CEILING
            end

            return AIR_STEP_NONE
        end

        if nextPos.y <= m.floorHeight then
            m.pos.y = m.floorHeight
            return AIR_STEP_LANDED
        end

        m.pos.y = nextPos.y
        return AIR_STEP_HIT_WALL
    end

    --! When the wall is not completely vertical or there is a slight wall
    -- misalignment, you can activate these conditions in unexpected situations
    if (stepArg and (stepArg & AIR_STEP_CHECK_LEDGE_GRAB) ~= 0) and upperWcd.numWalls == 0 and lowerWcd.numWalls > 0 then
        for i = 1, lowerWcd.numWalls do
            if gLevelValues.fixCollisionBugs == 0 then
                i = lowerWcd.numWalls
            end
            local wall = lowerWcd.walls[i]
            if donkey_kong_check_ledge_grab(m, wall, intendedPos, nextPos) ~= 0 then
                return AIR_STEP_GRABBED_LEDGE
            end
        end

        vec3f_copy(m.pos, nextPos)
        m.floor = floor
        m.floorHeight = floorHeight
        return AIR_STEP_NONE
    end

    vec3f_copy(m.pos, nextPos)
    m.floor = floor
    m.floorHeight = floorHeight

    if upperWcd.numWalls > 0 then
        table_to_wcd(tempWcd, upperWcd)
        mario_update_wall(m, tempWcd)
        upperWcd = wcd_to_table(tempWcd)

        for i = 1, upperWcd.numWalls do
            if gLevelValues.fixCollisionBugs == 0 then
                i = upperWcd.numWalls
            end

            local wall = upperWcd.walls[i]
            wallDYaw = atan2s(wall.normal.z, wall.normal.x) - m.faceAngle.y

            if wall.type == SURFACE_BURNING then
                m.wall = wall
                return AIR_STEP_HIT_LAVA_WALL
            end

            if wallDYaw < -0x6000 or wallDYaw > 0x6000 then
                m.wall = wall
                m.flags = m.flags | MARIO_UNKNOWN_30
                return AIR_STEP_HIT_WALL
            end
        end
    elseif lowerWcd.numWalls > 0 then
        table_to_wcd(tempWcd, lowerWcd)
        mario_update_wall(m, tempWcd)
        lowerWcd = wcd_to_table(tempWcd)

        for i = 1, lowerWcd.numWalls do
            if gLevelValues.fixCollisionBugs == 0 then
                i = lowerWcd.numWalls
            end

            local wall = lowerWcd.walls[i]
            wallDYaw = atan2s(wall.normal.z, wall.normal.x) - m.faceAngle.y

            if wall.type == SURFACE_BURNING then
                m.wall = wall
                return AIR_STEP_HIT_LAVA_WALL
            end

            if wallDYaw < -0x6000 or wallDYaw > 0x6000 then
                m.wall = wall
                m.flags = m.flags | MARIO_UNKNOWN_30
                return AIR_STEP_HIT_WALL
            end
        end
    end

    return AIR_STEP_NONE
end

--- @param m MarioState
--- Applies twirl gravity to donkey kong
local function apply_donkey_kong_twirl_gravity(m)
    if not m then return end
    local terminalVelocity
    local heaviness = 1.0

    if m.angleVel.y > 1024 then
        heaviness = 1024.0 / m.angleVel.y
    end

    terminalVelocity = -75.0 * heaviness

    m.vel.y = m.vel.y - 4.0 * heaviness
    if m.vel.y < terminalVelocity then
        m.vel.y = terminalVelocity
    end
end

--- @param m MarioState
--- @return integer
--- Checks if gravity should be strengthen for donkey kong jump ascent
local function should_strengthen_gravity_for_donkey_kong_jump_ascent(m)
    if not m then return 0 end
    if m.flags & MARIO_UNKNOWN_08 == 0 then
        return 0
    end

    if m.action & ACT_FLAG_INTANGIBLE ~= 0 or m.action & ACT_FLAG_INVULNERABLE ~= 0 then
        return 0
    end

    if m.input & INPUT_A_DOWN == 0 and m.vel.y > 20.0 then
        return m.action & ACT_FLAG_CONTROL_JUMP_HEIGHT ~= 0 and 1 or 0
    end

    return 0
end

--- @param m MarioState
--- Applies gravity to donkey kong
local function apply_donkey_kong_gravity(m)
    if m.action == ACT_TWIRLING and m.vel.y < 0.0 then
        apply_donkey_kong_twirl_gravity(m)
    elseif m.action == ACT_SHOT_FROM_CANNON then
        m.vel.y = math.max(-75, m.vel.y - 1)
    elseif m.action == ACT_LONG_JUMP or m.action == ACT_SLIDE_KICK or m.action == ACT_BBH_ENTER_SPIN then
        m.vel.y = math.max(-75, m.vel.y - 3.0)
    elseif m.action == ACT_LAVA_BOOST or m.action == ACT_FALL_AFTER_STAR_GRAB then
        m.vel.y = math.max(-65, m.vel.y - 4.8)
    elseif m.action == ACT_GETTING_BLOWN then
        m.vel.y = math.max(-75, m.vel.y - (1.5 * m.unkC4))
    elseif should_strengthen_gravity_for_donkey_kong_jump_ascent(m) ~= 0 then
        m.vel.y = m.vel.y / 4.0
    elseif m.action & ACT_FLAG_METAL_WATER ~= 0 then
        m.vel.y = math.max(-16, m.vel.y - 2.4)
    elseif m.flags & MARIO_WING_CAP ~= 0 and m.vel.y < 0.0 and m.input & INPUT_A_DOWN ~= 0 then
        m.marioBodyState.wingFlutter = 1

        m.vel.y = m.vel.y - 3.0
        if m.vel.y < -37.5 then
            m.vel.y = math.min(-37.5, m.vel.y + 4)
        end
    else
        if m.vel.y < 0 then
            m.vel.y = math.max(-75, m.vel.y - 6)
        else
            m.vel.y = math.max(-75, m.vel.y - 4.25)
        end
    end
end

---@param m MarioState
--- Applies vertical wind to donkey kong
local function apply_donkey_kong_vertical_wind(m)
    if not m then return end
    local maxVelY
    local offsetY
    if m.action ~= ACT_GROUND_POUND then
        offsetY = m.pos.y - -1500.0

        if m.floor and m.floor.type == SURFACE_VERTICAL_WIND and -3000.0 < offsetY and offsetY < 2000.0 then
            if offsetY >= 0.0 then
                maxVelY = 10000.0 / (offsetY + 200.0)
            else
                maxVelY = 50.0
            end

            if m.vel.y < maxVelY then
                m.vel.y = (m.vel.y + maxVelY / 6.0) -- Bit stronger so DK doesn't fall through
                if m.vel.y > maxVelY then
                    m.vel.y = maxVelY
                end
            end
        end
    end
end

--- @param m MarioState
--- @param stepArg integer
--- @return integer
--- Performs an air step for donkey kong
local function perform_donkey_kong_air_step(m, stepArg)
    local intendedPos = gVec3fZero()
    local quarterStepResult
    local stepResult = AIR_STEP_NONE

    m.wall = nil

    for i = 0, 3 do
        local step = gVec3fZero()
        step = {
            x = m.vel.x / 4.0,
            y = m.vel.y / 4.0,
            z = m.vel.z / 4.0,
        }

        intendedPos.x = m.pos.x + step.x
        intendedPos.y = m.pos.y + step.y
        intendedPos.z = m.pos.z + step.z

        vec3f_normalize(step)
        set_find_wall_direction(step, true, true)

        quarterStepResult = perform_donkey_kong_air_quarter_step(m, intendedPos, stepArg)
        set_find_wall_direction(step, false, false)

        --! On one qf, hit OOB/ceil/wall to store the 2 return value, and continue
        -- getting 0s until your last qf. Graze a wall on your last qf, and it will
        -- return the stored 2 with a sharply angled reference wall. (some gwks)

        if (quarterStepResult ~= AIR_STEP_NONE) then
            stepResult = quarterStepResult
        end

        if (quarterStepResult == AIR_STEP_LANDED or quarterStepResult == AIR_STEP_GRABBED_LEDGE
                or quarterStepResult == AIR_STEP_GRABBED_CEILING
                or quarterStepResult == AIR_STEP_HIT_LAVA_WALL) then
            break
        end
    end

    if (m.vel.y >= 0.0) then
        m.peakHeight = m.pos.y
    end

    m.terrainSoundAddend = mario_get_terrain_sound_addend(m)

    -- Start climbing
    if m.wall ~= nil and m.action ~= ACT_DONKEY_CLIMB and m.prevAction ~= ACT_DONKEY_CLIMB
    and (m.action & ACT_FLAG_INVULNERABLE == 0) and stepResult ~= AIR_STEP_HIT_LAVA_WALL
    and m.input & INPUT_A_DOWN ~= 0 and m.heldObj == nil then
        local wallangle = atan2s(m.wallNormal.z, m.wallNormal.x) + 0x8000
        -- Only grab wall if within certain angle of the wall
        if abs_angle_diff(wallangle, m.faceAngle.y) < 0x3000 then
            set_mario_action(m, ACT_DONKEY_CLIMB, 0)
            if stepResult == AIR_STEP_HIT_WALL then return 0 end
            return stepResult
        end
    end

    if (m.action ~= ACT_FLYING and m.action ~= ACT_BUBBLED) then
        apply_donkey_kong_gravity(m)
    end
    apply_donkey_kong_vertical_wind(m)

    vec3f_copy(m.marioObj.header.gfx.pos, m.pos)
    vec3s_set(m.marioObj.header.gfx.angle, 0, m.faceAngle.y, 0)

    return stepResult
end

function donkey_kong_before_phys_step(m, stepType, stepArg)
    if stepType == STEP_TYPE_GROUND then
        -- return perform_donkey_kong_ground_step(m) -- TBA
    elseif stepType == STEP_TYPE_AIR then
        return perform_donkey_kong_air_step(m, stepArg)
    elseif stepType == STEP_TYPE_WATER then
        -- return perform_donkey_kong_water_step(m) -- TBA
    elseif stepType == STEP_TYPE_HANG then
        -- return perform_donkey_kong_hanging_step(m) -- TBA
    end
end

function donkey_kong_before_action(m, action, actionArg)
    if (action == ACT_DIVE or action == ACT_MOVE_PUNCHING) and m.action & ACT_FLAG_AIR == 0 and m.input & INPUT_A_DOWN == 0 and m.forwardVel >= 20 then
        m.vel.y = 20
        m.faceAngle.x = 0
        return ACT_DONKEY_KONG_ROLL
    elseif (action == ACT_PUNCHING and actionArg == 9) then
        return ACT_DONKEY_KONG_POUND
    end
end

function donkey_kong_on_interact(m, o, type, value)
    -- allow donkey kong to grab objects with the roll
    if type == INTERACT_GRABBABLE and m.action == ACT_DONKEY_KONG_ROLL then
        if ((o.oInteractionSubtype & INT_SUBTYPE_NOT_GRABBABLE) == 0) then
            m.interactObj = o
            m.input = m.input | INPUT_INTERACT_OBJ_GRABBABLE
            if (o.oSyncID ~= 0) then network_send_object(o, false) end
            return 1
        end
    end
end

function on_attack_object(m, o, interaction)
    -- speed up when hitting enemies with roll
    if (m.action == ACT_DONKEY_KONG_ROLL or m.action == ACT_DONKEY_KONG_ROLL_AIR) and (interaction & INT_FAST_ATTACK_OR_SHELL ~= 0) then
        if o.oInteractType == INTERACT_BULLY then
            mario_set_forward_vel(m, -25)
            m.actionTimer = DONKEY_KONG_ROLL_DECAY_TIME
            m.actionArg = 1
        else
            local newForwardVel = math.min(m.forwardVel * 1.1, 70)
            mario_set_forward_vel(m, newForwardVel)
            m.actionTimer = 0
            m.actionArg = 0
        end
    end

    -- Bounce code
    if (CT_DONKEY_KONG ~= _G.charSelect.character_get_current_number(m.playerIndex)) then return end
    if (_G.charSelect.get_options_status(6) ~= 0) then
        if (interaction == INT_HIT_FROM_ABOVE and m.framesSinceA < 5) then
            m.actionTimer = 0
            if (m.action == ACT_DONKEY_KONG_BOUNCE) then
                set_mario_action(m, ACT_DONKEY_KONG_BOUNCE, m.actionArg + 1)
            else
                set_mario_action(m, ACT_DONKEY_KONG_BOUNCE, 1)
            end
        end
    end
end
hook_event(HOOK_ON_ATTACK_OBJECT, on_attack_object)

_G.ACT_DONKEY_KONG_ROLL = allocate_mario_action(ACT_GROUP_MOVING | ACT_FLAG_ATTACKING | ACT_FLAG_MOVING)
_G.ACT_DONKEY_KONG_ROLL_AIR = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_ATTACKING | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
_G.ACT_DONKEY_KONG_POUND = allocate_mario_action(ACT_GROUP_STATIONARY | ACT_FLAG_ATTACKING)
_G.ACT_DONKEY_KONG_POUND_HIT = allocate_mario_action(ACT_GROUP_STATIONARY | ACT_FLAG_ATTACKING)
_G.ACT_DONKEY_KONG_BOUNCE = (ACT_GROUP_AIRBORNE | ACT_FLAG_MOVING | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)

---------------
-- DK Bounce --
---------------

--- SwagSkeleton95
--- Allows the player to bounce across enemies with well-timed A presses. Spawns coins when chained across multiple enemies. Credit to baconator2558 for the vast majority of this code.
--- action

local bounceSounds = {
    audio_sample_load("z_sfx_dk_bounce1.ogg"),
    audio_sample_load("z_sfx_dk_bounce2.ogg"),
    audio_sample_load("z_sfx_dk_bounce3.ogg")
}

local coinObj = nil

function act_dk_bounce(m)
    if (m.actionTimer == 0) then
        set_character_animation(m, CHAR_ANIM_FORWARD_SPINNING)
        set_anim_to_frame(m, 0)
        m.forwardVel = 0
        m.vel.x = 0
        m.vel.y = 80
        play_character_sound(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE)
        m.vel.z = 0
        m.slideVelX = 0
        m.slideVelZ = 0
        m.faceAngle.y = m.intendedYaw
        if (m.actionArg >= 3) then
            coinObj = spawn_non_sync_object(id_bhvBlueCoinJumping, E_MODEL_SPARKLES, m.pos.x, m.pos.y, m.pos.z, nil)
        end
        audio_sample_play(bounceSounds[math.min(m.actionArg,3)], m.pos, 0.5)
        -- plays a random sound from a table ('bounceSounds') of 3 sound files.
        -- I didn't include them here because I ripped them straight from DKCR myself
        -- and I'm under the impression that this mod mainly uses self-made sound effects
        set_mario_particle_flags(m, PARTICLE_HORIZONTAL_STAR, 0)
    end

    if (m.actionTimer >= 1 and coinObj ~= nil) then
        coinObj.oPosX = m.pos.x
        coinObj.oPosY = m.pos.y
        coinObj.oPosZ = m.pos.z
        interact_coin(m, INTERACT_COIN, coinObj)
        coinObj = nil
    end

    if (m.actionTimer > 5 and m.marioObj.header.gfx.animInfo.animID == CHAR_ANIM_FORWARD_SPINNING) then
        set_character_animation(m, CHAR_ANIM_TRIPLE_JUMP)
        set_anim_to_frame(m, 21)
    end
    
    m.forwardVel = math.min(m.forwardVel, 95)

    update_air_without_turn(m)
    if (m.actionTimer > 20) then
        update_air_without_turn(m)
    end

    if (m.vel.y < 10) then
        update_air_without_turn(m)
        if (m.vel.y < -10) then
            update_air_without_turn(m)
            update_air_without_turn(m)
            update_air_without_turn(m)
            update_air_without_turn(m)
            update_air_without_turn(m)
        end
    end

    local stepResult = perform_air_step(m, AIR_STEP_CHECK_HANG | AIR_STEP_CHECK_LEDGE_GRAB)

    if (stepResult == AIR_STEP_LANDED) then
        set_character_animation(m, CHAR_ANIM_FORWARD_SPINNING)
        set_anim_to_frame(m, 0)
        return set_mario_action(m, ACT_DOUBLE_JUMP_LAND, 0)
    elseif (stepResult == AIR_STEP_GRABBED_LEDGE) then
        set_character_animation(m, CHAR_ANIM_IDLE_ON_LEDGE)
        return drop_and_set_mario_action(m, ACT_LEDGE_GRAB, 0)
    elseif (stepResult == AIR_STEP_GRABBED_CEILING) then
        return set_mario_action(m, ACT_START_HANGING, 0)
    end

    m.faceAngle.y = approach_s16_symmetric(m.faceAngle.y, m.intendedYaw, (abs_angle_diff(m.faceAngle.y, m.intendedYaw) / (25 * m.actionTimer + 1)) + 750)
    update_air_without_turn(m)
    m.actionTimer = m.actionTimer + 1
    if (check_kick_or_dive_in_air(m) ~= 0) then
        return 1
    end
    
    return 0
end

hook_mario_action(ACT_DONKEY_KONG_BOUNCE, act_dk_bounce, INT_HIT_FROM_ABOVE)

--- Roll

---@param m MarioState
local function act_donkey_kong_roll(m)
    if (not m) then return 0 end

    local isSliding = (mario_floor_is_slippery(m)) ~= 0
    if isSliding then
        if update_sliding(m, 4) ~= 0 or m.actionState == 0 then
            m.faceAngle.x = 0
            return set_mario_action(m, ACT_DECELERATING, 0)
        end
    end

    if mario_check_object_grab(m) ~= 0 then
        m.faceAngle.x = 0
        set_character_animation(m, CHAR_ANIM_FIRST_PUNCH)
        set_anim_to_frame(m, 2)
        return 1
    end

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        m.faceAngle.x = 0
        m.marioObj.header.gfx.angle.x = m.faceAngle.x
        local result = set_jumping_action(m, ACT_JUMP, 0)
        if not isSliding then
            m.forwardVel = m.forwardVel / 0.8 - 5 -- conserve all jump momentum minus 5
        end
        return result
    end

    local doSpinAnim = true
    m.actionTimer = m.actionTimer + 1

    set_character_animation(m, CHAR_ANIM_START_CROUCHING)
    if m.actionState == 0 then
        doSpinAnim = false
        local newForwardVel = m.forwardVel
        newForwardVel = DONKEY_KONG_ROLL_SPEED * (m.actionTimer / DONKEY_KONG_ROLL_STARTUP)
        if m.actionTimer >= DONKEY_KONG_ROLL_STARTUP then
            newForwardVel = DONKEY_KONG_ROLL_SPEED
            m.actionState = 1
        end
        mario_set_forward_vel(m, newForwardVel)
    elseif m.actionTimer >= DONKEY_KONG_ROLL_DECAY_TIME and not isSliding then
        -- slow down after a time
        local newForwardVel = m.forwardVel
        newForwardVel = newForwardVel * DONKEY_KONG_ROLL_DECAY_PERCENT
        mario_set_forward_vel(m, newForwardVel)
    end

    -- influence direction slightly
    m.marioObj.oMoveAngleYaw = m.faceAngle.y
    cur_obj_rotate_yaw_toward(m.intendedYaw, 0x100)
    m.faceAngle.y = m.marioObj.oMoveAngleYaw

    local result = perform_ground_step(m)
    if result == GROUND_STEP_LEFT_GROUND then
        if m.actionState == 0 then
            mario_set_forward_vel(m, DONKEY_KONG_ROLL_SPEED)
        end
        return set_mario_action(m, ACT_DONKEY_KONG_ROLL_AIR, 0)
    elseif result == GROUND_STEP_HIT_WALL then
        if (m.wall or gServerSettings.bouncyLevelBounds == BOUNCY_LEVEL_BOUNDS_OFF) then
            m.faceAngle.x = 0
            set_mario_particle_flags(m, PARTICLE_VERTICAL_STAR, 0)
            slide_bonk(m, ACT_GROUND_BONK, ACT_WALKING)
            return
        end
    end

    if doSpinAnim then
        local prevFaceAngleX = m.faceAngle.x
        m.faceAngle.x = m.faceAngle.x + 0x60 * m.forwardVel
        m.marioObj.header.gfx.angle.x = m.faceAngle.x
        m.marioObj.header.gfx.pos.y = m.marioObj.header.gfx.pos.y + 50
        if prevFaceAngleX <= 0 and m.faceAngle.x > 0 then
            play_sound(SOUND_ACTION_SPIN, m.marioObj.header.gfx.cameraToObject)
        end
    end

    -- end roll
    if m.actionTimer > DONKEY_KONG_ROLL_END then
        m.faceAngle.x = 0
        return set_mario_action(m, ACT_WALKING, 0)
    end

    return 0
end

hook_mario_action(ACT_DONKEY_KONG_ROLL, { every_frame = act_donkey_kong_roll }, INT_FAST_ATTACK_OR_SHELL)

---@param m MarioState
local function act_donkey_kong_roll_air(m)
    if (not m) then return 0 end

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        m.terrainSoundAddend = 0
        m.faceAngle.x = 0
        m.marioObj.header.gfx.angle.x = m.faceAngle.x
        local result = set_mario_action(m, ACT_JUMP, 0)
        m.forwardVel = m.forwardVel / 0.8 - 5 -- conserve all jump momentum minus 5
        return result
    end

    m.actionTimer = m.actionTimer + 1

    -- influence direction slightly
    m.marioObj.oMoveAngleYaw = m.faceAngle.y
    cur_obj_rotate_yaw_toward(m.intendedYaw, 0x100)
    m.faceAngle.y = m.marioObj.oMoveAngleYaw
    mario_set_forward_vel(m, m.forwardVel)

    local result = perform_air_step(m, AIR_STEP_CHECK_LEDGE_GRAB)
    if result == AIR_STEP_LANDED then
        if (check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0) then
            set_mario_action(m, ACT_DONKEY_KONG_ROLL, 0)
            m.actionState = 1
            return 1
        end
    elseif result == AIR_STEP_HIT_WALL then
        if (m.wall or gServerSettings.bouncyLevelBounds == BOUNCY_LEVEL_BOUNDS_OFF) then
            mario_bonk_reflection(m, 1)
            if (m.vel.y > 0) then m.vel.y = 0 end

            set_mario_particle_flags(m, PARTICLE_VERTICAL_STAR, 0)
            drop_and_set_mario_action(m, ACT_BACKWARD_AIR_KB, 0)
            return 1
        end
    elseif result == AIR_STEP_HIT_LAVA_WALL then
        lava_boost_on_wall(m)
        return 1
    end

    local prevFaceAngleX = m.faceAngle.x
    m.faceAngle.x = m.faceAngle.x + 0x60 * m.forwardVel
    m.marioObj.header.gfx.angle.x = m.faceAngle.x
    m.marioObj.header.gfx.pos.y = m.marioObj.header.gfx.pos.y + 50
    if prevFaceAngleX <= 0 and m.faceAngle.x > 0 then
        play_sound(SOUND_ACTION_SPIN, m.marioObj.header.gfx.cameraToObject)
    end

    if m.actionTimer > DONKEY_KONG_ROLL_END then
        m.faceAngle.x = 0
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    return 0
end

hook_mario_action(ACT_DONKEY_KONG_ROLL_AIR, { every_frame = act_donkey_kong_roll_air }, INT_FAST_ATTACK_OR_SHELL)

local function act_donkey_kong_pound(m)
    if (not m) then return 0 end

    mario_set_forward_vel(m, 0)
    if (mario_floor_is_slippery(m)) ~= 0 then
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0)
    end

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        local result = set_jumping_action(m, ACT_JUMP, 0)
        return result
    elseif (m.input & INPUT_B_PRESSED) ~= 0 and m.actionTimer ~= 0 then
        m.actionState = 1
    end

    m.actionTimer = m.actionTimer + 1
    if m.actionTimer == 1 then
        play_mario_heavy_landing_sound(m, SOUND_ACTION_TERRAIN_HEAVY_LANDING)

        -- Spawn particles at hand that hit ground
        local pos = {x = 0, y = 0, z = 0}
        if m.marioObj.header.gfx.animInfo.animFrame >= 8 then
            get_mario_anim_part_pos(m, MARIO_ANIM_PART_RIGHT_HAND, pos)
        else
            get_mario_anim_part_pos(m, MARIO_ANIM_PART_LEFT_HAND, pos)
        end
        pos.y = m.pos.y -- always appear on ground
        spawn_non_sync_object(id_bhvHorStarParticleSpawner, E_MODEL_NONE, pos.x, pos.y, pos.z, nil)
        spawn_non_sync_object(id_bhvMistCircParticleSpawner, E_MODEL_NONE, pos.x, pos.y, pos.z, nil)

        m.action = ACT_DONKEY_KONG_POUND_HIT
        m.marioObj.hitboxRadius = 100 -- larger hitbox
    elseif m.action == ACT_DONKEY_KONG_POUND_HIT then
        m.action = ACT_DONKEY_KONG_POUND
        m.marioObj.hitboxRadius = 37 -- reset hitbox
    elseif m.actionTimer >= 8 then
        if m.actionState ~= 0 then
            -- pound again
            m.actionTimer = 0
            m.actionState = 0
        elseif m.input & INPUT_Z_DOWN ~= 0 then
            set_mario_action(m, ACT_START_CROUCHING, 0)
        else
            set_mario_action(m, ACT_IDLE, 0)
        end
    end

    --set_character_anim_with_accel(m, CHAR_ANIM_PLACE_LIGHT_OBJ, 0x20000)
    -- 28 anim frames in 16 frames
    if m.marioObj.header.gfx.animInfo.animFrame > 15 and m.actionTimer == 0 then
        --djui_chat_message_create(tostring(m.marioObj.header.gfx.animInfo.animFrame))
        set_anim_to_frame(m, 0)
    end
    play_custom_anim(m, "donkey_ground_slap", 0x10000 * 28 // 16)
    --[[set_anim_to_frame(m, m.marioObj.header.gfx.animInfo.animFrame)
    if m.controller.buttonPressed & L_TRIG ~= 0 then
        set_anim_to_frame(m, m.marioObj.header.gfx.animInfo.animFrame + 1)
    end]]
    local result = perform_ground_step(m)
    if result == GROUND_STEP_LEFT_GROUND then
        return set_mario_action(m, ACT_FREEFALL, 0)
    end
end
hook_mario_action(ACT_DONKEY_KONG_POUND, { every_frame = act_donkey_kong_pound })

hook_mario_action(ACT_DONKEY_KONG_POUND_HIT, { every_frame = act_donkey_kong_pound }, INT_GROUND_POUND) -- same action but with ground pound interaction

-----------------------
--- Donkey Climbing ---
--- -------------------

DK_ANIM_CLIMBING = 'donkey_custom_climbing'

ACT_DONKEY_CLIMB = allocate_mario_action(ACT_FLAG_AIR | ACT_GROUP_AIRBORNE)

-- Climbing ability action
--- @param m MarioState
function act_donkey_climb(m)
    --No wall, no climb
    if m.wall == nil then
        set_mario_action(m, ACT_TRIPLE_JUMP, 0)
        mario_set_forward_vel(m, 10)
        return true

    --Press A to jump off
    elseif (m.input & INPUT_A_PRESSED) ~= 0 then
        set_mario_action(m, ACT_JUMP, 0)
        m.faceAngle.y = m.faceAngle.y - 0x8000
        mario_set_forward_vel(m, 20)
        return true

    --Press Z to just fall off
    elseif (m.input & INPUT_Z_PRESSED) ~= 0 then
        m.input = m.input &~ INPUT_Z_PRESSED
        play_character_sound(m, CHAR_SOUND_UH)

        mario_set_forward_vel(m, -8)
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    --Woah!
    if m.actionTimer == 0 then
        play_character_sound(m, CHAR_SOUND_WHOA)
    end

    local climbAnimSpeed = m.intendedMag
    local wallangle = atan2s(m.wallNormal.z, m.wallNormal.x) + 0x8000
    local transwall
    if m.actionTimer >= 4 then
        --Face beside wall and move around it
        m.faceAngle.y = wallangle - 0x4000
        if m.actionTimer <= DONKEY_KONG_SLIP_TIME then
            mario_set_forward_vel(m, m.controller.stickX/3)
            m.vel.y = m.controller.stickY/3
        elseif m.actionTimer <= DONKEY_KONG_SLIDE_TIME then -- Slip on wall after some time
            climbAnimSpeed = 32
            m.vel.y = 0
        else
            climbAnimSpeed = 0
            m.vel.y = m.vel.y + 8 -- counteract gravity
        end

        --Perform air step
        local air_step = perform_air_step(m, 0)
        transwall = m.wall
        if air_step == AIR_STEP_LANDED then
            return set_mario_action(m, ACT_FREEFALL_LAND, 0)
        end
    end

    --Face directly towards wall to make sure we're latched on
    m.faceAngle.y = wallangle
    mario_set_forward_vel(m, 1)
    if m.actionTimer <= DONKEY_KONG_SLIP_TIME then
        m.vel.y = 0
    elseif m.actionTimer <= DONKEY_KONG_SLIDE_TIME then
        m.vel.y = 5
    end

    --Perform air step
    air_step = perform_air_step(m, 0)
    if air_step == AIR_STEP_LANDED then
        return set_mario_action(m, ACT_FREEFALL_LAND, 0)
    elseif m.wall == nil then
        if transwall == nil then
            set_mario_action(m, ACT_TRIPLE_JUMP, 0)
            mario_set_forward_vel(m, 10)
            return true
        else
            m.wall = transwall
        end
    end

    --Climbing animation
    play_custom_anim(m, "donkey_custom_climbing", climbAnimSpeed * 0x3000)
    if m.actionTimer < 8 or climbAnimSpeed == 0 then
        set_anim_to_frame(m, 0)
    else
        m.particleFlags = m.particleFlags | PARTICLE_DUST

        m.terrainSoundAddend = SOUND_TERRAIN_SAND << 16
        play_step_sound(m, 26, 79)
    end
    local inward_offset = 25
    m.marioObj.header.gfx.pos.x = m.marioObj.header.gfx.pos.x + inward_offset * sins(m.faceAngle.y)
    m.marioObj.header.gfx.pos.z = m.marioObj.header.gfx.pos.z + inward_offset * coss(m.faceAngle.y)

    m.actionTimer = m.actionTimer + 1
end
hook_mario_action(ACT_DONKEY_CLIMB, {every_frame = act_donkey_climb, gravity = function() end})