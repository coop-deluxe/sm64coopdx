#include "types.h"
#include "audio/external.h"
#include "pc/mods/mods.h"
#include "pc/lua/smlua.h"
#include "pc/debuglog.h"
#include "pc/mods/mods_utils.h"

#define MAX_OVERRIDE 64

struct AudioOverride {
    bool enabled;
    bool loaded;
    const char* filename;
    u64 length;
    u8 bank;
    u8* buffer;
};

struct AudioOverride sAudioOverrides[MAX_OVERRIDE] = { 0 };

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
    for (s32 i = 0; i < MAX_OVERRIDE; i++) {
        if (sAudioOverrides[i].enabled) { sound_reset_background_music_default_volume(i); }
        smlua_audio_utils_reset(&sAudioOverrides[i]);
    }
}

bool smlua_audio_utils_override(u8 sequenceId, s32* bankId, void** seqData) {
    if (sequenceId >= MAX_OVERRIDE) { return false; }
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
    if (sequenceId >= MAX_OVERRIDE) {
        LOG_LUA("Invalid sequenceId given to smlua_audio_utils_replace_sequence(): %d", sequenceId);
        return;
    }

    if (bankId >= 64) {
        LOG_LUA("Invalid bankId given to smlua_audio_utils_replace_sequence(): %d", bankId);
        return;
    }

    char m64path[SYS_MAX_PATH] = { 0 };
    if (snprintf(m64path, SYS_MAX_PATH-1, "sound/%s.m64", m64Name) < 0) {
        LOG_LUA("Could not concat m64path: %s", m64path);
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
            smlua_audio_utils_reset(override);
            LOG_INFO("Loading audio: %s", file->cachedPath);
            override->filename = strdup(file->cachedPath);
            override->enabled = true;
            override->bank = bankId;
            sound_set_background_music_default_volume(sequenceId, defaultVolume);
            return;
        }
    }

    LOG_LUA("Could not find m64 at path: %s", m64path);
}
