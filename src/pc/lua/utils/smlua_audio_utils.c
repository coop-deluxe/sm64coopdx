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

struct AudioOverride {
    bool enabled;
    bool loaded;
    const char *filename;
    u64 length;
    u8 bank;
    u8* buffer;
};

struct AudioOverride sAudioOverrides[MAX_AUDIO_OVERRIDE] = { 0 };

static void smlua_audio_utils_reset(struct AudioOverride *override) {
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
    struct AudioOverride *override = &sAudioOverrides[sequenceId];
    if (!override->enabled) { return false; }

    if (gOverrideBank > -1) { override->bank = gOverrideBank; }

    if (override->loaded) {
        *seqData = override->buffer;
        *bankId = override->bank;
        return true;
    }

    u8* buffer = NULL;
    u32 length = 0;

    if (is_mod_fs_file(override->filename)) {
        if (!mod_fs_read_file_from_uri(override->filename, (void **) &buffer, &length)) {
            return false;
        }
    } else {
        FILE *fp = f_open_r(override->filename);
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
    }

    if (!buffer || !length) {
        return false;
    }

    // cache
    override->loaded = true;
    override->buffer = buffer;
    override->length = length;

    *seqData = buffer;
    *bankId = override->bank;
    return true;
}

static void smlua_audio_utils_create_audio_override(u8 sequenceId, u8 bankId, u8 defaultVolume, const char *filepath) {
    struct AudioOverride *override = &sAudioOverrides[sequenceId];
    if (override->enabled) { audio_init(); }
    smlua_audio_utils_reset(override);
    LOG_INFO("Loading audio: %s", filepath);
    override->filename = strdup(filepath);
    override->enabled = true;
    override->bank = bankId;
    sound_set_background_music_default_volume(sequenceId, defaultVolume);
}

void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, u8 defaultVolume, const char *m64Name) {
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
        smlua_audio_utils_create_audio_override(sequenceId, bankId, defaultVolume, m64Name);
        return;
    }

    char m64path[SYS_MAX_PATH] = { 0 };
    if (snprintf(m64path, SYS_MAX_PATH-1, "sound/%s.m64", m64Name) < 0) {
        LOG_LUA_LINE("Could not concat m64path: %s", m64path);
        return;
    }
    normalize_path(m64path);

    for (s32 i = 0; i < gLuaActiveMod->fileCount; i++) {
        struct ModFile *file = &gLuaActiveMod->files[i];
        char relPath[SYS_MAX_PATH] = { 0 };
        snprintf(relPath, SYS_MAX_PATH-1, "%s", file->relativePath);
        normalize_path(relPath);
        if (path_ends_with(relPath, m64path)) {
            smlua_audio_utils_create_audio_override(sequenceId, bankId, defaultVolume, file->cachedPath);
            return;
        }
    }

    LOG_LUA_LINE("Could not find m64 at path: %s", m64path);
}

u8 smlua_audio_utils_allocate_sequence(void) {
    for (u8 seqId = SEQ_COUNT + 1; seqId < MAX_AUDIO_OVERRIDE; seqId++) {
        if (!sAudioOverrides[seqId].enabled) {
            return seqId;
        }
    }
    LOG_ERROR("Cannot allocate more custom sequences.");
    return MAX_AUDIO_OVERRIDE;
}

  ///////////////
 // mod audio //
///////////////

// Optimization: disable spatialization for everything as it's not used
#define MA_SOUND_FLAGS (MA_SOUND_FLAG_NO_SPATIALIZATION | MA_SOUND_FLAG_NO_DEFAULT_ATTACHMENT)

static ma_engine sModAudioEngine;
static const char *sModAudioTypes[] = { "sound", "sample", "stream" };
static ma_sound_group sModAudioChannels[3];
static struct DynamicPool *sModAudioPool;
static bool sModAudioShuttingDown = false;

static bool audio_sanity_check(struct ModAudio *audio, u8 type, const char *action) {
    if (!audio || !audio->loaded) {
        LOG_LUA_LINE("Tried to %s an unloaded audio %s", action, audio ? sModAudioTypes[audio->type] : "(NULL)");
        return false;
    }
    if (type && (type != audio->type)) {
        LOG_LUA_LINE("Tried to %s a %s as a %s", action,
            sModAudioTypes[audio->type],
            sModAudioTypes[type]);
        return false;
    }
    return true;
}

// MA calls the end callback from its audio thread
// Use mutexes to be sure we don't try to delete the same memory at the same time
#include <pthread.h>
static pthread_mutex_t sSoundCopyMutex = PTHREAD_MUTEX_INITIALIZER;
static struct ModAudio *sSoundCopyFreeTail = NULL;

// Called whenever a sample copy finishes playback (called from the miniaudio thread)
// removes the copy from its linked list, and adds it to the pending list
static void audio_destroy_copy(struct ModAudio *copy) {
    pthread_mutex_lock(&sSoundCopyMutex);

    if (!sModAudioShuttingDown
        && copy && copy->copy
        && copy->parent->alive
    ) {
        if (copy->next) { copy->next->prev = copy->prev; }
        if (copy->prev) { copy->prev->next = copy->next; }
        if (copy == copy->parent->copiesTail) {
            copy->parent->copiesTail = copy->prev;
        }
        copy->next = NULL;
        copy->prev = NULL;
        copy->parent = NULL;

        // add copy to free list
        if (sSoundCopyFreeTail) {
            copy->prev = sSoundCopyFreeTail;
            sSoundCopyFreeTail->next = copy;
        }
        sSoundCopyFreeTail = copy;
    }

    pthread_mutex_unlock(&sSoundCopyMutex);
}

static void audio_destroy_copy_callback(void *userData, UNUSED ma_sound *sound) {
    audio_destroy_copy((struct ModAudio *)userData);
}

void audio_destroy_copies(struct ModAudio *node) {
    while (node) {
        struct ModAudio *prev = node->prev;
        ma_sound_uninit(&node->sound);
        ma_decoder_uninit(&node->decoder);
        smlua_free_audio_copy(node);
        node = prev;
    }
}

// Called every frame in the main thread from smlua_update()
// Frees all audio sample copies that are in the pending list
void audio_destroy_pending_copies(void) {
    pthread_mutex_lock(&sSoundCopyMutex);
    struct ModAudio *nodesToFree = sSoundCopyFreeTail;
    sSoundCopyFreeTail = NULL;
    pthread_mutex_unlock(&sSoundCopyMutex);

    if (nodesToFree) {
        audio_destroy_copies(nodesToFree);
    }
}

static void audio_destroy_all_copies(struct ModAudio *audio) {
    pthread_mutex_lock(&sSoundCopyMutex);
    struct ModAudio *node = audio->copiesTail;
    while (node) {
        struct ModAudio *prev = node->prev;

        // Detach from parent and unregister callback
        ma_sound_set_end_callback(&node->sound, NULL, NULL);
        ma_sound_stop(&node->sound);
        node->parent = NULL;
        node->next = NULL;
        node->prev = NULL;

        // Move to free list
        if (sSoundCopyFreeTail) {
            node->prev = sSoundCopyFreeTail;
            sSoundCopyFreeTail->next = node;
        }
        sSoundCopyFreeTail = node;

        node = prev;
    }
    audio->copiesTail = NULL;
    pthread_mutex_unlock(&sSoundCopyMutex);
}

struct ModAudio *audio_copy_internal(struct ModAudio *audio, bool link) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "copy")) { return NULL; }
    if (audio->copy) { audio = audio->parent; }

    struct ModAudio *copy = calloc(1, sizeof(struct ModAudio));
    if (!copy) {
        LOG_ERROR("Failed to allocate memory for audio copy.");
        return NULL;
    }
    ma_result result = ma_decoder_init_memory(audio->buffer, audio->bufferSize, NULL, &copy->decoder);
    if (result != MA_SUCCESS) {
        free(copy);
        return NULL;
    }
    result = ma_sound_init_from_data_source(&sModAudioEngine, &copy->decoder, MA_SOUND_FLAGS, NULL, &copy->sound);
    if (result != MA_SUCCESS) {
        ma_decoder_uninit(&copy->decoder);
        free(copy);
        return NULL;
    }
    ma_sound_set_end_callback(&copy->sound, audio_destroy_copy_callback, copy);
    copy->parent = audio;
    copy->flags = audio->flags;
    copy->copy = true;
    audio_set_volume_channel(copy, copy->channel);

    // Add to list
    if (link) {
        if (audio->copiesTail) {
            copy->prev = audio->copiesTail;
            audio->copiesTail->next = copy;
        }
        audio->copiesTail = copy;
    }

    return copy;
}

struct ModAudio *audio_copy(struct ModAudio *audio) {
    return audio_copy_internal(audio, true);
}

static void smlua_audio_custom_init(void) {
    sModAudioPool = dynamic_pool_init();

    ma_result result = ma_engine_init(NULL, &sModAudioEngine);
    if (result != MA_SUCCESS) {
        LOG_ERROR("failed to init Miniaudio: %d", result);
    }

    for (u8 i = 0; i < ARRAY_COUNT(sModAudioChannels); i++) {
        ma_sound_group_init(&sModAudioEngine, MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, &sModAudioChannels[i]);
    }

    audio_custom_update_volume();
}

static struct ModAudio *find_mod_audio(const char *filepath) {
    struct DynamicPoolNode *node = sModAudioPool->tail;
    while (node) {
        struct DynamicPoolNode *prev = node->prev;
        struct ModAudio *audio = node->ptr;
        if (audio->filepath && strcmp(filepath, audio->filepath) == 0) { return audio; }
        node = prev;
    }
    return NULL;
}

struct ModAudio *audio_load(const char *filename, enum ModAudioType type) {
    if (!sModAudioPool) { smlua_audio_custom_init(); }

    // check file type
    bool validFileType = false;
    const char *fileTypes[] = { ".mp3", ".aiff", ".ogg", NULL };
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
        struct ModFile *modFile = NULL;
        u16 fileCount = gLuaActiveMod->fileCount;
        for (u16 i = 0; i < fileCount; i++) {
            struct ModFile *file = &gLuaActiveMod->files[i];
            if (path_ends_with(file->relativePath, normPath)) {
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
    struct ModAudio *audio = find_mod_audio(filepath);
    if (audio && audio->loaded) {
        if (type != audio->type) {
            LOG_LUA_LINE("Tried to load a %s, when a %s already exists for '%s'", sModAudioTypes[type], sModAudioTypes[audio->type], filename);
            return NULL;
        }
        return audio;
    }

    // allocate in ModAudio pool if needed
    bool brandNew = (audio == NULL);
    if (brandNew) {
        audio = dynamic_pool_alloc(sModAudioPool, sizeof(struct ModAudio));
        if (!audio) {
            LOG_LUA_LINE("Could not allocate space for new mod audio!");
            return NULL;
        }
        audio->filepath = strdup(filepath);
        if (!audio->filepath) {
            dynamic_pool_free(sModAudioPool, audio);
            return NULL;
        }
    }

    void *buffer = NULL;
    u32 size = 0;
    bool decoderInit = false;
    bool soundInit = false;

    if (is_mod_fs_file(filepath)) {
        if (!mod_fs_read_file_from_uri(filepath, &buffer, &size)) {
            LOG_ERROR("failed to load audio file '%s': an error occurred with modfs", filename);
            goto error;
        }
    } else {

        // load audio
        FILE *f = f_open_r(filepath);
        if (!f) {
            LOG_ERROR("failed to load audio file '%s': file not found", filename);
            goto error;
        }

        f_seek(f, 0, SEEK_END);
        long toldSize = f_tell(f);
        if (toldSize < 0) {
            f_close(f);
            f_delete(f);
            LOG_ERROR("failed to read audio file size '%s'", filename);
            goto error;
        }
        size = (u32) toldSize;
        f_rewind(f);
        buffer = calloc(size, 1);
        if (!buffer) {
            f_close(f);
            f_delete(f);
            LOG_ERROR("failed to load audio file '%s': cannot allocate buffer of size: %d", filename, size);
            goto error;
        }

        // read the audio buffer
        if (f_read(buffer, 1, size, f) < size) {
            f_close(f);
            f_delete(f);
            LOG_ERROR("failed to load audio file '%s': cannot read audio buffer of size: %d", filename, size);
            goto error;
        }
        f_close(f);
        f_delete(f);
    }

    if (!buffer || !size) {
        LOG_ERROR("failed to load audio file '%s': failed to read audio data", filename);
        goto error;
    }

    // decode the audio buffer
    ma_result result = ma_decoder_init_memory(buffer, size, NULL, &audio->decoder);
    if (result != MA_SUCCESS) {
        LOG_ERROR("failed to load audio file '%s': failed to decode raw audio: %d", filename, result);
        goto error;
    }
    decoderInit = true;

    result = ma_sound_init_from_data_source(&sModAudioEngine, &audio->decoder, MA_SOUND_FLAGS, NULL, &audio->sound);
    if (result != MA_SUCCESS) {
        LOG_ERROR("failed to load audio file '%s': %d", filename, result);
        goto error;
    }
    soundInit = true;

    if (audio->buffer) { free(audio->buffer); }
    audio->buffer = buffer;
    audio->bufferSize = size;
    audio->type = type;
    audio->loaded = audio->alive = true;
    audio_set_volume_channel(audio, type == MA_TYPE_STREAM ? MA_CHANNEL_MUSIC : MA_CHANNEL_SFX);
    return audio;

error:
    if (soundInit) { ma_sound_uninit(&audio->sound); }
    if (decoderInit) { ma_decoder_uninit(&audio->decoder); }
    if (buffer) { free(buffer); }
    if (brandNew) {
        free((void *) audio->filepath);
        dynamic_pool_free(sModAudioPool, audio);
    }
    return NULL;
}

void audio_stream_play(struct ModAudio *audio, bool restart, f32 volume) {
    if (!audio_sanity_check(audio, MA_TYPE_STREAM, "play")) { return; }

    ma_sound_set_volume(&audio->sound, volume);
    if (restart) { ma_sound_seek_to_pcm_frame(&audio->sound, 0); }
    ma_sound_start(&audio->sound);
}

struct ModAudio *audio_sample_play(struct ModAudio *audio, Vec3f position, f32 volume) {
    if (!audio_sanity_check(audio, MA_TYPE_SAMPLE, "play")) { return NULL; }
    if (audio->copy) { audio = audio->parent; }

    ma_sound *sound = &audio->sound;
    struct ModAudio *copy = NULL;
    if (ma_sound_is_playing(sound)) {
        copy = audio_copy_internal(audio, false);
        if (!copy) { return NULL; }
        sound = &copy->sound;
    }

    f32 dist = 0;
    if (gCamera) {
        dist = vec3f_dist(position, gCamera->pos);

        if (configSoundOutput != SOUND_MODE_MONO) {
            Mat4 mtx;
            mtxf_translate(mtx, position);
            mtxf_mul(mtx, mtx, gCamera->mtx);
            f32 factor = 10;
            f32 pan = (get_sound_pan(mtx[3][0] * factor, mtx[3][2] * factor) - 0.5f) * 2.0f;
            ma_sound_set_pan(sound, pan);
        }
    }

    f32 intensity = sound_get_level_intensity(dist);
    ma_sound_set_volume(sound, volume * intensity);

    ma_result startResult = ma_sound_start(sound);
    if (startResult != MA_SUCCESS) {
        if (copy) {
            ma_sound_uninit(&copy->sound);
            ma_decoder_uninit(&copy->decoder);
            free(copy);
        }
        LOG_ERROR("Failed to start mod audio sample: %d", startResult);
        return NULL;
    }

    // Only add the copy to the list after a successful start
    if (copy) {
        pthread_mutex_lock(&sSoundCopyMutex);
        if (audio->copiesTail) {
            copy->prev = audio->copiesTail;
            audio->copiesTail->next = copy;
        }
        audio->copiesTail = copy;
        pthread_mutex_unlock(&sSoundCopyMutex);
        return copy;
    }
    return audio;
}

void audio_play(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "play")) { return; }
    ma_sound_start(&audio->sound);
}

void audio_pause(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "pause")) { return; }
    ma_sound_stop(&audio->sound);
}

void audio_stop(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "stop")) { return; }

    if (audio->type == MA_TYPE_SAMPLE) {
        if (audio->copy) {
            audio_destroy_copy(audio);
        } else if (audio->copiesTail) {
            audio_destroy_all_copies(audio);
        }
        audio_destroy_pending_copies();
    }

    ma_sound_stop(&audio->sound);
    ma_sound_seek_to_pcm_frame(&audio->sound, 0);
}

void audio_destroy(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "destroy")) { return; }

    audio->alive = false;
    if (audio->copy) {
        return audio_destroy_copy(audio);
    } else if (audio->copiesTail) {
        audio_destroy_all_copies(audio);
    }
    audio_destroy_pending_copies();

    ma_sound_uninit(&audio->sound);
    ma_decoder_uninit(&audio->decoder);
    free(audio->buffer);
    audio->buffer = NULL;
    audio->loaded = false;
}

void audio_reload(struct ModAudio *audio) {
    if (audio->copy) { audio = audio->parent; }
    if (audio->loaded) { audio_destroy(audio); }
    char *filename = strrchr(audio->filepath, *PATH_SEPARATOR);

    audio_load(filename, audio->type);
}

f32 audio_get_volume(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get volume from")) { return 0; }
    return ma_sound_get_volume(&audio->sound);
}

void audio_set_volume(struct ModAudio *audio, f32 volume) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "set volume for")) { return; }
    ma_sound_set_volume(&audio->sound, volume);
}

f32 audio_get_pan(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get pan from")) { return 0; }
    return ma_sound_get_pan(&audio->sound);
}

void audio_set_pan(struct ModAudio *audio, f32 pan) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "set pan for")) { return; }
    ma_sound_set_pan(&audio->sound, pan);
}

void audio_get_length(struct ModAudio *audio, RET f32 *length) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get length of")) { return; }
    ma_sound_get_length_in_seconds(&audio->sound, length);
}

void audio_get_position(struct ModAudio *audio, RET f32 *position) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get position from")) { return; }
    ma_sound_get_cursor_in_seconds(&audio->sound, position);
}

void audio_set_position(struct ModAudio *audio, f32 pos) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "set position for")) { return; }
    ma_sound_seek_to_second(&audio->sound, pos);
}

bool audio_get_looping(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get looping from")) { return false; }
    return ma_sound_is_looping(&audio->sound);
}

void audio_set_looping(struct ModAudio *audio, bool looping) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "set looping for")) { return; }
    ma_sound_set_looping(&audio->sound, looping);
}

bool audio_get_playing(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get playing from")) { return false; }
    return ma_sound_is_playing(&audio->sound);
}

void audio_set_playing(struct ModAudio *audio, bool playing) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "set playing for")) { return; }
    if (playing) { ma_sound_start(&audio->sound); }
    else { ma_sound_stop(&audio->sound); }
}

void audio_get_loop_points(struct ModAudio *audio, RET u64 *loopStart, RET u64 *loopEnd) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get loop points from")) { return; }
    ma_data_source_get_loop_point_in_pcm_frames(&audio->decoder, loopStart, loopEnd);
}

void audio_set_loop_points(struct ModAudio *audio, s64 loopStart, OPTIONAL s64 loopEnd) {
    if (!audio_sanity_check(audio, MA_TYPE_STREAM, "set loop points for")) { return; }

    u64 length; ma_data_source_get_length_in_pcm_frames(&audio->decoder, &length);
    if (loopStart < 0) loopStart = length + loopStart % length;
    if (loopEnd <= 0) loopEnd = length + loopEnd % length;

    ma_sound_set_looping(&audio->sound, true);
    ma_data_source_set_loop_point_in_pcm_frames(&audio->decoder, loopStart, loopEnd);
}

f32 audio_get_frequency(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get frequency from")) { return 0; }
    return ma_sound_get_pitch(&audio->sound);
}

void audio_set_frequency(struct ModAudio *audio, f32 freq) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "set frequency for")) { return; }
    ma_sound_set_pitch(&audio->sound, freq);
}

// f32 audio_stream_get_tempo(struct ModAudio *audio) {
//     if (!audio_sanity_check(audio, MA_TYPE_STREAM, "get stream tempo from")) { return 0; }
//
//     return bassh_get_tempo(audio->handle);
// }

// ? Possibly implement as a tempo node? https://source.chromium.org/chromium/chromium/src/+/main:third_party/webrtc/modules/audio_coding/neteq/time_stretch.cc
// ? https://github.com/audacity/audacity/blob/release-4.0.0-alpha2/au3/libraries/lib-time-and-pitch/StaffPad/readme.md
// void audio_stream_set_tempo(struct ModAudio *audio, f32 tempo) {
//     if (!audio_sanity_check(audio, MA_TYPE_STREAM, "set stream tempo for")) { return; }
//
//     bassh_set_tempo(audio->handle, tempo);
// }

// void audio_stream_set_speed(struct ModAudio *audio, f32 initial_freq, f32 speed, bool pitch) {
//     if (!audio_sanity_check(audio, MA_TYPE_STREAM, "set stream speed for")) { return; }
//
//     bassh_set_speed(audio->handle, initial_freq, speed, pitch);
// }

u8 audio_get_volume_channel(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get volume channel from")) { return 0; }

    return audio->channel;
}

void audio_set_volume_channel(struct ModAudio *audio, u8 channel) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "set volume channel for")) { return; }

    if (channel > MA_CHANNEL_MASTER) {
        LOG_LUA_LINE("Tried to set volume channel to invalid value: %d", channel);
        return;
    }

    audio->channel = channel;
    if (channel == MA_CHANNEL_MASTER) {
        ma_node_attach_output_bus(&audio->sound, 0, ma_node_graph_get_endpoint(&sModAudioEngine.nodeGraph), 0);
    } else {
        ma_node_attach_output_bus(&audio->sound, 0, &sModAudioChannels[channel], 0);
    }
}

u32 audio_get_sample_rate(struct ModAudio *audio) {
    if (!audio_sanity_check(audio, MA_TYPE_NONE, "get sample rate of")) { return 0; }
    return audio->sound.engineNode.sampleRate;
}

//////////////////////////////////////

void audio_custom_update_volume(void) {
    bool shouldMute = (configMuteFocusLoss && !gWindowApi->has_focus());

    // Update master volume
    gMasterVolume = shouldMute ? 0 : (configMasterVolume / 127.0f * gLuaVolumeMaster / 127.0f);
    if (!sModAudioPool) { return; }
    ma_engine_set_volume(&sModAudioEngine, gMasterVolume);

    // Update music volume
    f32 musicVolume = configMusicVolume / 127.0f * gLuaVolumeLevel / 127.0f;
    ma_sound_group_set_volume(&sModAudioChannels[MA_CHANNEL_MUSIC], musicVolume);

    // Update sound volume
    f32 sfxVolume = configSfxVolume / 127.0f * gLuaVolumeSfx / 127.0f;
    ma_sound_group_set_volume(&sModAudioChannels[MA_CHANNEL_SFX], sfxVolume);

    // Update env volume
    f32 envVolume = configEnvVolume / 127.0f * gLuaVolumeEnv / 127.0f;
    ma_sound_group_set_volume(&sModAudioChannels[MA_CHANNEL_ENV], envVolume);
}

void audio_custom_shutdown(void) {
    if (!sModAudioPool) { return; }

    audio_destroy_pending_copies();

    struct DynamicPoolNode *node = sModAudioPool->tail;
    while (node) {
        struct ModAudio *audio = node->ptr;
        if (audio->loaded) {
            audio->alive = false;

            ma_sound_stop(&audio->sound);

            pthread_mutex_lock(&sSoundCopyMutex);
            struct ModAudio *copy = audio->copiesTail;
            while (copy) {
                struct ModAudio *cprev = copy->prev;
                ma_sound_set_end_callback(&copy->sound, NULL, NULL);
                ma_sound_stop(&copy->sound);
                ma_sound_uninit(&copy->sound);
                ma_decoder_uninit(&copy->decoder);
                free(copy);
                copy = cprev;
            }
            audio->copiesTail = NULL;
            pthread_mutex_unlock(&sSoundCopyMutex);

            ma_sound_uninit(&audio->sound);
            ma_decoder_uninit(&audio->decoder);
            audio->loaded = false;
        }
        free((void *) audio->filepath);
        free(audio->buffer);
        audio->filepath = NULL;
        audio->buffer = NULL;
        node = node->prev;
    }

    // Intentionally call twice.
    // Call 1 frees previously scheduled nodes, and schedules the rest for deletion.
    // Call 2 frees the remaining nodes.
    dynamic_pool_free_pool(sModAudioPool);
    dynamic_pool_free_pool(sModAudioPool);

    // Catch anything that somehow was missed
    if (sSoundCopyFreeTail != NULL) {
        LOG_ERROR("Memory leak! Sample copies still exist after shutdown!");

        // Cover up the memory leak
        // but if a dev sees this log, it needs investigation
        audio_destroy_pending_copies();
    }
}

void smlua_audio_custom_deinit(void) {
    if (sModAudioPool) {
        pthread_mutex_lock(&sSoundCopyMutex);
        sModAudioShuttingDown = true;
        pthread_mutex_unlock(&sSoundCopyMutex);

        for (u8 i = 0; i < ARRAY_COUNT(sModAudioChannels); i++) { ma_sound_group_uninit(&sModAudioChannels[i]); }
        ma_engine_uninit(&sModAudioEngine);

        audio_custom_shutdown();
        free(sModAudioPool);
        sModAudioPool = NULL;

        pthread_mutex_lock(&sSoundCopyMutex);
        sModAudioShuttingDown = false;
        pthread_mutex_unlock(&sSoundCopyMutex);
    }
}
