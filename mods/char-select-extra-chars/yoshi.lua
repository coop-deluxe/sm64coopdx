if not _G.charSelectExists then return end

local E_MODEL_YOSHI_PLAYER = smlua_model_util_get_id("yoshi_player_geo")

local TEX_YOSHI = get_texture_info("yoshi_icon")

VOICETABLE_YOSHI = {
    [CHAR_SOUND_ATTACKED] = "yoshi_Hurt_Take_2.ogg",
    [CHAR_SOUND_DOH] = "yoshi_Hurt_Take_2.ogg",
    [CHAR_SOUND_DYING] = "yoshi_Falling_Take_1.ogg",
    [CHAR_SOUND_GROUND_POUND_WAH] = "yoshi_Wa_Take_1.ogg",
    [CHAR_SOUND_HAHA] = "yoshi_Long_Jump_Take_3.ogg",
    [CHAR_SOUND_HAHA_2] = "yoshi_Long_Jump_Take_3.ogg",
    [CHAR_SOUND_HELLO] = "yoshi_Stand_after_Triple_Jump_Take_1.ogg",
    [CHAR_SOUND_HERE_WE_GO] = "yoshi_Stand_after_Triple_Jump_Take_1.ogg",
    [CHAR_SOUND_HOOHOO] = "yoshi_DoubleJumpTake1.ogg",
    [CHAR_SOUND_IMA_TIRED] = "yoshi_Sleeping_Take_1.ogg",
    [CHAR_SOUND_LETS_A_GO] = "yoshi_Long_Jump_Take_3.ogg",
    [CHAR_SOUND_OKEY_DOKEY] = "yoshi_Stand_after_Triple_Jump_Take_1.ogg",
    [CHAR_SOUND_ON_FIRE] = "yoshi_Falling_Take_1.ogg",
    [CHAR_SOUND_PANTING] = "yoshi_Sleeping_Laying_down_Take_1.ogg",
    [CHAR_SOUND_PANTING_COLD] = "yoshi_Sleeping_Take_1.ogg",
    [CHAR_SOUND_PRESS_START_TO_PLAY] = "yoshi_Stand_after_Triple_Jump_Take_1.ogg",
    [CHAR_SOUND_PUNCH_HOO] = "yoshi_Hoo_Take_2.ogg",
    [CHAR_SOUND_PUNCH_WAH] = "yoshi_Wa_Take_1.ogg",
    [CHAR_SOUND_PUNCH_YAH] = "yoshi_DoubleJumpTake1.ogg",
    [CHAR_SOUND_SNORING1] = "yoshi_Sleeping_Take_1.ogg",
    [CHAR_SOUND_SNORING2] = "yoshi_Sleeping_Laying_down_Take_1.ogg",
    [CHAR_SOUND_SNORING3] = {"yoshi_Sleeping_Take_1.ogg", "yoshi_Sleeping_Laying_down_Take_1.ogg", "yoshi_Sleep_Talking_Take_1.ogg"},
    [CHAR_SOUND_SO_LONGA_BOWSER] = "yoshi_So_long_Bowser_Take_1.ogg",
    [CHAR_SOUND_TWIRL_BOUNCE] = "yoshi_Stand_after_Triple_Jump_Take_1.ogg",
    [CHAR_SOUND_UH] = "yoshi_Hurt_Take_2.ogg",
    [CHAR_SOUND_UH2] = "yoshi_Hoo_Take_2.ogg",
    [CHAR_SOUND_UH2_2] = "yoshi_Hurt_Take_2.ogg",
    [CHAR_SOUND_WAAAOOOW] = "yoshi_Falling_Take_2.ogg",
    [CHAR_SOUND_WAH2] = "yoshi_Wa_Take_1.ogg",
    [CHAR_SOUND_WHOA] = "yoshi_Ledge_Gra.ogg",
    [CHAR_SOUND_YAHOO] = "yoshi_Stand_after_Triple_Jump_Take_1.ogg",
    [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = {"yoshi_Stand_after_Triple_Jump_Take_1.ogg", "yoshi_Stand_after_Triple_Jump_Take_1.ogg", "yoshi_Jump3_Take1.ogg", "yoshi_Stand_after_Triple_Jump_Take_1.ogg"},
    [CHAR_SOUND_YAH_WAH_HOO] = {"yoshi_Jump_Take1.ogg", "yoshi_Wa_Take_1.ogg", "yoshi_Ya_Take_2.ogg", "yoshi_Jump3_Take1.ogg"},
    [CHAR_SOUND_YAWNING] = "yoshi_Falling_Asleep_Take_1.ogg",
    [CHAR_SOUND_COUGHING1] = "yoshi_cough.ogg",
    [CHAR_SOUND_COUGHING2] = "yoshi_cough.ogg",
    [CHAR_SOUND_COUGHING3] = "yoshi_cough.ogg",
    [CHAR_SOUND_DROWNING] = "yoshi_underwater_suffocation.ogg",
    [CHAR_SOUND_EEUH] = "yoshi_eeuh.ogg",
    [CHAR_SOUND_HRMM] = "yoshi_hrmm.ogg",
    [CHAR_SOUND_IMA_TIRED] = "yoshi_tired.ogg",
    [CHAR_SOUND_MAMA_MIA] = "yoshi_mama_mia.ogg",
    [CHAR_SOUND_LETS_A_GO] = "yoshi_lets_a_go.ogg",
    [CHAR_SOUND_ON_FIRE] = "yoshi_on_fire.ogg",
    [CHAR_SOUND_OOOF] = "yoshi_oof.ogg",
    [CHAR_SOUND_OOOF2] = "yoshi_oof2.ogg",
    [CHAR_SOUND_PANTING] = "yoshi_pant.ogg",
    [CHAR_SOUND_PANTING_COLD] = "yoshi_pant.ogg",
    [CHAR_SOUND_SNORING1] = "yoshi_snore1.ogg",
    [CHAR_SOUND_SNORING2] = "yoshi_snore2.ogg",
    [CHAR_SOUND_SNORING3] = {"yoshi_snore1.ogg", "yoshi_snore2.ogg", "yoshi_snore3.ogg"},
    [CHAR_SOUND_YAWNING] = "yoshi_yawn.ogg",
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

CT_YOSHI = _G.charSelect.character_add("Yoshi", {"A dinosuar and one of", "Mario's biggest pals!"}, "FluffaMario & AngelicMiracles", { r = 0, g = 255, b = 0 }, E_MODEL_YOSHI_PLAYER, CT_MARIO, TEX_YOSHI)
_G.charSelect.character_add_voice(E_MODEL_YOSHI_PLAYER, VOICETABLE_YOSHI)
_G.charSelect.character_add_palette_preset(E_MODEL_YOSHI_PLAYER, PALETTE_YOSHI)