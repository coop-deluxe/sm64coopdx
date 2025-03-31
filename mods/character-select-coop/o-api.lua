if incompatibleClient then return 0 end

-- localize functions to improve performance - o-api.lua
local table_insert,djui_hud_measure_text,smlua_model_util_get_id,type,tonumber = table.insert,djui_hud_measure_text,smlua_model_util_get_id,type,tonumber

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

---@ignore
local function split_text_into_lines(text)
    local words = {}
    for word in text:gmatch("%S+") do
        table_insert(words, word)
    end

    local lines = {}
    local currentLine = ""
    for i, word in ipairs(words) do
        local measuredWidth = djui_hud_measure_text(currentLine .. " " .. word)*0.3
        if measuredWidth <= 100 then
            currentLine = currentLine .. " " .. word
        else
            table_insert(lines, currentLine)
            currentLine = word
        end
    end
    table_insert(lines, currentLine) -- add the last line

    return lines
end

local TYPE_INTEGER = "number"
local TYPE_STRING = "string"
local TYPE_TABLE = "table"
local TYPE_TEX_INFO = "userdata"
local TYPE_FUNCTION = "function"

---@description A function that adds a Character to the Character Table
---@param name string|nil `"Custom Model"`
---@param description table|string|nil `{"string"}`
---@param credit string|nil `"You!"`, Credit the creators
---@param color Color|string|nil `{r, g, b}`
---@param modelInfo ModelExtendedId|integer|nil Use `smlua_model_util_get_id`
---@param forceChar CharacterType|nil Character Type, such as `CT_MARIO`
---@param lifeIcon TextureInfo|string|nil Use get_texture_info
---@param camScale integer|nil Zooms the camera based on a multiplier (Default `1`)
---@return integer --The index of the character in the character table
local function character_add(name, description, credit, color, modelInfo, forceChar, lifeIcon, camScale)
    if type(description) == TYPE_STRING then
        description = split_text_into_lines(description)
    end
    if color ~= nil and type(color) == TYPE_STRING then
        color = {r = tonumber(color:sub(1,2), 16), g = tonumber(color:sub(3,4), 16), b = tonumber(color:sub(5,6), 16) }
    end
    if lifeIcon ~= nil and type(lifeIcon) == TYPE_STRING then
        lifeIcon = lifeIcon:sub(1,1)
    end
    local addedModel = (modelInfo and modelInfo ~= E_MODEL_ERROR_MODEL) and modelInfo or E_MODEL_ARMATURE
    table_insert(characterTable, {
        saveName = type(name) == TYPE_STRING and string_space_to_underscore(name) or "Untitled",
        currAlt = 1,
        hasMoveset = false,
        locked = false,
        [1] = {
            name = type(name) == TYPE_STRING and name or "Untitled",
            description = type(description) == TYPE_TABLE and description or {"No description has been provided"},
            credit = type(credit) == TYPE_STRING and credit or "Unknown",
            color = type(color) == TYPE_TABLE and color or {r = 255, g = 255, b = 255},
            model = addedModel,
            ogModel = addedModel,
            forceChar = forceChar and forceChar or CT_MARIO,
            lifeIcon = (type(lifeIcon) == TYPE_TABLE or type(lifeIcon) == TYPE_TEX_INFO or type(lifeIcon) == TYPE_STRING) and lifeIcon or "?",
            starIcon = gTextures.star,
            camScale = type(camScale) == TYPE_INTEGER and camScale or 1,
            healthTexture = nil,
        },
    })
    saveNameTable[#characterTable] = characterTable[#characterTable].saveName
    characterMovesets[#characterTable] = {}
    return #characterTable
end

---@description A function that adds a Costume to an Existing Character, all inputs mimic character_edit
---@param charNum integer The number/table position of the Character you want to add a costume to
---@param name string|nil `"Custom Model"`
---@param description table|string|nil `{"string"}`
---@param credit string|nil `"You!"`, Credit the creators
---@param color Color|string|nil `{r, g, b}`
---@param modelInfo ModelExtendedId|integer|nil Use `smlua_model_util_get_id`
---@param forceChar CharacterType|nil Character Type, such as `CT_MARIO`
---@param lifeIcon TextureInfo|string|nil Use get_texture_info
---@param camScale integer|nil Zooms the camera based on a multiplier (Default `1`)
---@return integer --The index of the costume in the character's table
local function character_add_costume(charNum, name, description, credit, color, modelInfo, forceChar, lifeIcon, camScale)
    if tonumber(charNum) == nil or charNum > #characterTable or charNum < 0 then return end
    if type(description) == TYPE_STRING then
        description = split_text_into_lines(description)
    end
    if type(color) == TYPE_STRING then
        color = {r = tonumber(color:sub(1,2), 16), g = tonumber(color:sub(3,4), 16), b = tonumber(color:sub(5,6), 16) }
    end
    if lifeIcon ~= nil and type(lifeIcon) == TYPE_STRING then
        lifeIcon = lifeIcon:sub(1,1)
    end
    local addedModel = (modelInfo and modelInfo ~= E_MODEL_ERROR_MODEL) and modelInfo or tableCache.model
    local tableCache = characterTable[charNum][1]
    table_insert(characterTable[charNum], {
        name = type(name) == TYPE_STRING and name or tableCache.name,
        description = type(description) == TYPE_TABLE and description or tableCache.description,
        credit = type(credit) == TYPE_STRING and credit or tableCache.credit,
        color = type(color) == TYPE_TABLE and color or tableCache.color,
        model = addedModel,
        ogModel = addedModel,
        forceChar = type(forceChar) == TYPE_INTEGER and forceChar or tableCache.forceChar,
        lifeIcon = (type(lifeIcon) == TYPE_TABLE or type(lifeIcon) == TYPE_TEX_INFO or type(lifeIcon) == TYPE_STRING) and lifeIcon or tableCache.lifeIcon,
        starIcon = tableCache.starIcon, -- Done to prevent it getting lost in the sauce
        camScale = type(camScale) == TYPE_INTEGER and camScale or tableCache.camScale,
        healthTexture = tableCache.healthTexture,
    })
    return #characterTable[charNum]
end

---@description A function that Edits an existing Costume
---@param charNum integer The number/table position of the Character you want to edit the costume of
---@param charAlt integer The number/table position of the Costume you want to edit, this can be found by making a variable equal
---@param name string|nil `"Custom Model"`
---@param description table|string|nil `{"string"}`
---@param credit string|nil `"You!"`, Credit the creators
---@param color Color|string|nil `{r, g, b}`
---@param modelInfo ModelExtendedId|integer|nil Use `smlua_model_util_get_id`
---@param forceChar CharacterType|nil Character Type, such as `CT_MARIO`
---@param lifeIcon TextureInfo|string|nil Use get_texture_info
---@param camScale integer|nil Zooms the camera based on a multiplier (Default `1`)
local function character_edit_costume(charNum, charAlt, name, description, credit, color, modelInfo, forceChar, lifeIcon, camScale)
    if tonumber(charNum) == nil or charNum > #characterTable or charNum < 0 then return end
    if type(description) == TYPE_STRING then
        description = split_text_into_lines(description)
    end
    if type(color) == TYPE_STRING then
        color = {r = tonumber(color:sub(1,2), 16), g = tonumber(color:sub(3,4), 16), b = tonumber(color:sub(5,6), 16) }
    end
    if lifeIcon ~= nil and type(lifeIcon) == TYPE_STRING then
        lifeIcon = lifeIcon:sub(1,1)
    end
    local tableCache = characterTable[charNum][charAlt]
    characterTable[charNum][charAlt] = characterTable[charNum][charAlt] and {
        name = type(name) == TYPE_STRING and name or tableCache.name,
        saveName = saveNameTable[charNum],
        description = type(description) == TYPE_TABLE and description or tableCache.description,
        credit = type(credit) == TYPE_STRING and credit or tableCache.credit,
        color = type(color) == TYPE_TABLE and color or tableCache.color,
        model = (modelInfo and modelInfo ~= E_MODEL_ERROR_MODEL) and modelInfo or tableCache.model,
        ogModel = tableCache.ogModel,
        forceChar = type(forceChar) == TYPE_INTEGER and forceChar or tableCache.forceChar,
        lifeIcon = (type(lifeIcon) == TYPE_TABLE or type(lifeIcon) == TYPE_TEX_INFO or type(lifeIcon) == TYPE_STRING) and lifeIcon or tableCache.lifeIcon,
        starIcon = tableCache.starIcon, -- Done to prevent it getting lost in the sauce
        camScale = type(camScale) == TYPE_INTEGER and camScale or tableCache.camScale,
        healthTexture = tableCache.healthTexture,
    } or nil

    local ccp = characterColorPresets
    if modelInfo ~= nil and ccp[modelInfo] ~= nil and ccp[tableCache.model] ~= nil and ccp[modelInfo].currPalette <= ccp[tableCache.model].currPalette then
        ccp[modelInfo].currPalette = ccp[tableCache.model].currPalette
    end
end

---@description A function that Edits an Existing Character
---@param charNum integer The number/table position of the Character you want to edit
---@param name string|nil `"Custom Model"`
---@param description table|string|nil `{"string"}`
---@param credit string|nil `"You!"`, Credit the creators
---@param color Color|string|nil `{r, g, b}`
---@param modelInfo ModelExtendedId|integer|nil Use `smlua_model_util_get_id`
---@param forceChar CharacterType|nil Character Type, such as `CT_MARIO`
---@param lifeIcon TextureInfo|string|nil Use get_texture_info
---@param camScale integer|nil Zooms the camera based on a multiplier (Default `1`)
local function character_edit(charNum, name, description, credit, color, modelInfo, forceChar, lifeIcon, camScale)
    character_edit_costume(charNum, 1, name, description, credit, color, modelInfo, forceChar, lifeIcon, camScale)
end

---@description A function that adds a voice table to a character
---@param modelInfo ModelExtendedId|integer Model Information Received from smlua_model_util_get_id
---@param clips table A Table with your Character's Sound File Names
---@note ```lua
---@note local VOICETABLE_CHAR = {
---@note [CHAR_SOUND_ATTACKED] = 'NES-Hit.ogg',
---@note [CHAR_SOUND_DOH] = 'NES-Bump.ogg',
---@note [CHAR_SOUND_DROWNING] = 'NES-Die.ogg',
---@note [CHAR_SOUND_DYING] = 'NES-Die.ogg',
---@note [CHAR_SOUND_GROUND_POUND_WAH] = 'NES-Squish.ogg',
---@note [CHAR_SOUND_HAHA] = 'NES-1up.ogg',
---@note [CHAR_SOUND_HAHA_2] = 'NES-1up.ogg',
---@note [CHAR_SOUND_HERE_WE_GO] = 'NES-Flagpole.ogg',
---@note [CHAR_SOUND_HOOHOO] = 'NES-Jump.ogg',
---@note [CHAR_SOUND_MAMA_MIA] = 'NES-Warp.ogg',
---@note [CHAR_SOUND_OKEY_DOKEY] = 'NES-1up.ogg',
---@note [CHAR_SOUND_ON_FIRE] = 'NES-Enemy_Fire.ogg',
---@note [CHAR_SOUND_OOOF] = 'NES-Hit.ogg',
---@note [CHAR_SOUND_OOOF2] = 'NES-Hit.ogg',
---@note [CHAR_SOUND_PUNCH_HOO] = 'NES-Kick.ogg',
---@note [CHAR_SOUND_PUNCH_WAH] = 'NES-Thwomp.ogg',
---@note [CHAR_SOUND_PUNCH_YAH] = 'NES-Thwomp.ogg',
---@note [CHAR_SOUND_SO_LONGA_BOWSER] = 'NES-Bowser_Die.ogg',
---@note [CHAR_SOUND_TWIRL_BOUNCE] = 'NES-Item.ogg',
---@note [CHAR_SOUND_WAAAOOOW] = 'NES-Vine.ogg',
---@note [CHAR_SOUND_WAH2] = 'NES-Kick.ogg',
---@note [CHAR_SOUND_WHOA] = 'NES-Item.ogg',
---@note [CHAR_SOUND_YAHOO] = 'NES-Jump.ogg',
---@note [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = 'NES-Jump.ogg',
---@note [CHAR_SOUND_YAH_WAH_HOO] = 'NES-Big_Jump.ogg',
---@note [CHAR_SOUND_YAWNING] = 'NES-Pause.ogg',
---@note }
---@note ```
local function character_add_voice(modelInfo, clips)
    characterVoices[modelInfo] = type(clips) == TYPE_TABLE and clips or nil
end

---@description A function that adds a caps table to a character
---@param modelInfo ModelExtendedId|integer Model Information Received from smlua_model_util_get_id
---@param caps table Cap 
---@note ```lua
---@note local CAPTABLE_CHAR = {
---@note normal = smlua_model_util_get_id("custom_model_cap_normal_geo"),
---@note wing = smlua_model_util_get_id("custom_model_cap_wing_geo"),
---@note metal = smlua_model_util_get_id("custom_model_cap_metal_geo"),
---@note metalWing = smlua_model_util_get_id("custom_model_cap_wing_geo")
---@note }
---@note ```
local function character_add_caps(modelInfo, caps)
    characterCaps[modelInfo] = type(caps) == TYPE_TABLE and caps or nil
end

---@description A function that gets a model's cap table
---@param modelInfo ModelExtendedId|integer|nil Model Information Received from smlua_model_util_get_id
local function character_get_caps(modelInfo)
    if modelInfo == nil then modelInfo = characterTable[currChar][characterTable[currChar].currAlt].model end
    return characterCaps[modelInfo]
end

---@description A function that adds health meter textures to a character
---@param charNum integer The number/table position of the Character you want to add a meter to
---@param charAlt integer The number/table position of the Costume you want to add a meter to
---@param healthTexture table|nil A Table with your Character's Health Textures (Table Shown in character_add_health_meter)
local function character_add_costume_health_meter(charNum, charAlt, healthTexture)
    if type(charNum) ~= TYPE_INTEGER or charNum == nil then return end
    if type(charAlt) ~= TYPE_INTEGER or charAlt == nil then return end
    characterTable[charNum][charAlt].healthTexture = type(healthTexture) == TYPE_TABLE and healthTexture or nil
end

---@description A function that adds health meter textures to a character
---@param charNum integer The number/table position of the Character you want to add a meter to
---@param healthTexture table|nil A Table with your Character's Health Textures (Table Shown Below)
---@note ```lua
---@note local HEALTH_METER_CHAR = {
---@note     label = {
---@note         left = get_texture_info("hp-back-left"),
---@note         right = get_texture_info("hp-back-right"),
---@note     },
---@note     pie = {
---@note         [1] = get_texture_info("hp-pie-1"),
---@note         [2] = get_texture_info("hp-pie-2"),
---@note         [3] = get_texture_info("hp-pie-3"),
---@note         [4] = get_texture_info("hp-pie-4"),
---@note         [5] = get_texture_info("hp-pie-5"),
---@note         [6] = get_texture_info("hp-pie-6"),
---@note         [7] = get_texture_info("hp-pie-7"),
---@note         [8] = get_texture_info("hp-pie-8"),
---@note     }
---@note }
---@note ```
---@note This method is restricted to the default meter format, you can refer to the Disassembled sections in the image below for how to format your health meter (Spriters Resource Page)
---@note <p align=center> <img src="https://www.spriters-resource.com/resources/sheets/7/6841.png?updated=1595395218" width="720"> </p>
local function character_add_health_meter(charNum, healthTexture)
    character_add_costume_health_meter(charNum, 1, healthTexture)
end

---@param charNum integer
---@param charAlt integer
---@param courseTexture table|nil
local function character_add_costume_course(charNum, charAlt, courseTexture)
    if type(charNum) ~= TYPE_INTEGER or charNum == nil then return end
    if type(charAlt) ~= TYPE_INTEGER or charAlt == nil then return end
    characterTable[charNum][charAlt].courseTexture = type(courseTexture) == TYPE_TABLE and courseTexture or nil
end

---@description A function that adds a custom texture to the star select
---@param charNum integer The number/table position of the Character you want to add a course texture to
---@param courseTexture table|nil
local function character_add_course(charNum, courseTexture)
    character_add_costume_course(charNum, 1, courseTexture)
end

---@description A function that adds a celebration star model to a character
---@param modelInfo ModelExtendedId|integer Model Information Received from smlua_model_util_get_id()	
---@param starModel ModelExtendedId|integer Model Information Received from smlua_model_util_get_id()	
---@param starIcon TextureInfo|nil Texture Information Received from get_texture_info()
local function character_add_celebration_star(modelInfo, starModel, starIcon)
    characterCelebrationStar[modelInfo] = starModel
    for i = 2, #characterTable do
        for a = 1, #characterTable[i] do 
            if characterTable[i][a].model == modelInfo then
                characterTable[i][a].starIcon = type(starIcon) == TYPE_TABLE and starIcon or gTextures.star
                return
            end
        end
    end
    return false
end

---@description A function that adds a palette preset to a character
---@param modelInfo ModelExtendedId|integer
---@param paletteTable table
---@note ```lua
---@note local PALETTE_CHAR = {
---@note     [PANTS]  = {r = 0x00, g = 0x00, b = 0xff},
---@note     [SHIRT]  = {r = 0xff, g = 0x00, b = 0x00},
---@note     [GLOVES] = {r = 0xff, g = 0xff, b = 0xff},
---@note     [SHOES]  = {r = 0x72, g = 0x1c, b = 0x0e},
---@note     [HAIR]   = {r = 0x73, g = 0x06, b = 0x00},
---@note     [SKIN]   = {r = 0xfe, g = 0xc1, b = 0x79},
---@note     [CAP]    = {r = 0xff, g = 0x00, b = 0x00},
---@note }
---@note ```
---@note Strings can also be used rather than RGB tables, ex. `[PANTS] = "0000ff"`
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
    if characterColorPresets[modelInfo] == nil then
        characterColorPresets[modelInfo] = {
            currPalette = 1,
        }
    end
    table_insert(characterColorPresets[modelInfo], paletteTableOut)
end

---@param modelInfo ModelExtendedId|integer
---@param animTable table
local function character_add_animations(modelInfo, animTable)
    characterAnims[modelInfo] = type(animTable) == TYPE_TABLE and animTable or nil
end

---@param modelInfo ModelExtendedId|integer
local function character_get_animations(modelInfo)
    return characterAnims[modelInfo]
end

---@param tablePos integer|nil
---@param charAlt integer|nil
---@return CharacterTable
local function character_get_current_table(tablePos, charAlt)
    tablePos = tablePos and tablePos or currChar
    charAlt = charAlt and charAlt or 1
    return characterTable[tablePos][charAlt]
end

---@return table
local function character_get_full_table()
    return characterTable
end

--- @param localIndex integer|nil
--- @return integer|nil
local function character_get_current_number(localIndex)
    if localIndex == nil or localIndex == 0 then
        return currChar
    else
        for i = 1, #characterTable do
            if characterTable[i].saveName == gCSPlayers[localIndex].saveName then
                return i
            end
        end
        return nil
    end
end

--- @param localIndex integer|nil
--- @return integer|nil
local function character_get_current_costume(localIndex)
    if localIndex == nil or localIndex == 0 then
        return characterTable[currChar].currAlt
    else
        for i = 1, #characterTable do
            if characterTable[i].saveName == gCSPlayers[localIndex].saveName then
                return characterTable[i].currAlt
            end
        end
        return nil
    end
end

---@param charNum integer|nil
local function character_set_current_number(charNum)
    if type(charNum) ~= TYPE_INTEGER or characterTable[charNum] == nil then return end
    currChar = charNum
    charBeingSet = true
end

--- @return table|nil
local function character_get_current_palette()
    local model = characterTable[currChar][characterTable[currChar].currAlt].model
    return characterColorPresets[model][gCSPlayers[0].presetPalette]
end

--- @param localIndex integer|nil
--- @return integer|nil
local function character_get_current_palette_number(localIndex)
    if localIndex == nil then localIndex = 0 end
    return gCSPlayers[localIndex].presetPalette
end

---@param name string
local function character_get_number_from_string(name)
    if type(name) ~= TYPE_STRING then return nil end
    for i = 2, #characterTable do
        for a = 1, #characterTable[i] do
            if characterTable[i][a].name == name or characterTable[i][a].name == string_space_to_underscore(name) then
                return i
            end
        end
    end
    return nil
end

---@param m MarioState
function character_get_voice(m)
    return characterVoices[gCSPlayers[m.playerIndex].modelId]
end

---@param charNum integer|nil
---@param unlockCondition function|boolean|nil
---@param notify boolean|nil
local function character_set_locked(charNum, unlockCondition, notify)
    if charNum == nil or charNum > #characterTable or charNum < 2 then return end
    if unlockCondition == nil then unlockCondition = false end
    if notify == nil then notify = true end
    characterTable[charNum].locked = true
    if currChar == charNum then
        currChar = 1
    end
    characterUnlock[charNum] = {
        check = unlockCondition,
        notif = notify,
    }
end

---@return string
local function version_get()
    return MOD_VERSION_STRING
end

---@return table
local function version_get_full()
    return {
        api = MOD_VERSION_API,
        major = MOD_VERSION_MAJOR,
        minor = MOD_VERSION_MINOR,
        indev = MOD_VERSION_INDEV
    }
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

---@param charNum integer|nil
---@param hookEventType LuaHookedEventType|integer
---@param func function
local function character_hook_moveset(charNum, hookEventType, func)
    if charNum > #characterTable then return end
    if type(func) ~= TYPE_FUNCTION then return end
    characterMovesets[charNum][hookEventType] = func
    characterTable[charNum].hasMoveset = true
end

---@param charNum integer
local function character_get_moveset(charNum)
    return characterMovesets[charNum]
end

---@return boolean
local function is_options_open()
    return options
end

---@param modName string
---@param creditTo string Who did the thing
---@param creditFor string What did they do
local function credit_add(modName, creditTo, creditFor)
    if #creditTable > 1 then
        for i = 2, #creditTable do
            if modName == creditTable[i].packName then
                table_insert(creditTable[i], {creditTo = creditTo, creditFor = creditFor})
                return
            end
        end
    end
    local i = #creditTable + 1
    creditTable[i] = {
        packName = modName
    }
    table_insert(creditTable[i], {creditTo = creditTo, creditFor = creditFor})
end

---@param bool boolean
local function restrict_palettes(bool)
    if bool == nil then bool = true end
    stopPalettes = bool
end

---@param bool boolean
local function restrict_movesets(bool)
    if bool == nil then bool = true end
    stopMovesets = bool
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
    character_add_costume = character_add_costume,
    character_edit = character_edit,
    character_edit_costume = character_edit_costume,
    character_add_voice = character_add_voice,
    character_add_caps = character_add_caps,
    character_get_caps = character_get_caps,
    character_add_celebration_star = character_add_celebration_star,
    character_add_health_meter = character_add_health_meter,
    character_add_costume_health_meter = character_add_costume_health_meter,
    character_add_course_texture = character_add_course,
    character_add_costume_course_texture = character_add_costume_course,
    character_add_palette_preset = character_add_palette_preset,
    character_add_animations = character_add_animations,
    character_get_animations = character_get_animations,
    character_get_current_table = character_get_current_table,
    character_get_full_table = character_get_full_table,
    character_get_current_number = character_get_current_number,
    character_get_current_costume = character_get_current_costume,
    character_get_current_model_number = character_get_current_number, -- Outdated function name, Not recommended for use
    character_set_current_number = character_set_current_number,
    character_get_current_palette = character_get_current_palette,
    character_get_current_palette_number = character_get_current_palette_number,
    character_get_number_from_string = character_get_number_from_string,
    character_get_voice = character_get_voice,
    character_get_life_icon = life_icon_from_local_index, -- Function located in n-hud.lua
    character_render_life_icon = render_life_icon_from_local_index, -- Function located in n-hud.lua
    character_render_life_icon_interpolated = render_life_icon_from_local_index_interpolated, -- Function located in n-hud.lua
    character_get_star_icon = star_icon_from_local_index, -- Function located in n-hud.lua
    character_render_star_icon = render_star_icon_from_local_index, -- Function located in n-hud.lua
    character_render_star_icon_interpolated = render_star_icon_from_local_index_interpolated, -- Function located in n-hud.lua
    character_get_health_meter = health_meter_from_local_index, -- Function located in n-hud.lua
    character_render_health_meter = render_health_meter_from_local_index, -- Function located in n-hud.lua
    character_set_locked = character_set_locked,
    character_get_moveset = character_get_moveset,

    -- Hud Element Functions --
    hud_hide_element = hud_hide_element,
    hud_show_element = hud_show_element,
    hud_get_element = hud_get_element,

    -- Menu Functions --
    header_set_texture = header_set_texture, -- Function located in main.lua
    version_get = version_get,
    version_get_full = version_get_full,
    is_menu_open = is_menu_open,
    set_menu_open = set_menu_open,
    is_options_open = is_options_open,
    get_menu_color = get_menu_color,
    add_option = add_option,
    get_option = get_option,
    get_options_status = get_options_status,
    set_options_status = set_options_status,
    credit_add = credit_add,
    restrict_palettes = restrict_palettes,
    restrict_movesets = restrict_movesets,

    -- Misc --
    dialog_set_replace_name = dialog_set_replace_name, -- Function located in dialog.lua

    -- Tables & Variables --
    optionTableRef = optionTableRef,
    controller = controller,
    gCSPlayers = gCSPlayers,
    CUTSCENE_CS_MENU = CUTSCENE_CS_MENU,

    -- Custom Hooks --
    hook_allow_menu_open = hook_allow_menu_open,
    hook_render_in_menu = hook_render_in_menu,
    character_hook_moveset = character_hook_moveset,
}