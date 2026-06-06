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
