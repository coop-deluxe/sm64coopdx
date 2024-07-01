if not _G.charSelectExists then return end

local E_MODEL_TOADETTE = smlua_model_util_get_id("toadette_geo")

local TEX_TOADETTE = get_texture_info("toadette_icon")

VOICETABLE_TOADETTE = {
    [CHAR_SOUND_ATTACKED] = "toadette_hurt_hard.ogg",
    [CHAR_SOUND_GROUND_POUND_WAH] = "toadette_yah.ogg",
    [CHAR_SOUND_HAHA] = "toadette_haahaa.ogg",
    [CHAR_SOUND_HAHA_2] = "toadette_haahaa.ogg",
    [CHAR_SOUND_HERE_WE_GO] = "toadette_here_we_go.ogg",
    [CHAR_SOUND_HOOHOO] = "toadette_hoo.ogg",
    [CHAR_SOUND_ON_FIRE] = "toadette_burning.ogg",
    [CHAR_SOUND_OOOF] = "toadette_oof.ogg",
    [CHAR_SOUND_OOOF2] = "toadette_oof2.ogg",
    [CHAR_SOUND_PUNCH_HOO] = "toadette_hoo.ogg",
    [CHAR_SOUND_PUNCH_WAH] = "toadette_wah.ogg",
    [CHAR_SOUND_PUNCH_YAH] = "toadette_yah.ogg",
    [CHAR_SOUND_SO_LONGA_BOWSER] = "toadette_bowser.ogg",
    [CHAR_SOUND_TWIRL_BOUNCE] = "toadette_boing.ogg",
    [CHAR_SOUND_WAAAOOOW] = "toadette_fall.ogg",
    [CHAR_SOUND_WAH2] = "toadette_wah.ogg",
    [CHAR_SOUND_WHOA] = "toadette_woah.ogg",
    [CHAR_SOUND_YAHOO] = "toadette_yahoo.ogg",
    [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = {"toadette_yahoo.ogg", "toadette_yippee.ogg"},
    [CHAR_SOUND_YAH_WAH_HOO] = {"toadette_yah.ogg", "toadette_wah.ogg", "toadette_hoo.ogg"},
    [CHAR_SOUND_OKEY_DOKEY] = "toadette_okay.ogg",
    [CHAR_SOUND_LETS_A_GO] = "toadette_okay.ogg",
    [CHAR_SOUND_DYING] = "toadette_dead.ogg",
    [CHAR_SOUND_DROWNING] = "toadette_drowning.ogg",
    [CHAR_SOUND_EEUH] = "toadette_pickup.ogg",
    [CHAR_SOUND_MAMA_MIA] = "toadette_ooh.ogg",
    [CHAR_SOUND_DOH] = "toadette_oof.ogg",
    [CHAR_SOUND_HRMM] = "toadette_pickup.ogg",
    [CHAR_SOUND_PANTING] = "toadette_pant",
    [CHAR_SOUND_UH] = "toadette_oof_3.ogg",
    [CHAR_SOUND_UH2] = "toadette_oof_4.ogg",
    [CHAR_SOUND_UH2_2] = "toadette_oof_5.ogg"
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
    [HAIR]   = { r = 0xFF, g = 0x00, b = 0x00 },
    [SKIN]   = { r = 0xFE, g = 0xD5, b = 0xA1 },
    [CAP]    = { r = 0xF3, g = 0x00, b = 0x80 },
    [EMBLEM] = { r = 0xF3, g = 0x00, b = 0x80 }
}

CT_TOADETTE = _G.charSelect.character_add("Toadette", {"A female toad who debutted in", "2003 as a partner for Toad in", "Mario Kart: Double Dash!"}, "FluffaMario & AngelicMiracles", { r = 255, g = 70, b = 161 }, E_MODEL_TOADETTE, CT_TOAD, TEX_TOADETTE)
_G.charSelect.character_add_voice(E_MODEL_TOADETTE, VOICETABLE_TOADETTE)
_G.charSelect.character_add_palette_preset(E_MODEL_TOADETTE, PALETTE_TOADETTE)