_CObject = {
    __index = function (t,k)
        return _get_field(t['_lot'], t['_pointer'], k, t)
    end,
    __newindex = function (t,k,v)
        _set_field(t['_lot'], t['_pointer'], k, v, t)
    end,
    __eq = function (a, b)
        return a['_pointer'] == b['_pointer'] and a['_lot'] == b['_lot'] and a['_pointer'] ~= nil and a['_lot'] ~= nil
    end
}

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
    return current;
end

--- @param bank number
--- @param playFlags number
--- @param soundID number
--- @param priority number
--- @param flags2 number
--- @return number
function SOUND_ARG_LOAD(bank, playFlags, soundID, priority, flags2)
    if flags2 == nil then flags2 = 0 end
    return ((bank << 28) | (playFlags << 24) | (soundID << 16) | (priority << 8) | (flags2 << 4) | 1)
end
