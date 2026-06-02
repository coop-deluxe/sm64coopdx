#ifndef VOICECHAT_H
#define VOICECHAT_H

#include "types.h"

extern bool voicechat_loopback;
extern float voicechat_mic_level;

extern bool voicechat_others_muted[MAX_PLAYERS];

extern enum VoiceChatError {
    VOICECHAT_ERR_NONE,
    VOICECHAT_ERR_NO_MICROPHONE,
    VOICECHAT_ERR_FAILED_TO_INITIALIZE,
    VOICECHAT_ERR_FAILED_TO_ENCODE,
    VOICECHAT_ERR_FAILED_TO_DECODE,
} voicechat_error[MAX_PLAYERS];

enum VoiceChatActivationMode {
    VOICECHAT_ACTMODE_DISABLED,
    VOICECHAT_ACTMODE_PUSH_TO_TALK,
    VOICECHAT_ACTMODE_THRESHOLD
};

enum VoiceChatMuteState {
    VOICECHAT_UNMUTED     = 0,

    VOICECHAT_MUTE_LOCAL  = (1 << 0),
    VOICECHAT_MUTE_GLOBAL = (1 << 1),
};

enum {
    VOICECHAT_TYPE_DISABLED,
    VOICECHAT_TYPE_VOICE,
    VOICECHAT_TYPE_PROXIMITY,
};

void voicechat_init();
bool voicechat_inited();
void voicechat_shutdown();

u32* voicechat_player_muted(s32 id);
u32* voicechat_player_volume(s32 id);
bool voicechat_player_is_talking(s32 id);

u32 voicechat_encode_audio(u8* packet, u32 max_size);
void voicechat_decode_audio(s32 id, u8* packet, u32 packet_size);
void voicechat_mix(s16* out_pcm, u32 num_samples);

#endif