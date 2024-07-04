-- name: [CS] VL-Tone & Cjes Luigi
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

_G.charSelect.character_add("VL-Tone Luigi", {" A fanmade model of Luigi.", "The model was created for the", "program Toad's Tool 64, a romhack editor.", "This model is a nostalgic throwback to", "many players in the SM64 Community!"}, "VL-Tone", {r = 0, g = 152, b = 0}, E_MODEL_VL, CT_LUIGI, TEX_LUIGI)

_G.charSelect.character_add("Cjes Luigi", {"Another fanmade Luigi model.", "The model originates from Super", "Luigi 64 in 2015.", "This model originally was the", "main Luigi model for sm64ex-coop before", "the giga leak occured in 2020 and", "eventually replaced it." }, "Cjes", {r = 0, g = 152, b = 0}, E_MODEL_CJES, CT_LUIGI, TEX_LUIGI)
