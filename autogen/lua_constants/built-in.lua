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
    __newindex = function (_,k,_) error('Attempting to modify key `' .. k .. '` of read-only table') end,
    __metatable = false
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
gGlobalSoundSource = create_read_only_table({ x = 0, y = 0, z = 0 })

--- @param bank number
--- @param soundID number
--- @param priority number
--- @param flags number
--- @return number
function SOUND_ARG_LOAD(bank, soundID, priority, flags)
    if flags == nil then flags = 0 end
    return math.s32(
        ((bank << SOUNDARGS_SHIFT_BANK) & SOUNDARGS_MASK_BANK) |
        ((soundID << SOUNDARGS_SHIFT_SOUNDID) & SOUNDARGS_MASK_SOUNDID) |
        ((priority << SOUNDARGS_SHIFT_PRIORITY) & SOUNDARGS_MASK_PRIORITY) |
        (flags & SOUNDARGS_MASK_BITFLAGS) |
        SOUND_STATUS_WAITING
    )
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

--------------------------
-- local math functions --
--------------------------
local __math_min, __math_max, __math_sqrt, __math_floor, __math_ceil, __math_cos, __math_sin, __math_pi  = math.min, math.max, math.sqrt, math.floor, math.ceil, math.cos, math.sin, math.pi

------------
-- tweens --
------------
-- Unrelated to SM64, but these are for `math.tween`

---@param x number
---@return number
IN_SINE        = function (x) return 1 - __math_cos((x * __math_pi) / 2) end
---@param x number
---@return number
OUT_SINE       = function (x) return __math_sin((x * __math_pi) / 2) end
---@param x number
---@return number
IN_OUT_SINE    = function (x) return -(__math_cos(__math_pi * x) - 1) / 2 end
---@param x number
---@return number
OUT_IN_SINE    = function (x) return x < 0.5 and 0.5 * __math_sin(x * __math_pi) or 1 - 0.5 * __math_cos(((x * 2 - 1) * (__math_pi / 2))) end
---@param x number
---@return number
IN_QUAD        = function (x) return x ^ 2 end
---@param x number
---@return number
OUT_QUAD       = function (x) return 1 - ((1 - x) ^ 2) end
---@param x number
---@return number
IN_OUT_QUAD    = function (x) return x < 0.5 and 2 * (x ^ 2) or 1 - ((-2 * x + 2) ^ 2) / 2 end
---@param x number
---@return number
OUT_IN_QUAD    = function (x) return x < 0.5 and 0.5 * (-(2 * x) * ((2 * x) - 2)) or 0.5 + 0.5 * (2 * x - 1) ^ 2 end
---@param x number
---@return number
IN_CUBIC       = function (x) return x ^ 3 end
---@param x number
---@return number
OUT_CUBIC      = function (x) return 1 - ((1 - x) ^ 3) end
---@param x number
---@return number
IN_OUT_CUBIC   = function (x) return x < 0.5 and 4 * (x ^ 3) or 1 - ((-2 * x + 2) ^ 3) / 2 end
---@param x number
---@return number
OUT_IN_CUBIC   = function (x) return x < 0.5 and 0.5 * (((2 * x - 1) ^ 3) + 1) or 0.5 + 0.5 * (2 * x - 1) ^ 3 end
---@param x number
---@return number
IN_QUART       = function (x) return x ^ 4 end
---@param x number
---@return number
OUT_QUART      = function (x) return 1 - ((1 - x) ^ 4) end
---@param x number
---@return number
IN_OUT_QUART   = function (x) return x < 0.5 and 8 * (x ^ 4) or 1 - ((-2 * x + 2) ^ 4) / 2 end
---@param x number
---@return number
OUT_IN_QUART   = function (x) return x < 0.5 and 0.5 * (1 - ((2 * x - 1) ^ 4)) or 0.5 + 0.5 * (2 * x - 1) ^ 4 end
---@param x number
---@return number
IN_QUINT       = function (x) return x ^ 5 end
---@param x number
---@return number
OUT_QUINT      = function (x) return 1 - ((1 - x) ^ 5) end
---@param x number
---@return number
IN_OUT_QUINT   = function (x) return x < 0.5 and 16 * (x ^ 5) or 1 - ((-2 * x + 2) ^ 5) / 2 end
---@param x number
---@return number
OUT_IN_QUINT   = function (x) return x < 0.5 and 0.5 * (((2 * x - 1) ^ 5) + 1) or 0.5 + 0.5 * (2 * x - 1) ^ 5 end
---@param x number
---@return number
IN_EXPO        = function (x) return x == 0 and x or 2 ^ (10 * x - 10) end
---@param x number
---@return number
OUT_EXPO       = function (x) return x == 1 and x or 1 - (2 ^ (-10 * x)) end
---@param x number
---@return number
IN_OUT_EXPO    = function (x) return (x == 0 or x == 1) and x or x < 0.5 and (2 ^ (20 * x - 10)) / 2 or (2 - (2 ^ (-20 * x + 10))) / 2 end
---@param x number
---@return number
OUT_IN_EXPO    = function (x) return (x == 0 or x == 1) and x or x < 0.5 and 0.5 * (1 - 2 ^ (-20 * x)) or 0.5 + 0.5 * (2 ^ (20 * x - 20)) end
---@param x number
---@return number
IN_CIRC        = function (x) return 1 - __math_sqrt(1 - (x ^ 2)) end
---@param x number
---@return number
OUT_CIRC       = function (x) return __math_sqrt(1 - ((x - 1) ^ 2)) end
---@param x number
---@return number
IN_OUT_CIRC    = function (x) return x < 0.5 and (1 - __math_sqrt(1 - ((2 * x) ^ 2))) / 2 or (__math_sqrt(1 - ((-2 * x + 2) ^ 2)) + 1) / 2 end
---@param x number
---@return number
OUT_IN_CIRC    = function (x) return x < 0.5 and 0.5 * __math_sqrt(1 - (2 * x - 1) ^ 2) or 0.5 + 0.5 * (1 - __math_sqrt(1 - (2 * x - 1) ^ 2)) end
---@param x number
---@return number
IN_BACK        = function (x) return (1.70158 + 1) * (x ^ 3) - 1.70158 * (x ^ 2) end
---@param x number
---@return number
OUT_BACK       = function (x) return 1 + (1.70158 + 1) * ((x - 1) ^ 3) + 1.70158 * ((x - 1) ^ 2) end
---@param x number
---@return number
IN_OUT_BACK    = function (x) return x < 0.5 and (((2 * x) ^ 2) * (((1.70158 * 1.525) + 1) * 2 * x - (1.70158 * 1.525))) / 2 or (((2 * x - 2) ^ 2) * (((1.70158 * 1.525) + 1) * (x * 2 - 2) + (1.70158 * 1.525)) + 2) / 2 end
---@param x number
---@return number
OUT_IN_BACK    = function (x) return x < 0.5 and 0.5 * (1 + (1.70158 + 1) * ((2 * x) - 1) ^ 3 + 1.70158 * ((2 * x) - 1) ^ 2) or 0.5 + 0.5 * ((1.70158 + 1) * (2 * x - 1) ^ 3 - 1.70158 * (2 * x - 1) ^ 2) end
---@param x number
---@return number
IN_ELASTIC     = function (x) return (x == 0 or x == 1) and x or -(2 ^ (10 * x - 10)) * __math_sin((x * 10 - 10.75) * ((2 * __math_pi) / 3)) end
---@param x number
---@return number
OUT_ELASTIC    = function (x) return (x == 0 or x == 1) and x or (2 ^ (-10 * x)) * __math_sin((x * 10 - 0.75) * ((2 * __math_pi) / 3)) + 1 end
---@param x number
---@return number
IN_OUT_ELASTIC = function (x) return (x == 0 or x == 1) and x or (x < 0.5 and (-0.5 * (2 ^ (20 * x - 10)) * __math_sin((20 * x - 11.125) * ((2 * __math_pi) / 4.5)))) or (0.5 * (2 ^ (-20 * x + 10)) * __math_sin((20 * x - 11.125) * ((2 * __math_pi) / 4.5)) + 1) end
---@param x number
---@return number
OUT_IN_ELASTIC = function (x) return (x == 0 or x == 1) and x or (x < 0.5 and 0.5 * ((2 ^ (-10 * (x * 2))) * __math_sin(((x * 2) * 10 - 0.75) * ((2 * __math_pi) / 3)) + 1)) or 0.5 + 0.5 * (-(2 ^ (10 * ((x - 0.5) * 2) - 10)) * __math_sin((((x - 0.5) * 2) * 10 - 10.75) * ((2 * __math_pi) / 3))) end
---@param x number
---@return number
IN_BOUNCE      = function (x) return 1 - OUT_BOUNCE(1 - x) end
---@param x number
---@return number
OUT_BOUNCE     = function (x) if x < 1 / 2.75 then return 7.5625 * (x ^ 2) elseif x < 2 / 2.75 then x = x - 1.5 / 2.75 return 7.5625 * (x ^ 2) + 0.75 elseif x < 2.5 / 2.75 then x = x - 2.25 / 2.75 return 7.5625 * (x ^ 2) + 0.9375 else x = x - 2.625 / 2.75 return 7.5625 * (x ^ 2) + 0.984375 end end
---@param x number
---@return number
IN_OUT_BOUNCE  = function (x) return x < 0.5 and (1 - OUT_BOUNCE(1 - 2 * x)) / 2 or (1 + OUT_BOUNCE(2 * x - 1)) / 2 end
---@param x number
---@return number
OUT_IN_BOUNCE  = function (x) return x < 0.5 and 0.5 * OUT_BOUNCE(x * 2) or 0.5 + 0.5 * IN_BOUNCE(2 * x - 1) end

--------------------
-- math functions --
--------------------
--- Note: These functions don't exist in the Lua math library,
--- and are useful enough to not have to redefine them in every mod

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

--- @param t function | number
--- @param a number
--- @param b number
--- @param x number
--- @return number
--- Interpolates between `a` and `b` using delta `x` and a tweening or easing math function `t`
function math.tween(t, a, b, x)
    local y

    if type(t) == 'function' then
        y = a + t(x) * (b - a)
    else
        y = a + t * (b - a)
    end

    return y
end

local __common_signed_conversion = function (x, size)
    x = __math_floor(x) & (1 << size) - 1
    return x - ((x & (1 << (size - 1))) << 1)
end

local __common_unsigned_conversion = function (x, size)
    return __math_floor(x) & (1 << size) - 1
end

--- @param x number
--- @return integer
--- Converts `x` into a valid `s8` range
--- - `[-128, 127]`
function math.s8(x)
    return __common_signed_conversion(x, 8)
end
--- @param x number
--- @return integer
--- Converts `x` into a valid `s16` range
--- - `[-32768, 32767]`
function math.s16(x)
    return __common_signed_conversion(x, 16)
end
--- @param x number
--- @return integer
--- Converts `x` into a valid `s32` range
--- - `[-2147483648, 2147483647]`
function math.s32(x)
    return __common_signed_conversion(x, 32)
end
--- @param x number
--- @return integer
--- Converts `x` into a valid `u8` range
--- - `[0, 255]`
function math.u8(x)
    return __common_unsigned_conversion(x, 8)
end
--- @param x number
--- @return integer
--- Converts `x` into a valid `u16` range
--- - `[0, 65535]`
function math.u16(x)
    return __common_unsigned_conversion(x, 16)
end
--- @param x number
--- @return integer
--- Converts `x` into a valid `u32` range
--- - `[0, 4294967295]`
function math.u32(x)
    return __common_unsigned_conversion(x, 32)
end
