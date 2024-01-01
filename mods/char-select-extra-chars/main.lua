-- name: [CS] Extra Characters
-- description: Other characters from the Mario series!

local E_MODEL_TOADETTE = smlua_model_util_get_id("toadette_geo")

local TEXT_MOD_NAME = "Extra Characters"

local VOICETABLE_TOADETTE = {
    [CHAR_SOUND_ATTACKED] = 'TT_hurthard.ogg',
    [CHAR_SOUND_GROUND_POUND_WAH] = 'TT_Wah.ogg',
    [CHAR_SOUND_HAHA] = 'TT_haahaa.ogg',
    [CHAR_SOUND_HAHA_2] = 'TT_haahaa.ogg',
    [CHAR_SOUND_HERE_WE_GO] = 'TT_herewego.ogg',
    [CHAR_SOUND_HOOHOO] = 'TT_Jump2.ogg',
    [CHAR_SOUND_ON_FIRE] = 'TT_burning.ogg',
    [CHAR_SOUND_OOOF] = 'TT_Oof.ogg',
    [CHAR_SOUND_OOOF2] = 'TT_oof2.ogg',
    [CHAR_SOUND_PUNCH_HOO] = 'TT_HOO!-2.ogg',
    [CHAR_SOUND_PUNCH_WAH] = 'TT_Wah.ogg',
    [CHAR_SOUND_PUNCH_YAH] = 'TT_Yah!.ogg',
    [CHAR_SOUND_SO_LONGA_BOWSER] = 'TT_Bowser.ogg',
    [CHAR_SOUND_TWIRL_BOUNCE] = 'TT_boing.ogg',
    [CHAR_SOUND_WAAAOOOW] = 'TT_fall.ogg',
    [CHAR_SOUND_WAH2] = 'TT_Jump2.ogg',
    [CHAR_SOUND_WHOA] = 'TT_woah.ogg',
    [CHAR_SOUND_YAHOO] = 'TT_yahoo.ogg',
    [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = {'TT_yahoo.ogg', 'TT_yippee.ogg'},
    [CHAR_SOUND_YAH_WAH_HOO] = {'TT_Yah!.ogg', 'TT_Wah.ogg', 'TT_HOO!-2.ogg'},
    [CHAR_SOUND_OKEY_DOKEY] = 'okay.ogg',
    [CHAR_SOUND_LETS_A_GO] = 'okay.ogg',
    [CHAR_SOUND_DYING] = 'TT_dead.ogg',
    [CHAR_SOUND_DROWNING] = 'TT_drowning.ogg',
    [CHAR_SOUND_EEUH] = 'TT_eugh.ogg',
    [CHAR_SOUND_MAMA_MIA] = 'TT_ooh....ogg',
    [CHAR_SOUND_DOH] = 'TT_Oof.ogg',
    [CHAR_SOUND_HRMM] = 'TT_pickup.ogg',
    [CHAR_SOUND_PANTING] = 'TT_pant',
    [CHAR_SOUND_UH] = 'TT_Oof.ogg',
}

local TEX_TOADETTE = get_texture_info("toadette-icon")

if _G.charSelectExists then
    _G.charSelect.character_add("Toadette", {"A female toad who debutted in", "2003 as a partner for Toad in", "Mario Kart: Double Dash!"}, "Toadette", {r = 0, g = 152, b = 0}, E_MODEL_TOADETTE, CT_TOAD, TEX_TOADETTE)

    _G.charSelect.character_add_voice(E_MODEL_TOADETTE, VOICETABLE_TOADETTE)

    hook_event(HOOK_CHARACTER_SOUND, function (m, sound)
        if _G.charSelect.character_get_voice(m) == VOICETABLE_TOADETTE then return _G.charSelect.voice.sound(m, sound) end
    end)
    hook_event(HOOK_MARIO_UPDATE, function (m)
        if _G.charSelect.character_get_voice(m) == VOICETABLE_TOADETTE then return _G.charSelect.voice.snore(m) end
    end)
else
    djui_popup_create("\\#ffffdc\\\n"..TEXT_MOD_NAME.."\nRequires the Character Select Mod\nto use as a Library!\n\nPlease turn on the Character Select Mod\nand Restart the Room!", 6)
end