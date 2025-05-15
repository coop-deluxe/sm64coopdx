--- @type integer
ANIM_FLAG_FORWARD = (1 << 1)

--------------------
-- math functions --
--------------------

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