#include "proximity_chat.h"

#include "engine/math_util.h"
#include "game/camera.h"
#include "game/level_update.h"
#include "pc/audio/audio_api.h"
#include "pc/djui/djui_hud_utils.h"
#include "pc/network/network.h"
#include "pc_main.h"

#include <opus/opus.h>

#define INTERNAL_SAMPLE_RATE 48000
#define SAMPLE_RATE 32000
#define BITRATE 64000
#define FRAME_SIZE 960
#define STEREO_SPREAD 0.75
#define DECAY_TIME 20

#define HEARING_RADIUS 8192
#define FULL_VOL_RADIUS 1024

typedef struct {
    bool dynamic;
    u32 size, capacity;
    u32 tail, head;
    u8* bytes;
} Buffer;

static struct {
    float volume;
    Buffer audio;
    union {
        OpusEncoder* encoder;
        OpusDecoder* decoder;
    };
} players[MAX_PLAYERS], *client = &players[0];

static bool inited = false;

bool proxchat_muted = false;
bool proxchat_loopback = false;
float proxchat_mic_level = 0;

enum ProxchatError proxchat_error[MAX_PLAYERS];

static Buffer loopback_buffer = { .capacity = 8192 };

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

static u32 buffer_read(Buffer* buffer, u32 bytes, void* out) {
    if (bytes > buffer->size) bytes = buffer->size;
    for (u32 i = 0; i < bytes; i++) {
        if (out) ((u8*)out)[i] = buffer->bytes[buffer->tail];
        buffer->tail = (buffer->tail + 1) % buffer->capacity;
    }
    buffer->size -= bytes;
    return bytes;
}

static void buffer_grow(Buffer* buffer, u32 bytes) {
    if (buffer->dynamic && buffer->size + bytes > buffer->capacity) {
        buffer->capacity = buffer->size + bytes;
        if (buffer->capacity % 1024) buffer->capacity += 1024 - (buffer->capacity % 1024);
        if (buffer->bytes) {
            u8* new_bytes = malloc(buffer->capacity);
            memcpy(new_bytes, buffer->bytes + buffer->tail, (buffer->size - buffer->tail));
            memcpy(new_bytes + (buffer->size - buffer->tail), buffer->bytes, buffer->tail);
            free(buffer->bytes);
            buffer->bytes = new_bytes;
        }
        buffer->tail = 0;
        buffer->head = buffer->size;
    }

    if (!buffer->bytes) buffer->bytes = malloc(buffer->capacity);
}

static void buffer_write(Buffer* buffer, u32 bytes, void* data) {
    buffer_grow(buffer, bytes);
    for (u32 i = 0; i < bytes; i++) {
        buffer->bytes[buffer->head] = data ? ((u8*)data)[i] : 0;
        buffer->head = (buffer->head + 1) % buffer->capacity;
    }
    buffer->size += bytes;
    if (buffer->size > buffer->capacity) buffer->size = buffer->capacity;
}

static bool proxchat_is_ingame(s32 id) {
    return gNetworkPlayers[id].connected
        && gNetworkPlayers[id].currLevelNum  == gNetworkPlayers[0].currLevelNum
        && gNetworkPlayers[id].currAreaIndex == gNetworkPlayers[0].currAreaIndex
        && gNetworkPlayers[id].currActNum    == gNetworkPlayers[0].currActNum;
}

typedef void*(*Writer)(void*, s16);
static void proxchat_resample(Writer writer, void* ctx, const s16* from, f32 target_rate, f32 source_rate, u32 num_frames, u32 num_channels) {
    f32 ratio = source_rate / (f32)target_rate;
    u32 resampled_num_frames = num_frames * ratio;

    for (u32 i = 0; i < resampled_num_frames; i++) {
        for (u32 c = 0; c < num_channels; c++) {
            f32 float_index = i * ratio;
            u32 index = float_index;
            f32 interp = float_index - index;

            s16 sample = (from[(index + 1) * num_channels + c] - from[index * num_channels + c]) * interp + from[index * num_channels + c];
            ctx = writer(ctx, sample);
        }
    }
}

static void* buffer_writer(void* buf, s16 sample) {
    buffer_write(buf, sizeof(sample), &sample);
    return buf;
}

static void* byte_mixer(void* ptr, s16 sample) {
    s16* data = ptr;
    s32 mixed = *data + sample;
    if (mixed > +32767) mixed = +32767;
    if (mixed < -32767) mixed = -32767;
    *data = mixed;
    return ++data;
}

static bool is_below_threshold() {
    if (configProxchatActivationMode == PROXCHAT_ACTMODE_PUSH_TO_TALK) return false;
    
    static int decay = 0;
    if (proxchat_mic_level < configProxchatActivationThreshold / 100.f) {
        if (decay > 0) {
            decay--;
            return false;
        }
        return true;
    }
    decay = DECAY_TIME;
    return false;
}

static void proxchat_callback(const u8* input, u32 bytes) {
    u32 num_samples = bytes / sizeof(s16);
    s16 samples[num_samples];
    memcpy(samples, input, bytes);
    
    s32 sum = 0, avg;
    for (u32 i = 0; i < num_samples; i++) {
        s32 with_gain = samples[i] * (int)configProxchatMicrophoneGain / 100;
        if (with_gain < -32767) with_gain = -32767;
        if (with_gain > +32767) with_gain = +32767;
        samples[i] = with_gain;
        sum += abs(samples[i]);
    }
    avg = sum / num_samples;
    proxchat_mic_level = 1 - powf(1 - avg / 32767.f, 10);

    if (proxchat_loopback)
        buffer_write(&loopback_buffer, bytes, samples);

    if (!inited || gNetworkType == NT_NONE ||
        configProxchatActivationMode == PROXCHAT_ACTMODE_DISABLED ||
        !gServerSettings.proximityChat || proxchat_muted || is_below_threshold()
    ) {
        // drain the pcm buffer
        buffer_read(&client->audio, client->audio.size, NULL);
        return;
    }

    buffer_write(&client->audio, bytes, samples);

    if (client->audio.size >= FRAME_SIZE * sizeof(s16) * 2)
        network_send_proxchat_frame();
}

void proxchat_init() {
    gAudioApi->record_callback(proxchat_callback);

    for (int i = 0; i < MAX_PLAYERS; i++) {
        int err;
        if (i == 0) {
            players[i].encoder = opus_encoder_create(INTERNAL_SAMPLE_RATE, 1, OPUS_APPLICATION_VOIP, &err);
            if (err >= 0) opus_encoder_ctl(players[i].encoder, OPUS_SET_BITRATE(BITRATE));
        }
        else {
            players[i].decoder = opus_decoder_create(INTERNAL_SAMPLE_RATE, 1, &err);
        }

        if (err < 0) {
            fprintf(stderr, "[PROXCHAT] Failed to initialize player %d: %s\n", i, get_opus_error(err));
            proxchat_error[i] = PROXCHAT_ERR_FAILED_TO_INITIALIZE;
        }
        else proxchat_error[i] = PROXCHAT_ERR_NONE;

        players[i].audio.capacity = FRAME_SIZE * sizeof(s16) * 4;
        players[i].audio.dynamic = true;
        players[i].volume = 1;
    }

    proxchat_muted = configProxchatActivationMode == PROXCHAT_ACTMODE_PUSH_TO_TALK;

    inited = true;
}

void proxchat_shutdown() {
    if (!inited) return;

    if (client->encoder) opus_encoder_destroy(client->encoder);
    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (players[i].decoder) opus_decoder_destroy(players[i].decoder);
    }
    
    inited = false;
}

bool proxchat_inited() {
    return inited;
}

f32* proxchat_player_volume(s32 id) {
    return &players[id].volume;
}

bool proxchat_player_is_talking(s32 id) {
    return players[id].audio.size >= FRAME_SIZE;
}

u32 proxchat_encode_audio(u8* packet, u32 max_size) {
    s16 pcm[FRAME_SIZE];
    u32 bytes_read = buffer_read(&client->audio, FRAME_SIZE * sizeof(s16), pcm);
    memset((u8*)pcm + bytes_read, 0, sizeof(pcm) - bytes_read);

    if (!client->encoder) return 0;

    s32 out = opus_encode(client->encoder, pcm, FRAME_SIZE, packet, max_size);
    if (out < 0) {
        fprintf(stderr, "[PROXIMITY CHAT] Failed to encode opus packet: %s\n", get_opus_error(out));
        proxchat_error[0] = PROXCHAT_ERR_FAILED_TO_DECODE;
        return 0;
    }
    proxchat_error[0] = PROXCHAT_ERR_NONE;
    return out;
}

void proxchat_decode_audio(s32 id, u8* packet, u32 packet_size) {
    if (!proxchat_is_ingame(id) || !players[id].decoder) return;

    s16 pcm[FRAME_SIZE * sizeof(s16)];
    s32 num_frames = opus_decode(players[id].decoder, packet, packet_size, pcm, FRAME_SIZE, 0);
    if (num_frames < 0) {
        proxchat_error[id] = PROXCHAT_ERR_FAILED_TO_DECODE;
        return;
    }
    else proxchat_error[id] = PROXCHAT_ERR_NONE;
    buffer_write(&players[id].audio, num_frames * sizeof(s16), pcm);
}

void proxchat_mix(s16* out_pcm, u32 num_samples) {
    num_samples = num_samples * INTERNAL_SAMPLE_RATE / SAMPLE_RATE;
    s16 mixed[num_samples * 2 /* stereo */] = {};

    // skip over player 0 because thats the client
    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        if (!proxchat_is_ingame(i)) continue;

        float volume;
        float dist = vec3f_dist(gMarioStates[i].pos, gMarioState->pos);
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

        float pan = vec3f_dot(right, to_target);

        float pan_mono = 0.5f + pan * 0.5f * STEREO_SPREAD;
        float vol_right = pan_mono;
        float vol_left  = 1 - pan_mono;

        s16 player_pcm[num_samples];
        u32 n = buffer_read(&players[i].audio, sizeof(player_pcm), player_pcm) / sizeof(s16);
        memset(player_pcm + n, 0, sizeof(player_pcm) - n * sizeof(s16));
        
        for (u32 s = 0; s < num_samples * 2; s++) {
            float pan_factor = s % 2 == 0 ? vol_left : vol_right;

            s32 mixed_sample = mixed[s] + (s16)(player_pcm[(int)(s / 2)] * pan_factor * volume * players[i].volume * configProxchatVolume / 127.f);
            mixed[s] = mixed_sample > 32767 ? 32767 : mixed_sample < -32767 ? -32767 : mixed_sample;
        }
    }

    if (proxchat_loopback) {
        s16 pcm[num_samples];
        u32 n = buffer_read(&loopback_buffer, sizeof(pcm), pcm) / sizeof(s16);
        memset(pcm + n, 0, sizeof(pcm) - n * sizeof(s16));

        for (u32 s = 0; s < num_samples * 2; s++) {
            s32 mixed_sample = mixed[s] + pcm[(int)(s / 2)];
            mixed[s] = mixed_sample > 32767 ? 32767 : mixed_sample < -32767 ? -32767 : mixed_sample;
        }
    }

    proxchat_resample(byte_mixer, out_pcm, mixed, SAMPLE_RATE, INTERNAL_SAMPLE_RATE, num_samples, 2);
}
