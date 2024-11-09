-- name: Cheats
-- incompatible: cheats
-- description: Cheats\nA mod that adds a bunch of cheats to the mod menu, accessible through the pause menu.

-- localize functions to improve performance
local math_floor,smlua_text_utils_get_language,table_insert,approach_s32,set_mario_action,get_network_area_timer = math.floor,smlua_text_utils_get_language,table.insert,approach_s32,set_mario_action,get_network_area_timer

--- @class Cheat
--- @field public codename string
--- @field public names table
--- @field public hook LuaHookedEventType
--- @field public func function
--- @field public allowHazardSurfaces boolean

local CHEATS_VERSION = "v1.0"

--- @type Cheat[]
local sCheats = {}

--- @param m MarioState
--- Checks if `m` is active
local function active_player(m)
    local np = gNetworkPlayers[m.playerIndex]
    if m.playerIndex == 0 then
        return true
    end
    if not np.connected then
        return false
    end
    if np.currCourseNum ~= gNetworkPlayers[0].currCourseNum then
        return false
    end
    if np.currActNum ~= gNetworkPlayers[0].currActNum then
        return false
    end
    if np.currLevelNum ~= gNetworkPlayers[0].currLevelNum then
        return false
    end
    if np.currAreaIndex ~= gNetworkPlayers[0].currAreaIndex then
        return false
    end
    return true
end

--- @param num integer
--- Limits an integer in the s16 range
local function s16(num)
    num = math_floor(num) & 0xFFFF
    if num >= 32768 then return num - 65536 end
    return num
end

local function lang_string(strings)
    local table = strings[smlua_text_utils_get_language()]
    if table == nil then return strings["English"] end
    return table
end

--- @param codename string
--- @param names table<string, string>
--- @param hook LuaHookedEventType
--- @param func function
--- @param allowHazardSurfaces boolean
--- Registers a cheat
---
--- Supported hooks:
--- - `HOOK_MARIO_UPDATE`
--- - `HOOK_BEFORE_MARIO_UPDATE`
--- - `HOOK_BEFORE_PHYS_STEP`
local function register_cheat(codename, names, hook, func, allowHazardSurfaces)
    table_insert(sCheats, {
        codename = codename,
        names = names,
        hook = hook,
        func = func,
        allowHazardSurfaces = allowHazardSurfaces
    })

    for i = 0, MAX_PLAYERS - 1 do
        gPlayerSyncTable[i][codename] = false
    end
end

--- @param m MarioState
local function moon_jump_update(m)
    if m.controller.buttonDown & L_TRIG ~= 0 then
        m.faceAngle.y = m.intendedYaw - approach_s32(s16(m.intendedYaw - m.faceAngle.y), 0, 0x800, 0x800)
        m.vel.y = 40

        if m.action == ACT_FORWARD_GROUND_KB or
           m.action == ACT_BACKWARD_GROUND_KB or
           m.action == ACT_SOFT_FORWARD_GROUND_KB or
           m.action == ACT_HARD_BACKWARD_GROUND_KB or
           m.action == ACT_FORWARD_AIR_KB or
           m.action == ACT_BACKWARD_AIR_KB or
           m.action == ACT_HARD_FORWARD_AIR_KB or
           m.action == ACT_HARD_BACKWARD_AIR_KB or
           m.action == ACT_AIR_HIT_WALL then
            set_mario_action(m, ACT_FREEFALL, 0)
        end
    end
end

--- @param m MarioState
local function god_mode_update(m)
    m.health = 0x880
    m.healCounter = 0
    m.hurtCounter = 0
    m.peakHeight = m.pos.y
end

--- @param m MarioState
local function infinite_lives_update(m)
    m.numLives = 100
end

--- @param m MarioState
local function super_speed_update(m)
    if m.action ~= ACT_BUBBLED and m.action ~= ACT_WATER_JUMP and m.action ~= ACT_HOLD_WATER_JUMP then
        m.vel.x = m.vel.x * 4
        m.vel.z = m.vel.z * 4
    end
end

--- @param m MarioState
local function responsive_controls_update(m)
    if m.action == ACT_WALKING or
       m.action == ACT_HOLD_WALKING or
       m.action == ACT_HOLD_HEAVY_WALKING or
       m.action == ACT_FINISH_TURNING_AROUND or
       m.action == ACT_CRAWLING then
        m.faceAngle.y = m.intendedYaw
    end
end

--- @param m MarioState
local function rapid_fire_update(m)
    if (m.controller.buttonDown & A_BUTTON) ~= 0 and get_global_timer() % 2 == 0 then
        m.controller.buttonPressed = m.controller.buttonPressed | A_BUTTON
    end
end

local function blj_anywhere_update(m)
    if m.action == ACT_LONG_JUMP and
       m.controller.buttonDown & Z_TRIG ~= 0 and
       m.forwardVel < -15 then
        m.vel.y = -30
	end
end

local function always_triple_jump_update(m, action)
    if m.forwardVel < 20 and m.action == ACT_DOUBLE_JUMP_LAND and action == ACT_JUMP then
        return ACT_TRIPLE_JUMP
	end
end

register_cheat(
    "moonJump",
    {
        ["Czech"] = "Nekonečný Skok",
        ["Dutch"] = "Maan Sprong",
        ["English"] = "Moon Jump",
        ["French"] = "Saut Antigravité",
        ["German"] = "Mond-Sprung",
        ["Italian"] = "Salto della Luna",
        ["Polish"] = "Skok Ksiezycowy",
        ["Portuguese"] = "Pulo da Lua",
        ["Russian"] = "Супер прыжок",
        ["Spanish"] = "Salto Lunar"
    },
    HOOK_MARIO_UPDATE,
    moon_jump_update,
    true
)

register_cheat(
    "godMode",
    {
        ["Czech"] = "Nenech Se Zranit",
        ["Dutch"] = "God Modus",
        ["English"] = "God Mode",
        ["French"] = "Mode Invincible",
        ["German"] = "Gott Modus",
        ["Italian"] = "Modalità Dio",
        ["Polish"] = "Tryb Boga",
        ["Portuguese"] = "Modo Deus",
        ["Russian"] = "Режим бога",
        ["Spanish"] = "Modo Dios",
    },
    HOOK_MARIO_UPDATE,
    god_mode_update,
    false
)

register_cheat(
    "infiniteLives",
    {
        ["Czech"] = "Nekonečné Životy",
        ["Dutch"] = "Oneindige Levens",
        ["English"] = "Infinite Lives",
        ["French"] = "Vies Infinies",
        ["German"] = "Unbegrenzte Leben",
        ["Italian"] = "Vite Infinite",
        ["Polish"] = "Nieskonczone Zycia",
        ["Portuguese"] = "Vidas Infinitas",
        ["Russian"] = "Бесконечные жизни",
        ["Spanish"] = "Vidas Infinitas",
    },
    HOOK_MARIO_UPDATE,
    infinite_lives_update,
    true
)

register_cheat(
    "superSpeed",
    {
        ["Czech"] = "Super Rychlost",
        ["Dutch"] = "Super Snelheid",
        ["English"] = "Super Speed",
        ["French"] = "Super Vitesse",
        ["German"] = "Supergeschwindigkeit",
        ["Italian"] = "Super Velocità",
        ["Polish"] = "Super Szybkosc",
        ["Portuguese"] = "Super Velocidade",
        ["Russian"] = "Супер cкорость",
        ["Spanish"] = "Super Velocidad",
    },
    HOOK_BEFORE_PHYS_STEP,
    super_speed_update,
    true
)

register_cheat(
    "responsiveControls",
    {
        ["Czech"] = "Citlivé Ovládání",
        ["Dutch"] = "Snel Reagerende Controles",
        ["English"] = "Responsive Controls",
        ["French"] = "Contrôles Réactifs",
        ["German"] = "Reaktionsschnelle Steuerung",
        ["Italian"] = "Controlli Reattivi",
        ["Polish"] = "Responsywne Sterowanie",
        ["Portuguese"] = "Controle Responsivos",
        ["Russian"] = "Отзывчивое управление",
        ["Spanish"] = "Controles Responsivos",
    },
    HOOK_MARIO_UPDATE,
    responsive_controls_update,
    true
)

register_cheat(
    "rapidFire",
    {
        ["Czech"] = "Rychle Mačkat Tlačítko",
        ["Dutch"] = "Snel Vuur",
        ["English"] = "Rapid Fire",
        ["French"] = "Tir Rapide",
        ["German"] = "Schnellfeuer",
        ["Italian"] = "Fuoco Rapido",
        ["Polish"] = "Szybkostrzelnosc",
        ["Portuguese"] = "Fogo Rápido",
        ["Russian"] = "Быстрый огонь",
        ["Spanish"] = "Pulsación Rápida",
    },
    HOOK_BEFORE_MARIO_UPDATE,
    rapid_fire_update,
    true
)

register_cheat(
    "bljAnywhere",
    {
        ["Czech"] = "BLJ Všude",
        ["Dutch"] = "BLJ Overal",
        ["English"] = "BLJ Anywhere",
        ["French"] = "BLJ N'importe Où",
        ["German"] = "Überall Rückwertsweitspringen",
        ["Italian"] = "BLJ Ovunque",
        ["Polish"] = "BLJ Gdziekolwiek",
        ["Portuguese"] = "BLJ Em Qualquer Lugar",
        ["Russian"] = "BLJ в любом месте",
        ["Spanish"] = "BLJ Donde Sea",
    },
    HOOK_BEFORE_MARIO_UPDATE,
    blj_anywhere_update,
    true
)

register_cheat(
    "alwaysTripleJump",
    {
        ["Czech"] = "Vždy Trojitý Skok",
        ["Dutch"] = "Altijd Drievoudige Sprong",
        ["English"] = "Always Triple Jump",
        ["French"] = "Triple Sauts Infinis",
        ["German"] = "Immer Dreisprung",
        ["Italian"] = "Sempre Salto Triplo",
        ["Polish"] = "Potrojny Skok Zawsze",
        ["Portuguese"] = "Sempre Fazer Triple Jump",
        ["Russian"] = "Всегда тройной прыжок",
        ["Spanish"] = "Siempre Hacer Salto Triple",
    },
    HOOK_BEFORE_SET_MARIO_ACTION,
    always_triple_jump_update,
    true
)

--- @param hookType LuaHookedEventType
local function generate_mario_hook_function(hookType)
    --- @param m MarioState
    return function(m)
        if not active_player(m) then return end

        for _, cheat in ipairs(sCheats) do
            if cheat.hook == hookType and gPlayerSyncTable[m.playerIndex][cheat.codename] then
                cheat.func(m)
            end
        end
    end
end

local function before_set_mario_action(m, action)
    if not active_player(m) then return end

    for _, cheat in ipairs(sCheats) do
        if cheat.hook == HOOK_BEFORE_SET_MARIO_ACTION and gPlayerSyncTable[m.playerIndex][cheat.codename] then
            return cheat.func(m, action)
        end
    end
end

--- @param m MarioState
local function allow_hazard_surface(m)
    for _, cheat in ipairs(sCheats) do
        if gPlayerSyncTable[m.playerIndex][cheat.codename] and not cheat.allowHazardSurfaces then return false end
    end
    return true
end

local function on_language_changed()
    for i, cheat in ipairs(sCheats) do
        update_mod_menu_element_name(i - 1, lang_string(cheat.names))
    end
end


--- @param index integer
--- @param value boolean
local function update_cheat(index, value)
    for i, cheat in ipairs(sCheats) do
        if i == index + 1 then
            gPlayerSyncTable[0][cheat.codename] = value
        end
    end
end

local sReadonlyMetatable = {
    __index = function(table, key)
        return rawget(table, key)
    end,

    __newindex = function()
        error("attempt to update a read-only table", 2)
    end
}

_G.cheatsApi = {
    version = CHEATS_VERSION,
    register_cheat = register_cheat
}
setmetatable(_G.cheatsApi, sReadonlyMetatable)

hook_event(HOOK_MARIO_UPDATE, generate_mario_hook_function(HOOK_MARIO_UPDATE))
hook_event(HOOK_BEFORE_MARIO_UPDATE, generate_mario_hook_function(HOOK_BEFORE_MARIO_UPDATE))
hook_event(HOOK_BEFORE_PHYS_STEP, generate_mario_hook_function(HOOK_BEFORE_PHYS_STEP))
hook_event(HOOK_BEFORE_SET_MARIO_ACTION, before_set_mario_action)
hook_event(HOOK_ALLOW_HAZARD_SURFACE, allow_hazard_surface)
hook_event(HOOK_ON_LANGUAGE_CHANGED, on_language_changed)

for _, cheat in ipairs(sCheats) do
    hook_mod_menu_checkbox(lang_string(cheat.names), false, update_cheat)
end
