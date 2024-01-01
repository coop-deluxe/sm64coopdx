if SM64COOPDX_VERSION == nil then return end

-- localize functions to improve performance
local play_sound,table_insert,get_skybox,level_is_vanilla_level,math_floor,math_ceil = play_sound,table.insert,get_skybox,level_is_vanilla_level,math.floor,math.ceil

function if_then_else(cond, ifTrue, ifFalse)
    if cond then return ifTrue end
    return ifFalse
end

function split(s)
    local result = {}
    for match in (s):gmatch(string.format("[^%s]+", " ")) do
        table_insert(result, match)
    end
    return result
end

function lerp(a, b, t) return a * (1 - t) + b * t end

--- @param a Color
--- @param b Color
--- @return Color
function color_lerp(a, b, t)
    return {
        r = lerp(a.r, b.r, t),
        g = lerp(a.g, b.g, t),
        b = lerp(a.b, b.b, t)
    }
end

function SEQUENCE_ARGS(priority, seqId)
    return ((priority << 8) | seqId)
end

function on_or_off(value)
    if value then return "\\#00ff00\\ON" end
    return "\\#ff0000\\OFF"
end

function show_day_night_cycle()
    local skybox = get_skybox()
    return skybox ~= -1 and
        skybox ~= BACKGROUND_CUSTOM and
        skybox ~= BACKGROUND_FLAMING_SKY and
        skybox ~= BACKGROUND_GREEN_SKY and
        skybox ~= BACKGROUND_HAUNTED and
        skybox ~= BACKGROUND_PURPLE_SKY and
        skybox ~= BACKGROUND_UNDERWATER_CITY
end

function in_vanilla_level(levelNum)
    return gNetworkPlayers[0].currLevelNum == levelNum and level_is_vanilla_level(levelNum)
end

function lerp_round(a, b, t)
    local x = lerp(a, b, t)
    return x >= 0 and math_floor(x + 0.5) or math_ceil(x - 0.5)
end