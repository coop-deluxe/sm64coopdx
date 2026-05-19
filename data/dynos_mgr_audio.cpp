#include "data/dynos.cpp.h"
extern "C" {
#include "seq_ids.h"
#include "audio/load.h"
#include "audio/external.h"
#include "pc/fs/fmem.h"
#include "pc/mods/mod_fs.h"
}

struct AudioOverrideSet {
    AudioOverrideEntry pack;
    AudioOverrideEntry mod;
};

static AudioOverrideSet sAudioOverrides[MAX_AUDIO_OVERRIDE] = { 0 };

static void DynOS_Audio_ResetEntry(AudioOverrideEntry* aOverride) {
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
#ifdef VERSION_EU
        if (!sAudioOverrides[i].pack.enabled && sAudioOverrides[i].mod.enabled) {
            if (i >= SEQ_EVENT_CUTSCENE_LAKITU) {
                sBackgroundMusicDefaultVolume[i] = 75;
            } else {
                sBackgroundMusicDefaultVolume[i] = sBackgroundMusicDefaultVolumeDefault[i];
            }
        } else if (sAudioOverrides[i].pack.enabled) {
            // keep pack override default volume
            sBackgroundMusicDefaultVolume[i] = sAudioOverrides[i].pack.defaultVolume;
        }
#else
        if (!sAudioOverrides[i].pack.enabled && sAudioOverrides[i].mod.enabled) {
            sound_reset_background_music_default_volume(i);
        } else if (sAudioOverrides[i].pack.enabled) {
            // keep pack override default volume
            sound_set_background_music_default_volume(i, sAudioOverrides[i].pack.defaultVolume);
        }
#endif
        DynOS_Audio_ResetEntry(&sAudioOverrides[i].mod);
    }
}

static bool DynOS_Audio_LoadEntry(AudioOverrideEntry* aOverride, u8 aSequenceId, s32* aBankId, void** aSeqData) {
    if (aOverride == NULL || !aOverride->enabled) { return false; }

    if (gOverrideBank > -1) { aOverride->bank = gOverrideBank; }

    if (aOverride->loaded) {
        sound_set_background_music_default_volume(aSequenceId, aOverride->defaultVolume);
        *aSeqData = aOverride->buffer;
        *aBankId = aOverride->bank;
        return true;
    }

    u8* buffer = NULL;
    u32 length = 0;

    if (is_mod_fs_file(aOverride->filename)) {
        if (!mod_fs_read_file_from_uri(aOverride->filename, (void**)&buffer, &length)) {
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
    *aBankId = aOverride->bank;
    return true;
}

bool DynOS_Audio_Override(u8 aSequenceId, s32* aBankId, void** aSeqData) {
    if (aSequenceId >= MAX_AUDIO_OVERRIDE) { return false; }

    AudioOverrideSet* override = &sAudioOverrides[aSequenceId];

    if (override->mod.enabled) {
        if (DynOS_Audio_LoadEntry(&override->mod, aSequenceId, aBankId, aSeqData)) {
            return true;
        }
    }

    if (override->pack.enabled) {
        return DynOS_Audio_LoadEntry(&override->pack, aSequenceId, aBankId, aSeqData);
    }

    return false;
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

void DynOS_Audio_ActivateOverride(AudioOverrideEntry* aOverride) {
    if (aOverride == NULL || aOverride->enabled) { return; }
    aOverride->enabled = true;
    sound_set_background_music_default_volume(aOverride->sequenceId, aOverride->defaultVolume);
    DynOS_Audio_HotSwapIfActive(aOverride->sequenceId);
}

void DynOS_Audio_DeactivateOverride(AudioOverrideEntry* aOverride) {
    if (aOverride == NULL || !aOverride->enabled) { return; }
    aOverride->enabled = false;
    if (sAudioOverrides[aOverride->sequenceId].mod.enabled) {
        sound_set_background_music_default_volume(
            aOverride->sequenceId,
            sAudioOverrides[aOverride->sequenceId].mod.defaultVolume
        );
    } else {
        sound_reset_background_music_default_volume(aOverride->sequenceId);
    }
    DynOS_Audio_HotSwapIfActive(aOverride->sequenceId);
}

AudioOverrideEntry* DynOS_Audio_CreateOverride(u8 aSequenceId, u8 aBankId, u8 aDefaultVolume, const char *aFilepath, bool aIsPack) {
    if (aSequenceId >= MAX_AUDIO_OVERRIDE) {
        PrintError("Invalid sequenceId while creating override: %d", aSequenceId);
        return NULL;
    }

    if (aBankId >= 64) {
        PrintError("Invalid bankId while creating override: %d", aBankId);
        return NULL;
    }

    AudioOverrideEntry* override = aIsPack ? &sAudioOverrides[aSequenceId].pack : &sAudioOverrides[aSequenceId].mod;

    if (override->enabled) {
        if (aIsPack) {
            PrintError("Pack sequence override already exists for sequence ID %d", aSequenceId);
            return NULL;
        }
        audio_init();
    }
    DynOS_Audio_ResetEntry(override);
    Print("Loading audio: %s", aFilepath);
    override->filename = strdup(aFilepath);
    if (override->filename == NULL) {
        PrintError("Failed to allocate memory for audio filepath");
        return NULL;
    }
    override->sequenceId = aSequenceId;
    override->enabled = true;
    override->bank = aBankId;
    override->defaultVolume = aDefaultVolume;

    DynOS_Audio_HotSwapIfActive(aSequenceId);

    return override;
}

// Only for mods
u8 DynOS_Audio_AllocSequence() {
    for (u8 seqId = SEQ_COUNT + 1; seqId < MAX_AUDIO_OVERRIDE; seqId++) {
        if (!sAudioOverrides[seqId].mod.enabled) {
            return seqId;
        }
    }
    PrintError("Cannot allocate more custom sequences.");
    return MAX_AUDIO_OVERRIDE;
}
