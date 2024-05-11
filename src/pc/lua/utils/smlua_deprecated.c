#include <inttypes.h>
#include "types.h"
#ifdef DISCORD_SDK
#include "pc/discord/discord.h"
#endif
#include "pc/lua/smlua.h"
#include "game/hardcoded.h"
#include "game/object_list_processor.h"

char* network_discord_id_from_local_index(UNUSED u8 localIndex) {
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
    if (!gLuaActiveMod) { return; }
    gLuaActiveMod->renderBehindHud = enable;
}

struct ModAudio* audio_stream_load_url(UNUSED const char* url) {
    return NULL;
}

f32 audio_stream_get_tempo(UNUSED struct ModAudio* audio) {
    return 1;
}

void audio_stream_set_tempo(UNUSED struct ModAudio* audio, UNUSED f32 tempo) {
}

void audio_stream_set_speed(UNUSED struct ModAudio* audio, UNUSED f32 initial_freq, UNUSED f32 speed, UNUSED bool pitch) {
}

f32 get_environment_region(u8 index) {
    s32 idx = 6 * index;
    if (gEnvironmentRegions != NULL && index > 0 && index <= gEnvironmentRegions[0] && gEnvironmentRegionsLength > idx) {
        return gEnvironmentRegions[idx];
    }
    return gLevelValues.floorLowerLimit;
}

void set_environment_region(u8 index, s32 value) {
    s32 idx = 6 * index;
    if (gEnvironmentRegions != NULL && index > 0 && index <= gEnvironmentRegions[0] && gEnvironmentRegionsLength > idx) {
        gEnvironmentRegions[idx] = value;
    }
}
