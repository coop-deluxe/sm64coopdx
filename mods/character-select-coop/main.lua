-- name: Character Select
-- description: \\#ffff00\\ ----- Character Select Coop ----- \n\n\\#dcdcdc\\A Library / API made to make adding and using Custom Characters as simple as possible!\nUse\\#ffff00\\ /char-select\\#dcdcdc\\ to get started!\n\nCreated by:\\#008800\\ Squishy6094\n\\#dcdcdc\\Concepts by:\\#4496f5\\ AngelicMiracles\n\n\\#AAAAFF\\Updates and Packs can be found on\nCharacter Select's Github:\n\\#4444FF\\Squishy6094/character-select-coop


local menu = false
menuAndTransition = false
options = false
currChar = 1
local currOption = 1

local menuCrossFade = 10
local menuCrossFadeCap = menuCrossFade
local menuCrossFadeMath = 255/menuCrossFade

local TEX_HEADER = get_texture_info("char-select-text")

local TEXT_PREF_LOAD = "Default"

local ommActive = _G.OmmApi ~= nil

--[[
    Note: Do NOT add characters via the characterTable below,
    We highly reccomend you create your own mod and use the
    API to add characters, this ensures your pack is easy
    to use for anyone and low on file space!
]]
characterTable = {
    [1]  = {
        name = "Default",
        description = {"The vanilla cast for sm64ex-coop!", "", "These Characters are swappable", "via the default Options Menu"},
        credit = "Nintendo / Coop Team",
        color = {r = 255, g = 50, b = 50},
        model = nil,
        forceChar = nil,
        lifeIcon = gTextures.mario_head,
    },
}

local optionTableRef = {
    openInputs = 1,
    menuColor = 2,
    anims = 3,
    inputLatency = 4,
    localModels = 5,
    prefToDefault = 6,
    debugInfo = 7
}

optionTable = {
    [optionTableRef.openInputs] = {
        name = "Open Binds",
        toggle = tonumber(mod_storage_load("MenuInput")),
        toggleSaveName = "MenuInput",
        toggleDefault = 0,
        toggleMax = 2,
        toggleNames = {"None", ommActive and "D-pad Down + R" or "D-pad Down", "Z (Pause Menu)"},
    },
    [optionTableRef.menuColor] = {
        name = "Menu Color",
        toggle = tonumber(mod_storage_load("MenuColor")),
        toggleSaveName = "MenuColor",
        toggleDefault = 0,
        toggleMax = 9,
        toggleNames = {"Auto", "Red", "Orange", "Yellow", "Green", "Blue", "Pink", "Purple", "White", "Black"},
    },
    [optionTableRef.anims] = {
        name = "Animations",
        toggle = tonumber(mod_storage_load("Anims")),
        toggleSaveName = "Anims",
        toggleDefault = 1,
        toggleMax = 1,
    },
    [optionTableRef.inputLatency] = {
        name = "Scroll Speed",
        toggle = tonumber(mod_storage_load("Latency")),
        toggleSaveName = "Latency",
        toggleDefault = 1,
        toggleMax = 2,
        toggleNames = {"Slow", "Normal", "Fast"},
    },
    [optionTableRef.localModels] = {
        name = "Locally Display Models",
        toggle = tonumber(mod_storage_load("localModels")),
        toggleSaveName = "localModels",
        toggleDefault = 1,
        toggleMax = 1,
    },
    [optionTableRef.prefToDefault] = {
        name = "Set Preference to Default",
        toggle = 0,
        toggleDefault = 0,
        toggleMax = 1,
        toggleNames = {"", ""},
    },
    [optionTableRef.debugInfo] = {
        name = "Debugging Info",
        toggle = tonumber(mod_storage_load("debuginfo")),
        toggleSaveName = "debuginfo",
        toggleDefault = 0,
        toggleMax = 1,
    },
}

local defaultPlayerColors = {
    [CT_MARIO] = {r = 255, g = 50, b = 50},
    [CT_LUIGI] = {r = 50, g = 255, b = 50},
    [CT_TOAD] = {r = 100,  g = 100,  b = 255},
    [CT_WALUIGI] = {r = 130, g = 25,  b = 130},
    [CT_WARIO] = {r = 255, g = 255, b = 50},
}

local defaultIcons = {
    [CT_MARIO] = gTextures.mario_head,
    [CT_LUIGI] = gTextures.luigi_head,
    [CT_TOAD] = gTextures.toad_head,
    [CT_WALUIGI] = gTextures.waluigi_head,
    [CT_WARIO] = gTextures.wario_head,
}

local latencyValueTable = {15, 10, 5}

local menuColorTable = {
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

local camera_freeze = camera_freeze
local camera_unfreeze = camera_unfreeze
local network_local_index_from_global = network_local_index_from_global
local obj_set_model_extended = obj_set_model_extended
local hud_hide = hud_hide
local hud_show = hud_show
local djui_chat_message_create = djui_chat_message_create
local djui_hud_set_resolution = djui_hud_set_resolution
local djui_hud_set_font = djui_hud_set_font
local djui_hud_set_color = djui_hud_set_color
local djui_hud_get_screen_width = djui_hud_get_screen_width
local djui_hud_render_rect = djui_hud_render_rect
local djui_hud_print_text = djui_hud_print_text
local djui_hud_render_texture = djui_hud_render_texture
local math_max = math.max
local math_min = math.min
local math_sin = math.sin
local math_random = math.random
local math_abs = math.abs
local math_ceil = math.ceil
local play_sound = play_sound
local mod_storage_save = mod_storage_save
local mod_storage_load = mod_storage_load
local string_lower = string.lower

---@param m MarioState
local function nullify_inputs(m)
    local c = m.controller
    _G.charSelect.controller = {
        buttonDown = c.buttonDown,
        buttonPressed = c.buttonPressed & ~_G.charSelect.controller.buttonDown,
        extStickX = c.extStickX,
        extStickY = c.extStickY,
        rawStickX = c.rawStickX,
        rawStickY = c.rawStickY,
        stickMag = c.stickMag,
        stickX = c.stickX,
        stickY = c.stickY
    }
    c.buttonDown = 0
    c.buttonPressed = 0
    c.extStickX = 0
    c.extStickY = 0
    c.rawStickX = 0
    c.rawStickY = 0
    c.stickMag = 0
    c.stickX = 0
    c.stickY = 0
end

local function load_preferred_char()
    if mod_storage_load("PrefChar") ~= nil and mod_storage_load("PrefChar") ~= "Default" then
        for i = 2, #characterTable do
            if characterTable[i].name == mod_storage_load("PrefChar") then
                currChar = i
                if optionTable[optionTableRef.localModels].toggle == 1 then
                    djui_popup_create('Character Select:\nYour Preferred Character\n"'..string_underscore_to_space(characterTable[i].name)..'"\nwas applied successfully!', 4)
                end
                break
            end
        end
    elseif mod_storage_load("PrefChar") == nil then
        mod_storage_save("PrefChar", "Default")
    end
    if #characterTable == 1 then
        djui_popup_create("Character Select:\nNo Characters were Found", 2)
    end
    TEXT_PREF_LOAD = mod_storage_load("PrefChar")
end

local function failsafe_options()
    for i = 1, #optionTable do
        if optionTable[i].toggle == nil then
            optionTable[i].toggle = optionTable[i].toggleDefault
            if optionTable[i].toggleSaveName ~= nil then
                mod_storage_save(optionTable[i].toggleSaveName, tostring(optionTable[i].toggle))
            end
        end
        if optionTable[i].toggleNames == nil then
            optionTable[i].toggleNames = {"Off", "On"}
        end
    end
    if optionTable[optionTableRef.openInputs].toggle == 1 and ommActive then
        djui_popup_create('Character Select:\nYour Open bind has changed to:\nD-pad Down + R\nDue to OMM Rebirth being active!', 4)
    end
end

local function idiot_proof_note()
    if #characterTable > 1 then
        djui_chat_message_create("Character Select is active and has "..(#characterTable - 1).." characters available!\nYou can use \\#ffff00\\/char-select \\#ffffff\\to open the menu!")
    else
        djui_chat_message_create("Character Select is active!\nYou can use \\#ffff00\\/char-select \\#ffffff\\to open the menu!")
    end
end

-------------------
-- Model Handler --
-------------------

local stallFrame = 0
local noLoop = false

-- Respecfully, GO FUCK YOURSELVES. I hate EVERY SINGLE ONE OF YOU. Your lives are NOTHING. You serve ZERO PURPOSE. You should kill yourselves, NOW!
local ignored_surfaces = {
    SURFACE_BURNING, SURFACE_QUICKSAND, SURFACE_INSTANT_QUICKSAND, SURFACE_INSTANT_MOVING_QUICKSAND, SURFACE_DEEP_MOVING_QUICKSAND, SURFACE_INSTANT_QUICKSAND, SURFACE_DEEP_QUICKSAND, SURFACE_SHALLOW_MOVING_QUICKSAND,
    SURFACE_SHALLOW_QUICKSAND, SURFACE_WARP, SURFACE_LOOK_UP_WARP, SURFACE_WOBBLING_WARP, SURFACE_INSTANT_WARP_1B, SURFACE_INSTANT_WARP_1C, SURFACE_INSTANT_WARP_1D, SURFACE_INSTANT_WARP_1E
}
-- Yes, floral gave me permission to use this table full of USELESS PIECES OF SHITS

--- @param m MarioState
local function mario_update(m)
    if stallFrame == 1 then
        load_preferred_char()
        failsafe_options()
        idiot_proof_note()
    end

    if stallFrame < 2 then
        stallFrame = stallFrame + 1
    end
    
    if m.playerIndex == 0 and stallFrame > 1 then
        local modelIndex = gNetworkPlayers[m.playerIndex].modelIndex
        characterTable[1].forceChar = modelIndex
        if currChar == 1 then
            characterTable[1].color = defaultPlayerColors[modelIndex]
            characterTable[1].lifeIcon = defaultIcons[modelIndex]
        end
        if optionTable[optionTableRef.localModels].toggle > 0 then
            gPlayerSyncTable[m.playerIndex].modelId = characterTable[currChar].model
            gPlayerSyncTable[m.playerIndex].capModels = characterTable[currChar].capModels
            if characterTable[currChar].forceChar ~= nil then
                gNetworkPlayers[m.playerIndex].overrideModelIndex = characterTable[currChar].forceChar
            end
        else
            gPlayerSyncTable[m.playerIndex].modelId = nil
            gPlayerSyncTable[m.playerIndex].capModels = nil
            gNetworkPlayers[m.playerIndex].overrideModelIndex = characterTable[1].forceChar
        end

        if menuAndTransition then
            for _, func in pairs(allowMenu) do
                if not func() then
                    menu = false
                    return
                end
            end
            camera_freeze()
            hud_hide()
            if _G.PersonalStarCounter then
                _G.PersonalStarCounter.hide_star_counters(true)
            end
            local focusPos = {
                x = m.pos.x,
                y = m.pos.y + 120,
                z = m.pos.z,
            }
            vec3f_copy(gLakituState.focus, focusPos)
            gLakituState.pos.x = m.pos.x + sins(m.faceAngle.y) * 500
            gLakituState.pos.y = m.pos.y + 100
            gLakituState.pos.z = m.pos.z + coss(m.faceAngle.y) * 500

            if m.forwardVel == 0 and m.pos.y == m.floorHeight and not ignored_surfaces[m.floor.type] and m.health > 255 then
                set_mario_action(m, ACT_IDLE, 0)
                set_mario_animation(m, MARIO_ANIM_STAR_DANCE)
            end
            noLoop = false
        elseif not noLoop then
            camera_unfreeze()
            hud_show()
            if _G.PersonalStarCounter then
                _G.PersonalStarCounter.hide_star_counters(false)
            end
            noLoop = true
        end
    end

    --Set Pref to Default Check
    if optionTable[optionTableRef.prefToDefault].toggle > 0 then
        mod_storage_save("PrefChar", "Default")
        TEXT_PREF_LOAD = "Default"
        optionTable[optionTableRef.prefToDefault].toggle = 0
    end
end

function set_model(o, model)
    if obj_has_behavior_id(o, id_bhvMario) ~= 0 then
        local i = network_local_index_from_global(o.globalPlayerIndex)
        if gPlayerSyncTable[i].modelId ~= nil and obj_has_model_extended(o, gPlayerSyncTable[i].modelId) == 0 then
            obj_set_model_extended(o, gPlayerSyncTable[i].modelId)
            return
        end
    end
    if get_object_list_from_behavior(o.behavior) == OBJ_LIST_LEVEL then
        local i = network_local_index_from_global(o.globalPlayerIndex)
        local capModels = gPlayerSyncTable[i].capModels
        local capModel = nil
        if capModels ~= nil then
            if model == gMarioStates[i].character.capModelId then
                capModel = capModels.normal
            elseif model == gMarioStates[i].character.capWingModelId then
                capModel = capModels.wing
            elseif model == gMarioStates[i].character.capMetalModelId then
                capModel = capModels.metal
            elseif model == gMarioStates[i].character.capMetalWingModelId then
                capModel = capModels.metalWing
            end
            if capModel ~= nil and obj_has_model_extended(o, capModel) == 0 then
                obj_set_model_extended(o, capModel)
                return
            end
        end
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_OBJECT_SET_MODEL, set_model)

------------------
-- Menu Handler --
------------------

local buttonAnimTimer = 0
local buttonScroll = 0
local buttonScrollCap = 30

local optionAnimTimer = -200
local optionAnimTimerCap = optionAnimTimer

local inputStallTimer = 0
local inputStallTo = 15

local FONT_CS_NORMAL = FONT_NORMAL
if version_coop_dx() then
    FONT_CS_NORMAL = FONT_ALIASED
end

--Basic Menu Text
local TEXT_OPTIONS_HEADER = "Menu Options"
local TEXT_VERSION = "Version: "..modVersion
if version_coop_dx() then
    TEXT_VERSION = TEXT_VERSION.." | CoopDX Detected"
end
local TEXT_RATIO_UNSUPPORTED = "Your Current Aspect-Ratio isn't Supported!"
local TEXT_DESCRIPTION = "Character Description:"
local TEXT_PREF_SAVE = "Press A to Set as Preferred Character"
local TEXT_PAUSE_Z_OPEN = "Z Button - Character Select"
local TEXT_PAUSE_CURR_CHAR = "Current Character: "
if math_random(100) == 64 then -- Easter Egg if you get lucky loading the mod >v<
    TEXT_PAUSE_Z_OPEN = "Z - DynOS" -- Referencing the original sm64ex DynOS options
    TEXT_PAUSE_CURR_CHAR = "Model: "
end

--Debug Text
local TEXT_DEBUGGING = "Character Debug"
local TEXT_DESCRIPTION_SHORT = "Description:"
local TEXT_LIFE_ICON = "Life Icon:"
local TEXT_FORCED_CHAR = "Forced: "
local TEXT_TABLE_POS = "Table Position: "

--Options Text
local TEXT_OPTIONS_OPEN = "Press START to open Options"
local TEXT_MENU_CLOSE = "Press B to Exit Menu"
local TEXT_OPTIONS_SELECT = "A - Select | B - Exit  "
local TEXT_LOCAL_MODEL_OFF = "Locally Display Models is Off"
local TEXT_LOCAL_MODEL_OFF_OPTIONS = "You can turn it back on in the Options Menu"

local forceCharTable = {
    [CT_MARIO] = "CT_MARIO",
    [CT_LUIGI] = "CT_LUIGI",
    [CT_TOAD] = "CT_TOAD",
    [CT_WARIO] = "CT_WARIO",
    [CT_WALUIGI] = "CT_WALUIGI",
}

local menuColor = characterTable[currChar].color

local function on_hud_render()
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_CS_NORMAL)

    local width = djui_hud_get_screen_width() + 1.4
    local height = 240
    local widthHalf = width*0.5
    local heightHalf = height*0.5
    local widthScale = math_max(width, 321.4)*0.00311332503

    if menuAndTransition then
        if optionTable[optionTableRef.menuColor].toggle ~= 0 then
            menuColor = menuColorTable[optionTable[optionTableRef.menuColor].toggle]
        else
            menuColor = characterTable[currChar].color
        end

        if optionTable[optionTableRef.localModels].toggle == 0 then
            djui_hud_set_color(0, 0, 0, 200)
            djui_hud_render_rect(0, 0, width, height)
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_print_text(TEXT_LOCAL_MODEL_OFF, widthHalf - djui_hud_measure_text(TEXT_LOCAL_MODEL_OFF)*0.15*widthScale, heightHalf, 0.3 * widthScale)
            djui_hud_print_text(TEXT_LOCAL_MODEL_OFF_OPTIONS, widthHalf - djui_hud_measure_text(TEXT_LOCAL_MODEL_OFF_OPTIONS)*0.1*widthScale, heightHalf + 10*widthScale, 0.2*widthScale)
        end
        
        --Character Buttons
        local x = 135 * widthScale * 0.8
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_render_rect(0, 0, x, height)
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_render_rect(2, 2, x - 4, height - 4)

        if optionTable[optionTableRef.anims].toggle > 0 then
            buttonAnimTimer = buttonAnimTimer + 1
        end
        if optionTable[optionTableRef.anims].toggle == 0 then
            buttonScroll = 0
        elseif buttonScroll > 0.1 or buttonScroll < -0.1 then
            buttonScroll = buttonScroll*0.03*inputStallTo
        end

        local buttonColor = {}
        for i = -1, 4 do
            if characterTable[i + currChar] ~= nil then
                buttonColor = characterTable[i + currChar].color
                djui_hud_set_color(buttonColor.r, buttonColor.g, buttonColor.b, 255)
                local buttonX = 20 * widthScale
                if optionTable[optionTableRef.anims].toggle > 0 then
                    if i == 0 then buttonX = buttonX + math_sin(buttonAnimTimer*0.05)*2.5 + 5 end
                else
                    if i == 0 then buttonX = buttonX + 10 end
                end
                local y = (i + 3) * 30 + buttonScroll
                djui_hud_render_rect(buttonX, y, 70, 20)
                djui_hud_set_color(0, 0, 0, 255)
                djui_hud_render_rect(buttonX + 1, y + 1, 68, 18)
                djui_hud_set_font(FONT_TINY)
                djui_hud_set_color(buttonColor.r, buttonColor.g, buttonColor.b, 255)
                djui_hud_print_text(string_underscore_to_space(characterTable[currChar + i].name), buttonX + 5, y + 5, 0.6)
            end
        end
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_render_rect(0, height-2, x, 2)

        -- Scroll Bar
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_render_rect(7 * widthScale, 55, 7, 170)
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_render_rect(7 * widthScale + 1, 56, 5, 168)
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_render_rect(7 * widthScale + 2, 57 + 166 * ((currChar - 1) / #characterTable) - (buttonScroll*0.03333333333)*(166/#characterTable), 3, 166/#characterTable)
        djui_hud_set_font(FONT_TINY)
        local TEXT_CHAR_COUNT = currChar.."/"..#characterTable
        djui_hud_print_text(TEXT_CHAR_COUNT, (11 - djui_hud_measure_text(TEXT_CHAR_COUNT)*0.2) * widthScale, height - 12, 0.4)

        
        --Character Description
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_render_rect(width - x, 0, x, height)
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_render_rect(width - x + 2, 2, x - 4, height - 4)
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_set_font(FONT_CS_NORMAL)
        local character = characterTable[currChar]
        if optionTable[optionTableRef.debugInfo].toggle == 0 then -- Actual Description
            local TEXT_NAME = string_underscore_to_space(character.name)
            local TEXT_CREDIT = "Credit: "..character.credit
            local TEXT_DESCRIPTION_TABLE = character.description
            local TEXT_PREF = 'Preferred Character: "'..string_underscore_to_space(TEXT_PREF_LOAD)..'"'

            local textX = x * 0.5
            djui_hud_print_text(TEXT_NAME, width - textX - djui_hud_measure_text(TEXT_NAME)*0.3, 55, 0.6)
            djui_hud_set_font(FONT_TINY)
            djui_hud_print_text(TEXT_CREDIT, width - textX - djui_hud_measure_text(TEXT_CREDIT)*0.3, 72, 0.6)
            djui_hud_set_font(FONT_CS_NORMAL)
            djui_hud_print_text(TEXT_DESCRIPTION, width - textX - djui_hud_measure_text(TEXT_DESCRIPTION)*0.2, 85, 0.4)
            if widthScale < 1.65 then
                for i = 1, #TEXT_DESCRIPTION_TABLE do
                    djui_hud_print_text(TEXT_DESCRIPTION_TABLE[i], width - textX - djui_hud_measure_text(TEXT_DESCRIPTION_TABLE[i])*0.15, 90 + i*9, 0.3)
                end
            else
                for i = 1, math_ceil(#TEXT_DESCRIPTION_TABLE*0.5) do
                    local TablePos = (i * 2) - 1
                    local TEXT_STRING = ""
                    if TEXT_DESCRIPTION_TABLE[TablePos] and TEXT_DESCRIPTION_TABLE[TablePos + 1] then
                        local TEXT_STRING = TEXT_DESCRIPTION_TABLE[TablePos].." "..TEXT_DESCRIPTION_TABLE[TablePos + 1]
                        djui_hud_print_text(TEXT_STRING, width - textX - djui_hud_measure_text(TEXT_STRING)*0.15, 90 + i*9, 0.3)
                    elseif TEXT_DESCRIPTION_TABLE[TablePos] then
                        local TEXT_STRING = TEXT_DESCRIPTION_TABLE[TablePos]
                        djui_hud_print_text(TEXT_STRING, width - textX - djui_hud_measure_text(TEXT_STRING)*0.15, 90 + i*9, 0.3)
                    end
                end
            end

            djui_hud_print_text(TEXT_PREF, width - textX - djui_hud_measure_text(TEXT_PREF)*0.15, height - 22, 0.3)
            djui_hud_set_font(FONT_TINY)    
            djui_hud_print_text(TEXT_PREF_SAVE, width - textX - djui_hud_measure_text(TEXT_PREF_SAVE)*0.25, height - 13, 0.5)
        else -- Debugging Info
            local TEXT_NAME = "Name: "..character.name
            local TEXT_CREDIT = "Credit: "..character.credit
            local TEXT_DESCRIPTION_TABLE = character.description
            local TEXT_COLOR = "Color: R-"..character.color.r..", G-"..character.color.g..", B-"..character.color.b
            local TEX_ICON = character.lifeIcon
            local TEXT_PREF = "Preferred: "..TEXT_PREF_LOAD

            local textX = x * 0.5
            djui_hud_print_text(TEXT_DEBUGGING, width - textX - djui_hud_measure_text(TEXT_DEBUGGING)*0.3, 55, 0.6)
            djui_hud_set_font(FONT_TINY)
            djui_hud_print_text(TEXT_NAME, width - x + 8, 72, 0.6)
            djui_hud_print_text(TEXT_CREDIT, width - x + 8, 81, 0.6)
            djui_hud_print_text(TEXT_DESCRIPTION_SHORT, width - x + 8, 90, 0.6)
            local removeLine = 0
            for i = 1, #TEXT_DESCRIPTION_TABLE do
                if TEXT_DESCRIPTION_TABLE[i] ~= "" then
                    djui_hud_print_text(TEXT_DESCRIPTION_TABLE[i], width - x + 12, 92 + (i-removeLine)*7, 0.5)
                else
                    removeLine = removeLine + 1
                end
            end
            local descriptionOffset = (#TEXT_DESCRIPTION_TABLE - removeLine) * 7
            djui_hud_print_text(TEXT_COLOR, width - x + 8, 100 + descriptionOffset, 0.6)
            djui_hud_print_text(TEXT_LIFE_ICON.."    ("..TEX_ICON.width.."x"..TEX_ICON.height..")", width - x + 8, 109 + descriptionOffset, 0.6)
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_render_texture(TEX_ICON, width - x + 38, 110 + descriptionOffset, 0.5/(TEX_ICON.width/16), 0.5/(TEX_ICON.height/16))
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_print_text(TEXT_FORCED_CHAR..forceCharTable[character.forceChar], width - x + 8, 118 + descriptionOffset, 0.6)
            djui_hud_print_text(TEXT_TABLE_POS..currChar, width - x + 8, 127 + descriptionOffset, 0.6)
            djui_hud_print_text(TEXT_PREF, width - x + 8, height - 18, 0.6)
        end

        --Character Select Header
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_render_rect(0, 0, width, 50)
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_render_rect(2, 2, width - 4, 46)
        djui_hud_set_color(menuColor.r * 0.5 + 127, menuColor.g * 0.5 + 127, menuColor.b * 0.5 + 127, 255)
        djui_hud_render_texture(TEX_HEADER, widthHalf - 128, 10, 1, 1)
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_set_font(FONT_TINY)
        djui_hud_print_text(TEXT_VERSION, 5, 3, 0.5)
        --Unsupported Res Warning
        if width < 321.2 or width > 575 then
            djui_hud_print_text(TEXT_RATIO_UNSUPPORTED, 5, 39, 0.5)
        end

        --Options display
        if options or optionAnimTimer > optionAnimTimerCap then
            djui_hud_set_color(menuColor.r * 0.25, menuColor.g * 0.25, menuColor.b * 0.25, 205 + math_max(-200, optionAnimTimer))
            djui_hud_render_rect(0, 0, width, height)
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_render_rect(width*0.5 - 50 * widthScale, math.min(55 - optionAnimTimer, height - 25 * widthScale), 100 * widthScale, 200)
            djui_hud_set_color(0, 0, 0, 255)
            djui_hud_render_rect(width*0.5 - 50 * widthScale + 2, math.min(55 - optionAnimTimer + 2, height - 25 * widthScale + 2), 100 * widthScale - 4, 196)
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_render_rect(width*0.5 - 50 * widthScale, height - 2, 100 * widthScale, 2)
            djui_hud_set_font(FONT_CS_NORMAL)
            djui_hud_set_color(menuColor.r * 0.5 + 127, menuColor.g * 0.5 + 127, menuColor.b * 0.5 + 127, 255)
            djui_hud_print_text(TEXT_OPTIONS_HEADER, widthHalf - djui_hud_measure_text(TEXT_OPTIONS_HEADER)*0.3*math_min(widthScale, 1.5), 65 + optionAnimTimer * -1, 0.6*math_min(widthScale, 1.5))

            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            local widthScale = math_min(widthScale, 1.5)
            for i = 1, #optionTable do
                local toggleName = optionTable[i].name
                local scale = 0.5
                local yOffset = 70 + 10 * widthScale + i * 9 * widthScale - optionAnimTimer
                if i == currOption then
                    djui_hud_set_font(FONT_CS_NORMAL)
                    scale = 0.3
                    yOffset = yOffset - 1
                    if optionTable[i].toggleNames[optionTable[i].toggle + 1] ~= "" then
                        toggleName = "> " .. toggleName .. " - " .. optionTable[i].toggleNames[optionTable[i].toggle + 1]
                    else
                        toggleName = "> " .. toggleName
                    end
                else
                    djui_hud_set_font(FONT_TINY)
                end
                scale = scale * widthScale
                djui_hud_print_text(toggleName, widthHalf - djui_hud_measure_text(toggleName)*scale*0.5, yOffset, scale)
            end

            djui_hud_set_font(FONT_TINY)
            djui_hud_print_text(TEXT_OPTIONS_SELECT, widthHalf - djui_hud_measure_text(TEXT_OPTIONS_SELECT)*0.3, height - 20 - optionAnimTimer, 0.6)
        else
            -- How to open options display
            local widthScaleUnlimited = widthScale
            local widthScale = math_min(widthScale, 1.42)
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_render_rect(widthHalf - 50 * widthScaleUnlimited, height - 25 * widthScale, 100 * widthScaleUnlimited, 26 * widthScale)
            djui_hud_set_color(0, 0, 0, 255)
            djui_hud_render_rect(widthHalf - 50 * widthScaleUnlimited + 2, height - 25 * widthScale + 2, 100 * widthScaleUnlimited - 4, 22 * widthScale)
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_render_rect(widthHalf - 50 * widthScaleUnlimited, height - 2, 100 * widthScaleUnlimited, 2)
            djui_hud_set_font(FONT_CS_NORMAL)
            djui_hud_print_text(TEXT_OPTIONS_OPEN, widthHalf - djui_hud_measure_text(TEXT_OPTIONS_OPEN)*0.175 * widthScale, height - 23 * widthScale + optionAnimTimer + 202, 0.35 * widthScale)
            djui_hud_set_font(FONT_TINY)
            djui_hud_print_text(TEXT_MENU_CLOSE, widthHalf - djui_hud_measure_text(TEXT_MENU_CLOSE)*0.25 * widthScale, height - 13 * widthScale + optionAnimTimer + 202, 0.5 * widthScale)
        end

        -- Anim logic
        if options then
            if optionTable[optionTableRef.anims].toggle > 0 then
                if optionAnimTimer < -1 then
                    optionAnimTimer = optionAnimTimer/1.1
                end
            else
                optionAnimTimer = -1
            end
        else
            if optionTable[optionTableRef.anims].toggle > 0 then
                if optionAnimTimer > optionAnimTimerCap then
                    optionAnimTimer = optionAnimTimer*1.2
                end
            else
                optionAnimTimer = optionAnimTimerCap
            end
        end
        optionAnimTimer = math_max(optionAnimTimer, -200)
    else
        options = false
        optionAnimTimer = optionAnimTimerCap
    end

    -- Cross fade
    if optionTable[optionTableRef.anims].toggle == 1 then
        if menu and menuCrossFade > -menuCrossFadeCap then
            menuCrossFade = menuCrossFade - 1
            if menuCrossFade == 0 then menuCrossFade = menuCrossFade - 1 end
        end
        if not menu and menuCrossFade < menuCrossFadeCap then
            menuCrossFade = menuCrossFade + 1
            if menuCrossFade == 0 then menuCrossFade = menuCrossFade + 1 end
        end
        if menuCrossFade < 0 then
            menuAndTransition = true
        else
            menuAndTransition = false
        end
    else
        if menu then
            menuCrossFade = -menuCrossFadeCap
        else
            menuCrossFade = menuCrossFadeCap
        end
        menuAndTransition = menu
    end
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_color(0, 0, 0, (math_abs(menuCrossFade)) * -menuCrossFadeMath)
    djui_hud_render_rect(0, 0, width, height)

    -- Info / Z Open Bind on Pause Menu
    if is_game_paused() and not djui_hud_is_pause_menu_created() and gMarioStates[0].action ~= ACT_EXIT_LAND_SAVE_DIALOG then
        local currCharY = 0
        djui_hud_set_resolution(RESOLUTION_DJUI)
        djui_hud_set_font(FONT_NORMAL)
        if optionTable[optionTableRef.openInputs].toggle == 2 then
            currCharY = 27
            local width = djui_hud_get_screen_width() - djui_hud_measure_text(TEXT_PAUSE_Z_OPEN)
            if not version_coop_dx() then -- Done to match DX not having dropshadow on the "R Button - Options" thingy
                djui_hud_set_color(0, 0, 0, 255)
                djui_hud_print_text(TEXT_PAUSE_Z_OPEN, width - 19, 17, 1)
            end
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_print_text(TEXT_PAUSE_Z_OPEN, width - 20, 16, 1)
        end

        if optionTable[optionTableRef.localModels].toggle == 1 then
            local charName = string_underscore_to_space(characterTable[currChar].name)
            local TEXT_PAUSE_CURR_CHAR_WITH_NAME = TEXT_PAUSE_CURR_CHAR..charName
            local width = djui_hud_get_screen_width() - djui_hud_measure_text(TEXT_PAUSE_CURR_CHAR_WITH_NAME)
            local charColor = characterTable[currChar].color
            if not version_coop_dx() then
                djui_hud_set_color(0, 0, 0, 255)
                djui_hud_print_text(TEXT_PAUSE_CURR_CHAR_WITH_NAME, width - 19, 17 + currCharY, 1)
            end
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_print_text(TEXT_PAUSE_CURR_CHAR, width - 20, 16 + currCharY, 1)
            djui_hud_set_color(charColor.r, charColor.g, charColor.b, 255)
            djui_hud_print_text(charName, djui_hud_get_screen_width() - djui_hud_measure_text(charName) - 20, 16 + currCharY, 1)
        else
            local width = djui_hud_get_screen_width() - djui_hud_measure_text(TEXT_LOCAL_MODEL_OFF)
            if not version_coop_dx() then
                djui_hud_set_color(0, 0, 0, 255)
                djui_hud_print_text(TEXT_LOCAL_MODEL_OFF, width - 19, 17 + currCharY, 1)
            end
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_print_text(TEXT_LOCAL_MODEL_OFF, width - 20, 16 + currCharY, 1)
        end
    end
end

-- Custom life icon rendering (Thanks LuigiGamer)
function on_life_counter_render()
    if obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil then return end
    djui_hud_set_font(FONT_HUD)
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_color(255, 255, 255, 255);
    local x = 22
    local y = 15
    if gNetworkPlayers[0].currActNum == 99 then return end
    if not hud_is_hidden() then
        local icon = characterTable[currChar].lifeIcon
        djui_hud_render_texture(icon, x, y, 1/(icon.width/16), 1/(icon.height/16))
        djui_hud_print_text("@", x + 16, y, 1)
        djui_hud_print_text(tostring(gMarioStates[0].numLives), x + 32, y, 1)
        hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) &~ HUD_DISPLAY_FLAG_LIVES) -- Hides the lives counter
    else
        hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) | HUD_DISPLAY_FLAG_LIVES) -- Shows the lives counter, use this when you're no longer using a custom character
    end
end

local function before_mario_update(m)
    if m.playerIndex ~= 0 then return end
    if inputStallTimer > 0 then inputStallTimer = inputStallTimer - 1 end
    
    if menu and inputStallTo ~= latencyValueTable[optionTable[optionTableRef.inputLatency].toggle + 1] then
        inputStallTo = latencyValueTable[optionTable[optionTableRef.inputLatency].toggle + 1]
    end

    -- Menu Inputs
    if not menu and (m.controller.buttonDown & D_JPAD) ~= 0 and m.action ~= ACT_EXIT_LAND_SAVE_DIALOG and optionTable[optionTableRef.openInputs].toggle == 1 then
        if ommActive then
            if (m.controller.buttonDown & R_TRIG) ~= 0 then
                menu = true
            end
        else
            menu = true
        end
        inputStallTimer = inputStallTo
    end
    if is_game_paused() and m.action ~= ACT_EXIT_LAND_SAVE_DIALOG and (m.controller.buttonPressed & Z_TRIG) ~= 0 and optionTable[optionTableRef.openInputs].toggle == 2 then
        menu = true
    end

    local cameraToObject = gMarioStates[0].marioObj.header.gfx.cameraToObject

    -- C-up Failsafe (Camera Softlocks)
    if m.action == ACT_FIRST_PERSON or (m.prevAction == ACT_FIRST_PERSON and is_game_paused()) then
        menu = false
    elseif m.prevAction == ACT_FIRST_PERSON and not is_game_paused() then
        m.prevAction = ACT_WALKING
    end

    if gNetworkPlayers[0].currActNum == 99 then
        menu = false
    end

    if menuAndTransition and not options then
        if inputStallTimer == 0 and menu then
            if (m.controller.buttonPressed & D_JPAD) ~= 0 then
                currChar = currChar + 1
                inputStallTimer = inputStallTo
                buttonScroll = buttonScrollCap
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if (m.controller.buttonPressed & U_JPAD) ~= 0 then
                currChar = currChar - 1
                inputStallTimer = inputStallTo
                buttonScroll = -buttonScrollCap
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if (m.controller.buttonPressed & D_CBUTTONS) ~= 0 then
                currChar = currChar + 1
                inputStallTimer = inputStallTo*0.6
                buttonScroll = buttonScrollCap
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if (m.controller.buttonPressed & U_CBUTTONS) ~= 0 then
                currChar = currChar - 1
                inputStallTimer = inputStallTo*0.6
                buttonScroll = -buttonScrollCap
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if m.controller.stickY < -60 then
                currChar = currChar + 1
                inputStallTimer = inputStallTo
                buttonScroll = buttonScrollCap
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if m.controller.stickY > 60 then
                currChar = currChar - 1
                inputStallTimer = inputStallTo
                buttonScroll = -buttonScrollCap
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if (m.controller.buttonPressed & A_BUTTON) ~= 0 then
                if characterTable[currChar] ~= nil then
                    TEXT_PREF_LOAD = characterTable[currChar].name
                    mod_storage_save("PrefChar", TEXT_PREF_LOAD)
                    inputStallTimer = inputStallTo
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, cameraToObject)
                else
                    play_sound(SOUND_MENU_CAMERA_BUZZ, cameraToObject)
                end
            end
            if (m.controller.buttonPressed & B_BUTTON) ~= 0 then
                menu = false
            end
            if (m.controller.buttonPressed & START_BUTTON) ~= 0 then
                options = true
            end
        end
        if currChar > #characterTable then currChar = 1 end
        if currChar < 1 then currChar = #characterTable end
        nullify_inputs(m)
        if is_game_paused() then
            m.controller.buttonPressed = START_BUTTON
        end
    end

    if options then
        if inputStallTimer == 0 then
            if (m.controller.buttonPressed & D_JPAD) ~= 0 then
                currOption = currOption + 1
                inputStallTimer = inputStallTo
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if (m.controller.buttonPressed & U_JPAD) ~= 0 then
                currOption = currOption - 1
                inputStallTimer = inputStallTo
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if m.controller.stickY < -60 then
                currOption = currOption + 1
                inputStallTimer = inputStallTo
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if m.controller.stickY > 60 then
                currOption = currOption - 1
                inputStallTimer = inputStallTo
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if (m.controller.buttonPressed & A_BUTTON) ~= 0 then
                optionTable[currOption].toggle = optionTable[currOption].toggle + 1
                if optionTable[currOption].toggle > optionTable[currOption].toggleMax then optionTable[currOption].toggle = 0 end
                if optionTable[currOption].toggleSaveName ~= nil then
                    mod_storage_save(optionTable[currOption].toggleSaveName, tostring(optionTable[currOption].toggle))
                end
                inputStallTimer = inputStallTo
                play_sound(SOUND_MENU_CHANGE_SELECT, cameraToObject)
            end
            if (m.controller.buttonPressed & B_BUTTON) ~= 0 then
                options = false
                inputStallTimer = inputStallTo
            end
        end
        if currOption > #optionTable then currOption = 1 end
        if currOption < 1 then currOption = #optionTable end
        nullify_inputs(m)
    end
end

hook_event(HOOK_BEFORE_MARIO_UPDATE, before_mario_update)
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
hook_event(HOOK_ON_HUD_RENDER_BEHIND, on_life_counter_render)

--------------
-- Commands --
--------------

local function chat_command(msg)
    if msg ~= "" and msg ~= "menu" then
        -- Name Check
        msg = string_lower(msg)
        for i = 1, #characterTable do
            if msg == string_underscore_to_space(string_lower(characterTable[i].name)) or msg == string_lower(characterTable[i].name) then
                currChar = i
                djui_chat_message_create('Character set to "'..characterTable[i].name..'" Successfully!')
                return true
            end
        end
        
        -- Number Check
        if tonumber(msg) then
            msg = tonumber(msg)
            if msg > 0 and msg <= #characterTable then
                currChar = msg
                djui_chat_message_create('Character set to "'..characterTable[msg].name..'" Successfully!')
                return true
            end
        end
        djui_chat_message_create("Character Not Found")
        return true
    else
        menu = not menu
        return true
    end
end

hook_chat_command("char-select", "- Opens the Character Select Menu", chat_command)