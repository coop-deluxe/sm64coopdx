#include <inttypes.h>
#include "types.h"
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_audio_utils.h"
#include "game/hardcoded.h"
#include "game/object_list_processor.h"

void djui_hud_set_render_behind_hud(bool enable) {
    LOG_LUA_LINE_WARNING("[LUA] djui_hud_set_render_behind_hud() is deprecated! Please use HOOK_ON_HUD_RENDER_BEHIND instead.");
    if (!gLuaActiveMod) { return; }
    gLuaActiveMod->renderBehindHud = enable;
}

f32 audio_stream_get_tempo(UNUSED struct ModAudio* audio) {
    LOG_LUA_LINE_WARNING("[LUA] audio_stream_get_tempo() is deprecated! There may be a replacement for this function in the future.");
    return 1;
}

void audio_stream_set_tempo(UNUSED struct ModAudio* audio, UNUSED f32 tempo) {
    LOG_LUA_LINE_WARNING("[LUA] audio_stream_set_tempo() is deprecated! There may be a replacement for this function in the future.");
}

void audio_stream_set_speed(UNUSED struct ModAudio* audio, UNUSED f32 initial_freq, UNUSED f32 speed, UNUSED bool pitch) {
    LOG_LUA_LINE_WARNING("[LUA] audio_stream_set_speed() is deprecated! There may be a replacement for this function in the future.");
}

void network_player_color_to_palette(struct NetworkPlayer *np, enum PlayerPart part, Color color) {
    LOG_LUA_LINE_WARNING("[LUA] network_player_color_to_palette() is deprecated! Use network_player_set_override_palette_color() instead.");
    if (np == NULL || !(part < PLAYER_PART_MAX && part >= 0)) { return; }

    np->palette.parts[part][0] = color[0];
    np->palette.parts[part][1] = color[1];
    np->palette.parts[part][2] = color[2];
    np->overridePalette = np->palette;
}

void network_player_palette_to_color(struct NetworkPlayer *np, enum PlayerPart part, Color out) {
    LOG_LUA_LINE_WARNING("[LUA] network_player_palette_to_color() is deprecated! Use network_player_get_palette_color() or network_player_get_override_palette_color() instead.");
    if (np == NULL || !(part < PLAYER_PART_MAX && part >= 0)) {
        if (np == NULL) { // output config palette instead if np is NULL
            out[0] = configPlayerPalette.parts[part][0];
            out[1] = configPlayerPalette.parts[part][1];
            out[2] = configPlayerPalette.parts[part][2];
        }
        return;
    }

    out[0] = np->palette.parts[part][0];
    out[1] = np->palette.parts[part][1];
    out[2] = np->palette.parts[part][2];
}
