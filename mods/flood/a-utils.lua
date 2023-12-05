moveset = false
cheats = false

for mod in pairs(gActiveMods) do
    if gActiveMods[mod].name:find("Object Spawner") then
        cheats = true
    end
end

if gServerSettings.enableCheats ~= 0 then
    cheats = true
end

for i in pairs(gActiveMods) do
    if (gActiveMods[i].incompatible ~= nil and gActiveMods[i].incompatible:find("moveset")) or gActiveMods[i].name:find("Squishy's Server") or (gActiveMods[i].name:find("Pasta") and gActiveMods[i].name:find("Castle")) then
        moveset = true
    end
end

-- localize functions to improve performance
local math_floor,is_player_active,table_insert,is_game_paused,djui_hud_set_color = math.floor,is_player_active,table.insert,is_game_paused,djui_hud_set_color

rom_hack_cam_set_collisions(false)

-- Rounds up or down depending on the decimal position of `x`.
--- @param x number
--- @return integer
function math_round(x)
    return if_then_else(x - math.floor(x) >= 0.5, math.ceil(x), math.floor(x))
end

-- Recieves a value of any type and converts it into a boolean.
function tobool(v)
    local type = type(v)
    if type == "boolean" then
        return v
    elseif type == "number" then
        return v == 1
    elseif type == "string" then
        return v == "true"
    elseif type == "table" or type == "function" or type == "thread" or type == "userdata" then
        return true
    end
    return false
end

function switch(param, case_table)
    local case = case_table[param]
    if case then return case() end
    local def = case_table['default']
    return def and def() or nil
end

--- @param m MarioState
function active_player(m)
    local np = gNetworkPlayers[m.playerIndex]
    if m.playerIndex == 0 then
        return 1
    end
    if not np.connected then
        return 0
    end
    if np.currCourseNum ~= gNetworkPlayers[0].currCourseNum then
        return 0
    end
    if np.currActNum ~= gNetworkPlayers[0].currActNum then
        return 0
    end
    if np.currLevelNum ~= gNetworkPlayers[0].currLevelNum then
        return 0
    end
    if np.currAreaIndex ~= gNetworkPlayers[0].currAreaIndex then
        return 0
    end
    return is_player_active(m)
end

function if_then_else(cond, ifTrue, ifFalse)
    if cond then return ifTrue end
    return ifFalse
end

function string_without_hex(name)
    local s = ''
    local inSlash = false
    for i = 1, #name do
        local c = name:sub(i,i)
        if c == '\\' then
            inSlash = not inSlash
        elseif not inSlash then
            s = s .. c
        end
    end
    return s
end

function on_or_off(value)
    if value then return "\\#00ff00\\ON" end
    return "\\#ff0000\\OFF"
end

function split(s)
    local result = {}
    for match in (s):gmatch(string.format("[^%s]+", " ")) do
        table.insert(result, match)
    end
    return result
end

function djui_hud_set_adjusted_color(r, g, b, a)
    local multiplier = 1
    if is_game_paused() then multiplier = 0.5 end
    djui_hud_set_color(r * multiplier, g * multiplier, b * multiplier, a)
end

function SEQUENCE_ARGS(priority, seqId)
    return ((priority << 8) | seqId)
end

--- @param m MarioState
function mario_set_full_health(m)
    m.health = 0x880
    m.healCounter = 0
    m.hurtCounter = 0
end

local levelToCourse = {
    [LEVEL_NONE] = COURSE_NONE,
    [LEVEL_BOB] = COURSE_BOB,
    [LEVEL_WF] = COURSE_WF,
    [LEVEL_JRB] = COURSE_JRB,
    [LEVEL_CCM] = COURSE_CCM,
    [LEVEL_BBH] = COURSE_BBH,
    [LEVEL_HMC] = COURSE_HMC,
    [LEVEL_LLL] = COURSE_LLL,
    [LEVEL_SSL] = COURSE_SSL,
    [LEVEL_DDD] = COURSE_DDD,
    [LEVEL_SL] = COURSE_SL,
    [LEVEL_WDW] = COURSE_WDW,
    [LEVEL_TTM] = COURSE_TTM,
    [LEVEL_THI] = COURSE_THI,
    [LEVEL_TTC] = COURSE_TTC,
    [LEVEL_RR] = COURSE_RR,
    [LEVEL_BITDW] = COURSE_BITDW,
    [LEVEL_BITFS] = COURSE_BITFS,
    [LEVEL_BITS] = COURSE_BITS,
    [LEVEL_PSS] = COURSE_PSS,
    [LEVEL_COTMC] = COURSE_COTMC,
    [LEVEL_TOTWC] = COURSE_TOTWC,
    [LEVEL_VCUTM] = COURSE_VCUTM,
    [LEVEL_WMOTR] = COURSE_WMOTR,
    [LEVEL_SA] = COURSE_SA,
    [LEVEL_ENDING] = COURSE_CAKE_END,
}

function level_to_course(level)
    return levelToCourse[level] or COURSE_NONE
end

function timestamp(seconds)
    seconds = seconds / 30
    local minutes = math.floor(seconds / 60)
    local milliseconds = math.floor((seconds - math.floor(seconds)) * 1000)
    seconds = math.floor(seconds) % 60
    return string.format("%d:%02d:%03d", minutes, seconds, milliseconds)
end