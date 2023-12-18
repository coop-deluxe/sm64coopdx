-- name: [CS] Vl and Cjes Luigi
-- description: A character swap mod using the Character Select's API.

local E_MODEL_VL = smlua_model_util_get_id("vl_geo")
local E_MODEL_CJES = smlua_model_util_get_id("cjes_geo")

local TEXT_MOD_NAME = "Vl and Cjes Luigi"

local TEX_LUIGI = get_texture_info("luigi-icon")

if _G.charSelectExists then
    _G.charSelect.character_add("VL Luigi", {" A fanmade model of Luigi.", "The model was created for the", "program Toad's Tool 64, a romhack editor.", "This model is a nostalgic throwback to", "many players in the SM64 Community!"}, "VL Tone", {r = 0, g = 152, b = 0}, E_MODEL_VL, CT_LUIGI, TEX_LUIGI)
    _G.charSelect.character_add("Cjes Luigi", {"Another fanmade Luigi model.", "The model originates from Super", "Luigi 64 in 2015.", "This model originally was the", "main Luigi model for ex-Coop before", "the giga leak occured in 2020 and", "eventually replaced it." }, "Cjes", {r = 0, g = 152, b = 0}, E_MODEL_CJES, CT_LUIGI, TEX_LUIGI)
else
    djui_popup_create("\\#ffffdc\\\n"..TEXT_MOD_NAME.."\nRequires the Character Select Mod\nto use as a Library!\n\nPlease turn on the Character Select Mod\nand Restart the Room!", 6)        
end