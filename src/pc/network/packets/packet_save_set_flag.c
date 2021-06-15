#include <stdio.h>
#include "../network.h"
#include "game/save_file.h"

static bool sIgnoreSendSaveSetFlag = false;

void network_send_save_set_flag(u32 flags) {
    // prevent replying to the packet we just received
    if (sIgnoreSendSaveSetFlag) { return; }

    struct Packet p;
    packet_init(&p, PACKET_SAVE_SET_FLAG, true, false);
    packet_write(&p, &flags, sizeof(u32));
    network_send(&p);
}

void network_receive_save_set_flag(struct Packet* p) {
    u32 flags;
    packet_read(p, &flags, sizeof(u32));
    save_file_set_flags(flags);
}
