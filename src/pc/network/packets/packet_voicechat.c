#include "../network.h"

#include "pc/voice_chat.h"

// max frame size for opus frames; defined by the opus spec
#define OPUS_MAX_FRAME_SIZE 1275

void network_send_voicechat_frame(void) {
    struct Packet p = {};

    u8 frame[OPUS_MAX_FRAME_SIZE];
    u32 size = voicechat_encode_audio(frame, sizeof(frame));
    if (size == 0) return;

    packet_init(&p, PACKET_VOICECHAT_FRAME, false, gServerSettings.voiceChat == VOICECHAT_TYPE_PROXIMITY ? PLMT_AREA : PLMT_NONE);
    packet_write(&p, &size, sizeof(u32));
    packet_write(&p, frame, size);

    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) continue;
        if (gVoicePlayers[i].playerMutedState) continue;
        if (!voicechat_can_hear(gVoicePlayer->channel, gVoicePlayers[i].channel)) continue;

        network_send_to(i, &p);
    }
}

void network_receive_voicechat_frame(struct Packet* p) {
    u32 frame_size;
    packet_read(p, &frame_size, sizeof(u32));

    if (frame_size > OPUS_MAX_FRAME_SIZE) return;

    u8 frame_data[frame_size];
    packet_read(p, frame_data, frame_size);
    
    voicechat_decode_audio(
        network_local_index_from_global(p->orderedFromGlobalId),
        frame_data, frame_size
    );
}

void network_send_voicechat_muted(u8 globalIndex, u8 mask, bool muted) {
    struct Packet p = {};

    packet_init(&p, PACKET_VOICECHAT_MUTE, false, PLMT_NONE);
    packet_write(&p, &globalIndex, sizeof(u8));
    packet_write(&p, &mask, sizeof(u8));
    packet_write(&p, &muted, sizeof(bool));

    if (mask == VOICECHAT_MUTE_LOCAL) network_send_to(gNetworkPlayers[globalIndex].localIndex, &p);
    else network_send(&p);
}

void network_receive_voicechat_muted(struct Packet* p) {
    u8 globalIndex, mask;
    bool muted;

    packet_read(p, &globalIndex, sizeof(u8));
    packet_read(p, &mask, sizeof(u8));
    packet_read(p, &muted, sizeof(bool));

    struct NetworkPlayer* sender = network_player_from_global_index(p->orderedFromGlobalId);
    struct NetworkPlayer* receiver = network_player_from_global_index(globalIndex);

    if (!sender) {
        if (p->orderedFromGlobalId == 0 && mask & VOICECHAT_MUTE_GLOBAL)
            voicechat_push_pending_global_mute(globalIndex);
        return;
    }

    if (!sender->moderator && sender->globalIndex != 0) mask &= ~VOICECHAT_MUTE_GLOBAL;

    if (mask & VOICECHAT_MUTE_GLOBAL) {
        if (muted) gVoicePlayers[receiver->localIndex].clientMutedState |=  VOICECHAT_MUTE_GLOBAL;
        else       gVoicePlayers[receiver->localIndex].clientMutedState &= ~VOICECHAT_MUTE_GLOBAL;
    }

    if (muted) gVoicePlayers[sender->localIndex].playerMutedState |=  (mask & ~VOICECHAT_MUTE_GLOBAL);
    else       gVoicePlayers[sender->localIndex].playerMutedState &= ~(mask & ~VOICECHAT_MUTE_GLOBAL);
}