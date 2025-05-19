-- localize functions to improve performance - a-utils.lua
local string_lower,string_format,table_insert,get_date_and_time = string.lower,string.format,table.insert,get_date_and_time

-- Version Data --
MOD_VERSION_API = 1
MOD_VERSION_MAJOR = 14
MOD_VERSION_MINOR = 1
MOD_VERSION_INDEV = false
MOD_VERSION_STRING = tostring(MOD_VERSION_API) .. "." .. tostring(MOD_VERSION_MAJOR) .. (MOD_VERSION_MINOR > 0 and ("." .. tostring(MOD_VERSION_MINOR)) or "") .. (MOD_VERSION_INDEV and " (In-Dev)" or "")
MOD_VERSION_DEBUG = tostring(GITHUB_REPO) .. " | " .. tostring(GITHUB_COMMIT_ID) .. " | " .. tostring(GITHUB_COMMIT_TIME)

if VERSION_NUMBER < 38 then
    djui_popup_create("\n\\#FFAAAA\\Character Select requires\n the latest version of CoopDX to use!\n\nYou can find CoopDX here:\n\\#6666FF\\https://sm64coopdx.com", 5)
    incompatibleClient = true
    return 0
end

local dependacyFiles = {
    -- Required Lua File
    --"a-github.lua",
    "dialog.lua",
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

local fileErrorList = {}

-- Check for Missing Files
for i = 1, #dependacyFiles do
    if not mod_file_exists(dependacyFiles[i]) then
        log_to_console("Character Select file missing: '" .. dependacyFiles[i] .. "'", CONSOLE_MESSAGE_WARNING)
        table_insert(fileErrorList, "Missing File '" .. dependacyFiles[i] .. "'")
    end
end
-- Check for Legacy Files
for i = 1, #legacyFiles do
    if mod_file_exists(legacyFiles[i]) then
        log_to_console("Character Select legacy file found: '" .. legacyFiles[i] .. "'", CONSOLE_MESSAGE_WARNING)
        table_insert(fileErrorList, "Legacy File '" .. legacyFiles[i] .. "'")
    end
end
if #fileErrorList > 0 then
    incompatibleClient = true
    local frameCount = 0
    hook_event(HOOK_UPDATE, function ()
        frameCount = frameCount + 1
        if frameCount == 5 then
            local errorString = "\\#FFAAAA\\Character Select File Issues:"
            djui_popup_create("\\#FFAAAA\\Character Select is having\nfile issues and cannot load!\n\nErrors have been logged in chat!", 4)
            for i = 1, #fileErrorList do
                errorString = errorString .. "\n" .. fileErrorList[i]
            end
            errorString = errorString .. "\n\nThe best way to resolve these issues is to delete your current version of Character Select and then install the latest version!"
            
            log_to_console(errorString)
            djui_chat_message_create(errorString)
        end
    end)
    return 0
end

ommActive = false
for i in pairs(gActiveMods) do
    if gActiveMods[i].relativePath == "omm-coop" then
        ommActive = true
        break
    end
end

E_MODEL_ARMATURE = smlua_model_util_get_id("armature_geo")

local saveableCharacters = {
    ["1"] = 1,
    ["2"] = 1,
    ["3"] = 1,
    ["4"] = 1,
    ["5"] = 1,
    ["6"] = 1,
    ["7"] = 1,
    ["8"] = 1,
    ["9"] = 1,
    ["0"] = 1,
    ["a"] = 1,
    ["b"] = 1,
    ["c"] = 1,
    ["d"] = 1,
    ["e"] = 1,
    ["f"] = 1,
    ["g"] = 1,
    ["h"] = 1,
    ["i"] = 1,
    ["j"] = 1,
    ["k"] = 1,
    ["l"] = 1,
    ["m"] = 1,
    ["n"] = 1,
    ["o"] = 1,
    ["p"] = 1,
    ["q"] = 1,
    ["r"] = 1,
    ["s"] = 1,
    ["t"] = 1,
    ["u"] = 1,
    ["v"] = 1,
    ["w"] = 1,
    ["x"] = 1,
    ["y"] = 1,
    ["z"] = 1,
    ["_"] = 1,
    ["-"] = 1,
    ["."] = 1,

    -- Replace with Underscore
    [" "] = 0,
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
        if saveableCharacters[string_lower(c)] == 1 then
            s = s .. c
        elseif saveableCharacters[string_lower(c)] == 0 then
            s = s .. "_"
        end
    end
    return s
end

--- @param string string
--- Splits a string into a table by spaces
function string_split(string, splitAt)
    if splitAt == nil then
        splitAt = " "
    end
    local result = {}
    for match in string:gmatch(string_format("[^%s]+", splitAt)) do
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

function lerp(a, b, t)
    return a * (1 - t) + b * t
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
        inMenu = false,
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