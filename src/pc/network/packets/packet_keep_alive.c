#include <stdio.h>
#include "../network.h"
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_keep_alive(u8 localIndex) {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_KEEP_ALIVE, false, PLMT_NONE);
    network_send_to(localIndex, &p);
    LOG_INFO("Sending keep alive");
    
    packet_clear(&p);
}

void network_receive_keep_alive(UNUSED struct Packet* p) {
    LOG_INFO("Received keep alive");
}
