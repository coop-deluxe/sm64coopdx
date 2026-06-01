#ifndef PROXCHAT_H
#define PROXCHAT_H

#include "types.h"

extern bool proxchat_loopback;
extern float proxchat_mic_level;

extern enum ProxchatError {
    PROXCHAT_ERR_NONE,
    PROXCHAT_ERR_NO_MICROPHONE,
    PROXCHAT_ERR_FAILED_TO_INITIALIZE,
    PROXCHAT_ERR_FAILED_TO_ENCODE,
    PROXCHAT_ERR_FAILED_TO_DECODE,
} proxchat_error[MAX_PLAYERS];

enum ProxchatActivationMode {
    PROXCHAT_ACTMODE_DISABLED,
    PROXCHAT_ACTMODE_PUSH_TO_TALK,
    PROXCHAT_ACTMODE_THRESHOLD
};

enum ProxchatMuteState {
    PROXCHAT_UNMUTED     = 0,

    PROXCHAT_MUTE_LOCAL  = (1 << 0),
    PROXCHAT_MUTE_GLOBAL = (1 << 1),
};

void proxchat_init();
bool proxchat_inited();
void proxchat_shutdown();

const Texture* proxchat_get_microphone_texture();

u32* proxchat_player_muted(s32 id);
u32* proxchat_player_volume(s32 id);
bool proxchat_player_is_talking(s32 id);

u32 proxchat_encode_audio(u8* packet, u32 max_size);
void proxchat_decode_audio(s32 id, u8* packet, u32 packet_size);
void proxchat_mix(s16* out_pcm, u32 num_samples);

#endif