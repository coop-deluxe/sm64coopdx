#include "types.h"
#include "audio/external.h"
#include "game/camera.h"
#include "engine/math_util.h"
#include "pc/mods/mods.h"
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_audio_utils.h"
#include "pc/mods/mods_utils.h"
#include "bass_audio/bass_audio_helpers.h"
#include "pc/debuglog.h"

#define MAX_AUDIO_OVERRIDE 128

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
        if (sAudioOverrides[i].enabled) { sound_reset_background_music_default_volume(i); }
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

    FILE* fp = fopen(override->filename, "rb");
    if (!fp) { return false; }
    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);

    buffer = malloc(length+1);
    if (buffer == NULL) {
        LOG_ERROR("Failed to malloc m64 sound file");
        fclose(fp);
        return false;
    }

    fseek(fp, 0L, SEEK_SET);
    fread(buffer, length, 1, fp);

    fclose(fp);

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
            sound_set_background_music_default_volume(sequenceId, defaultVolume);
            return;
        }
    }

    LOG_LUA_LINE("Could not find m64 at path: %s", m64path);
}

  //////////
 // bass //
//////////

#define MAX_BASS_FILES 128
struct BassAudio sBassAudio[MAX_BASS_FILES];
u32 sBassAudioCount = 0;

static struct BassAudio* find_bass_audio(struct ModFile* file) {
    for(u16 i = 0; i < sBassAudioCount; i++) {
        struct BassAudio* audio = &sBassAudio[i];
        if (audio->file != file) { continue; }
        return audio;
    }
    return NULL;
}

static bool audio_sanity_check(struct BassAudio* audio, bool isStream, const char* action) {
    if (audio == NULL || !audio->loaded || audio->handle == 0) {
        LOG_LUA_LINE("Tried to %s unloaded audio stream", action);
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

struct BassAudio* audio_load_internal(const char* filename, bool isStream) {
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
    for(u16 i = 0; i < fileCount; i++) {
        struct ModFile* file = &gLuaActiveMod->files[i];
        if(str_ends_with(file->relativePath, (char*)filename)) {
            foundModFile = true;
            modFile = file;
            break;
        }
    }
    if(!foundModFile) {
        LOG_LUA_LINE("Could not find audio file: '%s'", filename);
        return NULL;
    }

    // find stream in BassAudio list
    struct BassAudio* bassAudio = find_bass_audio(modFile);
    if (bassAudio && bassAudio->loaded) {
        if (isStream == bassAudio->isStream) {
            return bassAudio;
        } else if (isStream) {
            LOG_LUA_LINE("Tried to load a stream, when a sample already exists for '%s'", filename);
            return NULL;
        } else {
            LOG_LUA_LINE("Tried to load a sample, when a stream already exists for '%s'", filename);
            return NULL;
        }
    }

    // allocate in BassAudio list
    if (sBassAudioCount >= MAX_BASS_FILES) {
        LOG_LUA_LINE("Ran out of available audio slots!");
        return NULL;
    }
    if (bassAudio == NULL) {
        bassAudio = &sBassAudio[sBassAudioCount++];
    }

    // remember file
    bassAudio->file = modFile;

    // open file pointer
    bool opened = false;
    if (modFile->fp == NULL) {
        modFile->fp = fopen(modFile->cachedPath, "rb");
        if (modFile->fp == NULL) {
            LOG_ERROR("Could not open mod file: %s", modFile->cachedPath);
            return NULL;
        }
        opened = true;
    }

    // copy data
    rewind(modFile->fp);
    bassAudio->rawData = (char*)malloc(modFile->size * sizeof(char));
    fread(bassAudio->rawData, modFile->size, 1, modFile->fp);

    // close file pointer
    if (opened) {
        fclose(modFile->fp);
        modFile->fp = NULL;
    }

    // load audio and return it
    if (isStream) {
        bassAudio->handle = bassh_create_fx_stream_from_file(bassAudio->rawData, modFile->size, 0);
        bassAudio->isStream = true;
    } else {
        bassAudio->handle = bassh_create_sample_from_file(bassAudio->rawData, modFile->size, 0);
        bassAudio->isStream = false;
    }
    bassAudio->loaded = true;
    return bassAudio;
}

struct BassAudio* audio_stream_load(const char* filename) {
    return audio_load_internal(filename, true);
}

struct BassAudio* audio_stream_load_url(const char* url) {
    if (url == NULL || strlen(url) == 0) {
        LOG_LUA_LINE("Failed to load url");
        return NULL;
    }
    HSTREAM stream = BASS_StreamCreateURL(url, 0, 0, NULL, NULL);
    struct BassAudio* res = malloc(sizeof(struct BassAudio));
    res->handle = stream;
    res->rawData = NULL;
    return res;
}

void audio_stream_destroy(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, true, "destroy")) {
        return;
    }

    bassh_free_stream(audio->handle);
    audio->handle = 0;
    audio->loaded = false;
    if (audio->rawData != NULL) {
        free(audio->rawData);
    }
    audio->rawData = NULL;
}

void audio_stream_play(struct BassAudio* audio, bool restart, f32 volume) {
    if (!audio_sanity_check(audio, true, "play")) {
        return;
    }
    f32 masterVolume = (f32)configMasterVolume / 127.0f;
    f32 musicVolume = (f32)configMusicVolume / 127.0f;
    bassh_set_stream_volume(audio->handle, masterVolume * musicVolume * volume);
    bassh_play_stream(audio->handle, restart);
}

void audio_stream_pause(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, true, "pause")) {
        return;
    }
    bassh_pause_stream(audio->handle);
}

void audio_stream_stop(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, true, "stop")) {
        return;
    }
    bassh_stop_stream(audio->handle);
}  

f32 audio_stream_get_position(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, true, "getpos")) {
        return 0;
    }
    return (f32)bassh_get_stream_pos(audio->handle);
}

void audio_stream_set_position(struct BassAudio* audio, f32 pos) {
    if (!audio_sanity_check(audio, true, "setpos")) {
        return;
    }
    bassh_set_stream_pos(audio->handle, (double)pos);
}

bool audio_stream_get_looping(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, true, "getloop")) {
        return false;
    }
    return bassh_get_looping(audio->handle);
}

void audio_stream_set_looping(struct BassAudio* audio, bool looping) {
    if (!audio_sanity_check(audio, true, "setloop")) {
        return;
    }
    bassh_set_looping(audio->handle, looping);
}

f32 audio_stream_get_frequency(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, true, "getfreq")) {
        return 0;
    }
    return bassh_get_frequency(audio->handle);
}

void audio_stream_set_frequency(struct BassAudio* audio, f32 freq) {
    if (!audio_sanity_check(audio, true, "setfreq")) {
        return;
    }
    bassh_set_frequency(audio->handle, freq);
}

f32 audio_stream_get_tempo(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, true, "gettempo")) {
        return 0;
    }
    return bassh_get_tempo(audio->handle);
}

void audio_stream_set_tempo(struct BassAudio* audio, f32 tempo) {
    if (!audio_sanity_check(audio, true, "settempo")) {
        return;
    }
    bassh_set_tempo(audio->handle, tempo);
}

f32 audio_stream_get_volume(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, true, "getvol")) {
        return 0;
    }
    return bassh_get_stream_volume(audio->handle);
}

void audio_stream_set_volume(struct BassAudio* audio, f32 volume) {
    if (!audio_sanity_check(audio, true, "setvol")) {
        return;
    }
    f32 masterVolume = (f32)configMasterVolume / 127.0f;
    f32 musicVolume = (f32)configMusicVolume / 127.0f;
    bassh_set_stream_volume(audio->handle, masterVolume * musicVolume * volume);
}

void audio_stream_set_speed(struct BassAudio* audio, f32 initial_freq, f32 speed, bool pitch) {
    if (!audio_sanity_check(audio, true, "setspeed")) {
        return;
    }
    bassh_set_speed(audio->handle, initial_freq, speed, pitch);
}

struct BassAudio* audio_sample_load(const char* filename) {
    return audio_load_internal(filename, false);
}

void audio_sample_destroy(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, false, "destroy")) {
        return;
    }

    bassh_free_stream(audio->handle);
    audio->handle = 0;
    audio->loaded = false;
    if (audio->rawData) {
        free(audio->rawData);
    }
    audio->rawData = NULL;
}

void audio_sample_stop(struct BassAudio* audio) {
    if (!audio_sanity_check(audio, false, "stop")) {
        return;
    }
    bassh_stop_sample(audio->handle);
}  

void audio_sample_play(struct BassAudio* audio, Vec3f position, f32 volume) {
    if (!audio_sanity_check(audio, false, "play")) {
        return;
    }
    HSTREAM stream = bassh_sample_get_stream(audio->handle);

    f32 dist = 0;
    f32 pan = 0;
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

    f32 intensity = sound_get_level_intensity(dist);
    f32 masterVolume = (f32)configMasterVolume / 127.0f;
    f32 sfxVolume = (f32)configSfxVolume / 127.0f;
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, masterVolume * sfxVolume * volume * intensity);
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_PAN, pan);

    bassh_play_stream(stream, true);
}

void audio_custom_shutdown(void) {
    for(u16 i = 0; i < sBassAudioCount; i++) {
        struct BassAudio* audio = &sBassAudio[i];
        if (!audio->loaded) { continue; }
        if (audio->isStream) {
            audio_stream_destroy(audio);
        } else {
            audio_sample_destroy(audio);
        }
    }
    sBassAudioCount = 0;
}
