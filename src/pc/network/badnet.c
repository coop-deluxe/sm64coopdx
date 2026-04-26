#include "badnet.h"

#include "socket/socket.h"
#include "pc/utils/misc.h"

/*

    Bad Net is a tool for simulating a bad network connection.

    It wraps gNetworkSystemSocket and manipulates out-going packets
    to recreate the same types of issues caused by an internet connection;
    all from the comfort of your direct connection over localhost.

*/

struct DelayedPacket {
    u8 localIndex;
    u8* data;
    u16 dataLength;
    f64 time;
    struct DelayedPacket* next;
};

// Requires reconnection
// Set to `true` to wrap gNetworkSystemSocket
bool gBadNetEnabled = true;

// Time in seconds for round trip
// 0.1 -> Good
// 0.2 -> Common
// 0.3 -> Across the sea
// 1.0 -> Too slow!
f64 gBadNetLatency = 0.0;

//Add an additional random delay to packets (Can cause out of order packets)
// 0.0 -> No Jitter
// 0.5 -> Extra 0 to 500ms extra delay.
f64 gBadNetLatencyJitter = 0.0;

// Randomly drop packets
// 0.0 -> No Packets Lost
// 1.0 -> All Packets Lost
f64 gBadNetPacketLoss = 0.0;

// Chance of packet being sent again. (Warning: This stacks! Use small values)
// 0.0 -> No duplication
// 0.1 -> Every packet has a 10% chance of
// 1.0 -> :Skull:
f64 gBadNetPacketDuplicate = 0.0;

struct NetworkSystem *gNetworkSystemBadNetWraps = &gNetworkSystemSocket;

struct DelayedPacket* delayedPackets = NULL;

static bool ns_badnet_initialize(enum NetworkType networkType, bool reconnecting) {
    return gNetworkSystemBadNetWraps->initialize(networkType, reconnecting);
}

static s64 ns_badnet_get_id(u8 localId) {
    return gNetworkSystemBadNetWraps->get_id(localId);
}

static char* ns_badnet_get_id_str(u8 localId) {
    return gNetworkSystemBadNetWraps->get_id_str(localId);
}

static void ns_badnet_save_id(u8 localId, s64 networkId) {
    gNetworkSystemBadNetWraps->save_id(localId, networkId);
}

static void ns_badnet_clear_id(u8 localId) {
    gNetworkSystemBadNetWraps->clear_id(localId);
}

static void* ns_badnet_dup_addr(u8 localIndex) {
    return gNetworkSystemBadNetWraps->dup_addr(localIndex);
}

static bool ns_badnet_match_addr(void* addr1, void* addr2) {
    return gNetworkSystemBadNetWraps->match_addr(addr1, addr2);
}

static void ns_badnet_update(void) {
    struct DelayedPacket* prev = NULL;
    struct DelayedPacket* p = delayedPackets;
    while(p) {
        struct DelayedPacket *next = p->next;
        if (clock_elapsed_f64() > p->time) {
            gNetworkSystemBadNetWraps->send(
                p->localIndex,
                gNetworkSystemBadNetWraps->dup_addr(p->localIndex),
                p->data,
                p->dataLength
                );
            free(p->data);
            free(p);
            if (prev) {
                prev->next = next;
            } else {
                delayedPackets = next;
            }
        } else {
            prev = p;
        }
        p = next;
    }

    gNetworkSystemBadNetWraps->update();
}

static f64 random_f64() {
    return (float)rand()/(float)RAND_MAX;
}

static int ns_badnet_send(u8 localIndex, UNUSED void* address, u8* data, u16 dataLength) {
    if (random_f64() > gBadNetPacketLoss) {
        do {
            struct DelayedPacket* p = malloc(sizeof(struct DelayedPacket));
            p->localIndex = localIndex;
            p->data = calloc(dataLength, sizeof(u8));
            memcpy(p->data, data, dataLength);
            p->dataLength = dataLength;
            p->time = clock_elapsed_f64() + (gBadNetLatency + gBadNetLatencyJitter * random_f64()) * 0.5;
            p->next = delayedPackets;
            delayedPackets = p;
        } while (random_f64() < gBadNetPacketDuplicate);
    }
    return dataLength;
}

static void ns_badnet_get_lobby_id(char* destination, u32 destLength) {
    gNetworkSystemBadNetWraps->get_lobby_id(destination, destLength);
}

static void ns_badnet_get_lobby_secret(char* destination, u32 destLength) {
    gNetworkSystemBadNetWraps->get_lobby_secret(destination, destLength);
}

static void ns_badnet_shutdown(bool reconnecting) {
    gNetworkSystemBadNetWraps->shutdown(reconnecting);
}

struct NetworkSystem gNetworkSystemBadNet = {
    .initialize       = ns_badnet_initialize,
    .get_id           = ns_badnet_get_id,
    .get_id_str       = ns_badnet_get_id_str,
    .save_id          = ns_badnet_save_id,
    .clear_id         = ns_badnet_clear_id,
    .dup_addr         = ns_badnet_dup_addr,
    .match_addr       = ns_badnet_match_addr,
    .update           = ns_badnet_update,
    .send             = ns_badnet_send,
    .get_lobby_id     = ns_badnet_get_lobby_id,
    .get_lobby_secret = ns_badnet_get_lobby_secret,
    .shutdown         = ns_badnet_shutdown,
    .requireServerBroadcast = true,
    .name             = "BadNet",
};
