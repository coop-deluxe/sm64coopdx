#include "types.h"
#include "seq_ids.h"
#include "audio/external.h"
#include "game/camera.h"
#include "engine/math_util.h"
#include "pc/mods/mods.h"
#include "pc/mods/mod_fs.h"
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_audio_utils.h"
#include "pc/mods/mods_utils.h"
#include "pc/utils/misc.h"
#include "pc/debuglog.h"
#include "pc/pc_main.h"
#include "pc/fs/fmem.h"
#include "audio/load.h"
#include "data/dynos.c.h"

void smlua_audio_utils_reset_all(void) {
    dynos_audio_reset_mods();
}

void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, u8 defaultVolume, const char* m64Name) {
    if (gLuaActiveMod == NULL) { return; }
    if (sequenceId >= MAX_AUDIO_OVERRIDE) {
        LOG_LUA_LINE("Invalid sequenceId given to smlua_audio_utils_replace_sequence(): %d", sequenceId);
        return;
    }

    if (bankId >= 64) {
        LOG_LUA_LINE("Invalid bankId given to smlua_audio_utils_replace_sequence(): %d", bankId);
        return;
    }

    if (is_mod_fs_file(m64Name)) {
        dynos_audio_create_override(sequenceId, bankId, defaultVolume, m64Name);
        return;
    }

    char m64path[SYS_MAX_PATH] = { 0 };
    if (snprintf(m64path, SYS_MAX_PATH-1, "sound/%s.m64", m64Name) < 0) {
        LOG_LUA_LINE("Could not concat m64path: %s", m64path);
        return;
    }
    normalize_path(m64path);

    for (s32 i = 0; i < gLuaActiveMod->fileCount; i++) {
        struct ModFile* file = &gLuaActiveMod->files[i];
        char relPath[SYS_MAX_PATH] = { 0 };
        snprintf(relPath, SYS_MAX_PATH-1, "%s", file->relativePath);
        normalize_path(relPath);
        if (path_ends_with(relPath, m64path)) {
            dynos_audio_create_override(sequenceId, bankId, defaultVolume, file->cachedPath);
            return;
        }
    }

    LOG_LUA_LINE("Could not find m64 at path: %s", m64path);
}

u8 smlua_audio_utils_allocate_sequence(void) {
    return dynos_audio_alloc_sequence();
}

  ///////////////
 // mod audio //
///////////////

// Optimization: disable spatialization for everything as it's not used
#define MA_SOUND_STREAM_FLAGS (MA_SOUND_FLAG_NO_SPATIALIZATION | MA_SOUND_FLAG_STREAM)
#define MA_SOUND_SAMPLE_FLAGS (MA_SOUND_FLAG_NO_SPATIALIZATION | MA_SOUND_FLAG_NO_PITCH | MA_SOUND_FLAG_DECODE) // No pitch, pre-decode audio samples

static ma_engine sModAudioEngine;
static struct DynamicPool *sModAudioPool;

static void smlua_audio_custom_init(void) {
    sModAudioPool = dynamic_pool_init();

    ma_result result = ma_engine_init(NULL, &sModAudioEngine);
    if (result != MA_SUCCESS) {
        LOG_ERROR("failed to init Miniaudio: %d", result);
    }
}

static struct ModAudio* find_mod_audio(const char *filepath) {
    struct DynamicPoolNode* node = sModAudioPool->tail;
    while (node) {
        struct DynamicPoolNode* prev = node->prev;
        struct ModAudio* audio = node->ptr;
        if (strcmp(filepath, audio->filepath) == 0) { return audio; }
        node = prev;
    }
    return NULL;
}

static bool audio_sanity_check(struct ModAudio* audio, bool isStream, const char* action) {
    if (!audio || !audio->loaded) {
        LOG_LUA_LINE("Tried to %s unloaded audio %s", action, audio ? (audio->isStream ? "stream" : "sample") : "(NULL)");
        return false;
    }
    if (isStream && !audio->isStream) {
        LOG_LUA_LINE("Tried to %s a sample as a stream", action);
        return false;
    }
    if (!isStream && audio->isStream) {
        LOG_LUA_LINE("Tried to %s a stream as a sample", action);
        return false;
    }
    return true;
}

struct ModAudio* audio_load_internal(const char* filename, bool isStream) {
    if (!sModAudioPool) { smlua_audio_custom_init(); }

    // check file type
    bool validFileType = false;
    const char* fileTypes[] = { ".mp3", ".aiff", ".ogg", NULL };
    const char** ft = fileTypes;
    while (*ft != NULL) {
        if (path_ends_with(filename, *ft)) {
            validFileType = true;
            break;
        }
        ft++;
    }
    if (!validFileType) {
        LOG_LUA_LINE("Tried to load audio file with invalid file type: %s", filename);
        return NULL;
    }

    const char *filepath = filename;
    if (!is_mod_fs_file(filename)) {

        // normalize filename
        char normPath[SYS_MAX_PATH] = { 0 };
        snprintf(normPath, SYS_MAX_PATH, "%s", filename);
        normalize_path(normPath);

        // find mod file in mod list
        bool foundModFile = false;
        struct ModFile* modFile = NULL;
        u16 fileCount = gLuaActiveMod->fileCount;
        for (u16 i = 0; i < fileCount; i++) {
            struct ModFile* file = &gLuaActiveMod->files[i];
            if(path_ends_with(file->relativePath, normPath)) {
                foundModFile = true;
                modFile = file;
                break;
            }
        }
        if (!foundModFile) {
            LOG_LUA_LINE("Could not find audio file: '%s'", filename);
            return NULL;
        }
        filepath = modFile->cachedPath;
    }

    // find stream in ModAudio list
    struct ModAudio* audio = find_mod_audio(filepath);
    if (audio) {
        if (isStream == audio->isStream) {
            return audio;
        } else if (isStream) {
            LOG_LUA_LINE("Tried to load a stream, when a sample already exists for '%s'", filename);
            return NULL;
        } else {
            LOG_LUA_LINE("Tried to load a sample, when a stream already exists for '%s'", filename);
            return NULL;
        }
    }

    // allocate in ModAudio pool
    if (audio == NULL) {
        audio = dynamic_pool_alloc(sModAudioPool, sizeof(struct ModAudio));
        if (!audio) {
            LOG_LUA_LINE("Could not allocate space for new mod audio!");
            return NULL;
        }
    }

    // remember file
    audio->filepath = strdup(filepath);

    void *buffer = NULL;
    u32 size = 0;

    if (is_mod_fs_file(filepath)) {
        if (!mod_fs_read_file_from_uri(filepath, &buffer, &size)) {
            LOG_ERROR("failed to load audio file '%s': an error occurred with modfs", filename);
            return NULL;
        }
    } else {

        // load audio
        FILE *f = f_open_r(filepath);
        if (!f) {
            LOG_ERROR("failed to load audio file '%s': file not found", filename);
            return NULL;
        }

        f_seek(f, 0, SEEK_END);
        size = f_tell(f);
        f_rewind(f);
        buffer = calloc(size, 1);
        if (!buffer) {
            f_close(f);
            f_delete(f);
            LOG_ERROR("failed to load audio file '%s': cannot allocate buffer of size: %d", filename, size);
            return NULL;
        }

        // read the audio buffer
        if (f_read(buffer, 1, size, f) < size) {
            free(buffer);
            f_close(f);
            f_delete(f);
            LOG_ERROR("failed to load audio file '%s': cannot read audio buffer of size: %d", filename, size);
            return NULL;
        }
        f_close(f);
        f_delete(f);
    }

    if (!buffer || !size) {
        LOG_ERROR("failed to load audio file '%s': failed to read audio data", filename);
        return NULL;
    }

    // decode the audio buffer
    ma_result result = ma_decoder_init_memory(buffer, size, NULL, &audio->decoder);
    if (result != MA_SUCCESS) {
        free(buffer);
        LOG_ERROR("failed to load audio file '%s': failed to decode raw audio: %d", filename, result);
        return NULL;
    }

    result = ma_sound_init_from_data_source(
        &sModAudioEngine, &audio->decoder,
        isStream ? MA_SOUND_STREAM_FLAGS : MA_SOUND_SAMPLE_FLAGS,
        NULL, &audio->sound
    );
    if (result != MA_SUCCESS) {
        free(buffer);
        LOG_ERROR("failed to load audio file '%s': %d", filename, result);
        return NULL;
    }

    audio->buffer = buffer;
    audio->bufferSize = size;
    audio->isStream = isStream;
    audio->baseVolume = 1.0f;
    audio->volChannel = MOD_AUDIO_CHANNEL_MUSIC;
    audio->loaded = true;
    return audio;
}

static f32 get_audio_volume(struct ModAudio* audio) {
    f32 volume = audio->baseVolume;
    if (audio->volChannel == MOD_AUDIO_CHANNEL_MUSIC) {
        volume *= (f32)configMusicVolume / 127.0f * (f32)gLuaVolumeLevel / 127.0f;
    } else if (audio->volChannel == MOD_AUDIO_CHANNEL_SFX) {
        volume *= (f32)configSfxVolume / 127.0f * (f32)gLuaVolumeSfx / 127.0f;
    } else if (audio->volChannel == MOD_AUDIO_CHANNEL_ENV) {
        volume *= (f32)configEnvVolume / 127.0f * (f32)gLuaVolumeEnv / 127.0f;
    }
    return gMasterVolume * volume;
}

struct ModAudio* audio_stream_load(const char* filename) {
    return audio_load_internal(filename, true);
}

void audio_stream_destroy(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, true, "destroy")) { return; }

    ma_sound_uninit(&audio->sound);
    audio->loaded = false;
}

void audio_stream_play(struct ModAudio* audio, bool restart, f32 volume) {
    if (!audio_sanity_check(audio, true, "play")) { return; }

    if (configMuteFocusLoss && !gWindowApi->has_focus()) {
        ma_sound_set_volume(&audio->sound, 0);
    } else {
        f32 musicVolume = (f32)configMusicVolume / 127.0f * (f32)gLuaVolumeLevel / 127.0f;
        ma_sound_set_volume(&audio->sound, gMasterVolume * musicVolume * volume);
    }
    audio->baseVolume = volume;
    ma_sound_set_volume(&audio->sound, get_audio_volume(audio));
    if (restart || !ma_sound_is_playing(&audio->sound)) { ma_sound_seek_to_pcm_frame(&audio->sound, 0); }
    ma_sound_start(&audio->sound);
}

void audio_stream_pause(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, true, "pause")) { return; }

    ma_sound_stop(&audio->sound);
}

void audio_stream_stop(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, true, "stop")) { return; }

    ma_sound_stop(&audio->sound);
    ma_sound_seek_to_pcm_frame(&audio->sound, 0);
}

f32 audio_stream_get_position(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, true, "get stream position from")) { return 0; }

    u64 cursor; ma_data_source_get_cursor_in_pcm_frames(&audio->decoder, &cursor);
    return (f32)cursor / ma_engine_get_sample_rate(&sModAudioEngine);
}

void audio_stream_set_position(struct ModAudio* audio, f32 pos) {
    if (!audio_sanity_check(audio, true, "set stream position for")) { return; }

    ma_sound_seek_to_pcm_frame(&audio->sound, pos * ma_engine_get_sample_rate(&sModAudioEngine));
}

bool audio_stream_get_looping(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, true, "get stream looping from")) { return false; }

    return ma_sound_is_looping(&audio->sound);
}

void audio_stream_set_looping(struct ModAudio* audio, bool looping) {
    if (!audio_sanity_check(audio, true, "set stream looping for")) { return; }

    ma_sound_set_looping(&audio->sound, looping);
}

void audio_stream_set_loop_points(struct ModAudio* audio, s64 loopStart, s64 loopEnd) {
    if (!audio_sanity_check(audio, true, "set stream loop points for")) { return; }

    u64 length; ma_data_source_get_length_in_pcm_frames(&audio->decoder, &length);
    if (loopStart < 0) loopStart += length;
    if (loopEnd <= 0) loopEnd += length;

    ma_data_source_set_loop_point_in_pcm_frames(&audio->decoder, loopStart, loopEnd);
}

f32 audio_stream_get_frequency(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, true, "get stream frequency from")) { return 0; }

    return ma_sound_get_pitch(&audio->sound);
}

void audio_stream_set_frequency(struct ModAudio* audio, f32 freq) {
    if (!audio_sanity_check(audio, true, "set stream frequency for")) { return; }

    ma_sound_set_pitch(&audio->sound, freq);
}

// f32 audio_stream_get_tempo(struct ModAudio* audio) {
//     if (!audio_sanity_check(audio, true, "get stream tempo from")) { return 0; }
//
//     return bassh_get_tempo(audio->handle);
// }

// ? Possibly implement as a tempo node? https://source.chromium.org/chromium/chromium/src/+/main:media/base/audio_shifter.cc
// void audio_stream_set_tempo(struct ModAudio* audio, f32 tempo) {
//     if (!audio_sanity_check(audio, true, "set stream tempo for")) { return; }
//
//     bassh_set_tempo(audio->handle, tempo);
// }

f32 audio_stream_get_volume(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, true, "get stream volume from")) { return 0; }

    return audio->baseVolume;
}

void audio_stream_set_volume(struct ModAudio* audio, f32 volume) {
    if (!audio_sanity_check(audio, true, "set stream volume for")) { return; }

    audio->baseVolume = volume;
    ma_sound_set_volume(&audio->sound, get_audio_volume(audio));
}

// void audio_stream_set_speed(struct ModAudio* audio, f32 initial_freq, f32 speed, bool pitch) {
//     if (!audio_sanity_check(audio, true, "set stream speed for")) { return; }
//
//     bassh_set_speed(audio->handle, initial_freq, speed, pitch);
// }

u8 audio_stream_get_volume_channel(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, true, "get stream volume channel from")) {
        return 0;
    }

    return audio->volChannel;
}

void audio_stream_set_volume_channel(struct ModAudio* audio, u8 channel) {
    if (!audio_sanity_check(audio, true, "set stream volume channel for")) {
        return;
    }

    if (channel > MOD_AUDIO_CHANNEL_ENV) {
        LOG_LUA_LINE("Tried to set volume channel to invalid value: %d", channel);
        return;
    }

    audio->volChannel = channel;
    ma_sound_set_volume(&audio->sound, get_audio_volume(audio));
}

//////////////////////////////////////

// MA calls the end callback from its audio thread
// Use mutexes to be sure we don't try to delete the same memory at the same time
#include <pthread.h>
static pthread_mutex_t sSampleCopyMutex = PTHREAD_MUTEX_INITIALIZER;
static struct ModAudioSampleCopies *sSampleCopyFreeTail = NULL;

// Called whenever a sample copy finishes playback (called from the miniaudio thread)
// removes the copy from its linked list, and adds it to the pending list
static void audio_sample_copy_end_callback(void* userData, UNUSED ma_sound* sound) {
    pthread_mutex_lock(&sSampleCopyMutex);

    struct ModAudioSampleCopies *copy = userData;
    if (copy->next) { copy->next->prev = copy->prev; }
    if (copy->prev) { copy->prev->next = copy->next; }
    if (!copy->next && !copy->prev) {
        // This is the last copy of this sample, clear the pointer to it
        copy->parent->sampleCopiesTail = NULL;
    }
    copy->next = NULL;
    copy->prev = NULL;

    // add copy to list
    if (sSampleCopyFreeTail) {
        copy->prev = sSampleCopyFreeTail;
        sSampleCopyFreeTail->next = copy;
    }
    sSampleCopyFreeTail = copy;

    pthread_mutex_unlock(&sSampleCopyMutex);
}

void audio_destroy_copies(struct ModAudioSampleCopies* node) {
    while (node) {
        struct ModAudioSampleCopies* prev = node->prev;
        ma_sound_uninit(&node->sound);
        free(node);
        node = prev;
    }
}

// Called every frame in the main thread from smlua_update()
// Frees all audio sample copies that are in the pending list
void audio_sample_destroy_pending_copies(void) {
    if (sSampleCopyFreeTail) {
        pthread_mutex_lock(&sSampleCopyMutex);
        audio_destroy_copies(sSampleCopyFreeTail);
        sSampleCopyFreeTail = NULL;
        pthread_mutex_unlock(&sSampleCopyMutex);
    }
}

static void audio_sample_destroy_copies(struct ModAudio* audio) {
    pthread_mutex_lock(&sSampleCopyMutex);
    audio_destroy_copies(audio->sampleCopiesTail);
    audio->sampleCopiesTail = NULL;
    pthread_mutex_unlock(&sSampleCopyMutex);
}

struct ModAudio* audio_sample_load(const char* filename) {
    return audio_load_internal(filename, false);
}

void audio_sample_destroy(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, false, "destroy")) { return; }

    if (audio->sampleCopiesTail) {
        audio_sample_destroy_copies(audio);
    }
    ma_sound_stop(&audio->sound);
    ma_sound_uninit(&audio->sound);
    audio->loaded = false;
}

void audio_sample_stop(struct ModAudio* audio) {
    if (!audio_sanity_check(audio, false, "stop")) { return; }

    if (audio->sampleCopiesTail) {
        audio_sample_destroy_copies(audio);
    }
    ma_sound_stop(&audio->sound);
    ma_sound_seek_to_pcm_frame(&audio->sound, 0);
}

void audio_sample_play(struct ModAudio* audio, Vec3f position, f32 volume) {
    if (!audio_sanity_check(audio, false, "play")) { return; }

    ma_sound *sound = &audio->sound;
    if (ma_sound_is_playing(sound)) {
        struct ModAudioSampleCopies* copy = calloc(1, sizeof(struct ModAudioSampleCopies));
        ma_result result = ma_decoder_init_memory(audio->buffer, audio->bufferSize, NULL, &copy->decoder);
        if (result != MA_SUCCESS) { return; }
        result = ma_sound_init_from_data_source(&sModAudioEngine, &copy->decoder, MA_SOUND_SAMPLE_FLAGS, NULL, &copy->sound);
        if (result != MA_SUCCESS) { return; }
        ma_sound_set_end_callback(&copy->sound, audio_sample_copy_end_callback, copy);
        copy->parent = audio;

        // Add to list
        if (audio->sampleCopiesTail) {
            copy->prev = audio->sampleCopiesTail;
            audio->sampleCopiesTail->next = copy;
        }
        audio->sampleCopiesTail = copy;

        sound = &copy->sound;
    }

    f32 dist = 0;
    f32 pan = 0;
    if (gCamera) {
        f32 dX = position[0] - gCamera->pos[0];
        f32 dY = position[1] - gCamera->pos[1];
        f32 dZ = position[2] - gCamera->pos[2];
        dist = sqrtf(dX * dX + dY * dY + dZ * dZ);

        if (configSoundOutput != SOUND_MODE_MONO) {
            Mat4 mtx;
            mtxf_translate(mtx, position);
            mtxf_mul(mtx, mtx, gCamera->mtx);
            f32 factor = 10;
            pan = (get_sound_pan(mtx[3][0] * factor, mtx[3][2] * factor) - 0.5f) * 2.0f;
        }
    }

    if (configMuteFocusLoss && !gWindowApi->has_focus()) {
        ma_sound_set_volume(sound, 0);
    } else {
        f32 intensity = sound_get_level_intensity(dist);
        f32 sfxVolume = (f32)configSfxVolume / 127.0f * (f32)gLuaVolumeSfx / 127.0f;
        ma_sound_set_volume(sound, gMasterVolume * sfxVolume * volume * intensity);
    }
    ma_sound_set_pan(sound, pan);
    audio->baseVolume = volume;

    ma_sound_start(sound);
}

void audio_custom_update_volume(void) {
    gMasterVolume = (f32)configMasterVolume / 127.0f * (f32)gLuaVolumeMaster / 127.0f;
    if (!sModAudioPool) { return; }
    f32 musicVolume = (f32)configMusicVolume / 127.0f * (f32)gLuaVolumeLevel / 127.0f;
    struct DynamicPoolNode* node = sModAudioPool->tail;
    while (node) {
        struct DynamicPoolNode* prev = node->prev;
        struct ModAudio* audio = node->ptr;
        if (configMuteFocusLoss && !gWindowApi->has_focus()) {
            ma_sound_set_volume(&audio->sound, 0);
        } else if (audio->isStream) {
            ma_sound_set_volume(&audio->sound, gMasterVolume * musicVolume * audio->baseVolume);
        }
        node = prev;
    }
}

void audio_custom_shutdown(void) {
    if (!sModAudioPool) { return; }
    struct DynamicPoolNode* node = sModAudioPool->tail;
    while (node) {
        struct DynamicPoolNode* prev = node->prev;
        struct ModAudio* audio = node->ptr;
        if (audio->loaded) {
            if (!audio->isStream && audio->sampleCopiesTail) {
                audio_sample_destroy_copies(audio);
            }
            ma_sound_uninit(&audio->sound);
            free((void *) audio->filepath);
        }
        dynamic_pool_free(sModAudioPool, audio);
        node = prev;
    }
    dynamic_pool_free_pool(sModAudioPool);
}

void smlua_audio_custom_deinit(void) {
    if (sModAudioPool) {
        audio_custom_shutdown();
        free(sModAudioPool);
        ma_engine_uninit(&sModAudioEngine);
        sModAudioPool = NULL;
    }
}
