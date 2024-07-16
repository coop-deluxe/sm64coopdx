-- name: [CS] \\#00ff00\\VL-Tone & Cjes Luigi
-- description: [CS] VL-Tone & Cjes Luigi\nBy Coop Deluxe Team\n\nnThis Character Select pack adds VL-Tone Luigi and Cjes Luigi, who was originally the model for luigi in earlier versions of sm64ex-coop.

if not _G.charSelectExists then
    local first = false
    hook_event(HOOK_ON_LEVEL_INIT, function()
        if not first then
            first = true
            play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
            djui_chat_message_create("\\#ffffa0\\Extra Characters requires Character Select to be enabled.\nPlease rehost with it enabled.")
        end
    end)
    return
end

local E_MODEL_VL = smlua_model_util_get_id("vl_geo")
local E_MODEL_CJES = smlua_model_util_get_id("cjes_geo")

local TEXT_MOD_NAME = "VL-Tone & Cjes Luigi"

local TEX_LUIGI = get_texture_info("luigi-icon")

local PALETTE_VL =  {
    [PANTS]  = {r = 0x20, g = 0x14, b = 0x7c}, -- 20147C
    [SHIRT]  = {r = 0x00, g = 0x98, b = 0x00}, -- 009800
    [GLOVES] = {r = 0xff, g = 0xff, b = 0xff}, -- FFFFFF
    [SHOES]  = {r = 0x48, g = 0x20, b = 0x18}, -- 482018
    [HAIR]   = {r = 0x68, g = 0x24, b = 0x14}, -- 682414
    [SKIN]   = {r = 0xfe, g = 0xc1, b = 0x79}, -- FEC179
    [CAP]    = {r = 0x00, g = 0x98, b = 0x00}, -- 009800
    [EMBLEM] = {r = 0x00, g = 0x98, b = 0x00}, -- 009800
}

local PALETTE_CJES =  {
    [PANTS]  = {r = 0x00, g = 0x00, b = 0xff}, -- 0000FF
    [SHIRT]  = {r = 0x00, g = 0x8c, b = 0x00}, -- 008C00
    [GLOVES] = {r = 0xff, g = 0xff, b = 0xff}, -- FFFFFF
    [SHOES]  = {r = 0x50, g = 0x16, b = 0x07}, -- 501607
    [HAIR]   = {r = 0x73, g = 0x06, b = 0x00}, -- 730600
    [SKIN]   = {r = 0xfe, g = 0xc1, b = 0x79}, -- FEC179
    [CAP]    = {r = 0x00, g = 0x8c, b = 0x00}, -- 008C00
    [EMBLEM] = {r = 0x00, g = 0x8c, b = 0x00}, -- 008C00
}

CT_VL_LUIGI   = _G.charSelect.character_add("VL-Tone Luigi", {" A fanmade model of Luigi.", "The model was created for the", "program Toad's Tool 64, a romhack editor.", "This model is a nostalgic throwback to", "many players in the SM64 Community!"}, "VL-Tone", {r = 0, g = 152, b = 0}, E_MODEL_VL, CT_LUIGI, TEX_LUIGI)
CT_CJES_LUIGI = _G.charSelect.character_add("Cjes Luigi", {"Another fanmade Luigi model.", "The model originates from Super", "Luigi 64 in 2015.", "This model originally was the", "main Luigi model for sm64ex-coop before", "the giga leak occured in 2020 and", "eventually replaced it." }, "Cjes", {r = 0, g = 140, b = 0}, E_MODEL_CJES, CT_LUIGI, TEX_LUIGI)

_G.charSelect.character_add_palette_preset(E_MODEL_VL, PALETTE_VL)
_G.charSelect.character_add_palette_preset(E_MODEL_CJES, PALETTE_CJES)