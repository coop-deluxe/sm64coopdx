-- special thanks to Coolio for figuring out worldspace shading

--- @param dest Vec3f
--- @param rotate Vec3f
--- Rotates `dest` around the Z, Y, and X axes
local function vec3f_rotate_zyx(dest, rotate)
    local v = { x = dest.x, y = dest.y, z = dest.z }

    local sx = sins(rotate.x)
    local cx = coss(rotate.x)

    local sy = sins(rotate.y)
    local cy = coss(rotate.y)

    local sz = sins(rotate.z)
    local cz = coss(rotate.z)

    -- Rotation around Z axis
    local xz = v.x * cz - v.y * sz
    local yz = v.x * sz + v.y * cz
    local zz = v.z

    -- Rotation around Y axis
    local xy = xz * cy + zz * sy
    local yy = yz
    local zy = -xz * sy + zz * cy

    -- Rotation around X axis
    dest.x = xy
    dest.y = yy * cx - zy * sx
    dest.z = yy * sx + zy * cx

    return dest
end

local LIGHTING_OFFSET = { x = 0x28 / 0xFF, y = 0x28 / 0xFF, z = 0x28 / 0xFF }

function shading_update()
    local l = gLakituState
    local pitch = calculate_pitch(l.pos, l.focus)
    local yaw = calculate_yaw(l.pos, l.focus)
    local roll = l.roll

    local lightingDir = gVec3fOne()
    vec3f_rotate_zyx(lightingDir, { x = -pitch, y = -yaw, z = roll })
    vec3f_sub(lightingDir, LIGHTING_OFFSET)

    set_lighting_dir(0, lightingDir.x)
    set_lighting_dir(1, lightingDir.y)
    set_lighting_dir(2, lightingDir.z)
end