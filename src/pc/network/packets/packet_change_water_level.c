#include "../network.h"
#include "game/object_list_processor.h"

void network_send_change_water_level(u8 index, s16 height) {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_CHANGE_WATER_LEVEL, true, PLMT_AREA);
    packet_write_uint8(&p, index);
    packet_write_int16(&p, height);
    network_send(&p);
    packet_clear(&p);
}

void network_receive_change_water_level(struct Packet* p) {
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8) + sizeof(s16));
    
    u8 index = packet_read_uint8(p);
    s16 height = packet_read_int16(p);

    if (gEnvironmentRegions && index % 6 == 0 && gEnvironmentRegionsLength > index) {
        gEnvironmentRegions[index] = height;
    }
}
