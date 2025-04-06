-- localize functions to improve performance - a-utils.lua
local string_lower,string_format,table_insert,get_date_and_time = string.lower,string.format,table.insert,get_date_and_time

if VERSION_NUMBER < 38 then
    djui_popup_create("\n\\#FFAAAA\\Character Select requires\n the latest version of CoopDX to use!\n\nYou can find CoopDX here:\n\\#6666FF\\https://sm64coopdx.com", 5)
    incompatibleClient = true
    return 0
end

local dependacyFiles = {
    -- Required Lua File
    "main.lua",
    "n-hud.lua",
    "o-api.lua",
    "z-moveset.lua",
    "z-palettes.lua",
    "z-voice.lua",
    -- Required Actors
    "actors/armature_geo.bin",
}
local legacyFiles = {
    "voice.lua",
    "palettes.lua",
    "z-anims.lua",
}

-- Check for Missing Files
local missingDependacyFiles = false
for i = 1, #dependacyFiles do
    if not mod_file_exists(dependacyFiles[i]) then
        log_to_console("Character Select file missing: '" .. dependacyFiles[i] .. "'", CONSOLE_MESSAGE_ERROR)
        missingDependacyFiles = true
    end
end
if missingDependacyFiles then
    djui_popup_create("\n\\#FFAAAA\\Character Select is missing\nan important file!\n\nYou can find a list of\nmissing files in the console!", 5)
    incompatibleClient = true
    return 0
end

-- Check for Legacy Files
local foundLegacyFiles = false
for i = 1, #legacyFiles do
    if mod_file_exists(legacyFiles[i]) then
        log_to_console("Character Select legacy file found: '" .. legacyFiles[i] .. "'", CONSOLE_MESSAGE_ERROR)
        foundLegacyFiles = true
    end
end
if foundLegacyFiles then
    djui_popup_create("\n\\#FFAAAA\\Character Select is loading\nan outdated file!\n\nYou can find a list of\nold files in the console!", 5)
    incompatibleClient = true
    return 0
end

-- Version Data --
MOD_VERSION_API = 1
MOD_VERSION_MAJOR = 13
MOD_VERSION_MINOR = 0
MOD_VERSION_INDEV = false
MOD_VERSION_STRING = tostring(MOD_VERSION_API) .. "." .. tostring(MOD_VERSION_MAJOR) .. (MOD_VERSION_MINOR > 0 and ("." .. tostring(MOD_VERSION_MINOR)) or "") .. (MOD_VERSION_INDEV and " (In-Dev)" or "")

ommActive = false
for i in pairs(gActiveMods) do
    if gActiveMods[i].relativePath == "omm-coop" then
        ommActive = true
        break
    end
end

local saveableCharacters = {
    ["1"] = true,
    ["2"] = true,
    ["3"] = true,
    ["4"] = true,
    ["5"] = true,
    ["6"] = true,
    ["7"] = true,
    ["8"] = true,
    ["9"] = true,
    ["0"] = true,
    ["a"] = true,
    ["b"] = true,
    ["c"] = true,
    ["d"] = true,
    ["e"] = true,
    ["f"] = true,
    ["g"] = true,
    ["h"] = true,
    ["i"] = true,
    ["j"] = true,
    ["k"] = true,
    ["l"] = true,
    ["m"] = true,
    ["n"] = true,
    ["o"] = true,
    ["p"] = true,
    ["q"] = true,
    ["r"] = true,
    ["s"] = true,
    ["t"] = true,
    ["u"] = true,
    ["v"] = true,
    ["w"] = true,
    ["x"] = true,
    ["y"] = true,
    ["z"] = true,
    ["_"] = true,
    ["-"] = true,
    ["."] = true,

    -- Replace with Underscore
    [" "] = false,
}

--- @param string string
--- Replaces underscores in the string with spaces
function string_underscore_to_space(string)
    if string == nil then return "" end
    return string:gsub("_", " ")
end

--- @param string string
--- Constructs a new string but only with characters from `saveableCharacters`
--- * Spaces are the notable character that gets turned into an underscore
function string_space_to_underscore(string)
    local s = ''
    for i = 1, #string do
        local c = string:sub(i,i)
        if saveableCharacters[string_lower(c)] then
            s = s .. c
        elseif saveableCharacters[string_lower(c)] ~= nil then
            s = s .. "_"
        end
    end
    return s
end

--- @param string string
--- Splits a string into a table by spaces
function string_split(string)
    local result = {}
    for match in string:gmatch(string_format("[^%s]+", " ")) do
        table_insert(result, match)
    end
    return result
end

--- @param param number
--- @param caseTable table
--- Switch statement function
function switch(param, caseTable)
    local case = caseTable[param]
    if case then return case() end
    local def = caseTable['default']
    return def and def() or nil
end

function clamp(num, min, max)
    return math.max(math.min(num, max), min)
end

allowMenu = {}

renderInMenuTable = {
    front = {},
    back = {},
}

queueStorageFailsafe = false

charBeingSet = false

stopPalettes = false
for i in pairs(gActiveMods) do
    if (gActiveMods[i].incompatible ~= nil and gActiveMods[i].incompatible:find("gamemode")) and not (gActiveMods[i].name:find("Personal Star Counter")) then
        stopPalettes = true
    end
end

stopMovesets = false

seasonalEvent = 0
SEASON_EVENT_BIRTHDAY = 1
SEASON_EVENT_CHRISTMAS = 2
-- December
if get_date_and_time().month == 11 then
    if get_date_and_time().day == 3 then
        -- Character Select's Birthday
        seasonalEvent = SEASON_EVENT_BIRTHDAY
    else
        -- Christmas
        seasonalEvent = SEASON_EVENT_CHRISTMAS
    end
end

-- Dedicated Networking Table for Character Select
gCSPlayers = {}
for i = 0, MAX_PLAYERS - 1 do
    gCSPlayers[i] = {
        index = network_global_index_from_local(i),
        saveName = "Default",
        currAlt = 1,
        presetPalette = 0,
        offset = 0,
        forceChar = 0,
        modelId = E_MODEL_MARIO,
        isUpdating = false,
        movesetToggle = true,
        modelEditOffset = 0,
    }
end

local stallPacket = 0
local function update()
    stallPacket = (stallPacket+1)%3 -- refresh rate (to reduce stress)
    if stallPacket == 0 then
        network_send(false, gCSPlayers[0])
    end
end

local function on_packet_recieve(data)
    local index = network_local_index_from_global(data.index)
    gCSPlayers[index] = data
end

hook_event(HOOK_ON_PACKET_RECEIVE, on_packet_recieve)
hook_event(HOOK_UPDATE, update)