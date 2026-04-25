-- localize functions to improve performance
local mod_storage_load,string_format,table_insert,type,math_ceil,math_lerp,math_round,level_is_vanilla_level,djui_hud_get_color,djui_hud_set_color,djui_hud_print_text,obj_get_first_with_behavior_id = mod_storage_load,string.format,table.insert,type,math.ceil,math.lerp,math.round,level_is_vanilla_level,djui_hud_get_color,djui_hud_set_color,djui_hud_print_text,obj_get_first_with_behavior_id

--- @param key string
--- `mod_storage_load_bool` except it returns true by default
function mod_storage_load_bool_2(key)
    local value = mod_storage_load(key)
    if value == nil then return true end
    return value == "true"
end

--- @param s string
--- Splits a string into a table by spaces
function string_split(s)
    local result = {}
    for match in (s):gmatch(string_format("[^%s]+", " ")) do
        table_insert(result, match)
    end
    return result
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

--- @param cond boolean
--- Human readable ternary operator
function if_then_else(cond, ifTrue, ifFalse)
    if cond then return ifTrue end
    return ifFalse
end

--- @param value boolean
--- Returns an on or off string depending on value
function on_or_off(value)
    if value then return "\\#00ff00\\ON" end
    return "\\#ff0000\\OFF"
end

--- @param a number
--- @param b number
--- @param t number
--- Linearly interpolates between two points using a delta but ceils the final value
function lerp_ceil(a, b, t)
    return math_ceil(math_lerp(a, b, t))
end

--- @param a number
--- @param b number
--- @param t number
--- Linearly interpolates between two points using a delta but rounds the final value
function lerp_round(a, b, t)
    return math_round(math_lerp(a, b, t))
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
--- Generates a sequence ID integer with priority
function SEQUENCE_ARGS(priority, seqId)
    return ((priority << 8) | seqId)
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
--- Prints outlined DJUI HUD text
function djui_hud_print_outlined_text(message, x, y, scale)
    local hudColor = djui_hud_get_color()
    djui_hud_set_color(0, 0, 0, hudColor.a)
    djui_hud_print_text(message, x - 1, y, scale)
    djui_hud_print_text(message, x + 1, y, scale)
    djui_hud_print_text(message, x, y - 1, scale)
    djui_hud_print_text(message, x, y + 1, scale)
    djui_hud_set_color(hudColor.r, hudColor.g, hudColor.b, hudColor.a)
    djui_hud_print_text(message, x, y, scale)
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