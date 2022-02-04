_CObject = {
    __index = function (t,k)
        return _get_field(t['_lot'], t['_pointer'], k)
    end,
    __newindex = function (t,k,v)
        _set_field(t['_lot'], t['_pointer'], k, v)
    end,
    __eq = function (a, b)
        return a['_pointer'] == b['_pointer'] and a['_lot'] == b['_lot'] and a['_pointer'] ~= nil and a['_lot'] ~= nil
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

function vec3f_copy(dest, src)
    dest.x = src.x
    dest.y = src.y
    dest.z = src.z
    return dest
end

function vec3f_set(dest, x, y, z)
    dest.x = x
    dest.y = y
    dest.z = z
    return dest
end

function vec3f_add(dest, a)
    dest.x = dest.x + a.x
    dest.y = dest.y + a.y
    dest.z = dest.z + a.z
    return dest
end

function vec3f_sum(dest, a, b)
    dest.x = a.x + b.x
    dest.y = a.y + b.y
    dest.z = a.z + b.z
    return dest
end

function vec3f_mul(dest, a)
    dest.x = dest.x * a
    dest.y = dest.y * a
    dest.z = dest.z * a
    return dest
end

function vec3f_dist(v1, v2)
    dx = v1.x - v2.x
    dy = v1.y - v2.y
    dz = v1.z - v2.z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
end

function vec3s_copy(dest, src)
    dest.x = src.x
    dest.y = src.y
    dest.z = src.z
    return dest
end

function vec3s_set(dest, x, y, z)
    dest.x = x
    dest.y = y
    dest.z = z
    return dest
end

function vec3s_add(dest, a)
    dest.x = dest.x + a.x
    dest.y = dest.y + a.y
    dest.z = dest.z + a.z
    return dest
end

function vec3s_sum(dest, a, b)
    dest.x = a.x + b.x
    dest.y = a.y + b.y
    dest.z = a.z + b.z
    return dest
end

function vec3s_mul(dest, a)
    dest.x = dest.x * a
    dest.y = dest.y * a
    dest.z = dest.z * a
    return dest
end

function vec3s_dist(v1, v2)
    dx = v1.x - v2.x
    dy = v1.y - v2.y
    dz = v1.z - v2.z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
end

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

function SOUND_ARG_LOAD(bank, playFlags, soundID, priority, flags2)
    return ((bank << 28) | (playFlags << 24) | (soundID << 16) | (priority << 8) | (flags2 << 4) | 1)
end
