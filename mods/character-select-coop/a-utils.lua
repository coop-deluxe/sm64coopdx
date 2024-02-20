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

function string_underscore_to_space(string)
    local s = ''
    for i = 1, #string do
        local c = string:sub(i,i)
        if c ~= '_' then
            s = s .. c
        else
            s = s .. " "
        end
    end
    return s
end

function string_space_to_underscore(string)
    local s = ''
    for i = 1, #string do
        local c = string:sub(i,i)
        if saveableCharacters[string.lower(c)] then
            s = s .. c
        elseif saveableCharacters[string.lower(c)] ~= nil then
            s = s .. "_"
        end
    end
    return s
end

function string_split(s)
    local result = {}
    for match in (s):gmatch(string.format("[^%s]+", " ")) do
        table.insert(result, match)
    end
    return result
end

client_is_coop_dx = get_coop_compatibility_enabled ~= nil -- Checks if Client is DX
-- network_is_coop_dx = SM64COOPDX_VERSION ~= nil -- Checks if Coop Compatibility is Off (As of now unused)

ommActive = false
for i in pairs(gActiveMods) do
    local name = gActiveMods[i].name
    if (name:find("OMM Rebirth")) then
        ommActive = true
    end
end

modVersion = "1.6.1"

allowMenu = {}
