-- name: Sex in Minecraft
-- description: Creeper pussy, oh so nice\nGreen block asshole, tight like paradise\nPickaxe my dick, till it explodes\nPlaying Minecraft and swallowing loads\nJumped on the bed and spam in chat\nI'm gonna cum I'm gonna splat\nMinecraft roleplay on the server tonight\nWhen I find a diamond, I get so tight\nYeah\nI'm having sex in Minecraft\nOoh\nOoh I jumped, I jump on the bed\nAughh\nWe're having sex in Minecraft\nOoh\nYeah we jumped, we jump on the bed\nBuild a penis out of brick\nThen I'll make a TNT dick\nI'll blow it up and jump some more\nOn the Minecraft server I am a whore\nScream into the mic like a demon\nIn the Minecraft world I drown in semen\nThere's something wrong in my head\nDoesn't matter as I fuck in my shed\nYeah\nI'm having sex in Minecraft\nOoh\nOoh I jumped, I jump on the bed\nAughh\nWe're having sex in Minecraft\nOoh\nYeah we jumped, we jump on the bed\nMinecraft\nMinecraft\nMinecraft\nMinecraft\nSex

local image = get_texture_info("grandma")
local sound = audio_stream_load("funnyjoel.mp3")

local timer = 1638 * 30
local show = true

local posWidth = djui_hud_get_screen_width()
local posHeight = djui_hud_get_screen_height()
local music = SEQ_SOUND_PLAYER

function on_level_init()
    show = true
    timer = 1638 * 30
    audio_stream_play(sound, true, 1)
    audio_stream_set_looping(sound, false)
    music = get_current_background_music()
    sound_banks_disable(SEQ_PLAYER_SFX, SOUND_BANKS_ALL)
end

---Bless you Sony, and bless you Money
---@param m MarioState
function mario_update_local(m)
    if m.playerIndex ~= 0 then return end
    if timer > 0 and show then
        timer = timer - 1
        set_mario_action(m, ACT_DISAPPEARED, 0)
        stop_background_music(music)
    end
    if timer <= 0 and show then
        show = false
        audio_stream_pause(sound)
        audio_stream_set_position(sound, 0)
        play_music(0, SEQUENCE_ARGS(8, music), 0)
        sound_banks_enable(SEQ_PLAYER_SFX, SOUND_BANKS_ALL)
        set_mario_action(m, ACT_IDLE, 0)
        m.marioObj.header.gfx.node.flags = m.marioObj.header.gfx.node.flags | GRAPH_RENDER_ACTIVE
    end
end

function on_hud_render()
    if show then
        djui_hud_set_resolution(RESOLUTION_N64)
        posWidth = djui_hud_get_screen_width()
        posHeight = djui_hud_get_screen_height()
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_render_rect(0, 0, posWidth+4, posHeight+4)
        djui_hud_set_resolution(RESOLUTION_DJUI)
        djui_hud_set_color(255, 255, 255, 255)
        posWidth = (djui_hud_get_screen_width() / 2) - (image.width * 0.8) / 2
        posHeight = (djui_hud_get_screen_height() / 2) - (image.height * 0.8) / 2
        djui_hud_render_texture(image, posWidth, posHeight, 0.8, 0.8)
    end
end

function SEQUENCE_ARGS(priority, seqId)
    return ((priority << 8) | seqId)
end

smlua_text_utils_dialog_replace(DIALOG_107, 1, 1, 95, 200,
"Ghoustbusters\n\
They're back in town\n\
You need to pee?\n\
That is so crazy\n\
What the fuck?\n\
You need to pee\n\
You call the Ghoustbusters\n\
They extract it\n\
There was ghosts\n\
In your bladder\n\
What the fuck?\n\
YAAAAAAAAAH\n\
\n\
\n\
You need to take the pee\n\
Crazy ghost pee-pee\n\
That is insanity!\n\
\n\
\n\
Ghoustbusters\n\
Use their machine\n\
To hook it up\n\
To your dick\n\
\n\
What?\n\
\n\
It hurts?\n\
\n\
When they activate it to remove ghosts\n\
\n\
\n\
\n\
Wuuuuuut?\n\
")

smlua_audio_utils_replace_sequence(SEQ_LEVEL_SPOOKY, 16, 100, "bbh")

hook_event(HOOK_MARIO_UPDATE, mario_update_local)
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)