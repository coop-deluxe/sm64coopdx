-- name: Football (soccer)
-- description: Play football in castle grounds.
-- incompatible: gamemode

---------------
-- constants --
---------------

ballGravity = 1.5
ballRadius = 50
ballFriction = 0.988
ballRestitution = 0.65
ballWaterDrag = 0.9
ballParallelInertia = 0.3
ballPerpendicularInertia = 1

ballActionValues = {
    [ACT_WATER_PUNCH] =       { xz = 20, y = 40, directionless = false },
    [ACT_MOVE_PUNCHING] =     { xz = 35, y =  0, directionless = false },
    [ACT_PUNCHING] =          { xz = 35, y =  0, directionless = false },
    [ACT_GROUND_POUND] =      { xz = 40, y = 40, directionless = true  },
    [ACT_GROUND_POUND_LAND] = { xz = 40, y = 40, directionless = true  },
    [ACT_JUMP_KICK] =         { xz = 10, y = 32, directionless = false },
    [ACT_SLIDE_KICK_SLIDE] =  { xz = -7, y = 25, directionless = false },
    [ACT_SLIDE_KICK] =        { xz = -7, y = 25, directionless = false },
    [ACT_LONG_JUMP] =         { xz =  0, y =  0, directionless = false },
    [ACT_CROUCH_SLIDE] =      { xz =  0, y =  0, directionless = false },
}

---------------
-- globals --
---------------

gBallTouchedLocal = false
gCachedBalls = {}

-----------
-- utils --
-----------

function clamp(x, a, b)
    if x < a then return a end
    if x > b then return b end
    return x
end

function vec3f_degrees_between(a, b)
    local ansAgain = math.acos(vec3f_dot(a, b) / (vec3f_length(a) * vec3f_length(b)))
    return math.deg(ansAgain)
end

function my_global_index()
    return gNetworkPlayers[gMarioStates[0].playerIndex].globalIndex
end

function my_location()
    local np = gNetworkPlayers[gMarioStates[0].playerIndex]
    return tostring(np.currCourseNum) .. '-' .. tostring(np.currLevelNum) .. '-' .. tostring(np.currAreaIndex) .. '-' .. tostring(np.currActNum)
end

function active_player(m)
    local np = gNetworkPlayers[m.playerIndex]
    if m.playerIndex == 0 then
        return true
    end
    if not np.connected then
        return false
    end
    return is_player_active(m)
end

function get_cached_ball(obj)
    local key = my_location() .. '-' .. tostring(obj.oSyncID)
    if gCachedBalls[key] == nil then
        local cb = {}
        cb.oGlobalOwner = obj.oGlobalOwner
        cb.oHitTime = obj.oHitTime
        cb.oNetworkTime = obj.oNetworkTime
        cb.oPosX = obj.oPosX
        cb.oPosY = obj.oPosY
        cb.oPosZ = obj.oPosZ
        cb.oVelX = obj.oVelX
        cb.oVelY = obj.oVelY
        cb.oVelZ = obj.oVelZ
        gCachedBalls[key] = cb
    end
    return gCachedBalls[key]
end

function should_reject_packet(obj)
    local cb = get_cached_ball(obj)
    if obj.oHitTime < cb.oHitTime then
        return true
    end

    if obj.oHitTime == cb.oHitTime and obj.oGlobalOwner > cb.oGlobalOwner then
        return true
    end

    if obj.oHitTime == cb.oHitTime and obj.oGlobalOwner == cb.oGlobalOwner and obj.oNetworkTime < cb.oNetworkTime then
        return true
    end

    return false
end

function find_ball()
    local obj = obj_get_first(OBJ_LIST_DEFAULT)
    while obj ~= nil do
        if get_id_from_behavior(obj.behavior) == id_bhvBall then
            return obj
        end
        obj = obj_get_next(obj)
    end
    return nil
end

function spawn_or_move_ball(x, y, z)
    -- search for ball
    local obj = find_ball()
    if obj ~= nil then
        -- move ball
        obj.oPosX = x
        obj.oPosY = y
        obj.oPosZ = z
        obj.oVelX = 0
        obj.oVelY = 0
        obj.oVelZ = 0

        obj.oGlobalOwner = my_global_index()
        obj.oHitTime = get_network_area_timer()
        obj.oNetworkTime = get_network_area_timer()
        network_send_object(obj, false)

        return obj
    end

    -- don't spawn unless server
    if my_global_index() ~= 0 then
        return nil
    end

    -- spawn ball
    return spawn_sync_object(
            id_bhvBall,
            E_MODEL_SPINY_BALL,
            x, y, z,

            function(obj)
                obj.oGlobalOwner = my_global_index()
            end)
end

--------------
-- behavior --
--------------

-- define ball's custom fields
define_custom_obj_fields({
    oNetworkTime = 'u32',
    oHitTime = 'u32',
    oGlobalOwner = 'u32',
    oFrozen = 'u32',
})

--- @param obj Object
function bhv_ball_particle_trail(obj)
    local spi = obj_get_temp_spawn_particles_info(E_MODEL_SPARKLES)
    if spi == nil then
        return nil
    end

    spi.behParam = 2
    spi.count = 1
    spi.offsetY = -1 * ballRadius
    spi.forwardVelBase = 8
    spi.forwardVelRange = 0
    spi.velYBase = 6
    spi.velYRange = 0
    spi.gravity = 0
    spi.dragStrength = 5
    spi.sizeBase = 10
    spi.sizeRange = 30

    cur_obj_spawn_particles(spi)
end

--- @param obj Object
function bhv_ball_particle_bounce(obj)
    local spi = obj_get_temp_spawn_particles_info(E_MODEL_MIST)
    if spi == nil then
        return nil
    end

    spi.behParam = 3
    spi.count = 5
    spi.offsetY = -1 * ballRadius
    spi.forwardVelBase = 6
    spi.forwardVelRange = -6
    spi.velYBase = 6
    spi.velYRange = -6
    spi.gravity = 0
    spi.dragStrength = 5
    spi.sizeBase = 8
    spi.sizeRange = 13

    cur_obj_spawn_particles(spi)
end

--- @param obj Object
function bhv_ball_init(obj)
    -- flags and such
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oGraphYOffset = 0
    cur_obj_scale(1.4)

    -- physics
    obj.oWallHitboxRadius = 40.00
    obj.oGravity          =  2.50
    obj.oBounciness       = -0.75
    obj.oDragStrength     =  0.00
    obj.oFriction         =  0.99
    obj.oBuoyancy         =  -2.00

    -- hitbox
    obj.hitboxRadius = 100
    obj.hitboxHeight = 100

    -- custom values
    obj.oNetworkTime = 0
    obj.oHitTime = 0
    obj.oFrozen = 0

    -- cache
    local cb = get_cached_ball(obj)

    network_init_object(obj, false, {
        'oPosX',
        'oPosY',
        'oPosZ',
        'oVelX',
        'oVelY',
        'oVelZ',
        'oGlobalOwner',
        'oNetworkTime',
        'oHitTime',
    })
end

--- @param obj Object
function bhv_ball_player_collision(obj)
    local alterPos = { x = 0, y = 0, z = 0}

    local m = nearest_mario_state_to_object(obj)
    if m == nil then return alterPos end
    local player = m.marioObj
    if player == nil then return alterPos end

    local playerRadius = 37
    local playerHeight = 160

    local objPoint = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ }
    local v = { x = obj.oVelX, y = obj.oVelY, z = obj.oVelZ }

    -- figure out player-to-ball radius
    local alterBallFlags = (ACT_FLAG_ATTACKING | ACT_FLAG_BUTT_OR_STOMACH_SLIDE | ACT_FLAG_DIVING)
    local playerBallRadius = ballRadius
    if ballActionValues[m.action] ~= nil or (m.action & alterBallFlags) ~= 0 then
        playerBallRadius = playerBallRadius + 50
    end

    ------------------------------------------------
    -- calculate position and determine collision --
    ------------------------------------------------

    -- calculate cylinder values
    local cylY1 = player.oPosY + playerRadius
    local cylY2 = player.oPosY + playerHeight - playerRadius
    local cylPoint = { x = player.oPosX, y = clamp(obj.oPosY, cylY1, cylY2), z = player.oPosZ }
    local cylDist = vec3f_dist(cylPoint, objPoint)

    -- check for collision
    if cylDist > (playerBallRadius + playerRadius) then
        return alterPos
    end

    gBallTouchedLocal = (m.playerIndex == 0)

    local vDifference = { x = objPoint.x - cylPoint.x, y = objPoint.y - cylPoint.y, z = objPoint.z - cylPoint.z }
    local differenceDir = { x = vDifference.x, y = vDifference.y, z = vDifference.z }
    if vec3f_length(differenceDir) ~= 0 then
        vec3f_normalize(differenceDir)
    end

    alterPos.x = (cylPoint.x + differenceDir.x * (playerBallRadius + playerRadius + 1)) - objPoint.x
    alterPos.y = (cylPoint.y + differenceDir.y * (playerBallRadius + playerRadius + 1)) - objPoint.y
    alterPos.z = (cylPoint.z + differenceDir.z * (playerBallRadius + playerRadius + 1)) - objPoint.z

    -----------------------------------------
    -- figure out player's attack velocity --
    -----------------------------------------

    local vPlayer = { x = player.oVelX, y = player.oVelY, z = player.oVelZ }
    local playerTheta = (m.faceAngle.y / 0x8000) * math.pi

    -- have attacks alter velocity further
    local alterXz = 0
    local alterY = 0
    local alterDirectionless = false

    if ballActionValues[m.action] ~= nil then
        alterXz = ballActionValues[m.action].xz
        alterY = ballActionValues[m.action].y
        alterDirectionless = ballActionValues[m.action].directionless
    elseif ((m.action & (ACT_FLAG_BUTT_OR_STOMACH_SLIDE | ACT_FLAG_DIVING)) ~= 0) or (m.action == ACT_SLIDE_KICK_SLIDE) or (m.action == ACT_SLIDE_KICK) then
        -- dive or slide sends it upward, and slows xz
        alterXz = -7
        alterY = 25
    elseif (m.action & ACT_FLAG_ATTACKING) ~= 0 then
        -- other attacks should just do something reasonable
        alterXz = 10
        alterY = 10
    end

    -- adjust angle
    local theta = playerTheta
    if alterDirectionless and differenceDir.z ~= 0 then
        theta = math.atan2(differenceDir.x, differenceDir.z)
    end

    vPlayer.x = vPlayer.x + math.sin(theta) * alterXz
    vPlayer.z = vPlayer.z + math.cos(theta) * alterXz
    if vPlayer.y < alterY then vPlayer.y = vPlayer.y + alterY end

    local vPlayerMag = vec3f_length(vPlayer)

    -------------------------------------------------
    -- figure out which velocity interaction to do --
    -------------------------------------------------

    local v = { x = obj.oVelX, y = obj.oVelY, z = obj.oVelZ }

    local doReflection = (vPlayerMag == 0)

    -- make sure ball is offset in the vPlayer direction
    if not doReflection then
        local objCylDir = { x = cylPoint.x - objPoint.x, y = cylPoint.y - objPoint.y, z = cylPoint.z - objPoint.z }
        local objCylDirXZ = { x = objCylDir.x, y = 0, z = objCylDir.z }
        local objCylDirMag = vec3f_length(objCylDir)

        local vPlayerXZ = { x = vPlayer.x, y = 0, z = vPlayer.z }
        local vPlayerXZMag = vec3f_length(vPlayerXZ)

        if objCylDirMag > 0 and vPlayerXZMag > 0 then
            doReflection = (vec3f_degrees_between(vPlayer, objCylDir)) <= 120
                       and (vec3f_degrees_between(vPlayerXZ, objCylDirXZ)) <= 120
        end
    end

    -- make sure player has a velocity
    if not doReflection and vPlayerMag == 0 then
        doReflection = true
    end

    --------------------------------------
    -- calculate velocity (interaction) --
    --------------------------------------

    if not doReflection then
        local vPlayerDir = { x = vPlayer.x, y = vPlayer.y, z = vPlayer.z }
        vec3f_normalize(vPlayerDir)

        -- split velocity into parallel/perpendicular to normal
        local perpendicular = vec3f_project(v, vPlayerDir)
        local parallel = { x = v.x - perpendicular.x, y = v.y - perpendicular.y, z = v.z - perpendicular.z }

        -- apply friction
        vec3f_mul(parallel, 0.5)

        local parallelMag = vec3f_length(parallel)
        local perpendicularMag = vec3f_length(perpendicular)

        if perpendicularMag == 0 or perpendicularMag < vPlayerMag then
            vec3f_copy(perpendicular, vPlayer)
        end

        -- reflect velocity along normal
        local reflect = {
            x = parallel.x + perpendicular.x,
            y = parallel.y + perpendicular.y,
            z = parallel.z + perpendicular.z
        }

        -- set new velocity
        obj.oVelX = reflect.x
        obj.oVelY = reflect.y
        obj.oVelZ = reflect.z
    end

    -------------------------------------
    -- calculate velocity (reflection) --
    -------------------------------------

    if doReflection then
        -- split velocity into parallel/perpendicular to normal
        local perpendicular = vec3f_project(v, differenceDir)
        local parallel = { x = v.x - perpendicular.x, y = v.y - perpendicular.y, z = v.z - perpendicular.z }

        -- apply friction and restitution
        vec3f_mul(parallel, ballFriction)
        vec3f_mul(perpendicular, ballRestitution)

        -- play sounds
        local parallelLength = vec3f_length(parallel)
        local perpendicularLength = vec3f_length(perpendicular)

        if perpendicularLength > 5 then
            cur_obj_play_sound_2(SOUND_GENERAL_BOX_LANDING_2)
        elseif parallelLength > 3 then
            cur_obj_play_sound_2(SOUND_ENV_SLIDING)
        end

        local pushOutMag = 10

        -- reflect velocity along normal
        local reflect = {
            x = parallel.x - perpendicular.x,
            y = parallel.y - perpendicular.y,
            z = parallel.z - perpendicular.z
        }

        -- set new velocity
        obj.oVelX = reflect.x + differenceDir.x * pushOutMag
        obj.oVelY = reflect.y + differenceDir.y * pushOutMag
        obj.oVelZ = reflect.z + differenceDir.z * pushOutMag
    end

    return alterPos
end

--- @param obj Object
--- @param offset Vec3f
function bhv_ball_resolve(obj, offset)
    local a   = { x = obj.oPosX + 0, y = obj.oPosY + 0, z = obj.oPosZ + 0 }
    local dir = { x = offset.x * -1.0, y = offset.y * -1.0, z = offset.z * -1.0}

    info = collision_find_surface_on_ray(
            a.x, a.y, a.z,
            dir.x, dir.y, dir.z)

    obj.oPosX = info.hitPos.x + offset.x
    obj.oPosY = info.hitPos.y + offset.y
    obj.oPosZ = info.hitPos.z + offset.z

    if info.surface == nil then return nil end
    return { x = info.surface.normal.x, y = info.surface.normal.y, z = info.surface.normal.z }
end

--- @param obj Object
function bhv_ball_loop(obj)
    if obj.oFrozen ~= 0 then
        return
    end

    gBallTouchedLocal = false
    local cb = get_cached_ball(obj)

    -- detect when a packet was received
    if obj.oNetworkTime ~= cb.oNetworkTime then
        if should_reject_packet(obj) then
            -- reject packet
            obj.oGlobalOwner = cb.oGlobalOwner
            obj.oHitTime = cb.oHitTime
            obj.oNetworkTime = cb.oNetworkTime
            obj.oPosX = cb.oPosX
            obj.oPosY = cb.oPosY
            obj.oPosZ = cb.oPosZ
            obj.oVelX = cb.oVelX
            obj.oVelY = cb.oVelY
            obj.oVelZ = cb.oVelZ
        end
    end

    local orig = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ }

    obj.oVelY = obj.oVelY - ballGravity
    if obj.oVelX == 0 and obj.oVelY == 0 and obj.oVelZ == 0 then
        obj.oVelY = obj.oVelY + 0.01
    end


    -- detect player collisions
    local alterPos = bhv_ball_player_collision(obj)

    -- alter end-point based on player collisions
    local a = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ }
    local v = { x = obj.oVelX, y = obj.oVelY, z = obj.oVelZ }
    local b = { x = v.x, y = v.y, z = v.z }
    vec3f_sum(b, b, alterPos)

    -- regular movement
    local info = collision_find_surface_on_ray(
        a.x, a.y, a.z,
        b.x, b.y, b.z)

    obj.oPosX = info.hitPos.x
    obj.oPosY = info.hitPos.y
    obj.oPosZ = info.hitPos.z

    -- detect normal along movement vector
    local vMag = vec3f_length(v)
    if vMag > 0 then
        local vNorm = { x = v.x / vMag, y = v.y / vMag, z = v.z / vMag }
        b = { x = v.x + vNorm.x * (vMag + ballRadius), y = v.y + vNorm.y * (vMag + ballRadius), z = v.z + vNorm.z * (vMag + ballRadius) }
    end

    info = collision_find_surface_on_ray(
            a.x, a.y, a.z,
            b.x, b.y, b.z)

    -- figure out the standard normal
    local colNormals = {}
    if info.surface ~= nil then
        table.insert(colNormals, { x = info.surface.normal.x, y = info.surface.normal.y, z = info.surface.normal.z })
        if vMag > 5 then
            bhv_ball_particle_bounce(obj)
        end
    else
        table.insert(colNormals, nil)
    end

    -- resolve collisions around ball
    table.insert(colNormals, bhv_ball_resolve(obj, { x =  ballRadius, y = 0, z = 0 }))
    table.insert(colNormals, bhv_ball_resolve(obj, { x = -ballRadius, y = 0, z = 0 }))
    table.insert(colNormals, bhv_ball_resolve(obj, { x = 0, y = 0, z =  ballRadius }))
    table.insert(colNormals, bhv_ball_resolve(obj, { x = 0, y = 0, z = -ballRadius }))
    table.insert(colNormals, bhv_ball_resolve(obj, { x = 0, y =  ballRadius, z = 0 }))
    table.insert(colNormals, bhv_ball_resolve(obj, { x = 0, y = -ballRadius, z = 0 }))

    -- figure out collision normal
    local collisionN = { x = 0, y = 0, z = 0 }
    local collisionCount = 0
    for _, colN in ipairs(colNormals) do
        if colN ~= nil then
            vec3f_sum(collisionN, collisionN, colN)
            collisionCount = collisionCount + 1
        end
    end

    -- reflect collisions
    if collisionCount > 0 then
        -- calculate total normal
        vec3f_mul(collisionN, 1.0 / collisionCount)
        vec3f_normalize(collisionN)

        -- split velocity into parallel/perpendicular to normal
        local perpendicular = vec3f_project(v, collisionN)
        local parallel = { x = v.x - perpendicular.x, y = v.y - perpendicular.y, z = v.z - perpendicular.z }

        -- apply friction and restitution
        vec3f_mul(parallel, ballFriction)
        vec3f_mul(perpendicular, ballRestitution)

        -- stop ball in parallel axis
        local parallelLength = vec3f_length(parallel)
        if parallelLength < ballParallelInertia then
            vec3f_mul(parallel, 0)
        end

        -- stop ball in perpendicular axis
        local perpendicularLength = vec3f_length(perpendicular)
        if perpendicularLength < ballPerpendicularInertia then
            vec3f_mul(perpendicular, 0)
        end

        -- play sounds
        if perpendicularLength > 5 then
            cur_obj_play_sound_2(SOUND_GENERAL_BOX_LANDING_2)
        elseif parallelLength > 3 then
            cur_obj_play_sound_2(SOUND_ENV_SLIDING)
        end

        -- reflect velocity along normal
        local reflect = {
            x = parallel.x - perpendicular.x,
            y = parallel.y - perpendicular.y,
            z = parallel.z - perpendicular.z
        }

        -- set new velocity
        obj.oVelX = reflect.x
        obj.oVelY = reflect.y
        obj.oVelZ = reflect.z
    end

    -- float in water
    local waterLevel = find_water_level(obj.oPosX, obj.oPosZ)
    if obj.oPosY < waterLevel then
        obj.oVelX = obj.oVelX * ballWaterDrag
        obj.oVelY = obj.oVelY * ballWaterDrag + 2
        obj.oVelZ = obj.oVelZ * ballWaterDrag
    end

    -- sanity check floor
    local floor = find_floor_height(obj.oPosX, obj.oPosY, obj.oPosZ)
    if obj.oPosY <= floor or floor <= -10000 then
        obj.oPosX = orig.x
        obj.oPosY = orig.y
        obj.oPosZ = orig.z
        obj.oVelX = -obj.oVelX
        obj.oVelY = -obj.oVelY
        obj.oVelZ = -obj.oVelZ
    end

    -- update rotation
    if obj.oVelX ~= 0 or obj.oVelZ ~= 0 then
        local moveAngle = atan2s(obj.oVelZ * 100, obj.oVelX * 100)
        local xzMag = math.sqrt(obj.oVelX * obj.oVelX + obj.oVelZ * obj.oVelZ)
        obj.oFaceAngleYaw = moveAngle
        obj.oFaceAnglePitch = obj.oFaceAnglePitch + xzMag * 100
    end

    -- send out object if we touched it
    local updateRateSend = (obj.oGlobalOwner == my_global_index() and (get_network_area_timer() - obj.oNetworkTime) > 5)
    if gBallTouchedLocal or updateRateSend then
        if gBallTouchedLocal then
            obj.oGlobalOwner = my_global_index()
            obj.oHitTime = get_network_area_timer()
        end
        obj.oNetworkTime = get_network_area_timer()
        network_send_object(obj, false)
    end

    -- spawn a particle trail
    if vMag > 50 then
        bhv_ball_particle_trail(obj)
    end

    -- hack: make sure we never set velocity to nan
    if obj.oVelX ~= obj.oVelX then obj.oVelX = 0 end
    if obj.oVelY ~= obj.oVelY then obj.oVelY = 0 end
    if obj.oVelZ ~= obj.oVelZ then obj.oVelZ = 0 end

    -- hack: save pos/vel to detect packets
    cb.oGlobalOwner = obj.oGlobalOwner
    cb.oHitTime = obj.oHitTime
    cb.oNetworkTime = obj.oNetworkTime
    cb.oPosX = obj.oPosX
    cb.oPosY = obj.oPosY
    cb.oPosZ = obj.oPosZ
    cb.oVelX = obj.oVelX
    cb.oVelY = obj.oVelY
    cb.oVelZ = obj.oVelZ
end

id_bhvBall = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_ball_init, bhv_ball_loop)

----------------------------------------------------------------------------------------------------------------

--------------
-- gamemode --
--------------

GAME_STATE_WAIT = 0
GAME_STATE_ACTIVE = 1
GAME_STATE_SCORE = 2
GAME_STATE_OOB = 3
GAME_STATE_OVER = 4

sSoccerBall = nil
sBallSpawnPos = { x = (4573 + -4634) / 2, y = -50, z = (-2077 + -212) / 2 }
sBallHidePos = { x = sBallSpawnPos.x, y = -5000, z = sBallSpawnPos.z }

sGameModeInitialized = false
sWaitTimeout = 30 * 5
sOobTimeout = 30 * 5
sScoreTimeout = 30 * 5
sOverTimeout = 30 * 15
sStateTimer = sWaitTimeout
sMaxScore = 5

gGlobalSyncTable.gameState = GAME_STATE_WAIT
gGlobalSyncTable.displayText = ' '
gGlobalSyncTable.displayFont = FONT_HUD
gGlobalSyncTable.displayColor = 0xFFFFFF
gGlobalSyncTable.scoreRed = 0
gGlobalSyncTable.scoreBlue = 0

function gamemode_initialize()
    -- hide the SM64 HUD
    hud_hide()

    sGameModeInitialized = true
end

function gamemode_shuffle()
    local t = {}
    local count = 0
    -- create table of players
    for i = 0, (MAX_PLAYERS-1) do
        local m = gMarioStates[i]
        local s = gPlayerSyncTable[i]
        if active_player(m) then
            table.insert(t, s)
            count = count + 1
        end
    end

    -- shuffle
    for i = #t, 2, -1 do
        local j = math.random(i)
        t[i], t[j] = t[j], t[i]
    end

    -- assign teams
    local team1Count = 0
    local team2Count = 0
    local oddS = nil
    for i, s in ipairs(t) do
        if (i - 1) < count / 2 then
            s.team = 1
            team1Count = team1Count + 1
            oddS = s
        else
            s.team = 2
            team2Count = team2Count + 1
        end
    end

    -- shuffle odd player
    if team1Count > team2Count then
        oddS.team = math.random(1, 2)
    end
end

function gamemode_wait()
    sSoccerBall = spawn_or_move_ball(sBallSpawnPos.x, sBallSpawnPos.y, sBallSpawnPos.z)

    -- server only
    if my_global_index() == 0 then
        -- claim the ball
        if sSoccerBall.oGlobalOwner ~= my_global_index() then
            sSoccerBall.oGlobalOwner = my_global_index()
            sSoccerBall.oHitTime = get_network_area_timer()
            sSoccerBall.oNetworkTime = get_network_area_timer()
            network_send_object(sSoccerBall, false)
        end

        -- clear sparkles
        for i=0,(MAX_PLAYERS-1) do
            local sm = gPlayerSyncTable[i]
            sm.sparkle = false
        end

        -- decrement timer
        sStateTimer = sStateTimer - 1

        -- update the visible timer
        if math.floor(sStateTimer / 30) ~= math.floor((sStateTimer + 1) / 30) then
            gGlobalSyncTable.displayFont = FONT_HUD
            gGlobalSyncTable.displayText = tostring(1 + math.floor(sStateTimer / 30))
            gGlobalSyncTable.displayColor = 0xFFFFFF
        end

        -- start the round
        if sStateTimer <= 0 then
            gGlobalSyncTable.gameState = GAME_STATE_ACTIVE
            gGlobalSyncTable.displayFont = FONT_HUD
            gGlobalSyncTable.displayText = ' '
            gGlobalSyncTable.displayColor = 0xFFFFFF
        end
    end
end

function gamemode_active()
    -- server only
    if my_global_index() == 0 then
        local validGoalY = ((sSoccerBall.oPosY + ballRadius) < -550)
        local validGoalZ = (sSoccerBall.oPosX < sBallSpawnPos.x and sSoccerBall.oPosZ < -2846) or (sSoccerBall.oPosX > sBallSpawnPos.x and sSoccerBall.oPosZ > -1205)
        if validGoalY and validGoalZ then
            if sSoccerBall.oPosX < sBallSpawnPos.x and sSoccerBall.oPosZ < -2846 then
            end

            spawn_sync_object(id_bhvExplosion, E_MODEL_EXPLOSION, sSoccerBall.oPosX, sSoccerBall.oPosY, sSoccerBall.oPosZ, nil)

            local scoringTeam = 0
            if sSoccerBall.oPosX < sBallSpawnPos.x then
                scoringTeam = 1
            else
                scoringTeam = 2
            end

            local gameOver = false
            local displayName = ''
            local scorerNp = network_player_from_global_index(sSoccerBall.oGlobalOwner)
            if scorerNp ~= nil then
                local scorerS = gPlayerSyncTable[scorerNp.localIndex]
                if scorerS.team == scoringTeam then
                    displayName = ' (' .. scorerNp.name .. ')'
                end
            end

            if scoringTeam == 1 then
                gGlobalSyncTable.scoreRed = gGlobalSyncTable.scoreRed + 1
                gGlobalSyncTable.displayFont = FONT_NORMAL
                gGlobalSyncTable.displayColor = 0xFF9999
                if gGlobalSyncTable.scoreRed >= sMaxScore then
                    gGlobalSyncTable.displayText = 'red team wins!'
                    gameOver = true
                else
                    gGlobalSyncTable.displayText = 'red team scored' .. displayName
                end
            else
                gGlobalSyncTable.scoreBlue = gGlobalSyncTable.scoreBlue + 1
                gGlobalSyncTable.displayFont = FONT_NORMAL
                gGlobalSyncTable.displayColor = 0x9999FF
                if gGlobalSyncTable.scoreBlue >= sMaxScore then
                    gGlobalSyncTable.displayText = 'blue team wins!'
                    gameOver = true
                else
                gGlobalSyncTable.displayText = 'blue team scored' .. displayName
                end
            end

            if gameOver then
                -- set sparkle
                for i=0,(MAX_PLAYERS-1) do
                    local im = gMarioStates[i]
                    local sm = gPlayerSyncTable[i]
                    if active_player(im) then
                        if sm.team == scoringTeam then
                            sm.sparkle = true
                        end
                    end
                end

                gGlobalSyncTable.gameState = GAME_STATE_OVER
                sStateTimer = sOverTimeout
            else
                -- set sparkle
                local scorerS = gPlayerSyncTable[scorerNp.localIndex]
                if scorerNp ~= nil and scorerS.team == scoringTeam then
                    scorerS.sparkle = true
                end
                gGlobalSyncTable.gameState = GAME_STATE_SCORE
                sStateTimer = sScoreTimeout
            end
        end

        -- check for oob
        local ignoreOob = (sSoccerBall.oPosX >= 3230 and sSoccerBall.oPosX <= 4460 and sSoccerBall.oPosZ >= -6230 and sSoccerBall.oPosZ <= -2725) -- ramp near bridge
        if not ignoreOob and sSoccerBall.oPosY > 0 then
            local floorHeight = find_floor_height(sSoccerBall.oPosX, sSoccerBall.oPosY, sSoccerBall.oPosZ)
            if sSoccerBall.oPosY - ballRadius - 10 < floorHeight then
                gGlobalSyncTable.gameState = GAME_STATE_OOB
                sStateTimer = sOobTimeout
            end
        end

        -- check for other OOB
        if validGoalY and not validGoalZ then
            gGlobalSyncTable.gameState = GAME_STATE_OOB
            sStateTimer = sOobTimeout
        end
    end
end

function gamemode_score()
    sSoccerBall = spawn_or_move_ball(sBallHidePos.x, sBallHidePos.y, sBallHidePos.z)

    -- server only
    if my_global_index() == 0 then
        -- decrement timer
        sStateTimer = sStateTimer - 1

        -- start the round
        if sStateTimer <= 0 then
            gGlobalSyncTable.gameState = GAME_STATE_WAIT
            sStateTimer = sWaitTimeout
        end
    end
end

function gamemode_oob()
    sSoccerBall = spawn_or_move_ball(sBallHidePos.x, sBallHidePos.y, sBallHidePos.z)

    -- server only
    if my_global_index() == 0 then
        -- decrement timer
        sStateTimer = sStateTimer - 1

        gGlobalSyncTable.displayFont = FONT_NORMAL
        gGlobalSyncTable.displayText = 'out of bounds'
        gGlobalSyncTable.displayColor = 0xFFFFFF

        -- start the round
        if sStateTimer <= 0 then
            gGlobalSyncTable.gameState = GAME_STATE_WAIT
            sStateTimer = sWaitTimeout
        end
    end
end

function gamemode_over()
    sSoccerBall = spawn_or_move_ball(sBallHidePos.x, sBallHidePos.y, sBallHidePos.z)

    -- server only
    if my_global_index() == 0 then
        -- decrement timer
        sStateTimer = sStateTimer - 1

        -- start the round
        if sStateTimer <= 0 then
            -- shuffle teams
            gamemode_shuffle()
            gGlobalSyncTable.scoreRed = 0
            gGlobalSyncTable.scoreBlue = 0
            gGlobalSyncTable.gameState = GAME_STATE_WAIT
            sStateTimer = sWaitTimeout
        end
    end
end

function gamemode_update()
    if not sGameModeInitialized then
        gamemode_initialize()
    end

    if sSoccerBall == nil then
        sSoccerBall = find_ball()
    else
        if gGlobalSyncTable.gameState == GAME_STATE_WAIT then
            sSoccerBall.oFrozen = 1
        else
            sSoccerBall.oFrozen = 0
        end
    end

    if gGlobalSyncTable.gameState == GAME_STATE_WAIT then
        gamemode_wait()
    elseif gGlobalSyncTable.gameState == GAME_STATE_ACTIVE then
        gamemode_active()
    elseif gGlobalSyncTable.gameState == GAME_STATE_SCORE then
        gamemode_score()
    elseif gGlobalSyncTable.gameState == GAME_STATE_OOB then
        gamemode_oob()
    elseif gGlobalSyncTable.gameState == GAME_STATE_OVER then
        gamemode_over()
    end
end

--- @param m MarioState
function on_player_connected(m)
    -- only run on server
    if not network_is_server() then
        return
    end

    -- figure out team
    local selectTeam = math.random(1, 2)
    local playersTeam1 = 0
    local playersTeam2 = 0
    for i=0,(MAX_PLAYERS-1) do
        local im = gMarioStates[i]
        local sm = gPlayerSyncTable[i]
        if active_player(im) and i ~= m.playerIndex then
            if sm.team == 1 then
                playersTeam1 = playersTeam1 + 1
            elseif sm.team == 2 then
                playersTeam2 = playersTeam2 + 1
            end
        end
    end
    if playersTeam1 < playersTeam2 then
        selectTeam = 1
    elseif playersTeam2 < playersTeam1 then
        selectTeam = 2
    end

    -- set team
    local s = gPlayerSyncTable[m.playerIndex]
    local np = gNetworkPlayers[m.playerIndex]
    s.team = selectTeam
end

--- @param m1 MarioState
--- @param m2 MarioState
function allow_pvp_attack(m1, m2)
    local s1 = gPlayerSyncTable[m1.playerIndex]
    local s2 = gPlayerSyncTable[m2.playerIndex]
    if s1.team == s2.team then
        return false
    end
    return true
end

function hud_score_render()
    djui_hud_set_font(FONT_HUD)

    -- get width of screen and text
    local screenWidth = djui_hud_get_screen_width()

    local width = 32
    local height = 16
    local x = (screenWidth - width) / 2.0
    local y = 5
    local xOffset = 20
    local textOffset = 8

    if gPlayerSyncTable[0].team == 2 then
        xOffset = xOffset * -1
    end

    -- render
    djui_hud_set_color(255, 100, 100, 180);
    djui_hud_render_rect(x - xOffset, y, width, height + 4);

    djui_hud_set_color(100, 100, 255, 180);
    djui_hud_render_rect(x + xOffset, y, width, height + 4);

    djui_hud_set_color(255, 255, 255, 255);
    djui_hud_print_text(tostring(gGlobalSyncTable.scoreRed), x - xOffset + textOffset, y + 2, 1);
    djui_hud_print_text(tostring(gGlobalSyncTable.scoreBlue), x + xOffset + textOffset, y + 2, 1);
end

function on_hud_render()
    -- render to N64 screen space, with the HUD font
    djui_hud_set_resolution(RESOLUTION_N64)

    hud_score_render()

    if gGlobalSyncTable.displayText == ' ' then
        return
    end
    djui_hud_set_font(gGlobalSyncTable.displayFont)

    -- set text
    local text = gGlobalSyncTable.displayText

    -- set scale
    local scale = 1

    local height = 1
    if gGlobalSyncTable.displayFont == FONT_HUD then
        height = 16 * scale
    elseif gGlobalSyncTable.displayFont == FONT_NORMAL then
        scale = 0.5
        height = 32 * scale
    end

    -- get width of screen and text
    local screenWidth = djui_hud_get_screen_width()
    local screenHeight = djui_hud_get_screen_height()
    local width = djui_hud_measure_text(text) * scale

    local x = (screenWidth - width) / 2.0
    local y = (screenHeight * 0.6 - height) / 2.0

    -- render
    djui_hud_set_color(0, 0, 0, 128);
    djui_hud_render_rect(x - 6 * scale, y - 6 * scale, width + 12 * scale, height + 12 * scale);

    local r = (gGlobalSyncTable.displayColor & 0xFF0000) >> (8 * 2)
    local g = (gGlobalSyncTable.displayColor & 0x00FF00) >> (8 * 1)
    local b = (gGlobalSyncTable.displayColor & 0x0000FF) >> (8 * 0)
    djui_hud_set_color(r, g, b, 255);
    djui_hud_print_text(text, x, y, scale);

end

function on_football_reset_command(msg)
    if msg == 'ball' then
        djui_chat_message_create('Resetting the ball.')
        sSoccerBall = spawn_or_move_ball(sBallSpawnPos.x, sBallSpawnPos.y, sBallSpawnPos.z)
        return true
    elseif msg == 'game' then
        djui_chat_message_create('Resetting the game.')
        gamemode_shuffle()
        gGlobalSyncTable.scoreRed = 0
        gGlobalSyncTable.scoreBlue = 0
        gGlobalSyncTable.displayText = ' '
        gGlobalSyncTable.gameState = GAME_STATE_WAIT
        sStateTimer = sWaitTimeout
        return true
    end
    return false
end

------------------
-- update stuff --
------------------

--- @param m MarioState
function mario_update_local(m)
    local np = gNetworkPlayers[m.playerIndex]
    local s = gPlayerSyncTable[m.playerIndex]

    if (m.controller.buttonPressed & D_JPAD) ~= 0 then
        --print(m.pos.x, m.pos.y, m.pos.z)
        --sSoccerBall = spawn_or_move_ball(m.pos.x, m.pos.y, m.pos.z)
    end

    -- force players into certain positions and angles
    if gGlobalSyncTable.gameState == GAME_STATE_WAIT then
        -- figure out team index
        local teamIndex = 0
        for i=1,(MAX_PLAYERS-1) do
            local mi = gMarioStates[i]
            local ni = gNetworkPlayers[i]
            local si = gPlayerSyncTable[i]
            if active_player(mi) and si.team == s.team then
                if ni.globalIndex < np.globalIndex then
                    teamIndex = teamIndex + 1
                end
            end
        end

        -- center camera
        m.controller.buttonDown = m.controller.buttonDown | L_TRIG

        -- figure out spawn position
        local teamTheta = (3.14 / -2)
        local teamDistance = 1550
        if (teamIndex % 2) == 0 then
            teamTheta = teamTheta - (teamIndex % 4) * 0.1
            teamDistance = teamDistance + math.floor(teamIndex / 4) * 500
        else
            teamTheta = teamTheta + (teamIndex % 4) * 0.1
            teamDistance = teamDistance + math.floor(teamIndex / 4) * 500
        end

        -- set spawn position
        local playerPos = { x = sBallSpawnPos.x, y = -511, z = sBallSpawnPos.z }
        if s.team == 1 then
            playerPos.x = playerPos.x - math.sin(teamTheta) * teamDistance
            playerPos.z = playerPos.z - math.cos(teamTheta) * teamDistance
            m.faceAngle.y = -0x4000
        elseif s.team == 2 then
            playerPos.x = playerPos.x + math.sin(teamTheta) * teamDistance
            playerPos.z = playerPos.z + math.cos(teamTheta) * teamDistance
            m.faceAngle.y = 0x4000
        end
        m.faceAngle.x = 0
        m.faceAngle.z = 0
        m.pos.x = playerPos.x
        m.pos.y = playerPos.y
        m.pos.z = playerPos.z
        m.vel.x = 0
        m.vel.y = 0
        m.vel.z = 0
        m.forwardVel = 0
        m.slideVelX = 0
        m.slideVelZ = 0
        set_mario_action(m, ACT_READING_AUTOMATIC_DIALOG, 0)

        -- fix vanilla camera
        if m.area.camera.mode == CAMERA_MODE_WATER_SURFACE then
            set_camera_mode(m.area.camera, CAMERA_MODE_FREE_ROAM, 1)
        end
    elseif m.action == ACT_READING_AUTOMATIC_DIALOG then
        set_mario_action(m, ACT_IDLE, 0)
    end
end

--- @param m MarioState
function mario_update(m)
    if m.playerIndex == 0 then
        mario_update_local(m)
    end

    -- update pos/angle
    if m.action == ACT_READING_AUTOMATIC_DIALOG then
        vec3f_copy(m.marioObj.header.gfx.pos, m.pos)
        vec3s_set(m.marioObj.header.gfx.angle, -m.faceAngle.x, m.faceAngle.y, m.faceAngle.z)
    end

    -- set metal state and health
    local s = gPlayerSyncTable[m.playerIndex]
    local np = gNetworkPlayers[m.playerIndex]
    if s.team == 2 then
        np.overridePaletteIndex = 7
        m.marioBodyState.modelState = 0
    elseif s.team == 1 then
        np.overridePaletteIndex = 15
        m.marioBodyState.modelState = 0
    else
        np.overridePaletteIndex = np.paletteIndex
        m.marioBodyState.modelState = MODEL_STATE_NOISE_ALPHA
    end
    m.health = 0x880

    -- update description
    if s.team == 1 then
        network_player_set_description(np, "red", 255, 64, 64, 255)
    elseif s.team == 2 then
        network_player_set_description(np, "blue", 64, 64, 255, 255)
    else
        network_player_set_description(np, "unknown", 64, 64, 64, 255)
    end

    if gPlayerSyncTable[m.playerIndex].sparkle then
        m.particleFlags = m.particleFlags | PARTICLE_SPARKLES
    else
        m.particleFlags = (m.particleFlags & (~PARTICLE_SPARKLES))
    end
end

function update()
    local m = gMarioStates[0]
    local np = gNetworkPlayers[m.playerIndex]

    if np.currAreaSyncValid then
        gamemode_update()
    end
end

function on_level_init()
    -- lower water level on castle grounds
    if gNetworkPlayers[0].currLevelNum == LEVEL_CASTLE_GROUNDS then
        set_environment_region(1, -800)
        set_environment_region(2, -800)
    end
end

function on_sync_valid()
    -- prevent warp doors from working
    local wasRefreshed = false
    local obj = obj_get_first(OBJ_LIST_SURFACE)
    while obj ~= nil do
        local behaviorId = get_id_from_behavior(obj.behavior)
        if behaviorId == id_bhvDoorWarp then
            obj.oInteractType = 0
        end

        -- hide exclamation box
        if behaviorId == id_bhvExclamationBox then
            obj.oPosX = sBallHidePos.x
            obj.oPosY = sBallHidePos.y
            obj.oPosZ = sBallHidePos.z
        end

        if behaviorId == id_bhvLllHexagonalMesh then
            wasRefreshed = true
        end
        obj = obj_get_next(obj)
    end

    -- server spawns objects
    if my_global_index() == 0 and not wasRefreshed then
        -- block vanish cap
        spawn_sync_object(
            id_bhvLllHexagonalMesh,
            E_MODEL_TRAMPOLINE,
            -3390, -512, -2023,
            function (obj)
                obj.oOpacity = 255
                obj.header.gfx.scale.x = 3
                obj.header.gfx.scale.z = 3;
            end)

        -- block basement door
        spawn_sync_object(
            id_bhvLllHexagonalMesh,
            E_MODEL_TRAMPOLINE,
            3279 + 45, -511, -2937 + 45,
            function (obj)
                obj.oOpacity = 255
                obj.header.gfx.scale.x = 2
                obj.header.gfx.scale.z = 2
                obj.oFaceAngleYaw = 0x6000
                obj.oFaceAngleRoll = 0x4000
            end)

        -- block area near ramp
        spawn_sync_object(
            id_bhvStaticCheckeredPlatform,
            E_MODEL_CHECKERBOARD_PLATFORM,
            4430 - 65, 545 + 250 - 5, -6000 - 65,
            function (obj)
                obj.oOpacity = 255
                obj.oFaceAngleYaw = 0x2000
                obj.oFaceAngleRoll = 0x4000
            end)

        -- block area near ramp
        for i=0,6 do
            spawn_sync_object(
                id_bhvStaticCheckeredPlatform,
                E_MODEL_CHECKERBOARD_PLATFORM,
                4460, 545 + 250, -6000 + i * 305,
                function (obj)
                    obj.oOpacity = 255
                    obj.oFaceAngleYaw = 0
                    obj.oFaceAngleRoll = 0x4000
                end)
        end

        -- block cannon
        spawn_sync_object(
            id_bhvLllHexagonalMesh,
            E_MODEL_TRAMPOLINE,
            2385, 88, 1956,
            function (obj)
                obj.oOpacity = 255
                obj.header.gfx.scale.x = 0.9
                obj.header.gfx.scale.z = 0.9
            end)
    end
end

-----------
-- hooks --
-----------

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_UPDATE, update)
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
hook_event(HOOK_ON_PLAYER_CONNECTED, on_player_connected)
hook_event(HOOK_ALLOW_PVP_ATTACK, allow_pvp_attack)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_ON_SYNC_VALID, on_sync_valid)
if network_is_server() then
    hook_chat_command('football-reset', "[game|ball] resets the game or ball", on_football_reset_command)
 end

for i=0,(MAX_PLAYERS-1) do
    local s = gPlayerSyncTable[i]
    s.team = 0
    s.sparkle = false
end
