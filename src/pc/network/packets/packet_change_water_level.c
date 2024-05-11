#include "../network.h"
#include "game/object_list_processor.h"

void network_send_change_water_level(u8 index, s16 height) {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_CHANGE_WATER_LEVEL, true, PLMT_AREA);
    packet_write(&p, &index, sizeof(u8));
    packet_write(&p, &height, sizeof(s16));

    network_send(&p);
}

void network_receive_change_water_level(struct Packet* p) {
    u8 index;
    s16 height;
    packet_read(p, &index, sizeof(u8));
    packet_read(p, &height, sizeof(s16));

    if (gEnvironmentRegions && index % 6 == 0 && gEnvironmentRegionsLength > index) {
        gEnvironmentRegions[index] = height;
    }
}
