#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"

void network_send_keep_alive(void) {
    struct Packet p;
    packet_init(&p, PACKET_KEEP_ALIVE, false, false);
    network_send(&p);
    gLastNetworkSend = clock();
    LOG_INFO("sending keep alive");
}

void network_receive_keep_alive(struct Packet* p) {
    LOG_INFO("received keep alive");
}
