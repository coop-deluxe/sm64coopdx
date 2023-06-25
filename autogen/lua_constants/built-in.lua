math.randomseed(get_time())

_CObjectPool = {}

_CObject = {
    __index = function (t,k)
        return _get_field(t['_lot'], t['_pointer'], k, t)
    end,
    __newindex = function (t,k,v)
        _set_field(t['_lot'], t['_pointer'], k, v, t)
    end,
    __tostring = function(t)
        return 'CObject: ' .. t['_lot'] .. ', [' .. string.format('0x%08X', t['_pointer']) .. ']'
    end,
    __eq = function (a, b)
        return a['_pointer'] == b['_pointer'] and a['_lot'] == b['_lot'] and a['_pointer'] ~= nil and a['_lot'] ~= nil
    end
}

function _NewCObject(lot, pointer)
    if _CObjectPool[lot] == nil then
        _CObjectPool[lot] = {}
    end

    if _CObjectPool[lot][pointer] == nil then
        local obj = {}
        rawset(obj, '_pointer', pointer)
        rawset(obj, '_lot', lot)
        setmetatable(obj, _CObject)
        _CObjectPool[lot][pointer] = obj
        return obj
    end

    return _CObjectPool[lot][pointer]
end

local _CPointerPool = {}

_CPointer = {
    __index = function (t,k)
        return nil
    end,
    __newindex = function (t,k,v)
    end,
    __tostring = function(t)
        return 'CPointer: ' .. t['_lvt'] .. ', [' .. string.format('0x%08X', t['_pointer']) .. ']'
    end,
    __eq = function (a, b)
        return a['_pointer'] == b['_pointer'] and a['_pointer'] ~= nil and a['_lvt'] ~= nil
    end
}

function _NewCPointer(lvt, pointer)
    if _CPointerPool[lvt] == nil then
        _CPointerPool[lvt] = {}
    end

    if _CPointerPool[lvt][pointer] == nil then
        local obj = {}
        rawset(obj, '_pointer', pointer)
        rawset(obj, '_lvt', lvt)
        setmetatable(obj, _CPointer)
        _CPointerPool[lvt][pointer] = obj
        return obj
    end

    return _CPointerPool[lvt][pointer]
end

_SyncTable = {
    __index = function (t,k)
        local _table = rawget(t, '_table')
        return _table[k]
    end,
    __newindex = function (t,k,v)
        local _table = rawget(t, '_table')
        if _table[k] == v then return end
        _set_sync_table_field(t, k, v)
    end
}

_ReadOnlyTable = {
    __index = function (t,k)
        local _table = rawget(t, '_table')
        return _table[k]
    end,
    __newindex = function (t,k,v)
    end
}

--- @param dest Vec3f
--- @param src Vec3f
--- @return Vec3f
function vec3f_copy(dest, src)
    dest.x = src.x
    dest.y = src.y
    dest.z = src.z
    return dest
end

--- @param dest Vec3f
--- @param x number
--- @param y number
--- @param z number
--- @return Vec3f
function vec3f_set(dest, x, y, z)
    dest.x = x
    dest.y = y
    dest.z = z
    return dest
end

--- @param dest Vec3f
--- @param a Vec3f
--- @return Vec3f
function vec3f_add(dest, a)
    dest.x = dest.x + a.x
    dest.y = dest.y + a.y
    dest.z = dest.z + a.z
    return dest
end

--- @param dest Vec3f
--- @param a Vec3f
--- @param b Vec3f
--- @return Vec3f
function vec3f_sum(dest, a, b)
    dest.x = a.x + b.x
    dest.y = a.y + b.y
    dest.z = a.z + b.z
    return dest
end

--- @param dest Vec3f
--- @param a number
--- @return Vec3f
function vec3f_mul(dest, a)
    dest.x = dest.x * a
    dest.y = dest.y * a
    dest.z = dest.z * a
    return dest
end

--- @param dest Vec3f
--- @return Vec3f
function vec3f_normalize(dest)
    local divisor = math.sqrt(dest.x * dest.x + dest.y * dest.y + dest.z * dest.z)
    if divisor == 0 then
        return dest
    end

    local invsqrt = 1.0 / divisor
    dest.x = dest.x * invsqrt
    dest.y = dest.y * invsqrt
    dest.z = dest.z * invsqrt

    return dest
end

--- @param a Vec3f
--- @return number
function vec3f_length(a)
    return math.sqrt(a.x * a.x + a.y * a.y + a.z * a.z)
end

--- @param a Vec3f
--- @param b Vec3f
--- @return number
function vec3f_dot(a, b)
    return a.x * b.x + a.y * b.y + a.z * b.z
end

--- @param vec Vec3f
--- @param onto Vec3f
--- @return Vec3f
function vec3f_project(vec, onto)
  local numerator = vec3f_dot(vec, onto)
  local denominator = vec3f_dot(onto, onto)
  local out = {}
  vec3f_copy(out, onto)
  vec3f_mul(out, numerator / denominator)
  return out
end

--- @param v1 Vec3f
--- @param v2 Vec3f
--- @return number
function vec3f_dist(v1, v2)
    dx = v1.x - v2.x
    dy = v1.y - v2.y
    dz = v1.z - v2.z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
end

--- @param dest Vec3s
--- @param src Vec3s
--- @return Vec3s
function vec3s_copy(dest, src)
    dest.x = src.x
    dest.y = src.y
    dest.z = src.z
    return dest
end

--- @param dest Vec3s
--- @param x number
--- @param y number
--- @param z number
--- @return Vec3s
function vec3s_set(dest, x, y, z)
    dest.x = x
    dest.y = y
    dest.z = z
    return dest
end

--- @param dest Vec3s
--- @param a Vec3s
--- @return Vec3s
function vec3s_add(dest, a)
    dest.x = dest.x + a.x
    dest.y = dest.y + a.y
    dest.z = dest.z + a.z
    return dest
end

--- @param dest Vec3s
--- @param a Vec3s
--- @param b Vec3s
--- @return Vec3s
function vec3s_sum(dest, a, b)
    dest.x = a.x + b.x
    dest.y = a.y + b.y
    dest.z = a.z + b.z
    return dest
end

--- @param dest Vec3s
--- @param a number
--- @return Vec3s
function vec3s_mul(dest, a)
    dest.x = dest.x * a
    dest.y = dest.y * a
    dest.z = dest.z * a
    return dest
end

--- @param v1 Vec3s
--- @param v2 Vec3s
--- @return number
function vec3s_dist(v1, v2)
    dx = v1.x - v2.x
    dy = v1.y - v2.y
    dz = v1.z - v2.z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
end

--- @param current number
--- @param target number
--- @param inc number
--- @param dec number
--- @return number
function approach_f32(current, target, inc, dec)
    if current < target then
        current = current + inc
        if current > target then
            current = target
        end
    else
        current = current - dec
        if current < target then
            current = target
        end
    end
    return current;
end

--- @param current number
--- @param target number
--- @param inc number
--- @param dec number
--- @return number
function approach_s32(current, target, inc, dec)
    if current < target then
        current = current + inc
        if current > target then
            current = target
        end
    else
        current = current - dec
        if current < target then
            current = target
        end
    end

    -- keep within 32 bits
    if current > 2147483647 then
        current = -2147483648 + (current - 2147483647)
    elseif current < -2147483648 then
        current = 2147483647 + (current - (-2147483648))
    end
    return current;
end

--- @param bank number
--- @param soundID number
--- @param priority number
--- @param flags number
--- @return number
function SOUND_ARG_LOAD(bank, soundID, priority, flags)
    if flags == nil then flags = 0 end
    return (bank << 28) | (soundID << 16) | (priority << 8) | flags | SOUND_STATUS_WAITING
end

-------------
-- courses --
-------------

--- @type integer
COURSE_NONE     = 0
--- @type integer
COURSE_BOB      = 1
--- @type integer
COURSE_WF       = 2
--- @type integer
COURSE_JRB      = 3
--- @type integer
COURSE_CCM      = 4
--- @type integer
COURSE_BBH      = 5
--- @type integer
COURSE_HMC      = 6
--- @type integer
COURSE_LLL      = 7
--- @type integer
COURSE_SSL      = 8
--- @type integer
COURSE_DDD      = 9
--- @type integer
COURSE_SL       = 10
--- @type integer
COURSE_WDW      = 11
--- @type integer
COURSE_TTM      = 12
--- @type integer
COURSE_THI      = 13
--- @type integer
COURSE_TTC      = 14
--- @type integer
COURSE_RR       = 15
--- @type integer
COURSE_BITDW    = 16
--- @type integer
COURSE_BITFS    = 17
--- @type integer
COURSE_BITS     = 18
--- @type integer
COURSE_PSS      = 19
--- @type integer
COURSE_COTMC    = 20
--- @type integer
COURSE_TOTWC    = 21
--- @type integer
COURSE_VCUTM    = 22
--- @type integer
COURSE_WMOTR    = 23
--- @type integer
COURSE_SA       = 24
--- @type integer
COURSE_CAKE_END = 25
--- @type integer
COURSE_END = 26
--- @type integer
COURSE_MAX = 25
--- @type integer
COURSE_COUNT = 25
--- @type integer
COURSE_MIN = 1