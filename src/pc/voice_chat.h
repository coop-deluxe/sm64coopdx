#ifndef VOICECHAT_H
#define VOICECHAT_H

#include "types.h"

#include <opus/opus.h>

enum VoiceChatType {
    VOICECHAT_TYPE_DISABLED,
    VOICECHAT_TYPE_VOICE,
    VOICECHAT_TYPE_PROXIMITY,
};

enum VoiceChatActivationMode {
    VOICECHAT_ACTMODE_DISABLED,
    VOICECHAT_ACTMODE_PUSH_TO_TALK,
    VOICECHAT_ACTMODE_THRESHOLD
};

enum VoiceChatError {
    VOICECHAT_ERR_NONE,
    VOICECHAT_ERR_NO_MICROPHONE,
    VOICECHAT_ERR_FAILED_TO_INITIALIZE,
    VOICECHAT_ERR_FAILED_TO_ENCODE,
    VOICECHAT_ERR_FAILED_TO_DECODE,
};

enum VoiceChatMuteState {
    VOICECHAT_UNMUTED     = 0,

    VOICECHAT_MUTE_LOCAL    = (1 << 0),
    VOICECHAT_MUTE_GLOBAL   = (1 << 1),
    VOICECHAT_MUTE_DEAFENED = (1 << 2),
};

struct VoiceBuffer {
    bool dynamic;
    u32 size, capacity;
    u32 tail, head;
    u8* bytes;
};

struct VoicePlayerInternal {
    struct VoiceBuffer buffer;
    union {
        OpusEncoder* encoder;
        OpusDecoder* decoder;
    };
};

struct VoicePlayer {
    bool talking;
    u32 volume;
    enum VoiceChatError error;
    enum VoiceChatMuteState clientMutedState; // did I mute them?
    enum VoiceChatMuteState playerMutedState; // did they mute themselves?
    struct VoicePlayerInternal internal;
};

extern struct VoicePlayer gVoicePlayers[MAX_PLAYERS];
extern struct VoicePlayer* gVoicePlayer;

extern bool gVoiceChatLoopback;
extern float gVoiceChatMicLevel;
extern s32 gVoiceChatDefaultChannel;

void voicechat_init();
void voicechat_shutdown();

void voicechat_init_player(s32 id);

u32 voicechat_encode_audio(u8* packet, u32 max_size);
void voicechat_decode_audio(s32 id, u8* packet, u32 packet_size);
void voicechat_mix(s16* out_pcm, u32 num_samples);

/* |description|Toggles mute state on the current player|descriptionEnd| */
void voicechat_toggle_mute();
/* |description|Toggles global mute state on another player|descriptionEnd| */
void voicechat_toggle_global_mute(s32 id);
/* |description|Toggles mute state on another player for the current client|descriptionEnd| */
void voicechat_toggle_mute_other(s32 id);
/* |description|Toggles deafen state on the current player|descriptionEnd| */
void voicechat_toggle_deafen();
/* |description|Sets mute state on the current player|descriptionEnd| */
void voicechat_set_mute(bool muted);
/* |description|Sets global mute state on another player|descriptionEnd| */
void voicechat_set_global_mute(s32 id, bool muted);
/* |description|Sets mute state on another player for the current client|descriptionEnd| */
void voicechat_set_mute_other(s32 id, bool muted);
/* |description|Sets deafen state on the current player|descriptionEnd| */
void voicechat_set_deafen(bool muted);

/* |description|Creates a new voice channel and returns its ID|descriptionEnd| */
s32 voicechat_create_channel();
/* |description|
Removes a voice channel.
All players in the to-be-removed channel will get moved to the default channel
|descriptionEnd| */
void voicechat_remove_channel(s32 channel);

/* |description|Returns the channel ID that the player is in|descriptionEnd| */
s32 voicechat_get_channel(s32 local_id);
/* |description|Moves a player to another channel|descriptionEnd| */
void voicechat_switch_channel(s32 local_id, s32 channel);

/* |description|Sets if players in `channel` should be able to hear players in `other_channel`|descriptionEnd| */
void voicechat_hear(s32 channel, s32 other_channel, bool can_hear);
/* |description|Checks if players in `channel` can hear players in `other_channel`|descriptionEnd| */
void voicechat_can_hear(s32 channel, s32 other_channel);

#endif