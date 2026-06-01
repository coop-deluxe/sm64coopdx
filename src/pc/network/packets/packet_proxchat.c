#include "../network.h"

#include "pc/proximity_chat.h"

void network_send_proxchat_frame(void) {
    struct Packet p = {};

    u8 frame[4096];
    u32 size = proxchat_encode_audio(frame, sizeof(frame));
    if (size == 0) return;

    packet_init(&p, PACKET_PROXCHAT_FRAME, false, PLMT_NONE);
    packet_write(&p, &size, sizeof(u32));
    packet_write(&p, frame, size);
    
    network_send(&p);
}

void network_receive_proxchat_frame(struct Packet* p) {
    u32 frame_size;
    packet_read(p, &frame_size, sizeof(u32));

    u8 frame_data[frame_size];
    packet_read(p, frame_data, frame_size);

    proxchat_decode_audio(
        network_player_from_global_index(p->orderedFromGlobalId)->localIndex,
        frame_data, frame_size
    );
}

void network_send_proxchat_muted(s32 globalIndex, bool muted) {
    struct Packet p = {};

    packet_init(&p, PACKET_PROXCHAT_GLOBAL_MUTE, false, PLMT_NONE);
    packet_write(&p, &globalIndex, sizeof(s32));
    packet_write(&p, &muted, sizeof(bool));

    network_send(&p);
}

void network_receive_proxchat_muted(struct Packet* p) {
    s32 globalIndex;
    bool muted;

    packet_read(p, &globalIndex, sizeof(s32));
    packet_read(p, &muted, sizeof(bool));

    if (!network_player_from_global_index(p->orderedFromGlobalId)->moderator) return;

    if (muted) *proxchat_player_muted(network_player_from_global_index(globalIndex)->localIndex) |=  PROXCHAT_MUTE_GLOBAL;
    else       *proxchat_player_muted(network_player_from_global_index(globalIndex)->localIndex) &= ~PROXCHAT_MUTE_GLOBAL;
}