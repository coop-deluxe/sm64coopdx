-- name: [CS] VL-Tone & Cjes Luigi
-- description: [CS] \\#00ff00\\VL-Tone \\#dcdcdc\\& \\#00ff00\\Cjes Luigi\n\\#dcdcdc\\By: Coop Deluxe Team\n\nReturn of TWO nostalgic Luigi's dating back to the 2000s!\n\n\\#00ff00\\Model Credits:\n\\#dcdcdc\\VL-Tone\nCJes\n\n\\#00ff00\\Model Porting:\n\\#dcdcdc\\AngelicMiracles "Yuyake"\nFluffaMario\nSonicDark

-- localize functions to improve performance
local table_insert,play_sound,djui_hud_get_screen_width,maxf,math_sin,djui_hud_set_color,djui_hud_set_font,string_format,djui_hud_measure_text,djui_hud_print_text,djui_hud_set_resolution,min,math_min,math_max,djui_hud_set_rotation,djui_hud_render_rect = table.insert,play_sound,djui_hud_get_screen_width,maxf,math.sin,djui_hud_set_color,djui_hud_set_font,string.format,djui_hud_measure_text,djui_hud_print_text,djui_hud_set_resolution,min,math.min,math.max,djui_hud_set_rotation,djui_hud_render_rect

local PALETTE_VL =  {
    [PANTS]  = { r = 0x20, g = 0x14, b = 0x7c }, -- 20147C
    [SHIRT]  = { r = 0x00, g = 0x98, b = 0x00 }, -- 009800
    [GLOVES] = { r = 0xff, g = 0xff, b = 0xff }, -- FFFFFF
    [SHOES]  = { r = 0x48, g = 0x20, b = 0x18 }, -- 482018
    [HAIR]   = { r = 0x68, g = 0x24, b = 0x14 }, -- 682414
    [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 }, -- FEC179
    [CAP]    = { r = 0x00, g = 0x98, b = 0x00 }, -- 009800
    [EMBLEM] = { r = 0x00, g = 0x98, b = 0x00 }, -- 009800
}

local PALETTE_CJES =  {
    [PANTS]  = { r = 0x00, g = 0x00, b = 0xff }, -- 0000FF
    [SHIRT]  = { r = 0x00, g = 0x8c, b = 0x00 }, -- 008C00
    [GLOVES] = { r = 0xff, g = 0xff, b = 0xff }, -- FFFFFF
    [SHOES]  = { r = 0x50, g = 0x16, b = 0x07 }, -- 501607
    [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 }, -- 730600
    [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 }, -- FEC179
    [CAP]    = { r = 0x00, g = 0x8c, b = 0x00 }, -- 008C00
    [EMBLEM] = { r = 0x00, g = 0x8c, b = 0x00 }, -- 008C00
}

local CT_VL_AND_CJES = _G.charSelect.character_add("VL & Cjes", "Fanmade models of Luigi that are a big nostalgic throwback to the Super Mario 64 fan community! VL was created as an easter egg for Toads Tool 64, a romhack editor. Cjes was the original model for sm64ex-coop before it was eventually replaced.", "VL-Tone and Cjes", {r = 0, g = 152, b = 0}, E_MODEL_VL, CT_LUIGI, gTextures.luigi_head)
_G.charSelect.character_add_palette_preset(E_MODEL_VL, PALETTE_VL)
_G.charSelect.character_add_palette_preset(E_MODEL_CJES, PALETTE_CJES)

--------------------------------------------
--- Alt Costume code from Paper Partners ---
------------ Modified by Squishy -----------
--------------------------------------------

local character_edit = _G.charSelect.character_edit
local character_get_current_number = _G.charSelect.character_get_current_number
local character_get_current_table = _G.charSelect.character_get_current_table
local get_options_status = _G.charSelect.get_options_status
local get_menu_color = _G.charSelect.get_menu_color
local hook_render_in_menu = _G.charSelect.hook_render_in_menu

local altCostumes = {
    [CT_VL_AND_CJES] = {
        currSkin = 1,
        { name = " VL ", model = E_MODEL_VL },
        { name = " CJES ", model = E_MODEL_CJES }
    }
}

local function update_character_skin(currChar, currAlt)
    local currSkin = altCostumes[currChar][currAlt]
    if altCostumes[currChar].desc == nil then
        altCostumes[currChar].desc = character_get_current_table().description
    end
    local description = {}
    for i = 1, #altCostumes[currChar].desc do
        table_insert(description, altCostumes[currChar].desc[i])
    end
    if currSkin.name ~= "" then
        table_insert(description, "")
        table_insert(description, "Current Outfit: "..currSkin.name)
    end
    character_edit(currChar, nil, description, nil, nil, currSkin.model, nil, nil)
    local cameraToObject = gMarioStates[0].marioObj.header.gfx.cameraToObject
    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, cameraToObject)
end

local inputLockTimer = 0
local buttonAnimTimer = 0

local latencyValueTable = { 12, 6, 3 }

local function hud_render()
    local width = djui_hud_get_screen_width() + 1.4
    local widthScale = maxf(width, 321.4) / 320
    local currChar = character_get_current_number()
    local charColors = character_get_current_table().color

    -- mimick button swaying, which is missing from the paper code
    local buttonAnim = 0
    local charSelectAnim = get_options_status(_G.charSelect.optionTableRef.anims)
    if charSelectAnim > 0 then
        buttonAnimTimer = buttonAnimTimer + 1
        buttonAnim = math_sin(buttonAnimTimer * 0.05) * 2.5 + 5
    else
        buttonAnim = 10
    end

    local inputLockTimerTo = latencyValueTable[get_options_status(_G.charSelect.optionTableRef.inputLatency) + 1]

    if altCostumes[currChar] ~= nil then
        -- render Mod Variond under CS version
        local menuColor = get_menu_color()
        djui_hud_set_color(menuColor.r, menuColor.g, menuColor.b, 255)
        djui_hud_set_font(FONT_TINY)
        local str = string_format("VL-Tone & Cjes Luigi (%s)", MOD_VERSION)
        djui_hud_print_text(str, width - 5 - djui_hud_measure_text(str) * 0.5, 3, 0.5)

        ---@type Controller
        local c = _G.charSelect.controller
        local currAlts = altCostumes[currChar]

        djui_hud_set_font(FONT_NORMAL)
        djui_hud_set_resolution(RESOLUTION_N64)
        local inputLockTimerAnim = 0

        local buttonX = 20 * widthScale + buttonAnim
        local x1 = buttonX - 4
        local x2 = x1 + 73
        local y = 97

        if charSelectAnim > 0 then
            inputLockTimerAnim = inputLockTimer / inputLockTimerTo * 3
            x1 = x1 + math_min(inputLockTimerAnim, 0)
            x2 = x2 + math_max(inputLockTimerAnim, 0)
        end

        -- left Arrow
        if currAlts.currSkin > 1 then
            djui_hud_set_color(charColors.r, charColors.g, charColors.b, 255)
            djui_hud_set_rotation(0x2000, 0.5, 0.5)
            djui_hud_render_rect(x1, y, 5, 5)
            djui_hud_set_color(0, 0, 0, 255)
            djui_hud_set_rotation(0, 0.5, 0.5)
            djui_hud_render_rect(x1 + 2.5, y - 2, 6, 8)
            djui_hud_set_color(charColors.r, charColors.g, charColors.b, 255)
            djui_hud_render_rect(buttonX, y - 3, 1, 10)

            if inputLockTimer == 0 and (c.buttonDown & L_JPAD ~= 0 or c.stickX < -0.5) then
                currAlts.currSkin = math_max(currAlts.currSkin - 1, 1)
                update_character_skin(currChar, currAlts.currSkin)
                inputLockTimer = -inputLockTimerTo
            end
        end

        -- right Arrow
        if currAlts.currSkin < #currAlts then
            -- changed arrows to mimick the ones seen in the options menu
            djui_hud_set_color(charColors.r, charColors.g, charColors.b, 255)
            djui_hud_set_rotation(0x2000, 0.5, 0.5)
            djui_hud_render_rect(x2, y, 5, 5)
            djui_hud_set_color(0, 0, 0, 255)
            djui_hud_set_rotation(0, 0.5, 0.5)
            djui_hud_render_rect(x2 - 3.5, y - 2, 6, 8)
            djui_hud_set_color(charColors.r, charColors.g, charColors.b, 255)
            djui_hud_render_rect(buttonX + 69, y - 3, 1, 10)

            if inputLockTimer == 0 and (c.buttonDown & R_JPAD ~= 0 or c.stickX > 0.5) then
                currAlts.currSkin = currAlts.currSkin + 1
                update_character_skin(currChar, currAlts.currSkin)
                inputLockTimer = inputLockTimerTo
            end
        end

        -- use an input lock to prevent cycling too fast
        if inputLockTimer > 0 then
            inputLockTimer = inputLockTimer - 1
        elseif inputLockTimer < 0 then
            inputLockTimer = inputLockTimer + 1
        end
    end
end

hook_render_in_menu(hud_render)