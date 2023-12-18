----------------------
-- Global Functions --
----------------------

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
        else
            s = s .. "_"
        end
    end
    return s
end

function version_coop_dx()
    if SM64COOPDX_VERSION then
        return true
    else
        return false
    end
end

----------------------
-- Global Variables --
----------------------

modVersion = "1.5.1"

allowMenu = {}

menuColorTable = {
    {r = 255, g = 50,  b = 50 },
    {r = 255, g = 100, b = 50 },
    {r = 255, g = 255, b = 50 },
    {r = 50,  g = 255, b = 50 },
    {r = 100,  g = 100,  b = 255},
    {r = 251, g = 148, b = 220},
    {r = 130, g = 25,  b = 130},
    {r = 255, g = 255, b = 255},
    {r = 50,  g = 50,  b = 50 },
}
