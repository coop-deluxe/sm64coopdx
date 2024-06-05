#include <inttypes.h>
#include "types.h"
#ifdef DISCORD_SDK
#include "pc/discord/discord.h"
#endif
#include "pc/lua/smlua.h"
#include "game/hardcoded.h"
#include "game/object_list_processor.h"

char* network_discord_id_from_local_index(UNUSED u8 localIndex) {
    smlua_mod_warning();
#ifdef DISCORD_SDK
    static char sDiscordId[64] = "";
    if (localIndex == 0) {
        snprintf(sDiscordId, 64, "%" PRIu64 "", (uint64_t)discord_get_user_id());
        return sDiscordId;
    }
#endif
    return NULL;
}

void djui_hud_set_render_behind_hud(bool enable) {
    smlua_mod_warning();
    if (!gLuaActiveMod) { return; }
    gLuaActiveMod->renderBehindHud = enable;
}

struct ModAudio* audio_stream_load_url(UNUSED const char* url) {
    smlua_mod_warning();
    return NULL;
}

f32 audio_stream_get_tempo(UNUSED struct ModAudio* audio) {
    smlua_mod_warning();
    return 1;
}

void audio_stream_set_tempo(UNUSED struct ModAudio* audio, UNUSED f32 tempo) {
    smlua_mod_warning();
}

void audio_stream_set_speed(UNUSED struct ModAudio* audio, UNUSED f32 initial_freq, UNUSED f32 speed, UNUSED bool pitch) {
    smlua_mod_warning();
}

f32 get_environment_region(u8 index) {
    smlua_mod_warning();
    s32 idx = 6 * index;
    if (gEnvironmentRegions != NULL && index > 0 && index <= gEnvironmentRegions[0] && gEnvironmentRegionsLength > idx) {
        return gEnvironmentRegions[idx];
    }
    return gLevelValues.floorLowerLimit;
}

void set_environment_region(u8 index, s32 value) {
    smlua_mod_warning();
    s32 idx = 6 * index;
    if (gEnvironmentRegions != NULL && index > 0 && index <= gEnvironmentRegions[0] && gEnvironmentRegionsLength > idx) {
        gEnvironmentRegions[idx] = value;
    }
}

void network_player_color_to_palette(struct NetworkPlayer *np, enum PlayerPart part, Color color) {
    smlua_mod_warning();
    if (np == NULL || !(part < PLAYER_PART_MAX && part >= 0)) { return; }

    np->palette.parts[part][0] = color[0];
    np->palette.parts[part][1] = color[1];
    np->palette.parts[part][2] = color[2];
    np->overridePalette = np->palette;
}

void network_player_palette_to_color(struct NetworkPlayer *np, enum PlayerPart part, Color out) {
    smlua_mod_warning();
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
