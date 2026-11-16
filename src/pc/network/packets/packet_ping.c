#include <stdio.h>
#include "../network.h"
#include "pc/utils/misc.h"
#include "pc/debuglog.h"

void network_send_ping(struct NetworkPlayer* toNp) {
    if (toNp == NULL) { return; }

    struct Packet p = { 0 };
    f64 timestamp = clock_elapsed_f64();

    toNp->lastPingSent = clock_elapsed();

    packet_init(&p, PACKET_PING, false, PLMT_NONE);
    packet_write_uint8(&p, toNp->globalIndex);
    packet_write_float64(&p, timestamp);
    network_send_to(toNp->localIndex, &p);
    packet_clear(&p);

    //LOG_INFO("tx ping");
}

void network_receive_ping(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8) + sizeof(f64));
    
    //LOG_INFO("rx ping");

    u8 globalIndex = packet_read_uint8(p);
    f64 timestamp = packet_read_float64(p);

    struct Packet p2 = { 0 };
    packet_init(&p2, PACKET_PONG, false, PLMT_NONE);
    packet_write_uint8(&p2, globalIndex);
    packet_write_float64(&p2, timestamp);
    network_send_to(p->localIndex, &p2);
    packet_clear(&p2);
}

void network_receive_pong(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8) + sizeof(f64));
    
    f64 now = clock_elapsed_f64();

    u8 globalIndex = packet_read_uint8(p);
    f64 timestamp = packet_read_float64(p);

    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving pong from inactive player!");
        return;
    }

    u32 ping = (now - timestamp) * 1000;
    if (ping > np->ping) {
        np->ping = ping;
    } else {
        np->ping = np->ping * 0.7f + ping * 0.3f;
    }
    if (np->ping > 1000) { np->ping = 1000; }
    //LOG_INFO("rx pong from %u: %u", globalIndex, ping);
}
