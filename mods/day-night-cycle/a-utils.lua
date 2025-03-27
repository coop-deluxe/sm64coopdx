-- localize functions to improve performance
local string_format,table_insert,math_floor,math_ceil,level_is_vanilla_level,djui_hud_get_color,djui_hud_set_color,djui_hud_print_text,obj_get_first_with_behavior_id = string.format,table.insert,math.floor,math.ceil,level_is_vanilla_level,djui_hud_get_color,djui_hud_set_color,djui_hud_print_text,obj_get_first_with_behavior_id

--- @param cond boolean
--- Human readable ternary operator
function if_then_else(cond, ifTrue, ifFalse)
    if cond then return ifTrue end
    return ifFalse
end

--- @param s string
--- Splits a string into a table by spaces
function split(s)
    local result = {}
    for match in (s):gmatch(string_format("[^%s]+", " ")) do
        table_insert(result, match)
    end
    return result
end

--- @param x number
--- @return integer
--- Rounds up or down depending on the decimal position of `x`
function math_round(x)
    return if_then_else(x - math_floor(x) >= 0.5, math_ceil(x), math_floor(x))
end

--- @param a number
--- @param b number
--- @param t number
--- Linearly interpolates between two points using a delta
function lerp(a, b, t)
    return a * (1 - t) + b * t
end

--- @param a number
--- @param b number
--- @param t number
--- Linearly interpolates between two points using a delta but ceils the final value
function lerp_ceil(a, b, t)
    return math_ceil(lerp(a, b, t))
end

--- @param a number
--- @param b number
--- @param t number
--- Linearly interpolates between two points using a delta but rounds the final value
function lerp_round(a, b, t)
    return math_round(lerp(a, b, t))
end

--- @param a Color
--- @param b Color
--- @return Color
--- Linearly interpolates between two colors using a delta
function color_lerp(a, b, t)
    return {
        r = lerp_round(a.r, b.r, t),
        g = lerp_round(a.g, b.g, t),
        b = lerp_round(a.b, b.b, t)
    }
end

--- @param priority integer
--- @param seqId SeqId
function SEQUENCE_ARGS(priority, seqId)
    return ((priority << 8) | seqId)
end

--- @param value boolean
--- Returns an on or off string depending on value
function on_or_off(value)
    if value then return "\\#00ff00\\ON" end
    return "\\#ff0000\\OFF"
end

--- @param levelNum LevelNum
--- Returns whether or not the local player is in a vanilla level
function in_vanilla_level(levelNum)
    return gNetworkPlayers[0].currLevelNum == levelNum and level_is_vanilla_level(levelNum)
end

--- @param message string
--- @param x number
--- @param y number
--- @param scale number
--- @param outlineBrightness number
--- Prints outlined DJUI HUD text
function djui_hud_print_outlined_text(message, x, y, scale, outlineBrightness)
    local color = djui_hud_get_color()
    djui_hud_set_color(color.r * outlineBrightness, color.g * outlineBrightness, color.b * outlineBrightness, color.a)
    djui_hud_print_text(message, x - 1, y, scale)
    djui_hud_print_text(message, x + 1, y, scale)
    djui_hud_print_text(message, x, y - 1, scale)
    djui_hud_print_text(message, x, y + 1, scale)
    djui_hud_set_color(color.r, color.g, color.b, color.a)
    djui_hud_print_text(message, x, y, scale)
end

--- @param table table
--- Clones a table out of an existing one, useful for making referenceless tables
function table_clone(table)
    local clone = {}
    for key, value in pairs(table) do
        if type(value) == "table" then
            clone[key] = table_clone(value) -- recursive call for nested tables
        else
            clone[key] = value
        end
    end
    return clone
end

--- Checks common conditions that make HUD rendering out of place
function check_common_hud_render_cancels()
    local action = gMarioStates[0].action
    return obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil or
           gNetworkPlayers[0].currActNum == 99 or
           gNetworkPlayers[0].currLevelNum == LEVEL_BOWSER_3 or
           gNetworkPlayers[0].currLevelNum == LEVEL_ENDING or
           action == ACT_END_PEACH_CUTSCENE or action == ACT_END_WAVING_CUTSCENE or action == ACT_CREDITS_CUTSCENE
end

local function tobool(value)
    local type = type(value)
    if type == "boolean" then
        return value
    elseif type == "number" then
        return value == 1
    elseif type == "string" then
        return value == "true"
    elseif type == "table" or type == "function" or type == "thread" or type == "userdata" then
        return true
    end
    return false
end

--- @param key string
--- `mod_storage_load_bool` except it returns true by default
function mod_storage_load_bool_2(key)
    local value = mod_storage_load(key)
    if value == nil then return true end
    return tobool(value)
end