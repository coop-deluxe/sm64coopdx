#include "voice_chat.h"

#include "engine/math_util.h"
#include "game/camera.h"
#include "game/level_update.h"
#include "pc/audio/audio_api.h"
#include "pc/djui/djui_hud_utils.h"
#include "pc/network/network.h"
#include "pc_main.h"
#include "pc/network/voice_list.h"

#include <opus/opus.h>

#define INTERNAL_SAMPLE_RATE 48000
#define SAMPLE_RATE 32000
#define BITRATE 64000
#define FRAME_SIZE 960
#define DECAY_TIME 20
#define MIN_FRAMES_REQUIRED 2
#define MAX_FRAMES 16

#define HEARING_RADIUS 8192
#define FULL_VOL_RADIUS 1024

bool gVoiceChatLoopback = false;
float gVoiceChatMicLevel = 0;

struct VoicePlayer gVoicePlayers[MAX_PLAYERS];
struct VoicePlayer* gVoicePlayer = &gVoicePlayers[0];

static struct VoiceBuffer sLoopbackBuffer = { .capacity = FRAME_SIZE * MAX_FRAMES * sizeof(s16) };

static bool sPendingGlobalMutes[MAX_PLAYERS];

static s32 sNumVoiceChannels = 0;
static struct VoiceChannel {
    bool active;
    u32 numAllocated;
    bool* canHear;
}* sVoiceChannels;

static const char* get_opus_error(int err) {
    switch (err) {
        case OPUS_ALLOC_FAIL: return "Allocation failed";
        case OPUS_BAD_ARG: return "Bad argument";
        case OPUS_BUFFER_TOO_SMALL: return "Buffer is too small";
        case OPUS_INTERNAL_ERROR: return "Internal error";
        case OPUS_INVALID_PACKET: return "Invalid packet";
        case OPUS_INVALID_STATE: return "Invalid state";
        default: return "No error";
    }
}

static u32 buffer_read(struct VoiceBuffer* buffer, u32 bytes, void* out) {
    if (bytes > buffer->size) bytes = buffer->size;
    for (u32 i = 0; i < bytes; i++) {
        if (out) ((u8*)out)[i] = buffer->bytes[buffer->tail];
        buffer->tail = (buffer->tail + 1) % buffer->capacity;
    }
    buffer->size -= bytes;
    return bytes;
}

static void buffer_write(struct VoiceBuffer* buffer, u32 bytes, void* data) {
    if (!buffer->bytes) buffer->bytes = malloc(buffer->capacity);
    for (u32 i = 0; i < bytes; i++) {
        buffer->bytes[buffer->head] = data ? ((u8*)data)[i] : 0;
        buffer->head = (buffer->head + 1) % buffer->capacity;
    }
    buffer->size += bytes;
    if (buffer->size > buffer->capacity) buffer->size = buffer->capacity;
}

static void buffer_drain(struct VoiceBuffer* buffer) {
    buffer->head = buffer->tail = buffer->size = 0;
}

static u32 voicechat_num_frames_in_buffer(struct VoiceBuffer* buffer) {
    return buffer->size / FRAME_SIZE / sizeof(s16);
}

static bool voicechat_is_ingame(s32 id) {
    return gNetworkPlayers[id].connected && (gServerSettings.voiceChat == VOICECHAT_TYPE_VOICE || (
        gNetworkPlayers[id].currLevelNum  == gNetworkPlayers[0].currLevelNum &&
        gNetworkPlayers[id].currAreaIndex == gNetworkPlayers[0].currAreaIndex &&
        gNetworkPlayers[id].currActNum    == gNetworkPlayers[0].currActNum
    ));
}

static void mix_and_resample_stereo_pcm(s16* dst, const s16* src, u32 dst_frames, u32 src_frames) {
    f32 step = (f32)(src_frames - 1) / (f32)(dst_frames - 1);

    for (u32 i = 0; i < dst_frames; i++) {
        f32 pos = i * step;
        u32 idx = (s32)pos;
        f32 interp  = pos - idx;

        u32 idx1 = idx + 1;
        if (idx1 >= src_frames) idx1 = src_frames - 1;

        s32 sample_l = dst[2 * i + 0] + src[2 * idx + 0] + interp * (src[2 * idx1 + 0] - src[2 * idx + 0]);
        s32 sample_r = dst[2 * i + 1] + src[2 * idx + 1] + interp * (src[2 * idx1 + 1] - src[2 * idx + 1]);

        dst[2 * i + 0] = sample_l < -32767 ? -32767 : sample_l > 32767 ? 32767 : sample_l;
        dst[2 * i + 1] = sample_r < -32767 ? -32767 : sample_r > 32767 ? 32767 : sample_r;
    }
}

static bool is_below_threshold() {
    if (configVoiceChatActivationMode == VOICECHAT_ACTMODE_PUSH_TO_TALK) return false;
    
    static int decay = 0;
    if (gVoiceChatMicLevel < configVoiceChatActivationThreshold / 100.f) {
        if (decay > 0) {
            decay--;
            return false;
        }
        return true;
    }
    decay = DECAY_TIME;
    return false;
}

static void voicechat_callback(const u8* input, u32 bytes) {
    u32 num_samples = bytes / sizeof(s16);
    s16 samples[num_samples];
    memcpy(samples, input, bytes);
    
    s32 sum = 0, avg;
    for (u32 i = 0; i < num_samples; i++) {
        s32 with_gain = samples[i] * (int)configVoiceChatMicrophoneGain / 100;
        if (with_gain < -32767) with_gain = -32767;
        if (with_gain > +32767) with_gain = +32767;
        samples[i] = with_gain;
        sum += abs(samples[i]);
    }
    avg = sum / num_samples;
    gVoiceChatMicLevel = 1 - powf(1 - avg / 32767.f, 10);

    if (gVoiceChatLoopback)
        buffer_write(&sLoopbackBuffer, bytes, samples);

    if (gNetworkType == NT_NONE || configVoiceChatActivationMode == VOICECHAT_ACTMODE_DISABLED ||
        !gServerSettings.voiceChat || gVoicePlayer->clientMutedState != VOICECHAT_UNMUTED ||
        is_below_threshold()
    ) {
        // drain the pcm buffer
        gVoicePlayer->talking = false;
        buffer_drain(&gVoicePlayer->internal.buffer);
        return;
    }

    gVoicePlayer->talking = true;

    buffer_write(&gVoicePlayer->internal.buffer, bytes, samples);

    if (voicechat_num_frames_in_buffer(&gVoicePlayer->internal.buffer) >= MIN_FRAMES_REQUIRED)
        network_send_voicechat_frame();
}

void voicechat_init() {
    gAudioApi->record_callback(voicechat_callback);

    sNumVoiceChannels = 4;
    sVoiceChannels = malloc(sizeof(struct VoiceChannel) * sNumVoiceChannels);
    memset(sVoiceChannels, 0, sizeof(struct VoiceChannel) * sNumVoiceChannels);
}

static void voicechat_shutdown_player(s32 id) {
    if (id == 0) {
        if (gVoicePlayers[id].internal.encoder) opus_encoder_destroy(gVoicePlayers[id].internal.encoder);
        gVoicePlayers[id].internal.encoder = NULL;
    }
    else {
        if (gVoicePlayers[id].internal.decoder) opus_decoder_destroy(gVoicePlayers[id].internal.decoder);
        gVoicePlayers[id].internal.decoder = NULL;
    }

    buffer_drain(&gVoicePlayers[id].internal.buffer);
    free(gVoicePlayers[id].internal.buffer.bytes);
    gVoicePlayers[id].internal.buffer.bytes = NULL;
}

void voicechat_shutdown() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        voicechat_shutdown_player(i);
    }
}

void voicechat_init_player(s32 id) {
    // clear any previous state
    voicechat_shutdown_player(id);

    int err;
    if (id == 0) {
        gVoicePlayers[id].internal.encoder = opus_encoder_create(INTERNAL_SAMPLE_RATE, 1, OPUS_APPLICATION_VOIP, &err);
        if (err >= 0) opus_encoder_ctl(gVoicePlayers[id].internal.encoder, OPUS_SET_BITRATE(BITRATE));
    }
    else {
        gVoicePlayers[id].internal.decoder = opus_decoder_create(INTERNAL_SAMPLE_RATE, 1, &err);
    }

    if (err < 0) {
        fprintf(stderr, "[VOICE CHAT] Failed to initialize player %d: %s\n", id, get_opus_error(err));
        gVoicePlayers[id].error = VOICECHAT_ERR_FAILED_TO_INITIALIZE;
    }
    else gVoicePlayers[id].error = VOICECHAT_ERR_NONE;

    gVoicePlayers[id].internal.buffer.capacity = FRAME_SIZE * MAX_FRAMES * sizeof(s16);
    gVoicePlayers[id].volume = 100;
    gVoicePlayers[id].channel = 0;
    gVoicePlayers[id].talking = false;
    gVoicePlayers[id].clientMutedState = 0;
    gVoicePlayers[id].playerMutedState = 0;

    if (id == 0 && configVoiceChatActivationMode == VOICECHAT_ACTMODE_PUSH_TO_TALK)
        gVoicePlayers[id].clientMutedState |= VOICECHAT_MUTE_LOCAL;
}

u32 voicechat_encode_audio(u8* packet, u32 max_size) {
    s16 pcm[FRAME_SIZE];
    u32 bytes_read = buffer_read(&gVoicePlayer->internal.buffer, FRAME_SIZE * sizeof(s16), pcm);
    memset((u8*)pcm + bytes_read, 0, sizeof(pcm) - bytes_read);

    if (!gVoicePlayer->internal.encoder) return 0;

    s32 out = opus_encode(gVoicePlayer->internal.encoder, pcm, FRAME_SIZE, packet, max_size);
    if (out < 0) {
        fprintf(stderr, "[VOICE CHAT] Failed to encode opus packet: %s\n", get_opus_error(out));
        gVoicePlayers[0].error = VOICECHAT_ERR_FAILED_TO_ENCODE;
        return 0;
    }
    gVoicePlayers[0].error = VOICECHAT_ERR_NONE;
    return out;
}

void voicechat_decode_audio(s32 id, u8* packet, u32 packet_size) {
    if (!voicechat_is_ingame(id) || !gVoicePlayers[id].internal.decoder) return;

    s16 pcm[FRAME_SIZE];
    s32 num_frames = opus_decode(gVoicePlayers[id].internal.decoder, packet, packet_size, pcm, FRAME_SIZE, 0);
    if (num_frames < 0) {
        fprintf(stderr, "[VOICE CHAT] Failed to decode opus packet: %s\n", get_opus_error(num_frames));
        gVoicePlayers[id].error = VOICECHAT_ERR_FAILED_TO_DECODE;
        return;
    }
    gVoicePlayers[id].error = VOICECHAT_ERR_NONE;
    buffer_write(&gVoicePlayers[id].internal.buffer, num_frames * sizeof(s16), pcm);
}

void voicechat_mix(s16* out_pcm, u32 num_out_samples) {
    s32 num_samples = num_out_samples * INTERNAL_SAMPLE_RATE / SAMPLE_RATE;
    s16 mixed[num_samples * 2 /* stereo */];
    memset(mixed, 0, sizeof(mixed)); // initialize via memset cuz older gcc was complaining about "= {}"

    // skip over player 0 because thats the client
    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        gVoicePlayers[i].talking = false;

        if (!voicechat_is_ingame(i) || gVoicePlayers[i].clientMutedState != VOICECHAT_UNMUTED || gVoicePlayer->clientMutedState & VOICECHAT_MUTE_DEAFENED) {
            buffer_drain(&gVoicePlayers[i].internal.buffer);
            continue;
        }

        if (voicechat_num_frames_in_buffer(&gVoicePlayers[i].internal.buffer) < MIN_FRAMES_REQUIRED) continue;

        gVoicePlayers[i].talking = true;
        
        s16 player_pcm[num_samples];
        u32 n = buffer_read(&gVoicePlayers[i].internal.buffer, sizeof(player_pcm), player_pcm) / sizeof(s16);
        memset(player_pcm + n, 0, sizeof(player_pcm) - n * sizeof(s16));

        f32 vol_left = 1, vol_right = 1;
        if (gServerSettings.voiceChat == VOICECHAT_TYPE_PROXIMITY) {
            f32 volume;
            f32 dist = vec3f_dist(gMarioStates[i].pos, gMarioState->pos);
            if (dist < FULL_VOL_RADIUS) volume = 1;
            else volume = 1 - (dist - FULL_VOL_RADIUS) / (HEARING_RADIUS - FULL_VOL_RADIUS);
            if (volume <= 0.0f) continue;
    
            Vec3f forward, right, to_target;
            vec3f_copy(forward, gCamera->focus);
            vec3f_sub(forward, gCamera->pos);
            vec3f_normalize(forward);
    
            vec3f_cross(right, forward, (Vec3f){ 0, 1, 0 });
        
            vec3f_copy(to_target, gMarioStates[i].pos);
            vec3f_sub(to_target, gCamera->pos);
            vec3f_normalize(to_target);
    
            f32 pan = vec3f_dot(right, to_target);
    
            f32 pan_mono = 0.5f + pan * 0.5f * (configVoiceChatStereoSpread / 100.f);
            vol_right = volume * (pan_mono);
            vol_left  = volume * (1 - pan_mono);
        }
        
        for (s32 s = 0; s < num_samples * 2; s++) {
            float pan_factor = s % 2 == 0 ? vol_left : vol_right;

            s32 mixed_sample = mixed[s] + (s16)(player_pcm[(int)(s / 2)] * pan_factor * (gVoicePlayers[i].volume / 100.f) * (configVoiceChatVolume / 127.f));
            mixed[s] = mixed_sample > 32767 ? 32767 : mixed_sample < -32767 ? -32767 : mixed_sample;
        }
    }

    if (gVoiceChatLoopback) {
        s16 pcm[num_samples];
        u32 n = buffer_read(&sLoopbackBuffer, sizeof(pcm), pcm) / sizeof(s16);
        memset(pcm + n, 0, sizeof(pcm) - n * sizeof(s16));

        for (s32 s = 0; s < num_samples * 2; s++) {
            s32 mixed_sample = mixed[s] + pcm[(int)(s / 2)];
            mixed[s] = mixed_sample > 32767 ? 32767 : mixed_sample < -32767 ? -32767 : mixed_sample;
        }
    }

    mix_and_resample_stereo_pcm(out_pcm, mixed, num_out_samples, num_samples);
}

void voicechat_push_pending_global_mute(s32 global_id) {
    sPendingGlobalMutes[global_id] = true;
}

void voicechat_resolve_pending_global_mutes() {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!sPendingGlobalMutes[i]) continue;
        gVoicePlayers[network_local_index_from_global(i)].clientMutedState |= VOICECHAT_MUTE_GLOBAL;
    }
}

void voicechat_toggle_mute() {
    voicechat_set_mute(!(gVoicePlayer->clientMutedState & VOICECHAT_MUTE_LOCAL));
}

void voicechat_toggle_global_mute(s32 id) {
    voicechat_set_global_mute(id, !(gVoicePlayers[id].clientMutedState & VOICECHAT_MUTE_GLOBAL));
}

void voicechat_toggle_mute_other(s32 id) {
    voicechat_set_mute_other(id, !(gVoicePlayers[id].clientMutedState & VOICECHAT_MUTE_LOCAL));
}

void voicechat_toggle_deafen() {
    voicechat_set_deafen(!(gVoicePlayer->clientMutedState & VOICECHAT_MUTE_DEAFENED));
}

void voicechat_set_mute(bool muted) {
    if (muted) gVoicePlayer->clientMutedState |=  VOICECHAT_MUTE_LOCAL;
    else       gVoicePlayer->clientMutedState &= ~VOICECHAT_MUTE_LOCAL;
}

void voicechat_set_global_mute(s32 id, bool muted) {
    if (!gNetworkPlayers[0].moderator && gNetworkPlayers[0].globalIndex != 0) return;

    if (gNetworkPlayers[0].globalIndex == 0)
        voice_list_get_or_create(gNetworkSystem->get_id_str(id))->is_globally_muted = muted;
    
    if (muted) gVoicePlayers[id].clientMutedState |=  VOICECHAT_MUTE_GLOBAL;
    else       gVoicePlayers[id].clientMutedState &= ~VOICECHAT_MUTE_GLOBAL;
    network_send_voicechat_muted(gNetworkPlayers[id].globalIndex, VOICECHAT_MUTE_GLOBAL, muted);
}

void voicechat_set_mute_other(s32 id, bool muted) {
    voice_list_get_or_create(gNetworkSystem->get_id_str(id))->is_muted = muted;

    if (muted) gVoicePlayers[id].clientMutedState |=  VOICECHAT_MUTE_LOCAL;
    else       gVoicePlayers[id].clientMutedState &= ~VOICECHAT_MUTE_LOCAL;
    network_send_voicechat_muted(gNetworkPlayers[id].globalIndex, VOICECHAT_MUTE_LOCAL, muted);
}

void voicechat_set_deafen(bool muted) {
    if (muted) gVoicePlayer->clientMutedState |=  VOICECHAT_MUTE_DEAFENED;
    else       gVoicePlayer->clientMutedState &= ~VOICECHAT_MUTE_DEAFENED;
    network_send_voicechat_muted(gNetworkPlayers[0].globalIndex, VOICECHAT_MUTE_DEAFENED, muted);
}

static void voicechat_channel_grow(s32 index) {
    struct VoiceChannel* channel = &sVoiceChannels[index];
    if (channel->numAllocated >= sNumVoiceChannels) return;

    channel->canHear = realloc(channel->canHear, sizeof(bool) * sNumVoiceChannels);
    memset(channel->canHear + channel->numAllocated, 0, sizeof(bool) * (sNumVoiceChannels - channel->numAllocated));
    channel->numAllocated = sNumVoiceChannels;
}

static s32 voicechat_init_channel(s32 index) {
    sVoiceChannels[index].active = true;
    voicechat_channel_grow(index);
    return index;
}

s32 voicechat_create_channel() {
    for (s32 i = 1; i < sNumVoiceChannels; i++) {
        if (!sVoiceChannels[i].active) return voicechat_init_channel(i);
    }

    s32 id = sNumVoiceChannels;
    sNumVoiceChannels *= 2;
    sVoiceChannels = realloc(sVoiceChannels, sizeof(struct VoiceChannel) * sNumVoiceChannels);
    memset(sVoiceChannels + id, 0, sizeof(struct VoiceChannel) * (sNumVoiceChannels - id));
    return voicechat_init_channel(id);
}

void voicechat_remove_channel(s32 channel) {
    if (channel < 1 || channel >= sNumVoiceChannels) return;
    sVoiceChannels[channel].active = false;
}

void voicechat_hear(s32 channel, s32 other_channel, bool can_hear) {
    if (channel < 0 || channel >= sNumVoiceChannels) return;
    if (other_channel < 0 || other_channel >= sNumVoiceChannels) return;
    voicechat_channel_grow(channel);
    sVoiceChannels[channel].canHear[other_channel] = can_hear;
}

bool voicechat_can_hear(s32 channel, s32 other_channel) {
    if (channel < 0 || channel >= sNumVoiceChannels) return false;
    if (other_channel < 0 || other_channel >= sNumVoiceChannels) return false;
    if (channel == other_channel) return true;
    voicechat_channel_grow(channel);
    return sVoiceChannels[channel].canHear[other_channel];
}
