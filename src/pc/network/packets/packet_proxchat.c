#include "../network.h"

#include "pc/proximity_chat.h"

void network_send_proxchat_frame(void) {
    struct Packet p = {};

    u8 frame[4096];
    u32 size = proxchat_encode_audio(frame, sizeof(frame));
    if (size == 0) return;

    packet_init(&p, PACKET_PROXCHAT_FRAME, false, PLMT_AREA);
    packet_write(&p, &gNetworkPlayers[0].globalIndex, sizeof(u8));
    packet_write(&p, &size, sizeof(u32));
    packet_write(&p, frame, size);

    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) continue;
        if (proxchat_others_muted[i]) continue;
        network_send_to(i, &p);
    }
}

void network_receive_proxchat_frame(struct Packet* p) {
    u8 sender_global_index;
    packet_read(p, &sender_global_index, sizeof(u8));

    u32 frame_size;
    packet_read(p, &frame_size, sizeof(u32));

    u8 frame_data[frame_size];
    packet_read(p, frame_data, frame_size);
    
    proxchat_decode_audio(
        network_player_from_global_index(sender_global_index)->localIndex,
        frame_data, frame_size
    );
}

void network_send_proxchat_muted(s32 globalIndex, bool global, bool muted) {
    struct Packet p = {};

    packet_init(&p, PACKET_PROXCHAT_MUTE, false, PLMT_NONE);
    packet_write(&p, &globalIndex, sizeof(s32));
    packet_write(&p, &global, sizeof(bool));
    packet_write(&p, &muted, sizeof(bool));

    if (global) network_send(&p);
    else network_send_to(gNetworkPlayers[globalIndex].localIndex, &p);
}

void network_receive_proxchat_muted(struct Packet* p) {
    s32 globalIndex;
    bool muted, global;

    packet_read(p, &globalIndex, sizeof(s32));
    packet_read(p, &global, sizeof(bool));
    packet_read(p, &muted, sizeof(bool));

    struct NetworkPlayer* sender = network_player_from_global_index(p->orderedFromGlobalId);
    struct NetworkPlayer* receiver = network_player_from_global_index(globalIndex);

    if (global) {
        if (!sender->moderator && sender->globalIndex != 0) return;

        if (muted) *proxchat_player_muted(receiver->localIndex) |=  PROXCHAT_MUTE_GLOBAL;
        else       *proxchat_player_muted(receiver->localIndex) &= ~PROXCHAT_MUTE_GLOBAL;
    }
    else proxchat_others_muted[sender->localIndex] = muted;
}