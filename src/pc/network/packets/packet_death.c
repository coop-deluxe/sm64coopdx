#include <stdio.h>
#include "sm64.h"
#include "../network.h"

void network_send_death(void) {
    if (gMarioStates[0].numLives < -1) { gMarioStates[0].numLives = -1; }
    struct Packet p = { 0 };
    packet_init(&p, PACKET_DEATH, true, PLMT_NONE);
    packet_write_uint8(&p, gMarioStates[0].numLives);
    network_send(&p);
    packet_clear(&p);
}

void network_receive_death(struct Packet* p) {
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8));
    
    u8 numLives = packet_read_uint8(p);
    if (numLives < gMarioStates[0].numLives) {
        gMarioStates[0].numLives = numLives;
    }
}
