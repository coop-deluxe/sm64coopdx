#include "data/dynos.cpp.h"
extern "C" {
#include "seq_ids.h"
#include "audio/load.h"
#include "audio/external.h"
#include "pc/fs/fmem.h"
#include "pc/mods/mod_fs.h"
}

static std::vector<AudioOverrideEntry *> sAudioPackOverrides[MAX_AUDIO_OVERRIDE];
static std::vector<AudioOverrideEntry *> sAudioModOverrides[MAX_AUDIO_OVERRIDE];

static AudioOverrideEntry *DynOS_Audio_GetActivePackOverride(u8 aSequenceId) {
    if (aSequenceId >= MAX_AUDIO_OVERRIDE) { return NULL; }
    auto& overrides = sAudioPackOverrides[aSequenceId];
    for (auto it = overrides.rbegin(); it != overrides.rend(); ++it) {
        if ((*it)->enabled) {
            return *it;
        }
    }
    return NULL;
}

static AudioOverrideEntry *DynOS_Audio_GetActiveModOverride(u8 aSequenceId) {
    if (aSequenceId >= MAX_AUDIO_OVERRIDE) { return NULL; }
    auto& overrides = sAudioModOverrides[aSequenceId];
    for (auto it = overrides.rbegin(); it != overrides.rend(); ++it) {
        if ((*it)->enabled) {
            return *it;
        }
    }
    return NULL;
}

static AudioOverrideEntry *DynOS_Audio_GetActiveOverride(u8 aSequenceId) {
    AudioOverrideEntry *override = DynOS_Audio_GetActiveModOverride(aSequenceId);
    if (override != NULL) { return override; }
    return DynOS_Audio_GetActivePackOverride(aSequenceId);
}

static void DynOS_Audio_HotSwapIfActive(u8 aSequenceId) {
    for (u8 player = 0; player < SEQUENCE_PLAYERS; player++) {
        if (gSequencePlayers[player].enabled && gSequencePlayers[player].seqId == aSequenceId) {
            if (player == SEQ_PLAYER_LEVEL) {
                stop_background_music(aSequenceId);
            }
            play_music(player, aSequenceId, 0);
        }
    }
}

static void DynOS_Audio_ResetModEntry(AudioOverrideEntry* aOverride) {
    if (aOverride == NULL) { return; }

    aOverride->sequenceId = 0;
    aOverride->enabled = false;
    aOverride->loaded = false;

    if (aOverride->filename) {
        free(aOverride->filename);
        aOverride->filename = NULL;
    }

    aOverride->length = 0;
    aOverride->bank = 0;
    aOverride->defaultVolume = 0;

    if (aOverride->buffer != NULL) {
        free(aOverride->buffer);
        aOverride->buffer = NULL;
    }
}

void DynOS_Audio_ResetMods() {
    audio_init();
    for (s32 i = 0; i < MAX_AUDIO_OVERRIDE; i++) {
        AudioOverrideEntry *activePack = DynOS_Audio_GetActivePackOverride(i);
        bool hasPack = activePack != NULL;
        bool hasMod = DynOS_Audio_GetActiveModOverride(i) != NULL;
#ifdef VERSION_EU
        if (!hasPack && hasMod) {
            if (i >= SEQ_EVENT_CUTSCENE_LAKITU) {
                sBackgroundMusicDefaultVolume[i] = 75;
            } else {
                sBackgroundMusicDefaultVolume[i] = sBackgroundMusicDefaultVolumeDefault[i];
            }
        } else if (hasPack) {
            AudioOverrideEntry* activePack = DynOS_Audio_GetActivePackOverride(i);
            sBackgroundMusicDefaultVolume[i] = activePack->defaultVolume;
        }
#else
        if (!hasPack && hasMod) {
            sound_reset_background_music_default_volume(i);
        } else if (hasPack) {
            sound_set_background_music_default_volume(i, activePack->defaultVolume);
        }
#endif
        for (auto& override : sAudioModOverrides[i]) {
            DynOS_Audio_ResetModEntry(override);
            free(override);
        }
        sAudioModOverrides[i].clear();
    }
}

static bool DynOS_Audio_LoadEntry(AudioOverrideEntry *aOverride, u8 aSequenceId, s32 *aBankId, void **aSeqData) {
    if (aOverride == NULL || !aOverride->enabled) { return false; }

    *aBankId = aOverride->bank;
    if (gOverrideBank > -1) { *aBankId = gOverrideBank; }

    if (aOverride->loaded) {
        sound_set_background_music_default_volume(aSequenceId, aOverride->defaultVolume);
        *aSeqData = aOverride->buffer;
        return true;
    }

    u8* buffer = NULL;
    u32 length = 0;

    if (is_mod_fs_file(aOverride->filename)) {
        if (!mod_fs_read_file_from_uri(aOverride->filename, (void **) &buffer, &length)) {
            return false;
        }
    } else {
        FILE* fp = f_open_r(aOverride->filename);
        if (!fp) { return false; }

        f_seek(fp, 0L, SEEK_END);
        length = f_tell(fp);

        buffer = (u8*)malloc(length + 1);
        if (buffer == NULL) {
            PrintError("Failed to malloc m64 sound file");
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

    aOverride->loaded = true;
    aOverride->buffer = buffer;
    aOverride->length = length;

    sound_set_background_music_default_volume(aSequenceId, aOverride->defaultVolume);

    *aSeqData = buffer;
    return true;
}

bool DynOS_Audio_Override(u8 aSequenceId, s32 *aBankId, void **aSeqData) {
    if (aSequenceId >= MAX_AUDIO_OVERRIDE) { return false; }

    AudioOverrideEntry *override = DynOS_Audio_GetActiveOverride(aSequenceId);
    if (!override) {
        return false;
    }

    return DynOS_Audio_LoadEntry(override, aSequenceId, aBankId, aSeqData);
}

void DynOS_Audio_ActivatePackOverride(AudioOverrideEntry *aOverride) {
    if (aOverride == NULL || aOverride->enabled) { return; }
    u8 sequenceId = aOverride->sequenceId;
    aOverride->enabled = true;
    if (DynOS_Audio_GetActiveOverride(sequenceId) == aOverride) {
        sound_set_background_music_default_volume(sequenceId, aOverride->defaultVolume);
        DynOS_Audio_HotSwapIfActive(sequenceId);
    }
}

void DynOS_Audio_DeactivatePackOverride(AudioOverrideEntry *aOverride) {
    if (aOverride == NULL || !aOverride->enabled) { return; }
    u8 sequenceId = aOverride->sequenceId;
    AudioOverrideEntry *activeOverride = DynOS_Audio_GetActiveOverride(sequenceId);
    bool wasActive = activeOverride == aOverride;

    aOverride->enabled = false;

    activeOverride = DynOS_Audio_GetActiveOverride(sequenceId); // Update it after disabling this override
    if (activeOverride != NULL) {
        sound_set_background_music_default_volume(sequenceId, activeOverride->defaultVolume);
    } else {
        sound_reset_background_music_default_volume(sequenceId);
    }
    if (wasActive) {
        DynOS_Audio_HotSwapIfActive(sequenceId);
    }
}

AudioOverrideEntry *DynOS_Audio_CreateOverride(u8 aSequenceId, u8 aBankId, u8 aDefaultVolume, const char *aFilepath, bool aIsPack) {
    if (aSequenceId >= MAX_AUDIO_OVERRIDE) {
        PrintError("Invalid sequenceId while creating override: %d", aSequenceId);
        return NULL;
    }

    if (aBankId >= 64) {
        PrintError("Invalid bankId while creating override: %d", aBankId);
        return NULL;
    }

    AudioOverrideEntry *override = (AudioOverrideEntry *) malloc(sizeof(AudioOverrideEntry));
    if (override == NULL) {
        PrintError("Failed to allocate audio override entry");
        return NULL;
    }

    Print("Loading audio: %s", aFilepath);
    override->filename = strdup(aFilepath);
    if (override->filename == NULL) {
        PrintError("Failed to allocate memory for audio filepath");
        free(override);
        return NULL;
    }
    override->sequenceId = aSequenceId;
    override->enabled = !aIsPack;
    override->loaded = false;
    override->bank = aBankId;
    override->defaultVolume = aDefaultVolume;
    override->buffer = NULL;

    if (aIsPack) {
        sAudioPackOverrides[aSequenceId].push_back(override);
    } else {
        sAudioModOverrides[aSequenceId].push_back(override);
    }

    // Apply the sequence override if it's active
    if (override->enabled && DynOS_Audio_GetActiveOverride(aSequenceId) == override) {
        sound_set_background_music_default_volume(aSequenceId, override->defaultVolume);
        DynOS_Audio_HotSwapIfActive(aSequenceId);
    }

    return override;
}

// Only for mods
u8 DynOS_Audio_AllocSequence() {
    for (u8 seqId = SEQ_COUNT + 1; seqId < MAX_AUDIO_OVERRIDE; seqId++) {
        if (DynOS_Audio_GetActiveModOverride(seqId) == NULL) {
            return seqId;
        }
    }
    PrintError("Cannot allocate more custom sequences.");
    return MAX_AUDIO_OVERRIDE;
}
