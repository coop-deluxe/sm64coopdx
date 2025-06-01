math.randomseed(get_time())

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

-----------
-- table --
-----------

--- Creates a shallow copy of table `t`
--- @param t table
--- @return table
function table.copy(t)
    return table_copy(t)
end

--- Creates a deep copy of table `t`
--- @param t table
--- @return table
function table.deepcopy(t)
    return table_deepcopy(t)
end

--- Utility function to create a read-only table
--- @param data table
--- @return table
function create_read_only_table(data)
    local t = {}
    local mt = {
        __index = data,
        __newindex = function(_, k, _)
            error('Attempting to modify key `' .. k .. '` of read-only table')
        end,
        __call = function() return table_copy(data) end,
        __metatable = false
    }
    setmetatable(t, mt)
    return t
end

-----------
-- sound --
-----------

--- @type Vec3f
gGlobalSoundSource = { x = 0, y = 0, z = 0 }

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


------------------------------
-- player palette functions --
------------------------------

--- @param np NetworkPlayer
--- @param part PlayerPart
--- @return Color
--- Gets the palette color of `part` on `np`
function network_player_get_palette_color(np, part)
    local color = {
        r = network_player_get_palette_color_channel(np, part, 0),
        g = network_player_get_palette_color_channel(np, part, 1),
        b = network_player_get_palette_color_channel(np, part, 2)
    }
    return color
end

--- @param np NetworkPlayer
--- @param part PlayerPart
--- @return Color
--- Gets the override palette color of `part` on `np`
function network_player_get_override_palette_color(np, part)
    local color = {
        r = network_player_get_override_palette_color_channel(np, part, 0),
        g = network_player_get_override_palette_color_channel(np, part, 1),
        b = network_player_get_override_palette_color_channel(np, part, 2)
    }
    return color
end


--------------------
-- math functions --
--------------------
--- Note: These functions don't exist in the Lua math library,
--- and are useful enough to not have to redefine them in every mod

local __math_min, __math_max, __math_sqrt, __math_floor, __math_ceil = math.min, math.max, math.sqrt, math.floor, math.ceil

--- @param x number
--- @return number
--- Computes the square of the number `x`
function math.sqr(x)
    return x * x
end

--- @param x number
--- @param a number
--- @param b number
--- @return number
--- Clamps the number `x` between bounds `a` (minimum) and `b` (maximum)
function math.clamp(x, a, b)
    return __math_min(__math_max(x, a), b)
end

--- @param a number
--- @param b number
--- @return number
--- Computes the hypotenuse of a right-angled triangle given sides `a` and `b` using the Pythagorean theorem
function math.hypot(a, b)
    return __math_sqrt(a * a + b * b)
end

--- @param x number
--- @return number
--- Returns 1 if `x` is positive or zero, -1 otherwise
function math.sign(x)
    return x >= 0 and 1 or -1
end

--- @param x number
--- @return number
--- Returns 1 if `x` is positive, 0 if it is zero, -1 otherwise
function math.sign0(x)
    return x ~= 0 and (x > 0 and 1 or -1) or 0
end

--- @param a number
--- @param b number
--- @param t number
--- @return number
--- Linearly interpolates between `a` and `b` using delta `t`
function math.lerp(a, b, t)
    return a + (b - a) * t
end

--- @param a number
--- @param b number
--- @param x number
--- @return number
--- Determines where `x` linearly lies between `a` and `b`. It's the inverse of `math.lerp`
function math.invlerp(a, b, x)
    return (x - a) / (b - a)
end

--- @param a number
--- @param b number
--- @param c number
--- @param d number
--- @param x number
--- @return number
--- Linearly remaps `x` from the source range `[a, b]` to the destination range `[c, d]`
function math.remap(a, b, c, d, x)
    return c + (d - c) * ((x - a) / (b - a))
end

--- @param x number
--- Rounds `x` to the nearest integer value
function math.round(x)
    return x > 0 and __math_floor(x + 0.5) or __math_ceil(x - 0.5)
end