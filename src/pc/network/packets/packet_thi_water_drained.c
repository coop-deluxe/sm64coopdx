#include "game/object_list_processor.h"
#include "../network.h"
#include "pc/debuglog.h"

void network_send_thi_water_drained() {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_THI_WATER_DRAINED, true, PLMT_LEVEL);
    packet_write(&p, &gTHIWaterDrained, sizeof(gTHIWaterDrained));

    network_send(&p);
}

void network_receive_thi_water_drained(struct Packet *p) {
    packet_read(p, &gTHIWaterDrained, sizeof(gTHIWaterDrained));
}