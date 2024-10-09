#include <stdio.h>
#include "../network.h"
#include "pc/utils/misc.h"
#include "pc/debuglog.h"

void network_send_ping(struct NetworkPlayer* toNp) {
    struct Packet p = { 0 };
    f64 timestamp = clock_elapsed_f64();

    toNp->lastPingSent = clock_elapsed();

    packet_init(&p, PACKET_PING, false, PLMT_NONE);
    packet_write(&p, &toNp->globalIndex, sizeof(u8));
    packet_write(&p, &timestamp,        sizeof(f64));
    network_send_to(toNp->localIndex, &p);

    //LOG_INFO("tx ping");
}

void network_receive_ping(struct Packet* p) {
    //LOG_INFO("rx ping");

    u8 globalIndex;
    f64 timestamp;

    packet_read(p, &globalIndex, sizeof(u8));
    packet_read(p, &timestamp,   sizeof(f64));

    struct Packet p2 = { 0 };
    packet_init(&p2, PACKET_PONG, false, PLMT_NONE);
    packet_write(&p2, &globalIndex, sizeof(u8));
    packet_write(&p2, &timestamp,   sizeof(f64));
    network_send_to(p->localIndex, &p2);
}

void network_receive_pong(struct Packet* p) {
    f64 now = clock_elapsed_f64();

    u8 globalIndex;
    f64 timestamp;

    packet_read(p, &globalIndex, sizeof(u8));
    packet_read(p, &timestamp,   sizeof(f64));

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
