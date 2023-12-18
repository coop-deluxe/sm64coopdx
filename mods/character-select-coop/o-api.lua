

local characterVoices = {}

local TEX_UNKNOWN_CHAR = get_texture_info("unknown-icon")

local E_MODEL_ARMATURE = smlua_model_util_get_id("armature_geo")

local table_insert = table.insert
local type = type

---------
-- API --
---------

---@param name string|nil Underscores turn into Spaces
---@param description table|nil {"string"}
---@param credit string|nil
---@param color Color|nil {r, g, b}
---@param modelInfo ModelExtendedId|table|nil Use smlua_model_util_get_id()
---@param forceChar CharacterType|nil CT_MARIO, CT_LUIGI, CT_TOAD, CT_WALUIGI, CT_WARIO
---@param lifeIcon TextureInfo|nil Use get_texture_info()
---@return integer
local character_add = function(name, description, credit, color, modelInfo, forceChar, lifeIcon)
    table_insert(characterTable, {
        name = name and string_space_to_underscore(name) or "Untitled",
        description = description and description or {"No description has been provided"},
        credit = credit and credit or "Unknown",
        color = color and color or menuColorTable[8],
        model = modelInfo and (type(modelInfo) == "table" and modelInfo[1] or modelInfo) or E_MODEL_ARMATURE,
        capModels = type(modelInfo) == "table" and modelInfo[2] or nil,
        forceChar = forceChar and forceChar or CT_MARIO,
        lifeIcon = lifeIcon and lifeIcon or TEX_UNKNOWN_CHAR,
    })
    return #characterTable
end

---@param charNum integer Use _G.charSelect.character_get_number_from_string() or _G.charSelect.character_add()'s return value
---@param name string|nil Underscores turn into Spaces
---@param description table|nil {"string"}
---@param credit string|nil
---@param color Color|nil {r, g, b}
---@param modelInfo ModelExtendedId|integer|table|nil Use smlua_model_util_get_id()
---@param forceChar CharacterType|nil CT_MARIO, CT_LUIGI, CT_TOAD, CT_WALUIGI, CT_WARIO
---@param lifeIcon TextureInfo|nil Use get_texture_info()
local character_edit = function(charNum, name, description, credit, color, modelInfo, forceChar, lifeIcon)
    characterTable[charNum] = characterTable[charNum] and {
        name = name and string_space_to_underscore(name) or characterTable[charNum].name,
        description = description and description or characterTable[charNum].description,
        credit = credit and credit or characterTable[charNum].credit,
        color = color and color or characterTable[charNum].color,
        model = modelInfo and (type(modelInfo) == "table" and modelInfo[1] or modelInfo) or characterTable[charNum].model,
        capModels = type(modelInfo) == "table" and modelInfo[2] or characterTable[charNum].capModels,
        forceChar = forceChar and forceChar or characterTable[charNum].forceChar,
        lifeIcon = lifeIcon and lifeIcon or characterTable[charNum].lifeIcon,
    } or nil
end

---@param modelInfo ModelExtendedId|integer
---@param clips table
local character_add_voice = function(modelInfo, clips)
    characterVoices[modelInfo] = clips
end

---@return table
local character_get_current_table = function ()
    return characterTable[currChar]
end

local character_get_current_model_number = function ()
    return currChar
end

---@param name string
local character_get_number_from_string = function (name)
    for i = 2, #characterTable do
        if characterTable[i].name == name or characterTable[i].name == string_space_to_underscore(name) then
            return i
        end
    end
    return false
end

---@param m MarioState
local character_get_voice = function (m)
    return characterVoices[gPlayerSyncTable[m.playerIndex].modelId]
end

local version_get = function ()
    return modVersion
end

local is_menu_open = function ()
    return menu
end

local hook_allow_menu_open = function (func)
    table.insert(allowMenu, func)
end

local is_options_open = function ()
    return options
end

local optionTableRef = {
    openInputs = 1,
    menuColor = 2,
    anims = 3,
    inputLatency = 4,
    localModels = 5,
    prefToDefault = 6,
}

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
local get_status = function (tableNum)
    return optionTable[tableNum].toggle
end

_G.charSelectExists = true -- Ace
_G.charSelect = {
    character_add = character_add,
    character_edit = character_edit,
    character_add_voice = character_add_voice,
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