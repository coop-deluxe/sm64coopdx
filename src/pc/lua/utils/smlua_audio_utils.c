#include "types.h"
#include "pc/mods/mods.h"
#include "pc/lua/smlua.h"
#include "pc/debuglog.h"

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

static smlua_audio_utils_reset(struct AudioOverride* override) {
    if (override == NULL) { return; }

    override->enabled = false;
    override->loaded = false;

    if (override->filename) {
        free(override->filename);
        override->filename = NULL;
    }

    override->length = 0;
    override->bank = 0;

    if (override->buffer != NULL) {
        free(override->filename);
        override->filename = NULL;
    }
}

void smlua_audio_utils_reset_all(void) {
    for (s32 i = 0; i < MAX_OVERRIDE; i++) {
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

void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, const char* m64Name) {
    if (gLuaActiveMod == NULL) { return; }
    if (sequenceId >= MAX_OVERRIDE) {
        LOG_LUA("Invalid sequenceId given to smlua_audio_utils_replace_sequence(): %d", sequenceId);
        return;
    }

    char m64path[SYS_MAX_PATH] = { 0 };
    if (snprintf(m64path, SYS_MAX_PATH-1, "sound/%s.m64", m64Name) < 0) {
        LOG_LUA("Could not find m64 at path: %s", m64path);
        return;
    }

    for (s32 i = 0; i < gLuaActiveMod->fileCount; i++) {
        struct ModFile* file = &gLuaActiveMod->files[i];
        if (!strcmp(file->relativePath, m64path)) {

            char fullPath[SYS_MAX_PATH] = { 0 };
            if (snprintf(fullPath, SYS_MAX_PATH - 1, "%s/%s", gLuaActiveMod->basePath, m64path) < 0) {
                LOG_ERROR("Failed to concat full path to m64: %s", m64Name);
                return;
            }

            struct AudioOverride* override = &sAudioOverrides[sequenceId];
            smlua_audio_utils_reset(override);
            override->filename = strdup(fullPath);
            override->enabled = true;
            override->bank = bankId;
            return;
        }
    }

    LOG_LUA("Could not find m64 at path: %s", m64path);
}
