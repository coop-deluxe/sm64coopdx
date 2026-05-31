#ifndef PROXCHAT_H
#define PROXCHAT_H

#include "types.h"

extern bool proxchat_muted;
extern bool proxchat_loopback;
extern float proxchat_mic_level;

enum ProxchatActivationMode {
    PROXCHAT_ACTMODE_DISABLED,
    PROXCHAT_ACTMODE_PUSH_TO_TALK,
    PROXCHAT_ACTMODE_THRESHOLD
};

void proxchat_init();
bool proxchat_inited();
void proxchat_shutdown();

f32* proxchat_player_volume(s32 id);
bool proxchat_player_is_talking(s32 id);

u32 proxchat_encode_audio(u8* packet, u32 max_size);
void proxchat_decode_audio(s32 id, u8* packet, u32 packet_size);
void proxchat_mix(s16* out_pcm, u32 num_samples);

#endif