function clamp(v, min, max)
    if v < min then return min end
    if v > max then return max end
    return v
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

function vec3f_tween(a, b, mult)
    if mult < 0 then mult = 0 end
    if mult > 1 then mult = 1 end
    local amult = 1 - mult
    return {
        x = a.x * amult + b.x * mult,
        y = a.y * amult + b.y * mult,
        z = a.z * amult + b.z * mult,
    }
end

function obj_set_vec3f(obj, v)
    if obj == nil or v == nil then return end
    obj.oPosX = v.x
    obj.oPosY = v.y
    obj.oPosZ = v.z
end

function get_last_waypoint_index()
    local index = 1
    while gLevelData.waypoints[index + 1] ~= nil do
        index = index + 1
    end
    return index
end

function get_waypoint(i)
    return gLevelData.waypoints[get_waypoint_index(i)]
end

function get_waypoint_index(i)
    local lastIndex = get_last_waypoint_index()
    i = ((i - 1) % lastIndex) + 1

    if gLevelData.waypoints[i] == nil then
        return 1
    end

    return i
end

function vec3f_non_nan(v)
    if v.x ~= v.x then v.x = 0 end
    if v.y ~= v.y then v.y = 0 end
    if v.z ~= v.z then v.z = 0 end
end

function vec3f_angle_between(a, b)
    return math.acos(vec3f_dot(a, b) / (vec3f_length(a) * vec3f_length(b)))
end

function is_riding(m)
    return (m.action == ACT_RIDING_SHELL_GROUND) or (m.action == ACT_RIDING_SHELL_FALL) or (m.action == ACT_RIDING_SHELL_JUMP)
end

function is_in_local_area(m)
    local np1 = gNetworkPlayers[0]
    local np2 = gNetworkPlayers[m.playerIndex]
    return (np1.currCourseNum == np2.currCourseNum) and (np1.currLevelNum == np2.currLevelNum) and (np1.currAreaIndex == np2.currAreaIndex) and (np1.currActNum == np2.currActNum)
end

function spawn_mist(obj)
    local spi = obj_get_temp_spawn_particles_info(E_MODEL_MIST)
    if spi == nil then
        return nil
    end

    spi.behParam = 3
    spi.count = 5
    spi.offsetY = 25
    spi.forwardVelBase = 6
    spi.forwardVelRange = -6
    spi.velYBase = 6
    spi.velYRange = -6
    spi.gravity = 0
    spi.dragStrength = 5
    spi.sizeBase = 10
    spi.sizeRange = 16

    cur_obj_spawn_particles(spi)
end

function spawn_triangles(obj)
    spawn_non_sync_object(id_bhvTriangleParticleSpawner, E_MODEL_NONE,
        obj.oPosX,
        obj.oPosY,
        obj.oPosZ,
        nil)
end

function spawn_sparkles(obj)
    for i = 0, 5 do
        spawn_non_sync_object(id_bhvSparkleSpawn, E_MODEL_NONE,
            obj.oPosX + math.random(-100, 100),
            obj.oPosY + math.random(-100, 100),
            obj.oPosZ + math.random(-100, 100),
            nil)
    end
end