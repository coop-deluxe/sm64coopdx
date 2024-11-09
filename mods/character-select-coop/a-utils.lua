if VERSION_NUMBER < 37 then
    djui_popup_create("\n\\#FFAAAA\\Character Select requires\n CoopDX v1 or higher use!\n\nYou can find CoopDX here:\n\\#6666FF\\https://sm64coopdx.com", 5)
    incompatibleClient = true
    return 0
end

MOD_VERSION = "1.9.2"

ommActive = false
for i in pairs(gActiveMods) do
    if gActiveMods[i].relativePath == "omm-coop" then
        ommActive = true
        break
    end
end

-- localize functions to improve performance
local string_lower,table_insert = string.lower,table.insert

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
    for match in string:gmatch(string.format("[^%s]+", " ")) do
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
