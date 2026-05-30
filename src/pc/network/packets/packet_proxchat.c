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

    proxchat_decode_audio(p->localIndex, frame_data, frame_size);
}
