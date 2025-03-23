#define MINIAUDIO_IMPLEMENTATION // required by miniaudio

// enable Vorbis decoding (provides ogg audio decoding support) for miniaudio
#define STB_VORBIS_HEADER_ONLY
#include "pc/utils/stb_vorbis.c"

#include "types.h"
#include "seq_ids.h"
#include "audio/external.h"
#include "game/camera.h"
#include "engine/math_util.h"
#include "pc/mods/mods.h"
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_audio_utils.h"
#include "pc/mods/mods_utils.h"
#include "pc/utils/misc.h"
#include "pc/debuglog.h"
#include "pc/pc_main.h"
#include "pc/fs/fmem.h"
#include "audio/external.h"

struct AudioOverride {
    bool enabled;
    bool loaded;
    const char* filename;
    u64 length;
    u8 bank;
    u8* buffer;
};

struct AudioOverride sAudioOverrides[MAX_AUDIO_OVERRIDE] = { 0 };

static void smlua_audio_utils_reset(struct AudioOverride* override) {
    if (override == NULL) { return; }

    override->enabled = false;
    override->loaded = false;

    if (override->filename) {
        free((char*)override->filename);
        override->filename = NULL;
    }

    override->length = 0;
    override->bank = 0;

    if (override->buffer != NULL) {
        free((u8*)override->buffer);
        override->buffer = NULL;
    }
}

void smlua_audio_utils_reset_all(void) {
    audio_init();
    for (s32 i = 0; i < MAX_AUDIO_OVERRIDE; i++) {
#ifdef VERSION_EU
        if (sAudioOverrides[i].enabled) {
            if (i >= SEQ_EVENT_CUTSCENE_LAKITU) {
                sBackgroundMusicDefaultVolume[i] = 75;
                return;
            }
            sBackgroundMusicDefaultVolume[i] = sBackgroundMusicDefaultVolumeDefault[i];
        }
#else
        if (sAudioOverrides[i].enabled) { sound_reset_background_music_default_volume(i); }
#endif
        smlua_audio_utils_reset(&sAudioOverrides[i]);
    }
}

bool smlua_audio_utils_override(u8 sequenceId, s32* bankId, void** seqData) {
    if (sequenceId >= MAX_AUDIO_OVERRIDE) { return false; }
    struct AudioOverride* override = &sAudioOverrides[sequenceId];
    if (!override->enabled) { return false; }

    if (override->loaded) {
        *seqData = override->buffer;
        *bankId = override->bank;
        return true;
    }

    static u8* buffer = NULL;
    static long int length = 0;

    FILE* fp = f_open_r(override->filename);
    if (!fp) { return false; }
    f_seek(fp, 0L, SEEK_END);
    length = f_tell(fp);

    buffer = malloc(length+1);
    if (buffer == NULL) {
        LOG_ERROR("Failed to malloc m64 sound file");
        f_close(fp);
        f_delete(fp);
        return false;
    }

    f_seek(fp, 0L, SEEK_SET);
    f_read(buffer, length, 1, fp);

    f_close(fp);
    f_delete(fp);

    // cache
    override->loaded = true;
    override->buffer = buffer;
    override->length = length;

    *seqData = buffer;
    *bankId = override->bank;
    return true;
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
        if (str_ends_with(relPath, m64path)) {
            struct AudioOverride* override = &sAudioOverrides[sequenceId];
            if (override->enabled) { audio_init(); }
            smlua_audio_utils_reset(override);
            LOG_INFO("Loading audio: %s", file->cachedPath);
            override->filename = strdup(file->cachedPath);
            override->enabled = true;
            override->bank = bankId;
#ifdef VERSION_EU
            //sBackgroundMusicDefaultVolume[sequenceId] = defaultVolume;
#else
            sound_set_background_music_default_volume(sequenceId, defaultVolume);
#endif
            return;
        }
    }

    LOG_LUA_LINE("Could not find m64 at path: %s", m64path);
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

static struct ModAudio* find_mod_audio(struct ModFile* file) {
    struct DynamicPoolNode* node = sModAudioPool->tail;
    while (node) {
        struct DynamicPoolNode* prev = node->prev;
        struct ModAudio* audio = node->ptr;
        if (audio->file == file) { return audio; }
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
        if (str_ends_with((char*)filename, (char*)*ft)) {
            validFileType = true;
            break;
        }
        ft++;
    }
    if (!validFileType) {
        LOG_LUA_LINE("Tried to load audio file with invalid file type: %s", filename);
        return NULL;
    }

    // find mod file in mod list
    bool foundModFile = false;
    struct ModFile* modFile = NULL;
    u16 fileCount = gLuaActiveMod->fileCount;
    for (u16 i = 0; i < fileCount; i++) {
        struct ModFile* file = &gLuaActiveMod->files[i];
        if(str_ends_with(file->relativePath, (char*)filename)) {
            foundModFile = true;
            modFile = file;
            break;
        }
    }
    if (!foundModFile) {
        LOG_LUA_LINE("Could not find audio file: '%s'", filename);
        return NULL;
    }

    // find stream in ModAudio list
    struct ModAudio* audio = find_mod_audio(modFile);
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
    audio->file = modFile;

    // load audio
    FILE *f = f_open_r(modFile->cachedPath);
    if (!f) {
        LOG_ERROR("failed to load audio file '%s': file not found", filename);
        return NULL;
    }

    f_seek(f, 0, SEEK_END);
    u32 size = f_tell(f);
    f_rewind(f);
    void *buffer = calloc(size, 1);
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
    audio->loaded = true;
    return audio;
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
    
    if (configMuteFocusLoss && !WAPI.has_focus()) {
        ma_sound_set_volume(&audio->sound, 0);
    } else {
        f32 masterVolume = (f32)configMasterVolume / 127.0f * (f32)gLuaVolumeMaster / 127.0f;
        f32 musicVolume = (f32)configMusicVolume / 127.0f * (f32)gLuaVolumeLevel / 127.0f;
        ma_sound_set_volume(&audio->sound, masterVolume * musicVolume * volume);
    }
    audio->baseVolume = volume;
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
    
    if (configMuteFocusLoss && !WAPI.has_focus()) {
        ma_sound_set_volume(&audio->sound, 0);
    } else {
        f32 masterVolume = (f32)configMasterVolume / 127.0f;
        f32 musicVolume = (f32)configMusicVolume / 127.0f;
        ma_sound_set_volume(&audio->sound, masterVolume * musicVolume * volume);
    }
    audio->baseVolume = volume;
}

// void audio_stream_set_speed(struct ModAudio* audio, f32 initial_freq, f32 speed, bool pitch) {
//     if (!audio_sanity_check(audio, true, "set stream speed for")) { return; }
//
//     bassh_set_speed(audio->handle, initial_freq, speed, pitch);
// }

//////////////////////////////////////

// MA calls the end callback from it's audio thread
// Use mutexes to be sure we don't try to delete the same memory at the same time
#include <pthread.h>
static pthread_mutex_t sSampleCopyMutex = PTHREAD_MUTEX_INITIALIZER;
static struct ModAudioSampleCopies *sSampleCopyFreeTail = NULL;

// Called whenever a sample copy finishes playback (called from the miniaudio thread)
// removes the copy from it's linked list, and adds it to the pending list
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
    f32 pan = 0.5f;
    if (gCamera) {
        f32 dX = position[0] - gCamera->pos[0];
        f32 dY = position[1] - gCamera->pos[1];
        f32 dZ = position[2] - gCamera->pos[2];
        dist = sqrtf(dX * dX + dY * dY + dZ * dZ);

        Mat4 mtx;
        mtxf_translate(mtx, position);
        mtxf_mul(mtx, mtx, gCamera->mtx);
        f32 factor = 10;
        pan = (get_sound_pan(mtx[3][0] * factor, mtx[3][2] * factor) - 0.5f) * 2.0f;
    }

    if (configMuteFocusLoss && !WAPI.has_focus()) {
        ma_sound_set_volume(sound, 0);
    } else {
        f32 intensity = sound_get_level_intensity(dist);
        f32 masterVolume = (f32)configMasterVolume / 127.0f * (f32)gLuaVolumeMaster / 127.0f;
        f32 sfxVolume = (f32)configSfxVolume / 127.0f * (f32)gLuaVolumeSfx / 127.0f;
        ma_sound_set_volume(sound, masterVolume * sfxVolume * volume * intensity);
    }
    ma_sound_set_pan(sound, pan);
    audio->baseVolume = volume;

    ma_sound_start(sound);
}

void audio_custom_update_volume(void) {
    if (!sModAudioPool) { return; }
    struct DynamicPoolNode* node = sModAudioPool->tail;
    while (node) {
        struct DynamicPoolNode* prev = node->prev;
        struct ModAudio* audio = node->ptr;
        if (configMuteFocusLoss && !WAPI.has_focus()) {
            ma_sound_set_volume(&audio->sound, 0);
        } else if (audio->isStream) {
            f32 masterVolume = (f32)configMasterVolume / 127.0f * (f32)gLuaVolumeMaster / 127.0f;
            f32 musicVolume = (f32)configMusicVolume / 127.0f * (f32)gLuaVolumeLevel / 127.0f;
            ma_sound_set_volume(&audio->sound, masterVolume * musicVolume * audio->baseVolume);
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
