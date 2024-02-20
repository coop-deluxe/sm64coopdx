
--- @class CharacterTable
--- @field public name string
--- @field public saveName string
--- @field public description table
--- @field public credit string
--- @field public color Color
--- @field public model ModelExtendedId|integer
--- @field public forceChar CharacterType
--- @field public lifeIcon TextureInfo
--- @field public camScale integer

local characterVoices = {}
local saveNameTable = {}

local E_MODEL_ARMATURE = smlua_model_util_get_id("armature_geo")

local table_insert = table.insert
local type = type

local function split_text_into_lines(text)
    local words = {}
    for word in text:gmatch("%S+") do
        table.insert(words, word)
    end

    local lines = {}
    local currentLine = ""
    for i, word in ipairs(words) do
        local measuredWidth = djui_hud_measure_text(currentLine .. " " .. word)*0.3
        if measuredWidth <= 100 then
            currentLine = currentLine .. " " .. word
        else
            table.insert(lines, currentLine)
            currentLine = word
        end
    end
    table.insert(lines, currentLine) -- add the last line

    return lines
end

---------
-- API --
---------

---@param name string|nil Underscores turn into Spaces
---@param description table|string|nil {"string"}
---@param credit string|nil
---@param color Color|nil {r, g, b}
---@param modelInfo ModelExtendedId|integer|nil Use smlua_model_util_get_id()
---@param forceChar CharacterType|nil CT_MARIO, CT_LUIGI, CT_TOAD, CT_WALUIGI, CT_WARIO
---@param lifeIcon TextureInfo|nil Use get_texture_info()
---@param camScale integer|nil Zooms the camera based on a multiplier (Default 1.0)
---@return integer
local function character_add(name, description, credit, color, modelInfo, forceChar, lifeIcon, camScale)
    if type(description) == "string" then
        description = split_text_into_lines(description)
    end
    table_insert(characterTable, {
        name = name and name or "Untitled",
        saveName = name and string_space_to_underscore(name) or "Untitled",
        description = description and description or {"No description has been provided"},
        credit = credit and credit or "Unknown",
        color = color and color or {r = 255, g = 255, b = 255},
        model = modelInfo and modelInfo or E_MODEL_ARMATURE,
        forceChar = forceChar and forceChar or CT_MARIO,
        lifeIcon = lifeIcon and lifeIcon or nil,
        camScale = camScale and camScale or 1
    })
    saveNameTable[#characterTable] = characterTable[#characterTable].saveName
    return #characterTable
end

---@param charNum integer Use _G.charSelect.character_get_number_from_string() or _G.charSelect.character_add()'s return value
---@param name string|nil Underscores turn into Spaces
---@param description table|string|nil {"string"}
---@param credit string|nil
---@param color Color|nil {r, g, b}
---@param modelInfo ModelExtendedId|integer|nil Use smlua_model_util_get_id()
---@param forceChar CharacterType|nil CT_MARIO, CT_LUIGI, CT_TOAD, CT_WALUIGI, CT_WARIO
---@param lifeIcon TextureInfo|nil Use get_texture_info()
---@param camScale integer|nil Zooms the camera based on a multiplier (Default 1.0)
local function character_edit(charNum, name, description, credit, color, modelInfo, forceChar, lifeIcon, camScale)
    if type(description) == "string" then
        description = split_text_into_lines(description)
    end
    characterTable[charNum] = characterTable[charNum] and {
        name = name and name or characterTable[charNum].name,
        saveName = saveNameTable[charNum],
        description = description and description or characterTable[charNum].description,
        credit = credit and credit or characterTable[charNum].credit,
        color = color and color or characterTable[charNum].color,
        model = modelInfo and modelInfo or characterTable[charNum].model,
        forceChar = forceChar and forceChar or characterTable[charNum].forceChar,
        lifeIcon = lifeIcon and lifeIcon or characterTable[charNum].lifeIcon,
        camScale = camScale and camScale or 1
    } or nil
end

---@param modelInfo ModelExtendedId|integer
---@param clips table
local function character_add_voice(modelInfo, clips)
    characterVoices[modelInfo] = clips
end

---@param modelInfo ModelExtendedId|integer
---@param caps table
local function character_add_caps(modelInfo, caps)
    characterCaps[modelInfo] = caps
end

---@return CharacterTable
local function character_get_current_table()
    return characterTable[currChar]
end

local function character_get_current_model_number()
    return currChar
end

---@param name string
local function character_get_number_from_string(name)
    for i = 2, #characterTable do
        if characterTable[i].name == name or characterTable[i].name == string_space_to_underscore(name) then
            return i
        end
    end
    return nil
end

---@param m MarioState
local function character_get_voice(m)
    return characterVoices[gPlayerSyncTable[m.playerIndex].modelId]
end

local function version_get()
    return modVersion
end

local function is_menu_open()
    return menuAndTransition
end

local function hook_allow_menu_open(func)
    table_insert(allowMenu, func)
end

local function is_options_open()
    return options
end

local controller = {
    buttonDown = 0,
    buttonPressed = 0,
    extStickX = 0,
    extStickY = 0,
    rawStickX = 0,
    rawStickY = 0,
    stickMag = 0,
    stickX = 0,
    stickY = 0
}

---@param tableNum integer
local function get_status(tableNum)
    return optionTable[tableNum].toggle
end

_G.charSelectExists = true -- Ace
_G.charSelect = {
    character_add = character_add,
    character_edit = character_edit,
    character_add_voice = character_add_voice,
    character_add_caps = character_add_caps,
    character_get_current_table = character_get_current_table,
    character_get_current_model_number = character_get_current_model_number,
    character_get_number_from_string = character_get_number_from_string,
    character_get_voice = character_get_voice,
    version_get = version_get,
    is_menu_open = is_menu_open,
    hook_allow_menu_open = hook_allow_menu_open,
    is_options_open = is_options_open,
    get_status = get_status,
    optionTableRef = optionTableRef,
    controller = controller,
}