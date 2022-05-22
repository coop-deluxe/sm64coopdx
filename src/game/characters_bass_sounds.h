#include "types.h"
#include "bass/bass.h"
#include "game/camera.h"
#undef min // Redefined in math_util.h, undef it to avoid compiler warnings
#undef max // Redefined in math_util.h, undef it to avoid compiler warnings
#include "engine/math_util.h"

#define H01(s, i, x)                        (x * 65599u + (u8) s[(i) < sizeof(s) ? (i) : sizeof(s)])
#define H04(s, i, x)                        H01(s, i, H01(s, i +  1, H01(s, i +  2, H01(s, i +  3, x))))
#define H16(s, i, x)                        H04(s, i, H04(s, i +  4, H04(s, i +  8, H04(s, i + 12, x))))
#define H64(s, i, x)                        H16(s, i, H16(s, i + 16, H16(s, i + 32, H16(s, i + 48, x))))
#define CHAR_BASS_MAGIC                     0xFF000000u
#define CHAR_BASS_SOUND_ID(name)            (H64(#name "________________________________________________________________", 0, 0) & ~CHAR_BASS_MAGIC)
#define CHAR_BASS_SOUND(name)               (CHAR_BASS_MAGIC | CHAR_BASS_SOUND_ID(name))
#define CHAR_BASS_SOUND_NOT_LOADED          0xFFFFFFFFu
#define DECL_CHAR_BASS_SOUND_RAW(name, ...) static const u8 sCharacterBassSoundRaw_##name[] =
#define DECL_CHAR_BASS_SOUND(name)          { CHAR_BASS_SOUND(name), (s32) sizeof(sCharacterBassSoundRaw_##name), sCharacterBassSoundRaw_##name, CHAR_BASS_SOUND_NOT_LOADED, 0.f }

// Undef these to avoid naming issues
#undef SOUND_MARIO_LETS_A_GO
#undef SOUND_LUIGI_LETS_A_GO
#undef SOUND_WARIO_LETS_A_GO
#undef SOUND_MARIO_OKEY_DOKEY
#undef SOUND_LUIGI_OKEY_DOKEY
#undef SOUND_WARIO_OKEY_DOKEY

/////////////////
// Bass sounds //
/////////////////

DECL_CHAR_BASS_SOUND_RAW(SOUND_MARIO_LETS_A_GO) {
#include "sound/samples/sfx_mario/1A_mario_lets_a_go.table.inc.c"
};

DECL_CHAR_BASS_SOUND_RAW(SOUND_LUIGI_LETS_A_GO) {
#include "sound/samples/sfx_custom_luigi/1A.table.inc.c"
};

DECL_CHAR_BASS_SOUND_RAW(SOUND_WARIO_LETS_A_GO) {
#include "sound/samples/sfx_custom_wario/1A.table.inc.c"
};

DECL_CHAR_BASS_SOUND_RAW(SOUND_MARIO_OKEY_DOKEY) {
#include "sound/samples/sfx_mario_peach/0B_mario_okey_dokey.table.inc.c"
};

DECL_CHAR_BASS_SOUND_RAW(SOUND_LUIGI_OKEY_DOKEY) {
#include "sound/samples/sfx_custom_luigi_peach/0B.table.inc.c"
};

DECL_CHAR_BASS_SOUND_RAW(SOUND_WARIO_OKEY_DOKEY) {
#include "sound/samples/sfx_custom_wario_peach/0B.table.inc.c"
};

///////////////////////
// Bass sounds table //
///////////////////////

typedef struct { s32 sound; s32 size; const u8 *raw; HSAMPLE sample; f32 freq; } CharacterBassSound;
static CharacterBassSound sCharacterBassSounds[] = {
    DECL_CHAR_BASS_SOUND(SOUND_MARIO_LETS_A_GO),
    DECL_CHAR_BASS_SOUND(SOUND_LUIGI_LETS_A_GO),
    DECL_CHAR_BASS_SOUND(SOUND_WARIO_LETS_A_GO),
    DECL_CHAR_BASS_SOUND(SOUND_MARIO_OKEY_DOKEY),
    DECL_CHAR_BASS_SOUND(SOUND_LUIGI_OKEY_DOKEY),
    DECL_CHAR_BASS_SOUND(SOUND_WARIO_OKEY_DOKEY),
    { 0, 0, NULL, CHAR_BASS_SOUND_NOT_LOADED, 0.f },
};

///////////////////////////
// Bass sounds functions //
///////////////////////////

static CharacterBassSound *get_character_bass_sound(s32 sound) {
    for (CharacterBassSound *cbs = sCharacterBassSounds; cbs->raw != NULL; cbs++) {
        if (cbs->sound == sound) {
            return cbs;
        }
    }
    return NULL;
}

static void play_character_bass_sound(CharacterBassSound *cbs, f32 *pos, f32 freqScale) {
    if (cbs->sample == CHAR_BASS_SOUND_NOT_LOADED) {
        cbs->sample = BASS_SampleLoad(TRUE, cbs->raw, 0, cbs->size, 32, BASS_SAMPLE_OVER_POS);
        BASS_SAMPLE info; BASS_SampleGetInfo(cbs->sample, &info);
        cbs->freq = info.freq;
    }
    DWORD handle = BASS_SampleGetChannel(cbs->sample, 0);
    f32 dist = vec3f_length(pos);
    f32 pan = (get_sound_pan(pos[0], pos[2]) - 0.5f) * 2.f;
    f32 intensity = sound_get_level_intensity(dist);
    f32 masterVolume = (f32) configMasterVolume / 127.f;
    f32 sfxVolume = (f32) configSfxVolume / 127.f;
    BASS_ChannelSetAttribute(handle, BASS_ATTRIB_VOL, masterVolume * sfxVolume * intensity * 0.75f);
    BASS_ChannelSetAttribute(handle, BASS_ATTRIB_PAN, pan);
    BASS_ChannelSetAttribute(handle, BASS_ATTRIB_FREQ, cbs->freq * freqScale);
    BASS_ChannelPlay(handle, TRUE);
}
