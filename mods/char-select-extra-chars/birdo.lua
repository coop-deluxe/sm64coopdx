if not _G.charSelectExists then return end

local E_MODEL_BIRDO = smlua_model_util_get_id("birdo_geo")

local TEX_BIRDO = get_texture_info("birdo-icon")

VOICETABLE_BIRDO = {
    [CHAR_SOUND_ATTACKED] = "birdo_attacked.ogg",
    [CHAR_SOUND_COUGHING1] = "birdo_coughing1.ogg",
    [CHAR_SOUND_COUGHING2] = "birdo_coughing2.ogg",
    [CHAR_SOUND_COUGHING3] = "birdo_coughing3.ogg",
    [CHAR_SOUND_DOH] = "birdo_doh.ogg",
    [CHAR_SOUND_DROWNING] = "birdo_drowning.ogg",
    [CHAR_SOUND_DYING] = "birdo_dying.ogg",
    [CHAR_SOUND_EEUH] = "birdo_euuh.ogg",
    [CHAR_SOUND_GROUND_POUND_WAH] = "birdo_ground_pound_wah.ogg",
    [CHAR_SOUND_HAHA] = "birdo_haha.ogg",
    [CHAR_SOUND_HAHA_2] = "birdo_haha2.ogg",
    [CHAR_SOUND_HERE_WE_GO] = "birdo_herewego.ogg",
    [CHAR_SOUND_HOOHOO] = "birdo_hoohoo.ogg",
    [CHAR_SOUND_HRMM] = "birdo_hrmm.ogg",
    [CHAR_SOUND_IMA_TIRED] = "birdo_imatired.ogg",
    [CHAR_SOUND_MAMA_MIA] = "birdo_mamamia.ogg",
    [CHAR_SOUND_LETS_A_GO] = "birdo_letsago.ogg",
    [CHAR_SOUND_ON_FIRE] = "birdo_on_fire.ogg",
    [CHAR_SOUND_OOOF] = "birdo_ooof.ogg",
    [CHAR_SOUND_OOOF2] = "birdo_ooof2.ogg",
    [CHAR_SOUND_PANTING] = "birdo_panting.ogg",
    [CHAR_SOUND_PANTING_COLD] = "birdo_panting_cold.ogg",
    [CHAR_SOUND_PUNCH_HOO] = "birdo_punch_hoo.ogg",
    [CHAR_SOUND_PUNCH_WAH] = "birdo_punch_wah.ogg",
    [CHAR_SOUND_PUNCH_YAH] = "birdo_punch_yah.ogg",
    [CHAR_SOUND_SO_LONGA_BOWSER] = "birdo_solonga_bowser.ogg",
    [CHAR_SOUND_SNORING1] = "birdo_snoring1.ogg",
    [CHAR_SOUND_SNORING2] = "birdo_snoring2.ogg",
    [CHAR_SOUND_SNORING3] = { "birdo_snoring1.ogg", "birdo_snoring2.ogg" },
    [CHAR_SOUND_TWIRL_BOUNCE] = "birdo_twirl_bounce.ogg",
    [CHAR_SOUND_UH] = "birdo_uh.ogg",
    [CHAR_SOUND_UH2] = "birdo_uh2.ogg",
    [CHAR_SOUND_UH2_2] = "birdo_uh2_2.ogg",
    [CHAR_SOUND_WAAAOOOW] = "birdo_waaaooow.ogg",
    [CHAR_SOUND_WAH2] = "birdo_ground_pound_wah.ogg",
    [CHAR_SOUND_WHOA] = "birdo_whoa.ogg",
    [CHAR_SOUND_YAHOO] = "birdo_yahoo.ogg",
    [CHAR_SOUND_YAWNING] = "birdo_yawning.ogg",
    [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { "birdo_yahoo.ogg", "birdo_yahoo1.ogg", "birdo_yahoo2.ogg", "birdo_yahoo3.ogg", "birdo_yahoo4.ogg", "birdo_yahoo5.ogg" },
    [CHAR_SOUND_YAH_WAH_HOO] = { "birdo_yah_wah_hoo1.ogg", "birdo_yah_wah_hoo2.ogg", "birdo_yah_wah_hoo3.ogg" },
    [CHAR_SOUND_HELLO] = "birdo_hello.ogg"
}

local PALETTE_BIRDO = {
    [PANTS]  = { r = 0xFF, g = 0x00, b = 0x00 }, --FF0000
    [SHIRT]  = { r = 0xFE, g = 0x4D, b = 0x7F }, --FE4D7F
    [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF }, --FFFFFF
    [SHOES]  = { r = 0xFE, g = 0x4D, b = 0x7F }, --FE4D7F
    [HAIR]   = { r = 0xFF, g = 0x00, b = 0x00 }, --FF0000
    [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 }, --FEC179
    [CAP]    = { r = 0xFE, g = 0x4D, b = 0x7F }, --FE4D7F
    [EMBLEM] = { r = 0xFF, g = 0x00, b = 0x00 }  --FF0000
}

_G.CT_BIRDO = _G.charSelect.character_add("Birdo", "A very feminine dinosaur who debutted in Super Mario Bros. 2! Some say she was born a boy but then found out her true self later in life and became a girl. Voiced by: RihannaDeleon.", "thagurltilly & AngelicMiracles", { r = 254, g = 77, b = 127 }, E_MODEL_BIRDO, CT_MARIO, TEX_BIRDO, 1.0, 0)
_G.charSelect.character_add_voice(E_MODEL_BIRDO, VOICETABLE_BIRDO)
_G.charSelect.character_add_palette_preset(E_MODEL_BIRDO, PALETTE_BIRDO)