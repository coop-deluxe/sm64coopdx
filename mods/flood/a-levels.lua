unsupported = false

FLOOD_WATER = 0
FLOOD_LAVA  = 1
FLOOD_SAND  = 2
FLOOD_MUD   = 3

FLOOD_BONUS_LEVELS = 0
FLOOD_LEVEL_COUNT = 0

LEVEL_LOBBY = LEVEL_CASTLE_GROUNDS
LEVEL_CTT = LEVEL_SA

GAME_VANILLA = 0
GAME_STAR_ROAD = 1

game = GAME_VANILLA

--- @class FloodLevel
--- @field public name string
--- @field public goalPos Vec3f
--- @field public speed number
--- @field public area integer
--- @field public type integer
--- @field public time integer
--- @field public customStartPos Vec3f

--- @type FloodLevel[]
gLevels = {}
gMapRotation = {}

-- localize functions to improve performance
local table_insert,djui_popup_create = table.insert,djui_popup_create

local function flood_define_level(bonus, level, name, goalPos, speed, area, type, customStartPos)
    gLevels[level] = { name = name, goalPos = goalPos, speed = speed, area = area, type = type, time = 0, customStartPos = customStartPos }
    table_insert(gMapRotation, level)

    if bonus then FLOOD_BONUS_LEVELS = FLOOD_BONUS_LEVELS + 1 end
    FLOOD_LEVEL_COUNT = FLOOD_LEVEL_COUNT + 1
end
_G.flood_define_level = flood_define_level

local function flood_load_vanilla_levels()
    game = GAME_VANILLA

    --                 bonus  level                 name              goal position                                    speed area type         custom start pos
    flood_define_level(false, LEVEL_BOB,            "bob",            { x =  3304, y = 4242, z = -4603, a =  0x0000 }, 2.5,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_WF,             "wf",             { x =  414,  y = 5325, z = -20,   a =  0x0000 }, 4.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_CCM,            "ccm",            { x =  -478, y = 3471, z = -964,  a =  0x0000 }, 5.0,  1,   FLOOD_WATER, { x = 3336, y = -3800, z =  0, a = 0x0000 })
    flood_define_level(false, LEVEL_BITDW,          "bitdw",          { x =  6772, y = 2867, z =  0,    a = -0x4000 }, 4.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_BBH,            "bbh",            { x =  655,  y = 3277, z =  244,  a =  0x8000 }, 3.5,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_HMC,            "hmc",            { x = -4163, y = 2355, z = -2544, a =  0x0000 }, 5.0,  1,   FLOOD_WATER, { x = -3538, y = -3979, z = 3568, a = 0x8000 })
    flood_define_level(false, LEVEL_LLL,            "lll",            { x =  2523, y = 3591, z = -898,  a = -0x8000 }, 3.5,  2,   FLOOD_LAVA,  nil)
    flood_define_level(false, LEVEL_SSL,            "ssl",            { x =  512,  y = 4815, z = -551,  a =  0x0000 }, 3.0,  2,   FLOOD_SAND,  nil)
    flood_define_level(false, LEVEL_WDW,            "wdw",            { x =  1467, y = 4096, z =  93,   a = -0x4000 }, 4.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_TTM,            "ttm",            { x =  1053, y = 2309, z =  305,  a =  0x0000 }, 3.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_THI,            "thi",            { x =  1037, y = 4060, z = -2091, a =  0x0000 }, 4.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_TTC,            "ttc",            { x =  2208, y = 7051, z =  2217, a =  0x0000 }, 4.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_BITS,           "bits",           { x =  369,  y = 6552, z = -6000, a =  0x0000 }, 4.5,  1,   FLOOD_LAVA,  nil)
    flood_define_level(false, LEVEL_CTT,            "ctt",            { x =  0,    y = 700,  z =  0,    a =  0x0000 }, 5.0,  1,   FLOOD_LAVA,  nil)
    flood_define_level(true,  LEVEL_SL,             "sl",             { x =  40,   y = 4864, z =  240,  a =  0x0000 }, 3.0,  1,   FLOOD_WATER, nil)
    flood_define_level(true,  LEVEL_RR,             "rr",             { x =  0,    y = 3468, z = -2335, a =  0x0000 }, 3.0,  1,   FLOOD_WATER, nil)
    flood_define_level(true,  LEVEL_CASTLE_GROUNDS, "castle_grounds", { x =  0,    y = 7583, z = -4015, a =  0x0000 }, 7.0,  1,   FLOOD_WATER, nil)
end

local function flood_load_star_road_levels()
    game = GAME_STAR_ROAD

    --                 bonus  level                 name              goal position                                     speed area type         custom start pos
    flood_define_level(false, LEVEL_BOB,            "bob",            { x =  5364, y = 1875,  z =  2251, a =  0x0000 }, 3.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_WF,             "wf",             { x =  208,  y = 2448,  z = -2080, a =  0x4000 }, 5.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_JRB,            "jrb",            { x = -4672, y = 3541,  z = -3619, a = -0x4000 }, 4.0,  1,   FLOOD_WATER, { x = 2316, y = -448, z = -5150, a = 0x0000 })
    flood_define_level(false, LEVEL_CCM,            "ccm",            { x =  5709, y = 3501,  z = -2141, a = -0x4000 }, 3.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_PSS,            "pss",            { x = -3415, y = 4573,  z =  2678, a =  0x0000 }, 3.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_BITDW,          "bitdw",          { x =  455,  y = 2324,  z =  0,    a = -0x4000 }, 3.0,  1,   FLOOD_MUD,   nil)
    flood_define_level(false, LEVEL_BBH,            "bbh",            { x =  4376, y = 2632,  z = -4542, a =  0x0000 }, 3.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_LLL,            "lll",            { x =  4348, y = 4638,  z =  3877, a = -0x4000 }, 7.0,  1,   FLOOD_SAND,  nil)
    flood_define_level(false, LEVEL_SL,             "sl",             { x =  4543, y = 3709,  z =  3311, a =  0x8000 }, 2.5,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_WDW,            "wdw",            { x = -3342, y = 2603,  z =  845,  a =  0x4000 }, 4.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_TTM,            "ttm",            { x =  1033, y = 4813,  z = -6320, a =  0x8000 }, 2.0,  1,   FLOOD_WATER, nil)
    flood_define_level(false, LEVEL_TTC,            "ttc",            { x =  1405, y = 3425,  z = -3463, a =  0x8000 }, 4.0,  1,   FLOOD_LAVA,  nil)
    flood_define_level(false, LEVEL_RR,             "rr",             { x =  5052, y = 11056, z =  413,  a = -0x4000 }, 4.0,  1,   FLOOD_WATER, { x = 3923, y = -3283, z = -1323, a = 0x8000 })
    flood_define_level(true,  LEVEL_CASTLE_GROUNDS, "castle_grounds", { x = -8455, y = 2746,  z =  2876, a =  0x8000 }, 15.0, 1,   FLOOD_WATER, { x = -1644, y = -614, z = -1524, a = -0x4000 })
end

-- load romhack levels
for mod in pairs(gActiveMods) do
    if gActiveMods[mod].incompatible ~= nil and gActiveMods[mod].incompatible:find("romhack") then
        if gActiveMods[mod].relativePath == "star-road" then
            flood_load_star_road_levels()
        else
            unsupported = true
            djui_popup_create("\\#ff0000\\This rom hack is not supported with Flood.", 2)
        end
        break
    end
end

if not unsupported and game == GAME_VANILLA then
    flood_load_vanilla_levels()
end