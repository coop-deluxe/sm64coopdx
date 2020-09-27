#include <stdio.h>
#include "../network.h"
#include "game/save_file.h"

void network_send_save_file(s32 fileIndex) {
    assert(gNetworkType == NT_CLIENT);
    struct Packet p;
    packet_init(&p, PACKET_SAVE_FILE, true, false);
    packet_write(&p, &fileIndex, sizeof(s32));
    network_send_to(gNetworkPlayerServer->localIndex, &p);
}

void network_receive_save_file(struct Packet* p) {
    if (gNetworkType != NT_SERVER) { return; }
    s32 fileIndex = 0;
    packet_read(p, &fileIndex, sizeof(s32));
    save_file_do_save(fileIndex, FALSE);
}
