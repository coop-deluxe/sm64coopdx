if not _G.charSelectExists then return end

---------------
-- Constants --
---------------

-- Cappy constants
local CAPPY_LIFETIME                        = 120
local CAPPY_RETURN_VEL                      = 120
local CAPPY_SLOWDOWN_FACTOR                 = 1.15
local CAPPY_HITBOX_RADIUS                   = 88
local CAPPY_HITBOX_HEIGHT                   = 128
local CAPPY_HITBOX_OFFSET                   = 48
local CAPPY_WALL_RADIUS                     = 56
local CAPPY_GFX_SCALE_X                     = 1.1
local CAPPY_GFX_SCALE_Y                     = 1.0
local CAPPY_GFX_SCALE_Z                     = 1.1
local CAPPY_GFX_ANGLE_VEL                   = 0x2000
local CAPPY_HOMING_VELOCITY                 = 90
local CAPPY_HOMING_VELOCITY_COIN            = 105
local CAPPY_HOMING_VELOCITY_SPIN            = 120
local CAPPY_HOMING_DURATION                 = 5
local CAPPY_NUM_STEPS                       = 4

-- Default throw
local CAPPY_BHV_DEFAULT_GROUND              = 0
local CAPPY_BHV_DEFAULT_AIR                 = 1
local CAPPY_BHV_DEFAULT_OFFSET              = 50
local CAPPY_BHV_DEFAULT_VEL                 = 128
local CAPPY_BHV_DEFAULT_CALL_BACK_START     = 10

-- Upwards throw
local CAPPY_BHV_UPWARDS_GROUND              = 2
local CAPPY_BHV_UPWARDS_AIR                 = 3
local CAPPY_BHV_UPWARDS_OFFSET              = 40
local CAPPY_BHV_UPWARDS_VEL                 = 80
local CAPPY_BHV_UPWARDS_CALL_BACK_START     = 10

-- Downwards throw
local CAPPY_BHV_DOWNWARDS_GROUND            = 4
local CAPPY_BHV_DOWNWARDS_AIR               = 5
local CAPPY_BHV_DOWNWARDS_OFFSET            = 40
local CAPPY_BHV_DOWNWARDS_VEL               = 100
local CAPPY_BHV_DOWNWARDS_CALL_BACK_START   = 10

-- Spin throw
local CAPPY_BHV_SPIN_GROUND                 = 6
local CAPPY_BHV_SPIN_AIR                    = 7
local CAPPY_BHV_SPIN_OFFSET                 = 60
local CAPPY_BHV_SPIN_RADIUS_MAX             = 240
local CAPPY_BHV_SPIN_RADIUS_GROWTH          = 16
local CAPPY_BHV_SPIN_ANGLE_VEL              = 0x1000
local CAPPY_BHV_SPIN_CALL_BACK_START        = 16

-- Flying throw
local CAPPY_BHV_FLYING                      = 8
local CAPPY_BHV_FLYING_OFFSET               = 30
local CAPPY_BHV_FLYING_RADIUS_MAX           = 180
local CAPPY_BHV_FLYING_RADIUS_GROWTH        = 12
local CAPPY_BHV_FLYING_ANGLE_VEL            = 0x1000
local CAPPY_BHV_FLYING_CALL_BACK_START      = 16

-- Cappy collision handlers
local CAPPY_COL_WALL_DEFAULT                = 1
local CAPPY_COL_WALL_FULL_STOP              = 2
local CAPPY_COL_FLOOR_CHANGE_BEHAVIOR       = 1

-- Events
local CAPPY_EVENT_SPAWN                     = 1
local CAPPY_EVENT_INIT                      = 2
local CAPPY_EVENT_HOMING                    = 3
local CAPPY_EVENT_RETURN                    = 4
local CAPPY_EVENT_UNLOAD                    = 5
local CAPPY_EVENT_BOUNCE                    = 6

-- Actions
local ACT_CAPPY_THROW_GROUND                = allocate_mario_action(ACT_GROUP_MOVING | ACT_FLAG_MOVING)
local ACT_CAPPY_THROW_AIRBORNE              = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR)
local ACT_CAPPY_BOUNCE                      = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
local ACT_CAPPY_VAULT                       = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
local ACT_CAPPY_RAINBOW_SPIN                = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_ATTACKING)
local ACT_CAPPY_THROW_WATER                 = allocate_mario_action(ACT_GROUP_SUBMERGED | ACT_FLAG_SWIMMING)

-- Animations
local MARIO_ANIM_PAULINE_CAPPY_VAULT        = "anim_pauline_cappy_vault"
local MARIO_ANIM_PAULINE_CAPPY_UP_THROW     = "anim_pauline_cappy_up_throw"
local MARIO_ANIM_PAULINE_CAPPY_DOWN_THROW   = "anim_pauline_cappy_down_throw"
local MARIO_ANIM_PAULINE_CAPPY_SPIN_THROW   = "anim_pauline_cappy_spin_throw"
local MARIO_ANIM_PAULINE_CAPPY_THROW        = "anim_pauline_cappy_throw"
local MARIO_ANIM_PAULINE_CAPPY_RAINBOW_SPIN = "anim_pauline_cappy_rainbow_spin"

-----------
-- Utils --
-----------

local function if_then_else(cond, if_true, if_false)
    if cond then return if_true end
    return if_false
end

local function clamp(x, a, b)
    if x < a then return a end
    if x > b then return b end
    return x
end

local function s16(x)
    x = (math.floor(x) & 0xFFFF)
    if x >= 32768 then return x - 65536 end
    return x
end

local function mario_anim_clamp(animInfo, a, b)
    local frame = animInfo.animFrame
    if frame < a then
        animInfo.animFrame = a
        animInfo.animFrameAccelAssist = (a << 16)
    end
    if frame > b then
        animInfo.animFrame = b
        animInfo.animFrameAccelAssist = (b << 16)
    end
end

local function mario_anim_reset(animInfo)
    animInfo.animID = 0xFF
end

local function mario_anim_play_custom(m, animName, animAccel)
    if smlua_anim_util_get_current_animation_name(m.marioObj) ~= animName or m.marioObj.header.gfx.animInfo.animID ~= -1 then
        mario_anim_clamp(m.marioObj.header.gfx.animInfo, 0, 0)
    end
    m.marioObj.header.gfx.animInfo.animID = -1
    smlua_anim_util_set_animation(m.marioObj, animName)
    m.marioObj.header.gfx.animInfo.animAccel = animAccel or 0x10000
end

-- Hacky way to get Pauline
local function get_pauline()
    for i = 1, #extraCharacters do
        local extraCharacter = extraCharacters[i]
        if extraCharacter.name == "Pauline" then
            return extraCharacter
        end
    end
    return nil
end

local function is_pauline(m)
    return _G.charSelect.character_get_current_number(m.playerIndex) == get_pauline().tablePos
end

-----------
-- Cappy --
-----------

-- oAction             -> index (Mario's global index + 1)
-- oSubAction          -> spawned
-- oTimer              -> timer
-- oUnkBC              -> timestamp
-- oPosX, oPosY, oPosZ -> position
-- oVelX, oVelY, oVelZ -> velocity
-- oMoveAngleYaw       -> direction
-- oBehParams2ndByte   -> behavior
-- oCapUnkF4           -> bounced
-- oCapUnkF8           -> flags: 0 = none, 1 = interact with local Mario, 2 = homing attack
-- oDragStrength       -> cappy throw strength

local id_bhvCappy = hook_behavior(
    nil,
    OBJ_LIST_SPAWNER,
    true,
    function (o) o.oFlags = o.oFlags | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE end,
    function (o) bhv_cappy_loop(o) end,
    "bhvCappy"
)

local function cappy_get_object(m)
    local index = network_global_index_from_local(m.playerIndex) + 1
    local cappy = obj_get_first_with_behavior_id_and_field_s32(id_bhvCappy, 0x31, index) -- oAction
    if cappy == nil then
        cappy = spawn_non_sync_object(id_bhvCappy, E_MODEL_NONE, m.pos.x, m.pos.y, m.pos.z, nil)
        if cappy ~= nil then
            cappy.oAction = index
            cappy.globalPlayerIndex = index - 1
        end
    end
    return cappy
end

------------
-- Events --
------------

-- A Cappy event is a "sync things now" event triggered by Mario or Cappy actions.
-- When received, the local game checks the whole value of the last event and compares it
-- with the received one. If they don't match, that means the received one is a new event.
--
-- An event fills specific Mario's object fields:
-- oUnk94 -> Event type
-- oUnkBC -> Target Id
-- oUnkC0 -> Timestamp
-- oUnk1A8 -> Behavior / Cappy throw strength
-- oHomeX -> Pos X
-- oHomeY -> Pos Y
-- oHomeZ -> Pos Z
-- oParentRelativePosX -> Vel X
-- oParentRelativePosY -> Vel Y
-- oParentRelativePosZ -> Vel Z

local gCappyEvents = {}
for i = 0, (MAX_PLAYERS - 1) do
    gCappyEvents[i] = {
        [CAPPY_EVENT_SPAWN]  = 0,
        [CAPPY_EVENT_INIT]   = 0,
        [CAPPY_EVENT_HOMING] = 0,
        [CAPPY_EVENT_RETURN] = 0,
        [CAPPY_EVENT_UNLOAD] = 0,
        [CAPPY_EVENT_BOUNCE] = 0,
    }
    local marioObj = gMarioStates[i].marioObj
    if marioObj ~= nil then marioObj.oUnk94 = 0 end
end

-- Spawn event: triggered when a player press (X) to throw Cappy
local function cappy_send_event_spawn(m, cappy)
    local marioObj = m.marioObj
    if m.playerIndex ~= 0 or marioObj == nil then return end
    marioObj.oUnk94 = CAPPY_EVENT_SPAWN
    marioObj.oUnkBC = cappy.oAction
    marioObj.oUnkC0 = marioObj.oTimer
    marioObj.oUnk1A8 = cappy.oBehParams2ndByte
    gCappyEvents[m.playerIndex][CAPPY_EVENT_SPAWN] = marioObj.oTimer
end

local function cappy_process_event_spawn(m, cappy)
    local marioObj = m.marioObj
    if marioObj == nil then return end
    if marioObj.oUnk94 ~= CAPPY_EVENT_SPAWN then return end
    if marioObj.oUnkBC ~= cappy.oAction then return end
    if marioObj.oUnkC0 == 0 then return end
    if marioObj.oUnkC0 == gCappyEvents[m.playerIndex][CAPPY_EVENT_SPAWN] then return end
    cappy.oBehParams2ndByte = marioObj.oUnk1A8
    gCappyEvents[m.playerIndex][CAPPY_EVENT_SPAWN] = marioObj.oUnkC0
    cappy.oSubAction = 1
    cappy.oTimer = if_then_else(cappy.oBehParams2ndByte < CAPPY_BHV_SPIN_GROUND, -4, 0)
    cappy.oCapUnkF8 = 0
end

-- Init event: triggered when Cappy timer reaches -1 (one frame before cappy_init_behavior)
local function cappy_send_event_init(m, cappy)
    local marioObj = m.marioObj
    if m.playerIndex ~= 0 or marioObj == nil then return end
    marioObj.oUnk94 = CAPPY_EVENT_INIT
    marioObj.oUnkBC = cappy.oAction
    marioObj.oUnkC0 = marioObj.oTimer
    marioObj.oUnk1A8 = cappy.oDragStrength
    gCappyEvents[m.playerIndex][CAPPY_EVENT_INIT] = marioObj.oTimer
end

local function cappy_process_event_init(m, cappy)
    local marioObj = m.marioObj
    if marioObj == nil then return end
    if marioObj.oUnk94 ~= CAPPY_EVENT_INIT then return end
    if marioObj.oUnkBC ~= cappy.oAction then return end
    if marioObj.oUnkC0 == 0 then return end
    if marioObj.oUnkC0 == gCappyEvents[m.playerIndex][CAPPY_EVENT_INIT] then return end
    cappy.oDragStrength = marioObj.oUnk1A8
    cappy.oTimer = 0
    gCappyEvents[m.playerIndex][CAPPY_EVENT_INIT] = marioObj.oUnkC0
end

-- Homing event: triggered when a player press a D-pad button to perform a homing attack
local function cappy_send_event_homing(m, cappy)
    local marioObj = m.marioObj
    if m.playerIndex ~= 0 or marioObj == nil then return end
    marioObj.oUnk94 = CAPPY_EVENT_HOMING
    marioObj.oUnkBC = cappy.oAction
    marioObj.oUnkC0 = marioObj.oTimer
    marioObj.oHomeX = cappy.oPosX
    marioObj.oHomeY = cappy.oPosY
    marioObj.oHomeZ = cappy.oPosZ
    marioObj.oParentRelativePosX = cappy.oVelX
    marioObj.oParentRelativePosY = cappy.oVelY
    marioObj.oParentRelativePosZ = cappy.oVelZ
    gCappyEvents[m.playerIndex][CAPPY_EVENT_HOMING] = marioObj.oTimer
end

local function cappy_process_event_homing(m, cappy)
    local marioObj = m.marioObj
    if marioObj == nil then return end
    if marioObj.oUnk94 ~= CAPPY_EVENT_HOMING then return end
    if marioObj.oUnkBC ~= cappy.oAction then return end
    if marioObj.oUnkC0 == 0 then return end
    if marioObj.oUnkC0 == gCappyEvents[m.playerIndex][CAPPY_EVENT_HOMING] then return end
    cappy.oPosX = marioObj.oHomeX
    cappy.oPosY = marioObj.oHomeY
    cappy.oPosZ = marioObj.oHomeZ
    cappy.oVelX = marioObj.oParentRelativePosX
    cappy.oVelY = marioObj.oParentRelativePosY
    cappy.oVelZ = marioObj.oParentRelativePosZ
    gCappyEvents[m.playerIndex][CAPPY_EVENT_HOMING] = marioObj.oUnkC0
    cappy.oTimer = math.max(20, CAPPY_LIFETIME - CAPPY_HOMING_DURATION - 1)
    cappy.oCapUnkF8 = 2
end

-- Return event: triggered when a player's Cappy enters the state 'Return to Mario'
local function cappy_send_event_return(m, cappy)
    local marioObj = m.marioObj
    if m.playerIndex ~= 0 or marioObj == nil then return end
    marioObj.oUnk94 = CAPPY_EVENT_RETURN
    marioObj.oUnkBC = cappy.oAction
    marioObj.oUnkC0 = marioObj.oTimer
    marioObj.oHomeX = cappy.oPosX
    marioObj.oHomeY = cappy.oPosY
    marioObj.oHomeZ = cappy.oPosZ
end

local function cappy_process_event_return(m, cappy)
    local marioObj = m.marioObj
    if marioObj == nil then return end
    if marioObj.oUnk94 ~= CAPPY_EVENT_RETURN then return end
    if marioObj.oUnkBC ~= cappy.oAction then return end
    if marioObj.oUnkC0 == 0 then return end
    if marioObj.oUnkC0 == gCappyEvents[m.playerIndex][CAPPY_EVENT_RETURN] then return end
    cappy.oPosX = marioObj.oHomeX
    cappy.oPosY = marioObj.oHomeY
    cappy.oPosZ = marioObj.oHomeZ
    gCappyEvents[m.playerIndex][CAPPY_EVENT_RETURN] = marioObj.oUnkC0
end

-- Unload event: triggered when a player's Cappy must be unloaded
local function cappy_send_event_unload(m, cappy)
    local marioObj = m.marioObj
    if m.playerIndex ~= 0 or marioObj == nil then return end
    marioObj.oUnk94 = CAPPY_EVENT_UNLOAD
    marioObj.oUnkBC = cappy.oAction
    marioObj.oUnkC0 = marioObj.oTimer
    gCappyEvents[m.playerIndex][CAPPY_EVENT_UNLOAD] = marioObj.oTimer
end

local function cappy_process_event_unload(m, cappy)
    local marioObj = m.marioObj
    if marioObj == nil then return end
    if marioObj.oUnk94 ~= CAPPY_EVENT_UNLOAD then return end
    if marioObj.oUnkBC ~= cappy.oAction then return end
    if marioObj.oUnkC0 == 0 then return end
    if marioObj.oUnkC0 == gCappyEvents[m.playerIndex][CAPPY_EVENT_UNLOAD] then return end
    gCappyEvents[m.playerIndex][CAPPY_EVENT_UNLOAD] = marioObj.oUnkC0
    cappy.oSubAction = 0
end

-- Bounce event: triggered when a player bounces on a Cappy
local function cappy_send_event_bounce(m, cappy)
    local marioObj = m.marioObj
    if m.playerIndex ~= 0 or marioObj == nil then return end
    marioObj.oUnk94 = CAPPY_EVENT_BOUNCE
    marioObj.oUnkBC = cappy.oAction
    marioObj.oUnkC0 = marioObj.oTimer
    gCappyEvents[m.playerIndex][CAPPY_EVENT_BOUNCE] = marioObj.oTimer
end

local function cappy_process_event_bounce(m, cappy)
    local marioObj = m.marioObj
    if marioObj == nil then return end
    if marioObj.oUnk94 ~= CAPPY_EVENT_BOUNCE then return end
    if marioObj.oUnkBC ~= cappy.oAction then return end
    if marioObj.oUnkC0 == 0 then return end
    if marioObj.oUnkC0 == gCappyEvents[m.playerIndex][CAPPY_EVENT_BOUNCE] then return end
    gCappyEvents[m.playerIndex][CAPPY_EVENT_BOUNCE] = marioObj.oUnkC0
    cappy.oSubAction = 0
end

-- Process events
local function cappy_process_events(m)
    local cappy = obj_get_first_with_behavior_id(id_bhvCappy)
    while cappy ~= nil do
        cappy_process_event_spawn (m, cappy)
        cappy_process_event_init  (m, cappy)
        cappy_process_event_homing(m, cappy)
        cappy_process_event_return(m, cappy)
        cappy_process_event_unload(m, cappy)
        cappy_process_event_bounce(m, cappy)
        cappy = obj_get_next_with_same_behavior_id(cappy)
    end
end

----------
-- Step --
----------

local function cappy_return_to_mario(m, cappy)
    if cappy.oTimer <= CAPPY_LIFETIME then
        cappy.oTimer = CAPPY_LIFETIME + 1
        cappy_send_event_return(m, cappy)
    end
end

local function cappy_bounce_back(m, cappy)
    if cappy.oBehParams2ndByte < CAPPY_BHV_SPIN_GROUND then
        spawn_non_sync_object(id_bhvHorStarParticleSpawner, E_MODEL_NONE, cappy.oPosX, cappy.oPosY, cappy.oPosZ, nil)
        play_sound(SOUND_OBJ_DEFAULT_DEATH, cappy.header.gfx.cameraToObject)
        cappy_return_to_mario(m, cappy)
    end
end

local function cappy_perform_step(m, cappy, vx, vy, vz, wallColHandler, floorColHandler)
    for _ = 1, CAPPY_NUM_STEPS do
        local x = cappy.oPosX
        local y = cappy.oPosY
        local z = cappy.oPosZ
        obj_move_xyz(cappy,
            vx / CAPPY_NUM_STEPS,
            vy / CAPPY_NUM_STEPS,
            vz / CAPPY_NUM_STEPS
        )

        -- Walls
        if (m.flags & MARIO_VANISH_CAP) == 0 then
            local pos = { x = cappy.oPosX, y = cappy.oPosY, z = cappy.oPosZ }
            local wall = resolve_and_return_wall_collisions(pos, CAPPY_HITBOX_HEIGHT / 2, CAPPY_WALL_RADIUS)
            if wall ~= nil then
                obj_set_pos(cappy, pos.x, pos.y, pos.z)
                if wallColHandler == CAPPY_COL_WALL_DEFAULT then
                    local wallDYaw = s16(atan2s(wall.normal.z, wall.normal.x) - atan2s(cappy.oVelZ, cappy.oVelX))
                    if (wallDYaw < 0x2000 or wallDYaw > 0x6000) and (wallDYaw > -0x2000 or wallDYaw < -0x6000) then
                        obj_set_vel(cappy, 0, 0, 0)
                        return
                    end
                elseif wallColHandler == CAPPY_COL_WALL_FULL_STOP then
                    return
                end
            end
        end

        -- Floor
        local floorY = find_floor_height(cappy.oPosX, cappy.oPosY, cappy.oPosZ)
        if floorY > gLevelValues.floorLowerLimit then
            local diffY = cappy.oPosY - floorY
            if diffY < 0 then
                cappy.oPosY = floorY
                if floorColHandler == CAPPY_COL_FLOOR_CHANGE_BEHAVIOR then
                    if cappy.oVelY ~= 0 then
                        vx = (CAPPY_BHV_DEFAULT_VEL / CAPPY_BHV_DOWNWARDS_VEL) * sins(cappy.oMoveAngleYaw) * math.abs(cappy.oVelY)
                        vz = (CAPPY_BHV_DEFAULT_VEL / CAPPY_BHV_DOWNWARDS_VEL) * coss(cappy.oMoveAngleYaw) * math.abs(cappy.oVelY)
                        vy = 0
                        obj_set_vel(cappy, vx, vy, vz)
                    end
                end
            end
        else
            obj_set_pos(cappy, x, y, z)
        end

        -- Ceiling
        if (m.flags & MARIO_VANISH_CAP) == 0 then
            local ceilY = find_ceil_height(cappy.oPosX, cappy.oPosY, cappy.oPosZ)
            if ceilY < gLevelValues.cellHeightLimit then
                local height = CAPPY_HITBOX_HEIGHT - CAPPY_HITBOX_OFFSET
                if ceilY - height < cappy.oPosY and cappy.oPosY < ceilY then
                    cappy.oPosY = math.max(ceilY - height, floorY)
                end
            end
        end
    end
end

local function cappy_slowdown(cappy)
    obj_set_vel(cappy,
        cappy.oVelX / CAPPY_SLOWDOWN_FACTOR,
        cappy.oVelY / CAPPY_SLOWDOWN_FACTOR,
        cappy.oVelZ / CAPPY_SLOWDOWN_FACTOR
    )
end

local function cappy_call_back(m, cappy, cbStart)
    if cappy.oTimer >= cbStart then
        local udlrx = m.controller.buttonPressed & (U_JPAD | D_JPAD | L_JPAD | R_JPAD | X_BUTTON)
        if udlrx ~= 0 then

            -- Homing attack
            if (udlrx & X_BUTTON) == 0 then
                cappy.oCapUnkF8 = 2
                cappy.oTimer = math.max(20, CAPPY_LIFETIME - CAPPY_HOMING_DURATION - 1)
                local cappyBhv = cappy.oBehParams2ndByte
                local duration = CAPPY_LIFETIME - (cappy.oTimer + 1)
                local ox, oy, oz, velocity
                if cappyBhv == CAPPY_BHV_SPIN_GROUND or cappyBhv == CAPPY_BHV_SPIN_AIR or cappyBhv == CAPPY_BHV_FLYING then
                    ox, oy, oz, velocity = m.pos.x, m.pos.y, m.pos.z, CAPPY_HOMING_VELOCITY_SPIN
                else
                    ox, oy, oz, velocity = cappy.oPosX, cappy.oPosY, cappy.oPosZ, CAPPY_HOMING_VELOCITY
                end
                target = cappy_find_target(m, ox, oy, oz, velocity * duration)
                if target ~= nil then
                    local dx = target.oPosX - cappy.oPosX
                    local dy = target.oPosY - cappy.oPosY
                    local dz = target.oPosZ - cappy.oPosZ
                    local dv = math.sqrt(dx^2 + dy^2 + dz^2)
                    if dv > velocity * duration then
                        obj_set_vel(cappy, dx / duration, dy / duration, dz / duration)
                        cappy_send_event_homing(m, cappy)
                    elseif dv ~= 0 then
                        obj_set_vel(cappy, velocity * dx / dv, velocity * dy / dv, velocity * dz / dv)
                        cappy_send_event_homing(m, cappy)
                    else
                        cappy_return_to_mario(m, cappy)
                    end
                else
                    if (cappyBhv == CAPPY_BHV_DEFAULT_GROUND or cappyBhv == CAPPY_BHV_DEFAULT_AIR or
                        cappyBhv == CAPPY_BHV_UPWARDS_GROUND or cappyBhv == CAPPY_BHV_UPWARDS_AIR or
                        cappyBhv == CAPPY_BHV_DOWNWARDS_GROUND or cappyBhv == CAPPY_BHV_DOWNWARDS_AIR) then
                        if udlrx == U_JPAD then
                            obj_set_vel(cappy, 0, velocity, 0)
                        elseif udlrx == D_JPAD then
                            obj_set_vel(cappy, 0, -velocity, 0)
                        elseif udlrx == L_JPAD then
                            obj_set_vel(cappy, velocity * sins(cappy.oMoveAngleYaw + 0x4000), 0, velocity * coss(cappy.oMoveAngleYaw + 0x4000))
                        elseif udlrx == R_JPAD then
                            obj_set_vel(cappy, velocity * sins(cappy.oMoveAngleYaw - 0x4000), 0, velocity * coss(cappy.oMoveAngleYaw - 0x4000))
                        else
                            cappy_return_to_mario(m, cappy)
                            return
                        end
                        cappy_send_event_homing(m, cappy)
                    else
                        cappy_return_to_mario(m, cappy)
                    end
                end
            else
                cappy_return_to_mario(m, cappy)
            end
        end
    end
end

local function cappy_perform_step_return_to_mario(m, cappy)
    local marioObj = m.marioObj
    local marioGfx = marioObj.header.gfx

    -- Disable interactions
    cappy.oCapUnkF8 = 0

    -- Move Cappy closer to Mario
    local dx = m.pos.x - cappy.oPosX
    local dy = m.pos.y - cappy.oPosY + (0.4 * marioObj.hitboxHeight * marioGfx.scale.y)
    local dz = m.pos.z - cappy.oPosZ
    local dv = math.sqrt(dx^2 + dy^2 + dz^2)
    if dv > CAPPY_RETURN_VEL then
        obj_move_xyz(cappy,
            (dx / dv) * CAPPY_RETURN_VEL,
            (dy / dv) * CAPPY_RETURN_VEL,
            (dz / dv) * CAPPY_RETURN_VEL
        )
    else
        obj_move_xyz(cappy, dx, dy, dz)
    end

    -- Unloads Cappy if he's close enough to Mario
    local marioRadius = marioGfx.scale.x * 50
    local cappyRadius = CAPPY_GFX_SCALE_X * CAPPY_HITBOX_RADIUS / 2
    return dv - CAPPY_RETURN_VEL <= marioRadius + cappyRadius
end

-------------------------
-- Object interactions --
-------------------------

local CAPPY_INTERACTION_LISTS = {
    OBJ_LIST_DEFAULT,
    OBJ_LIST_LEVEL,
    OBJ_LIST_PLAYER,
    OBJ_LIST_SURFACE,
    OBJ_LIST_PUSHABLE,
    OBJ_LIST_GENACTOR,
    OBJ_LIST_DESTRUCTIVE,
}

local m0 = gMarioStates[0]

local obj_is_valid_for_interaction = obj_is_valid_for_interaction
local obj_is_coin = obj_is_coin
local obj_is_mushroom_1up = obj_is_mushroom_1up
local obj_is_exclamation_box = obj_is_exclamation_box
local obj_is_bully = obj_is_bully
local obj_is_grabbable = obj_is_grabbable
local obj_is_attackable = obj_is_attackable

local function obj_is_remote_mario(obj)
    if obj == gMarioStates[0].marioObj then return false end
    if obj_has_behavior_id(obj, id_bhvMario) == 0 then return false end
    if (obj.header.gfx.node.flags & GRAPH_RENDER_ACTIVE) == 0 then return false end
    if (obj.header.gfx.node.flags & GRAPH_RENDER_INVISIBLE) ~= 0 then return false end
    if gMarioStates[obj.oBehParams - 1].action == ACT_BUBBLED then return true end
    if obj.oIntangibleTimer ~= 0 then return false end
    if obj.oInteractStatus ~= 0 then return false end
    return true
end

local function obj_is_treasure_chest(obj)
    return obj_has_behavior_id(obj, id_bhvTreasureChestBottom) == 1 and obj.oAction == 0
end

local function obj_is_breakable(obj)
    return (
        obj_has_behavior_id(obj, id_bhvBreakableBox) == 1 or
        obj_has_behavior_id(obj, id_bhvBreakableBoxSmall) == 1 or
        obj_has_behavior_id(obj, id_bhvHiddenObject) == 1 or
        obj_has_behavior_id(obj, id_bhvJumpingBox) == 1
    )
end

local function cappy_is_obj_targetable(m, obj)
    if obj_is_treasure_chest(obj) then return true end
    if obj_is_remote_mario(obj) then return true end
    if obj_is_valid_for_interaction(obj) == false then return false end
    if obj_is_coin(obj) then return true end
    if obj_is_mushroom_1up(obj) then return true end
    if obj_is_exclamation_box(obj) then return true end
    if obj_is_bully(obj) then return true end
    if obj_is_grabbable(obj) then return true end
    if obj_is_breakable(obj) then return true end
    if obj_is_attackable(obj) then return true end
    return false
end

function cappy_find_target(m, ox, oy, oz, distmax)
    local target = nil
    local targetCoin = nil
    local distmin = distmax
    local distminCoin = distmax
    for _, objList in pairs(CAPPY_INTERACTION_LISTS) do
        local obj = obj_get_first(objList)
        while obj ~= nil do
            if cappy_is_obj_targetable(m, obj) then
                local distToCappy = math.sqrt((ox - obj.oPosX)^2 + (oy - obj.oPosY)^2 + (oz - obj.oPosZ)^2) - (CAPPY_HITBOX_RADIUS + obj.hitboxRadius)
                if obj_is_coin(obj) then
                    if distToCappy < distminCoin then
                        distminCoin = distToCappy
                        targetCoin = obj
                    end
                else
                    if distToCappy < distmin then
                        distmin = distToCappy
                        target = obj
                    end
                end
            end
            obj = obj_get_next(obj)
        end
    end
    return if_then_else(targetCoin ~= nil, targetCoin, target)
end

local function cappy_mario_can_grab(m, obj)
    local marioAction = m.action
    if m.heldObj ~= nil or m.riddenObj ~= nil then return false end
    if marioAction == ACT_FIRST_PERSON then return false end
    if (marioAction & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE then return false end
    if (marioAction & ACT_GROUP_MASK) == ACT_GROUP_AUTOMATIC then return false end
    if (marioAction & ACT_FLAG_AIR) ~= 0 then return false end
    if (marioAction & ACT_FLAG_SWIMMING) ~= 0 then return false end
    if (marioAction & ACT_FLAG_METAL_WATER) ~= 0 then return false end
    if (marioAction & ACT_FLAG_ON_POLE) ~= 0 then return false end
    if (marioAction & ACT_FLAG_HANGING) ~= 0 then return false end
    if (marioAction & ACT_FLAG_INTANGIBLE) ~= 0 then return false end
    if (marioAction & ACT_FLAG_INVULNERABLE) ~= 0 then return false end
    if (marioAction & ACT_FLAG_RIDING_SHELL) ~= 0 then return false end
    if (obj_has_behavior_id(obj, id_bhvBowser) == 1) then return false end
    if (obj_has_behavior_id(obj, id_bhvBowserTailAnchor) == 1) then return false end
    return true
end

local function cappy_process_object_interaction(m, cappy, obj)
    local marioObj = m.marioObj

    -- Coin
    --- Teleport it to Mario
    --- Homing attack: target the next nearest coin or object
    if obj_is_coin(obj) then

        -- Target next nearest object
        if cappy.oCapUnkF8 == 2 then
            obj.oInteractStatus = INT_STATUS_INTERACTED
            local duration = CAPPY_HOMING_DURATION
            local velocity = CAPPY_HOMING_VELOCITY_COIN
            local target = cappy_find_target(m, cappy.oPosX, cappy.oPosY, cappy.oPosZ, velocity * duration)
            obj.oInteractStatus = 0
            if target ~= nil then
                local dx = target.oPosX - cappy.oPosX
                local dy = target.oPosY - cappy.oPosY
                local dz = target.oPosZ - cappy.oPosZ
                local dv = math.sqrt(dx^2 + dy^2 + dz^2)
                if dv > velocity * duration then
                    obj_set_vel(cappy, dx / duration, dy / duration, dz / duration)
                    cappy.oTimer = math.max(20, CAPPY_LIFETIME - CAPPY_HOMING_DURATION - 1)
                    cappy_send_event_homing(m, cappy)
                elseif dv ~= 0 then
                    obj_set_vel(cappy, velocity * dx / dv, velocity * dy / dv, velocity * dz / dv)
                    cappy.oTimer = math.max(20, CAPPY_LIFETIME - CAPPY_HOMING_DURATION - 1)
                    cappy_send_event_homing(m, cappy)
                end
            end
        end

        -- Collect coin
        if m.playerIndex == 0 then
            if interact_coin then
                interact_coin(m, 0, obj)
            else
                obj_set_pos(obj,
                    m.pos.x + m.vel.x,
                    m.pos.y + m.vel.y + 60,
                    m.pos.z + m.vel.z
                )
            end
        else
            obj.oIntangibleTimer = -1
            obj.oInteractStatus = INT_STATUS_INTERACTED
        end
        obj.header.gfx.node.flags = obj.header.gfx.node.flags | GRAPH_RENDER_INVISIBLE
        return true
    end

    -- Secret
    --- Set interacted flag to collect it
    if obj_is_secret(obj) then
        obj.oInteractStatus = INT_STATUS_INTERACTED
        return false
    end

    -- Exclamation box
    --- Attack it to break it
    if obj_is_exclamation_box(obj) then
        obj.oInteractStatus = INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED
        cappy_bounce_back(m, cappy)
        return true
    end

    -- Bully
    --- Bully the bully
    if obj_is_bully(obj) then
        local angle = obj_angle_to_object(obj, marioObj)
        obj.oForwardVel = 3600 / obj.hitboxRadius
        obj.oFaceAngleYaw = angle
        obj.oMoveAngleYaw = angle + 0x8000
        obj.oInteractStatus = ATTACK_KICK_OR_TRIP | INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED
        play_sound(SOUND_OBJ_BULLY_METAL, obj.header.gfx.cameraToObject)
        cappy_bounce_back(m, cappy)
        return true
    end

    -- Grabbable
    --- Make Mario instantly grab the interacted object
    --- Change the current animation to the first punch, and make it end next frame
    if obj_is_grabbable(obj) then
        if cappy_mario_can_grab(m, obj) then
            if m.playerIndex == 0 then
                m.usedObj = obj
                mario_grab_used_object(m)
                mario_set_action(m, ACT_PICKING_UP, 0, 0)
                set_mario_animation(m, MARIO_ANIM_FIRST_PUNCH)
                local animInfo = marioObj.header.gfx.animInfo
                mario_anim_clamp(animInfo, animInfo.curAnim.loopEnd - 2, animInfo.curAnim.loopEnd - 2)
            end
            cappy_return_to_mario(m, cappy)
            return true
        end
    end

    -- Breakable
    --- Set some specific flags to send a signal 'break that box'
    if obj_is_breakable(obj) then
        obj.oInteractStatus = ATTACK_KICK_OR_TRIP | INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED | INT_STATUS_STOP_RIDING
        cappy_bounce_back(m, cappy)
        return true
    end

    -- Attackable
    --- Attack it to damage it
    --- Do a ground-pound type attack to huge goombas to make them spawn their blue coin
    if obj_is_attackable(obj) then
        if obj_has_behavior_id(obj, id_bhvGoomba) and (obj.oGoombaSize & 1) ~= 0 then
            obj.oInteractStatus = ATTACK_GROUND_POUND_OR_TWIRL | INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED
        elseif obj_has_behavior_id(obj, id_bhvWigglerHead) then
            obj.oInteractStatus = ATTACK_GROUND_POUND_OR_TWIRL | INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED
        else
            obj.oInteractStatus = ATTACK_KICK_OR_TRIP | INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED
        end
        cappy_bounce_back(m, cappy)
        return true
    end

    -- Mushroom 1up
    --- Teleport it to Mario
    if obj_is_mushroom_1up(obj) then
        obj_set_pos(obj,
            m.pos.x + m.vel.x,
            m.pos.y + m.vel.y + 60,
            m.pos.z + m.vel.z
        )
        obj.header.gfx.node.flags = obj.header.gfx.node.flags | GRAPH_RENDER_INVISIBLE
        return false
    end

    -- No interaction
    return false
end

local function cappy_process_object_interactions(m, cappy)

    -- Basic interactions
    for _, objList in pairs(CAPPY_INTERACTION_LISTS) do
        local obj = obj_get_first(objList)
        while obj ~= nil do
            if (obj_is_valid_for_interaction(obj) and
                obj_check_hitbox_overlap(cappy, obj) and
                cappy_process_object_interaction(m, cappy, obj)) then
                return
            end
            obj = obj_get_next(obj)
        end
    end

    -- Treasure chests
    local obj = obj_get_first_with_behavior_id(id_bhvTreasureChestBottom)
    while obj ~= nil do
        local parentObj = obj.parentObj
        if obj.oAction == 0 and parentObj ~= nil then -- Not open
            obj.hitboxRadius = 120
            obj.hitboxHeight = 150
            obj.hurtboxRadius = 120
            obj.hurtboxHeight = 150
            obj.hitboxDownOffset = 0
            if obj_check_hitbox_overlap(cappy, obj) then
                if m.playerIndex == 0 then
                    if parentObj.oTreasureChestCurrentAnswer == obj.oBehParams2ndByte then
                        play_sound(SOUND_GENERAL2_RIGHT_ANSWER, obj.header.gfx.cameraToObject)
                        parentObj.oTreasureChestIsLastInteractionIncorrect = 0
                        parentObj.oTreasureChestCurrentAnswer = parentObj.oTreasureChestCurrentAnswer + 1
                        parentObj.oTreasureChestSound = 1
                        obj.oAction = 1
                    else
                        play_sound(SOUND_MENU_CAMERA_BUZZ, obj.header.gfx.cameraToObject)
                        parentObj.oTreasureChestIsLastInteractionIncorrect = 1
                        parentObj.oTreasureChestCurrentAnswer = 1
                        parentObj.oTreasureChestSound = 2
                        obj.oAction = 2
                        obj.oDamageOrCoinValue = 1
                        take_damage_and_knock_back(m, obj)
                    end
                    parentObj.oTreasureChestLastNetworkPlayerIndex = gNetworkPlayers[m.playerIndex].globalIndex
                    if (parentObj.coopFlags & COOP_OBJ_FLAG_NON_SYNC) == 0 and parentObj.oSyncID > 0 then
                        network_send_object(parentObj, false)
                    end
                    parentObj.oTreasureChestSound = 0
                end
                cappy_bounce_back(m, cappy)
                obj.hitboxRadius = 300
                obj.hitboxHeight = 300
                obj.hurtboxRadius = 310
                obj.hurtboxHeight = 310
                obj.hitboxDownOffset = 0
                return
            end
        end
        obj.hitboxRadius = 300
        obj.hitboxHeight = 300
        obj.hurtboxRadius = 310
        obj.hurtboxHeight = 310
        obj.hitboxDownOffset = 0
        obj = obj_get_next_with_same_behavior_id(obj)
    end
end

------------------------
-- Mario interactions --
------------------------

local function cappy_mario_can_bounce()
    local marioAction = m0.action
    if m0.heldObj ~= nil or m0.riddenObj ~= nil then return false end
    if m0.vel.y <= 0 and (marioAction == ACT_LAVA_BOOST or marioAction == ACT_LAVA_BOOST_LAND) then return true end
    if marioAction == ACT_BUBBLED then return true end
    if marioAction == ACT_FIRST_PERSON then return false end
    if (marioAction & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE then return false end
    if (marioAction & ACT_GROUP_MASK) == ACT_GROUP_AUTOMATIC then return false end
    if (marioAction & ACT_FLAG_ON_POLE) ~= 0 then return false end
    if (marioAction & ACT_FLAG_HANGING) ~= 0 then return false end
    if (marioAction & ACT_FLAG_INTANGIBLE) ~= 0 then return false end
    if (marioAction & ACT_FLAG_INVULNERABLE) ~= 0 then return false end
    if (marioAction & ACT_FLAG_RIDING_SHELL) ~= 0 then return false end
    if (marioAction & ACT_FLAG_METAL_WATER) ~= 0 then return false end
    return true
end

local function cappy_process_mario_interactions(cappy)
    if cappy_mario_can_bounce() then
        local marioObj = m0.marioObj
        obj_set_pos(marioObj, m0.pos.x, m0.pos.y, m0.pos.z)
        marioObj.hitboxRadius = 50
        local obj = obj_get_first_with_behavior_id(id_bhvCappy)
        while obj ~= nil do
            if (obj.oSubAction == 1 and         -- Cappy is spawned
                obj.oTimer > 0 and              -- Cappy is active
                obj.oTimer < CAPPY_LIFETIME and -- Cappy is not returning to Mario
                obj.oCapUnkF4 == 0 and (        -- Mario can bounce on that Cappy
                obj.oCapUnkF8 == 1 or           -- Cappy can interact with Mario
                obj.oAction ~= cappy.oAction)   -- That Cappy is not local Mario's
            ) then
                local mAction = m0.action

                -- Check that Cappy interaction setting
                if (marioObj.oIntangibleTimer == 0 or mAction == ACT_BUBBLED) then

                    -- Check hitbox overlap
                    if obj_check_hitbox_overlap(marioObj, obj) then
                        local marioGfx = marioObj.header.gfx

                        -- Pop bubble
                        if mAction == ACT_BUBBLED then
                            m0.vel.x = 0
                            m0.vel.y = 0
                            m0.vel.z = 0
                            m0.health = 0x100
                            m0.hurtCounter = 0
                            m0.healCounter = 31
                            m0.peakHeight = m0.pos.y
                            marioObj.oIntangibleTimer = 0
                            marioObj.activeFlags = marioObj.activeFlags & ~ACTIVE_FLAG_MOVE_THROUGH_GRATE
                            marioGfx.node.flags = marioGfx.node.flags & ~GRAPH_RENDER_INVISIBLE
                            if m0.pos.y < m0.waterLevel then
                                mario_set_action(m0, ACT_WATER_IDLE, 0, 0)
                            else
                                mario_set_action(m0, ACT_FREEFALL, 0, 0)
                            end
                            play_sound(SOUND_OBJ_DEFAULT_DEATH, marioGfx.cameraToObject)

                        -- Cappy bounce
                        elseif ((mAction & ACT_FLAG_AIR) ~= 0 or m0.floor.type == SURFACE_BURNING) and (mAction & ACT_FLAG_SWIMMING) == 0 then
                            obj.oCapUnkF4 = 1
                            if m0.framesSinceA < 3 then
                                mario_set_action(m0, ACT_CAPPY_VAULT, 0, 0)
                                m0.particleFlags = m0.particleFlags | PARTICLE_SPARKLES
                            else
                                mario_set_action(m0, ACT_CAPPY_BOUNCE, 0, 0)
                            end
                            play_sound(SOUND_GENERAL_BOING1, marioGfx.cameraToObject)
                            m0.particleFlags = m0.particleFlags | PARTICLE_HORIZONTAL_STAR

                        -- Cappy vault
                        elseif (mAction & ACT_FLAG_SWIMMING) == 0 then
                            mario_set_action(m0, ACT_CAPPY_VAULT, 0, 0)
                            play_sound(SOUND_GENERAL_BOING1, marioGfx.cameraToObject)
                            m0.particleFlags = m0.particleFlags | PARTICLE_HORIZONTAL_STAR
                        else
                            return
                        end

                        -- Unload interacted Cappy
                        cappy_send_event_bounce(m0, obj)
                        obj.oSubAction = 0
                        return
                    end
                end
            end
            obj = obj_get_next_with_same_behavior_id(obj)
        end
    end
end

--------------
-- Behavior --
--------------

local function cappy_get_behavior(m)
    local action = m.action
    local controller = m.controller
    local air = (action & (ACT_FLAG_AIR | ACT_FLAG_SWIMMING)) ~= 0 and 1 or 0
    if (action & ACT_FLAG_FLYING) == ACT_FLAG_FLYING then return CAPPY_BHV_FLYING end
    if (action & ACT_FLAG_RIDING_SHELL) ~= 0 then return CAPPY_BHV_SPIN_GROUND + air end
    if (controller.buttonDown & U_JPAD) ~= 0 then return CAPPY_BHV_UPWARDS_GROUND + air end
    if (controller.buttonDown & D_JPAD) ~= 0 then return CAPPY_BHV_DOWNWARDS_GROUND + air end
    if (controller.buttonDown & L_JPAD) ~= 0 then return CAPPY_BHV_SPIN_GROUND + air end
    if (controller.buttonDown & R_JPAD) ~= 0 then return CAPPY_BHV_SPIN_GROUND + air end
    if (controller.buttonPressed & A_BUTTON) ~= 0 then return CAPPY_BHV_UPWARDS_GROUND + air end
    if action == ACT_GROUND_POUND_LAND then return CAPPY_BHV_DOWNWARDS_GROUND end
    return CAPPY_BHV_DEFAULT_GROUND + air
end

local function cappy_init_behavior(m, cappy)
    local cappyBhv = cappy.oBehParams2ndByte
    local isWater = if_then_else((m.action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED and (m.action & ACT_FLAG_METAL_WATER) == 0, 1, 0)
    local throwStrength = cappy.oDragStrength / 4
    cappy.hitboxRadius = CAPPY_HITBOX_RADIUS
    cappy.hitboxHeight = CAPPY_HITBOX_HEIGHT
    cappy.hitboxDownOffset = CAPPY_HITBOX_OFFSET
    cappy.oInteractType = 0
    cappy.oDamageOrCoinValue = 0
    obj_set_angle(cappy, 0, 0, 0)

    -- Regular throw
    if cappyBhv == CAPPY_BHV_DEFAULT_GROUND or cappyBhv == CAPPY_BHV_DEFAULT_AIR then
        obj_set_pos(cappy,
            m.pos.x,
            m.pos.y + CAPPY_BHV_DEFAULT_OFFSET * (1 - isWater),
            m.pos.z
        )
        obj_set_vel(cappy,
            CAPPY_BHV_DEFAULT_VEL * throwStrength * coss(m.faceAngle.x * isWater) * sins(m.faceAngle.y),
            CAPPY_BHV_DEFAULT_VEL * throwStrength * sins(m.faceAngle.x * isWater),
            CAPPY_BHV_DEFAULT_VEL * throwStrength * coss(m.faceAngle.x * isWater) * coss(m.faceAngle.y)
        )

    -- Up-throw
    elseif cappyBhv == CAPPY_BHV_UPWARDS_GROUND or cappyBhv == CAPPY_BHV_UPWARDS_AIR then
        obj_set_pos(cappy,
            m.pos.x + CAPPY_BHV_UPWARDS_OFFSET * sins(m.faceAngle.y),
            m.pos.y + CAPPY_BHV_UPWARDS_OFFSET,
            m.pos.z + CAPPY_BHV_UPWARDS_OFFSET * coss(m.faceAngle.y)
        )
        obj_set_vel(cappy,
            0,
            CAPPY_BHV_UPWARDS_VEL,
            0
        )

    -- Down-throw
    elseif cappyBhv == CAPPY_BHV_DOWNWARDS_GROUND or cappyBhv == CAPPY_BHV_DOWNWARDS_AIR then
        obj_set_pos(cappy,
            m.pos.x + CAPPY_BHV_DOWNWARDS_OFFSET * sins(m.faceAngle.y),
            m.pos.y + CAPPY_BHV_DOWNWARDS_OFFSET,
            m.pos.z + CAPPY_BHV_DOWNWARDS_OFFSET * coss(m.faceAngle.y)
        )
        obj_set_vel(cappy,
            0,
            -CAPPY_BHV_DOWNWARDS_VEL,
            0
        )

    -- Spin throw
    elseif cappyBhv == CAPPY_BHV_SPIN_GROUND or cappyBhv == CAPPY_BHV_SPIN_AIR then
        obj_set_pos(cappy,
            m.pos.x,
            m.pos.y + CAPPY_BHV_SPIN_OFFSET,
            m.pos.z
        )

    -- Flying throw
    elseif cappyBhv == CAPPY_BHV_FLYING then
        obj_set_pos(cappy,
            m.pos.x,
            m.pos.y + CAPPY_BHV_FLYING_OFFSET,
            m.pos.z
        )
    end
end

local function cappy_update_behavior(m, cappy)
    local cappyBhv = cappy.oBehParams2ndByte

    -- Homing attack
    if cappy.oCapUnkF8 == 2 then
        if (m.controller.buttonPressed & X_BUTTON) ~= 0 then
            cappy_return_to_mario(m, cappy)
        else
            cappy_perform_step(m, cappy, cappy.oVelX, cappy.oVelY, cappy.oVelZ, 0, 0)
        end
        return
    end

    -- Regular throw
    if cappyBhv == CAPPY_BHV_DEFAULT_GROUND or cappyBhv == CAPPY_BHV_DEFAULT_AIR then
        if cappy.oTimer < CAPPY_BHV_DEFAULT_CALL_BACK_START then
            cappy.oCapUnkF8 = 0
            cappy_perform_step(m, cappy, cappy.oVelX, cappy.oVelY, cappy.oVelZ, CAPPY_COL_WALL_DEFAULT, 0)
            cappy_slowdown(cappy)
        else
            cappy.oCapUnkF8 = 1
            cappy_call_back(m, cappy, CAPPY_BHV_DEFAULT_CALL_BACK_START)
        end

    -- Up-throw
    elseif cappyBhv == CAPPY_BHV_UPWARDS_GROUND or cappyBhv == CAPPY_BHV_UPWARDS_AIR then
        if cappy.oTimer < CAPPY_BHV_UPWARDS_CALL_BACK_START then
            cappy.oCapUnkF8 = 0
            cappy_perform_step(m, cappy, cappy.oVelX, cappy.oVelY, cappy.oVelZ, 0, 0)
            cappy_slowdown(cappy)
        else
            cappy.oCapUnkF8 = 1
            cappy_call_back(m, cappy, CAPPY_BHV_UPWARDS_CALL_BACK_START)
        end

    -- Down-throw
    elseif cappyBhv == CAPPY_BHV_DOWNWARDS_GROUND or cappyBhv == CAPPY_BHV_DOWNWARDS_AIR then
        if cappy.oTimer < CAPPY_BHV_DOWNWARDS_CALL_BACK_START then
            cappy.oCapUnkF8 = 0
            cappy_perform_step(m, cappy, cappy.oVelX, cappy.oVelY, cappy.oVelZ, 0, CAPPY_COL_FLOOR_CHANGE_BEHAVIOR)
            cappy_slowdown(cappy)
            if cappy.oVelY == 0 then
                obj_set_vel(cappy, 0, -(math.sqrt(cappy.oVelX^2 + cappy.oVelZ^2) * CAPPY_BHV_DOWNWARDS_VEL) / CAPPY_BHV_DEFAULT_VEL, 0)
            end
        else
            cappy.oCapUnkF8 = 1
            cappy_call_back(m, cappy, CAPPY_BHV_DOWNWARDS_CALL_BACK_START)
        end

    -- Spin throw
    elseif cappyBhv == CAPPY_BHV_SPIN_GROUND or cappyBhv == CAPPY_BHV_SPIN_AIR then
        local r = math.min(cappy.oTimer * CAPPY_BHV_SPIN_RADIUS_GROWTH, CAPPY_BHV_SPIN_RADIUS_MAX)
        local dy = if_then_else((m.action & ACT_FLAG_RIDING_SHELL) ~= 0, 42, 0)
        obj_set_pos(cappy, m.pos.x, m.pos.y + dy + CAPPY_BHV_SPIN_OFFSET, m.pos.z)
        cappy.oMoveAngleYaw = s16(cappy.oMoveAngleYaw + CAPPY_BHV_SPIN_ANGLE_VEL)
        cappy.oCapUnkF8 = 0
        cappy_perform_step(m, cappy, r * coss(cappy.oMoveAngleYaw), 0, r * sins(cappy.oMoveAngleYaw), CAPPY_COL_WALL_FULL_STOP, 0)
        cappy_call_back(m, cappy, CAPPY_BHV_SPIN_CALL_BACK_START)

    -- Flying throw
    elseif cappyBhv == CAPPY_BHV_FLYING then
        if (m.action & ACT_FLAG_FLYING) == ACT_FLAG_FLYING then
            local r = math.min(cappy.oTimer * CAPPY_BHV_FLYING_RADIUS_GROWTH, CAPPY_BHV_FLYING_RADIUS_MAX)
            local a = s16(cappy.oTimer * CAPPY_BHV_FLYING_ANGLE_VEL)
            local v = { x = r * coss(a), y = r * sins(a), z = 0 }
            vec3f_rotate_zxy(v, { x = -m.faceAngle.x, y = m.faceAngle.y, z = 0 })
            obj_set_pos(cappy, m.pos.x, m.pos.y + CAPPY_BHV_FLYING_OFFSET, m.pos.z)
            cappy_perform_step(m, cappy, v.x, v.y, v.z, CAPPY_COL_WALL_FULL_STOP, 0)
        else
            cappy_return_to_mario(m, cappy)
        end
        cappy.oMoveAngleYaw = m.faceAngle.y
        cappy.oCapUnkF8 = 0
        cappy_call_back(m, cappy, CAPPY_BHV_FLYING_CALL_BACK_START)
    end
end

local function cappy_spawn(m)
    local cappy = cappy_get_object(m)
    if cappy ~= nil and cappy.oSubAction == 0 and (m.flags & MARIO_CAP_ON_HEAD) ~= 0 then
        if m.playerIndex == 0 then
            local behavior = cappy_get_behavior(m)
            cappy.oBehParams2ndByte = behavior
            cappy.oSubAction = 1
            cappy.oTimer = if_then_else(behavior < CAPPY_BHV_SPIN_GROUND, -4, 0)
            cappy.oUnkBC = m.marioObj.oTimer
            cappy.oCapUnkF8 = 0
            cappy.oDragStrength = 0
            cappy_send_event_spawn(m, cappy)
        end
        return true
    end
    return false
end

------------
-- Update --
------------

local PAULINE_CAP_MODELS = {
    [0] = "normal",
    [MARIO_WING_CAP] = "wing",
    [MARIO_METAL_CAP] = "metal",
    [MARIO_METAL_CAP | MARIO_WING_CAP] = "metalWing",
}

local function get_pauline_cap_model(m)
    return get_pauline().caps[PAULINE_CAP_MODELS[m.flags & (MARIO_METAL_CAP | MARIO_WING_CAP)]]
end

local function cappy_unload(m, cappy)
    if cappy.oSubAction ~= 0 then
        cappy.oSubAction = 0
        cappy_send_event_unload(m, cappy)
    end
end

local function cappy_update(m, cappy)

    -- Unload Cappy if...
    if (_G.OmmEnabled or                                -- OMM Rebirth is enabled
        not is_pauline(m) or                            -- Not Pauline
        not gNetworkPlayers[m.playerIndex].connected or -- Not connected
        not is_player_active(m)                         -- Not active
    ) then
        cappy_unload(m, cappy)
        cappy.oCapUnkF4 = 0
        return
    end

    -- If not spawned, reset some values
    if cappy.oSubAction == 0 then
        obj_set_pos(cappy, m.pos.x, m.pos.y, m.pos.z)
        obj_set_vel(cappy, 0, 0, 0)
        cappy.oMoveAngleYaw = 0
        cappy.oCapUnkF8 = 0
        cappy.oTimer = -255
        return
    end

    -- Unload Cappy if Mario bubbled
    if m.action == ACT_BUBBLED then
        cappy_unload(m, cappy)
        cappy.oCapUnkF4 = 0
        return
    end

    -- Unload Cappy if Mario lost his cap
    if (m.flags & MARIO_CAP_ON_HEAD) == 0 then
        cappy_unload(m, cappy)
        return
    end

    -- Call Cappy back if Mario is dead
    if m.health < 0x100 then
        cappy_return_to_mario(m, cappy)
    end

    -- Init Cappy
    if cappy.oTimer == 0 then
        cappy_init_behavior(m, cappy)
        cappy.oMoveAngleYaw = m.faceAngle.y
    end

    -- Update Cappy's behavior
    if cappy.oTimer >= 0 then
        if cappy.oTimer < CAPPY_LIFETIME and m.marioObj.header.gfx.node.flags & GRAPH_RENDER_ACTIVE ~= 0 then
            cappy_update_behavior(m, cappy)
            cappy_process_object_interactions(m, cappy)
        elseif cappy.oTimer == CAPPY_LIFETIME then
            cappy_return_to_mario(m, cappy)
        elseif cappy_perform_step_return_to_mario(m, cappy) then
            cappy_unload(m, cappy)
            return
        end
    end

    -- Increase Cappy throw strength
    if m.playerIndex == 0 then
        if cappy.oTimer < 0 and (m.controller.buttonDown & X_BUTTON) ~= 0 then
            cappy.oDragStrength = cappy.oDragStrength + 1
        end
        if m.controller.stickMag > 60 then
            cappy.oDragStrength = 4
        else
            cappy.oDragStrength = clamp(cappy.oDragStrength, 1, 4)
        end
    end

    -- Send an init event when about to init
    if cappy.oTimer == -1 then
        cappy_send_event_init(m, cappy)
    end
end

local function cappy_update_gfx(m, cappy)
    if cappy.oSubAction == 1 and cappy.oTimer >= 0 then
        cappy.oFaceAngleYaw = cappy.oFaceAngleYaw + CAPPY_GFX_ANGLE_VEL
        obj_scale_xyz(cappy, CAPPY_GFX_SCALE_X, CAPPY_GFX_SCALE_Y, CAPPY_GFX_SCALE_Z)
        cappy.header.gfx.node.flags = cappy.header.gfx.node.flags & ~GRAPH_RENDER_INVISIBLE
        obj_set_model_extended(cappy, get_pauline_cap_model(m))
        cappy.oOpacity = if_then_else((m.marioBodyState.modelState & 0x100) ~= 0, m.marioBodyState.modelState & 0xFF, 0xFF)
        if m.playerIndex == 0 then
            spawn_non_sync_object(id_bhvSparkleSpawn, E_MODEL_NONE, cappy.oPosX, cappy.oPosY, cappy.oPosZ, nil)
        end
    else
        cappy.header.gfx.node.flags = cappy.header.gfx.node.flags | GRAPH_RENDER_INVISIBLE
    end
end

function bhv_cappy_loop(o)
    if o.oAction ~= 0 then
        local i = network_local_index_from_global(o.oAction - 1)
        local m = gMarioStates[i]
        cappy_update(m, o)
        cappy_update_gfx(m, o)
    end
end

function pauline_update(m)
    if gNetworkPlayers[m.playerIndex].connected then

        -- Super bounce (3-frame window)
        if (m.controller.buttonDown & A_BUTTON) == 0 then
            m.framesSinceA = 0xFF
        end

        -- Process Mario interactions with Cappy's and update Mario's state
        local cappy = cappy_get_object(m)
        if cappy ~= nil then
            if m.playerIndex == 0 then

                -- Reset bounced flag for all Cappy's when grounded
                if ((m.action & ACT_FLAG_AIR) == 0 and m.floor ~= nil and m.floor.type ~= SURFACE_BURNING) then
                    local obj = obj_get_first_with_behavior_id(id_bhvCappy)
                    while obj ~= nil do
                        obj.oCapUnkF4 = 0
                        obj = obj_get_next_with_same_behavior_id(obj)
                    end
                end
                cappy_process_mario_interactions(cappy)
                m.marioObj.hitboxRadius = 37
            end

            -- Process Cappy events
            cappy_process_events(m)

            -- Update Mario's animation during a spin throw on a shell
            if cappy.oSubAction == 1 and (cappy.oBehParams2ndByte == CAPPY_BHV_SPIN_GROUND or cappy.oBehParams2ndByte == CAPPY_BHV_SPIN_AIR) and (m.action & ACT_FLAG_RIDING_SHELL) ~= 0 then
                local anim = CAPPY_THROW_ANIMS[cappy.oBehParams2ndByte]
                local frame = anim.frameStart + cappy.oTimer
                if anim.frameStart <= frame and frame < anim.frameEnd then
                    mario_anim_play_custom(m, anim.animName, anim.animAccel)
                    mario_anim_clamp(m.marioObj.header.gfx.animInfo, frame, frame)
                    m.marioBodyState.torsoAngle.x = 0
                    m.marioBodyState.torsoAngle.z = 0
                    m.marioObj.header.gfx.angle.z = 0
                end
            end

            -- Update Mario's roll during a flying throw
            if cappy.oSubAction == 1 and cappy.oBehParams2ndByte == CAPPY_BHV_FLYING and (m.action & ACT_FLAG_FLYING) == ACT_FLAG_FLYING and cappy.oTimer < CAPPY_BHV_FLYING_CALL_BACK_START then
                m.marioObj.header.gfx.angle.z = s16(m.marioObj.header.gfx.angle.z + (cappy.oTimer * 0x10000) / CAPPY_BHV_FLYING_CALL_BACK_START)
            end

            -- Update Mario's cap state
            if cappy.oSubAction == 1 and cappy.oTimer >= 0 then
                m.marioBodyState.capState = MARIO_HAS_DEFAULT_CAP_OFF
            end
        end
    end
end

-------------
-- Actions --
-------------

local function mario_init_action(m, forwardVel, upwardsVel, particles, sfx, charSfx)
    mario_set_forward_vel(m, forwardVel)
    m.vel.y = upwardsVel
    m.particleFlags = m.particleFlags | particles
    if sfx ~= nil then play_sound(sfx, m.marioObj.header.gfx.cameraToObject) end
    if charSfx ~= nil then
        if charSfx == CHAR_SOUND_YAHOO_WAHA_YIPPEE then play_character_sound_offset(m, charSfx, (2 + (m.marioObj.oTimer % 3)) << 16)
        else play_character_sound(m, charSfx) end
    end
end

function mario_set_action(m, action, actionArg, buttons)

    -- Set action and remove buttons pressed
    if (action ~= 0) then set_mario_action(m, action, actionArg) end
    if (buttons & A_BUTTON) then m.input = m.input & (~(INPUT_A_PRESSED)) end
    if (buttons & B_BUTTON) then m.input = m.input & (~(INPUT_B_PRESSED)) end
    if (buttons & Z_TRIG  ) then m.input = m.input & (~(INPUT_Z_PRESSED)) end
    m.controller.buttonPressed = m.controller.buttonPressed & (~(buttons))

    -- Set Mario's facing direction
    if (m.controller.stickMag > 32 and (
        (m.action == ACT_DIVE and m.prevAction == ACT_GROUND_POUND) or
        (m.action == ACT_CAPPY_THROW_GROUND) or
        (m.action == ACT_CAPPY_THROW_AIRBORNE)))
    then
        m.faceAngle.y = m.intendedYaw
    end
end

local function mario_set_action_if(m, condition, nextAction, actionArg)
    if condition then
        mario_set_action(m, nextAction, actionArg, 0)
        return true
    end
    return false
end

local function mario_set_action_if_a_pressed(m, nextAction, actionArg)
    return mario_set_action_if(m, (m.controller.buttonPressed & A_BUTTON) ~= 0 and not is_game_paused(), nextAction, actionArg)
end

local function mario_set_action_if_b_pressed(m, nextAction, actionArg)
    return mario_set_action_if(m, (m.controller.buttonPressed & B_BUTTON) ~= 0 and not is_game_paused(), nextAction, actionArg)
end

local function mario_set_action_if_z_pressed(m, nextAction, actionArg)
    return mario_set_action_if(m, (m.controller.buttonPressed & Z_TRIG) ~= 0 and not is_game_paused(), nextAction, actionArg)
end

------------------
-- Cappy throws --
------------------

CAPPY_THROW_ANIMS = {
    [CAPPY_BHV_DEFAULT_GROUND]   = { animName = MARIO_ANIM_PAULINE_CAPPY_THROW,      animAccel = 0x18000, frameStart =  0, frameEnd = 28 },
    [CAPPY_BHV_DEFAULT_AIR]      = { animName = MARIO_ANIM_PAULINE_CAPPY_THROW,      animAccel = 0x18000, frameStart = 31, frameEnd = 71 },
    [CAPPY_BHV_UPWARDS_GROUND]   = { animName = MARIO_ANIM_PAULINE_CAPPY_UP_THROW,   animAccel = 0x14000, frameStart =  0, frameEnd = 27 },
    [CAPPY_BHV_UPWARDS_AIR]      = { animName = MARIO_ANIM_PAULINE_CAPPY_UP_THROW,   animAccel = 0x14000, frameStart = 29, frameEnd = 46 },
    [CAPPY_BHV_DOWNWARDS_GROUND] = { animName = MARIO_ANIM_PAULINE_CAPPY_DOWN_THROW, animAccel = 0x14000, frameStart =  0, frameEnd = 27 },
    [CAPPY_BHV_DOWNWARDS_AIR]    = { animName = MARIO_ANIM_PAULINE_CAPPY_DOWN_THROW, animAccel = 0x14000, frameStart = 29, frameEnd = 47 },
    [CAPPY_BHV_SPIN_GROUND]      = { animName = MARIO_ANIM_PAULINE_CAPPY_SPIN_THROW, animAccel = 0x14000, frameStart =  0, frameEnd = 37 },
    [CAPPY_BHV_SPIN_AIR]         = { animName = MARIO_ANIM_PAULINE_CAPPY_SPIN_THROW, animAccel = 0x14000, frameStart = 39, frameEnd = 76 },
    [CAPPY_BHV_FLYING]           = { animID   = MARIO_ANIM_WING_CAP_FLY,             animAccel = 0x10000, frameStart =  0, frameEnd = 99 },
}

local function play_cappy_throw_sound(m)
    local cappy = cappy_get_object(m)
    if cappy ~= nil then
        local t = m.marioObj.oTimer
        if cappy.oBehParams2ndByte >= CAPPY_BHV_SPIN_GROUND then
            play_character_sound_offset(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE, (2 + (t % 3)) << 16)
        else
            if (t % 3) == 0 then play_character_sound(m, CHAR_SOUND_PUNCH_YAH) end
            if (t % 3) == 1 then play_character_sound(m, CHAR_SOUND_PUNCH_WAH) end
            if (t % 3) == 2 then play_character_sound(m, CHAR_SOUND_PUNCH_HOO) end
        end
    end
end

local function update_cappy_throw_anim(m)
    local cappy = cappy_get_object(m)
    if cappy ~= nil then
        local anim = CAPPY_THROW_ANIMS[cappy.oBehParams2ndByte]
        if anim ~= nil then
            if anim.animName ~= nil then
                mario_anim_play_custom(m, anim.animName, anim.animAccel)
            else
                set_mario_anim_with_accel(m, anim.animID, anim.animAccel)
            end
            mario_anim_clamp(m.marioObj.header.gfx.animInfo, anim.frameStart, anim.frameEnd)
            return is_anim_past_frame(m, anim.frameEnd) == 1
        end
    end
    return true
end

----------
-- Init --
----------

local PAULINE_ACTIONS_INIT = {

    [ACT_CAPPY_THROW_GROUND] = function(m)
        mario_init_action(m, m.forwardVel, 0, 0, nil, nil)
        play_cappy_throw_sound(m)
        mario_anim_reset(m.marioObj.header.gfx.animInfo)
    end,

    [ACT_CAPPY_THROW_AIRBORNE] = function(m)
        mario_init_action(m, math.min(m.forwardVel, 8), 16, 0, nil, nil)
        play_cappy_throw_sound(m)
        mario_anim_reset(m.marioObj.header.gfx.animInfo)
    end,

    [ACT_CAPPY_THROW_WATER] = function(m)
        mario_init_action(m, m.forwardVel, m.vel.y, 0, nil, nil)
        play_cappy_throw_sound(m)
        mario_anim_reset(m.marioObj.header.gfx.animInfo)
    end,

    [ACT_CAPPY_BOUNCE] = function(m)
        mario_init_action(m, m.forwardVel * 0.8, 56, 0, nil, CHAR_SOUND_HOOHOO)
    end,

    [ACT_CAPPY_VAULT] = function(m)
        mario_init_action(m, m.forwardVel * 0.8, 68, 0, nil, CHAR_SOUND_YAHOO_WAHA_YIPPEE)
        mario_anim_reset(m.marioObj.header.gfx.animInfo)
    end,

    [ACT_CAPPY_RAINBOW_SPIN] = function(m)
        play_character_sound(m, CHAR_SOUND_PUNCH_HOO)
        m.vel.y = 30
        mario_anim_reset(m.marioObj.header.gfx.animInfo)
        m.actionTimer = 0
    end,

}

function pauline_init_action(m)
    if gNetworkPlayers[m.playerIndex].connected then
        if PAULINE_ACTIONS_INIT[m.action] ~= nil then
            PAULINE_ACTIONS_INIT[m.action](m)
        end
    end
end

------------
-- Before --
------------

local PAULINE_ACTIONS_BEFORE = {

    [ACT_JUMP_KICK] = function(m)
        local cappy = cappy_get_object(m)
        if cappy ~= nil and cappy.oSubAction == 1 then
            return ACT_CAPPY_RAINBOW_SPIN
        end
    end,

}

function pauline_before_action(m, action)
    if gNetworkPlayers[m.playerIndex].connected then
        if PAULINE_ACTIONS_BEFORE[action] ~= nil then
            return PAULINE_ACTIONS_BEFORE[action](m)
        end
    end
end

------------
-- Cancel --
------------

local PAULINE_ACTIONS_CANCEL = {

    [ACT_GROUND_POUND] = function(m)
        if mario_set_action_if_b_pressed(m, ACT_DIVE, 0) then
            mario_init_action(m, 30, 30, PARTICLE_MIST_CIRCLE, nil, nil)
            vec3s_set(m.faceAngle, 0, m.faceAngle.y, 0)
            return
        end
    end,

    [ACT_JUMP_KICK] = function(m)
        if mario_set_action_if_z_pressed(m, ACT_GROUND_POUND, 0) then return end
    end,

}

local PAULINE_ACTIONS_NO_CAPPY_THROW = {
    [ACT_FIRST_PERSON] = true,
    [ACT_JUMP_KICK] = true,
    [ACT_CAPPY_RAINBOW_SPIN] = true,
    [ACT_DIVE] = true,
    [ACT_SHOT_FROM_CANNON] = true,
    [ACT_VERTICAL_WIND] = true,
    [ACT_TWIRLING] = true,
    [ACT_AIR_HIT_WALL] = true,
    [ACT_GROUND_POUND] = true,
    [ACT_SLIDE_KICK] = true,
    [ACT_AIR_THROW] = true,
    [ACT_WATER_THROW] = true,
    [ACT_PICKING_UP] = true,
    [ACT_DIVE_PICKING_UP] = true,
    [ACT_STOMACH_SLIDE_STOP] = true,
    [ACT_PLACING_DOWN] = true,
    [ACT_THROWING] = true,
    [ACT_HEAVY_THROW] = true,
    [ACT_HOLD_PANTING_UNUSED] = true,
    [ACT_HOLD_IDLE] = true,
    [ACT_HOLD_HEAVY_IDLE] = true,
    [ACT_HOLD_JUMP_LAND_STOP] = true,
    [ACT_HOLD_FREEFALL_LAND_STOP] = true,
    [ACT_HOLD_BUTT_SLIDE_STOP] = true,
    [ACT_HOLD_WALKING] = true,
    [ACT_HOLD_HEAVY_WALKING] = true,
    [ACT_HOLD_DECELERATING] = true,
    [ACT_HOLD_BEGIN_SLIDING] = true,
    [ACT_HOLD_BUTT_SLIDE] = true,
    [ACT_HOLD_STOMACH_SLIDE] = true,
    [ACT_HOLD_JUMP_LAND] = true,
    [ACT_HOLD_FREEFALL_LAND] = true,
    [ACT_HOLD_QUICKSAND_JUMP_LAND] = true,
    [ACT_HOLD_JUMP] = true,
    [ACT_HOLD_FREEFALL] = true,
    [ACT_HOLD_BUTT_SLIDE_AIR] = true,
    [ACT_HOLD_WATER_JUMP] = true,
    [ACT_HOLD_WATER_IDLE] = true,
    [ACT_HOLD_WATER_ACTION_END] = true,
    [ACT_HOLD_BREASTSTROKE] = true,
    [ACT_HOLD_SWIMMING_END] = true,
    [ACT_HOLD_FLUTTER_KICK] = true,
    [ACT_HOLD_METAL_WATER_STANDING] = true,
    [ACT_HOLD_METAL_WATER_WALKING] = true,
    [ACT_HOLD_METAL_WATER_FALLING] = true,
    [ACT_HOLD_METAL_WATER_FALL_LAND] = true,
    [ACT_HOLD_METAL_WATER_JUMP] = true,
    [ACT_HOLD_METAL_WATER_JUMP_LAND] = true,
    [ACT_HOLDING_POLE] = true,
    [ACT_PICKING_UP_BOWSER] = true,
    [ACT_HOLDING_BOWSER] = true,
    [ACT_RELEASING_BOWSER] = true,
    [ACT_CRAZY_BOX_BOUNCE] = true,
    [ACT_WATER_SHELL_SWIMMING] = true,
}

function pauline_cancel_action(m)
    if gNetworkPlayers[m.playerIndex].connected then

        -- Action cancels
        if PAULINE_ACTIONS_CANCEL[m.action] then
            PAULINE_ACTIONS_CANCEL[m.action](m)
        end

        -- Check Cappy throw
        if (m.controller.buttonPressed & X_BUTTON) ~= 0 and not is_game_paused() then
            if m.riddenObj ~= nil and (m.action & ACT_FLAG_RIDING_SHELL) == 0 then return end
            if m.riddenObj == nil and (m.action & ACT_FLAG_RIDING_SHELL) ~= 0 then return end
            if (m.action & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE then return end
            if (m.action & ACT_GROUP_MASK) == ACT_GROUP_AUTOMATIC then return end
            if (m.action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE) ~= 0 then return end
            if (m.action & ACT_FLAG_ON_POLE) ~= 0 then return end
            if (m.action & ACT_FLAG_HANGING) ~= 0 then return end
            if (m.action & ACT_FLAG_INTANGIBLE) ~= 0 then return end
            if (m.action & ACT_FLAG_INVULNERABLE) ~= 0 then return end
            if (m.action & ACT_FLAG_METAL_WATER) ~= 0 then return end
            if PAULINE_ACTIONS_NO_CAPPY_THROW[m.action] ~= nil then return end

            -- Cappy throw
            if cappy_spawn(m) then

                -- Shell ride
                if (m.action & ACT_FLAG_RIDING_SHELL) ~= 0 then
                    play_character_sound_offset(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE, (2 + (m.marioObj.oTimer % 3)) << 16)
                    if (m.action & ACT_FLAG_AIR) ~= 0 then
                        m.action = ACT_RIDING_SHELL_FALL -- prevent ACT_FLAG_CONTROL_JUMP_HEIGHT on ACT_RIDING_SHELL_JUMP from killing the upwards velocity
                        m.vel.y = math.max(m.vel.y, 32)
                    end
                    return
                end

                -- Flying throw
                if (m.action & ACT_FLAG_FLYING) == ACT_FLAG_FLYING then
                    play_character_sound_offset(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE, (2 + (m.marioObj.oTimer % 3)) << 16)
                    return
                end

                -- Water throw
                if (m.action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED then
                    mario_set_action(m, ACT_CAPPY_THROW_WATER, 0, X_BUTTON | A_BUTTON | B_BUTTON)
                    return
                end

                -- Airborne throw
                if (m.action & ACT_FLAG_AIR) ~= 0 then
                    mario_set_action(m, ACT_CAPPY_THROW_AIRBORNE, 0, X_BUTTON | A_BUTTON | B_BUTTON)
                    return
                end

                -- Ground throw
                mario_set_action(m, ACT_CAPPY_THROW_GROUND, 0, X_BUTTON | A_BUTTON | B_BUTTON)
                return
            end
        end
    end
end

--------------------
-- Custom actions --
--------------------

hook_mario_action(ACT_CAPPY_THROW_GROUND, function(m)
    if mario_set_action_if_a_pressed(m, ACT_JUMP, 0) then return 1 end
    if mario_set_action_if_b_pressed(m, ACT_MOVE_PUNCHING, 0) then return 1 end
    if mario_set_action_if_z_pressed(m, ACT_CROUCH_SLIDE, 0) then return 1 end

    local f = (coss(math.abs(m.faceAngle.y - m.intendedYaw)) * m.controller.stickMag) / 64
    mario_set_forward_vel(m, m.forwardVel * clamp(f, 0.80, 0.98))

    local step = perform_ground_step(m)
    if mario_set_action_if(m, step == GROUND_STEP_LEFT_GROUND, ACT_FREEFALL, 0) then return 0 end
    if mario_set_action_if(m, step == GROUND_STEP_HIT_WALL, ACT_IDLE, 0) then return 0 end
    if mario_set_action_if(m, update_cappy_throw_anim(m), ACT_WALKING, 0) then return 0 end
    return 0
end)

hook_mario_action(ACT_CAPPY_THROW_AIRBORNE, {
every_frame = function(m)
    if mario_set_action_if_z_pressed(m, ACT_GROUND_POUND, 0) then return 1 end
    if check_kick_or_dive_in_air(m) == 1 then return 1 end

    local step = common_air_action_step(m, ACT_FREEFALL_LAND, m.marioObj.header.gfx.animInfo.animID, 0)
    if mario_set_action_if(m, update_cappy_throw_anim(m), ACT_FREEFALL, 0) then return 0 end
    if mario_set_action_if(m, step ~= AIR_STEP_NONE, 0, 0) then return 0 end
    return 0
end,
gravity = function(m)
    m.vel.y = clamp(m.vel.y - 2, -75, 100)
end
})

hook_mario_action(ACT_CAPPY_THROW_WATER, function(m)
    if mario_set_action_if(m, (m.flags & MARIO_METAL_CAP) ~= 0, ACT_METAL_WATER_FALLING, 0) then return 1 end
    if mario_set_action_if_a_pressed(m, ACT_BREASTSTROKE, 0) then return 1 end
    if mario_set_action_if_b_pressed(m, ACT_WATER_PUNCH, 0) then return 1 end

    if m.actionTimer == 0 then
        m.angleVel.x = m.vel.x
        m.angleVel.y = m.vel.y
        m.angleVel.z = m.vel.z
    end
    m.vel.x = m.angleVel.x * 0.9 ^ (m.actionTimer)
    m.vel.y = m.angleVel.y * 0.9 ^ (m.actionTimer)
    m.vel.z = m.angleVel.z * 0.9 ^ (m.actionTimer)
    mario_set_forward_vel(m, math.sqrt(m.vel.x ^ 2 + m.vel.z ^ 2))
    m.actionTimer = m.actionTimer + 1

    perform_water_step(m)
    if mario_set_action_if(m, update_cappy_throw_anim(m), ACT_WATER_ACTION_END, 0) then return 0 end
    return 0
end)

hook_mario_action(ACT_CAPPY_BOUNCE, function(m)
    if mario_set_action_if_z_pressed(m, ACT_GROUND_POUND, 0) then return 1 end
    if check_kick_or_dive_in_air(m) == 1 then return 1 end

    if m.vel.y < 0 then
        set_mario_animation(m, MARIO_ANIM_DOUBLE_JUMP_FALL)
        m.action = ACT_DOUBLE_JUMP
        m.prevAction = ACT_DOUBLE_JUMP
        m.actionArg = 0
        m.actionState = 1
        m.actionTimer = 1
        m.flags = m.flags | MARIO_ACTION_SOUND_PLAYED | MARIO_MARIO_SOUND_PLAYED
        return 1
    end

    m.actionTimer = m.actionTimer + 1
    local step = common_air_action_step(m, ACT_DOUBLE_JUMP_LAND, MARIO_ANIM_DOUBLE_JUMP_RISE, AIR_STEP_CHECK_LEDGE_GRAB)
    if mario_set_action_if(m, step ~= AIR_STEP_NONE, 0, 0) then return 0 end
    return 0
end)

hook_mario_action(ACT_CAPPY_VAULT, function(m)
    if mario_set_action_if_z_pressed(m, ACT_GROUND_POUND, 0) then return 1 end
    if check_kick_or_dive_in_air(m) == 1 then return 1 end

    m.actionTimer = m.actionTimer + 1
    local step = common_air_action_step(m, ACT_DOUBLE_JUMP_LAND, m.marioObj.header.gfx.animInfo.animID, AIR_STEP_CHECK_LEDGE_GRAB)
    mario_anim_play_custom(m, MARIO_ANIM_PAULINE_CAPPY_VAULT)
    if mario_set_action_if(m, step ~= AIR_STEP_NONE, 0, 0) then return 0 end
    if is_anim_past_frame(m, 6) == 1 then
        play_sound(SOUND_ACTION_SIDE_FLIP_UNK, m.marioObj.header.gfx.cameraToObject)
    end
    return 0
end)

hook_mario_action(ACT_CAPPY_RAINBOW_SPIN, function(m)
    if mario_set_action_if_z_pressed(m, ACT_GROUND_POUND, 0) then return 1 end
    m.controller.buttonPressed = m.controller.buttonPressed & (~(B_BUTTON))
    m.actionTimer = m.actionTimer + 1

    update_air_without_turn(m)
    local step = perform_air_step(m, AIR_STEP_CHECK_LEDGE_GRAB)
    if mario_set_action_if(m, step == AIR_STEP_LANDED, ACT_FREEFALL_LAND, 0) then return 0 end
    if mario_set_action_if(m, step == AIR_STEP_HIT_LAVA_WALL and lava_boost_on_wall(m), ACT_LAVA_BOOST, 1) then return 0 end
    if mario_set_action_if(m, step == AIR_STEP_GRABBED_LEDGE, ACT_LEDGE_GRAB, 0) then return 0 end

    mario_anim_play_custom(m, MARIO_ANIM_PAULINE_CAPPY_RAINBOW_SPIN)
    local frame = m.marioObj.header.gfx.animInfo.animFrameAccelAssist >> 0x10
    if frame < 20 then m.flags = m.flags | MARIO_KICKING end
    m.marioBodyState.punchState = 0
    return 0
end)
