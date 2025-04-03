-- name: [CS] VL-Tone & Cjes Luigi
-- description: [CS] \\#00ff00\\VL-Tone \\#dcdcdc\\& \\#00ff00\\Cjes Luigi\n\\#dcdcdc\\By: Coop Deluxe Team\n\nReturn of TWO nostalgic Luigi's dating back to the 2000s!\n\n\\#00ff00\\Model Credits:\n\\#dcdcdc\\VL-Tone\nCJes\n\n\\#00ff00\\Model Porting:\n\\#dcdcdc\\AngelicMiracles "Yuyake"\nFluffaMario\nSonicDark

local MOD_NAME = "VL & Cjes Luigi"

if not _G.charSelectExists then
    djui_popup_create("\\#ffffa0\\"..MOD_NAME.." requires\nCharacter Select to be enabled.\n\nPlease rehost with it enabled.", 4)
    return
end

-- localize functions to improve performance
local table_insert,play_sound,djui_hud_get_screen_width,maxf,math_sin,djui_hud_set_color,djui_hud_set_font,string_format,djui_hud_measure_text,djui_hud_print_text,djui_hud_set_resolution,min,math_min,math_max,djui_hud_set_rotation,djui_hud_render_rect = table.insert,play_sound,djui_hud_get_screen_width,maxf,math.sin,djui_hud_set_color,djui_hud_set_font,string.format,djui_hud_measure_text,djui_hud_print_text,djui_hud_set_resolution,min,math.min,math.max,djui_hud_set_rotation,djui_hud_render_rect

local E_MODEL_VL = smlua_model_util_get_id("vl_geo")
local E_MODEL_CJES = smlua_model_util_get_id("cjes_geo")

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
local CT_VL = 0
local function on_character_select_load()
    CT_VL = _G.charSelect.character_add("VL and Cjes", {"A Fanmade model of Luigi that", "are a big nostalgic throwback for", "the Super Mario 64 community!", "", "VL was created as an easter egg", "for Toads Tool 64, a level editor", "released back in 2007!",}, "VL-Tone", PALETTE_VL[CAP], E_MODEL_VL, CT_LUIGI, "L")
    _G.charSelect.character_edit(CT_VL, "VL Luigi")
    _G.charSelect.character_add_costume(CT_VL, "Cjes Luigi", {"A Fanmade model of Luigi that", "are a big nostalgic throwback for", "the Super Mario 64 community!", "", "Cjes was the original model for", "SM64EX-Coop before it was", "eventually replaced."}, "Cjes", PALETTE_CJES[CAP], E_MODEL_CJES, CT_LUIGI, gTextures.luigi_head)
    _G.charSelect.character_add_palette_preset(E_MODEL_VL, PALETTE_VL)
    _G.charSelect.character_add_palette_preset(E_MODEL_CJES, PALETTE_CJES)
end

hook_event(HOOK_ON_MODS_LOADED, on_character_select_load)