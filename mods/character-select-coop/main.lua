-- name: Character Select
-- description:\\#ffff33\\---- Character Select Coop v1.7 ----\n\n\\#dcdcdc\\A Library / API made to make adding and using Custom Characters as simple as possible!\nUse\\#ffff33\\ /char-select\\#dcdcdc\\ to get started!\n\nCreated by:\\#008800\\ Squishy6094\n\\#dcdcdc\\Concepts by:\\#4496f5\\ AngelicMiracles\n\n\\#AAAAFF\\Updates and Packs can be found on\nCharacter Select's Github:\n\\#6666FF\\Squishy6094/character-select-coop

-- localize functions to improve performance
local mod_storage_load,tonumber,djui_popup_create,mod_storage_save,tostring,djui_chat_message_create,camera_freeze,hud_hide,vec3f_copy,set_mario_action,set_mario_animation,camera_unfreeze,hud_show,obj_has_behavior_id,network_local_index_from_global,obj_has_model_extended,obj_set_model_extended,get_id_from_behavior,nearest_player_to_object,math_random,djui_hud_set_resolution,djui_hud_set_font,djui_hud_get_screen_width,maxf,djui_hud_set_color,djui_hud_render_rect,djui_hud_measure_text,djui_hud_print_text,math_ceil,math_abs,math_sin,min,math_min,minf,djui_hud_set_rotation,djui_hud_is_pause_menu_created,is_game_paused,hud_is_hidden,obj_get_first_with_behavior_id,hud_get_value,hud_set_value,play_sound,string_lower = mod_storage_load,tonumber,djui_popup_create,mod_storage_save,tostring,djui_chat_message_create,camera_freeze,hud_hide,vec3f_copy,set_mario_action,set_mario_animation,camera_unfreeze,hud_show,obj_has_behavior_id,network_local_index_from_global,obj_has_model_extended,obj_set_model_extended,get_id_from_behavior,nearest_player_to_object,math.random,djui_hud_set_resolution,djui_hud_set_font,djui_hud_get_screen_width,maxf,djui_hud_set_color,djui_hud_render_rect,djui_hud_measure_text,djui_hud_print_text,math.ceil,math.abs,math.sin,min,math.min,minf,djui_hud_set_rotation,djui_hud_is_pause_menu_created,is_game_paused,hud_is_hidden,obj_get_first_with_behavior_id,hud_get_value,hud_set_value,play_sound,string.lower

local menu = false
menuAndTransition = false
options = false
currChar = 1
local currOption = 1

local menuCrossFade = 7
local menuCrossFadeCap = menuCrossFade
local menuCrossFadeMath = 255 / menuCrossFade

local TEX_HEADER = get_texture_info("char-select-text")
local TEX_OVERRIDE_HEADER = nil

---@param texture TextureInfo|nil
function header_set_texture(texture)
    TEX_OVERRIDE_HEADER = texture
end

local TEXT_PREF_LOAD = "Default"

--[[
    Note: Do NOT add characters via the characterTable below,
    We highly reccomend you create your own mod and use the
    API to add characters, this ensures your pack is easy
    to use for anyone and low on file space!
]]
characterTable = {
    [1] = {
        name = "Default",
        saveName = "Default",
        description = {"The vanilla cast for sm64ex-coop!", "", "These Characters are swappable", "via the default Options Menu"},
        credit = "Nintendo / Coop Team",
        color = {r = 255, g = 50, b = 50},
        model = nil,
        forceChar = nil,
        lifeIcon = gTextures.mario_head,
        starIcon = gTextures.star,
        camScale = 1.0
    },
}

characterCaps = {}
characterCelebrationStar = {}

optionTableRef = {
    openInputs = 1,
    notification = 2,
    menuColor = 3,
    anims = 4,
    inputLatency = 5,
    localModels = 6,
    localVoices = 7,
    debugInfo = 8,
    resetSaveData = 9
}

optionTable = {
    [optionTableRef.openInputs] = {
        name = "Open Binds",
        toggle = tonumber(mod_storage_load("MenuInput")),
        toggleSaveName = "MenuInput",
        toggleDefault = 0,
        toggleMax = 2,
        toggleNames = {"None", ommActive and "D-pad Down + R" or "D-pad Down", "Z (Pause Menu)"},
        description = {"Sets a Bind to Open the Menu", "rather than using the command."}
    },
    [optionTableRef.notification] = {
        name = "Notifications",
        toggle = tonumber(mod_storage_load("notifs")),
        toggleSaveName = "notifs",
        toggleDefault = 1,
        toggleMax = 2,
        toggleNames = {"Off", "On", "Pop-ups Only"},
        description = {"Toggles wheather Pop-ups and", "Chat Messages display"}
    },
    [optionTableRef.menuColor] = {
        name = "Menu Color",
        toggle = tonumber(mod_storage_load("MenuColor")),
        toggleSaveName = "MenuColor",
        toggleDefault = 0,
        toggleMax = 10,
        toggleNames = {"Auto", "Saved", "Red", "Orange", "Yellow", "Green", "Blue", "Pink", "Purple", "White", "Black"},
        description = {"Toggles the Menu Color"}
    },
    [optionTableRef.anims] = {
        name = "Animations",
        toggle = tonumber(mod_storage_load("Anims")),
        toggleSaveName = "Anims",
        toggleDefault = 1,
        toggleMax = 1,
        toggleNames = {"Off", "On"--[[, "On (30 fps)"]]},
        description = {"Toggles Animations In-Menu,", "Turning these off may", "Save Performance"}
    },
    [optionTableRef.inputLatency] = {
        name = "Scroll Speed",
        toggle = tonumber(mod_storage_load("Latency")),
        toggleSaveName = "Latency",
        toggleDefault = 1,
        toggleMax = 2,
        toggleNames = {"Slow", "Normal", "Fast"},
        description = {"Sets how fast you scroll", "throughout the Menu"}
    },
    [optionTableRef.localModels] = {
        name = "Locally Display Models",
        toggle = tonumber(mod_storage_load("localModels")),
        toggleSaveName = "localModels",
        toggleDefault = 1,
        toggleMax = 1,
        description = {"Toggles if Custom Models display", "on your client, practically", "disables Character Select if", "Toggled Off"}
    },
    [optionTableRef.localVoices] = {
        name = "Custom Voices",
        toggle = tonumber(mod_storage_load("localVoices")),
        toggleSaveName = "localVoices",
        toggleDefault = 1,
        toggleMax = 1,
        description = {"Toggle if Custom Voicelines play", "for Characters who support it"}
    },
    [optionTableRef.debugInfo] = {
        name = "Debugging Info",
        toggle = tonumber(mod_storage_load("debuginfo")),
        toggleSaveName = "debuginfo",
        toggleDefault = 0,
        toggleMax = 1,
        description = {"Replaces the Character", "Description with Character", "Debugging Information"}
    },
    [optionTableRef.resetSaveData] = {
        name = "Reset Save Data",
        toggle = 0,
        toggleDefault = 0,
        toggleMax = 1,
        toggleNames = {"", ""},
        description = {"Resets Character Select's", "Save Data"}
    },
}

local optionTableCount = #optionTable

local latencyValueTable = {12, 6, 3}

local menuColorTable = {
    { r = 255, g = 50,  b = 50  },
    { r = 255, g = 100, b = 50  },
    { r = 255, g = 255, b = 50  },
    { r = 50,  g = 255, b = 50  },
    { r = 50,  g = 50,  b = 255 },
    { r = 251, g = 148, b = 220 },
    { r = 130, g = 25,  b = 130 },
    { r = 255, g = 255, b = 255 },
    { r = 50,  g = 50,  b = 50  }
}

-- Default Player Adjustments
local defaultNames = {
    [CT_MARIO] = "Mario",
    [CT_LUIGI] = "Luigi",
    [CT_TOAD] = "Toad",
    [CT_WALUIGI] = "Waluigi",
    [CT_WARIO] = "Wario"
}
local defaultPlayerColors = {
    [CT_MARIO] = menuColorTable[1],
    [CT_LUIGI] = menuColorTable[4],
    [CT_TOAD] =  menuColorTable[5],
    [CT_WALUIGI] = menuColorTable[7],
    [CT_WARIO] = menuColorTable[3]
}
local defaultForceChar = {
    [CT_MARIO] = "CT_MARIO",
    [CT_LUIGI] = "CT_LUIGI",
    [CT_TOAD] = "CT_TOAD",
    [CT_WALUIGI] = "CT_WALUIGI",
    [CT_WARIO] = "CT_WARIO"
}
local defaultIcons = {
    [CT_MARIO] = gTextures.mario_head,
    [CT_LUIGI] = gTextures.luigi_head,
    [CT_TOAD] = gTextures.toad_head,
    [CT_WALUIGI] = gTextures.waluigi_head,
    [CT_WARIO] = gTextures.wario_head
}
local defaultCamScales = {
    [CT_MARIO] = 1,
    [CT_LUIGI] = 1,
    [CT_TOAD] = 0.8,
    [CT_WALUIGI] = 1.1,
    [CT_WARIO] = 1
}

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

local prefCharColor = defaultPlayerColors[CT_MARIO]

local function load_preferred_char()
    local savedChar = mod_storage_load("PrefChar")
    if savedChar == nil or savedChar == "" then
        mod_storage_save("PrefChar", "Default")
        savedChar = "Default"
    end
    if savedChar ~= nil and savedChar ~= "Default" then
        for i = 2, #characterTable do
            if characterTable[i].saveName == savedChar then
                currChar = i
                if optionTable[optionTableRef.localModels].toggle == 1 then
                    if optionTable[optionTableRef.notification].toggle > 0 then
                        djui_popup_create('Character Select:\nYour Preferred Character\n"' .. string_underscore_to_space(characterTable[i].name) .. '"\nwas applied successfully!', 4)
                    end
                end
                break
            end
        end
    end

    local savedCharColors = mod_storage_load("PrefCharColor")
    if savedCharColors ~= nil and savedCharColors ~= "" then
        local savedCharColorsTable = string_split(string_underscore_to_space(savedCharColors))
        prefCharColor = {
            r = tonumber(savedCharColorsTable[1]),
            g = tonumber(savedCharColorsTable[2]),
            b = tonumber(savedCharColorsTable[3])
        }
    else
        mod_storage_save("PrefCharColor", "255_50_50")
    end

    if #characterTable == 1 then
        if optionTable[optionTableRef.notification].toggle > 0 then
            djui_popup_create("Character Select:\nNo Characters were Found", 2)
        end
    end
    return savedChar
end

local function mod_storage_save_pref_char(charTable)
    mod_storage_save("PrefChar", charTable.saveName)
    mod_storage_save("PrefCharColor", tostring(charTable.color.r) .. "_" .. tostring(charTable.color.g) .. "_" .. tostring(charTable.color.b))
    TEXT_PREF_LOAD = charTable.saveName
    prefCharColor = charTable.color
end

local function failsafe_options()
    for i = 1, #optionTable do
        if optionTable[i].toggle == nil or optionTable[i].toggle == "" then
            optionTable[i].toggle = optionTable[i].toggleDefault
            if optionTable[i].toggleSaveName ~= nil then
                mod_storage_save(optionTable[i].toggleSaveName, tostring(optionTable[i].toggle))
            end
        end
        if optionTable[i].toggleNames == nil then
            optionTable[i].toggleNames = {"Off", "On"}
        end
    end
    if optionTable[optionTableRef.openInputs].toggle > 0 and ommActive then
        djui_popup_create('Character Select:\nYour Open bind has changed to:\nD-pad Down + R\nDue to OMM Rebirth being active!', 4)
    end
end

local promptedAreYouSure = false

local function reset_options(wasChatTriggered)
    if not promptedAreYouSure then
        djui_chat_message_create("\\#ffdcdc\\Are you sure you want to reset your Save Data for Character Select, including your Preferred Character\nand Settings?\n" .. (wasChatTriggered and "Type \\#ff3333\\/char-select reset\\#ffdcdc\\ to confirm." or "Press the \\#ff3333\\" .. optionTable[optionTableRef.resetSaveData].name .. "\\#ffdcdc\\ Option again to confirm." ))
        promptedAreYouSure = true
    else
        djui_chat_message_create("\\#ff3333\\Character Select Save Data Reset!")
        djui_chat_message_create("Note: If your issue has not been resolved, you may need to manually delete your save data via the directory below:\n\\#dcdcFF\\sm64ex-coop/sav/character-select-coop.sav")
        for i = 1, #optionTable do
            optionTable[i].toggle = optionTable[i].toggleDefault
            if optionTable[i].toggleSaveName ~= nil then
                mod_storage_save(optionTable[i].toggleSaveName, tostring(optionTable[i].toggle))
            end
            if optionTable[i].toggleNames == nil then
                optionTable[i].toggleNames = { "Off", "On" }
            end
        end
        mod_storage_save_pref_char(characterTable[1])
        promptedAreYouSure = false
    end
end

local function boot_note()
    if #characterTable > 1 then
        djui_chat_message_create("Character Select has " .. (#characterTable - 1) .. " character" .. (#characterTable > 2 and "s" or "") .. " available!\nYou can use \\#ffff33\\/char-select \\#ffffff\\to open the menu!")
    else
        djui_chat_message_create("Character Select is active!\nYou can use \\#ffff33\\/char-select \\#ffffff\\to open the menu!")
    end

    if not IS_COOPDX then
        djui_chat_message_create("\\#FFAAAA\\Note: Although not required, we highly reccomend\nusing SM64CoopDX when playing Character Select!\n\\#6666FF\\https://sm64coopdx.com")
    end
end

-------------------
-- Model Handler --
-------------------

local stallFrame = 0
local noLoop = false

local CUTSCENE_CS_MENU = 0xFA

local ignoredSurfaces = {
    SURFACE_BURNING, SURFACE_QUICKSAND, SURFACE_INSTANT_QUICKSAND, SURFACE_INSTANT_MOVING_QUICKSAND, SURFACE_DEEP_MOVING_QUICKSAND, SURFACE_INSTANT_QUICKSAND, SURFACE_DEEP_QUICKSAND, SURFACE_SHALLOW_MOVING_QUICKSAND,
    SURFACE_SHALLOW_QUICKSAND, SURFACE_WARP, SURFACE_LOOK_UP_WARP, SURFACE_WOBBLING_WARP, SURFACE_INSTANT_WARP_1B, SURFACE_INSTANT_WARP_1C, SURFACE_INSTANT_WARP_1D, SURFACE_INSTANT_WARP_1E
}

local menuActBlacklist = {
    -- Star Acts
    [ACT_FALL_AFTER_STAR_GRAB] = true,
    [ACT_STAR_DANCE_EXIT] = true,
    [ACT_STAR_DANCE_NO_EXIT] = true,
    [ACT_STAR_DANCE_WATER] = true,
    -- Key Acts
    [ACT_UNLOCKING_KEY_DOOR] = true,
    [ACT_UNLOCKING_STAR_DOOR] = true,
    -- Cutscene Acts
    [ACT_INTRO_CUTSCENE] = true,
    [ACT_CREDITS_CUTSCENE] = true,
    [ACT_WARP_DOOR_SPAWN] = true,
    [ACT_PULLING_DOOR] = true,
    [ACT_PUSHING_DOOR] = true,
    [ACT_UNLOCKING_KEY_DOOR] = true,
    [ACT_UNLOCKING_STAR_DOOR] = true,
    -- Dialog Acts
    [ACT_READING_NPC_DIALOG] = true,
    [ACT_WAITING_FOR_DIALOG] = true,
    [ACT_EXIT_LAND_SAVE_DIALOG] = true,
    [ACT_READING_AUTOMATIC_DIALOG] = true,
}

local faceAngle = 0

--- @param m MarioState
local function mario_update(m)
    if stallFrame == 1 then
        failsafe_options()
        TEXT_PREF_LOAD = load_preferred_char()
        if optionTable[optionTableRef.notification].toggle == 1 then
            boot_note()
        end
    end

    if stallFrame < 2 then
        stallFrame = stallFrame + 1
    end

    if m.playerIndex == 0 and stallFrame > 1 then
        local modelIndex = gNetworkPlayers[m.playerIndex].modelIndex
        characterTable[1].forceChar = modelIndex
        characterTable[1].name = defaultNames[modelIndex]
        if currChar == 1 then
            characterTable[1].color = defaultPlayerColors[modelIndex]
            characterTable[1].lifeIcon = defaultIcons[modelIndex]
            characterTable[1].camScale = defaultCamScales[modelIndex]
        end
        if optionTable[optionTableRef.localModels].toggle > 0 then
            gPlayerSyncTable[m.playerIndex].modelId = characterTable[currChar].model
            if characterTable[currChar].forceChar ~= nil then
                gNetworkPlayers[m.playerIndex].overrideModelIndex = characterTable[currChar].forceChar
            end
        else
            gPlayerSyncTable[m.playerIndex].modelId = nil
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
            if m.area.camera.cutscene == 0 then
                m.area.camera.cutscene = CUTSCENE_CS_MENU
            end
            local camScale = characterTable[currChar].camScale
            local focusPos = {
                x = m.pos.x,
                y = m.pos.y + 120 * camScale,
                z = m.pos.z,
            }
            vec3f_copy(gLakituState.focus, focusPos)
            gLakituState.pos.x = m.pos.x + sins(faceAngle) * 500 * camScale
            gLakituState.pos.y = m.pos.y + 100 * camScale
            gLakituState.pos.z = m.pos.z + coss(faceAngle) * 500 * camScale

            if m.forwardVel == 0 and m.pos.y == m.floorHeight and not ignoredSurfaces[m.floor.type] and m.health > 255 and not menuActBlacklist[m.action] then
                set_mario_action(m, ACT_IDLE, 0)
                set_mario_animation(m, MARIO_ANIM_FIRST_PERSON)
            end
            noLoop = false
        elseif not noLoop then
            camera_unfreeze()
            hud_show()
            if _G.PersonalStarCounter then
                _G.PersonalStarCounter.hide_star_counters(false)
            end
            if m.area.camera.cutscene == CUTSCENE_CS_MENU then
                m.area.camera.cutscene = CUTSCENE_STOP
            end
            noLoop = true
        end
    end

    --Reset Save Data Check
    if optionTable[optionTableRef.resetSaveData].toggle > 0 then
        reset_options(false)
        optionTable[optionTableRef.resetSaveData].toggle = 0
    end
end

local sCapBhvs = {
    [id_bhvWingCap] = true,
    [id_bhvVanishCap] = true,
    [id_bhvMetalCap] = true
}

--- @param o Object
--- @param model integer
function set_model(o, model)
    if obj_has_behavior_id(o, id_bhvMario) ~= 0 then
        local i = network_local_index_from_global(o.globalPlayerIndex)
        if gPlayerSyncTable[i].modelId ~= nil and obj_has_model_extended(o, gPlayerSyncTable[i].modelId) == 0 then
            obj_set_model_extended(o, gPlayerSyncTable[i].modelId)
        end
        return
    end
    if obj_has_behavior_id(o, id_bhvCelebrationStar) ~= 0 and o.parentObj ~= nil then
        local i = network_local_index_from_global(o.parentObj.globalPlayerIndex)
        local starModel = characterCelebrationStar[gPlayerSyncTable[i].modelId]
        if gPlayerSyncTable[i].modelId ~= nil and starModel ~= nil and obj_has_model_extended(o, starModel) == 0 then
            obj_set_model_extended(o, starModel)
        end
        return
    end

    if sCapBhvs[get_id_from_behavior(o.behavior)] then
        o.globalPlayerIndex = nearest_player_to_object(o.parentObj).globalPlayerIndex
    end
    local i = network_local_index_from_global(o.globalPlayerIndex)

    local c = gMarioStates[i].character
    if model == c.capModelId or
       model == c.capWingModelId or
       model == c.capMetalModelId or
       model == c.capMetalWingModelId then
        local capModels = characterCaps[gPlayerSyncTable[i].modelId]
        if capModels ~= nil then
            local capModel = E_MODEL_NONE
            if model == c.capModelId then
                capModel = capModels.normal
            elseif model == c.capWingModelId then
                capModel = capModels.wing
            elseif model == c.capMetalModelId then
                capModel = capModels.metal
            elseif model == c.capMetalWingModelId then
                capModel = capModels.metalWing
            end
            if capModel ~= E_MODEL_NONE then
                obj_set_model_extended(o, capModel)
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

local inputStallTimerButton = 0
local inputStallTimerDirectional = 0
local inputStallToDirectional = 12
local inputStallToButton = 10

-- Font Consistency between sm64ex-coop and sm64coopdx
local FONT_CS_NORMAL = IS_COOPDX and FONT_ALIASED or FONT_NORMAL

--Basic Menu Text
local TEXT_OPTIONS_HEADER = "Menu Options"
local TEXT_VERSION = "Version: " .. MOD_VERSION .. (IS_COOPDX and " | sm64coopdx" or " | sm64ex-coop")
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

local menuColor = characterTable[currChar].color

local MATH_DIVIDE_THREE_HUNDRED_TWENTY = 1/320
local MATH_DIVIDE_THIRTY_TWO = 1/32

local function on_hud_render()
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_CS_NORMAL)

    local width = djui_hud_get_screen_width() + 1.4
    local height = 240
    local widthHalf = width * 0.5
    local heightHalf = height * 0.5
    local widthScale = maxf(width, 321.4) * MATH_DIVIDE_THREE_HUNDRED_TWENTY

    if menuAndTransition then
        if optionTable[optionTableRef.menuColor].toggle > 1 then
            menuColor = menuColorTable[optionTable[optionTableRef.menuColor].toggle - 1]
        elseif optionTable[optionTableRef.menuColor].toggle == 1 then
            optionTable[optionTableRef.menuColor].toggleNames[2] = string_underscore_to_space(TEXT_PREF_LOAD) .. " (Pref)"
            menuColor = prefCharColor
        else
            menuColor = characterTable[currChar].color
        end

        if optionTable[optionTableRef.localModels].toggle == 0 then
            djui_hud_set_color(0, 0, 0, 200)
            djui_hud_render_rect(0, 0, width, height)
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_print_text(TEXT_LOCAL_MODEL_OFF, widthHalf - djui_hud_measure_text(TEXT_LOCAL_MODEL_OFF) * 0.15 * widthScale, heightHalf, 0.3 * widthScale)
            djui_hud_print_text(TEXT_LOCAL_MODEL_OFF_OPTIONS, widthHalf - djui_hud_measure_text(TEXT_LOCAL_MODEL_OFF_OPTIONS) * 0.1 * widthScale, heightHalf + 10 * widthScale, 0.2 * widthScale)
        end

        local x = 135 * widthScale * 0.8

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
            local TEXT_CREDIT = "Credit: " .. character.credit
            local TEXT_DESCRIPTION_TABLE = character.description
            local TEXT_PREF = "Preferred Character:"
            local TEXT_PREF_LOAD = string_underscore_to_space(TEXT_PREF_LOAD)
            if djui_hud_measure_text(TEXT_PREF_LOAD) / widthScale > 110 then
                TEXT_PREF = "Preferred Char:"
            end
            if djui_hud_measure_text(TEXT_PREF_LOAD) / widthScale > 164 then
                TEXT_PREF = "Pref Char:"
            end
            TEXT_PREF = TEXT_PREF .. ' "' .. TEXT_PREF_LOAD .. '"'

            local textX = x * 0.5
            djui_hud_print_text(TEXT_NAME, width - textX - djui_hud_measure_text(TEXT_NAME) * 0.3, 55, 0.6)
            djui_hud_set_font(FONT_TINY)
            djui_hud_print_text(TEXT_CREDIT, width - textX - djui_hud_measure_text(TEXT_CREDIT) * 0.3, 74, 0.6)
            djui_hud_set_font(FONT_CS_NORMAL)
            djui_hud_print_text(TEXT_DESCRIPTION, width - textX - djui_hud_measure_text(TEXT_DESCRIPTION) * 0.2, 85, 0.4)
            if widthScale < 1.65 then
                for i = 1, #TEXT_DESCRIPTION_TABLE do
                    djui_hud_print_text(TEXT_DESCRIPTION_TABLE[i], width - textX - djui_hud_measure_text(TEXT_DESCRIPTION_TABLE[i]) * 0.15, 90 + i * 9, 0.3)
                end
            else
                for i = 1, math_ceil(#TEXT_DESCRIPTION_TABLE*0.5) do
                    local tablePos = (i * 2) - 1
                    if TEXT_DESCRIPTION_TABLE[tablePos] and TEXT_DESCRIPTION_TABLE[tablePos + 1] then
                        local TEXT_STRING = TEXT_DESCRIPTION_TABLE[tablePos] .. " " .. TEXT_DESCRIPTION_TABLE[tablePos + 1]
                        djui_hud_print_text(TEXT_STRING, width - textX - djui_hud_measure_text(TEXT_STRING) * 0.15, 90 + i * 9, 0.3)
                    elseif TEXT_DESCRIPTION_TABLE[tablePos] then
                        local TEXT_STRING = TEXT_DESCRIPTION_TABLE[tablePos]
                        djui_hud_print_text(TEXT_STRING, width - textX - djui_hud_measure_text(TEXT_STRING) * 0.15, 90 + i * 9, 0.3)
                    end
                end
            end

            djui_hud_print_text(TEXT_PREF, width - textX - djui_hud_measure_text(TEXT_PREF) * 0.15, height - 22, 0.3)
            djui_hud_set_font(FONT_TINY)
            djui_hud_print_text(TEXT_PREF_SAVE, width - textX - djui_hud_measure_text(TEXT_PREF_SAVE) * 0.25, height - 13, 0.5)
        else -- Debugging Info
            local TEXT_NAME = "Name: " .. character.name
            local TEXT_SAVE_NAME = "Save Name: " .. character.saveName
            local TEXT_CREDIT = "Credit: " .. character.credit
            local TEXT_DESCRIPTION_TABLE = character.description
            local TEXT_COLOR = "Color: R-" .. character.color.r ..", G-" ..character.color.g ..", B-"..character.color.b
            local TEX_ICON = character.lifeIcon
            local TEXT_ICON_DEFAULT = "?"
            local TEXT_SCALE = "Camera Scale: " .. character.camScale
            local TEXT_PREF = "Preferred: " .. TEXT_PREF_LOAD
            local TEXT_PREF_COLOR = "Pref Color: R-" .. prefCharColor.r .. ", G-" .. prefCharColor.g .. ", B-" .. prefCharColor.b

            local textX = x * 0.5
            djui_hud_print_text(TEXT_DEBUGGING, width - textX - djui_hud_measure_text(TEXT_DEBUGGING) * 0.3, 55, 0.6)
            djui_hud_set_font(FONT_TINY)
            djui_hud_print_text(TEXT_NAME, width - x + 8, 72, 0.6)
            djui_hud_print_text(TEXT_SAVE_NAME, width - x + 8, 81, 0.6)
            djui_hud_print_text(TEXT_CREDIT, width - x + 8, 90, 0.6)
            djui_hud_print_text(TEXT_DESCRIPTION_SHORT, width - x + 8, 99, 0.6)
            local removeLine = 0
            for i = 1, #TEXT_DESCRIPTION_TABLE do
                if TEXT_DESCRIPTION_TABLE[i] ~= "" then
                    djui_hud_set_font(FONT_CS_NORMAL)
                    local TEXT_DESCRIPTION_LINE = TEXT_DESCRIPTION_TABLE[i]
                    if (djui_hud_measure_text(TEXT_DESCRIPTION_TABLE[i]) * 0.3 > 100) then
                        TEXT_DESCRIPTION_LINE = "(!) " .. TEXT_DESCRIPTION_LINE
                    else
                        TEXT_DESCRIPTION_LINE = "    " .. TEXT_DESCRIPTION_LINE
                    end
                    djui_hud_set_font(FONT_TINY)
                    djui_hud_print_text(TEXT_DESCRIPTION_LINE, width - x + 5, 101 + (i-removeLine) * 7, 0.5)
                else
                    removeLine = removeLine + 1
                end
            end
            local descriptionOffset = (#TEXT_DESCRIPTION_TABLE - removeLine) * 7
            djui_hud_print_text(TEXT_COLOR, width - x + 8, 109 + descriptionOffset, 0.6)
            if TEX_ICON ~= nil then
                djui_hud_print_text(TEXT_LIFE_ICON .. "    (" .. TEX_ICON.width .. "x" .. TEX_ICON.height .. ")", width - x + 8, 118 + descriptionOffset, 0.6)
                djui_hud_set_color(255, 255, 255, 255)
                djui_hud_render_texture(TEX_ICON, width - x + 38, 119 + descriptionOffset, 0.5 / (TEX_ICON.width / 16), 0.5 / (TEX_ICON.height / 16))
            else
                djui_hud_print_text(TEXT_LIFE_ICON .. "    (?x?)", width - x + 8, 118 + descriptionOffset, 0.6)
                djui_hud_set_font(FONT_HUD)
                djui_hud_set_color(255, 255, 255, 255)
                djui_hud_print_text(TEXT_ICON_DEFAULT, width - x + 38, 119 + descriptionOffset, 0.5)
                djui_hud_set_font(FONT_TINY)
            end
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_print_text(TEXT_FORCED_CHAR .. defaultForceChar[character.forceChar], width - x + 8, 127 + descriptionOffset, 0.6)
            djui_hud_print_text(TEXT_TABLE_POS .. currChar, width - x + 8, 136 + descriptionOffset, 0.6)
            djui_hud_print_text(TEXT_SCALE, width - x + 8, 145 + descriptionOffset, 0.6)


            djui_hud_print_text(TEXT_PREF, width - x + 8, height - 27, 0.6)
            djui_hud_print_text(TEXT_PREF_COLOR, width - x + 8, height - 18, 0.6)
        end

        --Character Buttons
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_render_rect(0, 0, x, height)
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_render_rect(2, 2, x - 4, height - 4)

        if optionTable[optionTableRef.anims].toggle > 0 then
            buttonAnimTimer = buttonAnimTimer + 1
        end
        if optionTable[optionTableRef.anims].toggle == 0 then
            buttonScroll = 0
        elseif math_abs(buttonScroll) > 0.1 then
            buttonScroll = buttonScroll * 0.03 * inputStallToDirectional
        end

        local buttonColor = {}
        for i = -1, 4 do
            if characterTable[i + currChar] ~= nil then
                buttonColor = characterTable[i + currChar].color
                djui_hud_set_color(buttonColor.r, buttonColor.g, buttonColor.b, 255)
                local buttonX = 20 * widthScale
                if i == 0 then
                    if optionTable[optionTableRef.anims].toggle > 0 then
                        buttonX = buttonX + math_sin(buttonAnimTimer * 0.05) * 2.5 + 5
                    else
                        buttonX = buttonX + 10
                    end
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
        djui_hud_render_rect(7 * widthScale + 2, 57 + 166 * ((currChar - 1) / #characterTable) - (buttonScroll * 0.03333333333) * (166 / #characterTable), 3, 166 / #characterTable)
        djui_hud_set_font(FONT_TINY)
        local TEXT_CHAR_COUNT = currChar .. "/" .. #characterTable
        djui_hud_print_text(TEXT_CHAR_COUNT, (11 - djui_hud_measure_text(TEXT_CHAR_COUNT) * 0.2) * widthScale, height - 12, 0.4)

        --Character Select Header
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_render_rect(0, 0, width, 50)
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_render_rect(2, 2, width - 4, 46)
        djui_hud_set_color(menuColor.r * 0.5 + 127, menuColor.g * 0.5 + 127, menuColor.b * 0.5 + 127, 255)
        if TEX_OVERRIDE_HEADER then -- Render Override Header
            djui_hud_render_texture(TEX_OVERRIDE_HEADER, widthHalf - 128, 10, 1/(TEX_OVERRIDE_HEADER.height*MATH_DIVIDE_THIRTY_TWO), 1/(TEX_OVERRIDE_HEADER.height*MATH_DIVIDE_THIRTY_TWO))
        else
            djui_hud_render_texture(TEX_HEADER, widthHalf - 128, 10, 1, 1)
        end
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_set_font(FONT_TINY)
        djui_hud_print_text(TEXT_VERSION, 5, 3, 0.5)

        --Unsupported Res Warning
        if width < 321.2 or width > 575 then
            djui_hud_print_text(TEXT_RATIO_UNSUPPORTED, 5, 39, 0.5)
        end

        -- API Rendering
        if #renderInMenuTable > 0 then
            for i = 1, #renderInMenuTable do
                renderInMenuTable[i]()
            end
        end

        --Options display
        if options or optionAnimTimer > optionAnimTimerCap then
            djui_hud_set_color(menuColor.r * 0.25, menuColor.g * 0.25, menuColor.b * 0.25, 205 + maxf(-200, optionAnimTimer))
            djui_hud_render_rect(0, 0, width, height)
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_render_rect(width * 0.5 - 50 * widthScale, minf(55 - optionAnimTimer, height - 25 * widthScale), 100 * widthScale, 200)
            djui_hud_set_color(0, 0, 0, 255)
            djui_hud_render_rect(width * 0.5 - 50 * widthScale + 2, minf(55 - optionAnimTimer + 2, height - 25 * widthScale + 2), 100 * widthScale - 4, 196)
            djui_hud_set_font(FONT_CS_NORMAL)
            djui_hud_set_color(menuColor.r * 0.5 + 127, menuColor.g * 0.5 + 127, menuColor.b * 0.5 + 127, 255)
            djui_hud_print_text(TEXT_OPTIONS_HEADER, widthHalf - djui_hud_measure_text(TEXT_OPTIONS_HEADER) * 0.3 * minf(widthScale, 1.5), 65 + optionAnimTimer * -1, 0.6 * minf(widthScale, 1.5))

            local widthScaleLimited = minf(widthScale, 1.5)
            -- Up Arrow
            if currOption > 3 then
                djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
                djui_hud_set_rotation(0x2000, 0.5, 0.5)
                djui_hud_render_rect(widthHalf - 3 * widthScaleLimited, 95 - optionAnimTimer, 5  * widthScaleLimited, 5  * widthScaleLimited)
                djui_hud_set_color(0, 0, 0, 255)
                djui_hud_set_rotation(0x0000, 0.5, 0.5)
                djui_hud_render_rect(widthHalf - 4 * widthScaleLimited, 95 - optionAnimTimer + 2 * widthScaleLimited, 8 * widthScaleLimited, 10)
            end

            -- Down Arrow
            if currOption < optionTableCount - 2 then
                local yOffset = 90 - optionAnimTimer + 45 * widthScaleLimited
                djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
                djui_hud_set_rotation(0x2000, 0.5, 0.5)
                djui_hud_render_rect(widthHalf - 3 * widthScaleLimited, yOffset + 10, 5 * widthScaleLimited, 5 * widthScaleLimited)
                djui_hud_set_color(0, 0, 0, 255)
                djui_hud_set_rotation(0x0000, 0.5, 0.5)
                djui_hud_render_rect(widthHalf - 4 * widthScaleLimited, yOffset + 10 - 2 * widthScaleLimited, 8 * widthScaleLimited, 5 * widthScaleLimited)
            end

            -- Options 
            for i = currOption - 2, currOption + 2 do
                if not (i < 1 or i > optionTableCount) then
                    local toggleName = optionTable[i].name
                    local scale = 0.5
                    local yOffset = 100 - optionAnimTimer + (i - currOption + 2) * 9 * widthScaleLimited
                    if i == currOption then
                        djui_hud_set_font(FONT_CS_NORMAL)
                        scale = 0.3
                        yOffset = yOffset - 1
                        if optionTable[i].toggleNames[optionTable[i].toggle + 1] ~= "" then
                            toggleName = toggleName .. " - " .. optionTable[i].toggleNames[optionTable[i].toggle + 1]
                        else
                            toggleName = toggleName
                        end
                        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
                    else
                        djui_hud_set_font(FONT_TINY)
                        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 150)
                    end
                    scale = scale * widthScaleLimited
                    djui_hud_print_text(toggleName, widthHalf - djui_hud_measure_text(toggleName) * scale * 0.5, yOffset, scale)
                end
            end

            -- Description
            if optionTable[currOption].description ~= nil then
                djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
                for i = 1, #optionTable[currOption].description do
                    djui_hud_set_font(FONT_CS_NORMAL)
                    local line = optionTable[currOption].description[i]
                    djui_hud_print_text(line, widthHalf - djui_hud_measure_text(line) * 0.15, 180 - optionAnimTimer + 15 * widthScaleLimited + 8 * i - 8 * #optionTable[currOption].description, 0.3)
                end
            end
            -- Footer
            djui_hud_set_font(FONT_TINY)
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_print_text(TEXT_OPTIONS_SELECT, widthHalf - djui_hud_measure_text(TEXT_OPTIONS_SELECT) * 0.3, height - 20 - optionAnimTimer, 0.6)
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_render_rect(width * 0.5 - 50 * widthScale, height - 2, 100 * widthScale, 2)
        else
            -- How to open options display
            local widthScaleLimited = minf(widthScale, 1.42)
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_render_rect(widthHalf - 50 * widthScale, height - 25 * widthScaleLimited, 100 * widthScale, 26 * widthScaleLimited)
            djui_hud_set_color(0, 0, 0, 255)
            djui_hud_render_rect(widthHalf - 50 * widthScale + 2, height - 25 * widthScaleLimited + 2, 100 * widthScale - 4, 22 * widthScaleLimited)
            djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
            djui_hud_render_rect(widthHalf - 50 * widthScale, height - 2, 100 * widthScale, 2)
            djui_hud_set_font(FONT_CS_NORMAL)
            djui_hud_print_text(TEXT_OPTIONS_OPEN, widthHalf - djui_hud_measure_text(TEXT_OPTIONS_OPEN) * 0.175 * widthScaleLimited, height - 23 * widthScaleLimited + optionAnimTimer + 202, 0.35 * widthScaleLimited)
            djui_hud_set_font(FONT_TINY)
            djui_hud_print_text(TEXT_MENU_CLOSE, widthHalf - djui_hud_measure_text(TEXT_MENU_CLOSE) * 0.25 * widthScaleLimited, height - 13 * widthScaleLimited + optionAnimTimer + 202, 0.5 * widthScaleLimited)
        end


        -- Anim logic
        if options then
            if optionTable[optionTableRef.anims].toggle > 0 then
                if optionAnimTimer < -1 then
                    optionAnimTimer = optionAnimTimer / 1.1
                end
            else
                optionAnimTimer = -1
            end
        else
            if optionTable[optionTableRef.anims].toggle > 0 then
                if optionAnimTimer > optionAnimTimerCap then
                    optionAnimTimer = optionAnimTimer * 1.3
                end
            else
                optionAnimTimer = optionAnimTimerCap
            end
        end
        optionAnimTimer = maxf(optionAnimTimer, -200)
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
            width = djui_hud_get_screen_width() - djui_hud_measure_text(TEXT_PAUSE_Z_OPEN)
            if not IS_COOPDX then -- Done to match DX not having dropshadow on the "R Button - Options" thingy
                djui_hud_set_color(0, 0, 0, 255)
                djui_hud_print_text(TEXT_PAUSE_Z_OPEN, width - 19, 17, 1)
            end
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_print_text(TEXT_PAUSE_Z_OPEN, width - 20, 16, 1)
        end

        if optionTable[optionTableRef.localModels].toggle == 1 then
            local charName = string_underscore_to_space(characterTable[currChar].name)
            local TEXT_PAUSE_CURR_CHAR_WITH_NAME = TEXT_PAUSE_CURR_CHAR .. charName
            width = djui_hud_get_screen_width() - djui_hud_measure_text(TEXT_PAUSE_CURR_CHAR_WITH_NAME)
            local charColor = characterTable[currChar].color
            if not IS_COOPDX then
                djui_hud_set_color(0, 0, 0, 255)
                djui_hud_print_text(TEXT_PAUSE_CURR_CHAR_WITH_NAME, width - 19, 17 + currCharY, 1)
            end
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_print_text(TEXT_PAUSE_CURR_CHAR, width - 20, 16 + currCharY, 1)
            djui_hud_set_color(charColor.r, charColor.g, charColor.b, 255)
            djui_hud_print_text(charName, djui_hud_get_screen_width() - djui_hud_measure_text(charName) - 20, 16 + currCharY, 1)
        else
            width = djui_hud_get_screen_width() - djui_hud_measure_text(TEXT_LOCAL_MODEL_OFF)
            if not IS_COOPDX then
                djui_hud_set_color(0, 0, 0, 255)
                djui_hud_print_text(TEXT_LOCAL_MODEL_OFF, width - 19, 17 + currCharY, 1)
            end
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_print_text(TEXT_LOCAL_MODEL_OFF, width - 20, 16 + currCharY, 1)
        end
    end
end

local function before_mario_update(m)
    if m.playerIndex ~= 0 then return end
    if inputStallTimerButton > 0 then inputStallTimerButton = inputStallTimerButton - 1 end
    if inputStallTimerDirectional > 0 then inputStallTimerDirectional = inputStallTimerDirectional - 1 end

    if menu and inputStallToDirectional ~= latencyValueTable[optionTable[optionTableRef.inputLatency].toggle + 1] then
        inputStallToDirectional = latencyValueTable[optionTable[optionTableRef.inputLatency].toggle + 1]
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
        inputStallTimerDirectional = inputStallToDirectional
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

    if gNetworkPlayers[0].currActNum == 99 then menu = false end
    if m.action == ACT_INTRO_CUTSCENE then menu = false end

    if menuAndTransition and not options then
        if menu then
            if inputStallTimerDirectional == 0 then
                if (m.controller.buttonPressed & D_JPAD) ~= 0 or (m.controller.buttonPressed & D_CBUTTONS) ~= 0 or m.controller.stickY < -60 then
                    currChar = currChar + 1
                    if (m.controller.buttonPressed & D_CBUTTONS) == 0 then
                        inputStallTimerDirectional = inputStallToDirectional
                    else
                        inputStallTimerDirectional = 3 -- C-Scrolling
                    end
                    buttonScroll = buttonScrollCap
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
                end
                if (m.controller.buttonPressed & U_JPAD) ~= 0 or (m.controller.buttonPressed & U_CBUTTONS) ~= 0 or m.controller.stickY > 60 then
                    currChar = currChar - 1
                    if (m.controller.buttonPressed & U_CBUTTONS) == 0 then
                        inputStallTimerDirectional = inputStallToDirectional
                    else
                        inputStallTimerDirectional = 3 -- C-Scrolling
                    end
                    buttonScroll = -buttonScrollCap
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
                end
            end

            if inputStallTimerButton == 0 then
                if (m.controller.buttonPressed & A_BUTTON) ~= 0 then
                    if characterTable[currChar] ~= nil then
                        mod_storage_save_pref_char(characterTable[currChar])
                        inputStallTimerButton = inputStallToButton
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
        end
        -- Wraping Menu
        if currChar > #characterTable then currChar = 1 end
        if currChar < 1 then currChar = #characterTable end

        -- Handles Camera Posistioning
        faceAngle = m.faceAngle.y
        if m.controller.buttonPressed & R_CBUTTONS ~= 0 then faceAngle = faceAngle + 0x1000 end
        if m.controller.buttonPressed & L_CBUTTONS ~= 0 then faceAngle = faceAngle - 0x1000 end

        nullify_inputs(m)
        if is_game_paused() then
            m.controller.buttonPressed = START_BUTTON
        end
    end

    if options then
        if inputStallTimerDirectional == 0 then
            if (m.controller.buttonPressed & D_JPAD) ~= 0 then
                currOption = currOption + 1
                inputStallTimerDirectional = inputStallToDirectional
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if (m.controller.buttonPressed & U_JPAD) ~= 0 then
                currOption = currOption - 1
                inputStallTimerDirectional = inputStallToDirectional
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if m.controller.stickY < -60 then
                currOption = currOption + 1
                inputStallTimerDirectional = inputStallToDirectional
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
            if m.controller.stickY > 60 then
                currOption = currOption - 1
                inputStallTimerDirectional = inputStallToDirectional
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
            end
        end

        if inputStallTimerButton == 0 then
            if (m.controller.buttonPressed & A_BUTTON) ~= 0 then
                optionTable[currOption].toggle = optionTable[currOption].toggle + 1
                if optionTable[currOption].toggle > optionTable[currOption].toggleMax then optionTable[currOption].toggle = 0 end
                if optionTable[currOption].toggleSaveName ~= nil then
                    mod_storage_save(optionTable[currOption].toggleSaveName, tostring(optionTable[currOption].toggle))
                end
                inputStallTimerButton = inputStallToButton
                play_sound(SOUND_MENU_CHANGE_SELECT, cameraToObject)
            end
            if (m.controller.buttonPressed & B_BUTTON) ~= 0 then
                options = false
                inputStallTimerButton = inputStallToButton
            end
        end
        if currOption > #optionTable then currOption = 1 end
        if currOption < 1 then currOption = #optionTable end
        nullify_inputs(m)
    end
end

hook_event(HOOK_BEFORE_MARIO_UPDATE, before_mario_update)
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)

--------------
-- Commands --
--------------

promptedAreYouSure = false

local function chat_command(msg)
    msg = string_lower(msg)

    -- Open Menu Check
    if msg == "" or msg == "menu" then
        menu = not menu
        return true
    end

    -- Help Prompt Check
    if msg == "?" or msg == "help" then
        djui_chat_message_create("Character Select's Avalible Commands:" ..
        "\n\\#ffff33\\/char-select help\\#ffffff\\ - Returns Avalible Commands" ..
        "\n\\#ffff33\\/char-select menu\\#ffffff\\ - Opens the Menu" ..
        "\n\\#ffff33\\/char-select [name/num]\\#ffffff\\ - Switches to Character" ..
        "\n\\#ff3333\\/char-select reset\\#ffffff\\ - Resets your Save Data")
        return true
    end

    -- Reset Save Data Check
    if msg == "reset" or (msg == "confirm" and promptedAreYouSure) then
        reset_options(true)
        return true
    end

    -- Name Check
    for i = 1, #characterTable do
        if msg == string_lower(characterTable[i].name) or msg == string_underscore_to_space(string_lower(characterTable[i].saveName)) then
            currChar = i
            djui_chat_message_create('Character set to "' .. characterTable[i].name .. '" Successfully!')
            return true
        end
    end

    -- Number Check
    if tonumber(msg) then
        msg = tonumber(msg)
        if msg > 0 and msg <= #characterTable then
            currChar = msg
            djui_chat_message_create('Character set to "' .. characterTable[msg].name .. '" Successfully!')
            return true
        end
    end
    djui_chat_message_create("Character Not Found")
    return true
end

hook_chat_command("char-select", "- Opens the Character Select Menu", chat_command)