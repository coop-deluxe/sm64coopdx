
if incompatibleClient then return 0 end

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
--- @field public offset integer

-- localize functions to improve performance
local smlua_model_util_get_id,table_insert,type,djui_hud_measure_text,tonumber = smlua_model_util_get_id,table.insert,type,djui_hud_measure_text,tonumber

local characterVoices = {}
local saveNameTable = {}

local E_MODEL_ARMATURE = smlua_model_util_get_id("armature_geo")

---------
-- API --
---------

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

local TYPE_INTEGER = "number"
local TYPE_STRING = "string"
local TYPE_TABLE = "table"
local TYPE_FUNCTION = "function"

---@param name string|nil Underscores turn into Spaces
---@param description table|string|nil {"string"}
---@param credit string|nil
---@param color Color|string|nil {r, g, b}
---@param modelInfo ModelExtendedId|integer|nil Use smlua_model_util_get_id()
---@param forceChar CharacterType|nil CT_MARIO, CT_LUIGI, CT_TOAD, CT_WALUIGI, CT_WARIO
---@param lifeIcon TextureInfo|nil Use get_texture_info()
---@param camScale integer|nil Zooms the camera based on a multiplier (Default 1.0)
---@param offset integer|nil Visually offsets the character
---@return integer
local function character_add(name, description, credit, color, modelInfo, forceChar, lifeIcon, camScale, offset)
    if type(description) == TYPE_STRING then
        description = split_text_into_lines(description)
    end
    if type(color) == TYPE_STRING then
        color = {r = tonumber(color:sub(1,2), 16), g = tonumber(color:sub(3,4), 16), b = tonumber(color:sub(5,6), 16) }
    end
    if type(offset) ~= TYPE_INTEGER then
        offset = (forceChar == CT_WALUIGI and 25 or 0)
    end
    table_insert(characterTable, {
        name = type(name) == TYPE_STRING and name or "Untitled",
        saveName = type(name) == TYPE_STRING and string_space_to_underscore(name) or "Untitled",
        description = type(description) == TYPE_TABLE and description or {"No description has been provided"},
        credit = type(credit) == TYPE_STRING and credit or "Unknown",
        color = type(color) == TYPE_TABLE and color or {r = 255, g = 255, b = 255},
        model = (modelInfo and modelInfo ~= E_MODEL_ERROR_MODEL) and modelInfo or E_MODEL_ARMATURE,
        forceChar = forceChar and forceChar or CT_MARIO,
        offset = offset and offset or 0,
        lifeIcon = type(lifeIcon) == TYPE_TABLE and lifeIcon or nil,
        starIcon = gTextures.star,
        camScale = type(camScale) == TYPE_INTEGER and camScale or 1,
        healthTexture = nil,
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
---@param forceChar integer|CharacterType|nil CT_MARIO, CT_LUIGI, CT_TOAD, CT_WALUIGI, CT_WARIO
---@param lifeIcon TextureInfo|nil Use get_texture_info()
---@param camScale integer|nil Zooms the camera based on a multiplier (Default 1.0)
---@param offset integer|nil Visually offsets the character
local function character_edit(charNum, name, description, credit, color, modelInfo, forceChar, lifeIcon, camScale, offset)
    if tonumber(charNum) == nil or charNum > #characterTable or charNum < 0 then return end
    if type(description) == TYPE_STRING then
        description = split_text_into_lines(description)
    end
    if type(color) == TYPE_STRING then
        color = {r = tonumber(color:sub(1,2), 16), g = tonumber(color:sub(3,4), 16), b = tonumber(color:sub(5,6), 16) }
    end
    if type(offset) ~= TYPE_INTEGER then
        offset = (forceChar == CT_WALUIGI and 25 or 0)
    end
    local tableCache = characterTable[charNum]
    characterTable[charNum] = characterTable[charNum] and {
        name = type(name) == TYPE_STRING and name or tableCache.name,
        saveName = saveNameTable[charNum],
        description = type(description) == TYPE_TABLE and description or tableCache.description,
        credit = type(credit) == TYPE_STRING and credit or tableCache.credit,
        color = type(color) == TYPE_TABLE and color or tableCache.color,
        model = (modelInfo and modelInfo ~= E_MODEL_ERROR_MODEL) and modelInfo or tableCache.model,
        forceChar = type(forceChar) == TYPE_INTEGER and forceChar or tableCache.forceChar,
        offset = type(offset) == TYPE_INTEGER and offset or tableCache.offset,
        lifeIcon = type(lifeIcon) == TYPE_TABLE and lifeIcon or tableCache.lifeIcon,
        starIcon = tableCache.starIcon, -- Done to prevent it getting lost in the sauce
        camScale = type(camScale) == TYPE_INTEGER and camScale or tableCache.camScale,
        healthTexture = tableCache.healthTexture,
    } or nil
end

---@param modelInfo ModelExtendedId|integer
---@param clips table
local function character_add_voice(modelInfo, clips)
    characterVoices[modelInfo] = type(clips) == TYPE_TABLE and clips or nil
end

---@param modelInfo ModelExtendedId|integer
---@param caps table
local function character_add_caps(modelInfo, caps)
    characterCaps[modelInfo] = type(caps) == TYPE_TABLE and caps or nil
end

---@param charNum integer
---@param healthTexture table|nil
local function character_add_health_meter(charNum, healthTexture)
    if type(charNum) ~= TYPE_INTEGER or charNum == nil then return end
    characterTable[charNum].healthTexture = type(healthTexture) == TYPE_TABLE and healthTexture or nil
    return false
end

---@param modelInfo ModelExtendedId|integer
---@param starModel ModelExtendedId|integer 
---@param starIcon TextureInfo|nil Use get_texture_info()
local function character_add_celebration_star(modelInfo, starModel, starIcon)
    characterCelebrationStar[modelInfo] = starModel
    for i = 2, #characterTable do
        if characterTable[i].model == modelInfo then
            characterTable[i].starIcon = type(starIcon) == TYPE_TABLE and starIcon or gTextures.star
            return
        end
    end
    return false
end

---@param modelInfo ModelExtendedId|integer
---@param paletteTable table 
local function character_add_palette_preset(modelInfo, paletteTable)
    local paletteTableOut = {}
    local defaultColors = characterColorPresets[E_MODEL_MARIO]
    for i = 0, 7 do
        local color = paletteTable[i]
        paletteTableOut[i] = {r = 0, g = 0, b = 0}
        if type(color) == TYPE_STRING then
            paletteTableOut[i].r = tonumber(color:sub(1,2), 16) and tonumber(color:sub(1,2), 16) or defaultColors[i].r
            paletteTableOut[i].g = tonumber(color:sub(3,4), 16) and tonumber(color:sub(3,4), 16) or defaultColors[i].g
            paletteTableOut[i].b = tonumber(color:sub(5,6), 16) and tonumber(color:sub(5,6), 16) or defaultColors[i].b
        end
        if type(color) == TYPE_TABLE then
            paletteTableOut[i].r = (type(color) == TYPE_TABLE and color.r ~= nil) and color.r or defaultColors[i].r
            paletteTableOut[i].g = (type(color) == TYPE_TABLE and color.g ~= nil) and color.g or defaultColors[i].g
            paletteTableOut[i].b = (type(color) == TYPE_TABLE and color.b ~= nil) and color.b or defaultColors[i].b
        end
    end
    characterColorPresets[modelInfo] = paletteTableOut
end

---@param tablePos integer|nil
---@return CharacterTable
local function character_get_current_table(tablePos)
    tablePos = tablePos and tablePos or currChar
    return characterTable[tablePos]
end

local function character_get_current_number()
    return currChar
end

---@param charNum integer|nil
local function character_set_current_number(charNum)
    if type(charNum) ~= TYPE_INTEGER or characterTable[charNum] == nil then return end
    currChar = charNum
    charBeingSet = true
end

---@param name string
local function character_get_number_from_string(name)
    if type(name) ~= TYPE_STRING then return nil end
    for i = 2, #characterTable do
        if characterTable[i].name == name or characterTable[i].name == string_space_to_underscore(name) then
            return i
        end
    end
    return nil
end

---@param m MarioState
function character_get_voice(m)
    return characterVoices[gPlayerSyncTable[m.playerIndex].modelId]
end

---@return string
local function version_get()
    return MOD_VERSION
end

---@return boolean
local function is_menu_open()
    return menuAndTransition
end

---@param bool boolean|nil Sets if the menu is open
local function set_menu_open(bool)
    if bool == nil then bool = true end
    menu = bool
end

---@return table
local function get_menu_color()
    return update_menu_color()
end

---@param func function
local function hook_allow_menu_open(func)
    if type(func) ~= TYPE_FUNCTION then return end
    table_insert(allowMenu, func)
end

---@param func function
local function hook_render_in_menu(func, underText)
    if type(func) ~= TYPE_FUNCTION then return end
    if underText then
        table_insert(renderInMenuTable.back, func)
    else
        table_insert(renderInMenuTable.front, func)
    end
end

---@return boolean
local function is_options_open()
    return options
end

---@param bool boolean
local function restrict_palettes(bool)
    if bool == nil then bool = true end
    stopPalettes = bool
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

---@param name string
---@param toggleDefault number|nil Defaults to 0
---@param toggleMax number|nil Defaults to 1
---@param toggleNames table|nil Table of Strings {"Off", "On"}
---@param description table|nil Table of Strings {"This toggle allows your", "character to feel everything."}
---@param save boolean|nil Defaults to true
---@return number
local function add_option(name, toggleDefault, toggleMax, toggleNames, description, save)
    if save == nil then save = true end
    local saveName = string_space_to_underscore(name)
    table_insert(optionTable, {
        name = type(name) == TYPE_STRING and name or "Unknown Toggle",
        toggle = nil, -- Set as nil for Failsafe to Catch
        toggleSaveName = save and saveName or nil,
        toggleDefault = type(toggleDefault) == TYPE_INTEGER and toggleDefault or 0,
        toggleMax = type(toggleMax) == TYPE_INTEGER and toggleMax or 1,
        toggleNames = type(toggleNames) == TYPE_TABLE and toggleNames or {"Off", "On"},
        description = type(description) == TYPE_TABLE and description or {""},
    })
    queueStorageFailsafe = true -- Used variable trigger to not save/load in the external mod
    return #optionTable
end

---@param tableNum integer
---@return table|nil
local function get_option(tableNum)
    if type(tableNum) ~= TYPE_INTEGER then return nil end
    return optionTable[tableNum]
end

---@param tableNum integer
---@return number|nil
local function get_options_status(tableNum)
    if type(tableNum) ~= TYPE_INTEGER then return nil end
    return optionTable[tableNum].toggle
end

---@param tableNum integer
---@param toggle integer
local function set_options_status(tableNum, toggle)
    local currOption = optionTable[tableNum]
    if currOption == nil or type(toggle) ~= TYPE_INTEGER or toggle > currOption.toggleMax or toggle < 1 then return end
    optionTable[tableNum].toggle = toggle
    optionTable[tableNum].optionBeingSet = true
end

_G.charSelectExists = true
_G.charSelect = {
    -- Character Functions --
    character_add = character_add,
    character_edit = character_edit,
    character_add_voice = character_add_voice,
    character_add_caps = character_add_caps,
    character_add_celebration_star = character_add_celebration_star,
    character_add_health_meter = character_add_health_meter,
    character_add_palette_preset = character_add_palette_preset,
    character_get_current_table = character_get_current_table,
    character_get_current_number = character_get_current_number,
    character_get_current_model_number = character_get_current_number, -- Outdated function name, Not recommended for use
    character_set_current_number = character_set_current_number,
    character_get_number_from_string = character_get_number_from_string,
    character_get_voice = character_get_voice,
    character_get_life_icon = life_icon_from_local_index, -- Function located in n-hud.lua
    character_get_star_icon = star_icon_from_local_index, -- Function located in n-hud.lua

    -- Hud Element Functions --
    hud_hide_element = hud_hide_element,
    hud_show_element = hud_show_element,
    hud_get_element = hud_get_element,

    -- Menu Functions --
    header_set_texture = header_set_texture, -- Function located in main.lua
    version_get = version_get,
    is_menu_open = is_menu_open,
    set_menu_open = set_menu_open,
    is_options_open = is_options_open,
    get_menu_color = get_menu_color,
    add_option = add_option,
    get_option = get_option,
    get_options_status = get_options_status,
    set_options_status = set_options_status,
    restrict_palettes = restrict_palettes,

    -- Tables --
    optionTableRef = optionTableRef,
    controller = controller,

    -- Custom Hooks --
    hook_allow_menu_open = hook_allow_menu_open,
    hook_render_in_menu = hook_render_in_menu,
}