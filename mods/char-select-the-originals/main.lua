-- name: [CS] \\#00AAFF\\The Originals
-- description: The Originals\nBy Coop Deluxe Team\n\nDid you ever want to play as older models of characters from other multiplayer SM64 hacks? Well, now you can!\n\nEnjoy playing as your favorite mario characters with nostalgic looks coming straight from the good ol' days of Multiplayer SM64.

local MOD_NAME = "\\#00AAFF\\The Originals"

if not charSelectExists then
    djui_popup_create(MOD_NAME.." \\#ffffa0\\requires\nCharacter Select to be enabled.\n\nPlease rehost with it enabled.", 4)
    return
end

-- localize functions to improve performance
local table_insert,play_sound,djui_hud_get_screen_width,maxf,math_sin,djui_hud_set_color,djui_hud_set_font,string_format,djui_hud_measure_text,djui_hud_print_text,djui_hud_set_resolution,min,math_min,math_max,djui_hud_set_rotation,djui_hud_render_rect = table.insert,play_sound,djui_hud_get_screen_width,maxf,math.sin,djui_hud_set_color,djui_hud_set_font,string.format,djui_hud_measure_text,djui_hud_print_text,djui_hud_set_resolution,min,math.min,math.max,djui_hud_set_rotation,djui_hud_render_rect

-- Models --

local E_MODEL_VL_TONE_LUIGI = smlua_model_util_get_id("vl_tone_luigi_geo")
local E_MODEL_CJ_LUIGI = smlua_model_util_get_id("cj_luigi_geo")
local E_MODEL_DJOSLIN_TOAD = smlua_model_util_get_id("djoslin_toad_geo")
local E_MODEL_FLUFFA_WARIO = smlua_model_util_get_id("fluffa_wario_geo")
local E_MODEL_KEEB_WALUIGI = smlua_model_util_get_id("keeb_waluigi_geo")
local E_MODEL_FLUFFA_WALUIGI = smlua_model_util_get_id("fluffa_waluigi_geo")

-- Textures --

local TEX_VL_TONE_LUIGI = get_texture_info("vl-tones-luigi")
local TEX_CJ_LUIGI = get_texture_info("cjes-luigi")
local TEX_DJOSLIN_TOAD = get_texture_info("djoslin-toad")
local TEX_FLUFFA_WARIO = get_texture_info("fluffa-wario")
local TEX_KEEB_WALUIGI = get_texture_info("keeb-waluigi")
local TEX_FLUFFA_WALUIGI = get_texture_info("fluffa-waluigi")

-- Palettes --

local PALETTE_VL_LUIGI = {
    [PANTS]  = { r = 0x20, g = 0x14, b = 0x7C }, -- 20147C
    [SHIRT]  = { r = 0x00, g = 0x98, b = 0x00 }, -- 009800
    [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF }, -- FFFFFF
    [SHOES]  = { r = 0x48, g = 0x20, b = 0x18 }, -- 482018
    [HAIR]   = { r = 0x68, g = 0x24, b = 0x14 }, -- 682414
    [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 }, -- FEC179
    [CAP]    = { r = 0x00, g = 0x98, b = 0x00 }, -- 009800
    [EMBLEM] = { r = 0x00, g = 0x98, b = 0x00 }, -- 009800
}

local PALETTE_CJ_LUIGI = {
    [PANTS]  = { r = 0x00, g = 0x00, b = 0xFF }, -- 0000FF
    [SHIRT]  = { r = 0x00, g = 0x8C, b = 0x00 }, -- 008C00
    [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF }, -- FFFFFF
    [SHOES]  = { r = 0x50, g = 0x16, b = 0x07 }, -- 501607
    [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 }, -- 730600
    [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 }, -- FEC179
    [CAP]    = { r = 0x00, g = 0x8C, b = 0x00 }, -- 008C00
    [EMBLEM] = { r = 0x00, g = 0x8C, b = 0x00 }, -- 008C00
}

local PALETTE_DJ_TOAD = {
    [PANTS]  = { r = 0xFF, g = 0xFF, b = 0xFF }, -- FFFFFF
    [SHIRT]  = { r = 0x4C, g = 0x2C, b = 0xD3 }, -- 4C2CD3
    [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF }, -- FFFFFF
    [SHOES]  = { r = 0x68, g = 0x40, b = 0x1B }, -- 68401B
    [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 }, -- 730600
    [SKIN]   = { r = 0xFE, g = 0xD5, b = 0xA1 }, -- FED5A1
    [CAP]    = { r = 0xFF, g = 0x00, b = 0x00 }, -- FF0000
    [EMBLEM] = { r = 0xFF, g = 0xFF, b = 0xFF }, -- FF0000
}

local PALETTE_FL_WARIO = {
    [PANTS]  = { r = 0x91, g = 0x00, b = 0xB2 }, -- 9100B2
    [SHIRT]  = { r = 0xFF, g = 0xC0, b = 0x00 }, -- FFC000
    [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF }, -- FFFFFF
    [SHOES]  = { r = 0x00, g = 0x80, b = 0x00 }, -- 008000
    [HAIR]   = { r = 0x70, g = 0x50, b = 0x00 }, -- 705000
    [SKIN]   = { r = 0xFF, g = 0xC0, b = 0x80 }, -- FFC080
    [CAP]    = { r = 0xFF, g = 0xC0, b = 0x00 }, -- FFC000
    [EMBLEM] = { r = 0x30, g = 0x60, b = 0xFF }, -- 3060FF
}

local PALETTE_KB_WALUIGI = {
    [PANTS]  = { r = 0x08, g = 0x10, b = 0x20 }, -- 081020
    [SHIRT]  = { r = 0x60, g = 0x00, b = 0xC0 }, -- 6000C0
    [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF }, -- FFFFFF
    [SHOES]  = { r = 0xFF, g = 0x60, b = 0x00 }, -- FF6000
    [HAIR]   = { r = 0x70, g = 0x50, b = 0x00 }, -- 705000
    [SKIN]   = { r = 0xF0, g = 0xA0, b = 0x60 }, -- F0A060
    [CAP]    = { r = 0x60, g = 0x00, b = 0xC0 }, -- 6000C0
    [EMBLEM] = { r = 0xFF, g = 0xFF, b = 0x00 }, -- FFFF00
}

local PALETTE_FL_WALUIGI = {
    [PANTS]  = { r = 0x15, g = 0x1A, b = 0x29 }, -- 151A29
    [SHIRT]  = { r = 0x66, g = 0x2C, b = 0xAD }, -- 662CAD
    [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF }, -- FFFFFF
    [SHOES]  = { r = 0xFC, g = 0x7A, b = 0x00 }, -- FC7A00
    [HAIR]   = { r = 0x63, g = 0x4A, b = 0x00 }, -- 634A00
    [SKIN]   = { r = 0xDF, g = 0xA1, b = 0x6A }, -- DFA16A
    [CAP]    = { r = 0x66, g = 0x2C, b = 0xAD }, -- 662CAD
    [EMBLEM] = { r = 0xFF, g = 0xF5, b = 0x00 }, -- FFF500
}

-- Sounds --

local DJ_TOAD_SOUNDS = {
    SOUND_MARIO_YAH_WAH_HOO,
    SOUND_MARIO_HOOHOO,
    SOUND_MARIO_YAHOO,
    SOUND_MARIO_UH,
    SOUND_MARIO_HRMM,
    SOUND_MARIO_WAH2,
    SOUND_MARIO_WHOA,
    SOUND_MARIO_EEUH,
    SOUND_MARIO_ATTACKED,
    SOUND_MARIO_OOOF,
    SOUND_MARIO_OOOF2,
    SOUND_MARIO_HERE_WE_GO,
    SOUND_MARIO_YAWNING,
    SOUND_MARIO_SNORING1,
    SOUND_MARIO_SNORING2,
    SOUND_MARIO_WAAAOOOW,
    SOUND_MARIO_HAHA,
    SOUND_MARIO_HAHA_2,
    SOUND_MARIO_UH2,
    SOUND_MARIO_UH2_2,
    SOUND_MARIO_ON_FIRE,
    SOUND_MARIO_DYING,
    SOUND_MARIO_PANTING_COLD,
    SOUND_MARIO_PANTING,
    SOUND_MARIO_COUGHING1,
    SOUND_MARIO_COUGHING2,
    SOUND_MARIO_COUGHING3,
    SOUND_MARIO_PUNCH_YAH,
    SOUND_MARIO_PUNCH_HOO,
    SOUND_MARIO_MAMA_MIA,
    SOUND_MARIO_GROUND_POUND_WAH,
    SOUND_MARIO_DROWNING,
    SOUND_MARIO_PUNCH_WAH,
    SOUND_MARIO_YAHOO_WAHA_YIPPEE,
    SOUND_MARIO_DOH,
    SOUND_MARIO_GAME_OVER,
    SOUND_MARIO_HELLO,
    SOUND_MARIO_PRESS_START_TO_PLAY,
    SOUND_MARIO_TWIRL_BOUNCE,
    SOUND_MARIO_SNORING3,
    SOUND_MARIO_SO_LONGA_BOWSER,
    SOUND_MARIO_IMA_TIRED,
    SOUND_MARIO_LETS_A_GO,
    SOUND_MARIO_OKEY_DOKEY
}

-- Loading Characters --

local function on_character_select_load()
    _G.CT_OGS_LUIGI = charSelect.character_add("VL-Tone Luigi", {"The Originals' Luigi", "Quite a throwback to the good ol' days", "of the Super Mario 64 community!", "", "VL-Tone Luigi was created as an easter egg", "for Toads Tool 64, an SM64 level editor", "released back in 2007!",}, "VL-Tone", PALETTE_VL_LUIGI[CAP], E_MODEL_VL_TONE_LUIGI, CT_LUIGI, TEX_VL_TONE_LUIGI)
    charSelect.character_add_costume(CT_OGS_LUIGI, "Cjes Luigi", {"The Originals' Luigi", "Quite a throwback to the good ol' days", "of the Super Mario 64 community!", "", "Cjes Luigi was originally used in", "SM64EX-Coop before he was", "eventually replaced."}, "Cjes", PALETTE_CJ_LUIGI[CAP], E_MODEL_CJ_LUIGI, CT_LUIGI, TEX_CJ_LUIGI)
    _G.CT_OGS_TOAD = charSelect.character_add("Djoslin Toad", {"The Originals' Toad", "Known by all the SM64EX-COOP veterans.", "", "Djoslin Toad was created by djoslin0", "for SM64EX-COOP (currently SM64COOPDX)", "before eventually being replaced", "with an improved model.", "Fun fact:", "djoslin0 originally created the model", "by editing the original Toad actor", "in Notepad, earning him the name", "\"Notepad Toad\""}, "Djoslin0", PALETTE_DJ_TOAD[SHIRT], E_MODEL_DJOSLIN_TOAD, CT_TOAD, TEX_DJOSLIN_TOAD, 0.8)
    _G.CT_OGS_WARIO = charSelect.character_add("Fluffa Wario", {"The Originals' Wario", "Quite a throwback to the good ol' days", "of the Super Mario 64 community!", "", "Fluffa Wario (Net64 Ver) was created", "for use in the most popular way to play", "multiplayer before SM64COOPDX,", "Net64.", "He may be the most iconic SM64 Wario", "with his stylish look that resembles", "his Mario Party series look."}, "FluffaMario", PALETTE_FL_WARIO[CAP], E_MODEL_FLUFFA_WARIO, CT_WARIO, TEX_FLUFFA_WARIO)
    _G.CT_OGS_WALUIGI = charSelect.character_add("Keeb Waluigi", {"The Originals' Waluigi", "Known by all the SM64EX-COOP veterans.", "", "Keeb Waluigi was created by keeberghrh", "for SM64EX-COOP (currently SM64COOPDX)", "and was still in use past SM64COOPDX", "before eventually being replaced", "with a new model."}, "Keeberghrh", PALETTE_KB_WALUIGI[CAP], E_MODEL_KEEB_WALUIGI, CT_WALUIGI, TEX_KEEB_WALUIGI)
    charSelect.character_add_costume(CT_OGS_WALUIGI, "Fluffa Waluigi", {"The Originals' Waluigi", "Quite a throwback to the good ol' days", "of the Super Mario 64 community!", "", "Fluffa Waluigi (Net64 Ver) was created", "for use in the most popular way to play", "multiplayer before SM64COOPDX,", "Net64.",  "He sports a look the resembles", "his Mario Party series look."}, "FluffaMario", PALETTE_FL_WALUIGI[CAP], E_MODEL_FLUFFA_WALUIGI, CT_WALUIGI, TEX_FLUFFA_WALUIGI, 1.1)
    charSelect.character_add_palette_preset(E_MODEL_VL_TONE_LUIGI, PALETTE_VL_LUIGI)
    charSelect.character_add_palette_preset(E_MODEL_CJ_LUIGI, PALETTE_CJ_LUIGI)
    charSelect.character_add_palette_preset(E_MODEL_DJOSLIN_TOAD, PALETTE_DJ_TOAD)
    charSelect.character_add_palette_preset(E_MODEL_FLUFFA_WARIO, PALETTE_FL_WARIO)
    charSelect.character_add_palette_preset(E_MODEL_KEEB_WALUIGI, PALETTE_KB_WALUIGI)
    charSelect.character_add_palette_preset(E_MODEL_FLUFFA_WALUIGI, PALETTE_FL_WALUIGI)
end

-- Djoslin Toad Sound
--- @param m MarioState
--- @param sound CharacterSound
local function character_sound(m, sound)
    if obj_get_model_id_extended(m.marioObj) == E_MODEL_DJOSLIN_TOAD then
        play_sound_with_freq_scale(DJ_TOAD_SOUNDS[sound + 1], m.marioObj.header.gfx.cameraToObject, 1.25)
        return NO_SOUND
    end
end

hook_event(HOOK_ON_MODS_LOADED, on_character_select_load)
hook_event(HOOK_CHARACTER_SOUND, character_sound)