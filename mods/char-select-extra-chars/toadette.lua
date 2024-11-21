if not _G.charSelectExists then return end

local E_MODEL_TOADETTE = smlua_model_util_get_id("toadette_geo")

local TEX_TOADETTE = get_texture_info("toadette_icon")

VOICETABLE_TOADETTE = {
    [CHAR_SOUND_ATTACKED] = "toadette_attacked.ogg",
    [CHAR_SOUND_COUGHING1] = "toadette_coughing1.ogg",
    [CHAR_SOUND_COUGHING2] = "toadette_coughing2.ogg",
    [CHAR_SOUND_COUGHING3] = "toadette_coughing3.ogg",
    [CHAR_SOUND_DOH] = "toadette_doh.ogg",
    [CHAR_SOUND_DROWNING] = "toadette_drowning.ogg",
    [CHAR_SOUND_DYING] = "toadette_dying.ogg",
    [CHAR_SOUND_EEUH] = "toadette_euuh.ogg",
    [CHAR_SOUND_GROUND_POUND_WAH] = "toadette_ground_pound_wah.ogg",
    [CHAR_SOUND_HAHA] = "toadette_haha.ogg",
    [CHAR_SOUND_HAHA_2] = "toadette_haha2.ogg",
    [CHAR_SOUND_HERE_WE_GO] = "toadette_herewego.ogg",
    [CHAR_SOUND_HOOHOO] = "toadette_hoohoo.ogg",
    [CHAR_SOUND_HRMM] = "toadette_hrmm.ogg",
    [CHAR_SOUND_IMA_TIRED] = "toadette_imatired.ogg",
    [CHAR_SOUND_MAMA_MIA] = "toadette_mamamia.ogg",
    [CHAR_SOUND_LETS_A_GO] = "toadette_letsago.ogg",
    [CHAR_SOUND_ON_FIRE] = "toadette_on_fire.ogg",
    [CHAR_SOUND_OOOF] = "toadette_ooof.ogg",
    [CHAR_SOUND_OOOF2] = "toadette_ooof2.ogg",
    [CHAR_SOUND_PANTING] = "toadette_panting.ogg",
    [CHAR_SOUND_PANTING_COLD] = "toadette_panting_cold.ogg",
    [CHAR_SOUND_PUNCH_HOO] = "toadette_punch_hoo.ogg",
    [CHAR_SOUND_PUNCH_WAH] = "toadette_punch_wah.ogg",
    [CHAR_SOUND_PUNCH_YAH] = "toadette_punch_yah.ogg",
    [CHAR_SOUND_SO_LONGA_BOWSER] = "toadette_solonga_bowser.ogg",
    [CHAR_SOUND_SNORING1] = "toadette_snoring1.ogg",
    [CHAR_SOUND_SNORING2] = "toadette_snoring2.ogg",
    [CHAR_SOUND_SNORING3] = {"toadette_snoring2.ogg", "toadette_snoring1.ogg", "toadette_snoring3.ogg"},
    [CHAR_SOUND_TWIRL_BOUNCE] = "toadette_twirl_bounce.ogg",
    [CHAR_SOUND_UH] = "toadette_uh.ogg",
    [CHAR_SOUND_UH2] = "toadette_uh2.ogg",
    [CHAR_SOUND_UH2_2] = "toadette_uh2_2.ogg",
    [CHAR_SOUND_WAAAOOOW] = "toadette_waaaooow.ogg",
    [CHAR_SOUND_WAH2] = "toadette_ground_pound_wah.ogg",
    [CHAR_SOUND_WHOA] = "toadette_whoa.ogg",
    [CHAR_SOUND_YAHOO] = "toadette_yahoo.ogg",
    [CHAR_SOUND_YAWNING] = "toadette_yawning.ogg",
    [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "toadette_yahoo.ogg", "toadette_yahoo1.ogg", "toadette_yahoo2.ogg", "toadette_yahoo3.ogg", "toadette_yahoo4.ogg", "toadette_yahoo5.ogg" },
    [CHAR_SOUND_YAH_WAH_HOO] = { "toadette_yah_wah_hoo1.ogg", "toadette_yah_wah_hoo2.ogg", "toadette_yah_wah_hoo3.ogg"},
    [CHAR_SOUND_HELLO] = "toadette_hello.ogg"
}

--MAKING VOICE CLIPS FOR ATM. USE PLACEHOLDER VOICE CLIPS!
--[CHAR_SOUND_COUGHING1] = "peach_coughing1.ogg",
--[CHAR_SOUND_COUGHING2] = "peach_coughing2.ogg",
--[CHAR_SOUND_COUGHING3] = "peach_coughing3.ogg",
--[CHAR_SOUND_IMA_TIRED] = "peach_imatired.ogg",
--[CHAR_SOUND_ON_FIRE] = "peach_on_fire.ogg",
--[CHAR_SOUND_PANTING_COLD] = "peach_panting_cold.ogg",
--[CHAR_SOUND_SNORING1] = "peach_snoring1.ogg",
--[CHAR_SOUND_SNORING2] = "peach_snoring2.ogg",
--[CHAR_SOUND_SNORING3] = {"peach_snoring2.ogg", "peach_snoring1.ogg", "peach_snoring3.ogg"},
--[CHAR_SOUND_YAWNING] = "peach_yawning.ogg",
--[CHAR_SOUND_HELLO] = "peach_float.ogg",

local PALETTE_TOADETTE = {
    [PANTS]  = { r = 0xFF, g = 0xFF, b = 0xFF },
    [SHIRT]  = { r = 0xFF, g = 0x00, b = 0x00 },
    [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
    [SHOES]  = { r = 0x68, g = 0x40, b = 0x1B },
    [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
    [SKIN]   = { r = 0xFE, g = 0xD5, b = 0xA1 },
    [CAP]    = { r = 0xF3, g = 0x00, b = 0x80 },
    [EMBLEM] = { r = 0xF3, g = 0x00, b = 0x80 }
}

_G.CT_TOADETTE = _G.charSelect.character_add("Toadette", {"A very bubbly female toad", "who has a hobby of construction!", "Although she hates the union.", "Wonder why?", "", "Voiced by: Melissa Mekrose."}, "FluffaMario & AngelicMiracles", { r = 255, g = 70, b = 161 }, E_MODEL_TOADETTE, CT_TOAD, TEX_TOADETTE)
_G.charSelect.character_add_voice(E_MODEL_TOADETTE, VOICETABLE_TOADETTE)
_G.charSelect.character_add_palette_preset(E_MODEL_TOADETTE, PALETTE_TOADETTE)
