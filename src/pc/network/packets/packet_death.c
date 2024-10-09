#include <stdio.h>
#include "sm64.h"
#include "../network.h"

void network_send_death(void) {
    if (gMarioStates[0].numLives < -1) { gMarioStates[0].numLives = -1; }
    struct Packet p = { 0 };
    packet_init(&p, PACKET_DEATH, true, PLMT_NONE);
    packet_write(&p, &gMarioStates[0].numLives, sizeof(u8));
    network_send(&p);
}

void network_receive_death(struct Packet* p) {
    u8 numLives = 0;
    packet_read(p, &numLives, sizeof(u8));
    if (numLives < gMarioStates[0].numLives) {
        gMarioStates[0].numLives = numLives;
    }
}
