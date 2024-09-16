if not _G.charSelectExists then return end

local E_MODEL_YOSHI_PLAYER = smlua_model_util_get_id("yoshi_player_geo")

local TEX_YOSHI = get_texture_info("yoshi-icon")

VOICETABLE_YOSHI = {
    [CHAR_SOUND_ATTACKED] = "yoshi_attacked.ogg",
    [CHAR_SOUND_COUGHING1] = "yoshi_coughing1.ogg",
    [CHAR_SOUND_COUGHING2] = "yoshi_coughing2.ogg",
    [CHAR_SOUND_COUGHING3] = "yoshi_coughing3.ogg",
    [CHAR_SOUND_DOH] = "yoshi_doh.ogg",
    [CHAR_SOUND_DROWNING] = "yoshi_drowning.ogg",
    [CHAR_SOUND_DYING] = "yoshi_dying.ogg",
    [CHAR_SOUND_EEUH] = "yoshi_euuh.ogg",
    [CHAR_SOUND_GROUND_POUND_WAH] = "yoshi_ground_pound_wah.ogg",
    [CHAR_SOUND_HAHA] = "yoshi_haha.ogg",
    [CHAR_SOUND_HAHA_2] = "yoshi_haha2.ogg",
    [CHAR_SOUND_HERE_WE_GO] = "yoshi_herewego.ogg",
    [CHAR_SOUND_HOOHOO] = "yoshi_hoohoo.ogg",
    [CHAR_SOUND_HRMM] = "yoshi_hrmm.ogg",
    [CHAR_SOUND_IMA_TIRED] = "yoshi_imatired.ogg",
    [CHAR_SOUND_MAMA_MIA] = "yoshi_mamamia.ogg",
    [CHAR_SOUND_LETS_A_GO] = "yoshi_letsago.ogg",
    [CHAR_SOUND_ON_FIRE] = "yoshi_on_fire.ogg",
    [CHAR_SOUND_OOOF] = "yoshi_ooof.ogg",
    [CHAR_SOUND_OOOF2] = "yoshi_ooof2.ogg",
    [CHAR_SOUND_PANTING] = "yoshi_panting.ogg",
    [CHAR_SOUND_PANTING_COLD] = "yoshi_panting_cold.ogg",
    [CHAR_SOUND_PUNCH_HOO] = "yoshi_punch_hoo.ogg",
    [CHAR_SOUND_PUNCH_WAH] = "yoshi_punch_wah.ogg",
    [CHAR_SOUND_PUNCH_YAH] = "yoshi_punch_yah.ogg",
    [CHAR_SOUND_SO_LONGA_BOWSER] = "yoshi_solonga_bowser.ogg",
    [CHAR_SOUND_SNORING1] = "yoshi_snoring1.ogg",
    [CHAR_SOUND_SNORING2] = "yoshi_snoring2.ogg",
    [CHAR_SOUND_SNORING3] = { "yoshi_snoring2.ogg", "yoshi_snoring1.ogg", "yoshi_snoring3.ogg" },
    [CHAR_SOUND_TWIRL_BOUNCE] = "yoshi_twirl_bounce.ogg",
    [CHAR_SOUND_UH] = "yoshi_uh.ogg",
    [CHAR_SOUND_UH2] = "yoshi_uh2.ogg",
    [CHAR_SOUND_UH2_2] = "yoshi_uh2_2.ogg",
    [CHAR_SOUND_WAAAOOOW] = "yoshi_waaaooow.ogg",
    [CHAR_SOUND_WAH2] = "yoshi_wah.ogg",
    [CHAR_SOUND_WHOA] = "yoshi_whoa.ogg",
    [CHAR_SOUND_YAHOO] = "yoshi_yahoo.ogg",
    [CHAR_SOUND_YAWNING] = "yoshi_yawning.ogg",
    [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "yoshi_yahoo.ogg", "yoshi_yahoo1.ogg", "yoshi_yahoo2.ogg", "yoshi_yahoo3.ogg", "yoshi_yahoo4.ogg", "yoshi_yahoo5.ogg" },
    [CHAR_SOUND_YAH_WAH_HOO] = { "yoshi_yah_wah_hoo1.ogg", "yoshi_yah_wah_hoo2.ogg", "yoshi_yah_wah_hoo3.ogg" },
    [CHAR_SOUND_HELLO] = "yoshi_hello.ogg"
}

local PALETTE_YOSHI = {
    [PANTS]  = { r = 0xFF, g = 0x00, b = 0x00 },
    [SHIRT]  = { r = 0x00, g = 0xFF, b = 0x00 },
    [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
    [SHOES]  = { r = 0xFF, g = 0x00, b = 0x00 },
    [HAIR]   = { r = 0xFF, g = 0x00, b = 0x00 },
    [SKIN]   = { r = 0xFF, g = 0xDE, b = 0x39 },
    [CAP]    = { r = 0x00, g = 0xFF, b = 0x00 },
    [EMBLEM] = { r = 0xFF, g = 0x00, b = 0x00 }
}

_G.CT_YOSHI = _G.charSelect.character_add("Yoshi", {"A friendly dinosuar originating from", "Dinosuar Land where he reunited with Mario!", "These cute little guys come in different colors!", "Best not to be near when they're", "in a very hungry mood...", "", "Voiced by: AngelicMiracles 'Yuyake'."}, "FluffaMario & AngelicMiracles", { r = 0, g = 255, b = 0 }, E_MODEL_YOSHI_PLAYER, CT_MARIO, TEX_YOSHI)
_G.charSelect.character_add_voice(E_MODEL_YOSHI_PLAYER, VOICETABLE_YOSHI)
_G.charSelect.character_add_palette_preset(E_MODEL_YOSHI_PLAYER, PALETTE_YOSHI)